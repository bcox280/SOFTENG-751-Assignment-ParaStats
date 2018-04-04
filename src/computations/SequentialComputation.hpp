#ifndef SOFTENG_751_ASSIGNMENT_PARASTATS_SEQUENTIALCOMPUTATION_H
#define SOFTENG_751_ASSIGNMENT_PARASTATS_SEQUENTIALCOMPUTATION_H

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cstring>
#include "AbstractComputation.hpp"
#include "SummaryStatistics.hpp"

/**
 * Header file for sequential computation, this class will provide the implementation
 * for the sequential computation of the provided data
 */
class SequentialComputation : public AbstractComputation {
public:
    explicit SequentialComputation(const string &fileName);
    void computeData();
    SummaryStatistics provideProgressUpdate();
    string createSummary();
};

#endif //SOFTENG_751_ASSIGNMENT_PARASTATS_SEQUENTIALCOMPUTATION_H
