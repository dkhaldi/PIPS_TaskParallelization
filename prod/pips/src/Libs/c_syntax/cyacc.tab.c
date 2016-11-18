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
#define yyparse         c_parse
#define yylex           c_lex
#define yyerror         c_error
#define yylval          c_lval
#define yychar          c_char
#define yydebug         c_debug
#define yynerrs         c_nerrs

/* Copy the first part of user declarations.  */
/* Line 336 of yacc.c  */
#line 52 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"

#ifdef HAVE_CONFIG_H
    #include "pips_config.h"
#endif
 /* C declarations */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "genC.h"
#include "linear.h"
#include "ri.h"
#include "ri-util.h"
#include "text-util.h"
#include "misc.h"
#include "properties.h"

#include "c_parser_private.h"

#include "c_syntax.h"

#define C_ERROR_VERBOSE 1 /* much clearer error messages with bison */

/* Increase the parser stack to have SPEC2006/445.gobmk/owl_defendpat.c
   going through without a:

   user warning in splitc_error: C memory exhausted near "0" at preprocessed line 13459 (user line 8732)
*/
#define YYMAXDEPTH 1000000

// To set breakpoint in cyacc.y
// void breakpoint(int l) {;}
// #define BREAKPOINT breakpoint(__LINE__)
#define BREAKPOINT ;

static int CurrentMode = 0; /**< to know the mode of the formal parameter: by value or by reference*/
static bool is_external = true; /**< to know if the variable is declared inside or outside a function, so its scope
				   is the current function or the compilation unit or TOP-LEVEL*/
static int enum_counter = 0; /**< to compute the enumerator value: val(i) = val(i-1) + 1 */
static int abstract_counter = 1; /**< to create temporary entities for abstract types */

 static list initialization_expressions = NIL; /**< to preserve information about the declarations for the prettyprinter, especially for the global variables, but also the derived types (struct, union, enum). */

 /* init_p = 0 => no initialization for a variable or no definition
    for a derived entity (struct, union, maybe enum) */
static void add_initialization_expression(int init_p)
{
  initialization_expressions
    = CONS(EXPRESSION, int_to_expression(init_p), initialization_expressions);
}

/* The following structures must be stacks because all the related
   entities are in recursive structures.  Since there are not stacks
   with basic types such as integer or logical domain, I used
   basic_domain to avoid creating special stacks for FormalStack,
   OffsetStack, ... */

static void PushFunction(entity f)
{
  stack_push((char *) f, FunctionStack);
}

static void PopFunction()
{
  stack_pop(FunctionStack);
 }

entity GetFunction()
{
  entity f = stack_head(FunctionStack);
  return f;
}

 // FI: I assumed it was the current context; in fact the current
 // context is rather the top of the ContextStack. I tried to maintain
 // as an invariant ycontext==stack_head(ContextStack). But this is not
 // be a good idea as it interferes with cyacc.y use of ycontext and
 // ContextStack
static c_parser_context ycontext = c_parser_context_undefined;


/* FI: these two variables are used in conjunction with comma
   expressions. I do not remember why they are needed. They sometimes
   stay set although they have become useless. The parser used not to
   reset them systematically, which caused problems with
   io_intrinsics*.c */
static string expression_comment = string_undefined;
static int expression_line_number = STATEMENT_NUMBER_UNDEFINED;

/* we don't want an expression comment with new lines, it is disgracefull */
void reset_expression_comment()
{
  if(!string_undefined_p(expression_comment)) {
    /* Too bad. This should not happen, but it happens with comma
       expressions in header files */
    free(expression_comment);
    expression_comment = string_undefined;
  }

  expression_line_number = STATEMENT_NUMBER_UNDEFINED;
}

/* flushes all expression comments and add them to statement s */
static statement flush_expression_comment(statement s) {
  if(!empty_comments_p(expression_comment)) {
    if(!empty_comments_p(statement_comments(s))) {
	  char *tmp = statement_comments(s);
	  asprintf(&statement_comments(s),"%s%s",statement_comments(s),expression_comment);
	  free(tmp);
      free(expression_comment);
    }
    else
      statement_comments(s) = expression_comment;
	statement_number(s) = expression_line_number;
	expression_line_number = STATEMENT_NUMBER_UNDEFINED;
    expression_comment=string_undefined;
  }
  return s;
}


/* after a while (crocodile) expression comments are pushed into a list that
   is purged upon call to add_expression_comment */ 
static list all_expression_comments_as_statement_comments = NIL;
static void save_expression_comment_as_statement_comment() {
	if(!string_undefined_p(expression_comment)) {
		all_expression_comments_as_statement_comments = 
		CONS(STRING,expression_comment, all_expression_comments_as_statement_comments);
	}
    expression_comment=string_undefined;
}
/* flushes all statement comments and add them to statement s */
static statement flush_statement_comment(statement s) {
  s=flush_expression_comment(s); // should not be necessary 
  if(!ENDP(all_expression_comments_as_statement_comments)) {
    pips_assert("not on a block",!statement_block_p(s));
    all_expression_comments_as_statement_comments = gen_nreverse(all_expression_comments_as_statement_comments);
    char * comments = list_to_string(all_expression_comments_as_statement_comments);
    if(!empty_comments_p(statement_comments(s))) {
	  char *tmp = statement_comments(s);
	  asprintf(&statement_comments(s),"%s%s",statement_comments(s), comments);
	  free(tmp);
	  free(comments);
    }
    else
      statement_comments(s) = comments;
    FOREACH(STRING,s,all_expression_comments_as_statement_comments) free(s);
    gen_free_list(all_expression_comments_as_statement_comments);
    all_expression_comments_as_statement_comments=NIL;
  }
  return s;
}


/* The scope is moved up the scope tree and a NULL is return when
   there are no more scope to explore. */
string pop_block_scope(string old_scope)
{
  string new_scope = old_scope;
  string last_scope = string_undefined;

  pips_debug(8, "old_scope = \"%s\"\n", old_scope);
  pips_assert("old_scope is a scope", string_block_scope_p(old_scope));

  if(strlen(old_scope)>0) {
    /* get rid of last block separator */
    new_scope[strlen(new_scope)-1] = '\0';
    last_scope = strrchr(new_scope, BLOCK_SEP_CHAR);

    if(last_scope==NULL)
      *new_scope = '\0';
    else
      *(last_scope+1) = '\0';
  }
  else
    new_scope = NULL;

  if(new_scope!=NULL) {
    pips_debug(8, "new_scope = \"%s\"\n", new_scope);
    pips_assert("new_scope is a scope", string_block_scope_p(new_scope));
  }
  else {
    pips_debug(8, "new_scope = NULL\n");
  }

  return new_scope;
}

/* Allocate a new string containing only block scope information */
string scope_to_block_scope(string full_scope)
{
  string l_scope = strrchr(full_scope, BLOCK_SEP_CHAR);
  string f_scope = strchr(full_scope, MODULE_SEP);
  string block_scope = string_undefined;

  pips_debug(8, "full_scope = \"%s\"\n", full_scope);

  if(f_scope==NULL)
    f_scope = full_scope;
  else
    f_scope++;

  if(l_scope==NULL)
    block_scope = strdup("");
  else
    block_scope = gen_strndup0(f_scope, (unsigned) (l_scope-f_scope+1));

  pips_debug(8, "f_scope = \"%s\", l_scope = \"%s\"\n", f_scope, l_scope);
  pips_assert("block_scope is a scope", string_block_scope_p(block_scope));

  return block_scope;
}

c_parser_context CreateDefaultContext()
{
  c_parser_context c = make_c_parser_context(empty_scope(),
					     type_undefined,
					     storage_undefined,
					     NIL,
					     false,
					     false);
  pips_debug(8, "New default context %p\n", c);
  return c;
}

static int C_scope_identifier = -2;

void InitScope()
{
  C_scope_identifier = -1;
}

static void EnterScope()
{
  c_parser_context nc = CreateDefaultContext();
  string cs = string_undefined;

  push_new_c_parser_scope(); // For the lexical analyzer

  pips_assert("C_scope_identifier has been initialized", C_scope_identifier>-2);

  if(!stack_empty_p(ContextStack)) {
    c_parser_context c = (c_parser_context) stack_head(ContextStack);
    pips_assert("The current context is defined", !c_parser_context_undefined_p(c));
    pips_assert("The current context scope is defined",
		!string_undefined_p(c_parser_context_scope(c))
		&& c_parser_context_scope(c)!=NULL);
    pips_assert("The current context only contains scope information",
		//type_undefined_p(c_parser_context_type(c)) &&
		storage_undefined_p(c_parser_context_storage(c))
		&& ENDP(c_parser_context_qualifiers(c))
		//&& !c_parser_context_typedef(c)
		//&& !c_parser_context_static(c)
		);
    cs = c_parser_context_scope(c);
    pips_assert("scope contains only block scope information", string_block_scope_p(cs));
  }
  else
    cs = "";

  // Add scope information if any
  C_scope_identifier++;
  // A scope is needed right away to distinguish between formal
  // parameters and local variables. See
  // Validation/C_syntax/block_scope01.c, identifier x in function foo
  if(C_scope_identifier>=0) {
    string ns = int2a(C_scope_identifier);

    char * stf = c_parser_context_scope(nc);
    c_parser_context_scope(nc) = strdup(concatenate(cs, ns, BLOCK_SEP_STRING, NULL));
	free(stf);
    free(ns);
  }
  else {
    char * stf = c_parser_context_scope(nc);
    c_parser_context_scope(nc) = strdup(cs);
	free(stf);
  }

  stack_push((char *) nc, ContextStack);
  //ycontext = nc;
  //pips_assert("ycontext is consistant with stack_head(ContextStack)",
  //	      ycontext==stack_head(ContextStack));
  pips_debug(8, "New block scope string: \"%s\" for context %p\n",
	     c_parser_context_scope(nc), nc);
}

int ScopeStackSize()
{
  return stack_size(ContextStack);
}

string GetScope()
{
  string s = "";

  /* FI: I do not know if it wouldn't be better to initialize the
     ContextStack with a default context before calling the C
     parser */
  if(!stack_empty_p(ContextStack)) {
    c_parser_context c = (c_parser_context) stack_head(ContextStack);

    s = c_parser_context_scope(c);
  }

  return s;
}

string GetParentScope()
{
  string s = "";

  if(!stack_empty_p(ContextStack) && stack_size(ContextStack)>=2) {
    c_parser_context c = (c_parser_context) stack_nth(ContextStack,2);

    s = c_parser_context_scope(c);
  }

  return s;
}

void ExitScope()
{
  c_parser_context c = (c_parser_context) stack_head(ContextStack);

  pop_c_parser_scope_stack();

  pips_assert("The current context is defined", !c_parser_context_undefined_p(c));
  pips_assert("The current context scope is defined",
	      !string_undefined_p(c_parser_context_scope(c))
	      && c_parser_context_scope(c)!=NULL);
  pips_assert("The current context only contains scope information",
	      //type_undefined_p(c_parser_context_type(c)) &&
	      storage_undefined_p(c_parser_context_storage(c))
	      && ENDP(c_parser_context_qualifiers(c))
	      //&& !c_parser_context_typedef(c)
	      //&& !c_parser_context_static(c)
	      );
  pips_debug(8, "Exiting context scope \"\%s\" in context %p\n",
	     c_parser_context_scope(c), c);
  free_c_parser_context(c);
  (void) stack_pop(ContextStack);
  if(!stack_empty_p(ContextStack)) {
    c_parser_context oc = (c_parser_context) stack_head(ContextStack);
    //pips_assert("ycontext is consistant with stack_head(ContextStack)",
    //		ycontext==stack_head(ContextStack));
    pips_debug(8, "Back to context scope \"\%s\" in context %p\n",
	       c_parser_context_scope(oc), oc);
  }
  else {
    // ycontext = c_parser_context_undefined;
    pips_debug(8, "Back to undefined context scope\n");
  }
}

void PushContext(c_parser_context c)
{
  stack_push((char *) c, ContextStack);
  pips_debug(8, "Context %p with scope \"%s\" is put in stack position %d\n",
	     c, c_parser_context_scope(c), stack_size(ContextStack));
}

void PopContext()
{
  c_parser_context fc = (c_parser_context) stack_head(ContextStack);

  pips_debug(8, "Context %p with scope \"%s\" is popped from stack position %d\n",
	     fc, c_parser_context_scope(fc), stack_size(ContextStack));
  (void)stack_pop(ContextStack);
  if(stack_empty_p(ContextStack)) {
    pips_debug(8, "context stack is now empty\n");
  }
  else {
    c_parser_context h = (c_parser_context) stack_head(ContextStack);
    pips_debug(8, "Context %p with scope \"%s\" is top of stack at position %d\n",
	       h, c_parser_context_scope(h), stack_size(ContextStack));
  }
}

c_parser_context GetContext()
{

    c_parser_context c = c_parser_context_undefined;

    if(!stack_empty_p(ContextStack))
      c = (c_parser_context) stack_head(ContextStack);
    else
      // Should we return a default context?
      // Not really compatible with a clean memory allocation policy
      pips_internal_error("No current context");

  pips_debug(8, "Context %p is obtained from stack position %d\n",
	     c, stack_size(ContextStack));

  return c;
}

c_parser_context GetContextCopy()
{
  c_parser_context c = (c_parser_context) stack_head(ContextStack);
  c_parser_context cc = copy_c_parser_context(c);
  pips_debug(8, "Context copy %p with scope \"%s\" is obtained from context %p with scope \"%s\" at stack position %d\n",
	     cc, c_parser_context_scope(cc),
	     c, c_parser_context_scope(c),
	     stack_size(ContextStack));
  return cc;
}
/* Declaration counter 
 *
 * It is used to declare the formal parameters in function declarations.
 */
 static int declaration_counter = 0;

 void reset_declaration_counter()
 {
   declaration_counter = 0;
 }

 int get_declaration_counter()
 {
   return declaration_counter;
 }

 /* Each scope in the current unit has its own number.
  *
  * The scope management in the C parser is the same as in the C preprocessor.
  *
  * The scope numbers defined here are used by the C parser lexical
  * analyzer to disambiguate between named types and variables, but
  * different scopes are defined for the internal representation.
 */
#define SCOPE_UNDEFINED (-1)
 static int c_parser_scope_number = SCOPE_UNDEFINED;
 static stack c_parser_scope_stack = stack_undefined;

 void init_c_parser_scope_stack()
 {
   c_parser_scope_number = 0;
   pips_assert("The stack is undefined",
	       stack_undefined_p(c_parser_scope_stack));
   c_parser_scope_stack = stack_make(string_domain, 0, 0);
 }

 void reset_c_parser_scope_stack()
 {
   if(c_parser_scope_stack != stack_undefined) {
     if(stack_empty_p(c_parser_scope_stack)) {
       stack_free(&c_parser_scope_stack);
       c_parser_scope_stack = stack_undefined;
     }
     else {
       // pips_internal_error? Could be a bad input C file...
       pips_user_warning("Parser scope stack is not empty.\n");
     }
   }
   c_parser_scope_number = SCOPE_UNDEFINED;
   return;
 }

 /* To be used by an error handler */
 void force_reset_c_parser_scope_stack()
 {
   if(c_parser_scope_stack != stack_undefined) {
       stack_free(&c_parser_scope_stack);
       c_parser_scope_stack = stack_undefined;
   }
   c_parser_scope_number = SCOPE_UNDEFINED;
   return;
 }

 void push_new_c_parser_scope()
 {
   c_parser_scope_number++;
   string sn = string_undefined;
   (void) asprintf(&sn, "%d", c_parser_scope_number);
   stack_push((void *) sn, c_parser_scope_stack);
   return;
 }

 void pop_c_parser_scope_stack()
 {
   stack_pop(c_parser_scope_stack);
   return;
 }

bool c_parser_scope_stack_empty_p()
{
  return stack_empty_p(c_parser_scope_stack);
}

string get_c_parser_current_scope()
 {
   string sn = string_undefined;
   if(c_parser_scope_stack_empty_p()) {
     // We are at the global level: no scope has been entered yet
     sn = "";
   }
   else
     sn = (string) stack_head(c_parser_scope_stack);
   return sn;
 }

string get_c_parser_nth_scope(int n)
 {
   string sn = (string) stack_nth(c_parser_scope_stack, n);
   return sn;
 }

int c_parser_number_of_scopes()
 {
   int n = stack_size(c_parser_scope_stack);
   return n;
 }

/* When struct and union declarations are nested, the rules cannot
   return information about the internal declarations because they
   must return type information. Hence internal declarations must be
   recorded and re-used when the final continue/declaration statement
   is generated. In order not to confuse the prettyprinter, they must
   appear first in the declaration list, that is in the innermost to
   outermost order. */

static list internal_derived_entity_declarations = NIL;

static void RecordDerivedEntityDeclaration(entity de)
{
  internal_derived_entity_declarations
    = gen_nconc(internal_derived_entity_declarations,
		CONS(ENTITY, de, NIL));
}

static list GetDerivedEntityDeclarations()
{
  list l = internal_derived_entity_declarations;
  /* The list spine is going to be reused by the caller. No need to
     free. */
  internal_derived_entity_declarations = NIL;
  return l;
}

static void ResetDerivedEntityDeclarations()
{
  if(!ENDP(internal_derived_entity_declarations)) {
    gen_free_list(internal_derived_entity_declarations);
    internal_derived_entity_declarations = NIL;
  }
}

/* Line 336 of yacc.c  */
#line 625 "cyacc.tab.c"

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
   by #include "cyacc.tab.h".  */
#ifndef C_CYACC_TAB_H
# define C_CYACC_TAB_H
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int c_debug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     TK_IDENT = 258,
     TK_CHARCON = 259,
     TK_INTCON = 260,
     TK_FLOATCON = 261,
     TK_NAMED_TYPE = 262,
     TK_STRINGCON = 263,
     TK_WSTRINGCON = 264,
     TK_EOF = 265,
     TK_CHAR = 266,
     TK_INT = 267,
     TK_INT128 = 268,
     TK_UINT128 = 269,
     TK_DOUBLE = 270,
     TK_FLOAT = 271,
     TK_VOID = 272,
     TK_COMPLEX = 273,
     TK_ENUM = 274,
     TK_STRUCT = 275,
     TK_TYPEDEF = 276,
     TK_UNION = 277,
     TK_SIGNED = 278,
     TK_UNSIGNED = 279,
     TK_LONG = 280,
     TK_SHORT = 281,
     TK_VOLATILE = 282,
     TK_EXTERN = 283,
     TK_STATIC = 284,
     TK_STATIC_DIMENSION = 285,
     TK_CONST = 286,
     TK_RESTRICT = 287,
     TK_AUTO = 288,
     TK_REGISTER = 289,
     TK_THREAD = 290,
     TK_SIZEOF = 291,
     TK_ALIGNOF = 292,
     TK_EQ = 293,
     TK_PLUS_EQ = 294,
     TK_MINUS_EQ = 295,
     TK_STAR_EQ = 296,
     TK_SLASH_EQ = 297,
     TK_PERCENT_EQ = 298,
     TK_AND_EQ = 299,
     TK_PIPE_EQ = 300,
     TK_CIRC_EQ = 301,
     TK_INF_INF_EQ = 302,
     TK_SUP_SUP_EQ = 303,
     TK_ARROW = 304,
     TK_DOT = 305,
     TK_EQ_EQ = 306,
     TK_EXCLAM_EQ = 307,
     TK_INF = 308,
     TK_SUP = 309,
     TK_INF_EQ = 310,
     TK_SUP_EQ = 311,
     TK_PLUS = 312,
     TK_MINUS = 313,
     TK_STAR = 314,
     TK_SLASH = 315,
     TK_PERCENT = 316,
     TK_TILDE = 317,
     TK_AND = 318,
     TK_PIPE = 319,
     TK_CIRC = 320,
     TK_EXCLAM = 321,
     TK_AND_AND = 322,
     TK_PIPE_PIPE = 323,
     TK_INF_INF = 324,
     TK_SUP_SUP = 325,
     TK_PLUS_PLUS = 326,
     TK_MINUS_MINUS = 327,
     TK_RPAREN = 328,
     TK_LPAREN = 329,
     TK_RBRACE = 330,
     TK_LBRACE = 331,
     TK_LBRACKET = 332,
     TK_RBRACKET = 333,
     TK_COLON = 334,
     TK_SEMICOLON = 335,
     TK_COMMA = 336,
     TK_ELLIPSIS = 337,
     TK_QUEST = 338,
     TK_BREAK = 339,
     TK_CONTINUE = 340,
     TK_GOTO = 341,
     TK_RETURN = 342,
     TK_SWITCH = 343,
     TK_CASE = 344,
     TK_DEFAULT = 345,
     TK_WHILE = 346,
     TK_DO = 347,
     TK_FOR = 348,
     TK_IF = 349,
     TK_ELSE = 350,
     TK_ATTRIBUTE = 351,
     TK_INLINE = 352,
     TK_ASM = 353,
     TK_TYPEOF = 354,
     TK_FUNCTION__ = 355,
     TK_PRETTY_FUNCTION__ = 356,
     TK_LABEL__ = 357,
     TK_BUILTIN_VA_ARG = 358,
     TK_BUILTIN_VA_LIST = 359,
     TK_BLOCKATTRIBUTE = 360,
     TK_DECLSPEC = 361,
     TK_MSASM = 362,
     TK_MSATTR = 363,
     TK_PRAGMA = 364,
     TK__Pragma = 365,
     TK_AT_TRANSFORM = 366,
     TK_AT_TRANSFORMEXPR = 367,
     TK_AT_SPECIFIER = 368,
     TK_AT_EXPR = 369,
     TK_AT_NAME = 370,
     TK_COMPLEXCON = 371,
     TK_CAST = 372,
     TK_ADDROF = 373
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 350 of yacc.c  */
#line 604 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"

	cons * liste;
	entity entity;
	expression expression;
	statement statement;
	string string;
	type type;
        parameter parameter;
        int integer;
        qualifier qualifier;


/* Line 350 of yacc.c  */
#line 799 "cyacc.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE c_lval;

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int c_parse (void *YYPARSE_PARAM);
#else
int c_parse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int c_parse (void);
#else
int c_parse ();
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !C_CYACC_TAB_H  */

/* Copy the second part of user declarations.  */

