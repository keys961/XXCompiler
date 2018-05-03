%{
#include <cstdio>
#include <cstdlib>
#include "lexer.h"
#include "parser.hpp"
%}
%token AND  ARRAY  ASSIGN  BEGIN  CASE CHAR COLON COMMA CONST DIV DO PROCEDURE
%token DOT DOTDOT DOWNTO OR ELSE END EQUAL FOR FUNCTION GE GOTO GT ID
%token IF INTEGER LB LE LP LT MINUS MOD MUL NOT OF PLUS PROGRAM RB 
%token READ REAL RECORD REPEAT RP SEMI STRING THEN TO TYPE UNEQUAL UNTIL VAR WHILE WRITE
%%
factor : ID 
%%

int yyerror(const char* str)
{
    return 1;
}