#include "SequentialComputation.hpp"

SequentialComputation::SequentialComputation(const string &fileName) : AbstractComputation(fileName) {

    ifstream input(fileName);

    for (string line; getline(input, line); ) {
        std::vector<double> vect;
        std::stringstream ss(line);
        double value;

        while (ss >> value) {
            vect.push_back(value);

            if (ss.peek() == ',') {
                ss.ignore();
            }
        }
    }
}

void SequentialComputation::computeData() {

}


SummaryStatistics SequentialComputation::provideProgressUpdate() {
    return SummaryStatistics();
}

string SequentialComputation::createSummary() {
    return string();
}
