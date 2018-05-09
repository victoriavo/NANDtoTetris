#include <iostream>
#include "parser.h"
#include "code.h"
#include "symbolTable.h"

using namespace std;


int main(int argc, char* const argv[])
{
    vector<string> fileInstructions;
    //1. Parse the assembly file that is read in.
    Parser parser;
    fileInstructions = parser.readInputFile(argv[1]);
    Code code;
    vector<string> processedInstructions;
    processedInstructions = code.processInstructions(fileInstructions);
    string outputFileName = parser.removeFileExtension(argv[1]);
    parser.writeOutputFile(outputFileName, processedInstructions);
    return 0;
}

