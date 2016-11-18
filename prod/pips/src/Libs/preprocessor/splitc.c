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
#define yyparse         splitc_parse
#define yylex           splitc_lex
#define yyerror         splitc_error
#define yylval          splitc_lval
#define yychar          splitc_char
#define yydebug         splitc_debug
#define yynerrs         splitc_nerrs

/* Copy the first part of user declarations.  */
/* Line 336 of yacc.c  */
#line 52 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"

#ifdef HAVE_CONFIG_H
    #include "pips_config.h"
#endif
 /* C declarations */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "genC.h"
#include "linear.h"
#include "ri-util.h"
#include "misc.h"
#include "properties.h"

#include "preprocessor.h"

#define C_ERROR_VERBOSE 1 /* much clearer error messages with bison */

/* Increase the parser stack to have SPEC2006/445.gobmk/owl_defendpat.c
   going through without a:

   user warning in splitc_error: C memory exhausted near "0" at preprocessed line 13459 (user line 8732)
*/
#define YYMAXDEPTH 1000000

/* The following global variables are used to store the information such as
   the scope, type and storage of an entity, given by the decl_spec_list,
   which are used later by direct_decl to create the entity.

   For the moment, block scope is not considered. CurrentScope can be File,
   Module, File'FILE_SEP_STRING'Module or TOP-LEVEL*/

/* static string CurrentScope = NULL; */
/*
static type CurrentType = type_undefined;
static storage CurrentStorage = storage_undefined;
static list CurrentQualifiers = NIL; */
/* static string CurrentDerivedName = NULL; */ /* to remember the name of a struct and add it to the member prefix name*/
/* static int CurrentMode = 0; */ /* to know the mode of the formal parameter : by value or by reference*/

int csplit_is_external = 0; /* to know if the variable is declared inside or outside a function */
int csplit_is_function = 0; /* to know if this is the declaration of a function or not, to distinguish between
			      a static variable and a static function */
/* Shared with the lexical analyzer */
string csplit_current_function_name = string_undefined;
string csplit_current_function_name2 = string_undefined;
string csplit_definite_function_name = string_undefined;
string csplit_definite_function_signature = string_undefined;


static void reset_csplit_current_function_name()
{
  if(!string_undefined_p(csplit_current_function_name)) {
    free(csplit_current_function_name);
    csplit_current_function_name =
      csplit_current_function_name2;
  }
  if(!string_undefined_p(csplit_current_function_name2)) {
    csplit_current_function_name2 = string_undefined;
  }
}
/* static int enum_counter = 0; */

/* Shared with the lexical analyzer */
bool csplit_is_static_p = false;
static bool current_function_is_static_p = false;

static void csplit_parser_warning_alist(
  const char * pips_func,
  const char * pips_file,
  const int pips_line,
  const string format,
  va_list * args)
{
  if (get_bool_property("NO_USER_WARNING"))
    return;

  string cpn = get_pips_current_pass_name();
  if (cpn==NULL)
    cpn = "unknown";

  string uifn = preprocessor_current_initial_file_name;
  // note: this is the line number in the preprocessed file, which changes
  // from cpp to cpp because of inserted preprocessor junk...
  int ln = csplit_line_number;
  string s = safe_read_nth_line(preprocessor_current_split_file_name, ln);

  pips_log_alist(warning_log, cpn, get_pips_current_module(),
                 (const string) pips_func, (const string) pips_file, pips_line,
                 NULL, (const string) uifn, ln, -1,
                 s, "see stderr for exact file and line number",
                 (const string) format, args);
  free(s);
}

void csplit_parser_warning_func(
  const char * pips_func,
  const char * pips_file,
  const int pips_line,
  const string format,
  ...)
{
  va_list args;
  va_start(args, format);
  csplit_parser_warning_alist(pips_func, pips_file, pips_line, format, &args);
  va_end(args);
}

/* Redundant with splitc_error()? */
void csplit_parser_error(const string msg)
{
  /* Should add the current line number of the lexer */

  /* csplit_parser_warning("Corrupted or non-supported C constructs.\n" */
  /* 		       "Make sure your code is compiled by gcc -stc=c99 first, " */
  /* 		       "and/or set proper PIPS option, " */
  /* 		       "CHECK_FORTRAN_SYNTAX_BEFORE_RUNNING_PIPS or " */
  /* 		       "CHECK_C_SYNTAX_BEFORE_RUNNING_PIPS.\n"); */

  csplit_parser_warning(msg);

  //pips_internal_error("Not implemented yet\n."
  //		 " Should reset all static variables.\n");
  /* Reset all static variables */
  /* Close all open files: at least three... */
  extern string current_file_name;
  csplit_close_files(current_file_name);
  csplit_error_handler();

  // See syn_reset_lex() -> syn_restart(syn_in); as in ParserError,
  // the error routine for the Fortran parser, but its lexer is
  // made of two passes, a Fortran-specific first pass and a lex second pass
  // syn_restart(splitc_in);
  // yy_flush_buffer(); //YY_FLUSH_BUFFER;
  splitc_lex_destroy(); // trial and error
  // BEGIN(0); we might have to reset the state of lex

  //pips_user_error(s);
  pips_user_error("Corrupted or non-supported C constructs.\n"
                  "Make sure your code is compiled by gcc -stc=c99 first, "
                  "and/or set proper PIPS option, "
                  "CHECK_FORTRAN_SYNTAX_BEFORE_RUNNING_PIPS or "
                  "CHECK_C_SYNTAX_BEFORE_RUNNING_PIPS.\n");
}

/* All the following global variables must be replaced by functions, once we have the preprocessor for C */

static int csplit_is_typedef = false; /* to know if this is a typedef name or not */
static stack TypedefStack = stack_undefined;

 static void PushTypedef()
 {
   pips_debug(8, "csplit_is_typedef = %s\n", bool_to_string(csplit_is_typedef));
   stack_push((void *) (_int)csplit_is_typedef, TypedefStack);
   csplit_is_typedef = false;
   pips_debug(8, "csplit_is_typedef = %s\n", bool_to_string(csplit_is_typedef));
 }

 static void PopTypedef()
 {
   csplit_is_typedef = (_int) stack_pop(TypedefStack);
   pips_debug(8, "csplit_is_typedef = %s\n", bool_to_string(csplit_is_typedef));
 }

 void MakeTypedefStack()
 {
   pips_assert("TypedefStack is undefined", stack_undefined_p(TypedefStack));
   TypedefStack = stack_make(int_domain, 0, 0);
}

 void ResetTypedefStack()
 {
   if(stack_empty_p(TypedefStack)) {
     stack_free(&TypedefStack);
     TypedefStack = stack_undefined;
   }
   else
     pips_internal_error("TypedefStack is not empty");
 }

void ForceResetTypedefStack()
{
     stack_free(&TypedefStack);
     TypedefStack = stack_undefined;
}

 /* Each scope in the compilation unit has its own number
  *
  * The scope management in the C preprocessor is different from the
  * scope management in the C parser.
 */
#define SCOPE_UNDEFINED (-1)
 static int c_preprocessor_scope_number = SCOPE_UNDEFINED;
 static stack c_preprocessor_scope_stack = stack_undefined;

 void init_preprocessor_scope_stack()
 {
   c_preprocessor_scope_number = 0;
   c_preprocessor_scope_stack = stack_make(string_domain, 0, 0);
 }

 void reset_preprocessor_scope_stack()
 {
   if(c_preprocessor_scope_stack != stack_undefined) {
     if(stack_empty_p(c_preprocessor_scope_stack)) {
       stack_free(&c_preprocessor_scope_stack);
       c_preprocessor_scope_stack = stack_undefined;
     }
     else {
       // pips_internal_error? Could be a bad input C file...
       pips_user_warning("Preprocessor scope stack is not empty.\n");
     }
   }
   c_preprocessor_scope_number = SCOPE_UNDEFINED;
   return;
 }

 /* To be used by an error handler */
 void force_reset_preprocessor_scope_stack()
 {
   if(c_preprocessor_scope_stack != stack_undefined) {
       stack_free(&c_preprocessor_scope_stack);
       c_preprocessor_scope_stack = stack_undefined;
   }
   c_preprocessor_scope_number = SCOPE_UNDEFINED;
   return;
 }

 void push_new_preprocessor_scope()
 {
   c_preprocessor_scope_number++;
   string sn = string_undefined;
   (void) asprintf(&sn, "%d", c_preprocessor_scope_number);
   stack_push((void *) sn, c_preprocessor_scope_stack);
   return;
 }

 void pop_preprocessor_scope()
 {
   stack_pop(c_preprocessor_scope_stack);
   return;
 }

bool preprocessor_scope_stack_empty_p()
{
  return stack_empty_p(c_preprocessor_scope_stack);
}

string get_preprocessor_current_scope()
 {
   string sn = string_undefined;
   if(preprocessor_scope_stack_empty_p()) {
     // We are at the global level: no scope has been entered yet
     sn = "";
   }
   else
     sn = (string) stack_head(c_preprocessor_scope_stack);
   return sn;
 }

string get_preprocessor_nth_scope(int n)
 {
   string sn = (string) stack_nth(c_preprocessor_scope_stack, n);
   return sn;
 }

int preprocessor_scope_number()
 {
   int n = stack_size(c_preprocessor_scope_stack);
   return n;
 }

/* If any of the strings is undefined, we are in trouble. If not,
   concatenate them with separator into a new string and free all input
   strings. No more than six arguments. */

 static int number_of_signatures_built = 0;
 static int number_of_signatures_freed = 0;

static string new_signature(const string s)
  {
    string new_s = strdup(s);
    number_of_signatures_built++;
    return new_s;
  }

static void free_partial_signature(string s)
  {
    number_of_signatures_freed++;
    if(!string_undefined_p(s))
      free(s);
  }

static string general_build_signature(bool arguments_are_defined_p,
				      string s1,
				      va_list * p_some_arguments)
  {
    /* va_list some_arguments; */
    int count = 0;
    string s = NULL;
    string sa[6] = {NULL, NULL, NULL, NULL, NULL, NULL};
    string r = string_undefined;
    int i;
    bool some_argument_undefined_p = false;

    /* va_start(*some_arguments, s1); */
    s = s1;
    while(s) {
      if(string_undefined_p(s)) {
	/* We are in trouble */
	if(arguments_are_defined_p)
	  pips_internal_error("Unexpected undefined argument %d", count+1);
	else
	  some_argument_undefined_p = true;
      }
      else if(s==NULL) {
	/* We are in trouble too */
	pips_internal_error("Unexpected NULL argument");
      }
      else if(strcmp(s, "")==0) {
	free(s);
      }
      else {
	pips_debug(9, "s%d = \"%s\"\n", count, s);
	sa[count++] = s;
      }
      s = va_arg(*p_some_arguments, string);
    }

    pips_assert("No more than 6 effective arguments (check grammar rules).",
		count<=6);

    if(some_argument_undefined_p)
      r = string_undefined;
    else {
      r = strdup(concatenate("", sa[0], " ", sa[1], " ", sa[2], " ",
			     sa[3], " ", sa[4], " ", sa[5], "", NULL));

      number_of_signatures_built++;
    }

    pips_debug(9, "%d arguments:\n", count);

    for(i=0; i<count; i++) {
      int j;
      for(j=0; i<count; i++) {
	if(sa[i]==sa[j]&&i!=j) pips_internal_error("Unexpected common arguments\n");
      }
    }

    for(i=0; i<count; i++) {
      /* pips_debug(9, "s%d = \"%s\"\n", i, sa[i]); */
      number_of_signatures_freed++;
      free(sa[i]);
    }

    pips_assert("An argument may be really undefined only if"
		" arguments are not guaranteed to be defined",
		!(some_argument_undefined_p && arguments_are_defined_p));
    pips_assert("If all arguments are defined, the result is defined",
		some_argument_undefined_p || !string_undefined_p(r));

    pips_debug(8, "Returns: \"%s\"\n", string_undefined_p(r)? "STRING_UNDEFINED" : r);

    return r;
  }

/* All arguments must be defined. The result is always defined. */
static string build_signature(string s1, ...)
  {
    va_list some_arguments;

    va_start(some_arguments, s1);
    return general_build_signature(true, s1, &some_arguments);
  }

/* Arguments may be defined or not, but as soon as one is undefined, an
   undefined_string is returned.*/
static string safe_build_signature(string s1, ...)
  {
    va_list some_arguments;

    va_start(some_arguments, s1);
    return general_build_signature(false, s1, &some_arguments);
  }

/* Get rid of useless spaces: multiple contiguous spaces, spaces next to a
   separator,... Some look ahead required to get rid of spaces before a
   separator. Could be moved into build_signature but it seemed easier to
   separate concerns. */
 static string simplify_signature(string s)
   {
     string new_s = strdup(s); /* Make sure to allocate enough space... */
     string source = s+1;
     string destination = new_s;

     pips_debug(8, "Begin with signature \"%s\"\n", s);

     pips_assert("The signature is not empty", *s);

     /* source points to the next character to copy and destination to the
        last character copied. The first character is already copied. */
     while(*source) {
       if(*destination==' ') {
	 if(*source==' ') {
	   /* Do not copy a second space */
	   source++;
	 }
	 else if (*source==',' || *source=='(' || *source==')' || *source==';') {
	   /* Overwrite the space in the destination */
	 *destination = *source++;
	 }
	 else {
	   /* Normal copy */
	 *++destination = *source++;
	 }
       }
       else if(*destination=='(' || *destination=='*') {
	 if(*source==' ') {
	   /* Do not copy a space after some separators */
	   source++;
	 }
	 else {
	 /* Normal copy */
	 *++destination = *source++;
	 }
       }
       else {
	 /* Normal copy */
	 *++destination = *source++;
       }
     }

     /* Get rid of a trailing SPACE. */
     if(*destination==' ')
       *(destination) = '\000';
     else
       *(destination+1) = '\000';

     pips_debug(8, "End with signature \"%s\"\n", new_s);

     free_partial_signature(s);
     return new_s;
   }

 int check_signature_balance()
   {
     int imbalance = number_of_signatures_built - number_of_signatures_freed;
     if(imbalance<0) {
       /* pips_internal_error("More signatures freed than allocated: %d\n", imbalance); */
       pips_debug(5, "More signatures freed than allocated: %d\n", imbalance);
     }
     return imbalance;
   }

/* Beware of the free: no constant strings in signature! */
static string new_empty()
   {
     return new_signature("");
   }
static string new_comma()
   {
     return new_signature(",");
   }
static string new_eq()
   {
     return new_signature("=");
   }
static string new_star()
   {
     return new_signature("*");
   }
static string new_semicolon()
   {
     return new_signature(";");
   }
static string new_colon()
   {
     return new_signature(":");
   }

static string new_lbrace()
   {
     return new_signature("{");
   }
static string new_rbrace()
   {
     return new_signature("}");
   }
static string new_lparen()
   {
     return new_signature("(");
   }
static string new_rparen()
   {
     return new_signature(")");
   }
static string new_lbracket()
   {
     return new_signature("[");
   }
static string new_rbracket()
   {
     return new_signature("]");
   }
static string new_ellipsis()
   {
     return new_signature("...");
   }

/* Line 336 of yacc.c  */
#line 587 "y.tab.c"

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
#ifndef SPLITC_Y_TAB_H
# define SPLITC_Y_TAB_H
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int splitc_debug;
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
     TK_CONST = 285,
     TK_RESTRICT = 286,
     TK_AUTO = 287,
     TK_REGISTER = 288,
     TK_THREAD = 289,
     TK_STATIC_DIMENSION = 290,
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
     TK_AT_TRANSFORM = 365,
     TK_AT_TRANSFORMEXPR = 366,
     TK_AT_SPECIFIER = 367,
     TK_AT_EXPR = 368,
     TK_AT_NAME = 369,
     TK_COMPLEXCON = 370,
     TK_ADDROF = 371,
     TK_CAST = 372
   };
#endif
/* Tokens.  */
#define TK_IDENT 258
#define TK_CHARCON 259
#define TK_INTCON 260
#define TK_FLOATCON 261
#define TK_NAMED_TYPE 262
#define TK_STRINGCON 263
#define TK_WSTRINGCON 264
#define TK_EOF 265
#define TK_CHAR 266
#define TK_INT 267
#define TK_INT128 268
#define TK_UINT128 269
#define TK_DOUBLE 270
#define TK_FLOAT 271
#define TK_VOID 272
#define TK_COMPLEX 273
#define TK_ENUM 274
#define TK_STRUCT 275
#define TK_TYPEDEF 276
#define TK_UNION 277
#define TK_SIGNED 278
#define TK_UNSIGNED 279
#define TK_LONG 280
#define TK_SHORT 281
#define TK_VOLATILE 282
#define TK_EXTERN 283
#define TK_STATIC 284
#define TK_CONST 285
#define TK_RESTRICT 286
#define TK_AUTO 287
#define TK_REGISTER 288
#define TK_THREAD 289
#define TK_STATIC_DIMENSION 290
#define TK_SIZEOF 291
#define TK_ALIGNOF 292
#define TK_EQ 293
#define TK_PLUS_EQ 294
#define TK_MINUS_EQ 295
#define TK_STAR_EQ 296
#define TK_SLASH_EQ 297
#define TK_PERCENT_EQ 298
#define TK_AND_EQ 299
#define TK_PIPE_EQ 300
#define TK_CIRC_EQ 301
#define TK_INF_INF_EQ 302
#define TK_SUP_SUP_EQ 303
#define TK_ARROW 304
#define TK_DOT 305
#define TK_EQ_EQ 306
#define TK_EXCLAM_EQ 307
#define TK_INF 308
#define TK_SUP 309
#define TK_INF_EQ 310
#define TK_SUP_EQ 311
#define TK_PLUS 312
#define TK_MINUS 313
#define TK_STAR 314
#define TK_SLASH 315
#define TK_PERCENT 316
#define TK_TILDE 317
#define TK_AND 318
#define TK_PIPE 319
#define TK_CIRC 320
#define TK_EXCLAM 321
#define TK_AND_AND 322
#define TK_PIPE_PIPE 323
#define TK_INF_INF 324
#define TK_SUP_SUP 325
#define TK_PLUS_PLUS 326
#define TK_MINUS_MINUS 327
#define TK_RPAREN 328
#define TK_LPAREN 329
#define TK_RBRACE 330
#define TK_LBRACE 331
#define TK_LBRACKET 332
#define TK_RBRACKET 333
#define TK_COLON 334
#define TK_SEMICOLON 335
#define TK_COMMA 336
#define TK_ELLIPSIS 337
#define TK_QUEST 338
#define TK_BREAK 339
#define TK_CONTINUE 340
#define TK_GOTO 341
#define TK_RETURN 342
#define TK_SWITCH 343
#define TK_CASE 344
#define TK_DEFAULT 345
#define TK_WHILE 346
#define TK_DO 347
#define TK_FOR 348
#define TK_IF 349
#define TK_ELSE 350
#define TK_ATTRIBUTE 351
#define TK_INLINE 352
#define TK_ASM 353
#define TK_TYPEOF 354
#define TK_FUNCTION__ 355
#define TK_PRETTY_FUNCTION__ 356
#define TK_LABEL__ 357
#define TK_BUILTIN_VA_ARG 358
#define TK_BUILTIN_VA_LIST 359
#define TK_BLOCKATTRIBUTE 360
#define TK_DECLSPEC 361
#define TK_MSASM 362
#define TK_MSATTR 363
#define TK_PRAGMA 364
#define TK_AT_TRANSFORM 365
#define TK_AT_TRANSFORMEXPR 366
#define TK_AT_SPECIFIER 367
#define TK_AT_EXPR 368
#define TK_AT_NAME 369
#define TK_COMPLEXCON 370
#define TK_ADDROF 371
#define TK_CAST 372



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 350 of yacc.c  */
#line 566 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"

	basic basic;
        char character;
	cons * liste;
	dimension dimension;
	entity entity;
	expression expression;
	statement statement;
	int integer;
	string string;
	syntax syntax;
	tag tag;
	type type;
	value value;
        parameter parameter;


/* Line 350 of yacc.c  */
#line 882 "y.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE splitc_lval;

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int splitc_parse (void *YYPARSE_PARAM);
#else
int splitc_parse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int splitc_parse (void);
#else
int splitc_parse ();
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !SPLITC_Y_TAB_H  */

/* Copy the second part of user declarations.  */

