/* A Bison parser, made by GNU Bison 2.6.1.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2012 Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.6.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1


/* Substitute the variable and function names.  */
#define yyparse         syn_parse
#define yylex           syn_lex
#define yyerror         syn_error
#define yylval          syn_lval
#define yychar          syn_char
#define yydebug         syn_debug
#define yynerrs         syn_nerrs

/* Copy the first part of user declarations.  */
/* Line 336 of yacc.c  */
#line 282 "yacc.in"

#ifdef HAVE_CONFIG_H
    #include "pips_config.h"
#endif
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "genC.h"
#include "parser_private.h"
#include "linear.h"
#include "ri.h"
#include "ri-util.h"

#include "misc.h"
#include "properties.h"

#include "syntax.h"

#define YYERROR_VERBOSE 1 /* much clearer error messages with bison */

    /* local variables */
    int ici; /* to count control specifications in IO statements */
    type CurrentType = type_undefined; /* the type in a type or dimension
					  or common statement */
    intptr_t CurrentTypeSize; /* number of bytes to store a value of that type */

/* functions for DATA */

static expression MakeDataValueSet(expression n, expression c)
  {
    expression repeat_factor = expression_undefined;
    expression value_set = expression_undefined;
    entity repeat_value = FindEntity(TOP_LEVEL_MODULE_NAME,
						REPEAT_VALUE_NAME);
    value vc = value_undefined;

    pips_assert("Function repeat value is defined", !entity_undefined_p(repeat_value));

    vc = EvalExpression(c);
    if (! value_constant_p(vc)) {
      if(!complex_constant_expression_p(c)) {
	ParserError("MakeDataValueSet", "data value must be a constant\n");
      }
    }

    if(expression_undefined_p(n)) {
      value_set = c;
    }
    else {
      repeat_factor = (n == expression_undefined) ? int_to_expression(1) : n;
      value_set = make_call_expression(repeat_value,
				       CONS(EXPRESSION, repeat_factor,
					    CONS(EXPRESSION, c, NIL)));
    }

    return value_set;
  }

/* Line 336 of yacc.c  */
#line 135 "y.tab.c"

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
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
   by #include "y.tab.h".  */
#ifndef SYN_Y_TAB_H
# define SYN_Y_TAB_H
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int syn_debug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     TK_ASSIGN = 258,
     TK_BACKSPACE = 259,
     TK_BLANK = 260,
     TK_BLOCKDATA = 261,
     TK_BUFFERIN = 262,
     TK_BUFFEROUT = 263,
     TK_CALL = 264,
     TK_CHARACTER = 265,
     TK_CLOSE = 266,
     TK_COMMON = 267,
     TK_COMPLEX = 268,
     TK_CONTINUE = 269,
     TK_CYCLE = 270,
     TK_DATA = 271,
     TK_DIMENSION = 272,
     TK_DOUBLEPRECISION = 273,
     TK_DOUBLECOMPLEX = 274,
     TK_DO = 275,
     TK_ELSEIF = 276,
     TK_ELSE = 277,
     TK_ENDFILE = 278,
     TK_ENDDO = 279,
     TK_ENDIF = 280,
     TK_END = 281,
     TK_ENTRY = 282,
     TK_EQUIVALENCE = 283,
     TK_EXIT = 284,
     TK_EXTERNAL = 285,
     TK_FORMAT = 286,
     TK_FUNCTION = 287,
     TK_GOTO = 288,
     TK_IF = 289,
     TK_IMPLICIT = 290,
     TK_INCLUDE = 291,
     TK_INQUIRE = 292,
     TK_INTEGER = 293,
     TK_INTRINSIC = 294,
     TK_IOSTAT = 295,
     TK_LOGICAL = 296,
     TK_OPEN = 297,
     TK_PARAMETER = 298,
     TK_PAUSE = 299,
     TK_POINTER = 300,
     TK_PRINT = 301,
     TK_PROGRAM = 302,
     TK_READ = 303,
     TK_REAL = 304,
     TK_RETURN = 305,
     TK_REWIND = 306,
     TK_SAVE = 307,
     TK_STATIC = 308,
     TK_STOP = 309,
     TK_SUBROUTINE = 310,
     TK_THEN = 311,
     TK_TO = 312,
     TK_WHILE = 313,
     TK_WRITE = 314,
     TK_INOUT = 315,
     TK_IN = 316,
     TK_OUT = 317,
     TK_AND = 318,
     TK_EQ = 319,
     TK_EQV = 320,
     TK_GE = 321,
     TK_GT = 322,
     TK_LE = 323,
     TK_LT = 324,
     TK_NE = 325,
     TK_NEQV = 326,
     TK_NOT = 327,
     TK_OR = 328,
     TK_TRUE = 329,
     TK_FALSE = 330,
     TK_NAME = 331,
     TK_ICON = 332,
     TK_SCON = 333,
     TK_RCON = 334,
     TK_DCON = 335,
     TK_MINUS = 336,
     TK_PLUS = 337,
     TK_SLASH = 338,
     TK_STAR = 339,
     TK_POWER = 340,
     TK_LPAR = 341,
     TK_RPAR = 342,
     TK_COMMA = 343,
     TK_COLON = 344,
     TK_EQUALS = 345,
     TK_CURRENCY = 346,
     TK_CONCAT = 347,
     TK_EOS = 348,
     TK_IOLPAR = 349
   };
#endif
/* Tokens.  */
#define TK_ASSIGN 258
#define TK_BACKSPACE 259
#define TK_BLANK 260
#define TK_BLOCKDATA 261
#define TK_BUFFERIN 262
#define TK_BUFFEROUT 263
#define TK_CALL 264
#define TK_CHARACTER 265
#define TK_CLOSE 266
#define TK_COMMON 267
#define TK_COMPLEX 268
#define TK_CONTINUE 269
#define TK_CYCLE 270
#define TK_DATA 271
#define TK_DIMENSION 272
#define TK_DOUBLEPRECISION 273
#define TK_DOUBLECOMPLEX 274
#define TK_DO 275
#define TK_ELSEIF 276
#define TK_ELSE 277
#define TK_ENDFILE 278
#define TK_ENDDO 279
#define TK_ENDIF 280
#define TK_END 281
#define TK_ENTRY 282
#define TK_EQUIVALENCE 283
#define TK_EXIT 284
#define TK_EXTERNAL 285
#define TK_FORMAT 286
#define TK_FUNCTION 287
#define TK_GOTO 288
#define TK_IF 289
#define TK_IMPLICIT 290
#define TK_INCLUDE 291
#define TK_INQUIRE 292
#define TK_INTEGER 293
#define TK_INTRINSIC 294
#define TK_IOSTAT 295
#define TK_LOGICAL 296
#define TK_OPEN 297
#define TK_PARAMETER 298
#define TK_PAUSE 299
#define TK_POINTER 300
#define TK_PRINT 301
#define TK_PROGRAM 302
#define TK_READ 303
#define TK_REAL 304
#define TK_RETURN 305
#define TK_REWIND 306
#define TK_SAVE 307
#define TK_STATIC 308
#define TK_STOP 309
#define TK_SUBROUTINE 310
#define TK_THEN 311
#define TK_TO 312
#define TK_WHILE 313
#define TK_WRITE 314
#define TK_INOUT 315
#define TK_IN 316
#define TK_OUT 317
#define TK_AND 318
#define TK_EQ 319
#define TK_EQV 320
#define TK_GE 321
#define TK_GT 322
#define TK_LE 323
#define TK_LT 324
#define TK_NE 325
#define TK_NEQV 326
#define TK_NOT 327
#define TK_OR 328
#define TK_TRUE 329
#define TK_FALSE 330
#define TK_NAME 331
#define TK_ICON 332
#define TK_SCON 333
#define TK_RCON 334
#define TK_DCON 335
#define TK_MINUS 336
#define TK_PLUS 337
#define TK_SLASH 338
#define TK_STAR 339
#define TK_POWER 340
#define TK_LPAR 341
#define TK_RPAR 342
#define TK_COMMA 343
#define TK_COLON 344
#define TK_EQUALS 345
#define TK_CURRENCY 346
#define TK_CONCAT 347
#define TK_EOS 348
#define TK_IOLPAR 349



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 350 of yacc.c  */
#line 358 "yacc.in"

	basic basic;
	chain chain;
        char character;
	cons * liste;
	dataval dataval;
	datavar datavar;
	dimension dimension;
	entity entity;
	expression expression;
	instruction instruction;
	int integer;
	range range;
	string string;
	syntax syntax;
	tag tag;
	type type; 
	value value;


/* Line 350 of yacc.c  */
#line 387 "y.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE syn_lval;

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int syn_parse (void *YYPARSE_PARAM);
#else
int syn_parse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int syn_parse (void);
#else
int syn_parse ();
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !SYN_Y_TAB_H  */

/* Copy the second part of user declarations.  */

