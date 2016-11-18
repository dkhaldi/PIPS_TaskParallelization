/* Warning! Do not modify this file that is automatically generated! */
/* Modify src/Libs/wp65/wp65-local.h instead, to add your own modifications. */

/* header file built by cproto */

#ifndef  wp65_header_included
#define  wp65_header_included
/*

  $Id: wp65-local.h 23065 2016-03-02 09:05:50Z coelho $

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
 /* Header File for WP65
  *
  * Francois Irigoin, Corinne Ancourt, Lei Zhou
  *
  * September 1991
  */

#ifndef WP65_INCLUDED
#define WP65_INCLUDED

#define EMULATED_SHARED_MEMORY_PREFIX  "ES_"
#define LOCAL_MEMORY_PREFIX            "L_"
#define LOCAL_MEMORY_SEPARATOR         "_"
#define COMPUTE_ENGINE_NAME            "WP65"
/* #define WP65_SUFFIX                    "_WP65" */
#define BANK_NAME                      "BANK"
/* #define MEMORY_EMULATOR_SUFFIX         "_BANK" */
#define PROCESSOR_IDENTIFIER           "PROC_ID"
#define BANK_IDENTIFIER                "BANK_ID"
#define BANK_LINE_IDENTIFIER           "L"
#define BANK_OFFSET_IDENTIFIER         "O"

#define SUFFIX_FOR_INDEX_TILE_IN_INITIAL_BASIS     "_1"
#define SUFFIX_FOR_INDEX_TILE_IN_TILE_BASIS        "_0"
#define PREFIX_FOR_LOCAL_TILE_BASIS                "L_"


/* These values should be read in model.rc (FI, 20/11/91)
   #define PROCESSOR_NUMBER 4
   #define BANK_NUMBER      4
   #define LINE_SIZE        25    
*/

/* FI: PIPELINE_DEPTH should be set to 3 */
#define PIPELINE_DEPTH    1

#define MAXIMUM_LOCAL_VARIABLE_NAME_SIZE 256

