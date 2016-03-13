#include "ast.hpp"
#include <sstream>
#include <iostream>
/*std::string tab(int scope)
{
	std::string out = "";
	for (int i = 0; i < scope; i++)
		out += "\t";
	return out;
}*/

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

void n_jump_stat::print(int& scope, std::ostream& out)
{
	out << type << " ";
	if (left != NULL)
		left->print(scope, out);
	out << ";\n";
	return;
}

// pre-code gen functions
// pre code gen is for checking and counting variables

void v_int::build_status(status& stat)
{
	return;
}

void v_str::build_status(status& stat)
{
	return;
}

void ast_node::build_status(status& stat)
{
	if (left != NULL)
		left->build_status(stat);
	if (right != NULL)
		right->build_status(stat);
	return;
}

void n_func_decl::build_status(status& stat)
{
	stat.add_function();
	if (left != NULL)
		left->build_status(stat);
	if (right != NULL)
		right->build_status(stat);
	return;
}

/*void n_func_def::build_status(status& stat)
{
	
}*/

void n_param_decl::build_status(status& stat)
{
	if (left != NULL)
		left->build_status(stat);
	if (right != NULL)
	{
		std::stringstream id;
		int tmp;
		right->print(tmp, id);
		stat.add_parameter(id.str());
	}

	return;
}

void n_init_decl::build_status(status& stat)
{
	if (left != NULL)
	{
		std::stringstream id;
		int tmp;
		left->print(tmp, id);
		stat.add_variable(id.str());
	}
	if (right != NULL)
		right->build_status(stat);

	return;
}

// code gen functions

void ast_root::code_gen(std::ostream& out)
{
	out << "\t.text\n"; // init
	try
	{
		tree->build_status(stat);
		stat.reset_current_function();
		tree->code_gen(stat, out);
	}
	catch (int e)
	{
		out << "Attempted use of uninitialised variable.\n";
	}
	return;
}


void v_int::code_gen(status& stat, std::ostream& out)
{
	out << "\tli\t$t" << stat.get_register() << "," << value << "\n";
	return;
}

void v_str::code_gen(status& stat, std::ostream& out)
{
	std::string location = stat.variable_location(value);
	if (location[0] == '$') // if the location is a register
		out << "\tmove\t";
	else // if the location is on the stack
		out << "\tlw\t";

	out << "$t" << stat.get_register() << "," << location << "\n";
	return;
}

void v_type::code_gen(status& stat, std::ostream& out)
{
	return;
}

void ast_node::code_gen(status& stat, std::ostream& out)
{
	if (left != NULL)
		left->code_gen(stat, out);
	if (right != NULL)
		right->code_gen(stat, out);
	return;
}

void n_func_decl::code_gen(status& stat, std::ostream& out)
{
	if (left != NULL) // get name of function.
	{
		std::stringstream id;
		int tmp;
		left->print(tmp, id);
		stat.name_function(id.str());
	}
	//if (right != NULL) // parameters/arguments. I'll deal with this later...
	//	right->code_gen(stat, out);
}

void n_func_def::code_gen(status& stat, std::ostream& out)
{
	// starting pseudo ops
	out << "\t.globl\t" << stat.get_function_name();
	out << "\n\t.ent\t" << stat.get_function_name();
	out << "\n";
	out << stat.get_function_name() << ":\n";
	
	// dealing with the stack and frame:
	// status contains the function number and number of variables in the function.
	// function 0 is global, main will probably be function 1 (not really relevant here)
	// we need 8 + (vars*4) space on the stack. All variables assigned 4 bytes for simplicity.

	int stack_space = 8;
	int variables = stat.number_variables();
	variables += (variables & 1); // stack must be a multiple of 8
	stack_space += (variables * 4);

	out << "\taddiu\t" << "$sp,$sp,-" << stack_space << "\n"; // stack grows down...
	out << "\tsw\t" << "$fp," << (stack_space - 4) << "($sp)\n"; // store the old fp at the top of the stack
	out << "\tadd\t" << "$fp,$sp," << stack_space << "\n"; // set new fp at the top of the stack frame.
	
	if (left != NULL)
		left->code_gen(stat, out); // the function body.

	out << "\tlw\t" << "$fp," << (stack_space - 4) << "($sp)\n"; // restore the old fp
	out << "\taddiu\t" << "$sp,$sp," << stack_space << "\n"; // move the stack back up.

	out << "\tj\t" << "$ra\n"; // return
	out << "\tnop\n";

	out << "\t.end\t" << stat.get_function_name() << "\n";

	return;
}

void n_init_decl::code_gen(status& stat, std::ostream& out)
{
	if (right != NULL) // if variable is initialised to value
	{
		stat.lock_register(out);
		right->code_gen(stat, out);
		std::stringstream id;
		int tmp;
		left->print(tmp, id);
		out << "\tsw\t$t" << stat.get_register() << "," << stat.variable_location(id.str());
		out << "\t# " << id.str() << "\n";
		stat.unlock_register(out);
	}

	return;
}

void n_expression::code_gen(status& stat, std::ostream& out)
{
	// left OP right : result_reg = t0 OP t1
	if (opstr == "+")
	{
		left->code_gen(stat, out);
		stat.lock_register(out);
		right->code_gen(stat, out);
		int op2 = stat.get_register();
		stat.unlock_register(out);
		out << "\tadd\t$t" << stat.get_register();
		out << ",$t" << stat.get_register() << ",$t" << op2 << "\n";
	}
	else if (opstr == "-")
	{
		left->code_gen(stat, out);
		stat.lock_register(out);
		right->code_gen(stat, out);
		int op2 = stat.get_register();
		stat.unlock_register(out);
		out << "\tsub\t$t" << stat.get_register();
		out << ",$t" << stat.get_register() << ",$t" << op2 << "\n";
	}
	else if (opstr == "=")
	{
		if (!stat.get_jump_expr())
			stat.lock_register(out);
		right->code_gen(stat, out);
		std::stringstream id;
		int tmp;
		left->print(tmp, id);
		std::string location = stat.variable_location(id.str());
		if (location[0] == '$') // if the location is a register
			out << "\tmove\t" << location << ",$t" << stat.get_register() << "\n";
		else // if the location is on the stack
			out << "\tsw\t$t" << stat.get_register() << "," << location << "\n";
		if (!stat.get_jump_expr())
			stat.unlock_register(out);
	}
	

	return;
}

void n_jump_stat::code_gen(status& stat, std::ostream& out)
{
	if (left != NULL)
	{
		stat.lock_register(out);
		stat.set_jump_expr();
		left->code_gen(stat, out);
		out << "\tmove\t$v0,$t" << stat.get_register() << "\n";
		stat.set_jump_expr();
		stat.unlock_register(out);
	}

	return;
}

