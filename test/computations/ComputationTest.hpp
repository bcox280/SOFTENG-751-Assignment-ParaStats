#ifndef SOFTENG_751_ASSIGNMENT_PARASTATS_SEQUENTIALCOMPUTATION_TEST_H
#define SOFTENG_751_ASSIGNMENT_PARASTATS_SEQUENTIALCOMPUTATION_TEST_H

#include "gtest/gtest.h"
#include "SummaryStatistics.hpp"
#include "SequentialComputation.hpp"
#include "ParallelComputation.hpp"

extern bool runOnTravis;

class ComputationTest : public ::testing::TestWithParam<SummaryStatistics *> {

};

#endif
