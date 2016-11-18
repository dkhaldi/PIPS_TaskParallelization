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
#define yyparse         genread_parse
#define yylex           genread_lex
#define yyerror         genread_error
#define yylval          genread_lval
#define yychar          genread_char
#define yydebug         genread_debug
#define yynerrs         genread_nerrs

/* Copy the first part of user declarations.  */
/* Line 336 of yacc.c  */
#line 1 "read.y"

/*

  $Id: read.y 1361 2016-07-01 11:57:40Z coelho $

  Copyright 1989-2014 MINES ParisTech

  This file is part of NewGen.

  NewGen is free software: you can redistribute it and/or modify it under the
  terms of the GNU General Public License as published by the Free Software
  Foundation, either version 3 of the License, or any later version.

  NewGen is distributed in the hope that it will be useful, but WITHOUT ANY
  WARRANTY; without even the implied warranty of MERCHANTABILITY or
  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public
  License for more details.

  You should have received a copy of the GNU General Public License along with
  NewGen.  If not, see <http://www.gnu.org/licenses/>.

*/

/* The syntax of objects printed by GEN_WRITE. */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "genC.h"
#include "newgen_include.h"

extern void newgen_lexer_position(FILE *);

#define YYERROR_VERBOSE 1 /* better error messages by bison */

extern int genread_input(void);
extern void yyerror(const char*);
extern FILE * genread_in;

/* This constant should be adapted to the particular need of the application */

/* set to 10000 by BC - necessary in PIPS for DYNA */
/* Should be a compilation option ? */
/* CA: pb avec COX si a 10000...
   p'tet mauvaise recursion dans le parser de newgen?
*/
#define YYMAXDEPTH 100000

/* User selectable options. */

int warn_on_ref_without_def_in_read_tabulated = false;

/* Where the root will be. */

gen_chunk *Read_chunk ;

/* The SHARED_TABLE 
 * maps a shared pointer number to its gen_chunk pointer value.
 * warning: big hack.
 */
static size_t shared_number;
static size_t shared_size;
static gen_chunk ** shared_table ;

/* The GEN_TABULATED_NAMES hash table maps ids to index in the table of
   the tabulated domains. In case of multiple definition, if the previous
   value is negative, then it came from a REF (by READ_TABULATED) and
   no error is reported. */

/* Management of forward references in read */

int newgen_allow_forward_ref = false;

static void * read_external(int);
static gen_chunk * make_def(gen_chunk *);
static gen_chunk * make_ref(int, gen_chunk *);
static gen_chunk * chunk_for_domain(int);

static stack current_chunk;
static stack current_chunk_index;
static stack current_chunk_size;


/* Line 336 of yacc.c  */
#line 161 "y.tab.c"

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
#ifndef GENREAD_Y_TAB_H
# define GENREAD_Y_TAB_H
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int genread_debug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     CHUNK_BEGIN = 258,
     VECTOR_BEGIN = 259,
     ARROW_BEGIN = 260,
     READ_BOOL = 261,
     TABULATED_BEGIN = 262,
     LP = 263,
     RP = 264,
     LC = 265,
     RC = 266,
     LB = 267,
     SHARED_POINTER = 268,
     READ_EXTERNAL = 269,
     READ_DEF = 270,
     READ_REF = 271,
     READ_NULL = 272,
     READ_LIST_UNDEFINED = 273,
     READ_SET_UNDEFINED = 274,
     READ_ARRAY_UNDEFINED = 275,
     READ_STRING = 276,
     READ_UNIT = 277,
     READ_CHAR = 278,
     READ_INT = 279,
     READ_FLOAT = 280
   };
#endif
/* Tokens.  */
#define CHUNK_BEGIN 258
#define VECTOR_BEGIN 259
#define ARROW_BEGIN 260
#define READ_BOOL 261
#define TABULATED_BEGIN 262
#define LP 263
#define RP 264
#define LC 265
#define RC 266
#define LB 267
#define SHARED_POINTER 268
#define READ_EXTERNAL 269
#define READ_DEF 270
#define READ_REF 271
#define READ_NULL 272
#define READ_LIST_UNDEFINED 273
#define READ_SET_UNDEFINED 274
#define READ_ARRAY_UNDEFINED 275
#define READ_STRING 276
#define READ_UNIT 277
#define READ_CHAR 278
#define READ_INT 279
#define READ_FLOAT 280



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 350 of yacc.c  */
#line 108 "read.y"

  gen_chunk chunk ;
  gen_chunk *chunkp ;
  cons *consp ;
  intptr_t val ;
  char * s;
  double d;
  char c;


