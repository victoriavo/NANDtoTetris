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
    
    //remove R if it is an R value
    if(instrLine[0] == 'R' && isdigit(instrLine[1]) )
    {
        instrLine = instrLine.substr(1, (instructionLine.length()-1));
    }
    
    //if numeric value
    //convert string address value to int and then to binary
    if(isNumericAddress(instrLine))
    {
        int addressVal = stoi(instrLine);
        string binAddress =  std::bitset<16>(addressVal).to_string();
        instructions[index] = binAddress;
    }
    //else it is a symbol
    else
    {
        string symbolName = instrLine;
        
    }
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
        std::stringstream ss;
        ss << std::setw(3) << std::setfill('0') << "000";
        jumpBits = ss.str();
        fields = separateInstruction(instrLine, 1);
        for(int i = 0; i < fields.size(); i++)
            cout << "checking fields: " << fields[i] << "field size: " << fields[i].length() << endl;
        translatedFields = translateInstruction(fields, 1);
        translatedString.append(highBits);
        for(int i = 0; i < translatedFields.size(); i++)
        {
            translatedString.append(translatedFields[i]);
        }
        translatedString.append(jumpBits);
        instructions[index] = translatedString;
    }
    else if (foundDest ==std::string::npos && foundJump != std::string::npos) //Only Jump
    {
        //C-instruction: comp;jump
        //Binary: 1 1 1 0  c1 c2 c3 c4  c5 c6 0 0  0 j1 j2 j3
        std::stringstream ss1;
        ss1 << std::setw(3) << std::setfill('0') << "000";
        destBits = ss1.str();
        std::stringstream ss2;
        ss2 << std::setw(1) << std::setfill('0') << "0";
        abit = ss2.str();
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
        cout << "Instruction : " << instructions[index] << endl;
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
        //fields argument = dest, comp, jump
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
        //fields argument = dest, comp
        
        comp = compBin(fields[1])[1];
        a = compBin(fields[1])[0];
        dest = destBin(fields[0]); //dest is fine
        binary.push_back(a);
        binary.push_back(comp);
        binary.push_back(dest);
    }
    if(function == 2) //comp and jump fields
    {
        //fields argument = comp, jump
        comp = compZEqual0(fields[0]);
        binary.push_back(comp);
        jump = jumpBin(fields[1]);
        binary.push_back(jump);
    }
    return binary;
}

string Code::destBin(string dest)
{
    std::stringstream ss;
    string returnStr;
    
    if(dest == "M")
    {
        ss << std::setw(3) << std::setfill('0') << "001";
        returnStr= ss.str();
        return returnStr;
    }
    if(dest == "D")
    {
        ss << std::setw(3) << std::setfill('0') << "010";
        returnStr = ss.str();
        return returnStr;
    }
    if(dest == "MD")
    {
        ss << std::setw(3) << std::setfill('0') << "011";
        returnStr = ss.str();
        return returnStr;
    }
    if(dest == "A")
    {
        ss << std::setw(3) << std::setfill('0') << "100";
        returnStr = ss.str();
        return returnStr;
    }
    if(dest == "AM")
    {
        ss << std::setw(3) << std::setfill('0') << "101";
        returnStr = ss.str();
        return returnStr;
    }
    if(dest == "AD")
    {
        ss << std::setw(3) << std::setfill('0') << "110";
        returnStr = ss.str();
        return returnStr;
    }
    if(dest == "AMD")
    {
        ss << std::setw(3) << std::setfill('0') << "111";
        returnStr = ss.str();
        return returnStr;
    }
    return dest;
}

string Code::jumpBin(string jumpIn)
{
    string jump = jumpIn.substr(0, (jumpIn.length()));
    string jump1 = jumpIn.substr(0, (jumpIn.length()-1));
    std::stringstream ss;
    string returnStr;
    
    if(jump == "JGT" || jump1 == "JGT")
    {
        ss << std::setw(3) << std::setfill('0') << "001";
        returnStr = ss.str();
        return returnStr;
    }
    if(jump == "JEQ" || jump1 == "JEQ")
    {
        ss << std::setw(3) << std::setfill('0') << "010";
        returnStr = ss.str();
        return returnStr;
    }
    if(jump == "JGE" || jump1 == "JGE")
    {
        ss << std::setw(3) << std::setfill('0') << "011";
        returnStr = ss.str();
        return returnStr;
    }
    if(jump == "JLT" || jump1 == "JLT")
    {
        ss << std::setw(3) << std::setfill('0') << "100";
        returnStr = ss.str();
        return returnStr;
    }
    if(jump == "JNE" || jump1 == "JNE")
    {
        ss << std::setw(3) << std::setfill('0') << "101";
        returnStr = ss.str();
        return returnStr;
    }
    if(jump == "JLE" || jump1 == "JLE")
    {
        ss << std::setw(3) << std::setfill('0') << "110";
        returnStr = ss.str();
        return returnStr;
    }
    if(jump == "JMP" || jump1 == "JMP")
    {
        ss << std::setw(3) << std::setfill('0') << "111";
        returnStr = ss.str();
        return returnStr;
    }
    
    return jump;
}


