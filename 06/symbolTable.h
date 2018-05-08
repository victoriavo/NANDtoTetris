#ifndef SYMBOLTABLE
#define SYMBOLTABLE

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

class SymbolTable
{
    public:
    void initializePredefinedSymbols();
    //void initializeSymbolTable();
    private:
    vector<string> instructions;
};

#endif //   SYMBOLTABLE
