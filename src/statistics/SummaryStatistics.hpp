#ifndef SOFTENG_751_ASSIGNMENT_PARASTATS_SUMMARYSTATISTICS_H
#define SOFTENG_751_ASSIGNMENT_PARASTATS_SUMMARYSTATISTICS_H

/**
 * This class will be used as a structure to keep the statistics from the data,
 * this will be used both for final statistics, and progression of statistics.
 */
class SummaryStatistics {
private:
    double m2, m3, m4, min, max, upperMedian, lowerMedian;
    double m1 = m2 = m3 = m4 = min = max = upperMedian = lowerMedian = 0;
    unsigned long long count = 0;
    std::vector<double> modes;
public:
    SummaryStatistics();

    double getM1() const;

    void setM1(double m1);

    double getM2() const;

    void setM2(double m2);

    double getM3() const;

    void setM3(double m3);

    double getM4() const;

    void setM4(double m4);

    std::vector<double> getModes() const;

    void setModes(std::vector<double> mode);

    double getFinancialMedian() const;

    double getUpperMedian() const;

    void setUpperMedian(double upperMedian);

    double getLowerMedian() const;

    void setLowerMedian(double lowerMedian);

    double getMin() const;

    void setMin(double min);

    double getMax() const;

    void setMax(double max);

    unsigned long long getCount() const;

    void setCount(unsigned long long count);

    double getVariance();

    double getEstimatedVariance();

    double getStandardDev();

    double getEstimatedStandardDev();

    double getSkewness();

    double getKurtosis();

    double getExcessKurtosis();

    double getSum();
};

#endif //SOFTENG_751_ASSIGNMENT_PARASTATS_SUMMARYSTATISTICS_H