#endif /* WP65_INCLUDED */
/* code.c */
extern Value offset_dim1;
extern Value offset_dim2;
extern void eval_variable_in_statement(entity /*module*/, statement /*s*/, Variable /*v*/, int /*min*/);
extern void tile_change_of_basis(Psysteme /*tile_domain*/, Pbase /*initial_basis*/, Pbase /*tile_basis*/, Pbase /*tile_init_basis*/, tiling /*tile*/);
extern statement make_scanning_over_tiles(entity /*module*/, list /*body*/, entity /*proc_id*/, int /*pn*/, tiling /*tile*/, Pbase /*initial_basis*/, Pbase /*tile_basis_in_tile_basis*/, Pbase /*tile_basis_in_initial_basis*/, Psysteme /*iteration_domain*/, int /*first_parallel_level*/, int /*last_parallel_level*/);
extern statement make_scanning_over_one_tile(entity /*module*/, statement /*body*/, tiling /*tile*/, Pbase /*initial_basis*/, Pbase /*local_basis*/, Pbase /*tile_basis_in_tile_basis*/, Pbase /*tile_basis_in_initial_basis*/, Psysteme /*iteration_domain*/, int /*first_parallel_level*/, int /*last_parallel_level*/);
extern list make_compute_block(entity /*module*/, statement /*body*/, Pvecteur /*offsets*/, hash_table /*r_to_llv*/, tiling /*tile*/, Pbase /*initial_basis*/, Pbase /*local_basis*/, Pbase /*tile_basis_in_tile_basis*/, Pbase /*tile_basis_in_initial_basis*/, Psysteme /*iteration_domain*/, int /*first_parallel_level*/, int /*last_parallel_level*/);
extern list reference_conversion_statement(entity /*module*/, statement /*body*/, list */*lt*/, hash_table /*r_to_llv*/, Pvecteur /*offsets*/, Pbase /*initial_basis*/, Pbase /*tile_indices*/, Pbase /*local_basis*/, tiling /*tile*/);
extern list reference_conversion_computation(entity /*compute_module*/, list */*lt*/, expression /*expr*/, Pbase /*initial_basis*/, Pbase /*tile_indices*/, Pbase /*tile_local_indices*/, tiling /*tile*/);
extern entity reference_translation(reference /*r*/, Pbase /*initial_basis*/, Pbase /*local_basis*/);
extern void reference_conversion_expression(expression /*e*/, hash_table /*r_to_llv*/, Pvecteur /*offsets*/, Pbase /*initial_basis*/, Pbase /*local_basis*/);
extern bool uniform_dependence_p(reference /*r1*/, reference /*r2*/);
extern list classify_reference(list /*llr*/, reference /*r*/);
extern Psysteme build_sc_with_several_uniform_ref(entity /*module*/, cons */*lr*/, Psysteme /*sc_domain*/, Pbase */*new_index_base*/);
extern void make_store_blocks(entity /*initial_module*/, entity /*compute_module*/, entity /*memory_module*/, entity /*var*/, entity /*shared_variable*/, entity /*local_variable*/, list /*lrefs*/, hash_table /*r_to_ud*/, Psysteme /*sc_domain*/, Pbase /*index_base*/, Pbase /*bank_indices*/, Pbase /*tile_indices*/, Pbase /*loop_body_indices*/, entity /*Proc_id*/, int /*pn*/, int /*bn*/, int /*ls*/, statement */*store_block*/, statement */*bank_store_block*/, int /*first_parallel_level*/, int /*last_parallel_level*/);
extern void make_load_blocks(entity /*initial_module*/, entity /*compute_module*/, entity /*memory_module*/, entity /*var*/, entity /*shared_variable*/, entity /*local_variable*/, list /*lrefs*/, hash_table /*r_to_ud*/, Psysteme /*sc_domain*/, Pbase /*index_base*/, Pbase /*bank_indices*/, Pbase /*tile_indices*/, Pbase /*loop_body_indices*/, entity /*Proc_id*/, int /*pn*/, int /*bn*/, int /*ls*/, statement */*load_block*/, statement */*bank_load_block*/, int /*first_parallel_level*/, int /*last_parallel_level*/);
extern Psysteme tile_membership(matrice /*P*/, Pbase /*origin*/, Pbase /*member*/);
/* tiling.c */
extern tiling loop_nest_to_tile(Psysteme /*sc*/, int /*ls*/, Pbase /*base_index*/, int /*first_parallel_level*/, int /*last_parallel_level*/, int /*perfect_nested_level*/);
/* variable.c */
extern void loop_nest_to_local_variables(entity /*initial_module*/, entity /*compute_module*/, entity /*memory_module*/, hash_table /*llv_to_lcr*/, hash_table /*r_to_llv*/, hash_table /*v_to_lllv*/, hash_table /*r_to_ud*/, hash_table /*v_to_esv*/, hash_table /*v_to_nlv*/, list /*lpv*/, statement /*body*/, Pbase /*indices*/, graph /*dg*/, int /*bn*/, int /*ls*/, int /*pd*/, tiling /*tile*/);
extern entity make_emulated_shared_variable(entity /*v*/, entity /*memory_module*/, int /*bn*/, int /*ls*/);
extern entity find_or_create_emulated_shared_variable(entity /*v*/, entity /*memory_module*/, hash_table /*v_to_esv*/, int /*bn*/, int /*ls*/);
extern list make_new_local_variables(entity /*v*/, entity /*compute_module*/, int /*number*/, int /*pd*/, hash_table /*v_to_lllv*/);
extern bool reference_conflicting_test_and_update(reference /*r*/, graph /*dg*/, hash_table /*v_to_lllv*/, hash_table /*llv_to_lcr*/, hash_table /*r_to_llv*/, hash_table /*r_to_ud*/);
extern bool reference_conflicting_p(reference /*r1*/, reference /*r2*/, graph /*dg*/);
extern Psysteme make_tile_constraints(matrice /*P*/, Pbase /*b*/);
extern void set_dimensions_of_local_variables(hash_table /*v_to_lllv*/, Pbase /*basis*/, tiling /*tile*/, hash_table /*llv_to_lcr*/);
extern void set_dimensions_of_local_variable_family(list /*llv*/, Psysteme /*tc*/, list /*lr*/, tiling /*tile*/, int /*dimn*/);
/* instruction_to_wp65_code.c */
extern bool list_of_calls_p(list /*lsb*/);
extern entity ith_index_of_ref(reference /*r*/, int /*level*/);
extern loop ith_loop_in_loop_nest(statement /*s1*/, int /*level*/);
extern void instruction_to_wp65_code(entity /*module*/, list /*l*/, graph /*dg*/, int /*pn*/, int /*bn*/, int /*ls*/, int /*pd*/, entity /*proc_id*/, entity /*proc_id_mm*/, Pbase /*bank_indices*/, hash_table /*v_to_esv*/, hash_table /*v_to_nlv*/, entity /*compute_module*/, statement /*computational*/, entity /*memory_module*/, statement /*emulator*/, statement_mapping /*fetch_map*/, statement_mapping /*store_map*/);
extern void call_to_wp65_code(statement /*s*/, entity /*compute_module*/, entity /*memory_module*/, entity /*bank_id*/, entity /*proc_id*/, statement /*computational*/, statement /*emulator*/, statement_mapping /*fetch_map*/, statement_mapping /*store_map*/, hash_table /*v_to_esv*/);
extern expression ref_in_implied_do(expression /*exp*/);
extern reference translate_IO_ref(call /*c*/, hash_table /*v_to_esv*/, bool /*loop_or_call_print*/);
extern statement generate_io_wp65_code(statement /*s1*/, statement /*body*/, hash_table /*v_to_esv*/, bool /*loop_or_call_print*/);
extern bool io_loop_nest_p(statement /*st*/);
extern void loop_nest_movement_generation(entity /*module*/, statement /*loop_nest*/, int /*pn*/, int /*bn*/, int /*ls*/, int /*pd*/, entity /*proc_id*/, entity /*proc_id_mm*/, Pbase /*bank_indices*/, hash_table /*v_to_esv*/, hash_table /*v_to_nlv*/, entity /*compute_module*/, statement /*computational*/, entity /*memory_module*/, statement /*emulator*/, statement_mapping /*fetch_map*/, statement_mapping /*store_map*/, statement /*mod_stat*/, bool /*fully_parallel*/, Psysteme /*sc_tile*/, Pbase /*initial_basis*/, Pbase /*local_basis*/, Pbase /*local_basis2*/, Pbase /*tile_basis_in_tile_basis*/, Pbase /*tile_basis_in_tile_basis2*/, Pbase /*loop_body_indices*/, list /*lpv*/, list */*lb*/, list */*blb*/, list */*sb*/, list */*bsb*/, int /*first_parallel_level*/, int /*last_parallel_level*/, hash_table /*llv_to_lcr*/, hash_table /*r_to_llv*/, hash_table /*v_to_lllv*/, hash_table /*r_to_ud*/);
extern void loop_nest_to_wp65_code(entity /*module*/, statement /*loop_nest*/, graph /*dg*/, int /*pn*/, int /*bn*/, int /*ls*/, int /*pd*/, entity /*proc_id*/, entity /*proc_id_mm*/, Pbase /*bank_indices*/, hash_table /*v_to_esv*/, hash_table /*v_to_nlv*/, entity /*compute_module*/, statement /*computational*/, entity /*memory_module*/, statement /*emulator*/, statement_mapping /*fetch_map*/, statement_mapping /*store_map*/, statement /*mod_stat*/);
extern void make_all_movement_blocks(entity /*initial_module*/, entity /*compute_module*/, entity /*memory_module*/, entity /*v*/, list /*map*/, hash_table /*llv_to_lcr*/, hash_table /*v_to_lllv*/, hash_table /*r_to_ud*/, hash_table /*v_to_esv*/, int /*pn*/, int /*bn*/, int /*ls*/, Psysteme /*iteration_domain*/, Pbase /*initial_basis*/, Pbase /*local_basis*/, entity /*proc_id*/, Pbase /*bank_indices*/, Pbase /*loop_body_indices*/, list */*pmb*/, list */*pbmb*/, tag /*use_def*/, int /*first_parallel_level*/, int /*last_parallel_level*/);
extern void search_parallel_loops(statement /*mod_stat*/, statement /*loop_statement*/, graph /*dg*/, bool /*loop_carried_dep*/[11]);
extern bool full_parallel_loop_nest_p(statement /*mod_stat*/, statement /*loop_stmt*/, int /*nest_dim*/, graph /*dg*/, bool */*loop_carried_dep*/);
/* wp65.c */
extern bool fetch_map_undefined_p(void);
extern void set_fetch_map(statement_mapping /*m*/);
extern statement_mapping get_fetch_map(void);
extern void reset_fetch_map(void);
extern void free_fetch_map(void);
extern void make_fetch_map(void);
extern list load_statement_fetch(statement /*s*/);
extern void delete_statement_fetch(statement /*s*/);
extern bool statement_fetch_undefined_p(statement /*s*/);
extern void store_statement_fetch(statement /*s*/, list /*t*/);
extern void update_statement_fetch(statement /*s*/, list /*t*/);
extern bool store_map_undefined_p(void);
extern void set_store_map(statement_mapping /*m*/);
extern statement_mapping get_store_map(void);
extern void reset_store_map(void);
extern void free_store_map(void);
extern void make_store_map(void);
extern list load_statement_store(statement /*s*/);
extern void delete_statement_store(statement /*s*/);
extern bool statement_store_undefined_p(statement /*s*/);
extern void store_statement_store(statement /*s*/, list /*t*/);
extern void update_statement_store(statement /*s*/, list /*t*/);
extern entity MakeEntityFunction(string /*sname*/);
extern bool wp65(const string /*input_module_name*/);
extern void module_to_wp65_modules(entity /*module*/, statement /*module_code*/, graph /*dg*/, int /*pn*/, int /*bn*/, int /*ls*/, int /*pd*/, entity */*pcompute_module*/, statement */*pcomputational*/, entity */*pmemory_module*/, statement */*pemulator*/);
extern void fprint_wp65_hash_tables(FILE */*fd*/, hash_table /*llv_to_lcr*/, hash_table /*r_to_llv*/, hash_table /*v_to_lllv*/, hash_table /*r_to_ud*/, hash_table /*v_to_esv*/);
extern bool wp65_conform_p(statement /*s*/);
/* basis.c */
extern entity create_local_index(entity /*module*/, Pvecteur /*pv*/, string /*st*/);
extern entity create_local_index2(entity /*module*/, Pvecteur /*pv*/, string /*st*/);
extern void create_tile_basis(entity /*initial_module*/, entity /*compute_module*/, entity /*memory_module*/, Pbase /*initial_basis*/, Pbase */*tile_basis_in_initial_basis*/, Pbase */*tile_basis_in_tile_basis*/, Pbase */*local_tile_basis*/, Pbase */*tile_basis_in_tile_basis2*/, Pbase */*local_tile_basis2*/);
/* find_iteration_domain.c */
extern void find_iteration_domain(statement /*s*/, Psysteme */*sc*/, Pbase */*basis*/, int */*nested_level*/, list */*list_statement_block*/, instruction */*inst*/);
extern void compute_iteration_domain(list /*list_loop_statement*/, Psysteme */*sc*/, Pbase */*basis*/);
extern void iteration_domain_from_statement(list */*list_loop_statement*/, statement /*s*/, int */*nested_level*/, list */*blocks*/, instruction */*inst*/);
/* model.c */
extern void model_fprint(FILE */*fd*/, int /*pn*/, int /*bn*/, int /*ls*/);
extern void model_fscan(FILE */*fd*/, int */*ppn*/, int */*pbn*/, int */*pls*/);
extern void get_model(int */*ppn*/, int */*pbn*/, int */*pls*/);
/* references.c */
extern bool ref_in_list_p(list /*lt*/, reference /*r*/);
extern void update_map(statement_mapping /*m*/, statement /*st*/, reference /*r*/);
extern list expression_to_operand_list(expression /*e*/, list /*lr*/);
extern bool reference_in_list_p(reference /*r*/, list /*lwr*/);
extern bool array_indice_in_list_p(reference /*r*/, list /*lwr*/);
extern void reference_list_update(list */*l*/, reference /*r*/);
extern void reference_list_add(list */*l1*/, list */*l2*/);
extern void reference_list_print(list /*l*/);
extern void reference_scalar_defined_p(reference /*r*/);
extern void variable_list_update(list */*l*/, reference /*r*/);
extern void variable_list_add(list */*l1*/, list */*l2*/);
extern void concat_data_list(list */*l*/, list */*lr*/, statement /*st*/, statement_mapping /*map*/, bool /*perfect_nested_loop*/);
/* communications.c */
extern void call_instruction_to_communications(statement /*s*/, statement /*st_level1*/, statement /*st_level2*/, list */*lwr*/, list */*lwr_local*/, statement_mapping */*fetch_map*/, statement_mapping */*store_map*/, hash_table /*r_to_ud*/, list */*lpv*/);
extern void loop_instruction_to_communications(statement /*stmt*/, statement /*st_level1*/, statement /*st_level2*/, list */*lwr*/, list */*lwr_local*/, statement_mapping */*fetch_map*/, statement_mapping */*store_map*/, hash_table /*r_to_ud*/, list */*lpv*/);
extern void statement_to_communications(statement /*stmt*/, statement /*st_level1*/, statement /*st_level2*/, list */*lwr*/, list */*lwr_local*/, statement_mapping */*fetch_map*/, statement_mapping */*store_map*/, hash_table /*r_to_ud*/, list */*lpv*/);
extern void compute_communications(list /*l*/, statement_mapping */*fetch_map*/, statement_mapping */*store_map*/);
extern void include_constant_symbolic_communication(entity /*compute_or_memory_module*/, list /*lrefs*/, bool /*load_code*/, statement /*computational_or_emulator*/, entity /*var_id*/);
extern list array_scalar_access_to_bank_communication(entity /*memory_module*/, Pbase /*bank_indices*/, int /*bn*/, int /*ls*/, list /*lt*/, bool /*load_code*/, entity /*proc_id*/, entity /*var_id*/, bool /*fully_sequential*/);
extern void insert_run_time_communications(entity /*compute_module*/, entity /*memory_module*/, Pbase /*bank_indices*/, int /*bn*/, int /*ls*/, entity /*proc_id*/, list /*list_statement_block*/, statement_mapping /*fetch_map*/, statement_mapping /*store_map*/, list */*new_slst*/, list */*new_blist*/, hash_table /*v_to_esv*/, bool /*fully_sequential*/, Pbase /*loop_indices*/, tiling /*tile*/, Pvecteur /*tile_delay*/, Pvecteur /*tile_indices*/, Pvecteur /*tile_local_indices*/);
extern bool test_run_time_communications(list /*list_statement_block*/, statement_mapping /*fetch_map*/, statement_mapping /*store_map*/);
#endif /*  wp65_header_included */
