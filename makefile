CC=g++ -g

all : bin/c_codegen

bin/c_codegen : src/parser.tab.cpp src/lexer.yy.cpp src/ast.cpp src/parser.tab.hpp src/ast.hpp src/status.hpp src/status.cpp src/compiler.cpp
	$(CC) src/parser.tab.cpp src/lexer.yy.cpp src/ast.cpp src/status.cpp src/compiler.cpp -o bin/c_codegen

src/parser.tab.cpp src/parser.tab.hpp : src/parser.y src/ast.hpp
	bison -d src/parser.y -o src/parser.tab.cpp

src/lexer.yy.cpp : src/lexer.l src/ast.hpp src/parser.tab.hpp
	flex -o src/lexer.yy.cpp src/lexer.l

clean :
	rm src/parser.tab.hpp
	rm src/parser.tab.cpp
	rm src/lexer.yy.cpp
	rm bin/c_codegen