/* Line 353 of yacc.c  */
#line 910 "y.tab.c"

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
#define YYFINAL  99
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   3937

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  118
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  91
/* YYNRULES -- Number of rules.  */
#define YYNRULES  351
/* YYNRULES -- Number of states.  */
#define YYNSTATES  664

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   372

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
     115,   116,   117
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     6,     8,     9,    12,    15,    16,    18,
      20,    26,    29,    36,    41,    50,    59,    63,    65,    67,
      72,    73,    75,    77,    79,    82,    87,    90,    95,    98,
     101,   104,   107,   110,   113,   116,   119,   122,   125,   129,
     133,   137,   139,   144,   151,   154,   160,   164,   168,   172,
     176,   180,   184,   188,   192,   196,   200,   204,   208,   212,
     216,   220,   224,   228,   232,   236,   240,   244,   248,   252,
     256,   260,   264,   268,   272,   276,   281,   288,   291,   296,
     298,   300,   302,   304,   306,   308,   310,   312,   314,   317,
     319,   322,   325,   327,   329,   331,   333,   337,   339,   343,
     344,   346,   350,   353,   355,   357,   358,   362,   367,   373,
     374,   376,   379,   380,   382,   383,   385,   387,   391,   395,
     396,   398,   402,   406,   410,   414,   415,   416,   425,   429,
     430,   433,   434,   437,   438,   441,   444,   445,   450,   452,
     456,   458,   461,   463,   467,   473,   474,   475,   481,   482,
     487,   488,   495,   496,   501,   505,   509,   515,   518,   521,
     525,   528,   531,   535,   540,   548,   550,   552,   556,   564,
     571,   575,   578,   580,   584,   586,   590,   593,   596,   599,
     602,   605,   608,   611,   614,   617,   622,   623,   625,   626,
     628,   630,   632,   634,   636,   638,   640,   642,   644,   646,
     648,   650,   652,   654,   657,   663,   668,   671,   677,   682,
     685,   692,   698,   700,   705,   710,   711,   715,   720,   724,
     726,   730,   732,   736,   739,   741,   745,   749,   751,   755,
     759,   761,   766,   772,   778,   783,   785,   786,   789,   790,
     793,   797,   800,   803,   805,   809,   812,   818,   822,   824,
     828,   829,   834,   839,   841,   845,   847,   851,   852,   854,
     857,   859,   863,   865,   870,   874,   879,   884,   886,   887,
     890,   893,   896,   901,   907,   911,   912,   915,   916,   919,
     925,   930,   933,   935,   937,   939,   941,   943,   944,   946,
     950,   954,   958,   961,   963,   965,   967,   970,   975,   978,
     983,   986,   989,   992,   995,   998,  1001,  1005,  1009,  1013,
    1017,  1021,  1025,  1029,  1033,  1037,  1041,  1045,  1049,  1053,
    1057,  1061,  1065,  1069,  1073,  1077,  1081,  1085,  1086,  1088,
    1092,  1096,  1100,  1104,  1105,  1108,  1111,  1113,  1116,  1117,
    1121,  1122,  1124,  1126,  1130,  1135,  1140,  1141,  1145,  1146,
    1149,  1151
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     119,     0,    -1,   120,    10,    -1,   121,    -1,    -1,   123,
     121,    -1,    80,   121,    -1,    -1,   162,    -1,   192,    -1,
      98,    74,   128,    73,    80,    -1,   109,   197,    -1,     3,
      74,   183,    73,   184,    80,    -1,     3,    74,    73,    80,
      -1,   110,    76,   123,    75,     3,    76,   121,    75,    -1,
     111,    76,   126,    75,     3,    76,   126,    75,    -1,   122,
       1,    80,    -1,     3,    -1,     7,    -1,   114,    74,     3,
      73,    -1,    -1,    81,    -1,   127,    -1,     3,    -1,    36,
     126,    -1,    36,    74,   188,    73,    -1,    37,   126,    -1,
      37,    74,   188,    73,    -1,    57,   126,    -1,    58,   126,
      -1,    59,   126,    -1,    63,   126,    -1,    66,   126,    -1,
      62,   126,    -1,    71,   126,    -1,   126,    71,    -1,    72,
     126,    -1,   126,    72,    -1,   126,    49,   124,    -1,   126,
      50,   124,    -1,    74,   147,    73,    -1,   145,    -1,   126,
      74,   141,    73,    -1,   103,    74,   126,    81,   188,    73,
      -1,   126,   146,    -1,   126,    83,   142,    79,   126,    -1,
     126,    57,   126,    -1,   126,    58,   126,    -1,   126,    59,
     126,    -1,   126,    60,   126,    -1,   126,    61,   126,    -1,
     126,    67,   126,    -1,   126,    68,   126,    -1,   126,    63,
     126,    -1,   126,    64,   126,    -1,   126,    65,   126,    -1,
     126,    51,   126,    -1,   126,    52,   126,    -1,   126,    53,
     126,    -1,   126,    54,   126,    -1,   126,    55,   126,    -1,
     126,    56,   126,    -1,   126,    69,   126,    -1,   126,    70,
     126,    -1,   126,    38,   126,    -1,   126,    39,   126,    -1,
     126,    40,   126,    -1,   126,    41,   126,    -1,   126,    42,
     126,    -1,   126,    43,   126,    -1,   126,    44,   126,    -1,
     126,    45,   126,    -1,   126,    46,   126,    -1,   126,    47,
     126,    -1,   126,    48,   126,    -1,    74,   188,    73,   126,
      -1,    74,   188,    73,    76,   135,    75,    -1,    67,     3,
      -1,   113,    74,     3,    73,    -1,     5,    -1,     6,    -1,
     115,    -1,     4,    -1,   128,    -1,   131,    -1,   130,    -1,
       8,    -1,   132,    -1,   130,   132,    -1,     9,    -1,   131,
     132,    -1,   131,     9,    -1,     8,    -1,   100,    -1,   101,
      -1,   126,    -1,    76,   135,    75,    -1,   136,    -1,   136,
      81,   135,    -1,    -1,   134,    -1,   138,   137,   133,    -1,
     140,   133,    -1,   133,    -1,    38,    -1,    -1,    50,   124,
     139,    -1,    77,   126,    78,   139,    -1,    77,   126,    82,
     126,    78,    -1,    -1,   138,    -1,   124,    79,    -1,    -1,
     143,    -1,    -1,   143,    -1,   126,    -1,   126,    81,   143,
      -1,     1,    81,   143,    -1,    -1,   143,    -1,    74,   143,
      73,    -1,    74,     1,    73,    -1,    77,   143,    78,    -1,
      77,     1,    78,    -1,    -1,    -1,    76,   148,   153,   150,
     151,   152,   149,    75,    -1,     1,   122,    75,    -1,    -1,
     105,   199,    -1,    -1,   162,   151,    -1,    -1,   155,   152,
      -1,     3,    79,    -1,    -1,   102,   154,    80,   153,    -1,
       3,    -1,     3,    81,   154,    -1,    80,    -1,   143,    80,
      -1,   147,    -1,    94,   145,   155,    -1,    94,   145,   155,
      95,   155,    -1,    -1,    -1,    88,   156,   145,   157,   155,
      -1,    -1,    91,   158,   145,   155,    -1,    -1,    92,   159,
     155,    91,   145,    80,    -1,    -1,    93,   160,    74,   161,
      -1,     3,    79,   155,    -1,    89,   126,    79,    -1,    89,
     126,    82,   126,    79,    -1,    90,    79,    -1,    87,    80,
      -1,    87,   143,    80,    -1,    84,    80,    -1,    85,    80,
      -1,    86,     3,    80,    -1,    86,    59,   143,    80,    -1,
      98,   200,    74,   201,   202,    73,    80,    -1,   107,    -1,
     162,    -1,     1,   122,    80,    -1,   142,    80,   142,    80,
     142,    73,   155,    -1,   162,   142,    80,   142,    73,   155,
      -1,   165,   163,    80,    -1,   165,    80,    -1,   164,    -1,
     164,    81,   163,    -1,   175,    -1,   175,    38,   133,    -1,
      21,   166,    -1,    28,   166,    -1,    29,   166,    -1,    32,
     166,    -1,    33,   166,    -1,    34,   166,    -1,   169,   167,
      -1,    97,   166,    -1,   196,   166,    -1,   112,    74,     3,
      73,    -1,    -1,   165,    -1,    -1,   168,    -1,   165,    -1,
      17,    -1,    11,    -1,    26,    -1,    12,    -1,    13,    -1,
      14,    -1,    18,    -1,    25,    -1,    16,    -1,    15,    -1,
      23,    -1,    24,    -1,    20,   124,    -1,    20,   124,    76,
     170,    75,    -1,    20,    76,   170,    75,    -1,    22,   124,
      -1,    22,   124,    76,   170,    75,    -1,    22,    76,   170,
      75,    -1,    19,   124,    -1,    19,   124,    76,   173,   125,
      75,    -1,    19,    76,   173,   125,    75,    -1,     7,    -1,
      99,    74,   126,    73,    -1,    99,    74,   188,    73,    -1,
      -1,   165,    80,   170,    -1,   165,   171,    80,   170,    -1,
       1,    80,   170,    -1,   172,    -1,   172,    81,   171,    -1,
     175,    -1,   175,    79,   126,    -1,    79,   126,    -1,   174,
      -1,   173,    81,   174,    -1,   173,    81,     1,    -1,     3,
      -1,     3,    38,   126,    -1,   187,   176,   195,    -1,   124,
      -1,    74,   194,   175,    73,    -1,   176,    77,   194,   144,
      78,    -1,   176,    77,   194,     1,    78,    -1,   176,   177,
     178,    73,    -1,    74,    -1,    -1,   180,   179,    -1,    -1,
      81,    82,    -1,    81,   180,   179,    -1,   165,   175,    -1,
     165,   189,    -1,   165,    -1,    74,   180,    73,    -1,   187,
     182,    -1,   176,    74,   183,    73,   184,    -1,   176,    74,
      73,    -1,     3,    -1,     3,    81,   183,    -1,    -1,   165,
     185,    80,    82,    -1,   165,   185,    80,   184,    -1,   175,
      -1,   175,    81,   185,    -1,     1,    -1,    59,   194,   187,
      -1,    -1,   186,    -1,   165,   189,    -1,   165,    -1,   187,
     190,   194,    -1,   186,    -1,    74,   194,   189,    73,    -1,
      74,     1,    73,    -1,   191,    77,   144,    78,    -1,   190,
     177,   178,    73,    -1,   190,    -1,    -1,   193,   147,    -1,
     165,   175,    -1,   165,   181,    -1,     3,   177,   178,    73,
      -1,     3,    74,   183,    73,   184,    -1,     3,    74,    73,
      -1,    -1,   196,   194,    -1,    -1,   196,   195,    -1,    98,
      74,   128,    73,   194,    -1,    96,    74,   199,    73,    -1,
     106,   199,    -1,   108,    -1,    30,    -1,    31,    -1,    27,
      -1,    35,    -1,    -1,   124,    -1,     3,    79,     5,    -1,
      90,    79,     5,    -1,     3,    74,    73,    -1,     3,   199,
      -1,     5,    -1,   128,    -1,    30,    -1,    36,   126,    -1,
      36,    74,   188,    73,    -1,    37,   126,    -1,    37,    74,
     188,    73,    -1,    57,   126,    -1,    58,   126,    -1,    59,
     126,    -1,    63,   126,    -1,    66,   126,    -1,    62,   126,
      -1,   197,    57,   197,    -1,   197,    58,   197,    -1,   197,
      59,   126,    -1,   197,    60,   197,    -1,   197,    61,   197,
      -1,   197,    67,   197,    -1,   197,    68,   197,    -1,   197,
      63,   197,    -1,   197,    64,   197,    -1,   197,    65,   197,
      -1,   197,    51,   197,    -1,   197,    52,   197,    -1,   197,
      53,   197,    -1,   197,    54,   197,    -1,   197,    55,   197,
      -1,   197,    56,   197,    -1,   197,    69,   197,    -1,   197,
      70,   197,    -1,   197,    49,   124,    -1,   197,    50,   124,
      -1,    74,   197,    73,    -1,    -1,   197,    -1,   197,    81,
     198,    -1,     1,    81,   198,    -1,    74,   198,    73,    -1,
      74,     1,    73,    -1,    -1,    27,   200,    -1,    30,   200,
      -1,   129,    -1,   129,   201,    -1,    -1,    79,   203,   206,
      -1,    -1,   204,    -1,   205,    -1,   204,    81,   205,    -1,
     128,    74,   126,    73,    -1,   128,    74,     1,    73,    -1,
      -1,    79,   203,   207,    -1,    -1,    79,   208,    -1,   129,
      -1,   129,    81,   208,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   742,   742,   744,   747,   748,   749,   753,   758,   773,
     796,   800,   807,   812,   817,   822,   826,   833,   837,   839,
     848,   849,   857,   861,   867,   873,   879,   884,   889,   893,
     897,   901,   905,   909,   913,   917,   921,   925,   929,   933,
     937,   942,   946,   952,   958,   964,   976,   980,   984,   988,
     992,   996,  1000,  1004,  1008,  1012,  1016,  1023,  1030,  1037,
    1044,  1051,  1058,  1065,  1072,  1078,  1084,  1090,  1096,  1102,
    1108,  1114,  1120,  1126,  1132,  1138,  1145,  1152,  1156,  1165,
    1169,  1173,  1177,  1181,  1187,  1196,  1202,  1206,  1209,  1215,
    1218,  1221,  1228,  1229,  1231,  1236,  1237,  1241,  1244,  1249,
    1250,  1253,  1256,  1259,  1262,  1266,  1270,  1272,  1274,  1278,
    1279,  1283,  1289,  1290,  1295,  1296,  1304,  1308,  1312,  1320,
    1321,  1325,  1330,  1338,  1342,  1349,  1349,  1349,  1354,  1359,
    1360,  1365,  1366,  1372,  1373,  1377,  1381,  1382,  1387,  1388,
    1392,  1395,  1399,  1400,  1404,  1409,  1412,  1408,  1419,  1418,
    1426,  1425,  1433,  1432,  1438,  1441,  1445,  1450,  1453,  1456,
    1460,  1463,  1466,  1469,  1473,  1475,  1477,  1479,  1485,  1488,
    1494,  1507,  1521,  1525,  1532,  1535,  1550,  1562,  1571,  1581,
    1590,  1599,  1609,  1637,  1646,  1657,  1670,  1671,  1679,  1679,
    1695,  1705,  1710,  1715,  1720,  1725,  1730,  1735,  1740,  1745,
    1750,  1755,  1760,  1765,  1786,  1799,  1806,  1814,  1823,  1829,
    1837,  1845,  1850,  1855,  1860,  1870,  1871,  1876,  1882,  1890,
    1894,  1901,  1902,  1906,  1913,  1917,  1921,  1929,  1935,  1944,
    1970,  1996,  2000,  2012,  2016,  2023,  2027,  2028,  2045,  2046,
    2050,  2057,  2062,  2084,  2089,  2098,  2104,  2116,  2123,  2127,
    2134,  2135,  2148,  2157,  2161,  2165,  2173,  2182,  2183,  2188,
    2193,  2201,  2206,  2216,  2220,  2225,  2230,  2237,  2241,  2245,
    2250,  2279,  2305,  2324,  2346,  2362,  2363,  2371,  2372,  2374,
    2389,  2394,  2398,  2403,  2407,  2411,  2415,  2424,  2425,  2427,
    2429,  2431,  2433,  2435,  2437,  2439,  2441,  2445,  2448,  2452,
    2454,  2458,  2460,  2462,  2465,  2467,  2469,  2471,  2473,  2475,
    2477,  2479,  2481,  2483,  2486,  2488,  2490,  2492,  2494,  2496,
    2498,  2500,  2502,  2504,  2506,  2508,  2510,  2514,  2515,  2517,
    2519,  2523,  2528,  2537,  2538,  2540,  2544,  2546,  2551,  2552,
    2557,  2558,  2562,  2564,  2568,  2570,  2575,  2576,  2581,  2582,
    2586,  2588
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
  "TK_SHORT", "TK_VOLATILE", "TK_EXTERN", "TK_STATIC", "TK_CONST",
  "TK_RESTRICT", "TK_AUTO", "TK_REGISTER", "TK_THREAD",
  "TK_STATIC_DIMENSION", "TK_SIZEOF", "TK_ALIGNOF", "TK_EQ", "TK_PLUS_EQ",
  "TK_MINUS_EQ", "TK_STAR_EQ", "TK_SLASH_EQ", "TK_PERCENT_EQ", "TK_AND_EQ",
  "TK_PIPE_EQ", "TK_CIRC_EQ", "TK_INF_INF_EQ", "TK_SUP_SUP_EQ", "TK_ARROW",
  "TK_DOT", "TK_EQ_EQ", "TK_EXCLAM_EQ", "TK_INF", "TK_SUP", "TK_INF_EQ",
  "TK_SUP_EQ", "TK_PLUS", "TK_MINUS", "TK_STAR", "TK_SLASH", "TK_PERCENT",
  "TK_TILDE", "TK_AND", "TK_PIPE", "TK_CIRC", "TK_EXCLAM", "TK_AND_AND",
  "TK_PIPE_PIPE", "TK_INF_INF", "TK_SUP_SUP", "TK_PLUS_PLUS",
  "TK_MINUS_MINUS", "TK_RPAREN", "TK_LPAREN", "TK_RBRACE", "TK_LBRACE",
  "TK_LBRACKET", "TK_RBRACKET", "TK_COLON", "TK_SEMICOLON", "TK_COMMA",
  "TK_ELLIPSIS", "TK_QUEST", "TK_BREAK", "TK_CONTINUE", "TK_GOTO",
  "TK_RETURN", "TK_SWITCH", "TK_CASE", "TK_DEFAULT", "TK_WHILE", "TK_DO",
  "TK_FOR", "TK_IF", "TK_ELSE", "TK_ATTRIBUTE", "TK_INLINE", "TK_ASM",
  "TK_TYPEOF", "TK_FUNCTION__", "TK_PRETTY_FUNCTION__", "TK_LABEL__",
  "TK_BUILTIN_VA_ARG", "TK_BUILTIN_VA_LIST", "TK_BLOCKATTRIBUTE",
  "TK_DECLSPEC", "TK_MSASM", "TK_MSATTR", "TK_PRAGMA", "TK_AT_TRANSFORM",
  "TK_AT_TRANSFORMEXPR", "TK_AT_SPECIFIER", "TK_AT_EXPR", "TK_AT_NAME",
  "TK_COMPLEXCON", "TK_ADDROF", "TK_CAST", "$accept", "interpret", "file",
  "globals", "location", "global", "id_or_typename", "maybecomma",
  "expression", "constant", "string_constant", "one_string_constant",
  "string_list", "wstring_list", "one_string", "init_expression",
  "initializer_list", "initializer_list_opt", "initializer", "eq_opt",
  "init_designators", "init_designators_opt", "gcc_init_designators",
  "arguments", "opt_expression", "comma_expression",
  "comma_expression_opt", "paren_comma_expression",
  "bracket_comma_expression", "block", "$@1", "$@2", "block_attrs",
  "declaration_list", "statement_list", "local_labels",
  "local_label_names", "statement", "$@3", "$@4", "$@5", "$@6", "$@7",
  "for_clause", "declaration", "init_declarator_list", "init_declarator",
  "decl_spec_list", "decl_spec_list_opt", "decl_spec_list_opt_no_named",
  "@8", "type_spec", "struct_decl_list", "field_decl_list", "field_decl",
  "enum_list", "enumerator", "declarator", "direct_decl",
  "parameter_list_startscope", "rest_par_list", "rest_par_list1",
  "parameter_decl", "old_proto_decl", "direct_old_proto_decl",
  "old_parameter_list_ne", "old_pardef_list", "old_pardef", "pointer",
  "pointer_opt", "type_name", "abstract_decl", "abs_direct_decl",
  "abs_direct_decl_opt", "function_def", "function_def_start",
  "attributes", "attributes_with_asm", "attribute", "attr", "attr_list_ne",
  "paren_attr_list_ne", "asmattr", "asmtemplate", "asmoutputs",
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
     365,   366,   367,   368,   369,   370,   371,   372
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   118,   119,   120,   121,   121,   121,   122,   123,   123,
     123,   123,   123,   123,   123,   123,   123,   124,   124,   124,
     125,   125,   126,   126,   126,   126,   126,   126,   126,   126,
     126,   126,   126,   126,   126,   126,   126,   126,   126,   126,
     126,   126,   126,   126,   126,   126,   126,   126,   126,   126,
     126,   126,   126,   126,   126,   126,   126,   126,   126,   126,
     126,   126,   126,   126,   126,   126,   126,   126,   126,   126,
     126,   126,   126,   126,   126,   126,   126,   126,   126,   127,
     127,   127,   127,   127,   127,   128,   129,   130,   130,   131,
     131,   131,   132,   132,   132,   133,   133,   134,   134,   135,
     135,   136,   136,   136,   137,   137,   138,   138,   138,   139,
     139,   140,   141,   141,   142,   142,   143,   143,   143,   144,
     144,   145,   145,   146,   146,   148,   149,   147,   147,   150,
     150,   151,   151,   152,   152,   152,   153,   153,   154,   154,
     155,   155,   155,   155,   155,   156,   157,   155,   158,   155,
     159,   155,   160,   155,   155,   155,   155,   155,   155,   155,
     155,   155,   155,   155,   155,   155,   155,   155,   161,   161,
     162,   162,   163,   163,   164,   164,   165,   165,   165,   165,
     165,   165,   165,   165,   165,   165,   166,   166,   168,   167,
     167,   169,   169,   169,   169,   169,   169,   169,   169,   169,
     169,   169,   169,   169,   169,   169,   169,   169,   169,   169,
     169,   169,   169,   169,   169,   170,   170,   170,   170,   171,
     171,   172,   172,   172,   173,   173,   173,   174,   174,   175,
     176,   176,   176,   176,   176,   177,   178,   178,   179,   179,
     179,   180,   180,   180,   180,   181,   182,   182,   183,   183,
     184,   184,   184,   185,   185,   185,   186,   187,   187,   188,
     188,   189,   189,   190,   190,   190,   190,   191,   191,   192,
     193,   193,   193,   193,   193,   194,   194,   195,   195,   195,
     196,   196,   196,   196,   196,   196,   196,   197,   197,   197,
     197,   197,   197,   197,   197,   197,   197,   197,   197,   197,
     197,   197,   197,   197,   197,   197,   197,   197,   197,   197,
     197,   197,   197,   197,   197,   197,   197,   197,   197,   197,
     197,   197,   197,   197,   197,   197,   197,   198,   198,   198,
     198,   199,   199,   200,   200,   200,   201,   201,   202,   202,
     203,   203,   204,   204,   205,   205,   206,   206,   207,   207,
     208,   208
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     1,     0,     2,     2,     0,     1,     1,
       5,     2,     6,     4,     8,     8,     3,     1,     1,     4,
       0,     1,     1,     1,     2,     4,     2,     4,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     3,     3,
       3,     1,     4,     6,     2,     5,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     4,     6,     2,     4,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     1,
       2,     2,     1,     1,     1,     1,     3,     1,     3,     0,
       1,     3,     2,     1,     1,     0,     3,     4,     5,     0,
       1,     2,     0,     1,     0,     1,     1,     3,     3,     0,
       1,     3,     3,     3,     3,     0,     0,     8,     3,     0,
       2,     0,     2,     0,     2,     2,     0,     4,     1,     3,
       1,     2,     1,     3,     5,     0,     0,     5,     0,     4,
       0,     6,     0,     4,     3,     3,     5,     2,     2,     3,
       2,     2,     3,     4,     7,     1,     1,     3,     7,     6,
       3,     2,     1,     3,     1,     3,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     4,     0,     1,     0,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     5,     4,     2,     5,     4,     2,
       6,     5,     1,     4,     4,     0,     3,     4,     3,     1,
       3,     1,     3,     2,     1,     3,     3,     1,     3,     3,
       1,     4,     5,     5,     4,     1,     0,     2,     0,     2,
       3,     2,     2,     1,     3,     2,     5,     3,     1,     3,
       0,     4,     4,     1,     3,     1,     3,     0,     1,     2,
       1,     3,     1,     4,     3,     4,     4,     1,     0,     2,
       2,     2,     4,     5,     3,     0,     2,     0,     2,     5,
       4,     2,     1,     1,     1,     1,     1,     0,     1,     3,
       3,     3,     2,     1,     1,     1,     2,     4,     2,     4,
       2,     2,     2,     2,     2,     2,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     0,     1,     3,
       3,     3,     3,     0,     2,     2,     1,     2,     0,     3,
       0,     1,     1,     3,     4,     4,     0,     3,     0,     2,
       1,     3
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       4,     0,   212,   192,   194,   195,   196,   200,   199,   191,
     197,     0,     0,   186,     0,   201,   202,   198,   193,   285,
     186,   186,   283,   284,   186,   186,   186,   286,     4,     0,
     186,     0,     0,     0,   282,   287,     0,     0,     0,     0,
       0,     3,     0,     4,     8,   257,   188,     9,     0,   186,
     235,   236,    17,    18,     0,     0,   209,     0,   203,   187,
     176,     0,   206,   177,   178,   179,   180,   181,     6,     0,
     183,     0,     0,     0,   281,    17,   293,    92,   295,     0,
       0,     0,     0,     0,     0,     0,     0,   287,     0,    93,
      94,   288,   294,    85,    87,    11,     7,     0,     0,     1,
       2,     0,     5,   275,   171,     0,   172,   174,   271,   258,
       0,   190,   182,   189,     7,   125,   269,   184,   248,     0,
       0,   257,     0,   238,   227,    20,   224,     0,     0,     0,
     257,     0,     0,     0,     0,     0,     0,    23,    82,    79,
      80,    89,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    81,     0,    22,    83,
      84,    41,   257,     0,     0,   328,     0,     0,     0,   292,
       0,   296,     0,   298,   300,   301,   302,   305,   303,   304,
       0,     0,    88,     0,     0,   287,   287,   287,   287,   287,
     287,   287,   287,     0,   287,   287,   287,   287,   287,   287,
     287,   287,   287,     0,     0,     0,    16,   257,   275,   170,
     257,     0,   275,   230,   277,   245,     0,   136,     0,   250,
       0,   241,   258,   268,   242,   272,     0,   237,     0,     0,
       0,     0,    20,     0,     0,     0,     0,   219,   221,     0,
     205,     0,   208,     0,   280,     0,     0,    24,     0,    26,
      28,    29,    30,    33,    31,    32,    77,    34,    36,     7,
     116,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    35,    37,   213,
       0,     0,     0,    44,    91,    90,   268,   259,   214,   332,
       0,     0,   331,   291,   289,     0,     0,   326,   290,   324,
     325,   316,   317,   318,   319,   320,   321,   306,   307,   308,
     309,   310,   313,   314,   315,   311,   312,   322,   323,     0,
       0,   185,   256,   276,   173,   174,    99,    95,   175,   257,
     235,   275,     0,   236,   229,   277,   128,     0,   129,   249,
       0,   273,   244,     0,   277,   275,     0,   239,   238,   228,
     226,   225,   211,    19,     0,   218,   223,   216,     0,   257,
       0,   204,   207,    10,     0,     0,   122,     0,     0,   121,
      40,     0,     0,     0,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    38,    39,    56,    57,    58,
      59,    60,    61,    46,    47,    48,    49,    50,    53,    54,
      55,    51,    52,    62,    63,     0,     0,   113,     0,     0,
       0,   115,     0,     0,   330,   329,   297,   299,     0,     0,
      23,     0,     0,     0,   103,   100,     0,    97,   105,     0,
       0,     0,     0,     0,     0,   278,   138,     0,     0,   131,
     255,   253,     0,    12,     0,   257,   235,   236,   261,     0,
     240,   210,   217,   220,   222,    25,    27,   118,   117,    99,
      75,     0,    78,    42,   124,   123,     0,   257,     4,     0,
     109,     0,   111,    96,    99,   104,     0,   102,   231,   250,
       0,   120,     0,     0,   234,     0,   136,   130,     0,   131,
     257,     0,   250,   264,     0,     0,     0,     0,     0,    45,
       0,     0,   110,   106,   109,     0,    98,   101,   246,   233,
     232,   275,   139,   137,     7,    23,   140,     0,     0,     0,
       0,   145,     0,     0,   148,   150,   152,     0,   333,   165,
       0,   142,   126,     0,   166,   132,   254,   251,   252,   263,
     266,   265,    76,    43,    14,    15,   107,     0,   279,     0,
       0,   160,   161,     0,     0,   158,     0,     0,     0,   157,
       0,     0,     0,     0,     0,   333,   333,     0,   141,     0,
     134,   108,   167,    23,   154,   162,     0,   159,   146,   155,
       0,     0,     0,     0,     0,   143,   334,   335,     0,   127,
       0,   163,     0,     0,   149,     0,     0,   153,     0,     0,
      86,   336,   338,   147,   156,     0,     0,     0,   144,   337,
     340,     0,   151,     0,     0,     0,   346,   341,   342,     0,
       0,     0,     0,   340,   339,     0,   164,     0,     0,     0,
       0,   348,   343,     0,   169,   345,   344,     0,   347,   168,
     350,   349,     0,   351
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    39,    40,    41,    42,    43,    91,   230,   260,   158,
     159,   621,    93,   160,    94,   444,   445,   446,   447,   496,
     448,   523,   449,   426,   430,   550,   502,   161,   303,   551,
     217,   589,   459,   508,   552,   358,   457,   553,   577,   612,
     580,   581,   582,   617,   554,   105,   106,   510,    60,   112,
     113,    46,   131,   236,   237,   125,   126,   238,   364,   353,
     122,   227,   123,   108,   215,   119,   361,   462,   109,   239,
     163,   514,   365,   366,    47,    48,   207,   354,    49,   165,
     166,    74,   587,   622,   631,   636,   637,   638,   644,   658,
     661
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -454
static const yytype_int16 yypact[] =
{
    2751,   -54,  -454,  -454,  -454,  -454,  -454,  -454,  -454,  -454,
    -454,    61,    98,  3157,   106,  -454,  -454,  -454,  -454,  -454,
    3157,  3157,  -454,  -454,  3157,  3157,  3157,  -454,  2751,     2,
    3157,    29,   117,   126,  -454,  2862,   -27,   128,   141,    39,
      33,  -454,    90,  2751,  -454,   -38,  3157,  -454,    17,  3157,
     214,  3026,  -454,  -454,   226,   162,   164,  2789,   176,  -454,
    -454,  2789,   218,  -454,  -454,  -454,  -454,  -454,  -454,   126,
    -454,    15,  2116,  1862,  -454,   -47,  -454,  -454,  -454,  2412,
    2484,  2502,  2502,  2502,  2502,  2502,  2502,  2862,   219,  -454,
    -454,  -454,  -454,    15,  -454,  3845,  2966,  2502,   299,  -454,
    -454,   228,  -454,   197,  -454,   230,   225,    24,  -454,  -454,
     104,  -454,  -454,  -454,  -454,  -454,  -454,  -454,   231,   241,
    3026,   111,   244,   245,   294,   253,  -454,   334,   226,   260,
     154,   266,  2789,   276,  2789,   280,   281,  -454,  -454,  -454,
    -454,  -454,  2574,  2646,  2502,  2502,  2502,  2502,  2502,  2502,
     353,  2502,  2502,   954,   283,   285,  -454,  3324,  -454,  -454,
     121,  -454,    11,   288,    55,  2672,   292,  1937,   363,  -454,
     954,   960,   954,   960,  1600,  1600,   960,   960,   960,   960,
    3820,   364,  -454,    91,    91,  2862,  2862,  2862,  2862,  2862,
    2862,  2862,  2862,  2502,  2862,  2862,  2862,  2862,  2862,  2862,
    2862,  2862,  2862,   297,  3370,   302,  -454,   317,   197,  -454,
     317,  2264,   197,  -454,   505,  -454,   304,   278,   214,  3157,
     310,  -454,   108,   204,  -454,  -454,  2997,  -454,  2502,   207,
     306,   311,   253,  2789,  2502,  2789,   307,   296,   309,   104,
    -454,   315,  -454,   320,  -454,   316,   954,   275,   954,   275,
    1193,  1193,   275,   275,   275,   275,  -454,   275,   275,   157,
    3416,   313,   325,   326,  2502,   398,  2502,  2502,  2502,  2502,
    2502,  2502,  2502,  2502,  2502,  2502,  2502,    91,    91,  2502,
    2502,  2502,  2502,  2502,  2502,  2502,  2502,  2502,  2502,  2502,
    2502,  2502,  2502,  2502,  2502,  2502,  2502,  -454,  -454,  -454,
    1147,  1628,  1221,  -454,  -454,  -454,   329,  -454,  -454,  -454,
    2012,  2012,  -454,  -454,  -454,   332,   335,  -454,  -454,  -454,
    -454,  1469,  1469,  1785,  1785,  1785,  1785,   270,   270,   960,
     122,   122,  1385,   719,   832,   606,  3867,   445,   445,   407,
     410,  -454,  -454,  -454,  -454,   377,  2189,  3692,  -454,   317,
     214,   197,   345,  3026,  -454,   491,  -454,   417,   321,  -454,
      21,   347,  -454,   308,  1080,  1160,   348,  -454,   245,  3692,
    -454,  -454,  -454,  -454,   354,  -454,  3692,  -454,  2789,   -28,
    2502,  -454,  -454,  -454,   355,   357,  -454,  1700,  1700,  -454,
    -454,  2338,  3462,   367,  3692,  3692,  3692,  3692,  3692,  3692,
    3692,  3692,  3692,  3692,  3692,  -454,  -454,  2884,  2884,  1443,
    1443,  1443,  1443,  1193,  1193,   275,   275,   275,  2373,  3791,
    2299,  3762,  3144,  1521,  1521,   360,   369,  -454,     4,   366,
     356,  -454,   362,   365,  -454,  -454,   477,   477,   371,   373,
     374,    91,  2502,   376,  -454,  -454,   370,   384,   414,  2264,
     375,   393,  1293,    15,   399,  -454,   392,   394,   126,  3157,
    -454,   403,   418,  -454,   406,   317,  -454,  3026,  -454,  1311,
    -454,  -454,  -454,  -454,  3692,   477,   477,  -454,  -454,  2189,
     275,  3157,  -454,  -454,  -454,  -454,  2502,   317,  2751,  2502,
     -37,  3232,  -454,  -454,  2189,  -454,  2264,  -454,  -454,  3157,
     120,  -454,   421,   428,  -454,   417,   278,  -454,   615,  3157,
     -38,    21,  3128,  -454,   434,   435,   431,   437,   442,  3727,
     448,  3508,  -454,  -454,   -37,  2502,  -454,  -454,  -454,  -454,
    -454,   197,  -454,  -454,   360,   446,  -454,   444,   449,    27,
    1394,  -454,  2502,   451,  -454,  -454,  -454,   454,   277,  -454,
     457,  -454,  -454,   615,  -454,  -454,  -454,  -454,  -454,  -454,
    -454,  -454,  -454,  -454,  -454,  -454,  -454,  3554,  -454,    67,
     728,  -454,  -454,   458,  1700,  -454,   462,   454,  3278,  -454,
     454,   841,   470,  1718,   841,   277,   277,   471,  -454,   456,
    -454,  -454,  -454,   468,  -454,  -454,   466,  -454,  -454,  -454,
    2502,   841,   459,  1067,   157,   460,  -454,  -454,   546,  -454,
     841,  -454,   841,  3600,  -454,   454,   476,  -454,  1474,   841,
    -454,   546,   497,  -454,  -454,   501,  1474,   503,  -454,  -454,
      15,   511,  -454,   506,  1554,   514,   512,   504,  -454,   513,
    1554,   521,  1790,    15,  -454,    15,  -454,   523,   841,   525,
    3646,   526,  -454,   841,  -454,  -454,  -454,   546,  -454,  -454,
     519,  -454,   546,  -454
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -454,  -454,  -454,   -26,  -111,   510,    -4,   380,   -25,  -454,
     -35,  -431,  -454,  -454,   -52,  -196,  -454,  -446,  -454,  -454,
    -453,    78,  -454,  -454,  -290,  -107,   138,  -378,  -454,    44,
    -454,  -454,  -454,   100,    62,   119,   109,  -210,  -454,  -454,
    -454,  -454,  -454,  -454,     1,   443,  -454,    53,   467,  -454,
    -454,  -454,   -45,   289,  -454,   551,   425,   -33,   570,     8,
    -334,   324,  -114,  -454,  -454,  -192,  -316,   172,  -117,   -31,
    -103,   -87,  -454,  -454,  -454,  -454,   -74,   330,   -68,   372,
      12,   -64,  -301,    63,  -454,    45,  -454,    48,  -454,  -454,
      32
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -288
static const yytype_int16 yytable[] =
{
      92,    44,    68,   216,   222,   135,   220,    56,    58,    51,
      62,   169,   107,   441,   110,   348,   133,   102,   114,   454,
      50,   103,   460,    77,  -257,  -270,   359,   167,  -257,    44,
     573,   103,   168,   517,   224,   208,   136,   522,    92,    99,
     442,   182,   104,   100,    44,   222,   261,   157,   526,    96,
     263,   234,    92,    45,   171,   173,   174,   175,   176,   177,
     178,   179,   211,   261,    52,   261,    59,   315,    53,   316,
     103,   522,   204,    59,    59,   307,    69,    59,    59,    59,
     103,    45,   484,    59,  -260,   387,   574,   241,   221,   243,
     223,   101,   116,   115,    52,  -257,    45,    44,    53,   111,
    -270,    52,    59,    71,   121,    53,   213,    52,   305,    52,
     130,    53,   368,    53,   130,    89,    90,   247,   249,   250,
     251,   252,   253,   254,   255,   162,   257,   258,   309,    77,
     304,   306,    92,   515,   343,  -257,   310,    54,   349,   261,
     208,   261,   356,   384,   208,   385,   355,   592,   216,    45,
      92,    92,    92,    92,    92,    92,    92,    92,   451,    92,
      92,    92,    92,    92,    92,    92,    92,    92,   329,   584,
     103,   183,   184,   121,    57,    55,   342,   345,   212,   319,
     320,  -262,    61,   528,  -243,   130,   347,   130,   375,  -262,
     377,    72,  -243,   427,   429,   431,   558,   262,   529,   598,
      73,   387,   601,   369,    97,    55,   162,    52,   370,   376,
     124,    53,    55,   103,   262,    98,   262,   118,    55,   213,
      55,    89,    90,   162,    19,   162,   660,    22,    23,   124,
     386,   660,    27,   234,   235,   213,   127,   625,   387,   392,
     128,   394,   395,   396,   397,   398,   399,   400,   401,   402,
     403,   404,   132,   497,   407,   408,   409,   410,   411,   412,
     413,   414,   415,   416,   417,   418,   419,   420,   421,   422,
     423,   424,   360,   405,   406,    92,    92,   452,   363,   121,
     477,   478,   -21,   208,   606,   607,   130,   355,   130,   465,
     262,   468,   262,    29,   134,   208,   355,   208,   181,   162,
     527,   162,   205,    33,   585,    34,   210,   586,   206,   464,
     209,  -275,   218,   616,   219,  -275,   450,   225,    55,   183,
     184,   347,   434,   435,   277,   278,   226,   461,   627,   193,
     194,   195,   228,   472,   229,    19,   633,   231,    22,    23,
     233,   240,   443,    27,   641,   501,   297,   298,   222,   300,
     647,   242,   301,   244,   245,   474,   256,   264,   487,   265,
     594,   308,   501,   464,   208,   312,   480,  -275,   314,   318,
     222,   602,   339,   467,   605,   341,   103,   379,   518,   356,
     357,   372,  -275,   362,   373,  -275,   389,   378,   380,    19,
     381,   614,    22,    23,   507,   382,   383,    27,   390,   391,
     594,   393,   623,   432,    29,   436,   121,    95,   437,   628,
     438,   480,   480,   439,    33,   211,    34,   491,   503,   453,
     456,  -275,  -275,   569,   347,   469,   458,   463,   475,   471,
     476,   130,   450,   576,   223,   486,  -275,   490,   654,  -275,
     482,   387,   483,   659,   485,   493,   310,   488,   498,   489,
     480,   480,   495,   -17,   347,   492,   306,   568,    29,   180,
     509,   519,   520,   208,   521,   494,   499,   596,    33,   347,
      34,   347,   504,   505,   506,   443,   261,   345,   461,   513,
     137,   138,   139,   140,   511,    77,   141,    63,    64,    44,
     443,    65,    66,    67,   183,   184,   431,    70,   512,   530,
     567,   531,   191,   192,   193,   194,   195,   559,   560,   561,
     509,   431,   562,   142,   143,   563,   117,   578,    19,   431,
     121,    22,    23,   564,   571,   570,    27,   431,   583,   572,
     579,   609,    19,   431,   162,    22,    23,   588,   595,   147,
      27,    45,   597,   149,   603,   608,   611,   610,   151,   152,
     615,   153,   360,   479,   620,   619,   626,   321,   322,   323,
     324,   325,   326,   327,   328,   360,   330,   331,   332,   333,
     334,   335,   336,   337,   338,   613,   630,    89,    90,   350,
     154,   632,   351,   634,   639,   645,   640,    29,   642,   352,
     155,   643,   156,   646,   648,   635,   653,    33,   655,    34,
     662,    29,   566,   352,   618,   657,   203,   516,   635,   555,
     635,    33,   374,    34,   532,   590,   534,   650,   535,   138,
     139,   140,     2,    77,   141,   533,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,   142,   143,   344,   371,   183,   184,   185,   186,   187,
     188,   189,   190,   191,   192,   193,   194,   195,   473,   196,
     197,   198,   144,   145,   146,   201,   202,   147,   148,   232,
     214,   149,   150,   556,   629,   455,   151,   152,   651,   153,
    -133,   115,   470,   652,   663,   536,     0,     0,     0,   537,
     538,   539,   540,   541,   542,   543,   544,   545,   546,   547,
       0,    29,    30,   548,    32,    89,    90,     0,   154,     0,
       0,    33,   549,    34,     0,     0,     0,    38,   155,   534,
     156,   593,   138,   139,   140,     2,    77,   141,     0,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,   142,   143,     0,     0,   183,   184,
     185,   186,   187,   188,   189,   190,   191,   192,   193,   194,
     195,     0,   196,     0,   198,   144,   145,   146,   201,   202,
     147,   148,     0,     0,   149,   150,     0,     0,     0,   151,
     152,     0,   153,  -135,   115,     0,     0,     0,   536,     0,
       0,     0,   537,   538,   539,   540,   541,   542,   543,   544,
     545,   546,   547,     0,    29,    30,   548,    32,    89,    90,
       0,   154,     0,     0,    33,   549,    34,     0,     0,     0,
      38,   155,   534,   156,   593,   138,   139,   140,     2,    77,
     141,     0,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,   142,   143,     0,
       0,   183,   184,   185,   186,   187,   188,   189,   190,   191,
     192,   193,   194,   195,     0,   196,     0,     0,   144,   145,
     146,   201,   202,   147,   148,     0,     0,   149,   150,     0,
       0,     0,   151,   152,     0,   153,     0,   115,     0,     0,
       0,   536,     0,     0,     0,   537,   538,   539,   540,   541,
     542,   543,   544,   545,   546,   547,     0,    29,    30,   548,
      32,    89,    90,     0,   154,     0,     0,    33,   549,    34,
       0,     0,     0,    38,   155,   259,   156,   137,   138,   139,
     140,     2,    77,   141,     0,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
     142,   143,     0,     0,     0,     0,     0,     0,   266,   267,
     268,   269,   270,   271,   272,   273,   274,   275,   276,   277,
     278,   144,   145,   146,     0,     0,   147,   148,     0,     0,
     149,   150,     0,     0,     0,   151,   152,     0,   153,     0,
     115,   297,   298,     0,   300,     0,     0,   301,     0,     0,
       0,     0,     0,   302,     0,     0,     0,     0,     0,     0,
      29,    30,     0,    32,    89,    90,     0,   154,     0,     0,
      33,     0,    34,     0,     0,     0,    38,   155,   425,   156,
     137,   138,   139,   140,     2,    77,   141,     0,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,   142,   143,     0,     0,    19,     0,     0,
      22,    23,     0,     0,     0,    27,     0,     0,     0,     0,
       0,     0,     0,     0,   144,   145,   146,     0,     0,   147,
     148,     0,     0,   149,   150,     0,     0,     0,   151,   152,
       0,   153,     0,     0,     0,     0,     0,  -114,   425,     0,
     137,   138,   139,   140,   466,    77,   141,   351,     0,     0,
       0,     0,     0,    29,    30,     0,    32,    89,    90,     0,
     154,     0,     0,    33,     0,    34,    29,     0,   352,    38,
     155,     0,   156,   142,   143,     0,    33,    19,    34,     0,
      22,    23,     0,     0,     0,    27,     0,     0,     0,     0,
       0,     0,     0,     0,   144,   145,   146,     0,     0,   147,
     148,     0,     0,   149,   150,     0,     0,     0,   151,   152,
    -112,   153,   425,     0,   137,   138,   139,   140,     0,    77,
     141,     0,     0,     0,   466,     0,     0,  -267,     0,     0,
       0,     0,   277,   278,     0,     0,     0,    89,    90,     0,
     154,     0,   287,   288,   289,     0,    29,   142,   143,     0,
     155,     0,   156,     0,   297,   298,    33,   300,    34,     0,
     301,     0,     0,     0,     0,     0,     0,     0,   144,   145,
     146,     0,     0,   147,   148,     0,     0,   149,   150,     0,
       0,     0,   151,   152,   500,   153,   137,   138,   139,   140,
    -114,    77,   141,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   425,     0,   137,   138,   139,   140,     0,    77,
     141,    89,    90,     0,   154,     0,     0,     0,     0,   142,
     143,     0,     0,     0,   155,     0,   156,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   142,   143,     0,
     144,   145,   146,     0,     0,   147,   148,     0,     0,   149,
     150,     0,     0,     0,   151,   152,     0,   153,   144,   145,
     146,  -119,     0,   147,   148,     0,     0,   149,   150,     0,
       0,     0,   151,   152,     0,   153,     0,     0,     0,  -119,
       0,     0,     0,    89,    90,   425,   154,   137,   138,   139,
     140,     0,    77,   141,     0,     0,   155,     0,   156,     0,
       0,    89,    90,     0,   154,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   155,     0,   156,     0,     0,     0,
     142,   143,     0,     0,   183,   184,   185,   186,   187,   188,
     189,   190,   191,   192,   193,   194,   195,     0,     0,     0,
       0,   144,   145,   146,   201,   202,   147,   148,     0,     0,
     149,   150,     0,     0,     0,   151,   152,     0,   153,     0,
       0,     0,     0,     0,   575,   425,     0,   137,   138,   139,
     140,     0,    77,   141,     0,     0,     0,     0,     0,     0,
       0,     0,   277,   278,    89,    90,     0,   154,     0,     0,
     285,   286,   287,   288,   289,     0,     0,   155,     0,   156,
     142,   143,   295,   296,   297,   298,     0,   300,   183,   184,
     301,     0,   187,   188,   189,   190,   191,   192,   193,   194,
     195,   144,   145,   146,     0,     0,   147,   148,   201,   202,
     149,   150,     0,     0,     0,   151,   152,     0,   153,     0,
       0,     0,     0,     0,  -114,   425,     0,   137,   138,   139,
     140,     0,    77,   141,     0,     0,     0,     0,     0,     0,
     277,   278,     0,     0,    89,    90,     0,   154,   285,   286,
     287,   288,   289,     0,     0,     0,     0,   155,     0,   156,
     142,   143,   297,   298,     0,   300,     0,     0,   301,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   144,   145,   146,     0,     0,   147,   148,     0,     0,
     149,   150,     0,     0,     0,   151,   152,  -114,   153,   428,
       0,   137,   138,   139,   140,     0,    77,   141,   266,   267,
     268,   269,   270,   271,   272,   273,   274,   275,   276,   277,
     278,     0,     0,     0,    89,    90,     0,   154,     0,   287,
     288,   289,     0,     0,   142,   143,     0,   155,     0,   156,
       0,   297,   298,     0,   300,     0,     0,   301,     0,     0,
       0,     0,     0,   302,     0,   144,   145,   146,     0,     0,
     147,   148,     0,     0,   149,   150,     0,     0,     0,   151,
     152,   425,   153,   137,   138,   139,   140,     0,    77,   141,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   604,
       0,   137,   138,   139,   140,     0,    77,   141,    89,    90,
       0,   154,     0,     0,     0,     0,   142,   143,     0,     0,
       0,   155,     0,   156,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   142,   143,     0,   144,   145,   146,
       0,     0,   147,   148,     0,     0,   149,   150,     0,     0,
       0,   151,   152,     0,   153,   144,   145,   146,     0,     0,
     147,   148,     0,     0,   149,   150,     0,     0,     0,   151,
     152,   649,   153,   137,   138,   139,   140,     0,    77,   141,
      89,    90,     0,   154,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   155,     0,   156,     0,     0,    89,    90,
       0,   154,     0,     0,     0,     0,   142,   143,     0,     0,
       0,   155,     0,   156,   183,   184,     0,     0,     0,     0,
       0,     0,   191,   192,   193,   194,   195,   144,   145,   146,
       0,     0,   147,   148,   201,   202,   149,   150,     0,     0,
       0,   151,   152,   164,   153,    75,     0,    76,     0,    53,
      77,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      89,    90,    78,   154,     0,     0,     0,     0,    79,    80,
       0,     0,     0,   155,     0,   156,     0,     0,     0,     0,
       0,  -287,  -287,  -287,  -287,  -287,  -287,  -287,  -287,    81,
      82,    83,  -287,  -287,    84,    85,  -287,  -287,    86,  -287,
    -287,  -287,  -287,     0,     0,  -287,    87,     0,   164,     0,
      75,     0,    76,  -287,    53,    77,     0,     0,     0,     0,
       0,     0,    88,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    89,    90,     0,     0,     0,    78,     0,     0,
       0,     0,     0,    79,    80,     0,    55,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  -287,  -287,  -287,  -287,
    -287,  -287,  -287,  -287,    81,    82,    83,  -287,  -287,    84,
      85,  -287,  -287,    86,  -287,  -287,  -287,  -287,     0,     0,
     313,    87,     0,   433,     0,    75,     0,    76,  -287,    53,
      77,     0,     0,     0,     0,     0,     0,    88,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    89,    90,     0,
       0,     0,    78,     0,     0,     0,     0,     0,    79,    80,
       0,    55,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  -287,  -287,  -287,  -287,  -287,  -287,  -287,  -287,    81,
      82,    83,  -287,  -287,    84,    85,  -287,  -287,    86,  -287,
    -287,  -287,  -287,     0,     0,  -287,    87,     0,     0,     0,
       0,     0,     0,  -287,     0,     0,     0,     0,     0,     0,
       0,     0,    88,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    89,    90,     0,     0,     0,     0,     0,   137,
     138,   139,   140,     2,    77,   141,    55,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,   142,   143,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   144,   145,   146,     0,     0,   147,   148,
       0,     0,   149,   150,     0,     0,     0,   151,   152,     0,
     153,     0,   440,   138,   139,   140,    53,    77,   141,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    29,    30,     0,    32,    89,    90,     0,   154,
       0,     0,    33,     0,    34,   142,   143,     0,    38,   155,
       0,   156,     0,     0,     0,     0,     0,     0,     0,   441,
       0,     0,     0,     0,     0,     0,   144,   145,   146,     0,
       0,   147,   148,     0,     0,   149,   150,     0,     0,     0,
     151,   152,     0,   153,     0,   346,   442,   137,   138,   139,
     140,     0,    77,   141,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    89,
      90,     0,   154,     0,     0,     0,     0,     0,     0,     0,
     142,   143,   155,    55,   156,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   144,   145,   146,     0,     0,   147,   148,     0,     0,
     149,   150,     0,     0,     0,   151,   152,     0,   153,     0,
     346,   137,   138,   139,   140,     0,    77,   141,   277,   278,
     279,   280,   281,   282,   283,   284,   285,   286,   287,   288,
     289,     0,   290,     0,    89,    90,     0,   154,   295,   296,
     297,   298,     0,   300,   142,   143,   301,   155,     0,   156,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   144,   145,   146,     0,     0,
     147,   148,     0,     0,   149,   150,     0,     0,     0,   151,
     152,     0,   153,     0,   479,   137,   138,   139,   140,     0,
      77,   141,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,     0,     0,     0,    89,    90,
       0,   154,   295,   296,   297,   298,     0,   300,   142,   143,
     301,   155,     0,   156,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   144,
     145,   146,     0,     0,   147,   148,     0,     0,   149,   150,
       0,     0,     0,   151,   152,     0,   170,   137,   138,   139,
     140,     0,    77,   141,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   137,   138,   139,   140,     0,
      77,   141,    89,    90,     0,   154,     0,     0,     0,     0,
     142,   143,     0,     0,     0,   155,     0,   156,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   142,   143,
       0,   144,   145,   146,     0,     0,   147,   148,     0,     0,
     149,   150,     0,     0,     0,   151,   152,     0,   172,   144,
     145,   146,     0,     0,   147,   148,     0,     0,   149,   150,
       0,     0,     0,   151,   152,     0,   153,   137,   138,   139,
     140,     0,    77,   141,    89,    90,     0,   154,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   155,     0,   156,
       0,     0,    89,    90,     0,   154,     0,     0,     0,     0,
     142,   143,     0,     0,     0,   155,     0,   156,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   144,   145,   146,     0,     0,   147,   148,     0,     0,
     149,   150,     0,     0,     0,   151,   152,     0,   246,   137,
     138,   139,   140,     0,    77,   141,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    89,    90,     0,   154,     0,     0,
       0,     0,   142,   143,     0,     0,     0,   155,     0,   156,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   144,   145,   146,     0,     0,   147,   148,
       0,     0,   149,   150,     0,     0,     0,   151,   152,     0,
     248,   183,   184,   185,   186,   187,   188,   189,   190,   191,
     192,   193,   194,   195,     0,   196,   197,   198,     0,   199,
     200,   201,   202,     0,     0,     0,    89,    90,     0,   154,
       0,     0,    -7,   311,     1,     0,     0,     0,     2,   155,
       0,   156,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,     0,     0,     0,
     129,     0,     0,     0,     0,     0,     2,     0,     0,     0,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,     0,     0,     0,     0,     0,
       0,    28,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    29,    30,    31,
      32,     0,     0,     0,     0,     0,     0,    33,     0,    34,
      35,    36,    37,    38,  -215,    75,     0,    76,     0,    53,
      77,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    29,    30,     0,    32,     0,
       0,     0,    78,     0,     0,    33,     0,    34,    79,    80,
       0,    38,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    81,
      82,    83,     0,     0,    84,    85,     0,     0,    86,     0,
       0,     0,     0,   277,   278,     0,    87,   281,   282,   283,
     284,   285,   286,   287,   288,   289,     0,     0,     0,     0,
       0,     0,    88,   295,   296,   297,   298,     0,   300,     0,
       0,   301,    89,    90,     0,     0,     0,     0,     0,     1,
       0,     0,     0,     2,     0,     0,    55,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,     0,     0,     2,     0,     0,     0,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,     2,     0,     0,     0,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    29,    30,    31,    32,     0,     0,     0,     0,
       0,   120,    33,     0,    34,    35,    36,    37,    38,   367,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    29,    30,     0,    32,     0,     0,     0,
     120,     0,     0,    33,     0,    34,     0,     0,     0,    38,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    29,    30,     0,    32,     0,     0,     0,     0,
       0,     0,    33,     0,    34,     2,     0,     0,    38,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,     2,     0,     0,     0,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,   277,   278,   279,   280,   281,   282,   283,
     284,   285,   286,   287,   288,   289,     0,   290,   291,   292,
     557,   293,     0,   295,   296,   297,   298,     0,   300,     0,
       0,   301,     0,     0,    29,    30,     0,    32,     0,     0,
       0,     0,     0,     0,    33,     0,    34,     0,     0,     0,
      38,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    29,    30,     0,    32,     0,     0,     0,
       0,     0,     0,    33,     0,    34,     0,     0,     0,    38,
     266,   267,   268,   269,   270,   271,   272,   273,   274,   275,
     276,   277,   278,   279,   280,   281,   282,   283,   284,   285,
     286,   287,   288,   289,     0,   290,   291,   292,     0,   293,
     294,   295,   296,   297,   298,     0,   300,     0,     0,   301,
     524,     0,     0,     0,   525,   302,   266,   267,   268,   269,
     270,   271,   272,   273,   274,   275,   276,   277,   278,   279,
     280,   281,   282,   283,   284,   285,   286,   287,   288,   289,
       0,   290,   291,   292,     0,   293,   294,   295,   296,   297,
     298,     0,   300,     0,     0,   301,     0,   599,     0,     0,
     600,   302,   266,   267,   268,   269,   270,   271,   272,   273,
     274,   275,   276,   277,   278,   279,   280,   281,   282,   283,
     284,   285,   286,   287,   288,   289,     0,   290,   291,   292,
       0,   293,   294,   295,   296,   297,   298,   299,   300,     0,
       0,   301,     0,     0,     0,     0,     0,   302,   266,   267,
     268,   269,   270,   271,   272,   273,   274,   275,   276,   277,
     278,   279,   280,   281,   282,   283,   284,   285,   286,   287,
     288,   289,     0,   290,   291,   292,     0,   293,   294,   295,
     296,   297,   298,     0,   300,   340,     0,   301,     0,     0,
       0,     0,     0,   302,   266,   267,   268,   269,   270,   271,
     272,   273,   274,   275,   276,   277,   278,   279,   280,   281,
     282,   283,   284,   285,   286,   287,   288,   289,     0,   290,
     291,   292,     0,   293,   294,   295,   296,   297,   298,     0,
     300,     0,     0,   301,     0,     0,     0,   388,     0,   302,
     266,   267,   268,   269,   270,   271,   272,   273,   274,   275,
     276,   277,   278,   279,   280,   281,   282,   283,   284,   285,
     286,   287,   288,   289,     0,   290,   291,   292,     0,   293,
     294,   295,   296,   297,   298,     0,   300,     0,     0,   301,
       0,     0,     0,   481,     0,   302,   266,   267,   268,   269,
     270,   271,   272,   273,   274,   275,   276,   277,   278,   279,
     280,   281,   282,   283,   284,   285,   286,   287,   288,   289,
       0,   290,   291,   292,     0,   293,   294,   295,   296,   297,
     298,     0,   300,   565,     0,   301,     0,     0,     0,     0,
       0,   302,   266,   267,   268,   269,   270,   271,   272,   273,
     274,   275,   276,   277,   278,   279,   280,   281,   282,   283,
     284,   285,   286,   287,   288,   289,     0,   290,   291,   292,
       0,   293,   294,   295,   296,   297,   298,     0,   300,     0,
       0,   301,   591,     0,     0,     0,     0,   302,   266,   267,
     268,   269,   270,   271,   272,   273,   274,   275,   276,   277,
     278,   279,   280,   281,   282,   283,   284,   285,   286,   287,
     288,   289,     0,   290,   291,   292,     0,   293,   294,   295,
     296,   297,   298,     0,   300,     0,     0,   301,     0,   624,
       0,     0,     0,   302,   266,   267,   268,   269,   270,   271,
     272,   273,   274,   275,   276,   277,   278,   279,   280,   281,
     282,   283,   284,   285,   286,   287,   288,   289,     0,   290,
     291,   292,     0,   293,   294,   295,   296,   297,   298,   656,
     300,     0,     0,   301,     0,     0,     0,     0,     0,   302,
     266,   267,   268,   269,   270,   271,   272,   273,   274,   275,
     276,   277,   278,   279,   280,   281,   282,   283,   284,   285,
     286,   287,   288,   289,     0,   290,   291,   292,     0,   293,
     294,   295,   296,   297,   298,     0,   300,     0,     0,   301,
       0,     0,     0,     0,     0,   302,   277,   278,   279,   280,
     281,   282,   283,   284,   285,   286,   287,   288,   289,     0,
     290,   291,   292,     0,   293,   294,   295,   296,   297,   298,
       0,   300,     0,     0,   301,     0,     0,     0,     0,     0,
     302,   277,   278,   279,   280,   281,   282,   283,   284,   285,
     286,   287,   288,   289,     0,   290,   291,   292,     0,     0,
       0,   295,   296,   297,   298,     0,   300,     0,     0,   301,
     277,   278,   279,   280,   281,   282,   283,   284,   285,   286,
     287,   288,   289,     0,   290,     0,   292,     0,     0,     0,
     295,   296,   297,   298,     0,   300,     0,     0,   301,   183,
     184,   185,   186,   187,   188,   189,   190,   191,   192,   193,
     194,   195,     0,   196,   197,   198,     0,   199,   200,   201,
     202,     0,     0,   317,   183,   184,   185,   186,   187,   188,
     189,   190,   191,   192,   193,   194,   195,     0,   196,   197,
     198,     0,   199,   200,   201,   202,   183,   184,   185,   186,
     187,   188,   189,   190,   191,   192,   193,   194,   195,     0,
     196,   197,   198,     0,   199,     0,   201,   202
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-454))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
      35,     0,    28,   114,   121,    69,   120,    11,    12,     1,
      14,    75,    45,    50,    45,   211,    61,    43,     1,   353,
      74,    59,     1,     8,     3,     1,   218,    74,     7,    28,
       3,    59,    79,   479,   121,   103,    71,   490,    73,     0,
      77,    93,    80,    10,    43,   162,   153,    72,   494,    76,
     153,    79,    87,     0,    79,    80,    81,    82,    83,    84,
      85,    86,    38,   170,     3,   172,    13,   170,     7,   172,
      59,   524,    97,    20,    21,   162,    74,    24,    25,    26,
      59,    28,    78,    30,    73,    81,    59,   132,   121,   134,
     121,     1,    48,    76,     3,    74,    43,    96,     7,    46,
      76,     3,    49,    74,    51,     7,   110,     3,   160,     3,
      57,     7,   226,     7,    61,   100,   101,   142,   143,   144,
     145,   146,   147,   148,   149,    72,   151,   152,    73,     8,
       9,   162,   167,   467,   208,   114,    81,    76,   212,   246,
     208,   248,    75,   246,   212,   248,   214,    80,   259,    96,
     185,   186,   187,   188,   189,   190,   191,   192,   350,   194,
     195,   196,   197,   198,   199,   200,   201,   202,   193,   547,
      59,    49,    50,   120,    76,   114,   207,   210,    74,   183,
     184,    73,    76,   499,    73,   132,   211,   134,   233,    81,
     235,    74,    81,   300,   301,   302,   512,   153,    78,   577,
      74,    81,   580,   228,    76,   114,   153,     3,     1,   234,
       3,     7,   114,    59,   170,    74,   172,     3,   114,   223,
     114,   100,   101,   170,    27,   172,   657,    30,    31,     3,
      73,   662,    35,    79,    80,   239,    74,   615,    81,   264,
      76,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,    76,   449,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   219,   277,   278,   310,   311,   351,    74,   226,
     387,   388,    75,   351,   585,   586,   233,   355,   235,   363,
     246,   365,   248,    96,    76,   363,   364,   365,    79,   246,
     496,   248,     3,   106,    27,   108,    81,    30,    80,     1,
      80,     3,    81,   603,    73,     7,   349,    73,   114,    49,
      50,   346,   310,   311,    49,    50,    81,   360,   618,    59,
      60,    61,    38,   378,    81,    27,   626,     3,    30,    31,
      80,    75,   346,    35,   634,   452,    71,    72,   465,    74,
     640,    75,    77,    73,    73,   380,     3,    74,   432,    74,
     570,    73,   469,     1,   432,    73,   391,    59,     5,     5,
     487,   581,    75,   365,   584,    73,    59,    81,   481,    75,
     102,    75,    74,    73,    73,    77,    73,    80,    79,    27,
      75,   601,    30,    31,   458,    75,    80,    35,    73,    73,
     610,     3,   612,    74,    96,    73,   353,    35,    73,   619,
       3,   436,   437,     3,   106,    38,   108,   442,   453,    74,
       3,    59,   114,   534,   449,    77,   105,    80,    73,    75,
      73,   378,   465,   540,   465,    79,    74,   441,   648,    77,
      73,    81,    73,   653,    78,    75,    81,    76,    73,    76,
     475,   476,    38,    79,   479,    79,   487,   531,    96,    87,
     459,   486,   488,   531,   489,    81,    73,   574,   106,   494,
     108,   496,    73,    81,    80,   479,   583,   510,   511,    73,
       3,     4,     5,     6,    81,     8,     9,    20,    21,   488,
     494,    24,    25,    26,    49,    50,   603,    30,    80,    78,
     525,    73,    57,    58,    59,    60,    61,    73,    73,    78,
     509,   618,    75,    36,    37,    73,    49,   542,    27,   626,
     467,    30,    31,    75,    80,    79,    35,   634,    74,    80,
      79,    75,    27,   640,   481,    30,    31,    80,    80,    62,
      35,   488,    80,    66,    74,    74,    80,    79,    71,    72,
      91,    74,   499,    76,     8,    95,    80,   185,   186,   187,
     188,   189,   190,   191,   192,   512,   194,   195,   196,   197,
     198,   199,   200,   201,   202,   600,    79,   100,   101,    74,
     103,    80,    77,    80,    73,    81,    80,    96,    74,    98,
     113,    79,   115,    80,    73,   630,    73,   106,    73,   108,
      81,    96,   524,    98,   603,    79,    96,   469,   643,   509,
     645,   106,   232,   108,   505,   553,     1,   642,     3,     4,
       5,     6,     7,     8,     9,   506,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,   210,   229,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,   379,    63,
      64,    65,    57,    58,    59,    69,    70,    62,    63,   128,
     110,    66,    67,   511,   621,   355,    71,    72,   643,    74,
      75,    76,   368,   645,   662,    80,    -1,    -1,    -1,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      -1,    96,    97,    98,    99,   100,   101,    -1,   103,    -1,
      -1,   106,   107,   108,    -1,    -1,    -1,   112,   113,     1,
     115,     3,     4,     5,     6,     7,     8,     9,    -1,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    -1,    -1,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    -1,    63,    -1,    65,    57,    58,    59,    69,    70,
      62,    63,    -1,    -1,    66,    67,    -1,    -1,    -1,    71,
      72,    -1,    74,    75,    76,    -1,    -1,    -1,    80,    -1,
      -1,    -1,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    -1,    96,    97,    98,    99,   100,   101,
      -1,   103,    -1,    -1,   106,   107,   108,    -1,    -1,    -1,
     112,   113,     1,   115,     3,     4,     5,     6,     7,     8,
       9,    -1,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    -1,
      -1,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    -1,    63,    -1,    -1,    57,    58,
      59,    69,    70,    62,    63,    -1,    -1,    66,    67,    -1,
      -1,    -1,    71,    72,    -1,    74,    -1,    76,    -1,    -1,
      -1,    80,    -1,    -1,    -1,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    -1,    96,    97,    98,
      99,   100,   101,    -1,   103,    -1,    -1,   106,   107,   108,
      -1,    -1,    -1,   112,   113,     1,   115,     3,     4,     5,
       6,     7,     8,     9,    -1,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    -1,    -1,    -1,    -1,    -1,    -1,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    57,    58,    59,    -1,    -1,    62,    63,    -1,    -1,
      66,    67,    -1,    -1,    -1,    71,    72,    -1,    74,    -1,
      76,    71,    72,    -1,    74,    -1,    -1,    77,    -1,    -1,
      -1,    -1,    -1,    83,    -1,    -1,    -1,    -1,    -1,    -1,
      96,    97,    -1,    99,   100,   101,    -1,   103,    -1,    -1,
     106,    -1,   108,    -1,    -1,    -1,   112,   113,     1,   115,
       3,     4,     5,     6,     7,     8,     9,    -1,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    -1,    -1,    27,    -1,    -1,
      30,    31,    -1,    -1,    -1,    35,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    57,    58,    59,    -1,    -1,    62,
      63,    -1,    -1,    66,    67,    -1,    -1,    -1,    71,    72,
      -1,    74,    -1,    -1,    -1,    -1,    -1,    80,     1,    -1,
       3,     4,     5,     6,    74,     8,     9,    77,    -1,    -1,
      -1,    -1,    -1,    96,    97,    -1,    99,   100,   101,    -1,
     103,    -1,    -1,   106,    -1,   108,    96,    -1,    98,   112,
     113,    -1,   115,    36,    37,    -1,   106,    27,   108,    -1,
      30,    31,    -1,    -1,    -1,    35,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    57,    58,    59,    -1,    -1,    62,
      63,    -1,    -1,    66,    67,    -1,    -1,    -1,    71,    72,
      73,    74,     1,    -1,     3,     4,     5,     6,    -1,     8,
       9,    -1,    -1,    -1,    74,    -1,    -1,    77,    -1,    -1,
      -1,    -1,    49,    50,    -1,    -1,    -1,   100,   101,    -1,
     103,    -1,    59,    60,    61,    -1,    96,    36,    37,    -1,
     113,    -1,   115,    -1,    71,    72,   106,    74,   108,    -1,
      77,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    57,    58,
      59,    -1,    -1,    62,    63,    -1,    -1,    66,    67,    -1,
      -1,    -1,    71,    72,     1,    74,     3,     4,     5,     6,
      79,     8,     9,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     1,    -1,     3,     4,     5,     6,    -1,     8,
       9,   100,   101,    -1,   103,    -1,    -1,    -1,    -1,    36,
      37,    -1,    -1,    -1,   113,    -1,   115,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,    37,    -1,
      57,    58,    59,    -1,    -1,    62,    63,    -1,    -1,    66,
      67,    -1,    -1,    -1,    71,    72,    -1,    74,    57,    58,
      59,    78,    -1,    62,    63,    -1,    -1,    66,    67,    -1,
      -1,    -1,    71,    72,    -1,    74,    -1,    -1,    -1,    78,
      -1,    -1,    -1,   100,   101,     1,   103,     3,     4,     5,
       6,    -1,     8,     9,    -1,    -1,   113,    -1,   115,    -1,
      -1,   100,   101,    -1,   103,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   113,    -1,   115,    -1,    -1,    -1,
      36,    37,    -1,    -1,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    -1,    -1,    -1,
      -1,    57,    58,    59,    69,    70,    62,    63,    -1,    -1,
      66,    67,    -1,    -1,    -1,    71,    72,    -1,    74,    -1,
      -1,    -1,    -1,    -1,    80,     1,    -1,     3,     4,     5,
       6,    -1,     8,     9,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    49,    50,   100,   101,    -1,   103,    -1,    -1,
      57,    58,    59,    60,    61,    -1,    -1,   113,    -1,   115,
      36,    37,    69,    70,    71,    72,    -1,    74,    49,    50,
      77,    -1,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    57,    58,    59,    -1,    -1,    62,    63,    69,    70,
      66,    67,    -1,    -1,    -1,    71,    72,    -1,    74,    -1,
      -1,    -1,    -1,    -1,    80,     1,    -1,     3,     4,     5,
       6,    -1,     8,     9,    -1,    -1,    -1,    -1,    -1,    -1,
      49,    50,    -1,    -1,   100,   101,    -1,   103,    57,    58,
      59,    60,    61,    -1,    -1,    -1,    -1,   113,    -1,   115,
      36,    37,    71,    72,    -1,    74,    -1,    -1,    77,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    57,    58,    59,    -1,    -1,    62,    63,    -1,    -1,
      66,    67,    -1,    -1,    -1,    71,    72,    73,    74,     1,
      -1,     3,     4,     5,     6,    -1,     8,     9,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    -1,    -1,    -1,   100,   101,    -1,   103,    -1,    59,
      60,    61,    -1,    -1,    36,    37,    -1,   113,    -1,   115,
      -1,    71,    72,    -1,    74,    -1,    -1,    77,    -1,    -1,
      -1,    -1,    -1,    83,    -1,    57,    58,    59,    -1,    -1,
      62,    63,    -1,    -1,    66,    67,    -1,    -1,    -1,    71,
      72,     1,    74,     3,     4,     5,     6,    -1,     8,     9,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     1,
      -1,     3,     4,     5,     6,    -1,     8,     9,   100,   101,
      -1,   103,    -1,    -1,    -1,    -1,    36,    37,    -1,    -1,
      -1,   113,    -1,   115,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    36,    37,    -1,    57,    58,    59,
      -1,    -1,    62,    63,    -1,    -1,    66,    67,    -1,    -1,
      -1,    71,    72,    -1,    74,    57,    58,    59,    -1,    -1,
      62,    63,    -1,    -1,    66,    67,    -1,    -1,    -1,    71,
      72,     1,    74,     3,     4,     5,     6,    -1,     8,     9,
     100,   101,    -1,   103,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   113,    -1,   115,    -1,    -1,   100,   101,
      -1,   103,    -1,    -1,    -1,    -1,    36,    37,    -1,    -1,
      -1,   113,    -1,   115,    49,    50,    -1,    -1,    -1,    -1,
      -1,    -1,    57,    58,    59,    60,    61,    57,    58,    59,
      -1,    -1,    62,    63,    69,    70,    66,    67,    -1,    -1,
      -1,    71,    72,     1,    74,     3,    -1,     5,    -1,     7,
       8,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     100,   101,    30,   103,    -1,    -1,    -1,    -1,    36,    37,
      -1,    -1,    -1,   113,    -1,   115,    -1,    -1,    -1,    -1,
      -1,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    -1,    -1,    73,    74,    -1,     1,    -1,
       3,    -1,     5,    81,     7,     8,    -1,    -1,    -1,    -1,
      -1,    -1,    90,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   100,   101,    -1,    -1,    -1,    30,    -1,    -1,
      -1,    -1,    -1,    36,    37,    -1,   114,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    -1,    -1,
      73,    74,    -1,     1,    -1,     3,    -1,     5,    81,     7,
       8,    -1,    -1,    -1,    -1,    -1,    -1,    90,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   100,   101,    -1,
      -1,    -1,    30,    -1,    -1,    -1,    -1,    -1,    36,    37,
      -1,   114,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    -1,    -1,    73,    74,    -1,    -1,    -1,
      -1,    -1,    -1,    81,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    90,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   100,   101,    -1,    -1,    -1,    -1,    -1,     3,
       4,     5,     6,     7,     8,     9,   114,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    57,    58,    59,    -1,    -1,    62,    63,
      -1,    -1,    66,    67,    -1,    -1,    -1,    71,    72,    -1,
      74,    -1,     3,     4,     5,     6,     7,     8,     9,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    96,    97,    -1,    99,   100,   101,    -1,   103,
      -1,    -1,   106,    -1,   108,    36,    37,    -1,   112,   113,
      -1,   115,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    50,
      -1,    -1,    -1,    -1,    -1,    -1,    57,    58,    59,    -1,
      -1,    62,    63,    -1,    -1,    66,    67,    -1,    -1,    -1,
      71,    72,    -1,    74,    -1,    76,    77,     3,     4,     5,
       6,    -1,     8,     9,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   100,
     101,    -1,   103,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      36,    37,   113,   114,   115,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    57,    58,    59,    -1,    -1,    62,    63,    -1,    -1,
      66,    67,    -1,    -1,    -1,    71,    72,    -1,    74,    -1,
      76,     3,     4,     5,     6,    -1,     8,     9,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    -1,    63,    -1,   100,   101,    -1,   103,    69,    70,
      71,    72,    -1,    74,    36,    37,    77,   113,    -1,   115,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    57,    58,    59,    -1,    -1,
      62,    63,    -1,    -1,    66,    67,    -1,    -1,    -1,    71,
      72,    -1,    74,    -1,    76,     3,     4,     5,     6,    -1,
       8,     9,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    -1,    -1,    -1,   100,   101,
      -1,   103,    69,    70,    71,    72,    -1,    74,    36,    37,
      77,   113,    -1,   115,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    57,
      58,    59,    -1,    -1,    62,    63,    -1,    -1,    66,    67,
      -1,    -1,    -1,    71,    72,    -1,    74,     3,     4,     5,
       6,    -1,     8,     9,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     3,     4,     5,     6,    -1,
       8,     9,   100,   101,    -1,   103,    -1,    -1,    -1,    -1,
      36,    37,    -1,    -1,    -1,   113,    -1,   115,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,    37,
      -1,    57,    58,    59,    -1,    -1,    62,    63,    -1,    -1,
      66,    67,    -1,    -1,    -1,    71,    72,    -1,    74,    57,
      58,    59,    -1,    -1,    62,    63,    -1,    -1,    66,    67,
      -1,    -1,    -1,    71,    72,    -1,    74,     3,     4,     5,
       6,    -1,     8,     9,   100,   101,    -1,   103,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   113,    -1,   115,
      -1,    -1,   100,   101,    -1,   103,    -1,    -1,    -1,    -1,
      36,    37,    -1,    -1,    -1,   113,    -1,   115,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    57,    58,    59,    -1,    -1,    62,    63,    -1,    -1,
      66,    67,    -1,    -1,    -1,    71,    72,    -1,    74,     3,
       4,     5,     6,    -1,     8,     9,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   100,   101,    -1,   103,    -1,    -1,
      -1,    -1,    36,    37,    -1,    -1,    -1,   113,    -1,   115,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    57,    58,    59,    -1,    -1,    62,    63,
      -1,    -1,    66,    67,    -1,    -1,    -1,    71,    72,    -1,
      74,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    -1,    63,    64,    65,    -1,    67,
      68,    69,    70,    -1,    -1,    -1,   100,   101,    -1,   103,
      -1,    -1,     1,    81,     3,    -1,    -1,    -1,     7,   113,
      -1,   115,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    -1,    -1,    -1,
       1,    -1,    -1,    -1,    -1,    -1,     7,    -1,    -1,    -1,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    -1,    -1,    -1,    -1,    -1,
      -1,    80,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    96,    97,    98,
      99,    -1,    -1,    -1,    -1,    -1,    -1,   106,    -1,   108,
     109,   110,   111,   112,    75,     3,    -1,     5,    -1,     7,
       8,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    96,    97,    -1,    99,    -1,
      -1,    -1,    30,    -1,    -1,   106,    -1,   108,    36,    37,
      -1,   112,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    57,
      58,    59,    -1,    -1,    62,    63,    -1,    -1,    66,    -1,
      -1,    -1,    -1,    49,    50,    -1,    74,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    -1,    -1,    -1,    -1,
      -1,    -1,    90,    69,    70,    71,    72,    -1,    74,    -1,
      -1,    77,   100,   101,    -1,    -1,    -1,    -1,    -1,     3,
      -1,    -1,    -1,     7,    -1,    -1,   114,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    -1,    -1,     7,    -1,    -1,    -1,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,     7,    -1,    -1,    -1,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    96,    97,    98,    99,    -1,    -1,    -1,    -1,
      -1,    74,   106,    -1,   108,   109,   110,   111,   112,    82,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    96,    97,    -1,    99,    -1,    -1,    -1,
      74,    -1,    -1,   106,    -1,   108,    -1,    -1,    -1,   112,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    96,    97,    -1,    99,    -1,    -1,    -1,    -1,
      -1,    -1,   106,    -1,   108,     7,    -1,    -1,   112,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,     7,    -1,    -1,    -1,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    -1,    63,    64,    65,
      82,    67,    -1,    69,    70,    71,    72,    -1,    74,    -1,
      -1,    77,    -1,    -1,    96,    97,    -1,    99,    -1,    -1,
      -1,    -1,    -1,    -1,   106,    -1,   108,    -1,    -1,    -1,
     112,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    96,    97,    -1,    99,    -1,    -1,    -1,
      -1,    -1,    -1,   106,    -1,   108,    -1,    -1,    -1,   112,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    -1,    63,    64,    65,    -1,    67,
      68,    69,    70,    71,    72,    -1,    74,    -1,    -1,    77,
      78,    -1,    -1,    -1,    82,    83,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      -1,    63,    64,    65,    -1,    67,    68,    69,    70,    71,
      72,    -1,    74,    -1,    -1,    77,    -1,    79,    -1,    -1,
      82,    83,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    -1,    63,    64,    65,
      -1,    67,    68,    69,    70,    71,    72,    73,    74,    -1,
      -1,    77,    -1,    -1,    -1,    -1,    -1,    83,    38,    39,
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
      68,    69,    70,    71,    72,    -1,    74,    -1,    -1,    77,
      -1,    -1,    -1,    81,    -1,    83,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      -1,    63,    64,    65,    -1,    67,    68,    69,    70,    71,
      72,    -1,    74,    75,    -1,    77,    -1,    -1,    -1,    -1,
      -1,    83,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    -1,    63,    64,    65,
      -1,    67,    68,    69,    70,    71,    72,    -1,    74,    -1,
      -1,    77,    78,    -1,    -1,    -1,    -1,    83,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    -1,    63,    64,    65,    -1,    67,    68,    69,
      70,    71,    72,    -1,    74,    -1,    -1,    77,    -1,    79,
      -1,    -1,    -1,    83,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    -1,    63,
      64,    65,    -1,    67,    68,    69,    70,    71,    72,    73,
      74,    -1,    -1,    77,    -1,    -1,    -1,    -1,    -1,    83,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    -1,    63,    64,    65,    -1,    67,
      68,    69,    70,    71,    72,    -1,    74,    -1,    -1,    77,
      -1,    -1,    -1,    -1,    -1,    83,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    -1,
      63,    64,    65,    -1,    67,    68,    69,    70,    71,    72,
      -1,    74,    -1,    -1,    77,    -1,    -1,    -1,    -1,    -1,
      83,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    -1,    63,    64,    65,    -1,    -1,
      -1,    69,    70,    71,    72,    -1,    74,    -1,    -1,    77,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    -1,    63,    -1,    65,    -1,    -1,    -1,
      69,    70,    71,    72,    -1,    74,    -1,    -1,    77,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    -1,    63,    64,    65,    -1,    67,    68,    69,
      70,    -1,    -1,    73,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    -1,    63,    64,
      65,    -1,    67,    68,    69,    70,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    -1,
      63,    64,    65,    -1,    67,    -1,    69,    70
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     7,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    80,    96,
      97,    98,    99,   106,   108,   109,   110,   111,   112,   119,
     120,   121,   122,   123,   162,   165,   169,   192,   193,   196,
      74,   177,     3,     7,    76,   114,   124,    76,   124,   165,
     166,    76,   124,   166,   166,   166,   166,   166,   121,    74,
     166,    74,    74,    74,   199,     3,     5,     8,    30,    36,
      37,    57,    58,    59,    62,    63,    66,    74,    90,   100,
     101,   124,   128,   130,   132,   197,    76,    76,    74,     0,
      10,     1,   121,    59,    80,   163,   164,   175,   181,   186,
     187,   165,   167,   168,     1,    76,   147,   166,     3,   183,
      74,   165,   178,   180,     3,   173,   174,    74,    76,     1,
     165,   170,    76,   170,    76,   199,   128,     3,     4,     5,
       6,     9,    36,    37,    57,    58,    59,    62,    63,    66,
      67,    71,    72,    74,   103,   113,   115,   126,   127,   128,
     131,   145,   165,   188,     1,   197,   198,    74,    79,   199,
      74,   126,    74,   126,   126,   126,   126,   126,   126,   126,
     197,    79,   132,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    63,    64,    65,    67,
      68,    69,    70,   123,   126,     3,    80,   194,   196,    80,
      81,    38,    74,   124,   176,   182,   122,   148,    81,    73,
     180,   175,   186,   187,   189,    73,    81,   179,    38,    81,
     125,     3,   173,    80,    79,    80,   171,   172,   175,   187,
      75,   170,    75,   170,    73,    73,    74,   126,    74,   126,
     126,   126,   126,   126,   126,   126,     3,   126,   126,     1,
     126,   143,   147,   188,    74,    74,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      63,    64,    65,    67,    68,    69,    70,    71,    72,    73,
      74,    77,    83,   146,     9,   132,   187,   189,    73,    73,
      81,    81,    73,    73,     5,   188,   188,    73,     5,   124,
     124,   197,   197,   197,   197,   197,   197,   197,   197,   126,
     197,   197,   197,   197,   197,   197,   197,   197,   197,    75,
      75,    73,   187,   194,   163,   175,    76,   126,   133,   194,
      74,    77,    98,   177,   195,   196,    75,   102,   153,   183,
     165,   184,    73,    74,   176,   190,   191,    82,   180,   126,
       1,   174,    75,    73,   125,   170,   126,   170,    80,    81,
      79,    75,    75,    80,   188,   188,    73,    81,    81,    73,
      73,    73,   126,     3,   126,   126,   126,   126,   126,   126,
     126,   126,   126,   126,   126,   124,   124,   126,   126,   126,
     126,   126,   126,   126,   126,   126,   126,   126,   126,   126,
     126,   126,   126,   126,   126,     1,   141,   143,     1,   143,
     142,   143,    74,     1,   198,   198,    73,    73,     3,     3,
       3,    50,    77,   124,   133,   134,   135,   136,   138,   140,
     175,   183,   194,    74,   178,   195,     3,   154,   105,   150,
       1,   175,   185,    80,     1,   194,    74,   177,   194,    77,
     179,    75,   170,   171,   126,    73,    73,   143,   143,    76,
     126,    81,    73,    73,    78,    78,    79,   194,    76,    76,
     124,   126,    79,    75,    81,    38,   137,   133,    73,    73,
       1,   143,   144,   128,    73,    81,    80,   199,   151,   162,
     165,    81,    80,    73,   189,   178,   144,   135,   188,   126,
     121,   126,   138,   139,    78,    82,   135,   133,   184,    78,
      78,    73,   154,   153,     1,     3,    80,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    98,   107,
     143,   147,   152,   155,   162,   151,   185,    82,   184,    73,
      73,    78,    75,    73,    75,    75,   139,   126,   194,   122,
      79,    80,    80,     3,    59,    80,   143,   156,   126,    79,
     158,   159,   160,    74,   145,    27,    30,   200,    80,   149,
     152,    78,    80,     3,   155,    80,   143,    80,   145,    79,
      82,   145,   155,    74,     1,   155,   200,   200,    74,    75,
      79,    80,   157,   126,   155,    91,   142,   161,   162,    95,
       8,   129,   201,   155,    79,   145,    80,   142,   155,   201,
      79,   202,    80,   142,    80,   128,   203,   204,   205,    73,
      80,   142,    74,    79,   206,    81,    80,   142,    73,     1,
     126,   203,   205,    73,   155,    73,    73,    79,   207,   155,
     129,   208,    81,   208
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
#line 743 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    { YYACCEPT; }
    break;

  case 4:
