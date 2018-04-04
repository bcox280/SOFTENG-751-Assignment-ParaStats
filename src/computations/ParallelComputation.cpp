#include "ParallelComputation.hpp"

ParallelComputation::ParallelComputation(const string &fileName) : AbstractComputation(fileName) {

}

void ParallelComputation::computeData() {

}

SummaryStatistics ParallelComputation::provideProgressUpdate() {
    return SummaryStatistics();
}

string ParallelComputation::createSummary() {
    return string();
}
