CC=g++

all : bin/c_parser

bin/c_parser : source/lexer.o source/parser.o
	$(CC) source/parser.o source/lexer.o -o c_parser

source/parser.o : source/parser.tab.cpp source/ast.hpp
	$(CC) -c source/parser.tab.cpp -o source/parser.o

source/parser.tab.cpp : source/parser.y
	bison -o source/parser.tab.cpp source/parser.y

source/lexer.o : source/lexer.yy.cpp source/tokens.tab.hpp
	$(CC) -c source/lexer.yy.cpp -o source/lexer.o

source/lexer.yy.cpp : source/lexer.l	
	flex -o source/lexer.yy.cpp source/lexer.l

clean :
	rm source/parser.tab.cpp
	rm source/parser.o
	rm source/lexer.yy.cpp
	rm source/lexer.o
	rm bin/c_parser
