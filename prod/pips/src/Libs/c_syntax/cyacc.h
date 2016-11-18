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
/* Line 2049 of yacc.c  */
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


/* Line 2049 of yacc.c  */
#line 188 "cyacc.tab.h"
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
