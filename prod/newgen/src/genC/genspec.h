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

#ifndef GENSPEC_Y_TAB_H
# define GENSPEC_Y_TAB_H
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int genspec_debug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     COMMA = 258,
     COLUMN = 259,
     SEMI_COLUMN = 260,
     AND = 261,
     OR = 262,
     ARROW = 263,
     STAR = 264,
     LB = 265,
     RB = 266,
     LR = 267,
     RR = 268,
     EQUAL = 269,
     FROM = 270,
     GRAM_EXTERNAL = 271,
     GRAM_IMPORT = 272,
     TABULATED = 273,
     PERSISTANT = 274,
     IDENT = 275,
     GRAM_FILE = 276,
     GRAM_INT = 277
   };
#endif
/* Tokens.  */
#define COMMA 258
#define COLUMN 259
#define SEMI_COLUMN 260
#define AND 261
#define OR 262
#define ARROW 263
#define STAR 264
#define LB 265
#define RB 266
#define LR 267
#define RR 268
#define EQUAL 269
#define FROM 270
#define GRAM_EXTERNAL 271
#define GRAM_IMPORT 272
#define TABULATED 273
#define PERSISTANT 274
#define IDENT 275
#define GRAM_FILE 276
#define GRAM_INT 277



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 2049 of yacc.c  */
#line 81 "spec.y"

  union domain *domain ;
  struct domainlist *domainlist ;
  struct namelist *namelist ;
  struct intlist *intlist ;
  char *name ;
  int val ;


/* Line 2049 of yacc.c  */
#line 111 "y.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE genspec_lval;

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int genspec_parse (void *YYPARSE_PARAM);
#else
int genspec_parse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int genspec_parse (void);
#else
int genspec_parse ();
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !GENSPEC_Y_TAB_H  */
