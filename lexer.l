/*yytext: current token text*/
%{
#define YYSTYPE TreeNode*
#include <cstdio>
#include <cstring>
#include <string>
#include "lexer.h"
#include "tree.h"
#include "parser.hpp"


class GlobalInfo;

extern GlobalInfo globalInfo; /*Global trace info*/
extern FILE* codeIn;
extern FILE* lexerOut; /* Lexer out */

std::string lexicalTypeStr[] = {
        "AND = 258",
        "ARRAY = 259",
        "BEGIN_ = 260",
        "CASE = 261",
        "CONST = 262",
        "DO = 263",
        "DOWNTO = 264",
        "OR = 265",
        "ELSE = 266",
        "END = 267",
        "FOR = 268",
        "FUNCTION = 269",
        "GOTO = 270",
        "IF = 271",
        "NOT = 272",
        "OF = 273",
        "PROGRAM = 274",
        "PROCEDURE = 275",
        "READ = 276",
        "RECORD = 277",
        "REPEAT = 278",
        "THEN = 279",
        "TO = 280",
        "TYPE = 281",
        "UNTIL = 282",
        "VAR = 283",
        "WHILE = 284",
        "WRITE = 285",
        "XOR = 286",
        "TYPE_INTEGER = 287",
        "TYPE_REAL = 288",
        "TYPE_STRING = 289",
        "TYPE_CHAR = 290",
        "NEWLINE = 291",
        "PLUS = 292",
        "MINUS = 293",
        "MULTIPLY = 294",
        "DIVIDE = 295",
        "MOD = 296",
        "LT = 297",
        "LE = 298",
        "EQUAL = 299",
        "UNEQUAL = 300",
        "GE = 301",
        "GT = 302",
        "DOT = 303",
        "DOTDOT = 304",
        "COMMA = 305",
        "SEMICOLON = 306",
        "COLON = 307",
        "ASSIGN = 308",
        "LB = 309",
        "RB = 310",
        "LP = 311",
        "RP = 312",
        "INTEGER = 313",
        "REAL = 314",
        "CHAR = 315",
        "STRING = 316",
        "ID = 317"
};

%}
/* Lex Definitions */
digit[0-9]
digits [0-9]+
letter [A-Za-z]

integer {digits}
real {digits}"."{digits}

string \'[^']\' 
char \'[.]\'
newline \n
whitespace [ \t]+
id ({letter}|_)+({letter}|{digit}|_)*

%%

"and" { return AND; } /*Key Words*/
"array" { return ARRAY; }
"begin" { return BEGIN_; }
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
{newline} { globalInfo.currentLineIndex++; globalInfo.currentTokenIndex = 0; }
{id} { TreeNode* t = new TreeNode();
        t->setName(yytext);
        yylval = t;
        return ID; }

%%

int getCurrentToken() 
{
	static int flag = 1;
	if(flag)
	{
		yyin = codeIn;
		flag = 0;
	}

	return saveTraceInfo();
}

int saveTraceInfo()
{
	int type = yylex();
	globalInfo.currentToken = yytext;
	if(globalInfo.currentToken == "\n")
	{
		globalInfo.currentLineIndex++;
		globalInfo.currentTokenIndex = 0;
	}
	else 
	{
		globalInfo.currentTokenIndex++;
		if(type >= 258)
		    fprintf(lexerOut, "%ld:%ld - Token: `%s` with type %s\n",
			    globalInfo.currentLineIndex, globalInfo.currentTokenIndex, yytext,
			    lexicalTypeStr[type - 258].c_str());
	}
	return type;
}

int yywrap()
{
	return 1;
}