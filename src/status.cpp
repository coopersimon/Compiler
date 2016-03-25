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

std::string status::data_label_gen()
{
	std::stringstream ss;
	ss << "dlabel_" << data_label_no;
	data_label_no++;
	return ss.str();
}

void status::add_function()
{
	current_function++;
	variable_count.push_back(0);
	return_count.push_back(0);
	return;
}

void status::pre_code_gen()
{
	current_function = 0;
	data_label_no = 0;
	return;
}

void status::add_variable(std::string var_name)
{
	if (var_size == 0)
		scope_vars[scope].add_variable(var_name, pointer_type(current_type), 1);
	else
		scope_vars[scope].add_variable(var_name, current_type, var_size);
	var_size = 1;
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

// aka the mega function: this deals with everything to do with variables!
// the reason why it is here is because almost all the data is stored in the status class
void status::load_store(std::string var_name, std::ostream& out)
{
	if (declaration && !pointer) // if variable is being declared
	{
		if (param_decl) // if parameter
		{
			add_parameter(var_name);
		}
		else
		{
			add_variable(var_name);
			if (scope == 0) // global
			{
				change_text_data("data", out);
				out << "\t.type\t" << var_name << ", @object\n";
				out << var_name << ":\n";
				out << "\t.word";
			}
		}
		return;
	}
	// otherwise the variable exists and is either being loaded or stored.
	// get the location of the variable.
	std::string location = variable_location(var_name); // location: either on the stack or a register
	std::string opcode = variable_opcode(var_name); // get the relevant opcode (store or load)

	bool ptr = false;
	if (array_type == long_p || array_type == char_p || array_type == short_p || array_type == float_p)
		ptr = true;
	
	if (assign && !pointer && (opcode == "move")) // if the variable needs to be moved
	{
		out << "\tmove\t" << location << ",$t" << get_register() << "\n";
	}
	else if ((pointer && !declaration && !ptr) || (no_args > 0) && variable_array(var_name)) // i.e. variable is being referenced & retrieved
	{
		// if the variable is being referenced OR an array
		out << "\taddiu\t$t" << get_register() << ",$fp," << location << "\n";
	}
	else // variable is either being dereferenced or retrieved OR a pointer to array OR is saved to stack
	{
		out << "\t" << opcode << "\t";
		if (float_type)
			out << "$f" << get_f_register();
		else
			out << "$t" << get_register();
		out << "," << location << "\n";
	}

	return;
}

std::string status::pointer_opcode()
{
	if (assign) // when storing (i.e. assignment)
	{
		if (array_type == long_s || array_type == long_u || array_type == char_p || array_type == short_p || array_type == long_p || array_type == float_p)
			return "sw";
		else if (array_type == short_s || array_type == short_u)
			return "sh";
		else if (array_type == char_s || array_type == char_u)
			return "sb";
	}
	else // when loading
	{
		if (array_type == long_s || array_type == long_u || array_type == char_p || array_type == short_p || array_type == long_p || array_type == float_p)
			return "lw";
		else if (array_type == short_s)
			return "lh";
		else if (array_type == short_u)
			return "lhu";
		else if (array_type == char_s)
			return "lb";
		else if (array_type == char_u)
			return "lbu";
	}
}

void status::add_parameter(std::string param_name)
{
	if (var_size == 0)
	{
		var_size = 1;
		function_params.add_variable(param_name, pointer_type(current_type));
	}
	else
		function_params.add_variable(param_name, current_type);
	
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
			bool array_arg = (no_args > 0) && variable_array(var_name);
			if (!(pointer && !declaration) && !array_arg) // if variable is being referenced we don't need ($fp) part
				ss << "($fp)";
			return ss.str();
		}
	}

	throw 404; // if not found
	return "error";
}

std::string status::variable_opcode(std::string var_name)
{
	type var_type = function_params.variable_type(var_name);
	if (var_type != void_t) // if var_name is a parameter
	{
		array_type = var_type;
		if (function_params.variable_offset(var_name) < 4) // if parameter is in the arguments
		{
			return "move";
		}
	}
	else // var_name must be on the stack or global
	{
		for (int i = scope; i >= 0; i--)
		{
			var_type = scope_vars[i].variable_type(var_name);
			if (var_type != void_t)
				break;
		}
	}

	array_type = var_type;
	if (assign) // when storing (i.e. assignment)
	{
		if (var_type == long_s || var_type == long_u || var_type == char_p || var_type == short_p || var_type == long_p || var_type == float_p)
			return "sw";
		else if (var_type == short_s || var_type == short_u)
			return "sh";
		else if (var_type == char_s || var_type == char_u)
			return "sb";
		else if (var_type == float_t)
			return "swc1";
	}
	else // when loading
	{
		if (var_type == long_s || var_type == long_u || var_type == char_p || var_type == short_p || var_type == long_p || var_type == float_p)
			return "lw";
		else if (var_type == short_s)
			return "lh";
		else if (var_type == short_u)
			return "lhu";
		else if (var_type == char_s)
			return "lb";
		else if (var_type == char_u)
			return "lbu";
		else if (var_type == float_t)
			return "lwc1";
	}
	
	// pretty much impossible to get to this point.
	throw 403;
	return "error";
}

