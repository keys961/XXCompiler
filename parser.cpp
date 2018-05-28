/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "parser.y" /* yacc.c:339  */

#define YYSTYPE TreeNode*
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <queue>
#include <string>
#include "tree.h"
#include "lexer.h"

class GlobalInfo;

extern char* yytext; // yytext
extern GlobalInfo globalInfo; // global info
extern std::ofstream grammarOut;
std::queue<int> intQueue; //store int values
std::queue<double> doubleQueue; //store double values
std::queue<std::string> stringQueue; //store string values
static int yylex(void);
static int hashCodeForString(const std::string& str);
static void showNodeInfo(const std::string& info);
int yyerror(const char *);

extern TreeNode* root;

#line 92 "parser.cpp" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "parser.hpp".  */
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

/* Copy the second part of user declarations.  */

#line 267 "parser.cpp" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   279

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  63
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  68
/* YYNRULES -- Number of rules.  */
#define YYNRULES  133
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  249

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   317

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    37,    37,    47,    54,    64,    74,    87,    92,    98,
     104,   112,   112,   122,   127,   132,   137,   144,   149,   155,
     161,   169,   169,   177,   182,   187,   192,   198,   203,   208,
     213,   218,   223,   229,   235,   240,   247,   253,   261,   261,
     270,   275,   281,   287,   295,   295,   304,   310,   317,   323,
     328,   334,   334,   342,   342,   350,   355,   362,   368,   376,
     376,   385,   393,   399,   405,   413,   419,   428,   436,   442,
     447,   452,   457,   462,   467,   472,   477,   482,   489,   495,
     500,   500,   507,   507,   507,   518,   527,   534,   534,   542,
     550,   555,   562,   569,   569,   581,   587,   595,   602,   608,
     614,   622,   629,   640,   645,   650,   655,   660,   665,   670,
     676,   681,   686,   691,   696,   702,   707,   712,   717,   722,
     728,   734,   734,   743,   743,   751,   751,   751,   761,   766,
     771,   777,   784,   790
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "AND", "ARRAY", "BEGIN_", "CASE",
  "CONST", "DO", "DOWNTO", "OR", "ELSE", "END", "FOR", "FUNCTION", "GOTO",
  "IF", "NOT", "OF", "PROGRAM", "PROCEDURE", "READ", "RECORD", "REPEAT",
  "THEN", "TO", "TYPE", "UNTIL", "VAR", "WHILE", "WRITE", "XOR",
  "TYPE_INTEGER", "TYPE_REAL", "TYPE_STRING", "TYPE_CHAR", "NEWLINE",
  "PLUS", "MINUS", "MULTIPLY", "DIVIDE", "MOD", "LT", "LE", "EQUAL",
  "UNEQUAL", "GE", "GT", "DOT", "DOTDOT", "COMMA", "SEMICOLON", "COLON",
  "ASSIGN", "LB", "RB", "LP", "RP", "INTEGER", "REAL", "CHAR", "STRING",
  "ID", "$accept", "program", "program_head", "block", "id_list",
  "constant_definition_part", "constant_list", "constant_definition",
  "$@1", "constant_value", "type_definition_part", "type_definition_list",
  "type_definition", "$@2", "type_denoter", "simple_type", "range_type",
  "array_type", "record_type", "field_definition_list", "field_definition",
  "$@3", "variable_declaration_part", "variable_declaration_list",
  "variable_declaration", "$@4", "procedure_function_declaration_part",
  "procedure_function_declaration", "procedure_declaration", "$@5",
  "function_declaration", "$@6", "parameters", "parameter_list",
  "parameter", "$@7", "block_body_part", "compound_statement",
  "statememt_list", "label", "statememt", "stmt", "assign_statememt",
  "variable_access", "$@8", "$@9", "$@10", "procedure_statement", "$@11",
  "if_statememt", "repeat_statememt", "for_statememt", "$@12", "direction",
  "while_statememt", "case_statememt", "case_list", "case_item",
  "goto_statememt", "expression", "expr", "term", "factor", "$@13", "$@14",
  "$@15", "$@16", "args", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317
};
# endif

#define YYPACT_NINF -139

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-139)))

