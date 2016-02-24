%{
#include <iostream>
#include <ast.hpp>

extern node *c_ast;

int yylex();
void yyerror(const char* s);
%}

%union
{
	int integer;
	char* str;
	ast_node node;
	n_function function;
	n_declar declaration;
	
}

%token _INT
%token _IF _ELSE _WHILE _FOR
%token _RETURN
%token _ID _CNUM
%token _ADD _SUB
%token _ASSIGN
%token _EQUAL
%token _SEMI _COMMA
%token _LPAR _RPAR _LCBRA _RCBRA 


%type <integer> _INT
%type <str> _ID
%type <node> trans_unit
%type <function> func_def
%type <declaration> declaration


%start root

%%

root		: trans_unit
	 		;

trans_unit	: func_def
		   	| trans_unit func_def
			;

func_def	: type_spec direct_dec
			| declaration comp_stat
		 	;

direct_dec	: _ID
		   	| direct_dec _LPAR param_list _RPAR
			;

param_list	: param_decl
		   	| param_list _COMMA param_decl
			;

param_decl	: type_spec direct_dec
		   	;

declaration : type_spec _ID
			;

type_spec	: _INT
		  	;

comp_stat	: _LCBRA _RCBRA
		  	| _LCBRA decl_list _RCBRA
			| _LCBRA stat_list _RCBRA
			| _LCBRA decl_list stat_list _RCBRA
			;

decl_list	: declaration
		  	| decl_list declaration
			;

stat_list	: statement
		  	| stat_list statement
			;

statement	: comp_stat
		  	| expr_stat
			| jump_stat
			;

expr_stat	: expr _SEMI
		  	| _SEMI
			;

expr		: assign_exp
	  		| expr LCOMMA assign_exp
			;

assign_exp	: equal_exp
		   	| prim_exp assign_op assign_exp
			;

equal_exp	: add_exp
		  	| equal_exp _EQUAL add_exp
			;

add_exp		: prim_exp
		 	| prim_exp _ADD add_exp
		 	| prim_exp _SUB add_exp
			;

prim_exp	: _ID
		 	| _CNUM
			| _LPAR expr _RPAR
			;

assign_op	: _ASSIGN
		  	;

%%


void yyerror(const char* s)
{
	std::cout << s << std::endl;
	return -1;
}

int main()
{
	yyparse();
}