/* Line 350 of yacc.c  */
#line 265 "y.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE genread_lval;

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int genread_parse (void *YYPARSE_PARAM);
#else
int genread_parse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int genread_parse (void);
#else
int genread_parse ();
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !GENREAD_Y_TAB_H  */

/* Copy the second part of user declarations.  */

/* Line 353 of yacc.c  */
#line 293 "y.tab.c"

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
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   179

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  26
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  16
/* YYNRULES -- Number of rules.  */
#define YYNRULES  40
/* YYNRULES -- Number of states.  */
#define YYNSTATES  63

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   280

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
      25
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     6,     8,    10,    15,    16,    23,    26,
      27,    29,    32,    33,    36,    37,    40,    41,    45,    46,
      48,    50,    54,    56,    61,    63,    68,    72,    74,    77,
      79,    82,    84,    86,    88,    90,    93,    96,   100,   102,
     104
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      27,     0,    -1,    28,    29,    -1,    40,    -1,    30,    -1,
       7,    33,    35,     9,    -1,    -1,    32,     3,    33,    31,
      36,     9,    -1,    12,    40,    -1,    -1,    40,    -1,    34,
      38,    -1,    -1,    35,    38,    -1,    -1,    36,    38,    -1,
      -1,    37,    40,    38,    -1,    -1,    39,    -1,    18,    -1,
       8,    34,     9,    -1,    19,    -1,    10,    40,    34,    11,
      -1,    20,    -1,     4,    40,    37,     9,    -1,     5,    34,
       9,    -1,    30,    -1,    13,    40,    -1,    22,    -1,     6,
      40,    -1,    23,    -1,    40,    -1,    25,    -1,    41,    -1,
      14,    40,    -1,    15,    30,    -1,    16,    33,    41,    -1,
      17,    -1,    24,    -1,    21,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   130,   130,   149,   164,   168,   177,   176,   211,   212,
     215,   223,   224,   229,   230,   234,   249,   252,   255,   258,
     259,   260,   261,   262,   276,   277,   301,   316,   317,   325,
     326,   327,   328,   329,   330,   331,   332,   333,   334,   337,
     340
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "CHUNK_BEGIN", "VECTOR_BEGIN",
  "ARROW_BEGIN", "READ_BOOL", "TABULATED_BEGIN", "LP", "RP", "LC", "RC",
  "LB", "SHARED_POINTER", "READ_EXTERNAL", "READ_DEF", "READ_REF",
  "READ_NULL", "READ_LIST_UNDEFINED", "READ_SET_UNDEFINED",
  "READ_ARRAY_UNDEFINED", "READ_STRING", "READ_UNIT", "READ_CHAR",
  "READ_INT", "READ_FLOAT", "$accept", "Read", "Nb_of_shared_pointers",
  "Contents", "Chunk", "$@1", "Shared_chunk", "Type", "Datas", "Datas2",
  "Datas3", "Sparse_Datas", "Data", "Basis", "Int", "String", YY_NULL
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    26,    27,    28,    29,    29,    31,    30,    32,    32,
      33,    34,    34,    35,    35,    36,    36,    37,    37,    38,
      38,    38,    38,    38,    38,    38,    38,    38,    38,    39,
      39,    39,    39,    39,    39,    39,    39,    39,    39,    40,
      41
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     1,     1,     4,     0,     6,     2,     0,
       1,     2,     0,     2,     0,     2,     0,     3,     0,     1,
       1,     3,     1,     4,     1,     4,     3,     1,     2,     1,
       2,     1,     1,     1,     1,     2,     2,     3,     1,     1,
       1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    39,     0,     9,     3,     1,     0,     0,     2,     4,
       0,    14,    10,     8,     0,     9,     6,     0,    12,     0,
      12,     5,     0,     0,     0,     9,     0,    38,    20,    22,
      24,    40,    29,    31,    33,    27,    13,    19,    32,    34,
      16,    18,     9,    30,     9,    12,    28,    35,    36,     0,
       9,     0,    26,    11,    21,     9,    37,     7,    15,    25,
       9,    23,    17
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     2,     3,     8,    35,    40,    10,    11,    42,    15,
      50,    51,    53,    37,    38,    39
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -35
static const yytype_int16 yypact[] =
{
     -15,   -35,    11,    -2,   -35,   -35,   -15,   -15,   -35,   -35,
       9,   -35,   -35,   -35,   -15,    44,   -35,   -15,   -35,   -15,
     -35,   -35,   -15,   -15,   -15,     1,   -15,   -35,   -35,   -35,
     -35,   -35,   -35,   -35,   -35,   -35,   -35,   -35,   -35,   -35,
     -35,   -35,    66,   -35,    88,   -35,   -35,   -35,   -35,    -1,
     110,    -6,   -35,   -35,   -35,   132,   -35,   -35,   -35,   -35,
     154,   -35,   -35
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -35,   -35,   -35,   -35,     5,   -35,   -35,   -10,   -18,   -35,
     -35,   -35,   -14,   -35,     0,   -34
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
       4,    36,    44,    59,    16,     6,    12,    13,     9,     1,
       7,     5,    14,     7,    12,    56,    49,    41,     1,    43,
      31,     0,    45,    46,    47,     0,    12,    55,     0,     0,
      48,     0,     0,     0,     0,     0,    58,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    62,     0,    17,    18,
      19,    60,    20,    21,    22,     0,     7,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,     1,    34,
      17,    18,    19,     0,    20,    52,    22,     0,     7,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
       1,    34,    17,    18,    19,     0,    20,    54,    22,     0,
       7,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,     1,    34,    17,    18,    19,     0,    20,    57,
      22,     0,     7,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,     1,    34,    17,    18,    19,     0,
      20,     0,    22,    61,     7,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,     1,    34,    17,    18,
      19,     0,    20,     0,    22,     0,     7,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,     1,    34
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-35))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int8 yycheck[] =
{
       0,    15,    20,     9,    14,     7,     6,     7,     3,    24,
      12,     0,     3,    12,    14,    49,    26,    17,    24,    19,
      21,    -1,    22,    23,    24,    -1,    26,    45,    -1,    -1,
      25,    -1,    -1,    -1,    -1,    -1,    50,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    60,    -1,     4,     5,
       6,    51,     8,     9,    10,    -1,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
       4,     5,     6,    -1,     8,     9,    10,    -1,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,     4,     5,     6,    -1,     8,     9,    10,    -1,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,     4,     5,     6,    -1,     8,     9,
      10,    -1,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,     4,     5,     6,    -1,
       8,    -1,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,     4,     5,
       6,    -1,     8,    -1,    10,    -1,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    24,    27,    28,    40,     0,     7,    12,    29,    30,
      32,    33,    40,    40,     3,    35,    33,     4,     5,     6,
       8,     9,    10,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    25,    30,    38,    39,    40,    41,
      31,    40,    34,    40,    34,    40,    40,    40,    30,    33,
      36,    37,     9,    38,     9,    34,    41,     9,    38,     9,
      40,    11,    38
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
        case 2:
/* Line 1787 of yacc.c  */
#line 131 "read.y"
    { 
	    Read_chunk = (yyvsp[(2) - (2)].chunkp);

	    free(shared_table);

	    message_assert("stacks are emty",
			   stack_size(current_chunk)==0 &&
			   stack_size(current_chunk_index)==0 &&
			   stack_size(current_chunk_size)==0);

	    stack_free(&current_chunk);
	    stack_free(&current_chunk_index);
	    stack_free(&current_chunk_size);
	    YYACCEPT;
	  }
    break;

  case 3:
/* Line 1787 of yacc.c  */
#line 150 "read.y"
    { 
	  size_t i;
	  shared_number = 0;
	  shared_size = (yyvsp[(1) - (1)].val);
	  shared_table = (gen_chunk **)alloc((yyvsp[(1) - (1)].val)*sizeof(gen_chunk*)); 
	  for (i=0; i<shared_size; i++)
	    shared_table[i] = gen_chunk_undefined;

	  current_chunk = stack_make(0, 0, 0);
	  current_chunk_index = stack_make(0, 0, 0);
	  current_chunk_size = stack_make(0, 0, 0);
        }
    break;

  case 4:
/* Line 1787 of yacc.c  */
#line 165 "read.y"
    { 
	  (yyval.chunkp) = (yyvsp[(1) - (1)].chunkp); 
	}
    break;

  case 5:
/* Line 1787 of yacc.c  */
#line 169 "read.y"
    { 
	   (yyval.chunkp) = (gen_chunk*) alloc(sizeof(gen_chunk));
	   (yyval.chunkp)->i = (yyvsp[(2) - (4)].val);
        }
    break;

  case 6:
/* Line 1787 of yacc.c  */
#line 177 "read.y"
    {
    gen_chunk * x = chunk_for_domain((yyvsp[(3) - (3)].val));
    stack_push((void*)(Domains[(yyvsp[(3) - (3)].val)].size), current_chunk_size);

    if ((yyvsp[(1) - (3)].val))
    {
      shared_table[(yyvsp[(1) - (3)].val)-1] = x;
      stack_push(x, current_chunk);
    }
    else
    {
      stack_push(x, current_chunk);
    }
    x->i = (yyvsp[(3) - (3)].val);
    if (Domains[(yyvsp[(3) - (3)].val)].tabulated)
    {
      (x+1)->i = 0; /* tabulated number */
      stack_push((void*)2, current_chunk_index);
    }
    else
    {
      stack_push((void*)1, current_chunk_index);
    }
  }
    break;

  case 7:
/* Line 1787 of yacc.c  */
#line 202 "read.y"
    {
    (yyval.chunkp) = stack_pop(current_chunk);
    void *ci = stack_pop(current_chunk_index),
      *cs = stack_pop(current_chunk_size);
    message_assert("all data copied", ci == cs );
  }
    break;

  case 8:
/* Line 1787 of yacc.c  */
#line 211 "read.y"
    { (yyval.val) = (yyvsp[(2) - (2)].val); }
    break;

  case 9:
/* Line 1787 of yacc.c  */
#line 212 "read.y"
    { (yyval.val) = 0; }
    break;

  case 10:
/* Line 1787 of yacc.c  */
#line 216 "read.y"
    {
    (yyval.val) = gen_type_translation_old_to_actual((yyvsp[(1) - (1)].val));
  }
    break;

  case 11:
/* Line 1787 of yacc.c  */
#line 223 "read.y"
    { (yyval.consp) = CONS( CHUNK, (yyvsp[(2) - (2)].chunk).p, (yyvsp[(1) - (2)].consp) ); }
    break;

  case 12:
/* Line 1787 of yacc.c  */
#line 224 "read.y"
    { (yyval.consp) = NIL; }
    break;

  case 13:
/* Line 1787 of yacc.c  */
#line 229 "read.y"
    { }
    break;

  case 14:
/* Line 1787 of yacc.c  */
#line 230 "read.y"
    { }
    break;

  case 15:
/* Line 1787 of yacc.c  */
#line 235 "read.y"
    {
    size_t i = (size_t) stack_pop(current_chunk_index);
    size_t size = (size_t) stack_head(current_chunk_size);
    gen_chunk * current = stack_head(current_chunk);
    if (i >= size) {
      char * s;
      int n = asprintf(
        &s, "wrong index: %d not in [0,%d)", (int) i, (int) size);
      message_assert("asprintf ok", n >= 0);
      yyerror(s);
    }
    *(current+i) = (yyvsp[(2) - (2)].chunk);
    stack_push((void *)(i+1), current_chunk_index);
  }
    break;

  case 16:
/* Line 1787 of yacc.c  */
#line 249 "read.y"
    { }
    break;

  case 17:
/* Line 1787 of yacc.c  */
#line 252 "read.y"
    { /* index, value */
	        (yyval.consp) = CONS(CONSP, CONS(INT, (yyvsp[(2) - (3)].val), CONS(CHUNK, (yyvsp[(3) - (3)].chunk).p, NIL)), (yyvsp[(1) - (3)].consp));
        }
    break;

  case 18:
/* Line 1787 of yacc.c  */
#line 255 "read.y"
    { (yyval.consp) = NIL; }
    break;

  case 19:
/* Line 1787 of yacc.c  */
#line 258 "read.y"
    { (yyval.chunk) = (yyvsp[(1) - (1)].chunk); }
    break;

  case 20:
/* Line 1787 of yacc.c  */
#line 259 "read.y"
    { (yyval.chunk).l = list_undefined; }
    break;

  case 21:
/* Line 1787 of yacc.c  */
#line 260 "read.y"
    {	(yyval.chunk).l = gen_nreverse((yyvsp[(2) - (3)].consp)); }
    break;

  case 22:
/* Line 1787 of yacc.c  */
#line 261 "read.y"
    { (yyval.chunk).t = set_undefined; }
    break;

  case 23:
/* Line 1787 of yacc.c  */
#line 263 "read.y"
    {
	  (yyval.chunk).t = set_make( (yyvsp[(2) - (4)].val) ) ;
	  MAPL( cp, {
	    switch( (yyvsp[(2) - (4)].val) ) {
	    case set_int:
	      set_add_element( (yyval.chunk).t, (yyval.chunk).t, (char *)cp->car.i ) ;
	      break ;
	    default:
	      set_add_element( (yyval.chunk).t, (yyval.chunk).t, cp->car.s ) ;
	      break ;
	    }}, (yyvsp[(3) - (4)].consp) ) ;
	  gen_free_list( (yyvsp[(3) - (4)].consp) ) ;
	}
    break;

  case 24:
/* Line 1787 of yacc.c  */
#line 276 "read.y"
    { (yyval.chunk).p = array_undefined ; }
    break;

  case 25:
/* Line 1787 of yacc.c  */
#line 278 "read.y"
    {
	  gen_chunk *kp ;
	  cons *cp ;
	  int i ;
	  
	  kp = (gen_chunk *)alloc( (yyvsp[(2) - (4)].val)*sizeof( gen_chunk )) ;
	  
	  for( i=0 ; i != (yyvsp[(2) - (4)].val) ; i++ ) {
	    kp[ i ].p = gen_chunk_undefined ;
	  }
	  for( cp=(yyvsp[(3) - (4)].consp) ; cp!=NULL ; cp=cp->cdr ) {
	    cons *pair = CONSP( CAR( cp )) ;
	    int index = INT(CAR(pair));
	    gen_chunk val = CAR(CDR(pair));
	    assert(index>=0 && index<(yyvsp[(2) - (4)].val));
	    kp[index] = val;

	    gen_free_list(pair); /* free */
	  }

	  gen_free_list((yyvsp[(3) - (4)].consp));
	  (yyval.chunk).p = kp ;
	}
    break;

  case 26:
/* Line 1787 of yacc.c  */
#line 301 "read.y"
    {
		hash_table h = hash_table_make( hash_chunk, 0 )	;
		cons *cp ;

		for( cp = gen_nreverse((yyvsp[(2) - (3)].consp)) ; cp != NULL ; cp=cp->cdr->cdr ) {
			gen_chunk *k = (gen_chunk *)alloc(sizeof(gen_chunk));
			gen_chunk *v = (gen_chunk *)alloc(sizeof(gen_chunk));
	
			*k = CAR(  cp ) ;
			*v = CAR( CDR( cp )) ;
			hash_put( h, (char *)k, (char *)v ) ;
		}
		gen_free_list( (yyvsp[(2) - (3)].consp) ) ;
		(yyval.chunk).h = h ;
		}
    break;

  case 27:
/* Line 1787 of yacc.c  */
#line 316 "read.y"
    { (yyval.chunk).p = (yyvsp[(1) - (1)].chunkp) ; }
    break;

  case 28:
/* Line 1787 of yacc.c  */
#line 318 "read.y"
    {
	  message_assert("shared is defined", 
			 shared_table[(yyvsp[(2) - (2)].val)-1]!=gen_chunk_undefined);
	  (yyval.chunk).p = shared_table[(yyvsp[(2) - (2)].val)-1];
	}
    break;

  case 29:
/* Line 1787 of yacc.c  */
#line 325 "read.y"
    { (yyval.chunk).u = 1; }
    break;

  case 30:
/* Line 1787 of yacc.c  */
#line 326 "read.y"
    { (yyval.chunk).b = (yyvsp[(2) - (2)].val); }
    break;

  case 31:
/* Line 1787 of yacc.c  */
#line 327 "read.y"
    { (yyval.chunk).c = (yyvsp[(1) - (1)].c); }
    break;

  case 32:
/* Line 1787 of yacc.c  */
#line 328 "read.y"
    { (yyval.chunk).i = (yyvsp[(1) - (1)].val); }
    break;

  case 33:
/* Line 1787 of yacc.c  */
#line 329 "read.y"
    { (yyval.chunk).f = (yyvsp[(1) - (1)].d); }
    break;

  case 34:
/* Line 1787 of yacc.c  */
#line 330 "read.y"
    { (yyval.chunk) = *(yyvsp[(1) - (1)].chunkp) ; }
    break;

  case 35:
/* Line 1787 of yacc.c  */
#line 331 "read.y"
    { (yyval.chunk).s = (char*) read_external((yyvsp[(2) - (2)].val)); }
    break;

  case 36:
/* Line 1787 of yacc.c  */
#line 332 "read.y"
    { (yyval.chunk).p = make_def((yyvsp[(2) - (2)].chunkp)); }
    break;

  case 37:
/* Line 1787 of yacc.c  */
#line 333 "read.y"
    { (yyval.chunk).p = make_ref((yyvsp[(2) - (3)].val), (yyvsp[(3) - (3)].chunkp)); }
    break;

  case 38:
/* Line 1787 of yacc.c  */
#line 334 "read.y"
    { (yyval.chunk).p = gen_chunk_undefined ; }
    break;

  case 39:
/* Line 1787 of yacc.c  */
#line 337 "read.y"
    { (yyval.val) = (yyvsp[(1) - (1)].val); }
    break;

  case 40:
/* Line 1787 of yacc.c  */
#line 340 "read.y"
    {
		gen_chunk *obj = (gen_chunk *)alloc(sizeof(gen_chunk));
		obj->s = (yyvsp[(1) - (1)].s);
		(yyval.chunkp) = obj;
	    }
    break;


/* Line 1787 of yacc.c  */
#line 1947 "y.tab.c"
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
#line 346 "read.y"


static gen_chunk * chunk_for_domain(int domain)
{
  gen_chunk * cp;
  check_domain(domain);
  cp = (gen_chunk*) alloc(sizeof(gen_chunk)*Domains[domain].size);
  cp->i = domain;
  return cp;
}

/* YYERROR manages a syntax error while reading an object. */

void yyerror(const char * s)
{
  int c, n=40;
  newgen_lexer_position(stderr);
  fprintf(stderr, "%s before ", s);

  while (n-->0  && ((c=genread_input()) != EOF))
    putc(c, stderr);

  fprintf(stderr, "\n\n");

  fatal("Incorrect object written by GEN_WRITE\n", (char *) NULL);
}

/* READ_EXTERNAL reads external types on stdin */

static void * read_external(int which)
{
  struct gen_binding *bp;
  union domain *dp;
  extern int genread_input();

  which = gen_type_translation_old_to_actual(which);
  message_assert("consistent domain number", which>=0 && which<MAX_DOMAIN);

  bp = &Domains[ which ] ;
  dp = bp->domain ;

  if( dp->ba.type != EXTERNAL_DT ) {
    fatal( "gen_read: undefined external %s\n", bp->name ) ;
    /*NOTREACHED*/
  }
  if( dp->ex.read == NULL ) {
    user( "gen_read: uninitialized external %s\n", bp->name ) ;
    return( NULL ) ;
  }
  if( genread_input() != ' ' ) {
    fatal( "read_external: white space expected\n", (char *)NULL ) ;
    /*NOTREACHED*/
  }
  /*
    Attention, ce qui suit est absolument horrible. Les fonctions
    suceptibles d'etre  appelees a cet endroit sont:
    - soit des fonctions 'user-written' pour les domaines externes
    non geres par NewGen
    - soit la fonctions gen_read pour les domaines externes geres
    par NewGen

    Dans le 1er cas, il faut passer la fonction de lecture d'un caractere
    (yyinput) a la fonction de lecture du domaine externe (on ne peut pas
    passer le pointeur de fichier car lex bufferise les caracteres en
    entree). Dans le second cas, il faut passer le pointeur de fichier a
    cause de yacc/lex.

    Je decide donc de passer les deux parametres: pointeur de fichier et
    pointeur de fonction de lecture. Dans chaque cas, l'un ou l'autre sera
    ignore.
  */
  return (*(dp->ex.read))(genread_in, genread_input);
}

/* MAKE_DEF defines the object CHUNK of name STRING to be in the tabulation
   table INT. domain translation is handled before in Chunk.
 */
static gen_chunk * make_def(gen_chunk * gc)
{
  int domain = gc->i;
  string id = (gc+2)->s;
  return gen_enter_tabulated(domain, id, gc, newgen_allow_forward_ref);
}

/* MAKE_REF references the object of hash name STRING in the tabulation table
   INT. Forward references are dealt with here.
 */
static gen_chunk * make_ref(int domain, gen_chunk * st)
{
  gen_chunk * cp = gen_find_tabulated(st->s, domain);

  if (gen_chunk_undefined_p(cp))
  {
    if (newgen_allow_forward_ref)
    {
      cp = (gen_chunk*) alloc(sizeof(gen_chunk)*Domains[domain].size);
      cp->i = domain;
      (cp+1)->i = 0; /* no number yet */
      (cp+2)->s = st->s; /* TAKEN! */
      cp = gen_do_enter_tabulated(domain, st->s, cp, true);
    }
    else
    {
      user("make_ref: forward references to %s prohibited\n", st->s) ;
    }
  }
  else
  {
    free(st->s);
  }

  free(st);
  return cp;
}

