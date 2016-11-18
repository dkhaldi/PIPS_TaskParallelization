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
#define yyparse         tp_parse
#define yylex           tp_lex
#define yyerror         tp_error
#define yylval          tp_lval
#define yychar          tp_char
#define yydebug         tp_debug
#define yynerrs         tp_nerrs

/* Copy the first part of user declarations.  */
/* Line 336 of yacc.c  */
#line 72 "tp_yacc.y"

#ifdef HAVE_CONFIG_H
	#include "pips_config.h"
#endif
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/param.h>
#include <unistd.h>

#include "linear.h"
#include "genC.h"

#include "ri.h"
#include "database.h"

#include "misc.h"

#include "ri-util.h" /* ri needed for statement_mapping in pipsdbm... */
#include "pipsdbm.h"
#include "resources.h"
#include "phases.h"
#include "properties.h"
#include "pipsmake.h"

#include "top-level.h"
#include "tpips.h"

/********************************************************** static variables */

extern const char *soft_revisions, *soft_date, *cc_version;

extern bool tpips_execution_mode;
extern bool consistency_enforced_p;
static bool processing_started_p=false;

#define YYERROR_VERBOSE 1 /* MUCH better error messages with bison */

extern void tpips_set_line_to_parse(string);
extern void tpips_lex_print_pos(FILE *);
extern int yylex(void);
extern void yyerror(const char *);

static void free_owner_content(res_or_rule * pr)
{
	gen_array_full_free(pr->the_owners), pr->the_owners = NULL;
	free(pr->the_name), pr->the_name = NULL;
}

static void set_env_log_and_free(string var, string val)
{
	string ival = getenv(var);
	if (!ival || !same_string_p(val, ival)) {
		putenv(strdup(concatenate(var, "=", val, NULL)));
  }
	user_log("setenv %s \"%s\"\n", var, val);
	free(var); free(val);
}

/* forward.
 */
static bool perform(bool (*)(const char*, const char*), res_or_rule *);

static void try_to_parse_everything_just_in_case(void)
{
	gen_array_t modules = db_get_module_list();
	res_or_rule r;
	r.the_owners = modules;
	r.the_name = strdup(DBR_CALLEES);
	perform(safe_make, &r);
  // r contents freed at the end of perform
}

/* try hard to open a module.
 */
static bool tp_set_current_module(const char* name)
{
	if (lazy_open_module(name))
    return true;

  // This is courageous, but makes debugging harder...
  try_to_parse_everything_just_in_case();
  if (lazy_open_module(name))
    return true;

  if (!safe_make(DBR_CODE, name))
    return false;

  if (lazy_open_module(name))
    return true;

  pips_user_error("Cannot open, module not found: %s", name);
  return false;
}

/* display a resource using $PAGER if defined and stdout on a tty.
 */
static bool display_a_resource(const char* rname, const char* mname)
{
	string fname;
	bool ret;

	if (!tp_set_current_module(mname))
	{
		pips_user_error("could not find module %s to display\n", mname);
	}

	fname = build_view_file(rname);

	if (!fname)
	{
		pips_user_error("Cannot build view file %s\n", rname);
		free(fname);
		return false;
	}

	if (jpips_is_running)
	{
		/* Should tell about what it is?
		 * What about special formats, such as graphs and all?
		 */
		jpips_tag2("show", fname);
		ret = true;
	}
	else
	{
		ret = safe_display(fname);
	}

	free(fname);
	return ret;
}

static bool remove_a_resource(const char* rname, const char* mname)
{
	if (db_resource_p(rname, mname))
		db_delete_resource(rname, mname);
	else
		pips_user_warning("no resource %s[%s] to delete.\n", rname, mname);
	return true;
}

/* tell pipsdbm that the resource is up to date.
 * may be useful if some transformations are applied
 * which do not change the results of some analyses.
 * under the responsability of the user, obviously...
 */
static bool touch_a_resource(const char* rname, const char* mname)
{
	if (db_resource_p(rname, mname))
		db_touch_resource(rname, mname);
	else
		pips_user_warning("no resource %s[%s] to delete.\n", rname, mname);
	return true;
}

static bool just_show(const char* rname, const char* mname)
{
	string file;

	if (!db_resource_p(rname, mname)) {
		pips_user_warning("no resource %s[%s].\n", rname, mname);
		return false;
	}

	if (!displayable_file_p(rname)) {
		pips_user_warning("resource %s cannot be displayed.\n", rname);
		return false;
	}

	/* now returns the name of the file.
	 */
	file = db_get_memory_resource(rname, mname, true);
	fprintf(stdout, "resource %s[%s] is file %s\n", rname, mname, file);

	return true;
}

/* perform "what" to all resources in "res". res is freed.
 * Several rules call it: display, apply...
 */
static bool perform(bool (*what)(const char*, const char*), res_or_rule * res)
{
	bool result = true;

	if (tpips_execution_mode)
	{
		string save_current_module_name;

		if (!db_get_current_workspace_name())
			pips_user_error("Open or create a workspace first!");

		// This may be always trapped earlier in the parser by rule "owner".
    if (gen_array_nitems(res->the_owners)==0) {
      pips_user_error("Empty action for %s: no argument!", res->the_name);
      free_owner_content(res);
    }

		// push the current module.
    string current = db_get_current_module_name();
		save_current_module_name = current? strdup(current): NULL;
    current = NULL;

		GEN_ARRAY_FOREACH(string, mod_name, res->the_owners)
    {
      if (mod_name != NULL)
      {
        if (!what(res->the_name, mod_name)) {
          result = false;
          break;
        }
      }
      else
        pips_user_warning("Select a module first!\n");
    }

		// restore the initial current module, if there was one
		if (save_current_module_name!=NULL)
    {
			if (db_get_current_module_name())
				db_reset_current_module_name();
			db_set_current_module_name(save_current_module_name);
			free(save_current_module_name);
		}
	}

	free_owner_content(res);
	return result;
}

static void tp_system(const char* s)
{
	int status;
	user_log("shell%s%s\n", (s[0]==' '|| s[0]=='\t')? "": " ", s);
	status = system(s);
	fflush(stdout);

	if (status)
	{
		pips_user_warning("shell returned status (%d.%d)\n",
											status/256, status%256);

	/* generate user error if not interactive,
	 * so as to abort quickly in scripts...
	 */
		if (!tpips_is_interactive)
			pips_user_error("shell error (%d) in tpips script\n", status);
	}
}

static bool tp_close_the_workspace(const char* s)
{
	bool result = true;

	pips_debug(7, "reduce rule i_close\n");

	if (tpips_execution_mode)
	{
		string current = db_get_current_workspace_name();

		if (current!=NULL && s!=NULL)
		{
			if (same_string_p(s, current))
			{
				close_workspace(false);
				result = true;
			}
			else
			{
				pips_user_error("must close the current workspace!\n");
				result = false;
			}
		}
		else {
			pips_user_error("No workspace to close. Open or create one!\n");
			result = false;
		}
		result = true;
	}

	return result;
}

