/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_PARSER_HPP_INCLUDED
# define YY_YY_PARSER_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    AND = 258,
    ARRAY = 259,
    ASSIGN = 260,
    BEGIN = 261,
    CASE = 262,
    CHAR = 263,
    COLON = 264,
    COMMA = 265,
    CONST = 266,
    DIV = 267,
    DO = 268,
    PROCEDURE = 269,
    DOT = 270,
    DOTDOT = 271,
    DOWNTO = 272,
    OR = 273,
    ELSE = 274,
    END = 275,
    EQUAL = 276,
    FOR = 277,
    FUNCTION = 278,
    GE = 279,
    GOTO = 280,
    GT = 281,
    ID = 282,
    IF = 283,
    INTEGER = 284,
    LB = 285,
    LE = 286,
    LP = 287,
    LT = 288,
    MINUS = 289,
    MOD = 290,
    MUL = 291,
    NOT = 292,
    OF = 293,
    PLUS = 294,
    PROGRAM = 295,
    RB = 296,
    READ = 297,
    REAL = 298,
    RECORD = 299,
    REPEAT = 300,
    RP = 301,
    SEMI = 302,
    STRING = 303,
    THEN = 304,
    TO = 305,
    TYPE = 306,
    UNEQUAL = 307,
    UNTIL = 308,
    VAR = 309,
    WHILE = 310,
    WRITE = 311
  };
#endif
/* Tokens.  */
#define AND 258
#define ARRAY 259
#define ASSIGN 260
#define BEGIN 261
#define CASE 262
#define CHAR 263
#define COLON 264
#define COMMA 265
#define CONST 266
#define DIV 267
#define DO 268
#define PROCEDURE 269
#define DOT 270
#define DOTDOT 271
#define DOWNTO 272
#define OR 273
#define ELSE 274
#define END 275
#define EQUAL 276
#define FOR 277
#define FUNCTION 278
#define GE 279
#define GOTO 280
#define GT 281
#define ID 282
#define IF 283
#define INTEGER 284
#define LB 285
#define LE 286
#define LP 287
#define LT 288
#define MINUS 289
#define MOD 290
#define MUL 291
#define NOT 292
#define OF 293
#define PLUS 294
#define PROGRAM 295
#define RB 296
#define READ 297
#define REAL 298
#define RECORD 299
#define REPEAT 300
#define RP 301
#define SEMI 302
#define STRING 303
#define THEN 304
#define TO 305
#define TYPE 306
#define UNEQUAL 307
#define UNTIL 308
#define VAR 309
#define WHILE 310
#define WRITE 311

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_HPP_INCLUDED  */
