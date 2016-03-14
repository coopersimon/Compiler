#include "status.hpp"
#include <sstream>

std::string status::label_gen(std::string in)
{
	std::stringstream ss;
	ss << in << "_label_" << label_no;
	label_no++;
	return ss.str();
}

void status::add_function()
{
	current_function++;
	function_vars.push_back(function());
	function_params.push_back(parameters());
	return;
}

void status::reset_current_function()
{
	current_function = 0;
	return;
}

void status::add_variable(std::string var_name)
{
	function_vars[current_function].add_variable(var_name);
	return;
}

std::string status::variable_location(std::string var_name)
{
	int offset = function_vars[current_function].variable_offset(var_name);
	if (offset != -1) // if var_name is a local variable
	{
		std::stringstream ss;
		ss << offset << "($fp)";
		return ss.str();
	}
	
	offset = function_params[current_function].variable_offset(var_name);
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

	throw 404; // if not found
	return "error";
}

int status::number_variables()
{
	current_function++;
	int function_variables = function_vars[current_function].var_count();
	return function_variables;
}

void status::add_parameter(std::string param_name)
{
	function_params[current_function].add_variable(param_name);
	return;
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
	if (reg_no < 9) // if a temp. register is free, use it.
	{
		reg_no++;
	}
	else // if no temps are free:
	{
		no_temps++;
		out << "\taddiu\t$sp,$sp,-4\n"; // reserve some stack space for the register.
		out << "\tsw\t$t9,$sp\n"; // store register on stack.
	}
	return;
}


int status::get_register()
{
	return reg_no;
}

void status::unlock_register(std::ostream& out)
{
	if (no_temps == 0)
	{
		reg_no--;
	}
	else
	{
		out << "\tlw\t$t9,$sp\n"; // restore register
		out << "\taddiu\t$sp,$sp,4\n"; // move stack back up.
		no_temps--;
	}

	return;
}

void status::push_arg_registers(std::ostream& out)
{
	int arg_regs = function_params[current_function].var_count();
	if (arg_regs > 3)
		arg_regs = 3;

	out << "\taddiu\t$sp,$sp,-" << (arg_regs * 4) << "\n";
	for (int i = 0; i < arg_regs; i++)
	{
		out << "\tsw\t$a" << i << "," << (i * 4) << "($sp)\n";
	}
	return;
}

void status::pop_arg_registers(std::ostream& out)
{
	int arg_regs = function_params[current_function].var_count();
	if (arg_regs > 3)
		arg_regs = 3;
	
	for (int i = 0; i < arg_regs; i++)
	{
		out << "\tlw\t$a" << i << "," << (i * 4) << "($sp)\n";
	}
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

void function::add_variable(std::string var_name)
{
	variables.push_back(std::string(var_name));
	return;
}

int function::variable_offset(std::string var_name)
{
	for (int i = 0; i < variables.size(); i++)
	{
		if (variables[i] == var_name)
			return (-12 -(i*4));
	}
	
	return -1;
}

int function::var_count()
{
	return variables.size();
}

int parameters::variable_offset(std::string var_name)
{
	for (int i = 0; i < variables.size(); i++)
	{
		if (variables[i] == var_name && i < 4)
			return i;
		if (variables[i] == var_name && i >= 4)
			return (variables.size() - i) * 4;
	}
	
	return -1;
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





