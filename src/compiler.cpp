#include "ast.hpp"
#include "parser.tab.hpp"
#include <iostream>
#include <fstream>

ast_value* c_ast;

int main(int argc, char* argv[])
{
	yyparse();

	ast_value* ast = c_ast;
	ast_root root(ast);

	//root.print(std::cout);
	root.code_gen(std::cout);

	return 0;
}
