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
/* Line 2049 of yacc.c  */
#line 500 "tp_yacc.y"

  int status;
  int ival;
  string name;
  res_or_rule rn;
  gen_array_t array;


/* Line 2049 of yacc.c  */
#line 168 "y.tab.h"
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
