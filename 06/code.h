#ifndef CODE
#define CODE

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

class Code
{
    public:
    vector<string> processInstructions(vector<string>);
    void replaceAInstructions(string, int);
    string convertToHex(int);
    private:
    vector<string> instructions;
};

#endif //   CODE
