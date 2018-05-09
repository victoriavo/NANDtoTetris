#include "symbolTable.h"



void SymbolTable::initializePredefinedSymbols()
{

    PredefinedMap.insert(std::make_pair("SP", 0));
    PredefinedMap.insert(std::make_pair("LCL", 1));
    PredefinedMap.insert(std::make_pair("ARG", 2));
    PredefinedMap.insert(std::make_pair("THIS", 3));
    PredefinedMap.insert(std::make_pair("THAT", 4));
    PredefinedMap.insert(std::make_pair("R0", 0));
    PredefinedMap.insert(std::make_pair("R1", 1));
    PredefinedMap.insert(std::make_pair("R2", 2));
    PredefinedMap.insert(std::make_pair("R3", 3));
    PredefinedMap.insert(std::make_pair("R4", 4));
    PredefinedMap.insert(std::make_pair("R5", 5));
    PredefinedMap.insert(std::make_pair("R6", 6));
    PredefinedMap.insert(std::make_pair("R7", 7));
    PredefinedMap.insert(std::make_pair("R8", 8));
    PredefinedMap.insert(std::make_pair("R9", 9));
    PredefinedMap.insert(std::make_pair("R10", 10));
    PredefinedMap.insert(std::make_pair("R11", 11));
    PredefinedMap.insert(std::make_pair("R12", 12));
    PredefinedMap.insert(std::make_pair("R13", 13));
    PredefinedMap.insert(std::make_pair("R14", 14));
    PredefinedMap.insert(std::make_pair("R15", 15));
    PredefinedMap.insert(std::make_pair("SCREEN", 16384));
    PredefinedMap.insert(std::make_pair("KBD", 24576));

    return;
}



//void SymbolTable::initializeSymbolTable()
//{
    

    
//}
