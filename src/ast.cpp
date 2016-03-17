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
	/*if (tree != NULL)
		delete tree;*/
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
	if (left != NULL)
	{
		std::cout << "deleting left\n";
		delete left;
	}
	if (right != NULL)
	{
		std::cout << "deleting right\n";
		delete right;
	}
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
	if (else_node != NULL)
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

void n_dowhile::print(int& scope, std::ostream& out)
{
	out << "do\n";
	if (left != NULL)
		left->print(scope, out);
	out << "while (";
	if (right != NULL)
		right->print(scope, out);
	out << ")\n";
	return;
}

void n_for::print(int& scope, std::ostream& out)
{
	out << "for (";
	if (init != NULL)
		init->print(scope, out);
	out << "; ";
	if (cond != NULL)
		cond->print(scope, out);
	out << "; ";
	if (right != NULL)
		right->print(scope, out);
	out << ")\n";

	if (left != NULL)
		left->print(scope, out);
	return;
}

n_for::~n_for()
{
	if (init != NULL)
		delete init;
	if (cond != NULL)
		delete cond;
}

void n_jump_stat::print(int& scope, std::ostream& out)
{
	out << type << " ";
	if (left != NULL)
		left->print(scope, out);
	out << ";\n";
	return;
}

void n_func_call::print(int& scope, std::ostream& out)
{
	if (left != NULL)
		left->print(scope, out);
	out << "(";
	if (right != NULL)
		right->print(scope, out);
	out << ")";
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

void n_init_decl::build_status(status& stat)
{
	if (left != NULL)
	{
		stat.count_variable();
	}
	if (right != NULL)
		right->build_status(stat);

	return;
}

void n_jump_stat::build_status(status& stat)
{
	if (left != NULL)
		left->build_status(stat);
	if (type == "return")
		stat.add_return();
	return;
}

// code gen functions

void ast_root::code_gen(std::ostream& out)
{
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
	if (right != NULL) // parameters/arguments.
		right->code_gen(stat, out);
	return;
}

void n_param_decl::code_gen(status& stat, std::ostream& out)
{
	if (left != NULL)
		left->code_gen(stat, out);
	if (right != NULL)
	{
		std::stringstream id;
		int tmp;
		right->print(tmp, id);
		stat.add_parameter(id.str());
	}
	return;
}

void n_func_def::code_gen(status& stat, std::ostream& out)
{
	// starting pseudo ops
	stat.change_text_data("text", out);
	out << "\t.globl\t" << stat.get_function_name() << "\n";
	out << "\t.ent\t" << stat.get_function_name() << "\n";
	out << "\t.type\t" << stat.get_function_name() << ", @function\n";
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

	out << "\tmove\t$v0,$zero\n"; // return zero by default
	if (stat.number_returns() > 0)
		out << "r" << stat.get_function_name() << ":"; // label to branch to and return

	out << "\tlw\t" << "$fp," << (stack_space - 4) << "($sp)\n"; // restore the old fp
	out << "\taddiu\t" << "$sp,$sp," << stack_space << "\n"; // move the stack back up.

	out << "\tj\t$ra\n"; // return
	out << "\tnop\n";

	out << "\t.end\t" << stat.get_function_name() << "\n\n";

	stat.remove_parameters();
	return;
}

void n_comp_stat::code_gen(status& stat, std::ostream& out)
{
	stat.new_scope();
	if (left != NULL)
		left->code_gen(stat, out);
	if (right != NULL)
		right->code_gen(stat, out);
	stat.delete_scope();
	return;
}

void n_init_decl::code_gen(status& stat, std::ostream& out)
{
	if (left != NULL)
	{
		std::stringstream id;
		int tmp;
		left->print(tmp, id);
		stat.add_variable(id.str());
		if (stat.global_var())
		{
			std::stringstream id;
			int tmp;
			left->print(tmp, id);
			stat.change_text_data("data", out);
			out << "\t.type\t" << id.str() << ", @object\n";
			out << id.str() << ":\n";
			out << "\t.word";
		}
	}

	if (right != NULL) // if variable is initialised to value
	{
		if (stat.global_var())
		{
			std::stringstream val;
			int tmp;
			right->print(tmp, val);
			out << "\t" << val.str() << "\n";
		}
		else
		{
			stat.lock_register(out);
			right->code_gen(stat, out);
			std::stringstream id;
			int tmp;
			left->print(tmp, id);
			std::string location = stat.variable_location(id.str());
			if (location[0] == '$') // if the location is a register
				out << "\tmove\t" << location << ",$t" << stat.get_register();
			else // if the location is on the stack or global
				out << "\tsw\t$t" << stat.get_register() << "," << location;
			out << "\t# " << id.str() << "\n";
			stat.unlock_register(out);
		}
	}

	return;
}

void n_ifelse::code_gen(status& stat, std::ostream& out)
{
	stat.lock_register(out);
	// check expression
	left->code_gen(stat, out);
	// branch over if statement, if the expression equals zero
	std::string else_label = stat.label_gen();
	out << "\tbeqz\t$t" << stat.get_register() << "," << else_label << "\n";
	out << "\tnop\n";
	stat.unlock_register(out);
	// if statement
	right->code_gen(stat, out);
	if (else_node != NULL)
	{
		std::string end_label = stat.label_gen();
		// branch over else statement, if if branch was executed
		out << "\tb\t" << end_label << "\n";
		out << "\tnop\n";
		out << else_label << ":\n";
		// else statement
		else_node->code_gen(stat, out);
		out << end_label << ":\n";
	}
	else
	{
		out << else_label << ":\n";
	}	

	return;
}

void n_while::code_gen(status& stat, std::ostream& out)
{
	// label signifying the start of the loop
	std::string loop_label = stat.label_gen();
	out << loop_label << ":\n";
	stat.lock_register(out);
	// check expression
	left->code_gen(stat, out);
	std::string exit_label = stat.label_gen();
	// exit loop if expression equals zero
	out << "\tbeqz\t$t" << stat.get_register() << "," << exit_label << "\n";
	out << "\tnop\n";
	stat.unlock_register(out);
	// loop statement
	right->code_gen(stat, out);
	// return to top of loop
	out << "\tb\t" << loop_label << "\n";
	out << "\tnop\n";
	out << exit_label << ":\n";
	return;
}

void n_dowhile::code_gen(status& stat, std::ostream& out)
{
	// label signifying the start of the loop
	std::string loop_label = stat.label_gen();
	out << loop_label << ":\n";
	// loop statement
	left->code_gen(stat, out);
	stat.lock_register(out);
	// check expression
	right->code_gen(stat, out);
	// do another loop if expression is non zero
	out << "\tbnez\t$t" << stat.get_register() << "," << loop_label << "\n";
	out << "\tnop\n";
	stat.unlock_register(out);
	return;
}

void n_for::code_gen(status& stat, std::ostream& out)
{
	if (init != NULL) // initialising expression
		init->code_gen(stat, out);
	// start of loop: this is a lot like a while loop.
	std::string loop_label = stat.label_gen();
	out << loop_label << ":\n";
	stat.lock_register(out);
	// check expression
	cond->code_gen(stat, out);
	std::string exit_label = stat.label_gen();
	// exit loop if expression equals zero
	out << "\tbeqz\t$t" << stat.get_register() << "," << exit_label << "\n";
	out << "\tnop\n";
	stat.unlock_register(out);
	// loop statement
	left->code_gen(stat, out);
	if (right != NULL) // loop expression (something like i++)
		right->code_gen(stat, out);
	out << "\tb\t" << loop_label << "\n";
	out << "\tnop\n";
	out << exit_label << ":\n";
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
	else if (opstr == "*")
	{
		left->code_gen(stat, out);
		stat.lock_register(out);
		right->code_gen(stat, out);
		int op2 = stat.get_register();
		stat.unlock_register(out);
		out << "\tmult\t$t" << stat.get_register() << ",$t" << op2 << "\n";
		out << "\tmflo\t$t" << stat.get_register() << "\n";
	}
	else if (opstr == "/")
	{
		left->code_gen(stat, out);
		stat.lock_register(out);
		right->code_gen(stat, out);
		int op2 = stat.get_register();
		stat.unlock_register(out);
		out << "\tdiv\t$t" << stat.get_register() << ",$t" << op2 << "\n";
		out << "\tmflo\t$t" << stat.get_register() << "\n";
	}
	else if (opstr == "%")
	{
		left->code_gen(stat, out);
		stat.lock_register(out);
		right->code_gen(stat, out);
		int op2 = stat.get_register();
		stat.unlock_register(out);
		out << "\tdiv\t$t" << stat.get_register() << ",$t" << op2 << "\n";
		out << "\tmfhi\t$t" << stat.get_register() << "\n";
	}
	else if (opstr == "&")
	{
		left->code_gen(stat, out);
		stat.lock_register(out);
		right->code_gen(stat, out);
		int op2 = stat.get_register();
		stat.unlock_register(out);
		out << "\tand\t$t" << stat.get_register();
		out << ",$t" << stat.get_register() << ",$t" << op2 << "\n";
	}
	else if (opstr == "|")
	{
		left->code_gen(stat, out);
		stat.lock_register(out);
		right->code_gen(stat, out);
		int op2 = stat.get_register();
		stat.unlock_register(out);
		out << "\tor\t$t" << stat.get_register();
		out << ",$t" << stat.get_register() << ",$t" << op2 << "\n";
	}
	else if (opstr == "^")
	{
		left->code_gen(stat, out);
		stat.lock_register(out);
		right->code_gen(stat, out);
		int op2 = stat.get_register();
		stat.unlock_register(out);
		out << "\txor\t$t" << stat.get_register();
		out << ",$t" << stat.get_register() << ",$t" << op2 << "\n";
	}
	else if (opstr == "<<")
	{
		left->code_gen(stat, out);
		stat.lock_register(out);
		right->code_gen(stat, out);
		int op2 = stat.get_register();
		stat.unlock_register(out);
		out << "\tsllv\t$t" << stat.get_register();
		out << ",$t" << stat.get_register() << ",$t" << op2 << "\n";
	}	
	else if (opstr == ">>")
	{
		left->code_gen(stat, out);
		stat.lock_register(out);
		right->code_gen(stat, out);
		int op2 = stat.get_register();
		stat.unlock_register(out);
		out << "\tsrav\t$t" << stat.get_register();
		out << ",$t" << stat.get_register() << ",$t" << op2 << "\n";
	}
	else if (opstr == "==")
	{
		left->code_gen(stat, out);
		stat.lock_register(out);
		right->code_gen(stat, out);
		int op2 = stat.get_register();
		stat.unlock_register(out);
		out << "\tseq\t$t" << stat.get_register() << ",$t" << stat.get_register() << ",$t" << op2 << "\n";
	}
	else if (opstr == "!=")
	{
		left->code_gen(stat, out);
		stat.lock_register(out);
		right->code_gen(stat, out);
		int op2 = stat.get_register();
		stat.unlock_register(out);
		out << "\tsne\t$t" << stat.get_register() << ",$t" << stat.get_register() << ",$t" << op2 << "\n";
	}
	else if (opstr == "<")
	{
		left->code_gen(stat, out);
		stat.lock_register(out);
		right->code_gen(stat, out);
		int op2 = stat.get_register();
		stat.unlock_register(out);
		out << "\tslt\t$t" << stat.get_register() << ",$t" << stat.get_register() << ",$t" << op2 << "\n";
	}
	else if (opstr == ">")
	{
		left->code_gen(stat, out);
		stat.lock_register(out);
		right->code_gen(stat, out);
		int op2 = stat.get_register();
		stat.unlock_register(out);
		out << "\tslt\t$t" << stat.get_register() << ",$t" << op2 << ",$t" << stat.get_register() << "\n";
	}
	else if (opstr == "<=")
	{
		left->code_gen(stat, out);
		stat.lock_register(out);
		right->code_gen(stat, out);
		int op2 = stat.get_register();
		stat.unlock_register(out);
		out << "\tsge\t$t" << stat.get_register() << ",$t" << op2 << ",$t" << stat.get_register() << "\n";
	}
	else if (opstr == ">=")
	{
		left->code_gen(stat, out);
		stat.lock_register(out);
		right->code_gen(stat, out);
		int op2 = stat.get_register();
		stat.unlock_register(out);
		out << "\tsge\t$t" << stat.get_register() << ",$t" << stat.get_register() << ",$t" << op2 << "\n";
	}
	else if (opstr == "++")
	{
		int lock_needed = stat.get_register();
		if (lock_needed == -1)
			stat.lock_register(out);
		if (left != NULL) // postfix
		{
			left->code_gen(stat, out);
			int op1 = stat.get_register();
			stat.lock_register(out);
			out << "\tadd\t$t" << stat.get_register() << ",$t" << op1 << ",1\n";
			std::stringstream id;
			int tmp;
			left->print(tmp, id);
			std::string location = stat.variable_location(id.str());
			if (location[0] == '$') // if the location is a register
				out << "\tmove\t" << location << ",$t" << stat.get_register() << "\n";
			else // if the location is on the stack or global
				out << "\tsw\t$t" << stat.get_register() << "," << location << "\n";
			stat.unlock_register(out);
		}
		else if (right != NULL) // prefix
		{
			right->code_gen(stat, out);
			out << "\tadd\t$t" << stat.get_register() << ",$t" << stat.get_register() << ",1\n";
			std::stringstream id;
			int tmp;
			right->print(tmp, id);
			std::string location = stat.variable_location(id.str());
			if (location[0] == '$') // if the location is a register
				out << "\tmove\t" << location << ",$t" << stat.get_register() << "\n";
			else // if the location is on the stack or global
				out << "\tsw\t$t" << stat.get_register() << "," << location << "\n";
		}
		if (lock_needed == -1)
			stat.unlock_register(out);
	}
	else if (opstr == "--")
	{
		int lock_needed = stat.get_register();
		if (lock_needed == -1)
			stat.lock_register(out);
		if (left != NULL) // postfix
		{
			left->code_gen(stat, out);
			int op1 = stat.get_register();
			stat.lock_register(out);
			out << "\tsub\t$t" << stat.get_register() << ",$t" << op1 << ",1\n";
			std::stringstream id;
			int tmp;
			left->print(tmp, id);
			std::string location = stat.variable_location(id.str());
			if (location[0] == '$') // if the location is a register
				out << "\tmove\t" << location << ",$t" << stat.get_register() << "\n";
			else // if the location is on the stack or global
				out << "\tsw\t$t" << stat.get_register() << "," << location << "\n";
			stat.unlock_register(out);
		}
		else if (right != NULL) // prefix
		{
			right->code_gen(stat, out);
			out << "\tsub\t$t" << stat.get_register() << ",$t" << stat.get_register() << ",1\n";
				std::stringstream id;
			int tmp;
			right->print(tmp, id);
			std::string location = stat.variable_location(id.str());
			if (location[0] == '$') // if the location is a register
				out << "\tmove\t" << location << ",$t" << stat.get_register() << "\n";
			else // if the location is on the stack or global
				out << "\tsw\t$t" << stat.get_register() << "," << location << "\n";
		}
		if (lock_needed == -1)
			stat.unlock_register(out);
	}
	else if (opstr == "!")
	{
		left->code_gen(stat, out);
		out << "\tseq\t$" << stat.get_register() << ",$zero,$t" << stat.get_register();
	}
	else if (opstr == "~")
	{
		left->code_gen(stat, out);
		out << "\tnot\t$" << stat.get_register() << ",$t" << stat.get_register() << "\n";
	}
	else if (opstr == "=")
	{
		if (!stat.get_assign_expr())
		{
			stat.lock_register(out);
			stat.set_assign_expr();
		}
		right->code_gen(stat, out);
		std::stringstream id;
		int tmp;
		left->print(tmp, id);
		std::string location = stat.variable_location(id.str());
		if (location[0] == '$') // if the location is a register
			out << "\tmove\t" << location << ",$t" << stat.get_register() << "\n";
		else // if the location is on the stack or global
			out << "\tsw\t$t" << stat.get_register() << "," << location << "\n";
		if (!stat.get_assign_expr())
		{
			stat.unlock_register(out);
			stat.set_assign_expr();
		}
	}
	return;
}



void n_jump_stat::code_gen(status& stat, std::ostream& out)
{
	if (left != NULL && type == "return")
	{
		stat.lock_register(out);
		stat.set_assign_expr();
		left->code_gen(stat, out);
		out << "\tmove\t$v0,$t" << stat.get_register() << "\n";
		stat.set_assign_expr();
		stat.unlock_register(out);
		out << "\tb\tr" << stat.get_function_name() << "\n";
		out << "\tnop\n";
	}

	return;
}

void n_func_call::code_gen(status& stat, std::ostream& out)
{
	// first, save the current return address in preallocated space.
	out << "\tsw\t$ra,-8($fp)\n";
	// next, push argument registers in use on the stack.
	stat.push_arg_registers(out);
	// next, load arguments into registers/stack.
	right->code_gen(stat, out);
	// next, call the function
	std::stringstream id;
	int tmp;
	left->print(tmp, id);
	out << "\t.option pic0\n"; // pic = position independent code
	out << "\tjal\t" << id.str() << "\n";
	out << "\tnop\n";
	out << "\t.option pic2\n"; // would I be honest if I said I knew what these meant? no.
	// store return value in preallocated register: 
	/***ASSUMING INT RETURN!!!!****/
	if (stat.get_register() >= 0)
		out << "\tmove\t$t" << stat.get_register() << ",$v0\n";
	// next, pop arguments 4+ off the stack.
	stat.unlock_arg_registers(out);
	// next, pop argument registers back off the stack.
	stat.pop_arg_registers(out);
	// finally, reload return address.
	out << "\tlw\t$ra,-8($fp)\n";
	return;
}

void n_arg_list::code_gen(status& stat, std::ostream& out)
{
	if (left != NULL)
		left->code_gen(stat, out);

	stat.lock_register(out);
	right->code_gen(stat, out);
	int arg_reg = stat.lock_arg_register(out);
	if (arg_reg < 4)
		out << "\tmove\t$a" << arg_reg << ",$t" << stat.get_register() << "\n";
	else
		out << "\tsw\t$t" << stat.get_register() << ",($sp)\n";
	stat.unlock_register(out);
	return;
}




