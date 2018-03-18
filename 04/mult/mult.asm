// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Mult.asm

// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

// Put your code here.

//Multiplication in assembly is basically repeated addition
//if we load R1's value, then we can set that to the "i" in a loop similar to a C/C++ loop
//pseudocode:
//int multiplier = R0
//int multiplicand = R1
//int product;
//for(int i = multiplicand; i > 0; i--)
//{
//  product += multiplier;
//}
//R2 = product;


//D = RAM[0]
@R0
D=M
//multiplier = RAM[0]
@multiplier
M=D

//D = RAM[1]
@R1
D=M
//multiplicand = RAM[1]
@multiplicand
M=D

//product = 0 (initialize product to 0)
@product
M=0

//set D register to A
@multiplicand
D=A
(Loop)
    //product += multiplier
    @multiplier
    D=A
    @product
    MD=M+D
    @Loop
    D=D-1;JLE

//RAM[2] = RAM[0] * RAM[1] (RAM[addr] = n)
@R2
D=A



