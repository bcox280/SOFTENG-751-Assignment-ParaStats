#ifndef SOFTENG_751_ASSIGNMENT_PARASTATS_PARALLELCOMPUATION_H
#define SOFTENG_751_ASSIGNMENT_PARASTATS_PARALLELCOMPUATION_H

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cstring>
#include "AbstractComputation.hpp"
#include "SummaryStatistics.hpp"

/**
 * Header file for parallel computation, this class will provide the implementation
 * for the parallelised computation of the provided data
 */
class ParallelComputation : public AbstractComputation {
public:
    ParallelComputation(const string &fileName);

    void computeData();

    SummaryStatistics provideProgressUpdate();
};

#endif //SOFTENG_751_ASSIGNMENT_PARASTATS_PARALLELCOMPUATION_H