/* Line 1787 of yacc.c  */
#line 747 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {}
    break;

  case 5:
/* Line 1787 of yacc.c  */
#line 748 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {}
    break;

  case 6:
/* Line 1787 of yacc.c  */
#line 749 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {}
    break;

  case 7:
/* Line 1787 of yacc.c  */
#line 753 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {}
    break;

  case 8:
/* Line 1787 of yacc.c  */
#line 759 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  pips_debug(5, "declaration->global\n");
			  csplit_is_external = 1; /* the variable is declared outside of any function */
			  /* csplit_is_typedef = 0; */
			  pips_debug(1, "Declaration is located between line %d and line %d\n", get_csplit_current_beginning(), csplit_line_number);
			  /* Useless since it is dealt by csplit_copy()
			     later */
			  //csplit_append_to_compilation_unit(csplit_line_number, get_current_csplit_file_offset());
			  if(!string_undefined_p((yyvsp[(1) - (1)].string))) {
			    pips_debug(1, "Definition: \"%s\"\n", (yyvsp[(1) - (1)].string));
			    free_partial_signature((yyvsp[(1) - (1)].string));
			  }
                          reset_csplit_current_beginning();
			}
    break;

  case 9:
/* Line 1787 of yacc.c  */
#line 774 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {

              /*SG: mechanism to prevent the generation of module for functions defined in standard header files
                    it should never be the case, but it sometimes happen with inline functions */
                  pips_debug(5, "function_def->global\n");
                  csplit_is_external = 0; /* the variable is declared inside a function */
                  pips_debug(1, "Function \"%s\" declaration and body are located between line %d and line %d\n",
                      csplit_definite_function_name,
                      get_csplit_current_beginning(),
                      csplit_line_number);
                  /* Hmm... It happens to early to gather
                     following comments to its module... */
                  csplit_copy(csplit_definite_function_name,
                          csplit_definite_function_signature,
                          get_csplit_current_beginning(),
                          csplit_line_number,
                          get_csplit_file_offset_beginning(),
                          get_current_csplit_file_offset(),
                          get_user_current_beginning(),
                          current_function_is_static_p);
              reset_csplit_current_beginning();
			}
    break;

  case 10:
