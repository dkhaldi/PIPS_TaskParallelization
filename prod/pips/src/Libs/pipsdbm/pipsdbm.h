/* Warning! Do not modify this file that is automatically generated! */
/* Modify src/Libs/pipsdbm/pipsdbm-local.h instead, to add your own modifications. */

/* header file built by cproto */

#ifndef  pipsdbm_header_included
#define  pipsdbm_header_included
/*

  $Id: pipsdbm-local.h 23065 2016-03-02 09:05:50Z coelho $

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
#include "linear.h"
#include "resources.h"

#define PIPSDBM_DEBUG_LEVEL "PIPSDBM_DEBUG_LEVEL"

#define PROGRAM_RESOURCE_OWNER ""

#define WORKSPACE_TMP_SPACE 		"Tmp"
#define WORKSPACE_SRC_SPACE 		"Src"
#define WORKSPACE_PROGRAM_SPACE 	"Program"
#define WORKSPACE_METADATA_SPACE	"Metadata"
/* Name of the file containing the names of the main procedures
 *
 * There may be more than one in Fortran. It is simpler in C, because
 * the main procedure is always called "main" and we cannot have more
 * than one without a name conflict.
 */
#define MAIN_FILE_NAMES                 "PROGRAM.main"

/* symbols exported by parser / lexer */
extern FILE *genread_in;
extern int genread_input(void);

/* conform to old interface.
 */

/** Put a memory resource into the current workspace database

    @ingroup pipsdbm

    This function allows to update a memory resource already available.

    @param rname is a resource name, such as DBR_CODE for the code of a
    module. The construction of these aliases are DBB_ + the uppercased
    name of a resource defined in pipsmake-rc.tex. They are defined
    automatically in include/resources.h

    @param oname is the resource owner name, typically a module name.
    
    @param res_val is an opaque pointer to the resource to be
    stored. Methods defined in methods.h will know how to deal with.
*/
#define DB_PUT_MEMORY_RESOURCE(res_name, own_name, res_val) \
  db_put_or_update_memory_resource(res_name, own_name, (void*) res_val, true)

/** Put a file resource into the current workspace database

    @ingroup pipsdbm
    
    This function allows to update a file resource already available.

    @param rname is a resource name, such as DBR_CODE for the code of a
    module. The construction of these aliases are DBB_ + the uppercased
    name of a resource defined in pipsmake-rc.tex. They are defined
    automatically in include/resources.h

    @param oname is the resource owner name, typically a module name.
    
    @param res_val is an opaque pointer to the resource to be
    stored. Methods defined in methods.h will know how to deal with.
*/
#define DB_PUT_FILE_RESOURCE DB_PUT_MEMORY_RESOURCE

/** Put a new file resource into the current workspace database

    @ingroup pipsdbm
    
    This function disallows to update a resource already available.

    @param rname is a resource name, such as DBR_CODE for the code of a
    module. The construction of these aliases are DBB_ + the uppercased
    name of a resource defined in pipsmake-rc.tex. They are defined
    automatically in include/resources.h

    @param oname is the resource owner name, typically a module name.
    
    @param res_val is an opaque pointer to the resource to be
    stored. Methods defined in methods.h will know how to deal with.
*/
#define DB_PUT_NEW_FILE_RESOURCE(res_name, own_name, res_val) \
  db_put_or_update_memory_resource(res_name, own_name, (void*) res_val, false)

#define db_get_file_resource db_get_memory_resource
#define db_unput_a_resource(r,o) db_delete_resource(r,o)
#define build_pgmwd db_get_workspace_directory_name

#define db_make_subdirectory(n) free(db_get_directory_name_for_module(n))

