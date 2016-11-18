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
/* Line 2049 of yacc.c  */
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


/* Line 2049 of yacc.c  */
#line 309 "y.tab.h"
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
