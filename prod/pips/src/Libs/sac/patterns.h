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

#ifndef PATTERNS_YY_PATTERNS_H
# define PATTERNS_YY_PATTERNS_H
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int patterns_yydebug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     UNKNOWN_TOK = 258,
     REFERENCE_TOK = 259,
     QI_REF_TOK = 260,
     HI_REF_TOK = 261,
     SI_REF_TOK = 262,
     DI_REF_TOK = 263,
     SF_REF_TOK = 264,
     DF_REF_TOK = 265,
     SC_REF_TOK = 266,
     DC_REF_TOK = 267,
     LOG_REF_TOK = 268,
     CONSTANT_TOK = 269,
     ASSIGN_OPERATOR_TOK = 270,
     PLUS_OPERATOR_TOK = 271,
     MINUS_OPERATOR_TOK = 272,
     UNARY_MINUS_OPERATOR_TOK = 273,
     MULTIPLY_OPERATOR_TOK = 274,
     MULADD_OPERATOR_TOK = 275,
     DIVIDE_OPERATOR_TOK = 276,
     INVERSE_OPERATOR_TOK = 277,
     POWER_OPERATOR_TOK = 278,
     MODULO_OPERATOR_TOK = 279,
     MIN_OPERATOR_TOK = 280,
     COS_OPERATOR_TOK = 281,
     SIN_OPERATOR_TOK = 282,
     MIN0_OPERATOR_TOK = 283,
     AMIN1_OPERATOR_TOK = 284,
     DMIN1_OPERATOR_TOK = 285,
     MAX_OPERATOR_TOK = 286,
     MAX0_OPERATOR_TOK = 287,
     AMAX1_OPERATOR_TOK = 288,
     DMAX1_OPERATOR_TOK = 289,
     ABS_OPERATOR_TOK = 290,
     IABS_OPERATOR_TOK = 291,
     DABS_OPERATOR_TOK = 292,
     CABS_OPERATOR_TOK = 293,
     AND_OPERATOR_TOK = 294,
     OR_OPERATOR_TOK = 295,
     NOT_OPERATOR_TOK = 296,
     NON_EQUAL_OPERATOR_TOK = 297,
     EQUIV_OPERATOR_TOK = 298,
     NON_EQUIV_OPERATOR_TOK = 299,
     TRUE_OPERATOR_TOK = 300,
     FALSE_OPERATOR_TOK = 301,
     GREATER_OR_EQUAL_OPERATOR_TOK = 302,
     GREATER_THAN_OPERATOR_TOK = 303,
     LESS_OR_EQUAL_OPERATOR_TOK = 304,
     LESS_THAN_OPERATOR_TOK = 305,
     EQUAL_OPERATOR_TOK = 306,
     PHI_TOK = 307,
     INTEGER_TOK = 308,
     FLOAT_TOK = 309,
     IDENTIFIER_TOK = 310
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 2049 of yacc.c  */
#line 56 "tmp.y"

      intptr_t tokenId;
      intptr_t typeId;
      list tokenList;
      list typeList;

      patternArg argument;
      list argsList;

      int iVal;
      float fVal;
      char * strVal;

      opcode opVal;
      list opcodesList;

      list mappingsList;


/* Line 2049 of yacc.c  */
#line 132 "patterns.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE patterns_yylval;

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int patterns_yyparse (void *YYPARSE_PARAM);
#else
int patterns_yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int patterns_yyparse (void);
#else
int patterns_yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !PATTERNS_YY_PATTERNS_H  */
