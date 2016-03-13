#include "ast.hpp"
#include "parser.tab.hpp"
#include <iostream>
#include <sstream>

ast_value* c_ast;

int main()
{
	yyparse();

	ast_value* ast = c_ast;
	ast_root root(ast);

	std::stringstream ss;	
	//root.print(ss);
	root.code_gen(ss);

	std::cout << ss.str();

	return 0;
}