/* Line 353 of yacc.c  */
#line 827 "cyacc.tab.c"

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
#define YYFINAL  7
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   3204

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  119
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  110
/* YYNRULES -- Number of rules.  */
#define YYNRULES  324
/* YYNRULES -- Number of states.  */
#define YYNSTATES  597

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   373

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
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     6,     8,     9,    10,    14,    17,    18,
      20,    22,    28,    30,    31,    39,    48,    57,    61,    63,
      65,    70,    71,    73,    75,    77,    80,    85,    88,    93,
      96,    99,   102,   105,   108,   111,   114,   117,   120,   123,
     127,   131,   135,   137,   142,   149,   152,   158,   162,   166,
     170,   174,   178,   182,   186,   190,   194,   198,   202,   206,
     210,   214,   218,   222,   226,   230,   234,   238,   242,   246,
     250,   254,   258,   262,   266,   270,   274,   279,   286,   289,
     294,   296,   298,   300,   302,   304,   306,   308,   310,   312,
     315,   317,   320,   323,   325,   327,   329,   331,   335,   337,
     341,   342,   344,   348,   351,   353,   355,   356,   360,   365,
     371,   372,   374,   377,   378,   380,   381,   383,   385,   389,
     393,   394,   396,   400,   404,   408,   412,   416,   420,   421,
     427,   430,   434,   435,   436,   438,   441,   443,   444,   449,
     451,   455,   458,   463,   465,   467,   470,   473,   475,   477,
     480,   482,   484,   488,   494,   495,   496,   502,   503,   508,
     509,   516,   517,   527,   528,   529,   539,   542,   546,   552,
     555,   558,   562,   565,   568,   572,   577,   585,   587,   591,
     592,   596,   600,   603,   605,   609,   611,   615,   616,   619,
     622,   625,   628,   631,   634,   637,   640,   643,   646,   651,
     652,   654,   655,   657,   659,   661,   663,   665,   667,   669,
     671,   673,   675,   677,   679,   681,   684,   685,   692,   693,
     699,   702,   703,   710,   711,   717,   720,   727,   733,   735,
     740,   745,   746,   750,   751,   757,   761,   763,   767,   769,
     773,   776,   778,   782,   786,   788,   792,   796,   798,   803,
     809,   815,   816,   822,   824,   825,   828,   829,   830,   834,
     835,   840,   843,   846,   848,   852,   855,   856,   863,   865,
     869,   870,   875,   880,   882,   886,   888,   892,   893,   895,
     898,   900,   904,   906,   911,   915,   920,   921,   927,   929,
     930,   931,   935,   938,   941,   942,   948,   949,   956,   957,
     960,   961,   964,   970,   972,   974,   976,   978,   980,   981,
     984,   987,   988,   992,   993,   995,   997,  1001,  1006,  1011,
    1012,  1016,  1017,  1020,  1022
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     120,     0,    -1,   121,    10,    -1,   122,    -1,    -1,    -1,
     123,   125,   122,    -1,    80,   122,    -1,    -1,   172,    -1,
     213,    -1,    98,    74,   131,    73,    80,    -1,   109,    -1,
      -1,     3,    74,   126,   203,    73,   204,    80,    -1,   111,
      76,   125,    75,     3,    76,   122,    75,    -1,   112,    76,
     129,    75,     3,    76,   129,    75,    -1,   124,     1,    80,
      -1,     3,    -1,     7,    -1,   115,    74,     3,    73,    -1,
      -1,    81,    -1,   130,    -1,     3,    -1,    36,   129,    -1,
      36,    74,   208,    73,    -1,    37,   129,    -1,    37,    74,
     208,    73,    -1,    57,   129,    -1,    58,   129,    -1,    59,
     129,    -1,    63,   129,    -1,    66,   129,    -1,    62,   129,
      -1,    71,   129,    -1,   129,    71,    -1,    72,   129,    -1,
     129,    72,    -1,   129,    49,   127,    -1,   129,    50,   127,
      -1,    74,   153,    73,    -1,   149,    -1,   129,    74,   144,
      73,    -1,   103,    74,   129,    81,   208,    73,    -1,   129,
     150,    -1,   129,    83,   145,    79,   129,    -1,   129,    57,
     129,    -1,   129,    58,   129,    -1,   129,    59,   129,    -1,
     129,    60,   129,    -1,   129,    61,   129,    -1,   129,    67,
     129,    -1,   129,    68,   129,    -1,   129,    63,   129,    -1,
     129,    64,   129,    -1,   129,    65,   129,    -1,   129,    51,
     129,    -1,   129,    52,   129,    -1,   129,    53,   129,    -1,
     129,    54,   129,    -1,   129,    55,   129,    -1,   129,    56,
     129,    -1,   129,    69,   129,    -1,   129,    70,   129,    -1,
     129,    38,   129,    -1,   129,    39,   129,    -1,   129,    40,
     129,    -1,   129,    41,   129,    -1,   129,    42,   129,    -1,
     129,    43,   129,    -1,   129,    44,   129,    -1,   129,    45,
     129,    -1,   129,    46,   129,    -1,   129,    47,   129,    -1,
     129,    48,   129,    -1,    74,   208,    73,   129,    -1,    74,
     208,    73,    76,   138,    75,    -1,    67,     3,    -1,   114,
      74,     3,    73,    -1,     5,    -1,     6,    -1,   116,    -1,
       4,    -1,   131,    -1,   134,    -1,   133,    -1,     8,    -1,
     135,    -1,   133,   135,    -1,     9,    -1,   134,   135,    -1,
     134,     9,    -1,     8,    -1,   100,    -1,   101,    -1,   129,
      -1,    76,   138,    75,    -1,   139,    -1,   139,    81,   138,
      -1,    -1,   137,    -1,   141,   140,   136,    -1,   143,   136,
      -1,   136,    -1,    38,    -1,    -1,    50,   127,   142,    -1,
      77,   129,    78,   142,    -1,    77,   129,    82,   129,    78,
      -1,    -1,   141,    -1,   127,    79,    -1,    -1,   146,    -1,
      -1,   146,    -1,   129,    -1,   129,    81,   146,    -1,     1,
      81,   146,    -1,    -1,   146,    -1,    74,   146,    73,    -1,
      74,     1,    73,    -1,    74,   146,    73,    -1,    74,     1,
      73,    -1,    77,   146,    78,    -1,    77,     1,    78,    -1,
      -1,    76,   152,   156,   154,   155,    -1,   151,    75,    -1,
       1,   124,    75,    -1,    -1,    -1,   160,    -1,   161,   155,
      -1,   158,    -1,    -1,   102,   157,    80,   156,    -1,     3,
      -1,     3,    81,   157,    -1,     3,    79,    -1,   110,    74,
     131,    73,    -1,   109,    -1,   159,    -1,   159,   160,    -1,
     160,   162,    -1,   162,    -1,    80,    -1,   146,    80,    -1,
     153,    -1,   172,    -1,    94,   148,   161,    -1,    94,   148,
     161,    95,   161,    -1,    -1,    -1,    88,   163,   148,   164,
     161,    -1,    -1,    91,   165,   148,   161,    -1,    -1,    92,
     166,   161,    91,   148,    80,    -1,    -1,   170,   145,    80,
     145,    80,   145,   167,    73,   161,    -1,    -1,    -1,   170,
     168,   172,   145,    80,   145,    73,   169,   161,    -1,   158,
     161,    -1,    89,   129,    79,    -1,    89,   129,    82,   129,
      79,    -1,    90,    79,    -1,    87,    80,    -1,    87,   146,
      80,    -1,    84,    80,    -1,    85,    80,    -1,    86,     3,
      80,    -1,    86,    59,   146,    80,    -1,    98,   221,    74,
     131,   222,    73,    80,    -1,   107,    -1,     1,   124,    80,
      -1,    -1,    93,   171,    74,    -1,   175,   173,    80,    -1,
     175,    80,    -1,   174,    -1,   174,    81,   173,    -1,   191,
      -1,   191,    38,   136,    -1,    -1,   176,   177,    -1,    21,
     178,    -1,    28,   178,    -1,    29,   178,    -1,    35,   178,
      -1,    33,   178,    -1,    34,   178,    -1,   180,   179,    -1,
      97,   178,    -1,   220,   178,    -1,   113,    74,     3,    73,
      -1,    -1,   177,    -1,    -1,   177,    -1,    17,    -1,    11,
      -1,    26,    -1,    12,    -1,    13,    -1,    14,    -1,    18,
      -1,    25,    -1,    16,    -1,    15,    -1,    23,    -1,    24,
      -1,    20,   127,    -1,    -1,    20,   127,    76,   181,   185,
      75,    -1,    -1,    20,    76,   182,   185,    75,    -1,    22,
     127,    -1,    -1,    22,   127,    76,   183,   185,    75,    -1,
      -1,    22,    76,   184,   185,    75,    -1,    19,   127,    -1,
      19,   127,    76,   189,   128,    75,    -1,    19,    76,   189,
     128,    75,    -1,     7,    -1,    99,    74,   129,    73,    -1,
      99,    74,   208,    73,    -1,    -1,   175,    80,   185,    -1,
      -1,   175,   186,   187,    80,   185,    -1,     1,    80,   185,
      -1,   188,    -1,   188,    81,   187,    -1,   191,    -1,   191,
      79,   129,    -1,    79,   129,    -1,   190,    -1,   189,    81,
     190,    -1,   189,    81,     1,    -1,     3,    -1,     3,    38,
     129,    -1,   207,   192,   219,    -1,   127,    -1,    74,   218,
     191,    73,    -1,   192,    77,   218,   147,    78,    -1,   192,
      77,   218,     1,    78,    -1,    -1,   192,   194,   193,   195,
      73,    -1,    74,    -1,    -1,   199,   196,    -1,    -1,    -1,
      81,   197,    82,    -1,    -1,    81,   198,   199,   196,    -1,
     175,   191,    -1,   175,   209,    -1,   175,    -1,    74,   199,
      73,    -1,   207,   201,    -1,    -1,   192,    74,   202,   203,
      73,   204,    -1,     3,    -1,     3,    81,   203,    -1,    -1,
     175,   205,    80,    82,    -1,   175,   205,    80,   204,    -1,
     191,    -1,   191,    81,   205,    -1,     1,    -1,    59,   218,
     207,    -1,    -1,   206,    -1,   175,   209,    -1,   175,    -1,
     207,   210,   218,    -1,   206,    -1,    74,   218,   209,    73,
      -1,    74,     1,    73,    -1,   212,    77,   147,    78,    -1,
      -1,   212,   194,   211,   195,    73,    -1,   210,    -1,    -1,
      -1,   215,   214,   153,    -1,   175,   191,    -1,   175,   200,
      -1,    -1,     3,   194,   216,   195,    73,    -1,    -1,     3,
      74,   203,   217,    73,   204,    -1,    -1,   220,   218,    -1,
      -1,   220,   219,    -1,    98,    74,   131,    73,   218,    -1,
     108,    -1,    31,    -1,    32,    -1,    27,    -1,    30,    -1,
      -1,    27,   221,    -1,    31,   221,    -1,    -1,    79,   223,
     226,    -1,    -1,   224,    -1,   225,    -1,   224,    81,   225,
      -1,   131,    74,   129,    73,    -1,   131,    74,     1,    73,
      -1,    -1,    79,   223,   227,    -1,    -1,    79,   228,    -1,
     132,    -1,   132,    81,   228,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   775,   775,   777,   815,   816,   816,   901,   915,   919,
     920,   921,   926,   940,   939,  1006,  1012,  1017,  1025,  1027,
    1029,  1035,  1037,  1043,  1047,  1053,  1057,  1061,  1065,  1069,
    1073,  1077,  1081,  1085,  1089,  1093,  1097,  1101,  1105,  1109,
    1116,  1121,  1125,  1152,  1156,  1171,  1175,  1179,  1183,  1187,
    1191,  1195,  1199,  1203,  1207,  1211,  1215,  1219,  1223,  1227,
    1231,  1235,  1239,  1243,  1247,  1251,  1270,  1275,  1280,  1285,
    1290,  1295,  1300,  1305,  1310,  1315,  1320,  1325,  1330,  1334,
    1341,  1346,  1351,  1358,  1363,  1371,  1381,  1390,  1394,  1398,
    1405,  1409,  1413,  1421,  1422,  1424,  1429,  1438,  1445,  1449,
    1455,  1456,  1459,  1463,  1467,  1470,  1474,  1479,  1481,  1483,
    1487,  1488,  1492,  1499,  1500,  1505,  1507,  1512,  1518,  1524,
    1531,  1532,  1536,  1543,  1549,  1557,  1564,  1568,  1578,  1577,
    1593,  1598,  1604,  1611,  1612,  1618,  1623,  1627,  1628,  1633,
    1634,  1638,  1648,  1656,  1664,  1668,  1676,  1686,  1694,  1707,
    1728,  1729,  1751,  1761,  1771,  1777,  1770,  1793,  1792,  1808,
    1807,  1826,  1820,  1837,  1848,  1836,  1858,  1869,  1873,  1877,
    1881,  1909,  1962,  1966,  1970,  1975,  1979,  1997,  1999,  2008,
    2007,  2037,  2088,  2114,  2119,  2126,  2135,  2157,  2157,  2219,
    2228,  2250,  2257,  2265,  2273,  2282,  2335,  2341,  2353,  2363,
    2368,  2377,  2396,  2402,  2407,  2413,  2419,  2429,  2439,  2449,
    2472,  2477,  2483,  2510,  2529,  2547,  2582,  2581,  2618,  2617,
    2644,  2671,  2670,  2693,  2692,  2721,  2761,  2776,  2789,  2812,
    2816,  2825,  2826,  2857,  2856,  2899,  2906,  2911,  2919,  2951,
    2965,  2987,  2993,  2999,  3006,  3031,  3084,  3114,  3181,  3194,
    3210,  3215,  3214,  3280,  3288,  3289,  3295,  3297,  3296,  3314,
    3313,  3324,  3335,  3347,  3357,  3363,  3373,  3372,  3403,  3407,
    3414,  3415,  3424,  3445,  3449,  3453,  3460,  3474,  3475,  3479,
    3493,  3503,  3510,  3538,  3546,  3551,  3557,  3556,  3576,  3578,
    3597,  3596,  3615,  3627,  3640,  3639,  3672,  3671,  3715,  3716,
    3725,  3726,  3728,  3740,  3743,  3747,  3751,  3755,  3871,  3872,
    3874,  3880,  3881,  3886,  3887,  3891,  3893,  3897,  3899,  3904,
    3905,  3910,  3911,  3915,  3917
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TK_IDENT", "TK_CHARCON", "TK_INTCON",
  "TK_FLOATCON", "TK_NAMED_TYPE", "TK_STRINGCON", "TK_WSTRINGCON",
  "TK_EOF", "TK_CHAR", "TK_INT", "TK_INT128", "TK_UINT128", "TK_DOUBLE",
  "TK_FLOAT", "TK_VOID", "TK_COMPLEX", "TK_ENUM", "TK_STRUCT",
  "TK_TYPEDEF", "TK_UNION", "TK_SIGNED", "TK_UNSIGNED", "TK_LONG",
  "TK_SHORT", "TK_VOLATILE", "TK_EXTERN", "TK_STATIC",
  "TK_STATIC_DIMENSION", "TK_CONST", "TK_RESTRICT", "TK_AUTO",
  "TK_REGISTER", "TK_THREAD", "TK_SIZEOF", "TK_ALIGNOF", "TK_EQ",
  "TK_PLUS_EQ", "TK_MINUS_EQ", "TK_STAR_EQ", "TK_SLASH_EQ",
  "TK_PERCENT_EQ", "TK_AND_EQ", "TK_PIPE_EQ", "TK_CIRC_EQ",
  "TK_INF_INF_EQ", "TK_SUP_SUP_EQ", "TK_ARROW", "TK_DOT", "TK_EQ_EQ",
  "TK_EXCLAM_EQ", "TK_INF", "TK_SUP", "TK_INF_EQ", "TK_SUP_EQ", "TK_PLUS",
  "TK_MINUS", "TK_STAR", "TK_SLASH", "TK_PERCENT", "TK_TILDE", "TK_AND",
  "TK_PIPE", "TK_CIRC", "TK_EXCLAM", "TK_AND_AND", "TK_PIPE_PIPE",
  "TK_INF_INF", "TK_SUP_SUP", "TK_PLUS_PLUS", "TK_MINUS_MINUS",
  "TK_RPAREN", "TK_LPAREN", "TK_RBRACE", "TK_LBRACE", "TK_LBRACKET",
  "TK_RBRACKET", "TK_COLON", "TK_SEMICOLON", "TK_COMMA", "TK_ELLIPSIS",
  "TK_QUEST", "TK_BREAK", "TK_CONTINUE", "TK_GOTO", "TK_RETURN",
  "TK_SWITCH", "TK_CASE", "TK_DEFAULT", "TK_WHILE", "TK_DO", "TK_FOR",
  "TK_IF", "TK_ELSE", "TK_ATTRIBUTE", "TK_INLINE", "TK_ASM", "TK_TYPEOF",
  "TK_FUNCTION__", "TK_PRETTY_FUNCTION__", "TK_LABEL__",
  "TK_BUILTIN_VA_ARG", "TK_BUILTIN_VA_LIST", "TK_BLOCKATTRIBUTE",
  "TK_DECLSPEC", "TK_MSASM", "TK_MSATTR", "TK_PRAGMA", "TK__Pragma",
  "TK_AT_TRANSFORM", "TK_AT_TRANSFORMEXPR", "TK_AT_SPECIFIER",
  "TK_AT_EXPR", "TK_AT_NAME", "TK_COMPLEXCON", "TK_CAST", "TK_ADDROF",
  "$accept", "interpret", "file", "globals", "$@1", "location", "global",
  "$@2", "id_or_typename", "maybecomma", "expression", "constant",
  "string_constant", "one_string_constant", "string_list", "wstring_list",
  "one_string", "init_expression", "initializer_list",
  "initializer_list_opt", "initializer", "eq_opt", "init_designators",
  "init_designators_opt", "gcc_init_designators", "arguments",
  "opt_expression", "comma_expression", "comma_expression_opt",
  "statement_paren_comma_expression", "paren_comma_expression",
  "bracket_comma_expression", "statements_inside_block", "$@3", "block",
  "block_attrs", "statement_list", "local_labels", "local_label_names",
  "label", "pragma", "pragmas", "statement", "statement_without_pragma",
  "$@4", "$@5", "$@6", "$@7", "$@8", "$@9", "$@10", "for_clause", "$@11",
  "declaration", "init_declarator_list", "init_declarator",
  "decl_spec_list", "$@12", "my_decl_spec_list", "decl_spec_list_opt",
  "decl_spec_list_opt_no_named", "type_spec", "$@13", "$@14", "$@15",
  "$@16", "struct_decl_list", "$@17", "field_decl_list", "field_decl",
  "enum_list", "enumerator", "declarator", "direct_decl", "$@18",
  "parameter_list_startscope", "rest_par_list", "rest_par_list1", "$@19",
  "$@20", "parameter_decl", "old_proto_decl", "direct_old_proto_decl",
  "$@21", "old_parameter_list_ne", "old_pardef_list", "old_pardef",
  "pointer", "pointer_opt", "type_name", "abstract_decl",
  "abs_direct_decl", "$@22", "abs_direct_decl_opt", "function_def", "$@23",
  "function_def_start", "$@24", "$@25", "attributes",
  "attributes_with_asm", "attribute", "asmattr", "asmoutputs",
  "asmoperands", "asmoperandsne", "asmoperand", "asminputs", "asmclobber",
  "asmcloberlst_ne", YY_NULL
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
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,   367,   368,   369,   370,   371,   372,   373
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   119,   120,   121,   122,   123,   122,   122,   124,   125,
     125,   125,   125,   126,   125,   125,   125,   125,   127,   127,
     127,   128,   128,   129,   129,   129,   129,   129,   129,   129,
     129,   129,   129,   129,   129,   129,   129,   129,   129,   129,
     129,   129,   129,   129,   129,   129,   129,   129,   129,   129,
     129,   129,   129,   129,   129,   129,   129,   129,   129,   129,
     129,   129,   129,   129,   129,   129,   129,   129,   129,   129,
     129,   129,   129,   129,   129,   129,   129,   129,   129,   129,
     130,   130,   130,   130,   130,   130,   131,   132,   133,   133,
     134,   134,   134,   135,   135,   135,   136,   136,   137,   137,
     138,   138,   139,   139,   139,   140,   140,   141,   141,   141,
     142,   142,   143,   144,   144,   145,   145,   146,   146,   146,
     147,   147,   148,   148,   149,   149,   150,   150,   152,   151,
     153,   153,   154,   155,   155,   155,   155,   156,   156,   157,
     157,   158,   159,   159,   160,   160,   161,   161,   162,   162,
     162,   162,   162,   162,   163,   164,   162,   165,   162,   166,
     162,   167,   162,   168,   169,   162,   162,   162,   162,   162,
     162,   162,   162,   162,   162,   162,   162,   162,   162,   171,
     170,   172,   172,   173,   173,   174,   174,   176,   175,   177,
     177,   177,   177,   177,   177,   177,   177,   177,   177,   178,
     178,   179,   179,   180,   180,   180,   180,   180,   180,   180,
     180,   180,   180,   180,   180,   180,   181,   180,   182,   180,
     180,   183,   180,   184,   180,   180,   180,   180,   180,   180,
     180,   185,   185,   186,   185,   185,   187,   187,   188,   188,
     188,   189,   189,   189,   190,   190,   191,   192,   192,   192,
     192,   193,   192,   194,   195,   195,   196,   197,   196,   198,
     196,   199,   199,   199,   199,   200,   202,   201,   203,   203,
     204,   204,   204,   205,   205,   205,   206,   207,   207,   208,
     208,   209,   209,   210,   210,   210,   211,   210,   212,   212,
     214,   213,   215,   215,   216,   215,   217,   215,   218,   218,
     219,   219,   219,   220,   220,   220,   220,   220,   221,   221,
     221,   222,   222,   223,   223,   224,   224,   225,   225,   226,
     226,   227,   227,   228,   228
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     1,     0,     0,     3,     2,     0,     1,
       1,     5,     1,     0,     7,     8,     8,     3,     1,     1,
       4,     0,     1,     1,     1,     2,     4,     2,     4,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     3,
       3,     3,     1,     4,     6,     2,     5,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     4,     6,     2,     4,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       1,     2,     2,     1,     1,     1,     1,     3,     1,     3,
       0,     1,     3,     2,     1,     1,     0,     3,     4,     5,
       0,     1,     2,     0,     1,     0,     1,     1,     3,     3,
       0,     1,     3,     3,     3,     3,     3,     3,     0,     5,
       2,     3,     0,     0,     1,     2,     1,     0,     4,     1,
       3,     2,     4,     1,     1,     2,     2,     1,     1,     2,
       1,     1,     3,     5,     0,     0,     5,     0,     4,     0,
       6,     0,     9,     0,     0,     9,     2,     3,     5,     2,
       2,     3,     2,     2,     3,     4,     7,     1,     3,     0,
       3,     3,     2,     1,     3,     1,     3,     0,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     4,     0,
       1,     0,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     0,     6,     0,     5,
       2,     0,     6,     0,     5,     2,     6,     5,     1,     4,
       4,     0,     3,     0,     5,     3,     1,     3,     1,     3,
       2,     1,     3,     3,     1,     3,     3,     1,     4,     5,
       5,     0,     5,     1,     0,     2,     0,     0,     3,     0,
       4,     2,     2,     1,     3,     2,     0,     6,     1,     3,
       0,     4,     4,     1,     3,     1,     3,     0,     1,     2,
       1,     3,     1,     4,     3,     4,     0,     5,     1,     0,
       0,     3,     2,     2,     0,     5,     0,     6,     0,     2,
       0,     2,     5,     1,     1,     1,     1,     1,     0,     2,
       2,     0,     3,     0,     1,     1,     3,     4,     4,     0,
       3,     0,     2,     1,     3
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       5,     5,     0,     0,     3,   187,     7,     1,     2,     0,
       0,    12,     0,     0,     0,     5,     9,   277,     0,    10,
     290,   253,   294,     0,   187,     0,     0,     6,   298,   182,
       0,   183,   185,   293,   278,     0,   228,   204,   206,   207,
     208,   212,   211,   203,   209,     0,     0,   199,     0,   213,
     214,   210,   205,   306,   199,   199,   307,   304,   305,   199,
     199,   199,   199,     0,   303,     0,   188,   201,   199,     0,
     268,     0,   296,   187,    93,    94,    95,     0,    86,    88,
       0,    24,    83,    80,    81,    90,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      82,     0,    23,    84,    85,    42,    17,   277,   298,   181,
     277,     0,    18,    19,   298,     0,   247,   300,   265,     0,
     225,   218,   215,   200,   189,   223,   220,   190,   191,   193,
     194,   192,   196,   187,     0,   202,   195,   197,     8,   128,
       0,   291,     0,     0,     0,   187,   277,     0,   256,     0,
      89,     0,     0,    25,     0,    27,    29,    30,    31,    34,
      32,    33,    78,    35,    37,     8,   117,     0,     0,   277,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    36,    38,     0,     0,     0,     0,
      45,    92,    91,   276,   299,   184,   185,     0,   100,    96,
     186,   277,     0,   253,   298,     0,   251,   246,   300,   244,
      21,   241,     0,     0,   216,     0,   221,     0,     0,     0,
       0,   137,   130,   269,   187,   187,     0,   261,   278,   289,
     262,   295,   259,   255,    11,     0,     0,     0,   125,     0,
       0,   124,    41,   289,   279,     0,     0,     0,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    39,
      40,    57,    58,    59,    60,    61,    62,    47,    48,    49,
      50,    51,    54,    55,    56,    52,    53,    63,    64,     0,
       0,   114,     0,     0,     0,     0,   116,   300,    24,     0,
       0,     0,   104,   101,     0,    98,   106,     0,     0,     0,
       0,     0,     0,   187,   301,     0,     0,     0,    21,     0,
     233,     0,     0,     0,     0,   229,   230,   198,   131,     0,
     132,     0,     0,   297,   264,     0,   288,     0,     0,   187,
       5,    26,    28,   119,   118,     0,   100,    76,   187,    79,
      43,     0,   127,   126,     0,   253,   110,     0,   112,    97,
     100,   105,     0,   103,   248,    20,     0,     0,   121,     0,
       0,     0,   245,   243,   242,   227,     0,     0,     0,   277,
     219,     0,   224,     0,   139,     0,     0,   275,   273,     0,
      14,     0,   277,   281,     0,   286,   258,   256,     0,   277,
       0,     0,     0,    46,   111,   107,   110,     0,    99,   102,
     187,   250,   249,   298,   252,   226,   235,   232,     0,     0,
     236,   238,   217,   222,     0,   137,     8,    24,   148,     0,
       0,     0,     0,   154,     0,     0,   157,   159,   179,     0,
     308,   177,   143,     0,     0,   150,   129,     0,   144,     0,
       0,   147,     0,   151,   277,     0,   187,   284,     0,     0,
     187,   260,    15,    77,    44,    16,   108,     0,   267,   302,
     240,     0,   277,     0,   140,   138,     0,   141,   172,   173,
       0,     0,   170,     0,     0,     0,   169,     0,     0,     0,
       0,     0,   308,   308,     0,     0,   149,     0,     0,   166,
     145,   146,   135,     0,   187,   274,   271,   272,   283,   285,
       0,   109,   234,   237,   239,   178,   174,     0,   171,   155,
     167,     0,     0,     0,   180,     0,     0,   152,   309,   310,
       0,     0,     0,     0,   287,   175,     0,     0,   158,     0,
     123,   122,     0,   311,   142,     0,     0,   156,   168,     0,
     153,   313,     0,     0,     0,   160,     0,   319,   314,   315,
       0,   161,     0,     0,   313,   312,     0,   176,     0,   164,
       0,     0,   321,   316,     0,     0,   318,   317,     0,   320,
     162,   165,    87,   323,   322,     0,   324
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     4,     5,    14,    15,    71,   116,   327,
     166,   102,   103,   593,    78,   104,    79,   312,   313,   314,
     315,   372,   316,   415,   317,   300,   305,   454,   379,   501,
     105,   210,   140,   241,   455,   396,   456,   340,   395,   507,
     458,   508,   460,   461,   494,   546,   497,   498,   578,   514,
     585,   462,   499,   463,    30,    31,   464,    18,   123,   124,
     136,    67,   332,   233,   334,   235,   331,   389,   429,   430,
     230,   231,   216,   307,   323,   226,   147,   253,   348,   349,
     148,    33,   118,   320,    72,   342,   399,    34,   217,   170,
     468,   346,   470,   347,    19,    69,    20,    73,   144,   107,
     227,    68,   504,   562,   567,   568,   569,   575,   589,   594
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -445
static const yytype_int16 yypact[] =
{
      46,   170,    42,    60,  -445,    90,  -445,  -445,  -445,     3,
      18,  -445,    65,    69,   180,   170,  -445,    26,  2435,  -445,
    -445,   115,  -445,    43,    90,  2210,   123,  -445,   288,  -445,
     125,   137,    72,  -445,  -445,    15,  -445,  -445,  -445,  -445,
    -445,  -445,  -445,  -445,  -445,    22,   114,  2435,   117,  -445,
    -445,  -445,  -445,  -445,  2435,  2435,  -445,  -445,  -445,  2435,
    2435,  2435,  2435,   154,  -445,   185,  -445,  2538,  2435,    25,
     190,   115,  -445,   175,  -445,  -445,  -445,   199,    43,  -445,
     187,  -445,  -445,  -445,  -445,  -445,  2282,  2300,  2210,  2210,
    2210,  2210,  2210,  2210,   276,  2210,  2210,  1150,   207,   208,
    -445,  2660,  -445,  -445,    11,  -445,  -445,   226,   288,  -445,
     226,  2062,  -445,  -445,   288,   214,  -445,   273,  -445,   287,
     218,  -445,   222,  -445,  -445,  -445,   230,  -445,  -445,  -445,
    -445,  -445,  -445,  2210,   304,  -445,  -445,  -445,  -445,  -445,
     235,  -445,   115,   240,   243,   248,   150,   244,   257,   261,
    -445,   321,  1150,   262,  1150,   262,   262,   262,   262,   262,
     262,   262,  -445,   262,   262,   119,  2706,   272,   278,    17,
     283,  2210,   346,  2210,  2210,  2210,  2210,  2210,  2210,  2210,
    2210,  2210,  2210,  2210,    76,    76,  2210,  2210,  2210,  2210,
    2210,  2210,  2210,  2210,  2210,  2210,  2210,  2210,  2210,  2210,
    2210,  2210,  2210,  2210,  -445,  -445,  1345,   354,  1828,  1419,
    -445,  -445,  -445,  -445,  -445,  -445,   320,    15,   442,  3028,
    -445,   226,   356,   357,   288,   290,  -445,  -445,   265,   327,
     285,  -445,   287,  2406,  -445,  2406,  -445,  2752,   294,   297,
     299,   270,  -445,  -445,   295,    27,   303,  -445,   143,   124,
    -445,  -445,   296,  -445,  -445,   301,   310,   311,  -445,  1900,
    1900,  -445,  -445,   313,  -445,  2136,  2798,   312,  3028,  3028,
    3028,  3028,  3028,  3028,  3028,  3028,  3028,  3028,  3028,  -445,
    -445,  1789,  1789,  2097,  2097,  2097,  2097,   363,   363,   262,
     262,   262,  1380,  2439,  1185,  3127,  3098,  1641,  1641,   308,
     317,  -445,   315,   -21,   319,   316,  -445,   454,   323,    76,
    2210,   326,  -445,  -445,   324,   333,   360,  2062,   334,   335,
     115,  1491,    43,   175,  -445,  2210,   122,   325,   285,   336,
     338,   340,  2406,   344,  2406,  -445,  -445,  -445,  -445,   418,
    -445,    45,   345,  -445,  -445,   379,   183,   181,   347,   248,
     171,  1680,  1680,  -445,  -445,   206,   442,   262,  -445,  -445,
    -445,  2210,  -445,  -445,  2210,  -445,     4,  2536,  -445,  -445,
     442,  -445,  2062,  -445,  -445,  -445,   355,   189,  -445,   349,
     358,   366,  3028,  -445,  -445,  -445,   361,  2406,  2406,   -18,
    -445,   367,  -445,   369,   352,   350,   580,  -445,   371,   374,
    -445,   384,   226,  -445,  1509,  -445,  -445,   257,   385,   226,
     386,   389,  2844,  3063,  -445,  -445,     4,  2210,  -445,  -445,
      27,  -445,  -445,   288,  -445,  -445,  -445,  -445,  2210,   383,
     390,   387,  -445,  -445,   418,   270,   308,   391,  -445,   393,
     394,    36,  1592,  -445,  2210,   396,  -445,  -445,  -445,   402,
      28,  -445,  -445,   403,   400,  -445,  -445,   694,   159,   922,
     580,  -445,  1264,  -445,    26,    45,   145,  -445,   392,   405,
     175,  -445,  -445,  -445,  -445,  -445,  -445,  2890,  -445,  -445,
    3028,  2406,   -18,  2210,  -445,  -445,   177,  -445,  -445,  -445,
     408,  1900,  -445,   411,   402,  2614,  -445,   402,   808,   419,
    1918,   808,    28,    28,   421,    43,  -445,   808,  1036,  -445,
    -445,  -445,  -445,   422,  -445,  -445,  -445,  -445,  -445,  -445,
     425,  -445,  -445,  -445,  3028,  -445,  -445,   423,  -445,  -445,
    -445,  2210,   808,   373,  -445,   149,   433,   415,  -445,  -445,
      43,   439,  1673,  1673,  -445,  -445,   808,  2936,  -445,   402,
    -445,  -445,   808,   436,  -445,   440,   441,  -445,  -445,   443,
    -445,    43,   449,  1754,  1754,  -445,   450,   446,   445,  -445,
     447,  -445,   457,  1990,    43,  -445,    43,  -445,   459,  -445,
     460,  2982,   455,  -445,   808,   808,  -445,  -445,   527,  -445,
    -445,  -445,  -445,   456,  -445,   527,  -445
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -445,  -445,  -445,     2,  -445,  -134,   512,  -445,    -1,   211,
     -24,  -445,   -23,  -445,  -445,  -445,   -29,   -98,  -445,  -144,
    -445,  -445,  -342,   128,  -445,  -445,  -435,   -74,   136,  -444,
    -445,  -445,  -445,  -445,   -39,  -445,    81,   111,   113,  -364,
    -445,  -358,  -223,  -424,  -445,  -445,  -445,  -445,  -445,  -445,
    -445,  -445,  -445,    -3,   438,  -445,   109,  -445,    19,   505,
    -445,  -445,  -445,  -445,  -445,  -445,  -192,  -445,    68,  -445,
     322,   229,   -10,   526,  -445,    -4,  -283,   156,  -445,  -445,
    -129,  -445,  -445,  -445,   -60,  -231,   103,  -136,    -8,  -118,
     -30,  -445,  -445,  -445,  -445,  -445,  -445,  -445,  -445,  -102,
     341,   -20,  -226,  -445,    -2,  -445,    -6,  -445,  -445,   -19
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -299
static const yytype_int16 yytable[] =
{
      77,   101,    16,     6,   240,    22,   214,    32,   108,    35,
     248,   143,   221,   220,   343,   238,   246,    27,   112,    74,
     211,    16,   113,   167,   414,   112,   138,   513,  -270,   113,
     141,   240,   457,   248,   256,   511,   257,    66,   459,   490,
     381,    28,     7,   333,   120,   122,   397,   126,  -277,   150,
     529,    74,  -277,   532,   309,   502,    -4,   362,   168,   503,
     259,   428,   153,   155,   156,   157,   158,   159,   160,   161,
       8,   163,   164,  -292,   414,   212,    28,    21,   167,   112,
     167,   310,   243,   113,   511,    28,   135,   219,   108,   114,
    -280,    -8,    23,     9,   108,   491,   457,   228,   119,   213,
     510,   139,   459,  -270,    28,   559,    29,   555,   556,   237,
     111,    75,    76,   168,    17,   168,   250,   112,    70,  -277,
     112,   113,   321,   383,   113,   229,     1,   112,   571,   572,
     115,   113,   301,    17,   304,   306,   247,   115,   249,   264,
     391,    24,   393,    75,    76,    25,  -270,   266,  -292,   268,
     269,   270,   271,   272,   273,   274,   275,   276,   277,   278,
    -277,   263,   281,   282,   283,   284,   285,   286,   287,   288,
     289,   290,   291,   292,   293,   294,   295,   296,   297,   298,
      -4,    26,   146,   279,   280,   353,   354,   520,    10,   478,
     121,   115,   258,   125,   219,   426,   427,   -22,   345,    11,
     259,    12,    13,   106,   108,   109,   169,   401,   228,    28,
      53,   318,   410,    56,    57,    58,  -282,   311,   110,   373,
     407,  -270,   550,  -263,  -282,  -270,   418,   516,   133,   115,
     259,  -263,   115,    53,   509,   517,    56,    57,    58,   115,
     411,   357,   169,   402,   403,    -4,    -4,   378,  -254,   145,
       1,     1,   338,   409,   146,   365,  -298,   525,   404,   134,
     376,   169,   151,   169,  -298,  -298,   248,   421,   452,   453,
     259,   142,   149,   248,   419,   533,   538,   539,   537,   162,
    -298,   171,   172,  -298,   509,    28,   367,   228,   222,   522,
     229,    64,    53,   219,   232,    56,    57,    58,   234,   380,
      53,   382,   486,    56,    57,    58,   236,   239,   366,   548,
     242,   184,   185,   244,    64,    53,   245,   251,    56,    57,
      58,   479,   145,   557,   255,   108,   108,   357,   357,   560,
     378,   398,   219,   204,   205,   108,   206,   412,   252,   208,
     413,   254,   330,   405,   330,   261,   219,   223,   219,   267,
     224,   262,   408,   341,   341,   311,   265,   302,   111,   319,
    -266,   590,   591,   225,   322,   325,   326,   336,   493,   311,
     337,   225,   339,    64,   338,  -270,   344,   350,  -257,   431,
     401,    64,  -298,   351,   352,   359,  -298,   355,   306,   259,
     360,   361,   318,   477,   249,   364,    64,   363,   371,   369,
     385,   263,   -18,   108,   480,   368,    53,   374,   375,    56,
      57,    58,   184,   185,   370,   390,   387,   527,   388,   392,
     495,   394,   194,   195,   196,   400,   536,   422,   420,   406,
     435,   423,   146,   434,   204,   205,   425,   206,  -298,   424,
     208,   330,   432,   330,   433,   308,    82,    83,    84,   113,
      74,    85,   465,  -298,   466,   398,  -298,   467,   146,   524,
     472,   473,   474,   481,   549,   518,   483,   169,   306,   306,
     487,   482,   431,   488,   489,   496,   500,   505,    86,    87,
     506,    53,   541,   519,    56,    57,    58,    64,   526,   306,
     306,   528,   309,   534,  -298,   540,   330,   330,   544,    88,
      89,    90,   542,   545,    91,    92,   551,   547,    93,    94,
     552,   543,   554,    95,    96,   561,    97,   553,   218,   310,
     563,   564,   570,   565,   573,   574,   576,   577,   365,   341,
     579,   224,   584,   586,   588,   592,    80,   595,   566,   386,
     469,   512,    75,    76,   476,    98,   485,   484,   215,   581,
     523,   566,   225,   566,   328,   384,    99,   115,   100,   127,
     128,   117,    64,   471,   129,   130,   131,   132,   515,   324,
     583,     0,   582,   137,     0,   341,   596,     0,     0,   146,
       0,   436,     0,   437,    82,    83,    84,  -187,    74,    85,
     330,  -187,  -187,  -187,  -187,  -187,  -187,  -187,  -187,  -187,
    -187,  -187,  -187,  -187,  -187,  -187,  -187,  -187,  -187,  -187,
    -187,  -187,  -187,  -187,  -187,  -187,    86,    87,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    88,    89,    90,
       0,     0,    91,    92,     0,     0,    93,    94,     0,     0,
       0,    95,    96,     0,    97,  -133,   139,     0,     0,     0,
     438,     0,     0,     0,   439,   440,   441,   442,   443,   444,
     445,   446,   447,   448,   449,     0,     0,  -187,   450,  -187,
      75,    76,     0,    98,     0,     0,     0,   451,  -187,   452,
     453,     0,     0,  -187,    99,   436,   100,   437,    82,    83,
      84,  -187,    74,    85,     0,  -187,  -187,  -187,  -187,  -187,
    -187,  -187,  -187,  -187,  -187,  -187,  -187,  -187,  -187,  -187,
    -187,  -187,  -187,  -187,  -187,  -187,  -187,  -187,  -187,  -187,
      86,    87,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    88,    89,    90,     0,     0,    91,    92,     0,     0,
      93,    94,     0,     0,     0,    95,    96,     0,    97,  -136,
     139,     0,     0,     0,   438,     0,     0,     0,   439,   440,
     441,   442,   443,   444,   445,   446,   447,   448,   449,     0,
       0,  -187,   450,  -187,    75,    76,     0,    98,     0,     0,
       0,   451,  -187,   452,   453,     0,     0,  -187,    99,   436,
     100,   437,    82,    83,    84,  -187,    74,    85,     0,  -187,
    -187,  -187,  -187,  -187,  -187,  -187,  -187,  -187,  -187,  -187,
    -187,  -187,  -187,  -187,  -187,  -187,  -187,  -187,  -187,  -187,
    -187,  -187,  -187,  -187,    86,    87,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    88,    89,    90,     0,     0,
      91,    92,     0,     0,    93,    94,     0,     0,     0,    95,
      96,     0,    97,     0,   139,     0,     0,     0,   438,     0,
       0,     0,   439,   440,   441,   442,   443,   444,   445,   446,
     447,   448,   449,     0,     0,  -187,   450,  -187,    75,    76,
       0,    98,     0,     0,     0,   451,  -187,   452,   453,     0,
       0,  -187,    99,   436,   100,   437,    82,    83,    84,  -187,
      74,    85,     0,  -187,  -187,  -187,  -187,  -187,  -187,  -187,
    -187,  -187,  -187,  -187,  -187,  -187,  -187,  -187,  -187,  -187,
    -187,  -187,  -187,  -187,  -187,  -187,  -187,  -187,    86,    87,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    88,
      89,    90,     0,     0,    91,    92,     0,     0,    93,    94,
       0,     0,     0,    95,    96,     0,    97,  -134,   139,     0,
       0,     0,   438,     0,     0,     0,   439,   440,   441,   442,
     443,   444,   445,   446,   447,   448,   449,     0,     0,  -187,
     450,  -187,    75,    76,     0,    98,     0,     0,     0,   451,
    -187,     0,     0,     0,     0,  -187,    99,   436,   100,   437,
      82,    83,    84,  -187,    74,    85,     0,  -187,  -187,  -187,
    -187,  -187,  -187,  -187,  -187,  -187,  -187,  -187,  -187,  -187,
    -187,  -187,  -187,  -187,  -187,  -187,  -187,  -187,  -187,  -187,
    -187,  -187,    86,    87,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    88,    89,    90,     0,     0,    91,    92,
       0,     0,    93,    94,     0,     0,     0,    95,    96,     0,
      97,     0,   139,     0,     0,     0,   438,     0,     0,     0,
     439,   440,   441,   442,   443,   444,   445,   446,   447,   448,
     449,     0,     0,  -187,   450,  -187,    75,    76,     0,    98,
       0,     0,     0,   451,  -187,     0,     0,     0,     0,  -187,
      99,   165,   100,    81,    82,    83,    84,  -187,    74,    85,
       0,  -187,  -187,  -187,  -187,  -187,  -187,  -187,  -187,  -187,
    -187,  -187,  -187,  -187,  -187,  -187,  -187,  -187,  -187,  -187,
    -187,  -187,  -187,  -187,  -187,  -187,    86,    87,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    88,    89,    90,
       0,     0,    91,    92,     0,     0,    93,    94,     0,     0,
       0,    95,    96,     0,    97,     0,   139,     0,     0,     0,
       0,     0,     0,     0,   184,   185,   186,   187,   188,   189,
     190,   191,   192,   193,   194,   195,   196,  -187,   197,  -187,
      75,    76,     0,    98,   202,   203,   204,   205,  -187,   206,
       0,     0,   208,  -187,    99,   299,   100,    81,    82,    83,
      84,  -163,    74,    85,     0,  -163,  -163,  -163,  -163,  -163,
    -163,  -163,  -163,  -163,  -163,  -163,  -163,  -163,  -163,  -163,
    -163,  -163,  -163,  -163,  -163,  -163,  -163,  -163,  -163,  -163,
      86,    87,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    88,    89,    90,     0,     0,    91,    92,     0,     0,
      93,    94,     0,     0,     0,    95,    96,     0,    97,     0,
       0,     0,     0,     0,  -115,     0,   299,     0,    81,    82,
      83,    84,     0,    74,    85,     0,     0,     0,     0,     0,
       0,  -163,     0,  -163,    75,    76,     0,    98,     0,     0,
       0,     0,  -163,     0,     0,     0,     0,  -163,    99,     0,
     100,    86,    87,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    88,    89,    90,     0,     0,    91,    92,     0,
       0,    93,    94,     0,     0,     0,    95,    96,  -113,    97,
     299,     0,    81,    82,    83,    84,     0,    74,    85,   184,
     185,   186,   187,   188,   189,   190,   191,   192,   193,   194,
     195,   196,     0,     0,     0,    75,    76,     0,    98,   202,
     203,   204,   205,     0,   206,    86,    87,   208,     0,    99,
       0,   100,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    88,    89,    90,     0,
       0,    91,    92,     0,     0,    93,    94,     0,     0,     0,
      95,    96,   377,    97,    81,    82,    83,    84,  -115,    74,
      85,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     299,     0,    81,    82,    83,    84,     0,    74,    85,    75,
      76,     0,    98,     0,     0,     0,     0,    86,    87,     0,
       0,     0,     0,    99,     0,   100,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    86,    87,     0,    88,    89,
      90,     0,     0,    91,    92,     0,     0,    93,    94,     0,
       0,     0,    95,    96,     0,    97,    88,    89,    90,  -120,
       0,    91,    92,     0,     0,    93,    94,     0,     0,     0,
      95,    96,     0,    97,     0,     0,     0,  -120,     0,     0,
       0,    75,    76,   299,    98,    81,    82,    83,    84,     0,
      74,    85,     0,     0,     0,    99,     0,   100,     0,    75,
      76,     0,    98,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    99,     0,   100,     0,     0,    86,    87,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    88,
      89,    90,     0,     0,    91,    92,     0,     0,    93,    94,
       0,     0,     0,    95,    96,     0,    97,     0,     0,     0,
       0,     0,   492,     0,   299,     0,    81,    82,    83,    84,
       0,    74,    85,    81,    82,    83,    84,     0,    74,    85,
     184,   185,    75,    76,     0,    98,     0,     0,   192,   193,
     194,   195,   196,     0,     0,     0,    99,     0,   100,    86,
      87,     0,   204,   205,     0,   206,    86,    87,   208,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      88,    89,    90,     0,     0,    91,    92,     0,     0,    93,
      94,     0,    91,     0,    95,    96,    93,    97,     0,     0,
       0,    95,    96,  -115,    97,   299,   356,    81,    82,    83,
      84,     0,    74,    85,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    75,    76,     0,    98,     0,     0,     0,
      75,    76,     0,    98,     0,     0,     0,    99,     0,   100,
      86,    87,     0,     0,    99,     0,   100,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    88,    89,    90,     0,     0,    91,    92,     0,     0,
      93,    94,     0,     0,     0,    95,    96,  -115,    97,   303,
       0,    81,    82,    83,    84,     0,    74,    85,   184,   185,
       0,     0,   188,   189,   190,   191,   192,   193,   194,   195,
     196,     0,     0,     0,    75,    76,     0,    98,   202,   203,
     204,   205,     0,   206,    86,    87,   208,     0,    99,     0,
     100,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    88,    89,    90,     0,     0,
      91,    92,     0,     0,    93,    94,     0,     0,     0,    95,
      96,   299,    97,    81,    82,    83,    84,     0,    74,    85,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   535,
       0,    81,    82,    83,    84,     0,    74,    85,    75,    76,
       0,    98,     0,     0,     0,     0,    86,    87,     0,     0,
       0,     0,    99,     0,   100,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    86,    87,     0,    88,    89,    90,
       0,     0,    91,    92,     0,     0,    93,    94,     0,     0,
       0,    95,    96,     0,    97,    88,    89,    90,     0,     0,
      91,    92,     0,     0,    93,    94,     0,     0,     0,    95,
      96,   580,    97,    81,    82,    83,    84,     0,    74,    85,
      75,    76,     0,    98,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    99,     0,   100,     0,    75,    76,
       0,    98,     0,     0,     0,     0,    86,    87,     0,     0,
       0,     0,    99,     0,   100,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    88,    89,    90,
       0,     0,    91,    92,     0,     0,    93,    94,     0,     0,
       0,    95,    96,     0,    97,    81,    82,    83,    84,     0,
      74,    85,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      75,    76,     0,    98,     0,     0,     0,     0,    86,    87,
       0,     0,     0,     0,    99,     0,   100,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    88,
      89,    90,     0,     0,    91,    92,     0,     0,    93,    94,
       0,     0,     0,    95,    96,     0,    97,     0,   218,    81,
      82,    83,    84,     0,    74,    85,   184,   185,     0,     0,
       0,     0,     0,     0,   192,   193,   194,   195,   196,     0,
       0,     0,    75,    76,     0,    98,   202,   203,   204,   205,
       0,   206,    86,    87,   208,     0,    99,     0,   100,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    88,    89,    90,     0,     0,    91,    92,
       0,     0,    93,    94,     0,     0,     0,    95,    96,     0,
      97,     0,   356,    81,    82,    83,    84,     0,    74,    85,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    75,    76,     0,    98,
       0,     0,     0,     0,     0,     0,    86,    87,     0,     0,
      99,     0,   100,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    88,    89,    90,
       0,     0,    91,    92,     0,     0,    93,    94,     0,     0,
       0,    95,    96,     0,    97,    81,    82,    83,    84,     0,
      74,    85,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    81,    82,    83,    84,     0,    74,    85,
      75,    76,     0,    98,     0,     0,     0,     0,    86,    87,
       0,     0,     0,     0,    99,     0,   100,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    86,    87,     0,    88,
      89,    90,     0,     0,    91,    92,     0,     0,    93,    94,
       0,     0,     0,    95,    96,     0,   152,    88,    89,    90,
       0,     0,    91,    92,     0,     0,    93,    94,     0,     0,
       0,    95,    96,     0,   154,     0,     0,     0,     0,     0,
       0,     0,    75,    76,     0,    98,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    99,     0,   100,     0,
      75,    76,     0,    98,     0,     0,     0,   329,     0,     0,
       0,     0,     0,  -187,    99,     0,   100,  -187,  -187,  -187,
    -187,  -187,  -187,  -187,  -187,  -187,  -187,  -187,  -187,  -187,
    -187,  -187,  -187,  -187,  -187,  -187,  -187,  -187,  -187,  -187,
    -187,  -187,    36,     0,     0,     0,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  -231,     0,     0,     0,     0,     0,     0,   184,   185,
     186,   187,   188,   189,   190,   191,   192,   193,   194,   195,
     196,     0,   197,  -187,   199,  -187,     0,     0,   202,   203,
     204,   205,     0,   206,  -187,     0,   208,     0,     0,  -187,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    62,     0,    63,     0,     0,     0,     0,     0,
       0,     0,     0,    64,     0,     0,     0,     0,    65,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,   173,   174,   175,   176,   177,   178,
     179,   180,   181,   182,   183,   184,   185,   186,   187,   188,
     189,   190,   191,   192,   193,   194,   195,   196,     0,   197,
     198,   199,     0,   200,   201,   202,   203,   204,   205,     0,
     206,     0,     0,   208,   416,     0,     0,     0,   417,   209,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    62,     0,    63,     0,     0,
       0,     0,     0,     0,     0,     0,    64,     0,     0,     0,
       0,    65,   173,   174,   175,   176,   177,   178,   179,   180,
     181,   182,   183,   184,   185,   186,   187,   188,   189,   190,
     191,   192,   193,   194,   195,   196,     0,   197,   198,   199,
       0,   200,   201,   202,   203,   204,   205,     0,   206,     0,
       0,   208,     0,   530,     0,     0,   531,   209,   173,   174,
     175,   176,   177,   178,   179,   180,   181,   182,   183,   184,
     185,   186,   187,   188,   189,   190,   191,   192,   193,   194,
     195,   196,     0,   197,   198,   199,     0,   200,   201,   202,
     203,   204,   205,     0,   206,   207,     0,   208,     0,     0,
       0,     0,     0,   209,   173,   174,   175,   176,   177,   178,
     179,   180,   181,   182,   183,   184,   185,   186,   187,   188,
     189,   190,   191,   192,   193,   194,   195,   196,     0,   197,
     198,   199,     0,   200,   201,   202,   203,   204,   205,     0,
     206,     0,     0,   208,     0,     0,     0,   260,     0,   209,
     173,   174,   175,   176,   177,   178,   179,   180,   181,   182,
     183,   184,   185,   186,   187,   188,   189,   190,   191,   192,
     193,   194,   195,   196,     0,   197,   198,   199,     0,   200,
     201,   202,   203,   204,   205,   335,   206,     0,     0,   208,
       0,     0,     0,     0,     0,   209,   173,   174,   175,   176,
     177,   178,   179,   180,   181,   182,   183,   184,   185,   186,
     187,   188,   189,   190,   191,   192,   193,   194,   195,   196,
       0,   197,   198,   199,     0,   200,   201,   202,   203,   204,
     205,     0,   206,     0,     0,   208,     0,     0,     0,   358,
       0,   209,   173,   174,   175,   176,   177,   178,   179,   180,
     181,   182,   183,   184,   185,   186,   187,   188,   189,   190,
     191,   192,   193,   194,   195,   196,     0,   197,   198,   199,
       0,   200,   201,   202,   203,   204,   205,     0,   206,   475,
       0,   208,     0,     0,     0,     0,     0,   209,   173,   174,
     175,   176,   177,   178,   179,   180,   181,   182,   183,   184,
     185,   186,   187,   188,   189,   190,   191,   192,   193,   194,
     195,   196,     0,   197,   198,   199,     0,   200,   201,   202,
     203,   204,   205,     0,   206,     0,     0,   208,   521,     0,
       0,     0,     0,   209,   173,   174,   175,   176,   177,   178,
     179,   180,   181,   182,   183,   184,   185,   186,   187,   188,
     189,   190,   191,   192,   193,   194,   195,   196,     0,   197,
     198,   199,     0,   200,   201,   202,   203,   204,   205,     0,
     206,     0,     0,   208,     0,   558,     0,     0,     0,   209,
     173,   174,   175,   176,   177,   178,   179,   180,   181,   182,
     183,   184,   185,   186,   187,   188,   189,   190,   191,   192,
     193,   194,   195,   196,     0,   197,   198,   199,     0,   200,
     201,   202,   203,   204,   205,   587,   206,     0,     0,   208,
       0,     0,     0,     0,     0,   209,   173,   174,   175,   176,
     177,   178,   179,   180,   181,   182,   183,   184,   185,   186,
     187,   188,   189,   190,   191,   192,   193,   194,   195,   196,
       0,   197,   198,   199,     0,   200,   201,   202,   203,   204,
     205,     0,   206,     0,     0,   208,     0,     0,     0,     0,
       0,   209,   184,   185,   186,   187,   188,   189,   190,   191,
     192,   193,   194,   195,   196,     0,   197,   198,   199,     0,
     200,   201,   202,   203,   204,   205,     0,   206,     0,     0,
     208,     0,     0,     0,     0,     0,   209,   184,   185,   186,
     187,   188,   189,   190,   191,   192,   193,   194,   195,   196,
       0,   197,   198,   199,     0,   200,     0,   202,   203,   204,
     205,     0,   206,     0,     0,   208,   184,   185,   186,   187,
     188,   189,   190,   191,   192,   193,   194,   195,   196,     0,
     197,   198,   199,     0,     0,     0,   202,   203,   204,   205,
       0,   206,     0,     0,   208
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-445))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
      23,    25,     5,     1,   138,     9,   108,    17,    28,    17,
     146,    71,   114,   111,   245,   133,   145,    15,     3,     8,
       9,    24,     7,    97,   366,     3,     1,   462,     1,     7,
      69,   165,   396,   169,   152,   459,   154,    18,   396,     3,
     323,    59,     0,   235,    45,    46,     1,    48,     3,    78,
     494,     8,     7,   497,    50,    27,    10,    78,    97,    31,
      81,    79,    86,    87,    88,    89,    90,    91,    92,    93,
      10,    95,    96,     1,   416,   104,    59,    74,   152,     3,
     154,    77,   142,     7,   508,    59,    67,   111,   108,    74,
      73,     1,    74,     3,   114,    59,   460,   117,    76,   107,
     458,    76,   460,    76,    59,   549,    80,   542,   543,   133,
      38,   100,   101,   152,     5,   154,   146,     3,     3,    74,
       3,     7,   224,     1,     7,     3,    80,     3,   563,   564,
     115,     7,   206,    24,   208,   209,   146,   115,   146,   169,
     332,    76,   334,   100,   101,    76,     1,   171,    76,   173,
     174,   175,   176,   177,   178,   179,   180,   181,   182,   183,
     115,   169,   186,   187,   188,   189,   190,   191,   192,   193,
     194,   195,   196,   197,   198,   199,   200,   201,   202,   203,
      10,     1,    73,   184,   185,   259,   260,   470,    98,   420,
      76,   115,    73,    76,   218,   387,   388,    75,    74,   109,
      81,   111,   112,    80,   224,    80,    97,     1,   228,    59,
      27,   221,   356,    30,    31,    32,    73,   218,    81,   317,
     349,    76,    73,    73,    81,    80,   370,    82,    74,   115,
      81,    81,   115,    27,   457,   466,    30,    31,    32,   115,
     358,   265,   133,   345,   346,    75,    75,   321,    73,    74,
      80,    80,    75,   355,   145,    74,    73,    80,    77,    74,
     320,   152,    75,   154,    81,    59,   402,    78,   109,   110,
      81,    81,    73,   409,   372,   498,   502,   503,   501,     3,
      74,    74,    74,    77,   507,    59,   310,   307,    74,   481,
       3,   108,    27,   317,    76,    30,    31,    32,    76,   322,
      27,   325,   436,    30,    31,    32,    76,     3,   309,   532,
      75,    49,    50,    73,   108,    27,    73,    73,    30,    31,
      32,   423,    74,   546,     3,   345,   346,   351,   352,   552,
     404,   341,   356,    71,    72,   355,    74,   361,    81,    77,
     364,    80,   233,   347,   235,    73,   370,    74,   372,     3,
      77,    73,   350,   244,   245,   356,    73,     3,    38,     3,
       3,   584,   585,    98,    74,    38,    81,    73,   442,   370,
      73,    98,   102,   108,    75,    80,    73,    76,    82,   389,
       1,   108,     3,    73,    73,    73,     7,    74,   462,    81,
      73,    76,   402,   417,   402,    79,   108,    78,    38,    75,
      75,   409,    79,   423,   428,    79,    27,    73,    73,    30,
      31,    32,    49,    50,    81,    75,    80,   491,    80,    75,
     444,     3,    59,    60,    61,    80,   500,    78,    73,    82,
      80,    73,   323,    81,    71,    72,    75,    74,    59,    73,
      77,   332,    75,   334,    75,     3,     4,     5,     6,     7,
       8,     9,    81,    74,    80,   465,    77,    73,   349,   483,
      75,    75,    73,    80,    91,    73,    79,   358,   542,   543,
      79,    81,   482,    80,    80,    79,    74,    74,    36,    37,
      80,    27,   505,    78,    30,    31,    32,   108,    80,   563,
     564,    80,    50,    74,   115,    74,   387,   388,    73,    57,
      58,    59,    80,    80,    62,    63,    73,   531,    66,    67,
      95,   514,    73,    71,    72,    79,    74,   540,    76,    77,
      80,    80,    73,    80,    74,    79,    81,    80,    74,   420,
      73,    77,    73,    73,    79,     8,    24,    81,   561,   328,
     404,   460,   100,   101,   416,   103,   435,   434,   110,   573,
     482,   574,    98,   576,   232,   326,   114,   115,   116,    54,
      55,    35,   108,   407,    59,    60,    61,    62,   465,   228,
     576,    -1,   574,    68,    -1,   466,   595,    -1,    -1,   470,
      -1,     1,    -1,     3,     4,     5,     6,     7,     8,     9,
     481,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    57,    58,    59,
      -1,    -1,    62,    63,    -1,    -1,    66,    67,    -1,    -1,
      -1,    71,    72,    -1,    74,    75,    76,    -1,    -1,    -1,
      80,    -1,    -1,    -1,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    -1,    -1,    97,    98,    99,
     100,   101,    -1,   103,    -1,    -1,    -1,   107,   108,   109,
     110,    -1,    -1,   113,   114,     1,   116,     3,     4,     5,
       6,     7,     8,     9,    -1,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    57,    58,    59,    -1,    -1,    62,    63,    -1,    -1,
      66,    67,    -1,    -1,    -1,    71,    72,    -1,    74,    75,
      76,    -1,    -1,    -1,    80,    -1,    -1,    -1,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    -1,
      -1,    97,    98,    99,   100,   101,    -1,   103,    -1,    -1,
      -1,   107,   108,   109,   110,    -1,    -1,   113,   114,     1,
     116,     3,     4,     5,     6,     7,     8,     9,    -1,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    57,    58,    59,    -1,    -1,
      62,    63,    -1,    -1,    66,    67,    -1,    -1,    -1,    71,
      72,    -1,    74,    -1,    76,    -1,    -1,    -1,    80,    -1,
      -1,    -1,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    -1,    -1,    97,    98,    99,   100,   101,
      -1,   103,    -1,    -1,    -1,   107,   108,   109,   110,    -1,
      -1,   113,   114,     1,   116,     3,     4,     5,     6,     7,
       8,     9,    -1,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    57,
      58,    59,    -1,    -1,    62,    63,    -1,    -1,    66,    67,
      -1,    -1,    -1,    71,    72,    -1,    74,    75,    76,    -1,
      -1,    -1,    80,    -1,    -1,    -1,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    -1,    -1,    97,
      98,    99,   100,   101,    -1,   103,    -1,    -1,    -1,   107,
     108,    -1,    -1,    -1,    -1,   113,   114,     1,   116,     3,
       4,     5,     6,     7,     8,     9,    -1,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    57,    58,    59,    -1,    -1,    62,    63,
      -1,    -1,    66,    67,    -1,    -1,    -1,    71,    72,    -1,
      74,    -1,    76,    -1,    -1,    -1,    80,    -1,    -1,    -1,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    -1,    -1,    97,    98,    99,   100,   101,    -1,   103,
      -1,    -1,    -1,   107,   108,    -1,    -1,    -1,    -1,   113,
     114,     1,   116,     3,     4,     5,     6,     7,     8,     9,
      -1,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    57,    58,    59,
      -1,    -1,    62,    63,    -1,    -1,    66,    67,    -1,    -1,
      -1,    71,    72,    -1,    74,    -1,    76,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    97,    63,    99,
     100,   101,    -1,   103,    69,    70,    71,    72,   108,    74,
      -1,    -1,    77,   113,   114,     1,   116,     3,     4,     5,
       6,     7,     8,     9,    -1,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    57,    58,    59,    -1,    -1,    62,    63,    -1,    -1,
      66,    67,    -1,    -1,    -1,    71,    72,    -1,    74,    -1,
      -1,    -1,    -1,    -1,    80,    -1,     1,    -1,     3,     4,
       5,     6,    -1,     8,     9,    -1,    -1,    -1,    -1,    -1,
      -1,    97,    -1,    99,   100,   101,    -1,   103,    -1,    -1,
      -1,    -1,   108,    -1,    -1,    -1,    -1,   113,   114,    -1,
     116,    36,    37,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    57,    58,    59,    -1,    -1,    62,    63,    -1,
      -1,    66,    67,    -1,    -1,    -1,    71,    72,    73,    74,
       1,    -1,     3,     4,     5,     6,    -1,     8,     9,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    -1,    -1,    -1,   100,   101,    -1,   103,    69,
      70,    71,    72,    -1,    74,    36,    37,    77,    -1,   114,
      -1,   116,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    57,    58,    59,    -1,
      -1,    62,    63,    -1,    -1,    66,    67,    -1,    -1,    -1,
      71,    72,     1,    74,     3,     4,     5,     6,    79,     8,
       9,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       1,    -1,     3,     4,     5,     6,    -1,     8,     9,   100,
     101,    -1,   103,    -1,    -1,    -1,    -1,    36,    37,    -1,
      -1,    -1,    -1,   114,    -1,   116,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    36,    37,    -1,    57,    58,
      59,    -1,    -1,    62,    63,    -1,    -1,    66,    67,    -1,
      -1,    -1,    71,    72,    -1,    74,    57,    58,    59,    78,
      -1,    62,    63,    -1,    -1,    66,    67,    -1,    -1,    -1,
      71,    72,    -1,    74,    -1,    -1,    -1,    78,    -1,    -1,
      -1,   100,   101,     1,   103,     3,     4,     5,     6,    -1,
       8,     9,    -1,    -1,    -1,   114,    -1,   116,    -1,   100,
     101,    -1,   103,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   114,    -1,   116,    -1,    -1,    36,    37,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    57,
      58,    59,    -1,    -1,    62,    63,    -1,    -1,    66,    67,
      -1,    -1,    -1,    71,    72,    -1,    74,    -1,    -1,    -1,
      -1,    -1,    80,    -1,     1,    -1,     3,     4,     5,     6,
      -1,     8,     9,     3,     4,     5,     6,    -1,     8,     9,
      49,    50,   100,   101,    -1,   103,    -1,    -1,    57,    58,
      59,    60,    61,    -1,    -1,    -1,   114,    -1,   116,    36,
      37,    -1,    71,    72,    -1,    74,    36,    37,    77,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      57,    58,    59,    -1,    -1,    62,    63,    -1,    -1,    66,
      67,    -1,    62,    -1,    71,    72,    66,    74,    -1,    -1,
      -1,    71,    72,    80,    74,     1,    76,     3,     4,     5,
       6,    -1,     8,     9,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   100,   101,    -1,   103,    -1,    -1,    -1,
     100,   101,    -1,   103,    -1,    -1,    -1,   114,    -1,   116,
      36,    37,    -1,    -1,   114,    -1,   116,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    57,    58,    59,    -1,    -1,    62,    63,    -1,    -1,
      66,    67,    -1,    -1,    -1,    71,    72,    73,    74,     1,
      -1,     3,     4,     5,     6,    -1,     8,     9,    49,    50,
      -1,    -1,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    -1,    -1,    -1,   100,   101,    -1,   103,    69,    70,
      71,    72,    -1,    74,    36,    37,    77,    -1,   114,    -1,
     116,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    57,    58,    59,    -1,    -1,
      62,    63,    -1,    -1,    66,    67,    -1,    -1,    -1,    71,
      72,     1,    74,     3,     4,     5,     6,    -1,     8,     9,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     1,
      -1,     3,     4,     5,     6,    -1,     8,     9,   100,   101,
      -1,   103,    -1,    -1,    -1,    -1,    36,    37,    -1,    -1,
      -1,    -1,   114,    -1,   116,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    36,    37,    -1,    57,    58,    59,
      -1,    -1,    62,    63,    -1,    -1,    66,    67,    -1,    -1,
      -1,    71,    72,    -1,    74,    57,    58,    59,    -1,    -1,
      62,    63,    -1,    -1,    66,    67,    -1,    -1,    -1,    71,
      72,     1,    74,     3,     4,     5,     6,    -1,     8,     9,
     100,   101,    -1,   103,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   114,    -1,   116,    -1,   100,   101,
      -1,   103,    -1,    -1,    -1,    -1,    36,    37,    -1,    -1,
      -1,    -1,   114,    -1,   116,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    57,    58,    59,
      -1,    -1,    62,    63,    -1,    -1,    66,    67,    -1,    -1,
      -1,    71,    72,    -1,    74,     3,     4,     5,     6,    -1,
       8,     9,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     100,   101,    -1,   103,    -1,    -1,    -1,    -1,    36,    37,
      -1,    -1,    -1,    -1,   114,    -1,   116,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    57,
      58,    59,    -1,    -1,    62,    63,    -1,    -1,    66,    67,
      -1,    -1,    -1,    71,    72,    -1,    74,    -1,    76,     3,
       4,     5,     6,    -1,     8,     9,    49,    50,    -1,    -1,
      -1,    -1,    -1,    -1,    57,    58,    59,    60,    61,    -1,
      -1,    -1,   100,   101,    -1,   103,    69,    70,    71,    72,
      -1,    74,    36,    37,    77,    -1,   114,    -1,   116,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    57,    58,    59,    -1,    -1,    62,    63,
      -1,    -1,    66,    67,    -1,    -1,    -1,    71,    72,    -1,
      74,    -1,    76,     3,     4,     5,     6,    -1,     8,     9,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   100,   101,    -1,   103,
      -1,    -1,    -1,    -1,    -1,    -1,    36,    37,    -1,    -1,
     114,    -1,   116,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    57,    58,    59,
      -1,    -1,    62,    63,    -1,    -1,    66,    67,    -1,    -1,
      -1,    71,    72,    -1,    74,     3,     4,     5,     6,    -1,
       8,     9,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     3,     4,     5,     6,    -1,     8,     9,
     100,   101,    -1,   103,    -1,    -1,    -1,    -1,    36,    37,
      -1,    -1,    -1,    -1,   114,    -1,   116,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    36,    37,    -1,    57,
      58,    59,    -1,    -1,    62,    63,    -1,    -1,    66,    67,
      -1,    -1,    -1,    71,    72,    -1,    74,    57,    58,    59,
      -1,    -1,    62,    63,    -1,    -1,    66,    67,    -1,    -1,
      -1,    71,    72,    -1,    74,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   100,   101,    -1,   103,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   114,    -1,   116,    -1,
     100,   101,    -1,   103,    -1,    -1,    -1,     1,    -1,    -1,
      -1,    -1,    -1,     7,   114,    -1,   116,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,     7,    -1,    -1,    -1,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    75,    -1,    -1,    -1,    -1,    -1,    -1,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    -1,    63,    97,    65,    99,    -1,    -1,    69,    70,
      71,    72,    -1,    74,   108,    -1,    77,    -1,    -1,   113,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    97,    -1,    99,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   108,    -1,    -1,    -1,    -1,   113,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    -1,    63,
      64,    65,    -1,    67,    68,    69,    70,    71,    72,    -1,
      74,    -1,    -1,    77,    78,    -1,    -1,    -1,    82,    83,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    97,    -1,    99,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   108,    -1,    -1,    -1,
      -1,   113,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    -1,    63,    64,    65,
      -1,    67,    68,    69,    70,    71,    72,    -1,    74,    -1,
      -1,    77,    -1,    79,    -1,    -1,    82,    83,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    -1,    63,    64,    65,    -1,    67,    68,    69,
      70,    71,    72,    -1,    74,    75,    -1,    77,    -1,    -1,
      -1,    -1,    -1,    83,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    -1,    63,
      64,    65,    -1,    67,    68,    69,    70,    71,    72,    -1,
      74,    -1,    -1,    77,    -1,    -1,    -1,    81,    -1,    83,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    -1,    63,    64,    65,    -1,    67,
      68,    69,    70,    71,    72,    73,    74,    -1,    -1,    77,
      -1,    -1,    -1,    -1,    -1,    83,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      -1,    63,    64,    65,    -1,    67,    68,    69,    70,    71,
      72,    -1,    74,    -1,    -1,    77,    -1,    -1,    -1,    81,
      -1,    83,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    -1,    63,    64,    65,
      -1,    67,    68,    69,    70,    71,    72,    -1,    74,    75,
      -1,    77,    -1,    -1,    -1,    -1,    -1,    83,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    -1,    63,    64,    65,    -1,    67,    68,    69,
      70,    71,    72,    -1,    74,    -1,    -1,    77,    78,    -1,
      -1,    -1,    -1,    83,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    -1,    63,
      64,    65,    -1,    67,    68,    69,    70,    71,    72,    -1,
      74,    -1,    -1,    77,    -1,    79,    -1,    -1,    -1,    83,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    -1,    63,    64,    65,    -1,    67,
      68,    69,    70,    71,    72,    73,    74,    -1,    -1,    77,
      -1,    -1,    -1,    -1,    -1,    83,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      -1,    63,    64,    65,    -1,    67,    68,    69,    70,    71,
      72,    -1,    74,    -1,    -1,    77,    -1,    -1,    -1,    -1,
      -1,    83,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    -1,    63,    64,    65,    -1,
      67,    68,    69,    70,    71,    72,    -1,    74,    -1,    -1,
      77,    -1,    -1,    -1,    -1,    -1,    83,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      -1,    63,    64,    65,    -1,    67,    -1,    69,    70,    71,
      72,    -1,    74,    -1,    -1,    77,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    -1,
      63,    64,    65,    -1,    -1,    -1,    69,    70,    71,    72,
      -1,    74,    -1,    -1,    77
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    80,   120,   121,   122,   123,   122,     0,    10,     3,
      98,   109,   111,   112,   124,   125,   172,   175,   176,   213,
     215,    74,   194,    74,    76,    76,     1,   122,    59,    80,
     173,   174,   191,   200,   206,   207,     7,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    97,    99,   108,   113,   177,   180,   220,   214,
       3,   126,   203,   216,     8,   100,   101,   131,   133,   135,
     125,     3,     4,     5,     6,     9,    36,    37,    57,    58,
      59,    62,    63,    66,    67,    71,    72,    74,   103,   114,
     116,   129,   130,   131,   134,   149,    80,   218,   220,    80,
      81,    38,     3,     7,    74,   115,   127,   192,   201,    76,
     127,    76,   127,   177,   178,    76,   127,   178,   178,   178,
     178,   178,   178,    74,    74,   177,   179,   178,     1,    76,
     151,   153,    81,   203,   217,    74,   175,   195,   199,    73,
     135,    75,    74,   129,    74,   129,   129,   129,   129,   129,
     129,   129,     3,   129,   129,     1,   129,   146,   153,   175,
     208,    74,    74,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    63,    64,    65,
      67,    68,    69,    70,    71,    72,    74,    75,    77,    83,
     150,     9,   135,   207,   218,   173,   191,   207,    76,   129,
     136,   218,    74,    74,    77,    98,   194,   219,   220,     3,
     189,   190,    76,   182,    76,   184,    76,   129,   208,     3,
     124,   152,    75,   203,    73,    73,   199,   191,   206,   207,
     209,    73,    81,   196,    80,     3,   208,   208,    73,    81,
      81,    73,    73,   207,   209,    73,   129,     3,   129,   129,
     129,   129,   129,   129,   129,   129,   129,   129,   129,   127,
     127,   129,   129,   129,   129,   129,   129,   129,   129,   129,
     129,   129,   129,   129,   129,   129,   129,   129,   129,     1,
     144,   146,     3,     1,   146,   145,   146,   192,     3,    50,
      77,   127,   136,   137,   138,   139,   141,   143,   191,     3,
     202,   218,    74,   193,   219,    38,    81,   128,   189,     1,
     175,   185,   181,   185,   183,    73,    73,    73,    75,   102,
     156,   175,   204,   204,    73,    74,   210,   212,   197,   198,
      76,    73,    73,   146,   146,    74,    76,   129,    81,    73,
      73,    76,    78,    78,    79,    74,   127,   129,    79,    75,
      81,    38,   140,   136,    73,    73,   203,     1,   146,   147,
     131,   195,   129,     1,   190,    75,   128,    80,    80,   186,
      75,   185,    75,   185,     3,   157,   154,     1,   191,   205,
      80,     1,   218,   218,    77,   194,    82,   199,   122,   218,
     138,   208,   129,   129,   141,   142,    78,    82,   138,   136,
      73,    78,    78,    73,    73,    75,   185,   185,    79,   187,
     188,   191,    75,    75,    81,    80,     1,     3,    80,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      98,   107,   109,   110,   146,   153,   155,   158,   159,   160,
     161,   162,   170,   172,   175,    81,    80,    73,   209,   147,
     211,   196,    75,    75,    73,    75,   142,   129,   204,   218,
     129,    80,    81,    79,   157,   156,   124,    79,    80,    80,
       3,    59,    80,   146,   163,   129,    79,   165,   166,   171,
      74,   148,    27,    31,   221,    74,    80,   158,   160,   161,
     160,   162,   155,   145,   168,   205,    82,   204,    73,    78,
     195,    78,   185,   187,   129,    80,    80,   146,    80,   148,
      79,    82,   148,   161,    74,     1,   146,   161,   221,   221,
      74,   131,    80,   172,    73,    80,   164,   129,   161,    91,
      73,    73,    95,   131,    73,   145,   145,   161,    79,   148,
     161,    79,   222,    80,    80,    80,   131,   223,   224,   225,
      73,   145,   145,    74,    79,   226,    81,    80,   167,    73,
       1,   129,   223,   225,    73,   169,    73,    73,    79,   227,
     161,   161,     8,   132,   228,    81,   228
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
#line 776 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {YYACCEPT;}
    break;

  case 3:
