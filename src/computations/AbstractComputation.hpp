#ifndef SOFTENG_751_ASSIGNMENT_PARASTATS_ABSTRACTCOMPUTATION_H
#define SOFTENG_751_ASSIGNMENT_PARASTATS_ABSTRACTCOMPUTATION_H

#include <cstring>
#include "SummaryStatistics.hpp"

using namespace std;

/**
 * Header file for an abstract class that will be inherited by children, this class provides
 * the implementation that the children class will need to follow
 */
class AbstractComputation {
    public:
        explicit AbstractComputation(const string &fileName);
        virtual void computeData() = 0;
        virtual SummaryStatistics provideProgressUpdate() = 0;
        virtual string createSummary() = 0;
};

#endif //SOFTENG_751_ASSIGNMENT_PARASTATS_ABSTRACTCOMPUTATION_H
