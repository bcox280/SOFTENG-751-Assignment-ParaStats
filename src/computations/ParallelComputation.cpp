#include "ParallelComputation.hpp"

ParallelComputation::ParallelComputation(const string &fileName) : AbstractComputation(fileName) {

    const char * valueDelimiter = ",";
    const char * lineDelimiter = "\n";

    std::vector<double> vect;
    char *contents, *line, *indValue, *ptrContents, *ptrLine;
    std::ifstream inputStr(fileName);

    if (inputStr) {
        //Create a buffer to read from
        std::streambuf *pFileBuffer = inputStr.rdbuf();
        std::streamsize size = pFileBuffer->pubseekoff(0, inputStr.end);
        //Change the internal pointer to point back at the start of the file
        pFileBuffer->pubseekoff(0, inputStr.beg);
        contents = new char[size];
        //Get the sequence of characters specified (whole file) and copy it to contents
        pFileBuffer->sgetn(contents, size);
        //Close the stream
        inputStr.close();

        for (int j = 1; ; j++, contents = nullptr) {
            //Split each chunk on a new line, while keeping the location of where the pointer is
            line = strtok_r(contents, lineDelimiter, &ptrContents);
            //If its a null pointer, end is found
            if (line == nullptr) {
                break;
            }

            // TODO Send off chunk to a worker thread

            for ( ; ; line = nullptr) {
                //Split each line into individual values, while keeping the location of where the pointer is in the line
                indValue = strtok_r(line, valueDelimiter, &ptrLine);
                //If the value is not a null pointer we can add it to the vector, else we have reached the end of the line
                if (indValue != nullptr) {
                    vect.push_back(stod(indValue));
                } else {
                    break;
                }
            }
        }
    }
}

void ParallelComputation::computeData() {

}

SummaryStatistics ParallelComputation::provideProgressUpdate() {
    return SummaryStatistics();
}

string ParallelComputation::createSummary() {
    return string();
}