#define YYTABLE_NINF -126

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       8,   -16,    43,    -2,  -139,  -139,    52,    17,    33,    56,
    -139,    17,  -139,  -139,    32,    67,    65,  -139,  -139,    32,
    -139,    37,    64,   186,    68,  -139,  -139,    66,  -139,    57,
      63,   137,  -139,  -139,  -139,  -139,  -139,  -139,  -139,    75,
      29,   103,    37,  -139,  -139,     5,  -139,  -139,  -139,  -139,
      73,    79,  -139,  -139,  -139,  -139,    92,  -139,   107,   109,
    -139,  -139,  -139,  -139,    29,  -139,   105,   105,    12,    96,
     113,    12,   132,     5,    12,   133,  -139,   142,  -139,    -3,
     141,   143,  -139,  -139,   139,  -139,  -139,  -139,  -139,  -139,
    -139,  -139,   186,  -139,    25,  -139,  -139,   -27,   186,  -139,
    -139,   -17,   147,   149,    12,    12,    12,   -32,  -139,   102,
      55,    99,  -139,  -139,  -139,   126,    12,   -19,    11,    12,
     162,   153,   159,  -139,     5,   100,  -139,    12,   164,   165,
    -139,    79,   158,  -139,  -139,  -139,  -139,   -26,  -139,   -20,
      52,  -139,  -139,   140,   179,   183,   173,   186,    12,    12,
      12,    12,    12,    12,    12,    12,    12,    12,    12,    12,
      12,    12,   199,     5,   196,    12,     5,   161,    12,   192,
      12,  -139,  -139,   187,   237,    29,  -139,  -139,   204,   195,
    -139,   207,   208,  -139,    12,    12,   198,   209,    26,  -139,
      55,    55,    55,    55,    55,    55,    99,    99,    99,    99,
    -139,  -139,  -139,  -139,    12,   251,  -139,   187,  -139,  -139,
     167,  -139,   187,    46,    29,  -139,   -20,  -139,    52,  -139,
      50,   181,  -139,     5,  -139,   186,   134,     5,  -139,  -139,
      12,  -139,  -139,  -139,   212,  -139,  -139,  -139,  -139,  -139,
    -139,  -139,    12,  -139,   187,  -139,    89,     5,  -139
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     3,     1,     8,     0,     0,    18,
      11,     7,    10,     2,     0,    41,     0,     9,    21,    17,
      20,     0,    48,     0,     0,    19,    44,     0,    43,     0,
       0,     0,    47,    49,    50,    13,    14,    15,    16,     0,
       0,     0,    40,    53,    51,    65,    46,     4,    61,    12,
       0,     0,    27,    29,    30,    28,     0,    31,     0,     0,
      23,    24,    25,    26,     0,    42,     0,     0,     0,     0,
       0,     0,     0,    65,     0,     0,    66,    89,    77,     0,
       0,     0,    68,    69,     0,    70,    71,    72,    73,    74,
      75,    76,     0,    38,     0,    37,     6,     0,     0,    22,
      45,     0,     0,     0,     0,     0,     0,   120,   128,     0,
     109,   114,   119,    93,   102,     0,     0,     0,     0,     0,
       0,     0,     0,    62,     0,     0,    64,     0,     0,     0,
      35,     0,     0,    32,    33,    56,    59,     0,    58,     0,
       8,   131,   130,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    63,    67,    78,     0,     0,    36,     5,     0,     0,
      55,     0,     0,   129,     0,     0,     0,     0,     0,   100,
     103,   104,   105,   108,   106,   107,   112,   113,   110,   111,
     118,   115,   116,   117,     0,    91,    85,    92,    97,    86,
       0,    83,   133,     0,     0,    39,     0,    57,     8,    52,
       0,     0,   126,     0,    98,     0,     0,     0,    81,    84,
       0,    88,    34,    60,     0,   122,   124,   127,   101,    99,
      96,    95,     0,    90,   132,    54,     0,     0,    94
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -139,  -139,  -139,  -138,  -139,  -139,  -139,   253,  -139,   -23,
    -139,  -139,   246,  -139,   -61,  -133,   174,  -139,  -139,  -139,
     136,  -139,  -139,  -139,   226,  -139,  -139,   238,  -139,  -139,
    -139,  -139,   203,  -139,    93,  -139,  -139,   240,   200,   205,
    -119,   151,  -139,  -139,  -139,  -139,  -139,  -139,  -139,  -139,
    -139,  -139,  -139,  -139,  -139,  -139,  -139,    49,  -139,   -67,
      90,    94,     6,  -139,  -139,  -139,  -139,    95
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     8,    97,     9,    11,    12,    16,   108,
      15,    19,    20,    24,    59,    60,    61,    62,    63,    94,
      95,   129,    22,    27,    28,    41,    31,    32,    33,    67,
      34,    66,   102,   137,   138,   178,    47,    78,    79,    80,
      81,    82,    83,    84,   120,   121,   229,    85,   122,    86,
      87,    88,   162,   242,    89,    90,   188,   189,    91,   212,
     110,   111,   112,   144,   145,   146,   237,   213
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      39,   109,   182,   100,   115,   171,   181,   118,   165,   123,
      45,    68,    52,    53,    54,    55,  -125,    58,    69,   166,
      70,    71,  -123,   132,  -121,   179,    72,     1,    73,   104,
     133,   180,   124,    50,    74,    75,    56,   130,   224,   143,
     135,    58,    57,     5,   205,   136,     4,   208,   124,     6,
     105,    51,   167,   148,   149,   150,   151,   152,   153,     7,
     173,    52,    53,    54,    55,   154,    76,    77,   106,    58,
      35,    36,    37,    38,   107,   134,   131,   225,    29,    10,
     234,    13,    14,   233,    30,    56,   155,    35,    36,    37,
      38,    57,   156,   157,    18,    21,   230,   247,   207,    26,
     230,   210,   158,   231,   238,    45,    68,   235,   243,    23,
     141,   142,    40,    69,   215,    70,    71,    42,   221,    43,
     147,    72,   164,    73,   187,    44,    49,    92,   248,    74,
      75,   148,   149,   150,   151,   152,   153,   226,   159,   160,
     161,    93,    45,   240,   148,   149,   150,   151,   152,   153,
     163,    29,    58,   232,    96,    64,    98,    30,   113,   241,
      99,   101,    77,   244,   200,   201,   202,   203,   148,   149,
     150,   151,   152,   153,    76,   246,   148,   149,   150,   151,
     152,   153,   148,   149,   150,   151,   152,   153,   116,   119,
     -82,    58,   127,   125,   126,   -79,   -80,   183,   -87,   139,
     140,   169,   187,   148,   149,   150,   151,   152,   153,   148,
     149,   150,   151,   152,   153,   170,   168,   175,   209,   174,
     177,   186,   228,   148,   149,   150,   151,   152,   153,   148,
     149,   150,   151,   152,   153,   184,   236,   185,   190,   191,
     192,   193,   194,   195,    35,    36,    37,    38,   196,   197,
     198,   199,   204,   206,   211,   214,   216,   136,   218,   219,
     222,   223,   227,   245,    17,    25,   128,   176,    65,    46,
     103,    48,   217,   117,   239,   114,   172,     0,     0,   220
};

static const yytype_int16 yycheck[] =
{
      23,    68,   140,    64,    71,   124,   139,    74,    27,    12,
       5,     6,    32,    33,    34,    35,    48,    40,    13,     8,
      15,    16,    54,    50,    56,    51,    21,    19,    23,    17,
      57,    57,    51,     4,    29,    30,    56,    12,    12,   106,
      57,    64,    62,     0,   163,    62,    62,   166,    51,    51,
      38,    22,   119,    42,    43,    44,    45,    46,    47,     7,
     127,    32,    33,    34,    35,    10,    61,    62,    56,    92,
      58,    59,    60,    61,    62,    98,    51,    51,    14,    62,
     218,    48,    26,   216,    20,    56,    31,    58,    59,    60,
      61,    62,    37,    38,    62,    28,    50,     8,   165,    62,
      50,   168,     3,    57,   223,     5,     6,    57,   227,    44,
     104,   105,    44,    13,   175,    15,    16,    51,   185,    62,
      18,    21,   116,    23,   147,    62,    51,    54,   247,    29,
      30,    42,    43,    44,    45,    46,    47,   204,    39,    40,
      41,    62,     5,     9,    42,    43,    44,    45,    46,    47,
      24,    14,   175,   214,    62,    52,    49,    20,    62,    25,
      51,    56,    62,   230,   158,   159,   160,   161,    42,    43,
      44,    45,    46,    47,    61,   242,    42,    43,    44,    45,
      46,    47,    42,    43,    44,    45,    46,    47,    56,    56,
      48,   214,    53,    52,    51,    53,    54,    57,    56,    52,
      51,    48,   225,    42,    43,    44,    45,    46,    47,    42,
      43,    44,    45,    46,    47,    56,    54,    52,    57,    55,
      62,    48,    55,    42,    43,    44,    45,    46,    47,    42,
      43,    44,    45,    46,    47,    56,    55,    54,   148,   149,
     150,   151,   152,   153,    58,    59,    60,    61,   154,   155,
     156,   157,    53,    57,    62,    18,    52,    62,    51,    51,
      62,    52,    11,    51,    11,    19,    92,   131,    42,    31,
      67,    31,   179,    73,   225,    70,   125,    -1,    -1,   184
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    19,    64,    65,    62,     0,    51,     7,    66,    68,
      62,    69,    70,    48,    26,    73,    71,    70,    62,    74,
      75,    28,    85,    44,    76,    75,    62,    86,    87,    14,
      20,    89,    90,    91,    93,    58,    59,    60,    61,    72,
      44,    88,    51,    62,    62,     5,    90,    99,   100,    51,
       4,    22,    32,    33,    34,    35,    56,    62,    72,    77,
      78,    79,    80,    81,    52,    87,    94,    92,     6,    13,
      15,    16,    21,    23,    29,    30,    61,    62,   100,   101,
     102,   103,   104,   105,   106,   110,   112,   113,   114,   117,
     118,   121,    54,    62,    82,    83,    62,    67,    49,    51,
      77,    56,    95,    95,    17,    38,    56,    62,    72,   122,
     123,   124,   125,    62,   102,   122,    56,   101,   122,    56,
     107,   108,   111,    12,    51,    52,    51,    53,    79,    84,
      12,    51,    50,    57,    72,    57,    62,    96,    97,    52,
      51,   125,   125,   122,   126,   127,   128,    18,    42,    43,
      44,    45,    46,    47,    10,    31,    37,    38,     3,    39,
      40,    41,   115,    24,   125,    27,     8,   122,    54,    48,
      56,   103,   104,   122,    55,    52,    83,    62,    98,    51,
      57,    78,    66,    57,    56,    54,    48,    72,   119,   120,
     123,   123,   123,   123,   123,   123,   124,   124,   124,   124,
     125,   125,   125,   125,    53,   103,    57,   122,   103,    57,
     122,    62,   122,   130,    18,    77,    52,    97,    51,    51,
     130,   122,    62,    52,    12,    51,   122,    11,    55,   109,
      50,    57,    77,    78,    66,    57,    55,   129,   103,   120,
       9,    25,   116,   103,   122,    51,   122,     8,   103
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    63,    64,    65,    66,    67,    67,    68,    68,    69,
      69,    71,    70,    72,    72,    72,    72,    73,    73,    74,
      74,    76,    75,    77,    77,    77,    77,    78,    78,    78,
      78,    78,    78,    79,    80,    81,    82,    82,    84,    83,
      85,    85,    86,    86,    88,    87,    89,    89,    89,    90,
      90,    92,    91,    94,    93,    95,    95,    96,    96,    98,
      97,    99,   100,   101,   101,   101,   102,   103,   103,   104,
     104,   104,   104,   104,   104,   104,   104,   104,   105,   106,
     107,   106,   108,   109,   106,   110,   110,   111,   110,   110,
     112,   112,   113,   115,   114,   116,   116,   117,   118,   119,
     119,   120,   121,   122,   122,   122,   122,   122,   122,   122,
     123,   123,   123,   123,   123,   124,   124,   124,   124,   124,
     125,   126,   125,   127,   125,   128,   129,   125,   125,   125,
     125,   125,   130,   130
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     4,     2,     5,     3,     1,     2,     0,     2,
       1,     0,     5,     1,     1,     1,     1,     2,     0,     2,
       1,     0,     5,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     3,     6,     3,     3,     1,     0,     4,
       3,     0,     3,     1,     0,     4,     2,     1,     0,     1,
       1,     0,     7,     0,     9,     3,     2,     3,     1,     0,
       4,     1,     3,     3,     2,     0,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     1,
       0,     5,     0,     0,     5,     4,     4,     0,     5,     1,
       6,     4,     4,     0,     9,     1,     1,     4,     5,     3,
       1,     3,     2,     3,     3,     3,     3,     3,     3,     1,
       3,     3,     3,     3,     1,     3,     3,     3,     3,     1,
       1,     0,     5,     0,     5,     0,     0,     5,     1,     3,
       2,     2,     3,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 38 "parser.y" /* yacc.c:1646  */
    {
             showNodeInfo("program -> program_head SEMICOLON block DOT");
             (yyval) = (yyvsp[-1]);
             (yyvsp[-1])->setName((yyvsp[-3])->getName());
             delete (yyvsp[-3]);

             root = (yyval);
         }
#line 1550 "parser.cpp" /* yacc.c:1646  */
    break;

  case 3:
#line 48 "parser.y" /* yacc.c:1646  */
    {
                  showNodeInfo("program_head -> PROGRAM ID");
                  (yyval) = new TreeNode();
                  (yyval)->setName(yytext);
              }
#line 1560 "parser.cpp" /* yacc.c:1646  */
    break;

  case 4:
#line 59 "parser.y" /* yacc.c:1646  */
    {
        showNodeInfo("block -> constant_definition_part type_definition_part variable_declaration_part procedure_function_declaration_part block_body_part");
        (yyval) = new ProgramBodyTreeNode((yyvsp[-4]), (yyvsp[-3]), (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0]));
    }
