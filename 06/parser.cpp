#include "parser.h"

void Parser::readInputFile(char* inputFile)
{
    string line;
    ifstream myfile (inputFile);
    if(myfile.is_open())
    {
        while ( getline (myfile, line) )
        {
            if((line[0] != '/') && (line[1] != '/') && (line.length() != 1)) //removes single line comments and blank lines
            {
                    cout << line << '\n';
            }
            //after finding start symbol, don't print until you find the end symbol
            if ((line[0] == '/') && (line[1] == '*')) //handles multiline (paragraph) comments
            {
                getline (myfile, line);
                while((line[line.length()-2] != '*') && (line[line.length()-1] != '/')
                      && (getline (myfile, line)))
                {
                        cout << "";
                }
            }
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
