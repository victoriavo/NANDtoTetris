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
    //typedef key<string> Key;
    typedef map< string, int > Map;
    typedef map< string, int > SymbolMap;
    
    public:
    void initializePredefinedSymbols();
    //void initializeSymbolTable();
    SymbolMap Symbols;
    Map PredefinedMap;
    private:
    //typedef pair<string, int> Key;
   
    vector<string> instructions;
    
};

#endif //   SYMBOLTABLE
