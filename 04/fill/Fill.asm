// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Fill.asm

// Runs an infinite loop that listens to the keyboard input.
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel;
// the screen should remain fully black as long as the key is pressed.
// When no key is pressed, the program clears the screen, i.e. writes
// "white" in every pixel;
// the screen should remain fully clear as long as no key is pressed.

// Put your code here.

@SCREEN
D=A
@screenpointer
M=D

//used to calculate pixel pointer
@rowcounter //each row has 32 consecutive words
M=0

@columncounter //each word has 16 bits
M=0

(INFLOOP) //Infinite reading and checking loop
//read from keyboard
@KBD
D=M
@key
M=D

@DIRECTIVE
0;JMP

(CLEAR)
//make the pixel equal to 0 (white)
//decrement the screen pointer
//RAM[memory_address] = 0

//Makes pixel white
@screenpointer
A=M
M=0

//Error checking
@SCREEN
D=M
@screenpointer
D=D-M
@INFLOOP
D;JEQ
@SCREEN
D=M+1
@screenpointer
D=D-M
@INFLOOP
D;JEQ

//Decrement pixel pointer
@screenpointer
M=M-1

@INFLOOP //go back for updates
0;JMP


(FILL)
//make the pixel equal to 1 (black)
//increment the screen pointer
//RAM[memory_address] = -1

//Makes pixel black
@screenpointer
A=M
M=-1

//Error checking
@131072
D=A
@screenpointer
D=D-M
@INFLOOP
D;JEQ

//Increment pixel pointer
@screenpointer
M=M+1
@INFLOOP //go back for updates
0;JMP

(DIRECTIVE)
//if kbd ascii code is 0, then clear
//else if ascii code is not 0, fill
@key
D=M
@CLEAR
D;JEQ
@FILL
0;JMP //go to location
@INFLOOP //reiterate the infinite loop
0;JMP



(END)
