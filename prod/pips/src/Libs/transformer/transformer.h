/* Warning! Do not modify this file that is automatically generated! */
/* Modify src/Libs/transformer/transformer-local.h instead, to add your own modifications. */

/* header file built by cproto */

#ifndef  transformer_header_included
#define  transformer_header_included
/*

  $Id: transformer-local.h 23065 2016-03-02 09:05:50Z coelho $

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
 /* include file for transformer library
  */

/* prefix used for value entity names; no conflict should occur with user
 * function names as long as they are restricted to 6 characters
 */
#define SEMANTICS_MODULE_NAME "*SEMANTICS*"

/* Must be used in suffixes and prefixes below */
#define SEMANTICS_SEPARATOR '#'

/* internal entity names (FI: I should have used suffixes to be consistent with external
 * suffixes */
#define OLD_VALUE_PREFIX "o#"
#define INTERMEDIATE_VALUE_PREFIX "i#"
#define TEMPORARY_VALUE_PREFIX "t#"

/* external suffixes (NEW_VALUE_SUFFIX is not used, new values are represented
 * by the variable itself, i.e. new value suffix is the empty string "")
 */
#define NEW_VALUE_SUFFIX "#new"
#define OLD_VALUE_SUFFIX "#init"
#define INTERMEDIATE_VALUE_SUFFIX "#int"

#define ADDRESS_OF_SUFFIX "#addressof"

