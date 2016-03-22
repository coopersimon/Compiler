%define parse.error verbose
%{
#include "ast.hpp"
#include "variables.hpp"
#include <iostream>

extern ast_value* c_ast;

int yylex();
void yyerror(const char*);
%}

%union
{
	int integer;
	char const* str;
	ast_value* node;
}

%token _CHAR _DOUBLE _FLOAT _INT _LONG _SHORT _SIGNED _UNSIGNED _VOID
%token _DO _ELSE _FOR _IF _WHILE
%token _BREAK _CONTINUE _GOTO _RETURN
%token _CASE _DEFAULT _SWITCH
%token _AUTO _CONST _EXTERN _REGISTER _STATIC _VOLATILE
%token _ENUM _STRUCT _TYPEDEF _UNION
%token _ID _CNUM _CFP _CCHAR _STR
%token _ADD _SUB _MULT _DIV _MOD _AND _OR _XOR _LSHIFT _RSHIFT
%token _ASSIGN _ADDA _SUBA _MULTA _DIVA _MODA _ANDA _ORA _XORA _LSHIFTA _RSHIFTA
%token _LAND _LOR _EQUAL _NEQUAL _LESSEQUAL _GREATEQUAL _LESSTHAN _GREATTHAN
%token _BITCOMP _COMP _INC _DEC
%token _COMMA _COLON _COND _SEMI _ELLIPSIS
%token _LPAR _RPAR _LCBRA _RCBRA _LBRAK _RBRAK
%token _DOT _ARROW _SIZEOF
%token _NEWLINE _PREP

%type <integer> _CNUM
%type <str> _ID assign_op unary_op
%type <node> type_spec
%type <node> trans_unit ext_decl func_def declaration id_list
%type <node> expr cast_exp unary_exp post_exp prim_exp
%type <node> statement label_stat expr_stat jump_stat select_stat iter_stat
%type <node> cond_exp lor_exp land_exp or_exp xor_exp and_exp
%type <node> assign_exp equal_exp relate_exp shift_exp add_exp mult_exp
%type <node> param_list decl_list stat_list arg_exp_list
%type <node> declarator direct_decl
%type <node> param_decl
%type <node> comp_stat
%type <node> init_decl init_d_list

%start root

%%

root		: trans_unit { c_ast = $1; }
	 		;

trans_unit	: ext_decl { $$ = $1; }
		   	| trans_unit ext_decl { $$ = new ast_node($1, $2); }
			;

ext_decl	: func_def { $$ = $1; }
		 	| declaration { $$ = $1; }
			;

func_def	: type_spec declarator { $$ = new ast_node($1, $2); }
		 	| declarator { $$ = $1; }
			| decl_list comp_stat { ast_value* func = new n_func_def($2);
						$$ = new ast_node($1, func); }
			| comp_stat { $$ = new n_func_def($1); }
		 	;

declarator	: _MULT direct_decl { $$ = new n_pointer($2); }
		| direct_decl { $$ = $1; }
		;

direct_decl	: _ID { $$ = new v_id($1); }
			| _LPAR declarator _RPAR { $$ = $2; }
			| direct_decl _LBRAK _CNUM _RBRAK { $$ = new n_array($1, $3); }
		   	| direct_decl _LPAR param_list _RPAR { $$ = new n_func_decl($1, $3); }
			| direct_decl _LPAR id_list _RPAR { $$ = new n_func_decl($1, $3); }
			| direct_decl _LPAR _RPAR { $$ = new n_func_decl($1, NULL); }
			;

param_list	: param_decl { $$ = $1; }
		   	| param_list _COMMA param_decl { $$ = new n_list($1, $3); }
			;

param_decl	: type_spec declarator { $$ = new n_param_decl($1, $2); }
		   	;

type_spec	: _INT { $$ = new v_type(long_s); }
		  	;

id_list		: _ID { $$ = new v_id($1); }
		 	| id_list _COMMA _ID	{ ast_value* ident = new v_id($3);
									  $$ = new n_list($1, ident); }
			;

comp_stat	: _LCBRA _RCBRA { $$ = new n_comp_stat(NULL, NULL); }
		  	| _LCBRA decl_list _RCBRA { $$ = new n_comp_stat($2, NULL); }
			| _LCBRA stat_list _RCBRA { $$ = new n_comp_stat(NULL, $2); }
			| _LCBRA decl_list stat_list _RCBRA { $$ = new n_comp_stat($2, $3); }
			;

decl_list	: declaration { $$ = $1; }
		  	| decl_list declaration { $$ = new ast_node($1, $2); }
			;

