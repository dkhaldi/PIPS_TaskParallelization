/* Warning! Do not modify this file that is automatically generated! */
/* Modify src/Libs/tpips/tpips-local.h instead, to add your own modifications. */

/* header file built by cproto */

#ifndef  tpips_header_included
#define  tpips_header_included
/*

  $Id: tpips-local.h 23065 2016-03-02 09:05:50Z coelho $

  Copyright 1989-2016 MINES ParisTech

  This file is part of PIPS.

  PIPS is free software: you can redistribute it and/or modify it
  under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  any later version.

  PIPS is distributed in the hope that it will be useful, but WITHOUT ANY
  WARRANTY; without even the implied warranty of MERCHANTABILITY or
  FITNESS FOR A PARTICULAR PURPOSE.

  See the GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with PIPS.  If not, see <http://www.gnu.org/licenses/>.

*/
/* Storage for arguments of tpips commands. E.g.
 display PRINTED_FILE[MOD_A, MOD_B]
 display PRINTED_FILE
*/
typedef struct {
  gen_array_t the_owners; /* MOD_A, MOD_B, %ALL after expansion, default
                             value can be PROGRAM or current_module */
  string the_name; /* e.g. PRINTED_FILE */
} res_or_rule;

extern int tp_lex();
extern int tp_parse();
extern void tp_error();
extern void tp_init_lex();
extern void tp_begin_key();
extern void tp_begin_fname();

extern FILE * tp_in;
#ifdef FLEX_SCANNER
extern void tp_restart(FILE *);
#endif

#define TPIPS_PRIMARY_PROMPT 	"tpips> " /* prompt for readline  */
#define TPIPS_REQUEST_PROMPT    "tpips-request> "
#define TPIPS_SECONDARY_PROMPT 	"> "
#define TPIPS_CONTINUATION_CHAR '\\'

#define TPIPS_HISTENV "TPIPS_HISTORY"	/* history file env variable */
#define TPIPS_HISTORY_LENGTH 100	/* max length of history file */
#define TPIPS_COMMENT_PREFIX '#'	/* comment prefix */
#define TPIPS_HISTORY ".tpips.history" 	/* default history file */

#define SHELL_ESCAPE "shell" 		/* ! used for history reference */
#define CHANGE_DIR   "cd"
#define TPIPS_SOURCE "source"

#define SET_ENV	     "setenv"
#define GET_ENV	     "getenv"

#define SET_PROP     "setproperty"
#define GET_PROP     "getproperty"

#define QUIT         "quit"
#define HELP         "help"
/* macro ECHO is reserved by flex */
#define ECHO_N         "echo"

#define skip_blanks(str) \
  while (*str && (*str==' ' || *str=='\t' || *str=='\n')) str++

// redundant declarations to help bootstrap?
extern bool tpips_execution_mode;
extern bool tpips_is_interactive;
extern bool jpips_is_running;
extern bool tpips_init_done;
/* tpips.c */
extern bool tpips_execution_mode;
extern bool tpips_is_interactive;
extern string tpips_current_file_name(void);
extern int tpips_current_line_number(void);
extern void tpips_next_line(void);
extern int tpips_current_line(void);
extern string tpips_current_name(void);
extern bool tpips_behaves_like_a_shell(void);
extern bool jpips_is_running;
extern FILE *jpips_out_file(void);
extern void jpips_begin_tag(string /*s*/);
extern void jpips_add_tag(string /*s*/);
extern void jpips_end_tag(void);
extern void jpips_tag(string /*s*/);
extern void jpips_tag2(string /*s1*/, string /*s2*/);
extern void jpips_done(void);
extern void jpips_string(const char */*a_message_format*/, va_list /*some_arguments*/);
extern void jpips_printf(const string /*format*/, ...);
extern char **get_module_names(void);
extern void tpips_internal_error(const char */*calling_function_name*/, const char */*a_message_format*/, ...);
extern void tpips_help(string /*line*/);
extern void tpips_close(void);
extern bool tpips_init_done;
extern bool consistency_enforced_p;
extern void tpips_init(void);
extern void tpips_process_a_file(FILE */*file*/, string /*name*/, bool /*use_rl*/);
extern int tpips_main(int /*argc*/, char */*argv*/[]);
extern bool phase_name_p(string /*name*/);
extern bool resource_name_p(string /*name*/);
extern bool property_name_p(string /*name*/);
/* wrapper.c */
extern void tpips_wrapper(void);
/* revisions.c */
#endif /*  tpips_header_included */
