#ifndef SOFTENG_751_ASSIGNMENT_PARASTATS_PARALLELCOMPUTATION_H
#define SOFTENG_751_ASSIGNMENT_PARASTATS_PARALLELCOMPUTATION_H

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cstring>
#include "AbstractComputation.hpp"
#include "SummaryStatistics.hpp"

// Add openCL library, declare enable_exceptions
// NVIDIA yet to support OpenCL 2.0
#define CL_USE_DEPRECATED_OPENCL_1_2_APIS
#define NVIDIA

#ifdef NVIDIA
#define __CL_ENABLE_EXCEPTIONS
#define CL_USE_DEPRECATED_OPENCL_1_2_APIS
#pragma GCC diagnostic ignored "-Wignored-attributes"
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



/**
 * Header file for parallel computation, this class will provide the implementation
 * for the parallelised computation of the provided data
 */
class ParallelComputation : public AbstractComputation {
public:
    explicit ParallelComputation(const string &fileName);

    void computeData();

    SummaryStatistics provideProgressUpdate();
};

#endif //SOFTENG_751_ASSIGNMENT_PARASTATS_PARALLELCOMPUTATION_H
