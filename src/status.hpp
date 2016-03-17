#ifndef STATUS_HPP
#define STATUS_HPP

#include <string>
#include <vector>
#include <map>
#include <ostream>

class variables
{
	protected:
		std::vector<std::string> vars;
	public:
		void add_variable(std::string var_name);
		int variable_offset(std::string var_name);
		int var_count();

		//void dump_vars();
};

class parameters : public variables
{
		// parameters are stored in the variables vector (inherited)
	public:
		int variable_offset(std::string var_name);
		void clear();
};

class status
{
	private:
		// dealing with jumps:
		int label_no;

		// dealing with functions:
		std::string function_name; // name of function: used in code_gen
		int current_function; // internal tracker used to access function vector
		std::vector<variables> scope_vars; // vector of variables, for each scope.
		std::vector<int> variable_count; // counts the variables in a function.
		
		// dealing with parameters:
		parameters function_params;
		
		// dealing with (temp) registers:
		int reg_no;
		bool assign_expr; // if jump is setting equal to something, then a register doesnt need to be reserved. e.g. return x = x + y;

		// dealing with returning
		std::vector<int> return_count; // number of return expressions in a function

		// dealing with function calls:
		int no_args;

		// dealing with scope:
		int scope;

		// dealing with text/data - start = 0, text = 1, data = 2 (more to be added later? maybe)
		int text_data;
	public:
		status() : label_no(0), current_function(0), reg_no(-1), assign_expr(false), no_args(0), scope(0), text_data(0) { scope_vars.push_back(variables()); variable_count.push_back(0); return_count.push_back(0); }

		std::string label_gen();

		void add_function(); // add a new function and increase the tracker.
		void reset_current_function(); // reset the function tracker.
		void add_variable(std::string var_name); // add a variable to the current function.
		std::string variable_location(std::string var_name); // get the location of a variable
		//std::string variable_location(int param_no); // get the location of a parameter
		int number_variables(); // get the number of variables in the current function.

		void add_parameter(std::string param_name); // add a parameter to the current function
		void remove_parameters(); // removes all parameters

		void name_function(std::string name);
		std::string get_function_name();

		void lock_register(std::ostream& out); // locks a register.
		int get_register(); // gets the value of the last locked register.
		void unlock_register(std::ostream& out); // unlocks the last locked register.

		void add_return(); // add a return statement to the current function.
		int number_returns();

		void push_arg_registers(std::ostream& out); // pushes all argument registers in use on the stack
		void pop_arg_registers(std::ostream& out); // pops all argument registers in use off the stack
		int lock_arg_register(std::ostream& out); // locks arg register/stack space and stores it
		void unlock_arg_registers(std::ostream& out); // pops args stored on stack off.

		void count_variable(); // counts the variable for stack use.

		void new_scope();
		void delete_scope();
		bool global_var();

		void set_assign_expr(); //sorry about these....
		bool get_assign_expr();

		void change_text_data(std::string in, std::ostream& out); // print change to text or data (if needed)
		//void dump_vars();
};


#endif
