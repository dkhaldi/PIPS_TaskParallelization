/* Warning! Do not modify this file that is automatically generated! */
/* Modify src/Libs/semantics/semantics-local.h instead, to add your own modifications. */

/* header file built by cproto */

#ifndef  semantics_header_included
#define  semantics_header_included
/*

  $Id: semantics-local.h 23065 2016-03-02 09:05:50Z coelho $

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
 /* include file for semantic analysis */

#define SEMANTICS_OPTIONS "?Otcfieod-D:"

#define SEQUENTIAL_TRANSFORMER_SUFFIX ".tran"
#define USER_TRANSFORMER_SUFFIX ".utran"
#define SEQUENTIAL_PRECONDITION_SUFFIX ".prec"
#define USER_PRECONDITION_SUFFIX ".uprec"
#define SEQUENTIAL_TOTAL_PRECONDITION_SUFFIX ".tprec"
#define USER_TOTAL_PRECONDITION_SUFFIX ".utprec"

extern bool refine_transformers_p;

typedef struct{
  gen_array_t indices;
  statement statement;
} path;

#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L) // C99
#define semantics_user_warning(...) \
  semantics_user_warning_func(CURRENT_FUNCTION, __VA_ARGS__)
#else
#define semantics_user_warning semantics_user_warning_func2
#endif