/* Line 1787 of yacc.c  */
#line 778 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  /* To handle special case: compilation unit module */
			  list dsl = (yyvsp[(1) - (1)].liste);
			  list dl = statements_to_declarations(dsl);

			  pips_assert("Here, only continue statements are expected",
				      continue_statements_p(dsl));

			  if (true /* dl != NIL*/) { /* A C file with comments only is OK */
			    if(!entity_undefined_p(get_current_module_entity())) {
			      if(!compilation_unit_p(get_current_module_name())) {
				pips_assert("Each variable is declared once", gen_once_p(dl));
				pips_internal_error("Compilation unit rule used for non"
						    " compilation unit %s\n",
						    get_current_module_name());
			      }
			      ifdebug(8) {
				pips_debug(8, "Declaration list for compilation unit %s: ",
					   get_current_module_name());
				print_entities(dl);
				pips_debug(8, "\n");
			      }
			      ModuleStatement = make_statement(entity_empty_label(),
							       STATEMENT_NUMBER_UNDEFINED,
							       STATEMENT_ORDERING_UNDEFINED,
							       string_undefined,
							       make_instruction_block(dsl),
							       dl, NULL, empty_extensions (), make_synchronization_none());
			      if(ENDP(dl)) {
				pips_user_warning("ISO C forbids an empty source file\n");
			      }
			    }
			  }
			}
    break;

  case 4:
/* Line 1787 of yacc.c  */
#line 815 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    { (yyval.liste) = NIL; }
    break;

  case 5:
/* Line 1787 of yacc.c  */
#line 816 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {is_external = true; }
    break;

  case 6:
/* Line 1787 of yacc.c  */
#line 817 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  list dsl = (yyvsp[(3) - (3)].liste);
			  list gdsl = (yyvsp[(2) - (3)].liste);

			  /* PRAGMA */
			  if(!ENDP(dsl) && gen_length(gdsl)==1)
			    {
			      statement stmt = STATEMENT(CAR(dsl));
			      statement stmt_pragma = STATEMENT(CAR(gdsl));
			      list exs = extensions_extension(statement_extensions(stmt_pragma));
			      if (!ENDP(exs))
			      {
				extensions_extension(statement_extensions(stmt)) = gen_nconc(exs, extensions_extension(statement_extensions(stmt)));
				extensions_extension(statement_extensions(stmt_pragma)) = NIL;
				gen_full_free_list(gdsl);
				gdsl = NIL;
			      }
			    }

				ifdebug(1) { // the successive calls to statements_to_declarations are too costly, so I only activate the test upond debug(1)
				  list dl = statements_to_declarations(dsl);
				  /* Each variable should be declared only
					 once. Type and initial value conflict
					 should have been detected earlier. */
				  if(!compilation_unit_p(get_current_module_name())) {
					pips_assert("Each variable is declared once", gen_once_p(dl));
				  }
				  ifdebug(9) {
					list gdl = statements_to_declarations(gdsl);
					fprintf(stderr, "New variables $2 (%p) are declared\n", gdl);
					print_entities(gdl);
					fprintf(stderr, "\n");
					fprintf(stderr, "*******Current declarations dl (%p) are: \n", dl);
					print_entities(dl);
					fprintf(stderr, "\n");
					gen_free_list(gdl);
				  }
				  gen_free_list(dl);
				}

			  /* The order of declarations must be
			     preserved: a structure is declared before
			     it is used to declare a variable */
			  /*
			  $$ = NIL;
			  MAP(ENTITY, v, {
			    if(!gen_in_list_p(v, $3))
			      $$ = gen_nconc($$, CONS(ENTITY, v , NIL));}, $2);
			  $$ = gen_nconc($$, $3);
			  */
			  /* Redeclarations are possible in C as long as they are compatible */
			  /* It is assumed that compatibility is checked somewhere else... */
			  (yyval.liste) = gen_nconc(gdsl, dsl);

			  ifdebug(9) {
			    list udl = statements_to_declarations((yyval.liste));
			    fprintf(stderr, "*******Updated $$ declarations (%p) are: \n", (yyval.liste));
			    fprintf(stderr, "\n");
			    if(ENDP((yyval.liste)))
			      fprintf(stderr, "Empty list\n");
			    else
			      print_entities(udl);
			    fprintf(stderr, "\n");
			  }

			  if(!compilation_unit_p(get_current_module_name())) {
			    list udl = statements_to_declarations((yyval.liste));
			    pips_assert("Each variable is declared once", gen_once_p(udl));
			    entity m = get_current_module_entity();
			    if(strcmp(entity_local_name(m),"main")==0) {
			      type mt = entity_type(m);
			      if(type_functional_p(mt)) {
				type rt = functional_result(type_functional(mt));
				if(!scalar_integer_type_p(rt))
				  /* Too late for line numbers, do not use c_parser_user_warning */
				  c_parser_user_warning("The \"main\" function should return an int value\n");
			      }
			      else {
				pips_internal_error("A function does not have a functional type\n");
			      }
			    }
			    ResetCurrentModule();
			  }
			}
    break;

  case 7:
/* Line 1787 of yacc.c  */
#line 902 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  pips_assert("Declarations are unique", gen_once_p((yyvsp[(2) - (2)].liste)));
			  ifdebug(8) {
			    list udl = statements_to_declarations((yyvsp[(2) - (2)].liste));
			    fprintf(stderr, "*******Current declarations are: \n");
			    print_entities(udl);
			    fprintf(stderr, "\n");
			  }
			  (yyval.liste) = (yyvsp[(2) - (2)].liste);
			}
    break;

  case 8:
/* Line 1787 of yacc.c  */
#line 915 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {}
    break;

  case 9:
/* Line 1787 of yacc.c  */
#line 919 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {pips_debug(1, "Reduction %d: declaration -> global\n", __LINE__); /* discard_C_comment();*/  /* fprintf(stderr, "declaration\n");*/ declaration_counter++; }
    break;

  case 10:
/* Line 1787 of yacc.c  */
#line 920 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    { (yyval.liste) = NIL;}
    break;

  case 11:
/* Line 1787 of yacc.c  */
#line 922 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  CParserError("ASM not implemented\n");
			  (yyval.liste) = NIL;
			}
    break;

  case 12:
/* Line 1787 of yacc.c  */
#line 927 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  /*
			  CParserError("PRAGMA not implemented at top level\n");
			  $$ = NIL;
			  */
			  statement s = make_continue_statement(entity_empty_label());
			  add_pragma_str_to_statement(s, (yyvsp[(1) - (1)].string), true);
			  (yyval.liste) = CONS(STATEMENT, s, NIL);
			}
    break;

  case 13:
/* Line 1787 of yacc.c  */
#line 940 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  entity oe = FindOrCreateEntity(TOP_LEVEL_MODULE_NAME,(yyvsp[(1) - (2)].string));
			  free((yyvsp[(1) - (2)].string));
			  entity e = oe; //RenameFunctionEntity(oe);
			  pips_debug(2,"Create function %s with old-style function prototype\n",(yyvsp[(1) - (2)].string));
			  if (storage_undefined_p(entity_storage(e))) {
			    //entity_storage(e) = make_storage_return(e);
			    entity_storage(e) = make_storage_rom();
			  }
			  if (value_undefined_p(entity_initial(e)))
			    entity_initial(e) = make_value(is_value_code,make_code(NIL,strdup(""),make_sequence(NIL),NIL, make_language_c()));
			  //pips_assert("e is a module", module_name_p(entity_module_name(e)));
			  else
			    CCleanLocalEntities(oe);
			  PushFunction(e);
			  stack_push((char *) make_basic_logical(true),FormalStack);
			  stack_push((char *) make_basic_int(1),OffsetStack);
			  // FI: commented out while looking for
			  //declaration comments
			  //discard_C_comment();
			}
    break;

  case 14:
/* Line 1787 of yacc.c  */
#line 962 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  entity e = GetFunction();
			  if (type_undefined_p(entity_type(e)))
			    {
			      list paras = MakeParameterList((yyvsp[(4) - (7)].liste),(yyvsp[(6) - (7)].liste),FunctionStack);
			      functional f = make_functional(paras,make_type_unknown());
			      entity_type(e) = make_type_functional(f);
			    }
			  pips_assert("Current function entity is consistent",entity_consistent_p(e));
			  PopFunction();
			  stack_pop(FormalStack);
			  StackPop(OffsetStack);
			  gen_free_list((yyvsp[(4) - (7)].liste));
			  (yyval.liste) = NIL;
			  // FI: commented out while trying to
			  //retrieve all comments
			  //discard_C_comment();
			}
    break;

  case 15:
/* Line 1787 of yacc.c  */
#line 1007 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  CParserError("CIL AT not implemented\n");
			  (yyval.liste) = NIL;
			}
    break;

  case 16:
/* Line 1787 of yacc.c  */
#line 1013 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  CParserError("CIL AT not implemented\n");
			  (yyval.liste) = NIL;
			}
    break;

  case 17:
/* Line 1787 of yacc.c  */
#line 1018 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  CParserError("Parse error: location error TK_SEMICOLON \n");
			  (yyval.liste) = NIL;
			}
    break;

  case 18:
/* Line 1787 of yacc.c  */
#line 1026 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {}
    break;

  case 19:
/* Line 1787 of yacc.c  */
#line 1028 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {}
    break;

  case 20:
/* Line 1787 of yacc.c  */
#line 1030 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			   CParserError("CIL AT not implemented\n");
			}
    break;

  case 23:
/* Line 1787 of yacc.c  */
#line 1044 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  (yyval.expression) = MakeNullaryCall((yyvsp[(1) - (1)].entity));
			}
    break;

  case 24:
/* Line 1787 of yacc.c  */
#line 1048 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  /* Create the expression corresponding to this identifier */
			  (yyval.expression) = IdentifierToExpression((yyvsp[(1) - (1)].string));
			  free((yyvsp[(1) - (1)].string));
                        }
    break;

  case 25:
/* Line 1787 of yacc.c  */
#line 1054 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
                          (yyval.expression) = MakeSizeofExpression((yyvsp[(2) - (2)].expression));
                        }
    break;

  case 26:
/* Line 1787 of yacc.c  */
#line 1058 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  (yyval.expression) = MakeSizeofType((yyvsp[(3) - (4)].type));
                        }
    break;

  case 27:
/* Line 1787 of yacc.c  */
#line 1062 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  CParserError("ALIGNOF not implemented\n");
			}
    break;

  case 28:
/* Line 1787 of yacc.c  */
#line 1066 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  CParserError("ALIGNOF not implemented\n");
			}
    break;

  case 29:
/* Line 1787 of yacc.c  */
#line 1070 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  (yyval.expression) = MakeUnaryCall(CreateIntrinsic(UNARY_PLUS_OPERATOR_NAME), (yyvsp[(2) - (2)].expression));
			}
    break;

  case 30:
/* Line 1787 of yacc.c  */
#line 1074 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  (yyval.expression) = MakeUnaryCall(CreateIntrinsic(UNARY_MINUS_OPERATOR_NAME), (yyvsp[(2) - (2)].expression));
			}
    break;

  case 31:
/* Line 1787 of yacc.c  */
#line 1078 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  (yyval.expression) = MakeUnaryCall(CreateIntrinsic(DEREFERENCING_OPERATOR_NAME), (yyvsp[(2) - (2)].expression));
			}
    break;

  case 32:
/* Line 1787 of yacc.c  */
#line 1082 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  (yyval.expression) = MakeUnaryCall(CreateIntrinsic(ADDRESS_OF_OPERATOR_NAME), (yyvsp[(2) - (2)].expression));
			}
    break;

  case 33:
/* Line 1787 of yacc.c  */
#line 1086 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  (yyval.expression) = MakeUnaryCall(CreateIntrinsic(C_NOT_OPERATOR_NAME), (yyvsp[(2) - (2)].expression));
			}
    break;

  case 34:
/* Line 1787 of yacc.c  */
#line 1090 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  (yyval.expression) = MakeUnaryCall(CreateIntrinsic(BITWISE_NOT_OPERATOR_NAME), (yyvsp[(2) - (2)].expression));
			}
    break;

  case 35:
/* Line 1787 of yacc.c  */
#line 1094 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  (yyval.expression) = MakeUnaryCall(CreateIntrinsic(PRE_INCREMENT_OPERATOR_NAME), (yyvsp[(2) - (2)].expression));
			}
    break;

  case 36:
/* Line 1787 of yacc.c  */
#line 1098 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  (yyval.expression) = MakeUnaryCall(CreateIntrinsic(POST_INCREMENT_OPERATOR_NAME), (yyvsp[(1) - (2)].expression));
			}
    break;

  case 37:
/* Line 1787 of yacc.c  */
#line 1102 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  (yyval.expression) = MakeUnaryCall(CreateIntrinsic(PRE_DECREMENT_OPERATOR_NAME), (yyvsp[(2) - (2)].expression));
			}
    break;

  case 38:
/* Line 1787 of yacc.c  */
#line 1106 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  (yyval.expression) = MakeUnaryCall(CreateIntrinsic(POST_DECREMENT_OPERATOR_NAME), (yyvsp[(1) - (2)].expression));
			}
    break;

  case 39:
/* Line 1787 of yacc.c  */
#line 1110 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  /* Find the struct/union type of the expression
			     then the struct/union member entity and transform it to expression */
			  expression exp = MemberIdentifierToExpression((yyvsp[(1) - (3)].expression),(yyvsp[(3) - (3)].string));
			  (yyval.expression) = MakeBinaryCall(CreateIntrinsic(POINT_TO_OPERATOR_NAME),(yyvsp[(1) - (3)].expression),exp);
			}
    break;

  case 40:
/* Line 1787 of yacc.c  */
#line 1117 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  expression exp = MemberIdentifierToExpression((yyvsp[(1) - (3)].expression),(yyvsp[(3) - (3)].string));
			  (yyval.expression) = MakeBinaryCall(CreateIntrinsic(FIELD_OPERATOR_NAME),(yyvsp[(1) - (3)].expression),exp);
			}
    break;

  case 41:
/* Line 1787 of yacc.c  */
#line 1122 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  CParserError("GNU extension not implemented\n");
			}
    break;

  case 42:
/* Line 1787 of yacc.c  */
#line 1126 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  if(false) {
                          char * ccc = pop_current_C_comment();
			  if(!empty_comments_p(ccc)) {
			    bool fullspace=true;
			    for(const char *iter=ccc;*iter;++iter)
			      if(!(fullspace=(isspace(*iter)&&*iter!='\n')))
				break;
			    if(fullspace)
			      free(ccc);
			    else {
			      /* paren_comma_expression is a list of
				 expressions, maybe reduced to one */
			      if(empty_comments_p(expression_comment))
				expression_comment=ccc;
			      else {
				char *tmp = expression_comment;
				asprintf(&expression_comment,"%s%s",expression_comment, ccc);
				free(tmp);
			      }
			    }
			  }
			  expression_line_number = pop_current_C_line_number();
			  }
			  (yyval.expression) = MakeCommaExpression((yyvsp[(1) - (1)].liste));
                        }
    break;

  case 43:
/* Line 1787 of yacc.c  */
#line 1153 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  (yyval.expression) = MakeFunctionExpression((yyvsp[(1) - (4)].expression),(yyvsp[(3) - (4)].liste));
			}
    break;

  case 44:
/* Line 1787 of yacc.c  */
#line 1157 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {

			  expression e = (yyvsp[(3) - (6)].expression);
			  type t = (yyvsp[(5) - (6)].type);
			  sizeofexpression e1 = make_sizeofexpression_expression(e);
			  sizeofexpression e2 = make_sizeofexpression_type(t);
			  list l = CONS(SIZEOFEXPRESSION, e1,
					CONS(SIZEOFEXPRESSION, e2, NIL));
			  syntax s = make_syntax_va_arg(l);
			  expression r = make_expression(s, make_normalized_complex());

			  (yyval.expression) = r;
			  //CParserError("BUILTIN_VA_ARG not implemented\n");
			}
    break;

  case 45:
/* Line 1787 of yacc.c  */
#line 1172 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  (yyval.expression) = MakeArrayExpression((yyvsp[(1) - (2)].expression),(yyvsp[(2) - (2)].liste));
			}
    break;

  case 46:
/* Line 1787 of yacc.c  */
#line 1176 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  (yyval.expression) = MakeTernaryCall(CreateIntrinsic(CONDITIONAL_OPERATOR_NAME), (yyvsp[(1) - (5)].expression), (yyvsp[(3) - (5)].expression), (yyvsp[(5) - (5)].expression));
			}
    break;

  case 47:
/* Line 1787 of yacc.c  */
#line 1180 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  (yyval.expression) = MakeBinaryCall(CreateIntrinsic(PLUS_C_OPERATOR_NAME), (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
			}
    break;

  case 48:
/* Line 1787 of yacc.c  */
#line 1184 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  (yyval.expression) = MakeBinaryCall(CreateIntrinsic(MINUS_C_OPERATOR_NAME), (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
			}
    break;

  case 49:
/* Line 1787 of yacc.c  */
#line 1188 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  (yyval.expression) = MakeBinaryCall(CreateIntrinsic(MULTIPLY_OPERATOR_NAME), (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
			}
    break;

  case 50:
/* Line 1787 of yacc.c  */
#line 1192 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  (yyval.expression) = MakeBinaryCall(CreateIntrinsic(DIVIDE_OPERATOR_NAME), (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
			}
    break;

  case 51:
/* Line 1787 of yacc.c  */
#line 1196 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  (yyval.expression) = MakeBinaryCall(CreateIntrinsic(C_MODULO_OPERATOR_NAME), (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
			}
    break;

  case 52:
/* Line 1787 of yacc.c  */
#line 1200 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  (yyval.expression) = MakeBinaryCall(CreateIntrinsic(C_AND_OPERATOR_NAME), (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
			}
    break;

  case 53:
/* Line 1787 of yacc.c  */
#line 1204 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  (yyval.expression) = MakeBinaryCall(CreateIntrinsic(C_OR_OPERATOR_NAME), (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
			}
    break;

  case 54:
/* Line 1787 of yacc.c  */
#line 1208 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  (yyval.expression) = MakeBinaryCall(CreateIntrinsic(BITWISE_AND_OPERATOR_NAME), (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
			}
    break;

  case 55:
/* Line 1787 of yacc.c  */
#line 1212 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  (yyval.expression) = MakeBinaryCall(CreateIntrinsic(BITWISE_OR_OPERATOR_NAME), (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
			}
    break;

  case 56:
/* Line 1787 of yacc.c  */
#line 1216 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  (yyval.expression) = MakeBinaryCall(CreateIntrinsic(BITWISE_XOR_OPERATOR_NAME), (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
			}
    break;

  case 57:
/* Line 1787 of yacc.c  */
#line 1220 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  (yyval.expression) = MakeBinaryCall(CreateIntrinsic(C_EQUAL_OPERATOR_NAME), (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
			}
    break;

  case 58:
/* Line 1787 of yacc.c  */
#line 1224 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  (yyval.expression) = MakeBinaryCall(CreateIntrinsic(C_NON_EQUAL_OPERATOR_NAME), (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
			}
    break;

  case 59:
/* Line 1787 of yacc.c  */
#line 1228 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  (yyval.expression) = MakeBinaryCall(CreateIntrinsic(C_LESS_THAN_OPERATOR_NAME), (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
			}
    break;

  case 60:
/* Line 1787 of yacc.c  */
#line 1232 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  (yyval.expression) = MakeBinaryCall(CreateIntrinsic(C_GREATER_THAN_OPERATOR_NAME), (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
			}
    break;

  case 61:
/* Line 1787 of yacc.c  */
#line 1236 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  (yyval.expression) = MakeBinaryCall(CreateIntrinsic(C_LESS_OR_EQUAL_OPERATOR_NAME), (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
			}
    break;

  case 62:
/* Line 1787 of yacc.c  */
#line 1240 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  (yyval.expression) = MakeBinaryCall(CreateIntrinsic(C_GREATER_OR_EQUAL_OPERATOR_NAME), (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
			}
    break;

  case 63:
/* Line 1787 of yacc.c  */
#line 1244 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  (yyval.expression) = MakeBinaryCall(CreateIntrinsic(LEFT_SHIFT_OPERATOR_NAME), (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
			}
    break;

  case 64:
/* Line 1787 of yacc.c  */
#line 1248 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  (yyval.expression) = MakeBinaryCall(CreateIntrinsic(RIGHT_SHIFT_OPERATOR_NAME), (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
			}
    break;

  case 65:
/* Line 1787 of yacc.c  */
#line 1252 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  expression lhs = (yyvsp[(1) - (3)].expression);
			  expression rhs = (yyvsp[(3) - (3)].expression);
			  /* Check the left hand side expression */
			  if(expression_reference_p(lhs)) {
			    reference r = expression_reference(lhs);
			    entity v = reference_variable(r);
			    type t = ultimate_type(entity_type(v));
			    if(type_functional_p(t)) {
			      c_parser_user_warning("Ill. left hand side reference to function \"%s\""
                                                " or variable \"%s\" not declared\n",
						entity_user_name(v), entity_user_name(v));
			      CParserError("Ill. left hand side expression");
			    }
			  }
			  (void) simplify_C_expression(rhs);
			  (yyval.expression) = make_assign_expression(lhs, rhs);
			}
    break;

  case 66:
/* Line 1787 of yacc.c  */
#line 1271 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  (void) simplify_C_expression((yyvsp[(3) - (3)].expression));
			  (yyval.expression) = MakeBinaryCall(CreateIntrinsic(PLUS_UPDATE_OPERATOR_NAME), (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
			}
    break;

  case 67:
/* Line 1787 of yacc.c  */
#line 1276 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  (void) simplify_C_expression((yyvsp[(3) - (3)].expression));
			  (yyval.expression) = MakeBinaryCall(CreateIntrinsic(MINUS_UPDATE_OPERATOR_NAME), (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
			}
    break;

  case 68:
/* Line 1787 of yacc.c  */
#line 1281 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  (void) simplify_C_expression((yyvsp[(3) - (3)].expression));
			  (yyval.expression) = MakeBinaryCall(CreateIntrinsic(MULTIPLY_UPDATE_OPERATOR_NAME), (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
			}
    break;

  case 69:
/* Line 1787 of yacc.c  */
#line 1286 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  (void) simplify_C_expression((yyvsp[(3) - (3)].expression));
			  (yyval.expression) = MakeBinaryCall(CreateIntrinsic(DIVIDE_UPDATE_OPERATOR_NAME), (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
			}
    break;

  case 70:
/* Line 1787 of yacc.c  */
#line 1291 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  (void) simplify_C_expression((yyvsp[(3) - (3)].expression));
			  (yyval.expression) = MakeBinaryCall(CreateIntrinsic(MODULO_UPDATE_OPERATOR_NAME), (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
			}
    break;

  case 71:
/* Line 1787 of yacc.c  */
#line 1296 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  (void) simplify_C_expression((yyvsp[(3) - (3)].expression));
			  (yyval.expression) = MakeBinaryCall(CreateIntrinsic(BITWISE_AND_UPDATE_OPERATOR_NAME), (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
			}
    break;

  case 72:
/* Line 1787 of yacc.c  */
#line 1301 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  (void) simplify_C_expression((yyvsp[(3) - (3)].expression));
			  (yyval.expression) = MakeBinaryCall(CreateIntrinsic(BITWISE_OR_UPDATE_OPERATOR_NAME), (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
			}
    break;

  case 73:
/* Line 1787 of yacc.c  */
#line 1306 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  (void) simplify_C_expression((yyvsp[(3) - (3)].expression));
			  (yyval.expression) = MakeBinaryCall(CreateIntrinsic(BITWISE_XOR_UPDATE_OPERATOR_NAME), (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
			}
    break;

  case 74:
/* Line 1787 of yacc.c  */
#line 1311 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  (void) simplify_C_expression((yyvsp[(3) - (3)].expression));
			  (yyval.expression) = MakeBinaryCall(CreateIntrinsic(LEFT_SHIFT_UPDATE_OPERATOR_NAME), (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
			}
    break;

  case 75:
/* Line 1787 of yacc.c  */
#line 1316 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  (void) simplify_C_expression((yyvsp[(3) - (3)].expression));
			  (yyval.expression) = MakeBinaryCall(CreateIntrinsic(RIGHT_SHIFT_UPDATE_OPERATOR_NAME), (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
			}
    break;

  case 76:
/* Line 1787 of yacc.c  */
#line 1321 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  (yyval.expression) = MakeCastExpression((yyvsp[(2) - (4)].type),(yyvsp[(4) - (4)].expression));
			}
    break;

  case 77:
/* Line 1787 of yacc.c  */
#line 1326 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  (yyval.expression) = MakeCastExpression((yyvsp[(2) - (6)].type),MakeBraceExpression((yyvsp[(5) - (6)].liste)));
			}
    break;

  case 78:
/* Line 1787 of yacc.c  */
#line 1331 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  CParserError("GCC's address of labels not implemented\n");
			}
    break;

  case 79:
/* Line 1787 of yacc.c  */
#line 1335 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  CParserError("GCC's address of labels not implemented\n");
			}
    break;

  case 80:
/* Line 1787 of yacc.c  */
#line 1342 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    { // Do we know about the size? 2, 4 or 8 bytes?
			  (yyval.entity) = make_C_constant_entity((yyvsp[(1) - (1)].string), is_basic_int, 4);
			  free((yyvsp[(1) - (1)].string));
			}
    break;

  case 81:
/* Line 1787 of yacc.c  */
#line 1347 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  (yyval.entity) = MakeConstant((yyvsp[(1) - (1)].string), is_basic_float);
			  free((yyvsp[(1) - (1)].string));
			}
    break;

  case 82:
/* Line 1787 of yacc.c  */
#line 1352 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  /* some work left to accomodate imaginary
			     constants */
			  (yyval.entity) = MakeConstant((yyvsp[(1) - (1)].string), is_basic_float);
			  free((yyvsp[(1) - (1)].string));
			}
    break;

  case 83:
/* Line 1787 of yacc.c  */
#line 1359 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  (yyval.entity) = make_C_constant_entity((yyvsp[(1) - (1)].string), is_basic_int, 1);
			  free((yyvsp[(1) - (1)].string));
			}
    break;

  case 84:
/* Line 1787 of yacc.c  */
#line 1364 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  /* The size will be fixed later, hence 0 here. */
			  (yyval.entity) = make_C_constant_entity((yyvsp[(1) - (1)].string), is_basic_string, 0);
			  free((yyvsp[(1) - (1)].string));
                        }
    break;

  case 85:
/* Line 1787 of yacc.c  */
#line 1372 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  (yyval.entity) = MakeConstant(list_to_string((yyvsp[(1) - (1)].liste)),is_basic_string);
			  free((yyvsp[(1) - (1)].liste));
                        }
    break;

  case 86:
/* Line 1787 of yacc.c  */
#line 1382 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  /* Hmmm... Looks like a memory leak on all the
			     strings... */
			  (yyval.string) = list_to_string(gen_nreverse((yyvsp[(1) - (1)].liste)));
			}
    break;

  case 87:
/* Line 1787 of yacc.c  */
#line 1391 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {}
    break;

  case 88:
/* Line 1787 of yacc.c  */
#line 1395 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  (yyval.liste) = CONS(STRING,(yyvsp[(1) - (1)].string),NIL);
			}
    break;

  case 89:
/* Line 1787 of yacc.c  */
#line 1399 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  (yyval.liste) = CONS(STRING,(yyvsp[(2) - (2)].string),(yyvsp[(1) - (2)].liste));
			}
    break;

  case 90:
/* Line 1787 of yacc.c  */
#line 1406 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  (yyval.liste) = CONS(STRING,(yyvsp[(1) - (1)].string),NIL);
			}
    break;

  case 91:
/* Line 1787 of yacc.c  */
#line 1410 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  (yyval.liste) = CONS(STRING,(yyvsp[(2) - (2)].string),(yyvsp[(1) - (2)].liste));
			}
    break;

  case 92:
/* Line 1787 of yacc.c  */
#line 1414 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  (yyval.liste) = gen_nconc((yyvsp[(1) - (2)].liste),CONS(STRING,(yyvsp[(2) - (2)].string),NIL));
			}
    break;

  case 93:
/* Line 1787 of yacc.c  */
#line 1421 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    { }
    break;

  case 94:
/* Line 1787 of yacc.c  */
#line 1423 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    { CParserError("TK_FUNCTION not implemented\n"); }
    break;

  case 95:
/* Line 1787 of yacc.c  */
#line 1425 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    { CParserError("TK_PRETTY_FUNCTION not implemented\n"); }
    break;

  case 96:
/* Line 1787 of yacc.c  */
#line 1429 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
                          expression ie = (yyvsp[(1) - (1)].expression);
			  /* ifdebug(8) { */
			  /*   fprintf(stderr, "Initialization expression: "); */
			  /*   print_expression(ie); */
			  /*   fprintf(stderr, "\n"); */
			  /* } */
			  (yyval.expression) = ie;
                        }
    break;

  case 97:
/* Line 1787 of yacc.c  */
#line 1439 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  /* Deduce the size of an array by its initialization ?*/
			  (yyval.expression) = MakeBraceExpression((yyvsp[(2) - (3)].liste));
			}
    break;

  case 98:
/* Line 1787 of yacc.c  */
#line 1446 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  (yyval.liste) = CONS(EXPRESSION,(yyvsp[(1) - (1)].expression),NIL);
			}
    break;

  case 99:
/* Line 1787 of yacc.c  */
#line 1450 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  (yyval.liste) = CONS(EXPRESSION,(yyvsp[(1) - (3)].expression),(yyvsp[(3) - (3)].liste));
			}
    break;

  case 100:
/* Line 1787 of yacc.c  */
#line 1455 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    { (yyval.liste) = NIL; }
    break;

  case 101:
/* Line 1787 of yacc.c  */
#line 1456 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    { }
    break;

  case 102:
/* Line 1787 of yacc.c  */
#line 1460 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  CParserError("Complicated initialization not implemented\n");
			}
    break;

  case 103:
/* Line 1787 of yacc.c  */
#line 1464 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  CParserError("gcc init designators not implemented\n");
			}
    break;

  case 104:
/* Line 1787 of yacc.c  */
#line 1467 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    { }
    break;

  case 105:
/* Line 1787 of yacc.c  */
#line 1471 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    { }
    break;

  case 106:
/* Line 1787 of yacc.c  */
#line 1474 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  CParserError("gcc missing = not implemented\n");
			}
    break;

  case 107:
/* Line 1787 of yacc.c  */
#line 1480 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    { }
    break;

  case 108:
/* Line 1787 of yacc.c  */
#line 1482 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    { }
    break;

  case 109:
/* Line 1787 of yacc.c  */
#line 1484 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    { }
    break;

  case 110:
/* Line 1787 of yacc.c  */
#line 1487 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    { (yyval.liste) = NIL; }
    break;

  case 111:
/* Line 1787 of yacc.c  */
#line 1488 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {}
    break;

  case 112:
/* Line 1787 of yacc.c  */
#line 1493 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  CParserError("gcc init designators not implemented\n");
			}
    break;

  case 113:
/* Line 1787 of yacc.c  */
#line 1499 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    { (yyval.liste) = NIL; }
    break;

  case 114:
/* Line 1787 of yacc.c  */
#line 1500 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    { }
    break;

  case 115:
/* Line 1787 of yacc.c  */
#line 1505 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    { (yyval.expression) = expression_undefined; }
    break;

  case 116:
/* Line 1787 of yacc.c  */
#line 1508 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    { (yyval.expression) = MakeCommaExpression((yyvsp[(1) - (1)].liste)); }
    break;

  case 117:
/* Line 1787 of yacc.c  */
#line 1513 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  pips_debug(1, "Reduction %d: expression -> comma_expression\n", __LINE__);
			  (void) simplify_C_expression((yyvsp[(1) - (1)].expression));
			  (yyval.liste) = CONS(EXPRESSION,(yyvsp[(1) - (1)].expression),NIL);
			}
    break;

  case 118:
/* Line 1787 of yacc.c  */
#line 1519 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  pips_debug(1, "Reduction %d: expression TK_COMMA comma_expression -> comma_expression\n", __LINE__);
			  (void) simplify_C_expression((yyvsp[(1) - (3)].expression));
			  (yyval.liste) = CONS(EXPRESSION,(yyvsp[(1) - (3)].expression),(yyvsp[(3) - (3)].liste));
			}
    break;

  case 119:
/* Line 1787 of yacc.c  */
#line 1525 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  CParserError("Parse error: error TK_COMMA comma_expression \n");
			}
    break;

  case 120:
/* Line 1787 of yacc.c  */
#line 1531 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    { (yyval.liste) = NIL; }
    break;

  case 121:
/* Line 1787 of yacc.c  */
#line 1532 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    { }
    break;

  case 122:
/* Line 1787 of yacc.c  */
#line 1537 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  push_current_C_comment();
			  push_current_C_line_number();
		      save_expression_comment_as_statement_comment();
			  (yyval.liste) = (yyvsp[(2) - (3)].liste);
			}
    break;

  case 123:
/* Line 1787 of yacc.c  */
#line 1544 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  CParserError("Parse error: TK_LPAREN error TK_RPAREN \n");
			}
    break;

  case 124:
/* Line 1787 of yacc.c  */
#line 1550 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  if(false) {
			  push_current_C_comment();
			  push_current_C_line_number();
			  }
			  (yyval.liste) = (yyvsp[(2) - (3)].liste);
			}
    break;

  case 125:
/* Line 1787 of yacc.c  */
#line 1558 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  CParserError("Parse error: TK_LPAREN error TK_RPAREN \n");
			}
    break;

  case 126:
/* Line 1787 of yacc.c  */
#line 1565 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  (yyval.liste) = (yyvsp[(2) - (3)].liste);
			}
    break;

  case 127:
/* Line 1787 of yacc.c  */
#line 1569 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  CParserError("Parse error: TK_LBRACKET error TK_RBRACKET\n");
			}
    break;

  case 128:
/* Line 1787 of yacc.c  */
#line 1578 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    { EnterScope();
			  /* To avoid some parasitic line skipping after the
			     block opening brace. May be it should be
			     cleaner to keep this eventual line-break as a
			     comment in the statement, for subtler user
			     source layout representation? */
			  discard_C_comment();
			}
    break;

  case 129:
/* Line 1787 of yacc.c  */
#line 1587 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  (yyval.statement) = MakeBlock((yyvsp[(5) - (5)].liste));
			  ExitScope();
			}
    break;

  case 130:
/* Line 1787 of yacc.c  */
#line 1594 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  (yyval.statement) = (yyvsp[(1) - (2)].statement);
			}
    break;

  case 131:
/* Line 1787 of yacc.c  */
#line 1599 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    { abort();CParserError("Parse error: error location TK_RBRACE \n"); }
    break;

  case 132:
/* Line 1787 of yacc.c  */
#line 1604 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {}
    break;

  case 133:
/* Line 1787 of yacc.c  */
#line 1611 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    { (yyval.liste) = NIL; }
    break;

  case 134:
/* Line 1787 of yacc.c  */
#line 1612 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
  statement s = make_continue_statement(entity_empty_label());
  add_pragma_strings_to_statement(s, gen_nreverse((yyvsp[(1) - (1)].liste)),false);
  gen_free_list((yyvsp[(1) - (1)].liste));
  (yyval.liste) = CONS(STATEMENT, s, NIL);
  }
    break;

  case 135:
/* Line 1787 of yacc.c  */
#line 1619 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  (yyval.liste) = CONS(STATEMENT,(yyvsp[(1) - (2)].statement),(yyvsp[(2) - (2)].liste));
			}
    break;

  case 136:
/* Line 1787 of yacc.c  */
#line 1623 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    { CParserError("gcc not implemented\n"); }
    break;

  case 137:
/* Line 1787 of yacc.c  */
#line 1627 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {}
    break;

  case 138:
/* Line 1787 of yacc.c  */
#line 1629 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    { CParserError("LABEL__ not implemented\n"); }
    break;

  case 139:
/* Line 1787 of yacc.c  */
#line 1633 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {free((yyvsp[(1) - (1)].string));}
    break;

  case 140:
/* Line 1787 of yacc.c  */
#line 1634 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {free((yyvsp[(1) - (3)].string));}
    break;

  case 141:
/* Line 1787 of yacc.c  */
#line 1639 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  // Push the comment associated with the label:
			  push_current_C_comment();
			  (yyval.string) = (yyvsp[(1) - (2)].string);
			}
    break;

  case 142:
/* Line 1787 of yacc.c  */
#line 1648 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
     /* Well, indeed this has not been tested at the time of writing since
	the _Pragma("...") is replaced by a #pragma ... in the C
	preprocessor, at least in gcc 4.4. */
     /* The pragma string has been strdup()ed in the lexer... */
     pips_debug(1, "Found _Pragma(\"%s\")\n", (yyvsp[(3) - (4)].string));
     (yyval.string) = (yyvsp[(3) - (4)].string);
   }
    break;

  case 143:
/* Line 1787 of yacc.c  */
#line 1656 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
  pips_debug(1, "Found #pragma %s\n", c_lval.string);
     (yyval.string) = c_lval.string;
   }
    break;

  case 144:
/* Line 1787 of yacc.c  */
#line 1664 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    { /* Only one pragma... The common case, return it in a list */
  pips_debug(1, "No longer pragma\n");
  (yyval.liste) = CONS(STRING, (yyvsp[(1) - (1)].string), NIL);
  }
    break;

  case 145:
/* Line 1787 of yacc.c  */
#line 1668 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
  /* Concatenate the pragma to the list of pragmas */
  (yyval.liste) = CONS(STRING,(yyvsp[(1) - (2)].string),(yyvsp[(2) - (2)].liste));
}
    break;

  case 146:
/* Line 1787 of yacc.c  */
#line 1677 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
  add_pragma_strings_to_statement((yyvsp[(2) - (2)].statement), gen_nreverse((yyvsp[(1) - (2)].liste)),
  				  false /* Do not reallocate the strings*/);
  /* Reduce the CO2 impact of this code, even there is huge memory leaks
     everywhere around in this file: */
  gen_free_list((yyvsp[(1) - (2)].liste));
  (yyval.statement) = (yyvsp[(2) - (2)].statement);
  reset_token_has_been_seen_p();
}
    break;

  case 147:
/* Line 1787 of yacc.c  */
#line 1686 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
  (yyval.statement) = (yyvsp[(1) - (1)].statement);
  reset_token_has_been_seen_p();
  }
    break;

  case 148:
/* Line 1787 of yacc.c  */
#line 1695 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  /* Null statement in C is represented as continue statement in Fortran*/
			  /* FI: the comments should be handled at
			     another level, so as not to repeat the
			     same code over and over again? */
			  string sc = get_current_C_comment();
			  int sn = get_current_C_line_number();
			  statement s = make_continue_statement(entity_empty_label());
			  statement_comments(s) = sc;
			  statement_number(s) = sn;
			  (yyval.statement) = s;
			}
    break;

  case 149:
/* Line 1787 of yacc.c  */
#line 1708 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  pips_debug(1, "Reduction %d: comma_expression TK_SEMICOLON -> statement_without_pragma\n", __LINE__);
			  statement s = statement_undefined;
			  if (gen_length((yyvsp[(1) - (2)].liste))==1) {
			    /* This uses the current comment and
			       current line number. */
			    s = ExpressionToStatement(EXPRESSION(CAR((yyvsp[(1) - (2)].liste))));
			    gen_free_list((yyvsp[(1) - (2)].liste));
			  }
			  else {
			    /* FI: I do not know how
			       expression_comment is supposed to
			       work for real comma expressions */
			    s = call_to_statement(make_call(CreateIntrinsic(COMMA_OPERATOR_NAME),(yyvsp[(1) - (2)].liste)));
			    statement_number(s) =
                              get_current_C_line_number();
			    statement_comments(s) = get_current_C_comment();
			  }
			  (yyval.statement) = flush_expression_comment(s);
			}
    break;

  case 150:
/* Line 1787 of yacc.c  */
#line 1728 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    { }
    break;

  case 151:
/* Line 1787 of yacc.c  */
#line 1729 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
  			  /* In C99 we can have a declaration anywhere!

			     Declaration returns a statement list. Maybe
			     it could be changed to return only a
			     statement? Well sometimes NIL is returned
			     here so deeper work is required for
			     this... */
                          pips_debug(1, "Reduction %d: declaration -> statement_without_pragma\n", __LINE__);
 			  list sl = (yyvsp[(1) - (1)].liste);
			  if (gen_length(sl) > 1) {
			    /* print_statements(sl); */
			    pips_internal_error("There should be no more than 1 declaration at a time here instead of %zd\n", gen_length(sl));
			  }
			  /* Extract the statement from the list and free
			     the list container: */
			  statement s = make_statement_from_statement_list_or_empty_block(sl);
			  // Necessary for comma02.c
			  // statement_comments(s) = get_current_C_comment();
			  // statement_number(s) = get_current_C_line_number();
			  (yyval.statement) = flush_expression_comment(s);
}
    break;

  case 152:
/* Line 1787 of yacc.c  */
#line 1752 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  (yyval.statement) = test_to_statement(make_test(MakeCommaExpression((yyvsp[(2) - (3)].liste)), (yyvsp[(3) - (3)].statement),
							   make_empty_block_statement()));
			  pips_assert("statement is a test", statement_test_p((yyval.statement)));
			  string sc = pop_current_C_comment();
			  int sn = pop_current_C_line_number();
			  (yyval.statement) = add_comment_and_line_number((yyval.statement), sc, sn);
			  (yyval.statement) = flush_statement_comment((yyval.statement));
			}
    break;

  case 153:
/* Line 1787 of yacc.c  */
#line 1762 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  (yyval.statement) = test_to_statement(make_test(MakeCommaExpression((yyvsp[(2) - (5)].liste)),(yyvsp[(3) - (5)].statement),(yyvsp[(5) - (5)].statement)));
			  pips_assert("statement is a test", statement_test_p((yyval.statement)));
			  string sc = pop_current_C_comment();
			  int sn = pop_current_C_line_number();
			  (yyval.statement) = add_comment_and_line_number((yyval.statement), sc, sn);
			  (yyval.statement) = flush_statement_comment((yyval.statement));
			}
    break;

  case 154:
/* Line 1787 of yacc.c  */
#line 1771 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  stack_push((char *) make_sequence(NIL),SwitchGotoStack);
			  stack_push((char *) make_basic_int(loop_counter++), LoopStack);
			  /* push_current_C_comment(); */
			}
    break;

  case 155:
/* Line 1787 of yacc.c  */
#line 1777 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  stack_push((char *)MakeCommaExpression((yyvsp[(3) - (3)].liste)),SwitchControllerStack);
			}
    break;

  case 156:
/* Line 1787 of yacc.c  */
#line 1781 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {

			  (yyval.statement) = MakeSwitchStatement((yyvsp[(5) - (5)].statement));
			  string sc = pop_current_C_comment();
			  int sn = pop_current_C_line_number();
			  (yyval.statement) = add_comment_and_line_number((yyval.statement), sc, sn);
			  //$$ = flush_statement_comment($$); SG too dangerous, maybe on a block
			  stack_pop(SwitchGotoStack);
			  stack_pop(SwitchControllerStack);
			  stack_pop(LoopStack);
			}
    break;

  case 157:
/* Line 1787 of yacc.c  */
#line 1793 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  stack_push((char *) make_basic_int(loop_counter++), LoopStack);
			  /* push_current_C_comment(); */
			}
    break;

  case 158:
/* Line 1787 of yacc.c  */
#line 1798 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  string sc = pop_current_C_comment();
			  int sn = pop_current_C_line_number();
			  pips_assert("While loop body consistent",statement_consistent_p((yyvsp[(4) - (4)].statement)));
			  (yyval.statement) = MakeWhileLoop((yyvsp[(3) - (4)].liste),(yyvsp[(4) - (4)].statement),true);
			  (yyval.statement) = add_comment_and_line_number((yyval.statement), sc, sn);
			  (yyval.statement) = flush_statement_comment((yyval.statement));
			  stack_pop(LoopStack);
			}
    break;

  case 159:
/* Line 1787 of yacc.c  */
#line 1808 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  stack_push((char *) make_basic_int(loop_counter++), LoopStack);
			  /* push_current_C_comment(); */
			}
    break;

  case 160:
/* Line 1787 of yacc.c  */
#line 1813 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  (yyval.statement) = MakeWhileLoop((yyvsp[(5) - (6)].liste),(yyvsp[(3) - (6)].statement),false);
			  /* The line number and comment are related to paren_comma_expression and not to TK_DO */
			  (void) pop_current_C_line_number();
			  (void) pop_current_C_comment();
			  stack_pop(LoopStack);
			}
    break;

  case 161:
/* Line 1787 of yacc.c  */
#line 1826 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  /* Save the comments agregated in the for close up to now: */
			  push_current_C_comment();
			}
    break;

  case 162:
/* Line 1787 of yacc.c  */
#line 1832 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  (yyval.statement) = MakeForloop((yyvsp[(2) - (9)].expression), (yyvsp[(4) - (9)].expression), (yyvsp[(6) - (9)].expression), (yyvsp[(9) - (9)].statement));
			  (yyval.statement)=flush_expression_comment((yyval.statement));
			}
    break;

  case 163:
/* Line 1787 of yacc.c  */
#line 1837 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  /* We need a new variable scope to avoid
			     conflict names between the loop index and
			     some previous upper declarations: */
                          EnterScope();
                        }
    break;

  case 164:
/* Line 1787 of yacc.c  */
#line 1848 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  /* Save the comments agregated in the for close up to now: */
			  push_current_C_comment();
			}
    break;

  case 165:
/* Line 1787 of yacc.c  */
#line 1853 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  (yyval.statement) = MakeForloopWithIndexDeclaration((yyvsp[(3) - (9)].liste), (yyvsp[(4) - (9)].expression), (yyvsp[(6) - (9)].expression), (yyvsp[(9) - (9)].statement));
			  (yyval.statement)=flush_expression_comment((yyval.statement));
			  ExitScope();
			}
    break;

  case 166:
/* Line 1787 of yacc.c  */
#line 1859 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  /* Create the statement with label comment in
			     front of it: */
			  (yyval.statement) = MakeLabeledStatement((yyvsp[(1) - (2)].string),(yyvsp[(2) - (2)].statement), pop_current_C_comment());
			  free((yyvsp[(1) - (2)].string));
			  /* ifdebug(8) { */
			  /*   pips_debug(8,"Adding label '%s' to statement:\n", $1); */
			  /*   print_statement($$); */
			  /* } */
			}
    break;

  case 167:
/* Line 1787 of yacc.c  */
#line 1870 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  (yyval.statement) = MakeCaseStatement((yyvsp[(2) - (3)].expression));
			}
    break;

  case 168:
/* Line 1787 of yacc.c  */
#line 1874 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  CParserError("case e1..e2 : not implemented\n");
			}
    break;

  case 169:
/* Line 1787 of yacc.c  */
#line 1878 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  (yyval.statement) = MakeDefaultStatement();
			}
    break;

  case 170:
/* Line 1787 of yacc.c  */
#line 1882 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  /* $$ =  call_to_statement(make_call(CreateIntrinsic(C_RETURN_FUNCTION_NAME),NIL)); */
			  if(!get_bool_property("C_PARSER_RETURN_SUBSTITUTION"))
                          (yyval.statement) = make_statement(entity_empty_label(),
			                      get_current_C_line_number(),
			                      STATEMENT_ORDERING_UNDEFINED,
			                      get_current_C_comment(),
			                      call_to_instruction(make_call(CreateIntrinsic(C_RETURN_FUNCTION_NAME),NIL)),
					      NIL, string_undefined,
			                      empty_extensions (), make_synchronization_none());
			  else
			    (yyval.statement) = C_MakeReturnStatement(NIL,
						       get_current_C_line_number(),
						       get_current_C_comment());
			  /*
			    $$ = make_statement(entity_empty_label(),
						get_current_C_line_number(),
						STATEMENT_ORDERING_UNDEFINED,
						get_current_C_comment(),
						C_MakeReturn(NIL),
						NIL,
						string_undefined,
						empty_extensions());
			  */

			  statement_consistent_p((yyval.statement));
			}
    break;

  case 171:
/* Line 1787 of yacc.c  */
#line 1910 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  /* $$ =  call_to_statement(make_call(CreateIntrinsic(C_RETURN_FUNCTION_NAME),$2)); */
			  list el = (yyvsp[(2) - (3)].liste);
			  expression res = expression_undefined;
			  if(gen_length(el)>1) {
			    res = make_call_expression(CreateIntrinsic(COMMA_OPERATOR_NAME), el);
			    el = CONS(EXPRESSION, res, NIL);
			  }
			  else if(gen_length(el)==1)
			    res = EXPRESSION(CAR((yyvsp[(2) - (3)].liste)));

			  if(expression_reference_p(res)) {
			    reference r = expression_reference(res);
			    entity v = reference_variable(r);
			    type t = ultimate_type(entity_type(v));
			    if(type_functional_p(t)) {
			      /* pointers to functions, hence
				 functions can be returned in C */
			      /* FI: relationship with undeclared? */
			      /*
			      c_parser_user_warning("Ill. returned value: reference to function \"%s\""
                                                " or variable \"%s\" not declared\n",
						entity_user_name(v), entity_user_name(v));
			      CParserError("Ill. return expression");
			      */
			    }
			  }
			  if(!get_bool_property("C_PARSER_RETURN_SUBSTITUTION"))
                          (yyval.statement) = make_statement(entity_empty_label(),
			                      get_current_C_line_number(),
			                      STATEMENT_ORDERING_UNDEFINED,
			                      get_current_C_comment(),
			                      make_instruction(is_instruction_call,
					      make_call(CreateIntrinsic(C_RETURN_FUNCTION_NAME), el)),
					      NIL, string_undefined, empty_extensions (), make_synchronization_none());
			  else
			    (yyval.statement) = C_MakeReturnStatement(el,
						       get_current_C_line_number(),
						       get_current_C_comment());
			  /*
			    $$ = make_statement(entity_empty_label(),
						get_current_C_line_number(),
						STATEMENT_ORDERING_UNDEFINED,
						get_current_C_comment(),
						C_MakeReturn($2),
						NIL,
						string_undefined,
						empty_extensions());
			  */
			  (yyval.statement)=flush_expression_comment((yyval.statement));
			  statement_consistent_p((yyval.statement));
			}
    break;

  case 172:
/* Line 1787 of yacc.c  */
#line 1963 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  (yyval.statement) = MakeBreakStatement(get_current_C_comment());
			}
    break;

  case 173:
/* Line 1787 of yacc.c  */
#line 1967 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  (yyval.statement) = MakeContinueStatement(get_current_C_comment());
			}
    break;

  case 174:
/* Line 1787 of yacc.c  */
#line 1971 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  (yyval.statement) = MakeGotoStatement((yyvsp[(2) - (3)].string));
			  free((yyvsp[(2) - (3)].string));
			}
    break;

  case 175:
/* Line 1787 of yacc.c  */
#line 1976 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  CParserError("GOTO * exp not implemented\n");
			}
    break;

  case 176:
/* Line 1787 of yacc.c  */
#line 1980 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    { 
							call c  = make_call(
									entity_intrinsic(ASM_FUNCTION_NAME),
									CONS(EXPRESSION,entity_to_expression(
										make_C_constant_entity((yyvsp[(4) - (7)].string), is_basic_string, 0)
									),NIL)
								);
			  				free((yyvsp[(4) - (7)].string));
							(yyval.statement) = make_statement(
								entity_empty_label(),
								get_current_C_line_number(),
								STATEMENT_ORDERING_UNDEFINED,
			   					get_current_C_comment(),
								make_instruction_call(c),
								NIL, string_undefined,
			   					empty_extensions(), make_synchronization_none());
						}
    break;

  case 177:
/* Line 1787 of yacc.c  */
#line 1998 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    { CParserError("ASM not implemented\n"); }
    break;

  case 178:
/* Line 1787 of yacc.c  */
#line 2000 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  CParserError("Parse error: error location TK_SEMICOLON\n");
			}
    break;

  case 179:
/* Line 1787 of yacc.c  */
#line 2008 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  /* Number the loops in prefix depth-first: */
			  stack_push((char *) make_basic_int(loop_counter++),
				     LoopStack);
                          /* Record the line number of thw "for" keyword: */
			  push_current_C_line_number();
			  /* Try to save a max of comments. The issue is
			     that opt_expression's afterwards can reset
			     the comments if there is a comma_expression
			     in them. So at least preserve the commemts
			     before the for.

			     Issue trigered by several examples such as
			     validation/Semantics-New/do01.tpips

			     But I think now (RK, 2011/02/05 :-) ) that in
			     a source-to-source compiler comments should
			     appear *explicitly* in the parser syntax and
			     not be dealt by some side effects in the
			     lexer as now in PIPS with some stacks and so
			     on.
			  */
			  push_current_C_comment();
			}
    break;

  case 181:
/* Line 1787 of yacc.c  */
#line 2038 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  pips_debug(1, "Reduction %d: decl_spec_list init_declarator_list TK_SEMICOLON -> declaration\n", __LINE__);

			  list el1 = (yyvsp[(1) - (3)].liste);
			  list el2 = (yyvsp[(2) - (3)].liste);
			  list el12 = gen_nconc(el1,el2);
			  statement s = statement_undefined;

			  pips_assert("el1 is an entity list", entities_p(el1));
			  pips_assert("el2 is an entity list", entities_p(el2));
			  pips_assert("Variable in el1 has not been declared before", !gen_in_list_p(el1, el2));

			  if(!ENDP(el12)) {
			    list el0 = GetDerivedEntityDeclarations();
			    FOREACH(ENTITY, e, el0) {
			      if(!gen_in_list_p(e, el12))
				el12 = CONS(ENTITY, e, el12);
			    }
			    gen_free_list(el0);

			    ifdebug(8) {
			      fprintf(stderr, "At %d, make_declarations_statement for ", __LINE__);
			      print_entities(el12);
			      fprintf(stderr, "\n");
			    }

			    int sn = get_current_C_line_number();
			    string sc = get_current_C_comment();
			    s = make_declarations_statement(el12, sn, sc);
			    initialization_expressions = add_prettyprint_control_list_to_declaration_statement(s, initialization_expressions);

			    ifdebug(1) {
			      fprintf(stderr, "New declaration statement for entities: ");
			      print_entities(el12);
			      fprintf(stderr, "\n");
			    }
			    pips_assert("no duplicate declaration",
					gen_once_p(el12));
			  }
			  else {
			    pips_internal_error("Unexpected case");
			  }

			  UpdateEntities(el2,ContextStack,FormalStack,FunctionStack,OffsetStack,is_external,true);
			  PopContext();
			  remove_entity_type_stacks(el12);
			  CleanUpEntities(el12);
			  (yyval.liste) = CONS(STATEMENT,s,NIL);
			  reset_token_has_been_seen_p();
			}
    break;

  case 182:
/* Line 1787 of yacc.c  */
#line 2089 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  pips_debug(1, "Reduction %d: decl_spec_list TK_SEMICOLON -> declaration\n", __LINE__);
			  list dl = (yyvsp[(1) - (2)].liste);
			  FOREACH(ENTITY, e, dl) {
			    value v = entity_initial(e);
			    if(value_undefined_p(v))
			      entity_initial(e) = make_value_unknown();
			  }
			  // FI: we build a declaration statement
			  // for each field of an enum...
			  int sn = get_current_C_line_number();
			  string sc = get_current_C_comment();
			  pips_debug(8, "New declaration statement at line %d\n", __LINE__);
			  statement s = make_declarations_statement(dl, sn, sc);
                          initialization_expressions = add_prettyprint_control_list_to_declaration_statement(s, initialization_expressions);
			  reset_token_has_been_seen_p();
			  //UpdateEntities(dl,ContextStack,FormalStack,FunctionStack,OffsetStack,is_external,true);
			  PopContext();
			  ResetDerivedEntityDeclarations();
			  (yyval.liste) = CONS(STATEMENT,s, NIL);
			  BREAKPOINT;
			}
    break;

  case 183:
/* Line 1787 of yacc.c  */
#line 2115 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {

			  (yyval.liste) = CONS(ENTITY,(yyvsp[(1) - (1)].entity),NIL);
			}
    break;

  case 184:
/* Line 1787 of yacc.c  */
#line 2120 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  (yyval.liste) = CONS(ENTITY,(yyvsp[(1) - (3)].entity),(yyvsp[(3) - (3)].liste));
			}
    break;

  case 185:
/* Line 1787 of yacc.c  */
#line 2126 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
                          /* The default initial value is often zero,
                              but not so for formal parameters or
                              functions */
                          if(value_undefined_p(entity_initial((yyvsp[(1) - (1)].entity))))
			    entity_initial((yyvsp[(1) - (1)].entity)) = make_value_unknown();
			  add_initialization_expression(0);
			  pips_debug(1, "declarator to init_declarator for entity %s\n", entity_name((yyvsp[(1) - (1)].entity)));
                        }
    break;

  case 186:
/* Line 1787 of yacc.c  */
#line 2136 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  entity v = (yyvsp[(1) - (3)].entity);
			  expression nie = (yyvsp[(3) - (3)].expression);

			  if(expression_undefined_p(nie)) {
			    /* Do nothing, leave the initial field of entity as it is. */
			    c_parser_user_warning("Undefined init_expression, why not use value_unknown?\n");
			    add_initialization_expression(0);
			  pips_debug(1, "declarator TK_EQ init_expression to init_declarator, with expression undefined\n");
			  }
			  else {
			    (void) simplify_C_expression(nie);
			    /* Put init_expression in the initial value of entity declarator*/
			    set_entity_initial(v, nie);
			    add_initialization_expression(1);
			    pips_debug(1, "declarator TK_EQ init_expression to init_declarator\n");
			  }
			}
    break;

  case 187:
/* Line 1787 of yacc.c  */
#line 2157 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			 if(stack_empty_p(ContextStack)) {
                           ycontext = CreateDefaultContext();
			   pips_debug(8, "new default context %p with scope \"%s\"\n", ycontext,
				      c_parser_context_scope(ycontext));
			 }
			 else {
			   /* Copy may be excessive as only the scope needs to be preserved...*/
			   //ycontext = copy_c_parser_context((c_parser_context)stack_head(ContextStack));
			   ycontext = GetContextCopy();
			   /* FI: You do not want to propagate
			      qualifiers */
			   gen_full_free_list(c_parser_context_qualifiers(ycontext));
			   c_parser_context_qualifiers(ycontext) = NIL;
			   /* How can these two problems occur since
			      ycontext is only a copy of the
			      ContextStack's head? Are we in the
			      middle of a stack_push() /stack_pop()?
			      The previous policy was to always
			      allocate a new ycontext, regardless of
			      the stack state */
			   /* FI: a bit afraid of freeing the past type if any */
			   c_parser_context_type(ycontext) = type_undefined;
			   /* A new context is entered: no longer typedef as in
			    "typedef int f(int a)" when we hit "int a"*/
			   c_parser_context_typedef(ycontext) = false;
			   /* FI: sometimes, the scope is erased and lost */
			   //if(strcmp(c_parser_context_scope(ycontext), "TOP-LEVEL:")==0)
			   //  c_parser_context_scope(ycontext) = empty_scope();
			   /* Finally, to avoid problems!*/
			   //c_parse
			   //r_context_scope(ycontext) = empty_scope();

			   /* Only block scope information is inherited */
			   if(!string_block_scope_p(c_parser_context_scope(ycontext))
			      && !string_struct_scope_p(c_parser_context_scope(ycontext))) {
			     /* FI: too primitive; we need to push
				and pop contexts more than to update
				them.

				Problem with "extern f(x), g(y);". f
				anf g are definitvely top-level, but x
				and y must be searched in the current
				scope first.
			     */
			     pips_debug(8, "Reset modified scope \"%s\"\n",
					c_parser_context_scope(ycontext));
				 free(c_parser_context_scope(ycontext));
			     c_parser_context_scope(ycontext) = empty_scope();
			   }
			   pips_debug(8, "new context %p with scope \"%s\" copied from context %p (stack size=%d)\n",
				      ycontext,
				      c_parser_context_scope(ycontext),
				      stack_head(ContextStack),
				      stack_size(ContextStack));
                         }
                        }
    break;

  case 188:
/* Line 1787 of yacc.c  */
#line 2214 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {pips_debug(1, "Reduction %d: my_decl_spec_list -> decl_spec_list\n", __LINE__); (yyval.liste) = (yyvsp[(2) - (2)].liste);}
    break;

  case 189:
/* Line 1787 of yacc.c  */
#line 2220 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  /* Add TYPEDEF_PREFIX to entity name prefix and make it a rom storage */
			  c_parser_context_typedef(ycontext) = true;
			  c_parser_context_storage(ycontext) = make_storage_rom();
			  //pips_assert("CONTINUE for declarations", continue_statements_p($2));
			  pips_assert("Entity list for declarations", entities_p((yyvsp[(2) - (2)].liste)));
			  (yyval.liste) = (yyvsp[(2) - (2)].liste);
			}
    break;

  case 190:
/* Line 1787 of yacc.c  */
#line 2229 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  /* This can be a variable or a function, whose storage is ram or return  */
			  /* What is the scope in cyacc.y of this
			     scope modification? Too much because the
			     TOP_LEVEL scope is going to be used for
			     argument types as well... */
			  pips_debug(8, "Scope of context %p forced to TOP_LEVEL_MODULE_NAME\n", ycontext);
			  free(c_parser_context_scope(ycontext));
			  c_parser_context_scope(ycontext) = strdup(concatenate(TOP_LEVEL_MODULE_NAME,
									       MODULE_SEP_STRING,NULL));
			  pips_assert("Entity list for declarations", entities_p((yyvsp[(2) - (2)].liste)));
			  /* FI: because of C laxity about
			     redeclarations in compilation unit, the
			     EXTERN information should be carried by
			     the declaration statement to be able to
			     regenerate precise source-to-source. */
			  // fprintf(stderr, "Force extern declaration.\n");
			  // statement dls = STATEMENT(CAR($2));
			  set_prettyprint_control_list_to_extern();
			  (yyval.liste) = (yyvsp[(2) - (2)].liste);
			}
    break;

  case 191:
/* Line 1787 of yacc.c  */
#line 2251 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
                          pips_debug(1, "Reduction %d: TK_STATIC decl_spec_list_opt -> my_decl_spec_list\n", __LINE__);
			  c_parser_context_static(ycontext) = true;
			  pips_assert("Entity list for declarations", entities_p((yyvsp[(2) - (2)].liste)));
			  (yyval.liste) = (yyvsp[(2) - (2)].liste);
			}
    break;

  case 192:
/* Line 1787 of yacc.c  */
#line 2258 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  /* Add to type variable qualifiers */
			  c_parser_context_qualifiers(ycontext) = gen_nconc(c_parser_context_qualifiers(ycontext),
									   CONS(QUALIFIER,make_qualifier_thread(),NIL));
			  pips_assert("Entity list for declarations", entities_p((yyvsp[(2) - (2)].liste)));
			  (yyval.liste) = (yyvsp[(2) - (2)].liste);
			}
    break;

  case 193:
/* Line 1787 of yacc.c  */
#line 2266 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  /* Make dynamic storage for current entity */
			  c_parser_context_qualifiers(ycontext) = gen_nconc(c_parser_context_qualifiers(ycontext),
									   CONS(QUALIFIER,make_qualifier_auto(),NIL));
			  pips_assert("Entity list for declarations", entities_p((yyvsp[(2) - (2)].liste)));
			  (yyval.liste) = (yyvsp[(2) - (2)].liste);
			}
    break;

  case 194:
/* Line 1787 of yacc.c  */
#line 2274 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  /* Add to type variable qualifiers */
			  c_parser_context_qualifiers(ycontext) = gen_nconc(c_parser_context_qualifiers(ycontext),
									   CONS(QUALIFIER,make_qualifier_register(),NIL));
			  pips_assert("Entity list for declarations", entities_p((yyvsp[(2) - (2)].liste)));
			  (yyval.liste) = (yyvsp[(2) - (2)].liste);
			}
    break;

  case 195:
/* Line 1787 of yacc.c  */
#line 2283 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  pips_debug(1, "Reduction %d: type_spec decl_spec_list_opt_no_named -> my_decl_spec_list\n", __LINE__);
			  BREAKPOINT;
			  // el contains only hidden internal PIPS
			  // entities, but some of them at least must
			  // be seen by the prettyprinter
			  list el = (yyvsp[(1) - (2)].liste); // entity list
			  list sl = (yyvsp[(2) - (2)].liste); // entity list
			  list rl = list_undefined;
			  pips_assert("el contains an entity list", entities_p(el));
			  pips_assert("sl contains an entity list", entities_p(sl));
			  if(ENDP(el)) {
			    rl = sl;
			  }
			  else if(ENDP(sl)) {
			    //BREAKPOINT;
			    rl = el;
			    ifdebug(8) {
			      //pips_debug(8, "New declaration statement for entities:\n");
			      print_entities(el);
			      fprintf(stderr, "\n");
			    }
			  }
			  else if(gen_length(sl)==1) {
			    // FI: I'm not sure it ever happens
			    // statement s = STATEMENT(CAR(sl));
			    ifdebug(8) {
			      //pips_debug(8, "Previous (unexpected) continue statement for entities: ");
			      //print_entities(statement_declarations(s));
			      print_entities(el);
			      fprintf(stderr, "\n");
			      pips_debug(8, "New entities added: ");
			      print_entities(el);
			      fprintf(stderr, "\n");
			      // rl = sl;
			    }
			    //statement_declarations(s) =
			    //gen_nconc(el, statement_declarations(s));
			    rl = gen_nconc(el, sl);
			  }
			  else {
			    pips_internal_error("Multiple statements not expected\n");
			    /* statement s = */
			    /*   make_continue_statement(entity_empty_label()); */
			    /* statement_declarations(s) = el; */
			    // $$ = gen_nconc($1,$2);
			    //$$ = $2;
			    //rl = gen_nconc(CONS(STATEMENT, s, NIL),sl);
			  }
			  (yyval.liste) = rl;
			}
    break;

  case 196:
/* Line 1787 of yacc.c  */
#line 2336 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  c_parser_user_warning("Keyword \"inline\" ignored\n");
			  pips_assert("Entity list for declarations", entities_p((yyvsp[(2) - (2)].liste)));
			  (yyval.liste) = (yyvsp[(2) - (2)].liste);
			}
    break;

  case 197:
/* Line 1787 of yacc.c  */
#line 2342 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  list ql = c_parser_context_qualifiers(ycontext);
			  qualifier nq = (yyvsp[(1) - (2)].qualifier);

			  c_parser_context_qualifiers(ycontext)
			    = insert_qualifier(ql, nq);

			  pips_assert("Entity list for declarations", entities_p((yyvsp[(2) - (2)].liste)));
			  (yyval.liste) = (yyvsp[(2) - (2)].liste);
			}
    break;

  case 198:
/* Line 1787 of yacc.c  */
#line 2354 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  CParserError("CIL AT not implemented\n");
			}
    break;

  case 199:
/* Line 1787 of yacc.c  */
#line 2363 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  //stack_push((char *) ycontext, ContextStack);
			  PushContext(ycontext);
			  (yyval.liste) = NIL;
			}
    break;

  case 200:
/* Line 1787 of yacc.c  */
#line 2368 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    { }
    break;

  case 201:
/* Line 1787 of yacc.c  */
#line 2377 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  pips_debug(1, "Reduction %d: empty -> decl_spec_list_opt_no_named\n", __LINE__);
			  // decl48.c: ycontext is not good because
			  // the current scope information is lost.
			  // I do not want to remove the Push to keep
			  // the Push/Pop balance ok
			  //PushContext(ycontext);
			  if(stack_empty_p(ContextStack))
			    PushContext(ycontext);
			  else {
			    c_parser_context y = GetContext();
			    string stf = (c_parser_context_scope(ycontext));
			    c_parser_context_scope(ycontext) =
			      strdup(c_parser_context_scope(y));
				free(stf);
			    PushContext(ycontext);
			  }
                          (yyval.liste) = NIL;
			}
    break;

  case 202:
/* Line 1787 of yacc.c  */
#line 2396 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {pips_debug(1, "Reduction %d: my_decl_spec_list -> decl_spec_list_opt_no_named\n", __LINE__);
 }
    break;

  case 203:
/* Line 1787 of yacc.c  */
#line 2403 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  c_parser_context_type(ycontext) = make_type_void(NIL);
			  (yyval.liste) = NIL;
                        }
    break;

  case 204:
/* Line 1787 of yacc.c  */
#line 2408 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  c_parser_context_type(ycontext) = make_standard_integer_type(c_parser_context_type(ycontext),
										      DEFAULT_CHARACTER_TYPE_SIZE);
			  (yyval.liste) = NIL;
			}
    break;

  case 205:
/* Line 1787 of yacc.c  */
#line 2414 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  c_parser_context_type(ycontext) = make_standard_integer_type(c_parser_context_type(ycontext),
										      DEFAULT_SHORT_INTEGER_TYPE_SIZE);
			  (yyval.liste) = NIL;
			}
    break;

  case 206:
/* Line 1787 of yacc.c  */
#line 2420 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
                          pips_debug(1, "Reduction %d: TK_INT -> type_spec\n", __LINE__);
			  if (c_parser_context_type(ycontext) == type_undefined)
			    {
			      variable v = make_variable(make_basic_int(DEFAULT_INTEGER_TYPE_SIZE),NIL,NIL);
			      c_parser_context_type(ycontext) = make_type_variable(v);
			    }
			  (yyval.liste) = NIL;
			}
    break;

  case 207:
/* Line 1787 of yacc.c  */
#line 2430 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
                          pips_debug(1, "Reduction %d: TK_INT128 -> type_spec\n", __LINE__);
			  if (c_parser_context_type(ycontext) == type_undefined)
			    {
			      variable v = make_variable(make_basic_int(DEFAULT_LONG_LONG_LONG_INTEGER_TYPE_SIZE),NIL,NIL);
			      c_parser_context_type(ycontext) = make_type_variable(v);
			    }
			  (yyval.liste) = NIL;
			}
    break;

  case 208:
/* Line 1787 of yacc.c  */
#line 2440 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
                          pips_debug(1, "Reduction %d: TK_UINT128 -> type_spec\n", __LINE__);
			  if (c_parser_context_type(ycontext) == type_undefined)
			    {
			      variable v = make_variable(make_basic_int(DEFAULT_LONG_LONG_LONG_INTEGER_TYPE_SIZE+10),NIL,NIL);
			      c_parser_context_type(ycontext) = make_type_variable(v);
			    }
			  (yyval.liste) = NIL;
			}
    break;

  case 209:
/* Line 1787 of yacc.c  */
#line 2450 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  if (c_parser_context_type(ycontext) == type_undefined)
			    {
			      variable v = make_variable(make_basic_complex(DEFAULT_COMPLEX_TYPE_SIZE),NIL,NIL);
			      c_parser_context_type(ycontext) = make_type_variable(v);
			    }
			  else {
			    /* Can be qualified by float, double and long double */
			    type t = c_parser_context_type(ycontext);
			    variable v = type_variable(t);
			    basic b = variable_basic(v);

			    pips_assert("prefix is for type variable",type_variable_p(t));
			    if(basic_float_p(b)) {
			      basic_tag(b) = is_basic_complex;
			      basic_complex(b) = 2*basic_complex(b);
			      if(basic_complex(b)==DEFAULT_COMPLEX_TYPE_SIZE)
				basic_complex(b) += 1;
			    }
			  }
			  (yyval.liste) = NIL;
			}
    break;

  case 210:
/* Line 1787 of yacc.c  */
#line 2473 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  c_parser_context_type(ycontext) = make_standard_long_integer_type(c_parser_context_type(ycontext));
			  (yyval.liste) = NIL;
			}
    break;

  case 211:
/* Line 1787 of yacc.c  */
#line 2478 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  variable v = make_variable(make_basic_float(DEFAULT_REAL_TYPE_SIZE),NIL,NIL);
			  c_parser_context_type(ycontext) = make_type_variable(v);
			  (yyval.liste) = NIL;
			}
    break;

  case 212:
/* Line 1787 of yacc.c  */
#line 2484 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  variable v = variable_undefined;
			  type t = c_parser_context_type(ycontext);

			  if(type_undefined_p(t))
			    v = make_variable(make_basic_float(DEFAULT_DOUBLEPRECISION_TYPE_SIZE),NIL,NIL);
			  else {
			    if(default_complex_type_p(t)) {
			      c_parser_user_warning("'complex double' declaration is not in the C99 standard but we accept it. You should use 'double complex' instead.\n"
);
			      v = make_variable(make_basic_complex(DEFAULT_DOUBLECOMPLEX_TYPE_SIZE), NIL, NIL);
			    }
			    /* This secondary test is probably
			       useless. See the case of TK_COMPLEX. */
			    else if(standard_long_integer_type_p(t))
			      v = make_variable(make_basic_float(DEFAULT_QUADPRECISION_TYPE_SIZE),NIL,NIL);
			    else
			      /* FI: we should probably have a user
				 or internal error here since we
				 ignore the beginning of the type declaration*/
			      v = make_variable(make_basic_float(DEFAULT_DOUBLEPRECISION_TYPE_SIZE),NIL,NIL);
			    free_type(t);
			  }
			  c_parser_context_type(ycontext) = make_type_variable(v);
			  (yyval.liste) = NIL;
			}
    break;

  case 213:
/* Line 1787 of yacc.c  */
#line 2511 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  /* see the IR document or ri-util.h for explanation */
			  int size = DEFAULT_INTEGER_TYPE_SIZE;
			  type t_old = c_parser_context_type(ycontext);
			  if(!type_undefined_p(t_old)) {
			    // FI: memory leak for t_old
			    variable v_old = type_variable(t_old);
			    basic b_old = variable_basic(v_old);
			    if(basic_int_p(b_old))
			      size = basic_int(b_old);
			    else
			      pips_internal_error("???");
			  }
			  variable v = make_variable(make_basic_int(DEFAULT_SIGNED_TYPE_SIZE*10+
								    size),NIL,NIL);
			  c_parser_context_type(ycontext) = make_type_variable(v);
			  (yyval.liste) = NIL;
			}
    break;

  case 214:
/* Line 1787 of yacc.c  */
#line 2530 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  int size = DEFAULT_INTEGER_TYPE_SIZE;
			  type t_old = c_parser_context_type(ycontext);
			  if(!type_undefined_p(t_old)) {
			    // FI: memory leak for t_old
			    variable v_old = type_variable(t_old);
			    basic b_old = variable_basic(v_old);
			    if(basic_int_p(b_old))
			      size = basic_int(b_old);
			    else
			      pips_internal_error("???");
			  }
			  variable v = make_variable(make_basic_int(DEFAULT_UNSIGNED_TYPE_SIZE*10+
								    size),NIL,NIL);
			  c_parser_context_type(ycontext) = make_type_variable(v);
			  (yyval.liste) = NIL;
			}
    break;

  case 215:
/* Line 1787 of yacc.c  */
#line 2548 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  pips_debug(1, "Reduction %d: TK_STRUCT id_or_typename -> type_spec\n", __LINE__);
			  // FI: this next call is now useless
			  set_prettyprint_control_list_to_dummy();
			  /* Find the entity associated to the struct, current scope can be [file%][module:][block]*/
			  entity ent = FindOrCreateEntityFromLocalNameAndPrefix((yyvsp[(2) - (2)].string),STRUCT_PREFIX,is_external);
			  /* Specify the type of the variable that follows this declaration specifier */
			  variable v = make_variable(make_basic_derived(ent),NIL,NIL);
			  /* To handle mesa.c (SPEC 2000 benchmark)
			     We have struct HashTable in a file, but do not know its structure and scope,
			     because it is declared in other file  */
			  if (type_undefined_p(entity_type(ent)))
			    entity_type(ent) = make_type_struct(NIL);
			  if (storage_undefined_p(entity_storage(ent)))
			    entity_storage(ent) = make_storage_rom();
			  c_parser_context_type(ycontext) = make_type_variable(v);
			  /* Declaration statement "struct s;"
			     disappears with $$ = NIL... See for
			     instance decl68.c. A place holder
			     variable is added, just in case. */
			  /* This may be useless, but will be fixed by
			     make_declarations_statement() */
			  entity phv = make_place_holder_variable(ent);
			  list dl = list_undefined;
			  if(entity_undefined_p(phv)) {
			    dl = CONS(ENTITY,ent,NIL);
			  }
			  else {
			    add_initialization_expression(0);
			    dl = CONS(ENTITY,ent,CONS(ENTITY, phv, NIL));
			  }
			  (yyval.liste) = dl;
			}
    break;

  case 216:
/* Line 1787 of yacc.c  */
#line 2582 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  code c = make_code(NIL,(yyvsp[(2) - (3)].string),sequence_undefined,NIL, make_language_c());
			  stack_push((char *) c, StructNameStack);
			}
    break;

  case 217:
/* Line 1787 of yacc.c  */
#line 2587 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  pips_debug(1, "Reduction %d: TK_STRUCT id_or_typename TK_LBRACE struct_decl_list TK_RBRACE -> type_spec\n", __LINE__);
			  /* field list, which may also contain nested
			     derived entities */
			  list fl = (yyvsp[(5) - (6)].liste);
			  /* Create the struct entity */
			  entity ent = MakeDerivedEntity((yyvsp[(2) - (6)].string),fl,is_external,is_type_struct);
			  /* Record the declaration of the struct
			     entity */
			  RecordDerivedEntityDeclaration(ent);
			  /* Specify the type of the variable that follows this declaration specifier*/
			  variable v = make_variable(make_basic_derived(ent),NIL,NIL);
			  /* Take from $5 the struct/union entities */
			  list le = TakeDerivedEntities(fl);
			  list rl = gen_in_list_p(ent, le)?
			    le : gen_nconc(le,CONS(ENTITY,ent,NIL));
			  /* Fields do not need to appear in the
			     declaration list, but they are used later
			     to decide which derived entities are
			     defined and which ones are used. */
			  FOREACH(ENTITY, f, fl) {
			    if(entity_field_p(f) && !gen_in_list_p(f,rl))
			      rl = gen_nconc(rl, CONS(ENTITY, f, NIL));
			  }
			  c_parser_context_type(ycontext) = make_type_variable(v);
			  stack_pop(StructNameStack);
			  BREAKPOINT;
			  //add_initialization_expression(1);
			  (yyval.liste) = rl;
			}
    break;

  case 218:
/* Line 1787 of yacc.c  */
#line 2618 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
              string istr = int2a(derived_counter++);
			  code c = make_code(NIL,strdup(concatenate(DUMMY_STRUCT_PREFIX,
								    istr,NULL)),sequence_undefined, NIL, make_language_c());
              free(istr);
			  stack_push((char *) c, StructNameStack);
                        }
    break;

  case 219:
/* Line 1787 of yacc.c  */
#line 2626 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  pips_debug(1, "Reduction %d: TK_STRUCT TK_LBRACE struct_decl_list TK_RBRACE -> type_spec\n", __LINE__);
			  /* Create the struct entity with unique name s */
			  string s = code_decls_text((code) stack_head(StructNameStack));
			  list el = (yyvsp[(4) - (5)].liste);
			  pips_assert("el is an entity list", entities_p(el));
			  entity ent = MakeDerivedEntity(s,el,is_external,is_type_struct);
			  variable v = make_variable(make_basic_derived(ent),NIL,NIL);
			  pips_assert("el is an entity list", entities_p(el));
			  /* Take from el the struct/union entities */
			  list le = TakeDerivedEntities(el);
			  list rl = gen_nconc(le,CONS(ENTITY,ent,NIL));
			  c_parser_context_type(ycontext) = make_type_variable(v);
			  stack_pop(StructNameStack);
			  BREAKPOINT;
			  //add_initialization_expression(1);
			  (yyval.liste) = rl;
			}
    break;

  case 220:
/* Line 1787 of yacc.c  */
#line 2645 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  set_prettyprint_control_list_to_dummy();
			  /* Find the entity associated to the union, current scope can be [file%][module:][block]*/
			  entity ent = FindOrCreateEntityFromLocalNameAndPrefix((yyvsp[(2) - (2)].string),UNION_PREFIX,is_external);
			  /* Specify the type of the variable that follows this declaration specifier */
			  variable v = make_variable(make_basic_derived(ent),NIL,NIL);
			  if (type_undefined_p(entity_type(ent)))
			    entity_type(ent) = make_type_union(NIL);
			  if (storage_undefined_p(entity_storage(ent)))
			    entity_storage(ent) = make_storage_rom();
			  c_parser_context_type(ycontext) = make_type_variable(v);
			  /* This may be useless, but will be fixed by
			     make_declarations_statement() */
			  entity phv = make_place_holder_variable(ent);
			  list dl = list_undefined;
			  if(entity_undefined_p(phv)) {
			    dl = CONS(ENTITY,ent,NIL);
			  }
			  else {
			    add_initialization_expression(0);
			    dl = CONS(ENTITY,ent,CONS(ENTITY, phv, NIL));
			  }
			  //list dl = CONS(ENTITY, ent, NIL);
			  (yyval.liste) = dl;
			}
    break;

  case 221:
/* Line 1787 of yacc.c  */
#line 2671 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  code c = make_code(NIL,(yyvsp[(2) - (3)].string),sequence_undefined, NIL, make_language_c());
			  stack_push((char *) c, StructNameStack);
			}
    break;

  case 222:
/* Line 1787 of yacc.c  */
#line 2676 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  list fl = (yyvsp[(5) - (6)].liste);
			  entity ent = MakeDerivedEntity((yyvsp[(2) - (6)].string),fl,is_external,is_type_union);
			  variable v = make_variable(make_basic_derived(ent),NIL,NIL);
			  /* Take from $5 the indirectly declared
			     struct/union entities as in "struct {struct ... ". */
			  // FI: struct are treated much more carefully to avoid
			  // multiple occurences of one entity
			  list le = TakeDerivedEntities((yyvsp[(5) - (6)].liste));
			  list rl = gen_nconc(le,CONS(ENTITY,ent,NIL));
			  //rl = gen_nconc(rl, fl);
			  //rl = gen_nconc(rl, le);
			  c_parser_context_type(ycontext) = make_type_variable(v);
			  stack_pop(StructNameStack);
			  (yyval.liste) = rl;
			}
    break;

  case 223:
/* Line 1787 of yacc.c  */
#line 2693 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  string n = int2a(derived_counter++);
			  code c = make_code(NIL,
					     strdup(concatenate(DUMMY_UNION_PREFIX,n,NULL)),
					     sequence_undefined,
					     NIL,
					     make_language_c());
			  free(n);
			  stack_push((char *) c, StructNameStack);
                        }
    break;

  case 224:
/* Line 1787 of yacc.c  */
#line 2704 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  /* Create the union entity with unique name */
			  string s = code_decls_text((code) stack_head(StructNameStack));
			  entity ent = MakeDerivedEntity(s,(yyvsp[(4) - (5)].liste),is_external,is_type_union);
			  RecordDerivedEntityDeclaration(ent);
			  variable v = make_variable(make_basic_derived(ent),NIL,NIL);
			  /* Take from $4 the struct/union entities */
			  (void)TakeDerivedEntities((yyvsp[(4) - (5)].liste));
			  //$$ = gen_nconc(le,CONS(ENTITY,ent,NIL));
			  //$$ = CONS(ENTITY,ent,le);
			  // entity phv = make_place_holder_variable(ent));
			  // list rl = CONS(ENTITY,ent,CONS(ENTITY, phv, NIL));
			  list rl = CONS(ENTITY,ent,NIL);
			  c_parser_context_type(ycontext) = make_type_variable(v);
			  stack_pop(StructNameStack);
			  (yyval.liste) = rl;
			}
    break;

  case 225:
/* Line 1787 of yacc.c  */
#line 2722 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  pips_debug(1, "Reduction %d: TK_ENUM id_or_typename -> type_spec\n", __LINE__);
			  set_prettyprint_control_list_to_dummy();
                          /* Find the entity associated to the enum */
			  entity ent = FindOrCreateEntityFromLocalNameAndPrefix((yyvsp[(2) - (2)].string),ENUM_PREFIX,is_external);
			  /* Specify the type of the variable that follows this declaration specifier */
			  variable v = make_variable(make_basic_derived(ent),NIL,NIL);
			  if (type_undefined_p(entity_type(ent)))
			    entity_type(ent) = make_type_enum(NIL);
			  /* FI: What should the initial value be? */
			  if (value_undefined_p(entity_initial(ent)))
			    entity_initial(ent) = make_value_unknown();
			  if (storage_undefined_p(entity_storage(ent)))
			    entity_storage(ent) = make_storage_rom();
			  if(!entity_undefined_p(get_current_module_entity()))
			    AddEntityToDeclarations(ent, get_current_module_entity());
			  else {
			    /* This happens with the old style
			       function declaration at least */
			    /* Oops, we have to assume that the enum
			       is also defined in the compilation
			       unit... else it would be useless. */
			    ;
			  }
			  c_parser_context_type(ycontext) = make_type_variable(v);
			  /* This may be useless, but will be fixed by
			     make_declarations_statement() */
			  entity phv = make_place_holder_variable(ent);
			  list dl = list_undefined;
			  if(entity_undefined_p(phv)) {
			    dl = CONS(ENTITY,ent,NIL);
			  }
			  else {
			    add_initialization_expression(0);
			    dl = CONS(ENTITY,ent,CONS(ENTITY, phv, NIL));
			  }
                          //list dl = CONS(ENTITY, ent, NIL);
			  (yyval.liste) = dl;
			}
    break;

  case 226:
/* Line 1787 of yacc.c  */
#line 2762 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  pips_debug(1, "Reduction %d: TK_ENUM id_or_typename TK_LBRACE enum_list maybecomma TK_RBRACE -> type_spec\n", __LINE__);
			  string en = (yyvsp[(2) - (6)].string);
			  list ml = (yyvsp[(4) - (6)].liste);
                          /* Create the enum entity */
			  entity ent = MakeDerivedEntity(en,ml,is_external,is_type_enum);
			  RecordDerivedEntityDeclaration(ent);
			  variable v = make_variable(make_basic_derived(ent),NIL,NIL);

			  InitializeEnumMemberValues(ml);
			  c_parser_context_type(ycontext) = make_type_variable(v);
			  list rl = CONS(ENTITY, ent, NIL);
			  (yyval.liste) = rl;
			}
    break;

  case 227:
/* Line 1787 of yacc.c  */
#line 2777 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  /* Create the enum entity with unique name */
			  string n = int2a(derived_counter++);
			  string s = strdup(concatenate(DUMMY_ENUM_PREFIX,n,NULL));
			  free(n);
			  entity ent = MakeDerivedEntity(s,(yyvsp[(3) - (5)].liste),is_external,is_type_enum);
			  variable v = make_variable(make_basic_derived(ent),NIL,NIL);

			  InitializeEnumMemberValues((yyvsp[(3) - (5)].liste));
			  c_parser_context_type(ycontext) = make_type_variable(v);
			  (yyval.liste) = CONS(ENTITY,ent,NIL);
			}
    break;

  case 228:
/* Line 1787 of yacc.c  */
#line 2790 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  entity ent;
			  ent = FindOrCreateEntityFromLocalNameAndPrefix((yyvsp[(1) - (1)].string),TYPEDEF_PREFIX,is_external);

			  /* Specify the type of the variable that follows this declaration specifier */
			  if (c_parser_context_typedef(ycontext))
			    {
			      /* typedef T1 T2 => the type of T2 will be that of T1*/
			      pips_debug(8,"typedef T1 T2 where T1 =  %s\n",entity_name(ent));
			      c_parser_context_type(ycontext) = entity_type(ent);
			      (yyval.liste) = CONS(ENTITY,ent,NIL);
			    }
			  else
			    {
			      /* T1 var => the type of var is basic typedef */
			      variable v = make_variable(make_basic_typedef(ent),NIL,NIL);
			      pips_debug(8,"T1 var where T1 =  %s\n",entity_name(ent));
			      c_parser_context_type(ycontext) = make_type_variable(v);
			      (yyval.liste) = NIL;
			    }

			}
    break;

  case 229:
/* Line 1787 of yacc.c  */
#line 2813 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
                          CParserError("TYPEOF not implemented\n");
			}
    break;

  case 230:
/* Line 1787 of yacc.c  */
#line 2817 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  CParserError("TYPEOF not implemented\n");
			}
    break;

  case 231:
/* Line 1787 of yacc.c  */
#line 2825 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    { pips_debug(1, "Reduction %d: empty -> struct_decl_list\n", __LINE__); (yyval.liste) = NIL; }
    break;

  case 232:
/* Line 1787 of yacc.c  */
#line 2827 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
                          pips_debug(1, "Reduction %d:decl_spec_list TK_SEMICOLON struct_decl_list  -> struct_decl_list\n", __LINE__);
			  //c_parser_context ycontext = stack_head(ContextStack);
			  c_parser_context ycontext = GetContext();
			  /* Create the struct member entity with unique name, the name of the
			     struct/union is added to the member name prefix */
              string istr = int2a(derived_counter++);
			  string s = strdup(concatenate("PIPS_MEMBER_",istr,NULL));
			  string derived = code_decls_text((code) stack_head(StructNameStack));
			  entity ent = CreateEntityFromLocalNameAndPrefix(s,strdup(concatenate(derived,
											       MEMBER_SEP_STRING,NULL)),
									  is_external);
			  pips_debug(5,"Current derived name: %s\n",derived);
			  pips_debug(5,"Member name: %s\n",entity_name(ent));
			  entity_storage(ent) = make_storage_rom();
			  entity_type(ent) = c_parser_context_type(ycontext);
              free(s);

			  /* Temporally put the list of struct/union
			     entities defined in $1 to initial value
			     of ent. FI: where is it retrieved? in
			     TakeDerivedEntities()? */
			  entity_initial(ent) = (value) (yyvsp[(1) - (3)].liste);

			  (yyval.liste) = CONS(ENTITY,ent,(yyvsp[(3) - (3)].liste));

			  //stack_pop(ContextStack);
			  PopContext();
			}
    break;

  case 233:
/* Line 1787 of yacc.c  */
#line 2857 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  //c_parser_context ycontext = stack_head(ContextStack);
			  c_parser_context ycontext = GetContext();
			  /* Add struct/union name and MEMBER_SEP_STRING to entity name */
			  string derived = code_decls_text((code) stack_head(StructNameStack));
			  string stf = (c_parser_context_scope(ycontext));
			  c_parser_context_scope(ycontext) = CreateMemberScope(derived,is_external);
			  free(stf);
			  c_parser_context_storage(ycontext) = make_storage_rom();
			}
    break;

  case 234:
/* Line 1787 of yacc.c  */
#line 2868 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
                          pips_debug(1, "Reduction %d: decl_spec_list field_decl_list TK_SEMICOLON struct_decl_list -> struct_decl_list\n", __LINE__);
			  /* Update the entity in field_decl_list with final type, storage, initial value*/

			  UpdateDerivedEntities((yyvsp[(1) - (5)].liste),(yyvsp[(3) - (5)].liste),ContextStack);

			  /* Create the list of member entities */
			  list l1 = (yyvsp[(3) - (5)].liste);
			  list l2 = (yyvsp[(5) - (5)].liste);
			  list nl2 = NIL;
			  FOREACH(ENTITY, e, l2) {
			    if(!gen_in_list_p(e, l1))
			      nl2 = CONS(ENTITY, e, nl2);
			  }
			  nl2 = gen_nreverse(nl2);
			  list rl = gen_nconc(l1, nl2);
			  gen_free_list(l2);
			  (yyval.liste) = rl;
			  PopContext();

			  /* This code is not good ...
			     I have problem with the global variable ycontext and recursion: ycontext is crushed
			     when this decl_spec_list in struct_decl_list is entered, so the scope and storage
			     of the new context are given to the old context, before it is pushed in the stack.

			     For the moment, I reset the changed values of the context, by hoping that in C,
			     before a STRUCT/UNION declaration, there is no extern, ... */
			  free(c_parser_context_scope(ycontext));
			  c_parser_context_scope(ycontext) = empty_scope();
			  c_parser_context_storage(ycontext) = storage_undefined;
			}
    break;

  case 235:
/* Line 1787 of yacc.c  */
#line 2900 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  CParserError("Parse error: error TK_SEMICOLON struct_decl_list\n");
			}
    break;

  case 236:
/* Line 1787 of yacc.c  */
#line 2907 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  entity f = (yyvsp[(1) - (1)].entity);
			  (yyval.liste) = CONS(ENTITY, f,NIL);
			}
    break;

  case 237:
/* Line 1787 of yacc.c  */
#line 2912 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  entity f = (yyvsp[(1) - (3)].entity);
			  (yyval.liste) = CONS(ENTITY,f,(yyvsp[(3) - (3)].liste));
			}
    break;

  case 238:
/* Line 1787 of yacc.c  */
#line 2920 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  /* For debugging... */
			  /* It's probably the last place where you
			     can use the qualifier from the context to
			     update the type of e when e is a pointer. */
			  entity e = (yyvsp[(1) - (1)].entity);
			  type t = entity_type(e);

			  /* FI: Well, this piece of code may be fully
			     useless because t or pt is always undefined. */
			  if(false && !type_undefined_p(t)) {
			    type ut = ultimate_type(t);

			    if(pointer_type_p(ut)) {
			      type pt = type_to_final_pointed_type(ut);
			      if(!type_undefined_p(pt) && type_variable_p(pt)) {
				variable v = type_variable(pt);
				list ql = c_parser_context_qualifiers(ycontext);
				pips_assert("the current qualifier list is empty",
					    ENDP(variable_qualifiers(v)));
				/* FI: because of the above assert, the
				   next statement could be simplified */
				variable_qualifiers(v) =
				  gen_nconc(variable_qualifiers(v), ql);
				c_parser_context_qualifiers(ycontext) = NIL;
			      }
			    }
			  }

			  (yyval.entity) = e;
			}
    break;

  case 239:
/* Line 1787 of yacc.c  */
#line 2952 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  value nv = EvalExpression((yyvsp[(3) - (3)].expression));
			  constant c = value_constant_p(nv)?
			    value_constant(nv) : make_constant_unknown();
			  symbolic s = make_symbolic((yyvsp[(3) - (3)].expression), c);
			  variable v = make_variable(make_basic_bit(s),NIL,NIL);

			  /*pips_assert("Width of bit-field must be a positive constant integer",
			    integer_constant_expression_p($3)); */
			  /* Ignore for this moment if the bit is signed or unsigned */
			  entity_type((yyvsp[(1) - (3)].entity)) = make_type_variable(v);
			  (yyval.entity) = (yyvsp[(1) - (3)].entity);
			}
    break;

  case 240:
/* Line 1787 of yacc.c  */
#line 2966 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  //c_parser_context ycontext = stack_head(ContextStack);
			  c_parser_context ycontext = GetContext();
			  /* Unnamed bit-field : special and unique name */
			  string n = int2a(derived_counter++);
			  string s = strdup(concatenate(DUMMY_MEMBER_PREFIX,n,NULL));
			  entity ent = CreateEntityFromLocalNameAndPrefix(s,c_parser_context_scope(ycontext),is_external);
			  value nv = EvalExpression((yyvsp[(2) - (2)].expression));
			  constant c = value_constant_p(nv)?
			    value_constant(nv) : make_constant_unknown();
			  symbolic se = make_symbolic((yyvsp[(2) - (2)].expression), c);
			  variable v = make_variable(make_basic_bit(se),NIL,NIL);
                          /* pips_assert("Width of bit-field must be a positive constant integer",
                             integer_constant_expression_p($2)); */
			  entity_type(ent) = make_type_variable(v);
              free(n);
			  (yyval.entity) = ent;
			}
    break;

  case 241:
/* Line 1787 of yacc.c  */
#line 2988 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  /* initial_value = 0 or $3*/
			  (yyval.liste) = CONS(ENTITY,(yyvsp[(1) - (1)].entity),NIL);
			  enum_counter = 1;
			}
    break;

  case 242:
/* Line 1787 of yacc.c  */
#line 2994 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  /* Attention to the reverse recursive definition*/
			  (yyval.liste) = gen_nconc((yyvsp[(1) - (3)].liste),CONS(ENTITY,(yyvsp[(3) - (3)].entity),NIL));
			  enum_counter ++;
			}
    break;

  case 243:
/* Line 1787 of yacc.c  */
#line 3000 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  CParserError("Parse error: enum_list TK_COMMA error\n");
			}
    break;

  case 244:
/* Line 1787 of yacc.c  */
#line 3007 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  /* Create an entity of is_basic_int, storage rom
			     initial_value = 0 if it is the first member
			     initial_value = intial_value(precedessor) + 1

			  No need to add current struct/union/enum name to the name's scope of the member entity
			  for ENUM, as in the case of STRUCT and UNION */

			  entity ent = CreateEntityFromLocalNameAndPrefix((yyvsp[(1) - (1)].string),"",is_external);
		      free((yyvsp[(1) - (1)].string));
			  variable v = make_variable(make_basic_int(DEFAULT_INTEGER_TYPE_SIZE),NIL,NIL);
			  type rt = make_type(is_type_variable, v);
			  functional f = make_functional(NIL, rt);

			  entity_storage(ent) = make_storage_rom();
			  entity_type(ent) = make_type_functional(f);
			  /* The information is not yet available, but
			     I need to recognize this entity as
			     symbolic for next rule */
			  entity_initial(ent) = make_value_symbolic(make_symbolic(expression_undefined, make_constant_unknown()));
			  // enum_list is not available yet. Values should be fixed later.
			  /*  entity_initial(ent) = MakeEnumeratorInitialValue(enum_list,enum_counter);*/
			  (yyval.entity) = ent;
			}
    break;

  case 245:
/* Line 1787 of yacc.c  */
#line 3032 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  /* Create an entity of is_basic_int, storage rom, initial_value = $3 */
			  /* No, enum member must be functional
			     entity, just like Fortran's parameters */
			  //int i;
			  value vinit = value_undefined;
			  entity ent = CreateEntityFromLocalNameAndPrefix((yyvsp[(1) - (3)].string),"",is_external);
			  free((yyvsp[(1) - (3)].string));
			  variable v =
			    make_variable(make_basic_int(DEFAULT_INTEGER_TYPE_SIZE),NIL,NIL);
			  type rt = make_type(is_type_variable, v);
			  functional f = make_functional(NIL, rt);

			  //pips_assert("Enumerated value must be a constant integer",
			  //	      signed_integer_constant_expression_p($3));
			  //i = signed_integer_constant_expression_value($3);
			  vinit = EvalExpression((yyvsp[(3) - (3)].expression));
			  entity_storage(ent) = make_storage_rom();
			  entity_type(ent) = make_type_functional(f);

                          if(value_constant_p(vinit) && constant_int_p(value_constant(vinit))) {
			    entity_initial(ent) =
			      make_value_symbolic(make_symbolic((yyvsp[(3) - (3)].expression), value_constant(vinit)));
			  }
                          else {
			    /* Error or reference to a previous member of the same enum (enum04.c) */
			    /* FI: it might be easier to delay systematically the evaluation */
			    bool is_ok = false;
			    if(expression_call_p((yyvsp[(3) - (3)].expression))) {
			      call c = syntax_call(expression_syntax((yyvsp[(3) - (3)].expression)));
			      entity m = call_function(c);

			      if(entity_symbolic_p(m)) {
				is_ok = true;
			      }
			    }
			    if(is_ok)
			      entity_initial(ent) =
				make_value_symbolic(make_symbolic((yyvsp[(3) - (3)].expression), make_constant_unknown()));
			    else {
			      /* Let's try to delay evaluation anyway (enum05.c) */
			      entity_initial(ent) =
				make_value_symbolic(make_symbolic((yyvsp[(3) - (3)].expression), make_constant_unknown()));
			      //pips_internal_error("Constant integer expression not evaluated\n");
			    }
			  }

			  (yyval.entity) = ent;
			}
    break;

  case 246:
/* Line 1787 of yacc.c  */
#line 3085 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  /* Update the type of the direct_decl entity with pointer_opt and attributes*/
			  if (!type_undefined_p((yyvsp[(1) - (3)].type)))
			    UpdatePointerEntity((yyvsp[(2) - (3)].entity),(yyvsp[(1) - (3)].type),(yyvsp[(3) - (3)].liste));
			  else if(!entity_undefined_p((yyvsp[(2) - (3)].entity)) &&!ENDP((yyvsp[(3) - (3)].liste)) ) {
                    if(type_undefined_p(entity_type((yyvsp[(2) - (3)].entity)))) {
						entity_type((yyvsp[(2) - (3)].entity)) = make_type_variable(
							make_variable(
								basic_undefined,
								NIL,
								(yyvsp[(3) - (3)].liste)
							)
						);
                    }
					else if( type_variable_p(entity_type((yyvsp[(2) - (3)].entity)) ) ){
		                variable v = type_variable(entity_type((yyvsp[(2) - (3)].entity)));
						variable_qualifiers(v)=gen_nconc(variable_qualifiers(v),(yyvsp[(3) - (3)].liste));
					}
					else  {
						c_parser_user_warning("some _asm(..) attributes are going to be lost for entity `%s'\n",entity_name((yyvsp[(2) - (3)].entity)));
					}
              }
			  (yyval.entity) = (yyvsp[(2) - (3)].entity);
			}
    break;

  case 247:
/* Line 1787 of yacc.c  */
#line 3115 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  /* FI: A variable cannot be redeclared
			     within the same scope, but this is not
			     checked yet. */
			  entity e = FindOrCreateCurrentEntity((yyvsp[(1) - (1)].string),ContextStack,FormalStack,FunctionStack,is_external);
			  /* Initialize the type stack and push the
			     type of found/created entity to the
			     stack.  It can be undefined if the entity
			     has not been parsed, or a given type
			     which is used later to check if the
			     declarations are the same for one entity.
			     This stack is put temporarily in the
			     storage of the entity, not a global
			     variable for each declarator to avoid
			     being erased by recursion (FI: this last
			     sentence seems to be wrong) */
			  stack s = get_from_entity_type_stack_table(e);
			  if(stack_undefined_p(s)) {
			    s = stack_make(type_domain,0,0);
			    stack_push((char *) entity_type(e),s);
			    put_to_entity_type_stack_table(e,s);
			  }
			  else {
			    /* e has already been defined since a type
			       stack is associated to it. At least, if
			       the mapping from entity to type stack
			       is well managed. Since entities are
			       sometimes destroyed, a new entity might
			       end up with the same memory address and
			       hence the same type stack. */
			    entity cm = get_current_module_entity();
			    /* A function can be redeclared inside itself. see C_syntax/extern.c */
			    if(cm!=e) {
			      /* Dummy parameters can also be redeclared
				 as long as their types are equal */
			      if(dummy_parameter_entity_p(e)) {
				c_parser_user_warning("Dummy parameter \"%s\" is redefined.\n",
						      entity_user_name(e));
				CParserError("Dummy redefinition accepted by gcc but not compatible with ISO standard."
					     " Try to compile with \"gcc -ansi -c\"\n");
			      }
			      else {
				type t = (type) stack_head(s);
				if(type_undefined_p(t)) {
				  c_parser_user_warning("Symbol \"%s\" is redefined.\n",
							entity_user_name(e) /* entity_name(e)*/);
				}
				else if(type_functional_p(t)) {
				  c_parser_user_warning("Function \"%s\" is redefined.\n",
							entity_user_name(e) /* entity_name(e)*/);
				}
				else {
				c_parser_user_warning("Variable \"%s\" is redefined.\n",
						      entity_user_name(e) /* entity_name(e)*/);
				CParserError("Variable redefinitions are not compatible with ISO standard."
					     " Try to compile with \"gcc -ansi -c\"\n");
				}
			      }
			    }
			  }

			  entity_type(e) = type_undefined;
			  //discard_C_comment();
			  //push_current_C_comment();
			  (yyval.entity) = e;
			}
    break;

  case 248:
/* Line 1787 of yacc.c  */
#line 3182 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  /* Add attributes such as const, restrict, ... to variable's qualifiers */
			  UpdateParenEntity((yyvsp[(3) - (4)].entity), (yyvsp[(2) - (4)].liste));
			  (yyval.entity) = (yyvsp[(3) - (4)].entity);
			  stack_push((char *) entity_type((yyval.entity)),
			     get_from_entity_type_stack_table((yyval.entity)));
			  // FI: if I rely on the stack, I won't know for a while what
			  // this entity is. And I'd like to make a difference between
			  // a function and a pointer to a function before I declare
			  // dummy arguments. But Nga's design has to be redone:-(.
			  entity_type((yyval.entity)) = type_undefined;
			}
    break;

  case 249:
/* Line 1787 of yacc.c  */
#line 3195 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			 /* This is the last dimension of an array (i.e a[1][2][3] => [3]).
			    Questions:
			     - What can be attributes ?
			     - Why comma_expression, it can be a list of expressions ?
                             - When the comma_expression is empty (corresponding to the first dimension),
			       the array is of unknown size => can be determined by the intialization ? TO BE DONE*/
			  list el = (yyvsp[(4) - (5)].liste);
			  if(gen_length(el)<=1)
			    UpdateArrayEntity((yyvsp[(1) - (5)].entity),(yyvsp[(3) - (5)].liste),el);
			  else {
			    expression d = MakeCommaExpression(el);
			    UpdateArrayEntity((yyvsp[(1) - (5)].entity),(yyvsp[(3) - (5)].liste),CONS(EXPRESSION, d, NIL));
			  }
			}
    break;

  case 250:
/* Line 1787 of yacc.c  */
#line 3211 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  CParserError("Parse error: direct_decl TK_LBRACKET attributes error TK_RBRACKET\n");
			}
    break;

  case 251:
/* Line 1787 of yacc.c  */
#line 3215 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  /* Well, here it can be a function or a pointer to a function */
			  entity e = (yyvsp[(1) - (2)].entity); //RenameFunctionEntity($1);
			  if (value_undefined_p(entity_initial(e))
			      ||value_unknown_p(entity_initial(e))) {
			    /* If it is a pointer, its value is going
			       to be "unknown" or "expression"; if it is
			       a function, its value is going to be
			       "code". If the value cannot stay
			       undefined, it should be made
			       unknown... */
			    entity_initial(e) = make_value(is_value_code,make_code(NIL,strdup(""),make_sequence(NIL), NIL, make_language_c()));
			    //entity_initial(e) = make_value_unknown();
			  }
			  //pips_assert("e is a module", module_name_p(entity_module_name(e)));
			  PushFunction(e);
			}
    break;

  case 252:
/* Line 1787 of yacc.c  */
#line 3233 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  entity m = get_current_module_entity();
			  entity e = GetFunction();
			  entity ne = e;
			    pips_assert("ne is an entity",
					entity_domain_number(ne)==entity_domain);
			  PopFunction();
			  stack_pop(FormalStack);
			  StackPop(OffsetStack);
			  /* Intrinsic functions in C such as printf, fprintf, ... are considered
			     as entities with functional type ???
			     if (!intrinsic_entity_p(e))*/
			  /* e can be a function or a pointer to a
			     function. The information is available
			     somewhere in the stacks... */
			  stack ts = get_from_entity_type_stack_table(e);
			  if(!stack_undefined_p(ts)) {
			    type et = (type) stack_head(ts);
			    if(type_undefined_p(et))
			      ne = RenameFunctionEntity(e);
			    else if(!type_variable_p(et))
			      ne = RenameFunctionEntity(e);
			  }
			    pips_assert("ne is an entity",
					entity_domain_number(ne)==entity_domain);
			  UpdateFunctionEntity(ne,(yyvsp[(4) - (5)].liste));
			    pips_assert("ne is an entity",
					entity_domain_number(ne)==entity_domain);
			  /* No need to declare C user functions
			     extern in a compilation unit; they are
			     global or local. */
			  if(!entity_undefined_p(m)
			     && compilation_unit_entity_p(m)
			     && !intrinsic_entity_p(ne)) {
			    /* Too early: pointers to functions are still
			     * seen as functions here. Let's delay
			     */
			    // RemoveFromExterns(ne);
			    pips_assert("ne is an entity",
					entity_domain_number(ne)==entity_domain);
			    removable_extern_entities =
			      CONS(ENTITY, ne, removable_extern_entities);
			  }
			  (yyval.entity) = ne;
			}
    break;

  case 253:
/* Line 1787 of yacc.c  */
#line 3281 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  stack_push((char *) make_basic_logical(true), FormalStack);
			  stack_push((char *) make_basic_int(1),OffsetStack);
			}
    break;

  case 254:
/* Line 1787 of yacc.c  */
#line 3288 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    { (yyval.liste) = NIL; }
    break;

  case 255:
/* Line 1787 of yacc.c  */
#line 3290 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  (yyval.liste) = CONS(PARAMETER,(yyvsp[(1) - (2)].parameter),(yyvsp[(2) - (2)].liste));
			}
    break;

  case 256:
/* Line 1787 of yacc.c  */
#line 3295 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    { (yyval.liste) = NIL; }
    break;

  case 257:
/* Line 1787 of yacc.c  */
#line 3297 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  StackPush(OffsetStack);
			}
    break;

  case 258:
/* Line 1787 of yacc.c  */
#line 3301 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  /*$$ = CONS(PARAMETER,make_parameter(make_type_varargs(type_undefined),
			    make_mode(CurrentMode,UU), make_dummy_unknown()),NIL); */
			  type at = make_type(is_type_variable,
					      make_variable(make_basic(is_basic_overloaded, UU),
							    NIL, NIL));
			  (yyval.liste) = CONS(PARAMETER,
				    make_parameter(make_type_varargs(at),
						   make_mode(CurrentMode,UU),
						   make_dummy_unknown()),
				    NIL);
			}
    break;

  case 259:
/* Line 1787 of yacc.c  */
#line 3314 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  StackPush(OffsetStack);
			}
    break;

  case 260:
/* Line 1787 of yacc.c  */
#line 3318 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  (yyval.liste) = CONS(PARAMETER,(yyvsp[(3) - (4)].parameter),(yyvsp[(4) - (4)].liste));
			}
    break;

  case 261:
/* Line 1787 of yacc.c  */
#line 3325 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  UpdateEntity((yyvsp[(2) - (2)].entity),ContextStack,FormalStack,FunctionStack,OffsetStack,is_external,false);
			  (yyval.parameter) = make_parameter(copy_type(entity_type((yyvsp[(2) - (2)].entity))),
					      make_mode(CurrentMode,UU),
					      make_dummy_identifier((yyvsp[(2) - (2)].entity))); //FI: or should it
			  // be entity_undefined? Are we parsing a compilation unit or a function?
			  /* Set CurentMode where ???? */
			  //stack_pop(ContextStack);
			  PopContext();
			}
    break;

  case 262:
/* Line 1787 of yacc.c  */
#line 3336 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  UpdateAbstractEntity((yyvsp[(2) - (2)].entity),ContextStack);
			  (yyval.parameter) = make_parameter(copy_type(entity_type((yyvsp[(2) - (2)].entity))),
					      make_mode(CurrentMode,UU),
					      make_dummy_unknown()); //FI: to be checked
			  RemoveFromExterns((yyvsp[(2) - (2)].entity));
			  gen_remove(&removable_extern_entities, (void *) (yyvsp[(2) - (2)].entity));
			  free_entity((yyvsp[(2) - (2)].entity));
			  //stack_pop(ContextStack);
			  PopContext();
			}
    break;

  case 263:
/* Line 1787 of yacc.c  */
#line 3348 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  c_parser_context ycontext = stack_head(ContextStack);
			  (yyval.parameter) = make_parameter(copy_type(c_parser_context_type(ycontext)),
					      make_mode(CurrentMode,UU),
					      make_dummy_unknown());
			  /* function prototype*/
			  //stack_pop(ContextStack);
			  PopContext();
			}
    break;

  case 264:
/* Line 1787 of yacc.c  */
#line 3358 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    { (yyval.parameter) = (yyvsp[(2) - (3)].parameter); }
    break;

  case 265:
/* Line 1787 of yacc.c  */
#line 3364 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  if (!type_undefined_p((yyvsp[(1) - (2)].type)))
			    UpdatePointerEntity((yyvsp[(2) - (2)].entity),(yyvsp[(1) - (2)].type),NIL);
			  (yyval.entity) = (yyvsp[(2) - (2)].entity);
			}
    break;

  case 266:
/* Line 1787 of yacc.c  */
#line 3373 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  entity e = (yyvsp[(1) - (2)].entity); //RenameFunctionEntity($1);
			  if (value_undefined_p(entity_initial(e)))
			    entity_initial((yyvsp[(1) - (2)].entity)) = make_value(is_value_code,make_code(NIL,strdup(""),make_sequence(NIL),NIL, make_language_c()));
			  //pips_assert("e is a module", module_name_p(entity_module_name(e)));
			  PushFunction(e);
			  stack_push((char *) make_basic_logical(true),FormalStack);
			  stack_push((char *) make_basic_int(1),OffsetStack);
			}
    break;

  case 267:
/* Line 1787 of yacc.c  */
#line 3383 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  entity e = GetFunction();
			  list paras = MakeParameterList((yyvsp[(4) - (6)].liste),(yyvsp[(6) - (6)].liste),FunctionStack);
			  PopFunction();
			  stack_pop(FormalStack);
			  StackPop(OffsetStack);
			  (void) UpdateFunctionEntity(e, paras);
			  //CreateReturnEntity(e);
			  gen_free_list((yyvsp[(4) - (6)].liste));
			  (yyval.entity) = e;
			}
    break;

  case 268:
/* Line 1787 of yacc.c  */
#line 3404 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  (yyval.liste) = CONS(STRING,(yyvsp[(1) - (1)].string),NIL);
			}
    break;

  case 269:
/* Line 1787 of yacc.c  */
#line 3408 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  (yyval.liste) = CONS(STRING,(yyvsp[(1) - (3)].string),(yyvsp[(3) - (3)].liste));
			}
    break;

  case 270:
/* Line 1787 of yacc.c  */
#line 3414 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    { (yyval.liste) = NIL; }
    break;

  case 271:
/* Line 1787 of yacc.c  */
#line 3416 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  UpdateEntities((yyvsp[(2) - (4)].liste),ContextStack,FormalStack,FunctionStack,OffsetStack,is_external,false);
			  //stack_pop(ContextStack);
			  PopContext();
			  /* Can we have struct/union definition in $1 ?*/
			  /*$$ = gen_nconc($1,$2);*/
			  (yyval.liste) = (yyvsp[(2) - (4)].liste);
			}
    break;

  case 272:
/* Line 1787 of yacc.c  */
#line 3425 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  /* Rule used for C_syntax/activate.c,
			     decl33.c and adi.c. CreateReturnEntity()
			     only useful for activate.c  */
			  list el = (yyvsp[(2) - (4)].liste);
			  entity f = stack_head(FunctionStack);
			  SubstituteDummyParameters(f, el);
			  UpdateEntities(el,ContextStack,FormalStack,FunctionStack,OffsetStack,is_external,false);
			  // The functional type of f could be
			  // completed with the parameter types...
			  CreateReturnEntity(f);
			  //stack_pop(ContextStack);
			  PopContext();
			  /* Can we have struct/union definition in $1 ?*/
			  /*$$ = gen_nconc($1,gen_nconc(el,$4));*/
			  (yyval.liste) = gen_nconc(el,(yyvsp[(4) - (4)].liste));
			}
    break;

  case 273:
/* Line 1787 of yacc.c  */
#line 3446 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  (yyval.liste) = CONS(ENTITY,(yyvsp[(1) - (1)].entity),NIL);
			}
    break;

  case 274:
/* Line 1787 of yacc.c  */
#line 3450 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  (yyval.liste) = CONS(ENTITY,(yyvsp[(1) - (3)].entity),(yyvsp[(3) - (3)].liste));
			}
    break;

  case 275:
/* Line 1787 of yacc.c  */
#line 3454 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  CParserError("Parse error: error \n");
			}
    break;

  case 276:
/* Line 1787 of yacc.c  */
#line 3461 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    { /* decl24.c, decl50.c, decl51.c, decl52.c,
			     decl53.c :
			     const attribute lost or misplaced for pointers */
			  list al = (yyvsp[(2) - (3)].liste);
			  type t = (yyvsp[(3) - (3)].type);
			  //c_parser_context_qualifiers(ycontext) =
			  //  gen_nconc(c_parser_context_qualifiers(ycontext), al);
			  (yyval.type) = make_type_variable(make_variable(make_basic_pointer(t), NIL, al));
			  //c_parser_context_qualifiers(ycontext) = NIL;
			}
    break;

  case 277:
/* Line 1787 of yacc.c  */
#line 3474 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    { (yyval.type) = type_undefined;}
    break;

  case 278:
/* Line 1787 of yacc.c  */
#line 3475 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    { }
    break;

  case 279:
/* Line 1787 of yacc.c  */
#line 3480 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  entity e = (yyvsp[(2) - (2)].entity);
			  list el = CONS(ENTITY, e, NIL);
			  UpdateAbstractEntity(e,ContextStack);
			  (yyval.type) = copy_type(entity_type(e));
			  RemoveFromExterns(e); // should be useless
			  gen_remove(&removable_extern_entities, (void *) e);
			  remove_entity_type_stacks(el);
			  gen_free_list(el);
			  free_entity(e);
			  //stack_pop(ContextStack);
			  PopContext();
			}
    break;

  case 280:
/* Line 1787 of yacc.c  */
#line 3494 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  c_parser_context ycontext = stack_head(ContextStack);
			  (yyval.type) = c_parser_context_type(ycontext);
			  //stack_pop(ContextStack);
			  PopContext();
			}
    break;

  case 281:
/* Line 1787 of yacc.c  */
#line 3504 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  /* Update the type of the direct_decl entity with pointer_opt and attributes*/
			  if (!type_undefined_p((yyvsp[(1) - (3)].type)))
			    UpdatePointerEntity((yyvsp[(2) - (3)].entity),(yyvsp[(1) - (3)].type),(yyvsp[(3) - (3)].liste));
			  (yyval.entity) = (yyvsp[(2) - (3)].entity);
			}
    break;

  case 282:
/* Line 1787 of yacc.c  */
#line 3511 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  string n = int2a(abstract_counter++);
			  entity e = FindOrCreateCurrentEntity(strdup(concatenate(DUMMY_ABSTRACT_PREFIX,
										  n,NULL)),
							 ContextStack,
							 FormalStack,
							 FunctionStack,
							 is_external);
			  free(n);
			  UpdatePointerEntity(e,(yyvsp[(1) - (1)].type),NIL);
			  /* Initialize the type stack and push the type of found/created entity to the stack.
			     It can be undefined if the entity has not been parsed, or a given type which is
			     used later to check if the declarations are the same for one entity.
			     This stack is put temporarily in the storage of the entity, not a global variable
			     for each declarator to avoid being erased by recursion */
			  stack s = stack_make(type_domain, 0, 0);
			  //entity_storage($$) = (storage) s;
			  stack_push((char *) entity_type(e),s);
			  put_to_entity_type_stack_table(e, s);
			  /*entity_type($$) = type_undefined;*/
			  (yyval.entity) = e;
			}
    break;

  case 283:
/* Line 1787 of yacc.c  */
#line 3539 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  UpdateParenEntity((yyvsp[(3) - (4)].entity),(yyvsp[(2) - (4)].liste));
			  (yyval.entity) = (yyvsp[(3) - (4)].entity);
			  stack_push((char *) entity_type((yyval.entity)),
				     get_from_entity_type_stack_table((yyval.entity)));
			  entity_type((yyval.entity)) = type_undefined;
			}
    break;

  case 284:
/* Line 1787 of yacc.c  */
#line 3547 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  CParserError("Parse error: TK_LPAREN error TK_RPAREN\n");
			}
    break;

  case 285:
/* Line 1787 of yacc.c  */
#line 3552 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  UpdateArrayEntity((yyvsp[(1) - (4)].entity),NIL,(yyvsp[(3) - (4)].liste));
			}
    break;

  case 286:
/* Line 1787 of yacc.c  */
#line 3557 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  entity e = (yyvsp[(1) - (2)].entity); //RenameFunctionEntity($1);
			  if (value_undefined_p(entity_initial(e)))
			    entity_initial(e) = make_value(is_value_code,make_code(NIL,strdup(""),make_sequence(NIL),NIL, make_language_c()));
			  //pips_assert("e is a module", module_name_p(entity_module_name($1)));
			  PushFunction(e);
			}
    break;

  case 287:
/* Line 1787 of yacc.c  */
#line 3565 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  entity e = GetFunction();
			  PopFunction();
			  stack_pop(FormalStack);
			  StackPop(OffsetStack);
			  (void) UpdateFunctionEntity(e,(yyvsp[(4) - (5)].liste));
			  (yyval.entity) = e;
			}
    break;

  case 288:
/* Line 1787 of yacc.c  */
#line 3577 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    { }
    break;

  case 289:
/* Line 1787 of yacc.c  */
#line 3578 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
                          string n = int2a(abstract_counter++);
			  entity e = FindOrCreateCurrentEntity(strdup(concatenate(DUMMY_ABSTRACT_PREFIX,
									    n,NULL)),
							 ContextStack,FormalStack,
							 FunctionStack,
							 is_external);
			  free(n);
			  stack s = stack_make(type_domain,0,0);
			  //entity_storage($$) = (storage) s;
			  stack_push((char *) entity_type(e),s);
			  put_to_entity_type_stack_table(e, s);
			  entity_type(e) = type_undefined;
			  (yyval.entity) = e;
    }
    break;

  case 290:
/* Line 1787 of yacc.c  */
#line 3597 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  InitializeBlock();
			  is_external = false;
			}
    break;

  case 291:
/* Line 1787 of yacc.c  */
#line 3602 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  /* Make value_code for current module here */
			  //list dl = statement_declarations($3);
			  ModuleStatement = (yyvsp[(3) - (3)].statement);
			  pips_assert("Module statement is consistent",
				      statement_consistent_p(ModuleStatement));
			  pips_assert("No illegal redundant declarations",
				      check_declaration_uniqueness_p(ModuleStatement));
			  /* Let's delay this? ResetCurrentModule(); */
			  is_external = true;
			}
    break;

  case 292:
/* Line 1787 of yacc.c  */
#line 3616 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  UpdateEntity((yyvsp[(2) - (2)].entity),ContextStack,FormalStack,FunctionStack,OffsetStack,is_external, false);
			  //stack_pop(ContextStack);
			  PopContext();
			  pips_debug(2,"Create current module %s\n",entity_user_name((yyvsp[(2) - (2)].entity)));
			  MakeCurrentModule((yyvsp[(2) - (2)].entity));
			  reset_token_has_been_seen_p();
			  clear_C_comment();
			  pips_assert("Module is consistent\n",entity_consistent_p((yyvsp[(2) - (2)].entity)));
			}
    break;

  case 293:
/* Line 1787 of yacc.c  */
#line 3628 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  UpdateEntity((yyvsp[(2) - (2)].entity),ContextStack,FormalStack,FunctionStack,OffsetStack,is_external, false);
			  //stack_pop(ContextStack);
			  PopContext();
			  pips_debug(2,"Create current module %s with old-style prototype\n",entity_user_name((yyvsp[(2) - (2)].entity)));
			  MakeCurrentModule((yyvsp[(2) - (2)].entity));
			  reset_token_has_been_seen_p();
			  clear_C_comment();
			  pips_assert("Module is consistent\n",entity_consistent_p((yyvsp[(2) - (2)].entity)));
			}
    break;

  case 294:
/* Line 1787 of yacc.c  */
#line 3640 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  entity oe = FindOrCreateEntity(TOP_LEVEL_MODULE_NAME,(yyvsp[(1) - (2)].string));
			  free((yyvsp[(1) - (2)].string));
			  entity e = oe; //RenameFunctionEntity(oe);
			  pips_debug(2,"Create current module \"%s\" with no return type\n",
			       entity_name(e));
                          MakeCurrentModule(e);
			  reset_token_has_been_seen_p();
			  clear_C_comment();
			  //pips_assert("e is a module", module_name_p(entity_module_name(e)));
			  PushFunction(e);
			}
    break;

  case 295:
/* Line 1787 of yacc.c  */
#line 3653 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  /* Functional type is unknown or int (by default) or void ?*/
			  //functional f = make_functional($4,make_type_unknown());
			  functional f = make_functional((yyvsp[(4) - (5)].liste),MakeIntegerResult());
			  entity e = GetFunction();
			  entity_type(e) = make_type_functional(f);
			  pips_assert("Current module entity is consistent\n",entity_consistent_p(e));
			  // Too late for full UpdateEntity() but at
			  //least the return value and the formal
			  //parameters should be properly defined
			  //UpdateEntity(e,ContextStack,FormalStack,FunctionStack,OffsetStack,is_external,
			  //false);
			  UpdateEntity2(e, FormalStack, OffsetStack);
			  PopFunction();
			  stack_pop(FormalStack);
			  StackPop(OffsetStack);
			}
    break;

  case 296:
/* Line 1787 of yacc.c  */
#line 3672 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  entity oe = FindOrCreateEntity(TOP_LEVEL_MODULE_NAME,(yyvsp[(1) - (3)].string));
			  entity e= oe; //RenameFunctionEntity(oe);
			  pips_debug(2,"Create current module %s with no return type + old-style parameter list\n",(yyvsp[(1) - (3)].string));
			  free((yyvsp[(1) - (3)].string));
			  MakeCurrentModule(e);
			  clear_C_comment();
			  //pips_assert("e is a module", module_name_p(entity_module_name(e)));
			  PushFunction(e);
			  stack_push((char *) make_basic_logical(true),FormalStack);
			  stack_push((char *) make_basic_int(1),OffsetStack);
			}
    break;

  case 297:
/* Line 1787 of yacc.c  */
#line 3685 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  list paras = MakeParameterList((yyvsp[(3) - (6)].liste),(yyvsp[(6) - (6)].liste),FunctionStack);
			  gen_free_list((yyvsp[(3) - (6)].liste));
			  functional f = make_functional(paras,make_type_unknown());
			  entity e = GetFunction();
			  entity_type(e) = make_type_functional(f);
			  pips_assert("Current module entity is consistent\n",entity_consistent_p(e));
			  PopFunction();
			  stack_pop(FormalStack);
			  StackPop(OffsetStack);
			}
    break;

  case 298:
/* Line 1787 of yacc.c  */
#line 3715 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    { (yyval.liste) = NIL; }
    break;

  case 299:
/* Line 1787 of yacc.c  */
#line 3718 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    { (yyval.liste) = insert_qualifier((yyvsp[(2) - (2)].liste), (yyvsp[(1) - (2)].qualifier));}
    break;

  case 300:
/* Line 1787 of yacc.c  */
#line 3725 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    { (yyval.liste) = NIL; }
    break;

  case 301:
/* Line 1787 of yacc.c  */
#line 3727 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    { (yyval.liste) = CONS(QUALIFIER,(yyvsp[(1) - (2)].qualifier),(yyvsp[(2) - (2)].liste)); }
    break;

  case 302:
/* Line 1787 of yacc.c  */
#line 3729 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    { (yyval.liste) = CONS(QUALIFIER,make_qualifier_asm((yyvsp[(3) - (5)].string)), (yyvsp[(5) - (5)].liste));}
    break;

  case 303:
/* Line 1787 of yacc.c  */
#line 3741 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    { CParserError("ATTRIBUTE not implemented\n"); }
    break;

  case 304:
/* Line 1787 of yacc.c  */
#line 3744 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  (yyval.qualifier) = make_qualifier_const();
			}
    break;

  case 305:
/* Line 1787 of yacc.c  */
#line 3748 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  (yyval.qualifier) = make_qualifier_restrict();
			}
    break;

  case 306:
/* Line 1787 of yacc.c  */
#line 3752 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  (yyval.qualifier) = make_qualifier_volatile();
			}
    break;

  case 307:
/* Line 1787 of yacc.c  */
#line 3756 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {
			  (yyval.qualifier) = make_qualifier_static_dimension();
			}
    break;

  case 308:
/* Line 1787 of yacc.c  */
#line 3871 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {  }
    break;

  case 309:
/* Line 1787 of yacc.c  */
#line 3873 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    { CParserError("ASM not implemented\n"); }
    break;

  case 310:
/* Line 1787 of yacc.c  */
#line 3875 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    { CParserError("ASM not implemented\n"); }
    break;

  case 311:
/* Line 1787 of yacc.c  */
#line 3880 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {  }
    break;

  case 312:
/* Line 1787 of yacc.c  */
#line 3882 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    { CParserError("ASM not implemented\n"); }
    break;

  case 313:
/* Line 1787 of yacc.c  */
#line 3886 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {  }
    break;

  case 314:
/* Line 1787 of yacc.c  */
#line 3888 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    { CParserError("ASM not implemented\n"); }
    break;

  case 315:
/* Line 1787 of yacc.c  */
#line 3892 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    { CParserError("ASM not implemented\n"); }
    break;

  case 316:
/* Line 1787 of yacc.c  */
#line 3894 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    { CParserError("ASM not implemented\n"); }
    break;

  case 317:
/* Line 1787 of yacc.c  */
#line 3898 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    { CParserError("ASM not implemented\n"); }
    break;

  case 318:
/* Line 1787 of yacc.c  */
#line 3900 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    { CParserError("ASM not implemented\n"); }
    break;

  case 319:
/* Line 1787 of yacc.c  */
#line 3904 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {  }
    break;

  case 320:
/* Line 1787 of yacc.c  */
#line 3906 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    { CParserError("ASM not implemented\n"); }
    break;

  case 321:
/* Line 1787 of yacc.c  */
#line 3910 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    {  }
    break;

  case 322:
/* Line 1787 of yacc.c  */
#line 3912 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    { CParserError("ASM not implemented\n"); }
    break;

  case 323:
/* Line 1787 of yacc.c  */
#line 3916 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    { CParserError("ASM not implemented\n"); }
    break;

  case 324:
/* Line 1787 of yacc.c  */
#line 3918 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"
    { CParserError("ASM not implemented\n"); }
    break;


/* Line 1787 of yacc.c  */
#line 7172 "cyacc.tab.c"
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
#line 3921 "/home/dounia/MYPIPS/prod/pips/src/Libs/c_syntax/cyacc.y"


