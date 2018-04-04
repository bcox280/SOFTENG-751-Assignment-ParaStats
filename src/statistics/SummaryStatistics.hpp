#ifndef SOFTENG_751_ASSIGNMENT_PARASTATS_SUMMARYSTATISTICS_H
#define SOFTENG_751_ASSIGNMENT_PARASTATS_SUMMARYSTATISTICS_H

/**
 * This class will be used as a structure to keep the statistics from the data,
 * this will be used both for final statistics, and progression of statistics.
 */
class SummaryStatistics {
private:
    double m1, m2, m3, m4, m5, mode, median,  min, max;
    unsigned int count;
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

    double getM5() const;

    void setM5(double m5);

    double getMode() const;

    void setMode(double mode);

    double getMedian() const;

    void setMedian(double median);

    double getMin() const;

    void setMin(double min);

    double getMax() const;

    void setMax(double max);

    unsigned int getCount() const;

    void setCount(unsigned int count);

    double getVariance();

    double getStandardDev();

    double getSkewneess();

    double getKurtosis();

    double getSum();
};

#endif //SOFTENG_751_ASSIGNMENT_PARASTATS_SUMMARYSTATISTICS_H