/* Line 1787 of yacc.c  */
#line 797 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
                           reset_csplit_current_beginning();
                        }
    break;

  case 11:
/* Line 1787 of yacc.c  */
#line 801 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
                          reset_csplit_current_beginning();
			}
    break;

  case 12:
/* Line 1787 of yacc.c  */
#line 808 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  pips_internal_error("Not implemented yet\n");
			}
    break;

  case 13:
/* Line 1787 of yacc.c  */
#line 813 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  pips_internal_error("Not implemented yet\n");
			}
    break;

  case 14:
/* Line 1787 of yacc.c  */
#line 818 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  pips_internal_error("Not implemented yet\n");
			}
    break;

  case 15:
/* Line 1787 of yacc.c  */
#line 823 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  pips_internal_error("Not implemented yet\n");
			}
    break;

  case 16:
/* Line 1787 of yacc.c  */
#line 827 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  pips_user_error("Parse error: location error TK_SEMICOLON \n");
			}
    break;

  case 17:
/* Line 1787 of yacc.c  */
#line 834 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  (yyval.string)=new_signature(splitc_text);
			}
    break;

  case 18:
/* Line 1787 of yacc.c  */
#line 838 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    { (yyval.string)=new_signature(splitc_text);}
    break;

  case 19:
/* Line 1787 of yacc.c  */
#line 840 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			   csplit_parser_warning("CIL AT not implemented\n");
			   (yyval.string) = build_signature(new_signature("at_name"), new_lparen(), new_signature((yyvsp[(3) - (4)].string)),
						new_rparen(), NULL);
			}
    break;

  case 20:
