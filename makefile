CC=g++

bin/c_lexer : tokeniser/tokeniser.yy.cpp
	$(CC) tokeniser/tokeniser.yy.cpp -o bin/c_lexer

tokeniser/tokeniser.yy.cpp : tokeniser/tokeniser.l
	flex -o tokeniser/tokeniser.yy.cpp tokeniser/tokeniser.l

clean :
	rm tokeniser/tokeniser.yy.cpp
	rm bin/c_lexer
