#include "ast.hpp"
#include <typeinfo>

std::string tab(int scope)
{
	std::string out = "";
	for (int i = 0; i < scope; i++)
		out += "\t";
	return out;
}

ast_root::~ast_root()
{
	delete tree;
}

void ast_root::print(std::ostream& out)
{
	tree->print(scope, out);
	return;
}

void v_int::print(int& scope, std::ostream& out)
{
	out << value;
	return;
}

void v_str::print(int& scope, std::ostream& out)
{
	out << value;
	return;
}

ast_node::ast_node()
{
	left = NULL;
	right = NULL;
}

ast_node::~ast_node()
{
	delete left;
	delete right;
}

void ast_node::print(int& scope, std::ostream& out)
{
	if (left != NULL)
		left->print(scope, out);
	if (right != NULL)
		right->print(scope, out);
	return;
}

void n_func_decl::print(int& scope, std::ostream& out)
{
	out << " ";
	if (left != NULL)
		left->print(scope, out);

	out << " (";
	if (right != NULL)
		right->print(scope, out);

	out << ")";
	return;
}

void n_list::print(int& scope, std::ostream& out)
{
	if (left != NULL)
		left->print(scope, out);
	if (right != NULL)
	{
		out << ", ";
		right->print(scope, out);
	}
	return;
}

void n_param_decl::print(int& scope, std::ostream& out)
{
	if (left != NULL)
		left->print(scope, out);
	out << " ";
	if (right != NULL)
		right->print(scope, out);
	return;
}

void n_comp_stat::print(int& scope, std::ostream& out)
{
	scope++;
	out << "{\n";
	if (left != NULL)
		left->print(scope, out);
	if (right != NULL)
		right->print(scope, out);
	out << "}";
	scope--;
	return;
}

void n_stat::print(int& scope, std::ostream& out)
{
	if (left != NULL)
		left->print(scope, out);
	if (right != NULL)
	{
		out << " ";
		right->print(scope, out);
	}
	out << ";\n";
	return;
}

void n_init_decl::print(int& scope, std::ostream& out)
{
	if (left != NULL)
		left->print(scope, out);
	if (right != NULL)
	{
		out << "=";
		right->print(scope, out);
	}
	return;
}

void n_expression::print(int& scope, std::ostream& out)
{
	out << "(";
	if (left != NULL)
		left->print(scope, out);
	out << opstr;
	if (right != NULL)
		right->print(scope, out);
	out << ")";
	return;
}

n_ifelse::~n_ifelse()
{
	delete else_node;
}

void n_ifelse::print(int& scope, std::ostream& out)
{
	out << "if (";
	if (left != NULL)
		left->print(scope, out);
	out << ")\n";
	if (right != NULL)
		right->print(scope, out);
	if (else_node != NULL)
	{
		out << "else\n";
		else_node->print(scope, out);
	}
	return;
}

void n_while::print(int& scope, std::ostream& out)
{
	out << "while (";
	if (left != NULL)
		left->print(scope, out);
	out << ")\n";
	if (right != NULL)
		right->print(scope, out);
	return;
}





