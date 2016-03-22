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

void v_id::print(int& scope, std::ostream& out)
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
		delete left;
	if (right != NULL)
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

n_ternary::~n_ternary()
{
	if (cond != NULL)
		delete cond;
}

void n_ternary::print(int& scope, std::ostream& out)
{
	out << "(";
	if (cond != NULL)
		cond->print(scope, out);
	out << " ? ";
	if (left != NULL)
		left->print(scope, out);
	out << " : ";
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

void n_switch::print(int& scope, std::ostream& out)
{
	out << "switch (";
	if (left != NULL)
		left->print(scope, out);
	out << ")\n";
	if (right != NULL)
		right->print(scope, out);
	return;
}

void n_case::print(int& scope, std::ostream& out)
{
	if (left != NULL)
	{
		out << "case ";
		left->print(scope, out);
	}
	else
		out << "default";
	out << ":\n";
	if (right != NULL)
		right->print(scope, out);
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
	if (type != "continue" && type != "break" && type != "return")
		out << "goto ";
	out << type;
	if (left != NULL)
	{
		out << " ";
		left->print(scope, out);
	}
	out << ";\n";
	return;
}

void n_label::print(int& scope, std::ostream& out)
{
	out << label << "label:";
	if (left != NULL)
		left->print(scope, out);
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

void n_pointer::print(int& scope, std::ostream& out)
{
	out << "*";
	if (left != NULL)
		left->print(scope, out);
	return;
}

void n_array::print(int& scope, std::ostream& out)
{
	if (left != NULL)
		left->print(scope, out);
	out << "[";
	if (right != NULL)
		right->print(scope, out);
	out << "]";
	return;
}

// pre-code gen functions
// pre code gen is for checking and counting variables

void v_int::build_status(status& stat)
{
	return;
}

void v_id::build_status(status& stat)
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
		left->build_status(stat);
		stat.count_variable();
	}
	if (right != NULL)
		right->build_status(stat);

	return;
}

void n_array::build_status(status& stat)
{
	if (left != NULL)
		left->build_status(stat);
	stat.set_var_size(size);
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
		std::cerr << "Attempted use of uninitialised variable.\n";
	}
	return;
}


void v_int::code_gen(status& stat, std::ostream& out)
{
	out << "\tli\t$t" << stat.get_register() << "," << value << "\n";
	return;
}

void v_id::code_gen(status& stat, std::ostream& out)
{
	bool param = false;
	if (stat.get_decl(param)) // if the variable is being declared
	{
		if (param)
			stat.add_parameter(value);
		else
		{
			stat.add_variable(value);
			if (stat.global_var())
			{
				stat.change_text_data("data", out);
				out << "\t.type\t" << value << ", @object\n";
				out << value << ":\n";
				out << "\t.word";
				// if variable needs to be declared to a value, here is the place to do it
				out << "\n";
			}
		}
	}
	else if (stat.get_assign_var() && !stat.get_dereference() && !stat.get_reference()) // if the variable needs to be saved
	{
		std::string location = stat.variable_location(value);
		if (location[0] == '$') // if the location is a register
			out << "\tmove\t" << location << ",$t" << stat.get_register() << "\n";
		else // if the location is on the stack or global
			out << "\tsw\t$t" << stat.get_register() << "," << location << "\n";	
	}
	else if (stat.get_reference()) // if the variable is being referenced & retrieved
	{
		std::string location = stat.variable_location(value);
		out << "\taddiu\t$t" << stat.get_register() << ",$fp," << location << "\n";
	}
	else if (stat.get_dereference()) // if deref'd variable : used for pointers
	{
		std::string location = stat.variable_location(value);

		if (location[0] == '$') // if the location is a register
			out << "\tmove\t$t" << stat.get_register() << "," << location << "\n";
		else // if the location is on the stack
			out << "\tlw\t$t" << stat.get_register() << "," << location << "($fp)\n";
	}
	else // if the variable needs to be retrieved
	{
		std::string location = stat.variable_location(value);
		if (location[0] == '$') // if the location is a register
			out << "\tmove\t";
		else // if the location is on the stack
			out << "\tlw\t";
		out << "$t" << stat.get_register() << "," << location << "\n";
	}
	return;
}

