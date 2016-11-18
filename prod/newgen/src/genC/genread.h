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
/* Line 2049 of yacc.c  */
#line 108 "read.y"

  gen_chunk chunk ;
  gen_chunk *chunkp ;
  cons *consp ;
  intptr_t val ;
  char * s;
  double d;
  char c;


/* Line 2049 of yacc.c  */
#line 118 "y.tab.h"
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
