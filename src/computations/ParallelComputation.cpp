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
    std::string input = "../src/kernels/stats.cl"; // Kernel to build
    ::size_t work_group_size;

    // Random vector input size
    ::size_t input_vect_size = 1024;
    // Device buffers
    cl::Buffer d_input;

    try // Catch OpenCL errors
    {
        /************************
         * Step 1: Select device and create context and queue
         */
        // TODO: Implement choosing of devices from commandline arguments
        cl_uint deviceIndex = 1; // 0 for CPU, 1 for GPU if available

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
        cout << numDevices << " devices found!" << endl;

        // Check device index in range
        if (deviceIndex >= numDevices) {
            cout << "Invalid device index" << endl;
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
        cout << "Using OpenCL device: " << name << endl;

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
            cout << "Cannot open file: " << input << endl;
            exit(1);
        }
        cl::Program program(context, std::string(
                std::istreambuf_iterator<char>(stream),
                (std::istreambuf_iterator<char>())), true);

        // Create the kernel object for querying information
        cl::Kernel ko_stats(program, "stats");

        // Get the work group size
        // TODO: Better determine work group size
        work_group_size = ko_stats.getWorkGroupInfo<CL_KERNEL_WORK_GROUP_SIZE>(device);

        // Create kernel object, use OpenCL 2 syntax if not using nvidia
#ifdef NVIDIA
        cl::make_kernel<cl::Buffer, cl::Buffer, cl::LocalSpaceArg, cl::LocalSpaceArg> stats(program, "stats");
#else
        cl::KernelFunctor<cl::Buffer, cl::Buffer, cl::LocalSpaceArg, cl::LocalSpaceArg> stats(program, "stats");
#endif

        // Now that we know the size of the work_groups, we can set the number of work
        // groups, the actual number of steps, and the step size
        ::size_t nwork_groups = input_vect.size() / work_group_size;
        if (nwork_groups < 1) {
            nwork_groups = device.getInfo<CL_DEVICE_MAX_COMPUTE_UNITS>();
            work_group_size = input_vect.size() / nwork_groups;
        }
        cout << nwork_groups << " work groups, " << work_group_size << " work items per group" << endl << endl;

        // Declare output buffer
        cl::Buffer d_output_stats = cl::Buffer(context, CL_MEM_WRITE_ONLY, sizeof(rawStats)*nwork_groups);

        /************************
         * Step 3: Run program
         */

        // Execute the kernel over the entire range of our 1d input data set
        // using the maximum number of work group items for this device
        stats(
                cl::EnqueueArgs(
                        queue,
                        cl::NDRange(input_vect.size()),
                        cl::NDRange(work_group_size)
                ),
                d_input,
                d_output_stats,
                cl::Local(sizeof(double)*work_group_size),
                cl::Local(sizeof(moments)*(work_group_size/2)));

        // TODO update summary statistics

        // Get output vector
        std::vector<rawStats> stat_values(nwork_groups);
        cl::copy(queue, d_output_stats, stat_values.begin(), stat_values.end());
        rawStats final_value = stat_values[0];
        double mean_sum = stat_values[0].rawMoments.m1;
        // Reduce results on host
        for (int i = 1; i < nwork_groups; i++) {
            final_value.min = (final_value.min>stat_values[i].min) ? stat_values[i].min : final_value.min;
            final_value.max = (final_value.max<stat_values[i].max) ? stat_values[i].max : final_value.max;
            mean_sum += stat_values[i].rawMoments.m1;
        }
        final_value.rawMoments.m1 = mean_sum / nwork_groups;
        // TODO: Reduce m2, m3, m4 on host
        // TODO: Reduce moments incrementally to prevent overflow
//        double delta;
//        for (int i = 1; i < ceil(log(nwork_groups, 2)); i*=2) { // Moments
//            for (int j = 1; j < nwork_groups; j++) {
//                if (!(i % 2) && ((i + 1) < nwork_groups)) {
//                    delta = stat_values[i + 1].rawMoments.m1 - stat_values[i].rawMoments.m1;
//                    stat_values[i].rawMoments.m1 = stat_values[i].rawMoments.m1 + (delta * 0.5);
//                }
//            }
//        }
        // Print results to screen
        printf("Min value = %.17g\n", final_value.min);
        printf("Max value = %.17g\n", final_value.max);
        printf("M1 = %.17g\n", final_value.rawMoments.m1);
        printf("M2(workgroup1) = %.17g\n", final_value.rawMoments.m2);
        printf("M3(workgroup1) = %.17g\n", final_value.rawMoments.m3);
        printf("M4(workgroup1) = %.17g\n", final_value.rawMoments.m4);
    }
    catch (cl::Error& err) {
        cout << "Exception\n";
        cerr << "ERROR: " << err.what() << "(" << err.err() << ")" << endl;
    }

}

SummaryStatistics ParallelComputation::provideProgressUpdate() {
    return SummaryStatistics();
}
