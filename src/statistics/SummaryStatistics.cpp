#include "SummaryStatistics.hpp"

SummaryStatistics::SummaryStatistics() = default;

double SummaryStatistics::getM1() const {
    return m1;
}

void SummaryStatistics::setM1(double m1) {
    SummaryStatistics::m1 = m1;
}

double SummaryStatistics::getM2() const {
    return m2;
}

void SummaryStatistics::setM2(double m2) {
    SummaryStatistics::m2 = m2;
}

double SummaryStatistics::getM3() const {
    return m3;
}

void SummaryStatistics::setM3(double m3) {
    SummaryStatistics::m3 = m3;
}

double SummaryStatistics::getM4() const {
    return m4;
}

void SummaryStatistics::setM4(double m4) {
    SummaryStatistics::m4 = m4;
}

double SummaryStatistics::getM5() const {
    return m5;
}

void SummaryStatistics::setM5(double m5) {
    SummaryStatistics::m5 = m5;
}

double SummaryStatistics::getMode() const {
    return mode;
}

void SummaryStatistics::setMode(double mode) {
    SummaryStatistics::mode = mode;
}

double SummaryStatistics::getMedian() const {
    return median;
}

void SummaryStatistics::setMedian(double median) {
    SummaryStatistics::median = median;
}

double SummaryStatistics::getMin() const {
    return min;
}

void SummaryStatistics::setMin(double min) {
    SummaryStatistics::min = min;
}

double SummaryStatistics::getMax() const {
    return max;
}

void SummaryStatistics::setMax(double max) {
    SummaryStatistics::max = max;
}

unsigned int SummaryStatistics::getCount() const {
    return count;
}

void SummaryStatistics::setCount(unsigned int count) {
    SummaryStatistics::count = count;
}

double SummaryStatistics::getVariance() {
    return 0;
}

double SummaryStatistics::getStandardDev() {
    return 0;
}

double SummaryStatistics::getSkewneess() {
    return 0;
}

double SummaryStatistics::getKurtosis() {
    return 0;
}

double SummaryStatistics::getSum() {
    return 0;
}

