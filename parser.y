%{
//#define YYSTYPE int
#include <cstdio>
#include <cstdlib>
extern char* yytext;
int yylex(void);
int yyerror(const char *);
%}
%token AND ARRAY BEGIN_ CASE CONST DO DOWNTO OR ELSE END
%token FOR FUNCTION GOTO IF NOT OF PROGRAM PROCEDURE READ RECORD
%token REPEAT THEN TO TYPE UNTIL VAR WHILE WRITE XOR TYPE_INTEGER
%token TYPE_REAL TYPE_STRING TYPE_CHAR NEWLINE
%token PLUS MINUS MULTIPLY DIVIDE MOD LT LE EQUAL UNEQUAL GE GT
%token DOT DOTDOT COMMA SEMICOLON COLON ASSIGN LB RB LP RP
%token INTEGER REAL CHAR STRING
%token ID
%%
input:
    | input line
    ;
line : NEWLINE 
    | expr NEWLINE { printf("Value = %d.\n", $1); }
    ;
expr : expr PLUS term { $$ = $1 + $3; printf("%d\t", $$); }
    | expr MINUS term { $$ = $1 - $3; }
    | term { $$ = $1; printf("in expr %d\n", $$);}
    ;
term : term MULTIPLY factor { $$ = $1 * $3; }
    | term DIVIDE factor { $$ = $1 / $3; }
    | factor { $$ = $1; }
    ;
factor : LP expr RP { $$ = $2; }
    | INTEGER { $$ = atoi(yytext); }
    ;
%%

int yyerror(const char* str)
{
    printf("%s\n", str);
    return 1;
}

int yywrap()
{
    return 1;
}

int main()
{
    yyparse();
    return 0;
}