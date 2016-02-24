%option noyywrap
%{
#include <cstdlib>
#include "tokens.tab.hpp"
%}

DIGIT		[0-9]
OCT			[0-7]
HEX			[0-9a-fA-F]
LETTER		[a-zA-Z_]
CHAR		[0-9a-zA-Z_]
ESCCHAR		(\\\?|\\\\|\\'|\\\"|\\a|\\b|\\f|\\n|\\r|\\t|\\v|\\{OCT}{OCT}?{OCT}?|\\x{HEX}+)
STRING		\"([^\n\"\\]|{ESCCHAR})*\"
S			(([uU][lL]?)|([lL][uU]?))?

FLOAT1		(([0-9]*\.[0-9]+)|([0-9]+\.[0-9]*))[fFlL]?
FLOAT2		[0-9]+[eE][+-]?[0-9]+[fFlL]?
FLOAT3		(([0-9]*\.[0-9]+)|([0-9]+\.[0-9]*))[eE][+-]?[0-9]+[fFlL]?

CCHAR		'([^\n'\\]|{ESCCHAR})+'

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

{LETTER}{CHAR}*	{ yylval.str=yytext; return _ID;}


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

[1-9]{DIGIT}*{S}			{ yylval.integer=atoi(yytext); return _CNUM; }
({FLOAT1}|{FLOAT2}|{FLOAT3})	return _CFP;
0[xX]{HEX}+{S}				{ yylval.integer=strtol(yytext, NULL, 16); return _CNUM; }
0{OCT}*{S}					{ yylval.integer=strtol(yytext, NULL, 8); return _CNUM; }
[L]?{CCHAR}						return _CCHAR;


[L]?{STRING}		return _STR;


\n				return _NEWLINE;
\t
[ ]
{SOURCE}		return _PREP;

%%