#line 1569 "parser.cpp" /* yacc.c:1646  */
    break;

  case 5:
#line 65 "parser.y" /* yacc.c:1646  */
    {
             showNodeInfo("id_list -> id_list COMMA ID");
             (yyval) = (yyvsp[-2]);
             std::string name = yytext;
             TreeNode* node = new TreeNode();
             node->setName(name);

             ((ListTreeNode*)(yyval))->insert(node);
         }
#line 1583 "parser.cpp" /* yacc.c:1646  */
    break;

  case 6:
#line 75 "parser.y" /* yacc.c:1646  */
    {
          showNodeInfo("id_list -> ID");
          std::string name = yytext;
          std::vector<TreeNode*> list;
          TreeNode* node = new TreeNode();
          node->setName(name);
          list.push_back(node);

          (yyval) = new ListTreeNode("id_list", list);
      }
#line 1598 "parser.cpp" /* yacc.c:1646  */
    break;

  case 7:
#line 88 "parser.y" /* yacc.c:1646  */
    {
                              showNodeInfo("constant_definition_part -> CONST constant_list");
                              (yyval) = (yyvsp[-1]);
                          }
#line 1607 "parser.cpp" /* yacc.c:1646  */
    break;

  case 8:
#line 92 "parser.y" /* yacc.c:1646  */
    {
         showNodeInfo("constant_definition_part ->");
         std::vector<TreeNode*> list;
         (yyval) = new ListTreeNode("constant_definition_part", list);
      }
#line 1617 "parser.cpp" /* yacc.c:1646  */
    break;

  case 9:
#line 99 "parser.y" /* yacc.c:1646  */
    {
                   showNodeInfo("constant_list -> constant_list constant_definition");
                   (yyval) = (yyvsp[-1]);
                   ((ListTreeNode*)(yyval))->insert((yyvsp[0]));
               }
#line 1627 "parser.cpp" /* yacc.c:1646  */
    break;

  case 10:
#line 105 "parser.y" /* yacc.c:1646  */
    {
          showNodeInfo("constant_list -> constant_definition");
          std::vector<TreeNode*> list;
          list.push_back((yyvsp[0]));
          (yyval) = new ListTreeNode("constant_list", list);
      }
#line 1638 "parser.cpp" /* yacc.c:1646  */
    break;

  case 11:
#line 112 "parser.y" /* yacc.c:1646  */
    { stringQueue.push(yytext); }
#line 1644 "parser.cpp" /* yacc.c:1646  */
    break;

  case 12:
#line 113 "parser.y" /* yacc.c:1646  */
    {
                         showNodeInfo("constant_definition -> ID EQUAL constant_value SEMICOLON");
                         std::string name = stringQueue.front();
                         stringQueue.pop();
                         VariableTreeNode* varNode = new VariableTreeNode(name, nullptr, true);
                         BinaryExprTreeNode* binNode = new BinaryExprTreeNode(":=", varNode, (yyvsp[-1]));
                         (yyval) = binNode;
                     }
#line 1657 "parser.cpp" /* yacc.c:1646  */
    break;

  case 13:
#line 123 "parser.y" /* yacc.c:1646  */
    {
                    showNodeInfo("constant_value -> INTEGER");
                    (yyval) = new LiteralTreeNode(yytext, "integer");
                }
#line 1666 "parser.cpp" /* yacc.c:1646  */
    break;

  case 14:
#line 128 "parser.y" /* yacc.c:1646  */
    {
          showNodeInfo("constant_value -> REAL");
          (yyval) = new LiteralTreeNode(yytext, "real");
      }
#line 1675 "parser.cpp" /* yacc.c:1646  */
    break;

  case 15:
#line 133 "parser.y" /* yacc.c:1646  */
    {
          showNodeInfo("constant_value -> CHAR");
          (yyval) = new LiteralTreeNode(yytext, "char");
      }
#line 1684 "parser.cpp" /* yacc.c:1646  */
    break;

  case 16:
