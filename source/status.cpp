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
	function_params.clear();
	variable_count.push_back(0);
	return;
}

void status::reset_current_function()
{
	current_function = 0;
	return;
}

void status::add_variable(std::string var_name)
{
	scope_vars[scope].add_variable(var_name);
	return;
}

int status::number_variables()
{
	current_function++;
	return variable_count[current_function];
}

void status::add_parameter(std::string param_name)
{
	function_params.add_variable(param_name);
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

	int i = scope;
	for (; i >= 0; i--) // look in each scope for variable
	{
		offset = scope_vars[i].variable_offset(var_name);
		if (offset != -1) // if var_name is a local variable
		{
			for (int j = 1; j < i; j++) // get scope offset
				offset -= (scope_vars[j].var_count() * 4);
			offset -= 12; // subtract base stack area
			std::stringstream ss;
			ss << offset << "($fp)";
			return ss.str();
		}
	}

	// if scope == 0: get from .data
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

void status::count_variable()
{
	variable_count[current_function]++;
	return;
}

void status::new_scope()
{
	scope++;
	scope_vars.push_back(variables());
	return;
}

void status::delete_scope()
{
	scope--;
	scope_vars.pop_back();
	return;
}

void status::set_jump_expr()
{
	if (jump_expr)
		jump_expr = false;
	else
		jump_expr = true;
	return;
}


bool status::get_jump_expr()
{
	return jump_expr;
}

void variables::add_variable(std::string var_name)
{
	vars.push_back(std::string(var_name));
	return;
}

int variables::variable_offset(std::string var_name)
{
	for (int i = 0; i < vars.size(); i++)
	{
		if (vars[i] == var_name)
			return -(i*4);
	}
	
	return -1;
}

int variables::var_count()
{
	return vars.size();
}

int parameters::variable_offset(std::string var_name)
{
	for (int i = 0; i < vars.size(); i++)
	{
		if (vars[i] == var_name && i < 4)
			return i;
		if (vars[i] == var_name && i >= 4)
			return (vars.size() - i) * 4;
	}
	
	return -1;
}

void parameters::clear()
{
	vars.clear();
	return;
}


/*void status::dump_vars()
{
	for (int i =0; i < function_vars.size(); i++)
	{
		std::cout << i << std::endl;
		function_vars[i].dump_vars();
	}
	return;
}

void function::dump_vars()
{
	for (int i = 0; i < variables.size(); i++)
	{
		std::cout << variables[i] << std::endl;
	}
	return;
}*/





