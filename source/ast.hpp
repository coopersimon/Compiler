#ifndef AST_HPP
#define AST_HPP

#include <string>

class ast_node
{
	public:
		ast_node *left;
		ast_node *right;
		virtual void print() const=0;

};

class n_function : public ast_node
{
	public:
		void print() const;
};

class n_declar : public ast_node
{
	public:
		string type;
		string id;
};

class n_compstat : public ast_node
{
	public:
		void print() const;
};

class n_expression : public ast_node
{
	public:
		string oper;
};


#endif