#line 138 "parser.y" /* yacc.c:1646  */
    {
          showNodeInfo("constant_value -> STRING");
          (yyval) = new LiteralTreeNode(yytext, "string");
      }
#line 1693 "parser.cpp" /* yacc.c:1646  */
    break;

  case 17:
#line 145 "parser.y" /* yacc.c:1646  */
    {
                          showNodeInfo("type_definition_part -> TYPE type_definition_list");
                          (yyval) = (yyvsp[0]);
                      }
#line 1702 "parser.cpp" /* yacc.c:1646  */
    break;

  case 18:
#line 149 "parser.y" /* yacc.c:1646  */
    {
         showNodeInfo("type_definition_part -> ");
         std::vector<TreeNode*> list;
         (yyval) = new ListTreeNode("type_definition_part", list);
      }
#line 1712 "parser.cpp" /* yacc.c:1646  */
    break;

  case 19:
#line 156 "parser.y" /* yacc.c:1646  */
    {
                          showNodeInfo("type_definition_list -> type_definition_list type_definition");
                          (yyval) = (yyvsp[-1]);
                          ((ListTreeNode*)(yyval))->insert((yyvsp[-1]));
                      }
#line 1722 "parser.cpp" /* yacc.c:1646  */
    break;

  case 20:
#line 162 "parser.y" /* yacc.c:1646  */
    {
          showNodeInfo("type_definition_list -> type_definition");
          std::vector<TreeNode*> list;
          list.push_back((yyvsp[0]));
          (yyval) = new ListTreeNode("type_definition_list", list);
      }
#line 1733 "parser.cpp" /* yacc.c:1646  */
    break;

  case 21:
#line 169 "parser.y" /* yacc.c:1646  */
    { stringQueue.push(yytext); }
#line 1739 "parser.cpp" /* yacc.c:1646  */
    break;

  case 22:
#line 170 "parser.y" /* yacc.c:1646  */
    {
                     showNodeInfo("type_definition -> ID EQUAL type_denoter SEMICOLON");
                     std::string name = stringQueue.front();
                     stringQueue.pop();
                     (yyval) = new CustomTypeTreeNode(name, (yyvsp[-1]));
                 }
#line 1750 "parser.cpp" /* yacc.c:1646  */
    break;

  case 23:
#line 178 "parser.y" /* yacc.c:1646  */
    {
                  showNodeInfo("type_denoter -> simple_type");
                  (yyval) = (yyvsp[0]);
              }
#line 1759 "parser.cpp" /* yacc.c:1646  */
    break;

  case 24:
#line 183 "parser.y" /* yacc.c:1646  */
    {
          showNodeInfo("type_denoter -> range_type");
          (yyval) = (yyvsp[0]);
      }
#line 1768 "parser.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 188 "parser.y" /* yacc.c:1646  */
    {
          showNodeInfo("type_denoter -> array_type");
          (yyval) = (yyvsp[0]);
      }
#line 1777 "parser.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 193 "parser.y" /* yacc.c:1646  */
    {
          showNodeInfo("type_denoter -> record_type");
          (yyval) = (yyvsp[0]);
      }
#line 1786 "parser.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 199 "parser.y" /* yacc.c:1646  */
    {
                 showNodeInfo("simple_type -> TYPE_INTEGER");
                 (yyval) = new CommonTypeTreeNode("integer");
             }
#line 1795 "parser.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 204 "parser.y" /* yacc.c:1646  */
    {
          showNodeInfo("simple_type -> TYPE_CHAR");
          (yyval) = new CommonTypeTreeNode("char");
      }
#line 1804 "parser.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 209 "parser.y" /* yacc.c:1646  */
    {
          showNodeInfo("simple_type -> TYPE_REAL");
          (yyval) = new CommonTypeTreeNode("real");
      }
#line 1813 "parser.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 214 "parser.y" /* yacc.c:1646  */
    {
          showNodeInfo("simple_type -> TYPE_STRING");
          (yyval) = new CommonTypeTreeNode("string");
      }
#line 1822 "parser.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 219 "parser.y" /* yacc.c:1646  */
    {
          showNodeInfo("simple_type -> ID");
          (yyval) = new CustomTypeTreeNode(yytext, nullptr);
      }
#line 1831 "parser.cpp" /* yacc.c:1646  */
    break;

  case 32:
#line 224 "parser.y" /* yacc.c:1646  */
    {
          showNodeInfo("simple_type -> LP id_list RP");
          (yyval) = new EnumTypeTreeNode((yyvsp[-1]), "enum_type");
      }
#line 1840 "parser.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 230 "parser.y" /* yacc.c:1646  */
    {
                showNodeInfo("range_type -> constant_value DOTDOT constant_value");
                (yyval) = new RangeTypeTreeNode((IDTreeNode*)(yyvsp[-2]), (IDTreeNode*)(yyvsp[0]));
            }
#line 1849 "parser.cpp" /* yacc.c:1646  */
    break;

  case 34:
#line 236 "parser.y" /* yacc.c:1646  */
    {

            }
#line 1857 "parser.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 241 "parser.y" /* yacc.c:1646  */
    {
                 showNodeInfo("record_type -> RECORD field_definition_list END");
                 std::vector<TreeNode*> list = ((ListTreeNode*)(yyvsp[-1]))->getList();
                 (yyval) = new RecordTypeTreeNode(list);
             }
#line 1867 "parser.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 248 "parser.y" /* yacc.c:1646  */
    {
                           showNodeInfo("field_definition_list -> field_definition_list SEMICOLON field_definition");
                           (yyval) = (yyvsp[-2]);
                           ((ListTreeNode*)(yyval))->insert((yyvsp[0]));
                       }
#line 1877 "parser.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 254 "parser.y" /* yacc.c:1646  */
    {
          showNodeInfo("field_definition_list -> field_definition");
          std::vector<TreeNode*> list;
          list.push_back((yyvsp[0]));
          (yyval) = new ListTreeNode("field_definition_list", list);
      }
#line 1888 "parser.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 261 "parser.y" /* yacc.c:1646  */
    { stringQueue.push(yytext); }
#line 1894 "parser.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 262 "parser.y" /* yacc.c:1646  */
    {
                      showNodeInfo("field_definition -> ID COLON type_denoter");
                      std::string name = stringQueue.front();
                      stringQueue.pop();
                      (yyval) = new VariableTreeNode(name, (yyvsp[0]));
                  }
#line 1905 "parser.cpp" /* yacc.c:1646  */
    break;

  case 40:
#line 271 "parser.y" /* yacc.c:1646  */
    {
                               showNodeInfo("variable_declaration_part -> VAR variable_declaration_list SEMICOLON");
                               (yyval) = (yyvsp[-1]);
                           }
#line 1914 "parser.cpp" /* yacc.c:1646  */
    break;

  case 41:
#line 275 "parser.y" /* yacc.c:1646  */
    {
          showNodeInfo("variable_declaration_part ->");
          std::vector<TreeNode*> list;
          (yyval) = new ListTreeNode("variable_declaration_part", list);
      }
#line 1924 "parser.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 282 "parser.y" /* yacc.c:1646  */
    {
                               showNodeInfo("variable_declaration_list -> variable_declaration_list SEMICOLON variable_declaration");
                               (yyval) = (yyvsp[-2]);
                               ((ListTreeNode*)(yyval))->insert((yyvsp[0]));
                           }
#line 1934 "parser.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 288 "parser.y" /* yacc.c:1646  */
    {
          showNodeInfo("variable_declaration_list -> variable_declaration");
          std::vector<TreeNode*> list;
          list.push_back((yyvsp[0]));
          (yyval) = new ListTreeNode("variable_declaration_list", list);
      }