void v_type::code_gen(status& stat, std::ostream& out)
{
	stat.set_type(value);
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

void n_pointer::code_gen(status& stat, std::ostream& out)
{
	if (left != NULL)
	{
		stat.set_pointer();
		left->code_gen(stat, out);
	}
	return;
}

void n_array::code_gen(status& stat, std::ostream& out)
{
	if (left != NULL)
	{
		stat.set_var_size(size);
		left->code_gen(stat, out);
	}
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
		stat.set_decl(true);
		right->code_gen(stat, out);
		stat.set_decl(false);
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

	int stack_space = 8 + stat.size_variables();

	out << "\taddiu\t" << "$sp,$sp,-" << stack_space << "\n"; // stack grows down...
	out << "\tsw\t" << "$fp," << (stack_space - 4) << "($sp)\n"; // store the old fp at the top of the stack
	out << "\taddi\t" << "$fp,$sp," << stack_space << "\n"; // set new fp at the top of the stack frame.
	
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
		stat.set_decl(false); // let the id node know that a variable is being declared
		left->code_gen(stat, out);
		stat.set_decl(false);	
	}

	if (right != NULL) // if variable is initialised to value
	{
		stat.lock_register(out);
		stat.set_assign_expr();
		// evaluate assign expr
		right->code_gen(stat, out);
		stat.set_assign_var(); // let the id node know that a variable is being set to a value
		left->code_gen(stat, out);
		stat.set_assign_var();
		stat.unlock_register(out);
		stat.set_assign_expr();
	}

	return;
}