/* Line 1787 of yacc.c  */
#line 848 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    { (yyval.string) =new_signature("");}
    break;

  case 21:
/* Line 1787 of yacc.c  */
#line 849 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    { (yyval.string) = new_comma();}
    break;

  case 22:
/* Line 1787 of yacc.c  */
#line 858 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  (yyval.string) = (yyvsp[(1) - (1)].string);
			}
    break;

  case 23:
/* Line 1787 of yacc.c  */
#line 862 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  /* Elements in enum are symbolic constant which
                             may appear in an array declaration. */
			  (yyval.string) = new_signature((yyvsp[(1) - (1)].string));
                        }
    break;

  case 24:
/* Line 1787 of yacc.c  */
#line 868 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  /* Can be used to dimemsion an argument */
			  (yyval.string) = safe_build_signature(new_signature("sizeof"),
						    (yyvsp[(2) - (2)].string), NULL);
                        }
    break;

  case 25:
/* Line 1787 of yacc.c  */
#line 874 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  (yyval.string) = safe_build_signature(new_signature("sizeof"),
						    new_lparen(), (yyvsp[(3) - (4)].string), new_rparen(),
						    NULL);
                        }
    break;

  case 26:
/* Line 1787 of yacc.c  */
#line 880 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  free_partial_signature((yyvsp[(2) - (2)].string));
			  (yyval.string) = string_undefined;
			}
    break;

  case 27:
/* Line 1787 of yacc.c  */
#line 885 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  free_partial_signature((yyvsp[(3) - (4)].string));
			  (yyval.string) = string_undefined;
			}
    break;

  case 28:
/* Line 1787 of yacc.c  */
#line 890 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  (yyval.string) = safe_build_signature(new_signature("+"), (yyvsp[(2) - (2)].string), NULL);
			}
    break;

  case 29:
/* Line 1787 of yacc.c  */
#line 894 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  (yyval.string) = safe_build_signature(new_signature("-"), (yyvsp[(2) - (2)].string), NULL);
			}
    break;

  case 30:
/* Line 1787 of yacc.c  */
#line 898 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  (yyval.string) = safe_build_signature(new_signature("*"), (yyvsp[(2) - (2)].string), NULL);
			}
    break;

  case 31:
/* Line 1787 of yacc.c  */
#line 902 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  (yyval.string) = safe_build_signature(new_signature("&"), (yyvsp[(2) - (2)].string), NULL);
			}
    break;

  case 32:
/* Line 1787 of yacc.c  */
#line 906 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  (yyval.string) = safe_build_signature(new_signature("!"), (yyvsp[(2) - (2)].string), NULL);
			}
    break;

  case 33:
/* Line 1787 of yacc.c  */
#line 910 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  (yyval.string) = safe_build_signature(new_signature("~"), (yyvsp[(2) - (2)].string), NULL);
			}
    break;

  case 34:
/* Line 1787 of yacc.c  */
#line 914 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  (yyval.string) = safe_build_signature(new_signature("++"), (yyvsp[(2) - (2)].string), NULL);
			}
    break;

  case 35:
/* Line 1787 of yacc.c  */
#line 918 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  (yyval.string) = safe_build_signature((yyvsp[(1) - (2)].string), new_signature("++"), NULL);
			}
    break;

  case 36:
/* Line 1787 of yacc.c  */
#line 922 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  (yyval.string) = safe_build_signature(new_signature("--"), (yyvsp[(2) - (2)].string), NULL);
			}
    break;

  case 37:
