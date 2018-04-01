cmake_minimum_required(VERSION 3.8)
project(SOFTENG-751-Assignment-ParaStats)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES hello_world.cpp)
add_executable(SOFTENG-751-Assignment-ParaStats ${SOURCE_FILES})
target_link_libraries(SOFTENG-751-Assignment-ParaStats OpenCL)
