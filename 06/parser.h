#ifndef PARSER
#define PARSER

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Parser
{
public:
    void readInputFile(char*);
    string removeFileExtension(string&);
    //void writeOutputFile(String&);
};

#endif //   PARSER