declaration : type_spec init_d_list _SEMI { $$ = new n_stat($1, $2); }
			;

init_d_list	: init_decl { $$ = $1; }
			| init_d_list _COMMA init_decl { $$ = new n_list($1, $3); }
			;

init_decl	: declarator { $$ = new n_init_decl($1, NULL); }
		  	| declarator _ASSIGN assign_exp { $$ = new n_init_decl($1, $3); }
			;

stat_list	: statement { $$ = $1; }
		  	| stat_list statement { $$ = new ast_node($1, $2); }
			;

statement	: expr_stat { $$ = $1; }
			| comp_stat { $$ = $1; }
		  	| label_stat { $$ = $1; }
			| select_stat { $$ = $1; }
			| iter_stat { $$ = $1; }
			| jump_stat { $$ = $1; }
			;

label_stat	/*: _ID _COLON statement { $$ = new n_label($1, $3); }*/
		: _CASE cond_exp _COLON statement { $$ = new n_case($2, $4); }
		| _DEFAULT _COLON statement { $$ = new n_case(NULL, $3); }
		;

expr_stat	: expr _SEMI { $$ = new n_stat($1, NULL); }
		  	| _SEMI { $$ = new n_stat(NULL, NULL); }
			;

select_stat	: _IF _LPAR expr _RPAR statement { $$ = new n_ifelse($3, $5, NULL); }
			| _IF _LPAR expr _RPAR statement _ELSE statement { $$ = new n_ifelse($3, $5, $7); }
			| _SWITCH _LPAR expr _RPAR statement { $$ = new n_switch($3, $5); }
			;

iter_stat	: _WHILE _LPAR expr _RPAR statement { $$ = new n_while($3, $5); }
		  	| _DO statement _WHILE _LPAR expr _RPAR _SEMI { $$ = new n_dowhile($2, $5); }
			| _FOR _LPAR _SEMI _SEMI _RPAR statement	{ ast_value* cond = new v_int(1);
										$$ = new n_for(NULL, cond, NULL, $6); }
			| _FOR _LPAR expr _SEMI _SEMI _RPAR statement	{ ast_value* cond = new v_int(1);
										$$ = new n_for($3, cond, NULL, $7); }
			| _FOR _LPAR _SEMI expr _SEMI _RPAR statement	{ $$ = new n_for(NULL, $4, NULL, $7); }
			| _FOR _LPAR _SEMI _SEMI expr _RPAR statement	{ ast_value* cond = new v_int(1);
										$$ = new n_for(NULL, cond, $5, $7); }
			| _FOR _LPAR expr _SEMI expr _SEMI _RPAR statement { $$ = new n_for($3, $5, NULL, $8); }
			| _FOR _LPAR expr _SEMI _SEMI expr _RPAR statement { ast_value* cond = new v_int(1);
										$$ = new n_for($3, cond, $6, $8); }
			| _FOR _LPAR _SEMI expr _SEMI expr _RPAR statement { $$ = new n_for(NULL, $4, $6, $8); }
			| _FOR _LPAR expr _SEMI expr _SEMI expr _RPAR statement { $$ = new n_for($3, $5, $7, $9); }
			;

jump_stat	/*: _GOTO _ID _SEMI { $$ = new n_jump_stat(NULL, $2); }*/
			: _CONTINUE _SEMI { $$ = new n_jump_stat(NULL, "continue"); }
			| _BREAK _SEMI { $$ = new n_jump_stat(NULL, "break"); }
			| _RETURN _SEMI { $$ = new n_jump_stat(NULL, "return"); }
		  	| _RETURN expr _SEMI	{ $$ = new n_jump_stat($2, "return"); }
			;

expr		: assign_exp { $$ = $1; }
	  		| expr _COMMA assign_exp { $$ = new n_list($1, $3); }
			;

assign_exp	: cond_exp { $$ = $1; }
		   	| unary_exp _ASSIGN assign_exp { $$ = new n_expression($1, $3, "="); }
			| unary_exp assign_op assign_exp { ast_value* result = new n_expression($1, $3, $2);
							$$ = new n_expression($1, result, "="); }
			;

cond_exp	: lor_exp { $$ = $1; }
			| lor_exp _COND expr _COLON cond_exp { $$ = new n_ternary($1, $3, $5); }
			;

lor_exp		: land_exp { $$ = $1; }
		 	| lor_exp _LOR land_exp { $$ = new n_expression($1, $3, "||"); }
			;

