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
@0
D=A
@screenpointer
A=M
@A
M=D
@16400
D=A
@screenpointer
D=D-M
@INFLOOP
D;JEQ
@16
D=A
@screenpointer
M=M-D
@INFLOOP //go back for updates
0;JMP


(FILL)
//make the pixel equal to 1 (black)
//increment the screen pointer
//RAM[memory_address] = -1
@-1
D=A
@screenpointer
A=M
@A
M=D
@131072
D=A
@screenpointer
D=D-M
@INFLOOP
D;JEQ
@16
D=A
@screenpointer
M=M+D
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
