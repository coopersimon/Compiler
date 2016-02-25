#ifndef C_AST_HPP
#define C_AST_HPP

#include <string>

// virtual base class
class ast_value
{
	public:
		virtual ~ast_value() {}
		virtual void print(int& scope) {}
};

// the root of the tree: contains a pointer to the tree itself
class ast_root
{
	private:
		ast_value* tree;
		int scope;
	public:
		ast_root(ast_value* t_in) : tree(t_in), scope(0) {}
		~ast_root();
		void print();
};

class v_int : public ast_value
{
	private:
		int value;
		bool hidden;
	public:
		v_int(int in) : value(in), hidden(false) {}
		v_int(int in, bool h_in) : value(in), hidden(h_in) {}
		void print(int& scope);
};

class v_str : public ast_value
{
	private:
		std::string value;
		bool hidden;
	public:
		v_str(std::string in) : value(std::string(in)), hidden(false) {}
		v_str(std::string in, bool h_in) : value(in), hidden(h_in) {}
		void print(int& scope);
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
		void print(int& scope);
};

class n_direct_decl : public ast_node
{
	public:
		n_direct_decl(ast_value* l_in, ast_value* r_in) : ast_node(l_in, r_in) {}
		void print(int& scope);
};

class n_param_decl : public ast_node
{
	public:
		n_param_decl(ast_value* l_in, ast_value* r_in) : ast_node(l_in, r_in) {}
		void print(int& scope);
};

class n_comp_stat : public ast_node
{
	public:
		n_comp_stat(ast_value* l_in, ast_value* r_in) : ast_node(l_in, r_in) {}
		void print(int& scope);
};

class n_init_decl : public ast_node
{
	public:
		n_init_decl(ast_value* l_in, ast_value* r_in) : ast_node(l_in, r_in) {}
		void print(int& scope);
};

class n_expression : public ast_node
{
	private:
		std::string opstr;
	public:
		n_expression(ast_value* l_in, ast_value* r_in, std::string op_in) : ast_node(l_in, r_in), opstr(std::string(op_in)) {}
};

class n_ifelse : public ast_node
{
	private:
		ast_value* else_node;
	public:
		n_ifelse(ast_value* l_in, ast_value* r_in, ast_value* e_in) : ast_node(l_in, r_in), else_node(e_in) {}
		void print(int& scope);
};

/*class n_for : public ast_node
{
	private:
		ast_value* 
	public:
		n_for(ast_value* l_in, ast_value* r_in) : ast_node(l_in, r_in) {}
		void print(int& scope);
};*/

#endif
