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
    BEGIN_ = 260,
    CASE = 261,
    CONST = 262,
    DO = 263,
    DOWNTO = 264,
    OR = 265,
    ELSE = 266,
    END = 267,
    FOR = 268,
    FUNCTION = 269,
    GOTO = 270,
    IF = 271,
    NOT = 272,
    OF = 273,
    PROGRAM = 274,
    PROCEDURE = 275,
    READ = 276,
    RECORD = 277,
    REPEAT = 278,
    THEN = 279,
    TO = 280,
    TYPE = 281,
    UNTIL = 282,
    VAR = 283,
    WHILE = 284,
    WRITE = 285,
    XOR = 286,
    TYPE_INTEGER = 287,
    TYPE_REAL = 288,
    TYPE_STRING = 289,
    TYPE_CHAR = 290,
    NEWLINE = 291,
    PLUS = 292,
    MINUS = 293,
    MULTIPLY = 294,
    DIVIDE = 295,
    MOD = 296,
    LT = 297,
    LE = 298,
    EQUAL = 299,
    UNEQUAL = 300,
    GE = 301,
    GT = 302,
    DOT = 303,
    DOTDOT = 304,
    COMMA = 305,
    SEMICOLON = 306,
    COLON = 307,
    ASSIGN = 308,
    LB = 309,
    RB = 310,
    LP = 311,
    RP = 312,
    INTEGER = 313,
    REAL = 314,
    CHAR = 315,
    STRING = 316,
    ID = 317
  };
#endif
/* Tokens.  */
#define AND 258
#define ARRAY 259
#define BEGIN_ 260
#define CASE 261
#define CONST 262
#define DO 263
#define DOWNTO 264
#define OR 265
#define ELSE 266
#define END 267
#define FOR 268
#define FUNCTION 269
#define GOTO 270
#define IF 271
#define NOT 272
#define OF 273
#define PROGRAM 274
#define PROCEDURE 275
#define READ 276
#define RECORD 277
#define REPEAT 278
#define THEN 279
#define TO 280
#define TYPE 281
#define UNTIL 282
#define VAR 283
#define WHILE 284
#define WRITE 285
#define XOR 286
#define TYPE_INTEGER 287
#define TYPE_REAL 288
#define TYPE_STRING 289
#define TYPE_CHAR 290
#define NEWLINE 291
#define PLUS 292
#define MINUS 293
#define MULTIPLY 294
#define DIVIDE 295
#define MOD 296
#define LT 297
#define LE 298
#define EQUAL 299
#define UNEQUAL 300
#define GE 301
#define GT 302
#define DOT 303
#define DOTDOT 304
#define COMMA 305
#define SEMICOLON 306
#define COLON 307
#define ASSIGN 308
#define LB 309
#define RB 310
#define LP 311
#define RP 312
#define INTEGER 313
#define REAL 314
#define CHAR 315
#define STRING 316
#define ID 317

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_HPP_INCLUDED  */
