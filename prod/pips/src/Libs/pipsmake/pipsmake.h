/* Warning! Do not modify this file that is automatically generated! */
/* Modify src/Libs/pipsmake/pipsmake-local.h instead, to add your own modifications. */

/* header file built by cproto */

#ifndef  pipsmake_header_included
#define  pipsmake_header_included
/*

  $Id: pipsmake-local.h 23065 2016-03-02 09:05:50Z coelho $

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
#include "makefile.h"
typedef bool (*pipsmake_callback_handler_type)(void);

/* symbols exported by lex / yacc */
extern void pipsmake_error(const char *);
extern FILE *pipsmake_in;
extern int pipsmake_lex(void);
extern int pipsmake_parse(void);
/* pipsmake.c */
extern void set_current_phase_context(const char */*rname*/, const char */*oname*/);
extern void reset_current_phase_context(void);
extern void reset_make_cache(void);
extern void init_make_cache(void);
extern bool make_cache_p(void);
extern void reinit_make_cache_if_necessary(void);
extern bool make_cache_hit_p(void */*rr_id*/);
extern void add_resource_to_make_cache(void */*res_id*/);
extern void remove_resource_from_make_cache(void */*res_id*/);
extern void print_make_cache(void);
extern bool make_cache_consistent_p(void);
extern void reset_static_phase_variables(void);
extern rule find_rule_by_resource(const char */*rname*/);
extern bool rmake(const char */*rname*/, const char */*oname*/);
extern int delete_obsolete_resources(void);
extern void delete_some_resources(void);
extern bool check_resource_up_to_date(const char */*rname*/, const char */*oname*/);
extern void delete_named_resources(const char */*rn*/);
extern void delete_all_resources(void);
extern string get_first_main_module(void);
extern void do_resource_usage_check(const char */*oname*/, rule /*ru*/);
extern bool safe_make(const char */*res_n*/, const char */*module_n*/);
extern bool safe_apply(const char */*phase_n*/, const char */*module_n*/);
extern bool safe_concurrent_apply(const char */*phase_n*/, gen_array_t /*modules*/);
extern bool safe_set_property(const char */*propname*/, const char */*value*/);
extern gen_array_t get_callers(string /*module*/);
extern gen_array_t get_callees(string /*module*/);
/* activate.c */
extern void save_active_phases(void);
extern void retrieve_active_phases(void);
extern bool active_phase_p(const char */*phase*/);
extern bool saved_active_phase_p(const char */*phase*/);
extern void fprint_activated(FILE */*fd*/);
extern string active_phase_for_resource(string /*res*/);
extern const char *activate_phase(const char */*phase*/);
extern const char *activate(const char */*phase*/);
extern bool activate_phases(void);
extern void activate_language(language /*l*/);
extern bool rule_use_resource_produced(rule /*r*/);
/* openclose.c */
extern string build_pgm_makefile(const char */*n*/);
extern string make_open_workspace(const char */*name*/);
extern bool make_close_workspace(bool /*is_quit*/);
extern void checkpoint_workspace(void);
/* callback.c */
extern void set_pipsmake_callback(pipsmake_callback_handler_type /*p*/);
extern void reset_pipsmake_callback(void);
extern bool run_pipsmake_callback(void);
/* unsplit.c */
extern bool unsplit(const string /*name*/);
extern bool unsplit_parsed(const string /*name*/);
/* stubs.c */
extern bool array_dfg(string /*module*/);
extern bool print_array_dfg(string /*module*/);
extern bool scheduling(string /*module*/);
extern bool print_bdt(string /*module*/);
extern bool prgm_mapping(string /*module*/);
extern bool print_plc(string /*module*/);
extern bool reindexing(string /*module*/);
extern bool print_parallelizedCMF_code(string /*module*/);
extern bool print_parallelizedCRAFT_code(string /*module*/);
/* view.c */
extern string build_view_file(const char */*print_type*/);
extern string get_dont_build_view_file(const char */*print_type*/);
/* signal.c */
extern void reset_pips_timeout(void);
extern void set_pips_timeout(unsigned int /*delay*/);
extern void set_pips_timeout_from_env(void);
extern void initialize_signal_catcher(void);
/* readmakefile.y */
extern void yyerror(const char */*s*/);
extern void fprint_virtual_resources(FILE */*fd*/, const char */*dir*/, list /*lrv*/);
extern void fprint_makefile(FILE */*fd*/, makefile /*m*/);
extern makefile parse_makefile(void);
extern rule find_rule_by_phase(const char */*pname*/);
extern void add_rule(rule /*r*/);
extern makefile open_makefile(const char */*name*/);
extern void save_makefile(const char */*name*/);
extern bool close_makefile(const char */*name*/);
/* lexer.l */
extern int yywrap(void);
extern int init_lex(void);
extern void yyerror_lex_part(const char */*s*/);
#endif /*  pipsmake_header_included */
