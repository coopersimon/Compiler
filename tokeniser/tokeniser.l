%option noyywrap
%{
#include <iostream>
#include <string>
#include <cstdlib>
enum token_type {_AUTO = 256, _BREAK, _CAS, _CHAR, _CONST, _CONTINUE, _DEFAULT, _DO, _DOUBLE, _ELSE, _ENUM, _EXTERN, _FLOAT, _FOR, _GOTO, _IF, _INT, _LONG, _REGISTER, _RETURN, _SHORT, _SIGNED, _SIZEOF, _STATIC, _STRUCT, _SWITCH, _TYPEDEF, _UNION, _UNSIGNED, _VOID, _VOLATILE, _WHILE, _ID, _ADD, _SUB, _MULT, _DIV, _MOD, _AND, _OR, _XOR, _LSHIFT, _RSHIFT, _ASSIGN, _ADDA, _SUBA, _MULTA, _DIVA, _MODA, _ANDA, _ORA, _XORA, _LSHIFTA, _RSHIFTA, _LAND, _LOR, _EQUAL, _NEQUAL, _LESSEQUAL, _GREATEQUAL, _LESSTHAN, _GREATTHAN, _BITCOMP, _COMP, _INC, _DEC, _COMMA, _CASE, _COND, _SEMI, _LPAR, _RPAR, _LCBRA, _RCBRA, _LBRAK, _RBRAK, _CDEC, _CFP, _CHEX, _COCT, _STR, _WSPACE, _NEWLINE, _PREP, _DOT, _ARROW, _ELLIPSIS, _CCHAR, _INVALID };
%}

DIGIT		[0-9]
LETTER		[a-zA-Z_]
CHAR		[0-9a-zA-Z_]
STRING		\"[^\n\"\\]*\"
HEX			[0-9a-fA-F]
OCT			[0-7]
S			(([uU][lL]?)|([lL][uU]?))?

FLOAT1		(([0-9]*\.[0-9]+)|([0-9]+\.[0-9]*))[fFlL]?
FLOAT2		[0-9]+[eE][+-]?[0-9]+[fFlL]?
FLOAT3		(([0-9]*\.[0-9]+)|([0-9]+\.[0-9]*))[eE][+-]?[0-9]+[fFlL]?

CCHAR		\'[^\n'\\]+\'

WHITESPACE	[ \t]

SOURCE		#[ ]{DIGIT}+[ ]{STRING}([ ]1)?([ ]2)?([ ]3)?([ ]4)?

%%
auto			return _AUTO;
break			return _BREAK;
case			return _CAS;
char			return _CHAR;
const			return _CONST;
continue		return _CONTINUE;
default			return _DEFAULT;
do				return _DO;
double			return _DOUBLE;
else			return _ELSE;
enum			return _ENUM;
extern			return _EXTERN;
float			return _FLOAT;
for				return _FOR;
goto			return _GOTO;
if				return _IF;
int				return _INT;
long			return _LONG;
register		return _REGISTER;
return			return _RETURN;
short			return _SHORT;
signed			return _SIGNED;
static			return _STATIC;
struct			return _STRUCT;
switch			return _SWITCH;
typedef			return _TYPEDEF;
union			return _UNION;
unsigned		return _UNSIGNED;
void			return _VOID;
volatile		return _VOLATILE;
while			return _WHILE;

sizeof			return _SIZEOF;

{LETTER}{CHAR}*	return _ID;


\+				return _ADD;
-				return _SUB;
\*				return _MULT;
\/				return _DIV;
%				return _MOD;

&				return _AND;
\|				return _OR;
\^				return _XOR;
\<\<			return _LSHIFT;
>>				return _RSHIFT;

=				return _ASSIGN;
\+=				return _ADDA;
-=				return _SUBA;
\*=				return _MULTA;
\/=				return _DIVA;
%=				return _MODA;
&=				return _ANDA;
\|=				return _ORA;
\^=				return _XORA;
\<\<=			return _LSHIFTA;
>>=				return _RSHIFTA;

&&				return _LAND;
\|\|			return _LOR;
==				return _EQUAL;
!=				return _NEQUAL;
\<=				return _LESSEQUAL;
>=				return _GREATEQUAL;
\<				return _LESSTHAN;
>				return _GREATTHAN;

~				return _BITCOMP;
!				return _COMP;
\+\+			return _INC;
--				return _DEC;

,				return _COMMA;
:				return _CASE;
\?				return _COND;
;				return _SEMI;
\.\.\.			return _ELLIPSIS;