/* Line 1787 of yacc.c  */
#line 926 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  (yyval.string) = safe_build_signature((yyvsp[(1) - (2)].string), new_signature("--"), NULL);
			}
    break;

  case 38:
/* Line 1787 of yacc.c  */
#line 930 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  (yyval.string) = safe_build_signature((yyvsp[(1) - (3)].string), new_signature("->"), (yyvsp[(3) - (3)].string), NULL);
			}
    break;

  case 39:
/* Line 1787 of yacc.c  */
#line 934 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  (yyval.string) = safe_build_signature((yyvsp[(1) - (3)].string), new_signature("."), (yyvsp[(3) - (3)].string), NULL);
			}
    break;

  case 40:
/* Line 1787 of yacc.c  */
#line 938 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  (yyval.string) = string_undefined;
			  /* $$ = new_signature("block"); */
			}
    break;

  case 41:
/* Line 1787 of yacc.c  */
#line 943 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  (yyval.string) = (yyvsp[(1) - (1)].string);
			}
    break;

  case 42:
/* Line 1787 of yacc.c  */
#line 947 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  free_partial_signature((yyvsp[(1) - (4)].string));
			  /* arguments does not return anything. */
			  (yyval.string) = string_undefined;
			}
    break;

  case 43:
/* Line 1787 of yacc.c  */
#line 953 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  free_partial_signature((yyvsp[(3) - (6)].string));
			  free_partial_signature((yyvsp[(5) - (6)].string));
			  (yyval.string) = string_undefined;
			}
    break;

  case 44:
/* Line 1787 of yacc.c  */
#line 959 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  free_partial_signature((yyvsp[(1) - (2)].string));
			  /* bracket_comma_expression does not return anything. */
			  (yyval.string) = string_undefined;
			}
    break;

  case 45:
/* Line 1787 of yacc.c  */
#line 965 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  //free_partial_signature($1);
			  /* opt_expression does not return anything. */
			  //free_partial_signature($5);
			  //$$ = string_undefined;
			  (yyval.string) = safe_build_signature((yyvsp[(1) - (5)].string),
						    new_signature("?"),
						    (yyvsp[(3) - (5)].string),
						    new_signature(":"),
						    (yyvsp[(5) - (5)].string), NULL);
			}
    break;

  case 46:
/* Line 1787 of yacc.c  */
#line 977 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  (yyval.string) = safe_build_signature((yyvsp[(1) - (3)].string), new_signature("+"), (yyvsp[(3) - (3)].string), NULL);
			}
    break;

  case 47:
/* Line 1787 of yacc.c  */
#line 981 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  (yyval.string) = safe_build_signature((yyvsp[(1) - (3)].string), new_signature("-"), (yyvsp[(3) - (3)].string), NULL);
			}
    break;

  case 48:
/* Line 1787 of yacc.c  */
#line 985 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  (yyval.string) = safe_build_signature((yyvsp[(1) - (3)].string), new_signature("*"), (yyvsp[(3) - (3)].string), NULL);
			}
    break;

  case 49:
/* Line 1787 of yacc.c  */
#line 989 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  (yyval.string) = safe_build_signature((yyvsp[(1) - (3)].string), new_signature("/"), (yyvsp[(3) - (3)].string), NULL);
			}
    break;

  case 50:
/* Line 1787 of yacc.c  */
#line 993 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  (yyval.string) = safe_build_signature((yyvsp[(1) - (3)].string), new_signature("%"), (yyvsp[(3) - (3)].string), NULL);
			}
    break;

  case 51:
/* Line 1787 of yacc.c  */
#line 997 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  (yyval.string) = safe_build_signature((yyvsp[(1) - (3)].string), new_signature("&&"), (yyvsp[(3) - (3)].string), NULL);
			}
    break;

  case 52:
/* Line 1787 of yacc.c  */
#line 1001 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  (yyval.string) = safe_build_signature((yyvsp[(1) - (3)].string), new_signature("||"), (yyvsp[(3) - (3)].string), NULL);
			}
    break;

  case 53:
/* Line 1787 of yacc.c  */
#line 1005 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  (yyval.string) = safe_build_signature((yyvsp[(1) - (3)].string), new_signature("&"), (yyvsp[(3) - (3)].string), NULL);
			}
    break;

  case 54:
/* Line 1787 of yacc.c  */
#line 1009 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  (yyval.string) = safe_build_signature((yyvsp[(1) - (3)].string), new_signature("|"), (yyvsp[(3) - (3)].string), NULL);
			}
    break;

  case 55:
/* Line 1787 of yacc.c  */
#line 1013 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  (yyval.string) = safe_build_signature((yyvsp[(1) - (3)].string), new_signature("^"), (yyvsp[(3) - (3)].string), NULL);
			}
    break;

  case 56:
/* Line 1787 of yacc.c  */
#line 1017 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  //free_partial_signature($1);
			  //free_partial_signature($3);
			  //$$ = string_undefined;
			  (yyval.string) = safe_build_signature((yyvsp[(1) - (3)].string), new_signature("=="), (yyvsp[(3) - (3)].string), NULL);
			}
    break;

  case 57:
/* Line 1787 of yacc.c  */
#line 1024 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  //free_partial_signature($1);
			  //free_partial_signature($3);
			  //$$ = string_undefined;
			  (yyval.string) = safe_build_signature((yyvsp[(1) - (3)].string), new_signature("!="), (yyvsp[(3) - (3)].string), NULL);
			}
    break;

  case 58:
/* Line 1787 of yacc.c  */
#line 1031 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  //free_partial_signature($1);
			  //free_partial_signature($3);
			  //$$ = string_undefined;
			  (yyval.string) = safe_build_signature((yyvsp[(1) - (3)].string), new_signature("<"), (yyvsp[(3) - (3)].string), NULL);
			}
    break;

  case 59:
/* Line 1787 of yacc.c  */
#line 1038 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  //free_partial_signature($1);
			  //free_partial_signature($3);
			  //$$ = string_undefined;
			  (yyval.string) = safe_build_signature((yyvsp[(1) - (3)].string), new_signature(">"), (yyvsp[(3) - (3)].string), NULL);
			}
    break;

  case 60:
/* Line 1787 of yacc.c  */
#line 1045 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  //free_partial_signature($1);
			  //free_partial_signature($3);
			  //$$ = string_undefined;
			  (yyval.string) = safe_build_signature((yyvsp[(1) - (3)].string), new_signature("<="), (yyvsp[(3) - (3)].string), NULL);
			}
    break;

  case 61:
/* Line 1787 of yacc.c  */
#line 1052 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  //free_partial_signature($1);
			  //free_partial_signature($3);
			  //$$ = string_undefined;
			  (yyval.string) = safe_build_signature((yyvsp[(1) - (3)].string), new_signature(">="), (yyvsp[(3) - (3)].string), NULL);
			}
    break;

  case 62:
/* Line 1787 of yacc.c  */
#line 1059 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  //free_partial_signature($1);
			  //free_partial_signature($3);
			  //$$ = string_undefined;
			  (yyval.string) = safe_build_signature((yyvsp[(1) - (3)].string), new_signature("<<"), (yyvsp[(3) - (3)].string), NULL);
			}
    break;

  case 63:
/* Line 1787 of yacc.c  */
#line 1066 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  //free_partial_signature($1);
			  //free_partial_signature($3);
			  //$$ = string_undefined;
			  (yyval.string) = safe_build_signature((yyvsp[(1) - (3)].string), new_signature(">>"), (yyvsp[(3) - (3)].string), NULL);
			}
    break;

  case 64:
/* Line 1787 of yacc.c  */
#line 1073 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  free_partial_signature((yyvsp[(1) - (3)].string));
			  free_partial_signature((yyvsp[(3) - (3)].string));
			  (yyval.string) = string_undefined;
			}
    break;

  case 65:
/* Line 1787 of yacc.c  */
#line 1079 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  free_partial_signature((yyvsp[(1) - (3)].string));
			  free_partial_signature((yyvsp[(3) - (3)].string));
			  (yyval.string) = string_undefined;
			}
    break;

  case 66:
/* Line 1787 of yacc.c  */
#line 1085 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  free_partial_signature((yyvsp[(1) - (3)].string));
			  free_partial_signature((yyvsp[(3) - (3)].string));
			  (yyval.string) = string_undefined;
			}
    break;

  case 67:
/* Line 1787 of yacc.c  */
#line 1091 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  free_partial_signature((yyvsp[(1) - (3)].string));
			  free_partial_signature((yyvsp[(3) - (3)].string));
			  (yyval.string) = string_undefined;
			}
    break;

  case 68:
/* Line 1787 of yacc.c  */
#line 1097 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  free_partial_signature((yyvsp[(1) - (3)].string));
			  free_partial_signature((yyvsp[(3) - (3)].string));
			  (yyval.string) = string_undefined;
			}
    break;

  case 69:
/* Line 1787 of yacc.c  */
#line 1103 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  free_partial_signature((yyvsp[(1) - (3)].string));
			  free_partial_signature((yyvsp[(3) - (3)].string));
			  (yyval.string) = string_undefined;
			}
    break;

  case 70:
/* Line 1787 of yacc.c  */
#line 1109 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  free_partial_signature((yyvsp[(1) - (3)].string));
			  free_partial_signature((yyvsp[(3) - (3)].string));
			  (yyval.string) = string_undefined;
			}
    break;

  case 71:
/* Line 1787 of yacc.c  */
#line 1115 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  free_partial_signature((yyvsp[(1) - (3)].string));
			  free_partial_signature((yyvsp[(3) - (3)].string));
			  (yyval.string) = string_undefined;
			}
    break;

  case 72:
/* Line 1787 of yacc.c  */
#line 1121 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  free_partial_signature((yyvsp[(1) - (3)].string));
			  free_partial_signature((yyvsp[(3) - (3)].string));
			  (yyval.string) = string_undefined;
			}
    break;

  case 73:
/* Line 1787 of yacc.c  */
#line 1127 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  free_partial_signature((yyvsp[(1) - (3)].string));
			  free_partial_signature((yyvsp[(3) - (3)].string));
			  (yyval.string) = string_undefined;
			}
    break;

  case 74:
/* Line 1787 of yacc.c  */
#line 1133 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  free_partial_signature((yyvsp[(1) - (3)].string));
			  free_partial_signature((yyvsp[(3) - (3)].string));
			  (yyval.string) = string_undefined;
			}
    break;

  case 75:
/* Line 1787 of yacc.c  */
#line 1139 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  free_partial_signature((yyvsp[(2) - (4)].string));
			  free_partial_signature((yyvsp[(4) - (4)].string));
			  (yyval.string) = string_undefined;
			}
    break;

  case 76:
/* Line 1787 of yacc.c  */
#line 1146 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  free_partial_signature((yyvsp[(2) - (6)].string));
			  /* initializer_list_opt does not return anything. */
			  (yyval.string) = string_undefined;
			}
    break;

  case 77:
/* Line 1787 of yacc.c  */
#line 1153 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  (yyval.string) = string_undefined;
			}
    break;

  case 78:
/* Line 1787 of yacc.c  */
#line 1157 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  (yyval.string) = string_undefined;
			}
    break;

  case 79:
/* Line 1787 of yacc.c  */
#line 1166 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  (yyval.string) = new_signature((yyvsp[(1) - (1)].string));
			}
    break;

  case 80:
/* Line 1787 of yacc.c  */
#line 1170 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  (yyval.string) = string_undefined;
			}
    break;

  case 81:
/* Line 1787 of yacc.c  */
#line 1174 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  (yyval.string) = string_undefined;
			}
    break;

  case 82:
/* Line 1787 of yacc.c  */
#line 1178 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  (yyval.string) = string_undefined;
			}
    break;

  case 83:
/* Line 1787 of yacc.c  */
#line 1182 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  (yyval.string) = string_undefined;
                        }
    break;

  case 84:
/* Line 1787 of yacc.c  */
#line 1188 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  (yyval.string) = string_undefined;
                        }
    break;

  case 85:
/* Line 1787 of yacc.c  */
#line 1197 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			}
    break;

  case 86:
/* Line 1787 of yacc.c  */
#line 1203 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {}
    break;

  case 87:
/* Line 1787 of yacc.c  */
#line 1207 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			}
    break;

  case 88:
/* Line 1787 of yacc.c  */
#line 1210 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			}
    break;

  case 89:
/* Line 1787 of yacc.c  */
#line 1216 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			}
    break;

  case 90:
/* Line 1787 of yacc.c  */
#line 1219 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			}
    break;

  case 91:
/* Line 1787 of yacc.c  */
#line 1222 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			}
    break;

  case 92:
/* Line 1787 of yacc.c  */
#line 1228 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    { }
    break;

  case 93:
/* Line 1787 of yacc.c  */
#line 1230 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    { }
    break;

  case 94:
/* Line 1787 of yacc.c  */
#line 1232 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    { }
    break;

  case 95:
/* Line 1787 of yacc.c  */
#line 1236 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    { free_partial_signature((yyvsp[(1) - (1)].string));}
    break;

  case 96:
/* Line 1787 of yacc.c  */
#line 1238 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    { }
    break;

  case 97:
/* Line 1787 of yacc.c  */
#line 1242 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			}
    break;

  case 98:
/* Line 1787 of yacc.c  */
#line 1245 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			}
    break;

  case 99:
/* Line 1787 of yacc.c  */
#line 1249 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    { }
    break;

  case 100:
/* Line 1787 of yacc.c  */
#line 1250 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    { }
    break;

  case 101:
/* Line 1787 of yacc.c  */
#line 1254 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			}
    break;

  case 102:
/* Line 1787 of yacc.c  */
#line 1257 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			}
    break;

  case 103:
/* Line 1787 of yacc.c  */
#line 1259 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    { }
    break;

  case 104:
/* Line 1787 of yacc.c  */
#line 1263 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    { }
    break;

  case 105:
/* Line 1787 of yacc.c  */
#line 1266 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			}
    break;

  case 106:
/* Line 1787 of yacc.c  */
#line 1271 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    { }
    break;

  case 107:
/* Line 1787 of yacc.c  */
#line 1273 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    { free_partial_signature((yyvsp[(2) - (4)].string)); }
    break;

  case 108:
/* Line 1787 of yacc.c  */
#line 1275 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    { free_partial_signature((yyvsp[(2) - (5)].string)); free_partial_signature((yyvsp[(4) - (5)].string)); }
    break;

  case 109:
/* Line 1787 of yacc.c  */
#line 1278 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    { }
    break;

  case 110:
/* Line 1787 of yacc.c  */
#line 1279 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {}
    break;

  case 111:
/* Line 1787 of yacc.c  */
#line 1284 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			}
    break;

  case 112:
/* Line 1787 of yacc.c  */
#line 1289 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    { }
    break;

  case 113:
/* Line 1787 of yacc.c  */
#line 1290 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    { free_partial_signature((yyvsp[(1) - (1)].string)); }
    break;

  case 114:
/* Line 1787 of yacc.c  */
#line 1295 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    { (yyval.string)=strdup(" ");}
    break;

  case 115:
/* Line 1787 of yacc.c  */
#line 1297 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
                          //free_partial_signature($1);
			  (yyval.string) = (yyvsp[(1) - (1)].string);
			}
    break;

  case 116:
/* Line 1787 of yacc.c  */
#line 1305 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  (yyval.string) = (yyvsp[(1) - (1)].string);
			}
    break;

  case 117:
/* Line 1787 of yacc.c  */
#line 1309 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  (yyval.string) = safe_build_signature((yyvsp[(1) - (3)].string), new_comma(), (yyvsp[(3) - (3)].string), NULL);
			}
    break;

  case 118:
/* Line 1787 of yacc.c  */
#line 1313 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  csplit_parser_error("within expression list.\n");
			  (yyval.string) = string_undefined;
			}
    break;

  case 119:
/* Line 1787 of yacc.c  */
#line 1320 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    { (yyval.string) = new_empty(); }
    break;

  case 120:
/* Line 1787 of yacc.c  */
#line 1321 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    { (yyval.string) = (yyvsp[(1) - (1)].string); }
    break;

  case 121:
/* Line 1787 of yacc.c  */
#line 1326 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  (yyval.string) = safe_build_signature(new_lparen(), (yyvsp[(2) - (3)].string),
						    new_rparen(), NULL);
			}
    break;

  case 122:
/* Line 1787 of yacc.c  */
#line 1331 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  csplit_parser_error("Error within parenthesized expression.\n");
			  (yyval.string) = string_undefined;
			}
    break;

  case 123:
/* Line 1787 of yacc.c  */
#line 1339 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  free_partial_signature((yyvsp[(2) - (3)].string));
			}
    break;

  case 124:
/* Line 1787 of yacc.c  */
#line 1343 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			}
    break;

  case 125:
/* Line 1787 of yacc.c  */
#line 1349 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {push_new_preprocessor_scope();}
    break;

  case 126:
/* Line 1787 of yacc.c  */
#line 1349 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {pop_preprocessor_scope();}
    break;

  case 127:
/* Line 1787 of yacc.c  */
#line 1350 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  pips_debug(5, "block found at line %d\n",
				  csplit_line_number);
			}
    break;

  case 128:
/* Line 1787 of yacc.c  */
#line 1355 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    { }
    break;

  case 129:
/* Line 1787 of yacc.c  */
#line 1359 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {}
    break;

  case 130:
/* Line 1787 of yacc.c  */
#line 1361 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    { }
    break;

  case 131:
/* Line 1787 of yacc.c  */
#line 1365 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    { }
    break;

  case 132:
/* Line 1787 of yacc.c  */
#line 1367 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			}
    break;

  case 133:
/* Line 1787 of yacc.c  */
#line 1372 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    { }
    break;

  case 134:
/* Line 1787 of yacc.c  */
#line 1374 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			}
    break;

  case 135:
/* Line 1787 of yacc.c  */
#line 1377 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    { }
    break;

  case 136:
/* Line 1787 of yacc.c  */
#line 1381 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {}
    break;

  case 137:
/* Line 1787 of yacc.c  */
#line 1383 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    { }
    break;

  case 138:
/* Line 1787 of yacc.c  */
#line 1387 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {}
    break;

  case 139:
/* Line 1787 of yacc.c  */
#line 1388 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {}
    break;

  case 140:
/* Line 1787 of yacc.c  */
#line 1393 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			}
    break;

  case 141:
/* Line 1787 of yacc.c  */
#line 1396 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  free_partial_signature((yyvsp[(1) - (2)].string));
			}
    break;

  case 142:
/* Line 1787 of yacc.c  */
#line 1399 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    { }
    break;

  case 143:
/* Line 1787 of yacc.c  */
#line 1401 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  free_partial_signature((yyvsp[(2) - (3)].string));
			}
    break;

  case 144:
/* Line 1787 of yacc.c  */
#line 1405 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  free_partial_signature((yyvsp[(2) - (5)].string));
			}
    break;

  case 145:
/* Line 1787 of yacc.c  */
#line 1409 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			}
    break;

  case 146:
/* Line 1787 of yacc.c  */
#line 1412 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  /* free_partial_signature($1); */
			}
    break;

  case 147:
/* Line 1787 of yacc.c  */
#line 1416 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			}
    break;

  case 148:
/* Line 1787 of yacc.c  */
#line 1419 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			}
    break;

  case 149:
/* Line 1787 of yacc.c  */
#line 1422 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  /* free_partial_signature($1); */
			}
    break;

  case 150:
/* Line 1787 of yacc.c  */
#line 1426 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			}
    break;

  case 151:
/* Line 1787 of yacc.c  */
#line 1429 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  /* free_partial_signature($3); */
			}
    break;

  case 152:
/* Line 1787 of yacc.c  */
#line 1433 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			}
    break;

  case 153:
/* Line 1787 of yacc.c  */
#line 1436 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			}
    break;

  case 154:
/* Line 1787 of yacc.c  */
#line 1439 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			}
    break;

  case 155:
/* Line 1787 of yacc.c  */
#line 1442 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  free_partial_signature((yyvsp[(2) - (3)].string));
			}
    break;

  case 156:
/* Line 1787 of yacc.c  */
#line 1446 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  free_partial_signature((yyvsp[(2) - (5)].string));
			  free_partial_signature((yyvsp[(4) - (5)].string));
			}
    break;

  case 157:
/* Line 1787 of yacc.c  */
#line 1451 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			}
    break;

  case 158:
/* Line 1787 of yacc.c  */
#line 1454 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			}
    break;

  case 159:
/* Line 1787 of yacc.c  */
#line 1457 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  free_partial_signature((yyvsp[(2) - (3)].string));
			}
    break;

  case 160:
/* Line 1787 of yacc.c  */
#line 1461 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			}
    break;

  case 161:
/* Line 1787 of yacc.c  */
#line 1464 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			}
    break;

  case 162:
/* Line 1787 of yacc.c  */
#line 1467 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			}
    break;

  case 163:
/* Line 1787 of yacc.c  */
#line 1470 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  free_partial_signature((yyvsp[(3) - (4)].string));
			}
    break;

  case 164:
/* Line 1787 of yacc.c  */
#line 1474 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    { }
    break;

  case 165:
/* Line 1787 of yacc.c  */
#line 1476 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    { }
    break;

  case 166:
/* Line 1787 of yacc.c  */
#line 1478 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    { /* In C99 we can have declarations everywhere... */ }
    break;

  case 167:
/* Line 1787 of yacc.c  */
#line 1480 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			}
    break;

  case 168:
/* Line 1787 of yacc.c  */
#line 1486 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			}
    break;

  case 169:
/* Line 1787 of yacc.c  */
#line 1489 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			}
    break;

  case 170:
/* Line 1787 of yacc.c  */
#line 1495 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  pips_debug(5, "decl_spec_list init_declarator_list TK_SEMICOLON -> declaration\n");
			  pips_debug(5, "decl_spec_list=\"%s\", init_declarator_list=\"%s\"\n",
				     (yyvsp[(1) - (3)].string), string_undefined_p((yyvsp[(2) - (3)].string)) ? "UNDEFINED" : (yyvsp[(2) - (3)].string));
			  csplit_is_function = 0; /* not function's declaration */
			  //pips_assert("TypedefStack is empty", stack_empty_p(TypedefStack));
			  csplit_is_typedef = false;
			  free_partial_signature((yyvsp[(1) - (3)].string));
			  free_partial_signature((yyvsp[(2) - (3)].string));
			  (yyval.string) = string_undefined;
			  PopTypedef();
			}
    break;

  case 171:
/* Line 1787 of yacc.c  */
#line 1508 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  pips_debug(5, "decl_spec_list TK_SEMICOLON -> declaration\n");
			  pips_debug(5, "decl_spec_list=\"%s\"\n", (yyvsp[(1) - (2)].string));
			  csplit_is_function = 0; /* not function's declaration */
			  //pips_assert("TypedefStack is empty", stack_empty_p(TypedefStack));
			  csplit_is_typedef = false;
			  free_partial_signature((yyvsp[(1) - (2)].string));
			  (yyval.string) = string_undefined;
			  PopTypedef();
			}
    break;

  case 172:
