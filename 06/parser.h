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
    String removeFileExtension(String&);
    void writeOutputFile(String&);
};

#endif //   PARSER