land_exp	: or_exp { $$ = $1; }
		 	| land_exp _LAND or_exp { $$ = new n_expression($1, $3, "&&"); }
			;

or_exp		: xor_exp { $$ = $1; }
			| or_exp _OR xor_exp { $$ = new n_expression($1, $3, "|"); }
			;

xor_exp		: and_exp { $$ = $1; }
		 	| xor_exp _XOR and_exp { $$ = new n_expression($1, $3, "^"); }
			;

and_exp		: equal_exp { $$ = $1; }
		 	| and_exp _AND equal_exp { $$ = new n_expression($1, $3, "&"); }
			;

equal_exp	: relate_exp { $$ = $1; }
		  	| equal_exp _EQUAL relate_exp { $$ = new n_expression($1, $3, "=="); }
			| equal_exp _NEQUAL relate_exp { $$ = new n_expression($1, $3, "!="); }
			;

relate_exp	: shift_exp { $$ = $1; }
		   	| relate_exp _LESSTHAN shift_exp { $$ = new n_expression($1, $3, "<"); }
			| relate_exp _GREATTHAN shift_exp { $$ = new n_expression($1, $3, ">"); }
			| relate_exp _LESSEQUAL shift_exp { $$ = new n_expression($1, $3, "<="); }
			| relate_exp _GREATEQUAL shift_exp { $$ = new n_expression($1, $3, ">="); }
			;

shift_exp	: add_exp { $$ = $1; }
		  	| shift_exp _LSHIFT add_exp { $$ = new n_expression($1, $3, "<<"); }
			| shift_exp _RSHIFT add_exp { $$ = new n_expression($1, $3, ">>"); }
			;

add_exp		: mult_exp { $$ = $1; }
		 	| add_exp _ADD mult_exp { $$ = new n_expression($1, $3, "+"); }
		 	| add_exp _SUB mult_exp { $$ = new n_expression($1, $3, "-"); }
			;

mult_exp	: cast_exp { $$ = $1; }
		 	| mult_exp _MULT cast_exp { $$ = new n_expression($1, $3, "*"); }
		 	| mult_exp _DIV cast_exp { $$ = new n_expression($1, $3, "/"); }
		 	| mult_exp _MOD cast_exp { $$ = new n_expression($1, $3, "%"); }
			;

cast_exp	: unary_exp { $$ = $1; }
		| _LPAR type_spec _RPAR cast_exp { $$ = new ast_node($2, $4); }
		;

unary_exp	: post_exp { $$ = $1; }
		  	| _INC unary_exp { $$ = new n_expression(NULL, $2, "++"); }
			| _DEC unary_exp { $$ = new n_expression(NULL, $2, "--"); }
			| unary_op cast_exp { $$ = new n_expression(NULL, $2, $1); }
			;

unary_op	: _COMP { $$ = "!"; }
		| _BITCOMP { $$ = "~"; }
		| _ADD { $$ = "+"; }
		| _SUB { $$ = "-"; }
		| _AND { $$ = "&"; }
		| _MULT { $$ = "*"; }
		;

post_exp	: prim_exp { $$ = $1; }
			| post_exp _LBRAK expr _RBRAK { $$ = new n_expression($1, $3, "[]"); }
		 	| post_exp _INC { $$ = new n_expression($1, NULL, "++"); }
			| post_exp _DEC { $$ = new n_expression($1, NULL, "--"); }
			| post_exp _LPAR arg_exp_list _RPAR { $$ = new n_func_call($1, $3); }
			| post_exp _LPAR _RPAR { $$ = new n_func_call($1, NULL); }
			;

prim_exp	: _ID { $$ = new v_id($1); }
		 	| _CNUM { $$ = new v_int($1); }
			| _LPAR expr _RPAR { $$ = $2; }
			;

arg_exp_list	: assign_exp { $$ = new n_arg_list(NULL, $1); }
		| arg_exp_list _COMMA assign_exp { $$ = new n_arg_list($1, $3); }
		;

assign_op	: _ADDA { $$ = "+"; }
		| _SUBA { $$ = "-"; }
		| _MULTA { $$ = "*"; }
		| _DIVA { $$ = "/"; }
		| _MODA { $$ = "%"; }
		| _ANDA { $$ = "&"; }
		| _ORA { $$ = "|"; }
		| _XORA { $$ = "^"; }
		| _LSHIFTA { $$ = "<<"; }
		| _RSHIFTA { $$ = ">>"; }
		;
%%


void yyerror(const char* s)
{
	std::cerr << s << std::endl;
	return;
}
