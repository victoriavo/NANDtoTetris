#include "parser.h"

void Parser::openInputFile(char* inputFile)
{
    
}

String Parser::removeFileExtension(String& fileName)
{
    string fileName = fileName;
    string fileNameWithoutExtension = fileName.substr(0, fileName.rfind("."));
    
    return(fileNameWithoutExtension);
}
