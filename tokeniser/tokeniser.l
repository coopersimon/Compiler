%option noyywrap
%{
#include <iostream>
#include <string>
#include <cstdlib>
enum token_type {_AUTO = 256, _BREAK, _CAS, _CHAR, _CONST, _CONTINUE, _DEFAULT, _DO, _DOUBLE, _ELSE, _ENUM, _EXTERN, _FLOAT, _FOR, _GOTO, _IF, _INT, _LONG, _REGISTER, _RETURN, _SHORT, _SIGNED, _SIZEOF, _STATIC, _STRUCT, _SWITCH, _TYPEDEF, _UNION, _UNSIGNED, _VOID, _VOLATILE, _WHILE, _ID, _ADD, _SUB, _MULT, _DIV, _MOD, _AND, _OR, _XOR, _LSHIFT, _RSHIFT, _ASSIGN, _ADDA, _SUBA, _MULTA, _DIVA, _MODA, _ANDA, _ORA, _XORA, _LSHIFTA, _RSHIFTA, _LAND, _LOR, _EQUAL, _NEQUAL, _LESSEQUAL, _GREATEQUAL, _LESSTHAN, _GREATTHAN, _BITCOMP, _COMP, _INC, _DEC, _COMMA, _CASE, _COND, _SEMI, _LPAR, _RPAR, _LCBRA, _RCBRA, _LBRAK, _RBRAK, _CDEC, _CFP, _CHEX, _COCT, _STR, _WSPACE, _NEWLINE, _PREP };
%}

DIGIT		[0-9]
LETTER		[a-zA-Z_]
CHAR		({DIGIT}|{LETTER})	
STRING		\".+\"
HEX			[0-9a-fA-F]
OCT			[0-7]
S			[uUlL]?

FP1			{DIGIT}*\.{DIGIT}+
FP2			{DIGIT}+\.{DIGIT}*
FP3			({FP1}|{FP2})
EXP1		{DIGIT}+[eE]{DIGIT}+
EXP2		{FP3}[eE]{DIGIT}+
FLOAT		({FP3}|{EXP1}|{EXP2})[fFlL]?

WHITESPACE	[ \t]

SOURCE		#[ ]{DIGIT}+[ ]{STRING}([ ]1)?([ ]2)?([ ]3)?([ ]4)?

%%
auto			 return _AUTO;
break			 return _BREAK;
case			 return _CAS;
char			 return _CHAR;
const			 return _CONST;
continue		 return _CONTINUE;
default			 return _DEFAULT;
do				 return _DO;
double			 return _DOUBLE;
else			 return _ELSE;
enum			 return _ENUM;
extern			 return _EXTERN;
float			 return _FLOAT;
for				 return _FOR;
goto			 return _GOTO;
if				 return _IF;
int				 return _INT;
long			 return _LONG;
register		 return _REGISTER;
return			 return _RETURN;
short			 return _SHORT;
signed			 return _SIGNED;
sizeof			 return _SIZEOF;
static			 return _STATIC;
struct			 return _STRUCT;
switch			 return _SWITCH;
typedef			 return _TYPEDEF;
union			 return _UNION;
unsigned		 return _UNSIGNED;
void			 return _VOID;
volatile		 return _VOLATILE;
while			 return _WHILE;


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

\(				return _LPAR;
\)				return _RPAR;
\{				return _LCBRA;
\}				return _RCBRA;
\[				return _LBRAK;
\]				return _RBRAK;


[1-9]{DIGIT}*{S}	return _CDEC;
{FLOAT}				return _CFP;
0[xX]{HEX}+{S}		return _CHEX;
0{OCT}*{S}			return _COCT;


{STRING}		return _STR;


\n				return _NEWLINE;
\t
[ ]
{SOURCE}		return _PREP;

%%

