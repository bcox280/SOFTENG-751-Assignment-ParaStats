#include "CommandLineInterface.hpp"

CommandLineInterface::CommandLineInterface(int numberOfArguments, char* arguments[]) {
    _inputVectorSize = 1024;

    // Deals with CLI arguments
    bool inputChangeFlag = false;
    bool outputChangeFlag = false;
    bool vectorChangeFlag = false;
    for (int i = 0; i < numberOfArguments; i++) {
        if (inputChangeFlag) {
            inputChangeFlag = false;
            if (checkOption("i", arguments[i - 1])) {
                _inputFilename = arguments[i];
            }
        } else if (outputChangeFlag) {
            outputChangeFlag = false;
            if (checkOption("o", arguments[i - 1])) {
                _outputFilename = arguments[i];
            }
        } else if (vectorChangeFlag) {
            vectorChangeFlag = false;
            if (checkOption("z", arguments[i - 1])) {
                size_t vector;
                try {
                    vector = stoi(arguments[i]);
                } catch(...) {
                    cout << "Please enter a valid input vector size" << endl;
                    throw ExitException();
                }
                _inputVectorSize = vector;
            }
        } else {
            if (checkOption("h", arguments[i])) {
                printHelp();
                throw ExitException();
            } else if (checkOption("v", arguments[i])) {
                printVersion();
                throw ExitException();
            } else if (checkOption("q", arguments[i])) {
                _quiet = true;
            } else if (checkOption("s", arguments[i])) {
                _parallel = false;
            } else if (checkOption("p", arguments[i])) {
                _parallel = true;
            } else if (checkOption("i", arguments[i])) {
                inputChangeFlag = true;
            } else if (checkOption("z", arguments[i])) {
                vectorChangeFlag = true;
            } else if (checkOption("o", arguments[i])) {
                outputChangeFlag = true;
                _printToFile = true;
            }
        }
    }

    if (numberOfArguments == 1) { // The first argument is always the absolute path to the executable
        cout << "Run ParaStats again with /h or -h to get help" << endl;
    }

    CommandLineInterface::checkInputFileExists();

    if (!_quiet) {
        printSeparatorLine();
        cout << "ParaStats " << _version << " initialising..." << endl;
        cout << "Reading from the input file: " << _inputFilename << endl;
        if (_printToFile) {
            cout << "Writing the results to the output file: " << _outputFilename << endl;
        } else {
            cout << "Not writing the results to a file" << endl;
        }
        if (_parallel) {
            cout << "Running in OpenCL mode" << endl;
        } else {
            cout << "Running in sequential mode" << endl;
        }
        printSeparatorLine();
    }
}

size_t CommandLineInterface::userVectorSize() {
    return _inputVectorSize;
}

void CommandLineInterface::printSeparatorLine() {
    cout << "==============================================================================" << endl;
}

void CommandLineInterface::printRuntime(std::chrono::system_clock::time_point initialTime,
                                        std::chrono::system_clock::time_point finalTime) {
    std::cout << "Calculating the statistical values took: "
              << std::chrono::duration_cast<std::chrono::nanoseconds>(finalTime - initialTime).count() /
                 NANO_TO_MILLI_SECONDS
              << " milliseconds " << std::endl;
}

void CommandLineInterface::printResults(SummaryStatistics summaryStatistics) {
//        cout << std::scientific;
            cout << std::setprecision(17);
        cout << "Count " << summaryStatistics.getCount() << endl;
        cout << "Mean " << summaryStatistics.getM1() << endl;
//    cout << "Mode(s) ";
//    for (double mode : summaryStatistics.getModes())
//        std::cout << mode << ',';
//    cout << endl;
//    cout << "Median (financial) " << summaryStatistics.getFinancialMedian() << endl;
        cout << "Min " << summaryStatistics.getMin() << endl;
        cout << "Max " << summaryStatistics.getMax() << endl;
        cout << "Estimated variance " << summaryStatistics.getEstimatedVariance() << endl;
        cout << "Estimated standard deviation " << summaryStatistics.getEstimatedStandardDev() << endl;
        cout << "Skewness " << summaryStatistics.getSkewness() << endl;
        cout << "Kurtosis (normal) " << summaryStatistics.getKurtosis() << endl;
        cout << "Sum " << summaryStatistics.getSum() << endl;
        cout << "2nd moment " << summaryStatistics.getM2() << endl;
        cout << "3rd moment " << summaryStatistics.getM3() << endl;
        cout << "4th moment " << summaryStatistics.getM4() << endl;
        cout << "Standard deviation " << summaryStatistics.getStandardDev() << endl;
        cout << "Variance " << summaryStatistics.getVariance() << endl;
        cout << "Excess kurtosis " << summaryStatistics.getExcessKurtosis() << endl;
//    cout << "Upper median " << summaryStatistics.getUpperMedian() << endl;
//    cout << "Lower median " << summaryStatistics.getLowerMedian() << endl;
}

void CommandLineInterface::printVersion() {
    cout << "This version of ParaStats is: " << _version << endl;
}

string CommandLineInterface::inputFilename() {
    return _inputFilename;
}

bool CommandLineInterface::runInParallel() {
    return _parallel;
}

void CommandLineInterface::printHelp() {
    cout << "=== ParaStats Help ===" << endl;
    cout << endl;
    cout << "Usage:" << endl;
    cout << "\tParaStats -o [output file name]" << endl;
    cout << "\tParaStats -i <input  file name>" << endl;
    cout << "\tParaStats -h" << endl;
    cout << "\tParaStats -s" << endl;
    cout << "\tParaStats -p" << endl;
    cout << "\tParaStats -v" << endl;
    cout << "\tParaStats -q" << endl;
    cout << "\tParaStats -z <input vector size>" << endl;
    cout << "Options:" << endl;
    cout << "\t-o Change the output file name." << endl;
    cout << "\t-i Change the input  file name." << endl;
    cout << "\t-h Show this screen." << endl;
    cout << "\t-s Calculate using the sequential implementation." << endl;
    cout << "\t-p Calculate using the OpenCL implementation." << endl;
    cout << "\t-v Show version." << endl;
    cout << "\t-q Run in quiet mode." << endl;
    cout << "\t-z Change the input vector size for the device." << endl;
}

bool CommandLineInterface::checkOption(string option, string input) {
    return (input == ("/" + option) || input == ("-" + option));
}

bool CommandLineInterface::printToFile() {
    return _printToFile;
}

string *CommandLineInterface::outputFilename() {
    return &_outputFilename;
}

void CommandLineInterface::checkInputFileExists() {
    if (access(_inputFilename.c_str(), F_OK) == -1) {
        cout << "The selected input file was not able to be opened: " << _inputFilename << endl;
        throw ExitException();
    }
}