static void tp_some_info(const char* about)
{
	if (same_string_p(about, "workspace"))
	{
		string ws = db_get_current_workspace_name();
		fprintf(stdout, "%s\n", ws? ws: "");
		if (jpips_is_running) jpips_tag2("workspace", ws? ws: "<none>");
	}
	else if (same_string_p(about, "module"))
	{
		string m = db_get_current_module_name();
		fprintf(stdout, "%s\n", m? m: "");
		if (jpips_is_running) jpips_tag2("module", m? m: "<none>");
	}
	else if (same_string_p(about, "modules") &&
					 db_get_current_workspace_name())
	{
		gen_array_t modules = db_get_module_list();
		int n = gen_array_nitems(modules), i;

		if (jpips_is_running)
		{
			jpips_begin_tag("modules");
			jpips_add_tag("");
		}

		for(i=0; i<n; i++)
		{
			string m = gen_array_item(modules, i);
			if (jpips_is_running) jpips_add_tag(m);
			else fprintf(stdout, "%s ", m);

		}
		if (jpips_is_running) jpips_end_tag();

		gen_array_full_free(modules);
	}
	else if (same_string_p(about, "directory"))
	{
	char pathname[MAXPATHLEN];
	fprintf(stdout, "%s\n", (char*) getcwd(pathname, MAXPATHLEN));
	if (jpips_is_running)
		jpips_tag2("directory", (char*) getcwd(pathname, MAXPATHLEN));
	}

	fprintf(stdout, "\n");
}

/* Returns a newgen array with the main inside. If no main is found,
 * try to build all callees to parse all sources and maybe find it.
 *
 * FI: since the preprocessor has already analyzed all source code and
 * detect main functions, what do you expect by parsing its result?
 */
static gen_array_t get_main(void)
{
	gen_array_t result = gen_array_make(0), modules;
	int number_of_main = 0;
	int n = 0;
	string main_name = get_first_main_module();

	if (!string_undefined_p(main_name))
	{
		gen_array_append(result, main_name);
		return result;
	}

	/* else try something else just in case...
   * well, it looks rather useless, maybe.
   */
	while (number_of_main==0 && n<2)
	{
		n++;
		modules = db_get_module_list();

		if (n==2)
		{
			pips_user_warning("no main directly found, parsing...\n");
			try_to_parse_everything_just_in_case();
		}

		GEN_ARRAY_FOREACH(string, on, modules)
    {
      entity mod = local_name_to_top_level_entity(on);

      if (!entity_undefined_p(mod) && entity_main_module_p(mod))
      {
        if (number_of_main)
          pips_user_error("More than one main\n");
        number_of_main++;
        gen_array_dupappend(result, on);
      }
    }
		gen_array_full_free(modules);
	}

	return result;
}

static void process_file_list(const gen_array_t a)
{
  int n = gen_array_nitems(a);
  volatile int i = 0;
  bool saved_tpips_is_interactive = tpips_is_interactive;
  tpips_is_interactive = false;
  CATCH(user_exception_error)
  {
    // cleanup
    gen_array_full_free(a);
    tpips_set_line_to_parse(""); // humm...
    tpips_is_interactive = saved_tpips_is_interactive;
    RETHROW();
  }
  TRY
  {
    for(; i<n; i++)
    {
      string name = gen_array_item(a, i);
      FILE * sourced = fopen(name, "r");
      if (!sourced) {
        perror("while sourcing");
        /* just in case, maybe tpips_init is not yet performed. */
        if (tpips_init_done)
          /* this performs a throw... */
          pips_user_error("cannot source file '%s'\n", name);
        else
        {
          fprintf(stderr, "cannot source file '%s'\n", name);
          break;
        }
      }
      else
      {
        tpips_process_a_file(sourced, name, false);
        fclose(sourced);
      }
    }
    tpips_set_line_to_parse(""); /* humm... */
    tpips_is_interactive = saved_tpips_is_interactive;
    UNCATCH(user_exception_error);
  }
}


/* Line 336 of yacc.c  */
#line 503 "y.tab.c"

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
#ifndef TP_Y_TAB_H
# define TP_Y_TAB_H
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int tp_debug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     TK_OPEN = 258,
     TK_CREATE = 259,
     TK_CLOSE = 260,
     TK_CHECKPOINT = 261,
     TK_DELETE = 262,
     TK_MODULE = 263,
     TK_MAKE = 264,
     TK_APPLY = 265,
     TK_CAPPLY = 266,
     TK_DISPLAY = 267,
     TK_REMOVE = 268,
     TK_ACTIVATE = 269,
     TK_SET_PROPERTY = 270,
     TK_GET_PROPERTY = 271,
     TK_SET_ENVIRONMENT = 272,
     TK_GET_ENVIRONMENT = 273,
     TK_UNSET_ENVIRONMENT = 274,
     TK_CDIR = 275,
     TK_INFO = 276,
     TK_PWD = 277,
     TK_HELP = 278,
     TK_SHOW = 279,
     TK_SOURCE = 280,
     TK_SHELL = 281,
     TK_ECHO = 282,
     TK_UNKNOWN = 283,
     TK_TIMEOUT = 284,
     TK_QUIT = 285,
     TK_EXIT = 286,
     TK_LINE = 287,
     TK_CHECKACTIVE = 288,
     TK_VERSION = 289,
     TK_TOUCH = 290,
     TK_OWNER_NAME = 291,
     TK_OWNER_ALL = 292,
     TK_OWNER_ALLFUNC = 293,
     TK_OWNER_PROGRAM = 294,
     TK_OWNER_MAIN = 295,
     TK_OWNER_MODULE = 296,
     TK_OWNER_CALLERS = 297,
     TK_OWNER_CALLEES = 298,
     TK_OPENPAREN = 299,
     TK_COMMA = 300,
     TK_CLOSEPAREN = 301,
     TK_EQUAL = 302,
     TK_NAME = 303,
     TK_A_STRING = 304,
     TK_ENDOFLINE = 305,
     TK_INT = 306
   };
#endif
/* Tokens.  */
#define TK_OPEN 258
#define TK_CREATE 259
#define TK_CLOSE 260
#define TK_CHECKPOINT 261
#define TK_DELETE 262
#define TK_MODULE 263
#define TK_MAKE 264
#define TK_APPLY 265
#define TK_CAPPLY 266
#define TK_DISPLAY 267
#define TK_REMOVE 268
#define TK_ACTIVATE 269
#define TK_SET_PROPERTY 270
#define TK_GET_PROPERTY 271
#define TK_SET_ENVIRONMENT 272
#define TK_GET_ENVIRONMENT 273
#define TK_UNSET_ENVIRONMENT 274
#define TK_CDIR 275
#define TK_INFO 276
#define TK_PWD 277
#define TK_HELP 278
#define TK_SHOW 279
#define TK_SOURCE 280
#define TK_SHELL 281
#define TK_ECHO 282
#define TK_UNKNOWN 283
#define TK_TIMEOUT 284
#define TK_QUIT 285
#define TK_EXIT 286
#define TK_LINE 287
#define TK_CHECKACTIVE 288
#define TK_VERSION 289
#define TK_TOUCH 290
#define TK_OWNER_NAME 291
#define TK_OWNER_ALL 292
#define TK_OWNER_ALLFUNC 293
#define TK_OWNER_PROGRAM 294
#define TK_OWNER_MAIN 295
#define TK_OWNER_MODULE 296
#define TK_OWNER_CALLERS 297
#define TK_OWNER_CALLEES 298
#define TK_OPENPAREN 299
#define TK_COMMA 300
#define TK_CLOSEPAREN 301
#define TK_EQUAL 302
#define TK_NAME 303
#define TK_A_STRING 304
#define TK_ENDOFLINE 305
#define TK_INT 306



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 350 of yacc.c  */
#line 500 "tp_yacc.y"

  int status;
  int ival;
  string name;
  res_or_rule rn;
  gen_array_t array;


