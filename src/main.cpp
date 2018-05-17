#include <iostream>
#include <vector>
#include <sstream>
#include <cstring>
#include "ParallelComputation.cpp"
#include "SequentialComputation.cpp"
#include "SummaryStatistics.cpp"
#include "AbstractComputation.cpp"
#include <chrono>

typedef std::chrono::high_resolution_clock Clock;


using namespace std;

void printHelp();

void printVersion(string version);

bool checkOption(string option, string input);

int main(int argc, char *argv[]) {
    const string version("beta");
    string outputFilename("results.txt");
    string inputFilename("../data/voltage_normal_10240000.csv");
    bool parallel = true;
    bool quiet = false;

    bool inputChangeFlag = false;
    bool outputChangeFlag = false;
    for (int i = 0; i < argc; i++) {
        if (inputChangeFlag) {
            inputChangeFlag = false;
            if (checkOption("i", argv[i - 1])) {
                inputFilename = argv[i];
            }
        } else if (outputChangeFlag) {
            outputChangeFlag = false;
            if (checkOption("o", argv[i - 1])) {
                outputFilename = argv[i];
            }
        } else {
            if (checkOption("h", argv[i])) {
                printHelp();
                return 0;
            } else if (checkOption("v", argv[i])) {
                printVersion(version);
                return 0;
            } else if (checkOption("q", argv[i])) {
                quiet = true;
            } else if (checkOption("s", argv[i])) {
                parallel = false;
            } else if (checkOption("i", argv[i])) {
                inputChangeFlag = true;
            } else if (checkOption("o", argv[i])) {
                outputChangeFlag = true;
            }
        }
    }

    if (argc == 0) {
        printHelp();
    }

//    auto pt1 = Clock::now();
//    SequentialComputation sq = SequentialComputation(inputFilename);
//    sq.computeData();

//    auto pt2 = Clock::now();
//    std::cout << "Delta sez t2-t1: "
//              << std::chrono::duration_cast<std::chrono::nanoseconds>(pt2 - pt1).count() / 1000000
//              << " milliseconds " << std::endl;


    ParallelComputation pr = ParallelComputation(inputFilename);
    pr.computeData();

    return 0;
}

void printHelp() {
    cout << "=== ParaStats Help ==" << endl;
    cout << "-o outputFileName" << endl;
    cout << "-i inputFileName" << endl;
    cout << "-h help" << endl;
    cout << "-s sequential mode" << endl;
    cout << "-v version" << endl;
    cout << "-q quiet" << endl;
}

void printVersion(string version) {
    cout << version << endl;
}

bool checkOption(string option, string input) {
    if (input.compare("/" + option) == 0 || input.compare("-" + option) == 0) {
        return true;
    }
    return false;
}

void runComputation() {

}
