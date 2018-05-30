/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison implementation for Yacc-like parsers in C

      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.

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
#define YYBISON_VERSION "2.5"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 268 of yacc.c  */
#line 1 "test.y"

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


/* Line 268 of yacc.c  */
#line 98 "y.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
/* Put the tokens into the symbol table, so that GDB and other debuggers
   know about them.  */
enum yytokentype {
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




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 264 "y.tab.c"

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
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
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
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
/* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   291

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  63
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  53
/* YYNRULES -- Number of rules.  */
#define YYNRULES  117
/* YYNRULES -- Number of states.  */
#define YYNSTATES  232

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   317

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
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
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     8,    11,    17,    21,    23,    26,    27,
      30,    32,    37,    39,    41,    43,    45,    48,    49,    52,
      54,    59,    61,    63,    65,    67,    69,    71,    73,    75,
      77,    81,    85,    92,    96,   100,   102,   106,   110,   111,
     115,   117,   121,   124,   126,   127,   129,   131,   138,   147,
     151,   154,   158,   160,   164,   166,   170,   174,   175,   177,
     181,   183,   185,   187,   189,   191,   193,   195,   197,   199,
     201,   205,   207,   212,   216,   221,   226,   231,   233,   240,
     245,   250,   251,   261,   263,   265,   270,   276,   280,   282,
     286,   289,   293,   297,   301,   305,   309,   313,   315,   319,
     323,   327,   331,   333,   337,   341,   345,   349,   351,   353,
     358,   363,   367,   369,   373,   376,   379,   383
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      64,     0,    -1,    65,    51,    66,    48,    -1,    19,    62,
      -1,    68,    72,    82,    85,    92,    -1,    67,    50,    62,
      -1,    62,    -1,     7,    69,    -1,    -1,    69,    70,    -1,
      70,    -1,    62,    44,    71,    51,    -1,    58,    -1,    59,
      -1,    60,    -1,    61,    -1,    26,    73,    -1,    -1,    73,
      74,    -1,    74,    -1,    62,    44,    75,    51,    -1,    76,
      -1,    77,    -1,    78,    -1,    79,    -1,    32,    -1,    35,
      -1,    33,    -1,    34,    -1,    62,    -1,    56,    67,    57,
      -1,    71,    49,    71,    -1,     4,    54,    77,    55,    18,
      75,    -1,    22,    80,    12,    -1,    80,    51,    81,    -1,
      81,    -1,    62,    52,    75,    -1,    28,    83,    51,    -1,
      -1,    83,    51,    84,    -1,    84,    -1,    62,    52,    75,
      -1,    85,    86,    -1,    86,    -1,    -1,    87,    -1,    88,
      -1,    20,    62,    89,    51,    66,    51,    -1,    14,    62,
      89,    52,    76,    51,    66,    51,    -1,    56,    90,    57,
      -1,    56,    57,    -1,    90,    51,    91,    -1,    91,    -1,
      62,    52,    76,    -1,    93,    -1,     5,    94,    12,    -1,
      94,    96,    51,    -1,    -1,    61,    -1,    95,    52,    97,
      -1,    97,    -1,    98,    -1,   100,    -1,   101,    -1,   102,
      -1,   103,    -1,   106,    -1,   107,    -1,   110,    -1,    93,
      -1,    99,    53,   111,    -1,    62,    -1,    62,    54,   111,
      55,    -1,    62,    48,    62,    -1,    21,    56,   114,    57,
      -1,    30,    56,   111,    57,    -1,    62,    56,   115,    57,
      -1,    62,    -1,    16,   111,    24,    96,    11,    96,    -1,
      16,   111,    24,    96,    -1,    23,    94,    27,   111,    -1,
      -1,    13,    62,   104,    53,   111,   105,   111,     8,    96,
      -1,    25,    -1,     9,    -1,    29,   111,     8,    96,    -1,
       6,   111,    18,   108,    12,    -1,   108,    51,   109,    -1,
     109,    -1,    71,    52,    96,    -1,    15,    95,    -1,   111,
      42,   112,    -1,   111,    43,   112,    -1,   111,    44,   112,
      -1,   111,    46,   112,    -1,   111,    47,   112,    -1,   111,
      45,   112,    -1,   112,    -1,   112,    37,   113,    -1,   112,
      38,   113,    -1,   112,    10,   113,    -1,   112,    31,   113,
      -1,   113,    -1,   113,    39,   114,    -1,   113,    40,   114,
      -1,   113,    41,   114,    -1,   113,     3,   114,    -1,   114,
      -1,    62,    -1,    62,    56,   115,    57,    -1,    62,    54,
     111,    55,    -1,    62,    48,    62,    -1,    71,    -1,    56,
     111,    57,    -1,    38,   114,    -1,    17,   114,    -1,   115,
      50,   111,    -1,   111,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    37,    37,    47,    55,    65,    76,    89,    94,   100,
     106,   114,   124,   129,   134,   139,   146,   151,   157,   163,
     171,   179,   184,   189,   194,   200,   205,   210,   215,   220,
     226,   232,   238,   244,   251,   257,   265,   274,   279,   285,
     291,   299,   308,   314,   321,   327,   332,   338,   346,   354,
     359,   366,   372,   380,   389,   397,   403,   410,   416,   425,
     433,   439,   444,   449,   454,   459,   464,   469,   474,   479,
     486,   492,   498,   504,   513,   522,   529,   537,   546,   551,
     558,   565,   565,   577,   583,   591,   598,   604,   610,   618,
     625,   636,   641,   646,   651,   656,   661,   666,   672,   677,
     682,   687,   692,   698,   703,   708,   713,   718,   724,   731,
     740,   748,   756,   761,   766,   772,   779,   785
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
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
  "constant_value", "type_definition_part", "type_definition_list",
  "type_definition", "type_denoter", "simple_type", "range_type",
  "array_type", "record_type", "field_definition_list", "field_definition",
  "variable_declaration_part", "variable_declaration_list",
  "variable_declaration", "procedure_function_declaration_part",
  "procedure_function_declaration", "procedure_declaration",
  "function_declaration", "parameters", "parameter_list", "parameter",
  "block_body_part", "compound_statement", "statememt_list", "label",
  "statememt", "stmt", "assign_statememt", "variable_access",
  "procedure_statement", "if_statememt", "repeat_statememt",
  "for_statememt", "$@1", "direction", "while_statememt", "case_statememt",
  "case_list", "case_item", "goto_statememt", "expression", "expr", "term",
  "factor", "args", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
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

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
        {
                0,    63,    64,    65,    66,    67,    67,    68,    68,    69,
                69,    70,    71,    71,    71,    71,    72,    72,    73,    73,
                74,    75,    75,    75,    75,    76,    76,    76,    76,    76,
                76,    77,    78,    79,    80,    80,    81,    82,    82,    83,
                83,    84,    85,    85,    85,    86,    86,    87,    88,    89,
                89,    90,    90,    91,    92,    93,    94,    94,    95,    96,
                96,    97,    97,    97,    97,    97,    97,    97,    97,    97,
                98,    99,    99,    99,   100,   100,   100,   100,   101,   101,
                102,   104,   103,   105,   105,   106,   107,   108,   108,   109,
                110,   111,   111,   111,   111,   111,   111,   111,   112,   112,
                112,   112,   112,   113,   113,   113,   113,   113,   114,   114,
                114,   114,   114,   114,   114,   114,   115,   115
        };

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
        {
                0,     2,     4,     2,     5,     3,     1,     2,     0,     2,
                1,     4,     1,     1,     1,     1,     2,     0,     2,     1,
                4,     1,     1,     1,     1,     1,     1,     1,     1,     1,
                3,     3,     6,     3,     3,     1,     3,     3,     0,     3,
                1,     3,     2,     1,     0,     1,     1,     6,     8,     3,
                2,     3,     1,     3,     1,     3,     3,     0,     1,     3,
                1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
                3,     1,     4,     3,     4,     4,     4,     1,     6,     4,
                4,     0,     9,     1,     1,     4,     5,     3,     1,     3,
                2,     3,     3,     3,     3,     3,     3,     1,     3,     3,
                3,     3,     1,     3,     3,     3,     3,     1,     1,     4,
                4,     3,     1,     3,     2,     2,     3,     1
        };

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
        {
                0,     0,     0,     0,     3,     1,     8,     0,     0,    17,
                0,     7,    10,     2,     0,    38,     0,     9,     0,    16,
                19,     0,    44,    12,    13,    14,    15,     0,     0,    18,
                0,     0,    40,     0,     0,     0,    43,    45,    46,    11,
                0,     0,    25,    27,    28,    26,     0,    29,     0,     0,
                21,    22,    23,    24,     0,    37,     0,     0,    57,    42,
                4,    54,     0,     0,     0,    35,     6,     0,     0,    20,
                41,    39,     0,     0,     0,     0,     0,     0,    33,     0,
                0,    30,    31,    50,     0,     0,    52,     0,     8,     0,
                55,     0,     0,     0,     0,    57,     0,     0,    58,    77,
                69,     0,     0,    60,    61,     0,    62,    63,    64,    65,
                66,    67,    68,     0,    36,    34,     5,     0,     0,    49,
                0,     0,     0,     0,     0,   108,   112,     0,    97,   102,
                107,    81,    90,     0,     0,     0,     0,     0,     0,     0,
                0,     0,    56,     0,     0,    53,    51,     8,    47,   115,
                114,     0,     0,     0,     0,     0,     0,     0,     0,     0,
                0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
                0,     0,     0,     0,     0,     0,    73,     0,   117,     0,
                59,    70,    32,     0,   113,   111,     0,     0,     0,     0,
                88,    91,    92,    93,    96,    94,    95,   100,   101,    98,
                99,   106,   103,   104,   105,     0,    79,    74,    80,    85,
                75,    72,     0,    76,    48,   110,   109,     0,    86,     0,
                0,     0,   116,    89,    87,    84,    83,     0,    78,     0,
                0,    82
        };

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
        {
                -1,     2,     3,     8,    67,     9,    11,    12,   126,    15,
                19,    20,    49,    50,    51,    52,    53,    64,    65,    22,
                31,    32,    35,    36,    37,    38,    73,    85,    86,    60,
                100,    75,   101,   102,   103,   104,   105,   106,   107,   108,
                109,   170,   227,   110,   111,   189,   190,   112,   178,   128,
                129,   130,   179
        };

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -167
static const yytype_int16 yypact[] =
        {
                -10,   -55,    20,   -33,  -167,  -167,    25,     4,    19,    42,
                1,     4,  -167,  -167,    31,    67,    72,  -167,    62,    31,
                -167,    50,    78,  -167,  -167,  -167,  -167,    63,    15,  -167,
                61,    65,  -167,    56,    58,    -3,  -167,  -167,  -167,  -167,
                82,    76,  -167,  -167,  -167,  -167,    91,  -167,   105,   117,
                -167,  -167,  -167,  -167,    15,    50,    71,    71,  -167,  -167,
                -167,  -167,    72,   121,    -8,  -167,  -167,    30,    72,  -167,
                -167,  -167,   -28,   123,   125,    73,   128,    15,  -167,    76,
                138,  -167,  -167,  -167,   150,    12,  -167,    49,    25,   102,
                -167,   139,   143,   102,   157,  -167,   102,   159,  -167,   -26,
                -167,   153,   155,  -167,  -167,   163,  -167,  -167,  -167,  -167,
                -167,  -167,  -167,   199,  -167,  -167,  -167,    49,   156,  -167,
                168,   170,   102,   102,   102,   -12,  -167,   149,   189,    18,
                -167,  -167,  -167,   190,   102,    94,   135,   102,   160,   102,
                102,    10,  -167,   102,    15,  -167,  -167,    25,  -167,  -167,
                -167,   196,   161,   102,   102,    72,   102,   102,   102,   102,
                102,   102,   102,   102,   102,   102,   102,   102,   102,   102,
                171,   136,   172,   102,   136,   202,  -167,   218,   238,    47,
                -167,   238,  -167,   174,  -167,  -167,   224,    51,   176,     2,
                -167,   189,   189,   189,   189,   189,   189,    18,    18,    18,
                18,  -167,  -167,  -167,  -167,   102,   219,  -167,   238,  -167,
                -167,  -167,   102,  -167,  -167,  -167,  -167,   136,  -167,    72,
                165,   136,   238,  -167,  -167,  -167,  -167,   102,  -167,   142,
                136,  -167
        };

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
        {
                -167,  -167,  -167,   -85,  -167,  -167,  -167,   220,   -16,  -167,
                -167,   231,   -53,   -52,   192,  -167,  -167,  -167,   173,  -167,
                -167,   200,  -167,   216,  -167,  -167,   201,  -167,   154,  -167,
                221,   162,   182,  -166,   134,  -167,  -167,  -167,  -167,  -167,
                -167,  -167,  -167,  -167,  -167,  -167,    57,  -167,   -83,   130,
                -17,     3,   124
        };

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -72
static const yytype_int16 yytable[] =
        {
                27,    70,    58,   121,    78,   206,   127,     4,   209,     1,
                133,    33,    48,   136,   218,    58,    89,    34,     6,    40,
                5,   166,   138,    91,   114,    92,    93,   -71,   139,    83,
                140,    94,     7,    95,    84,   120,   152,    41,    48,    96,
                97,   151,   153,    79,   154,    16,    48,    42,    43,    44,
                45,   223,    82,   219,   175,   228,   177,   167,   168,   169,
                181,    48,   183,   118,   231,   145,    10,    13,    14,   119,
                186,    46,    99,    23,    24,    25,    26,    47,    58,    89,
                80,    42,    43,    44,    45,    90,    91,    81,    92,    93,
                208,   182,    33,    18,    94,    21,    95,   212,    34,    58,
                89,   212,    96,    97,   213,    46,    28,    91,   216,    92,
                93,    47,    30,    54,    39,    94,    55,    95,    56,   122,
                57,   173,   220,    96,    97,   149,   150,    72,    48,   222,
                23,    24,    25,    26,    98,    99,    62,   172,    63,   188,
                123,    58,    89,   174,   229,   197,   198,   199,   200,    91,
                230,    92,    93,    66,    68,    98,    99,    94,   124,    95,
                23,    24,    25,    26,   125,    96,    97,   155,    69,   201,
                202,   203,   204,    77,   225,    87,    88,   156,   157,   158,
                159,   160,   161,   113,   156,   157,   158,   159,   160,   161,
                226,   156,   157,   158,   159,   160,   161,    98,    99,   162,
                116,   131,   117,   188,    98,   141,   142,   156,   157,   158,
                159,   160,   161,   134,   171,   137,   143,   144,    84,   147,
                163,   148,   176,   185,   205,   214,   164,   165,   217,   207,
                221,    17,   156,   157,   158,   159,   160,   161,   156,   157,
                158,   159,   160,   161,   156,   157,   158,   159,   160,   161,
                29,    59,   115,   184,    76,    71,    61,   135,    74,   210,
                156,   157,   158,   159,   160,   161,   156,   157,   158,   159,
                160,   161,   146,   211,   132,   180,   224,     0,   187,   215,
                156,   157,   158,   159,   160,   161,   191,   192,   193,   194,
                195,   196
        };

#define yypact_value_is_default(yystate) \
  ((yystate) == (-167))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
        {
                16,    54,     5,    88,    12,   171,    89,    62,   174,    19,
                93,    14,    28,    96,    12,     5,     6,    20,    51,     4,
                0,     3,    48,    13,    77,    15,    16,    53,    54,    57,
                56,    21,     7,    23,    62,    87,    48,    22,    54,    29,
                30,   124,    54,    51,    56,    44,    62,    32,    33,    34,
                35,   217,    68,    51,   137,   221,   139,    39,    40,    41,
                143,    77,   147,    51,   230,   117,    62,    48,    26,    57,
                153,    56,    62,    58,    59,    60,    61,    62,     5,     6,
                50,    32,    33,    34,    35,    12,    13,    57,    15,    16,
                173,   144,    14,    62,    21,    28,    23,    50,    20,     5,
                6,    50,    29,    30,    57,    56,    44,    13,    57,    15,
                16,    62,    62,    52,    51,    21,    51,    23,    62,    17,
                62,    27,   205,    29,    30,   122,   123,    56,   144,   212,
                58,    59,    60,    61,    61,    62,    54,   134,    62,   155,
                38,     5,     6,     8,   227,   162,   163,   164,   165,    13,
                8,    15,    16,    62,    49,    61,    62,    21,    56,    23,
                58,    59,    60,    61,    62,    29,    30,    18,    51,   166,
                167,   168,   169,    52,     9,    52,    51,    42,    43,    44,
                45,    46,    47,    55,    42,    43,    44,    45,    46,    47,
                25,    42,    43,    44,    45,    46,    47,    61,    62,    10,
                62,    62,    52,   219,    61,    52,    51,    42,    43,    44,
                45,    46,    47,    56,    24,    56,    53,    18,    62,    51,
                31,    51,    62,    62,    53,    51,    37,    38,    52,    57,
                11,    11,    42,    43,    44,    45,    46,    47,    42,    43,
                44,    45,    46,    47,    42,    43,    44,    45,    46,    47,
                19,    35,    79,    57,    62,    55,    35,    95,    57,    57,
                42,    43,    44,    45,    46,    47,    42,    43,    44,    45,
                46,    47,   118,    55,    92,   141,   219,    -1,   154,    55,
                42,    43,    44,    45,    46,    47,   156,   157,   158,   159,
                160,   161
        };

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
        {
                0,    19,    64,    65,    62,     0,    51,     7,    66,    68,
                62,    69,    70,    48,    26,    72,    44,    70,    62,    73,
                74,    28,    82,    58,    59,    60,    61,    71,    44,    74,
                62,    83,    84,    14,    20,    85,    86,    87,    88,    51,
                4,    22,    32,    33,    34,    35,    56,    62,    71,    75,
                76,    77,    78,    79,    52,    51,    62,    62,     5,    86,
                92,    93,    54,    62,    80,    81,    62,    67,    49,    51,
                75,    84,    56,    89,    89,    94,    77,    52,    12,    51,
                50,    57,    71,    57,    62,    90,    91,    52,    51,     6,
                12,    13,    15,    16,    21,    23,    29,    30,    61,    62,
                93,    95,    96,    97,    98,    99,   100,   101,   102,   103,
                106,   107,   110,    55,    75,    81,    62,    52,    51,    57,
                76,    66,    17,    38,    56,    62,    71,   111,   112,   113,
                114,    62,    95,   111,    56,    94,   111,    56,    48,    54,
                56,    52,    51,    53,    18,    76,    91,    51,    51,   114,
                114,   111,    48,    54,    56,    18,    42,    43,    44,    45,
                46,    47,    10,    31,    37,    38,     3,    39,    40,    41,
                104,    24,   114,    27,     8,   111,    62,   111,   111,   115,
                97,   111,    75,    66,    57,    62,   111,   115,    71,   108,
                109,   112,   112,   112,   112,   112,   112,   113,   113,   113,
                113,   114,   114,   114,   114,    53,    96,    57,   111,    96,
                57,    55,    50,    57,    51,    55,    57,    52,    12,    51,
                111,    11,   111,    96,   109,     9,    25,   105,    96,   111,
                8,    96
        };

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
/* This is here to suppress warnings from the GCC cpp's
   -Wunused-macros.  Normally we don't worry about that warning, but
   some users do, and we want to make it easy for users to remove
   YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* This macro is provided for backward compatibility. */

#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

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
#ifndef	YYINITDEPTH
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
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
  YYSIZE_T yysize0 = yytnamerr (0, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  YYSIZE_T yysize1;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = 0;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
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
                yysize1 = yysize + yytnamerr (0, yytname[yyx]);
                if (! (yysize <= yysize1
                       && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                  return 2;
                yysize = yysize1;
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

  yysize1 = yysize + yystrlen (yyformat);
  if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
    return 2;
  yysize = yysize1;

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

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
    YYUSE (yyvaluep);

    if (!yymsg)
        yymsg = "Deleting";
    YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

    switch (yytype)
    {

        default:
            break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
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
    int yytoken;
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

    yytoken = 0;
    yyss = yyssa;
    yyvs = yyvsa;
    yystacksize = YYINITDEPTH;

    YYDPRINTF ((stderr, "Starting parse\n"));

    yystate = 0;
    yyerrstatus = 0;
    yynerrs = 0;
    yychar = YYEMPTY; /* Cause a token to be read.  */

    /* Initialize stack pointers.
       Waste one element of value and location stack
       so that they stay on the same level as the state stack.
       The wasted elements are never initialized.  */
    yyssp = yyss;
    yyvsp = yyvs;

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
        yychar = YYLEX;
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
    *++yyvsp = yylval;

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
       `$$ = $1'.

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

/* Line 1806 of yacc.c  */
#line 38 "test.y"
        {
            showNodeInfo("program -> program_head SEMICOLON block DOT");
            (yyval) = (yyvsp[(3) - (4)]);
            (yyvsp[(3) - (4)])->setName((yyvsp[(1) - (4)])->getName());
            delete (yyvsp[(1) - (4)]);

            root = (yyval);
        }
            break;

        case 3:

/* Line 1806 of yacc.c  */
#line 48 "test.y"
        {
            showNodeInfo("program_head -> PROGRAM ID");
            (yyval) = new TreeNode();
            (yyval)->setName((yyvsp[(2) - (2)])->getName());
            delete (yyvsp[(2) - (2)]);
        }
            break;

        case 4:

/* Line 1806 of yacc.c  */
#line 60 "test.y"
        {
            showNodeInfo("block -> constant_definition_part type_definition_part variable_declaration_part procedure_function_declaration_part block_body_part");
            (yyval) = new ProgramBodyTreeNode((yyvsp[(1) - (5)]), (yyvsp[(2) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(4) - (5)]), (yyvsp[(5) - (5)]));
        }
            break;

        case 5:

/* Line 1806 of yacc.c  */
#line 66 "test.y"
        {
            showNodeInfo("id_list -> id_list COMMA ID");
            (yyval) = (yyvsp[(1) - (3)]);
            std::string name = (yyvsp[(3) - (3)])->getName();
            TreeNode* node = new TreeNode();
            node->setName(name);

            ((ListTreeNode*)(yyval))->insert(node);
            delete (yyvsp[(3) - (3)]);
        }
            break;

        case 6:

/* Line 1806 of yacc.c  */
#line 77 "test.y"
        {
            showNodeInfo("id_list -> ID");
            std::string name = (yyvsp[(1) - (1)])->getName();
            std::vector<TreeNode*> list;
            TreeNode* node = new TreeNode();
            node->setName(name);
            list.push_back(node);
            delete (yyvsp[(1) - (1)]);
            (yyval) = new ListTreeNode("id_list", list);
        }
            break;

        case 7:

/* Line 1806 of yacc.c  */
#line 90 "test.y"
        {
            showNodeInfo("constant_definition_part -> CONST constant_list");
            (yyval) = (yyvsp[(2) - (2)]);
        }
            break;

        case 8:

/* Line 1806 of yacc.c  */
#line 94 "test.y"
        {
            showNodeInfo("constant_definition_part ->");
            std::vector<TreeNode*> list;
            (yyval) = new ListTreeNode("constant_definition_part", list);
        }
            break;

        case 9:

/* Line 1806 of yacc.c  */
#line 101 "test.y"
        {
            showNodeInfo("constant_list -> constant_list constant_definition");
            (yyval) = (yyvsp[(1) - (2)]);
            ((ListTreeNode*)(yyval))->insert((yyvsp[(2) - (2)]));
        }
            break;

        case 10:

/* Line 1806 of yacc.c  */
#line 107 "test.y"
        {
            showNodeInfo("constant_list -> constant_definition");
            std::vector<TreeNode*> list;
            list.push_back((yyvsp[(1) - (1)]));
            (yyval) = new ListTreeNode("constant_list", list);
        }
            break;

        case 11:

/* Line 1806 of yacc.c  */
#line 115 "test.y"
        {
            showNodeInfo("constant_definition -> ID EQUAL constant_value SEMICOLON");
            std::string name = (yyvsp[(1) - (4)])->getName();
            VariableTreeNode* varNode = new VariableTreeNode(name, nullptr, true);
            BinaryExprTreeNode* binNode = new BinaryExprTreeNode(":=", varNode, (yyvsp[(3) - (4)]));
            (yyval) = binNode;
            delete (yyvsp[(1) - (4)]);
        }
            break;

        case 12:

/* Line 1806 of yacc.c  */
#line 125 "test.y"
        {
            showNodeInfo("constant_value -> INTEGER");
            (yyval) = new LiteralTreeNode(yytext, "integer");
        }
            break;

        case 13:

/* Line 1806 of yacc.c  */
#line 130 "test.y"
        {
            showNodeInfo("constant_value -> REAL");
            (yyval) = new LiteralTreeNode(yytext, "real");
        }
            break;

        case 14:

/* Line 1806 of yacc.c  */
#line 135 "test.y"
        {
            showNodeInfo("constant_value -> CHAR");
            (yyval) = new LiteralTreeNode(yytext, "char");
        }
            break;

        case 15:

/* Line 1806 of yacc.c  */
#line 140 "test.y"
        {
            showNodeInfo("constant_value -> STRING");
            (yyval) = new LiteralTreeNode(yytext, "string");
        }
            break;

        case 16:

/* Line 1806 of yacc.c  */
#line 147 "test.y"
        {
            showNodeInfo("type_definition_part -> TYPE type_definition_list");
            (yyval) = (yyvsp[(2) - (2)]);
        }
            break;

        case 17:

/* Line 1806 of yacc.c  */
#line 151 "test.y"
        {
            showNodeInfo("type_definition_part -> ");
            std::vector<TreeNode*> list;
            (yyval) = new ListTreeNode("type_definition_part", list);
        }
            break;

        case 18:

/* Line 1806 of yacc.c  */
#line 158 "test.y"
        {
            showNodeInfo("type_definition_list -> type_definition_list type_definition");
            (yyval) = (yyvsp[(1) - (2)]);
            ((ListTreeNode*)(yyval))->insert((yyvsp[(1) - (2)]));
        }
            break;

        case 19:

/* Line 1806 of yacc.c  */
#line 164 "test.y"
        {
            showNodeInfo("type_definition_list -> type_definition");
            std::vector<TreeNode*> list;
            list.push_back((yyvsp[(1) - (1)]));
            (yyval) = new ListTreeNode("type_definition_list", list);
        }
            break;

        case 20:

/* Line 1806 of yacc.c  */
#line 172 "test.y"
        {
            showNodeInfo("type_definition -> ID EQUAL type_denoter SEMICOLON");
            std::string name = (yyvsp[(1) - (4)])->getName();
            (yyval) = new CustomTypeTreeNode(name, (yyvsp[(3) - (4)]));
            delete (yyvsp[(1) - (4)]);
        }
            break;

        case 21:

/* Line 1806 of yacc.c  */
#line 180 "test.y"
        {
            showNodeInfo("type_denoter -> simple_type");
            (yyval) = (yyvsp[(1) - (1)]);
        }
            break;

        case 22:

/* Line 1806 of yacc.c  */
#line 185 "test.y"
        {
            showNodeInfo("type_denoter -> range_type");
            (yyval) = (yyvsp[(1) - (1)]);
        }
            break;

        case 23:

/* Line 1806 of yacc.c  */
#line 190 "test.y"
        {
            showNodeInfo("type_denoter -> array_type");
            (yyval) = (yyvsp[(1) - (1)]);
        }
            break;

        case 24:

/* Line 1806 of yacc.c  */
#line 195 "test.y"
        {
            showNodeInfo("type_denoter -> record_type");
            (yyval) = (yyvsp[(1) - (1)]);
        }
            break;

        case 25:

/* Line 1806 of yacc.c  */
#line 201 "test.y"
        {
            showNodeInfo("simple_type -> TYPE_INTEGER");
            (yyval) = new CommonTypeTreeNode("integer");
        }
            break;

        case 26:

/* Line 1806 of yacc.c  */
#line 206 "test.y"
        {
            showNodeInfo("simple_type -> TYPE_CHAR");
            (yyval) = new CommonTypeTreeNode("char");
        }
            break;

        case 27:

/* Line 1806 of yacc.c  */
#line 211 "test.y"
        {
            showNodeInfo("simple_type -> TYPE_REAL");
            (yyval) = new CommonTypeTreeNode("real");
        }
            break;

        case 28:

/* Line 1806 of yacc.c  */
#line 216 "test.y"
        {
            showNodeInfo("simple_type -> TYPE_STRING");
            (yyval) = new CommonTypeTreeNode("string");
        }
            break;

        case 29:

/* Line 1806 of yacc.c  */
#line 221 "test.y"
        {
            showNodeInfo("simple_type -> ID");
            (yyval) = new CustomTypeTreeNode((yyvsp[(1) - (1)])->getName(), nullptr);
            delete (yyvsp[(1) - (1)]);
        }
            break;

        case 30:

/* Line 1806 of yacc.c  */
#line 227 "test.y"
        {
            showNodeInfo("simple_type -> LP id_list RP");
            (yyval) = new EnumTypeTreeNode((yyvsp[(2) - (3)]), "enum_type");
        }
            break;

        case 31:

/* Line 1806 of yacc.c  */
#line 233 "test.y"
        {
            showNodeInfo("range_type -> constant_value DOTDOT constant_value");
            (yyval) = new RangeTypeTreeNode((IDTreeNode*)(yyvsp[(3) - (3)]), (IDTreeNode*)(yyvsp[(1) - (3)]));
        }
            break;

        case 32:

/* Line 1806 of yacc.c  */
#line 239 "test.y"
        {
            showNodeInfo("array_type -> ARRAY LB range_type RB OF type_denoter");
            (yyval) = new ArrayTypeTreeNode((RangeTypeTreeNode*)(yyvsp[(3) - (6)]), (CommonTypeTreeNode*)(yyvsp[(6) - (6)]));
        }
            break;

        case 33:

/* Line 1806 of yacc.c  */
#line 245 "test.y"
        {
            showNodeInfo("record_type -> RECORD field_definition_list END");
            std::vector<TreeNode*> list = ((ListTreeNode*)(yyvsp[(2) - (3)]))->getList();
            (yyval) = new RecordTypeTreeNode(list);
        }
            break;

        case 34:

/* Line 1806 of yacc.c  */
#line 252 "test.y"
        {
            showNodeInfo("field_definition_list -> field_definition_list SEMICOLON field_definition");
            (yyval) = (yyvsp[(1) - (3)]);
            ((ListTreeNode*)(yyval))->insert((yyvsp[(3) - (3)]));
        }
            break;

        case 35:

/* Line 1806 of yacc.c  */
#line 258 "test.y"
        {
            showNodeInfo("field_definition_list -> field_definition");
            std::vector<TreeNode*> list;
            list.push_back((yyvsp[(1) - (1)]));
            (yyval) = new ListTreeNode("field_definition_list", list);
        }
            break;

        case 36:

/* Line 1806 of yacc.c  */
#line 266 "test.y"
        {
            showNodeInfo("field_definition -> ID COLON type_denoter");
            std::string name = (yyvsp[(1) - (3)])->getName();
            delete (yyvsp[(1) - (3)]);
            (yyval) = new VariableTreeNode(name, (yyvsp[(3) - (3)]));
        }
            break;

        case 37:

/* Line 1806 of yacc.c  */
#line 275 "test.y"
        {
            showNodeInfo("variable_declaration_part -> VAR variable_declaration_list SEMICOLON");
            (yyval) = (yyvsp[(2) - (3)]);
        }
            break;

        case 38:

/* Line 1806 of yacc.c  */
#line 279 "test.y"
        {
            showNodeInfo("variable_declaration_part ->");
            std::vector<TreeNode*> list;
            (yyval) = new ListTreeNode("variable_declaration_part", list);
        }
            break;

        case 39:

/* Line 1806 of yacc.c  */
#line 286 "test.y"
        {
            showNodeInfo("variable_declaration_list -> variable_declaration_list SEMICOLON variable_declaration");
            (yyval) = (yyvsp[(1) - (3)]);
            ((ListTreeNode*)(yyval))->insert((yyvsp[(3) - (3)]));
        }
            break;

        case 40:

/* Line 1806 of yacc.c  */
#line 292 "test.y"
        {
            showNodeInfo("variable_declaration_list -> variable_declaration");
            std::vector<TreeNode*> list;
            list.push_back((yyvsp[(1) - (1)]));
            (yyval) = new ListTreeNode("variable_declaration_list", list);
        }
            break;

        case 41:

/* Line 1806 of yacc.c  */
#line 300 "test.y"
        {
            showNodeInfo("variable_declaration -> ID COLON type_denoter");
            std::string name = (yyvsp[(1) - (3)])->getName();
            delete (yyvsp[(1) - (3)]);
            (yyval) = new VariableTreeNode(name, (yyvsp[(3) - (3)]));
        }
            break;

        case 42:

/* Line 1806 of yacc.c  */
#line 309 "test.y"
        {
            showNodeInfo("procedure_function_declaration_part -> procedure_function_declaration_part procedure_function_declaration");
            (yyval) = (yyvsp[(1) - (2)]);
            ((ListTreeNode*)(yyval))->insert((yyvsp[(2) - (2)]));
        }
            break;

        case 43:

/* Line 1806 of yacc.c  */
#line 315 "test.y"
        {
            showNodeInfo("procedure_function_declaration_part -> procedure_function_declaration");
            std::vector<TreeNode*> list;
            list.push_back((yyvsp[(1) - (1)]));
            (yyval) = new ListTreeNode("procedure_function_declaration_part", list);
        }
            break;

        case 44:

/* Line 1806 of yacc.c  */
#line 321 "test.y"
        {
            showNodeInfo("procedure_function_declaration_part ->");
            std::vector<TreeNode*> list;
            (yyval) = new ListTreeNode("procedure_function_declaration_part", list);
        }
            break;

        case 45:

/* Line 1806 of yacc.c  */
#line 328 "test.y"
        {
            showNodeInfo("procedure_function_declaration -> procedure_declaration ");
            (yyval) = (yyvsp[(1) - (1)]);
        }
            break;

        case 46:

/* Line 1806 of yacc.c  */
#line 333 "test.y"
        {
            showNodeInfo("procedure_function_declaration -> function_declaration");
            (yyval) = (yyvsp[(1) - (1)]);
        }
            break;

        case 47:

/* Line 1806 of yacc.c  */
#line 339 "test.y"
        {
            showNodeInfo("procedure_declaration -> PROCEDURE ID parameters SEMICOLON block SEMICOLON");
            std::string name = (yyvsp[(2) - (6)])->getName();
            delete (yyvsp[(2) - (6)]);
            (yyval) = new FuncOrProcTreeNode(name, (yyvsp[(3) - (6)]), (yyvsp[(5) - (6)]));
        }
            break;

        case 48:

/* Line 1806 of yacc.c  */
#line 347 "test.y"
        {
            showNodeInfo("function_declaration -> FUNCTION ID parameters COLON simple_type SEMICOLON block SEMICOLON");
            std::string name = (yyvsp[(2) - (8)])->getName();
            delete (yyvsp[(2) - (8)]);
            (yyval) = new FuncOrProcTreeNode(name, (yyvsp[(3) - (8)]), (yyvsp[(7) - (8)]), (yyvsp[(5) - (8)]), true);
        }
            break;

        case 49:

/* Line 1806 of yacc.c  */
#line 355 "test.y"
        {
            showNodeInfo("parameters -> LP parameter_list RP");
            (yyval) = (yyvsp[(2) - (3)]);
        }
            break;

        case 50:

/* Line 1806 of yacc.c  */
#line 360 "test.y"
        {
            showNodeInfo("parameters -> LP RP");
            std::vector<TreeNode*> emptyList;
            (yyval) = new ListTreeNode("parameters", emptyList);
        }
            break;

        case 51:

/* Line 1806 of yacc.c  */
#line 367 "test.y"
        {
            showNodeInfo("parameter_list -> parameter_list SEMICOLON parameter");
            (yyval) = (yyvsp[(1) - (3)]);
            ((ListTreeNode*)(yyval))->insert((yyvsp[(3) - (3)]));
        }
            break;

        case 52:

/* Line 1806 of yacc.c  */
#line 373 "test.y"
        {
            showNodeInfo("parameter_list -> parameter");
            std::vector<TreeNode*> list;
            list.push_back((yyvsp[(1) - (1)]));
            (yyval) = new ListTreeNode("parameter_list", list);
        }
            break;

        case 53:

/* Line 1806 of yacc.c  */
#line 381 "test.y"
        {
            showNodeInfo("parameter -> ID COLON simple_type");
            std::string name = (yyvsp[(1) - (3)])->getName();
            delete (yyvsp[(1) - (3)]);
            (yyval) = new VariableTreeNode(name, (yyvsp[(3) - (3)]));
        }
            break;

        case 54:

/* Line 1806 of yacc.c  */
#line 390 "test.y"
        {
            showNodeInfo("block_body_part -> compound_statement");
            std::vector<TreeNode*> body;
            body.push_back((yyvsp[(1) - (1)]));
            (yyval) = new ListTreeNode("block_body_part", body);
        }
            break;

        case 55:

/* Line 1806 of yacc.c  */
#line 398 "test.y"
        {
            showNodeInfo("compound_statement -> BEGIN_ statememt_list END");
            (yyval) = new CompoundStmtTreeNode((ListTreeNode*)(yyvsp[(2) - (3)]));
        }
            break;

        case 56:

/* Line 1806 of yacc.c  */
#line 404 "test.y"
        {
            showNodeInfo("statememt_list -> statememt_list statememt SEMICOLON");
            (yyval) = (yyvsp[(1) - (3)]);
            ((ListTreeNode*)(yyval))->insert((yyvsp[(2) - (3)]));
        }
            break;

        case 57:

/* Line 1806 of yacc.c  */
#line 410 "test.y"
        {
            showNodeInfo("statememt_list -> ");
            std::vector<TreeNode*> list;
            (yyval) = new ListTreeNode("statement_list", list);
        }
            break;

        case 58:

/* Line 1806 of yacc.c  */
#line 417 "test.y"
        {
            showNodeInfo("label -> STRING");
            std::string labelName = yytext;
            TreeNode* node = new TreeNode();
            node->setName(labelName);
            (yyval) = node;
        }
            break;

        case 59:

/* Line 1806 of yacc.c  */
#line 426 "test.y"
        {
            showNodeInfo("statement -> label COLON stmt");
            (yyval) = (yyvsp[(3) - (3)]);
            const std::string labelName = (yyvsp[(1) - (3)])->getName();
            ((StatementTreeNode*)(yyval))->setLabel(hashCodeForString(labelName));
            delete (yyvsp[(1) - (3)]);
        }
            break;

        case 60:

/* Line 1806 of yacc.c  */
#line 434 "test.y"
        {
            showNodeInfo("statement -> stmt");
            (yyval) = (yyvsp[(1) - (1)]);
        }
            break;

        case 61:

/* Line 1806 of yacc.c  */
#line 440 "test.y"
        {
            showNodeInfo("stmt -> assign_statememt");
            (yyval) = (yyvsp[(1) - (1)]);
        }
            break;

        case 62:

/* Line 1806 of yacc.c  */
#line 445 "test.y"
        {
            showNodeInfo("stmt -> procedure_statement");
            (yyval) = (yyvsp[(1) - (1)]);
        }
            break;

        case 63:

/* Line 1806 of yacc.c  */
#line 450 "test.y"
        {
            showNodeInfo("stmt -> if_statememt");
            (yyval) = (yyvsp[(1) - (1)]);
        }
            break;

        case 64:

/* Line 1806 of yacc.c  */
#line 455 "test.y"
        {
            showNodeInfo("stmt -> repeat_statement");
            (yyval) = (yyvsp[(1) - (1)]);
        }
            break;

        case 65:

/* Line 1806 of yacc.c  */
#line 460 "test.y"
        {
            showNodeInfo("stmt -> for_statememt");
            (yyval) = (yyvsp[(1) - (1)]);
        }
            break;

        case 66:

/* Line 1806 of yacc.c  */
#line 465 "test.y"
        {
            showNodeInfo("stmt -> while_statememt");
            (yyval) = (yyvsp[(1) - (1)]);
        }
            break;

        case 67:

/* Line 1806 of yacc.c  */
#line 470 "test.y"
        {
            showNodeInfo("stmt -> case_statememt");
            (yyval) = (yyvsp[(1) - (1)]);
        }
            break;

        case 68:

/* Line 1806 of yacc.c  */
#line 475 "test.y"
        {
            showNodeInfo("stmt -> goto_statememt");
            (yyval) = (yyvsp[(1) - (1)]);
        }
            break;

        case 69:

/* Line 1806 of yacc.c  */
#line 480 "test.y"
        {
            showNodeInfo("stmt -> compound_statement");
            (yyval) = (yyvsp[(1) - (1)]);
        }
            break;

        case 70:

/* Line 1806 of yacc.c  */
#line 487 "test.y"
        {
            showNodeInfo("assign_statememt -> variable_access ASSIGN expression");
            (yyval) = new BinaryExprTreeNode(":=", (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
        }
            break;

        case 71:

/* Line 1806 of yacc.c  */
#line 493 "test.y"
        {
            showNodeInfo("variable_access -> ID");
            (yyval) = new VariableTreeNode((yyvsp[(1) - (1)])->getName());
            delete (yyvsp[(1) - (1)]);
        }
            break;

        case 72:

/* Line 1806 of yacc.c  */
#line 499 "test.y"
        {
            showNodeInfo("variable_access -> ID LB expression RB");
            std::string arrayName = (yyvsp[(1) - (4)])->getName();
            (yyval) = new ArrayElemTreeNode(arrayName, (yyvsp[(3) - (4)]));
        }
            break;

        case 73:

/* Line 1806 of yacc.c  */
#line 505 "test.y"
        {
            showNodeInfo("variable_access -> ID DOT ID");
            (yyval) = new RecordElemTreeNode((yyvsp[(1) - (3)])->getName(), (yyvsp[(3) - (3)])->getName());
            delete (yyvsp[(1) - (3)]);
            delete (yyvsp[(3) - (3)]);
        }
            break;

        case 74:

/* Line 1806 of yacc.c  */
#line 514 "test.y"
        {
            showNodeInfo("procedure_statement -> READ LP factor RP");
            // You need to release it and make it NULL
            std::vector<TreeNode*>* list = new std::vector<TreeNode*>;
            list->push_back((yyvsp[(3) - (4)]));
            (yyval) = new CallExprTreeNode("read", list, false);

        }
            break;

        case 75:

/* Line 1806 of yacc.c  */
#line 523 "test.y"
        {
            showNodeInfo("procedure_statement -> WRITE LP expression RP");
            std::vector<TreeNode*>* list = new std::vector<TreeNode*>;
            list->push_back((yyvsp[(3) - (4)]));
            (yyval) = new CallExprTreeNode("write", list, false);
        }
            break;

        case 76:

/* Line 1806 of yacc.c  */
#line 530 "test.y"
        {
            showNodeInfo("procedure_statement -> ID LP args RP");
            std::string procName = (yyvsp[(1) - (4)])->getName();
            delete (yyvsp[(1) - (4)]);
            (yyval) = new CallExprTreeNode(procName, &(((ListTreeNode*)(yyvsp[(3) - (4)]))->getList()),
                                           false);
        }
            break;

        case 77:

/* Line 1806 of yacc.c  */
#line 538 "test.y"
        {
            showNodeInfo("procedure_statement -> ID");
            std::string procName = (yyvsp[(1) - (1)])->getName();
            delete (yyvsp[(1) - (1)]);
            (yyval) = new CallExprTreeNode(procName, nullptr, false);
        }
            break;

        case 78:

/* Line 1806 of yacc.c  */
#line 547 "test.y"
        {
            showNodeInfo("if_statememt -> IF expression THEN statememt ELSE statememt");
            (yyval) = new IfStmtTreeNode((ExprTreeNode*)(yyvsp[(2) - (6)]), (StatementTreeNode*)(yyvsp[(4) - (6)]), (StatementTreeNode*)(yyvsp[(6) - (6)]));
        }
            break;

        case 79:

/* Line 1806 of yacc.c  */
#line 552 "test.y"
        {
            showNodeInfo("if_statememt -> IF expression THEN statememt");
            (yyval) = new IfStmtTreeNode((ExprTreeNode*)(yyvsp[(2) - (4)]), (StatementTreeNode*)(yyvsp[(4) - (4)]), nullptr);
        }
            break;

        case 80:

/* Line 1806 of yacc.c  */
#line 559 "test.y"
        {
            showNodeInfo("repeat_statememt -> REPEAT statememt_list UNTIL expression");
            (yyval) = new RepeatStmtTreeNode((ExprTreeNode *)(yyvsp[(4) - (4)]), (StatementTreeNode *)(yyvsp[(2) - (4)]));
        }
            break;

        case 81:

/* Line 1806 of yacc.c  */
#line 565 "test.y"
        { stringQueue.push(yytext); }
            break;

        case 82:

/* Line 1806 of yacc.c  */
#line 566 "test.y"
        {
            showNodeInfo("for_statement -> FOR ID ASSIGN expression direction expression DO statememt");
            std::string variableId = (yyvsp[(2) - (9)])->getName();
            delete (yyvsp[(2) - (9)]);
            VariableTreeNode* varNode = new VariableTreeNode(variableId);
            BinaryExprTreeNode* exprNode = new BinaryExprTreeNode(":=", varNode, (yyvsp[(5) - (9)]));
            std::string direction = (yyvsp[(6) - (9)])->getName();
            (yyval) = new ForStmtTreeNode(exprNode, direction, (yyvsp[(7) - (9)]), (StatementTreeNode *)(yyvsp[(9) - (9)]));
            delete (yyvsp[(6) - (9)]);
        }
            break;

        case 83:

/* Line 1806 of yacc.c  */
#line 578 "test.y"
        {
            showNodeInfo("direction -> TO");
            (yyval) = new TreeNode();
            (yyval)->setName("to");
        }
            break;

        case 84:

/* Line 1806 of yacc.c  */
#line 584 "test.y"
        {
            showNodeInfo("direction -> DOWNTO");
            (yyval) = new TreeNode();
            (yyval)->setName("downto");
        }
            break;

        case 85:

/* Line 1806 of yacc.c  */
#line 592 "test.y"
        {
            showNodeInfo("while_statement -> WHILE expression DO statement");
            (yyval) = new WhileStmtTreeNode((ExprTreeNode *)(yyvsp[(2) - (4)]), (StatementTreeNode *)(yyvsp[(4) - (4)]));
        }
            break;

        case 86:

/* Line 1806 of yacc.c  */
#line 599 "test.y"
        {
            showNodeInfo("case_statement -> CASE expresion OF case_list END");
            (yyval) = new SwitchStmtTreeNode((ExprTreeNode *)(yyvsp[(2) - (5)]), (ListTreeNode *)(yyvsp[(4) - (5)]));
        }
            break;

        case 87:

/* Line 1806 of yacc.c  */
#line 605 "test.y"
        {
            showNodeInfo("case_list -> case_list SEMICOLON case_item");
            (yyval) = (yyvsp[(1) - (3)]);
            ((ListTreeNode*)(yyval))->insert((yyvsp[(3) - (3)]));
        }
            break;

        case 88:

/* Line 1806 of yacc.c  */
#line 611 "test.y"
        {
            showNodeInfo("case_list -> case_item");
            std::vector<TreeNode*> list;
            list.push_back((yyvsp[(1) - (1)]));
            (yyval) = new ListTreeNode("case_list", list);
        }
            break;

        case 89:

/* Line 1806 of yacc.c  */
#line 619 "test.y"
        {
            showNodeInfo("case_item -> constant_value COLON statement");
            (yyval) = new CaseExprTreeNode((IDTreeNode *)(yyvsp[(1) - (3)]), (StatementTreeNode *)(yyvsp[(3) - (3)]));
        }
            break;

        case 90:

/* Line 1806 of yacc.c  */
#line 626 "test.y"
        {
            showNodeInfo("goto_statememt -> GOTO label");
            std::string labelName = (yyvsp[(2) - (2)])->getName();
            // you need to hash the labelName
            (yyval) = new GotoStmtTreeNode(labelName);
            // remove tree node created for label
            delete (yyvsp[(2) - (2)]);
        }
            break;

        case 91:

/* Line 1806 of yacc.c  */
#line 637 "test.y"
        {
            showNodeInfo("expression -> expression LT expr");
            (yyval) = new BinaryExprTreeNode("<", (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
        }
            break;

        case 92:

/* Line 1806 of yacc.c  */
#line 642 "test.y"
        {
            showNodeInfo("expression -> expression LE expr");
            (yyval) = new BinaryExprTreeNode("<=", (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
        }
            break;

        case 93:

/* Line 1806 of yacc.c  */
#line 647 "test.y"
        {
            showNodeInfo("expression -> expression EQUAL expr");
            (yyval) = new BinaryExprTreeNode("=", (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
        }
            break;

        case 94:

/* Line 1806 of yacc.c  */
#line 652 "test.y"
        {
            showNodeInfo("expression -> expression GE expr");
            (yyval) = new BinaryExprTreeNode(">=", (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
        }
            break;

        case 95:

/* Line 1806 of yacc.c  */
#line 657 "test.y"
        {
            showNodeInfo("expression -> expression GT expr");
            (yyval) = new BinaryExprTreeNode(">", (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
        }
            break;

        case 96:

/* Line 1806 of yacc.c  */
#line 662 "test.y"
        {
            showNodeInfo("expression -> expression UNEQUAL expr");
            (yyval) = new BinaryExprTreeNode("!=", (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
        }
            break;

        case 97:

/* Line 1806 of yacc.c  */
#line 667 "test.y"
        {
            showNodeInfo("expression -> expr");
            (yyval) = (yyvsp[(1) - (1)]);
        }
            break;

        case 98:

/* Line 1806 of yacc.c  */
#line 673 "test.y"
        {
            showNodeInfo("expr -> expr PLUS term");
            (yyval) = new BinaryExprTreeNode("+", (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
        }
            break;

        case 99:

/* Line 1806 of yacc.c  */
#line 678 "test.y"
        {
            showNodeInfo("expr -> expr MNUS term");
            (yyval) = new BinaryExprTreeNode("-", (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
        }
            break;

        case 100:

/* Line 1806 of yacc.c  */
#line 683 "test.y"
        {
            showNodeInfo("expr -> expr OR term");
            (yyval) = new BinaryExprTreeNode("or", (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
        }
            break;

        case 101:

/* Line 1806 of yacc.c  */
#line 688 "test.y"
        {
            showNodeInfo("expr -> expr XOR term");
            (yyval) = new BinaryExprTreeNode("xor", (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
        }
            break;

        case 102:

/* Line 1806 of yacc.c  */
#line 693 "test.y"
        {
            showNodeInfo("expr -> term");
            (yyval) = (yyvsp[(1) - (1)]);
        }
            break;

        case 103:

/* Line 1806 of yacc.c  */
#line 699 "test.y"
        {
            showNodeInfo("term -> term MULTIPLY factor");
            (yyval) = new BinaryExprTreeNode("*", (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
        }
            break;

        case 104:

/* Line 1806 of yacc.c  */
#line 704 "test.y"
        {
            showNodeInfo("term -> term DIVIDE factor");
            (yyval) = new BinaryExprTreeNode("/", (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
        }
            break;

        case 105:

/* Line 1806 of yacc.c  */
#line 709 "test.y"
        {
            showNodeInfo("term -> term MOD factor");
            (yyval) = new BinaryExprTreeNode("%", (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
        }
            break;

        case 106:

/* Line 1806 of yacc.c  */
#line 714 "test.y"
        {
            showNodeInfo("term -> term AND factor");
            (yyval) = new BinaryExprTreeNode("and", (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
        }
            break;

        case 107:

/* Line 1806 of yacc.c  */
#line 719 "test.y"
        {
            showNodeInfo("term -> factor");
            (yyval) = (yyvsp[(1) - (1)]);
        }
            break;

        case 108:

/* Line 1806 of yacc.c  */
#line 725 "test.y"
        {
            // Simple variable
            showNodeInfo("factor -> ID");
            (yyval) = new VariableTreeNode((yyvsp[(1) - (1)])->getName());
            delete (yyvsp[(1) - (1)]);
        }
            break;

        case 109:

/* Line 1806 of yacc.c  */
#line 732 "test.y"
        {
            // Function value
            showNodeInfo("factor -> ID LP args RP");
            std::string functionName = (yyvsp[(1) - (4)])->getName();
            delete (yyvsp[(1) - (4)]);
            (yyval) = new CallExprTreeNode(functionName,
                                           &(((ListTreeNode*)(yyvsp[(3) - (4)]))->getList()));
        }
            break;

        case 110:

/* Line 1806 of yacc.c  */
#line 741 "test.y"
        {
            // Array Element
            showNodeInfo("factor -> ID LB expression RB");
            std::string arrayName = (yyvsp[(1) - (4)])->getName();
            delete (yyvsp[(1) - (4)]);
            (yyval) = new ArrayElemTreeNode(arrayName, (yyvsp[(3) - (4)]));
        }
            break;

        case 111:

/* Line 1806 of yacc.c  */
#line 749 "test.y"
        {
            // Record element
            showNodeInfo("factor -> ID DOT ID");
            (yyval) = new RecordElemTreeNode((yyvsp[(1) - (3)])->getName(), (yyvsp[(3) - (3)])->getName());
            delete (yyvsp[(1) - (3)]);
            delete (yyvsp[(3) - (3)]);
        }
            break;

        case 112:

/* Line 1806 of yacc.c  */
#line 757 "test.y"
        {
            showNodeInfo("factor -> constant_value");
            (yyval) = (yyvsp[(1) - (1)]);
        }
            break;

        case 113:

/* Line 1806 of yacc.c  */
#line 762 "test.y"
        {
            showNodeInfo("factor -> LP expression RP");
            (yyval) = (yyvsp[(2) - (3)]);
        }
            break;

        case 114:

/* Line 1806 of yacc.c  */
#line 767 "test.y"
        {
            // Negative value
            showNodeInfo("factor -> MINUS factor");
            (yyval) = new UnaryExprTreeNode("-", (yyvsp[(2) - (2)]));
        }
            break;

        case 115:

/* Line 1806 of yacc.c  */
#line 773 "test.y"
        {
            // Not value for bit..
            showNodeInfo("factor -> NOT factor");
            (yyval) = new UnaryExprTreeNode("not", (yyvsp[(2) - (2)]));
        }
            break;

        case 116:

/* Line 1806 of yacc.c  */
#line 780 "test.y"
        {
            showNodeInfo("args -> args COMMA expression)");
            (yyval) = (yyvsp[(1) - (3)]);
            ((ListTreeNode*)(yyval))->insert((yyvsp[(3) - (3)]));
        }
            break;

        case 117:

/* Line 1806 of yacc.c  */
#line 786 "test.y"
        {
            showNodeInfo("args -> expression");
            std::vector<TreeNode*> expressionList;
            expressionList.push_back((yyvsp[(1) - (1)]));
            (yyval) = new ListTreeNode("args", expressionList);
        }
            break;



/* Line 1806 of yacc.c  */
#line 2998 "y.tab.c"
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

    /* Now `shift' the result of the reduction.  Determine what state
       that goes to, based on the state we popped back to and the rule
       number reduced by.  */

    yyn = yyr1[yyn];

    yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
    if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
        yystate = yytable[yystate];
    else
        yystate = yydefgoto[yyn - YYNTOKENS];

    goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
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

    /* Do not reclaim the symbols of the rule which action triggered
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
    yyerrstatus = 3;	/* Each real token shifted decrements this.  */

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

    *++yyvsp = yylval;


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

#if !defined(yyoverflow) || YYERROR_VERBOSE
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
    /* Do not reclaim the symbols of the rule which action triggered
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
    /* Make sure YYID is used.  */
    return YYID (yyresult);
}



/* Line 2067 of yacc.c  */
#line 793 "test.y"


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
