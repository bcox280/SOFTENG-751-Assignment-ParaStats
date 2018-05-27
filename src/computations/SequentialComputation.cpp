#include "SequentialComputation.hpp"

SequentialComputation::SequentialComputation(const string &fileName) : AbstractComputation(fileName) {
}

SummaryStatistics SequentialComputation::computeData() {
    const char *valueDelimiter = ",";
    const char *lineDelimiter = "\n";
    unsigned long long completedDataPoints = 0;
    unsigned long long dataPointsInChunk = 0;
    double max = -DBL_MAX;
    double min = DBL_MAX;
    double M1 = 0;
    double M2 = 0;
    double M3 = 0;
    double M4 = 0;

    char *contents, *line, *indValue, *ptrContents;
    std::ifstream inputStr(_fileName);

    if (inputStr) {
        //Create a buffer to read from
        std::streambuf* pFileBuffer = inputStr.rdbuf();
        std::streamsize size = pFileBuffer->pubseekoff(0, std::ifstream::end);
        //Change the internal pointer to point back at the start of the file
        pFileBuffer->pubseekoff(0, std::ifstream::beg);
        contents = new char[size];

        //Get the sequence of characters specified (whole file) and copy it to contents
        pFileBuffer->sgetn(contents, size);
        //Close the stream
        inputStr.close();

        for (;; contents = nullptr) {
            //Split each chunk on a new line, while keeping the location of where the pointer is
            line = strtok_r(contents, lineDelimiter, &ptrContents);
            //If its a null pointer, end is found
            if (line == nullptr) {
                break;
            }
            for (;; line = nullptr) {
                //Split each line into individual values, while keeping the location of where the pointer is in the line
                indValue = strtok(line, valueDelimiter);
                //If the value is not a null pointer we can add it to the vector, else we have reached the end of the line
                if (indValue == nullptr) {
                    break;
                }

                if (max < stod(indValue)) {
                    max = stod(indValue);
                }
                if (min > stod(indValue)) {
                    min = stod(indValue);
                }

                unsigned long long n1 = completedDataPoints;
                unsigned long long n = completedDataPoints + 1;
                double delta = stod(indValue) - M1;
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
                    _summaryStats = newStats;
                    // TODO Call the main print SS here
                    dataPointsInChunk = 0;
                }
            }
        }
        delete[] contents;
    }

    SummaryStatistics finalStats = SummaryStatistics();
    finalStats.setM1(M1);
    finalStats.setM2(M2);
    finalStats.setM3(M3);
    finalStats.setM4(M4);
    finalStats.setMax(max);
    finalStats.setMin(min);
    finalStats.setCount(completedDataPoints);
    _summaryStats = finalStats;

    return _summaryStats;
}

SummaryStatistics SequentialComputation::provideProgressUpdate() {
    return SequentialComputation::_summaryStats;
}