#line 1945 "parser.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 295 "parser.y" /* yacc.c:1646  */
    { stringQueue.push(yytext); }
#line 1951 "parser.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 296 "parser.y" /* yacc.c:1646  */
    {
                          showNodeInfo("variable_declaration -> ID COLON type_denoter");
                          std::string name = stringQueue.front();
                          stringQueue.pop();
                          (yyval) = new VariableTreeNode(name, (yyvsp[0]));
                      }
#line 1962 "parser.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 305 "parser.y" /* yacc.c:1646  */
    {
                                         showNodeInfo("procedure_function_declaration_part -> procedure_function_declaration_part procedure_function_declaration");
                                         (yyval) = (yyvsp[-1]);
                                         ((ListTreeNode*)(yyval))->insert((yyvsp[0]));
                                     }
#line 1972 "parser.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 311 "parser.y" /* yacc.c:1646  */
    {
          showNodeInfo("procedure_function_declaration_part -> procedure_function_declaration");
          std::vector<TreeNode*> list;
          list.push_back((yyvsp[0]));
          (yyval) = new ListTreeNode("procedure_function_declaration_part", list);
      }
#line 1983 "parser.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 317 "parser.y" /* yacc.c:1646  */
    {
          showNodeInfo("procedure_function_declaration_part ->");
          std::vector<TreeNode*> list;
          (yyval) = new ListTreeNode("procedure_function_declaration_part", list);
      }
#line 1993 "parser.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 324 "parser.y" /* yacc.c:1646  */
    {
                                    showNodeInfo("procedure_function_declaration -> procedure_declaration ");
                                    (yyval) = (yyvsp[0]);
                                }
#line 2002 "parser.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 329 "parser.y" /* yacc.c:1646  */
    {
          showNodeInfo("procedure_function_declaration -> function_declaration");
          (yyval) = (yyvsp[0]);
      }
#line 2011 "parser.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 334 "parser.y" /* yacc.c:1646  */
    { stringQueue.push(yytext); }
#line 2017 "parser.cpp" /* yacc.c:1646  */
    break;

  case 52:
#line 335 "parser.y" /* yacc.c:1646  */
    {
                           showNodeInfo("procedure_declaration -> PROCEDURE ID parameters SEMICOLON block SEMICOLON");
                           std::string name = stringQueue.front();
                           stringQueue.pop();
                           (yyval) = new FuncOrProcTreeNode(name, (yyvsp[-3]), (yyvsp[-1]));
                       }
#line 2028 "parser.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 342 "parser.y" /* yacc.c:1646  */
    { stringQueue.push(yytext); }
#line 2034 "parser.cpp" /* yacc.c:1646  */
    break;

  case 54:
#line 343 "parser.y" /* yacc.c:1646  */
    {
                          showNodeInfo("function_declaration -> FUNCTION ID parameters COLON simple_type SEMICOLON block SEMICOLON");
                          std::string name = stringQueue.front();
                          stringQueue.pop();
                          (yyval) = new FuncOrProcTreeNode(name, (yyvsp[-5]), (yyvsp[-1]), (yyvsp[-3]), true);
                      }
#line 2045 "parser.cpp" /* yacc.c:1646  */
    break;

  case 55:
#line 351 "parser.y" /* yacc.c:1646  */
    {
                showNodeInfo("parameters -> LP parameter_list RP");
                (yyval) = (yyvsp[-1]);
            }
#line 2054 "parser.cpp" /* yacc.c:1646  */
    break;

  case 56:
#line 356 "parser.y" /* yacc.c:1646  */
    {
          showNodeInfo("parameters -> LP RP");
          std::vector<TreeNode*> emptyList;
          (yyval) = new ListTreeNode("parameters", emptyList);
      }
#line 2064 "parser.cpp" /* yacc.c:1646  */
    break;

  case 57:
#line 363 "parser.y" /* yacc.c:1646  */
    {
                    showNodeInfo("parameter_list -> parameter_list SEMICOLON parameter");
                    (yyval) = (yyvsp[-2]);
                    ((ListTreeNode*)(yyval))->insert((yyvsp[0]));
                }
#line 2074 "parser.cpp" /* yacc.c:1646  */
    break;

  case 58:
#line 369 "parser.y" /* yacc.c:1646  */
    {
          showNodeInfo("parameter_list -> parameter");
          std::vector<TreeNode*> list;
          list.push_back((yyvsp[0]));
          (yyval) = new ListTreeNode("parameter_list", list);
      }
#line 2085 "parser.cpp" /* yacc.c:1646  */
    break;

  case 59:
#line 376 "parser.y" /* yacc.c:1646  */
    { stringQueue.push(yytext); }
#line 2091 "parser.cpp" /* yacc.c:1646  */
    break;

  case 60:
#line 377 "parser.y" /* yacc.c:1646  */
    {
               showNodeInfo("parameter -> ID COLON simple_type");
               std::string name = stringQueue.front();
               stringQueue.pop();
               (yyval) = new VariableTreeNode(name, (yyvsp[0]));
           }
#line 2102 "parser.cpp" /* yacc.c:1646  */
    break;

  case 61:
#line 386 "parser.y" /* yacc.c:1646  */
    {
                     showNodeInfo("block_body_part -> compound_statement");
                     std::vector<TreeNode*> body;
                     body.push_back((yyvsp[0]));
                     (yyval) = new ListTreeNode("block_body_part", body);
                 }
#line 2113 "parser.cpp" /* yacc.c:1646  */
    break;

  case 62:
#line 394 "parser.y" /* yacc.c:1646  */
    {
                        showNodeInfo("compound_statement -> BEGIN_ statememt_list END");
                        (yyval) = new CompoundStmtTreeNode((ListTreeNode*)(yyvsp[-1]));
                    }
#line 2122 "parser.cpp" /* yacc.c:1646  */
    break;

  case 63:
#line 400 "parser.y" /* yacc.c:1646  */
    {
                    showNodeInfo("statememt_list -> statememt_list SEMICOLON statememt");
                    (yyval) = (yyvsp[-2]);
                    ((ListTreeNode*)(yyval))->insert((yyvsp[0]));
                }
#line 2132 "parser.cpp" /* yacc.c:1646  */
    break;

  case 64:
#line 406 "parser.y" /* yacc.c:1646  */
    {
          showNodeInfo("statememt_list -> statememt SEMICOLON");
          std::vector<TreeNode*> list;
          list.push_back((yyvsp[-1]));
          (yyval) = new ListTreeNode("statement_list", list);
      }
#line 2143 "parser.cpp" /* yacc.c:1646  */
    break;

  case 65:
#line 413 "parser.y" /* yacc.c:1646  */
    {
         showNodeInfo("statememt_list -> ");
         std::vector<TreeNode*> list;
         (yyval) = new ListTreeNode("statement_list", list);
      }
#line 2153 "parser.cpp" /* yacc.c:1646  */
    break;

  case 66:
#line 420 "parser.y" /* yacc.c:1646  */
    {
           showNodeInfo("label -> STRING");
           std::string labelName = yytext;
           TreeNode* node = new TreeNode();
           node->setName(labelName);
           (yyval) = node;
       }
#line 2165 "parser.cpp" /* yacc.c:1646  */
    break;

  case 67:
