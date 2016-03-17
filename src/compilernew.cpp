#include "ast.hpp"
#include "parser.tab.hpp"
#include <iostream>
#include <fstream>

ast_value* c_ast;

int main(int argc, char* argv[])
{
	bool gen = true;
	yyparse();

	ast_value* ast = c_ast;
	ast_root root(ast);

	for (int i = 1; i < argc; i++)
	{
		if (argv[i] == "-p")
		{
			std::ofstream print_out;
			print_out.open("print_out.c");
			root.print(print_out);
			print_out.close();
		}
		else if (argv[i] == "-n")
			gen = false;
	}

	if (gen)
		root.code_gen(std::cout);


	return 0;
}
