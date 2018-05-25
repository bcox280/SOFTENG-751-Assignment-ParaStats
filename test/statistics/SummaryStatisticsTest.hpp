#ifndef SOFTENG_751_ASSIGNMENT_PARASTATS_SUMMARYSTATISTICS_TEST_H
#define SOFTENG_751_ASSIGNMENT_PARASTATS_SUMMARYSTATISTICS_TEST_H

#include <vector>
#include <limits>
#include "gtest/gtest.h"
#include "SummaryStatistics.hpp"

class SummaryStatisticsTest : public ::testing::Test {

protected:
    SummaryStatistics summaryStatistics;

public:
    SummaryStatisticsTest();

};

#endif
