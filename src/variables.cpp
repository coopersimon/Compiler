#include "variables.hpp"

type pointer_type(type input, bool ptr)
{
	if (ptr)
	{
		if (input == char_s || input == char_u)
			return char_p;
		else if (input == short_s || input == short_u)
			return short_p;
		else if (input == long_s || input == long_u)
			return long_p;
		else if (input == float_t)
			return float_p;
		else
			return input;
	}
	else
		return input;
}

std::string variable::name()
{
	return var_name;
}

int variable::var_size()
{
	return elements*4;
}

void var_list::add_variable(std::string var_name, type var_type)
{
	vars.push_back(variable(var_name, var_type));
	return;
}

void var_list::add_variable(std::string var_name, type var_type, int var_size)
{
	vars.push_back(variable(var_name, var_type, var_size));
	return;
}

int var_list::variable_offset(std::string var_name)
{
	int offset_count = 0;
	for (int i = 0; i < vars.size(); i++)
	{
		if (vars[i].name() == var_name)
			return -offset_count;
		offset_count += vars[i].var_size();
	}
	
	return -1;
}

int var_list::var_count()
{
	return vars.size();
}

void var_list::clear()
{
	vars.clear();
	return;
}

int parameter_list::variable_offset(std::string var_name)
{
	for (int i = 0; i < vars.size(); i++)
	{
		if (vars[i].name() == var_name && i < 4)
			return i;
		if (vars[i].name() == var_name && i >= 4)
			return (vars.size() - i) * 4;
	}
	
	return -1;
}

