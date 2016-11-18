/* A Bison parser, made by GNU Bison 2.6.1.  */

/* Bison interface for Yacc-like parsers in C
   
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

#ifndef PIPSMAKE_Y_TAB_H
# define PIPSMAKE_Y_TAB_H
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int pipsmake_debug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     PROGRAM = 258,
     MODULE = 259,
     MAIN = 260,
     COMMON = 261,
     TK_CALLEES = 262,
     CALLERS = 263,
     ALL = 264,
     SELECT = 265,
     COMPILATION_UNIT = 266,
     REQUIRED = 267,
     PRODUCED = 268,
     MODIFIED = 269,
     PRESERVED = 270,
     PRE_TRANSFORMATION = 271,
     POST_TRANSFORMATION = 272,
     DOT = 273,
     NAME = 274
   };
#endif
/* Tokens.  */
#define PROGRAM 258
#define MODULE 259
#define MAIN 260
#define COMMON 261
#define TK_CALLEES 262
#define CALLERS 263
#define ALL 264
#define SELECT 265
#define COMPILATION_UNIT 266
#define REQUIRED 267
#define PRODUCED 268
#define MODIFIED 269
#define PRESERVED 270
#define PRE_TRANSFORMATION 271
#define POST_TRANSFORMATION 272
#define DOT 273
#define NAME 274



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 2049 of yacc.c  */
#line 86 "readmakefile.y"

	string name;
	owner owner;
	virtual_resource virtual;
	cons *list;
	rule rule;
	int tag;


/* Line 2049 of yacc.c  */
#line 105 "y.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE pipsmake_lval;

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int pipsmake_parse (void *YYPARSE_PARAM);
#else
int pipsmake_parse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int pipsmake_parse (void);
#else
int pipsmake_parse ();
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !PIPSMAKE_Y_TAB_H  */
