CC=g++

all : bin/compiler

bin/compiler : source/parser.tab.cpp source/lexer.yy.cpp source/ast.cpp source/parser.tab.hpp source/ast.hpp source/status.hpp source/status.cpp source/compiler.cpp
	$(CC) source/parser.tab.cpp source/lexer.yy.cpp source/ast.cpp source/status.cpp source/compiler.cpp -o bin/compiler

source/parser.tab.cpp source/parser.tab.hpp : source/parser.y source/ast.hpp
	bison -d source/parser.y -o source/parser.tab.cpp

source/lexer.yy.cpp : source/lexer.l source/ast.hpp source/parser.tab.hpp
	flex -o source/lexer.yy.cpp source/lexer.l

clean :
	rm source/parser.tab.hpp
	rm source/parser.tab.cpp
	rm source/lexer.yy.cpp
	rm bin/compiler
