# ParaStats
__Parallel computation of statistical values__

[![Build Status](https://travis-ci.com/mkem114/SOFTENG-751-Assignment-ParaStats.svg?token=4tn5PhULbqssssJGM5Gs&branch=master)](https://travis-ci.com/mkem114/SOFTENG-751-Assignment-ParaStats)

When working with data sets created from natural processes, it is often important to get statistical values for these data-sets. This assignment implements the calculation of statistical values over large data sets in parallel. The algorithms are implemented in OpenCL (Open Computing Language), a (low level) language based on C (C99) and an API for implementing high performance and parallel computing code. OpenCL's goal is to be cross platform, in particular for the programming of acceleration units, such as graphics cards (GPUs) or FPGAs. Specifically we have implemented and accelerate the calculation of statistical values for large input data sets.

### Authors
- Blair Cox (bcox280)
- Logan Small (lsma604)
- Michael Kemp (mkem114)

### License
- MIT

### Running the executable
You will need to install a runtime, and implementation of OpenCL:
##### OSX (not tested)
- OpenCL runtimes are provided by default by Apple
##### Linux (Debian-based and Arch-based tested)
- You'll need a loader; "ocl-icd-libopencl1" on Debian-based systems, "libOpenCL1" on OpenSuse-based systems, "ocl-icd" for Arch-based systems
- NVIDIA devices, install "nvidia-XXX" drivers for Debian-based systems, "opencl-nvidia" for Arch-based systems
- AMD devices, (untested), install "opencl-mesa" on Arch-based systems
- Intel devices, "intel-opencl-runtime" and "beignet" on Arch-based systems
- To check which OpenCL device implementations are currently on your system, "ls /etc/OpenCL/vendors" (you'll need at least 1 for running the OpenCL implementation)
##### Windows (tested)
- Install the relevant OpenCL runtimes/drivers for your devices from their websites
- The provided executable (under releases) works on UG4 windows installation, you'll need to source the OpenCL.dll (from your device driver), or find one online.
##### Why won't it run?
- Make sure you have the /src/kernels folder, this contains the critical OpenCL kernel(s)
- Make sure the executables are in the /bin folder
- Make sure the sample data files (if you're using them) are in the /data folder

### Compiling
##### OSX (not tested)
- Apple does not provide OpenCL C++ header files, you'll have to download one and include it the compilation process
- Run "cmake .", "make SOFTENG-751-Assignment-ParaStats", and "make SOFTENG-751-Assignment-ParaStats-Test".
##### Linux (cinnamon, arch tested)
- To compile OpenCL you need the -lOpenCL library, install "ocl-icd-opencl-dev" on Debian-based, "ocl-icd" on Arch-based and OpenSuse-based
- We also need the headers/bindings, install "opencl-headers"
- If it can't find the library, you may need a symbolic link: e.g. "ln -s /usr/lib/x86_64-linux-gnu/libOpenCL.so.1 /usr/local/lib/libOpenCL.so" in Debian-based systems or "ln -s /usr/lib64/libOpenCL.so.1 /usr/lib64/libOpenCL.so" in OpenSuse
- Run "cmake .", "make SOFTENG-751-Assignment-ParaStats", and "make SOFTENG-751-Assignment-ParaStats-Test".
##### Windows (tested)
- Installation of an OpenCL SDK should provide the header files (the Intel SDK is what we used and was least painful)
- For compiling we installed MinGW-w64 (as recommended by JetBrains) and Visual Studio C++ Compiler is not tested
- To compile either install CLion and it will manage the process for you or run "cmake .", "make SOFTENG-751-Assignment-ParaStats", and "make SOFTENG-751-Assignment-ParaStats-Test" in the MinGW-w64 environment