#line 429 "parser.y" /* yacc.c:1646  */
    {
               showNodeInfo("statement -> label COLON stmt");
               (yyval) = (yyvsp[0]);
               const std::string labelName = (yyvsp[-2])->getName();
               ((StatementTreeNode*)(yyval))->setLabel(hashCodeForString(labelName));
               delete (yyvsp[-2]);
           }
#line 2177 "parser.cpp" /* yacc.c:1646  */
    break;

  case 68:
#line 437 "parser.y" /* yacc.c:1646  */
    {
          showNodeInfo("statement -> stmt");
          (yyval) = (yyvsp[0]);
      }
#line 2186 "parser.cpp" /* yacc.c:1646  */
    break;

  case 69:
#line 443 "parser.y" /* yacc.c:1646  */
    {
          showNodeInfo("stmt -> assign_statememt");
          (yyval) = (yyvsp[0]);
      }
#line 2195 "parser.cpp" /* yacc.c:1646  */
    break;

  case 70:
#line 448 "parser.y" /* yacc.c:1646  */
    {
          showNodeInfo("stmt -> procedure_statement");
          (yyval) = (yyvsp[0]);
      }
#line 2204 "parser.cpp" /* yacc.c:1646  */
    break;

  case 71:
#line 453 "parser.y" /* yacc.c:1646  */
    {
          showNodeInfo("stmt -> if_statememt");
          (yyval) = (yyvsp[0]);
      }
#line 2213 "parser.cpp" /* yacc.c:1646  */
    break;

  case 72:
#line 458 "parser.y" /* yacc.c:1646  */
    {
          showNodeInfo("stmt -> repeat_statement");
          (yyval) = (yyvsp[0]);
      }
#line 2222 "parser.cpp" /* yacc.c:1646  */
    break;

  case 73:
#line 463 "parser.y" /* yacc.c:1646  */
    {
          showNodeInfo("stmt -> for_statememt");
          (yyval) = (yyvsp[0]);
      }
#line 2231 "parser.cpp" /* yacc.c:1646  */
    break;

  case 74:
#line 468 "parser.y" /* yacc.c:1646  */
    {
          showNodeInfo("stmt -> while_statememt");
          (yyval) = (yyvsp[0]);
      }
#line 2240 "parser.cpp" /* yacc.c:1646  */
    break;

  case 75:
#line 473 "parser.y" /* yacc.c:1646  */
    {
          showNodeInfo("stmt -> case_statememt");
          (yyval) = (yyvsp[0]);
      }
#line 2249 "parser.cpp" /* yacc.c:1646  */
    break;

  case 76:
#line 478 "parser.y" /* yacc.c:1646  */
    {
          showNodeInfo("stmt -> goto_statememt");
          (yyval) = (yyvsp[0]);
      }
#line 2258 "parser.cpp" /* yacc.c:1646  */
    break;

  case 77:
#line 483 "parser.y" /* yacc.c:1646  */
    {
          showNodeInfo("stmt -> compound_statement");
          (yyval) = (yyvsp[0]);
      }
#line 2267 "parser.cpp" /* yacc.c:1646  */
    break;

  case 78:
#line 490 "parser.y" /* yacc.c:1646  */
    {
                     showNodeInfo("assign_statememt -> variable_access ASSIGN expression");
                     (yyval) = new BinaryExprTreeNode(":=", (yyvsp[-2]), (yyvsp[0]));
                  }
#line 2276 "parser.cpp" /* yacc.c:1646  */
    break;

  case 79:
#line 496 "parser.y" /* yacc.c:1646  */
    {
                     showNodeInfo("variable_access -> ID");
                     (yyval) = new VariableTreeNode(yytext);
                 }
#line 2285 "parser.cpp" /* yacc.c:1646  */
    break;

  case 80:
#line 500 "parser.y" /* yacc.c:1646  */
    { stringQueue.push(yytext); }
#line 2291 "parser.cpp" /* yacc.c:1646  */
    break;

  case 81:
#line 501 "parser.y" /* yacc.c:1646  */
    {
          showNodeInfo("variable_access -> ID LB expression RB");
          std::string arrayName = stringQueue.front();
          stringQueue.pop();
          (yyval) = new ArrayElemTreeNode(arrayName, (yyvsp[-1]));
      }
#line 2302 "parser.cpp" /* yacc.c:1646  */
    break;

  case 82:
#line 507 "parser.y" /* yacc.c:1646  */
    { stringQueue.push(yytext); }
#line 2308 "parser.cpp" /* yacc.c:1646  */
    break;

  case 83:
#line 507 "parser.y" /* yacc.c:1646  */
    { stringQueue.push(yytext); }
#line 2314 "parser.cpp" /* yacc.c:1646  */
    break;

  case 84:
#line 508 "parser.y" /* yacc.c:1646  */
    {
          showNodeInfo("variable_access -> ID DOT ID");
          std::string rname = stringQueue.front();
          stringQueue.pop();
          std::string ename = stringQueue.front();
          stringQueue.pop();
          (yyval) = new RecordElemTreeNode(rname, ename);
      }
#line 2327 "parser.cpp" /* yacc.c:1646  */
    break;

  case 85:
#line 519 "parser.y" /* yacc.c:1646  */
    {
                         showNodeInfo("procedure_statement -> READ LP factor RP");
                         // You need to release it and make it NULL
                         std::vector<TreeNode*>* list = new std::vector<TreeNode*>;
                         list->push_back((yyvsp[-1]));
                         (yyval) = new CallExprTreeNode("read", list, false);
                         
                     }
#line 2340 "parser.cpp" /* yacc.c:1646  */
    break;

  case 86:
#line 528 "parser.y" /* yacc.c:1646  */
    {
          showNodeInfo("procedure_statement -> WRITE LP expression RP");
          std::vector<TreeNode*>* list = new std::vector<TreeNode*>;
          list->push_back((yyvsp[-1]));
          (yyval) = new CallExprTreeNode("write", list, false);
      }
#line 2351 "parser.cpp" /* yacc.c:1646  */
    break;

  case 87:
#line 534 "parser.y" /* yacc.c:1646  */
    { stringQueue.push(yytext); }
#line 2357 "parser.cpp" /* yacc.c:1646  */
    break;

  case 88:
#line 535 "parser.y" /* yacc.c:1646  */
    {
          showNodeInfo("procedure_statement -> ID LP args RP");
          std::string procName = stringQueue.front();
          stringQueue.pop();
          (yyval) = new CallExprTreeNode(procName, &(((ListTreeNode*)(yyvsp[-1]))->getList()), 
            false);
      }
#line 2369 "parser.cpp" /* yacc.c:1646  */
    break;

  case 89:
#line 543 "parser.y" /* yacc.c:1646  */
    {
          showNodeInfo("procedure_statement -> ID");
          std::string procName = yytext;
          (yyval) = new CallExprTreeNode(procName, nullptr, false);
      }
#line 2379 "parser.cpp" /* yacc.c:1646  */
    break;

  case 90:
#line 551 "parser.y" /* yacc.c:1646  */
    {
                  showNodeInfo("if_statememt -> IF expression THEN statememt ELSE statememt");
                  (yyval) = new IfStmtTreeNode((ExprTreeNode*)(yyvsp[-4]), (StatementTreeNode*)(yyvsp[-2]), (StatementTreeNode*)(yyvsp[0]));
              }
#line 2388 "parser.cpp" /* yacc.c:1646  */
    break;

  case 91:
