#Object oriented Hello World ruby program
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
