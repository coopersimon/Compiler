#ifndef C_AST_HPP
#define C_AST_HPP

#include "status.hpp"
#include <string>
#include <ostream>

typedef union
{
	int i;
	float f;
} fl_int;

// function to print tabs for scopes:
//std::string tab(int scope);

// virtual base class
class ast_value
{
	public:
		virtual ~ast_value() {}
		virtual void print(std::ostream& out) {}
		virtual void build_status(status& stat, std::ostream& out) {}
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
		void print(std::ostream& out);
		void build_status(status& stat, std::ostream& out);
		void code_gen(status& stat, std::ostream& out);
};

class v_id : public ast_value
{
	private:
		std::string value;
	public:
		v_id(std::string in) : value(std::string(in)) {}
		void print(std::ostream& out);
		void build_status(status& stat, std::ostream& out);
		void code_gen(status& stat, std::ostream& out);
};

class v_type : public ast_value
{
	private:
		type value;
	public:
		v_type(type in) : value(in) {}
		void print(std::ostream& out);
		void build_status(status& stat, std::ostream& out);
		void code_gen(status& stat, std::ostream& out);
};

class v_str : public ast_value
{
	private:
		std::string value;
	public:
		v_str(std::string in) : value(std::string(in)) {}
		void print(std::ostream& out);
		void build_status(status& stat, std::ostream& out);
		void code_gen(status& stat, std::ostream& out);
};

class v_float : public ast_value
{
	private:
		fl_int value;
	public:
		v_float(float in){ value.f = in; }
		void print(std::ostream& out);
		void build_status(status& stat, std::ostream& out);
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
		void print(std::ostream& out);
		void build_status(status& stat, std::ostream& out);
		void code_gen(status& stat, std::ostream& out);
};

class n_pointer : public ast_node
{
	public:
		n_pointer(ast_value* l_in) : ast_node(l_in, NULL) {}
		void print(std::ostream& out);
		void code_gen(status& stat, std::ostream& out);
};

class n_array : public ast_node
{
	private:
		int size;
	public:
		n_array(ast_value* l_in, int size_in) : ast_node(l_in, NULL), size(size_in) {}
		void print(std::ostream& out);
		void build_status(status& stat, std::ostream& out);
		void code_gen(status& stat, std::ostream& out);
};

class n_func_decl : public ast_node
{
	public:
		n_func_decl(ast_value* l_in, ast_value* r_in) : ast_node(l_in, r_in) {}
		void print(std::ostream& out);
		void build_status(status& stat, std::ostream& out);
		void code_gen(status& stat, std::ostream& out);
};

class n_list : public ast_node
{
	public:
		n_list(ast_value* l_in, ast_value* r_in) : ast_node(l_in, r_in) {}
		void print(std::ostream& out);
		//void code_gen(status& stat, std::ostream& out);
};

class n_param_decl : public ast_node
{
	public:
		n_param_decl(ast_value* l_in, ast_value* r_in) : ast_node(l_in, r_in) {}
		void print(std::ostream& out);
		void code_gen(status& stat, std::ostream& out);
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
		void print(std::ostream& out);
		void code_gen(status& stat, std::ostream& out);
};

class n_stat : public ast_node
{
	public:
		n_stat(ast_value* l_in, ast_value* r_in) : ast_node(l_in, r_in) {}
		void print(std::ostream& out);
		//void code_gen(status& stat, std::ostream& out);
};

class n_init_decl : public ast_node
{
	public:
		n_init_decl(ast_value* l_in, ast_value* r_in) : ast_node(l_in, r_in) {}
		void print(std::ostream& out);
		void build_status(status& stat, std::ostream& out);
		void code_gen(status& stat, std::ostream& out);
};

class n_expression : public ast_node
{
	private:
		std::string opstr;
	public:
		n_expression(ast_value* l_in, ast_value* r_in, std::string op_in) : ast_node(l_in, r_in), opstr(std::string(op_in)) {}
		void print(std::ostream& out);
		void code_gen(status& stat, std::ostream& out);
};

class n_ternary : public ast_node
{
	private:
		ast_value* cond;
	public:
		n_ternary(ast_value* cond_in, ast_value* true_in, ast_value* false_in) : ast_node(true_in, false_in), cond(cond_in) {}
		~n_ternary();
		void print(std::ostream& out);
		void code_gen(status& stat, std::ostream& out);
};

class n_ifelse : public ast_node
{
	private:
		ast_value* else_node;
	public:
		n_ifelse(ast_value* l_in, ast_value* r_in, ast_value* e_in) : ast_node(l_in, r_in), else_node(e_in) {}
		~n_ifelse();
		void print(std::ostream& out);
		void code_gen(status& stat, std::ostream& out);
};

class n_switch : public ast_node
{
	public:
		n_switch(ast_value* l_in, ast_value* r_in) : ast_node(l_in, r_in) {}
		void print(std::ostream& out);
		void code_gen(status& stat, std::ostream& out);
};

class n_case : public ast_node
{
	public:
		n_case(ast_value* l_in, ast_value* r_in) : ast_node(l_in, r_in) {}
		void print(std::ostream& out);
		void code_gen(status& stat, std::ostream& out);
};

class n_while : public ast_node
{
	public:
		n_while(ast_value* l_in, ast_value* r_in) : ast_node(l_in, r_in) {}
		void print(std::ostream& out);
		void code_gen(status& stat, std::ostream& out);
};

class n_dowhile : public ast_node
{
	public:
		n_dowhile(ast_value* l_in, ast_value* r_in) : ast_node(l_in, r_in) {}
		void print(std::ostream& out);
		void code_gen(status& stat, std::ostream& out);
};

class n_for : public ast_node
{
	private:
		ast_value* init;
		ast_value* cond;
	public:
		n_for(ast_value* init_expr, ast_value* cond_expr, ast_value* loop_expr, ast_value* body) : ast_node(body, loop_expr), init(init_expr), cond(cond_expr) {}
		~n_for();
		void print(std::ostream& out);
		void code_gen(status& stat, std::ostream& out);
};

class n_jump_stat : public ast_node
{
	private:
		std::string type;
	public:
		n_jump_stat(ast_value* exp_in, std::string type_in) : ast_node(exp_in, NULL), type(std::string(type_in)) {}
		void print(std::ostream& out);
		void build_status(status& stat, std::ostream& out);
		void code_gen(status& stat, std::ostream& out);
};

class n_label : public ast_node
{
	private:
		std::string label;
	public:
		n_label(std::string label_in, ast_value* stat_in) : ast_node(stat_in, NULL), label(std::string(label_in)) {}
		void print(std::ostream& out);
		void code_gen(status& stat, std::ostream& out);
};

class n_func_call : public ast_node
{
	public:
		n_func_call(ast_value* l_in, ast_value* r_in) : ast_node(l_in, r_in) {}
		void print(std::ostream& out);
		void code_gen(status& stat, std::ostream& out);
};

class n_arg_list : public n_list
{
	public:
		n_arg_list(ast_value* l_in, ast_value* r_in) : n_list(l_in, r_in) {}
		void code_gen(status& stat, std::ostream& out);
};

#endif
