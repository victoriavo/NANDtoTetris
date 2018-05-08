#include "code.h"

vector<string> instructions;

vector<string> Code::processInstructions(vector<string> fileInstructions)
{
    instructions = fileInstructions;
    for(int i = 0; i < instructions.size(); i++)
    {
        if(instructions[i][0] == '@')//checks for basic A - instructions
        {
            replaceAInstructions(instructions[i], i);
        }
        else //C - instructions
        {
            replaceCInstructions(instructions[i], i);
        }
    }
    return instructions;
}

//only works for basic instructions
void Code::replaceAInstructions(string instructionLine, int index)
{
    //remove '@' symbol
    string instrLine = instructionLine;
    instrLine = instrLine.substr(1, (instructionLine.length()-1));
    //convert string address value to int and then to hexadecimal
    int addressVal = stoi(instrLine);
    string hexAddress = convertToHex(addressVal);
    
    instructions[index] = hexAddress;
    
    return;
}

//only works for basic instructions
void Code::replaceCInstructions(string instructionLine, int index)
{
    /* C-instruction: dest=comp;jump 
     * Either dest or jump fields may be empty.
     * If dest is empty, the "=" is omitted.
     * If jump is empty, the ";" is omitted.
     * Binary: 1 1 1 a  c1 c2 c3 c4  c5 c6 d1 d2  d3 j1 j2 j3
     */
    
    string instrLine = instructionLine;
    
    //determine if there is a dest, a jump, or both
    string dst = "=";
    string jmp = ";";
    size_t foundDest = instructionLine.find(dst);
    size_t foundJump = instructionLine.find(jmp);
    
    string highBits = "111";
    string compBits; //7 bits
    string destBits; //3 bits
    string jumpBits; //3 bits
    
    vector<string> fields;
    vector<string> translatedFields;
    
    if(foundDest !=std::string::npos && foundJump != std::string::npos) //Dest & Jump
    {
        //C-instruction: dest=comp;jump
        //Binary: 1 1 1 a  c1 c2 c3 c4  c5 c6 d1 d2  d3 j1 j2 j3
        fields = separateInstruction(instrLine, 0);
        //translatedFields = translateInstruction(fields, 0);
    }
    else if (foundDest !=std::string::npos && foundJump == std::string::npos) //Only Dest
    {
        //C-instruction: dest=comp
        //Binary: 1 1 1 a  c1 c2 c3 c4  c5 c6 d1 d2  d3 0 0 0
        fields = separateInstruction(instrLine, 1);
        //translatedFields = translateInstruction(fields, 1);
    }
    else if (foundDest ==std::string::npos && foundJump != std::string::npos) //Only Jump
    {
        //C-instruction: comp;jump
        //Binary: 1 1 1 0  c1 c2 c3 c4  c5 c6 0 0  0 j1 j2 j3
        fields = separateInstruction(instrLine, 2);
        //translatedFields = translateInstruction(fields, 2);
    }
    else
    {
        cout << "Error: Invalid C - instruction" << endl;
    }
}

vector<string> Code::separateInstruction(string instrLine, int function)
{
    vector<string> cinstruction;
    
    string dest;
    string comp;
    string jump;
    
    if(function == 0)
    {
        dest = instrLine.substr(0, instrLine.rfind("="));
        comp = instrLine.substr(instrLine.rfind("=")+1, instrLine.rfind(";"));
        jump = instrLine.substr(instrLine.rfind(";")+1, (instrLine.length()-1));
        cinstruction.push_back(dest);
        cinstruction.push_back(comp);
        cinstruction.push_back(jump);
    }
    if(function == 1)
    {
        dest = instrLine.substr(0, instrLine.rfind("="));
        comp = instrLine.substr(instrLine.rfind("=")+1, (instrLine.length()-1));
        cinstruction.push_back(dest);
        cinstruction.push_back(comp);
    }
    if(function == 2)
    {
        comp = instrLine.substr(0, instrLine.rfind(";"));
        jump = instrLine.substr(instrLine.rfind(";")+1, (instrLine.length()-1));
        cinstruction.push_back(comp);
        cinstruction.push_back(jump);
    }
    cout << "dest: " << dest << endl;
    cout << "comp: " << comp << endl;
    cout << "jump: " << jump << endl;
    
    return cinstruction;
}

vector<string> Code::translateInstruction(vector<string> fields, int function)
{
    vector<string> binary;
    
    string dest;
    string comp;
    string jump;
    
    /*
    if(function == 0)
    {
        
    }
    if(function == 1)
    {
        
    }
    if(function == 2)
    {
        
    }
     */
    
    return binary;
}

string Code::convertToHex(int value)
{
    //string of 16 characters
    stringstream sstream;
    sstream << std::hex << value;
    string lowerFigs = sstream.str();
    int numDigits = lowerFigs.length();
    int digitsToAdd = 16 - numDigits;
    string result;
    for(int i = 0; i < digitsToAdd; i++)
        result.append("0");
    result.append(lowerFigs);
    return result;
}
