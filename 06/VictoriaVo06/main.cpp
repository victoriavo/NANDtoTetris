#include <iostream>
#include "parser.h"
#include "code.h"
#include "symbolTable.h"

using namespace std;

//initializes the symbol table with all the predefined symbols and their pre-allocated RAM addresses
//void initialization()
//{
//    cout << "initialization" << endl;
//    return;
//}

//goes through the entire assembly program, line by line, and builds the symbol table without generating any code
//keeps a running number recording the ROM address into which the current command will eventually be loaded
//number starts at 0 and is incremented by 1 whenever a C-instruction or an A-instruction is encounterd
//running number does not change when a label pseudocommand or a comment is encountered
//each time a pseudocommand (Xxx) is encountered, add a new entry to the symbol table, associating Xxx with the ROM address that will eventually store the next command in the program
//this pass results in entering al the program's labels along with their ROM addresses into the symbol table
//The program's variables are handled in the second pass
//void firstPass()
//{
//    cout << "first pass" << endl;
//    return;
//}

//go through the entire program and parse each line
//each time a symbolic A-instruction is encounterd, namely @Xxx where Xxx is a symbol and not a number,
//look up Xxx in the symbol table
//If symbol is found in the table, replace it with its numeric meaning and complete the command's translation
//if the symbol is not found in the table, then it must represent a new variable
//to handle it, add the pair (Xxx, n) to the symbol table, where n is the next available RAM address, and complete the command's translation
//The allocated RAM addresses are consecutive numbers, starting at address 16 (just after the address is allocated to the predefined symbols)
//void secondPass()
//{
//    cout << "second pass" << endl;
//    return;
//}

int main(int argc, char* const argv[])
{
    vector<string> fileInstructions;
    //1. Parse the assembly file that is read in.
    Parser parser;
    fileInstructions = parser.readInputFile(argv[1]);
    //SymbolTable symbolTable;
    Code code;
    vector<string> processedInstructions;
    processedInstructions = code.processInstructions(fileInstructions);
    string outputFileName = parser.removeFileExtension(argv[1]);
    parser.writeOutputFile(outputFileName, processedInstructions);
    return 0;
}

