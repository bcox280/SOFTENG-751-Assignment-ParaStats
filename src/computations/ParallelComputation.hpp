#ifndef SOFTENG_751_ASSIGNMENT_PARASTATS_PARALLELCOMPUTATION_H
#define SOFTENG_751_ASSIGNMENT_PARASTATS_PARALLELCOMPUTATION_H

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cstring>
#include <memory>
#include <functional>
#include "statStructs.hpp"
#include "AbstractComputation.hpp"
#include "SummaryStatistics.hpp"

/**
 * Header file for parallel computation, this class will provide the implementation
 * for the parallelised computation of the provided data
 */
class ParallelComputation : public AbstractComputation {
public:
    explicit ParallelComputation(const string &fileName);

    void computeData();

    SummaryStatistics provideProgressUpdate();

    void processOpenCL(std::vector<double>);

private:
    std::string _stats_src = "../src/kernels/stats.cl"; // Kernel to build
    cl::Device _device;
    cl::CommandQueue _queue;
    cl::Context _context;
    cl::Kernel _ko_stats;
    cl::Program _program;
    std::shared_ptr<cl::make_kernel <cl::Buffer, cl::Buffer, cl::LocalSpaceArg, cl::LocalSpaceArg>> _stats;
    cl::Buffer _d_output_stats;
    cl::Buffer _d_input;
    size_t _work_group_size;
    size_t _nwork_groups;
    size_t _input_vect_size = 1024;
};

#endif //SOFTENG_751_ASSIGNMENT_PARASTATS_PARALLELCOMPUTATION_H
