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

#ifndef SYN_Y_TAB_H
# define SYN_Y_TAB_H
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int syn_debug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     TK_ASSIGN = 258,
     TK_BACKSPACE = 259,
     TK_BLANK = 260,
     TK_BLOCKDATA = 261,
     TK_BUFFERIN = 262,
     TK_BUFFEROUT = 263,
     TK_CALL = 264,
     TK_CHARACTER = 265,
     TK_CLOSE = 266,
     TK_COMMON = 267,
     TK_COMPLEX = 268,
     TK_CONTINUE = 269,
     TK_CYCLE = 270,
     TK_DATA = 271,
     TK_DIMENSION = 272,
     TK_DOUBLEPRECISION = 273,
     TK_DOUBLECOMPLEX = 274,
     TK_DO = 275,
     TK_ELSEIF = 276,
     TK_ELSE = 277,
     TK_ENDFILE = 278,
     TK_ENDDO = 279,
     TK_ENDIF = 280,
     TK_END = 281,
     TK_ENTRY = 282,
     TK_EQUIVALENCE = 283,
     TK_EXIT = 284,
     TK_EXTERNAL = 285,
     TK_FORMAT = 286,
     TK_FUNCTION = 287,
     TK_GOTO = 288,
     TK_IF = 289,
     TK_IMPLICIT = 290,
     TK_INCLUDE = 291,
     TK_INQUIRE = 292,
     TK_INTEGER = 293,
     TK_INTRINSIC = 294,
     TK_IOSTAT = 295,
     TK_LOGICAL = 296,
     TK_OPEN = 297,
     TK_PARAMETER = 298,
     TK_PAUSE = 299,
     TK_POINTER = 300,
     TK_PRINT = 301,
     TK_PROGRAM = 302,
     TK_READ = 303,
     TK_REAL = 304,
     TK_RETURN = 305,
     TK_REWIND = 306,
     TK_SAVE = 307,
     TK_STATIC = 308,
     TK_STOP = 309,
     TK_SUBROUTINE = 310,
     TK_THEN = 311,
     TK_TO = 312,
     TK_WHILE = 313,
     TK_WRITE = 314,
     TK_INOUT = 315,
     TK_IN = 316,
     TK_OUT = 317,
     TK_AND = 318,
     TK_EQ = 319,
     TK_EQV = 320,
     TK_GE = 321,
     TK_GT = 322,
     TK_LE = 323,
     TK_LT = 324,
     TK_NE = 325,
     TK_NEQV = 326,
     TK_NOT = 327,
     TK_OR = 328,
     TK_TRUE = 329,
     TK_FALSE = 330,
     TK_NAME = 331,
     TK_ICON = 332,
     TK_SCON = 333,
     TK_RCON = 334,
     TK_DCON = 335,
     TK_MINUS = 336,
     TK_PLUS = 337,
     TK_SLASH = 338,
     TK_STAR = 339,
     TK_POWER = 340,
     TK_LPAR = 341,
     TK_RPAR = 342,
     TK_COMMA = 343,
     TK_COLON = 344,
     TK_EQUALS = 345,
     TK_CURRENCY = 346,
     TK_CONCAT = 347,
     TK_EOS = 348,
     TK_IOLPAR = 349
   };
#endif
/* Tokens.  */
#define TK_ASSIGN 258
#define TK_BACKSPACE 259
#define TK_BLANK 260
#define TK_BLOCKDATA 261
#define TK_BUFFERIN 262
#define TK_BUFFEROUT 263
#define TK_CALL 264
#define TK_CHARACTER 265
#define TK_CLOSE 266
#define TK_COMMON 267
#define TK_COMPLEX 268
#define TK_CONTINUE 269
#define TK_CYCLE 270
#define TK_DATA 271
#define TK_DIMENSION 272
#define TK_DOUBLEPRECISION 273
#define TK_DOUBLECOMPLEX 274
#define TK_DO 275
#define TK_ELSEIF 276
#define TK_ELSE 277
#define TK_ENDFILE 278
#define TK_ENDDO 279
#define TK_ENDIF 280
#define TK_END 281
#define TK_ENTRY 282
#define TK_EQUIVALENCE 283
#define TK_EXIT 284
#define TK_EXTERNAL 285
#define TK_FORMAT 286
#define TK_FUNCTION 287
#define TK_GOTO 288
#define TK_IF 289
#define TK_IMPLICIT 290
#define TK_INCLUDE 291
#define TK_INQUIRE 292
#define TK_INTEGER 293
#define TK_INTRINSIC 294
#define TK_IOSTAT 295
#define TK_LOGICAL 296
#define TK_OPEN 297
#define TK_PARAMETER 298
#define TK_PAUSE 299
#define TK_POINTER 300
#define TK_PRINT 301
#define TK_PROGRAM 302
#define TK_READ 303
#define TK_REAL 304
#define TK_RETURN 305
#define TK_REWIND 306
#define TK_SAVE 307
#define TK_STATIC 308
#define TK_STOP 309
#define TK_SUBROUTINE 310
#define TK_THEN 311
#define TK_TO 312
#define TK_WHILE 313
#define TK_WRITE 314
#define TK_INOUT 315
#define TK_IN 316
#define TK_OUT 317
#define TK_AND 318
#define TK_EQ 319
#define TK_EQV 320
#define TK_GE 321
#define TK_GT 322
#define TK_LE 323
#define TK_LT 324
#define TK_NE 325
#define TK_NEQV 326
#define TK_NOT 327
#define TK_OR 328
#define TK_TRUE 329
#define TK_FALSE 330
#define TK_NAME 331
#define TK_ICON 332
#define TK_SCON 333
#define TK_RCON 334
#define TK_DCON 335
#define TK_MINUS 336
#define TK_PLUS 337
#define TK_SLASH 338
#define TK_STAR 339
#define TK_POWER 340
#define TK_LPAR 341
#define TK_RPAR 342
#define TK_COMMA 343
#define TK_COLON 344
#define TK_EQUALS 345
#define TK_CURRENCY 346
#define TK_CONCAT 347
#define TK_EOS 348
#define TK_IOLPAR 349



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 2049 of yacc.c  */
#line 358 "yacc.in"

	basic basic;
	chain chain;
        char character;
	cons * liste;
	dataval dataval;
	datavar datavar;
	dimension dimension;
	entity entity;
	expression expression;
	instruction instruction;
	int integer;
	range range;
	string string;
	syntax syntax;
	tag tag;
	type type; 
	value value;


/* Line 2049 of yacc.c  */
#line 266 "y.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE syn_lval;

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int syn_parse (void *YYPARSE_PARAM);
#else
int syn_parse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int syn_parse (void);
#else
int syn_parse ();
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !SYN_Y_TAB_H  */
