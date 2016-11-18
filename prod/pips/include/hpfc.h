/* Warning! Do not modify this file that is automatically generated! */
/* Modify src/Libs/hpfc/hpfc-local.h instead, to add your own modifications. */

/* header file built by cproto */

#ifndef  hpfc_header_included
#define  hpfc_header_included
/*

  $Id: hpfc-local.h 23065 2016-03-02 09:05:50Z coelho $

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
/* local definitions
 */

#define HPFC_PACKAGE "HPFC-PACKAGE"
#include "hpf_private.h"
#include "hpf.h"
#include "message.h"

/* end of it
 */
/* directives.c */
extern bool the_dynamics_undefined_p(void);
extern void reset_the_dynamics(void);
extern void error_reset_the_dynamics(void);
extern void set_the_dynamics(list /*o*/);
extern list get_the_dynamics(void);
extern void init_the_dynamics(void);
extern void close_the_dynamics(void);
extern void add_a_dynamic(entity /*c*/);
extern void hpfc_directives_error_handler(void);
extern void handle_hpf_directives(statement /*s*/, bool /*dyn*/);
/* dynamic.c */
extern bool dynamic_hpf_undefined_p(void);
extern void reset_dynamic_hpf(void);
extern void error_reset_dynamic_hpf(void);
extern void set_dynamic_hpf(entity_entities /*o*/);
extern entity_entities get_dynamic_hpf(void);
extern void init_dynamic_hpf(void);
extern void close_dynamic_hpf(void);
extern void store_dynamic_hpf(entity /*k*/, entities /*v*/);
extern void update_dynamic_hpf(entity /*k*/, entities /*v*/);
extern entities load_dynamic_hpf(entity /*k*/);
extern entities delete_dynamic_hpf(entity /*k*/);
extern bool bound_dynamic_hpf_p(entity /*k*/);
extern void store_or_update_dynamic_hpf(entity /*k*/, entities /*v*/);
extern bool primary_entity_undefined_p(void);
extern void reset_primary_entity(void);
extern void error_reset_primary_entity(void);
extern void set_primary_entity(entitymap /*o*/);
extern entitymap get_primary_entity(void);
extern void init_primary_entity(void);
extern void close_primary_entity(void);
extern void store_primary_entity(entity /*k*/, entity /*v*/);
extern void update_primary_entity(entity /*k*/, entity /*v*/);
extern entity load_primary_entity(entity /*k*/);
extern entity delete_primary_entity(entity /*k*/);
extern bool bound_primary_entity_p(entity /*k*/);
extern void store_or_update_primary_entity(entity /*k*/, entity /*v*/);
extern bool renamings_undefined_p(void);
extern void reset_renamings(void);
extern void error_reset_renamings(void);
extern void set_renamings(statement_renamings /*o*/);
extern statement_renamings get_renamings(void);
extern void init_renamings(void);
extern void close_renamings(void);
extern void store_renamings(statement /*k*/, list /*v*/);
extern void update_renamings(statement /*k*/, list /*v*/);
extern list load_renamings(statement /*k*/);
extern list delete_renamings(statement /*k*/);
extern bool bound_renamings_p(statement /*k*/);
extern void store_or_update_renamings(statement /*k*/, list /*v*/);
extern bool maybeuseful_mappings_undefined_p(void);
extern void reset_maybeuseful_mappings(void);
extern void error_reset_maybeuseful_mappings(void);
extern void set_maybeuseful_mappings(statement_entities /*o*/);
extern statement_entities get_maybeuseful_mappings(void);
extern void init_maybeuseful_mappings(void);
extern void close_maybeuseful_mappings(void);
extern void store_maybeuseful_mappings(statement /*k*/, entities /*v*/);
extern void update_maybeuseful_mappings(statement /*k*/, entities /*v*/);
extern entities load_maybeuseful_mappings(statement /*k*/);
extern entities delete_maybeuseful_mappings(statement /*k*/);
extern bool bound_maybeuseful_mappings_p(statement /*k*/);
extern void store_or_update_maybeuseful_mappings(statement /*k*/, entities /*v*/);
extern bool similar_mapping_undefined_p(void);
extern void reset_similar_mapping(void);
extern void error_reset_similar_mapping(void);
extern void set_similar_mapping(entitymap /*o*/);
extern entitymap get_similar_mapping(void);
extern void init_similar_mapping(void);
extern void close_similar_mapping(void);
extern void store_similar_mapping(entity /*k*/, entity /*v*/);
extern void update_similar_mapping(entity /*k*/, entity /*v*/);
extern entity load_similar_mapping(entity /*k*/);
extern entity delete_similar_mapping(entity /*k*/);
extern bool bound_similar_mapping_p(entity /*k*/);
extern void store_or_update_similar_mapping(entity /*k*/, entity /*v*/);
extern entity safe_load_primary_entity(entity /*e*/);
extern bool same_primary_entity_p(entity /*e1*/, entity /*e2*/);
extern void init_dynamic_status(void);
extern void reset_dynamic_status(void);
extern dynamic_status get_dynamic_status(void);
extern void set_dynamic_status(dynamic_status /*d*/);
extern void close_dynamic_status(void);
extern void set_entity_as_dynamic(entity /*e*/);
extern bool (*dynamic_entity_p)(entity);
extern void set_similar_mappings_for_updates(void);
extern void hpfc_check_for_similarities(list /*le*/);
extern bool conformant_templates_p(entity /*t1*/, entity /*t2*/);
extern entity array_synonym_aligned_as(entity /*array*/, align /*a*/);
extern align new_align_with_template(align /*a*/, entity /*t*/);
extern entity template_synonym_distributed_as(entity /*temp*/, distribute /*d*/);
extern bool array_distribution_similar_p(entity /*a1*/, entity /*a2*/);
extern bool hpfc_call_with_distributed_args_p(call /*c*/);
extern void hpfc_translate_call_with_distributed_args(statement /*s*/, call /*c*/);
extern void init_dynamic_locals(void);
extern void close_dynamic_locals(void);
extern void add_as_a_used_dynamic_to_statement(statement /*s*/, entity /*e*/);
extern void propagate_synonym(statement /*s*/, entity /*old*/, entity /*new*/, bool /*is_array*/);
extern void dump_current_remapping_graph(string /*when*/);
extern void simplify_remapping_graph(void);
extern list alive_arrays(statement /*s*/, entity /*t*/);
extern statement generate_copy_loop_nest(entity /*src*/, entity /*trg*/);
/* hpfc.c */
extern bool hpf_reductions_undefined_p(void);
extern void reset_hpf_reductions(void);
extern void error_reset_hpf_reductions(void);
extern void set_hpf_reductions(statement_entities /*o*/);
extern statement_entities get_hpf_reductions(void);
extern void init_hpf_reductions(void);
extern void close_hpf_reductions(void);
extern void store_hpf_reductions(statement /*k*/, entities /*v*/);
extern void update_hpf_reductions(statement /*k*/, entities /*v*/);
extern entities load_hpf_reductions(statement /*k*/);
extern entities delete_hpf_reductions(statement /*k*/);
extern bool bound_hpf_reductions_p(statement /*k*/);
extern void store_or_update_hpf_reductions(statement /*k*/, entities /*v*/);
extern void add_a_common(entity /*c*/);
extern void add_a_pure(entity /*f*/);
extern bool hpf_pure_p(entity /*f*/);
extern void add_an_io_function(entity /*f*/);
extern bool hpfc_special_io(entity /*f*/);
extern void add_a_fake_function(entity /*f*/);
extern bool hpfc_special_fake(entity /*f*/);
extern bool remapping_already_computed_p(renaming /*x*/);
extern void add_remapping_as_computed(renaming /*r*/, list /*vars*/);
extern void add_remapping_as_used(renaming /*x*/);
extern void hpfc_add_ahead_of_node_code(statement /*s*/);
extern bool hpfc_init(const string /*name*/);
extern bool hpfc_filter(const string /*name*/);
extern bool hpfc_static_directives(const string /*name*/);
extern bool hpfc_dynamic_directives(const string /*name*/);
extern bool hpfc_compile(const string /*name*/);
extern bool hpfc_common(const string /*name*/);
extern bool hpfc_close(const string /*name*/);
extern bool hpfc_install(const string /*name*/);
extern bool hpfc_make(const string /*name*/);
extern bool hpfc_run(const string /*name*/);
/* debug-util.c */
extern void print_align(align /*a*/);
extern void print_alignment(alignment /*a*/);
extern void print_aligns(void);
extern void print_distributes(void);
extern void print_distribute(distribute /*d*/);
extern void print_distribution(distribution /*d*/);
extern void print_hpf_dir(void);
extern void print_templates(void);
extern void print_processors(void);
extern void print_distributed_arrays(void);
extern void hpfc_print_common(FILE */*file*/, entity /*module*/, entity /*common*/);
extern void hpfc_print_file(string /*file_name*/);
extern void fprint_range(FILE */*file*/, range /*r*/);
extern void fprint_lrange(FILE */*file*/, list /*l*/);
extern void fprint_message(FILE */*file*/, message /*m*/);
extern void fprint_lmessage(FILE */*file*/, list /*l*/);
/* hpfc-util.c */
extern bool ref_to_dist_array_p(void */*obj*/);
extern bool written_effect_p(entity /*var*/, list /*le*/);
extern bool written_effects_to_dist_arrays_p(expression /*expr*/);
extern bool replicated_p(entity /*e*/);
extern bool ith_dim_replicated_p(entity /*template*/, int /*i*/, list /*la*/, distribution /*dist*/);
extern bool processors_dim_replicated_p(entity /*p*/, entity /*a*/, int /*i*/);
extern bool ith_dim_distributed_p(entity /*array*/, int /*i*/, int */*pprocdim*/);
extern bool ith_dim_overlapable_p(entity /*array*/, int /*i*/);
extern statement MakeStatementLike(statement /*stat*/, int /*the_tag*/);
extern void kill_statement_number_and_ordering(statement /*s*/);
extern list DistArraysEffects(expression /*expr*/);
extern list FindRefToDistArrayFromList(list /*lexpr*/);
extern list FindRefToDistArray(void */*obj*/);
extern void AddEntityToHostAndNodeModules(entity /*e*/);
extern void AddCommonToModule(entity /*common*/, entity /*module*/, void (* /*update*/)(void), string /*suffix*/);
extern void AddCommonToHostAndNodeModules(entity /*common*/);
extern alignment FindAlignmentOfDim(list /*lal*/, int /*dim*/);
extern alignment FindAlignmentOfTemplateDim(list /*lal*/, int /*dim*/);
extern distribution FindDistributionOfDim(list /*ldi*/, int /*dim*/, int */*pdim*/);
extern distribution FindDistributionOfProcessorDim(list /*ldi*/, int /*dim*/, int */*tdim*/);
extern int template_dimension_of_array_dimension(entity /*array*/, int /*dim*/);
extern int processor_dimension_of_template_dimension(entity /*template*/, int /*dim*/);
extern int DistributionParameterOfArrayDim(entity /*array*/, int /*dim*/, int */*pprocdim*/);
extern int processor_number(entity /*template*/, int /*tdim*/, int /*tcell*/, int */*pprocdim*/);
extern int template_cell_local_mapping(entity /*array*/, int /*dim*/, int /*tc*/);
extern int global_array_cell_to_local_array_cell(entity /*array*/, int /*dim*/, int /*acell*/);
extern int HpfcExpressionToInt(expression /*e*/);
extern void get_alignment(entity /*array*/, int /*dim*/, int */*ptdim*/, int */*pa*/, int */*pb*/);
extern void get_distribution(entity /*template*/, int /*dim*/, int */*ppdim*/, int */*pn*/);
extern void get_entity_dimensions(entity /*e*/, int /*dim*/, int */*plow*/, int */*pup*/);
extern bool alignments_compatible_p(entity /*e1*/, int /*dim1*/, entity /*e2*/, int /*dim2*/);
extern bool references_aligned_p(reference /*r1*/, reference /*r2*/);
extern void hpfc_util_error_handler(void);
extern void statement_structural_cleaning(statement /*s*/);
/* declarations.c */
extern int number_of_distributed_arrays(void);
extern list list_of_distributed_arrays(void);
extern bool array_distributed_p(entity /*e*/);
extern void set_array_as_distributed(entity /*e*/);
extern bool declaration_delayed_p(entity /*e*/);
extern list list_of_distributed_arrays_for_module(entity /*module*/);
extern int number_of_templates(void);
extern list list_of_templates(void);
extern bool entity_template_p(entity /*e*/);
extern void set_template(entity /*e*/);
extern int number_of_processors(void);
extern list list_of_processors(void);
extern bool entity_processor_p(entity /*e*/);
extern void set_processor(entity /*e*/);
extern void reset_hpf_object_lists(void);
extern void free_hpf_object_lists(void);
extern bool hpf_number_undefined_p(void);
extern void reset_hpf_number(void);
extern void error_reset_hpf_number(void);
extern void set_hpf_number(entity_int /*o*/);
extern entity_int get_hpf_number(void);
extern void init_hpf_number(void);
extern void close_hpf_number(void);
extern void store_hpf_number(entity /*k*/, intptr_t /*v*/);
extern void update_hpf_number(entity /*k*/, intptr_t /*v*/);
extern intptr_t load_hpf_number(entity /*k*/);
extern intptr_t delete_hpf_number(entity /*k*/);
extern bool bound_hpf_number_p(entity /*k*/);
extern void store_or_update_hpf_number(entity /*k*/, intptr_t /*v*/);
extern void init_hpf_number_status(void);
extern numbers_status get_hpf_number_status(void);
extern void reset_hpf_number_status(void);
extern void set_hpf_number_status(numbers_status /*s*/);
extern void close_hpf_number_status(void);
extern void GiveToHpfObjectsTheirNumber(void);
extern expression entity_hpf_number(entity /*e*/);
extern bool hpf_alignment_undefined_p(void);
extern void reset_hpf_alignment(void);
extern void error_reset_hpf_alignment(void);
extern void set_hpf_alignment(alignmap /*o*/);
extern alignmap get_hpf_alignment(void);
extern void init_hpf_alignment(void);
extern void close_hpf_alignment(void);
extern void store_hpf_alignment(entity /*k*/, align /*v*/);
extern void update_hpf_alignment(entity /*k*/, align /*v*/);
extern align load_hpf_alignment(entity /*k*/);
extern align delete_hpf_alignment(entity /*k*/);
extern bool bound_hpf_alignment_p(entity /*k*/);
extern void store_or_update_hpf_alignment(entity /*k*/, align /*v*/);
extern bool hpf_distribution_undefined_p(void);
extern void reset_hpf_distribution(void);
extern void error_reset_hpf_distribution(void);
extern void set_hpf_distribution(distributemap /*o*/);
extern distributemap get_hpf_distribution(void);
extern void init_hpf_distribution(void);
extern void close_hpf_distribution(void);
extern void store_hpf_distribution(entity /*k*/, distribute /*v*/);
extern void update_hpf_distribution(entity /*k*/, distribute /*v*/);
extern distribute load_hpf_distribution(entity /*k*/);
extern distribute delete_hpf_distribution(entity /*k*/);
extern bool bound_hpf_distribution_p(entity /*k*/);
extern void store_or_update_hpf_distribution(entity /*k*/, distribute /*v*/);
extern tag new_declaration_tag(entity /*array*/, int /*dim*/);
extern void get_ith_dim_new_declaration(entity /*array*/, int /*i*/, int */*pmin*/, int */*pmax*/);
extern void init_data_status(void);
extern data_status get_data_status(void);
extern void reset_data_status(void);
extern void set_data_status(data_status /*s*/);
extern void close_data_status(void);
extern void normalize_distribute(entity /*t*/, distribute /*d*/);
extern void normalize_align(entity /*e*/, align /*a*/);
extern void normalize_hpf_object(entity /*v*/);
extern void NormalizeHpfDeclarations(void);
extern void NewDeclarationsOfDistributedArrays(void);
extern bool overlap_status_undefined_p(void);
extern void reset_overlap_status(void);
extern void error_reset_overlap_status(void);
extern void set_overlap_status(overlapsmap /*o*/);
extern overlapsmap get_overlap_status(void);
extern void init_overlap_status(void);
extern void close_overlap_status(void);
extern void store_overlap_status(entity /*k*/, list /*v*/);
extern void update_overlap_status(entity /*k*/, list /*v*/);
extern list load_overlap_status(entity /*k*/);
extern list delete_overlap_status(entity /*k*/);
extern bool bound_overlap_status_p(entity /*k*/);
extern void store_or_update_overlap_status(entity /*k*/, list /*v*/);
extern void set_overlap(entity /*ent*/, int /*dim*/, int /*side*/, int /*width*/);
extern int get_overlap(entity /*ent*/, int /*dim*/, int /*side*/);
extern void declaration_with_overlaps_for_module(entity /*module*/);
extern void update_overlaps_in_caller(entity /*fun*/, list /*le*/);
/* compiler-util.c */
extern void update_control_lists(control /*c*/, control_mapping /*map*/);
extern list updated_control_list(list /*lc*/, control_mapping /*map*/);
extern void FindRefToDistArrayInStatement(statement /*obj*/, list */*lwp*/, list */*lrp*/);
extern list lIndicesOfRef(list /*lsyn*/);
extern list IndicesOfRef(syntax /*syn*/);
extern list AddOnceToIndicesList(list /*l*/, list /*lsyn*/);
extern bool is_in_syntax_list(entity /*e*/, list /*l*/);
extern list FindDefinitionsOf(statement /*stat*/, list /*lsyn*/);
extern bool atomic_accesses_only_p(statement /*stat*/);
extern bool indirections_inside_statement_p(statement /*stat*/);
extern statement parallel_loop_nest_to_body(statement /*loop_nest*/, list */*pblocks*/, list */*ploops*/);
extern void set_current_loops(statement /*obj*/);
extern void reset_current_loops(void);
extern bool entity_loop_index_p(entity /*e*/);
extern range loop_index_to_range(entity /*index*/);
/* compiler.c */
extern entity host_module;
extern entity node_module;
extern void hpf_compiler(statement /*stat*/, statement */*hoststatp*/, statement */*nodestatp*/);
/* compile.c */
extern void make_host_and_node_modules(entity /*module*/);
extern void init_host_and_node_entities(void);
extern FILE *hpfc_fopen(string /*name*/);
extern void hpfc_fclose(FILE */*f*/, string /*name*/);
extern void hpfc_print_code(FILE */*file*/, entity /*module*/, statement /*stat*/);
extern void put_generated_resources_for_common(entity /*common*/);
extern void compile_a_special_io_function(entity /*module*/);
extern void compile_a_pure_function(entity /*module*/);
extern void put_generated_resources_for_module(statement /*stat*/, statement /*host_stat*/, statement /*node_stat*/);
extern void put_generated_resources_for_program(string /*program_name*/);
extern void hpfcompile(const char */*module_name*/);
extern entity hpfc_new_variable(entity /*module*/, basic /*b*/);
extern void hpfc_compile_error_handler(void);
extern void NormalizeCodeForHpfc(statement /*s*/);
extern bool update_common_map_undefined_p(void);
extern void set_update_common_map(entity_mapping /*m*/);
extern entity_mapping get_update_common_map(void);
extern void reset_update_common_map(void);
extern void free_update_common_map(void);
extern void make_update_common_map(void);
extern entity load_entity_update_common(entity /*s*/);
extern void delete_entity_update_common(entity /*s*/);
extern bool entity_update_common_undefined_p(entity /*s*/);
extern void store_entity_update_common(entity /*s*/, entity /*t*/);
extern void update_entity_update_common(entity /*s*/, entity /*t*/);
extern void debug_print_referenced_entities(void */*obj*/);
extern void update_common_references_in_obj(void */*obj*/);
extern void update_common_references_in_regions(void);
extern void NormalizeCommonVariables(entity /*module*/, statement /*stat*/);
/* run-time.c */
extern entity MakeRunTimeSupportSubroutine(string /*local_name*/, int /*number_of_arguments*/);
extern entity MakeRunTimeSupportFunction(string /*local_name*/, int /*number_of_arguments*/, tag /*return_type*/);
extern expression pvm_what_option_expression(entity /*v*/);
extern string pvm_what_options(basic /*b*/);
extern statement st_call_send_or_receive(entity /*f*/, reference /*r*/);
extern statement st_compute_current_computer(reference /*ref*/);
extern statement st_compute_current_owners(reference /*ref*/);
extern expression expr_compute_local_index(entity /*array*/, int /*dim*/, expression /*expr*/);
extern statement hpfc_make_call_statement(entity /*e*/, list /*l*/);
extern void add_pvm_init_and_end(statement */*phs*/, statement */*pns*/);
extern statement st_compute_neighbour(int /*d*/);
extern statement st_generate_packing(entity /*array*/, list /*content*/, bool /*bsend*/);
extern entity hpfc_main_entity(entity /*e*/);
extern const char *hpfc_main_entity_name(entity /*e*/);
extern string bound_parameter_name(entity /*array*/, string /*side*/, int /*dim*/);
extern entity argument_bound_entity(entity /*module*/, entity /*array*/, bool /*upper*/, int /*dim*/);
extern expression hpfc_array_bound(entity /*array*/, bool /*upper*/, int /*dim*/);
extern list array_lower_upper_bounds_list(entity /*array*/);
extern void hpfc_init_run_time_entities(void);
extern entity hpfc_name_to_entity(const char */*name*/);
extern bool hpfc_intrinsic_like_function(entity /*e*/);
extern bool hpfc_io_like_function(entity /*e*/);
/* generate.c */
extern void generate_c1_beta(statement /*stat*/, list */*lhp*/, list */*lnp*/);
extern void generate_c1_alpha(statement /*stat*/, list */*lhp*/, list */*lnp*/);
extern void generate_update_values_on_nodes(reference /*ref*/, reference /*newref*/, list */*lscompp*/, list */*lsnotcompp*/);
extern void generate_read_of_ref_for_computer(syntax /*s*/, list */*lcompp*/, list */*lnotcompp*/);
extern void generate_read_of_ref_for_all(syntax /*s*/, list */*lhp*/, list */*lnp*/);
extern void generate_compute_local_indices(reference /*ref*/, list */*lsp*/, list */*lindsp*/);
extern void generate_get_value_locally(reference /*ref*/, reference /*goal*/, list */*lstatp*/);
extern void generate_send_to_computer(reference /*ref*/, list */*lstatp*/);
extern void generate_receive_from_computer(reference /*ref*/, list */*lstatp*/);
extern void generate_parallel_body(statement /*body*/, list */*lstatp*/, list /*lw*/, list /*lr*/);
extern void generate_update_values_on_computer_and_nodes(reference /*ref*/, reference /*val*/, list */*lscompp*/, list */*lsnotcompp*/);
extern void generate_update_distributed_value_from_host(syntax /*s*/, list */*lhstatp*/, list */*lnstatp*/);
extern void generate_update_private_value_from_host(syntax /*s*/, list */*lhstatp*/, list */*lnstatp*/);
extern statement st_get_value_locally_and_send(reference /*ref*/, reference /*goal*/);
extern statement st_compute_ith_local_index(entity /*array*/, int /*i*/, expression /*expr*/, syntax */*sp*/);
extern statement st_send_to_host_and_nodes(reference /*ref*/, reference /*val*/);
extern statement st_send_to_computer_if_necessary(reference /*ref*/);
extern statement st_get_value_for_all(reference /*ref*/, reference /*goal*/);
extern statement st_get_value_for_computer(reference /*ref*/, reference /*goal*/);
extern statement st_receive_from(reference /*ref*/, reference /*goal*/);
/* local-ri-util.c */
extern type type_variable_dup(type /*t*/);
extern bool fortran_library_entity_p(entity /*e*/);
/* inits.c */
extern void create_common_parameters_h(FILE */*file*/);
extern void create_parameters_h(FILE */*file*/, entity /*module*/);
extern int max_size_of_processors(void);
extern void create_init_common_param_for_arrays(FILE */*file*/, entity /*module*/);
extern void create_init_common_param_for_templates(FILE */*file*/);
extern void create_init_common_param_for_processors(FILE */*file*/);
extern void create_init_common_param(FILE */*file*/);
/* o-analysis.c */
extern bool block_distributed_p(entity /*array*/);
extern bool Overlap_Analysis(statement /*stat*/, statement */*pstat*/);
/* align-checker.c */
extern bool hpfc_current_statement_undefined_p(void);
extern void reset_hpfc_current_statement(void);
extern void error_reset_hpfc_current_statement(void);
extern void set_hpfc_current_statement(statement /*o*/);
extern statement get_hpfc_current_statement(void);
extern bool local_integer_constant_expression(expression /*e*/);
extern bool align_check(reference /*r1*/, reference /*r2*/, list */*plvect*/, list */*plkind*/);
extern bool hpfc_integer_constant_expression_p(expression /*e*/, int */*pi*/);
/* messages.c */
extern statement messages_handling(list /*Ro*/, list /*lRo*/);
/* message-utils.c */
extern Pvecteur the_index_of_vect(Pvecteur /*v0*/);
extern list add_to_list_of_ranges_list(list /*l*/, range /*r*/);
extern list dup_list_of_ranges_list(list /*l*/);
extern list dup_list_of_Pvecteur(list /*l*/);
extern list add_elem_to_list_of_Pvecteur(list /*l*/, int /*var*/, int /*val*/);
extern range complementary_range(entity /*array*/, int /*dim*/, range /*r*/);
extern list generate_message_from_3_lists(entity /*array*/, list /*lcontent*/, list /*lneighbour*/, list /*ldomain*/);
extern bool empty_section_p(list /*lr*/);
extern bool empty_range_p(range /*r*/);
extern char *sprint_lrange(string /*str*/, list /*l*/);
extern char *sprint_range(string /*str*/, range /*r*/);
extern list compute_receive_content(entity /*array*/, list /*lr*/, Pvecteur /*v*/);
extern list compute_receive_domain(list /*lr*/, Pvecteur /*v*/);
extern bool larger_message_in_list(message /*m*/, list /*l*/);
extern bool message_larger_p(message /*m1*/, message /*m2*/);
extern bool lrange_larger_p(list /*lr1*/, list /*lr2*/);
extern list array_ranges_to_template_ranges(entity /*array*/, list /*lra*/);
extern list template_ranges_to_processors_ranges(entity /*template*/, list /*lrt*/);
extern list array_access_to_array_ranges(reference /*r*/, list /*lkref*/, list /*lvref*/);
extern statement generate_guarded_statement(statement /*stat*/, entity /*proc*/, list /*lr*/);
extern bool make_guard_expression(entity /*proc*/, list /*lrref*/, expression */*pguard*/);
extern expression make_mypos_expression(int /*i*/, expression /*exp*/);
extern statement loop_nest_guard(statement /*stat*/, reference /*r*/, list /*lkref*/, list /*lvref*/);
/* build-system.c */
extern bool entity_hpfc_dummy_p(entity /*e*/);
extern entity get_ith_region_dummy(int /*i*/);
extern entity get_ith_region_prime(int /*i*/);
extern entity get_ith_array_dummy(int /*i*/);
extern entity get_ith_array_prime(int /*i*/);
extern entity get_ith_template_dummy(int /*i*/);
extern entity get_ith_template_prime(int /*i*/);
extern entity get_ith_processor_dummy(int /*i*/);
extern entity get_ith_processor_prime(int /*i*/);
extern entity get_ith_block_dummy(int /*i*/);
extern entity get_ith_block_prime(int /*i*/);
extern entity get_ith_cycle_dummy(int /*i*/);
extern entity get_ith_cycle_prime(int /*i*/);
extern entity get_ith_local_dummy(int /*i*/);
extern entity get_ith_local_prime(int /*i*/);
extern entity get_ith_shift_dummy(int /*i*/);
extern entity get_ith_shift_prime(int /*i*/);
extern entity get_ith_auxiliary_dummy(int /*i*/);
extern entity get_ith_auxiliary_prime(int /*i*/);
extern entity get_ith_temporary_dummy(int /*i*/);
extern entity get_ith_temporary_prime(int /*i*/);
extern void hpfc_init_dummy_to_prime(void);
extern void hpfc_close_dummy_to_prime(void);
extern Psysteme shift_system_to_prime_variables(Psysteme /*s*/);
extern void make_hpfc_current_mappings(void);
extern void free_hpfc_current_mappings(void);
extern Psysteme compute_entity_to_declaration_constraints(entity /*ent*/, string /*suffix*/, string /*prefix*/);
extern Psysteme entity_to_declaration_constraints(entity /*e*/, tag /*what*/);
extern Psysteme hpfc_compute_unicity_constraints(entity /*e*/);
extern Psysteme entity_to_hpf_align_constraints(entity /*e*/);
extern Psysteme entity_to_hpf_distribute_constraints(entity /*e*/);
extern effect entity_to_region(statement /*stat*/, entity /*ent*/, tag /*act*/);
extern Psysteme hpfc_compute_entity_to_new_declaration(entity /*array*/);
extern Psysteme entity_to_new_declaration(entity /*array*/);
extern Psysteme generate_system_for_equal_variables(int /*n*/, entity (* /*gen1*/)(int), entity (* /*gen2*/)(int));
extern Psysteme hpfc_unstutter_dummies(entity /*array*/);
extern Psysteme generate_system_for_distributed_variable(entity /*v*/);
/* io-util.c */
extern bool only_io_map_undefined_p(void);
extern void set_only_io_map(statement_mapping /*m*/);
extern statement_mapping get_only_io_map(void);
extern void reset_only_io_map(void);
extern void free_only_io_map(void);
extern void make_only_io_map(void);
extern bool load_statement_only_io(statement /*s*/);
extern void delete_statement_only_io(statement /*s*/);
extern bool statement_only_io_undefined_p(statement /*s*/);
extern void store_statement_only_io(statement /*s*/, bool /*t*/);
extern void update_statement_only_io(statement /*s*/, bool /*t*/);
extern void hpfc_io_util_error_handler(void);
extern void only_io_mapping_initialize(statement /*program*/);
extern void generate_io_statements_for_distributed_arrays(entity /*array*/, tag /*move*/, Psysteme /*condition*/, Psysteme /*proc_echelon*/, Psysteme /*tile_echelon*/, list /*parameters*/, list /*processors*/, list /*scanners*/, list /*rebuild*/, statement */*psh*/, statement */*psn*/);
extern void generate_io_statements_for_shared_arrays(entity /*array*/, tag /*move*/, Psysteme /*condition*/, Psysteme /*echelon*/, list /*parameters*/, list /*scanners*/, list /*rebuild*/, statement */*psh*/, statement */*psn*/);
/* io-compile.c */
extern void hpfc_algorithm_row_echelon(Psysteme /*syst*/, list /*scanners*/, Psysteme */*pcond*/, Psysteme */*penum*/);
extern list make_list_of_dummy_variables(entity (* /*creation*/)(void), int /*number*/);
extern void remove_variables_if_possible(Psysteme */*psyst*/, list */*plvars*/);
extern void remove_variables_from_system(Psysteme */*ps*/, list */*plv*/);
extern void clean_the_system(Psysteme */*ps*/, list */*plrm*/, list */*pltry*/);
extern list simplify_deducable_variables(Psysteme /*syst*/, list /*vars*/, list */*pleftvars*/);
extern list hpfc_order_variables(list /*le*/, bool /*number_first*/);
extern void hpfc_algorithm_tiling(Psysteme /*syst*/, list /*processors*/, list /*scanners*/, Psysteme */*pcondition*/, Psysteme */*pproc_echelon*/, Psysteme */*ptile_echelon*/);
extern void hpfc_simplify_condition(Psysteme */*psc*/, statement /*stat*/, tag /*move*/);
extern void io_efficient_compile(statement /*stat*/, statement */*hp*/, statement */*np*/);
/* generate-util.c */
extern statement define_node_processor_id(entity /*proc*/, entity (* /*creation*/)(int));
extern statement generate_deducables(list /*le*/);
extern list hpfc_gen_n_vars_expr(entity (* /*creation*/)(void), int /*number*/);
extern expression make_reference_expression(entity /*e*/, entity (* /*creation*/)(void));
extern statement hpfc_add_n(entity /*var*/, int /*n*/);
extern statement hpfc_add_2(expression /*exp*/);
extern statement hpfc_message(expression /*tid*/, expression /*channel*/, bool /*send*/);
extern statement hpfc_lazy_guard(bool /*snd*/, statement /*then*/);
extern statement hpfc_generate_message(entity /*ld*/, bool /*send*/, bool /*lazy*/);
extern statement hpfc_initsend(bool /*lazy*/);
extern expression hpfc_buffer_reference(entity /*array*/, entity /*index*/);
extern statement hpfc_buffer_packing(entity /*array*/, entity (* /*creation*/)(void), bool /*pack*/);
extern statement hpfc_packing_of_current__buffer(entity /*array*/, bool /*pack*/);
extern statement hpfc_broadcast_if_necessary(entity /*array*/, entity /*trg*/, entity /*lid*/, entity /*proc*/, bool /*is_lazy*/);
extern statement hpfc_lazy_buffer_packing(entity /*src*/, entity /*trg*/, entity /*lid*/, entity /*proc*/, entity (* /*array_dim*/)(void), bool /*is_send*/, bool /*is_lazy*/);
extern statement hpfc_buffer_initialization(bool /*is_send*/, bool /*is_lazy*/, bool /*job_was_done*/);
extern statement hpfc_lazy_packing(entity /*array*/, entity /*lid*/, entity (* /*creation*/)(void), bool /*pack*/, bool /*lazy*/);
extern statement hpfc_compute_lid(entity /*lid*/, entity /*proc*/, entity (* /*creation*/)(void), entity /*array*/);
/* remapping.c */
extern Pcontrainte full_linearization(entity /*obj*/, entity /*var*/, int */*psize*/, entity (* /*create_var*/)(int), bool /*fortran_way*/, int /*initial_offset*/);
extern statement generate_all_liveness(entity /*primary*/, bool /*val*/);
extern statement root_statement_remapping_inits(statement /*root*/);
extern void remapping_compile(statement /*s*/, statement */*hsp*/, statement */*nsp*/);
/* host_node_entities.c */
extern bool new_host_undefined_p(void);
extern void reset_new_host(void);
extern void error_reset_new_host(void);
extern void set_new_host(entitymap /*o*/);
extern entitymap get_new_host(void);
extern void init_new_host(void);
extern void close_new_host(void);
extern void store_new_host(entity /*k*/, entity /*v*/);
extern void update_new_host(entity /*k*/, entity /*v*/);
extern entity load_new_host(entity /*k*/);
extern entity delete_new_host(entity /*k*/);
extern bool bound_new_host_p(entity /*k*/);
extern void store_or_update_new_host(entity /*k*/, entity /*v*/);
extern bool old_host_undefined_p(void);
extern void reset_old_host(void);
extern void error_reset_old_host(void);
extern void set_old_host(entitymap /*o*/);
extern entitymap get_old_host(void);
extern void init_old_host(void);
extern void close_old_host(void);
extern void store_old_host(entity /*k*/, entity /*v*/);
extern void update_old_host(entity /*k*/, entity /*v*/);
extern entity load_old_host(entity /*k*/);
extern entity delete_old_host(entity /*k*/);
extern bool bound_old_host_p(entity /*k*/);
extern void store_or_update_old_host(entity /*k*/, entity /*v*/);
extern bool new_node_undefined_p(void);
extern void reset_new_node(void);
extern void error_reset_new_node(void);
extern void set_new_node(entitymap /*o*/);
extern entitymap get_new_node(void);
extern void init_new_node(void);
extern void close_new_node(void);
extern void store_new_node(entity /*k*/, entity /*v*/);
extern void update_new_node(entity /*k*/, entity /*v*/);
extern entity load_new_node(entity /*k*/);
extern entity delete_new_node(entity /*k*/);
extern bool bound_new_node_p(entity /*k*/);
extern void store_or_update_new_node(entity /*k*/, entity /*v*/);
extern bool old_node_undefined_p(void);
extern void reset_old_node(void);
extern void error_reset_old_node(void);
extern void set_old_node(entitymap /*o*/);
extern entitymap get_old_node(void);
extern void init_old_node(void);
extern void close_old_node(void);
extern void store_old_node(entity /*k*/, entity /*v*/);
extern void update_old_node(entity /*k*/, entity /*v*/);
extern entity load_old_node(entity /*k*/);
extern entity delete_old_node(entity /*k*/);
extern bool bound_old_node_p(entity /*k*/);
extern void store_or_update_old_node(entity /*k*/, entity /*v*/);
extern void debug_host_node_variables(entity /*e*/);
extern void store_new_node_variable(entity /*new*/, entity /*old*/);
extern void store_new_host_variable(entity /*new*/, entity /*old*/);
extern void store_new_host_node_variable(entity /*neh*/, entity /*nen*/, entity /*old*/);
extern void init_entity_status(void);
extern entity_status get_entity_status(void);
extern void set_entity_status(entity_status /*s*/);
extern void reset_entity_status(void);
extern void close_entity_status(void);
extern string hpfc_module_suffix(entity /*module*/);
extern void update_object_for_module(void */*obj*/, entity /*module*/);
extern void update_list_for_module(list /*l*/, entity /*module*/);
extern expression UpdateExpressionForModule(entity /*module*/, expression /*ex*/);
extern list lUpdateExpr_but_distributed(entity /*module*/, list /*l*/);
extern list lUpdateExpr(entity /*module*/, list /*l*/);
extern list lNewVariableForModule(entity /*module*/, list /*le*/);
extern entity NewVariableForModule(entity /*module*/, entity /*e*/);
extern statement UpdateStatementForModule(entity /*module*/, statement /*stat*/);
/* special_cases.c */
extern bool hpfc_entity_reduction_p(entity /*e*/);
extern bool call_reduction_p(call /*c*/);
extern bool compile_reduction(statement /*initial*/, statement */*phost*/, statement */*pnode*/);
extern list handle_hpf_reduction(statement /*s*/);
extern list compile_hpf_reduction(list /*lr*/, bool /*prolog*/, bool /*host*/);
extern void free_vector_list(list /*l*/);
extern bool subarray_shift_p(statement /*s*/, entity */*pe*/, list */*plvect*/);
extern Psysteme get_read_effect_area(list /*le*/, entity /*var*/);
extern list make_rectangular_area(statement /*st*/, entity /*var*/);
extern statement generate_subarray_shift(statement /*s*/, entity /*var*/, list /*lshift*/);
extern void hpfc_special_cases_error_handler(void);
extern statement simple_statement(statement /*s*/);
extern bool full_define_p(reference /*r*/, list /*ll*/);
extern bool full_copy_p(statement /*s*/, reference */*pleft*/, reference */*pright*/);
extern statement generate_full_copy(reference /*left*/, reference /*right*/);
/* lattice_extraction.c */
extern void extract_lattice(Psysteme /*s*/, list /*scanners*/, list */*newscs*/, list */*ddc*/);
#endif /*  hpfc_header_included */
