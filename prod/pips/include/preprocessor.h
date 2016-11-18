/* Warning! Do not modify this file that is automatically generated! */
/* Modify src/Libs/preprocessor/preprocessor-local.h instead, to add your own modifications. */

/* header file built by cproto */

#ifndef  preprocessor_header_included
#define  preprocessor_header_included
/*

  $Id: preprocessor-local.h 23065 2016-03-02 09:05:50Z coelho $

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
/* Preprocessing and splitting of Fortran and C files
 */

/* the name of the environment variable where source files are searched for. */
#define SRCPATH "PIPS_SRCPATH"

/* pre-processor and added options from environment
 */
#define CPP_PIPS_ENV		"PIPS_CPP"
#define CPP_PIPS_OPTIONS_ENV 	"PIPS_CPP_FLAGS"
#define FPP_PIPS_ENV		"PIPS_FPP"
#define FPP_PIPS_OPTIONS_ENV 	"PIPS_FPP_FLAGS"

/* default preprocessor and basic options
 * -C: do not discard comments...
 * -P: inhibit linemakers (# 1 "file.c")
 * -ffreestanding: ignore "stdc-predef.h"
 */
// alternative values: "gcc -E -C"
// force c99 for gcc/clang validation compatibility
#define CPP_CPP			"cpp -C -std=c99"
/* #define CPP_CPPFLAGS		" -P -D__PIPS__ -D__HPFC__ " */
/* -U__GNUC__ seems to be still useful to avoid spoiling the libC files
    with too many GCC extensions: */
#define CPP_CPPFLAGS		" -D__PIPS__ -D__HPFC__ -U__GNUC__ "

/** The preprocessor to use for Fortran files.

    Alternative values: "gcc -E -C" or "fpp". The issue with cpp or gcc -E
    is that they don't undestand Fortran and chokes on unbalanced strings
    in Fortran comments and so on.
*/
#define FPP_CPP			"gfortran -E"

/** The default preprocessor flags to use with Fortran files */
#define FPP_CPPFLAGS		" -P -D__PIPS__ -D__HPFC__ "

#define DEFAULT_PIPS_FLINT "gfortran -Wall"

/* See necessary definitions in pipsmake-rc.tex */
#define DEFAULT_PIPS_CC "gcc -std=c99 -D__PIPS__ -D__HPFC__ -U__GNUC__ "
#define DEFAULT_PIPS_CC_FLAGS " -Wall "

/* Define some functions from the .l or .y since cproto cannot dig them out: */
void MakeTypedefStack();
void ResetTypedefStack();

#define csplit_parser_warning(...)                                 \
  csplit_parser_warning_func(CURRENT_FUNCTION, __FILE__, __LINE__, \
                             __VA_ARGS__)

