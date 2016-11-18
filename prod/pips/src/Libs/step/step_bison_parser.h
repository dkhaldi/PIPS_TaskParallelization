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

#ifndef STEP_LEXER_STEP_BISON_PARSER_H
# define STEP_LEXER_STEP_BISON_PARSER_H
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int step_lexerdebug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     TK_EOL = 258,
     TK_ERROR = 259,
     TK_LPAREN = 260,
     TK_RPAREN = 261,
     TK_COLON = 262,
     TK_COMMA = 263,
     TK_IDENT = 264,
     TK_COMMENT = 265,
     TK_OPERATOR = 266,
     TK_RAW = 267,
     TK_OMP_PRAGMA = 268,
     TK_OMP_PARALLEL = 269,
     TK_OMP_LOOP = 270,
     TK_OMP_END = 271,
     TK_OMP_BARRIER = 272,
     TK_OMP_MASTER = 273,
     TK_OMP_SINGLE = 274,
     TK_OMP_THREADPRIVATE = 275,
     TK_OMP_SHARED = 276,
     TK_OMP_PRIVATE = 277,
     TK_OMP_NOWAIT = 278,
     TK_OMP_REDUCTION = 279,
     TK_OMP_DEFAULT = 280,
     TK_OMP_COPYIN = 281,
     TK_OMP_FIRSTPRIVATE = 282,
     TK_OMP_SCHEDULE = 283,
     TK_STEP_PRAGMA = 284,
     TK_STEP_TRANSFORMATION = 285
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 2049 of yacc.c  */
#line 36 "step_bison_parser.y"

  char* string;
  cons * liste;
  int integer;
  step_directive step_directive;
  step_clause step_clause;


/* Line 2049 of yacc.c  */
#line 96 "step_bison_parser.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE step_lexerlval;

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int step_lexerparse (void *YYPARSE_PARAM);
#else
int step_lexerparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int step_lexerparse (void);
#else
int step_lexerparse ();
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !STEP_LEXER_STEP_BISON_PARSER_H  */
