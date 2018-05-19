#include <unordered_map>
#include "SequentialComputation.hpp"

SequentialComputation::SequentialComputation(const string &fileName) : AbstractComputation(fileName) {
    filename = fileName;
}

void SequentialComputation::computeData() {
    ifstream input(filename);

    unordered_map<double, unsigned long long> occurrences;
    unsigned long long completedDataPoints = 0;
    unsigned long long dataPointsInChunk = 0;
    double max = -DBL_MAX;
    double min = DBL_MAX;
    double M1 = 0;
    double M2 = 0;
    double M3 = 0;
    double M4 = 0;
    double upperMedian = 0;
    double lowerMedian = 0;

    std::cout << filename << std::endl;
    for (string line; getline(input, line);) {
        std::stringstream ss(line);
        double value;

        while (ss >> value) {
            occurrences[value]++;

            if (max < value) {
                max = value;
            }
            if (min > value) {
                min = value;
            }

            unsigned long long n1 = completedDataPoints;
            unsigned long long n = completedDataPoints + 1;
            double delta = value - M1;
            double delta_n = delta / n;
            double delta_n2 = delta_n * delta_n;
            double term1 = delta * delta_n * n1;
            M1 = M1 + delta_n;
            M4 = M4 + term1 * delta_n2 * (n * n - 3 * n + 3) + 6 * delta_n2 * M2 - 4 * delta_n * M3;
            M3 = M3 + term1 * delta_n * (n - 2) - 3 * delta_n * M2;
            M2 = M2 + term1;
            completedDataPoints++;
            dataPointsInChunk++;


            if (dataPointsInChunk == CHUNK_SIZE) {
                SummaryStatistics newStats = SummaryStatistics();
                newStats.setM1(M1);
                newStats.setM2(M2);
                newStats.setM3(M3);
                newStats.setM4(M4);
                newStats.setMax(max);
                newStats.setMin(min);
                newStats.setCount(completedDataPoints);
                summaryStats = newStats;
                // TODO Call the main print SS here
                dataPointsInChunk = 0;
            }

            if (ss.peek() == ',') {
                ss.ignore();
            }
        }
    }

    unsigned long long mostOccurences = 0;
    vector<double> modes;
    for (std::pair<double, unsigned long long> value : occurrences) {
        if (value.second > mostOccurences) {
            mostOccurences = value.second;
            modes.clear();
            modes.push_back(value.first);
        } else if (value.second == mostOccurences) {
            modes.push_back(value.first);
        }
    }


    SummaryStatistics finalStats = SummaryStatistics();
    finalStats.setModes(modes);
    finalStats.setM1(M1);
    finalStats.setM2(M2);
    finalStats.setM3(M3);
    finalStats.setM4(M4);
    finalStats.setMax(max);
    finalStats.setMin(min);
    finalStats.setCount(completedDataPoints);
    summaryStats = finalStats;


    cout << "Count " << finalStats.getCount() << endl;
    cout << "Mean " << finalStats.getM1() << endl;
    cout << "Mode(s) ";
    for (double mode : finalStats.getModes())
        std::cout << mode << ',';
    cout << endl;
    cout << "Median (financial) " << finalStats.getFinancialMedian() << endl;
    cout << "Min " << finalStats.getMin() << endl;
    cout << "Max " << finalStats.getMax() << endl;
    cout << "Estimated variance " << finalStats.getEstimatedVariance() << endl;
    cout << "Estimated standard deviation " << finalStats.getEstimatedStandardDev() << endl;
    cout << "Skewness " << finalStats.getSkewness() << endl;
    cout << "Kurtosis (normal) " << finalStats.getKurtosis() << endl;
    cout << "Sum " << finalStats.getSum() << endl;
    cout << "2nd moment " << finalStats.getM2() << endl;
    cout << "3rd moment " << finalStats.getM3() << endl;
    cout << "4th moment " << finalStats.getM4() << endl;
    cout << "Standard deviation " << finalStats.getStandardDev() << endl;
    cout << "Variance " << finalStats.getVariance() << endl;
    cout << "Excess kurtosis " << finalStats.getExcessKurtosis() << endl;
    cout << "Upper median " << finalStats.getUpperMedian() << endl;
    cout << "Lower median " << finalStats.getLowerMedian() << endl;
}


SummaryStatistics SequentialComputation::provideProgressUpdate() {
    return SequentialComputation::summaryStats;
}
