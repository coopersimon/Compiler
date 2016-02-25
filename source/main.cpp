#include "ast.hpp"
#include "parser.tab.hpp"

ast_value* c_ast;

int main()
{
	yyparse();

	ast_value* ast = c_ast;

	ast_root root(ast);

	root.print();

	return 0;
}