/* symbols exported by lex / yacc */
extern char * splitc_text;
extern FILE * splitc_in;
extern int splitc_lex();
extern int splitc_lex_destroy();
extern int splitc_parse();
extern void splitc_error(const char*);
/* source_file.c */
extern void pips_get_workspace_list(gen_array_t /*array*/);
extern void pips_get_fortran_list(gen_array_t /*array*/);
extern string hpfc_generate_path_name_of_file_name(const char */*file_name*/);
extern int hpfc_get_file_list(gen_array_t /*file_names*/, char **/*hpfc_directory_name*/);
extern string pips_change_directory(const char */*dir*/);
extern void pips_srcpath_set(string /*path*/);
extern string pips_srcpath_append(string /*pathtoadd*/);
extern void init_processed_include_cache(void);
extern void close_processed_include_cache(void);
extern bool filter_file(string /*mod_name*/);
extern string preprocessor_current_split_file_name;
extern string preprocessed_to_user_file(string /*preprocessed_user_file*/);
extern bool dot_F_file_p(string /*name*/);
extern bool dot_f_file_p(string /*name*/);
extern bool dot_f90_file_p(string /*name*/);
extern bool dot_f95_file_p(string /*name*/);
extern bool dot_c_file_p(string /*name*/);
extern language workspace_language(gen_array_t /*files*/);
extern int find_eol_coding(string /*name*/);
extern string preprocessor_current_initial_file_name;
extern bool process_user_file(string /*file*/);
extern bool flag_as_stub(const string /*module_name*/);
extern bool bootstrap_stubs(const string /*module_name*/);
/* split_file.c */
extern char fsplit_copyright[];
extern char fsplit_sccsid[];
extern char *fsplit(char */*dir_name*/, char */*file_name*/, FILE */*out*/);
extern char *process_bang_comments_and_hollerith(FILE */*in*/, FILE */*out*/);
/* csplit_file.c */
extern char *current_include_file_path;
extern char *current_file_path;
extern void init_module_name_list(void);
extern void reset_module_name_list(void);
extern void error_reset_module_name_list(void);
extern string get_splitc_input_file_name(void);
extern void reset_current_input_line(void);
extern void csplit_open_compilation_unit(string /*input_file_name*/);
extern void csplit_close_compilation_unit(void);
extern void copy_between_2_fd_up_to_offset(FILE */*source*/, FILE */*destination*/, unsigned long long /*up_to_offset*/, bool /*greedy_spaces*/);
extern void csplit_append_to_compilation_unit(int /*last_line*/, unsigned long long /*last_offset*/);
extern void csplit_copy(const char */*module_name*/, string /*signature*/, int /*first_line*/, int /*last_line*/, size_t /*first_offset*/, size_t /*last_offset*/, int /*user_first_line*/, bool /*is_static_p*/);
extern void keep_track_of_typedef(string /*type_name*/);
extern void csplit_error_handler(void);
extern void csplit_reset(void);
extern void csplit_close_files(string /*file_name*/);
extern void preprocessor_init_keyword_typedef_table(void);
extern string current_file_name;
extern string csplit(char */*dir_name*/, char */*file_name*/, FILE */*out*/);
/* f95split_file.c */
extern char *f95split(char */*dir_name*/, char */*file_name*/, FILE **/*out*/);
/* splitc.y */
extern int csplit_is_external;
extern int csplit_is_function;
extern string csplit_current_function_name;
extern string csplit_current_function_name2;
extern string csplit_definite_function_name;
extern string csplit_definite_function_signature;
extern bool csplit_is_static_p;
extern void csplit_parser_warning_func(const char */*pips_func*/, const char */*pips_file*/, const int /*pips_line*/, const string /*format*/, ...);
extern void csplit_parser_error(const string /*msg*/);
extern void MakeTypedefStack(void);
extern void ResetTypedefStack(void);
extern void ForceResetTypedefStack(void);
extern void init_preprocessor_scope_stack(void);
extern void reset_preprocessor_scope_stack(void);
extern void force_reset_preprocessor_scope_stack(void);
extern void push_new_preprocessor_scope(void);
extern void pop_preprocessor_scope(void);
extern bool preprocessor_scope_stack_empty_p(void);
extern string get_preprocessor_current_scope(void);
extern string get_preprocessor_nth_scope(int /*n*/);
extern int preprocessor_scope_number(void);
extern int check_signature_balance(void);
/* lexer.l */
extern int csplit_line_number;
extern int user_line_number;
extern size_t current_csplit_file_offset;
extern size_t csplit_file_offset_beginning;
extern enum gather_comment_state_t gather_comment_state_machine;
extern void reset_csplit_line_number(void);
extern void reset_csplit_current_beginning(void);
extern int get_csplit_current_beginning(void);
extern int get_user_current_beginning(void);
extern size_t get_csplit_file_offset_beginning(void);
extern size_t get_current_csplit_file_offset(void);
extern void update_csplit_file_offset_information(void);
extern void splitc_error(const char */*msg*/);
extern int yywrap(void);
#endif /*  preprocessor_header_included */