/* Line 1787 of yacc.c  */
#line 1522 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  (yyval.string) = string_undefined;
			}
    break;

  case 173:
/* Line 1787 of yacc.c  */
#line 1526 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  (yyval.string) = string_undefined;
			}
    break;

  case 174:
/* Line 1787 of yacc.c  */
#line 1532 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  (yyval.string) = string_undefined;
                        }
    break;

  case 175:
/* Line 1787 of yacc.c  */
#line 1536 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  (yyval.string) = string_undefined;
			}
    break;

  case 176:
/* Line 1787 of yacc.c  */
#line 1551 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  pips_debug(5, "TK_TYPEDEF decl_spec_list_opt->decl_spec_list\n");
			  csplit_is_typedef = true;
			  pips_debug(8, "csplit_is_typedef=%s\n", bool_to_string(csplit_is_typedef));
			  /* I would have liked not to build them when unnecessary. */
			  /*
			  free_partial_signature($2);
			  $$ = string_undefined;
			  */
			  (yyval.string) = build_signature(new_signature("typedef"), (yyvsp[(2) - (2)].string), NULL);
			}
    break;

  case 177:
/* Line 1787 of yacc.c  */
#line 1563 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  pips_debug(5, "TK_EXTERN decl_spec_list_opt->decl_spec_list\n");
			  /*
			  free_partial_signature($2);
			  $$ = string_undefined;
			  */
			  (yyval.string) = build_signature(new_signature("extern"), (yyvsp[(2) - (2)].string), NULL);
			}
    break;

  case 178:
/* Line 1787 of yacc.c  */
#line 1572 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  /* There are 3 cases: static function, external and internal static variable*/
			  pips_debug(5, "TK_STATIC decl_spec_list_opt->decl_spec_list\n");
			  csplit_is_static_p = true;
			  if (!csplit_is_function) {
			    pips_debug(5, "We are not within a function, so this STATIC may be related to a function: %s.\n", (yyvsp[(2) - (2)].string));
			  }
			  (yyval.string) = build_signature(new_signature("static"), (yyvsp[(2) - (2)].string), NULL);
			}
    break;

  case 179:
/* Line 1787 of yacc.c  */
#line 1582 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  pips_debug(5, "TK_AUTO decl_spec_list_opt->decl_spec_list\n");
			  /*
			  free_partial_signature($2);
			  $$ = string_undefined;
			  */
			  (yyval.string) = build_signature(new_signature("auto"), (yyvsp[(2) - (2)].string), NULL);
			}
    break;

  case 180:
/* Line 1787 of yacc.c  */
#line 1591 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  pips_debug(5, "TK_REGISTER decl_spec_list_opt->decl_spec_list\n");
			  /*
			  free_partial_signature($2);
			  $$ = string_undefined;
			  */
			  (yyval.string) = build_signature(new_signature("register"), (yyvsp[(2) - (2)].string), NULL);
			}
    break;

  case 181:
/* Line 1787 of yacc.c  */
#line 1600 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  pips_debug(5, "TK_THREAD decl_spec_list_opt->decl_spec_list\n");
			  /*
			  free_partial_signature($2);
			  $$ = string_undefined;
			  */
			  (yyval.string) = build_signature(new_signature("thread"), (yyvsp[(2) - (2)].string), NULL);
			}
    break;

  case 182:
/* Line 1787 of yacc.c  */
#line 1610 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  pips_debug(5, "type_spec and decl_spec_list_opt_no_named -> decl_spec_list\n");
			  if(string_undefined_p((yyvsp[(1) - (2)].string))) {
			    pips_debug(5, "type_spec is undefined\n");
			    if(!string_undefined_p((yyvsp[(2) - (2)].string))) {
			      pips_debug(5, "Useless partial signature $2: %s\n", (yyvsp[(2) - (2)].string));
			      free((yyvsp[(2) - (2)].string));
			    }
			    else
			      pips_debug(5, "$1 and $2 undefined\n");
			    (yyval.string) = string_undefined;
			  }
			  else {
			    pips_debug(5, "Type spec: \"%s\"\n", (yyvsp[(1) - (2)].string));
			    (yyval.string) = build_signature((yyvsp[(1) - (2)].string), (yyvsp[(2) - (2)].string), NULL);
			    pips_debug(5, "Partial signature: \"%s\"\n", (yyval.string));
			    /* FI: might need a call to reset_csplit_current_function_name
			    if(!string_undefined_p(csplit_current_function_name)
			       && strcmp($2, csplit_current_function_name)==0) {
			      csplit_current_function_name
				= csplit_current_function_name2;
			      csplit_current_function_name2 = string_undefined;
			    }
			    */
			  }
			}
    break;

  case 183:
/* Line 1787 of yacc.c  */
#line 1638 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  pips_debug(5, "TK_INLINE decl_spec_list_opt->decl_spec_list\n");
			  /*
			  free_partial_signature($2);
			  $$ = string_undefined;
			  */
			  (yyval.string) = build_signature(new_signature("inline"), (yyvsp[(2) - (2)].string), NULL);
			}
    break;

  case 184:
/* Line 1787 of yacc.c  */
#line 1647 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  pips_debug(5, "attribute decl_spec_list_opt->decl_spec_list\n");
			  /*
			  free_partial_signature($1);
			  free_partial_signature($2);
			  $$ = string_undefined;
			  */
			  (yyval.string) = build_signature((yyvsp[(1) - (2)].string), (yyvsp[(2) - (2)].string), NULL);
			}
    break;

  case 185:
/* Line 1787 of yacc.c  */
#line 1658 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  pips_debug(5, "TK_AT_SPECIFIER TK_LPAREN TK_IDENT TK_RPAREN->decl_spec_list\n");
			  /* $$ = string_undefined; */
			  (yyval.string) = build_signature(new_signature("at specifier"),
					       new_lparen(), new_signature((yyvsp[(3) - (4)].string)),
					       new_rparen(), NULL);
			}
    break;

  case 186:
/* Line 1787 of yacc.c  */
#line 1670 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    { (yyval.string)=new_empty(); PushTypedef();}
    break;

  case 187:
/* Line 1787 of yacc.c  */
#line 1671 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    { (yyval.string)=(yyvsp[(1) - (1)].string);}
    break;

  case 188:
/* Line 1787 of yacc.c  */
#line 1679 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  /* Cf "Actions in Mid-Rule" in the Bison doc. */
			  (yyval.string) = new_empty();
			  PushTypedef();
              free((yyval.string));
			}
    break;

  case 189:
/* Line 1787 of yacc.c  */
#line 1686 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  pips_debug(8, "empty TK_IDENT->decl_spec_list_opt_no_named\n");
			  /* pips_debug(8, "TK_IDENT %s is discarded\n", $1); */
			  /* free($1); */
			  /* FI: I do not feel safe about this. */
			  /* $$=strdup(splitc_text); */ /* FI: why not $1?*/
			  /* $$ = strdup("IAmNotSure"); */
			  (yyval.string) = new_empty();
			}
    break;

  case 190:
/* Line 1787 of yacc.c  */
#line 1695 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  pips_debug(8,
				     "decl_spec_slit->decl_spec_list_opt_no_named\n");
			  (yyval.string)=(yyvsp[(1) - (1)].string);
                        }
    break;

  case 191:
/* Line 1787 of yacc.c  */
#line 1706 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  pips_debug(8, "TK_VOID->type_spec\n");
			  (yyval.string) = new_signature(splitc_text);
                        }
    break;

  case 192:
/* Line 1787 of yacc.c  */
#line 1711 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  pips_debug(8, "TK_CHAR->type_spec\n");
			  (yyval.string) = new_signature(splitc_text);
			}
    break;

  case 193:
/* Line 1787 of yacc.c  */
#line 1716 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  pips_debug(8, "TK_SHORT->type_spec\n");
			  (yyval.string) = new_signature(splitc_text);
			}
    break;

  case 194:
/* Line 1787 of yacc.c  */
#line 1721 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  pips_debug(8, "TK_INT->type_spec\n");
			  (yyval.string) = new_signature(splitc_text);
			}
    break;

  case 195:
/* Line 1787 of yacc.c  */
#line 1726 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  pips_debug(8, "TK_INT128->type_spec\n");
			  (yyval.string) = new_signature(splitc_text);
			}
    break;

  case 196:
/* Line 1787 of yacc.c  */
#line 1731 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  pips_debug(8, "TK_UINT128->type_spec\n");
			  (yyval.string) = new_signature(splitc_text);
			}
    break;

  case 197:
/* Line 1787 of yacc.c  */
#line 1736 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  pips_debug(8, "TK_COMPLEX->type_spec\n");
			  (yyval.string) = new_signature(splitc_text);
			}
    break;

  case 198:
/* Line 1787 of yacc.c  */
#line 1741 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  pips_debug(8, "TK_LONG->type_spec\n");
			  (yyval.string) = new_signature(splitc_text);
			}
    break;

  case 199:
/* Line 1787 of yacc.c  */
#line 1746 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  pips_debug(8, "TK_FLOAT->type_spec\n");
			  (yyval.string) = new_signature(splitc_text);
			}
    break;

  case 200:
/* Line 1787 of yacc.c  */
#line 1751 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  pips_debug(8, "TK_DOUBLE->type_spec\n");
			  (yyval.string) = new_signature(splitc_text);
			}
    break;

  case 201:
/* Line 1787 of yacc.c  */
#line 1756 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  pips_debug(8, "TK_SIGNED->type_spec\n");
			  (yyval.string) = new_signature(splitc_text);
			}
    break;

  case 202:
/* Line 1787 of yacc.c  */
#line 1761 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  pips_debug(8, "TK_UNSIGNED->type_spec\n");
			  (yyval.string) = new_signature(splitc_text);
			}
    break;

  case 203:
/* Line 1787 of yacc.c  */
#line 1766 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  pips_debug(8, "TK_STRUCT id_or_typename->type_spec\n");
			  /* FI: not clean, but the parser
			     distinguishes between different kinds of
			     ident and do not process them the same
			     way. */
			  if(!string_undefined_p(csplit_current_function_name)
			     && strcmp(csplit_current_function_name, (yyvsp[(2) - (2)].string))==0) {
			    reset_csplit_current_function_name();
			  }
			  (yyval.string) = build_signature(new_signature("struct"), (yyvsp[(2) - (2)].string), NULL);
			  /* see reset_csplit_current_function_name()
			    if(!string_undefined_p(csplit_current_function_name)
			       && strcmp($2, csplit_current_function_name)==0) {
			      csplit_current_function_name
				= csplit_current_function_name2;
			      csplit_current_function_name2 = string_undefined;
			    }
			  */
			}
    break;

  case 204:
/* Line 1787 of yacc.c  */
#line 1787 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  pips_debug(8, "TK_STRUCT id_or_typename TK_LBRACE struct_decl_list"
				     " TK_RBRACE->type_spec\n");
			  /* FI: I do not understand the reset. I copy
			     the guard from previous rule */
			  if(!string_undefined_p(csplit_current_function_name)
			     && strcmp(csplit_current_function_name, (yyvsp[(2) - (5)].string))==0) {
			    reset_csplit_current_function_name();
			  }
			  (yyval.string) = build_signature(new_signature("bstruct"), (yyvsp[(2) - (5)].string), new_lbrace(), (yyvsp[(4) - (5)].string),
					       new_rbrace(), NULL);
			}
    break;

  case 205:
/* Line 1787 of yacc.c  */
#line 1801 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  pips_debug(8, "TK_STRUCT TK_LBRACE struct_decl_list TK_RBRACE->type_spec\n");
			  (yyval.string) = build_signature(new_signature("struct"), new_lbrace(), (yyvsp[(3) - (4)].string),
					       new_rbrace(), NULL);
			}
    break;

  case 206:
/* Line 1787 of yacc.c  */
#line 1807 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  pips_debug(8, "TK_UNION id_or_typename->type_spec\n");
			  if(strcmp(csplit_current_function_name, (yyvsp[(2) - (2)].string))==0) {
			    reset_csplit_current_function_name();
			  }
			  (yyval.string) = build_signature(new_signature("union"), (yyvsp[(2) - (2)].string), NULL);
			}
    break;

  case 207:
/* Line 1787 of yacc.c  */
#line 1815 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  pips_debug(8, "TK_UNION id_or_typename TK_LBRACE struct_decl_list TK_RBRACE->type_spec\n");
			  if(strcmp(csplit_current_function_name, (yyvsp[(2) - (5)].string))==0) {
			    reset_csplit_current_function_name();
			  }
			  (yyval.string) = build_signature(new_signature("union"), (yyvsp[(2) - (5)].string), new_lbrace(), (yyvsp[(4) - (5)].string),
					       new_rbrace(), NULL);
			}
    break;

  case 208:
/* Line 1787 of yacc.c  */
#line 1824 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  pips_debug(8, "TK_UNION TK_LBRACE->type_spec\n");
			  (yyval.string) = build_signature(new_signature("union"), new_lbrace(), (yyvsp[(3) - (4)].string),
					       new_rbrace(), NULL);
			}
    break;

  case 209:
/* Line 1787 of yacc.c  */
#line 1830 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  pips_debug(8, "TK_ENUM id_or_typename->type_spec\n");
			  if(strcmp(csplit_current_function_name, (yyvsp[(2) - (2)].string))==0) {
			    reset_csplit_current_function_name();
			  }
			  (yyval.string) = build_signature(new_signature("enum"), (yyvsp[(2) - (2)].string), NULL);
			}
    break;

  case 210:
/* Line 1787 of yacc.c  */
#line 1838 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  pips_debug(8, "TK_ENUM id_or_typename TK_LBRACE enum_list maybecomma TK_RBRACE->type_spec\n");
			  if(strcmp(csplit_current_function_name, (yyvsp[(2) - (6)].string))==0) {
			    reset_csplit_current_function_name();
			  }
			  (yyval.string) = build_signature(new_signature("enum"), (yyvsp[(2) - (6)].string), new_lbrace(), (yyvsp[(4) - (6)].string), (yyvsp[(5) - (6)].string), new_rbrace(), NULL);
			}
    break;

  case 211:
/* Line 1787 of yacc.c  */
#line 1846 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  pips_debug(8, "TK_ENUM TK_LBRACE enum_list maybecomma TK_RBRACE->type_spec\n");
			  (yyval.string) = build_signature(new_signature("enum"), new_lbrace(), (yyvsp[(3) - (5)].string), (yyvsp[(4) - (5)].string), new_rbrace(), NULL);
			}
    break;

  case 212:
/* Line 1787 of yacc.c  */
#line 1851 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  pips_debug(8, "TK_NAMED_TYPE->type_spec\n");
			  (yyval.string) = new_signature((yyvsp[(1) - (1)].string));
			}
    break;

  case 213:
/* Line 1787 of yacc.c  */
#line 1856 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  pips_debug(8, "TK_TYPEOF TK_LPAREN expression TK_RPAREN->type_spec\n");
			  (yyval.string) = build_signature(new_signature("typeof"), new_lparen(), new_signature("IDoNotWantToDealWithExpressions"), new_rparen(), NULL);
			}
    break;

  case 214:
/* Line 1787 of yacc.c  */
#line 1861 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  pips_debug(8, "TK_TYPEOF TK_LPAREN type_name TK_RPAREN->type_spec\n");
			  (yyval.string) = build_signature(new_signature("typeof"), new_lparen(), (yyvsp[(3) - (4)].string), new_rparen(), NULL);;
			}
    break;

  case 215:
/* Line 1787 of yacc.c  */
#line 1870 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    { (yyval.string) = new_empty(); }
    break;

  case 216:
/* Line 1787 of yacc.c  */
#line 1872 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  PopTypedef();
			  (yyval.string) = build_signature((yyvsp[(1) - (3)].string), new_semicolon(), (yyvsp[(3) - (3)].string), NULL);
			}
    break;

  case 217:
/* Line 1787 of yacc.c  */
#line 1878 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  PopTypedef();
			  (yyval.string) = build_signature((yyvsp[(1) - (4)].string), (yyvsp[(2) - (4)].string), new_semicolon(), (yyvsp[(4) - (4)].string), NULL);
			}
    break;

  case 218:
/* Line 1787 of yacc.c  */
#line 1883 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  csplit_parser_error("in struct declaration.");
			  (yyval.string) = string_undefined;
			}
    break;

  case 219:
/* Line 1787 of yacc.c  */
#line 1891 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  (yyval.string) = (yyvsp[(1) - (1)].string);
			}
    break;

  case 220:
/* Line 1787 of yacc.c  */
#line 1895 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  (yyval.string) = build_signature((yyvsp[(1) - (3)].string), new_comma(), (yyvsp[(3) - (3)].string), NULL);
			}
    break;

  case 221:
/* Line 1787 of yacc.c  */
#line 1901 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    { (yyval.string) = (yyvsp[(1) - (1)].string); }
    break;

  case 222:
/* Line 1787 of yacc.c  */
#line 1903 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  (yyval.string) = build_signature((yyvsp[(1) - (3)].string), new_colon(), (yyvsp[(3) - (3)].string), NULL);
			}
    break;

  case 223:
/* Line 1787 of yacc.c  */
#line 1907 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  (yyval.string) = build_signature(new_colon(), (yyvsp[(2) - (2)].string), NULL);
			}
    break;

  case 224:
/* Line 1787 of yacc.c  */
#line 1914 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  (yyval.string) = (yyvsp[(1) - (1)].string);
			}
    break;

  case 225:
/* Line 1787 of yacc.c  */
#line 1918 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  (yyval.string) = build_signature((yyvsp[(1) - (3)].string), new_comma(), (yyvsp[(3) - (3)].string), NULL);
			}
    break;

  case 226:
/* Line 1787 of yacc.c  */
#line 1922 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  csplit_parser_error("in enum list");
			  (yyval.string) = string_undefined;
			}
    break;

  case 227:
/* Line 1787 of yacc.c  */
#line 1930 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  pips_debug(5, "TK_IDENT->enumerator\n");
			  pips_debug(9, "TK_IDENT=%s\n", (yyvsp[(1) - (1)].string));
			  (yyval.string) = new_signature((yyvsp[(1) - (1)].string));
			}
    break;

  case 228:
/* Line 1787 of yacc.c  */
#line 1936 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  pips_debug(5, "TK_IDENT TK_EQ expression->enumerator\n");
			  pips_debug(9, "TK_IDENT=%s\n", (yyvsp[(1) - (3)].string));
			  (yyval.string) = build_signature(new_signature((yyvsp[(1) - (3)].string)), new_eq(), (yyvsp[(3) - (3)].string), NULL);
			}
    break;

  case 229:
/* Line 1787 of yacc.c  */
#line 1945 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  pips_debug(5, "pointer_opt direct_decl attributes_with_asm -> declarator\n");
			  pips_debug(5, "pointer_opt=\"%s\", direct_decl=\"%s\", attributes_with_asm=\"%s\"\n", (yyvsp[(1) - (3)].string), (yyvsp[(2) - (3)].string), (yyvsp[(3) - (3)].string));
			  /* Type and identifier information are mixed
                             here. Instead of trying to retrieve the type
                             only, it might be easier to postprocess the
                             signature for Rule 2. */
			  if(!string_undefined_p((yyvsp[(3) - (3)].string)) && strlen((yyvsp[(3) - (3)].string))>0) {
			    pips_user_warning("attributes_with_asm=", (yyvsp[(3) - (3)].string));
			    csplit_parser_warning("attributes_with_asm not supported\n");
			    free_partial_signature((yyvsp[(3) - (3)].string));
			  }
			  if(true) /* Keep parameter names in signatures. */
			    (yyval.string) = build_signature((yyvsp[(1) - (3)].string), (yyvsp[(2) - (3)].string), NULL);
			  else {
			    /* This does not work! Do not try it anymore... */
			    free_partial_signature((yyvsp[(2) - (3)].string));
			    (yyval.string) = (yyvsp[(1) - (3)].string);
			  }
			}
    break;

  case 230:
/* Line 1787 of yacc.c  */
#line 1971 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			 pips_debug(5, "id_or_typename -> direct_decl\n");
			 pips_debug(5,"id_or_typename=\"%s\", csplit_is_typedef=%s\n", (yyvsp[(1) - (1)].string), bool_to_string(csplit_is_typedef));
			 /* FI: I declare many too many types! I should look at Nga's grammar. */
			 if (csplit_is_typedef) {
			   /* Tell the lexer about the new type names : add to keyword_typedef_table */
			   /*
			     hash_put(keyword_typedef_table,new_signature($1),(void *) TK_NAMED_TYPE);
			   */
			   keep_track_of_typedef(new_signature((yyvsp[(1) - (1)].string)));
			   /* Too early to reset: one typedef can be used
                              to declare several named types... but I do
                              not know how to use it. */
			   //csplit_is_typedef = false;
			   (yyval.string) = (yyvsp[(1) - (1)].string);
			 }
			 else if(true) { /* Keep identifiers in signatures */
			   (yyval.string) = (yyvsp[(1) - (1)].string);
			 }
			 else { /* You are going to loose the function
                                   identifier. You may also loose enum
                                   member names... */
			   (yyval.string) = new_empty();
			 }
		       }
    break;

  case 231:
/* Line 1787 of yacc.c  */
#line 1997 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  (yyval.string) = build_signature(new_lparen(), (yyvsp[(2) - (4)].string), (yyvsp[(3) - (4)].string), new_rparen(), NULL);
			}
    break;

  case 232:
/* Line 1787 of yacc.c  */
#line 2001 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  string s1 = (yyvsp[(1) - (5)].string);
			  string s3 = (yyvsp[(3) - (5)].string);
			  string s4 = (yyvsp[(4) - (5)].string);
			  /* FI: quick fix for
			     summary_preconditions02.c which uses a
			     function call to size an array... */
			  if(string_undefined_p(s4))
			    s4 = new_empty();
			  (yyval.string) = build_signature(s1, new_lbracket(), s3, s4, new_rbracket(), NULL);
			}
    break;

  case 233:
/* Line 1787 of yacc.c  */
#line 2013 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  (yyval.string) = build_signature((yyvsp[(1) - (5)].string), new_lbracket(), (yyvsp[(3) - (5)].string), new_rbracket(), NULL);
			}
    break;

  case 234:
/* Line 1787 of yacc.c  */
#line 2017 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  (yyval.string) = build_signature((yyvsp[(1) - (4)].string), (yyvsp[(2) - (4)].string), (yyvsp[(3) - (4)].string), new_rparen(), NULL);
			}
    break;

  case 235:
/* Line 1787 of yacc.c  */
#line 2023 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    { (yyval.string) = new_lparen();}
    break;

  case 236:
/* Line 1787 of yacc.c  */
#line 2027 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    { (yyval.string) = new_empty();}
    break;

  case 237:
