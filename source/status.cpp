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
	current_variable = 0;
	current_function++;
	std::map<std::string, int> new_function;
	function.push_back(new_function);
	return;
}

void status::reset_current_function()
{
	current_function = 1;
	return;
}

void status::add_variable(std::string var_name)
{
	current_variable++;
	(function[current_function])[var_name] = (-4 - (4*current_variable));
	return;
}

int status::variable_offset(std::string var_name)
{
	if (function[current_function].count(var_name) > 0)
		return (function[current_function])[var_name]; // return offset if variable exists
	else
		return 0; // return 0 otherwise
}

int status::number_variables()
{
	int function_variables = function[current_function].size();
	current_function++;
	return function_variables;
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

bool status::lock_register()
{
	if (reg_no > 7)
		return false;
	else
	{
		reg_no++;
		return true;
	}
}


int status::get_register()
{
	return reg_no;
}

void status::unlock_register()
{
	if (reg_no > 0)
		reg_no--;

	return;
}







