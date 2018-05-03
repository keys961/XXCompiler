/*yytext: current token text*/
%{
#include <cstdio>
#include <cstring>
#include <string>
#include "lexer.h"
#include "parser.hpp"
extern GlobalInfo globalInfo; /*Global trace info*/
extern FILE* in;
extern FILE* out;
%}
/* Lex Definitions */
digit[0-9]
digits [0-9]+
letter [A-Za-z]

integer {digits}
real ({digits}"."[0-9]*)|([0-9]*"."{digits})

string \'[^']\' 
char \'[.]\'
newline \n
whitespace [ \t]+
id ({letter}|_)+({letter}|{digit}|_)*

%%

"and" { return AND; } /*Key Words*/
"array" { return ARRAY; }
"begin" { return BEGIN; }
"case" { return CASE; }
"const" { return CONST; }
"do" { return DO; }
"downto" { return DOWNTO; }
"or" { return OR; }
"else" { return ELSE; }
"end" { return END; }
"for" { return FOR; }
"function" { return FUNCTION; }
"goto" { return GOTO; }
"if" { return IF; }
"not" { return NOT; }
"of" { return OF; }
"program" { return PROGRAM; }
"procedure" { return PROCEDURE; }
"read" { return READ; }
"record" { return RECORD; }
"repeat" { return REPEAT; }
"then" { return THEN; }
"to" { return TO; }
"type" { return TYPE; }
"until" { return UNTIL; }
"var" { return VAR; }
"while" { return WHILE; }
"write" { return WRITE; }
"xor" { return XOR; }
"integer" { return TYPE_INTEGER; }
"real" { return TYPE_REAL; }
"string" { return TYPE_STRING; }
"char" { return TYPE_CHAR; }

"+" { return PLUS; } /*Operations*/
"-" { return MINUS; }
"*" { return MULTIPLY; }
"/" { return DIVIDE; }
"%" { return MOD; }
"<" { return LT; }
"<=" { return LE; }
"=" { return EQUAL; }
"!=" { return UNEQUAL; }
">=" { return GE; }
">" { return GT; }

"." { return DOT; } /*Other signs*/
".." { return DOTDOT; }
"," { return COMMA; }
";" { return SEMICOLON; }
":" { return COLON; }
":=" { return ASSIGN; }
"[" { return LB; } /*Brackets*/ 
"]" { return RB; }
"(" { return LP; } /*Parentheses*/
")" { return RP; }

{integer} { return INTEGER; }
{real} { return REAL; }
{char} { return CHAR; }
{string} { return STRING; }

{whitespace} {}
{newline} { globalInfo.currentLineCount++; }
{id} { return ID; }

%%

int getCurrentToken() 
{
	static int flag = 1;
	if(flag)
	{
		yyin = in;
		yyout = out;
		flag = 0;
	}

	return saveTraceInfo();
}

int saveTraceInfo()
{
	int currentTokenType = yylex();
	globalInfo.currentToken = yytext;
	fprintf(yyout, "%d: %s\n", globalInfo.currentLineCount,
			yytext);
	return currentTokenType;
}

int yywrap()
{
	return 1;
}