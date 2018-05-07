#ifndef PARSER
#define PARSER

#include <iostream>
#include <fstream>

using namespace std;

class Parser
{
public:
    void openInputFile(char*);
    String removeFileExtension(String& string);
};

#endif //   PARSER
