#ifndef SOFTENG_751_ASSIGNMENT_PARASTATS_COMMANDLINEINTERFACE_HPP
#define SOFTENG_751_ASSIGNMENT_PARASTATS_COMMANDLINEINTERFACE_HPP


static const int NANO_TO_MILLI_SECONDS = 1000000;

#include "SummaryStatistics.hpp"
#include "ExitException.hpp"
#include <chrono>
#include <sys/unistd.h>
#include <iomanip>

class CommandLineInterface {
public:
    CommandLineInterface(int numberOfArguments, char* arguments[]);

    bool runInParallel();

    string inputFilename();

    bool printToFile();

    string *outputFilename();

    void printRuntime(std::chrono::system_clock::time_point initialTime,
                      std::chrono::system_clock::time_point finalTime);

    void printResults(SummaryStatistics summaryStatistics);

private:
    const string _version = "1.0";
    string _outputFilename = "results.csv";
    string _inputFilename = "../data/voltage_normal_10240000.csv";
    bool _parallel = true;
    bool _quiet = false;
    bool _printToFile = false;

    void printHelp();

    void printVersion();

    void printSeparatorLine();

    bool checkOption(string option, string input);

    void checkInputFileExists();

};


#endif //SOFTENG_751_ASSIGNMENT_PARASTATS_COMMANDLINEINTERFACE_HPP
