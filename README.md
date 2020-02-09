# pascal-compiler
a pascal ++ compiler using pgen and flex
to compile the compiler use:
g++ Compiler.cpp Parser.cpp CodeGenerator.cpp PTBlock.cpp Scanner.cpp -o compiler.o -std=c++0x
to use it type:
./compiler.o
clang out.ll -o out.o
./out.o