/* Line 353 of yacc.c  */
#line 415 "y.tab.c"

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
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
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
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  14
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1222

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  95
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  113
/* YYNRULES -- Number of rules.  */
#define YYNRULES  271
/* YYNRULES -- Number of states.  */
#define YYNSTATES  465

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   349

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
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     8,     9,    10,    16,    17,    21,
      27,    31,    34,    36,    39,    43,    45,    46,    49,    50,
      53,    55,    57,    59,    61,    63,    65,    67,    69,    71,
      73,    75,    77,    79,    81,    83,    85,    87,    89,    91,
      93,    95,    97,    99,   101,   103,   105,   107,   109,   111,
     113,   116,   119,   123,   125,   128,   132,   134,   138,   141,
     146,   149,   154,   161,   173,   175,   177,   179,   183,   187,
     191,   193,   194,   196,   198,   202,   204,   207,   210,   212,
     218,   222,   228,   235,   240,   247,   249,   251,   253,   259,
     265,   271,   281,   284,   291,   298,   301,   303,   307,   312,
     316,   318,   320,   323,   326,   328,   332,   334,   336,   339,
     343,   346,   350,   353,   357,   361,   362,   366,   368,   372,
     374,   376,   380,   384,   387,   391,   395,   400,   402,   404,
     408,   416,   419,   421,   425,   429,   431,   435,   438,   442,
     444,   450,   457,   459,   463,   465,   469,   471,   475,   477,
     483,   485,   487,   489,   496,   499,   501,   505,   510,   512,
     516,   518,   522,   524,   529,   531,   535,   539,   541,   543,
     545,   547,   549,   551,   552,   555,   559,   561,   563,   567,
     571,   573,   574,   577,   579,   581,   583,   585,   587,   589,
     591,   592,   597,   602,   605,   607,   610,   617,   625,   628,
     632,   634,   638,   640,   641,   643,   647,   653,   660,   669,
     671,   673,   676,   680,   684,   688,   692,   696,   700,   704,
     708,   712,   716,   719,   723,   725,   729,   731,   733,   736,
     740,   744,   748,   752,   756,   760,   763,   765,   767,   769,
     771,   773,   775,   777,   779,   781,   782,   784,   786,   788,
     790,   792,   794,   796,   798,   800,   802,   804,   806,   808,
     810,   812,   814,   816,   818,   820,   822,   824,   826,   828,
     830,   831
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      96,     0,    -1,    97,    -1,    96,    97,    -1,    -1,    -1,
     101,    98,   104,    99,   103,    -1,    -1,   101,   100,   103,
      -1,   184,   206,   178,   182,    93,    -1,    27,   176,   182,
      -1,    26,    93,    -1,    93,    -1,   105,    93,    -1,   104,
     105,    93,    -1,   160,    -1,    -1,   106,   108,    -1,    -1,
     107,   109,    -1,   139,    -1,   173,    -1,   167,    -1,   158,
      -1,   153,    -1,   154,    -1,   150,    -1,   145,    -1,   144,
      -1,   143,    -1,   140,    -1,   138,    -1,   136,    -1,   135,
      -1,   134,    -1,   133,    -1,   132,    -1,   131,    -1,   129,
      -1,   130,    -1,   125,    -1,   126,    -1,   127,    -1,   124,
      -1,   123,    -1,   122,    -1,   111,    -1,   110,    -1,   115,
      -1,   102,    -1,    50,   191,    -1,   112,   180,    -1,   112,
     180,   113,    -1,     9,    -1,    86,    87,    -1,    86,   114,
      87,    -1,   192,    -1,   114,    88,   192,    -1,    84,    77,
      -1,   114,    88,    84,    77,    -1,   204,   116,    -1,   204,
     116,    88,   119,    -1,   204,    86,   117,    87,   207,   119,
      -1,   205,    86,   116,    88,   116,    87,    86,   195,    88,
     195,    87,    -1,   195,    -1,    84,    -1,   118,    -1,   117,
      88,   118,    -1,   177,    90,   195,    -1,   177,    90,    84,
      -1,   116,    -1,    -1,   120,    -1,   121,    -1,   120,    88,
     121,    -1,   192,    -1,    44,   191,    -1,    54,   191,    -1,
      14,    -1,    20,   199,   207,   188,   128,    -1,    20,   188,
     128,    -1,    20,    58,    86,   192,    87,    -1,    20,   199,
      58,    86,   192,    87,    -1,    90,   192,    88,   192,    -1,
      90,   192,    88,   192,    88,   192,    -1,    25,    -1,    24,
      -1,    22,    -1,    21,    86,   192,    87,    56,    -1,    34,
      86,   192,    87,    56,    -1,    34,    86,   192,    87,   109,
      -1,    34,    86,   192,    87,   199,    88,   199,    88,   199,
      -1,    33,   199,    -1,    33,    86,   137,    87,   207,   192,
      -1,    33,   176,   207,    86,   137,    87,    -1,    33,   176,
      -1,   199,    -1,   137,    88,   199,    -1,     3,   198,    57,
     188,    -1,   188,    90,   192,    -1,    31,    -1,    52,    -1,
      52,   141,    -1,    53,   141,    -1,   142,    -1,   141,    88,
     142,    -1,   176,    -1,   152,    -1,    39,   179,    -1,   143,
      88,   179,    -1,    30,   180,    -1,   144,    88,   180,    -1,
     185,   146,    -1,   145,    88,   146,    -1,   176,   147,   187,
      -1,    -1,    86,   148,    87,    -1,   149,    -1,   149,    88,
     148,    -1,   192,    -1,    84,    -1,   192,    89,    84,    -1,
     192,    89,   192,    -1,   151,   146,    -1,   151,   152,   146,
      -1,   150,    88,   146,    -1,   150,   207,   152,   146,    -1,
      12,    -1,    92,    -1,    83,   181,    83,    -1,    45,    86,
     176,    88,   176,   147,    87,    -1,    28,   155,    -1,   156,
      -1,   155,    88,   156,    -1,    86,   157,    87,    -1,   188,
      -1,   157,    88,   188,    -1,   159,   146,    -1,   158,    88,
     146,    -1,    17,    -1,    16,   161,    83,   162,    83,    -1,
     160,   207,   161,    83,   162,    83,    -1,   165,    -1,   161,
      88,   165,    -1,   163,    -1,   162,    88,   163,    -1,   164,
      -1,   164,    84,   164,    -1,   196,    -1,    86,   196,    88,
     196,    87,    -1,   176,    -1,   188,    -1,   166,    -1,    86,
     161,    88,   176,   128,    87,    -1,    35,   168,    -1,   169,
      -1,   168,    88,   169,    -1,   185,    86,   170,    87,    -1,
     171,    -1,   170,    88,   171,    -1,   172,    -1,   172,    81,
     172,    -1,    76,    -1,    43,    86,   174,    87,    -1,   175,
      -1,   174,    88,   175,    -1,   176,    90,   192,    -1,   177,
      -1,    76,    -1,   181,    -1,   181,    -1,   177,    -1,    76,
      -1,    -1,    86,    87,    -1,    86,   183,    87,    -1,   176,
      -1,    84,    -1,   183,    88,   176,    -1,   183,    88,    84,
      -1,   185,    -1,    -1,   186,   187,    -1,    38,    -1,    49,
      -1,    18,    -1,    41,    -1,    13,    -1,    19,    -1,    10,
      -1,    -1,    84,    86,    84,    87,    -1,    84,    86,   192,
      87,    -1,    84,   200,    -1,   176,    -1,   176,   189,    -1,
     176,    86,   191,    89,   191,    87,    -1,   176,   189,    86,
     191,    89,   191,    87,    -1,    86,    87,    -1,    86,   190,
      87,    -1,   192,    -1,   190,    88,   192,    -1,   192,    -1,
      -1,   193,    -1,    86,   192,    87,    -1,    86,   192,    88,
     192,    87,    -1,    86,   192,    88,   188,   128,    87,    -1,
      86,   192,    88,   190,    88,   188,   128,    87,    -1,   188,
      -1,   197,    -1,   202,   192,    -1,   192,    82,   192,    -1,
     192,    81,   192,    -1,   192,    84,   192,    -1,   192,    83,
     192,    -1,   192,    85,   192,    -1,   192,   203,   192,    -1,
     192,    65,   192,    -1,   192,    71,   192,    -1,   192,    73,
     192,    -1,   192,    63,   192,    -1,    72,   192,    -1,   192,
      92,   192,    -1,   195,    -1,    86,   194,    87,    -1,   188,
      -1,   197,    -1,   202,   194,    -1,   194,    82,   194,    -1,
     194,    81,   194,    -1,   194,    84,   194,    -1,   194,    83,
     194,    -1,   194,    85,   194,    -1,   194,    92,   194,    -1,
     201,   197,    -1,    74,    -1,    75,    -1,   198,    -1,    80,
      -1,    78,    -1,    79,    -1,    77,    -1,    77,    -1,    77,
      -1,    -1,   202,    -1,    82,    -1,    81,    -1,    64,    -1,
      70,    -1,    69,    -1,    68,    -1,    66,    -1,    67,    -1,
      46,    -1,    59,    -1,    48,    -1,    11,    -1,    42,    -1,
      23,    -1,     4,    -1,    51,    -1,    37,    -1,     7,    -1,
       8,    -1,    47,    -1,    55,    -1,    32,    -1,     6,    -1,
      -1,    88,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   380,   380,   381,   386,   386,   386,   387,   387,   390,
     397,   413,   417,   418,   419,   423,   443,   443,   444,   444,
     449,   455,   456,   457,   458,   459,   460,   461,   462,   463,
     464,   467,   469,   471,   473,   475,   477,   479,   481,   483,
     485,   487,   489,   491,   493,   495,   497,   499,   501,   503,
     507,   511,   514,   518,   522,   524,   528,   532,   536,   543,
     553,   557,   561,   563,   568,   569,   573,   575,   586,   603,
     623,   642,   643,   647,   649,   653,   657,   661,   665,   669,
     676,   683,   690,   699,   705,   714,   718,   722,   726,   737,
     746,   754,   763,   767,   773,   783,   795,   799,   805,   816,
     830,   838,   840,   841,   844,   845,   848,   850,   854,   858,
     864,   869,   875,   877,   880,   919,   922,   928,   932,   938,
     949,   955,   961,   976,   981,   986,   991,   999,  1005,  1009,
    1015,  1021,  1024,  1025,  1028,  1032,  1036,  1044,  1047,  1052,
    1058,  1063,  1070,  1074,  1081,  1085,  1091,  1095,  1101,  1105,
    1109,  1143,  1147,  1151,  1160,  1167,  1170,  1175,  1180,  1183,
    1188,  1197,  1208,  1214,  1217,  1218,  1221,  1227,  1249,  1253,
    1264,  1272,  1280,  1285,  1288,  1292,  1300,  1304,  1312,  1316,
    1326,  1331,  1336,  1349,  1354,  1359,  1364,  1369,  1374,  1379,
    1387,  1398,  1402,  1406,  1412,  1417,  1422,  1426,  1432,  1434,
    1438,  1442,  1448,  1455,  1458,  1460,  1462,  1471,  1473,  1477,
    1481,  1485,  1492,  1496,  1500,  1504,  1508,  1513,  1517,  1522,
    1527,  1533,  1539,  1544,  1551,  1552,  1556,  1561,  1565,  1572,
    1576,  1580,  1584,  1588,  1593,  1600,  1610,  1614,  1618,  1622,
    1628,  1633,  1640,  1647,  1653,  1661,  1664,  1670,  1674,  1680,
    1684,  1688,  1692,  1696,  1700,  1706,  1708,  1710,  1712,  1714,
    1716,  1718,  1720,  1722,  1726,  1728,  1732,  1734,  1737,  1740,
    1744,  1745
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TK_ASSIGN", "TK_BACKSPACE", "TK_BLANK",
  "TK_BLOCKDATA", "TK_BUFFERIN", "TK_BUFFEROUT", "TK_CALL", "TK_CHARACTER",
  "TK_CLOSE", "TK_COMMON", "TK_COMPLEX", "TK_CONTINUE", "TK_CYCLE",
  "TK_DATA", "TK_DIMENSION", "TK_DOUBLEPRECISION", "TK_DOUBLECOMPLEX",
  "TK_DO", "TK_ELSEIF", "TK_ELSE", "TK_ENDFILE", "TK_ENDDO", "TK_ENDIF",
  "TK_END", "TK_ENTRY", "TK_EQUIVALENCE", "TK_EXIT", "TK_EXTERNAL",
  "TK_FORMAT", "TK_FUNCTION", "TK_GOTO", "TK_IF", "TK_IMPLICIT",
  "TK_INCLUDE", "TK_INQUIRE", "TK_INTEGER", "TK_INTRINSIC", "TK_IOSTAT",
  "TK_LOGICAL", "TK_OPEN", "TK_PARAMETER", "TK_PAUSE", "TK_POINTER",
  "TK_PRINT", "TK_PROGRAM", "TK_READ", "TK_REAL", "TK_RETURN", "TK_REWIND",
  "TK_SAVE", "TK_STATIC", "TK_STOP", "TK_SUBROUTINE", "TK_THEN", "TK_TO",
  "TK_WHILE", "TK_WRITE", "TK_INOUT", "TK_IN", "TK_OUT", "TK_AND", "TK_EQ",
  "TK_EQV", "TK_GE", "TK_GT", "TK_LE", "TK_LT", "TK_NE", "TK_NEQV",
  "TK_NOT", "TK_OR", "TK_TRUE", "TK_FALSE", "TK_NAME", "TK_ICON",
  "TK_SCON", "TK_RCON", "TK_DCON", "TK_MINUS", "TK_PLUS", "TK_SLASH",
  "TK_STAR", "TK_POWER", "TK_LPAR", "TK_RPAR", "TK_COMMA", "TK_COLON",
  "TK_EQUALS", "TK_CURRENCY", "TK_CONCAT", "TK_EOS", "TK_IOLPAR",
  "$accept", "lprg_exec", "prg_exec", "$@1", "$@2", "$@3", "begin_inst",
  "entry_inst", "end_inst", "linstruction", "instruction", "$@4", "$@5",
  "inst_spec", "inst_exec", "return_inst", "call_inst", "tk_call",
  "parameters", "arguments", "io_inst", "io_f_u_id", "lci", "ci",
  "opt_lio_elem", "lio_elem", "io_elem", "pause_inst", "stop_inst",
  "continue_inst", "do_inst", "bdo_inst", "wdo_inst", "do_plage",
  "endif_inst", "enddo_inst", "else_inst", "elseif_inst", "blockif_inst",
  "logicalif_inst", "arithmif_inst", "goto_inst", "licon",
  "assignment_inst", "format_inst", "save_inst", "lsavename", "savename",
  "intrinsic_inst", "external_inst", "type_inst", "declaration",
  "decl_tableau", "ldim_tableau", "dim_tableau", "common_inst", "common",
  "common_name", "pointer_inst", "equivalence_inst", "lequivchain",
  "equivchain", "latom", "dimension_inst", "dimension", "data_inst",
  "ldatavar", "ldataval", "dataval", "dataconst", "datavar", "dataidl",
  "implicit_inst", "limplicit", "implicit", "l_letter_letter",
  "letter_letter", "letter", "parameter_inst", "lparametre", "parametre",
  "entity_name", "name", "module_name", "global_entity_name",
  "functional_entity_name", "global_name", "opt_lformalparameter",
  "lformalparameter", "opt_fortran_type", "fortran_type",
  "fortran_basic_type", "lg_fortran_type", "atom", "indices",
  "lexpression", "opt_expression", "expression", "sous_expression",
  "io_expr", "unpar_io_expr", "const_simple", "unsigned_const_simple",
  "icon", "label", "ival", "opt_signe", "signe", "oper_rela", "io_keyword",
  "iobuf_keyword", "psf_keyword", "opt_virgule", YY_NULL
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
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    95,    96,    96,    98,    99,    97,   100,    97,   101,
     102,   103,   104,   104,   104,   105,   106,   105,   107,   105,
     105,   108,   108,   108,   108,   108,   108,   108,   108,   108,
     108,   109,   109,   109,   109,   109,   109,   109,   109,   109,
     109,   109,   109,   109,   109,   109,   109,   109,   109,   109,
     110,   111,   111,   112,   113,   113,   114,   114,   114,   114,
     115,   115,   115,   115,   116,   116,   117,   117,   118,   118,
     118,   119,   119,   120,   120,   121,   122,   123,   124,   125,
     126,   127,   127,   128,   128,   129,   130,   131,   132,   133,
     134,   135,   136,   136,   136,   136,   137,   137,   138,   138,
     139,   140,   140,   140,   141,   141,   142,   142,   143,   143,
     144,   144,   145,   145,   146,   147,   147,   148,   148,   149,
     149,   149,   149,   150,   150,   150,   150,   151,   152,   152,
     153,   154,   155,   155,   156,   157,   157,   158,   158,   159,
     160,   160,   161,   161,   162,   162,   163,   163,   164,   164,
     164,   165,   165,   166,   167,   168,   168,   169,   170,   170,
     171,   171,   172,   173,   174,   174,   175,   176,   177,   178,
     179,   180,   181,   182,   182,   182,   183,   183,   183,   183,
     184,   184,   185,   186,   186,   186,   186,   186,   186,   186,
     187,   187,   187,   187,   188,   188,   188,   188,   189,   189,
     190,   190,   191,   191,   192,   192,   192,   192,   192,   193,
     193,   193,   193,   193,   193,   193,   193,   193,   193,   193,
     193,   193,   193,   193,   194,   194,   195,   195,   195,   195,
     195,   195,   195,   195,   195,   196,   197,   197,   197,   197,
     197,   197,   198,   199,   200,   201,   201,   202,   202,   203,
     203,   203,   203,   203,   203,   204,   204,   204,   204,   204,
     204,   204,   204,   204,   205,   205,   206,   206,   206,   206,
     207,   207
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     0,     0,     5,     0,     3,     5,
       3,     2,     1,     2,     3,     1,     0,     2,     0,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     2,     3,     1,     2,     3,     1,     3,     2,     4,
       2,     4,     6,    11,     1,     1,     1,     3,     3,     3,
       1,     0,     1,     1,     3,     1,     2,     2,     1,     5,
       3,     5,     6,     4,     6,     1,     1,     1,     5,     5,
       5,     9,     2,     6,     6,     2,     1,     3,     4,     3,
       1,     1,     2,     2,     1,     3,     1,     1,     2,     3,
       2,     3,     2,     3,     3,     0,     3,     1,     3,     1,
       1,     3,     3,     2,     3,     3,     4,     1,     1,     3,
       7,     2,     1,     3,     3,     1,     3,     2,     3,     1,
       5,     6,     1,     3,     1,     3,     1,     3,     1,     5,
       1,     1,     1,     6,     2,     1,     3,     4,     1,     3,
       1,     3,     1,     4,     1,     3,     3,     1,     1,     1,
       1,     1,     1,     0,     2,     3,     1,     1,     3,     3,
       1,     0,     2,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     4,     2,     1,     2,     6,     7,     2,     3,
       1,     3,     1,     0,     1,     3,     5,     6,     8,     1,
       1,     2,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     2,     3,     1,     3,     1,     1,     2,     3,
       3,     3,     3,     3,     3,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
     181,   189,   187,   185,   188,   183,   186,   184,   181,     2,
       4,     0,   180,   190,     1,     3,    18,     0,   269,   268,
     266,   267,     0,     0,   182,     0,   100,    12,    18,     0,
       0,     0,    20,   270,     0,     8,   172,   173,   169,   244,
       0,   193,   168,     0,     0,   142,   152,   194,   167,   151,
       0,     0,    13,   127,   139,     0,     0,     0,     0,     0,
       0,   101,     0,    17,    30,    29,    28,    27,   270,     0,
      24,    25,    23,     0,    22,    21,     0,     0,   261,   264,
     265,    53,   258,    78,     0,     0,    87,   260,    86,    85,
       0,     0,     0,   263,   259,   203,   255,   257,   203,   262,
     203,   256,    49,    19,    47,    46,     0,    48,    45,    44,
      43,    40,    41,    42,    38,    39,    37,    36,    35,    34,
      33,    32,    31,     0,     0,     0,   271,     0,    11,     0,
       0,     0,   236,   237,   242,   240,   241,   239,   248,   247,
       0,     0,   209,     0,   204,   210,   238,     0,     0,   245,
       0,   203,   195,     6,    14,     0,   131,   132,   171,   110,
     154,   155,     0,   108,   170,     0,     0,     0,   128,   102,
     104,   107,   106,   103,     0,     0,     0,   271,     0,   123,
       0,   115,     0,   137,   112,     0,     0,   243,     0,   270,
       0,   173,     0,    95,    92,     0,    76,   202,    50,    77,
      51,     0,    65,     0,    60,   226,     0,   224,   227,     0,
       0,     0,   177,   174,   176,     0,     9,   222,   191,     0,
       0,   249,     0,   253,   254,   252,   251,   250,     0,     0,
       0,     0,     0,     0,     0,   192,     0,     0,   211,     0,
     245,     0,   144,   146,   150,   148,     0,   246,   143,   198,
       0,     0,   200,   203,     0,   135,     0,     0,     0,     0,
     164,     0,     0,     0,     0,   109,   111,   113,   125,     0,
     124,     0,   190,   138,     0,     0,     0,    80,     0,     0,
       0,    10,     0,    96,     0,     0,     0,    52,    99,     0,
      70,     0,    66,   167,     0,    71,     0,     0,     0,     0,
       0,     0,   228,   224,     0,   245,   175,     0,   205,     0,
     221,   218,   219,   220,   213,   212,   215,   214,   216,   223,
     217,   194,     0,   140,   245,   245,   235,   199,     0,   203,
       0,   134,     0,   133,   156,   162,     0,   158,   160,   163,
       0,     0,     0,   129,   105,   126,   120,     0,   117,   119,
     114,    98,     0,     0,     0,     0,     0,   270,     0,     0,
       0,     0,    54,     0,    56,   270,     0,     0,   225,    61,
      72,    73,    75,   230,   229,   232,   231,   233,   234,     0,
       0,   179,   178,   209,     0,   200,     0,   245,   145,   147,
     201,     0,   203,   136,   157,     0,     0,   165,   166,   115,
     116,     0,     0,    81,     0,     0,    79,    88,     0,    97,
       0,    89,    90,     0,    58,    55,     0,    71,    67,    69,
     224,     0,     0,   141,     0,     0,   206,   153,     0,   196,
       0,   159,   161,     0,   118,   121,   122,    83,    82,    93,
      94,     0,     0,    57,    62,    74,     0,   207,   209,   149,
     197,   130,     0,     0,    59,     0,     0,    84,     0,   224,
     208,    91,     0,   224,    63
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     8,     9,    16,    50,    17,    10,   102,    35,    28,
      29,    30,    31,    63,   103,   104,   105,   106,   287,   363,
     107,   290,   291,   292,   369,   370,   371,   108,   109,   110,
     111,   112,   113,   277,   114,   115,   116,   117,   118,   119,
     120,   121,   282,   122,    32,    64,   169,   170,    65,    66,
      67,   179,   272,   347,   348,    68,    69,   171,    70,    71,
     156,   157,   254,    72,    73,    33,    44,   241,   242,   243,
      45,    46,    74,   160,   161,   336,   337,   338,    75,   259,
     260,    47,    48,    37,   163,   159,   164,   130,   215,    11,
      12,    13,    24,   142,   152,   250,   196,   197,   144,   206,
     303,   245,   145,   146,   283,    41,   246,   147,   237,   124,
     125,    22,   127
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -310
static const yytype_int16 yypact[] =
{
      32,  -310,  -310,  -310,  -310,  -310,  -310,  -310,    22,  -310,
      -5,    17,  -310,   -51,  -310,  -310,   447,    29,  -310,  -310,
    -310,  -310,     3,   -21,  -310,   -38,  -310,  -310,   653,    -3,
     691,   602,  -310,   -57,     5,  -310,  -310,   -18,  -310,  -310,
     213,  -310,  -310,   -38,    -8,  -310,  -310,    14,  -310,  -310,
      29,    36,  -310,  -310,  -310,    24,    42,    32,     3,    40,
      46,    -7,    -7,  -310,  -310,    34,    48,    57,   -11,    -7,
    -310,  -310,    61,    42,  -310,  -310,    42,    75,  -310,  -310,
    -310,  -310,  -310,  -310,   -33,    87,  -310,  -310,  -310,  -310,
      42,   -47,   119,  -310,  -310,  1097,  -310,  -310,  1097,  -310,
    1097,  -310,  -310,  -310,  -310,  -310,    42,  -310,  -310,  -310,
    -310,  -310,  -310,  -310,  -310,  -310,  -310,  -310,  -310,  -310,
    -310,  -310,  -310,    92,  1110,   143,  -310,   -38,  -310,   -50,
     120,  1097,  -310,  -310,  -310,  -310,  -310,  -310,  -310,  -310,
     151,  1097,  -310,   712,  -310,  -310,  -310,  1097,   156,    33,
     -38,   251,   169,  -310,  -310,    42,   173,  -310,  -310,  -310,
     175,  -310,   180,  -310,  -310,    42,    42,     3,  -310,   179,
    -310,  -310,  -310,   179,     3,    42,    42,    42,   -26,  -310,
      42,   184,    42,  -310,  -310,   220,   192,  -310,   190,   -41,
    1097,   -18,   205,    60,  -310,  1097,  -310,   982,  -310,  -310,
     200,  1097,  -310,  1123,   208,  -310,    12,    19,  -310,   427,
    1123,     4,  -310,  -310,  -310,   -35,  -310,   127,  -310,   682,
    1097,  -310,  1097,  -310,  -310,  -310,  -310,  -310,  1097,  1097,
    1097,  1097,  1097,  1097,  1097,  -310,  1097,  1097,   219,   -38,
      94,    25,  -310,   222,  -310,  -310,   147,  -310,  -310,  -310,
      54,   223,   350,  1097,    99,  -310,    24,    32,   232,   101,
    -310,   230,   221,   239,    -7,  -310,  -310,  -310,  -310,    42,
    -310,   369,   -51,  -310,    42,  1097,  1097,  -310,   248,    42,
     742,  -310,   128,  -310,   253,   772,  1055,  -310,   982,   427,
    -310,   130,  -310,   250,    85,  1097,   427,   427,   427,   427,
     427,   427,   259,  -310,   257,    33,  -310,     2,  -310,  1097,
     127,  1009,  1009,   511,    78,    78,   219,   219,   219,   234,
    1036,    30,   258,  -310,    33,    33,  -310,  -310,  1097,  1097,
     272,  -310,    42,  -310,  -310,  -310,   149,  -310,   266,  -310,
      42,  1097,    42,  -310,  -310,  -310,  -310,   275,   277,   802,
    -310,  -310,   832,   862,  1097,   190,   310,   279,   205,   205,
     508,   286,  -310,   155,   982,   279,  1123,  1136,  -310,  -310,
     282,  -310,   982,    96,    96,   259,   259,   259,   268,  1123,
      52,  -310,  -310,   190,   285,   892,   288,    94,  -310,  -310,
     982,   290,  1097,  -310,  -310,   232,   232,  -310,   982,   184,
    -310,   369,  1071,  -310,  1097,   922,  -310,  -310,  1097,  -310,
     163,  -310,  -310,   291,  -310,  -310,  1084,  1097,  -310,  -310,
     165,  1097,   295,  -310,   297,  1097,  -310,  -310,   298,  -310,
     301,  -310,  -310,   303,  -310,  -310,   982,   952,  -310,   982,
    -310,   205,   315,   982,  -310,  -310,   308,  -310,   190,  -310,
    -310,  -310,  1097,   305,  -310,   427,   312,   982,   205,   313,
    -310,  -310,   427,   316,  -310
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -310,  -310,   394,  -310,  -310,  -310,  -310,  -310,   354,  -310,
     377,  -310,  -310,  -310,    47,  -310,  -310,  -310,  -310,  -310,
    -310,  -122,  -310,    43,    -9,  -310,   -15,  -310,  -310,  -310,
    -310,  -310,  -310,  -309,  -310,  -310,  -310,  -310,  -310,  -310,
    -310,  -310,    51,  -310,  -310,  -310,   349,   148,  -310,  -310,
    -310,   -49,    28,    23,  -310,  -310,  -310,   -54,  -310,  -310,
    -310,   172,  -310,  -310,  -310,  -310,   -24,   124,   116,   129,
    -134,  -310,  -310,  -310,   195,  -310,    63,    65,  -310,  -310,
     122,   307,   -52,  -310,   293,   -86,   -14,   278,  -310,  -310,
     -29,  -310,   196,   -25,  -310,   161,   -89,   -30,  -310,  -142,
    -119,  -237,    59,   397,   -77,  -310,  -310,   -66,  -310,  -310,
    -310,  -310,   -55
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -271
static const yytype_int16 yytable[] =
{
      49,    76,   204,   322,   158,   207,   123,   189,    38,   198,
     143,   199,   386,   178,   194,   180,   248,   278,    49,   148,
     200,    -7,    14,    18,   183,   186,    42,   184,   162,    42,
     187,   126,     1,    23,   212,     2,   -15,   213,    42,   192,
       3,     4,     1,    42,   187,     2,   406,   126,    43,    19,
       3,     4,   306,   307,   158,    34,    39,   167,   209,   188,
       5,   294,   251,     6,    20,    40,   168,   302,   129,    42,
       5,     7,    21,     6,   424,   149,   167,   177,    42,    36,
     150,     7,   -26,   247,   207,   168,   381,   305,   304,   266,
      52,   207,   150,   296,   297,   298,   299,   300,   128,   205,
     151,   217,    49,   211,   301,   248,   -64,   -64,   323,    42,
     155,   219,   -64,   324,   138,   139,   151,   238,    42,   240,
     276,   252,   174,   158,   269,    49,   165,   267,   268,   154,
     255,   270,   166,   273,   279,   423,   175,   209,   284,   456,
     324,   327,   328,   209,   209,   176,  -270,   294,   126,   182,
     428,   293,   134,   263,   373,   374,   375,   376,   377,   378,
     280,   232,   233,   234,   330,   285,   296,   297,   298,   299,
     300,   288,   368,   190,   247,   138,   139,   301,   205,   298,
     299,   300,   201,   208,   205,   205,   331,   332,   339,   340,
     310,   221,   311,   223,   224,   225,   226,   227,   312,   313,
     314,   315,   316,   317,   318,   195,   319,   320,   230,   231,
     232,   233,   234,   216,    49,   357,   358,   365,   366,   236,
     345,   132,   133,   209,   134,   135,   136,   137,   162,   210,
     209,   209,   209,   209,   209,   209,   394,   395,   218,   247,
     391,   349,   415,   416,   239,   352,   353,   207,   420,   351,
     440,   358,   -68,   -68,   355,   253,   364,   422,   247,   247,
     207,   256,   208,   257,   205,   372,   258,   264,   208,   208,
     271,   205,   205,   205,   205,   205,   205,   274,   275,   385,
     276,   409,   187,   413,   383,   131,   286,   132,   133,    42,
     134,   135,   136,   137,   138,   139,   295,   140,   390,   141,
     209,   209,   408,   430,   234,   326,   325,   393,   335,   342,
     417,   398,   329,   209,   293,   230,   231,   232,   233,   234,
     341,   247,   343,   131,   405,   132,   133,    42,   134,   135,
     136,   137,   138,   139,   354,   123,   459,   141,   249,   359,
     367,   205,   205,   463,   300,   379,   387,   396,   208,   296,
     297,   298,   299,   300,   205,   208,   208,   208,   208,   208,
     208,   392,   400,   414,   453,   401,   407,   126,   172,   172,
     421,   349,   436,   425,   437,   427,   181,   429,   439,   441,
     181,   461,   446,   181,   447,   449,   443,   372,   450,   209,
     451,   372,   454,   458,   455,   390,   209,   191,   193,   460,
     448,   462,    15,   464,   153,    51,   445,   412,   444,   418,
     410,   173,   344,   220,   221,   222,   223,   224,   225,   226,
     227,   228,   457,   229,   434,   208,   208,   433,   333,   380,
     205,   230,   231,   232,   233,   234,   214,   205,   208,  -202,
     388,   131,   236,   132,   133,    42,   134,   135,   136,   137,
     138,   139,   334,   346,   389,   141,   244,   -16,   431,   -16,
     -16,   432,   397,    25,   -16,   -16,   -16,   265,   350,   281,
     384,     0,   261,   262,   185,   -16,     0,   -16,    26,     0,
       0,     0,   -16,   181,   181,   -16,   -16,   181,   -16,   181,
     -16,     0,   -16,     0,     0,     0,   -16,     0,     0,   -16,
     -16,   132,   133,    42,   134,   135,   136,   137,   138,   139,
       0,    77,    78,   289,   208,    79,    80,    81,     0,    82,
       0,   208,    83,     0,     0,     0,     0,     0,    84,    85,
      86,    87,    88,    89,     0,    90,     0,     0,     0,     0,
      27,    91,    92,     0,     0,    93,   321,     0,     0,     0,
      94,     0,    95,     0,    96,     0,    97,     0,    98,    99,
       0,     0,   100,     0,   411,     0,     0,   101,     0,     0,
       0,   172,     0,     0,   220,   221,   181,   223,   224,   225,
     226,   227,     0,     0,    42,   187,     0,     0,     0,     0,
       0,     0,   230,   231,   232,   233,   234,     0,     0,     0,
       0,     0,     0,   236,     0,    77,    78,     0,     0,    79,
      80,    81,   244,    82,   382,     0,    83,     0,     0,     0,
       0,     0,    84,    85,    86,    87,    88,    89,     0,    90,
       0,   244,   244,     0,     0,    91,    92,     0,     0,    93,
       0,     0,     0,     0,    94,     0,    95,   261,    96,   399,
      97,     0,    98,    99,     0,     0,   100,     0,     0,     0,
       0,   101,     0,   -16,     0,   -16,   -16,     0,     0,    25,
     -16,   -16,   -16,     0,     0,     0,     0,     0,    42,    -5,
       0,   -16,     0,   -16,    26,     0,     0,     0,   -16,     0,
       0,   -16,   -16,     0,   -16,     0,   -16,     0,   -16,     0,
       0,     1,   -16,    53,     2,   -16,   -16,     0,    54,     3,
       4,     0,     0,     0,     0,     0,     0,     0,     0,    55,
       0,    56,     0,     0,     0,     0,    57,     0,     0,     5,
      58,     0,     6,     0,    59,     0,    60,     0,     0,     0,
       7,     0,     0,    61,    62,   220,   221,   222,   223,   224,
     225,   226,   227,   228,     0,   229,     0,     0,     0,     0,
       0,     0,     0,   230,   231,   232,   233,   234,     0,   308,
     309,     0,     0,     0,   236,   220,   221,   222,   223,   224,
     225,   226,   227,   228,     0,   229,     0,     0,     0,     0,
       0,     0,     0,   230,   231,   232,   233,   234,     0,   235,
       0,     0,     0,     0,   236,   220,   221,   222,   223,   224,
     225,   226,   227,   228,     0,   229,     0,     0,     0,     0,
       0,     0,     0,   230,   231,   232,   233,   234,     0,   356,
       0,     0,     0,     0,   236,   220,   221,   222,   223,   224,
     225,   226,   227,   228,     0,   229,     0,     0,     0,     0,
       0,     0,     0,   230,   231,   232,   233,   234,     0,   360,
       0,     0,     0,     0,   236,   220,   221,   222,   223,   224,
     225,   226,   227,   228,     0,   229,     0,     0,     0,     0,
       0,     0,     0,   230,   231,   232,   233,   234,     0,     0,
       0,   402,     0,     0,   236,   220,   221,   222,   223,   224,
     225,   226,   227,   228,     0,   229,     0,     0,     0,     0,
       0,     0,     0,   230,   231,   232,   233,   234,     0,   403,
       0,     0,     0,     0,   236,   220,   221,   222,   223,   224,
     225,   226,   227,   228,     0,   229,     0,     0,     0,     0,
       0,     0,     0,   230,   231,   232,   233,   234,     0,     0,
     404,     0,     0,     0,   236,   220,   221,   222,   223,   224,
     225,   226,   227,   228,     0,   229,     0,     0,     0,     0,
       0,     0,     0,   230,   231,   232,   233,   234,     0,   426,
       0,     0,     0,     0,   236,   220,   221,   222,   223,   224,
     225,   226,   227,   228,     0,   229,     0,     0,     0,     0,
       0,     0,     0,   230,   231,   232,   233,   234,     0,   438,
       0,     0,     0,     0,   236,   220,   221,   222,   223,   224,
     225,   226,   227,   228,     0,   229,     0,     0,     0,     0,
       0,     0,     0,   230,   231,   232,   233,   234,     0,     0,
     452,     0,     0,     0,   236,   220,   221,   222,   223,   224,
     225,   226,   227,   228,     0,   229,     0,     0,     0,     0,
       0,     0,     0,   230,   231,   232,   233,   234,     0,     0,
       0,     0,   220,   221,   236,   223,   224,   225,   226,   227,
       0,     0,   229,     0,     0,     0,     0,     0,     0,     0,
     230,   231,   232,   233,   234,     0,     0,     0,     0,     0,
    -271,   236,  -271,  -271,  -271,  -271,  -271,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   230,   231,   232,
     233,   234,     0,     0,     0,     0,     0,   131,   236,   132,
     133,    42,   134,   135,   136,   137,   138,   139,     0,   361,
       0,   141,   362,   131,     0,   132,   133,    42,   134,   135,
     136,   137,   138,   139,     0,   435,   131,   141,   132,   133,
      42,   134,   135,   136,   137,   138,   139,     0,   442,   131,
     141,   132,   133,    42,   134,   135,   136,   137,   138,   139,
       0,     0,     0,   141,   132,   133,    42,   134,   135,   136,
     137,   138,   139,     0,   202,     0,   203,   132,   133,    42,
     134,   135,   136,   137,   138,   139,     0,   202,     0,   289,
     132,   133,    42,   134,   135,   136,   137,   138,   139,     0,
     419,     0,   289
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-310))

