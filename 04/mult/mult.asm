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


//LOAD R1
@R1
D=M //D = RAM[1] (multiplicand and counter for loop)
@counter
M=D

//SET R2 TO ZERO
@R2
M=0

(LOOP)
@counter
D=M
@END
D;JEQ //If counter is not greater than 0, break out of loop
@1
D=D-A //decrementing counter
@counter //and updating the value
M=D

//(MULTOP)
//load R0 (multiplier)
@R0
D=M //D = RAM[0]
@R2
M=M+D
@LOOP
0;JMP

//end program
(END)
@END
0;JMP



