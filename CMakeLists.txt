cmake_minimum_required (VERSION 3.2)

# Define project name
project (SOFTENG-751-Assignment-ParaStats)

# Include OpenCL includes
if (WIN32)
    set(CMAKE_CXX_FLAGS "-static -static-libgcc -static-libstdc++")
    #Specify location of new method to find OpenCL
    set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/")

    #Find where OpenCL /include/ dir is
    find_package( OpenCL REQUIRED )

    include_directories( ${OPENCL_DIR} )
else(WIN32)
    set(OPENCL_LIBRARIES OpenCL)
endif(WIN32)

# Source code of application
set(SOURCE_FILES
        src/main.cpp
        src/kernels
        src/statistics
        src/computations
        src/interfaces)
include_directories(src/computations src/statistics src/interfaces)

# Compiler flags
set(CMAKE_CXX_STANDARD 17)

# Set up executable
add_executable (SOFTENG-751-Assignment-ParaStats ${SOURCE_FILES})
target_link_libraries(SOFTENG-751-Assignment-ParaStats ${OPENCL_LIBRARIES})










###### T E S T I N G ######
# from https://github.com/google/googletest/tree/master/googletest

# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
if(result)
    message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
if(result)
    message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines the gtest and gtest_main targets.
add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
        ${CMAKE_BINARY_DIR}/googletest-build
        EXCLUDE_FROM_ALL)

# Source code of application
set(TEST_SOURCE_FILES
        src
        src/computations
        src/statistics
        test
        test/statistics
        test/computations
        test/main_test.cpp
        test/computations/ComputationTest.cpp
        test/statistics/SummaryStatisticsTest.cpp)

# Set up executable
add_executable (SOFTENG-751-Assignment-ParaStats-Test ${TEST_SOURCE_FILES})
target_link_libraries(SOFTENG-751-Assignment-ParaStats-Test ${OPENCL_LIBRARIES} gtest_main)
##### / T E S T I N G #####
