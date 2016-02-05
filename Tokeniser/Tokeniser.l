%option noyywrap
%{
#include <iostream>
int line_num = 1;
%}

DIGIT		[0-9]
LETTER		[a-zA-Z_]
CHAR		({DIGIT}|{LETTER})	

%%
auto				 std::cout << yytext << " keyword AUTO " << line_num << std::endl;
break				 std::cout << yytext << " keyword BREAK " << line_num << std::endl;
case				 std::cout << yytext << " keyword CASE " << line_num << std::endl;
char				 std::cout << yytext << " keyword CHAR " << line_num << std::endl;
const				 std::cout << yytext << " keyword CONST " << line_num << std::endl;
continue			 std::cout << yytext << " keyword CONTINUE " << line_num << std::endl;
default				 std::cout << yytext << " keyword DEFAULT " << line_num << std::endl;
do					 std::cout << yytext << " keyword DO " << line_num << std::endl;
double				 std::cout << yytext << " keyword DOUBLE " << line_num << std::endl;
else				 std::cout << yytext << " keyword ELSE " << line_num << std::endl;
enum				 std::cout << yytext << " keyword ENUM " << line_num << std::endl;
extern				 std::cout << yytext << " keyword EXTERN " << line_num << std::endl;
float				 std::cout << yytext << " keyword FLOAT " << line_num << std::endl;
for					 std::cout << yytext << " keyword FOR " << line_num << std::endl;
goto				 std::cout << yytext << " keyword GOTO " << line_num << std::endl;
if					 std::cout << yytext << " keyword IF " << line_num << std::endl;
int					 std::cout << yytext << " keyword INT " << line_num << std::endl;
long				 std::cout << yytext << " keyword LONG " << line_num << std::endl;
register			 std::cout << yytext << " keyword REGISTER " << line_num << std::endl;
return				 std::cout << yytext << " keyword RETURN " << line_num << std::endl;
short				 std::cout << yytext << " keyword SHORT " << line_num << std::endl;
signed				 std::cout << yytext << " keyword SIGNED " << line_num << std::endl;
sizeof				 std::cout << yytext << " keyword SIZEOF " << line_num << std::endl;
static				 std::cout << yytext << " keyword STATIC " << line_num << std::endl;
struct				 std::cout << yytext << " keyword STRUCT " << line_num << std::endl;
switch				 std::cout << yytext << " keyword SWITCH " << line_num << std::endl;
typedef				 std::cout << yytext << " keyword TYPEDEF " << line_num << std::endl;
union				 std::cout << yytext << " keyword UNION " << line_num << std::endl;
unsigned			 std::cout << yytext << " keyword UNSIGNED " << line_num << std::endl;
void				 std::cout << yytext << " keyword VOID " << line_num << std::endl;
volatile			 std::cout << yytext << " keyword VOLATILE " << line_num << std::endl;
while				 std::cout << yytext << " keyword WHILE " << line_num << std::endl;

{LETTER}{CHAR}*		std::cout << yytext << " identifier ID " << line_num << std::endl;

\+					std::cout << yytext << " operator ADD " << line_num << std::endl;
-					std::cout << yytext << " operator SUB " << line_num << std::endl;
\*					std::cout << yytext << " operator MULT " << line_num << std::endl;
\/					std::cout << yytext << " operator DIV " << line_num << std::endl;
%					std::cout << yytext << " operator MOD " << line_num << std::endl;

&					std::cout << yytext << " operator AND " << line_num << std::endl;
\|					std::cout << yytext << " operator OR " << line_num << std::endl;
\^					std::cout << yytext << " operator XOR " << line_num << std::endl;
\<\<				std::cout << yytext << " operator LSHIFT " << line_num << std::endl;
>>					std::cout << yytext << " operator RSHIFT " << line_num << std::endl;

=					std::cout << yytext << " operator ASSIGN " << line_num << std::endl;
\+=					std::cout << yytext << " operator ADDA " << line_num << std::endl;
-=					std::cout << yytext << " operator SUBA " << line_num << std::endl;
\*=					std::cout << yytext << " operator MULTA " << line_num << std::endl;
\/=					std::cout << yytext << " operator DIVA " << line_num << std::endl;
%=					std::cout << yytext << " operator MODA " << line_num << std::endl;
&=					std::cout << yytext << " operator ANDA " << line_num << std::endl;
\|=					std::cout << yytext << " operator ORA " << line_num << std::endl;
\^=					std::cout << yytext << " operator XORA " << line_num << std::endl;
\<\<=				std::cout << yytext << " operator LSHIFTA " << line_num << std::endl;
>>=					std::cout << yytext << " operator RSHIFTA " << line_num << std::endl;

&&					std::cout << yytext << " operator LAND " << line_num << std::endl;
\|\|				std::cout << yytext << " operator LOR " << line_num << std::endl;
==					std::cout << yytext << " operator EQUAL " << line_num << std::endl;
!=					std::cout << yytext << " operator NEQUAL " << line_num << std::endl;
\<=					std::cout << yytext << " operator LESSEQUAL " << line_num << std::endl;
>=					std::cout << yytext << " operator GREATEQUAL " << line_num << std::endl;
\<					std::cout << yytext << " operator LESSTHAN " << line_num << std::endl;
>					std::cout << yytext << " operator GREATTHAN " << line_num << std::endl;

~					std::cout << yytext << " operator BITCOMP " << line_num << std::endl;
!					std::cout << yytext << " operator COMP " << line_num << std::endl;
\+\+				std::cout << yytext << " operator INC " << line_num << std::endl;
--					std::cout << yytext << " operator DEC " << line_num << std::endl;

,					std::cout << yytext << " operator COMMA " << line_num << std::endl;
:					std::cout << yytext << " operator CASE " << line_num << std::endl;
\?					std::cout << yytext << " operator COND " << line_num << std::endl;
;					std::cout << yytext << " operator SEMI " << line_num << std::endl;

\(					std::cout << yytext << " operator LPAR " << line_num << std::endl;
\)					std::cout << yytext << " operator RPAR " << line_num << std::endl;
\{					std::cout << yytext << " operator LCBRA " << line_num << std::endl;
\}					std::cout << yytext << " operator RCBRA " << line_num << std::endl;
\[					std::cout << yytext << " operator LBRAK " << line_num << std::endl;
\]					std::cout << yytext << " operator RBRAK " << line_num << std::endl;


{DIGIT}+			std::cout << yytext << " constant C " << line_num << std::endl;

\".+\"				std::cout << yytext << " stringliteral STR " << line_num << std::endl;

\n					line_num++;
\t
[ ]

%%

int main()
{
	yylex();
}