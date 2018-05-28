#include "ComputationTest.hpp"

SummaryStatistics sequential1024 = SequentialComputation("../data/voltage_normal_10240000.csv").computeData();
SummaryStatistics sequential1024Travis = SequentialComputation("./data/voltage_normal_10240000.csv").computeData();
SummaryStatistics parallel1024 = ParallelComputation("../data/voltage_normal_10240000.csv", true).computeData();
//SummaryStatistics parallel1024Travis = ParallelComputation("./data/voltage_normal_10240000.csv", true).computeData();

INSTANTIATE_TEST_CASE_P(Computation, ComputationTest, ::testing::Values(
        runOnTravis ? &sequential1024Travis : (&sequential1024, & parallel1024)));


TEST_P(ComputationTest, DISABLED_getModes) {
    std::vector<double> modes = GetParam()->getModes();
    EXPECT_EQ(modes.size(), 1);
}

TEST_P(ComputationTest, DISABLED_getFinancialMedian) {
    EXPECT_LT(GetParam()->getFinancialMedian(), 0 * 1.000001);
    EXPECT_GT(GetParam()->getFinancialMedian(), 0 * 0.999999);
}

TEST_P(ComputationTest, DISABLED_getUpperMedian) {
    EXPECT_LT(GetParam()->getUpperMedian(), 0 * 1.000001);
    EXPECT_GT(GetParam()->getUpperMedian(), 0 * 0.999999);
}

TEST_P(ComputationTest, DISABLED_getLowerMedian) {
    EXPECT_LT(GetParam()->getLowerMedian(), 0 * 1.000001);
    EXPECT_GT(GetParam()->getUpperMedian(), 0 * 0.999999);
}

TEST_P(ComputationTest, getExcessKurtosis) {
    EXPECT_LT(GetParam()->getExcessKurtosis(), 0.0021841612240902641 * 1.000001);
    EXPECT_GT(GetParam()->getExcessKurtosis(), 0.0021841612240902641 * 0.999999);
}

TEST_P(ComputationTest, getKurtosis) {
    EXPECT_LT(GetParam()->getKurtosis(), 3.0021841612240903 * 1.000001);
    EXPECT_GT(GetParam()->getKurtosis(), 3.0021841612240903 * 0.999999);
}

TEST_P(ComputationTest, _getSum) {
    EXPECT_LT(GetParam()->getSum(), 2360323839.460166 * 1.000001);
    EXPECT_GT(GetParam()->getSum(), 2360323839.460166 * 0.999999);
}

TEST_P(ComputationTest, _getSkewness) {
    EXPECT_LT(GetParam()->getSkewness(), 0.0003185249932269064 * 1.000001);
    EXPECT_GT(GetParam()->getSkewness(), 0.0003185249932269064 * 0.999999);
}

TEST_P(ComputationTest, _getEstimatedVariance) {
    EXPECT_LT(GetParam()->getEstimatedVariance(), 3.9987660723803216 * 1.000001);
    EXPECT_GT(GetParam()->getEstimatedVariance(), 3.9987660723803216 * 0.999999);
}

TEST_P(ComputationTest, _getVariance) {
    EXPECT_LT(GetParam()->getVariance(), 3.9987656818758222 * 1.000001);
    EXPECT_GT(GetParam()->getVariance(), 3.9987656818758222 * 0.999999);
}

TEST_P(ComputationTest, _getEstimatedStandardDev) {
    EXPECT_LT(GetParam()->getEstimatedStandardDev(), 1.9996914943011388 * 1.000001);
    EXPECT_GT(GetParam()->getEstimatedStandardDev(), 1.9996914943011388 * 0.999999);
}

TEST_P(ComputationTest, _getStandardDev) {
    EXPECT_LT(GetParam()->getStandardDev(), 1.9996913966599501 * 1.000001);
    EXPECT_GT(GetParam()->getStandardDev(), 1.9996913966599501 * 0.999999);
}

TEST_P(ComputationTest, _getMax) {
    EXPECT_LT(GetParam()->getMax(), 240.5 * 1.000001);
    EXPECT_GT(GetParam()->getMax(), 240.5 * 0.999999);
}

TEST_P(ComputationTest, _getMin) {
    EXPECT_LT(GetParam()->getMin(), 220.05 * 1.000001);
    EXPECT_GT(GetParam()->getMin(), 220.05 * 0.999999);
}

TEST_P(ComputationTest, _getCount) {
    EXPECT_EQ(GetParam()->getCount(), 10240000);
}

TEST_P(ComputationTest, _getM1) {
    EXPECT_LT(GetParam()->getM1(), 230.50037494728184 * 1.000001);
    EXPECT_GT(GetParam()->getM1(), 230.50037494728184 * 0.999999);
}

TEST_P(ComputationTest, _getM2) {
    EXPECT_LT(GetParam()->getM2(), 40947360.582408421 * 1.000001);
    EXPECT_GT(GetParam()->getM2(), 40947360.582408421 * 0.999999);
}

TEST_P(ComputationTest, _getM3) {
    EXPECT_LT(GetParam()->getM3(), 26081.49046573689 * 1.000001);
    EXPECT_GT(GetParam()->getM3(), 26081.49046573689 * 0.999999);
}

TEST_P(ComputationTest, _getM4) {
    EXPECT_LT(GetParam()->getM4(), 491574332.93781263 * 1.000001);
    EXPECT_GT(GetParam()->getM4(), 491574332.93781263 * 0.999999);
}
