#ifndef STATUS_HPP
#define STATUS_HPP

#include "variables.hpp"
#include <string>
#include <vector>
#include <ostream>

class status
{
	private:
		// dealing with jumps:
		int label_no;

		// dealing with functions:
		std::string function_name; // name of function: used in code_gen
		int current_function; // internal tracker used to access function vector
		std::vector<var_list> scope_vars; // vector of variables, for each scope.
		std::vector<int> variable_count; // counts the variables in a function.

		// dealing with types:
		type current_type; // keeps track of current type
		int var_size;

		// dealing with parameters:
		parameter_list function_params;
		
		// dealing with variables:
		bool declaration;
		bool param_decl;
		bool assign;

		// dealing with pointers:
		bool pointer;

		// dealing with (temp) registers:
		int reg_no;
		bool assign_expr; // if jump is setting equal to something, then a register doesnt need to be reserved. e.g. return x = x + y;

		// dealing with jumps
		std::vector<int> return_count; // number of return expressions in a function
		std::vector<std::string> continue_label; // the labels in use for continues
		std::vector<std::string> break_label; // the labels in use for breaks
		std::string case_label; // label for cases

		// dealing with function calls:
		int no_args;

		// dealing with scope:
		int scope;

		// dealing with text/data - start = 0, text = 1, data = 2 (more to be added later? maybe)
		int text_data;
	public:
		status() : label_no(0), current_function(0), current_type(long_s), var_size(1), reg_no(-1), assign_expr(false), no_args(0), scope(0), text_data(0), declaration(false), assign(false), param_decl(false), pointer(false), case_label("empty") { scope_vars.push_back(var_list()); variable_count.push_back(0); return_count.push_back(0); }

		std::string label_gen();

		void add_function(); // add a new function and increase the tracker.
		void reset_current_function(); // reset the function tracker.
		void add_variable(std::string var_name); // add a variable to the current function.
		std::string variable_location(std::string var_name); // get the location of a variable
		void count_variable(); // counts the variable for stack use.
		int size_variables(); // get the size of variables in the function (in bytes)

		void set_type(type in_type); // set the type which all init decls use
		void set_var_size(int in); // set the stack size which all variables use

		void add_parameter(std::string param_name); // add a parameter to the current function
		void remove_parameters(); // removes all parameters

		void name_function(std::string name);
		std::string get_function_name();

		void set_decl(bool param); // for if a variable is being declared
		bool get_decl(bool &param);
		void set_assign_var(); // for if a variable is being assigned a value
		bool get_assign_var();

		void set_reference(); // for if a value is being referenced
		bool get_reference();
		void set_dereference(); // for if a value is being dereferenced
		bool get_dereference();

		void lock_register(std::ostream& out); // locks a register.
		int get_register(); // gets the value of the last locked register.
		void unlock_register(std::ostream& out); // unlocks the last locked register.

		void add_return(); // add a return statement to the current function.
		int number_returns();

		void push_arg_registers(std::ostream& out); // pushes all argument registers in use on the stack
		void pop_arg_registers(std::ostream& out); // pops all argument registers in use off the stack
		int lock_arg_register(std::ostream& out); // locks arg register/stack space and stores it
		void unlock_arg_registers(std::ostream& out); // pops args stored on stack off.

		void new_scope();
		void delete_scope();
		bool global_var();

		void set_assign_expr(); //sorry about these....
		bool get_assign_expr();

		void reset_labels(bool cont); // empties break (& optionally continue) labels
		void set_continue_label(); // sets the label used for contiues within a loop
		std::string get_continue_label(); // gets the continue label
		void set_break_label();
		std::string get_break_label();
		void set_case_label();
		std::string get_case_label();

		void change_text_data(std::string in, std::ostream& out); // print change to text or data (if needed)
		//void dump_vars();
};


#endif