#line 556 "parser.y" /* yacc.c:1646  */
    {
          showNodeInfo("if_statememt -> IF expression THEN statememt");
          (yyval) = new IfStmtTreeNode((ExprTreeNode*)(yyvsp[-2]), (StatementTreeNode*)(yyvsp[0]), nullptr);
      }
#line 2397 "parser.cpp" /* yacc.c:1646  */
    break;

  case 92:
#line 563 "parser.y" /* yacc.c:1646  */
    {
                      showNodeInfo("repeat_statememt -> REPEAT statememt_list UNTIL expression");
                      (yyval) = new RepeatStmtTreeNode((ExprTreeNode *)(yyvsp[0]), (StatementTreeNode *)(yyvsp[-2]));
                  }
#line 2406 "parser.cpp" /* yacc.c:1646  */
    break;

  case 93:
#line 569 "parser.y" /* yacc.c:1646  */
    { stringQueue.push(yytext); }
#line 2412 "parser.cpp" /* yacc.c:1646  */
    break;

  case 94:
#line 570 "parser.y" /* yacc.c:1646  */
    {
                   showNodeInfo("for_statement -> FOR ID ASSIGN expression direction expression DO statememt");
                   std::string variableId = stringQueue.front();
                   stringQueue.pop();
                   VariableTreeNode* varNode = new VariableTreeNode(variableId);
                   BinaryExprTreeNode* exprNode = new BinaryExprTreeNode(":=", varNode, (yyvsp[-4]));
                   std::string direction = (yyvsp[-3])->getName();
                   (yyval) = new ForStmtTreeNode(exprNode, direction, (ExprTreeNode *)(yyvsp[-2]), (StatementTreeNode *)(yyvsp[0]));
                   delete (yyvsp[-3]);
               }
#line 2427 "parser.cpp" /* yacc.c:1646  */
    break;

  case 95:
#line 582 "parser.y" /* yacc.c:1646  */
    {
               showNodeInfo("direction -> TO");
               (yyval) = new TreeNode();
               (yyval)->setName("to");
           }
#line 2437 "parser.cpp" /* yacc.c:1646  */
    break;

  case 96:
#line 588 "parser.y" /* yacc.c:1646  */
    {
          showNodeInfo("direction -> DOWNTO");
          (yyval) = new TreeNode();
          (yyval)->setName("downto");
      }
#line 2447 "parser.cpp" /* yacc.c:1646  */
    break;

  case 97:
#line 596 "parser.y" /* yacc.c:1646  */
    {
                     showNodeInfo("while_statement -> WHILE expression DO statement");
                     (yyval) = new WhileStmtTreeNode((ExprTreeNode *)(yyvsp[-2]), (StatementTreeNode *)(yyvsp[0]));
                 }
#line 2456 "parser.cpp" /* yacc.c:1646  */
    break;

  case 98:
#line 603 "parser.y" /* yacc.c:1646  */
    {
                    showNodeInfo("case_statement -> CASE expresion OF case_list END");
                    (yyval) = new SwitchStmtTreeNode((ExprTreeNode *)(yyvsp[-3]), (ListTreeNode *)(yyvsp[-1]));
                }
#line 2465 "parser.cpp" /* yacc.c:1646  */
    break;

  case 99:
#line 609 "parser.y" /* yacc.c:1646  */
    {
               showNodeInfo("case_list -> case_list SEMICOLON case_item");
               (yyval) = (yyvsp[-2]);
               ((ListTreeNode*)(yyval))->insert((yyvsp[0]));
           }
#line 2475 "parser.cpp" /* yacc.c:1646  */
    break;

  case 100:
#line 615 "parser.y" /* yacc.c:1646  */
    {
          showNodeInfo("case_list -> case_item");
          std::vector<TreeNode*> list;
          list.push_back((yyvsp[0]));
          (yyval) = new ListTreeNode("case_list", list);
      }
#line 2486 "parser.cpp" /* yacc.c:1646  */
    break;

  case 101:
#line 623 "parser.y" /* yacc.c:1646  */
    {
               showNodeInfo("case_item -> constant_value COLON statement");
               (yyval) = new CaseExprTreeNode((IDTreeNode *)(yyvsp[-2]), (StatementTreeNode *)(yyvsp[0]));
           }
#line 2495 "parser.cpp" /* yacc.c:1646  */
    break;

  case 102:
#line 630 "parser.y" /* yacc.c:1646  */
    {
                    showNodeInfo("goto_statememt -> GOTO label");
                    std::string labelName = (yyvsp[0])->getName();
                    // you need to hash the labelName 
                    (yyval) = new GotoStmtTreeNode(labelName);
                    // remove tree node created for label
                    delete (yyvsp[0]);
                }
#line 2508 "parser.cpp" /* yacc.c:1646  */
    break;

  case 103:
#line 641 "parser.y" /* yacc.c:1646  */
    {
                showNodeInfo("expression -> expression LT expr");
                (yyval) = new BinaryExprTreeNode("<", (yyvsp[-2]), (yyvsp[0]));
            }
#line 2517 "parser.cpp" /* yacc.c:1646  */
    break;

  case 104:
#line 646 "parser.y" /* yacc.c:1646  */
    {
          showNodeInfo("expression -> expression LE expr");
          (yyval) = new BinaryExprTreeNode("<=", (yyvsp[-2]), (yyvsp[0]));
      }
#line 2526 "parser.cpp" /* yacc.c:1646  */
    break;

  case 105:
#line 651 "parser.y" /* yacc.c:1646  */
    {
          showNodeInfo("expression -> expression EQUAL expr");
          (yyval) = new BinaryExprTreeNode("=", (yyvsp[-2]), (yyvsp[0]));
      }
#line 2535 "parser.cpp" /* yacc.c:1646  */
    break;

  case 106:
#line 656 "parser.y" /* yacc.c:1646  */
    {
          showNodeInfo("expression -> expression GE expr");
          (yyval) = new BinaryExprTreeNode(">=", (yyvsp[-2]), (yyvsp[0]));
      }
#line 2544 "parser.cpp" /* yacc.c:1646  */
    break;

  case 107:
#line 661 "parser.y" /* yacc.c:1646  */
    {
          showNodeInfo("expression -> expression GT expr");
          (yyval) = new BinaryExprTreeNode(">", (yyvsp[-2]), (yyvsp[0]));
      }
#line 2553 "parser.cpp" /* yacc.c:1646  */
    break;

  case 108:
#line 666 "parser.y" /* yacc.c:1646  */
    {
          showNodeInfo("expression -> expression UNEQUAL expr");
          (yyval) = new BinaryExprTreeNode("!=", (yyvsp[-2]), (yyvsp[0]));
      }
#line 2562 "parser.cpp" /* yacc.c:1646  */
    break;

  case 109:
#line 671 "parser.y" /* yacc.c:1646  */
    {
          showNodeInfo("expression -> expr");
          (yyval) = (yyvsp[0]);
      }
#line 2571 "parser.cpp" /* yacc.c:1646  */
    break;

  case 110:
#line 677 "parser.y" /* yacc.c:1646  */
    {
          showNodeInfo("expr -> expr PLUS term");
          (yyval) = new BinaryExprTreeNode("+", (yyvsp[-2]), (yyvsp[0]));
      }
#line 2580 "parser.cpp" /* yacc.c:1646  */
    break;

  case 111:
#line 682 "parser.y" /* yacc.c:1646  */
    {
          showNodeInfo("expr -> expr MNUS term");
          (yyval) = new BinaryExprTreeNode("-", (yyvsp[-2]), (yyvsp[0]));
      }
