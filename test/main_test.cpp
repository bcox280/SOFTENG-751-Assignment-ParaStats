#include <cstring>
#include "gtest/gtest.h"
#include "SummaryStatistics.cpp"
#include "AbstractComputation.cpp"
#include "ParallelComputation.cpp"
#include "SequentialComputation.cpp"
#include "ComputationTest.hpp"

bool runOnTravis;

int main(int argc, char **argv) {
    bool travisFlag = false;
    for (int argument = 0; argument < argc; argument++) {
        if (!strcmp(argv[argument], "TRAVIS")) {
            travisFlag = true;
        }
    }
    runOnTravis = travisFlag;
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
