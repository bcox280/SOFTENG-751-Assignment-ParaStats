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

// TODO Fix reading input file and try to standardise
// TODO Try compiling with -O3
// TODO Create a TravisCI Equivalent test script for winDOS and *nix OS -> possibly get travis to run the same script
// TODO Document how to setup winDOS or *nix to compile and run the application
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
        computer = new ParallelComputation(cli->inputFilename());
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
    if (finalStatistics.getModes().empty()) {
        outputFile << "Mode(s)" << "," << endl;
    }
    outputFile << "Count" << ","
               << "Mean" << ","
               << "Median (financial)" << ","
               << "Min" << ","
               << "Max" << ","
               << "Estimated variance" << ","
               << "Estimated standard deviation" << ","
               << "Skewness" << ","
               << "Kurtosis (normal)" << ","
               << "Sum" << ","
               << "2nd moment" << ","
               << "3rd moment" << ","
               << "4th moment" << ","
               << "Standard deviation" << ","
               << "Variance" << ","
               << "Excess kurtosis" << ","
               << "Upper median" << ","
               << "Lower median" << std::endl;
    outputFile << std::scientific;
    if (finalStatistics.getModes().empty()) {
        outputFile << finalStatistics.getModes().at(0) << "," << endl;
    }
    outputFile << finalStatistics.getCount() << ","
            << finalStatistics.getM1() << ","
            << finalStatistics.getFinancialMedian() << ","
            << finalStatistics.getMin() << ","
            << finalStatistics.getMax() << ","
            << finalStatistics.getEstimatedVariance() << ","
            << finalStatistics.getEstimatedStandardDev() << ","
            << finalStatistics.getSkewness() << ","
            << finalStatistics.getKurtosis() << ","
            << finalStatistics.getSum() << ","
            << finalStatistics.getM2() << ","
            << finalStatistics.getM3() << ","
            << finalStatistics.getM4() << ","
            << finalStatistics.getStandardDev() << ","
            << finalStatistics.getVariance() << ","
            << finalStatistics.getExcessKurtosis() << ","
            << finalStatistics.getUpperMedian() << ","
            << finalStatistics.getLowerMedian() << endl;
    for (unsigned long long int mode = 1; mode < finalStatistics.getModes().size(); mode++) {
        cout << finalStatistics.getModes().at(mode) << endl;
    }
    outputFile.close();
}
