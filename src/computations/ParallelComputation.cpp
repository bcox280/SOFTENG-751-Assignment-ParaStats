#include "ParallelComputation.hpp"

ParallelComputation::ParallelComputation(const string &fileName) : AbstractComputation(fileName) {
    // Catch OpenCL errors
    try {
        /************************
         * Step 1: Select device and create context and queue
         */
        // TODO: Implement choosing of devices from commandline arguments
        cl_uint deviceIndex; // 0 for CPU, 1 for GPU if available

        // Get list of platforms
        std::vector<cl::Platform> platforms;
        cl::Platform::get(&platforms);

        // Enumerate devices
        std::vector<cl::Device> devices;
        for (auto &platform : platforms) {
            std::vector<cl::Device> plat_devices;
            platform.getDevices(CL_DEVICE_TYPE_ALL, &plat_devices);
            devices.insert(devices.end(), plat_devices.begin(), plat_devices.end());
        }
        string user_input = "";
        // Get list of devices
        unsigned long numDevices = devices.size();
        cout << numDevices << " devices found!" << endl;

        // Get device name
        std::string name[numDevices];
        cl_device_info info = CL_DEVICE_NAME;
        for (int i = 0; i < numDevices; i++) {
            // Special case for AMD
#ifdef CL_DEVICE_BOARD_NAME_AMD
            devices[i].getInfo(CL_DEVICE_VENDOR, &name[i]);
            if (strstr(name[i].c_str(), "Advanced Micro Devices")) {
                info = CL_DEVICE_BOARD_NAME_AMD;
            }
#endif
            devices[i].getInfo(info, &name[i]);
        }

        for (int i = 0; i < numDevices; i++) {
            cout << "Device " << i << ": " << name[i] << endl;
        }
        while(true) {
            cout << "Select the device you would like to use: (0 - " << numDevices-1 << ")" << endl;
            cin >> deviceIndex;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cout << "Input was not a number" << endl;
            } else if (deviceIndex >= 0 && deviceIndex < numDevices) {
                break;
            } else {
                cout << "Invalid device index" << endl;
            }
        }

        // Select device to use
        cl::Device device = devices[deviceIndex];
        _device = device;

        cout << "Using OpenCL device: " << name[deviceIndex] << endl;

        // TODO: Replace this section with a loop going through all devices
        std::vector<cl::Device> chosen_device;
        chosen_device.push_back(_device);
        cl::Context context(chosen_device);
        _context = context;
        //cl::Context context(CL_DEVICE_TYPE_ALL); // Context for all devices
        cl::CommandQueue queue(_context, _device);
        _queue = queue;

        /************************
         * Step 2: Create the kernel and program
         */

        // Load in kernel source, creating a program object for the context
        std::ifstream stream(_stats_src.c_str());
        if (!stream.is_open()) {
            cout << "Cannot open file: " << _stats_src << endl;
            exit(1);
        }
        cl::Program program(_context, std::string(
                std::istreambuf_iterator<char>(stream),
                (std::istreambuf_iterator<char>())), true);
        _program = program;

        // Create kernel object, use OpenCL 2 syntax if not using nvidia
#ifdef NVIDIA
        _stats.reset(new cl::make_kernel<cl::Buffer, cl::Buffer, cl::LocalSpaceArg, cl::LocalSpaceArg>(_program, "stats"));
#else
        _stats.reset(new cl::KernelFunctor<cl::Buffer, cl::Buffer, cl::LocalSpaceArg, cl::LocalSpaceArg>(_program, "stats"));
#endif

        // Create the kernel object for querying information
        cl::Kernel ko_stats(_program, "stats");
        _ko_stats = ko_stats;

        // Get the work group size
        // TODO: Better determine work group size
        _work_group_size = _ko_stats.getWorkGroupInfo<CL_KERNEL_WORK_GROUP_SIZE>(_device);

        // Now that we know the size of the work_groups, we can set the number of work
        // groups, the actual number of steps, and the step size
        _nwork_groups = _input_vect_size / _work_group_size;
        if (_nwork_groups < 1) {
            _nwork_groups = _device.getInfo<CL_DEVICE_MAX_COMPUTE_UNITS>();
            _work_group_size = _input_vect_size / _nwork_groups;
        }
        // DEBUG: Work group/item sizes
        cout << _nwork_groups << " work groups, " << _work_group_size << " work items per group" << endl << endl;

        // Declare output buffer
        _d_output_stats = cl::Buffer(_context, CL_MEM_WRITE_ONLY, sizeof(rawStats)*_nwork_groups);
    } catch (cl::Error& err) {
        cout << "Exception\n";
        cerr << "ERROR: " << err.what() << "(" << err.err() << ")" << endl;
    }
}

