#ifndef SOFTENG_751_ASSIGNMENT_PARASTATS_STATSTRUCTS_H
#define SOFTENG_751_ASSIGNMENT_PARASTATS_STATSTRUCTS_H

// Add openCL library, declare enable_exceptions
// NVIDIA yet to support OpenCL 2.0
#define NVIDIA

#ifdef WIN32
#pragma GCC diagnostic ignored "-Wignored-attributes"
#endif

#if defined(__APPLE__) || defined(__MACOSX)
#define __CL_ENABLE_EXCEPTIONS
#define CL_USE_DEPRECATED_OPENCL_1_2_APIS
#include "CL/cl.hpp"
#elif defined(NVIDIA)
#define __CL_ENABLE_EXCEPTIONS
#define CL_USE_DEPRECATED_OPENCL_1_2_APIS
#include "CL/cl.hpp"
#else
#define CL_HPP_ENABLE_EXCEPTIONS
#define CL_HPP_TARGET_OPENCL_VERSION 200
#include "CL/cl2.hpp"
#endif

typedef struct moments {
    cl_double m1;
    cl_double m2;
    cl_double m3;
    cl_double m4;
} __attribute__ ((packed)) moments;

typedef struct rawStats {
    cl_double min;
    cl_double max;
    moments rawMoments;
} __attribute__ ((packed)) rawStats;

#endif //SOFTENG_751_ASSIGNMENT_PARASTATS_STATSTRUCTS_H
