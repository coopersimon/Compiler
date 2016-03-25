#ifndef VARIABLES_HPP
#define VARIABLES_HPP

#include <string>
#include <vector>

enum type {void_t, char_s, char_u, char_p, short_s, short_u, short_p, long_s, long_u, long_p, float_t, float_p};

type pointer_type(type input);

class variable
{
	private:
		std::string var_name;
		type var_type;
		int elements; // number of elements (usually 1)
	public:
		variable(std::string name_in, type type_in) : var_name(name_in), var_type(type_in), elements(1) {}
		variable(std::string name_in, type type_in, int e_in) : var_name(name_in), var_type(type_in), elements(e_in) {}
		std::string name();
		type get_var_type();
		int var_size();
};

class var_list
{
	protected:
		std::vector<variable> vars;
	public:
		void add_variable(std::string var_name, type var_type);
		void add_variable(std::string var_name, type var_type, int var_size);
		int variable_offset(std::string var_name);
		type variable_type(std::string var_name);
		int variable_size(std::string var_name);
		int var_count();
		void clear();
};

class parameter_list : public var_list
{
		// parameters are stored in the variables vector (inherited)
	public:
		int variable_offset(std::string var_name);
};

#endif
