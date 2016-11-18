/* Warning! Do not modify this file that is automatically generated! */
/* Modify src/Libs/hwac/hwac-local.h instead, to add your own modifications. */

/* header file built by cproto */

#ifndef  hwac_header_included
#define  hwac_header_included
/*

  $Id: hwac-local.h 23065 2016-03-02 09:05:50Z coelho $

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
#include "freia_spoc_private.h"
/* hardware_accelerator.c */
extern bool freia_spoc_compiler(const string /*module*/);
extern bool freia_terapix_compiler(const string /*module*/);
extern bool freia_aipo_compiler(const string /*module*/);
extern bool freia_opencl_compiler(const string /*module*/);
extern bool freia_sigmac_compiler(const string /*module*/);
/* freia.c */
extern bool freia_some_effects_on_images(statement /*s*/);
extern expression freia_transpose_kernel(const expression /*kref*/);
extern bool freia_is_transpose_call(statement /*s*/);
extern string freia_compile(string /*module*/, statement /*mod_stat*/, string /*target*/);
/* freia_spoc.c */
extern list freia_spoc_compile_calls(string /*module*/, dag /*fulld*/, sequence /*sq*/, list /*ls*/, const hash_table /*occs*/, hash_table /*exchanges*/, const set /*output_images*/, FILE */*helper_file*/, set /*helpers*/, int /*number*/);
/* freia_terapix.c */
extern list freia_trpx_compile_calls(string /*module*/, dag /*fulld*/, sequence /*sq*/, list /*ls*/, const hash_table /*occs*/, hash_table /*exchanges*/, const set /*output_images*/, FILE */*helper_file*/, set /*helpers*/, int /*number*/);
/* freia_opencl.c */
extern list freia_opencl_compile_calls(string /*module*/, dag /*fulld*/, sequence /*sq*/, list /*ls*/, const hash_table /*occs*/, hash_table /*exchanges*/, const set /*output_images*/, FILE */*helper_file*/, set /*helpers*/, int /*number*/, hash_table /*signatures*/);
/* freia_aipo.c */
extern list freia_aipo_compile_calls(string /*module*/, dag /*fulld*/, list /*ls*/, const hash_table /*occs*/, hash_table /*exchanges*/, int /*number*/);
/* freia_sigmac.c */
extern int ncompound;
extern int n_dags;
extern string_buffer subg_calls;
extern list freia_sigmac_compile_calls(string /*module*/, dag /*fulld*/, sequence /*sq*/, list /*ls*/, const hash_table /*occs*/, hash_table /*exchanges*/, const set /*output_images*/, FILE */*helper_file*/, set /*helpers*/, int /*number*/, int /*n_calls*/);
/* dag-utils.c */
extern string dagvtx_to_string(const dagvtx /*v*/);
extern statement dagvtx_statement(const dagvtx /*v*/);
extern void dag_statements(set /*stats*/, const dag /*d*/);
extern bool dagvtx_other_stuff_p(const dagvtx /*v*/);
extern entity dagvtx_image(const dagvtx /*v*/);
extern _int dagvtx_number(const dagvtx /*v*/);
extern string dagvtx_number_str(const dagvtx /*v*/);
extern _int dagvtx_optype(const dagvtx /*v*/);
extern _int dagvtx_opid(const dagvtx /*v*/);
extern string dagvtx_function_name(const dagvtx /*v*/);
extern string dagvtx_operation(const dagvtx /*v*/);
extern string dagvtx_compact_operation(const dagvtx /*v*/);
extern int dagvtx_ordering(const dagvtx */*v1*/, const dagvtx */*v2*/);
extern dagvtx dagvtx_get_producer(const dag /*d*/, const dagvtx /*sink*/, const entity /*e*/, _int /*before_number*/);
extern void dagvtx_nb_dump(FILE */*out*/, const string /*what*/, const list /*l*/);
extern void dagvtx_dump(FILE */*out*/, const string /*name*/, const dagvtx /*v*/);
extern void dag_dump(FILE */*out*/, const string /*what*/, const dag /*d*/);
extern void dag_dot(FILE */*out*/, const string /*what*/, const dag /*d*/, const list /*lb*/, const list /*la*/);
extern void dag_dot_dump(const string /*module*/, const string /*name*/, const dag /*d*/, const list /*lb*/, const list /*la*/);
extern void dag_dot_dump_prefix(const string /*module*/, const string /*prefix*/, int /*number*/, const dag /*d*/, const list /*lb*/, const list /*la*/);
extern void dag_consistency_asserts(dag /*d*/);
extern void dag_remove_vertex(dag /*d*/, const dagvtx /*v*/);
extern dagvtx copy_dagvtx_norec(dagvtx /*v*/);
extern bool dagvtx_is_measurement_p(const dagvtx /*v*/);
extern void dag_append_vertex(dag /*d*/, dagvtx /*nv*/);
extern int dag_computation_count(const dag /*d*/);
extern list dag_vertex_preds(const dag /*d*/, const dagvtx /*target*/);
extern void freia_dag_optimize(dag /*d*/, hash_table /*exchanges*/, list */*lbefore*/, list */*lafter*/);
extern void dag_compute_outputs(dag /*d*/, const hash_table /*occs*/, const set /*output_images*/, const list /*ld*/, bool /*inloop*/);
extern void freia_hack_fix_global_ins_outs(dag /*dfull*/, dag /*d*/);
extern void dag_cleanup_other_statements(dag /*d*/);
extern bool single_image_assignement_p(dag /*d*/);
extern list dag_computable_vertices(dag /*d*/, const set /*computed*/, const set /*maybe*/, const set /*currents*/);
extern void set_append_vertex_statements(set /*s*/, list /*lv*/);
extern dag freia_build_dag(string /*module*/, list /*ls*/, int /*number*/, const hash_table /*occurrences*/, const set /*output_images*/, const list /*ld*/, bool /*inloop*/);
extern bool dag_no_image_operation(dag /*d*/);
extern statement freia_memory_management_statement(entity /*image*/, const hash_table /*occs*/, bool /*alloc*/);
extern void freia_switch_image_in_statement(statement /*s*/, entity /*old*/, entity /*img*/, bool /*write*/);
extern list dag_fix_image_reuse(dag /*d*/, hash_table /*init*/, const hash_table /*occs*/);
extern list dag_split_on_scalars(const dag /*initial*/, bool (* /*alone_only*/)(const dagvtx), dagvtx (* /*choose_vertex*/)(const list, bool), gen_cmp_func_t /*priority*/, void (* /*priority_update*/)(const dag), const set /*output_images*/);
extern list dag_connected_component(dag /*d*/, list */*plv*/, bool (* /*compat*/)(const dagvtx, const set, const dag));
extern list dag_split_connected_components(dag /*d*/, set /*output_images*/);
/* freia-utils.c */
extern const freia_api_t *hwac_freia_api(const char */*function*/);
extern int hwac_freia_api_index(const string /*function*/);
extern const freia_api_t *get_freia_api(int /*index*/);
extern const freia_api_t *get_freia_api_vtx(dagvtx /*v*/);
extern string what_operation(const _int type);
extern string what_operation_shape(const _int type);
extern void freia_spoc_set_operation(const freia_api_t */*api*/, _int */*type*/, _int */*id*/);
extern list freia_get_params(const freia_api_t */*api*/, list /*args*/);
extern list freia_get_vertex_params(const dagvtx /*v*/);
extern expression freia_get_nth_scalar_param(const dagvtx /*v*/, int /*n*/);
extern int freia_max_pixel_value(void);
extern list freia_extract_params(const int /*napi*/, list /*args*/, string_buffer /*head*/, string_buffer /*head2*/, hash_table /*params*/, int */*nparams*/);
extern call freia_ok(void);
extern bool freia_assignment_p(const entity /*e*/);
extern statement freia_copy_image(const entity /*source*/, const entity /*target*/);
extern void hwac_replace_statement(statement /*s*/, call /*newc*/, bool /*kill*/);
extern void hwac_kill_statement(statement /*s*/);
extern bool freia_image_variable_p(const entity /*var*/);
extern bool entity_freia_api_p(const entity /*f*/);
extern bool freia_statement_aipo_call_p(const statement /*s*/);
extern void freia_init_dep_cache(void);
extern void freia_close_dep_cache(void);
extern bool freia_scalar_rw_dep(const statement /*s*/, const statement /*t*/, list */*vars*/);
extern call freia_statement_to_call(const statement /*s*/);
extern bool is_freia_alloc(const statement /*s*/);
extern bool is_freia_dealloc(const statement /*s*/);
extern bool same_constant_parameters(const dagvtx /*v1*/, const dagvtx /*v2*/);
extern entity freia_create_helper_function(const string /*function_name*/, list /*lparams*/);
extern int freia_substitute_by_helper_call(dag /*d*/, set /*global_remainings*/, set /*remainings*/, list /*ls*/, const string /*function_name*/, list /*lparams*/, set /*helpers*/, int /*preceeding*/);
extern void freia_insert_added_stats(list /*ls*/, list /*stats*/, bool /*before*/);
extern void freia_add_image_arguments(list /*limg*/, list */*lparams*/);
extern hash_table freia_build_image_occurrences(statement /*s*/, set /*image_occs_stats*/, hash_table /*image_stats*/, const hash_table /*signatures*/);
extern void freia_clean_image_occurrences(hash_table /*occs*/);
extern bool freia_aipo_spoc_implemented(const freia_api_t */*api*/);
extern bool freia_aipo_terapix_implemented(const freia_api_t */*api*/);
extern bool freia_convolution_p(dagvtx /*v*/);
extern bool freia_convolution_width_height(dagvtx /*v*/, _int */*pw*/, _int */*ph*/, bool /*check*/);
extern list freia_allocate_new_images_if_needed(list /*ls*/, list /*images*/, const hash_table /*occs*/, const hash_table /*init*/, const hash_table /*signatures*/);
extern int freia_aipo_count(dag /*d*/, int */*pa*/, int */*pc*/);
extern set freia_compute_output_images(entity /*module*/, statement /*s*/);
extern set freia_compute_current_output_images(void);
extern void freia_migrate_statements(sequence /*sq*/, const set /*stats*/, const set /*before*/);
extern bool freia_extract_kernel_vtx(dagvtx /*v*/, bool /*strict*/, intptr_t */*k00*/, intptr_t */*k10*/, intptr_t */*k20*/, intptr_t */*k01*/, intptr_t */*k11*/, intptr_t */*k21*/, intptr_t */*k02*/, intptr_t */*k12*/, intptr_t */*k22*/);
extern string helper_file_name(string /*func_name*/, string /*suffix*/);
/* freia_transformations.c */
extern bool freia_unroll_while(const string /*module*/);
extern bool freia_remove_scalar_ww_deps(const string /*module*/);
extern bool remove_simple_scalar_pointers(const string /*module*/);
extern void freia_shuffle_move_forward(statement /*s*/);
#endif /*  hwac_header_included */