#include "newgen.h" /* ??? statement_mapping */
/* database.c */
extern void db_create_pips_database(void);
extern bool db_open_pips_database(FILE */*fd*/);
extern void db_save_pips_database(FILE */*fd*/);
extern void db_close_pips_database(void);
extern void db_reset_pips_database_if_necessary(void);
extern void dump_all_db_resource_status(FILE */*file*/, string /*where*/);
extern void db_delete_resource(const char */*rname*/, const char */*oname*/);
extern bool db_update_time(const char */*rname*/, const char */*oname*/);
extern void db_print_all_required_resources(FILE */*file*/);
extern void db_clean_all_required_resources(void);
extern bool db_resource_required_or_available_p(const char */*rname*/, const char */*oname*/);
extern bool db_resource_is_required_p(const char */*rname*/, const char */*oname*/);
extern bool db_resource_p(const char */*rname*/, const char */*oname*/);
extern bool db_touch_resource(const char */*rname*/, const char */*oname*/);
extern int db_time_of_resource(const char */*rname*/, const char */*oname*/);
extern string db_get_resource_id(const char */*rname*/, const char */*oname*/);
extern string db_get_memory_resource(const char */*rname*/, const char */*oname*/, bool /*pure*/);
extern void db_set_resource_as_required(const char */*rname*/, const char */*oname*/);
extern void db_put_or_update_memory_resource(const char */*rname*/, const char */*oname*/, void */*p*/, bool /*update_is_ok*/);
extern void db_invalidate_memory_resource(const char */*rname*/, const char */*oname*/);
extern int db_unput_resources(const char */*rname*/);
extern list db_retrieve_resources(const char */*rname*/);
extern string db_resource_name(void */*dbr*/);
extern string db_resource_owner_name(void */*dbr*/);
extern void db_save_and_free_memory_resource_if_any(const char */*rname*/, const char */*oname*/, bool /*do_free*/);
extern void db_delete_all_resources(void);
extern bool db_set_current_module_name(const char */*name*/);
extern string db_get_current_module_name(void);
extern void db_reset_current_module_name(void);
extern int db_delete_obsolete_resources(bool (* /*keep_p*/)(const char *, const char *));
extern bool db_module_exists_p(const char */*name*/);
extern gen_array_t db_get_module_list_initial_order(void);
extern gen_array_t db_get_module_or_function_list(bool /*module_p*/);
extern gen_array_t db_get_module_list(void);
extern gen_array_t db_get_function_list(void);
/* lowlevel.c */
extern const char *dbll_current_module;
extern int dbll_number_of_resources(void);
extern string dbll_get_ith_resource_name(int /*i*/);
extern bool dbll_very_special_resource_p(const char */*rname*/, const char */*oname*/);
extern void db_set_current_builder_name(const char */*name*/);
extern void db_reset_current_builder_name(void);
extern string db_get_current_builder_name(void);
extern string db_get_directory_name_for_module(const char */*name*/);
extern string db_build_file_resource_name(const char */*rname*/, const char */*oname*/, const char */*suffix*/);
extern string get_resource_file_name(const char */*rname*/, const char */*oname*/);
extern void dbll_unlink_resource_file(const char */*rname*/, const char */*oname*/, bool /*erroriffailed*/);
extern int dbll_stat_local_file(const char */*file_name*/, bool /*okifnotthere*/);
extern int dbll_stat_resource_file(const char */*rname*/, const char */*oname*/, bool /*okifnotthere*/);
extern void dbll_save_resource(const char */*rname*/, const char */*oname*/, void */*p*/);
extern void *dbll_load_resource(const char */*rname*/, const char */*oname*/);
extern void dbll_free_resource(const char */*rname*/, const char */*oname*/, void */*p*/);
extern bool dbll_check_resource(const char */*rname*/, const char */*oname*/, void */*p*/);
extern bool dbll_storable_p(const char */*rname*/);
extern void dbll_save_and_free_resource(const char */*rname*/, const char */*oname*/, void */*p*/, bool /*do_free*/);
extern bool displayable_file_p(const char */*name*/);
extern bool dbll_database_managed_file_p(const char */*name*/);
/* workspace.c */
extern bool workspace_name_p(const char */*name*/);
extern string db_get_current_workspace_name(void);
extern string db_get_workspace_directory_name(const char */*name*/);
extern string db_get_current_workspace_directory(void);
extern int db_inc_logical_time(void);
extern int db_get_logical_time(void);
extern string db_get_meta_data_directory(void);
extern bool workspace_exists_p(const char */*name*/);
extern bool workspace_ok_p(const char */*name*/);
extern bool db_create_workspace(const char */*name*/);
extern void db_checkpoint_workspace(void);
extern bool db_close_workspace(bool /*is_quit*/);
extern bool db_open_workspace(const char */*name*/);
/* externals.c */
extern char *pipsdbm_read_entities(FILE */*fd*/);
extern void pipsdbm_free_entities(char */*p*/);
extern void pipsdbm_write_statement_mapping(FILE */*fd*/, statement_mapping /*h*/);
extern hash_table pipsdbm_read_statement_mapping(FILE */*fd*/);
extern bool pipsdbm_check_statement_mapping(statement_mapping /*h*/);
extern void pipsdbm_free_statement_mapping(statement_mapping /*h*/);
extern bool pipsdbm_consistent_statement_function(gen_chunkp /*map*/);
extern void pipsdbm_write_statement_function(FILE */*fd*/, gen_chunkp /*map*/);
extern gen_chunkp pipsdbm_read_statement_function(FILE */*fd*/);
extern void free_static_control_mapping(statement_mapping /*map*/);
extern void declarations_write(FILE */*f*/, hash_table /*h*/);
extern hash_table declarations_read(FILE */*f*/);
/* util.c */
extern bool some_main_entity_p(void);
extern string get_main_entity_name(void);
/* misc.c */
extern void interrupt_pipsmake_asap(void);
extern void dont_interrupt_pipsmake_asap(void);
extern bool interrupt_pipsmake_asap_p(void);
extern void init_request_timers(void);
extern void init_log_timers(void);
extern void dbm_start_timer(void);
extern void dbm_stop_timer(void);
extern void get_string_timers(string */*with_io*/, string */*io*/);
extern void get_request_string_timers(string */*global*/, string */*phases*/, string */*dbm*/);
extern void init_resource_usage_check(void);
extern void add_read_resource(string /*rname*/, string /*oname*/);
extern void add_write_resource(string /*rname*/, string /*oname*/);
extern void get_logged_resources(set */*sr*/, set */*sw*/);
#endif /*  pipsdbm_header_included */
