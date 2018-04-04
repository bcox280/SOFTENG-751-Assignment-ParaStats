#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cstring>

using namespace std;

void printHelp();
void printVersion(string version);
bool checkOption(string option, string input);

int main(int argc, char *argv[]) {
    const string version ("beta");
    string outputFilename ("results.txt");
    string inputFilename ("../data/voltage_normal_1280000.csv");
    bool parallel = true;
    bool quiet = false;

    bool inputChangeFlag = false;
    bool outputChangeFlag = false;
    for (int i = 0; i < argc; i++) {
        if (inputChangeFlag) {
            inputChangeFlag = false;
            if (checkOption("i", argv[i-1])) {
                inputFilename = argv[i];
            }
        } else if (outputChangeFlag) {
            outputChangeFlag = false;
            if (checkOption("o", argv[i-1])) {
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

    ifstream input(inputFilename);

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

        for (int i = 0; i < vect.size(); i++) {
            std::cout << vect.at(i) << std::endl;
        }
    }

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
