#include "ComputationTest.hpp"

INSTANTIATE_TEST_CASE_P(SequentialComputation, ComputationTest, ::testing::Values(&sequential1024));

TEST_P(ComputationTest, lowerMedian) {
    EXPECT_EQ(GetParam()->getLowerMedian(), 0);
}

TEST_P(ComputationTest, DISABLED_getModes) {
    std::vector<double> modes = GetParam()->getModes();
    EXPECT_EQ(modes.size(), 1);
}

TEST_P(ComputationTest, getFinancialMedian) {
    EXPECT_EQ(GetParam()->getFinancialMedian(), 0);
}

TEST_P(ComputationTest, DISABLED_getExcessKurtosis) {
    EXPECT_EQ(GetParam()->getExcessKurtosis(), 0.00218416);
}

TEST_P(ComputationTest, DISABLED_getKurtosis) {
    EXPECT_EQ(GetParam()->getKurtosis(), 3.00218);
}

TEST_P(ComputationTest, DISABLED_getSum) {
    EXPECT_EQ(GetParam()->getSum(), 1);
}

TEST_P(ComputationTest, DISABLED_getSkewness) {
    EXPECT_EQ(GetParam()->getSkewness(), 0.000318525);
}

TEST_P(ComputationTest, DISABLED_getEstimatedVariance) {
    EXPECT_EQ(GetParam()->getEstimatedVariance(), 3.99877);
}

TEST_P(ComputationTest, DISABLED_getVariance) {
    EXPECT_EQ(GetParam()->getVariance(), 3.99877);
}

TEST_P(ComputationTest, DISABLED_getEstimatedStandardDev) {
    EXPECT_EQ(GetParam()->getEstimatedStandardDev(), 1.99969);
}

TEST_P(ComputationTest, DISABLED_getStandardDev) {
    EXPECT_EQ(GetParam()->getStandardDev(), 1.99969);
}

TEST_P(ComputationTest, DISABLED_getMax) {
    EXPECT_EQ(GetParam()->getMax(), 240.5);
}

TEST_P(ComputationTest, DISABLED_getMin) {
    EXPECT_EQ(GetParam()->getMin(), 220.05);
}

TEST_P(ComputationTest, DISABLED_getCount) {
    EXPECT_EQ(GetParam()->getCount(), 10240000);
}

TEST_P(ComputationTest, DISABLED_getM1) {
    EXPECT_EQ(GetParam()->getM1(), 230.5);
}

TEST_P(ComputationTest, DISABLED_getM2) {
    EXPECT_EQ(GetParam()->getM2(), 1);
}

TEST_P(ComputationTest, DISABLED_getM3) {
    EXPECT_EQ(GetParam()->getM3(), 26081.5);
}

TEST_P(ComputationTest, DISABLED_getM4) {
    EXPECT_EQ(GetParam()->getM4(), 1);
}