SummaryStatistics ParallelComputation::computeData() {

    const char *valueDelimiter = ",";
    const char *lineDelimiter = "\n";

    char *contents, *line, *indValue, *ptrContents, *ptrLine;
    std::ifstream inputStr(_fileName);

    if (inputStr) {
        //Create a buffer to read from
        std::streambuf *pFileBuffer = inputStr.rdbuf();
        std::streamsize size = pFileBuffer->pubseekoff(0, inputStr.end);
        //Change the internal pointer to point back at the start of the filej
        pFileBuffer->pubseekoff(0, inputStr.beg);
        contents = new char[size];
        //Get the sequence of characters specified (whole file) and copy it to contents
        pFileBuffer->sgetn(contents, size);
        //Close the stream
        inputStr.close();

        int count = 0;
        std::vector<double> input_vector;
        for (int j = 1;; j++, contents = nullptr) {
            //Split each chunk on a new line, while keeping the location of where the pointer is
            line = strtok_r(contents, lineDelimiter, &ptrContents);
            //If its a null pointer, end is found
            if (line == nullptr) {
                break;
            }

            // TODO Send off chunk to a worker thread

            for (;; line = nullptr) {
                //Split each line into individual values, while keeping the location of where the pointer is in the line
                indValue = strtok_r(line, valueDelimiter, &ptrLine);
                //If the value is not a null pointer we can add it to the vector, else we have reached the end of the line
                if (indValue != nullptr) {
                    count++;
                    input_vector.push_back(stod(indValue));
                    if (count == _input_vect_size) {
                        processOpenCL(input_vector);
                        count = 0;
                        input_vector.clear();
                    }
                } else {
                    break;
                }
            }
        }
    }

    return _summaryStats;
}

void ParallelComputation::processOpenCL(std::vector<double> input_vect) {
    // Catch OpenCL errors
    try {
        /************************
         * Step 3: Run program
         */

        // Input buffer copying from vect
        _d_input = cl::Buffer(_context, input_vect.begin(), input_vect.end(), true);

        // Execute the kernel over the entire range of our 1d input data set
        // using the maximum number of work group items for this device
        _stats.get()->functor_(
                cl::EnqueueArgs(
                        _queue,
                        cl::NDRange(input_vect.size()),
                        cl::NDRange(_work_group_size)
                ),
                _d_input,
                _d_output_stats,
                cl::Local(sizeof(double)*_work_group_size),
                cl::Local(sizeof(moments)*(_work_group_size/2)));

        // Get output vector
        std::vector<rawStats> stat_values(_nwork_groups);
        cl::copy(_queue, _d_output_stats, stat_values.begin(), stat_values.end());

        // Update summaryStats
        for (int i = 0; i < _nwork_groups; i++) {
            _summaryStats.updateStats(stat_values[i], _work_group_size);
        }
    } catch (cl::Error& err) {
        cout << "Exception\n";
        cerr << "ERROR: " << err.what() << "(" << err.err() << ")" << endl;
    }
}

SummaryStatistics ParallelComputation::provideProgressUpdate() {
    return _summaryStats;
}
