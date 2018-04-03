#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

int main() {
    ifstream input( "../data.csv" );

    for (string line; getline(input, line); ) {
        std::vector<double> vect;
        std::stringstream ss(line);
        double i;
        while (ss >> i) {
            vect.push_back(i);

            if (ss.peek() == ',')
                ss.ignore();
        }

        for (i=0; i< vect.size(); i++) {
            std::cout << vect.at(i) << std::endl;
        }
    }

    return 0;
}