int main()
{
	using namespace std;

	int line_num = 1;
	int source_line = 0;
	string source_file;

	int ttcode = yylex();
	
	while(ttcode != 0)
	{
		switch(ttcode)
		{
			case _AUTO:
				cout << yytext << " Keyword T_AUTO " << line_num << " " << source_file << " " << source_line << endl;
				break;
			case _BREAK:
				cout << yytext << " Keyword T_BREAK " << line_num << " " << source_file << " " << source_line << endl;
				break;
			case _CAS:
				cout << yytext << " Keyword T_CASE " << line_num << " " << source_file << " " << source_line << endl;
				break;
			case _CHAR:
				cout << yytext << " Keyword T_CHAR " << line_num << " " << source_file << " " << source_line << endl;
				break;
			case _CONST:
				cout << yytext << " Keyword T_CONST " << line_num << " " << source_file << " " << source_line << endl;
				break;
			case _CONTINUE:
				cout << yytext << " Keyword T_CONTINUE " << line_num << " " << source_file << " " << source_line << endl;
				break;
			case _DEFAULT:
				cout << yytext << " Keyword T_DEFAULT " << line_num << " " << source_file << " " << source_line << endl;
				break;
			case _DO:
				cout << yytext << " Keyword T_DO " << line_num << " " << source_file << " " << source_line << endl;
				break;
			case _DOUBLE:
				cout << yytext << " Keyword T_DOUBLE " << line_num << " " << source_file << " " << source_line << endl;
				break;
			case _ELSE:
				cout << yytext << " Keyword T_ELSE " << line_num << " " << source_file << " " << source_line << endl;
				break;
			case _ENUM:
				cout << yytext << " Keyword T_ENUM " << line_num << " " << source_file << " " << source_line << endl;
				break;
			case _EXTERN:
				cout << yytext << " Keyword T_EXTERN " << line_num << " " << source_file << " " << source_line << endl;
				break;
			case _FLOAT:
				cout << yytext << " Keyword T_FLOAT " << line_num << " " << source_file << " " << source_line << endl;
				break;
			case _FOR:
				cout << yytext << " Keyword T_FOR " << line_num << " " << source_file << " " << source_line << endl;
				break;
			case _GOTO:
				cout << yytext << " Keyword T_GOTO " << line_num << " " << source_file << " " << source_line << endl;
				break;
			case _IF:
				cout << yytext << " Keyword T_IF " << line_num << " " << source_file << " " << source_line << endl;
				break;
			case _INT:
				cout << yytext << " Keyword T_INT " << line_num << " " << source_file << " " << source_line << endl;
				break;
			case _LONG:
				cout << yytext << " Keyword T_LONG " << line_num << " " << source_file << " " << source_line << endl;
				break;
			case _REGISTER:
				cout << yytext << " Keyword T_REGISTER " << line_num << " " << source_file << " " << source_line << endl;
				break;
			case _RETURN:
				cout << yytext << " Keyword T_RETURN " << line_num << " " << source_file << " " << source_line << endl;
				break;
			case _SHORT:
				cout << yytext << " Keyword T_SHORT " << line_num << " " << source_file << " " << source_line << endl;
				break;
			case _SIGNED:
				cout << yytext << " Keyword T_SIGNED " << line_num << " " << source_file << " " << source_line << endl;
				break;
			case _SIZEOF:
				cout << yytext << " Keyword T_SIZEOF " << line_num << " " << source_file << " " << source_line << endl;
				break;
			case _STATIC:
				cout << yytext << " Keyword T_STATIC " << line_num << " " << source_file << " " << source_line << endl;
				break;
			case _STRUCT:
				cout << yytext << " Keyword T_STRUCT " << line_num << " " << source_file << " " << source_line << endl;
				break;
			case _SWITCH:
				cout << yytext << " Keyword T_SWITCH " << line_num << " " << source_file << " " << source_line << endl;
				break;
			case _TYPEDEF:
				cout << yytext << " Keyword T_TYPEDEF " << line_num << " " << source_file << " " << source_line << endl;
				break;
			case _UNION:
				cout << yytext << " Keyword T_UNION " << line_num << " " << source_file << " " << source_line << endl;
				break;
			case _UNSIGNED:
				cout << yytext << " Keyword T_UNSIGNED " << line_num << " " << source_file << " " << source_line << endl;
				break;
			case _VOID:
				cout << yytext << " Keyword T_VOID " << line_num << " " << source_file << " " << source_line << endl;
				break;
			case _VOLATILE:
				cout << yytext << " Keyword T_VOLATILE " << line_num << " " << source_file << " " << source_line << endl;
				break;
			case _WHILE:
				cout << yytext << " Keyword T_WHILE " << line_num << " " << source_file << " " << source_line << endl;
				break;
			case _ID:
				cout << yytext << " Identifier T_ID " << line_num << " " << source_file << " " << source_line << endl;
				break;
			case _ADD:
				cout << yytext << " Operator T_ADD " << line_num << " " << source_file << " " << source_line << endl;
				break;
			case _SUB:
				cout << yytext << " Operator T_SUB " << line_num << " " << source_file << " " << source_line << endl;
				break;
			case _MULT:
				cout << yytext << " Operator T_MULT " << line_num << " " << source_file << " " << source_line << endl;
				break;
			case _DIV:
				cout << yytext << " Operator T_DIV " << line_num << " " << source_file << " " << source_line << endl;
				break;
			case _MOD:
				cout << yytext << " Operator T_MOD " << line_num << " " << source_file << " " << source_line << endl;
				break;
			case _AND:
				cout << yytext << " Operator T_AND " << line_num << " " << source_file << " " << source_line << endl;
				break;
			case _OR:
				cout << yytext << " Operator T_OR " << line_num << " " << source_file << " " << source_line << endl;
				break;
			case _XOR:
				cout << yytext << " Operator T_XOR " << line_num << " " << source_file << " " << source_line << endl;
				break;
			case _LSHIFT:
				cout << yytext << " Operator T_LSHIFT " << line_num << " " << source_file << " " << source_line << endl;
				break;
			case _RSHIFT:
				cout << yytext << " Operator T_RSHIFT " << line_num << " " << source_file << " " << source_line << endl;
				break;
			case _ASSIGN:
				cout << yytext << " Operator T_ASSIGN " << line_num << " " << source_file << " " << source_line << endl;
				break;
			case _ADDA:
				cout << yytext << " Operator T_ADDA " << line_num << " " << source_file << " " << source_line << endl;
				break;
			case _SUBA:
				cout << yytext << " Operator T_SUBA " << line_num << " " << source_file << " " << source_line << endl;
				break;
			case _MULTA:
				cout << yytext << " Operator T_MULTA " << line_num << " " << source_file << " " << source_line << endl;
				break;
			case _DIVA:
				cout << yytext << " Operator T_DIVA " << line_num << " " << source_file << " " << source_line << endl;
				break;
			case _MODA:
				cout << yytext << " Operator T_MODA " << line_num << " " << source_file << " " << source_line << endl;
				break;
			case _ANDA:
				cout << yytext << " Operator T_ANDA " << line_num << " " << source_file << " " << source_line << endl;
				break;
			case _ORA:
				cout << yytext << " Operator T_ORA " << line_num << " " << source_file << " " << source_line << endl;
				break;
			case _XORA:
				cout << yytext << " Operator T_XORA " << line_num << " " << source_file << " " << source_line << endl;
				break;
			case _LSHIFTA:
				cout << yytext << " Operator T_LSHIFTA " << line_num << " " << source_file << " " << source_line << endl;
				break;
			case _RSHIFTA:
				cout << yytext << " Operator T_RSHIFTA " << line_num << " " << source_file << " " << source_line << endl;
				break;
			case _LAND:
				cout << yytext << " Operator T_LAND " << line_num << " " << source_file << " " << source_line << endl;
				break;
			case _LOR:
				cout << yytext << " Operator T_LOR " << line_num << " " << source_file << " " << source_line << endl;
				break;
			case _EQUAL:
				cout << yytext << " Operator T_EQUAL " << line_num << " " << source_file << " " << source_line << endl;
				break;
			case _NEQUAL:
				cout << yytext << " Operator T_NEQUAL " << line_num << " " << source_file << " " << source_line << endl;
				break;
			case _LESSEQUAL:
				cout << yytext << " Operator T_LESSEQUAL " << line_num << " " << source_file << " " << source_line << endl;
				break;
			case _GREATEQUAL:
				cout << yytext << " Operator T_GREATEQUAL " << line_num << " " << source_file << " " << source_line << endl;
				break;
			case _LESSTHAN:
				cout << yytext << " Operator T_LESSTHAN " << line_num << " " << source_file << " " << source_line << endl;
				break;
			case _GREATTHAN:
				cout << yytext << " Operator T_GREATTHAN " << line_num << " " << source_file << " " << source_line << endl;
				break;
			case _BITCOMP:
				cout << yytext << " Operator T_BITCOMP " << line_num << " " << source_file << " " << source_line << endl;
				break;
			case _COMP:
				cout << yytext << " Operator T_COMP " << line_num << " " << source_file << " " << source_line << endl;
				break;
			case _INC:
				cout << yytext << " Operator T_INC " << line_num << " " << source_file << " " << source_line << endl;
				break;
			case _DEC:
				cout << yytext << " Operator T_DEC " << line_num << " " << source_file << " " << source_line << endl;
				break;
			case _COMMA:
				cout << yytext << " Operator T_COMMA " << line_num << " " << source_file << " " << source_line << endl;
				break;
			case _CASE:
				cout << yytext << " Operator T_CASE " << line_num << " " << source_file << " " << source_line << endl;
				break;
			case _COND:
				cout << yytext << " Operator T_COND " << line_num << " " << source_file << " " << source_line << endl;
				break;
			case _SEMI:
				cout << yytext << " Operator T_SEMI " << line_num << " " << source_file << " " << source_line << endl;
				break;
			case _LPAR:
				cout << yytext << " Operator T_LPAR " << line_num << " " << source_file << " " << source_line << endl;
				break;
			case _RPAR:
				cout << yytext << " Operator T_RPAR " << line_num << " " << source_file << " " << source_line << endl;
				break;
			case _LCBRA:
				cout << yytext << " Operator T_LBRA " << line_num << " " << source_file << " " << source_line << endl;
				break;
			case _RCBRA:
				cout << yytext << " Operator T_RBRA " << line_num << " " << source_file << " " << source_line << endl;
				break;
			case _LBRAK:
				cout << yytext << " Operator T_LBRAK " << line_num << " " << source_file << " " << source_line << endl;
				break;
			case _RBRAK:
				cout << yytext << " Operator T_RBRAK " << line_num << " " << source_file << " " << source_line << endl;
				break;
			case _CDEC:
				cout << yytext << " Constant T_CDEC " << line_num << " " << source_file << " " << source_line << endl;
				break;
			case _CFP:
				cout << yytext << " Constant T_CFP " << line_num << " " << source_file << " " << source_line << endl;
				break;
			case _CHEX:
				cout << yytext << " Constant T_CHEX " << line_num << " " << source_file << " " << source_line << endl;
				break;
			case _COCT:
				cout << yytext << " Constant T_COCT " << line_num << " " << source_file << " " << source_line << endl;
				break;
			case _STR:
				cout << yytext << " StringLiteral T_STR " << line_num << " " << source_file << " " << source_line << endl;
				break;
			case _NEWLINE:
				line_num++;
				source_line++;
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
				source_line = strtol(num.c_str(), NULL, 10);
				source_line--;
			}
				break;
			default:
				cout << yytext << " invalid T_INVALID " << line_num << " " << source_file << " " << source_line << endl;
				break;
		}

		ttcode = yylex();
	}

	return 0;
}
