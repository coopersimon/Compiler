#ifndef STATUS_HPP
#define STATUS_HPP

#include <string>
#include <vector>
#include <map>

class status
{
	private:
		// dealing with jumps:
		int label_no;

		// dealing with functions:
		std::string function_name; // name of function: used in code_gen
		int current_function; // internal tracker used to access function vector
		int current_variable;
		std::vector<std::map<std::string, int> > function; // vector of maps, each map contains all the variables of a function
		
		// dealing with (temp) registers:
		int reg_no;

	public:
		status() : label_no(0), current_function(0), reg_no(-1) {}

		std::string label_gen(std::string in);

		void add_function();
		void reset_current_function();
		void add_variable(std::string var_name);
		int variable_offset(std::string var_name);
		int number_variables();

		void name_function(std::string name);
		std::string get_function_name();

		bool lock_register(); // locks a register.
		int get_register(); // gets the value of the last locked register.
		void unlock_register(); // unlocks the last locked register.
};

#endif
