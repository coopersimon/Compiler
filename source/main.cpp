#include "ast.hpp"
#include "parser.tab.hpp"
#include <iostream>

ast_value* c_ast;

int main()
{
	yyparse();

	ast_value* ast = c_ast;

	ast_root root(ast);

	root.print(std::cout);

	return 0;
}