#define yytable_value_is_error(yytable_value) \
  ((yytable_value) == (-271))

static const yytype_int16 yycheck[] =
{
      25,    30,   124,   240,    56,   124,    31,    84,    22,    98,
      40,   100,   321,    68,    91,    69,   150,    58,    43,    43,
     106,    26,     0,     6,    73,    58,    76,    76,    57,    76,
      77,    88,    10,    84,    84,    13,    93,    87,    76,    86,
      18,    19,    10,    76,    77,    13,   355,    88,    86,    32,
      18,    19,    87,    88,   106,    26,    77,    83,   124,    84,
      38,   203,   151,    41,    47,    86,    92,   209,    86,    76,
      38,    49,    55,    41,   383,    83,    83,    88,    76,    76,
      88,    49,    93,   149,   203,    92,    84,    83,   210,   175,
      93,   210,    88,    81,    82,    83,    84,    85,    93,   124,
      86,   131,   127,   127,    92,   239,    87,    88,    83,    76,
      86,   141,    93,    88,    81,    82,    86,   147,    76,    86,
      90,   151,    88,   175,   178,   150,    86,   176,   177,    93,
     155,   180,    86,   182,   189,    83,    88,   203,   193,   448,
      88,    87,    88,   209,   210,    88,    86,   289,    88,    88,
     387,   203,    77,   167,   296,   297,   298,   299,   300,   301,
     190,    83,    84,    85,   253,   195,    81,    82,    83,    84,
      85,   201,    87,    86,   240,    81,    82,    92,   203,    83,
      84,    85,    90,   124,   209,   210,    87,    88,    87,    88,
     220,    64,   222,    66,    67,    68,    69,    70,   228,   229,
     230,   231,   232,   233,   234,    86,   236,   237,    81,    82,
      83,    84,    85,    93,   239,    87,    88,    87,    88,    92,
     269,    74,    75,   289,    77,    78,    79,    80,   257,    86,
     296,   297,   298,   299,   300,   301,    87,    88,    87,   305,
     329,   271,    87,    88,    88,   275,   276,   366,   367,   274,
      87,    88,    87,    88,   279,    86,   286,   379,   324,   325,
     379,    88,   203,    88,   289,   295,    86,    88,   209,   210,
      86,   296,   297,   298,   299,   300,   301,    57,    86,   309,
      90,   358,    77,   360,   309,    72,    86,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    88,    84,   328,    86,
     366,   367,   357,   392,    85,   246,    84,   332,    76,    88,
     365,   341,    89,   379,   366,    81,    82,    83,    84,    85,
      90,   387,    83,    72,   354,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    86,   360,   455,    86,    87,    86,
      90,   366,   367,   462,    85,    88,    88,    81,   289,    81,
      82,    83,    84,    85,   379,   296,   297,   298,   299,   300,
     301,    89,    87,    77,   441,    88,    56,    88,    61,    62,
      88,   401,   402,    88,   404,    87,    69,    87,   408,    88,
      73,   458,    87,    76,    87,    87,   416,   417,    87,   455,
      87,   421,    77,    88,    86,   425,   462,    90,    91,    87,
     425,    88,     8,    87,    50,    28,   421,   360,   417,   366,
     359,    62,   264,    63,    64,    65,    66,    67,    68,    69,
      70,    71,   452,    73,   401,   366,   367,   399,   256,   305,
     455,    81,    82,    83,    84,    85,   129,   462,   379,    89,
     324,    72,    92,    74,    75,    76,    77,    78,    79,    80,
      81,    82,   257,    84,   325,    86,   149,    10,   395,    12,
      13,   396,   340,    16,    17,    18,    19,   174,   272,   191,
     309,    -1,   165,   166,    77,    28,    -1,    30,    31,    -1,
      -1,    -1,    35,   176,   177,    38,    39,   180,    41,   182,
      43,    -1,    45,    -1,    -1,    -1,    49,    -1,    -1,    52,
      53,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      -1,     3,     4,    86,   455,     7,     8,     9,    -1,    11,
      -1,   462,    14,    -1,    -1,    -1,    -1,    -1,    20,    21,
      22,    23,    24,    25,    -1,    27,    -1,    -1,    -1,    -1,
      93,    33,    34,    -1,    -1,    37,   239,    -1,    -1,    -1,
      42,    -1,    44,    -1,    46,    -1,    48,    -1,    50,    51,
      -1,    -1,    54,    -1,    56,    -1,    -1,    59,    -1,    -1,
      -1,   264,    -1,    -1,    63,    64,   269,    66,    67,    68,
      69,    70,    -1,    -1,    76,    77,    -1,    -1,    -1,    -1,
      -1,    -1,    81,    82,    83,    84,    85,    -1,    -1,    -1,
      -1,    -1,    -1,    92,    -1,     3,     4,    -1,    -1,     7,
       8,     9,   305,    11,   307,    -1,    14,    -1,    -1,    -1,
      -1,    -1,    20,    21,    22,    23,    24,    25,    -1,    27,
      -1,   324,   325,    -1,    -1,    33,    34,    -1,    -1,    37,
      -1,    -1,    -1,    -1,    42,    -1,    44,   340,    46,   342,
      48,    -1,    50,    51,    -1,    -1,    54,    -1,    -1,    -1,
      -1,    59,    -1,    10,    -1,    12,    13,    -1,    -1,    16,
      17,    18,    19,    -1,    -1,    -1,    -1,    -1,    76,    26,
      -1,    28,    -1,    30,    31,    -1,    -1,    -1,    35,    -1,
      -1,    38,    39,    -1,    41,    -1,    43,    -1,    45,    -1,
      -1,    10,    49,    12,    13,    52,    53,    -1,    17,    18,
      19,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    28,
      -1,    30,    -1,    -1,    -1,    -1,    35,    -1,    -1,    38,
      39,    -1,    41,    -1,    43,    -1,    45,    -1,    -1,    -1,
      49,    -1,    -1,    52,    53,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    -1,    73,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    81,    82,    83,    84,    85,    -1,    87,
      88,    -1,    -1,    -1,    92,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    -1,    73,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    81,    82,    83,    84,    85,    -1,    87,
      -1,    -1,    -1,    -1,    92,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    -1,    73,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    81,    82,    83,    84,    85,    -1,    87,
      -1,    -1,    -1,    -1,    92,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    -1,    73,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    81,    82,    83,    84,    85,    -1,    87,
      -1,    -1,    -1,    -1,    92,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    -1,    73,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    81,    82,    83,    84,    85,    -1,    -1,
      -1,    89,    -1,    -1,    92,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    -1,    73,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    81,    82,    83,    84,    85,    -1,    87,
      -1,    -1,    -1,    -1,    92,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    -1,    73,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    81,    82,    83,    84,    85,    -1,    -1,
      88,    -1,    -1,    -1,    92,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    -1,    73,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    81,    82,    83,    84,    85,    -1,    87,
      -1,    -1,    -1,    -1,    92,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    -1,    73,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    81,    82,    83,    84,    85,    -1,    87,
      -1,    -1,    -1,    -1,    92,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    -1,    73,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    81,    82,    83,    84,    85,    -1,    -1,
      88,    -1,    -1,    -1,    92,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    -1,    73,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    81,    82,    83,    84,    85,    -1,    -1,
      -1,    -1,    63,    64,    92,    66,    67,    68,    69,    70,
      -1,    -1,    73,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      81,    82,    83,    84,    85,    -1,    -1,    -1,    -1,    -1,
      64,    92,    66,    67,    68,    69,    70,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    81,    82,    83,
      84,    85,    -1,    -1,    -1,    -1,    -1,    72,    92,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    -1,    84,
      -1,    86,    87,    72,    -1,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    -1,    84,    72,    86,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    -1,    84,    72,
      86,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      -1,    -1,    -1,    86,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    -1,    84,    -1,    86,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    -1,    84,    -1,    86,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    -1,
      84,    -1,    86
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    10,    13,    18,    19,    38,    41,    49,    96,    97,
     101,   184,   185,   186,     0,    97,    98,   100,     6,    32,
      47,    55,   206,    84,   187,    16,    31,    93,   104,   105,
     106,   107,   139,   160,    26,   103,    76,   178,   181,    77,
      86,   200,    76,    86,   161,   165,   166,   176,   177,   188,
      99,   105,    93,    12,    17,    28,    30,    35,    39,    43,
      45,    52,    53,   108,   140,   143,   144,   145,   150,   151,
     153,   154,   158,   159,   167,   173,   185,     3,     4,     7,
       8,     9,    11,    14,    20,    21,    22,    23,    24,    25,
      27,    33,    34,    37,    42,    44,    46,    48,    50,    51,
      54,    59,   102,   109,   110,   111,   112,   115,   122,   123,
     124,   125,   126,   127,   129,   130,   131,   132,   133,   134,
     135,   136,   138,   188,   204,   205,    88,   207,    93,    86,
     182,    72,    74,    75,    77,    78,    79,    80,    81,    82,
      84,    86,   188,   192,   193,   197,   198,   202,   161,    83,
      88,    86,   189,   103,    93,    86,   155,   156,   177,   180,
     168,   169,   185,   179,   181,    86,    86,    83,    92,   141,
     142,   152,   176,   141,    88,    88,    88,    88,   207,   146,
     152,   176,    88,   146,   146,   198,    58,    77,   188,   199,
      86,   176,    86,   176,   199,    86,   191,   192,   191,   191,
     180,    90,    84,    86,   116,   188,   194,   195,   197,   202,
      86,   161,    84,    87,   176,   183,    93,   192,    87,   192,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    73,
      81,    82,    83,    84,    85,    87,    92,   203,   192,    88,
      86,   162,   163,   164,   176,   196,   201,   202,   165,    87,
     190,   191,   192,    86,   157,   188,    88,    88,    86,   174,
     175,   176,   176,   181,    88,   179,   180,   146,   146,   152,
     146,    86,   147,   146,    57,    86,    90,   128,    58,   207,
     192,   182,   137,   199,   207,   192,    86,   113,   192,    86,
     116,   117,   118,   177,   194,    88,    81,    82,    83,    84,
      85,    92,   194,   195,   116,    83,    87,    88,    87,    88,
     192,   192,   192,   192,   192,   192,   192,   192,   192,   192,
     192,   176,   196,    83,    88,    84,   197,    87,    88,    89,
     191,    87,    88,   156,   169,    76,   170,   171,   172,    87,
      88,    90,    88,    83,   142,   146,    84,   148,   149,   192,
     187,   188,   192,   192,    86,   188,    87,    87,    88,    86,
      87,    84,    87,   114,   192,    87,    88,    90,    87,   119,
     120,   121,   192,   194,   194,   194,   194,   194,   194,    88,
     162,    84,   176,   188,   190,   192,   128,    88,   163,   164,
     192,   191,    89,   188,    87,    88,    81,   175,   192,   176,
      87,    88,    89,    87,    88,   192,   128,    56,   207,   199,
     137,    56,   109,   199,    77,    87,    88,   207,   118,    84,
     195,    88,   116,    83,   128,    88,    87,    87,   196,    87,
     191,   171,   172,   147,   148,    84,   192,   192,    87,   192,
      87,    88,    84,   192,   119,   121,    87,    87,   188,    87,
      87,    87,    88,   199,    77,    86,   128,   192,    88,   195,
      87,   199,    88,   195,    87
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
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (YYID (N))                                                     \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (YYID (0))
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])



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
  FILE *yyo = yyoutput;
  YYUSE (yyo);
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
  YYSIZE_T yysize0 = yytnamerr (YY_NULL, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  YYSIZE_T yysize1;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
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
                yysize1 = yysize + yytnamerr (YY_NULL, yytname[yyx]);
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
        case 3:
/* Line 1787 of yacc.c  */
#line 382 "yacc.in"
    { FatalError("parser", 
			 "Multiple modules in one file! Check fsplit!");}
    break;

  case 4:
/* Line 1787 of yacc.c  */
#line 386 "yacc.in"
    {reset_first_statement();}
    break;

  case 5:
/* Line 1787 of yacc.c  */
#line 386 "yacc.in"
    { check_first_statement();}
    break;

  case 7:
/* Line 1787 of yacc.c  */
#line 387 "yacc.in"
    {reset_first_statement(); check_first_statement();}
    break;

  case 9:
/* Line 1787 of yacc.c  */
#line 392 "yacc.in"
    { 
                 MakeCurrentFunction((yyvsp[(1) - (5)].type), (yyvsp[(2) - (5)].integer), (yyvsp[(3) - (5)].string), (yyvsp[(4) - (5)].liste));
            }
    break;

  case 10:
/* Line 1787 of yacc.c  */
#line 398 "yacc.in"
    { 
	      /* In case the entry is a FUNCTION, you want to recover its type.
	       * You cannot use entity_functional_name as second rule element.
	       */
		if(get_bool_property("PARSER_SUBSTITUTE_ENTRIES")) {
		    (yyval.instruction) = MakeEntry((yyvsp[(2) - (3)].entity), (yyvsp[(3) - (3)].liste));
		}
		else {
		    ParserError("Syntax", "ENTRY are not directly processed. "
				"Set property PARSER_SUBSTITUTE_ENTRIES to allow "
				"entry substitutions");
		}
            }
    break;

  case 11:
/* Line 1787 of yacc.c  */
#line 414 "yacc.in"
    { EndOfProcedure(); }
    break;

  case 15:
/* Line 1787 of yacc.c  */
#line 424 "yacc.in"
    { /* can appear anywhere in specs and execs! */ 
	    if (first_executable_statement_seen())
	    {
		/* the DATA string to be added to declarations...
		 * however, the information is not really available.
		 * as a hack, I'll try to append the Stmt buffer, but it
		 * has already been processed, thus it is quite far
		 * from the initial statement, and may be incorrect.
		 * I think that this parser is a mess;-) FC.
		 */
		pips_user_warning(
		    "DATA as an executable statement, moved up...\n");
		append_data_current_stmt_buffer_to_declarations();
	    }

	    /* See if we could save the DATA statements somewhere */
	    /* dump_current_statement(); */

	}
    break;

  case 16:
/* Line 1787 of yacc.c  */
#line 443 "yacc.in"
    { check_in_declarations();}
    break;

  case 18:
/* Line 1787 of yacc.c  */
#line 444 "yacc.in"
    { check_first_statement();}
    break;

  case 19:
/* Line 1787 of yacc.c  */
#line 445 "yacc.in"
    { 
		if ((yyvsp[(2) - (2)].instruction) != instruction_undefined)
			LinkInstToCurrentBlock((yyvsp[(2) - (2)].instruction), true);
	    }
    break;

  case 20:
/* Line 1787 of yacc.c  */
#line 450 "yacc.in"
    { 
		LinkInstToCurrentBlock((yyvsp[(1) - (1)].instruction), true);
	    }
    break;

  case 26:
/* Line 1787 of yacc.c  */
#line 460 "yacc.in"
    {}
    break;

  case 31:
/* Line 1787 of yacc.c  */
#line 468 "yacc.in"
    { (yyval.instruction) = (yyvsp[(1) - (1)].instruction); }
    break;

  case 32:
/* Line 1787 of yacc.c  */
#line 470 "yacc.in"
    { (yyval.instruction) = (yyvsp[(1) - (1)].instruction); }
    break;

  case 33:
/* Line 1787 of yacc.c  */
#line 472 "yacc.in"
    { (yyval.instruction) = (yyvsp[(1) - (1)].instruction); }
    break;

  case 34:
/* Line 1787 of yacc.c  */
#line 474 "yacc.in"
    { (yyval.instruction) = (yyvsp[(1) - (1)].instruction); }
    break;

  case 35:
/* Line 1787 of yacc.c  */
#line 476 "yacc.in"
    { (yyval.instruction) = (yyvsp[(1) - (1)].instruction); }
    break;

  case 36:
/* Line 1787 of yacc.c  */
#line 478 "yacc.in"
    { (yyval.instruction) = (yyvsp[(1) - (1)].instruction); }
    break;

  case 37:
/* Line 1787 of yacc.c  */
#line 480 "yacc.in"
    { (yyval.instruction) = instruction_undefined; }
    break;

  case 38:
/* Line 1787 of yacc.c  */
#line 482 "yacc.in"
    { (yyval.instruction) = instruction_undefined; }
    break;

  case 39:
/* Line 1787 of yacc.c  */
#line 484 "yacc.in"
    { (yyval.instruction) = instruction_undefined; }
    break;

  case 40:
/* Line 1787 of yacc.c  */
#line 486 "yacc.in"
    { (yyval.instruction) = instruction_undefined; }
    break;

  case 41:
/* Line 1787 of yacc.c  */
#line 488 "yacc.in"
    { (yyval.instruction) = instruction_undefined; }
    break;

  case 42:
/* Line 1787 of yacc.c  */
#line 490 "yacc.in"
    { (yyval.instruction) = instruction_undefined; }
    break;

  case 43:
/* Line 1787 of yacc.c  */
#line 492 "yacc.in"
    { (yyval.instruction) = (yyvsp[(1) - (1)].instruction); }
    break;

  case 44:
/* Line 1787 of yacc.c  */
#line 494 "yacc.in"
    { (yyval.instruction) = (yyvsp[(1) - (1)].instruction); }
    break;

  case 45:
/* Line 1787 of yacc.c  */
#line 496 "yacc.in"
    { (yyval.instruction) = (yyvsp[(1) - (1)].instruction); }
    break;

  case 46:
/* Line 1787 of yacc.c  */
#line 498 "yacc.in"
    { (yyval.instruction) = (yyvsp[(1) - (1)].instruction); }
    break;

  case 47:
/* Line 1787 of yacc.c  */
#line 500 "yacc.in"
    { (yyval.instruction) = (yyvsp[(1) - (1)].instruction); }
    break;

  case 48:
/* Line 1787 of yacc.c  */
#line 502 "yacc.in"
    { (yyval.instruction) = (yyvsp[(1) - (1)].instruction); }
    break;

  case 49:
/* Line 1787 of yacc.c  */
#line 504 "yacc.in"
    { (yyval.instruction) = (yyvsp[(1) - (1)].instruction); }
    break;

  case 50:
/* Line 1787 of yacc.c  */
#line 508 "yacc.in"
    { (yyval.instruction) = MakeReturn((yyvsp[(2) - (2)].expression)); }
    break;

  case 51:
/* Line 1787 of yacc.c  */
#line 512 "yacc.in"
    { (yyval.instruction) = MakeCallInst((yyvsp[(2) - (2)].entity), NIL); reset_alternate_returns();}
    break;

  case 52:
/* Line 1787 of yacc.c  */
#line 515 "yacc.in"
    { (yyval.instruction) = MakeCallInst((yyvsp[(2) - (3)].entity), (yyvsp[(3) - (3)].liste)); reset_alternate_returns(); }
    break;

  case 53:
/* Line 1787 of yacc.c  */
#line 519 "yacc.in"
    { set_alternate_returns();}
    break;

  case 54:
/* Line 1787 of yacc.c  */
#line 523 "yacc.in"
    { (yyval.liste) = NULL; }
    break;

  case 55:
/* Line 1787 of yacc.c  */
#line 525 "yacc.in"
    { (yyval.liste) = (yyvsp[(2) - (3)].liste); }
    break;

  case 56:
/* Line 1787 of yacc.c  */
#line 529 "yacc.in"
    {
		(yyval.liste) = CONS(EXPRESSION, (yyvsp[(1) - (1)].expression), NIL);
	    }
    break;

  case 57:
/* Line 1787 of yacc.c  */
#line 533 "yacc.in"
    {
		(yyval.liste) = gen_nconc((yyvsp[(1) - (3)].liste), CONS(EXPRESSION, (yyvsp[(3) - (3)].expression), NIL));
	    }
    break;

  case 58:
/* Line 1787 of yacc.c  */
#line 537 "yacc.in"
    {
		add_alternate_return((yyvsp[(2) - (2)].string));
		(yyval.liste) = CONS(EXPRESSION,
			  generate_string_for_alternate_return_argument((yyvsp[(2) - (2)].string)),
			  NIL);
	    }
    break;

  case 59:
/* Line 1787 of yacc.c  */
#line 544 "yacc.in"
    {
		add_alternate_return((yyvsp[(4) - (4)].string));
		(yyval.liste) = gen_nconc((yyvsp[(1) - (4)].liste), CONS(EXPRESSION,
					generate_string_for_alternate_return_argument((yyvsp[(4) - (4)].string)),
					NIL));
	    }
    break;

  case 60:
/* Line 1787 of yacc.c  */
#line 554 "yacc.in"
    { 
                (yyval.instruction) = MakeSimpleIoInst1((yyvsp[(1) - (2)].integer), (yyvsp[(2) - (2)].expression));
	    }
    break;

  case 61:
/* Line 1787 of yacc.c  */
#line 558 "yacc.in"
    {
		(yyval.instruction) = MakeSimpleIoInst2((yyvsp[(1) - (4)].integer), (yyvsp[(2) - (4)].expression), (yyvsp[(4) - (4)].liste));
	    }
    break;

  case 62:
/* Line 1787 of yacc.c  */
#line 562 "yacc.in"
    { (yyval.instruction) = MakeIoInstA((yyvsp[(1) - (6)].integer), (yyvsp[(3) - (6)].liste), (yyvsp[(6) - (6)].liste)); }
    break;

  case 63:
/* Line 1787 of yacc.c  */
#line 565 "yacc.in"
    { (yyval.instruction) = MakeIoInstB((yyvsp[(1) - (11)].integer), (yyvsp[(3) - (11)].expression), (yyvsp[(5) - (11)].expression), (yyvsp[(8) - (11)].expression), (yyvsp[(10) - (11)].expression)); }
    break;

  case 65:
/* Line 1787 of yacc.c  */
#line 570 "yacc.in"
    { (yyval.expression) = MakeNullaryCall(CreateIntrinsic(LIST_DIRECTED_FORMAT_NAME)); }
    break;

  case 66:
/* Line 1787 of yacc.c  */
#line 574 "yacc.in"
    { (yyval.liste) = (yyvsp[(1) - (1)].liste); }
    break;

  case 67:
/* Line 1787 of yacc.c  */
#line 576 "yacc.in"
    { 
	      /*
		CDR(CDR($3)) = $1;
		$$ = $3;
		*/
	      (yyval.liste) = gen_nconc((yyvsp[(1) - (3)].liste), (yyvsp[(3) - (3)].liste));
	    }
    break;

  case 68:
/* Line 1787 of yacc.c  */
#line 587 "yacc.in"
    {
		char buffer[20];
		(void) strcpy(buffer, (yyvsp[(1) - (3)].string));
		free((yyvsp[(1) - (3)].string));

		if(strcmp(buffer,"END")==0||strcmp(buffer,"ERR")==0) {
		  ;
		}

		(void) strcat(buffer, "=");
		
		(yyval.liste) = CONS(EXPRESSION, 
			  MakeCharacterConstantExpression(buffer),
			  CONS(EXPRESSION, (yyvsp[(3) - (3)].expression), NULL));
		ici += 2;
	    }
    break;

  case 69:
/* Line 1787 of yacc.c  */
#line 604 "yacc.in"
    {
		char buffer[20];
		(void) strcpy(buffer, (yyvsp[(1) - (3)].string));
		free((yyvsp[(1) - (3)].string));

		if(strcmp(buffer,"UNIT")!=0 && strcmp(buffer,"FMT")!=0) {
		  ParserError("parser", 
			  "Illegal default option '*' in IO control list\n");
		}

		(void) strcat(buffer, "=");
		
		(yyval.liste) = CONS(EXPRESSION, 
			  MakeCharacterConstantExpression(buffer),
			  CONS(EXPRESSION,
		 MakeNullaryCall(CreateIntrinsic(LIST_DIRECTED_FORMAT_NAME))
			       , NULL));
		ici += 2;
	    }
    break;

  case 70:
/* Line 1787 of yacc.c  */
#line 624 "yacc.in"
    {
		if(ici==1 || ici==2) {
		(yyval.liste) = CONS(EXPRESSION,
			  MakeCharacterConstantExpression(ici == 1 ? 
			                                  "UNIT=" : 
			                                  "FMT="),
			  CONS(EXPRESSION, (yyvsp[(1) - (1)].expression), NULL));
		}
		else {
		    ParserError("Syntax", "The unit identifier and the format identifier"
			" must be first and second in the control info list (standard Page F-12)");
		}
		ici += 1;
	    }
    break;

  case 71:
/* Line 1787 of yacc.c  */
#line 642 "yacc.in"
    { (yyval.liste) = NULL; }
    break;

  case 72:
/* Line 1787 of yacc.c  */
#line 644 "yacc.in"
    { (yyval.liste) = MakeIoList((yyvsp[(1) - (1)].liste)); }
    break;

  case 73:
/* Line 1787 of yacc.c  */
#line 648 "yacc.in"
    { (yyval.liste) = CONS(EXPRESSION, (yyvsp[(1) - (1)].expression), NULL); }
    break;

  case 74:
/* Line 1787 of yacc.c  */
#line 650 "yacc.in"
    { (yyval.liste) = CONS(EXPRESSION, (yyvsp[(3) - (3)].expression), (yyvsp[(1) - (3)].liste)); }
    break;

  case 75:
/* Line 1787 of yacc.c  */
#line 654 "yacc.in"
    { (yyval.expression) = (yyvsp[(1) - (1)].expression); }
    break;

  case 76:
/* Line 1787 of yacc.c  */
#line 658 "yacc.in"
    { (yyval.instruction) = MakeZeroOrOneArgCallInst("PAUSE", (yyvsp[(2) - (2)].expression)); }
    break;

  case 77:
/* Line 1787 of yacc.c  */
#line 662 "yacc.in"
    { (yyval.instruction) = MakeZeroOrOneArgCallInst("STOP", (yyvsp[(2) - (2)].expression)); }
    break;

  case 78:
/* Line 1787 of yacc.c  */
#line 666 "yacc.in"
    { (yyval.instruction) = MakeZeroOrOneArgCallInst("CONTINUE", expression_undefined);}
    break;

  case 79:
/* Line 1787 of yacc.c  */
#line 670 "yacc.in"
    { 
		MakeDoInst((yyvsp[(4) - (5)].syntax), (yyvsp[(5) - (5)].range), (yyvsp[(2) - (5)].string)); 
		(yyval.instruction) = instruction_undefined;
	    }
    break;

  case 80:
/* Line 1787 of yacc.c  */
#line 677 "yacc.in"
    { 
		MakeDoInst((yyvsp[(2) - (3)].syntax), (yyvsp[(3) - (3)].range), "BLOCKDO"); 
		(yyval.instruction) = instruction_undefined;
	    }
    break;

  case 81:
/* Line 1787 of yacc.c  */
#line 684 "yacc.in"
    { 
	        if(expression_implied_do_p((yyvsp[(4) - (5)].expression)))
		    ParserError("Syntax", "Unexpected implied DO\n");
		MakeWhileDoInst((yyvsp[(4) - (5)].expression), "BLOCKDO");
		(yyval.instruction) = instruction_undefined;
	    }
    break;

  case 82:
/* Line 1787 of yacc.c  */
#line 691 "yacc.in"
    { 
	        if(expression_implied_do_p((yyvsp[(5) - (6)].expression)))
		    ParserError("Syntax", "Unexpected implied DO\n");
		MakeWhileDoInst((yyvsp[(5) - (6)].expression), (yyvsp[(2) - (6)].string));
		(yyval.instruction) = instruction_undefined;
	    }
    break;

  case 83:
/* Line 1787 of yacc.c  */
#line 700 "yacc.in"
    { 
	      if(expression_implied_do_p((yyvsp[(2) - (4)].expression)) || expression_implied_do_p((yyvsp[(4) - (4)].expression)))
		  ParserError("Syntax", "Unexpected implied DO\n");
	      (yyval.range) = make_range((yyvsp[(2) - (4)].expression), (yyvsp[(4) - (4)].expression), int_to_expression(1));
	    }
    break;

  case 84:
/* Line 1787 of yacc.c  */
#line 706 "yacc.in"
    {
	      if(expression_implied_do_p((yyvsp[(2) - (6)].expression)) || expression_implied_do_p((yyvsp[(4) - (6)].expression))
		 || expression_implied_do_p((yyvsp[(6) - (6)].expression)))
		  ParserError("Syntax", "Unexpected implied DO\n");
	      (yyval.range) = make_range((yyvsp[(2) - (6)].expression), (yyvsp[(4) - (6)].expression), (yyvsp[(6) - (6)].expression));
	    }
    break;

  case 85:
/* Line 1787 of yacc.c  */
#line 715 "yacc.in"
    { MakeEndifInst(); }
    break;

  case 86:
/* Line 1787 of yacc.c  */
#line 719 "yacc.in"
    { MakeEnddoInst(); }
    break;

  case 87:
/* Line 1787 of yacc.c  */
#line 723 "yacc.in"
    { MakeElseInst(true); }
    break;

  case 88:
/* Line 1787 of yacc.c  */
#line 727 "yacc.in"
    {
		int elsifs = MakeElseInst(false);

	        if(expression_implied_do_p((yyvsp[(3) - (5)].expression)))
		    ParserError("Syntax", "Unexpected implied DO\n");
		MakeBlockIfInst( (yyvsp[(3) - (5)].expression), elsifs+1 );
		(yyval.instruction) = instruction_undefined;
	    }
    break;

  case 89:
/* Line 1787 of yacc.c  */
#line 738 "yacc.in"
    {
	        if(expression_implied_do_p((yyvsp[(3) - (5)].expression)))
		    ParserError("Syntax", "Unexpected implied DO\n");
		MakeBlockIfInst((yyvsp[(3) - (5)].expression),0);
		(yyval.instruction) = instruction_undefined;
	    }
    break;

  case 90:
/* Line 1787 of yacc.c  */
#line 747 "yacc.in"
    {
	        if(expression_implied_do_p((yyvsp[(3) - (5)].expression)))
		    ParserError("Syntax", "Unexpected implied DO\n");
		(yyval.instruction) = MakeLogicalIfInst((yyvsp[(3) - (5)].expression), (yyvsp[(5) - (5)].instruction)); 
	    }
    break;

  case 91:
/* Line 1787 of yacc.c  */
#line 756 "yacc.in"
    {
	        if(expression_implied_do_p((yyvsp[(3) - (9)].expression)))
		    ParserError("Syntax", "Unexpected implied DO\n");
		(yyval.instruction) = MakeArithmIfInst((yyvsp[(3) - (9)].expression), (yyvsp[(5) - (9)].string), (yyvsp[(7) - (9)].string), (yyvsp[(9) - (9)].string));
	    }
    break;

  case 92:
/* Line 1787 of yacc.c  */
#line 764 "yacc.in"
    {
		(yyval.instruction) = MakeGotoInst((yyvsp[(2) - (2)].string));
	    }
    break;

  case 93:
/* Line 1787 of yacc.c  */
#line 768 "yacc.in"
    {
	        if(expression_implied_do_p((yyvsp[(6) - (6)].expression)))
		    ParserError("Syntax", "Unexpected implied DO\n");
		(yyval.instruction) = MakeComputedGotoInst((yyvsp[(3) - (6)].liste), (yyvsp[(6) - (6)].expression));
	    }
    break;

  case 94:
/* Line 1787 of yacc.c  */
#line 774 "yacc.in"
    {
                if(get_bool_property("PARSER_SUBSTITUTE_ASSIGNED_GOTO")) {
		    (yyval.instruction) = MakeAssignedGotoInst((yyvsp[(5) - (6)].liste), (yyvsp[(2) - (6)].entity));
		}
		else {
		    ParserError("parser", "assigned goto statement prohibited"
				" unless property PARSER_SUBSTITUTE_ASSIGNED_GOTO is set\n");
		}
	    }
    break;

  case 95:
/* Line 1787 of yacc.c  */
#line 784 "yacc.in"
    {
                if(get_bool_property("PARSER_SUBSTITUTE_ASSIGNED_GOTO")) {
		    ParserError("parser", "assigned goto statement cannot be"
				" desugared without a target list\n");
		}
		else {
		    ParserError("parser", "assigned goto statement prohibited\n");
		}
	    }
    break;

  case 96:
/* Line 1787 of yacc.c  */
#line 796 "yacc.in"
    {
               (yyval.liste) = CONS(STRING, (yyvsp[(1) - (1)].string), NIL);
            }
    break;

  case 97:
/* Line 1787 of yacc.c  */
#line 800 "yacc.in"
    {
               (yyval.liste) = CONS(STRING, (yyvsp[(3) - (3)].string), (yyvsp[(1) - (3)].liste));
            }
    break;

  case 98:
/* Line 1787 of yacc.c  */
#line 806 "yacc.in"
    {
                if(get_bool_property("PARSER_SUBSTITUTE_ASSIGNED_GOTO")) {
		    expression e = entity_to_expression((yyvsp[(2) - (4)].entity));
		    (yyval.instruction) = MakeAssignInst((yyvsp[(4) - (4)].syntax), e);
		}
		else {
		    ParserError("parser", "ASSIGN statement prohibited by PIPS"
				" unless property PARSER_SUBSTITUTE_ASSIGNED_GOTO is set\n");
		}
	    }
    break;

  case 99:
/* Line 1787 of yacc.c  */
#line 817 "yacc.in"
    {
		syntax s = (yyvsp[(1) - (3)].syntax);
		syntax new_s = syntax_undefined;

	        if(expression_implied_do_p((yyvsp[(3) - (3)].expression)))
		  ParserError("Syntax", "Unexpected implied DO\n");

		new_s = CheckLeftHandSide(s);

		(yyval.instruction) = MakeAssignInst(new_s, (yyvsp[(3) - (3)].expression));
	    }
    break;

  case 100:
/* Line 1787 of yacc.c  */
#line 831 "yacc.in"
    {
		set_first_format_statement();
		(yyval.instruction) = MakeZeroOrOneArgCallInst("FORMAT",
			MakeCharacterConstantExpression(FormatValue));
	    }
    break;

  case 101:
/* Line 1787 of yacc.c  */
#line 839 "yacc.in"
    { save_all_entities(); }
    break;

  case 106:
/* Line 1787 of yacc.c  */
#line 849 "yacc.in"
    { ProcessSave((yyvsp[(1) - (1)].entity)); }
    break;

  case 107:
/* Line 1787 of yacc.c  */
#line 851 "yacc.in"
    { SaveCommon((yyvsp[(1) - (1)].entity)); }
    break;

  case 108:
/* Line 1787 of yacc.c  */
#line 855 "yacc.in"
    {
		(void) DeclareIntrinsic((yyvsp[(2) - (2)].entity));
	    }
    break;

  case 109:
/* Line 1787 of yacc.c  */
#line 859 "yacc.in"
    {
		(void) DeclareIntrinsic((yyvsp[(3) - (3)].entity));
	    }
    break;

  case 110:
/* Line 1787 of yacc.c  */
#line 865 "yacc.in"
    {
		CurrentType = type_undefined;
		(void) DeclareExternalFunction((yyvsp[(2) - (2)].entity));
	    }
    break;

  case 111:
/* Line 1787 of yacc.c  */
#line 870 "yacc.in"
    {
		(void) DeclareExternalFunction((yyvsp[(3) - (3)].entity));
	    }
    break;

  case 112:
/* Line 1787 of yacc.c  */
#line 876 "yacc.in"
    {}
    break;

  case 114:
/* Line 1787 of yacc.c  */
#line 881 "yacc.in"
    {
		/* the size returned by lg_fortran_type should be
		   consistent with CurrentType unless it is of type string
		   or undefined */
		type t = CurrentType;

		if(t != type_undefined) {
		    basic b;

		    if(!type_variable_p(CurrentType))
			FatalError("yyparse", "ill. type for CurrentType\n");

		    b = variable_basic(type_variable(CurrentType));

		    /* character [*len1] foo [*len2]:
		     * if len2 is "default" then len1
		     */
		    if(basic_string_p(b))
			t = value_intrinsic_p((yyvsp[(3) - (3)].value))? /* ??? default */
			    copy_type(t):
				MakeTypeVariable
				    (make_basic(is_basic_string, (yyvsp[(3) - (3)].value)), NIL);

		    DeclareVariable((yyvsp[(1) - (3)].entity), t, (yyvsp[(2) - (3)].liste),
			storage_undefined, value_undefined);

		    if(basic_string_p(b))
			free_type(t);
		}
		else
		    DeclareVariable((yyvsp[(1) - (3)].entity), t, (yyvsp[(2) - (3)].liste),
				    storage_undefined, value_undefined);

		(yyval.entity) = (yyvsp[(1) - (3)].entity);
	    }
    break;

  case 115:
/* Line 1787 of yacc.c  */
#line 919 "yacc.in"
    {
		    (yyval.liste) = NULL;
	    }
    break;

  case 116:
/* Line 1787 of yacc.c  */
#line 923 "yacc.in"
    {
		    (yyval.liste) = (yyvsp[(2) - (3)].liste);
	    }
    break;

  case 117:
/* Line 1787 of yacc.c  */
#line 929 "yacc.in"
    {
		    (yyval.liste) = CONS(DIMENSION, (yyvsp[(1) - (1)].dimension), NULL);		    
	    }
    break;

  case 118:
/* Line 1787 of yacc.c  */
#line 933 "yacc.in"
    {
		    (yyval.liste) = CONS(DIMENSION, (yyvsp[(1) - (3)].dimension), (yyvsp[(3) - (3)].liste));
	    }
    break;

  case 119:
/* Line 1787 of yacc.c  */
#line 939 "yacc.in"
    {
	      expression e = (yyvsp[(1) - (1)].expression);
	      type t = expression_to_type(e);
	      if(scalar_integer_type_p(t))
		(yyval.dimension) = make_dimension(int_to_expression(1), e, NIL);
	      else // Not OK with gfortran, maybe OK with f77
		ParserError("Syntax",
			    "Array sized with a non-integer expression");
	      free_type(t);
	    }
    break;

  case 120:
/* Line 1787 of yacc.c  */
#line 950 "yacc.in"
    {
		(yyval.dimension) = make_dimension(int_to_expression(1),
				    MakeNullaryCall(CreateIntrinsic(UNBOUNDED_DIMENSION_NAME)),
				    NIL);
	    }
    break;

  case 121:
/* Line 1787 of yacc.c  */
#line 956 "yacc.in"
    {
		    (yyval.dimension) = make_dimension((yyvsp[(1) - (3)].expression), 
					MakeNullaryCall(CreateIntrinsic(UNBOUNDED_DIMENSION_NAME)),
					NIL);
	    }
    break;

  case 122:
/* Line 1787 of yacc.c  */
#line 962 "yacc.in"
    {
	      expression e1 = (yyvsp[(1) - (3)].expression);
	      type t1 = expression_to_type(e1);
	      expression e2 = (yyvsp[(3) - (3)].expression);
	      type t2 = expression_to_type(e2);
	      if(scalar_integer_type_p(t1) && scalar_integer_type_p(t2))
		(yyval.dimension) = make_dimension(e1, e2, NIL);
	      else // Not OK with gfortran, maybe OK with f77
		ParserError("Syntax",
			    "Array sized with a non-integer expression");
	      free_type(t1), free_type(t2);
	    }
    break;

  case 123:
/* Line 1787 of yacc.c  */
#line 977 "yacc.in"
    { 
		(yyval.entity) = NameToCommon(BLANK_COMMON_LOCAL_NAME);
		AddVariableToCommon((yyval.entity), (yyvsp[(2) - (2)].entity));
	    }
    break;

  case 124:
/* Line 1787 of yacc.c  */
#line 982 "yacc.in"
    {
		(yyval.entity) = (yyvsp[(2) - (3)].entity);
		AddVariableToCommon((yyval.entity), (yyvsp[(3) - (3)].entity));
	    }
    break;

  case 125:
/* Line 1787 of yacc.c  */
#line 987 "yacc.in"
    {
		(yyval.entity) = (yyvsp[(1) - (3)].entity);
		AddVariableToCommon((yyval.entity), (yyvsp[(3) - (3)].entity));
	    }
    break;

  case 126:
/* Line 1787 of yacc.c  */
#line 992 "yacc.in"
    {
		(yyval.entity) = (yyvsp[(3) - (4)].entity);
		AddVariableToCommon((yyval.entity), (yyvsp[(4) - (4)].entity));
	    }
    break;

  case 127:
/* Line 1787 of yacc.c  */
#line 1000 "yacc.in"
    {
		CurrentType = type_undefined;
	    }
    break;

  case 128:
/* Line 1787 of yacc.c  */
#line 1006 "yacc.in"
    {
		(yyval.entity) = NameToCommon(BLANK_COMMON_LOCAL_NAME);
	    }
    break;

  case 129:
/* Line 1787 of yacc.c  */
#line 1010 "yacc.in"
    {
		(yyval.entity) = NameToCommon((yyvsp[(2) - (3)].string));
	    }
    break;

  case 130:
/* Line 1787 of yacc.c  */
#line 1016 "yacc.in"
    {
	      DeclarePointer((yyvsp[(3) - (7)].entity), (yyvsp[(5) - (7)].entity), (yyvsp[(6) - (7)].liste));
            }
    break;

  case 134:
/* Line 1787 of yacc.c  */
#line 1029 "yacc.in"
    { StoreEquivChain((yyvsp[(2) - (3)].chain)); }
    break;

  case 135:
/* Line 1787 of yacc.c  */
#line 1033 "yacc.in"
    {
		(yyval.chain) = make_chain(CONS(ATOM, MakeEquivAtom((yyvsp[(1) - (1)].syntax)), (cons*) NULL));
	    }
    break;

  case 136:
/* Line 1787 of yacc.c  */
#line 1037 "yacc.in"
    { 
		chain_atoms((yyvsp[(1) - (3)].chain)) = CONS(ATOM, MakeEquivAtom((yyvsp[(3) - (3)].syntax)), 
				     chain_atoms((yyvsp[(1) - (3)].chain)));
		(yyval.chain) = (yyvsp[(1) - (3)].chain);
	    }
    break;

  case 137:
/* Line 1787 of yacc.c  */
#line 1045 "yacc.in"
    {
	    }
    break;

  case 138:
/* Line 1787 of yacc.c  */
#line 1048 "yacc.in"
    {
	    }
    break;

  case 139:
/* Line 1787 of yacc.c  */
#line 1053 "yacc.in"
    {
		CurrentType = type_undefined;
	    }
    break;

  case 140:
/* Line 1787 of yacc.c  */
#line 1059 "yacc.in"
    {
	      /* AnalyzeData($2, $4); */
	      MakeDataStatement((yyvsp[(2) - (5)].liste), (yyvsp[(4) - (5)].liste));
	    }
    break;

  case 141:
/* Line 1787 of yacc.c  */
#line 1064 "yacc.in"
    {
	      /* AnalyzeData($3, $5); */
	      MakeDataStatement((yyvsp[(3) - (6)].liste), (yyvsp[(5) - (6)].liste));
	    }
    break;

  case 142:
/* Line 1787 of yacc.c  */
#line 1071 "yacc.in"
    {
		(yyval.liste) = CONS(EXPRESSION, (yyvsp[(1) - (1)].expression), NIL);
	    }
    break;

  case 143:
/* Line 1787 of yacc.c  */
#line 1075 "yacc.in"
    {
		(yyval.liste) = gen_nconc((yyvsp[(1) - (3)].liste), CONS(EXPRESSION, (yyvsp[(3) - (3)].expression), NIL));
	    }
    break;

  case 144:
/* Line 1787 of yacc.c  */
#line 1082 "yacc.in"
    {
		(yyval.liste) = CONS(EXPRESSION, (yyvsp[(1) - (1)].expression), NIL);
	    }
    break;

  case 145:
/* Line 1787 of yacc.c  */
#line 1086 "yacc.in"
    {
		(yyval.liste) = gen_nconc((yyvsp[(1) - (3)].liste), CONS(EXPRESSION, (yyvsp[(3) - (3)].expression), NIL));
	    }
    break;

  case 146:
/* Line 1787 of yacc.c  */
#line 1092 "yacc.in"
    {
		(yyval.expression) = MakeDataValueSet(expression_undefined, (yyvsp[(1) - (1)].expression));
	    }
    break;

  case 147:
/* Line 1787 of yacc.c  */
#line 1096 "yacc.in"
    {
		(yyval.expression) = MakeDataValueSet((yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
	    }
    break;

  case 148:
/* Line 1787 of yacc.c  */
#line 1102 "yacc.in"
    {
		(yyval.expression) = (yyvsp[(1) - (1)].expression);
	    }
    break;

  case 149:
/* Line 1787 of yacc.c  */
#line 1106 "yacc.in"
    {
		(yyval.expression) = MakeComplexConstantExpression((yyvsp[(2) - (5)].expression), (yyvsp[(4) - (5)].expression));
	    }
    break;

  case 150:
/* Line 1787 of yacc.c  */
#line 1110 "yacc.in"
    {
		/* Cachan bug 4: there should be a check about the entity
		 * returned as $1 because MakeDatVal() is going to try
		 * to evaluate that expression. The entity must be a
		 * parameter.
		 */
		if(symbolic_constant_entity_p((yyvsp[(1) - (1)].entity))) {
		    (yyval.expression) = make_expression(make_syntax(is_syntax_call,
						     make_call((yyvsp[(1) - (1)].entity), NIL)), 
					 normalized_undefined);
		}
		else {
		    user_warning("gram", "Symbolic constant expected: %s\n",
			       entity_local_name((yyvsp[(1) - (1)].entity)));
		    if(strcmp("Z", entity_local_name((yyvsp[(1) - (1)].entity)))==0) {
			user_warning("gram",
		       "Might be a non supported hexadecimal constant\n");
		    }
		    ParserError("gram", "Error in initializer");
		}
	    }
    break;

  case 151:
/* Line 1787 of yacc.c  */
#line 1144 "yacc.in"
    {
	      (yyval.expression) = make_expression((yyvsp[(1) - (1)].syntax), normalized_undefined);
	    }
    break;

  case 152:
/* Line 1787 of yacc.c  */
#line 1148 "yacc.in"
    { (yyval.expression) = (yyvsp[(1) - (1)].expression); }
    break;

  case 153:
/* Line 1787 of yacc.c  */
#line 1152 "yacc.in"
    {
	      /* $$ = MakeDataVar($2, $5); */
	      reference r = make_reference((yyvsp[(4) - (6)].entity), NIL);
	      syntax s = make_syntax(is_syntax_reference, r);
	      (yyval.expression) = MakeImpliedDo(s, (yyvsp[(5) - (6)].range), (yyvsp[(2) - (6)].liste));
	    }
    break;

  case 154:
/* Line 1787 of yacc.c  */
#line 1161 "yacc.in"
    {
               /* Formal parameters have inherited default implicit types */
               retype_formal_parameters();
	    }
    break;

  case 155:
/* Line 1787 of yacc.c  */
#line 1168 "yacc.in"
    {
	    }
    break;

  case 156:
/* Line 1787 of yacc.c  */
#line 1171 "yacc.in"
    {
	    }
    break;

  case 157:
/* Line 1787 of yacc.c  */
#line 1176 "yacc.in"
    {
	    }
    break;

  case 158:
/* Line 1787 of yacc.c  */
#line 1181 "yacc.in"
    {
	    }
    break;

  case 159:
/* Line 1787 of yacc.c  */
#line 1184 "yacc.in"
    {
	    }
    break;

  case 160:
/* Line 1787 of yacc.c  */
#line 1189 "yacc.in"
    {
		basic b;

		pips_assert("gram.y", type_variable_p(CurrentType));
		b = variable_basic(type_variable(CurrentType));

		cr_implicit(basic_tag(b), SizeOfElements(b), (yyvsp[(1) - (1)].character), (yyvsp[(1) - (1)].character));
	    }
    break;

  case 161:
/* Line 1787 of yacc.c  */
#line 1198 "yacc.in"
    {
		basic b;

		pips_assert("gram.y", type_variable_p(CurrentType));
		b = variable_basic(type_variable(CurrentType));

		cr_implicit(basic_tag(b), SizeOfElements(b), (yyvsp[(1) - (3)].character), (yyvsp[(3) - (3)].character));
	    }
    break;

  case 162:
/* Line 1787 of yacc.c  */
#line 1209 "yacc.in"
    {
		(yyval.character) = (yyvsp[(1) - (1)].string)[0]; free((yyvsp[(1) - (1)].string));
	    }
    break;

  case 166:
/* Line 1787 of yacc.c  */
#line 1222 "yacc.in"
    {
		AddEntityToDeclarations(MakeParameter((yyvsp[(1) - (3)].entity), (yyvsp[(3) - (3)].expression)), get_current_module_entity());
	    }
    break;

  case 167:
/* Line 1787 of yacc.c  */
#line 1228 "yacc.in"
    {
	      /* malloc_verify(); */
	      /* if SafeFind were always used, intrinsic would mask local
                 variables, either when the module declarations are not
                 available or when a new entity still has to be
                 declared. See Validation/capture01.f */
	      /* Let's try not to search intrinsics in SafeFindOrCreateEntity(). */
	      /* Do not declare undeclared variables, because it generates
                 a problem when processing entries. */
	      /* $$ = SafeFindOrCreateEntity(CurrentPackage, $1); */

	      if(!entity_undefined_p(get_current_module_entity())) {
		(yyval.entity) = SafeFindOrCreateEntity(CurrentPackage, (yyvsp[(1) - (1)].string));
		/* AddEntityToDeclarations($$, get_current_module_entity()); */
	      }
	      else
		(yyval.entity) = FindOrCreateEntity(CurrentPackage, (yyvsp[(1) - (1)].string));
	      free((yyvsp[(1) - (1)].string));
	    }
    break;

  case 168:
/* Line 1787 of yacc.c  */
#line 1250 "yacc.in"
    { (yyval.string) = (yyvsp[(1) - (1)].string); }
    break;

  case 169:
/* Line 1787 of yacc.c  */
#line 1254 "yacc.in"
    {
		/* $$ = FindOrCreateEntity(CurrentPackage, $1); */
		/* $$ = FindOrCreateEntity(TOP_LEVEL_MODULE_NAME, $1); */
		CurrentPackage = strdup((yyvsp[(1) - (1)].string));
	        BeginingOfProcedure();
		free((yyvsp[(1) - (1)].string));
		(yyval.string) = (char*)CurrentPackage;
	    }
    break;

  case 170:
/* Line 1787 of yacc.c  */
#line 1265 "yacc.in"
    {
		/* $$ = FindOrCreateEntity(CurrentPackage, $1); */
		(yyval.entity) = FindOrCreateEntity(TOP_LEVEL_MODULE_NAME, (yyvsp[(1) - (1)].string));
		free((yyvsp[(1) - (1)].string));
	    }
    break;

  case 171:
/* Line 1787 of yacc.c  */
#line 1273 "yacc.in"
    {
		/* This includes BLOCKDATA modules because of EXTERNAL */
		(yyval.entity) = NameToFunctionalEntity((yyvsp[(1) - (1)].string));
		free((yyvsp[(1) - (1)].string));
	    }
    break;

  case 172:
/* Line 1787 of yacc.c  */
#line 1281 "yacc.in"
    { (yyval.string) = (yyvsp[(1) - (1)].string); }
    break;

  case 173:
/* Line 1787 of yacc.c  */
#line 1285 "yacc.in"
    {
		    (yyval.liste) = NULL;
	    }
    break;

  case 174:
/* Line 1787 of yacc.c  */
#line 1289 "yacc.in"
    {
		    (yyval.liste) = NULL;
	    }
    break;

  case 175:
/* Line 1787 of yacc.c  */
#line 1293 "yacc.in"
    {
		/* Too early: the current module is still unknown */
		/* $$ = add_formal_return_code($2); */
	      (yyval.liste) = (yyvsp[(2) - (3)].liste);
	    }
    break;

  case 176:
/* Line 1787 of yacc.c  */
#line 1301 "yacc.in"
    {
		    (yyval.liste) = CONS(ENTITY, (yyvsp[(1) - (1)].entity), NULL);
	    }
    break;

  case 177:
/* Line 1787 of yacc.c  */
#line 1305 "yacc.in"
    {
		uses_alternate_return(true);
		(yyval.liste) = CONS(ENTITY, 
			  generate_pseudo_formal_variable_for_formal_label
			  (CurrentPackage, get_current_number_of_alternate_returns()),
			  NIL);
            }
    break;

  case 178:
/* Line 1787 of yacc.c  */
#line 1313 "yacc.in"
    {
		    (yyval.liste) = gen_nconc((yyvsp[(1) - (3)].liste), CONS(ENTITY, (yyvsp[(3) - (3)].entity), NIL));
	    }
    break;

  case 179:
/* Line 1787 of yacc.c  */
#line 1317 "yacc.in"
    {
		uses_alternate_return(true);
		(yyval.liste) = gen_nconc((yyvsp[(1) - (3)].liste), CONS(ENTITY,
					generate_pseudo_formal_variable_for_formal_label
					(CurrentPackage, get_current_number_of_alternate_returns()),
					NIL));
            }
    break;

  case 180:
/* Line 1787 of yacc.c  */
#line 1327 "yacc.in"
    {
		(yyval.type) = CurrentType = (yyvsp[(1) - (1)].type) ;
	    }
    break;

  case 181:
/* Line 1787 of yacc.c  */
#line 1331 "yacc.in"
    {
		(yyval.type) = CurrentType = type_undefined;
	    }
    break;

  case 182:
/* Line 1787 of yacc.c  */
#line 1337 "yacc.in"
    {
                if (value_intrinsic_p((yyvsp[(2) - (2)].value))) /* ??? default! */
                {
		    free_value((yyvsp[(2) - (2)].value));
		    (yyvsp[(2) - (2)].value) = make_value_constant(
		       make_constant_int( CurrentTypeSize));
		}

		(yyval.type) = CurrentType = MakeFortranType((yyvsp[(1) - (2)].tag), (yyvsp[(2) - (2)].value));
	    }
    break;

  case 183:
/* Line 1787 of yacc.c  */
#line 1350 "yacc.in"
    {
		    (yyval.tag) = is_basic_int;
		    CurrentTypeSize = DEFAULT_INTEGER_TYPE_SIZE;
	    }
    break;

  case 184:
/* Line 1787 of yacc.c  */
#line 1355 "yacc.in"
    {
		    (yyval.tag) = is_basic_float; 
		    CurrentTypeSize = DEFAULT_REAL_TYPE_SIZE;
	    }
    break;

  case 185:
/* Line 1787 of yacc.c  */
#line 1360 "yacc.in"
    {
		    (yyval.tag) = is_basic_float; 
		    CurrentTypeSize = DEFAULT_DOUBLEPRECISION_TYPE_SIZE;
	    }
    break;

  case 186:
/* Line 1787 of yacc.c  */
#line 1365 "yacc.in"
    {
		    (yyval.tag) = is_basic_logical; 
		    CurrentTypeSize = DEFAULT_LOGICAL_TYPE_SIZE;
	    }
    break;

  case 187:
/* Line 1787 of yacc.c  */
#line 1370 "yacc.in"
    {
		    (yyval.tag) = is_basic_complex; 
		    CurrentTypeSize = DEFAULT_COMPLEX_TYPE_SIZE;
	    }
    break;

  case 188:
/* Line 1787 of yacc.c  */
#line 1375 "yacc.in"
    {
	            (yyval.tag) = is_basic_complex;
		    CurrentTypeSize = DEFAULT_DOUBLECOMPLEX_TYPE_SIZE;
	    }
    break;

  case 189:
/* Line 1787 of yacc.c  */
#line 1380 "yacc.in"
    {
		    (yyval.tag) = is_basic_string; 
		    CurrentTypeSize = DEFAULT_CHARACTER_TYPE_SIZE;
	    }
    break;

  case 190:
/* Line 1787 of yacc.c  */
#line 1387 "yacc.in"
    {
                   (yyval.value) = make_value(is_value_intrinsic, UU); /* ??? default! */
		/* was: $$ = make_value(is_value_constant,
		 *      make_constant(is_constant_int, CurrentTypeSize)); 
		 * then how to differentiate character*len1 foo[*len2]
		 * if len2 is 1 or whatever... the issue is that 
		 * there should be two lg_..., one for the default that
		 * would change CurrentTypeSize at ival, and the other not...
		 * FC, 13/06/96
		 */
	    }
    break;

  case 191:
/* Line 1787 of yacc.c  */
#line 1399 "yacc.in"
    {
		    (yyval.value) = make_value_unknown();
	    }
    break;

  case 192:
/* Line 1787 of yacc.c  */
#line 1403 "yacc.in"
    {
		    (yyval.value) = MakeValueSymbolic((yyvsp[(3) - (4)].expression));
	    }
    break;

  case 193:
/* Line 1787 of yacc.c  */
#line 1407 "yacc.in"
    {
		    (yyval.value) = make_value_constant(make_constant_int((yyvsp[(2) - (2)].integer)));
	    }
    break;

  case 194:
/* Line 1787 of yacc.c  */
#line 1413 "yacc.in"
    {
		(yyval.syntax) = MakeAtom((yyvsp[(1) - (1)].entity), NIL, expression_undefined, 
				expression_undefined, false);
	    }
    break;

  case 195:
/* Line 1787 of yacc.c  */
#line 1418 "yacc.in"
    {
		(yyval.syntax) = MakeAtom((yyvsp[(1) - (2)].entity), (yyvsp[(2) - (2)].liste), expression_undefined, 
				expression_undefined, true);
	    }
    break;

  case 196:
/* Line 1787 of yacc.c  */
#line 1423 "yacc.in"
    {
		(yyval.syntax) = MakeAtom((yyvsp[(1) - (6)].entity), NIL, (yyvsp[(3) - (6)].expression), (yyvsp[(5) - (6)].expression), true);
	    }
    break;

  case 197:
/* Line 1787 of yacc.c  */
#line 1427 "yacc.in"
    {
		(yyval.syntax) = MakeAtom((yyvsp[(1) - (7)].entity), (yyvsp[(2) - (7)].liste), (yyvsp[(4) - (7)].expression), (yyvsp[(6) - (7)].expression), true);
	    }
    break;

  case 198:
/* Line 1787 of yacc.c  */
#line 1433 "yacc.in"
    { (yyval.liste) = NULL; }
    break;

  case 199:
/* Line 1787 of yacc.c  */
#line 1435 "yacc.in"
    { (yyval.liste) = FortranExpressionList((yyvsp[(2) - (3)].liste)); }
    break;

  case 200:
/* Line 1787 of yacc.c  */
#line 1439 "yacc.in"
    {
		(yyval.liste) = CONS(EXPRESSION, (yyvsp[(1) - (1)].expression), NULL);
	    }
    break;

  case 201:
/* Line 1787 of yacc.c  */
#line 1443 "yacc.in"
    {
		(yyval.liste) = gen_nconc((yyvsp[(1) - (3)].liste), CONS(EXPRESSION, (yyvsp[(3) - (3)].expression), NIL));
	    }
    break;

  case 202:
/* Line 1787 of yacc.c  */
#line 1449 "yacc.in"
    { 
	        if(expression_implied_do_p((yyvsp[(1) - (1)].expression)))
		  ParserError("Syntax", "Unexpected implied DO\n");
		(yyval.expression) = (yyvsp[(1) - (1)].expression);
            }
    break;

  case 203:
/* Line 1787 of yacc.c  */
#line 1455 "yacc.in"
    { (yyval.expression) = expression_undefined; }
    break;

  case 204:
/* Line 1787 of yacc.c  */
#line 1459 "yacc.in"
    { (yyval.expression) = (yyvsp[(1) - (1)].expression); }
    break;

  case 205:
/* Line 1787 of yacc.c  */
#line 1461 "yacc.in"
    { (yyval.expression) = (yyvsp[(2) - (3)].expression); }
    break;

  case 206:
/* Line 1787 of yacc.c  */
#line 1463 "yacc.in"
    {
                    expression c = MakeComplexConstantExpression((yyvsp[(2) - (5)].expression), (yyvsp[(4) - (5)].expression));

                    if(expression_undefined_p(c))
		        ParserError("Syntax", "Illegal complex constant\n");

		    (yyval.expression) = c;
            }
    break;

  case 207:
/* Line 1787 of yacc.c  */
#line 1472 "yacc.in"
    { (yyval.expression) = MakeImpliedDo((yyvsp[(4) - (6)].syntax), (yyvsp[(5) - (6)].range), CONS(EXPRESSION, (yyvsp[(2) - (6)].expression), NIL)); }
    break;

  case 208:
/* Line 1787 of yacc.c  */
#line 1474 "yacc.in"
    { (yyval.expression) = MakeImpliedDo((yyvsp[(6) - (8)].syntax), (yyvsp[(7) - (8)].range), CONS(EXPRESSION, (yyvsp[(2) - (8)].expression), (yyvsp[(4) - (8)].liste))); }
    break;

  case 209:
/* Line 1787 of yacc.c  */
#line 1478 "yacc.in"
    {
		    (yyval.expression) = make_expression((yyvsp[(1) - (1)].syntax), normalized_undefined);
	    }
    break;

  case 210:
/* Line 1787 of yacc.c  */
#line 1482 "yacc.in"
    {
		    (yyval.expression) = MakeNullaryCall((yyvsp[(1) - (1)].entity));    
	    }
    break;

  case 211:
/* Line 1787 of yacc.c  */
#line 1486 "yacc.in"
    {
		    if ((yyvsp[(1) - (2)].integer) == -1)
			(yyval.expression) = MakeFortranUnaryCall(CreateIntrinsic("--"), (yyvsp[(2) - (2)].expression));
		    else
			(yyval.expression) = (yyvsp[(2) - (2)].expression);
	    }
    break;

  case 212:
/* Line 1787 of yacc.c  */
#line 1493 "yacc.in"
    {
		    (yyval.expression) = MakeFortranBinaryCall(CreateIntrinsic("+"), (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
	    }
    break;

  case 213:
/* Line 1787 of yacc.c  */
#line 1497 "yacc.in"
    {
		    (yyval.expression) = MakeFortranBinaryCall(CreateIntrinsic("-"), (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
	    }
    break;

  case 214:
/* Line 1787 of yacc.c  */
#line 1501 "yacc.in"
    {
		    (yyval.expression) = MakeFortranBinaryCall(CreateIntrinsic("*"), (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
	    }
    break;

  case 215:
/* Line 1787 of yacc.c  */
#line 1505 "yacc.in"
    {
		    (yyval.expression) = MakeFortranBinaryCall(CreateIntrinsic("/"), (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
	    }
    break;

  case 216:
/* Line 1787 of yacc.c  */
#line 1509 "yacc.in"
    {
		    (yyval.expression) = MakeFortranBinaryCall(CreateIntrinsic("**"), 
					      (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
	    }
    break;

  case 217:
/* Line 1787 of yacc.c  */
#line 1514 "yacc.in"
    {
		    (yyval.expression) = MakeFortranBinaryCall((yyvsp[(2) - (3)].entity), (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));    
	    }
    break;

  case 218:
/* Line 1787 of yacc.c  */
#line 1518 "yacc.in"
    {
		    (yyval.expression) = MakeFortranBinaryCall(CreateIntrinsic(".EQV."), 
					      (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
	    }
    break;

  case 219:
/* Line 1787 of yacc.c  */
#line 1523 "yacc.in"
    {
		    (yyval.expression) = MakeFortranBinaryCall(CreateIntrinsic(".NEQV."), 
					      (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
	    }
    break;

  case 220:
/* Line 1787 of yacc.c  */
#line 1528 "yacc.in"
    {
		    (yyval.expression) = MakeFortranBinaryCall(CreateIntrinsic(".OR."), 
					       fix_if_condition((yyvsp[(1) - (3)].expression)),
					       fix_if_condition((yyvsp[(3) - (3)].expression)));
	    }
    break;

  case 221:
/* Line 1787 of yacc.c  */
#line 1534 "yacc.in"
    {
		    (yyval.expression) = MakeFortranBinaryCall(CreateIntrinsic(".AND."), 
					       fix_if_condition((yyvsp[(1) - (3)].expression)),
					       fix_if_condition((yyvsp[(3) - (3)].expression)));
	    }
    break;

  case 222:
/* Line 1787 of yacc.c  */
#line 1540 "yacc.in"
    {
		    (yyval.expression) = MakeFortranUnaryCall(CreateIntrinsic(".NOT."),
					      fix_if_condition((yyvsp[(2) - (2)].expression)));
	    }
    break;

  case 223:
/* Line 1787 of yacc.c  */
#line 1545 "yacc.in"
    {
		    (yyval.expression) = MakeFortranBinaryCall(CreateIntrinsic("//"), 
					      (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));    
	    }
    break;

  case 225:
/* Line 1787 of yacc.c  */
#line 1553 "yacc.in"
    { (yyval.expression) = (yyvsp[(2) - (3)].expression); }
    break;

  case 226:
/* Line 1787 of yacc.c  */
#line 1557 "yacc.in"
    {
		    (yyval.expression) = make_expression((yyvsp[(1) - (1)].syntax), normalized_undefined);
	    }
    break;

  case 227:
/* Line 1787 of yacc.c  */
#line 1562 "yacc.in"
    {
		    (yyval.expression) = MakeNullaryCall((yyvsp[(1) - (1)].entity));    
	    }
    break;

  case 228:
/* Line 1787 of yacc.c  */
#line 1566 "yacc.in"
    {
		    if ((yyvsp[(1) - (2)].integer) == -1)
			(yyval.expression) = MakeFortranUnaryCall(CreateIntrinsic("--"), (yyvsp[(2) - (2)].expression));
		    else
			(yyval.expression) = (yyvsp[(2) - (2)].expression);
	    }
    break;

  case 229:
/* Line 1787 of yacc.c  */
#line 1573 "yacc.in"
    {
		    (yyval.expression) = MakeFortranBinaryCall(CreateIntrinsic("+"), (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
	    }
    break;

  case 230:
/* Line 1787 of yacc.c  */
#line 1577 "yacc.in"
    {
		    (yyval.expression) = MakeFortranBinaryCall(CreateIntrinsic("-"), (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
	    }
    break;

  case 231:
/* Line 1787 of yacc.c  */
#line 1581 "yacc.in"
    {
		    (yyval.expression) = MakeFortranBinaryCall(CreateIntrinsic("*"), (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
	    }
    break;

  case 232:
/* Line 1787 of yacc.c  */
#line 1585 "yacc.in"
    {
		    (yyval.expression) = MakeFortranBinaryCall(CreateIntrinsic("/"), (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
	    }
    break;

  case 233:
/* Line 1787 of yacc.c  */
#line 1589 "yacc.in"
    {
		    (yyval.expression) = MakeFortranBinaryCall(CreateIntrinsic("**"), 
					      (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
	    }
    break;

  case 234:
/* Line 1787 of yacc.c  */
#line 1594 "yacc.in"
    {
		    (yyval.expression) = MakeFortranBinaryCall(CreateIntrinsic("//"), 
					      (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));    
	    }
    break;

  case 235:
/* Line 1787 of yacc.c  */
#line 1601 "yacc.in"
    {
		    if ((yyvsp[(1) - (2)].integer) == -1)
			(yyval.expression) = MakeUnaryCall(CreateIntrinsic("--"), 
					   MakeNullaryCall((yyvsp[(2) - (2)].entity)));
		    else
			(yyval.expression) = MakeNullaryCall((yyvsp[(2) - (2)].entity));
	    }
    break;

  case 236:
/* Line 1787 of yacc.c  */
#line 1611 "yacc.in"
    {
	            (yyval.entity) = SafeMakeConstant(".TRUE.", is_basic_logical, ParserError);
	    }
    break;

  case 237:
/* Line 1787 of yacc.c  */
#line 1615 "yacc.in"
    {
	            (yyval.entity) = SafeMakeConstant(".FALSE.", is_basic_logical, ParserError);
	    }
    break;

  case 238:
/* Line 1787 of yacc.c  */
#line 1619 "yacc.in"
    {
		    (yyval.entity) = (yyvsp[(1) - (1)].entity);
	    }
    break;

  case 239:
/* Line 1787 of yacc.c  */
#line 1623 "yacc.in"
    {
		    (yyval.entity) = make_Fortran_constant_entity((yyvsp[(1) - (1)].string), is_basic_float,
						      DEFAULT_DOUBLEPRECISION_TYPE_SIZE);
		    free((yyvsp[(1) - (1)].string));
	    }
    break;

  case 240:
/* Line 1787 of yacc.c  */
#line 1629 "yacc.in"
    {
	            (yyval.entity) = SafeMakeConstant((yyvsp[(1) - (1)].string), is_basic_string, ParserError);
		    free((yyvsp[(1) - (1)].string));
	    }
    break;

  case 241:
/* Line 1787 of yacc.c  */
#line 1634 "yacc.in"
    {
	            (yyval.entity) = SafeMakeConstant((yyvsp[(1) - (1)].string), is_basic_float, ParserError);
		    free((yyvsp[(1) - (1)].string));
	    }
    break;

  case 242:
/* Line 1787 of yacc.c  */
#line 1641 "yacc.in"
    {
	            (yyval.entity) = SafeMakeConstant((yyvsp[(1) - (1)].string), is_basic_int, ParserError);
		    free((yyvsp[(1) - (1)].string));
	    }
    break;

  case 243:
/* Line 1787 of yacc.c  */
#line 1648 "yacc.in"
    {
		    (yyval.string) = (yyvsp[(1) - (1)].string);
	    }
    break;

  case 244:
/* Line 1787 of yacc.c  */
#line 1654 "yacc.in"
    {
		    (yyval.integer) = atoi((yyvsp[(1) - (1)].string));
		    free((yyvsp[(1) - (1)].string));
	    }
    break;

  case 245:
/* Line 1787 of yacc.c  */
#line 1661 "yacc.in"
    {
		    (yyval.integer) = 1;
	    }
    break;

  case 246:
/* Line 1787 of yacc.c  */
#line 1665 "yacc.in"
    {
		    (yyval.integer) = (yyvsp[(1) - (1)].integer);
	    }
    break;

  case 247:
/* Line 1787 of yacc.c  */
#line 1671 "yacc.in"
    {
		    (yyval.integer) = 1;
	    }
    break;

  case 248:
/* Line 1787 of yacc.c  */
#line 1675 "yacc.in"
    {
		    (yyval.integer) = -1;
	    }
    break;

  case 249:
/* Line 1787 of yacc.c  */
#line 1681 "yacc.in"
    {
		    (yyval.entity) = CreateIntrinsic(".EQ.");
	    }
    break;

  case 250:
/* Line 1787 of yacc.c  */
#line 1685 "yacc.in"
    {
		    (yyval.entity) = CreateIntrinsic(".NE.");
	    }
    break;

  case 251:
/* Line 1787 of yacc.c  */
#line 1689 "yacc.in"
    {
		    (yyval.entity) = CreateIntrinsic(".LT.");
	    }
    break;

  case 252:
/* Line 1787 of yacc.c  */
#line 1693 "yacc.in"
    {
		    (yyval.entity) = CreateIntrinsic(".LE.");
	    }
    break;

  case 253:
/* Line 1787 of yacc.c  */
#line 1697 "yacc.in"
    {
		    (yyval.entity) = CreateIntrinsic(".GE.");
	    }
    break;

  case 254:
/* Line 1787 of yacc.c  */
#line 1701 "yacc.in"
    {
		    (yyval.entity) = CreateIntrinsic(".GT.");
	    }
    break;

  case 255:
/* Line 1787 of yacc.c  */
#line 1707 "yacc.in"
    { (yyval.integer) = TK_PRINT; ici = 1; }
    break;

  case 256:
/* Line 1787 of yacc.c  */
#line 1709 "yacc.in"
    { (yyval.integer) = TK_WRITE; ici = 1; }
    break;

  case 257:
/* Line 1787 of yacc.c  */
#line 1711 "yacc.in"
    { (yyval.integer) = TK_READ; ici = 1; }
    break;

  case 258:
/* Line 1787 of yacc.c  */
#line 1713 "yacc.in"
    { (yyval.integer) = TK_CLOSE; ici = 1; }
    break;

  case 259:
/* Line 1787 of yacc.c  */
#line 1715 "yacc.in"
    { (yyval.integer) = TK_OPEN; ici = 1; }
    break;

  case 260:
/* Line 1787 of yacc.c  */
#line 1717 "yacc.in"
    { (yyval.integer) = TK_ENDFILE; ici = 1; }
    break;

  case 261:
/* Line 1787 of yacc.c  */
#line 1719 "yacc.in"
    { (yyval.integer) = TK_BACKSPACE; ici = 1; }
    break;

  case 262:
/* Line 1787 of yacc.c  */
#line 1721 "yacc.in"
    { (yyval.integer) = TK_REWIND; ici = 1; }
    break;

  case 263:
/* Line 1787 of yacc.c  */
#line 1723 "yacc.in"
    { (yyval.integer) = TK_INQUIRE; ici = 1; }
    break;

  case 264:
/* Line 1787 of yacc.c  */
#line 1727 "yacc.in"
    { (yyval.integer) = TK_BUFFERIN; ici = 1; }
    break;

  case 265:
/* Line 1787 of yacc.c  */
#line 1729 "yacc.in"
    { (yyval.integer) = TK_BUFFEROUT ; ici = 1; }
    break;

  case 266:
/* Line 1787 of yacc.c  */
#line 1733 "yacc.in"
    { (yyval.integer) = TK_PROGRAM; init_ghost_variable_entities(); }
    break;

  case 267:
/* Line 1787 of yacc.c  */
#line 1735 "yacc.in"
    { (yyval.integer) = TK_SUBROUTINE; init_ghost_variable_entities();
	    set_current_number_of_alternate_returns();}
    break;

  case 268:
/* Line 1787 of yacc.c  */
#line 1738 "yacc.in"
    { (yyval.integer) = TK_FUNCTION; init_ghost_variable_entities();
	    set_current_number_of_alternate_returns();}
    break;

  case 269:
/* Line 1787 of yacc.c  */
#line 1741 "yacc.in"
    { (yyval.integer) = TK_BLOCKDATA; init_ghost_variable_entities(); }
    break;


/* Line 1787 of yacc.c  */
#line 4334 "y.tab.c"
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


/* Line 2048 of yacc.c  */
#line 1747 "yacc.in"


