#ifndef C_AST_HPP
#define C_AST_HPP

#include "status.hpp"
#include <string>
#include <ostream>

// function to print tabs for scopes:
//std::string tab(int scope);

// virtual base class
class ast_value
{
	public:
		virtual ~ast_value() {}
		virtual void print(int& scope, std::ostream& out) {}
		virtual void build_status(status& stat) {}
		virtual void code_gen(status& stat, std::ostream& out) {}
};

// the root of the tree: contains a pointer to the tree itself
class ast_root
{
	private:
		ast_value* tree;
		status stat;
		int scope;
	public:
		ast_root(ast_value* t_in) : tree(t_in), stat(), scope(0) {}
		~ast_root();
		void print(std::ostream& out);
		void code_gen(std::ostream& out);
};

class v_int : public ast_value
{
	private:
		int value;
	public:
		v_int(int in) : value(in) {}
		void print(int& scope, std::ostream& out);
		void build_status(status& stat);
		void code_gen(status& stat, std::ostream& out);
};

class v_str : public ast_value
{
	private:
		std::string value;
	public:
		v_str(std::string in) : value(std::string(in)) {}
		void print(int& scope, std::ostream& out);
		void build_status(status& stat);
		void code_gen(status& stat, std::ostream& out);
};

// generic node: used for things which dont need special printing
class ast_node : public ast_value
{
	protected:
		ast_value* left;
		ast_value* right;
	public:	
		ast_node();
		ast_node(ast_value* l_in, ast_value* r_in) : left(l_in), right(r_in) {}
		~ast_node();
		void print(int& scope, std::ostream& out);
		void build_status(status& stat);
		void code_gen(status& stat, std::ostream& out);
};

class n_func_decl : public ast_node
{
	public:
		n_func_decl(ast_value* l_in, ast_value* r_in) : ast_node(l_in, r_in) {}
		void print(int& scope, std::ostream& out);
		void build_status(status& stat);
		void code_gen(status& stat, std::ostream& out);
};

class n_list : public ast_node
{
	public:
		n_list(ast_value* l_in, ast_value* r_in) : ast_node(l_in, r_in) {}
		void print(int& scope, std::ostream& out);
		//void code_gen(status& stat, std::ostream& out);
};

class n_param_decl : public ast_node
{
	public:
		n_param_decl(ast_value* l_in, ast_value* r_in) : ast_node(l_in, r_in) {}
		void print(int& scope, std::ostream& out);
		//void code_gen(status& stat, std::ostream& out);
};

class n_func_def : public ast_node // not to be confused with func_decl!
{
	public:
		n_func_def(ast_value* compstat_in) : ast_node(compstat_in, NULL) {}
		void code_gen(status& stat, std::ostream& out);
};

class n_comp_stat : public ast_node
{
	public:
		n_comp_stat(ast_value* l_in, ast_value* r_in) : ast_node(l_in, r_in) {}
		void print(int& scope, std::ostream& out);
		//void code_gen(status& stat, std::ostream& out);
};

class n_stat : public ast_node
{
	public:
		n_stat(ast_value* l_in, ast_value* r_in) : ast_node(l_in, r_in) {}
		void print(int& scope, std::ostream& out);
		//void code_gen(status& stat, std::ostream& out);
};

class n_init_decl : public ast_node
{
	public:
		n_init_decl(ast_value* l_in, ast_value* r_in) : ast_node(l_in, r_in) {}
		void print(int& scope, std::ostream& out);
		void build_status(status& stat);
		void code_gen(status& stat, std::ostream& out);
};

class n_expression : public ast_node
{
	private:
		std::string opstr;
	public:
		n_expression(ast_value* l_in, ast_value* r_in, std::string op_in) : ast_node(l_in, r_in), opstr(std::string(op_in)) {}
		void print(int& scope, std::ostream& out);
		void code_gen(status& stat, std::ostream& out);
};

class n_ifelse : public ast_node
{
	private:
		ast_value* else_node;
	public:
		n_ifelse(ast_value* l_in, ast_value* r_in, ast_value* e_in) : ast_node(l_in, r_in), else_node(e_in) {}
		~n_ifelse();
		void print(int& scope, std::ostream& out);
		//void code_gen(status& stat, std::ostream& out);
};

class n_while : public ast_node
{
	public:
		n_while(ast_value* l_in, ast_value* r_in) : ast_node(l_in, r_in) {}
		void print(int& scope, std::ostream& out);
		//void code_gen(status& stat, std::ostream& out);
};

class n_jump_stat : public ast_node
{
	private:
		std::string type;
	public:
		n_jump_stat(ast_value* exp_in, std::string type_in) : ast_node(exp_in, NULL), type(std::string(type_in)) {}
		void print(int& scope, std::ostream& out);
		void code_gen(status& stat, std::ostream& out);
};

#endif
