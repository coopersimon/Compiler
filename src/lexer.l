%option noyywrap
%{
#include <cstdlib>
#include "ast.hpp"
#include "parser.tab.hpp"
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

COMMENT		\/\*(.|[\n])*\*\/

SOURCE		#[ ]{DIGIT}+[ ]{STRING}([ ]1)?([ ]2)?([ ]3)?([ ]4)?

%%
auto			return _AUTO;
break			return _BREAK;
case			return _CASE;
const			return _CONST;
continue		return _CONTINUE;
default			return _DEFAULT;
do				return _DO;
double			return _DOUBLE;
else			return _ELSE;
enum			return _ENUM;
extern			return _EXTERN;
for				return _FOR;
goto			return _GOTO;
if				return _IF;
register		return _REGISTER;
return			return _RETURN;
static			return _STATIC;
struct			return _STRUCT;
switch			return _SWITCH;
typedef			return _TYPEDEF;
union			return _UNION;
volatile		return _VOLATILE;
while			return _WHILE;

sizeof			return _SIZEOF;

void			return _VOID;

int			return _LONGINT;
signed			return _LONGINT;
signed[ ]int		return _LONGINT;
long			return _LONGINT;
long[ ]int		return _LONGINT;
signed[ ]long		return _LONGINT;
signed[ ]long[ ]int	return _LONGINT;

unsigned		return _LONGINTU;
unsigned[ ]int		return _LONGINTU;
unsigned[ ]long		return _LONGINTU;
unsigned[ ]long[ ]int	return _LONGINTU;

short			return _SHORTINT;
short[ ]int		return _SHORTINT;
signed[ ]short		return _SHORTINT;
signed[ ]short[ ]int	return _SHORTINT;

unsigned[ ]short	return _SHORTINTU;
unsigned[ ]short[ ]int	return _SHORTINTU;

signed[ ]char		return _CHAR;
char			return _CHAR;

unsigned[ ]char		return _CHARU;

float			return _FLOAT;

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
:				return _COLON;
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
({FLOAT1}|{FLOAT2}|{FLOAT3})	{ yylval.fp=atof(yytext); return _CFP; }
0[xX]{HEX}+{S}				{ yylval.integer=strtol(yytext, NULL, 16); return _CNUM; }
0{OCT}*{S}					{ yylval.integer=strtol(yytext, NULL, 8); return _CNUM; }
[L]?{CCHAR}						return _CCHAR;


[L]?{STRING}		{ yylval.str=yytext; return _STR; }


\n
\t
[ ]
{COMMENT}	
{SOURCE}		return _PREP;

%%