/* misc.c */
extern int call_site_count(entity /*m*/);
extern int caller_count(entity /*m*/);
extern int dynamic_call_count(entity /*m*/);
extern void semantics_user_warning_func(const char */*func_name*/, const char */*format*/, ...);
extern void semantics_user_warning_func2(const char */*format*/, ...);
/* ri_to_transformers.c */
extern transformer effects_to_transformer(list /*e*/);
extern transformer filter_transformer(transformer /*t*/, list /*e*/);
extern transformer dimensions_to_transformer(entity /*v*/, transformer /*pre*/);
extern transformer declaration_to_transformer(entity /*v*/, transformer /*pre*/);
extern transformer declarations_to_transformer(list /*dl*/, transformer /*pre*/);
extern list effects_to_arguments(list /*fx*/);
extern transformer intrinsic_to_transformer(entity /*e*/, list /*pc*/, transformer /*pre*/, list /*ef*/);
extern transformer call_to_transformer(call /*c*/, transformer /*pre*/, list /*ef*/);
extern transformer user_function_call_to_transformer(entity /*e*/, expression /*expr*/, transformer /*pre*/);
extern transformer generic_transformer_intra_to_inter(transformer /*tf*/, list /*le*/, bool /*preserve_rv_p*/);
extern transformer transformer_intra_to_inter(transformer /*tf*/, list /*le*/);
extern unsigned int number_of_usable_functional_parameters(list /*pl*/);
extern transformer any_user_call_site_to_transformer(entity /*f*/, list /*pc*/, transformer /*pre*/, list /*ef*/);
extern transformer c_user_call_to_transformer(entity /*f*/, list /*pc*/, transformer /*pre*/, list /*ef*/);
extern transformer fortran_user_call_to_transformer(entity /*f*/, list /*pc*/, list /*ef*/);
extern transformer user_call_to_transformer(entity /*f*/, list /*pc*/, transformer /*pre*/, list /*ef*/);
extern transformer c_return_to_transformer(entity /*e*/, list /*pc*/, list /*ef*/, transformer /*pre*/);
extern transformer assigned_expression_to_transformer(entity /*v*/, expression /*expr*/, transformer /*pre*/);
extern transformer safe_assigned_expression_to_transformer(entity /*v*/, expression /*expr*/, transformer /*pre*/);
extern transformer integer_assign_to_transformer(expression /*lhs*/, expression /*rhs*/, transformer /*pre*/, list /*ef*/);
extern transformer any_scalar_assign_to_transformer_without_effect(entity /*v*/, expression /*rhs*/, transformer /*pre*/);
extern transformer any_scalar_assign_to_transformer(entity /*v*/, expression /*rhs*/, list /*ef*/, transformer /*pre*/);
extern transformer transformer_apply_field_assignments(transformer /*t*/, reference /*l*/, reference /*r*/, type /*st*/);
extern transformer transformer_apply_unknown_field_assignments(transformer /*t*/, reference /*l*/, type /*st*/);
extern transformer struct_reference_assignment_to_transformer(reference /*r*/, type /*t*/, expression /*rhs*/, transformer /*pre*/, list /*ef*/);
extern transformer struct_variable_assignment_to_transformer(entity /*v*/, type /*t*/, expression /*rhs*/, transformer /*pre*/, list /*ef*/);
extern transformer any_assign_to_transformer(list /*args*/, list /*ef*/, transformer /*pre*/);
extern transformer any_update_to_transformer(entity /*op*/, list /*args*/, list /*ef*/, transformer /*pre*/);
extern transformer any_basic_update_to_transformer(entity /*op*/, list /*args*/, list /*ef*/, transformer /*pre*/);
extern transformer complete_statement_transformer(transformer /*t*/, transformer /*pre*/, statement /*s*/);
extern transformer complete_non_identity_statement_transformer(transformer /*t*/, transformer /*pre*/, statement /*s*/);
extern transformer generic_complete_statement_transformer(transformer /*t*/, transformer /*pre*/, statement /*s*/, bool /*identity_p*/);
extern transformer statement_to_transformer(statement /*s*/, transformer /*spre*/);
/* interprocedural.c */
extern transformer get_module_precondition(entity /*m*/);
extern void add_module_call_site_precondition(entity /*m*/, transformer /*p*/);
extern list module_to_formal_analyzable_parameters(entity /*f*/);
extern bool same_analyzable_type_scalar_entity_list_p(list /*l*/);
extern transformer add_formal_to_actual_bindings(call /*c*/, transformer /*pre*/, entity /*caller*/);
extern transformer new_add_formal_to_actual_bindings(call /*c*/, transformer /*pre*/, entity /*caller*/);
extern transformer precondition_intra_to_inter(entity /*callee*/, transformer /*pre*/, list /*le*/);
extern void translate_global_values(entity /*m*/, transformer /*tf*/);
extern void translate_global_value(entity /*m*/, transformer /*tf*/, entity /*v*/);
extern void expressions_to_summary_precondition(transformer /*pre*/, list /*le*/);
extern void expression_to_summary_precondition(transformer /*pre*/, expression /*e*/);
extern void call_to_summary_precondition(transformer /*pre*/, call /*c*/);
extern text call_site_to_module_precondition_text(entity /*caller*/, entity /*callee*/, statement /*s*/, call /*c*/);
extern void reset_call_site_number(void);
extern int get_call_site_number(void);
extern void update_summary_precondition_in_declaration(expression /*e*/, transformer /*pre*/);
extern transformer update_precondition_with_call_site_preconditions(transformer /*t*/, entity /*caller*/, entity /*callee*/);
extern transformer value_passing_summary_transformer(entity /*f*/, transformer /*tf*/);
/* ri_to_preconditions.c */
extern list get_module_global_arguments(void);
extern void set_module_global_arguments(list /*args*/);
extern list effects_to_entity_list(list /*lef*/);
extern transformer data_to_precondition(entity /*m*/);
extern transformer all_data_to_precondition(entity /*m*/);
extern void precondition_add_reference_information(transformer /*pre*/, statement /*s*/);
extern void transformer_add_reference_information(transformer /*tf*/, statement /*s*/);
extern void precondition_add_type_information(transformer /*pre*/);
extern transformer statement_to_postcondition(transformer /*pre*/, statement /*s*/);
extern transformer propagate_preconditions_in_declarations(list /*dl*/, transformer /*pre*/, void (* /*process_initial_expression*/)(expression, transformer));
/* mappings.c */
extern transformer tf_equivalence_equalities_add(transformer /*tf*/);
extern void add_equivalenced_values(entity /*e*/, entity /*eq*/, bool /*readonly*/);
extern void add_intraprocedural_value_entities(entity /*e*/);
extern void add_or_kill_equivalenced_variables(entity /*e*/, bool /*readonly*/);
extern void add_implicit_interprocedural_write_effects(entity /*al*/, list /*el*/);
extern void module_to_value_mappings(entity /*m*/);
extern bool value_mappings_compatible_vector_p(Pvecteur /*iv*/);
extern list variables_to_values(list /*list_mod*/);
extern list variable_to_values(entity /*e*/);
extern list dynamic_variables_to_values(list /*list_mod*/);
extern list variables_to_old_values(list /*list_mod*/);
extern void variables_to_new_values(Pvecteur /*v*/);
extern void upwards_vect_rename(Pvecteur /*v*/, transformer /*post*/);
/* dbm_interface.c */
extern bool transformer_map_undefined_p(void);
extern void set_transformer_map(statement_mapping /*m*/);
extern statement_mapping get_transformer_map(void);
extern void reset_transformer_map(void);
extern void free_transformer_map(void);
extern void make_transformer_map(void);
extern transformer load_statement_transformer(statement /*s*/);
extern void delete_statement_transformer(statement /*s*/);
extern bool statement_transformer_undefined_p(statement /*s*/);
extern void store_statement_transformer(statement /*s*/, transformer /*t*/);
extern void update_statement_transformer(statement /*s*/, transformer /*t*/);
extern bool precondition_map_undefined_p(void);
extern void set_precondition_map(statement_mapping /*m*/);
extern statement_mapping get_precondition_map(void);
extern void reset_precondition_map(void);
extern void free_precondition_map(void);
extern void make_precondition_map(void);
extern transformer load_statement_precondition(statement /*s*/);
extern void delete_statement_precondition(statement /*s*/);
extern bool statement_precondition_undefined_p(statement /*s*/);
extern void store_statement_precondition(statement /*s*/, transformer /*t*/);
extern void update_statement_precondition(statement /*s*/, transformer /*t*/);
extern bool total_precondition_map_undefined_p(void);
extern void set_total_precondition_map(statement_mapping /*m*/);
extern statement_mapping get_total_precondition_map(void);
extern void reset_total_precondition_map(void);
extern void free_total_precondition_map(void);
extern void make_total_precondition_map(void);
extern transformer load_statement_total_precondition(statement /*s*/);
extern void delete_statement_total_precondition(statement /*s*/);
extern bool statement_total_precondition_undefined_p(statement /*s*/);
extern void store_statement_total_precondition(statement /*s*/, transformer /*t*/);
extern void update_statement_total_precondition(statement /*s*/, transformer /*t*/);
extern transformer load_completed_statement_transformer(statement /*s*/);
extern void add_declaration_list_information(transformer /*pre*/, list /*dl*/, bool /*precondition_p*/);
extern bool transformers_intra_fast(char */*module_name*/);
extern bool transformers_intra_full(char */*module_name*/);
extern bool transformers_inter_fast(char */*module_name*/);
extern bool transformers_inter_full(char */*module_name*/);
extern bool transformers_inter_full_with_points_to(char */*module_name*/);
extern bool refine_transformers_p;
extern bool refine_transformers(char */*module_name*/);
extern bool refine_transformers_with_points_to(char */*module_name*/);
extern bool summary_transformer(char */*module_name*/);
extern bool preconditions_intra(char */*module_name*/);
extern bool preconditions_intra_fast(char */*module_name*/);
extern bool preconditions_inter_fast(char */*module_name*/);
extern bool preconditions_inter_full(char */*module_name*/);
extern bool preconditions_inter_full_with_points_to(char */*module_name*/);
extern bool total_preconditions_intra(char */*module_name*/);
extern bool total_preconditions_inter(char */*module_name*/);
extern bool old_summary_precondition(char */*module_name*/);
extern bool intraprocedural_summary_precondition(char */*module_name*/);
extern bool interprocedural_summary_precondition(char */*module_name*/);
extern bool use_points_to_p(void);
extern bool interprocedural_summary_precondition_with_points_to(char */*module_name*/);
extern bool summary_precondition(char */*module_name*/);
extern bool summary_total_postcondition(char */*module_name*/);
extern bool summary_total_precondition(char */*module_name*/);
extern void set_warning_counters(void);
extern bool test_warning_counters(void);
extern bool generic_module_name_to_transformers(const char */*module_name*/, bool /*in_context*/);
extern bool module_name_to_transformers_in_context(const char */*module_name*/);
extern bool module_name_to_transformers(const char */*module_name*/);
extern bool module_name_to_preconditions(const char */*module_name*/);
extern bool module_name_to_total_preconditions(const char */*module_name*/);
extern transformer load_summary_transformer(entity /*e*/);
extern void update_summary_precondition(entity /*e*/, transformer /*t*/);
extern transformer load_summary_precondition(entity /*e*/);
extern transformer load_summary_total_postcondition(entity /*e*/);
extern list load_summary_effects(entity /*e*/);
extern list load_body_effects(entity /*e*/);
extern list load_module_intraprocedural_effects(entity /*e*/);
extern void cumulated_effects_map_print(void);
/* prettyprint.c */
extern bool semantic_map_undefined_p(void);
extern void set_semantic_map(statement_mapping /*m*/);
extern statement_mapping get_semantic_map(void);
extern void reset_semantic_map(void);
extern void free_semantic_map(void);
extern void make_semantic_map(void);
extern transformer load_statement_semantic(statement /*s*/);
extern void delete_statement_semantic(statement /*s*/);
extern bool statement_semantic_undefined_p(statement /*s*/);
extern void store_statement_semantic(statement /*s*/, transformer /*t*/);
extern void update_statement_semantic(statement /*s*/, transformer /*t*/);
extern void set_prettyprint_transformer(void);
extern bool print_code_transformers(const char */*module_name*/);
extern bool print_code_as_a_graph_transformers(const string /*mod_name*/);
extern bool print_code_preconditions(const char */*module_name*/);
extern bool print_code_as_a_graph_preconditions(const string /*mod_name*/);
extern bool print_code_total_preconditions(const char */*module_name*/);
extern bool print_code_as_a_graph_total_preconditions(const string /*mod_name*/);
extern bool print_source_transformers(const char */*module_name*/);
extern bool print_source_preconditions(const char */*module_name*/);
extern bool print_source_total_preconditions(const char */*module_name*/);
extern text get_text_transformers(const string /*module_name*/);
extern text get_text_preconditions(const string /*module_name*/);
extern text get_text_total_preconditions(const string /*module_name*/);
extern text semantic_to_text(entity /*module*/, int /*margin*/, statement /*stmt*/);
extern text text_transformer(transformer /*tran*/);
extern text text_for_a_transformer(transformer /*tran*/, bool /*is_a_transformer*/);
extern text string_predicate_to_commentary(string /*str_pred*/, string /*comment_prefix*/);
extern text words_predicate_to_commentary(list /*w_pred*/, string /*comment_prefix*/);
extern sentence make_pred_commentary_sentence(string /*str_pred*/, string /*comment_prefix*/);
extern bool print_call_graph_with_transformers(const string /*module_name*/);
extern bool print_call_graph_with_preconditions(const string /*module_name*/);
extern bool print_call_graph_with_total_preconditions(const string /*module_name*/);
extern bool print_icfg_with_preconditions(const string /*module_name*/);
extern bool print_icfg_with_transformers(const string /*module_name*/);
extern bool print_icfg_with_loops_preconditions(const string /*module_name*/);
extern bool print_icfg_with_loops_transformers(const string /*module_name*/);
extern bool print_icfg_with_control_preconditions(const string /*module_name*/);
extern bool print_icfg_with_control_transformers(const string /*module_name*/);
extern bool print_icfg_with_total_preconditions(const string /*module_name*/);
extern bool print_icfg_with_loops_total_preconditions(const string /*module_name*/);
extern bool print_icfg_with_control_total_preconditions(const string /*module_name*/);
/* postcondition.c */
extern bool postcondition_map_undefined_p(void);
extern void set_postcondition_map(statement_mapping /*m*/);
extern statement_mapping get_postcondition_map(void);
extern void reset_postcondition_map(void);
extern void free_postcondition_map(void);
extern void make_postcondition_map(void);
extern transformer load_statement_postcondition(statement /*s*/);
extern void delete_statement_postcondition(statement /*s*/);
extern bool statement_postcondition_undefined_p(statement /*s*/);
extern void store_statement_postcondition(statement /*s*/, transformer /*t*/);
extern void update_statement_postcondition(statement /*s*/, transformer /*t*/);
extern statement_mapping compute_postcondition(statement /*stat*/, statement_mapping /*post_map*/, statement_mapping /*pre_map*/);
/* utils.c */
extern bool statement_weakly_feasible_p(statement /*s*/);
extern bool statement_feasible_p(statement /*s*/);
extern bool statement_strongly_feasible_p(statement /*s*/);
extern bool empty_range_wrt_precondition_p(range /*r*/, transformer /*p*/);
extern bool non_empty_range_wrt_precondition_p(range /*r*/, transformer /*p*/);
extern bool check_range_wrt_precondition(range /*r*/, transformer /*p*/, bool /*check_empty*/);
extern bool condition_true_wrt_precondition_p(expression /*c*/, transformer /*p*/);
extern bool condition_false_wrt_precondition_p(expression /*c*/, transformer /*p*/);
extern bool check_condition_wrt_precondition(expression /*c*/, transformer /*pre*/, bool /*check_true*/);
extern void expression_and_precondition_to_integer_interval(expression /*e*/, transformer /*p*/, int */*plb*/, int */*pub*/);
extern void integer_expression_and_precondition_to_integer_interval(expression /*e*/, transformer /*p*/, int */*plb*/, int */*pub*/);
extern void integer_value_and_precondition_to_integer_interval(entity /*v*/, transformer /*p*/, int */*plb*/, int */*pub*/);
/* initial.c */
extern bool initial_precondition(string /*name*/);
extern bool program_precondition(const string /*name*/);
extern bool program_postcondition(const string /*name*/);
extern bool print_initial_precondition(const string /*name*/);
extern bool print_program_precondition(const string /*name*/);
/* unstructured.c */
extern void print_control_postcondition_map(control_mapping /*control_postcondition_map*/);
extern transformer load_cycle_fix_point(control /*c*/, hash_table /*fix_point_map*/);
extern void update_temporary_precondition(void */*k*/, transformer /*pre*/, hash_table /*precondition_map*/);
extern void update_statement_temporary_precondition(statement /*s*/, transformer /*pre*/, statement_mapping /*statement_temporary_precondition_map*/);
extern void print_statement_temporary_precondition(statement_mapping /*statement_temporary_precondition_map*/);
extern void update_cycle_temporary_precondition(control /*c*/, transformer /*pre*/, control_mapping /*cycle_temporary_precondition_map*/);
extern transformer load_cycle_temporary_precondition(control /*c*/, control_mapping /*cycle_temporary_precondition_map*/, hash_table /*ancestor_map*/, hash_table /*scc_map*/);
extern transformer load_statement_temporary_precondition(statement /*s*/, statement_mapping /*statement_temporary_precondition_map*/);
extern transformer dag_or_cycle_to_flow_sensitive_postconditions_or_transformers(list /*partition*/, unstructured /*ndu*/, hash_table /*ancestor_map*/, hash_table /*scc_map*/, control_mapping /*fix_point_map*/, transformer /*e_pre*/, transformer /*n_pre*/, hash_table /*control_postcondition_map*/, bool /*postcondition_p*/, bool /*is_dag*/);
extern transformer dag_to_flow_sensitive_postconditions_or_transformers(list /*partition*/, unstructured /*ndu*/, hash_table /*ancestor_map*/, hash_table /*scc_map*/, control_mapping /*fix_point_map*/, transformer /*e_pre*/, transformer /*n_pre*/, hash_table /*control_postcondition_map*/, bool /*postcondition_p*/);
extern transformer cycle_to_flow_sensitive_postconditions_or_transformers(list /*partition*/, unstructured /*ndu*/, hash_table /*ancestor_map*/, hash_table /*scc_map*/, control_mapping /*fix_point_map*/, transformer /*e_pre*/, transformer /*n_pre*/, hash_table /*control_postcondition_map*/, bool /*postcondition_p*/);
extern transformer unstructured_to_flow_sensitive_postconditions_or_transformers(transformer /*pre_u*/, transformer /*pre*/, unstructured /*u*/, bool /*postcondition_p*/);
extern transformer unstructured_to_flow_sensitive_postconditions(transformer /*pre_u*/, transformer /*pre*/, unstructured /*u*/);
extern transformer unstructured_to_postcondition(transformer /*pre*/, unstructured /*u*/, transformer /*tf*/);
extern transformer unstructured_to_flow_insensitive_transformer(unstructured /*u*/);
extern transformer unstructured_to_transformer(unstructured /*u*/, transformer /*e_pre*/, list /*e*/);
extern transformer unstructured_to_flow_sensitive_total_preconditions(transformer /*t_post_u*/, transformer /*pre*/, unstructured /*u*/);
/* expression.c */
extern transformer generic_reference_to_transformer(entity /*v*/, reference /*r*/, transformer /*pre*/, bool /*is_internal*/);
extern transformer any_basic_update_operation_to_transformer(entity /*tmp*/, entity /*v*/, entity /*op*/);
extern transformer any_assign_operation_to_transformer(entity /*tmp*/, list /*args*/, transformer /*pre*/, bool /*is_internal*/);
extern transformer safe_any_assign_operation_to_transformer(entity /*tmp*/, list /*args*/, transformer /*pre*/, bool /*is_internal*/);
extern transformer transformer_add_condition_information(transformer /*pre*/, expression /*c*/, transformer /*context*/, bool /*veracity*/);
extern transformer precondition_add_condition_information(transformer /*pre*/, expression /*c*/, transformer /*context*/, bool /*veracity*/);
extern transformer transformer_add_domain_condition(transformer /*tf*/, expression /*c*/, transformer /*context*/, bool /*veracity*/);
extern transformer transformer_add_range_condition(transformer /*tf*/, expression /*c*/, transformer /*context*/, bool /*veracity*/);
extern transformer simple_affine_to_transformer(entity /*e*/, Pvecteur /*a*/, bool /*is_internal*/);
extern transformer affine_to_transformer(entity /*e*/, Pvecteur /*a*/, bool /*assignment*/);
extern transformer affine_increment_to_transformer(entity /*e*/, Pvecteur /*a*/);
extern transformer modulo_by_a_constant_to_transformer(entity /*v1*/, transformer /*prec*/, entity /*v2*/, int /*k*/);
extern transformer assign_operation_to_transformer(entity /*val*/, expression /*lhs*/, expression /*rhs*/, transformer /*pre*/);
extern transformer points_to_unary_operation_to_transformer(entity /*e*/, entity /*op*/, expression /*e1*/, transformer /*pre*/, bool /*is_internal*/, bool /*is_pointer*/);
extern transformer expression_effects_to_transformer(expression /*expr*/);
extern transformer integer_expression_to_transformer(entity /*v*/, expression /*expr*/, transformer /*pre*/, bool /*is_internal*/);
extern transformer safe_integer_expression_to_transformer(entity /*v*/, expression /*expr*/, transformer /*pre*/, bool /*is_internal*/);
extern transformer transformer_logical_inequalities_add(transformer /*tf*/, entity /*v*/);
extern transformer logical_intrinsic_to_transformer(entity /*v*/, call /*c*/, transformer /*pre*/, bool /*is_internal*/);
extern transformer logical_expression_to_transformer(entity /*v*/, expression /*rhs*/, transformer /*pre*/, bool /*is_internal*/);
extern transformer string_expression_to_transformer(entity /*v*/, expression /*rhs*/);
extern transformer float_expression_to_transformer(entity /*v*/, expression /*rhs*/, transformer /*pre*/, bool /*is_internal*/);
extern transformer pointer_expression_to_transformer(entity /*v*/, expression /*expr*/, transformer /*pre*/, bool /*is_internal*/);
extern transformer transformer_add_any_relation_information(transformer /*pre*/, entity /*op*/, expression /*e1*/, expression /*e2*/, transformer /*context*/, bool /*veracity*/, bool /*upwards*/);
extern transformer any_expression_side_effects_to_transformer(expression /*e*/, transformer /*p*/, bool /*is_internal*/);
extern transformer any_expressions_side_effects_to_transformer(list /*el*/, transformer /*p*/, bool /*is_internal*/);
extern transformer safe_any_expression_side_effects_to_transformer(expression /*e*/, transformer /*p*/, bool /*is_internal*/);
extern transformer any_expression_to_transformer(entity /*v*/, expression /*expr*/, transformer /*pre*/, bool /*is_internal*/);
extern transformer safe_any_expression_to_transformer(entity /*v*/, expression /*expr*/, transformer /*pre*/, bool /*is_internal*/);
extern transformer expression_to_transformer(expression /*exp*/, transformer /*pre*/, list /*el*/);
extern transformer safe_expression_to_transformer(expression /*exp*/, transformer /*pre*/);
extern transformer condition_to_transformer(expression /*cond*/, transformer /*pre*/, bool /*veracity*/);
extern transformer conditional_to_transformer(expression /*cond*/, expression /*te*/, expression /*fe*/, transformer /*pre*/, list /*ef*/);
extern transformer any_conditional_to_transformer(entity /*v*/, list /*args*/, transformer /*pre*/);
extern transformer logical_not_to_transformer(entity /*v*/, list /*args*/, transformer /*pre*/);
extern transformer bitwise_xor_to_transformer(entity /*v*/, list /*args*/, transformer /*pre*/);
extern transformer expressions_to_transformer(list /*expl*/, transformer /*pre*/);
extern transformer any_expressions_to_transformer(entity /*v*/, list /*expl*/, transformer /*pre*/);
extern bool precondition_minmax_of_value(entity /*val*/, transformer /*tr*/, intptr_t */*pmin*/, intptr_t */*pmax*/);
extern bool precondition_minmax_of_expression(expression /*exp*/, transformer /*tr*/, intptr_t */*pmin*/, intptr_t */*pmax*/);
extern void simplify_minmax_expression(expression /*e*/, transformer /*tr*/);
extern bool false_condition_wrt_precondition_p(expression /*c*/, transformer /*pre*/);
extern bool true_condition_wrt_precondition_p(expression /*c*/, transformer /*pre*/);
extern bool eval_condition_wrt_precondition_p(expression /*c*/, transformer /*pre*/, bool /*veracity*/);
extern transformer transformer_add_integer_relation_information(transformer /*pre*/, entity /*relop*/, expression /*e1*/, expression /*e2*/, bool /*veracity*/, bool /*upwards*/);
extern int simplify_boolean_expression_with_precondition(expression /*e*/, transformer /*p*/);
extern bool semantics_usable_points_to_reference_p(reference /*rlhs*/, expression /*lhs*/, int /*n*/);
extern transformer lhs_expression_to_transformer(entity /*e*/, expression /*lhs*/, transformer /*pre*/);
/* loop.c */
extern transformer any_loop_to_k_transformer(transformer /*t_init*/, transformer /*t_enter*/, transformer /*t_next*/, statement /*body*/, list /*lel*/, transformer /*post_init*/, int /*k*/);
extern transformer any_loop_to_transformer(transformer /*t_init*/, transformer /*t_enter*/, transformer /*t_next*/, statement /*body*/, list /*lel*/, transformer /*post_init*/);
extern transformer forloop_to_transformer(forloop /*fl*/, transformer /*pre*/, list /*flel*/);
extern list forloop_to_transformer_list(forloop /*l*/, transformer /*pre*/, list /*e*/);
extern transformer new_whileloop_to_transformer(whileloop /*wl*/, transformer /*pre*/, list /*wlel*/);
extern transformer new_whileloop_to_k_transformer(whileloop /*wl*/, transformer /*pre*/, list /*wlel*/, int /*k*/);
extern transformer repeatloop_to_transformer(whileloop /*wl*/, transformer /*pre*/, list /*wlel*/);
extern transformer add_loop_skip_condition(transformer /*tf*/, loop /*l*/, transformer /*pre*/);
extern transformer add_index_range_conditions(transformer /*pre*/, entity /*i*/, range /*r*/, transformer /*tfb*/);
extern transformer add_loop_index_exit_value(transformer /*post*/, loop /*l*/, transformer /*pre*/);
extern bool simple_dead_loop_p(expression /*lower*/, expression /*upper*/);
extern transformer precondition_filter_old_values(transformer /*pre*/);
extern transformer transformer_add_loop_index_initialization(transformer /*tf*/, loop /*l*/, transformer /*pre*/);
extern transformer transformer_add_loop_index_incrementation(transformer /*tf*/, loop /*l*/, transformer /*pre*/);
extern transformer loop_bound_evaluation_to_transformer(loop /*l*/, transformer /*pre*/);
extern transformer loop_initialization_to_transformer(loop /*l*/, transformer /*pre*/);
extern transformer loop_to_transformer(loop /*l*/, transformer /*pre*/, list /*e*/);
extern list loop_to_transformer_list(loop /*l*/, transformer /*pre*/, list /*e*/);
extern transformer loop_to_initialization_transformer(loop /*l*/, transformer /*pre*/);
extern transformer loop_to_enter_transformer(loop /*l*/, transformer /*pre*/);
extern transformer loop_to_continue_transformer(loop /*l*/, transformer /*pre*/);
extern transformer new_loop_to_transformer(loop /*l*/, transformer /*pre*/, list /*lel*/);
extern list complete_any_loop_transformer_list(transformer /*t_init*/, transformer /*t_skip*/, transformer /*t_body_star*/, transformer /*t_body*/, transformer /*t_inc*/, transformer /*t_exit*/);
extern transformer complete_any_loop_transformer(transformer /*t_init*/, transformer /*t_enter*/, transformer /*t_skip*/, transformer /*t_body_star*/, transformer /*t_body*/, transformer /*t_continue*/, transformer /*t_inc*/, transformer /*t_exit*/);
extern transformer complete_forloop_transformer(transformer /*t_body_star*/, transformer /*pre*/, forloop /*fl*/);
extern list complete_forloop_transformer_list(transformer /*t_body_star*/, transformer /*pre*/, forloop /*fl*/);
extern list new_complete_whileloop_transformer_list(transformer /*t_body_star*/, transformer /*pre*/, whileloop /*wl*/, bool /*entered_p*/);
extern transformer new_complete_whileloop_transformer(transformer /*t_body_star*/, transformer /*pre*/, whileloop /*wl*/, bool /*entered_p*/);
extern list complete_repeatloop_transformer_list(transformer /*t_body_star*/, transformer /*pre*/, whileloop /*wl*/);
extern transformer complete_repeatloop_transformer(transformer /*t_body_star*/, transformer /*pre*/, whileloop /*wl*/);
extern transformer complete_loop_transformer(transformer /*ltf*/, transformer /*pre*/, loop /*l*/);
extern list complete_loop_transformer_list(transformer /*ltf*/, transformer /*pre*/, loop /*l*/);
extern transformer complete_whileloop_transformer(transformer /*ltf*/, transformer /*pre*/, whileloop /*wl*/);
extern list complete_whileloop_transformer_list(transformer /*ltf*/, transformer /*pre*/, whileloop /*wl*/);
extern transformer old_complete_whileloop_transformer(transformer /*ltf*/, transformer /*pre*/, whileloop /*l*/);
extern transformer standard_whileloop_to_transformer(whileloop /*l*/, transformer /*pre*/, list /*e*/);
extern transformer whileloop_to_transformer(whileloop /*l*/, transformer /*pre*/, list /*e*/);
extern transformer whileloop_to_k_transformer(whileloop /*l*/, transformer /*pre*/, list /*e*/, int /*k*/);
extern transformer any_loop_to_postcondition(statement /*body*/, transformer /*t_init*/, transformer /*t_enter*/, transformer /*t_skip*/, transformer /*t_body_star*/, transformer /*t_body*/, transformer /*t_next*/, transformer /*t_inc*/, transformer /*t_exit*/, transformer /*pre*/);
extern transformer forloop_to_postcondition(transformer /*pre*/, forloop /*fl*/, transformer /*t_body_star*/);
extern transformer repeatloop_to_postcondition(transformer /*pre*/, whileloop /*wl*/, transformer /*t_body_star*/);
extern transformer loop_to_postcondition(transformer /*pre*/, loop /*l*/, transformer /*tf*/);
extern transformer loop_to_total_precondition(transformer /*t_post*/, loop /*l*/, transformer /*tf*/, transformer /*context*/);
extern transformer whileloop_to_postcondition(transformer /*pre*/, whileloop /*l*/, transformer /*tf*/);
extern transformer whileloop_to_total_precondition(transformer /*t_post*/, whileloop /*l*/, transformer /*tf*/, transformer /*context*/);
/* ri_to_total_preconditions.c */
extern transformer statement_to_total_precondition(transformer /*t_post*/, statement /*s*/);
/* ri_to_transformer_lists.c */
extern list declaration_to_transformer_list(entity /*v*/, transformer /*pre*/);
extern list declarations_to_transformer_list(list /*dl*/, transformer /*pre*/);
extern list intrinsic_to_transformer_list(entity /*e*/, list /*pc*/, transformer /*pre*/, list /*ef*/);
extern list assigned_expression_to_transformer_list(entity /*v*/, expression /*expr*/, transformer /*pre*/);
extern list safe_assigned_expression_to_transformer_list(entity /*v*/, expression /*expr*/, transformer /*pre*/);
extern list integer_assign_to_transformer_list(expression /*lhs*/, expression /*rhs*/, transformer /*pre*/, list /*ef*/);
extern list any_scalar_assign_to_transformer_list(entity /*v*/, expression /*rhs*/, list /*ef*/, transformer /*pre*/);
extern list any_assign_to_transformer_list(list /*args*/, list /*ef*/, transformer /*pre*/);
extern list any_update_to_transformer_list(entity /*op*/, list /*args*/, list /*ef*/, transformer /*pre*/);
extern list any_basic_update_to_transformer_list(entity /*op*/, list /*args*/, list /*ef*/, transformer /*pre*/);
extern list statement_to_transformer_list(statement /*s*/, transformer /*spre*/);
/* path_transformer.c */
extern void path_initialize(statement /*s*/, statement /*sbegin*/, statement /*send*/, path */*pb*/, path */*pe*/);
extern transformer path_transformer_on(statement /*s*/, path /*pbegin*/, path /*pend*/, int /*m*/);
extern transformer compute_path_transformer(statement /*s*/, path /*pbegin*/, path /*pend*/);
extern bool path_transformer(const string /*module_name*/);
/* type.c */
extern void transformer_add_type_information(transformer /*tf*/);
extern void transformer_add_variable_type_information(transformer /*tf*/, entity /*v*/);
/* points_to.c */
extern list semantics_expression_to_points_to_sources(expression /*e*/);
extern list semantics_expression_to_points_to_sinks(expression /*e*/);
extern transformer substitute_scalar_stub_in_transformer(transformer /*tf*/, entity /*se*/, entity /*de*/, bool /*backward_p*/, list */*ppl*/);
extern transformer substitute_stubs_in_transformer(transformer /*tf*/, call /*c*/, statement /*s*/, bool /*backward_p*/);
#endif /*  semantics_header_included */