#define SIZEOF_SUFFIX "#sizeof"
/* basic.c */
extern transformer transformer_dup(transformer /*t_in*/);
extern void transformer_free(transformer /*t*/);
extern void free_transformers(transformer /*t*/, ...);
extern void old_transformer_free(transformer /*t*/);
extern transformer transformer_identity(void);
extern transformer transformer_empty(void);
extern transformer empty_transformer(transformer /*t*/);
extern bool transformer_identity_p(transformer /*t*/);
extern bool transformer_is_empty_p(transformer /*t*/);
extern bool transformer_is_rn_p(transformer /*t*/);
extern transformer transformer_add_sign_information(transformer /*tf*/, entity /*v*/, int /*v_sign*/);
extern transformer transformer_add_variable_incrementation(transformer /*t*/, entity /*i*/, Pvecteur /*incr*/);
extern transformer transformer_add_variable_update(transformer /*t*/, entity /*v*/);
extern transformer transformer_add_value_update(transformer /*t*/, entity /*v*/);
extern transformer transformer_add_variables_update(transformer /*t*/, list /*vl*/);
extern transformer transformer_constraint_add(transformer /*tf*/, Pvecteur /*i*/, bool /*equality*/);
extern transformer transformer_inequality_add(transformer /*tf*/, Pvecteur /*i*/);
extern transformer transformer_equality_add(transformer /*tf*/, Pvecteur /*i*/);
extern transformer transformer_equalities_add(transformer /*tf*/, Pcontrainte /*eqs*/);
extern transformer transformer_inequalities_add(transformer /*tf*/, Pcontrainte /*ineqs*/);
extern transformer transformer_add_identity(transformer /*tf*/, entity /*v*/);
extern transformer transformer_add_equality(transformer /*tf*/, entity /*v1*/, entity /*v2*/);
extern transformer transformer_add_equality_with_integer_constant(transformer /*tf*/, entity /*v*/, long long int /*cst*/);
extern transformer transformer_add_inequality(transformer /*tf*/, entity /*v1*/, entity /*v2*/, bool /*strict_p*/);
extern transformer transformer_add_inequality_with_integer_constraint(transformer /*tf*/, entity /*v*/, long long int /*cst*/, bool /*less_than_p*/);
extern transformer transformer_add_inequality_with_affine_term(transformer /*tf*/, entity /*v*/, entity /*x*/, int /*a*/, int /*cst*/, bool /*less_than_p*/);
extern transformer transformer_add_equality_with_affine_term(transformer /*tf*/, entity /*v*/, entity /*x*/, int /*a*/, int /*cst*/);
extern transformer transformer_add_inequality_with_linear_term(transformer /*tf*/, entity /*v*/, entity /*x*/, int /*a*/, bool /*less_than_p*/);
extern transformer transformer_add_3d_affine_constraint(transformer /*tf*/, int /*a1*/, entity /*v1*/, int /*a2*/, entity /*v2*/, int /*a3*/, entity /*v3*/, int /*cst*/, bool /*equation_p*/);
extern bool transformer_argument_consistency_p(transformer /*t*/);
extern bool transformer_argument_weak_consistency_p(transformer /*t*/);
extern bool transformer_argument_general_consistency_p(transformer /*t*/, bool /*is_weak*/);
extern bool transformer_consistency_p(transformer /*t*/);
extern bool transformers_consistency_p(list /*tl*/);
extern bool transformer_weak_consistency_p(transformer /*t*/);
extern bool transformer_general_consistency_p(transformer /*tf*/, bool /*is_weak*/);
extern bool transformer_internal_consistency_p(transformer /*t*/);
extern list transformer_projectable_values(transformer /*tf*/);
extern bool value_belongs_to_transformer_space(entity /*v*/, transformer /*tf*/);
extern void add_value_to_transformer_space(entity /*v*/, transformer /*tf*/);
extern transformer precondition_to_abstract_store(transformer /*pre*/);
extern transformer transformer_add_modified_variable(transformer /*tf*/, entity /*var*/);
extern transformer transformer_add_modified_variable_entity(transformer /*tf*/, entity /*var*/);
extern transformer move_transformer(transformer /*t1*/, transformer /*t2*/);
extern bool transformer_equations_constrain_variable_p(const transformer /*t*/, const entity /*v*/);
extern bool transformer_inequalities_constrain_variable_p(const transformer /*t*/, const entity /*v*/);
/* convex_hull.c */
extern transformer transformer_convex_hull(transformer /*t1*/, transformer /*t2*/);
/* fix_point.c */
extern transformer (*transformer_fix_point_operator)(transformer);
extern transformer transformer_halbwachs_fix_point(transformer /*tf*/);
extern transformer transformer_equality_fix_point(transformer /*tf*/);
extern void build_transfer_equations(Pcontrainte /*leq*/, Pcontrainte */*plteq*/, Pbase */*pb_new*/);
extern bool transfer_equation_p(Pvecteur /*eq*/);
extern entity new_value_in_transfer_equation(Pvecteur /*eq*/);
extern bool sub_basis_p(Pbase /*b1*/, Pbase /*b2*/);
extern void equations_to_bases(Pcontrainte /*lteq*/, Pbase */*pb_new*/, Pbase */*pb_old*/);
extern transformer transformer_pattern_fix_point(transformer /*tf*/);
extern Pvecteur look_for_the_best_counter(Pcontrainte /*egs*/);
extern Psysteme sc_eliminate_constant_terms(Psysteme /*sc*/, Pvecteur /*v*/);
extern Pcontrainte constraints_eliminate_constant_terms(Pcontrainte /*lc*/, Pvecteur /*v*/);
extern Psysteme sc_keep_invariants_only(Psysteme /*sc*/);
extern Pcontrainte constraints_keep_invariants_only(Pcontrainte /*lc*/);
extern bool invariant_vector_p(Pvecteur /*v*/);
extern Psysteme sc_multiply_constant_terms(Psysteme /*sc*/, Variable /*ik*/, bool /*star_p*/);
extern transformer transformer_derivative_fix_point(transformer /*tf*/);
extern list transformers_derivative_fix_point(list /*tl*/);
extern transformer transformer_basic_fix_point(transformer /*tf*/);
extern transformer any_transformer_to_k_closure(transformer /*t_init*/, transformer /*t_enter*/, transformer /*t_next*/, transformer /*t_body*/, transformer /*post_init*/, int /*k*/, bool /*assume_previous_iteration_p*/);
/* io.c */
extern transformer print_transformer(transformer /*tf*/);
extern transformer print_any_transformer(transformer /*tf*/);
extern list print_transformers(list /*tl*/);
extern transformer fprint_transformer(FILE */*fd*/, transformer /*tf*/, get_variable_name_t /*value_name*/);
extern list fprint_transformers(FILE */*fd*/, list /*tl*/, get_variable_name_t /*value_name*/);
extern char *dump_value_name(entity /*e*/);
extern void dump_transformer(transformer /*tf*/);
/* transformer.c */
extern transformer simple_equality_to_transformer(entity /*e*/, entity /*f*/, bool /*assignment*/);
extern transformer simple_unary_minus_to_transformer(entity /*e*/, entity /*f*/);
extern transformer generic_equality_to_transformer(entity /*e*/, entity /*f*/, bool /*assignment*/, bool /*unary_minus_p*/);
extern transformer simple_addition_to_transformer(entity /*e*/, entity /*e1*/, entity /*e2*/, bool /*addition_p*/);
extern transformer relation_to_transformer(entity /*op*/, entity /*e1*/, entity /*e2*/, bool /*veracity*/);
extern transformer transformer_combine(volatile transformer /*t1*/, transformer /*t2*/);
extern list transformers_combine(list /*tl1*/, transformer /*t2*/);
extern list one_to_one_transformers_combine(list /*tl1*/, list /*tl2*/);
extern transformer transformer_safe_combine_with_warnings(transformer /*tf1*/, transformer /*tf2*/);
extern transformer transformer_intersection(transformer /*t1*/, transformer /*t2*/);
extern transformer transformer_image_intersection(transformer /*t1*/, transformer /*t2*/);
extern transformer transformer_safe_intersection(transformer /*t1*/, transformer /*t2*/);
extern transformer transformer_safe_image_intersection(transformer /*t1*/, transformer /*t2*/);
extern transformer transformer_domain_intersection(transformer /*tf*/, transformer /*pre*/);
extern transformer transformer_safe_domain_intersection(transformer /*tf*/, transformer /*pre*/);
extern transformer transformer_range(transformer /*tf*/);
extern transformer transformer_safe_range(transformer /*tf*/);
extern list transformers_range(list /*tfl*/);
extern transformer transformer_to_domain(transformer /*tf*/);
extern transformer transformer_safe_domain(transformer /*tf*/);
extern transformer transformer_range_intersection(transformer /*tf*/, transformer /*r*/);
extern transformer transformer_intersect_range_with_domain(transformer /*tf*/);
extern transformer transformer_normalize(transformer /*t*/, int /*level*/);
extern transformer transformer_safe_normalize(transformer /*t*/, int /*level*/);
extern list transformers_safe_normalize(list /*tl*/, int /*level*/);
extern bool transformer_with_temporary_values_p(transformer /*tf*/);
extern transformer transformer_temporary_value_projection(transformer /*tf*/);
extern transformer safe_transformer_projection(transformer /*t*/, list /*args*/);
extern transformer transformer_formal_parameter_projection(entity /*f*/, transformer /*t*/);
extern transformer transformer_return_value_projection(entity /*f*/, transformer /*t*/);
extern transformer transformer_projection(transformer /*t*/, list /*args*/);
extern transformer transformer_arguments_projection(transformer /*t*/);
extern Psysteme no_elim(Psysteme /*ps*/);
extern transformer transformer_projection_with_redundancy_elimination(transformer /*t*/, list /*args*/, Psysteme (* /*elim*/)(Psysteme));
extern transformer transformer_projection_without_check(transformer /*t*/, list /*args*/, Psysteme (* /*elim*/)(Psysteme));
extern transformer transformer_projection_with_redundancy_elimination_and_check(volatile transformer /*t*/, list /*args*/, Psysteme (* /*elim*/)(Psysteme), bool /*check_consistency_p*/);
extern transformer transformer_apply(transformer /*tf*/, transformer /*pre*/);
extern list transformer_apply_generic(list /*tl*/, transformer /*pre*/, bool /*keep_p*/);
extern list transformer_apply_map(list /*tl*/, transformer /*pre*/);
extern list transformers_apply(list /*tl*/, transformer /*pre*/);
extern list transformers_apply_and_keep_all(list /*tl*/, transformer /*pre*/);
extern transformer transformer_safe_apply(transformer /*tf*/, transformer /*pre*/);
extern list transformers_safe_apply(list /*tl*/, transformer /*pre*/);
extern transformer transformer_inverse_apply(transformer /*tf*/, transformer /*post*/);
extern transformer transformer_safe_inverse_apply(transformer /*tf*/, transformer /*post*/);
extern transformer transformer_filter(transformer /*t*/, list /*args*/);
extern transformer transformer_variables_filter(transformer /*t*/, list /*vl*/);
extern bool transformer_affect_linear_p(transformer /*tf*/, Pvecteur /*l*/);
extern bool transformer_affect_transformer_p(transformer /*tf1*/, transformer /*tf2*/);
extern bool transformer_safe_affect_transformer_p(transformer /*tf1*/, transformer /*tf2*/);
extern transformer args_to_transformer(list /*le*/);
extern transformer invariant_wrt_transformer(transformer /*p*/, transformer /*tf*/);
extern transformer transformer_value_substitute(transformer /*t*/, entity /*e1*/, entity /*e2*/);
extern bool transformer_value_substitutable_p(transformer /*t*/, entity /*e1*/, entity /*e2*/);
extern transformer transformer_safe_value_substitute(transformer /*t*/, entity /*e1*/, entity /*e2*/);
extern Pvecteur simplify_float_constraint(Pvecteur /*v*/, bool /*is_equation_p*/);
extern Psysteme simplify_float_constraint_system(Psysteme /*ps*/);
extern bool transformer_empty_p(transformer /*t*/);
extern bool transformer_strongly_empty_p(transformer /*t*/);
extern bool transformer_to_1D_lattice(entity /*v*/, transformer /*pre*/, Value */*gcd_p*/, Value */*c_p*/);
extern transformer formal_and_actual_parameters_association(call /*c*/, transformer /*pre*/);
extern bool same_dimension_p(entity /*actual_array*/, entity /*dummy_array*/, list /*l_actual_ref*/, size_t /*i*/, transformer /*context*/);
/* value.c */
extern bool hash_entity_to_values_undefined_p(void);
extern void reset_value_counters(void);
extern void reset_temporary_value_counter(void);
extern int number_of_temporary_values(void);
extern void set_analyzed_types(void);
extern void reset_analyzed_types(void);
extern bool integer_analyzed_p(void);
extern bool boolean_analyzed_p(void);
extern bool string_analyzed_p(void);
extern bool float_analyzed_p(void);
extern bool complex_analyzed_p(void);
extern bool pointer_analyzed_p(void);
extern bool constant_path_analyzed_p(void);
extern bool analyzed_basic_p(basic /*b*/);
extern bool analyzed_type_p(type /*t*/);
extern bool analyzable_scalar_entity_p(entity /*e*/);
extern bool analyzed_constant_p(entity /*f*/);
extern bool analyzed_reference_p(reference /*r*/);
extern entity make_local_temporary_value_entity(type /*t*/);
extern entity make_local_temporary_value_entity_with_basic(basic /*b*/);
extern entity make_local_temporary_integer_value_entity(void);
extern bool local_old_value_entity_p(entity /*e*/);
extern bool local_intermediate_value_entity_p(entity /*e*/);
extern bool local_temporary_value_entity_p(entity /*e*/);
extern bool global_new_value_p(entity /*e*/);
extern bool global_old_value_p(entity /*e*/);
extern bool global_intermediate_value_p(entity /*e*/);
extern entity global_new_value_to_global_old_value(entity /*v_new*/);
extern const char *global_value_name_to_user_name(const char */*gn*/);
extern const char *external_value_name(entity /*e*/);
extern const char *pips_user_value_name(entity /*e*/);
extern entity entity_to_new_value(entity /*e*/);
extern entity entity_to_old_value(entity /*e*/);
extern entity entity_to_intermediate_value(entity /*e*/);
extern entity reference_to_address_of_value(reference /*r*/);
extern entity type_to_sizeof_value(type /*t*/);
extern bool entity_has_values_p(entity /*e*/);
extern bool new_value_entity_p(entity /*e*/);
extern bool old_value_entity_p(entity /*e*/);
extern bool intermediate_value_entity_p(entity /*e*/);
extern bool address_of_value_entity_p(entity /*e*/);
extern bool sizeof_value_entity_p(entity /*e*/);
extern bool value_entity_p(entity /*e*/);
extern void print_value_mappings(void);
extern list modified_variables_with_values(void);
extern void test_mapping_entry_consistency(void);
extern int number_of_analyzed_values(void);
extern int aproximate_number_of_analyzed_variables(void);
extern int number_of_analyzed_variables(void);
extern void allocate_value_mappings(int /*n*/, int /*o*/, int /*i*/);
extern bool hash_value_to_name_undefined_p(void);
extern void error_reset_value_mappings(void);
extern void free_value_mappings(void);
extern void error_free_value_mappings(void);
extern entity reference_to_address_entity(reference /*r*/);
extern void add_address_of_value(reference /*r*/, type /*t*/);
extern void add_sizeof_value(type /*t*/);
extern void add_new_value(entity /*e*/);
extern void add_new_alias_value(entity /*e*/, entity /*a*/);
extern entity external_entity_to_new_value(entity /*e*/);
extern entity external_entity_to_old_value(entity /*e*/);
extern void add_old_value(entity /*e*/);
extern void add_old_alias_value(entity /*e*/, entity /*a*/);
extern void add_intermediate_value(entity /*e*/);
extern void add_intermediate_alias_value(entity /*e*/, entity /*a*/);
extern void add_local_old_value(entity /*e*/);
extern void add_local_intermediate_value(entity /*e*/);
extern void remove_entity_values(entity /*e*/, bool /*readonly*/);
extern void add_synonym_values(entity /*e*/, entity /*eq*/, bool /*readonly*/);
extern entity value_to_variable(entity /*val*/);
extern entity old_value_to_new_value(entity /*o_val*/);
extern entity new_value_to_old_value(entity /*n_val*/);
extern entity value_alias(entity /*e*/);
extern Pvecteur vect_variables_to_values(Pvecteur /*v*/);
extern string value_full_name(entity /*v*/);
extern const char *readable_value_name(entity /*v*/);
/* prettyprint.c */
extern string transformer_to_string(transformer /*tf*/);
extern string precondition_to_string(transformer /*pre*/);
extern string arguments_to_string(string /*s*/, list /*args*/);
extern string relation_to_string(string /*s*/, Psysteme /*ps*/, char *(* /*variable_name*/)(entity));
extern const char *generic_value_name(entity /*e*/);
/* transformer_list.c */
extern list merge_transformer_lists(list /*tl1*/, list /*tl2*/);
extern bool check_transformer_list(list /*tl*/);
extern list combine_transformer_lists(list /*tl1*/, list /*tl2*/);
extern list apply_transformer_lists_generic(list /*tl1*/, list /*tl2*/, bool /*exclude_p*/);
extern list apply_transformer_lists(list /*tl1*/, list /*tl2*/);
extern list apply_transformer_lists_with_exclusion(list /*tl1*/, list /*tl2*/);
extern list clean_up_transformer_list(list /*tfl*/);
extern list two_transformers_to_list(transformer /*t1*/, transformer /*t2*/);
extern transformer generic_transformer_list_to_transformer(list /*ltl*/, bool /*active_p*/);
extern transformer transformer_list_to_transformer(list /*ltl*/);
extern transformer active_transformer_list_to_transformer(list /*ltl*/);
extern list transformer_list_to_active_transformer_list(list /*tl*/);
extern transformer transformer_list_closure_to_precondition(list /*tl*/, transformer /*c_t*/, transformer /*p_0*/);
extern list transformer_list_safe_variables_projection(list /*tl*/, list /*proj*/);
extern list transformer_list_to_argument(list /*tl*/);
extern list transformer_list_with_effect(list /*tl*/, entity /*v*/);
extern list transformer_list_preserved_variables(list /*vl*/, list /*tl*/, list /*tl_v*/);
extern transformer transformer_list_multiple_closure_to_precondition(list /*tl*/, transformer /*c_t*/, transformer /*p_0*/);
extern Psysteme transformer_derivative_constraints(transformer /*t*/);
extern transformer transformer_list_generic_transitive_closure(list /*tfl*/, bool /*star_p*/);
extern transformer transformer_list_transitive_closure(list /*tfl*/);
extern transformer transformer_list_transitive_closure_plus(list /*tfl*/);
#endif /*  transformer_header_included */
