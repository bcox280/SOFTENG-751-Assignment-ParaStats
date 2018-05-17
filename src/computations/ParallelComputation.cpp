#include "ParallelComputation.hpp"

std::vector<double> vect;

ParallelComputation::ParallelComputation(const string &fileName) : AbstractComputation(fileName) {

    const char *valueDelimiter = ",";
    const char *lineDelimiter = "\n";

    char *contents, *line, *indValue, *ptrContents, *ptrLine;
    std::ifstream inputStr(fileName);

    if (inputStr) {
        //Create a buffer to read from
        std::streambuf *pFileBuffer = inputStr.rdbuf();
        std::streamsize size = pFileBuffer->pubseekoff(0, inputStr.end);
        //Change the internal pointer to point back at the start of the file
        pFileBuffer->pubseekoff(0, inputStr.beg);
        contents = new char[size];
        //Get the sequence of characters specified (whole file) and copy it to contents
        pFileBuffer->sgetn(contents, size);
        //Close the stream
        inputStr.close();

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
                    vect.push_back(stod(indValue));
                } else {
                    break;
                }
            }
        }
    }
}

void ParallelComputation::computeData() {

    /************************
     * Step 0: Declare host variables
     */
    std::string input = "../src/kernels/minmax.cl"; // Kernel to build
    ::size_t work_group_size;

    // Random vector input size
    const unsigned int input_vect_size = 1024;
    // Device buffers
    cl::Buffer d_input;

    try // Catch OpenCL errors
    {
        /************************
         * Step 1: Select device and create context and queue
         */
        // TODO: Implement choosing of devices from commandline arguments
        cl_uint deviceIndex = 0; // 0 for CPU, 1 for GPU if available

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

        // Get list of devices
        unsigned long numDevices = devices.size();
        std::cout << endl << numDevices << " devices found!" << std::endl;

        // Check device index in range
        if (deviceIndex >= numDevices) {
            std::cout << "Invalid device index" << std::endl;
            return;
        }

        // Select device to use
        cl::Device device = devices[deviceIndex];
        // Get device name
        std::string name;
        cl_device_info info = CL_DEVICE_NAME;
        // Special case for AMD
#ifdef CL_DEVICE_BOARD_NAME_AMD
        device.getInfo(CL_DEVICE_VENDOR, &name);
        if (strstr(name.c_str(), "Advanced Micro Devices")) {
            info = CL_DEVICE_BOARD_NAME_AMD;
        }
#endif
        device.getInfo(info, &name);
        std::cout << "\nUsing OpenCL device: " << name << std::endl;

        // TODO: Replace this section with a loop going through all devices
        std::vector<cl::Device> chosen_device;
        chosen_device.push_back(device);
        cl::Context context(chosen_device);
        //cl::Context context(CL_DEVICE_TYPE_ALL); // Context for all devices
        cl::CommandQueue queue(context, device);

        std::vector<double> input_vect(input_vect_size);
        for(int i = 0; i < input_vect_size; i++) {
            input_vect[i]  = rand() / (double)RAND_MAX;
        }

        // Input buffer copying from vect
        d_input = cl::Buffer(context, input_vect.begin(), input_vect.end(), true);

        /************************
         * Step 2: Create the kernel and program
         */

        // Load in kernel source, creating a program object for the context
        std::ifstream stream(input.c_str());
        if (!stream.is_open()) {
            std::cout << "Cannot open file: " << input << std::endl;
            exit(1);
        }
        cl::Program program(context, std::string(
                std::istreambuf_iterator<char>(stream),
                (std::istreambuf_iterator<char>())), true);

        // Create the kernel object for querying information
        cl::Kernel ko_minmax(program, "minmax");

        // Get the work group size
        work_group_size = ko_minmax.getWorkGroupInfo<CL_KERNEL_WORK_GROUP_SIZE>(device);

        // Create kernel object, use OpenCL 2 syntax if not using nvidia
#ifndef NVIDIA
        cl::KernelFunctor<cl::Buffer, cl::Buffer, cl::LocalSpaceArg, cl::LocalSpaceArg> minmax(program, "minmax");
#else
        cl::make_kernel<cl::Buffer, cl::Buffer, cl::LocalSpaceArg, cl::LocalSpaceArg> minmax(program, "minmax");
#endif

        // Now that we know the size of the work_groups, we can set the number of work
        // groups, the actual number of steps, and the step size
        ::size_t nwork_groups = input_vect.size() / work_group_size;
        if (nwork_groups < 1) {
            nwork_groups = device.getInfo<CL_DEVICE_MAX_COMPUTE_UNITS>();
            work_group_size = input_vect.size() / nwork_groups;
        }
        cout << nwork_groups << endl;
        cout << work_group_size << endl;

        // Declare output buffer
        cl::Buffer d_output_stats = cl::Buffer(context, CL_MEM_WRITE_ONLY, sizeof(rawStats)*nwork_groups);

        /************************
         * Step 3: Run program
         */

        // Execute the kernel over the entire range of our 1d input data set
        // using the maximum number of work group items for this device
        minmax(
                cl::EnqueueArgs(
                        queue,
                        cl::NDRange(input_vect.size()),
                        //cl::NullRange,
                        cl::NDRange(work_group_size)
                ),
                d_input,
                d_output_stats,
                cl::Local(sizeof(double)*work_group_size),
                cl::Local(sizeof(double)*work_group_size));

        // TODO update summary statistics

        // Get output vector
        std::vector<rawStats> stat_values(nwork_groups);
        cl::copy(queue, d_output_stats, stat_values.begin(), stat_values.end());
        rawStats final_value = stat_values[0];
        // Reduce results on host
        for(int i = 1; i < nwork_groups; i++) {
            final_value.min = (final_value.min>stat_values[i].min) ? stat_values[i].min : final_value.min;
            final_value.max = (final_value.max<stat_values[i].max) ? stat_values[i].max : final_value.max;
        }
        // Print results to screen
        printf(" Min value = %f\n", final_value.min);
        printf(" Max value = %f\n", final_value.max);
    }
    catch (cl::Error& err) {
        std::cout << "Exception\n";
        std::cerr << "ERROR: " << err.what() << "(" << err.err() << ")" << std::endl;
    }

}

SummaryStatistics ParallelComputation::provideProgressUpdate() {
    return SummaryStatistics();
}
