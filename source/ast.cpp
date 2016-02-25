#include "ast.hpp"
#include <iostream>
#include <typeinfo>

ast_root::~ast_root()
{
	delete tree;
}

void ast_root::print()
{
	tree->print(scope);
	return;
}

void v_int::print(int& scope)
{
	if (!hidden)
		std::cout << value;
	return;
}

void v_str::print(int& scope)
{
	if (!hidden)
		std::cout << value;
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

void ast_node::print(int& scope)
{
	if (left != NULL)
		left->print(scope);
	if (right != NULL)
		right->print(scope);
	return;
}

void n_direct_decl::print(int& scope)
{
	if (left != NULL)
	{
		for(int i = 0; i < scope; i++)
			std::cout << "    ";
		std::cout << "FUNCTION : ";
		left->print(scope);
		std::cout << std::endl;
	}
	if (right != NULL)
		right->print(scope);
	return;
}

void n_param_decl::print(int& scope)
{
	if (left != NULL)
		left->print(scope);
	if (right != NULL)
	{
		for(int i = 0; i < scope; i++)
			std::cout << "    ";
		std::cout << "    PARAMETER : ";
		right->print(scope);
		std::cout << std::endl;
	}
	return;
}

void n_comp_stat::print(int& scope)
{
	for(int i = 0; i < scope; i++)
		std::cout << "    ";
	std::cout << "SCOPE" << std::endl;
	scope++;
	if (left != NULL)
		left->print(scope);
	if (right != NULL)
		right->print(scope);
	scope--;
	return;
}

void n_init_decl::print(int& scope)
{
	if (left != NULL)
	{
		for(int i = 0; i < scope; i++)
			std::cout << "    ";
		std::cout << "VARIABLE : ";
		left->print(scope);
		std::cout << std::endl;
	}
	if (right!= NULL)
		right->print(scope);
}

void n_ifelse::print(int& scope)
{
	if (left != NULL)
		left->print(scope);
	if (right != NULL)
		right->print(scope);
	if (else_node != NULL)
		else_node->print(scope);
	return;
}

/*void n_for::print(int& scope)
{
	if (left != NULL)
		left->print(scope);
	if (right != NULL)
		right->print(scope);
}*/





