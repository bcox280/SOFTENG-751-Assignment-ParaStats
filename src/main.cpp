#include <iostream>
#include <vector>
#include <sstream>
#include <cstring>
#include <fstream>
#include <chrono>
#include "ParallelComputation.cpp"
#include "SequentialComputation.cpp"
#include "SummaryStatistics.cpp"
#include "AbstractComputation.cpp"
#include "CommandLineInterface.cpp"
#include "ExitException.cpp"

typedef std::chrono::high_resolution_clock Clock;

using namespace std;

// TODO Fix reading input file in winDOS and try to standardise
// TODO FileReader testing via reading in, printing and and comparing hashcodes

void printResultsToCsvFile(SummaryStatistics finalStatistics, string *outputFilename);

int main(int argc, char *argv[]) {
    CommandLineInterface *cli;
    try {
        cli = new CommandLineInterface(argc, argv);
    } catch (ExitException &exception) {
        return 0;
    }

    AbstractComputation* computer;
    if (cli->runInParallel()) {
        computer = new ParallelComputation(cli->inputFilename(), cli->userVectorSize());
    } else {
        computer = new SequentialComputation(cli->inputFilename());
    }

    auto initialTime = Clock::now(); // Start timer
    SummaryStatistics finalStatistics = computer->computeData();
    auto finalTime = Clock::now(); // End timer

    // TODO Print out statistics as they're being calculated

    cli->printResults(finalStatistics);

    cli->printRuntime(initialTime, finalTime);

    if (cli->printToFile()) {
        printResultsToCsvFile(finalStatistics, cli->outputFilename());
    }

    return 0;
}

// TODO Share this code and CLI printing in one object that just takes a stream
void printResultsToCsvFile(SummaryStatistics finalStatistics, string *outputFilename) {
    std::ofstream outputFile(*outputFilename);

//    if (finalStatistics.getModes().empty()) {
//        outputFile << "Mode(s)" << ",";
//    }
    outputFile << "Count" << ","
                << "Min" << ","
                << "Max" << ","
                << "Mean" << ","
                << "Standard deviation" << ","
                << "Variance" << ","
                << "Skewness" << ","
                << "Kurtosis" << ","
                << "Sum"
//               << "Median (financial)" << ","
//               << "Estimated variance" << ","
//               << "Estimated standard deviation" << ","
//               << "2nd moment" << ","
//               << "3rd moment" << ","
//               << "4th moment" << ","
//               << "Excess kurtosis" << ","
//               << "Upper median" << ","
//               << "Lower median"
                << std::endl;

    outputFile << std::scientific;
//    if (finalStatistics.getModes().empty()) {
//        outputFile << finalStatistics.getModes().at(0) << "," << endl;
//    }
    outputFile << finalStatistics.getCount() << ","
            << finalStatistics.getMin() << ","
            << finalStatistics.getMax() << ","
            << finalStatistics.getM1() << ","
            << finalStatistics.getStandardDev() << ","
            << finalStatistics.getVariance() << ","
            << finalStatistics.getSkewness() << ","
            << finalStatistics.getKurtosis() << ","
            << finalStatistics.getSum()
//            << finalStatistics.getFinancialMedian() << ","
//            << finalStatistics.getEstimatedVariance() << ","
//            << finalStatistics.getEstimatedStandardDev() << ","
//            << finalStatistics.getM2() << ","
//            << finalStatistics.getM3() << ","
//            << finalStatistics.getM4() << ","
//            << finalStatistics.getExcessKurtosis() << ","
//            << finalStatistics.getUpperMedian() << ","
//            << finalStatistics.getLowerMedian() << endl;
//    for (unsigned long long int mode = 1; mode < finalStatistics.getModes().size(); mode++) {
//        cout << finalStatistics.getModes().at(mode) << endl;
//    }
            << std::endl;

    outputFile.close();
}
