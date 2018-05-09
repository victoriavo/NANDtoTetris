#include "symbolTable.h"



void SymbolTable::initializePredefinedSymbols()
{
    //Making a symbol table/map
    //Formated with LABEL - RAM ADDRESS - HEXADECIMAL ADDRESS
    
    /*
    Key sp("SP", 0); //hexa: 0x0000
    Key lcl("LCL", 1); //hexa: 0x0001
    Key arg("ARG", 2); //hexa: 0x0002
    Key _this("THIS", 3); //hexa: 0x0003
    Key that("THAT", 4); //hexa: 0x0004
    Key r0("RO", 0); //hexa: 0x0000
    Key r1("R1", 1); //hexa: 0x0001
    Key r2("R2", 2); //hexa: 0x0002
    Key r3("R3", 3); //hexa: 0x0003
    Key r4("R4", 4); //hexa: 0x0004
    Key r5("R5", 5); //hexa: 0x0005
    Key r6("R6", 6); //hexa: 0x0006
    Key r7("R7", 7); //hexa: 0x0007
    Key r8("R8", 8); //hexa: 0x0008
    Key r9("R9", 9); //hexa: 0x0009
    Key r10("R10", 10); //hexa: 0x000A
    Key r11("R11", 11); //hexa: 0x000B
    Key r12("R12", 12); //hexa: 0x000C
    Key r13("R13", 13); //hexa: 0x000D
    Key r14("R14", 14); //hexa: 0x000E
    Key r15("R15", 15); //hexa: 0x000F
    Key screen("SCREEN", 16384); //hexa: 0x4000
    Key kbd("KBD", 24576); //hexa: 0x6000
    
    
    PredefinedMap.insert(std::make_pair(sp, "0x0000"));
    PredefinedMap.insert(std::make_pair(lcl, "0x0001"));
    PredefinedMap.insert(std::make_pair(arg, "0x0002"));
    PredefinedMap.insert(std::make_pair(_this, "0x0003"));
    PredefinedMap.insert(std::make_pair(that, "0x0004"));
    PredefinedMap.insert(std::make_pair(r0, "0x0000"));
    PredefinedMap.insert(std::make_pair(r1, "0x0001"));
    PredefinedMap.insert(std::make_pair(r2, "0x0002"));
    PredefinedMap.insert(std::make_pair(r3, "0x0003"));
    PredefinedMap.insert(std::make_pair(r4, "0x0004"));
    PredefinedMap.insert(std::make_pair(r5, "0x0005"));
    PredefinedMap.insert(std::make_pair(r6, "0x0006"));
    PredefinedMap.insert(std::make_pair(r7, "0x0007"));
    PredefinedMap.insert(std::make_pair(r8, "0x0008"));
    PredefinedMap.insert(std::make_pair(r9, "0x0009"));
    PredefinedMap.insert(std::make_pair(r10, "0x000A"));
    PredefinedMap.insert(std::make_pair(r11, "0x000B"));
    PredefinedMap.insert(std::make_pair(r12, "0x000C"));
    PredefinedMap.insert(std::make_pair(r13, "0x000D"));
    PredefinedMap.insert(std::make_pair(r14, "0x000E"));
    PredefinedMap.insert(std::make_pair(r15, "0x000F"));
    PredefinedMap.insert(std::make_pair(screen, "0x4000"));
    PredefinedMap.insert(std::make_pair(kbd, "0x6000"));
     */
    /*
    Key sp("SP"); //hexa: 0x0000
    Key lcl("LCL"); //hexa: 0x0001
    Key arg("ARG"); //hexa: 0x0002
    Key _this("THIS"); //hexa: 0x0003
    Key that("THAT"); //hexa: 0x0004
    Key r0("RO"); //hexa: 0x0000
    Key r1("R1"); //hexa: 0x0001
    Key r2("R2"); //hexa: 0x0002
    Key r3("R3"); //hexa: 0x0003
    Key r4("R4"); //hexa: 0x0004
    Key r5("R5"); //hexa: 0x0005
    Key r6("R6"); //hexa: 0x0006
    Key r7("R7"); //hexa: 0x0007
    Key r8("R8"); //hexa: 0x0008
    Key r9("R9"); //hexa: 0x0009
    Key r10("R10"); //hexa: 0x000A
    Key r11("R11"); //hexa: 0x000B
    Key r12("R12"); //hexa: 0x000C
    Key r13("R13"); //hexa: 0x000D
    Key r14("R14"); //hexa: 0x000E
    Key r15("R15"); //hexa: 0x000F
    Key screen("SCREEN"); //hexa: 0x4000
    Key kbd("KBD"); //hexa: 0x6000
    */
    
    PredefinedMap.insert(std::make_pair("SP", 0));
    PredefinedMap.insert(std::make_pair("LCL", 1));
    PredefinedMap.insert(std::make_pair("ARG", 2));
    PredefinedMap.insert(std::make_pair("THIS", 3));
    PredefinedMap.insert(std::make_pair("THAT", 4));
    PredefinedMap.insert(std::make_pair("R0", 0));
    PredefinedMap.insert(std::make_pair("R1", 1));
    PredefinedMap.insert(std::make_pair("R2", 2));
    PredefinedMap.insert(std::make_pair("R3", 3));
    PredefinedMap.insert(std::make_pair("R4", 4));
    PredefinedMap.insert(std::make_pair("R5", 5));
    PredefinedMap.insert(std::make_pair("R6", 6));
    PredefinedMap.insert(std::make_pair("R7", 7));
    PredefinedMap.insert(std::make_pair("R8", 8));
    PredefinedMap.insert(std::make_pair("R9", 9));
    PredefinedMap.insert(std::make_pair("R10", 10));
    PredefinedMap.insert(std::make_pair("R11", 11));
    PredefinedMap.insert(std::make_pair("R12", 12));
    PredefinedMap.insert(std::make_pair("R13", 13));
    PredefinedMap.insert(std::make_pair("R14", 14));
    PredefinedMap.insert(std::make_pair("R15", 15));
    PredefinedMap.insert(std::make_pair("SCREEN", 16384));
    PredefinedMap.insert(std::make_pair("KBD", 24576));

    return;
}



//void SymbolTable::initializeSymbolTable()
//{
    

    
//}
