#include "SummaryStatisticsTest.hpp"

SummaryStatisticsTest::SummaryStatisticsTest() {
    SummaryStatisticsTest::summaryStatistics = SummaryStatistics();
    std::vector<double> modes;
    modes.push_back(1);

    SummaryStatisticsTest::summaryStatistics.setCount(1);
    SummaryStatisticsTest::summaryStatistics.setM1(1);
    SummaryStatisticsTest::summaryStatistics.setMin(1);
    SummaryStatisticsTest::summaryStatistics.setMax(1);
    SummaryStatisticsTest::summaryStatistics.setLowerMedian(1);
    SummaryStatisticsTest::summaryStatistics.setM2(1);
    SummaryStatisticsTest::summaryStatistics.setM3(1);
    SummaryStatisticsTest::summaryStatistics.setM4(1);
    SummaryStatisticsTest::summaryStatistics.setModes(modes);
    SummaryStatisticsTest::summaryStatistics.setUpperMedian(2);
}

TEST_F(SummaryStatisticsTest, lowerMedian) {
    EXPECT_EQ(SummaryStatisticsTest::summaryStatistics.getLowerMedian(), 1);
}

TEST_F(SummaryStatisticsTest, upperMedian) {
    EXPECT_EQ(SummaryStatisticsTest::summaryStatistics.getUpperMedian(), 2);
}

TEST_F(SummaryStatisticsTest, getModes) {
    std::vector<double> modes = SummaryStatisticsTest::summaryStatistics.getModes();
    EXPECT_EQ(modes.size(), 1);
    EXPECT_EQ(modes.front(), 1);
}

TEST_F(SummaryStatisticsTest, getFinancialMedian) {
    EXPECT_EQ(SummaryStatisticsTest::summaryStatistics.getFinancialMedian(), 1.5);
}

TEST_F(SummaryStatisticsTest, getExcessKurtosis) {
    EXPECT_EQ(SummaryStatisticsTest::summaryStatistics.getExcessKurtosis(), -2);
}

TEST_F(SummaryStatisticsTest, getKurtosis) {
    EXPECT_EQ(SummaryStatisticsTest::summaryStatistics.getKurtosis(), 1);
}

TEST_F(SummaryStatisticsTest, getSum) {
    EXPECT_EQ(SummaryStatisticsTest::summaryStatistics.getSum(), 1);
}

TEST_F(SummaryStatisticsTest, getSkewness) {
    EXPECT_EQ(SummaryStatisticsTest::summaryStatistics.getSkewness(), 1);
}

TEST_F(SummaryStatisticsTest, getEstimatedVariance) {
    EXPECT_EQ(SummaryStatisticsTest::summaryStatistics.getEstimatedVariance(), std::numeric_limits<double>::infinity());
}

TEST_F(SummaryStatisticsTest, getVariance) {
    EXPECT_EQ(SummaryStatisticsTest::summaryStatistics.getVariance(), 1);
}

TEST_F(SummaryStatisticsTest, getEstimatedStandardDev) {
    EXPECT_EQ(SummaryStatisticsTest::summaryStatistics.getEstimatedStandardDev(),
              std::numeric_limits<double>::infinity());
}

TEST_F(SummaryStatisticsTest, getStandardDev) {
    EXPECT_EQ(SummaryStatisticsTest::summaryStatistics.getStandardDev(), 1);
}

TEST_F(SummaryStatisticsTest, getMax) {
    EXPECT_EQ(SummaryStatisticsTest::summaryStatistics.getMax(), 1);
}

TEST_F(SummaryStatisticsTest, getMin) {
    EXPECT_EQ(SummaryStatisticsTest::summaryStatistics.getMin(), 1);
}

TEST_F(SummaryStatisticsTest, getCount) {
    EXPECT_EQ(SummaryStatisticsTest::summaryStatistics.getCount(), 1);
}

TEST_F(SummaryStatisticsTest, getM1) {
    EXPECT_EQ(SummaryStatisticsTest::summaryStatistics.getM1(), 1);
}

TEST_F(SummaryStatisticsTest, getM2) {
    EXPECT_EQ(SummaryStatisticsTest::summaryStatistics.getM2(), 1);
}

TEST_F(SummaryStatisticsTest, getM3) {
    EXPECT_EQ(SummaryStatisticsTest::summaryStatistics.getM3(), 1);
}

TEST_F(SummaryStatisticsTest, getM4) {
    EXPECT_EQ(SummaryStatisticsTest::summaryStatistics.getM4(), 1);
}
