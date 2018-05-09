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
    string removeFileExtension(string);
    void writeOutputFile(string, vector<string>);
    bool checkFileExtension(string);
private:
    vector<string> instructions;
};

#endif //   PARSER