/* Line 350 of yacc.c  */
#line 657 "y.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE tp_lval;

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int tp_parse (void *YYPARSE_PARAM);
#else
int tp_parse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int tp_parse (void);
#else
int tp_parse ();
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !TP_Y_TAB_H  */

/* Copy the second part of user declarations.  */

/* Line 353 of yacc.c  */
#line 685 "y.tab.c"

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
#define YYFINAL  114
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   177

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  52
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  46
/* YYNRULES -- Number of rules.  */
#define YYNRULES  102
/* YYNRULES -- Number of states.  */
#define YYNSTATES  183

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   306

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
      45,    46,    47,    48,    49,    50,    51
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,    30,    32,    34,    36,    38,
      40,    42,    44,    46,    48,    50,    52,    54,    56,    58,
      60,    62,    64,    66,    68,    70,    72,    74,    76,    79,
      82,    85,    89,    92,    96,    99,   103,   106,   110,   113,
     117,   121,   124,   128,   133,   139,   144,   150,   155,   161,
     166,   172,   176,   180,   183,   187,   189,   194,   197,   201,
     205,   209,   213,   217,   221,   225,   229,   233,   237,   241,
     245,   249,   253,   255,   258,   260,   262,   265,   268,   272,
     276,   280,   284,   288,   292,   296,   300,   301,   303,   306,
     310,   312,   314
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      53,     0,    -1,    53,    54,    -1,    54,    -1,    50,    -1,
      71,    -1,    73,    -1,    74,    -1,    75,    -1,    70,    -1,
      76,    -1,    77,    -1,    78,    -1,    79,    -1,    80,    -1,
      82,    -1,    83,    -1,    84,    -1,    85,    -1,    86,    -1,
      66,    -1,    67,    -1,    68,    -1,    69,    -1,    64,    -1,
      65,    -1,    87,    -1,    63,    -1,    62,    -1,    60,    -1,
      59,    -1,    55,    -1,    57,    -1,    56,    -1,    58,    -1,
      81,    -1,    61,    -1,     1,    -1,    30,    50,    -1,    31,
      50,    -1,    34,    50,    -1,    23,    48,    50,    -1,    23,
      50,    -1,    15,    32,    50,    -1,    26,    50,    -1,    26,
      32,    50,    -1,    28,    50,    -1,    27,    32,    50,    -1,
      27,    50,    -1,    21,    48,    50,    -1,    20,    48,    50,
      -1,    22,    50,    -1,    18,    48,    50,    -1,    17,    48,
      48,    50,    -1,    17,    48,    47,    48,    50,    -1,    17,
      48,    49,    50,    -1,    17,    48,    47,    49,    50,    -1,
      17,    48,    89,    50,    -1,    17,    48,    47,    89,    50,
      -1,    17,    48,    51,    50,    -1,    17,    48,    47,    51,
      50,    -1,    19,    48,    50,    -1,    29,    51,    50,    -1,
       6,    50,    -1,     3,    72,    50,    -1,    48,    -1,     4,
      72,    89,    50,    -1,     5,    50,    -1,     5,    48,    50,
      -1,     7,    72,    50,    -1,     8,    48,    50,    -1,     9,
      91,    50,    -1,    10,    92,    50,    -1,    11,    92,    50,
      -1,    12,    91,    50,    -1,    35,    91,    50,    -1,    24,
      91,    50,    -1,    13,    91,    50,    -1,    14,    88,    50,
      -1,    33,    97,    50,    -1,    16,    95,    50,    -1,    25,
      89,    50,    -1,    96,    -1,    89,    90,    -1,    90,    -1,
      48,    -1,    97,    93,    -1,    96,    93,    -1,    44,    37,
      46,    -1,    44,    38,    46,    -1,    44,    39,    46,    -1,
      44,    40,    46,    -1,    44,    41,    46,    -1,    44,    43,
      46,    -1,    44,    42,    46,    -1,    44,    94,    46,    -1,
      -1,    48,    -1,    94,    48,    -1,    94,    45,    48,    -1,
      48,    -1,    48,    -1,    48,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   510,   510,   511,   514,   515,   516,   517,   518,   519,
     520,   521,   522,   523,   524,   525,   526,   527,   528,   529,
     530,   531,   532,   533,   534,   535,   536,   537,   538,   539,
     540,   541,   542,   543,   544,   545,   546,   547,   550,   558,
     564,   578,   582,   588,   615,   619,   625,   666,   675,   683,
     690,   698,   707,   718,   720,   722,   724,   726,   728,   730,
     732,   736,   740,   744,   756,   789,   797,   877,   881,   888,
     921,   939,   946,   953,   960,   967,   974,   981,   988,  1004,
    1018,  1038,  1045,  1048,  1053,  1060,  1063,  1071,  1079,  1090,
    1101,  1110,  1122,  1131,  1150,  1158,  1161,  1187,  1191,  1193,
    1197,  1205,  1213
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TK_OPEN", "TK_CREATE", "TK_CLOSE",
  "TK_CHECKPOINT", "TK_DELETE", "TK_MODULE", "TK_MAKE", "TK_APPLY",
  "TK_CAPPLY", "TK_DISPLAY", "TK_REMOVE", "TK_ACTIVATE", "TK_SET_PROPERTY",
  "TK_GET_PROPERTY", "TK_SET_ENVIRONMENT", "TK_GET_ENVIRONMENT",
  "TK_UNSET_ENVIRONMENT", "TK_CDIR", "TK_INFO", "TK_PWD", "TK_HELP",
  "TK_SHOW", "TK_SOURCE", "TK_SHELL", "TK_ECHO", "TK_UNKNOWN",
  "TK_TIMEOUT", "TK_QUIT", "TK_EXIT", "TK_LINE", "TK_CHECKACTIVE",
  "TK_VERSION", "TK_TOUCH", "TK_OWNER_NAME", "TK_OWNER_ALL",
  "TK_OWNER_ALLFUNC", "TK_OWNER_PROGRAM", "TK_OWNER_MAIN",
  "TK_OWNER_MODULE", "TK_OWNER_CALLERS", "TK_OWNER_CALLEES",
  "TK_OPENPAREN", "TK_COMMA", "TK_CLOSEPAREN", "TK_EQUAL", "TK_NAME",
  "TK_A_STRING", "TK_ENDOFLINE", "TK_INT", "$accept", "commands",
  "command", "i_quit", "i_exit", "i_version", "i_help", "i_setprop",
  "i_shell", "i_unknown", "i_echo", "i_info", "i_cd", "i_pwd", "i_getenv",
  "i_setenv", "i_unsetenv", "i_timeout", "i_checkpoint", "i_open",
  "workspace_name", "i_create", "i_close", "i_delete", "i_module",
  "i_make", "i_apply", "i_capply", "i_display", "i_touch", "i_show",
  "i_rm", "i_activate", "i_checkactive", "i_get", "i_source", "rulename",
  "filename_list", "filename", "resource_id", "rule_id", "owner",
  "list_of_owner_name", "propname", "phasename", "resourcename", YY_NULL
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
     305,   306
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    52,    53,    53,    54,    54,    54,    54,    54,    54,
      54,    54,    54,    54,    54,    54,    54,    54,    54,    54,
      54,    54,    54,    54,    54,    54,    54,    54,    54,    54,
      54,    54,    54,    54,    54,    54,    54,    54,    55,    56,
      57,    58,    58,    59,    60,    60,    61,    62,    62,    63,
      64,    65,    66,    67,    67,    67,    67,    67,    67,    67,
      67,    68,    69,    70,    71,    72,    73,    74,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    89,    90,    91,    92,    93,    93,
      93,    93,    93,    93,    93,    93,    93,    94,    94,    94,
      95,    96,    97
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     2,
       2,     3,     2,     3,     2,     3,     2,     3,     2,     3,
       3,     2,     3,     4,     5,     4,     5,     4,     5,     4,
       5,     3,     3,     2,     3,     1,     4,     2,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     1,     2,     1,     1,     2,     2,     3,     3,
       3,     3,     3,     3,     3,     3,     0,     1,     2,     3,
       1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    37,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     4,     0,     3,    31,    33,    32,
      34,    30,    29,    36,    28,    27,    24,    25,    20,    21,
      22,    23,     9,     5,     6,     7,     8,    10,    11,    12,
      13,    14,    35,    15,    16,    17,    18,    19,    26,    65,
       0,     0,     0,    67,    63,     0,     0,   102,     0,    96,
     101,     0,    96,     0,     0,     0,     0,    82,     0,   100,
       0,     0,     0,     0,     0,     0,    51,     0,    42,     0,
      85,     0,    84,     0,    44,     0,    48,    46,     0,    38,
      39,     0,    40,     0,     1,     2,    64,     0,    68,    69,
      70,    71,     0,    86,    72,    87,    73,    74,    77,    78,
      43,    80,     0,    85,     0,     0,     0,    52,    61,    50,
      49,    41,    76,    81,    83,    45,    47,    62,    79,    75,
      66,     0,     0,     0,     0,     0,     0,     0,    97,     0,
      85,     0,     0,     0,    53,    55,    59,    57,    88,    89,
      90,    91,    92,    94,    93,     0,    95,    98,    54,    56,
      60,    58,    99
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      70,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    86,   101,   102,    78,
      81,   123,   159,    90,    82,    79
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -102
static const yytype_int16 yypact[] =
{
     112,  -102,   -42,   -42,   -10,   -29,   -42,   -28,   -24,   -19,
     -19,   -24,   -24,   -19,    18,   -15,     4,     5,     6,     7,
       8,     9,    -7,   -24,    10,   -31,   -27,    16,    45,    50,
      51,   -24,    52,   -24,  -102,    64,  -102,  -102,  -102,  -102,
    -102,  -102,  -102,  -102,  -102,  -102,  -102,  -102,  -102,  -102,
    -102,  -102,  -102,  -102,  -102,  -102,  -102,  -102,  -102,  -102,
    -102,  -102,  -102,  -102,  -102,  -102,  -102,  -102,  -102,  -102,
      53,    10,    54,  -102,  -102,    55,    56,  -102,    57,    13,
    -102,    58,    13,    59,    60,    61,    62,  -102,    94,  -102,
      98,   -21,    99,   100,   101,   102,  -102,   103,  -102,   104,
    -102,    -6,  -102,   105,  -102,   106,  -102,  -102,   107,  -102,
    -102,   108,  -102,   109,  -102,  -102,  -102,    -3,  -102,  -102,
    -102,  -102,   -30,  -102,  -102,  -102,  -102,  -102,  -102,  -102,
    -102,  -102,   -17,   110,   111,   113,    -2,  -102,  -102,  -102,
    -102,  -102,  -102,  -102,  -102,  -102,  -102,  -102,  -102,  -102,
    -102,    14,    15,   118,   119,   120,   121,   122,  -102,    -9,
     123,   124,   125,     1,  -102,  -102,  -102,  -102,  -102,  -102,
    -102,  -102,  -102,  -102,  -102,   128,  -102,  -102,  -102,  -102,
    -102,  -102,  -102
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -102,  -102,   134,  -102,  -102,  -102,  -102,  -102,  -102,  -102,
    -102,  -102,  -102,  -102,  -102,  -102,  -102,  -102,  -102,  -102,
      11,  -102,  -102,  -102,  -102,  -102,  -102,  -102,  -102,  -102,
    -102,  -102,  -102,  -102,  -102,  -102,  -102,   -69,  -101,    -8,
     160,    89,  -102,  -102,   159,   146
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
     144,   103,   117,    84,    85,   105,    69,   151,   152,   153,
     154,   155,   156,   157,    71,    99,   144,    75,   158,   104,
      76,    74,   136,   106,    77,   113,   132,   133,   134,    80,
     135,   160,   161,    89,   162,   144,   175,   176,    72,   177,
      73,    97,   100,    98,   143,   100,   100,   150,   167,   100,
      88,   181,    91,    92,    93,    94,    95,   122,   100,    96,
     168,   169,   144,   163,   114,     1,   107,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,   108,    31,    32,    33,
     109,   110,   112,   116,   118,   119,   120,   121,   124,   126,
     127,   128,   129,     1,    34,     2,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,   130,    31,    32,    33,   131,   137,
     138,   139,   140,   141,   142,   145,   146,   147,   148,   149,
     164,   165,    34,   166,   170,   171,   172,   173,   174,   115,
      83,   125,    87,   178,   179,   180,   182,   111
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-102))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_uint8 yycheck[] =
{
     101,    32,    71,    11,    12,    32,    48,    37,    38,    39,
      40,    41,    42,    43,     3,    23,   117,     6,    48,    50,
      48,    50,    91,    50,    48,    33,    47,    48,    49,    48,
      51,    48,    49,    48,    51,   136,    45,    46,    48,    48,
      50,    48,    48,    50,    50,    48,    48,    50,    50,    48,
      32,    50,    48,    48,    48,    48,    48,    44,    48,    50,
      46,    46,   163,   132,     0,     1,    50,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    51,    33,    34,    35,
      50,    50,    50,    50,    50,    50,    50,    50,    50,    50,
      50,    50,    50,     1,    50,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    50,    33,    34,    35,    50,    50,
      50,    50,    50,    50,    50,    50,    50,    50,    50,    50,
      50,    50,    50,    50,    46,    46,    46,    46,    46,    35,
      10,    82,    13,    50,    50,    50,    48,    31
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    33,    34,    35,    50,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    48,
      72,    72,    48,    50,    50,    72,    48,    48,    91,    97,
      48,    92,    96,    92,    91,    91,    88,    96,    32,    48,
      95,    48,    48,    48,    48,    48,    50,    48,    50,    91,
      48,    89,    90,    32,    50,    32,    50,    50,    51,    50,
      50,    97,    50,    91,     0,    54,    50,    89,    50,    50,
      50,    50,    44,    93,    50,    93,    50,    50,    50,    50,
      50,    50,    47,    48,    49,    51,    89,    50,    50,    50,
      50,    50,    50,    50,    90,    50,    50,    50,    50,    50,
      50,    37,    38,    39,    40,    41,    42,    43,    48,    94,
      48,    49,    51,    89,    50,    50,    50,    50,    46,    46,
      46,    46,    46,    46,    46,    45,    46,    48,    50,    50,
      50,    50,    48
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
volatile 
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
yytype_int16 * volatile yyss;
yytype_int16 * volatile yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
YYSTYPE * volatile yyvs;
    YYSTYPE *yyvsp;

volatile YYSIZE_T yystacksize;

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
#line 510 "tp_yacc.y"
    { (yyval.status) = (yyvsp[(1) - (2)].status) && (yyvsp[(2) - (2)].status); }
    break;

  case 4:
/* Line 1787 of yacc.c  */
#line 514 "tp_yacc.y"
    { /* may be empty! */ }
    break;

  case 5:
/* Line 1787 of yacc.c  */
#line 515 "tp_yacc.y"
    { processing_started_p = true; }
    break;

  case 6:
/* Line 1787 of yacc.c  */
#line 516 "tp_yacc.y"
    { processing_started_p = false; }
    break;

  case 7:
/* Line 1787 of yacc.c  */
#line 517 "tp_yacc.y"
    { processing_started_p = false; }
    break;

  case 8:
/* Line 1787 of yacc.c  */
#line 518 "tp_yacc.y"
    { processing_started_p = false; }
    break;

  case 11:
/* Line 1787 of yacc.c  */
#line 521 "tp_yacc.y"
    { processing_started_p = true; }
    break;

  case 12:
/* Line 1787 of yacc.c  */
#line 522 "tp_yacc.y"
    { processing_started_p = true; }
    break;

  case 13:
/* Line 1787 of yacc.c  */
#line 523 "tp_yacc.y"
    { processing_started_p = true; }
    break;

  case 14:
/* Line 1787 of yacc.c  */
#line 524 "tp_yacc.y"
    { processing_started_p = true; }
    break;

  case 37:
/* Line 1787 of yacc.c  */
#line 547 "tp_yacc.y"
    {(yyval.status) = false;}
    break;

  case 38:
/* Line 1787 of yacc.c  */
#line 551 "tp_yacc.y"
    {
		tpips_close();
    pips_stop(info_log, 0, "tpips quit");
	}
    break;

  case 39:
/* Line 1787 of yacc.c  */
#line 559 "tp_yacc.y"
    {
		exit(0); /* rather rough! */
	}
    break;

  case 40:
/* Line 1787 of yacc.c  */
#line 565 "tp_yacc.y"
    {
		fprintf(stdout,
						// "tpips: (%s)\n"
						"ARCH=" STRINGIFY(SOFT_ARCH) "\n"
						"REVS=\n"
						"%s"
						"DATE=%s\n"
						"CC_VERSION=%s\n",
						soft_revisions, soft_date, cc_version);
		fflush(stdout);
	}
    break;

  case 41:
/* Line 1787 of yacc.c  */
#line 579 "tp_yacc.y"
    {
		tpips_help((yyvsp[(2) - (3)].name)); free((yyvsp[(2) - (3)].name));
	}
    break;

  case 42:
/* Line 1787 of yacc.c  */
#line 583 "tp_yacc.y"
    {
		tpips_help("");
	}
    break;

  case 43:
/* Line 1787 of yacc.c  */
#line 589 "tp_yacc.y"
    {
	  consistency_enforced_p = get_bool_property("CONSISTENCY_ENFORCED_P");
	  if(!consistency_enforced_p || !processing_started_p) {
		user_log("setproperty %s\n", (yyvsp[(2) - (3)].name));
		reset_property_error(); // We start again at tpips
					// level and should be able to
					// avoid the fatal loop...
		parse_properties_string((yyvsp[(2) - (3)].name), processing_started_p);
		if(processing_started_p) {
		  pips_user_warning("Properties should not be updated during "
				    "tpips processing."
				    " Move the setproperty statement at the "
				    "beginning of your tpips script.\n");
		}
	  }
	  else {
	    pips_user_error("Properties should not be updated during tpips "
			    "processing."
			    " Move the setproperty statement at the beginning "
			    "of your tpips script.\n");
	  }
		fflush(stdout);
		free((yyvsp[(2) - (3)].name));
	}
    break;

  case 44:
/* Line 1787 of yacc.c  */
#line 616 "tp_yacc.y"
    {
		tp_system("${SHELL:-sh}");
	}
    break;

  case 45:
/* Line 1787 of yacc.c  */
#line 620 "tp_yacc.y"
    {
		tp_system((yyvsp[(2) - (3)].name)); free((yyvsp[(2) - (3)].name));
	}
    break;

  case 46:
/* Line 1787 of yacc.c  */
#line 626 "tp_yacc.y"
    {
		if (tpips_behaves_like_a_shell())
		{
			pips_user_warning("implicit shell command assumed!\n");
			tp_system((yyvsp[(1) - (2)].name));
		}
		else
		{
			tpips_lex_print_pos(stderr);
			if(get_bool_property("ABORT_ON_USER_ERROR") ||
                           get_bool_property("CLOSE_WORKSPACE_AND_QUIT_ON_ERROR")) {
			  // FI: the next call is used to check error management 
			  // pips_internal_error("Just a temporary test\n.");
			  extern string tpips_unknown_string;
				pips_user_error(
					"\n\n"
					"\tUnknown command \"%s\" at line %d in file \"%s\".\n"
					"\tMaybe you intended to execute a direct shell command.\n"
					"\tThis convenient feature is desactivated by default.\n"
					"\tTo enable it, you can run tpips with the -s option,\n"
					"\tor do \"setproperty TPIPS_IS_A_SHELL=TRUE\",\n"
					"\tor do \"setenv TPIPS_IS_A_SHELL=TRUE\".\n"
					"\tOtherwise use ! or \"shell\" as a command prefix.\n\n", tpips_unknown_string, tpips_current_line_number(), tpips_current_file_name());
			}
			else {
			  extern string tpips_unknown_string; // provided by the lexer
				pips_user_warning(
					"\n\n"
					"\tMaybe you intended to execute a direct shell command.\n"
					"\tThis convenient feature is desactivated by default.\n"
					"\tTo enable it, you can run tpips with the -s option,\n"
					"\tor do \"setproperty TPIPS_IS_A_SHELL=TRUE\",\n"
					"\tor do \"setenv TPIPS_IS_A_SHELL=TRUE\".\n"
					"\tOtherwise use ! or \"shell\" as a command prefix.\n\n");
			}
		}
		free((yyvsp[(1) - (2)].name));
	}
    break;

  case 47:
/* Line 1787 of yacc.c  */
#line 667 "tp_yacc.y"
    {
		string s = (yyvsp[(2) - (3)].name);
		user_log("echo %s\n", (yyvsp[(2) - (3)].name));
		skip_blanks(s);
		fprintf(stdout,"%s\n",s);
		fflush(stdout);
		free((yyvsp[(2) - (3)].name));
	}
    break;

  case 48:
/* Line 1787 of yacc.c  */
#line 676 "tp_yacc.y"
    {
		user_log("echo\n");
		fprintf(stdout,"\n");
		fflush(stdout);
	}
    break;

  case 49:
/* Line 1787 of yacc.c  */
#line 684 "tp_yacc.y"
    {
		tp_some_info((yyvsp[(2) - (3)].name));
		free((yyvsp[(2) - (3)].name));
	}
    break;

  case 50:
/* Line 1787 of yacc.c  */
#line 691 "tp_yacc.y"
    {
		user_log("cd %s\n", (yyvsp[(2) - (3)].name));
		if (chdir((yyvsp[(2) - (3)].name))) fprintf(stderr, "error while changing directory\n");
		free((yyvsp[(2) - (3)].name));
	}
    break;

  case 51:
/* Line 1787 of yacc.c  */
#line 699 "tp_yacc.y"
    {
		char pathname[MAXPATHLEN];
		fprintf(stdout, "current working directory: %s\n",
						(char*) getcwd(pathname, MAXPATHLEN));
		fflush(stdout);
	}
    break;

  case 52:
/* Line 1787 of yacc.c  */
#line 708 "tp_yacc.y"
    {
		string val = getenv((yyvsp[(2) - (3)].name));
		user_log("getenv %s\n", (yyvsp[(2) - (3)].name));
		if (val) fprintf(stdout, "%s=%s\n", (yyvsp[(2) - (3)].name), val);
		else fprintf(stdout, "%s is not defined\n", (yyvsp[(2) - (3)].name));
		free((yyvsp[(2) - (3)].name));
	}
    break;

  case 53:
/* Line 1787 of yacc.c  */
#line 719 "tp_yacc.y"
    { set_env_log_and_free((yyvsp[(2) - (4)].name), (yyvsp[(3) - (4)].name));	}
    break;

  case 54:
/* Line 1787 of yacc.c  */
#line 721 "tp_yacc.y"
    { set_env_log_and_free((yyvsp[(2) - (5)].name), (yyvsp[(4) - (5)].name));	}
    break;

  case 55:
/* Line 1787 of yacc.c  */
#line 723 "tp_yacc.y"
    { set_env_log_and_free((yyvsp[(2) - (4)].name), (yyvsp[(3) - (4)].name));	}
    break;

  case 56:
/* Line 1787 of yacc.c  */
#line 725 "tp_yacc.y"
    { set_env_log_and_free((yyvsp[(2) - (5)].name), (yyvsp[(4) - (5)].name));	}
    break;

  case 57:
/* Line 1787 of yacc.c  */
#line 727 "tp_yacc.y"
    { set_env_log_and_free((yyvsp[(2) - (4)].name), strdup(string_array_join((yyvsp[(3) - (4)].array), " ")));	}
    break;

  case 58:
/* Line 1787 of yacc.c  */
#line 729 "tp_yacc.y"
    { set_env_log_and_free((yyvsp[(2) - (5)].name), strdup(string_array_join((yyvsp[(4) - (5)].array), " ")));	}
    break;

  case 59:
/* Line 1787 of yacc.c  */
#line 731 "tp_yacc.y"
    { char * v; asprintf(&v, "%d", (yyvsp[(3) - (4)].ival)); set_env_log_and_free((yyvsp[(2) - (4)].name), v);	}
    break;

  case 60:
/* Line 1787 of yacc.c  */
#line 733 "tp_yacc.y"
    { char * v; asprintf(&v, "%d", (yyvsp[(4) - (5)].ival)); set_env_log_and_free((yyvsp[(2) - (5)].name), v);	}
    break;

  case 61:
/* Line 1787 of yacc.c  */
#line 737 "tp_yacc.y"
    { user_log("unsetenv %s\n", (yyvsp[(2) - (3)].name)); unsetenv((yyvsp[(2) - (3)].name)); }
    break;

  case 62:
/* Line 1787 of yacc.c  */
#line 741 "tp_yacc.y"
    { user_log("timeout %d\n", (yyvsp[(2) - (3)].ival)); set_pips_timeout((yyvsp[(2) - (3)].ival)); }
    break;

  case 63:
/* Line 1787 of yacc.c  */
#line 745 "tp_yacc.y"
    {
		if (tpips_execution_mode)
		{
			if (db_get_current_workspace_name())
				checkpoint_workspace();
			else
				pips_user_error("Cannot checkpoint, no workspace!\n");
		}
	}
    break;

  case 64:
/* Line 1787 of yacc.c  */
#line 757 "tp_yacc.y"
    {
		string main_module_name;

		pips_debug(7,"reduce rule i_open\n");

		if (tpips_execution_mode) {
			if (db_get_current_workspace_name() != NULL) {
				pips_user_warning("Closing workspace %s "
													"before opening %s!\n",
													db_get_current_workspace_name(), (yyvsp[(2) - (3)].name));
				close_workspace(false);
			}
			if (!workspace_exists_p((yyvsp[(2) - (3)].name)))
				pips_user_error("No workspace %s to open!\n", (yyvsp[(2) - (3)].name));

			if (( (yyval.status) = open_workspace ((yyvsp[(2) - (3)].name))))
			{
				main_module_name = get_first_main_module();

				if (!string_undefined_p(main_module_name)) {
					/* Ok, we got it ! Now we select it: */
					user_log("Main module PROGRAM \"%s\" selected.\n",
									 main_module_name);
					lazy_open_module(main_module_name);
					free(main_module_name);
				}
			}
		}
		free((yyvsp[(2) - (3)].name));
	}
    break;

  case 65:
/* Line 1787 of yacc.c  */
#line 790 "tp_yacc.y"
    {
		if(workspace_name_p((yyvsp[(1) - (1)].name)))
			(yyval.name) = (yyvsp[(1) - (1)].name);
		else
			pips_user_error("workspace name %s contains invalid char(s)\n", (yyvsp[(1) - (1)].name));
	}
    break;

  case 66:
/* Line 1787 of yacc.c  */
#line 799 "tp_yacc.y"
    {
		string main_module_name;
		pips_debug(7,"reduce rule i_create\n");

		if (tpips_execution_mode)
    {
			if (workspace_exists_p((yyvsp[(2) - (4)].name)))
				pips_user_error("Workspace %s already exists. Delete it!", (yyvsp[(2) - (4)].name));
			else if (db_get_current_workspace_name())
      {
				pips_user_error("Close current workspace %s before "
												"creating another!",
												db_get_current_workspace_name());
			}
			else
			{
				if (db_create_workspace((yyvsp[(2) - (4)].name)))
				{
          volatile bool ws_ok;
          volatile bool user_exception_raised = false;

          CATCH(user_exception_error) {
            ws_ok = false;
            user_exception_raised = true;
          }
          TRY {
            ws_ok = create_workspace((yyvsp[(3) - (4)].array));
            UNCATCH(user_exception_error);
          }

          if (!ws_ok)
          {
            if (get_bool_property("CLOSE_WORKSPACE_AND_QUIT_ON_ERROR"))
            {
              // this is dangerous, it may or may not work...
              // hmmm... might recurse on user errors?
              db_close_workspace(false);
              pips_user_error("Could not create workspace \"%s\"", (yyvsp[(2) - (4)].name));
            }
            else
            {
              db_close_workspace(false);
              // If you need to preserve the workspace
              // for debugging purposes, use property ABORT_ON_USER_ERROR
              if (!get_bool_property("ABORT_ON_USER_ERROR"))
              {
                user_log("Deleting workspace...\n");
                delete_workspace((yyvsp[(2) - (4)].name));
              }
              pips_user_error("Could not create workspace \"%s\"\n", (yyvsp[(2) - (4)].name));
            }
          }

          if (user_exception_raised)
            THROW(user_exception_error);

          main_module_name = get_first_main_module();

          if (!string_undefined_p(main_module_name))
          {
            // Ok, we got it ! Now we select it:
            user_log("Main module PROGRAM \"%s\" selected.", main_module_name);
            lazy_open_module(main_module_name);
            free(main_module_name);
          }
          (yyval.status) = true;
				}
				else {
					pips_user_error("Cannot create directory for workspace, "
													"check rights!\n");
				}
			}
		}
		free((yyvsp[(2) - (4)].name));
		gen_array_full_free((yyvsp[(3) - (4)].array));
	}
    break;

  case 67:
/* Line 1787 of yacc.c  */
#line 878 "tp_yacc.y"
    {
		(yyval.status) = tp_close_the_workspace(db_get_current_workspace_name());
	}
    break;

  case 68:
/* Line 1787 of yacc.c  */
#line 882 "tp_yacc.y"
    {
		(yyval.status) = tp_close_the_workspace((yyvsp[(2) - (3)].name));
		free((yyvsp[(2) - (3)].name));
	}
    break;

  case 69:
/* Line 1787 of yacc.c  */
#line 889 "tp_yacc.y"
    {
		pips_debug(7,"reduce rule i_delete\n");

		if (tpips_execution_mode) {
		string wname = db_get_current_workspace_name();
		if ((wname != NULL) && same_string_p(wname, (yyvsp[(2) - (3)].name))) {
			pips_user_error("Close before delete: "
											"Workspace %s is open\n", wname);
			(yyval.status) = false;
		} else {
			if(workspace_exists_p((yyvsp[(2) - (3)].name)))
			{
				if(delete_workspace ((yyvsp[(2) - (3)].name))) {
					/* In case of problem, user_error() has been
						 called, so it is OK now !!*/
					user_log ("Workspace %s deleted.\n", (yyvsp[(2) - (3)].name));
					(yyval.status) = true;
			}
			else {
				pips_user_warning(
					"Could not delete workspace \"%s\"\n", (yyvsp[(2) - (3)].name));
			}
			}
			else {
				pips_user_warning("%s: No such workspace\n", (yyvsp[(2) - (3)].name));
			}
		}
		}
		free((yyvsp[(2) - (3)].name));
	}
    break;

  case 70:
/* Line 1787 of yacc.c  */
#line 922 "tp_yacc.y"
    {
		pips_debug(7,"reduce rule i_module\n");

		if (tpips_execution_mode) {
			if (db_get_current_workspace_name()) {
				(yyval.status) = tp_set_current_module((yyvsp[(2) - (3)].name) /*strupper($2,$2)*/);
		        free((yyvsp[(2) - (3)].name));
			} else {
		        free((yyvsp[(2) - (3)].name));
				pips_user_error("No workspace open. Open or create one!\n");
				(yyval.status) = false;
			}
		}
        else free((yyvsp[(2) - (3)].name));
	}
    break;

  case 71:
/* Line 1787 of yacc.c  */
#line 940 "tp_yacc.y"
    {
		pips_debug(7, "reduce rule i_make\n");
		(yyval.status) = perform(safe_make, &(yyvsp[(2) - (3)].rn));
	}
    break;

  case 72:
/* Line 1787 of yacc.c  */
#line 947 "tp_yacc.y"
    {
		pips_debug(7,"reduce rule i_apply\n");
		(yyval.status) = perform(safe_apply, &(yyvsp[(2) - (3)].rn));
	}
    break;

  case 73:
/* Line 1787 of yacc.c  */
#line 954 "tp_yacc.y"
    {
		pips_debug(7, "reduce rule i_capply\n");
		(yyval.status) = safe_concurrent_apply((yyvsp[(2) - (3)].rn).the_name, (yyvsp[(2) - (3)].rn).the_owners);
	}
    break;

  case 74:
/* Line 1787 of yacc.c  */
#line 961 "tp_yacc.y"
    {
		pips_debug(7,"reduce rule i_display\n");
		(yyval.status) = perform(display_a_resource, &(yyvsp[(2) - (3)].rn));
	}
    break;

  case 75:
/* Line 1787 of yacc.c  */
#line 968 "tp_yacc.y"
    {
		pips_debug(7, "reduce rule i_touch\n");
		(yyval.status) = perform(touch_a_resource, &(yyvsp[(2) - (3)].rn));
	}
    break;

  case 76:
/* Line 1787 of yacc.c  */
#line 975 "tp_yacc.y"
    {
		pips_debug(7, "reduce rule i_show\n");
		(yyval.status) = perform(just_show, &(yyvsp[(2) - (3)].rn));
	}
    break;

  case 77:
/* Line 1787 of yacc.c  */
#line 982 "tp_yacc.y"
    {
		pips_debug(7,"reduce rule i_rm\n");
		(yyval.status) = perform(remove_a_resource, &(yyvsp[(2) - (3)].rn));
	}
    break;

  case 78:
/* Line 1787 of yacc.c  */
#line 989 "tp_yacc.y"
    {
		pips_debug(7,"reduce rule i_activate\n");
		if (tpips_execution_mode)
		{
			if(!db_get_current_workspace_name())
				pips_user_error("Open or create a workspace first!\n");

		user_log("Selecting rule: %s\n", (yyvsp[(2) - (3)].name));
		activate((yyvsp[(2) - (3)].name));
		(yyval.status) = true;
		}
		free((yyvsp[(2) - (3)].name));
	}
    break;

  case 79:
/* Line 1787 of yacc.c  */
#line 1005 "tp_yacc.y"
    {
		string ph = active_phase_for_resource((yyvsp[(2) - (3)].name));
		fprintf(stdout, "resource %s built by phase %s\n", (yyvsp[(2) - (3)].name), ph);
		if (jpips_is_running)
		{
			jpips_begin_tag("result");
			jpips_add_tag(ph);
			jpips_end_tag();
		}
		free((yyvsp[(2) - (3)].name));
	}
    break;

  case 80:
/* Line 1787 of yacc.c  */
#line 1019 "tp_yacc.y"
    {
		pips_debug(7,"reduce rule i_get (%s)\n", (yyvsp[(2) - (3)].name));

		if (tpips_execution_mode) {
			fprint_property(stdout, (yyvsp[(2) - (3)].name));
			if (jpips_is_running)
			{
				jpips_begin_tag("result");
				jpips_add_tag("");
				fprint_property_direct(jpips_out_file(), (yyvsp[(2) - (3)].name));
				jpips_end_tag();
			}
			(yyval.status) = true;
		}
		free((yyvsp[(2) - (3)].name));
	}
    break;

  case 81:
/* Line 1787 of yacc.c  */
#line 1039 "tp_yacc.y"
    {
    process_file_list((yyvsp[(2) - (3)].array));
    gen_array_full_free((yyvsp[(2) - (3)].array));
  }
    break;

  case 83:
/* Line 1787 of yacc.c  */
#line 1049 "tp_yacc.y"
    {
		gen_array_append((yyvsp[(1) - (2)].array), (yyvsp[(2) - (2)].name));
		(yyval.array) = (yyvsp[(1) - (2)].array);
	}
    break;

  case 84:
/* Line 1787 of yacc.c  */
#line 1054 "tp_yacc.y"
    {
		(yyval.array) = gen_array_make(0);
		gen_array_append((yyval.array), (yyvsp[(1) - (1)].name));
	}
    break;

  case 86:
/* Line 1787 of yacc.c  */
#line 1064 "tp_yacc.y"
    {
		pips_debug(7,"reduce rule resource_id (%s)\n",(yyvsp[(2) - (2)].name));
		(yyval.rn).the_name = (yyvsp[(1) - (2)].name);
		(yyval.rn).the_owners = (yyvsp[(2) - (2)].array);
	}
    break;

  case 87:
/* Line 1787 of yacc.c  */
#line 1072 "tp_yacc.y"
    {
		pips_debug(7,"reduce rule rule_id (%s)\n",(yyvsp[(1) - (2)].name));
		(yyval.rn).the_name = (yyvsp[(1) - (2)].name);
		(yyval.rn).the_owners = (yyvsp[(2) - (2)].array);
	}
    break;

  case 88:
/* Line 1787 of yacc.c  */
#line 1080 "tp_yacc.y"
    {
		pips_debug(7,"reduce rule owner (ALL)\n");
		if (tpips_execution_mode)
		{
			if (!db_get_current_workspace_name())
				pips_user_error("No current workspace! create or open one!\n");
			else
				(yyval.array) = db_get_module_list();
		}
	}
    break;

  case 89:
/* Line 1787 of yacc.c  */
#line 1091 "tp_yacc.y"
    {
		pips_debug(7,"reduce rule owner (ALL)\n");
		if (tpips_execution_mode)
		{
			if (!db_get_current_workspace_name())
				pips_user_error("No current workspace! create or open one!\n");
			else
				(yyval.array) = db_get_function_list();
		}
	}
    break;

  case 90:
/* Line 1787 of yacc.c  */
#line 1102 "tp_yacc.y"
    {
		pips_debug(7,"reduce rule owner (PROGRAM)\n");
		if (tpips_execution_mode)
		{
			(yyval.array) = gen_array_make(0);
			gen_array_dupappend((yyval.array), "");
		}
	}
    break;

  case 91:
/* Line 1787 of yacc.c  */
#line 1111 "tp_yacc.y"
    {
		pips_debug(7,"reduce rule owner (MAIN)\n");

		if (tpips_execution_mode) {
			if (!db_get_current_workspace_name())
				pips_user_error("No current workspace! create or open one!\n");
			else {
				(yyval.array) = get_main();
			}
		}
	}
    break;

  case 92:
/* Line 1787 of yacc.c  */
#line 1123 "tp_yacc.y"
    {
		pips_debug(7,"reduce rule owner (MODULE)\n");
		if (tpips_execution_mode) {
			string n = db_get_current_module_name();
			(yyval.array) = gen_array_make(0);
			if (n) gen_array_dupappend((yyval.array), n);
		}
	}
    break;

  case 93:
/* Line 1787 of yacc.c  */
#line 1132 "tp_yacc.y"
    {
		pips_debug(7,"reduce rule owner (CALLEES)\n");

		if (tpips_execution_mode)
		{
			callees called_modules;

			if (!safe_make(DBR_CALLEES, db_get_current_module_name()))
				pips_internal_error("Cannot make callees for %s\n",
														db_get_current_module_name());

			called_modules = (callees)
				db_get_memory_resource(DBR_CALLEES,
															 db_get_current_module_name(),true);

			(yyval.array) = gen_array_from_list(callees_callees(called_modules));
		}
	}
    break;

  case 94:
/* Line 1787 of yacc.c  */
#line 1151 "tp_yacc.y"
    {
		pips_debug(7,"reduce rule owner (CALLERS)\n");
		if (tpips_execution_mode)
		{
                        (yyval.array) = get_callers(db_get_current_module_name());
		}
	}
    break;

  case 95:
/* Line 1787 of yacc.c  */
#line 1159 "tp_yacc.y"
    { (yyval.array) = (yyvsp[(2) - (3)].array); }
    break;

  case 96:
/* Line 1787 of yacc.c  */
#line 1161 "tp_yacc.y"
    {
		pips_debug(7,"reduce rule owner (none)\n");
		if (tpips_execution_mode)
		{
			string n = db_get_current_module_name();
			(yyval.array) = gen_array_make(0);
			if (n)
				gen_array_dupappend((yyval.array), n);
			else {
				string wsn = db_get_current_workspace_name();
				// pips_internal_error("No current module name\n");
				if (wsn==NULL)
					pips_user_error(
						"No current workspace. Open or create one first!");
				else
          pips_user_error(
            "No current module has been defined, explicitly or implictly.\n"
            "Please specify a module name as argument or check that"
            " the current workspace \"%s\" contains one main module"
            " or no more than one module.\n",
            wsn);
			}
		}
	}
    break;

  case 97:
/* Line 1787 of yacc.c  */
#line 1188 "tp_yacc.y"
    {
		(yyval.array) = gen_array_make(0); gen_array_append((yyval.array), (yyvsp[(1) - (1)].name));
	}
    break;

  case 98:
/* Line 1787 of yacc.c  */
#line 1192 "tp_yacc.y"
    { gen_array_append((yyvsp[(1) - (2)].array), (yyvsp[(2) - (2)].name) /* strupper($2,$2) */); (yyval.array) = (yyvsp[(1) - (2)].array); }
    break;

  case 99:
/* Line 1787 of yacc.c  */
#line 1194 "tp_yacc.y"
    { gen_array_append((yyvsp[(1) - (3)].array), (yyvsp[(3) - (3)].name) /* strupper($3,$3) */); (yyval.array) = (yyvsp[(1) - (3)].array); }
    break;

  case 100:
/* Line 1787 of yacc.c  */
#line 1198 "tp_yacc.y"
    {
		if (!property_name_p((yyvsp[(1) - (1)].name)))
			yyerror("Expecting a property name.\n");
		(yyval.name) = (yyvsp[(1) - (1)].name);
	}
    break;

  case 101:
/* Line 1787 of yacc.c  */
#line 1206 "tp_yacc.y"
    {
		if (!phase_name_p((yyvsp[(1) - (1)].name)))
			yyerror("Expecting a phase name.\n");
		(yyval.name) = (yyvsp[(1) - (1)].name);
	}
    break;

  case 102:
/* Line 1787 of yacc.c  */
#line 1214 "tp_yacc.y"
    {
		if (!resource_name_p((yyvsp[(1) - (1)].name)))
			yyerror("expecting a resource name\n");
		(yyval.name) = (yyvsp[(1) - (1)].name);
	}
    break;


/* Line 1787 of yacc.c  */
#line 2976 "y.tab.c"
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
#line 1221 "tp_yacc.y"


