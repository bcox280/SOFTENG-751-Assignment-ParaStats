#include <cmath>
#include <algorithm>
#include "SummaryStatistics.hpp"

/* TODO Check that the following source for our calculations is correct
https://stats.stackexchange.com/questions/88837/single-pass-algorithm-for-kurtosis */

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

std::vector<double> SummaryStatistics::getModes() const {
    return modes;
}

void SummaryStatistics::setModes(std::vector<double> modes) {
    SummaryStatistics::modes = modes;
}


double SummaryStatistics::getUpperMedian() const {
    return upperMedian;
}

void SummaryStatistics::setUpperMedian(double upperMedian) {
    SummaryStatistics::upperMedian = upperMedian;
}

double SummaryStatistics::getLowerMedian() const {
    return lowerMedian;
}

void SummaryStatistics::setLowerMedian(double lowerMedian) {
    SummaryStatistics::lowerMedian = lowerMedian;
}

double SummaryStatistics::getFinancialMedian() const {
    return (getUpperMedian() * 0.5 + getLowerMedian() * 0.5);
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

unsigned long long SummaryStatistics::getCount() const {
    return count;
}

void SummaryStatistics::setCount(unsigned long long count) {
    SummaryStatistics::count = count;
}

double SummaryStatistics::getVariance() {
    return getM2() / getCount();
}

double SummaryStatistics::getEstimatedVariance() {
    return getM2() / (getCount() - 1);
}

double SummaryStatistics::getStandardDev() {
    return sqrt(getVariance());
}

double SummaryStatistics::getEstimatedStandardDev() {
    return sqrt(getEstimatedVariance());
}

double SummaryStatistics::getSkewness() {
    return sqrt(getCount()) * getM3() / pow(getM2(), 1.5);
}

double SummaryStatistics::getKurtosis() {
    return (getCount() * getM4() / (getM2() * getM2()));
}

double SummaryStatistics::getExcessKurtosis() {
    return getKurtosis() - 3;
}

double SummaryStatistics::getSum() {
    return getM1() * getCount();
}

