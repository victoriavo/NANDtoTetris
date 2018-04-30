//  Prog.asm.s
//  Created by Victoria Vo on 4/30/18.
//  Translates Prog.asm into Prog.hack

//Eliminate comments and white space
//Allocate variables to memory
//Translate each assembly command into a single 16-bit instruction written in the Hack machine language
//Treat label declarations like (LOOP) and (END) as pseudo commands that generate no code

//Command line:
put "Hello World"

//Object oriented
class HelloWorld
    def initialize(name)
        @name = name.capitalize
    end
    def sayHi
        puts "Hello #{@name}!"
    end
end

hello = HelloWorld.new("World")
hello.sayHi
