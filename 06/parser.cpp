#include "parser.h"

void Parser::readInputFile(char* inputFile)
{
    string line;
    ifstream myfile (inputFile);
    if(myfile.is_open())
    {
        while ( getline (myfile, line) )
        {
            cout << line << '\n';
        }
        myfile.close();
    }
    else cout << "Unable to open file";
    
    return;
}

string Parser::removeFileExtension(string& inputFileName)
{
    string fileName = inputFileName;
    string fileNameWithoutExtension = fileName.substr(0, fileName.rfind("."));
    
    return(fileNameWithoutExtension);
}

//will write binary code
/*
void Parser::writeOutputFile(String& fileNameWithoutExtension)
{
    ofstream myfile (fileNameWithoutExtension + ".hack");
    if (myfile.is_open())
    {
        myfile << "This is a line.\n";
        myfile << "This is another line.\n";
        myfile.close();
    }
    else cout << "Unable to open file";
    return 0;
}
*/
