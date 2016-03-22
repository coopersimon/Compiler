CC=g++

all : bin/c_codegen

bin/c_codegen : src/parser.tab.cpp src/lexer.yy.cpp src/ast.o src/parser.tab.hpp src/ast.hpp src/status.hpp src/status.o src/variables.hpp src/variables.o src/compiler.cpp
	$(CC) src/parser.tab.cpp src/lexer.yy.cpp src/ast.o src/status.o src/variables.o src/compiler.cpp -o bin/c_codegen
	@cat cow.out

src/variables.o : src/variables.cpp src/variables.hpp
	$(CC) -c src/variables.cpp -o src/variables.o

src/status.o : src/status.hpp src/status.cpp src/variables.hpp
	$(CC) -c src/status.cpp -o src/status.o

src/ast.o : src/ast.hpp src/ast.cpp src/status.hpp src/variables.hpp
	$(CC) -c src/ast.cpp -o src/ast.o

src/parser.tab.cpp src/parser.tab.hpp : src/parser.y src/ast.hpp
	bison -d src/parser.y -o src/parser.tab.cpp

src/lexer.yy.cpp : src/lexer.l src/ast.hpp src/parser.tab.hpp
	flex -o src/lexer.yy.cpp src/lexer.l

clean :
	rm src/parser.tab.hpp
	rm src/parser.tab.cpp
	rm src/lexer.yy.cpp
	rm src/status.o
	rm src/ast.o
	rm bin/c_codegen