void n_ifelse::code_gen(status& stat, std::ostream& out)
{
	stat.lock_register(out);
	stat.set_assign_expr();
	// check expression
	left->code_gen(stat, out);
	// branch over if statement, if the expression equals zero
	std::string else_label = stat.label_gen();
	out << "\tbeqz\t$t" << stat.get_register() << "," << else_label << "\n";
	out << "\tnop\n";
	stat.unlock_register(out);
	stat.set_assign_expr();
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

void n_switch::code_gen(status& stat, std::ostream& out)
{
	stat.lock_register(out);
	stat.set_assign_expr();
	// check expression
	left->code_gen(stat, out);
	stat.set_assign_expr();
	stat.set_break_label();
	// list of cases
	right->code_gen(stat, out);
	stat.unlock_register(out);
	out << stat.get_break_label() << ":\n";
	stat.reset_labels(false);
	return;
}

void n_case::code_gen(status& stat, std::ostream& out)
{
	if (left != NULL) // case:
	{
		stat.lock_register(out);
		stat.set_assign_expr();
		int op2 = stat.get_register();
		left->code_gen(stat, out);
		stat.unlock_register(out);
		stat.set_assign_expr();
		std::string case_label = stat.label_gen();
		// if the expressions are not equal, branch over statement
		out << "\tbne\t$t" << stat.get_register() << ",$t" << op2 << "," << case_label << "\n";
		if (right != NULL)
			right->code_gen(stat, out);
		out << case_label << ":\n";
	}
	else // default:
	{
		if (right != NULL)
			right->code_gen(stat, out);
	}
	return;	
}

void n_while::code_gen(status& stat, std::ostream& out)
{
	// label signifying the start of the loop
	stat.set_continue_label();
	out << stat.get_continue_label() << ":\n";
	stat.lock_register(out);
	stat.set_assign_expr();
	// check expression
	left->code_gen(stat, out);
	stat.set_break_label();
	// exit loop if expression equals zero
	out << "\tbeqz\t$t" << stat.get_register() << "," << stat.get_break_label() << "\n";
	out << "\tnop\n";
	stat.unlock_register(out);
	stat.set_assign_expr();
	// loop statement
	right->code_gen(stat, out);
	// return to top of loop
	out << "\tb\t" << stat.get_continue_label() << "\n";
	out << "\tnop\n";
	out << stat.get_break_label() << ":\n";
	stat.reset_labels(true);
	return;
}

void n_dowhile::code_gen(status& stat, std::ostream& out)
{
	// label signifying the start of the loop
	stat.set_continue_label();
	out << stat.get_continue_label() << ":\n";
	// loop statement
	stat.set_break_label();
	left->code_gen(stat, out);
	stat.lock_register(out);
	stat.set_assign_expr();
	// check expression
	right->code_gen(stat, out);
	// do another loop if expression is non zero
	out << "\tbnez\t$t" << stat.get_register() << "," << stat.get_continue_label() << "\n";
	out << "\tnop\n";
	out << stat.get_break_label() << ":\n";
	stat.unlock_register(out);
	stat.set_assign_expr();
	stat.reset_labels(true);
	return;
}

void n_for::code_gen(status& stat, std::ostream& out)
{
	if (init != NULL) // initialising expression
		init->code_gen(stat, out);
	// start of loop: this is a lot like a while loop.
	stat.set_continue_label();
	out << stat.get_continue_label() << ":\n";
	stat.lock_register(out);
	stat.set_assign_expr();
	// check expression
	cond->code_gen(stat, out);
	stat.set_break_label();
	// exit loop if expression equals zero
	out << "\tbeqz\t$t" << stat.get_register() << "," << stat.get_break_label() << "\n";
	out << "\tnop\n";
	stat.unlock_register(out);
	stat.set_assign_expr();
	// loop statement
	left->code_gen(stat, out);
	if (right != NULL) // loop expression (something like i++)
		right->code_gen(stat, out);
	out << "\tb\t" << stat.get_continue_label() << "\n";
	out << "\tnop\n";
	out << stat.get_break_label() << ":\n";
	stat.reset_labels(true);
	return;
}

void n_expression::code_gen(status& stat, std::ostream& out)
{
	// left OP right : result_reg = t0 OP t1
	bool unlock = false;
	if (!stat.get_assign_expr())
	{
		stat.lock_register(out);
		stat.set_assign_expr();
		unlock = true;
	}
	if (opstr == "+")
	{
		if (left != NULL)
		{
			left->code_gen(stat, out);
			stat.lock_register(out);
			right->code_gen(stat, out);
			int op2 = stat.get_register();
			stat.unlock_register(out);
			out << "\tadd\t$t" << stat.get_register() << ",$t" << stat.get_register() << ",$t" << op2 << "\n";
		}
	}
	else if (opstr == "-")
	{
		if (left != NULL)
		{
			left->code_gen(stat, out);
			stat.lock_register(out);
			right->code_gen(stat, out);
			int op2 = stat.get_register();
			stat.unlock_register(out);
			out << "\tsub\t$t" << stat.get_register() << ",$t" << stat.get_register() << ",$t" << op2 << "\n";
		}
		else
		{
			stat.lock_register(out);
			right->code_gen(stat, out);
			int op2 = stat.get_register();
			stat.unlock_register(out);
			out << "\tneg\t$t" << stat.get_register() << ",$t" << op2 << "\n";
		}
	}
	else if (opstr == "*")
	{
		if (left != NULL) // if operation is left MULT right
		{
			left->code_gen(stat, out);
			stat.lock_register(out);
			right->code_gen(stat, out);
			int op2 = stat.get_register();
			stat.unlock_register(out);
			out << "\tmult\t$t" << stat.get_register() << ",$t" << op2 << "\n";
			out << "\tmflo\t$t" << stat.get_register() << "\n";
			out << "\tnop\n\tnop\n";
		}
		else // if operation is dereferencing
		{
			if (stat.get_assign_var())
				stat.lock_register(out);
			int op2 = stat.get_register();
			stat.set_dereference();
			right->code_gen(stat, out);
			stat.set_dereference();
			if (stat.get_assign_var()) // if variable needs to be saved
			{
				stat.unlock_register(out);
				out << "\tsw\t";
			}
			else // if variable needs to be retrieved
				out << "\tlw\t";
			out << "$t" << stat.get_register() << ",($t" << op2 << ")\n";

		}
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
		out << "\tnop\n\tnop\n";
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
		out << "\tnop\n\tnop\n";
	}
	else if (opstr == "&")
	{
		if (left != NULL) // if operation is left AND right
		{
			left->code_gen(stat, out);
			stat.lock_register(out);
			right->code_gen(stat, out);
			int op2 = stat.get_register();
			stat.unlock_register(out);
			out << "\tand\t$t" << stat.get_register();
			out << ",$t" << stat.get_register() << ",$t" << op2 << "\n";
		}
		else // if operation is referencing
		{
			stat.set_reference();
			right->code_gen(stat, out);
			stat.set_reference();
		}
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
		if (left != NULL) // postfix
		{
			left->code_gen(stat, out);
			int op1 = stat.get_register();
			stat.lock_register(out);
			out << "\tadd\t$t" << stat.get_register() << ",$t" << op1 << ",1\n";
			stat.set_assign_var();
			left->code_gen(stat, out);
			stat.set_assign_var();
			stat.unlock_register(out);
		}
		else if (right != NULL) // prefix
		{
			right->code_gen(stat, out);
			out << "\tadd\t$t" << stat.get_register() << ",$t" << stat.get_register() << ",1\n";
			stat.set_assign_var();
			right->code_gen(stat, out);
			stat.set_assign_var();
		}
	}
	else if (opstr == "--")
	{
		if (left != NULL) // postfix
		{
			left->code_gen(stat, out);
			int op1 = stat.get_register();
			stat.lock_register(out);
			out << "\tsub\t$t" << stat.get_register() << ",$t" << op1 << ",1\n";
			stat.set_assign_var();
			left->code_gen(stat, out);
			stat.set_assign_var();
			stat.unlock_register(out);
		}
		else if (right != NULL) // prefix
		{
			right->code_gen(stat, out);
			out << "\tsub\t$t" << stat.get_register() << ",$t" << stat.get_register() << ",1\n";
			stat.set_assign_var();
			right->code_gen(stat, out);
			stat.set_assign_var();
		}
	}
	else if (opstr == "[]")
	{
		if (stat.get_assign_var())
			stat.lock_register(out);
		// evaluate operation
		right->code_gen(stat, out);
		// shift the operation to get number of bytes for array offset
		out << "\tsll\t$t" << stat.get_register() << ",$t" << stat.get_register() << ",2\n"; // 2 for ints
		// get offset of first element
		stat.lock_register(out);
		int op2 = stat.get_register();
		stat.set_reference();
		left->code_gen(stat, out);
		stat.set_reference();
		stat.unlock_register(out);
		// add on array offset
		out << "\taddu\t$t" << stat.get_register() << ",$t" << stat.get_register() << ",$t" << op2 << "\n";
		// store or load the variable
		op2 = stat.get_register();
		if (stat.get_assign_var()) // if variable needs to be saved
		{
			stat.unlock_register(out);
			out << "\tsw\t";
		}
		else // if variable needs to be retrieved
			out << "\tlw\t";
		out << "$t" << stat.get_register() << ",($t" << op2 << ")\n";
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
		right->code_gen(stat, out);
		stat.set_assign_var();
		left->code_gen(stat, out);
		stat.set_assign_var();
	}

	if (unlock)
	{
		stat.unlock_register(out);
		stat.set_assign_expr();
	}
	return;
}

void n_ternary::code_gen(status& stat, std::ostream& out)
{
	bool unlock = false;
	if (!stat.get_assign_expr())
	{
		stat.lock_register(out);
		stat.set_assign_expr();
		unlock = true;
	}

	cond->code_gen(stat, out); // the condition
	std::string zero_label = stat.label_gen();
	out << "\tbeqz\t$t" << stat.get_register() << "," << zero_label << "\n";
	out << "\tnop\n";
	left->code_gen(stat, out); // the first expression
	std::string end_label = stat.label_gen();
	out << "\tb\t" << end_label << "\n";
	out << zero_label << ":\n";
	right->code_gen(stat, out); // the second expression
	out << end_label << ":\n";

	if (unlock)
	{
		stat.unlock_register(out);
		stat.set_assign_expr();
	}
	return;
}

void n_jump_stat::code_gen(status& stat, std::ostream& out)
{
	if (type == "continue")
	{
		out << "\tb\t" << stat.get_continue_label() << "\n";
	}
	else if (type == "break")
	{
		out << "\tb\t" << stat.get_break_label() << "\n";
	}
	else if (type == "return")
	{
		if (left != NULL)
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
	}
	else // goto
	{
		out << "\tj\tl_" << type << "\n";
	}

	return;
}

void n_label::code_gen(status& stat, std::ostream& out)
{
	out << "l_" << label << ":\n";
	if (left != NULL)
		left->code_gen(stat, out);
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