bool status::variable_array(std::string var_name)
{
	int size = function_params.variable_size(var_name);
	if (size != 0)
	{
		if (size > 4)
			return true;
		else
			return false;
	}
	
	for (int i = scope; i >= 0; i--)
	{
		size = scope_vars[i].variable_size(var_name);
		if (size != 0)
		{
			if (size > 4)
				return true;
			else
				return false;
		}
	}
	return false;
}

void status::set_float()
{
	float_type = true;
	return;
}

void status::set_float(std::string var_name)
{
	type var_type = function_params.variable_type(var_name);
	if (var_type == void_t)
	{
		for (int i = scope; i >= 0; i--)
		{
			var_type = scope_vars[i].variable_type(var_name);
			if (var_type != void_t)
				break;
		}
	}
	if (var_type == float_t)
		float_type = true;
	return;
}

bool status::is_float()
{
	if (float_type)
	{
		float_type = false;
		return true;
	}
	else
		return false;
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
	f_reg_no += 2;

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

	f_reg_no -= 2;
	reg_no--;
	return;
}

/*void status::lock_f_register(std::ostream& out)
{
	f_reg_no++;

	if (f_reg_no > 31) // if no temps are free:
	{
		out << "\taddiu\t$sp,$sp,-4\n"; // reserve some stack space for the register.
		out << "\tsw\t$t" << (reg_no % 10) << ",$sp\n"; // store register on stack.
	}
	return;
}*/

int status::get_f_register()
{
	return f_reg_no % 32;
}

/*void status::unlock_f_register(std::ostream& out)
{
	if (reg_no > 32) // if there are regs on the stack:
	{
		out << "\tlw\t$t" << (reg_no % 10) << ",$sp\n"; // restore register
		out << "\taddiu\t$sp,$sp,4\n"; // move stack back up.
	}

	f_reg_no--;
	return;
}*/

void status::add_return()
{
	return_count[current_function]++;
	return;
}

int status::number_returns()
{
	return return_count[current_function];
}

void status::push_registers(std::ostream& out)
{
	int arg_regs = function_params.var_count();
	if (arg_regs > 4)
		arg_regs = 4;

	// one reg has been allocated for return so doesn't need to be saved.
	int temp_regs = reg_no;
	if (temp_regs == -1)
		temp_regs = 0;

	if (arg_regs + temp_regs > 0)
		out << "\taddiu\t$sp,$sp,-" << ((arg_regs + temp_regs) * 4) << "\n";
	for (int i = 0; i < arg_regs; i++)
	{
		out << "\tsw\t$a" << i << "," << (i * 4) << "($sp)\n";
	}

	for (int i = 0; i < temp_regs; i++)
	{
		out << "\tsw\t$t" << i << "," << ((arg_regs + i) * 4) << "($sp)\n";
	}
	
	return;
}

void status::pop_registers(std::ostream& out)
{
	int arg_regs = function_params.var_count();
	if (arg_regs > 4)
		arg_regs = 4;
	
	int temp_regs = reg_no;
	if (temp_regs == -1)
		temp_regs = 0;

	for (int i = 0; i < arg_regs; i++)
	{
		out << "\tlw\t$a" << i << "," << (i * 4) << "($sp)\n";
	}

	for (int i = 0; i < temp_regs; i++)
	{	
		out << "\tlw\t$t" << i << "," << ((arg_regs + i) * 4) << "($sp)\n";
	}

	if (arg_regs + temp_regs > 0)
		out << "\taddiu\t$sp,$sp," << ((arg_regs + temp_regs) * 4) << "\n";
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
	case_label = "empty";
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

void status::set_case_label()
{
	case_label = label_gen();
	return;
}

std::string status::get_case_label()
{
	return case_label;
}

void status::change_text_data(std::string in, std::ostream& out)
{
	if (in == "text")
	{
		if (text_data != 1)
			out << "\t.text\n";
		text_data = 1;
	}
	else if (in == "data")
	{
		if (text_data != 2)
			out << "\t.data\n";
		text_data = 2;
	}
	else if (in == "rdata")
	{
		if (text_data != 3)
			out << "\t.rdata\n";
		text_data = 3;
	}

	return;
}