string Code::compZEqual0(string compIn)
{
    cout << "compZEqual0" << endl;
    string comp = compIn.substr(0, (compIn.length()-1));
    cout << "comp : " << comp << endl;
    std::stringstream ss;
    string returnStr;
    
    if(comp == "0")
    {
        ss << std::setw(6) << std::setfill('0') << "101010";
        returnStr = ss.str();
        return returnStr;
    }
    if(comp == "1")
    {
        ss << std::setw(6) << std::setfill('0') << "111111";
        returnStr = ss.str();
        return returnStr;
    }
    if(comp == "-1")
    {
        ss << std::setw(6) << std::setfill('0') << "111010";
        returnStr = ss.str();
        return returnStr;
    }
    if(comp == "D")
    {
        ss << std::setw(6) << std::setfill('0') << "001100";
        returnStr = ss.str();
        return returnStr;
    }
    if(comp == "A")
    {
        ss << std::setw(6) << std::setfill('0') << "110000";
        returnStr = ss.str();
        return returnStr;
    }
    if(comp == "!D")
    {
        ss << std::setw(6) << std::setfill('0') << "001101";
        returnStr = ss.str();
        return returnStr;
    }
    if(comp == "!A")
    {
        ss << std::setw(6) << std::setfill('0') << "110001";
        returnStr = ss.str();
        return returnStr;
    }
    if(comp == "-D")
    {
        ss << std::setw(6) << std::setfill('0') << "001111";
        returnStr = ss.str();
        return returnStr;
    }
    if(comp == "-A")
    {
        ss << std::setw(6) << std::setfill('0') << "110011";
        returnStr = ss.str();
        return returnStr;
    }
    if(comp == "D+1")
    {
        ss << std::setw(6) << std::setfill('0') << "011111";
        returnStr = ss.str();
        return returnStr;
    }
    if(comp == "A+1")
    {
        ss << std::setw(6) << std::setfill('0') << "110111";
        returnStr = ss.str();
        return returnStr;
    }
    if(comp == "D-1")
    {
        ss << std::setw(6) << std::setfill('0') << "001110";
        returnStr = ss.str();
        return returnStr;
    }
    if(comp == "A-1")
    {
        ss << std::setw(6) << std::setfill('0') << "110010";
        returnStr = ss.str();
        return returnStr;
    }
    if(comp == "D+A")
    {
        ss << std::setw(6) << std::setfill('0') << "000010";
        returnStr = ss.str();
        return returnStr;
    }
    if(comp == "D-A")
    {
        ss << std::setw(6) << std::setfill('0') << "010011";
        returnStr = ss.str();
        return returnStr;
    }
    if(comp == "A-D")
    {
        ss << std::setw(6) << std::setfill('0') << "000111";
        returnStr = ss.str();
        return returnStr;
    }
    if(comp == "D&A")
    {
        ss << std::setw(6) << std::setfill('0') << "000000";
        returnStr = ss.str();
        return returnStr;
    }
    if(comp == "D|A")
    {
        ss << std::setw(6) << std::setfill('0') << "010101";
        returnStr = ss.str();
        return returnStr;
    }
    return comp;
}

