cmake_minimum_required (VERSION 3.8)

# Define project name
project (SOFTENG-751-Assignment-ParaStats)

# Include OpenCL includes
if (WIN32)
    #Specify location of new method to find OpenCL
    set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/")

    #Find where OpenCL /include/ dir is
    find_package( OpenCL REQUIRED )

    include_directories( ${OPENCL_DIR} )
else(WIN32)
    set(OPENCL_LIBRARIES OpenCL)
endif(WIN32)

# Source code of application
set(SOURCE_FILES main.cpp)

# Compiler flags
set(CMAKE_CXX_STANDARD 17)


# Set up executable
add_executable (SOFTENG-751-Assignment-ParaStats ${SOURCE_FILES})
target_link_libraries(SOFTENG-751-Assignment-ParaStats ${OPENCL_LIBRARIES})