\(				return _LPAR;
\)				return _RPAR;
\{				return _LCBRA;
\}				return _RCBRA;
\[				return _LBRAK;
\]				return _RBRAK;

\.				return _DOT;
->				return _ARROW;

[1-9]{DIGIT}*{S}			return _CDEC;
({FLOAT1}|{FLOAT2}|{FLOAT3})	return _CFP;
0[xX]{HEX}+{S}				return _CHEX;
0{OCT}*{S}					return _COCT;
[L]?{CCHAR}						return _CCHAR;


[L]?{STRING}		return _STR;


\n				return _NEWLINE;
\t
[ ]
{SOURCE}		return _PREP;

%%

int main()
{
	using namespace std;

	int line_num = 1;
	int source_line = 1;
	string source_file = "";

	bool print;
	string t_class_type;

	int ttcode = yylex();
	
	while(ttcode != 0)
	{
		print = true;

		switch(ttcode)
		{
			case _AUTO:
				t_class_type = " Keyword T_AUTO ";
				break;
			case _BREAK:
				t_class_type = " Keyword T_BREAK ";
				break;
			case _CAS:
				t_class_type = " Keyword T_CASE ";
				break;
			case _CHAR:
				t_class_type = " Keyword T_CHAR ";
				break;
			case _CONST:
				t_class_type = " Keyword T_CONST ";
				break;
			case _CONTINUE:
				t_class_type = " Keyword T_CONTINUE ";
				break;
			case _DEFAULT:
				t_class_type = " Keyword T_DEFAULT ";
				break;
			case _DO:
				t_class_type = " Keyword T_DO ";
				break;
			case _DOUBLE:
				t_class_type = " Keyword T_DOUBLE ";
				break;
			case _ELSE:
				t_class_type = " Keyword T_ELSE ";
				break;
			case _ENUM:
				t_class_type = " Keyword T_ENUM ";
				break;
			case _EXTERN:
				t_class_type = " Keyword T_EXTERN ";
				break;
			case _FLOAT:
				t_class_type = " Keyword T_FLOAT ";
				break;
			case _FOR:
				t_class_type = " Keyword T_FOR ";
				break;
			case _GOTO:
				t_class_type = " Keyword T_GOTO ";
				break;
			case _IF:
				t_class_type = " Keyword T_IF ";
				break;
			case _INT:
				t_class_type = " Keyword T_INT ";
				break;
			case _LONG:
				t_class_type = " Keyword T_LONG ";
				break;
			case _REGISTER:
				t_class_type = " Keyword T_REGISTER ";
				break;
			case _RETURN:
				t_class_type = " Keyword T_RETURN ";
				break;
			case _SHORT:
				t_class_type = " Keyword T_SHORT ";
				break;
			case _SIGNED:
				t_class_type = " Keyword T_SIGNED ";
				break;
			case _STATIC:
				t_class_type = " Keyword T_STATIC ";
				break;
			case _STRUCT:
				t_class_type = " Keyword T_STRUCT ";
				break;
			case _SWITCH:
				t_class_type = " Keyword T_SWITCH ";
				break;
			case _TYPEDEF:
				t_class_type = " Keyword T_TYPEDEF ";
				break;
			case _UNION:
				t_class_type = " Keyword T_UNION ";
				break;
			case _UNSIGNED:
				t_class_type = " Keyword T_UNSIGNED ";
				break;
			case _VOID:
				t_class_type = " Keyword T_VOID ";
				break;
			case _VOLATILE:
				t_class_type = " Keyword T_VOLATILE ";
				break;
			case _WHILE:
				t_class_type = " Keyword T_WHILE ";
				break;
			case _ID:
				t_class_type = " Identifier T_ID ";
				break;
			case _ADD:
				t_class_type = " Operator T_ADD ";
				break;
			case _SUB:
				t_class_type = " Operator T_SUB ";
				break;
			case _MULT:
				t_class_type = " Operator T_MULT ";
				break;
			case _DIV:
				t_class_type = " Operator T_DIV ";
				break;
			case _MOD:
				t_class_type = " Operator T_MOD ";
				break;
			case _AND:
				t_class_type = " Operator T_AND ";
				break;
			case _OR:
				t_class_type = " Operator T_OR ";
				break;
			case _XOR:
				t_class_type = " Operator T_XOR ";
				break;
			case _LSHIFT:
				t_class_type = " Operator T_LSHIFT ";
				break;
			case _RSHIFT:
				t_class_type = " Operator T_RSHIFT ";
				break;
			case _ASSIGN:
				t_class_type = " Operator T_ASSIGN ";
				break;
			case _ADDA:
				t_class_type = " Operator T_ADDA ";
				break;
			case _SUBA:
				t_class_type = " Operator T_SUBA ";
				break;
			case _MULTA:
				t_class_type = " Operator T_MULTA ";
				break;
			case _DIVA:
				t_class_type = " Operator T_DIVA ";
				break;
			case _MODA:
				t_class_type = " Operator T_MODA ";
				break;
			case _ANDA:
				t_class_type = " Operator T_ANDA ";
				break;
			case _ORA:
				t_class_type = " Operator T_ORA ";
				break;
			case _XORA:
				t_class_type = " Operator T_XORA ";
				break;
			case _LSHIFTA:
				t_class_type = " Operator T_LSHIFTA ";
				break;
			case _RSHIFTA:
				t_class_type = " Operator T_RSHIFTA ";
				break;
			case _LAND:
				t_class_type = " Operator T_LAND ";
				break;
			case _LOR:
				t_class_type = " Operator T_LOR ";
				break;
			case _EQUAL:
				t_class_type = " Operator T_EQUAL ";
				break;
			case _NEQUAL:
				t_class_type = " Operator T_NEQUAL ";
				break;
			case _LESSEQUAL:
				t_class_type = " Operator T_LESSEQUAL ";
				break;
			case _GREATEQUAL:
				t_class_type = " Operator T_GREATEQUAL ";
				break;
			case _LESSTHAN:
				t_class_type = " Operator T_LESSTHAN ";
				break;
			case _GREATTHAN:
				t_class_type = " Operator T_GREATTHAN ";
				break;
			case _BITCOMP:
				t_class_type = " Operator T_BITCOMP ";
				break;
			case _COMP:
				t_class_type = " Operator T_COMP ";
				break;
			case _INC:
				t_class_type = " Operator T_INC ";
				break;
			case _DEC:
				t_class_type = " Operator T_DEC ";
				break;
			case _COMMA:
				t_class_type = " Operator T_COMMA ";
				break;
			case _CASE:
				t_class_type = " Operator T_CASE ";
				break;
			case _COND:
				t_class_type = " Operator T_COND ";
				break;
			case _SEMI:
				t_class_type = " Operator T_SEMI ";
				break;
			case _LPAR:
				t_class_type = " Operator T_LPAR ";
				break;
			case _RPAR:
				t_class_type = " Operator T_RPAR ";
				break;
			case _LCBRA:
				t_class_type = " Operator T_LBRA ";
				break;
			case _RCBRA:
				t_class_type = " Operator T_RBRA ";
				break;
			case _LBRAK:
				t_class_type = " Operator T_LBRAK ";
				break;
			case _RBRAK:
				t_class_type = " Operator T_RBRAK ";
				break;
			case _SIZEOF:
				t_class_type = " Operator T_SIZEOF ";
				break;
			case _DOT:
				t_class_type = " Operator T_DOT ";
				break;
			case _ARROW:
				t_class_type = " Operator T_ARROW ";
				break;
			case _ELLIPSIS:
				t_class_type = " Operator T_ELLIPSIS ";
				break;
			case _CDEC:
				t_class_type = " Constant T_CDEC ";
				break;
			case _CFP:
				t_class_type = " Constant T_CFP ";
				break;
			case _CHEX:
				t_class_type = " Constant T_CHEX ";
				break;
			case _COCT:
				t_class_type = " Constant T_COCT ";
				break;
			case _CCHAR:
				t_class_type = " Constant T_CCHAR ";
				break;
			case _STR:
				t_class_type = " StringLiteral T_STR ";
				break;
			case _NEWLINE:
				line_num++;
				source_line++;
				print = false;
				break;
			case _PREP:
			{
				string prep(yytext);
				// find the first "
				size_t first = prep.find('"');
				// find the last "
				size_t last = prep.rfind('"');
				// erase the flags
				prep.erase(last);
				// get just the source file
				source_file = prep.substr(first + 1, last - first - 1);
				prep.erase(first - 1);
				// get just the source line
				string num = prep.substr(2);
				source_line = strtol(num.c_str(), NULL, 10) - 1;
				print = false;
			}
				break;
			default:
				t_class_type = " invalid T_INVALID ";
				break;
		}
		
		if (print)
			cout << yytext << t_class_type << line_num << " " << source_file << " " << source_line << endl;

		ttcode = yylex();
	}

	return 0;
}