vector<string> Code::compBin(string compIn)
{
    cout << "compBin" << endl;
    string comp = compIn.substr(0, (compIn.length()));
    string comp1 = compIn.substr(0, (compIn.length()-1));
    cout << "comp : " << comp << endl;
    vector<string> binary;
    string a;
    string compBin;
    
    std::stringstream ss;
    std::stringstream ss1;

    
    if(comp == "M" || comp1 == "M" )
    {
        cout << "right here " << endl;
        ss << std::setw(6) << std::setfill('0') << "110000";
        compBin = ss.str();
        a = "1";
    }
    if(comp == "!M" || comp1 == "!M")
    {
        ss << std::setw(6) << std::setfill('0') << "110001";
        compBin = ss.str();
        a = "1";
    }
    if(comp == "-M" || comp1 == "-M")
    {
        ss << std::setw(6) << std::setfill('0') << "110011";
        compBin = ss.str();
        a = "1";
    }
    if(comp == "M+1" || comp1 == "M+1")
    {
        ss << std::setw(6) << std::setfill('0') << "110111";
        compBin = ss.str();
        a = "1";
    }
    if(comp == "M-1" || comp1 == "M-1")
    {
        ss << std::setw(6) << std::setfill('0') << "110010";
        compBin = ss.str();
        a = "1";
    }
    if(comp == "D+M" || comp1 == "D+M")
    {
        ss << std::setw(6) << std::setfill('0') << "000010";
        compBin = ss.str();
        a = "1";
    }
    if(comp == "D-M" || comp1 == "D-M")
    {
        ss << std::setw(6) << std::setfill('0') << "010011";
        compBin = ss.str();
        a = "1";
    }
    if(comp == "M-D" || comp1 == "M-D")
    {
        ss << std::setw(6) << std::setfill('0') << "000111";
        compBin = ss.str();
        a = "1";
    }
    if(comp == "D&M" || comp1 == "D&M")
    {
        ss << std::setw(6) << std::setfill('0') << "000000";
        compBin = ss.str();
        a = "1";
    }
    if(comp == "D|M" || comp1 == "D|M")
    {
        ss << std::setw(6) << std::setfill('0') << "010101";
        compBin = ss.str();
        a = "1";
    }
    
    
    
    
    
    
    if(comp == "0" || comp1 == "0")
    {
        ss << std::setw(6) << std::setfill('0') << "101010";
        compBin = ss.str();
        ss1 << std::setw(1) << std::setfill('0') << "0";
        a = ss1.str();
    }
    if(comp == "1" || comp1 == "1")
    {
        ss << std::setw(6) << std::setfill('0') << "111111";
        compBin = ss.str();
        ss1 << std::setw(1) << std::setfill('0') << "0";
        a = ss1.str();
    }
    if(comp == "-1" || comp1 == "-1")
    {
        ss << std::setw(6) << std::setfill('0') << "111010";
        compBin = ss.str();
        ss1 << std::setw(1) << std::setfill('0') << "0";
        a = ss1.str();
    }
    if(comp == "D" || comp1 == "D")
    {
        ss << std::setw(6) << std::setfill('0') << "001100";
        compBin = ss.str();
        ss1 << std::setw(1) << std::setfill('0') << "0";
        a = ss1.str();
    }
    if(comp == "A" || comp1 == "A")
    {
        ss << std::setw(6) << std::setfill('0') << "110000";
        compBin = ss.str();
        ss1 << std::setw(1) << std::setfill('0') << "0";
        a = ss1.str();
    }
    if(comp == "!D" || comp1 == "!D")
    {
        ss << std::setw(6) << std::setfill('0') << "001101";
        compBin = ss.str();
        ss1 << std::setw(1) << std::setfill('0') << "0";
        a = ss1.str();
    }
    if(comp == "!A" || comp1 == "!A")
    {
        ss << std::setw(6) << std::setfill('0') << "110001";
        compBin = ss.str();
        ss1 << std::setw(1) << std::setfill('0') << "0";
        a = ss1.str();
    }
    if(comp == "-D" || comp1 == "-D")
    {
        ss << std::setw(6) << std::setfill('0') << "001111";
        compBin = ss.str();
        ss1 << std::setw(1) << std::setfill('0') << "0";
        a = ss1.str();
    }
    if(comp == "-A" || comp1 == "-A")
    {
        ss << std::setw(6) << std::setfill('0') << "110011";
        compBin = ss.str();
        ss1 << std::setw(1) << std::setfill('0') << "0";
        a = ss1.str();
    }
    if(comp == "D+1" || comp1 == "D+1")
    {
        ss << std::setw(6) << std::setfill('0') << "011111";
        compBin = ss.str();
        ss1 << std::setw(1) << std::setfill('0') << "0";
        a = ss1.str();
    }
    if(comp == "A+1" || comp1 == "A+1")
    {
        ss << std::setw(6) << std::setfill('0') << "110111";
        compBin = ss.str();
        ss1 << std::setw(1) << std::setfill('0') << "0";
        a = ss1.str();
    }
    if(comp == "D-1" || comp1 == "D-1")
    {
        ss << std::setw(6) << std::setfill('0') << "001110";
        compBin = ss.str();
        ss1 << std::setw(1) << std::setfill('0') << "0";
        a = ss1.str();
    }
    if(comp == "A-1" || comp1 == "A-1")
    {
        ss << std::setw(6) << std::setfill('0') << "110010";
        compBin = ss.str();
        ss1 << std::setw(1) << std::setfill('0') << "0";
        a = ss1.str();
    }
    if(comp == "D+A" || comp1 == "D+A")
    {
        ss << std::setw(6) << std::setfill('0') << "000010";
        compBin = ss.str();
        ss1 << std::setw(1) << std::setfill('0') << "0";
        a = ss1.str();
    }
    if(comp == "D-A" || comp1 == "D-A")
    {
        ss << std::setw(6) << std::setfill('0') << "010011";
        compBin = ss.str();
        ss1 << std::setw(1) << std::setfill('0') << "0";
        a = ss1.str();
    }
    if(comp == "A-D" || comp1 == "A-D")
    {
        ss << std::setw(6) << std::setfill('0') << "000111";
        compBin = ss.str();
        ss1 << std::setw(1) << std::setfill('0') << "0";
        a = ss1.str();
    }
    if(comp == "D&A" || comp1 == "D&A")
    {
        ss << std::setw(6) << std::setfill('0') << "000000";
        compBin = ss.str();
        ss1 << std::setw(1) << std::setfill('0') << "0";
        a = ss1.str();
    }
    if(comp == "D|A" || comp1 == "D|A")
    {
        ss << std::setw(6) << std::setfill('0') << "010101";
        compBin = ss.str();
        ss1 << std::setw(1) << std::setfill('0') << "0";
        a = ss1.str();
    }
    
    binary.push_back(a);
    binary.push_back(compBin);
    return binary;

}

bool Code::isNumericAddress(string address)
{
    for(int i = 0; i < address.length()-1; i++)
    {
        if(isdigit(address[i]) == 0)
        {
           return false;
        }
    }
    return true;
}