/* Line 1787 of yacc.c  */
#line 2029 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  /* If such a test is really useful, it might be
                             better located in another version of
                             build_signature() which would check its
                             arguments and decide to return
                             string_undefined as soon as one of its
                             arguments is undefined. */
			  if(string_undefined_p((yyvsp[(1) - (2)].string))) {
			    free_partial_signature((yyvsp[(2) - (2)].string));
			    (yyval.string) = string_undefined;
			  }
			  else
			    (yyval.string) = build_signature((yyvsp[(1) - (2)].string), (yyvsp[(2) - (2)].string), NULL);
			}
    break;

  case 238:
/* Line 1787 of yacc.c  */
#line 2045 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    { (yyval.string) = new_empty(); }
    break;

  case 239:
/* Line 1787 of yacc.c  */
#line 2047 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  (yyval.string) = build_signature(new_comma(), new_ellipsis(), NULL);
			}
    break;

  case 240:
/* Line 1787 of yacc.c  */
#line 2051 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  (yyval.string) = build_signature(new_comma(), (yyvsp[(2) - (3)].string), (yyvsp[(3) - (3)].string), NULL);
			}
    break;

  case 241:
/* Line 1787 of yacc.c  */
#line 2058 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  PopTypedef();
			  (yyval.string) = build_signature((yyvsp[(1) - (2)].string), (yyvsp[(2) - (2)].string), NULL);
			}
    break;

  case 242:
/* Line 1787 of yacc.c  */
#line 2063 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  pips_debug(5, "decl_spec_list abstract_decl->parameter_decl\n");
			  /*
			  $$ = build_signature($1, $2, NULL);
			  $$ = build_signature($1,
					       $2,
					       NULL);
			  */
			  /* pips_internal_error("FI: C syntax problem...\n"); */
			  /* To avoid building to much useless stuff,
                             although it foes not gain much because of
                             parser structure: $2 is built before you
                             realize it's useless because of $1. */
			  if(string_undefined_p((yyvsp[(1) - (2)].string))) {
			    free_partial_signature((yyvsp[(2) - (2)].string));
			    (yyval.string) = string_undefined;
			  }
			  else
			    (yyval.string) = build_signature((yyvsp[(1) - (2)].string), (yyvsp[(2) - (2)].string), NULL);
			  PopTypedef();
			}
    break;

  case 243:
/* Line 1787 of yacc.c  */
#line 2085 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  PopTypedef();
			  (yyval.string) = (yyvsp[(1) - (1)].string);
			}
    break;

  case 244:
/* Line 1787 of yacc.c  */
#line 2090 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  //PopTypedef();
			  (yyval.string) = build_signature(new_lparen(), (yyvsp[(2) - (3)].string), new_rparen(), NULL);
			}
    break;

  case 245:
/* Line 1787 of yacc.c  */
#line 2099 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  (yyval.string) = build_signature((yyvsp[(1) - (2)].string), (yyvsp[(2) - (2)].string), NULL);
			}
    break;

  case 246:
/* Line 1787 of yacc.c  */
#line 2105 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  /* You do not need the formal parameter list */
			  /*
			  $$ = build_signature($1, new_lparen(), $3, new_rparen(),
					       $5, NULL);
			  */
			  free_partial_signature((yyvsp[(3) - (5)].string));
			  free_partial_signature((yyvsp[(5) - (5)].string));
			  /* $$ = build_signature($1, new_lparen(), new_rparen(), $5, NULL); */
			  (yyval.string) = build_signature((yyvsp[(1) - (5)].string), new_lparen(), new_rparen(), NULL);
			}
    break;

  case 247:
/* Line 1787 of yacc.c  */
#line 2117 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  (yyval.string) = build_signature((yyvsp[(1) - (3)].string), new_lparen(), new_rparen(), NULL);
			}
    break;

  case 248:
/* Line 1787 of yacc.c  */
#line 2124 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  (yyval.string) = new_signature((yyvsp[(1) - (1)].string));
			}
    break;

  case 249:
/* Line 1787 of yacc.c  */
#line 2128 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  (yyval.string) = build_signature((yyvsp[(1) - (3)].string), new_comma(), (yyvsp[(3) - (3)].string), NULL);
			}
    break;

  case 250:
/* Line 1787 of yacc.c  */
#line 2134 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    { (yyval.string) = new_empty(); }
    break;

  case 251:
/* Line 1787 of yacc.c  */
#line 2136 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  /* You want a comma-separated list of types, but... */
			  /* bad news: "int * pj" is broken as "int" for
                             decl_spec_list and "* pj" for old_pardef */
			  (yyval.string) = build_signature((yyvsp[(1) - (4)].string), (yyvsp[(2) - (4)].string), new_semicolon(),
					       new_ellipsis(), NULL);
			  /*
			  $$ = build_signature($1, $2, new_comma(),
					       new_ellipsis(), NULL);
			  */
			  PopTypedef();
			}
    break;

  case 252:
/* Line 1787 of yacc.c  */
#line 2149 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  (yyval.string) = build_signature((yyvsp[(1) - (4)].string), (yyvsp[(2) - (4)].string), new_semicolon(),
					       (yyvsp[(4) - (4)].string), NULL);
			  PopTypedef();
			}
    break;

  case 253:
/* Line 1787 of yacc.c  */
#line 2158 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  (yyval.string) = (yyvsp[(1) - (1)].string);
			}
    break;

  case 254:
/* Line 1787 of yacc.c  */
#line 2162 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  (yyval.string) = build_signature((yyvsp[(1) - (3)].string), new_comma(), (yyvsp[(3) - (3)].string), NULL);
			}
    break;

  case 255:
/* Line 1787 of yacc.c  */
#line 2166 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  csplit_parser_error("In old parameter definition\n");
			  (yyval.string) = string_undefined;
			}
    break;

  case 256:
/* Line 1787 of yacc.c  */
#line 2174 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  pips_debug(5, "TK_STAR attributes pointer_opt -> pointer\n");
			  pips_debug(5, "attributes: \"%s\", pointer_opt: \"%s\"\n", (yyvsp[(2) - (3)].string), (yyvsp[(3) - (3)].string));
			  (yyval.string) = build_signature(new_star(), (yyvsp[(2) - (3)].string), (yyvsp[(3) - (3)].string), NULL);
			}
    break;

  case 257:
/* Line 1787 of yacc.c  */
#line 2182 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    { (yyval.string) = new_empty(); }
    break;

  case 258:
/* Line 1787 of yacc.c  */
#line 2184 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    { (yyval.string) = (yyvsp[(1) - (1)].string); }
    break;

  case 259:
/* Line 1787 of yacc.c  */
#line 2189 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  PopTypedef();
			  (yyval.string) = build_signature((yyvsp[(1) - (2)].string), (yyvsp[(2) - (2)].string), NULL);
			}
    break;

  case 260:
/* Line 1787 of yacc.c  */
#line 2194 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  PopTypedef();
			  (yyval.string) = (yyvsp[(1) - (1)].string);
			}
    break;

  case 261:
/* Line 1787 of yacc.c  */
#line 2202 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  pips_debug(5, "pointer_opt abs_direct_decl attributes -> abstract_decl\n");
			  (yyval.string) = build_signature((yyvsp[(1) - (3)].string), (yyvsp[(2) - (3)].string), (yyvsp[(3) - (3)].string), NULL);
			}
    break;

  case 262:
/* Line 1787 of yacc.c  */
#line 2207 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  pips_debug(5, "pointer -> abstract_decl\n");
			  (yyval.string) = (yyvsp[(1) - (1)].string);
			}
    break;

  case 263:
/* Line 1787 of yacc.c  */
#line 2217 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  (yyval.string) = build_signature(new_lparen(), (yyvsp[(2) - (4)].string), (yyvsp[(3) - (4)].string), new_rparen(), NULL);
			}
    break;

  case 264:
/* Line 1787 of yacc.c  */
#line 2221 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  csplit_parser_error("Parse error: TK_LPAREN error TK_RPAREN\n");
			}
    break;

  case 265:
/* Line 1787 of yacc.c  */
#line 2226 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  (yyval.string) = build_signature((yyvsp[(1) - (4)].string), new_lbracket(), new_signature("IDoNotWantcomma_expression_opt"), new_rbracket(), NULL);
			}
    break;

  case 266:
/* Line 1787 of yacc.c  */
#line 2231 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  (yyval.string) = build_signature((yyvsp[(1) - (4)].string), (yyvsp[(2) - (4)].string), (yyvsp[(3) - (4)].string), new_rparen(), NULL);
			}
    break;

  case 267:
/* Line 1787 of yacc.c  */
#line 2238 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  (yyval.string) = (yyvsp[(1) - (1)].string);
			}
    break;

  case 268:
/* Line 1787 of yacc.c  */
#line 2241 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    { (yyval.string) = new_empty(); }
    break;

  case 269:
/* Line 1787 of yacc.c  */
#line 2246 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			}
    break;

  case 270:
/* Line 1787 of yacc.c  */
#line 2251 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  pips_debug(5, "decl_spec_list declarator->function_def_start\n");
			  /* let's use a pretty limited stack... */
			  if(string_undefined_p(csplit_current_function_name)) {
			    csplit_current_function_name =
			      csplit_current_function_name2;
			    csplit_current_function_name2 = string_undefined;
			  }

			  pips_assert("A temptative function name is available",
				      !string_undefined_p(csplit_current_function_name));
			  pips_assert("No definite function name is available",
				      string_undefined_p(csplit_definite_function_name));
			  csplit_definite_function_name
			    = strdup(csplit_current_function_name);
			  pips_debug(5, "Rule 1: Function declaration is located between line %d and line %d\n", get_csplit_current_beginning(), csplit_line_number);
			  csplit_is_function = 1; /* function's declaration */

			  current_function_is_static_p = csplit_is_static_p;
			  csplit_is_static_p = false;
			  csplit_definite_function_signature
			    = simplify_signature(build_signature((yyvsp[(1) - (2)].string), (yyvsp[(2) - (2)].string), NULL));
			  pips_debug(1, "Signature for function \"%s\": \"%s\"\n\n",
				     csplit_definite_function_name,
				     csplit_definite_function_signature);
			  PopTypedef();
			}
    break;

  case 271:
/* Line 1787 of yacc.c  */
#line 2280 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  /* The signature obtained here must be
                             post-processed. The declaration list after
                             the empty parameter list could be entirely
                             dropped or converted into a type list. But
                             beware of parameters declared together or
                             declared in another order. Note that we could
                             keep the parameter list between the
                             parentheses and fetch the associated
                             types. */
			  pips_debug(5, "decl_spec_list old_proto_decl->function_def_start");
			  csplit_definite_function_name
			    = strdup(csplit_current_function_name);
			  pips_debug(5, "Rule 2: Function declaration is located between line %d and line %d\n", get_csplit_current_beginning(), csplit_line_number);
			  csplit_is_function = 1; /* function's declaration */
			  current_function_is_static_p = csplit_is_static_p;
			  csplit_is_static_p = false;
			  csplit_definite_function_signature
			    = simplify_signature(build_signature((yyvsp[(1) - (2)].string), (yyvsp[(2) - (2)].string), NULL));
			  pips_debug(1, "Signature for function \"%s\": \"%s\"\n\n",
				     csplit_definite_function_name,
				     csplit_definite_function_signature);
			  PopTypedef();
			}
    break;

  case 272:
/* Line 1787 of yacc.c  */
#line 2306 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  pips_debug(5, "TK_IDENT parameter_list_startscope rest_par_list TK_RPAREN->function_def_start");
			  /* Create the current function */
			  pips_debug(5, "Rule 3: Function declaration of \"%s\" is located between line %d and line %d\n", (yyvsp[(1) - (4)].string), get_csplit_current_beginning(), csplit_line_number);
			  /* current_function_name = strdup($1); */
			  csplit_definite_function_name = strdup((yyvsp[(1) - (4)].string));
			  csplit_is_function = 1; /* function's declaration */
			  current_function_is_static_p = csplit_is_static_p;
			  csplit_is_static_p = false;

			  csplit_definite_function_signature
			    = simplify_signature
			    (build_signature((yyvsp[(1) - (4)].string), (yyvsp[(2) - (4)].string), (yyvsp[(3) - (4)].string), new_rparen(), NULL));
			  pips_debug(1, "Signature for function %s: %s\n\n",
				     csplit_current_function_name,
				     csplit_definite_function_signature);
			}
    break;

  case 273:
/* Line 1787 of yacc.c  */
#line 2325 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  pips_debug(5, "TK_IDENT TK_LPAREN old_parameter_list_ne TK_RPAREN old_pardef_list->function_def_start");
			  pips_debug(5, "Rule 4: Function \"%s\" declaration is located between line %d and line %d\n",
				     (yyvsp[(1) - (5)].string),
				     get_csplit_current_beginning(),
				     csplit_line_number);
			  csplit_definite_function_name = strdup((yyvsp[(1) - (5)].string));
			  csplit_is_function = 1; /* function's declaration */
			  current_function_is_static_p = csplit_is_static_p;
			  csplit_is_static_p = false;

			  free_partial_signature((yyvsp[(3) - (5)].string));
			  free_partial_signature((yyvsp[(5) - (5)].string));
			  csplit_definite_function_signature
			    = simplify_signature
			    (build_signature((yyvsp[(1) - (5)].string), new_lparen(), new_rparen(), NULL));
			  pips_debug(1, "Signature for function %s: %s\n\n",
				     csplit_current_function_name,
				     csplit_definite_function_signature);
			}
    break;

  case 274:
/* Line 1787 of yacc.c  */
#line 2347 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  pips_debug(5, "TK_IDENT TK_LPAREN TK_RPAREN->function_def_start");
			  /* MakeCurrentFunction*/
			  csplit_is_function = 5; /* function's declaration */
			  pips_debug(5, "Rule 5: Function \"%s\" declaration is located between line %d and line %d\n",
				     (yyvsp[(1) - (3)].string),
				     get_csplit_current_beginning(),
				     csplit_line_number);
			  pips_internal_error("Not implemented yet");
			}
    break;

  case 275:
/* Line 1787 of yacc.c  */
#line 2362 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    { (yyval.string) = new_empty(); }
    break;

  case 276:
/* Line 1787 of yacc.c  */
#line 2364 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    { (yyval.string) = build_signature((yyvsp[(1) - (2)].string), (yyvsp[(2) - (2)].string), NULL); }
    break;

  case 277:
/* Line 1787 of yacc.c  */
#line 2371 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    { (yyval.string) = new_empty(); }
    break;

  case 278:
/* Line 1787 of yacc.c  */
#line 2373 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    { (yyval.string) = build_signature((yyvsp[(1) - (2)].string), (yyvsp[(2) - (2)].string), NULL); }
    break;

  case 279:
/* Line 1787 of yacc.c  */
#line 2375 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
/* skip the asm declaration ... this is relatively dangerous because it can change the symbol name. Yet it is ok to skip it at split level */
#if 0
			  free_partial_signature((yyvsp[(5) - (5)].string));
			  csplit_parser_error("ASM extensions not implemented\n");
			  (yyval.string) = string_undefined;
#else
                        { (yyval.string) = build_signature((yyvsp[(5) - (5)].string), NULL, NULL); }

#endif
			}
    break;

  case 280:
/* Line 1787 of yacc.c  */
#line 2390 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  (yyval.string) = build_signature(new_signature("attribute"), new_lparen(), (yyvsp[(3) - (4)].string),
					       new_rparen(), NULL);
			}
    break;

  case 281:
/* Line 1787 of yacc.c  */
#line 2395 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  (yyval.string) = build_signature(new_signature("decl_spec"), (yyvsp[(2) - (2)].string), NULL);
			}
    break;

  case 282:
/* Line 1787 of yacc.c  */
#line 2399 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  (yyval.string) = new_signature("msattr");
			}
    break;

  case 283:
/* Line 1787 of yacc.c  */
#line 2404 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  (yyval.string) = new_signature("const");
			}
    break;

  case 284:
/* Line 1787 of yacc.c  */
#line 2408 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  (yyval.string) = new_signature("restrict");
			}
    break;

  case 285:
/* Line 1787 of yacc.c  */
#line 2412 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  (yyval.string) = new_signature("volatile");
			}
    break;

  case 286:
/* Line 1787 of yacc.c  */
#line 2416 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  (yyval.string) = new_signature("static");
			}
    break;

  case 288:
/* Line 1787 of yacc.c  */
#line 2426 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    { }
    break;

  case 289:
/* Line 1787 of yacc.c  */
#line 2428 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    { }
    break;

  case 290:
/* Line 1787 of yacc.c  */
#line 2430 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    { }
    break;

  case 291:
/* Line 1787 of yacc.c  */
#line 2432 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    { }
    break;

  case 292:
/* Line 1787 of yacc.c  */
#line 2434 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    { }
    break;

  case 293:
/* Line 1787 of yacc.c  */
#line 2436 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    { }
    break;

  case 294:
/* Line 1787 of yacc.c  */
#line 2438 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    { }
    break;

  case 295:
/* Line 1787 of yacc.c  */
#line 2440 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    { }
    break;

  case 296:
/* Line 1787 of yacc.c  */
#line 2442 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  free_partial_signature((yyvsp[(2) - (2)].string));
			}
    break;

  case 297:
/* Line 1787 of yacc.c  */
#line 2446 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    { }
    break;

  case 298:
/* Line 1787 of yacc.c  */
#line 2449 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  free_partial_signature((yyvsp[(2) - (2)].string));
			}
    break;

  case 299:
/* Line 1787 of yacc.c  */
#line 2453 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    { }
    break;

  case 300:
/* Line 1787 of yacc.c  */
#line 2455 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  free_partial_signature((yyvsp[(2) - (2)].string));
			}
    break;

  case 301:
/* Line 1787 of yacc.c  */
#line 2459 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    { free_partial_signature((yyvsp[(2) - (2)].string));}
    break;

  case 302:
/* Line 1787 of yacc.c  */
#line 2461 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    { free_partial_signature((yyvsp[(2) - (2)].string));}
    break;

  case 303:
/* Line 1787 of yacc.c  */
#line 2464 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    { free_partial_signature((yyvsp[(2) - (2)].string));}
    break;

  case 304:
/* Line 1787 of yacc.c  */
#line 2466 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    { free_partial_signature((yyvsp[(2) - (2)].string));}
    break;

  case 305:
/* Line 1787 of yacc.c  */
#line 2468 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    { free_partial_signature((yyvsp[(2) - (2)].string));}
    break;

  case 306:
/* Line 1787 of yacc.c  */
#line 2470 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    { }
    break;

  case 307:
/* Line 1787 of yacc.c  */
#line 2472 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    { }
    break;

  case 308:
/* Line 1787 of yacc.c  */
#line 2474 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    { free_partial_signature((yyvsp[(3) - (3)].string));}
    break;

  case 309:
/* Line 1787 of yacc.c  */
#line 2476 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    { }
    break;

  case 310:
/* Line 1787 of yacc.c  */
#line 2478 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    { }
    break;

  case 311:
/* Line 1787 of yacc.c  */
#line 2480 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    { }
    break;

  case 312:
/* Line 1787 of yacc.c  */
#line 2482 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    { }
    break;

  case 313:
/* Line 1787 of yacc.c  */
#line 2484 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
		        }
    break;

  case 314:
/* Line 1787 of yacc.c  */
#line 2487 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    { }
    break;

  case 315:
/* Line 1787 of yacc.c  */
#line 2489 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    { }
    break;

  case 316:
/* Line 1787 of yacc.c  */
#line 2491 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    { }
    break;

  case 317:
/* Line 1787 of yacc.c  */
#line 2493 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    { }
    break;

  case 318:
/* Line 1787 of yacc.c  */
#line 2495 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    { }
    break;

  case 319:
/* Line 1787 of yacc.c  */
#line 2497 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    { }
    break;

  case 320:
/* Line 1787 of yacc.c  */
#line 2499 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    { }
    break;

  case 321:
/* Line 1787 of yacc.c  */
#line 2501 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    { }
    break;

  case 322:
/* Line 1787 of yacc.c  */
#line 2503 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    { }
    break;

  case 323:
/* Line 1787 of yacc.c  */
#line 2505 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    { }
    break;

  case 324:
/* Line 1787 of yacc.c  */
#line 2507 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    { }
    break;

  case 325:
/* Line 1787 of yacc.c  */
#line 2509 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    { }
    break;

  case 326:
/* Line 1787 of yacc.c  */
#line 2511 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    { }
    break;

  case 328:
/* Line 1787 of yacc.c  */
#line 2516 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    { }
    break;

  case 329:
/* Line 1787 of yacc.c  */
#line 2518 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    { }
    break;

  case 330:
/* Line 1787 of yacc.c  */
#line 2520 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    { }
    break;

  case 331:
/* Line 1787 of yacc.c  */
#line 2524 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  csplit_parser_error("Attribute lists are not supported yet.\n");
			  (yyval.string) = build_signature(new_lparen(), new_signature("IDoNotWantAttrListne"), new_rparen(), NULL);
			}
    break;

  case 332:
/* Line 1787 of yacc.c  */
#line 2529 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {
			  csplit_parser_error("Near attribute list ne");
			  (yyval.string) = string_undefined;
			}
    break;

  case 333:
/* Line 1787 of yacc.c  */
#line 2537 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    { }
    break;

  case 334:
/* Line 1787 of yacc.c  */
#line 2539 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    { }
    break;

  case 335:
/* Line 1787 of yacc.c  */
#line 2541 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    { }
    break;

  case 336:
/* Line 1787 of yacc.c  */
#line 2545 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    { }
    break;

  case 337:
/* Line 1787 of yacc.c  */
#line 2547 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    { }
    break;

  case 338:
/* Line 1787 of yacc.c  */
#line 2551 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    { }
    break;

  case 339:
/* Line 1787 of yacc.c  */
#line 2553 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    {  }
    break;

  case 340:
/* Line 1787 of yacc.c  */
#line 2557 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    { }
    break;

  case 341:
/* Line 1787 of yacc.c  */
#line 2559 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    { }
    break;

  case 342:
/* Line 1787 of yacc.c  */
#line 2563 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    { }
    break;

  case 343:
/* Line 1787 of yacc.c  */
#line 2565 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    { }
    break;

  case 344:
/* Line 1787 of yacc.c  */
#line 2569 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    { free_partial_signature((yyvsp[(3) - (4)].string));}
    break;

  case 345:
/* Line 1787 of yacc.c  */
#line 2571 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    { }
    break;

  case 346:
/* Line 1787 of yacc.c  */
#line 2575 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    { }
    break;

  case 347:
/* Line 1787 of yacc.c  */
#line 2577 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    { }
    break;

  case 348:
/* Line 1787 of yacc.c  */
#line 2581 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    { }
    break;

  case 349:
/* Line 1787 of yacc.c  */
#line 2583 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    { }
    break;

  case 350:
/* Line 1787 of yacc.c  */
#line 2587 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    { }
    break;

  case 351:
/* Line 1787 of yacc.c  */
#line 2589 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"
    { }
    break;


/* Line 1787 of yacc.c  */
#line 6424 "y.tab.c"
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
#line 2592 "/home/dounia/MYPIPS/prod/pips/src/Libs/preprocessor/splitc.y"


