#ifndef PARSER
#define PARSER

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Parser
{
public:
    vector<string> readInputFile(char*);
    string removeFileExtension(string&);
    //void writeOutputFile(String&);
private:
    vector<string> instructions;
};

#endif //   PARSER
