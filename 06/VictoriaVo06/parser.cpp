#include "parser.h"

vector<string> Parser::readInputFile(char* inputFile)
{
    vector<string> instructions;
    if (checkFileExtension(inputFile) == true)
    {
        string line;
        ifstream myfile (inputFile);
        if(myfile.is_open())
        {
            while ( getline (myfile, line) )
            {
                //removes single line comments and blank lines
                if((line[0] != '/') && (line[1] != '/') && (line.length() != 1)
                   //getting rid of labels since they don't translate to anything
                    && ((line[0] != '(') && (line[line.length()-1] != ')')) )
                {
                        //get rid of whitespace
                        std::string::iterator end_pos = std::remove(line.begin(), line.end(), ' ');
                        line.erase(end_pos, line.end());
                        //handling for inline comments ex: @R2 //ugh another comment
                        line = line.substr(0, line.rfind("//"));
                        //add instruction to vector of instructions
                        instructions.push_back(line);
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
    
        //check vector of instructions
        for(int i = 0; i < instructions.size(); i++)
            cout << instructions[i] << endl;
    }
    else
    {
        cout << "Error: Invalid file extension. Must be an .asm file." << endl;
        exit (0);
    }
    return instructions;
}

bool Parser::checkFileExtension(string inputFileName)
{
    string fileName = inputFileName;
    string fileExtension = inputFileName.substr(inputFileName.length()-4, inputFileName.length()-1);
    
    if (fileExtension == ".asm")
        return true;
    
    return false;
}

string Parser::removeFileExtension(string inputFileName)
{
    string fileName = inputFileName;
    string fileNameWithoutExtension = fileName.substr(0, fileName.rfind("."));
    
    return(fileNameWithoutExtension);
}

//will write binary code

void Parser::writeOutputFile(string fileNameWithoutExtension, vector<string> instructionsToWrite)
{
    ofstream myfile (fileNameWithoutExtension + ".hack");
    if (myfile.is_open())
    {
        for(int i = 0; i < instructionsToWrite.size(); i++)
        {
            myfile << instructionsToWrite[i] << "\n";
        }
        myfile.close();
    }
    else cout << "Unable to open file";
    return;
}
