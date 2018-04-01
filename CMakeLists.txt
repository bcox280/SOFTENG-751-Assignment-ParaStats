# Minimal version of CMake
cmake_minimum_required (VERSION 3.8)

# Define project name
project (SOFTENG-751-Assignment-ParaStats)

# Include OpenCL includes
if (WIN32)
    find_package( OpenCL REQUIRED )
    include_directories( ${OPENCL_INCLUDE_DIR} )
else()
    set(OPENCL_LIBRARIES OpenCL)
endif()

# Source code of application
set(SOURCE_FILES hello_world.cpp)

# Compiler flags
set(CMAKE_CXX_STANDARD 17)

# Set up executable
add_executable (SOFTENG-751-Assignment-ParaStats ${SOURCE_FILES})
target_link_libraries(SOFTENG-751-Assignment-ParaStats ${OPENCL_LIBRARIES})