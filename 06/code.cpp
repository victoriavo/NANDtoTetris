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
    string binAddress =  std::bitset<16>(addressVal).to_string();
    instructions[index] = binAddress;
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
    string abit;
    string compBits; //7 bits
    string destBits; //3 bits
    string jumpBits; //3 bits
    
    vector<string> fields;
    vector<string> translatedFields;
    
    string translatedString;
    
    if(foundDest !=std::string::npos && foundJump != std::string::npos) //Dest & Jump
    {
        //C-instruction: dest=comp;jump
        //Binary: 1 1 1 a  c1 c2 c3 c4  c5 c6 d1 d2  d3 j1 j2 j3
        fields = separateInstruction(instrLine, 0);
        translatedFields = translateInstruction(fields, 0);
        translatedString.append(highBits);
        for(int i = 0; i < translatedFields.size(); i++)
            translatedString.append(translatedFields[i]);
        
        instructions[index] = translatedString;
    }
    else if (foundDest !=std::string::npos && foundJump == std::string::npos) //Only Dest
    {
        //C-instruction: dest=comp
        //Binary: 1 1 1 a  c1 c2 c3 c4  c5 c6 d1 d2  d3 0 0 0
        jumpBits = "000";
        fields = separateInstruction(instrLine, 1);
        translatedFields = translateInstruction(fields, 1);
        translatedString.append(highBits);
        for(int i = 0; i < translatedFields.size(); i++)
            translatedString.append(translatedFields[i]);
        translatedString.append(jumpBits);
        
        instructions[index] = translatedString;
    }
    else if (foundDest ==std::string::npos && foundJump != std::string::npos) //Only Jump
    {
        //C-instruction: comp;jump
        //Binary: 1 1 1 0  c1 c2 c3 c4  c5 c6 0 0  0 j1 j2 j3
        abit = "0";
        destBits = "000";
        fields = separateInstruction(instrLine, 2);
        translatedFields = translateInstruction(fields, 2);
        translatedString.append(highBits);
        translatedString.append(abit);
        translatedString.append(translatedFields[0]);
        translatedString.append(destBits);
        translatedString.append(translatedFields[1]);
        
        instructions[index] = translatedString;
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
    string a;
    
    
    if(function == 0) //dest, comp, and jump fields
    {
        dest = destBin(fields[0]);
        comp = compBin(fields[1])[1];
        a = compBin(fields[1])[0];
        jump = jumpBin(fields[2]);
        binary.push_back(a);
        binary.push_back(comp);
        binary.push_back(dest);
        binary.push_back(jump);
    }
    if(function == 1) //dest and comp fields
    {
        comp = compBin(fields[1])[1];
        a = compBin(fields[1])[0];
        dest = destBin(fields[0]);
        binary.push_back(a);
        binary.push_back(comp);
        binary.push_back(dest);
    }
    if(function == 2) //comp and jump fields
    {
        comp = compZEqual0(fields[0]);
        binary.push_back(comp);
        jump = jumpBin(fields[1]);
        binary.push_back(jump);
    }
    for(int i = i; i < binary.size(); i++)
        cout << binary[i] << endl;
    return binary;
}

string Code::destBin(string dest)
{
    if(dest == "M")
        return "001";
    if(dest == "D")
        return "010";
    if(dest == "MD")
        return "011";
    if(dest == "A")
        return "100";
    if(dest == "AM")
        return "101";
    if(dest == "AD")
        return "110";
    if(dest == "AMD")
        return "111";
    return dest;
}

string Code::jumpBin(string jump)
{
    if(jump == "JGT")
        return "001";
    if(jump == "JEQ")
        return "010";
    if(jump == "JGE")
        return "011";
    if(jump == "JLT")
        return "100";
    if(jump == "JNE")
        return "101";
    if(jump == "JLE")
        return "110";
    if(jump == "JMP")
        return "111";
    return jump;
}


string Code::compZEqual0(string comp)
{
    if(comp == "0")
        return "101010";
    if(comp == "1")
        return "111111";
    if(comp == "-1")
        return "111010";
    if(comp == "D")
        return "001100";
    if(comp == "A")
        return "110000";
    if(comp == "!D")
        return "001101";
    if(comp == "!A")
        return "110001";
    if(comp == "-D")
        return "001111";
    if(comp == "-A")
        return "110011";
    if(comp == "D+1")
        return "011111";
    if(comp == "A+1")
        return "110111";
    if(comp == "D-1")
        return "001110";
    if(comp == "A-1")
        return "110010";
    if(comp == "D+A")
        return "000010";
    if(comp == "D-A")
        return "010011";
    if(comp == "A-D")
        return "000111";
    if(comp == "D&A")
        return "000000";
    if(comp == "D|A")
        return "010101";
    return comp;
}

vector<string> Code::compBin(string comp)
{
    vector<string> binary;
    string a;
    string compBin;
    
    if(comp == "M")
    {
        compBin = "110000";
        a = "1";
    }
    if(comp == "!M")
    {
        compBin = "110001";
        a = "1";
    }
    if(comp == "-M")
    {
        compBin = "110011";
        a = "1";
    }
    if(comp == "M+1")
    {
        compBin = "110111";
        a = "1";
    }
    if(comp == "M-1")
    {
        compBin = "110010";
        a = "1";
    }
    if(comp == "D+M")
    {
        compBin = "000010";
        a = "1";
    }
    if(comp == "D-M")
    {
        compBin = "010011";
        a = "1";
    }
    if(comp == "M-D")
    {
        compBin = "000111";
        a = "1";
    }
    if(comp == "D&M")
    {
        compBin = "000000";
        a = "1";
    }
    if(comp == "D|M")
    {
        compBin = "010101";
        a = "1";
    }
    if(comp == "0")
    {
        compBin = "101010";
        a = "0";
    }
    if(comp == "1")
    {
        compBin = "111111";
        a = "0";
    }
    if(comp == "-1")
    {
        compBin = "111010";
        a = "0";
    }
    if(comp == "D")
    {
        compBin = "001100";
        a = "0";
    }
    if(comp == "A")
    {
        compBin = "110000";
        a = "0";
    }
    if(comp == "!D")
    {
        compBin = "001101";
        a = "0";
    }
    if(comp == "!A")
    {
        compBin = "110001";
        a = "0";
    }
    if(comp == "-D")
    {
        compBin = "001111";
        a = "0";
    }
    if(comp == "-A")
    {
        compBin = "110011";
        a = "0";
    }
    if(comp == "D+1")
    {
        compBin = "011111";
        a = "0";
    }
    if(comp == "A+1")
    {
        compBin = "110111";
        a = "0";
    }
    if(comp == "D-1")
    {
        compBin = "001110";
        a = "0";
    }
    if(comp == "A-1")
    {
        compBin = "110010";
        a = "0";
    }
    if(comp == "D+A")
    {
        compBin = "000010";
        a = "0";
    }
    if(comp == "D-A")
    {
        compBin = "010011";
        a = "0";
    }
    if(comp == "A-D")
    {
        compBin = "000111";
        a = "0";
    }
    if(comp == "D&A")
    {
        compBin = "000000";
        a = "0";
    }
    if(comp == "D|A")
    {
        compBin = "010101";
        a = "0";
    }
    
    binary.push_back(a);
    binary.push_back(compBin);
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
