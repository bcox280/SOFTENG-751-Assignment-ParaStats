#include "AbstractComputation.hpp"

AbstractComputation::AbstractComputation(const string &fileName) {
    _summaryStats = SummaryStatistics();
    _fileName = fileName;
}
