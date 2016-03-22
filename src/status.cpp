#include "status.hpp"
#include <sstream>
#include <iostream>

std::string status::label_gen()
{
	std::stringstream ss;
	ss << "label_" << label_no;
	label_no++;
	return ss.str();
}

void status::add_function()
{
	current_function++;
	variable_count.push_back(0);
	return_count.push_back(0);
	return;
}

void status::reset_current_function()
{
	current_function = 0;
	return;
}

void status::add_variable(std::string var_name)
{
	scope_vars[scope].add_variable(var_name, pointer_type(current_type, pointer), var_size);
	var_size = 1;
	pointer = false;
	return;
}

void status::count_variable()
{
	variable_count[current_function] += (var_size * 4);
	var_size = 1;
	return;
}

int status::size_variables()
{
	current_function++;
	return variable_count[current_function];
}

void status::set_type(type in_type)
{
	current_type = in_type;
	return;
}

void status::set_var_size(int in)
{
	var_size = in;
	return;
}

void status::add_parameter(std::string param_name)
{
	function_params.add_variable(param_name, pointer_type(current_type, pointer));
	pointer = false;
	return;
}

void status::remove_parameters()
{
	function_params.clear();
	return;
}

std::string status::variable_location(std::string var_name)
{
	int offset = function_params.variable_offset(var_name);
	if (offset != -1) // if var_name is a parameter
	{
		if (offset < 4) // if parameter is in the arguments
		{
			std::stringstream ss;
			ss << "$a" << offset;
			return ss.str();
		}
		else // if parameter is on the stack
		{
			std::stringstream ss;
			ss << (offset - 4) << "($fp)";
			return ss.str();
		}
	}

	for (int i = scope; i >= 0; i--) // look in each scope for variable
	{
		
		offset = scope_vars[i].variable_offset(var_name);
		if (offset != -1) // if var_name is a local/global variable
		{
			if (i == 0) // if var_name is global
				return var_name;
			for (int j = 1; j < i; j++) // get scope offset
				offset -= (scope_vars[j].var_count() * 4);
			offset -= 12; // subtract base stack area
			std::stringstream ss;
			ss << offset;
			if (!pointer)
				ss << "($fp)";
			return ss.str();
		}
	}

	throw 404; // if not found
	return "error";
}

void status::name_function(std::string in)
{
	function_name = in;
	return;
}

std::string status::get_function_name()
{
	return function_name;
}

void status::set_decl(bool param)
{
	declaration = !declaration;
	param_decl = param;
	pointer = false;
	return;
}

bool status::get_decl(bool& param)
{
	param = param_decl;
	return (declaration && !pointer);
}

void status::set_assign_var()
{
	assign = !assign;
	return;
}

bool status::get_assign_var()
{
	return assign;
}

void status::set_pointer()
{
	pointer = true;
	return;
}

void status::set_reference()
{
	pointer = !pointer;
	declaration = false;
	return;
}

bool status::get_reference()
{
	return (pointer && !declaration);
}

void status::set_dereference()
{
	pointer = !pointer;
	declaration = !declaration;
	return;
}

bool status::get_dereference()
{
	return (pointer && declaration);
}

void status::lock_register(std::ostream& out)
{
	reg_no++;

	if (reg_no > 9) // if no temps are free:
	{
		out << "\taddiu\t$sp,$sp,-4\n"; // reserve some stack space for the register.
		out << "\tsw\t$t" << (reg_no % 10) << ",$sp\n"; // store register on stack.
	}
	return;
}

int status::get_register()
{
	return reg_no % 10;
}

void status::unlock_register(std::ostream& out)
{
	if (reg_no > 9) // if there are regs on the stack:
	{
		out << "\tlw\t$t" << (reg_no % 10) << ",$sp\n"; // restore register
		out << "\taddiu\t$sp,$sp,4\n"; // move stack back up.
	}

	reg_no--;
	return;
}

void status::add_return()
{
	return_count[current_function]++;
	return;
}

int status::number_returns()
{
	return return_count[current_function];
}

void status::push_arg_registers(std::ostream& out)
{
	int arg_regs = function_params.var_count();
	if (arg_regs > 4)
		arg_regs = 4;

	if (arg_regs > 0)
		out << "\taddiu\t$sp,$sp,-" << (arg_regs * 4) << "\n";
	for (int i = 0; i < arg_regs; i++)
	{
		out << "\tsw\t$a" << i << "," << (i * 4) << "($sp)\n";
	}
	return;
}

void status::pop_arg_registers(std::ostream& out)
{
	int arg_regs = function_params.var_count();
	if (arg_regs > 4)
		arg_regs = 4;
	
	for (int i = 0; i < arg_regs; i++)
	{
		out << "\tlw\t$a" << i << "," << (i * 4) << "($sp)\n";
	}

	if (arg_regs > 0)
		out << "\taddiu\t$sp,$sp," << (arg_regs * 4) << "\n";
	return;
}

int status::lock_arg_register(std::ostream& out)
{
	int reg_val = no_args;
	no_args++;
	if (reg_val > 3)
	{
		out << "\taddiu\t$sp,$sp,-4\n";
	}
	return reg_val;
}

void status::unlock_arg_registers(std::ostream& out)
{
	if (no_args > 4)
	{
		out << "\taddiu\t$sp,$sp," << ((no_args - 4) * 4) << "\n";
	}
	no_args = 0;
	return;
}

void status::new_scope()
{
	scope++;
	scope_vars.push_back(var_list());
	return;
}

void status::delete_scope()
{
	scope--;
	scope_vars.pop_back();
	return;
}

bool status::global_var()
{
	if (scope == 0)
		return true;
	else
		return false;
}

void status::set_assign_expr()
{
	assign_expr = !assign_expr;
	return;
}

bool status::get_assign_expr()
{
	return assign_expr;
}

void status::reset_labels(bool cont)
{
	if (cont)
		continue_label.pop_back();
	break_label.pop_back();
	return;
}

void status::set_continue_label()
{
	std::string label = label_gen();
	continue_label.push_back(label);
	return;
}

std::string status::get_continue_label()
{
	return continue_label[continue_label.size() - 1];
}

void status::set_break_label()
{
	std::string label = label_gen();
	break_label.push_back(label);
	return;
}

std::string status::get_break_label()
{
	return break_label[break_label.size() - 1];
}

void status::change_text_data(std::string in, std::ostream& out)
{
	if (in == "text")
	{
		if (text_data != 1)
			out << "\t.text\n";
	}
	else if (in == "data")
	{
		if (text_data != 2)
			out << "\t.data\n";
	}

	return;
}