#line 2589 "parser.cpp" /* yacc.c:1646  */
    break;

  case 112:
#line 687 "parser.y" /* yacc.c:1646  */
    {
          showNodeInfo("expr -> expr OR term");
          (yyval) = new BinaryExprTreeNode("or", (yyvsp[-2]), (yyvsp[0]));
      }
#line 2598 "parser.cpp" /* yacc.c:1646  */
    break;

  case 113:
#line 692 "parser.y" /* yacc.c:1646  */
    {
          showNodeInfo("expr -> expr XOR term");
          (yyval) = new BinaryExprTreeNode("xor", (yyvsp[-2]), (yyvsp[0]));
      }
#line 2607 "parser.cpp" /* yacc.c:1646  */
    break;

  case 114:
#line 697 "parser.y" /* yacc.c:1646  */
    {
          showNodeInfo("expr -> term");
          (yyval) = (yyvsp[0]);
      }
#line 2616 "parser.cpp" /* yacc.c:1646  */
    break;

  case 115:
#line 703 "parser.y" /* yacc.c:1646  */
    {
          showNodeInfo("term -> term MULTIPLY factor");
          (yyval) = new BinaryExprTreeNode("*", (yyvsp[-2]), (yyvsp[0]));
      }
#line 2625 "parser.cpp" /* yacc.c:1646  */
    break;

  case 116:
#line 708 "parser.y" /* yacc.c:1646  */
    {
          showNodeInfo("term -> term DIVIDE factor");
          (yyval) = new BinaryExprTreeNode("/", (yyvsp[-2]), (yyvsp[0]));
      }
#line 2634 "parser.cpp" /* yacc.c:1646  */
    break;

  case 117:
#line 713 "parser.y" /* yacc.c:1646  */
    {
          showNodeInfo("term -> term MOD factor");
          (yyval) = new BinaryExprTreeNode("%", (yyvsp[-2]), (yyvsp[0]));
      }
#line 2643 "parser.cpp" /* yacc.c:1646  */
    break;

  case 118:
#line 718 "parser.y" /* yacc.c:1646  */
    {
          showNodeInfo("term -> term AND factor");
          (yyval) = new BinaryExprTreeNode("and", (yyvsp[-2]), (yyvsp[0]));
      }
#line 2652 "parser.cpp" /* yacc.c:1646  */
    break;

  case 119:
#line 723 "parser.y" /* yacc.c:1646  */
    {
          showNodeInfo("term -> factor");
          (yyval) = (yyvsp[0]);
      }
#line 2661 "parser.cpp" /* yacc.c:1646  */
    break;

  case 120:
#line 729 "parser.y" /* yacc.c:1646  */
    { 
          // Simple variable
          showNodeInfo("factor ->ID");
          (yyval) = new VariableTreeNode(yytext);
        }
#line 2671 "parser.cpp" /* yacc.c:1646  */
    break;

  case 121:
#line 734 "parser.y" /* yacc.c:1646  */
    { stringQueue.push(yytext); }
#line 2677 "parser.cpp" /* yacc.c:1646  */
    break;

  case 122:
#line 735 "parser.y" /* yacc.c:1646  */
    { 
          // Function value
          showNodeInfo("factor -> ID LP args RP"); 
          std::string functionName = stringQueue.front();
          stringQueue.pop();
          (yyval) = new CallExprTreeNode(functionName,
            &(((ListTreeNode*)(yyvsp[-1]))->getList()));
      }
#line 2690 "parser.cpp" /* yacc.c:1646  */
    break;

  case 123:
#line 743 "parser.y" /* yacc.c:1646  */
    { stringQueue.push(yytext); }
#line 2696 "parser.cpp" /* yacc.c:1646  */
    break;

  case 124:
#line 744 "parser.y" /* yacc.c:1646  */
    {
          // Array Element
          showNodeInfo("factor -> ID LB expression RB");
          std::string arrayName = stringQueue.front();
          stringQueue.pop();
          (yyval) = new ArrayElemTreeNode(arrayName, (yyvsp[-1]));
      }
#line 2708 "parser.cpp" /* yacc.c:1646  */
    break;

  case 125:
#line 751 "parser.y" /* yacc.c:1646  */
    { stringQueue.push(yytext); }
#line 2714 "parser.cpp" /* yacc.c:1646  */
    break;

  case 126:
#line 751 "parser.y" /* yacc.c:1646  */
    { stringQueue.push(yytext); }
#line 2720 "parser.cpp" /* yacc.c:1646  */
    break;

  case 127:
#line 752 "parser.y" /* yacc.c:1646  */
    {
          // Record element
          showNodeInfo("factor -> ID DOT ID");
          std::string recordName = stringQueue.front();
          stringQueue.pop();
          std::string recordElemName = stringQueue.front();
          stringQueue.pop();
          (yyval) = new RecordElemTreeNode(recordName, recordElemName);
      }
#line 2734 "parser.cpp" /* yacc.c:1646  */
    break;

  case 128:
#line 762 "parser.y" /* yacc.c:1646  */
    {
          showNodeInfo("factor -> constant_value");
          (yyval) = (yyvsp[0]);
      }
#line 2743 "parser.cpp" /* yacc.c:1646  */
    break;

  case 129:
#line 767 "parser.y" /* yacc.c:1646  */
    {
          showNodeInfo("factor -> LP expression RP");
          (yyval) = (yyvsp[-1]);
      }
#line 2752 "parser.cpp" /* yacc.c:1646  */
    break;

  case 130:
#line 772 "parser.y" /* yacc.c:1646  */
    {
          // Negative value
          showNodeInfo("factor -> MINUS factor");
          (yyval) = new UnaryExprTreeNode("-", (yyvsp[0]));
      }
#line 2762 "parser.cpp" /* yacc.c:1646  */
    break;

  case 131:
#line 778 "parser.y" /* yacc.c:1646  */
    {
          // Not value for bit..
          showNodeInfo("factor -> NOT factor");
          (yyval) = new UnaryExprTreeNode("not", (yyvsp[0]));
      }
#line 2772 "parser.cpp" /* yacc.c:1646  */
    break;

  case 132:
#line 785 "parser.y" /* yacc.c:1646  */
    {
          showNodeInfo("args -> args COMMA expression)");
          (yyval) = (yyvsp[-2]);
          ((ListTreeNode*)(yyval))->insert((yyvsp[0]));
      }
#line 2782 "parser.cpp" /* yacc.c:1646  */
    break;

  case 133:
#line 791 "parser.y" /* yacc.c:1646  */
    { 
          showNodeInfo("args -> expression");
          std::vector<TreeNode*> expressionList;
          expressionList.push_back((yyvsp[0]));
          (yyval) = new ListTreeNode("args", expressionList);
      }
#line 2793 "parser.cpp" /* yacc.c:1646  */
    break;


#line 2797 "parser.cpp" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 798 "parser.y" /* yacc.c:1906  */


static int yylex(void)
{
    return getCurrentToken();
}

static int hashCodeForString(const std::string& str)
{
    int h = 0;
    for(int i = 0; i < str.length(); i++)
        h = 31 * h + (str[i] & 0xff);
    
    return h;
}

static void showNodeInfo(const std::string& info)
{
    grammarOut << "At line " << globalInfo.currentLineIndex
        << ": Node - " << info << std::endl; 
}

int yyerror(const char* str)
{
    printf("Error message: %s\n", str);
    return 1;
}

int yywrap()
{
    return 1;
}
