/* Warning! Do not modify this file that is automatically generated! */
/* Modify src/Libs/effects-simple/effects-simple-local.h instead, to add your own modifications. */

/* header file built by cproto */

#ifndef  effects_simple_header_included
#define  effects_simple_header_included
/*

  $Id: effects-simple-local.h 23065 2016-03-02 09:05:50Z coelho $

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

/* actions interpretation for simple effects prettyprinting */
typedef enum {act_rw, act_inout, act_live_in, act_live_out}
  simple_effects_actions_interpretations;

/* copies an effect with no subcript expression */
#define make_sdfi_effect(e) \
 (reference_indices(effect_any_reference(e)) == NIL) ? \
  make_simple_effect(make_reference(reference_variable(effect_any_reference(e)), NIL),\
     copy_action(effect_action(e)), \
     make_approximation(approximation_tag(effect_approximation(e)), UU)) : \
  make_simple_effect(make_reference(reference_variable(effect_any_reference(e)), NIL), \
	      copy_action(effect_action(e)), \
	      make_approximation(is_approximation_may, UU))
/* binary_operators.c */
extern list ReferenceUnion(list /*l1*/, list /*l2*/, bool (* /*union_combinable_p*/)(effect, effect));
extern list ReferenceTestUnion(list /*l1*/, list /*l2*/, bool (* /*union_combinable_p*/)(effect, effect));
extern list EffectsMayUnion(list /*l1*/, list /*l2*/, bool (* /*union_combinable_p*/)(effect, effect));
extern list ProperEffectsMustUnion(list /*l1*/, list /*l2*/, bool (* /*union_combinable_p*/)(effect, effect));
extern list EffectsMustUnion(list /*l1*/, list /*l2*/, bool (* /*union_combinable_p*/)(effect, effect));
extern list effects_may_union(effect /*eff1*/, effect /*eff2*/);
extern list effects_must_union(effect /*eff1*/, effect /*eff2*/);
extern effect effect_may_union(effect /*eff1*/, effect /*eff2*/);
extern effect effect_must_union(effect /*eff1*/, effect /*eff2*/);
extern list EffectsSupDifference(list /*l1*/, list /*l2*/, bool (* /*difference_combinable_p*/)(effect, effect));
extern list EffectsInfDifference(list /*l1*/, list /*l2*/, bool (* /*difference_combinable_p*/)(effect, effect));
extern effect proper_to_summary_simple_effect(effect /*eff*/);
extern bool simple_cells_intersection_p(cell /*c1*/, descriptor /*d1*/, cell /*c2*/, descriptor /*d2*/, bool */*exact_p*/);
extern bool simple_cells_inclusion_p(cell /*c1*/, descriptor /*d1*/, cell /*c2*/, descriptor /*d2*/, bool */*exact_p*/);
/* interface.c */
extern bool cumulated_references(const string /*module_name*/);
extern bool proper_references(const string /*module_name*/);
extern bool proper_pointer_effects(const string /*module_name*/);
extern bool summary_pointer_effects(const string /*module_name*/);
extern bool cumulated_pointer_effects(const string /*module_name*/);
extern bool cumulated_pointer_effects_with_points_to(const string /*module_name*/);
extern bool cumulated_pointer_effects_with_pointer_values(const string /*module_name*/);
extern bool proper_effects(const string /*module_name*/);
extern bool proper_effects_with_points_to(const string /*module_name*/);
extern bool proper_effects_with_pointer_values(const string /*module_name*/);
extern bool summary_effects(const string /*module_name*/);
extern bool cumulated_effects(const string /*module_name*/);
extern bool cumulated_effects_with_points_to(const string /*module_name*/);
extern bool cumulated_effects_with_pointer_values(const string /*module_name*/);
extern bool in_summary_effects(const string /*module_name*/);
extern bool out_summary_effects(const string /*module_name*/);
extern bool in_effects(const string /*module_name*/);
extern bool out_effects(const string /*module_name*/);
extern bool print_code_proper_pointer_effects(const string /*module_name*/);
extern bool print_code_cumulated_pointer_effects(const string /*module_name*/);
extern bool print_code_proper_effects(const string /*module_name*/);
extern bool print_code_cumulated_effects(const string /*module_name*/);
extern bool print_code_proper_references(const string /*module_name*/);
extern bool print_code_cumulated_references(const string /*module_name*/);
extern bool print_code_in_effects(const string /*module_name*/);
extern bool print_code_out_effects(const string /*module_name*/);
extern bool print_source_proper_effects(const string /*module_name*/);
extern bool print_source_cumulated_effects(const string /*module_name*/);
extern bool print_source_in_effects(const string /*module_name*/);
extern bool print_source_out_effects(const string /*module_name*/);
extern bool print_code_as_a_graph_proper_effects(const string /*mod_name*/);
extern bool print_code_as_a_graph_cumulated_effects(const string /*mod_name*/);
extern text get_text_proper_pointer_effects(const string /*module_name*/);
extern text get_text_cumulated_pointer_effects(const string /*module_name*/);
extern text get_text_proper_effects(const string /*module_name*/);
extern text get_text_cumulated_effects(const string /*module_name*/);
extern list proper_effects_of_expression(expression /*e*/);
extern list expression_to_proper_effects(expression /*e*/);
extern list proper_constant_path_effects_of_expression(expression /*e*/);
extern list expression_to_proper_constant_path_effects(expression /*e*/);
extern bool expression_with_side_effect_p(expression /*e*/);
extern list proper_constant_path_effects_of_expression_with_points_to(expression /*e*/, statement /*stmt*/);
extern list expression_to_proper_constant_path_effects_with_points_to(expression /*e*/, statement /*stmt*/);
extern list proper_effects_of_range(range /*r*/);
extern bool expression_invariant_wrt_effects(expression /*exp*/, list /*el*/);
extern void rproper_effects_of_statement(statement /*s*/);
extern void rcumulated_effects_of_statement(statement /*s*/);
extern list statement_to_effects(statement /*s*/);
extern bool full_simple_proper_effects(const char */*module_name*/, statement /*current*/);
extern bool simple_cumulated_effects(const char */*module_name*/, statement /*current*/);
extern bool live_paths(const string /*module_name*/);
extern bool live_in_summary_paths(const string /*module_name*/);
extern bool live_out_summary_paths(const string /*module_name*/);
extern bool print_code_live_in_paths(const string /*module_name*/);
extern bool print_code_live_out_paths(const string /*module_name*/);
extern bool update_loops_locals(const char */*module_name*/, statement /*module_stat*/);
extern bool is_implied_do_index(entity /*e*/, instruction /*ins*/);
extern list get_list_of_variable_to_filter(void);
extern bool print_icfg_with_proper_effects(const string /*module_name*/);
extern bool print_icfg_with_cumulated_effects(const string /*module_name*/);
extern bool print_icfg_with_loops_proper_effects(const string /*module_name*/);
extern bool print_icfg_with_loops_cumulated_effects(const string /*module_name*/);
extern bool print_icfg_with_control_proper_effects(const string /*module_name*/);
extern bool print_icfg_with_control_cumulated_effects(const string /*module_name*/);
extern bool print_icfg_with_filtered_proper_effects(const string /*module_name*/);
extern bool print_dvicfg_with_filtered_proper_effects(const string /*module_name*/);
/* methods.c */
extern void set_methods_for_proper_references(void);
extern void set_methods_for_cumulated_references(void);
extern void set_default_methods_for_proper_simple_effects(void);
extern void set_methods_for_proper_simple_effects(void);
extern void set_methods_for_proper_simple_pointer_effects(void);
extern void set_methods_for_simple_effects(void);
extern void set_methods_for_simple_pointer_effects(void);
extern void set_methods_for_inout_effects(const char */*module_name*/);
extern void set_methods_for_live_paths(const char */*module_name*/);
extern void reset_methods_for_inout_effects(void);
extern void set_methods_for_rw_effects_prettyprint(const char */*module_name*/);
extern void set_methods_for_inout_effects_prettyprint(const char */*module_name*/);
extern void set_methods_for_live_in_paths_prettyprint(const char */*module_name*/);
extern void set_methods_for_live_out_paths_prettyprint(const char */*module_name*/);
extern void reset_methods_for_effects_prettyprint(const char */*module_name*/);
/* translation.c */
extern bool add_points_to_subscript_lists(list */*posl*/, list /*asl*/, list /*isl*/);
extern bool simple_cell_reference_with_address_of_cell_reference_translation_fi(reference /*input_ref*/, descriptor /*input_desc*/, reference /*address_of_ref*/, descriptor /*address_of_desc*/, int /*nb_common_indices*/, reference */*output_ref*/, descriptor */*output_desc*/, bool */*exact_p*/);
extern void simple_cell_reference_with_address_of_cell_reference_translation(reference /*input_ref*/, descriptor /*input_desc*/, reference /*address_of_ref*/, descriptor /*address_of_desc*/, int /*nb_common_indices*/, reference */*output_ref*/, descriptor */*output_desc*/, bool */*exact_p*/);
extern void simple_cell_reference_with_value_of_cell_reference_translation(reference /*input_ref*/, descriptor /*input_desc*/, reference /*value_of_ref*/, descriptor /*value_of_desc*/, int /*nb_common_indices*/, reference */*output_ref*/, descriptor */*output_desc*/, bool */*exact_p*/);
extern void simple_cell_with_address_of_cell_translation(cell /*input_cell*/, descriptor /*input_desc*/, cell /*address_of_cell*/, descriptor /*address_of_desc*/, int /*nb_common_indices*/, cell */*output_cell*/, descriptor */*output_desc*/, bool */*exact_p*/);
extern void simple_cell_with_value_of_cell_translation(cell /*input_cell*/, descriptor /*input_desc*/, cell /*value_of_cell*/, descriptor /*value_of_desc*/, int /*nb_common_indices*/, cell */*output_cell*/, descriptor */*output_desc*/, bool */*exact_p*/);
/* interprocedural.c */
extern void simple_effects_translation_init(entity /*callee*/, list /*real_args*/, bool /*backward_p*/);
extern void simple_effects_translation_end(void);
extern void simple_effect_descriptor_interprocedural_translation(effect /*eff*/);
extern list simple_effects_backward_translation(entity /*func*/, list /*real_args*/, list /*l_eff*/, transformer /*context*/);
extern effect translate_effect_to_sdfi_effect(effect /*eff*/);
extern list effects_dynamic_elim(list /*l_eff*/);
extern list make_unknown_subscript(int /*d*/);
extern list summary_effect_to_proper_effect(call /*c*/, effect /*e*/);
extern void check_user_call_site(entity /*func*/, list /*args*/);
extern list fortran_summary_to_proper_effects(entity /*func*/, list /*args*/, list /*func_sdfi*/);
extern list c_simple_effects_on_formal_parameter_backward_translation(list /*l_sum_eff*/, expression /*real_arg*/, transformer /*context*/);
extern list c_summary_effect_to_proper_effects(effect /*eff*/, expression /*real_arg*/);
extern list c_summary_to_proper_effects(entity /*func*/, list /*args*/, list /*func_sdfi*/);
extern list summary_to_proper_effects(entity /*func*/, list /*args*/, list /*func_sdfi*/);
extern list simple_effects_forward_translation(entity /*callee*/, list /*real_args*/, list /*l_eff*/, transformer /*context*/);
extern list c_simple_effects_on_actual_parameter_forward_translation(entity /*callee*/, expression /*real_exp*/, entity /*formal_ent*/, list /*l_eff*/, transformer /*context*/);
/* prettyprint.c */
extern text simple_rw_effects_to_text(list /*l*/);
extern text simple_inout_effects_to_text(list /*l*/);
extern text simple_live_in_paths_to_text(list /*l*/);
extern text simple_live_out_paths_to_text(list /*l*/);
extern string effect_to_string(effect /*eff*/);
extern list words_effect_generic(effect /*obj*/, bool /*approximation_p*/);
extern list words_effect(effect /*obj*/);
extern list words_effect_without_approximation(effect /*obj*/);
extern void print_effect(effect /*e*/);
extern void print_effects(list /*pc*/);
extern void print_memory_effects(list /*pc*/);
extern bool print_call_graph_with_proper_effects(const string /*module_name*/);
extern bool print_call_graph_with_cumulated_effects(const string /*module_name*/);
/* unary_operators.c */
extern effect reference_to_simple_effect(reference /*ref*/, action /*act*/, bool /*use_preference_p*/);
extern void simple_effect_add_expression_dimension(effect /*eff*/, expression /*exp*/);
extern void simple_effect_change_ith_dimension_expression(effect /*eff*/, expression /*exp*/, int /*i*/);
extern effect simple_effect_field_to_rank_conversion(effect /*input_effect*/);
extern effect simple_effect_dup(effect /*eff*/);
extern effect reference_to_reference_effect(reference /*ref*/, action /*act*/, bool /*use_preference_p*/);
extern list simple_effects_union_over_range(list /*l_eff*/, entity /*i*/, range /*r*/, descriptor /*d*/);
extern reference simple_reference_to_store_independent_reference(reference /*r*/, bool */*changed_p*/);
extern cell simple_cell_to_store_independent_cell(cell /*c*/, bool */*changed_p*/);
extern list effect_to_store_independent_sdfi_list(effect /*eff*/, bool /*force_may_p*/);
extern list effect_to_may_sdfi_list(effect /*eff*/);
extern list effect_to_sdfi_list(effect /*eff*/);
extern void simple_effects_descriptor_normalize(list /*l_eff*/);
extern list simple_effects_composition_with_effect_transformer(list /*l_eff*/, transformer /*trans*/);
extern list old_effects_composition_with_effect_transformer(list /*l_eff*/, transformer /*trans*/);
/* filter_proper_effects.c */
extern bool filter_proper_effects(const char */*module_name*/);
/* eval.c */
extern bool simple_cell_reference_preceding_p(reference /*r1*/, descriptor /*d1*/, reference /*r2*/, descriptor /*d2*/, transformer /*current_precondition*/, bool /*strict_p*/, bool */*exact_p*/);
extern bool simple_cell_preceding_p(cell /*c1*/, descriptor /*d1*/, cell /*c2*/, descriptor /*d2*/, transformer /*current_precondition*/, bool /*strict_p*/, bool */*exact_p*/);
extern bool path_preceding_p(effect /*eff1*/, effect /*eff2*/, transformer /*current_precondition*/, bool /*strict_p*/, bool */*exact_p*/);
extern void simple_reference_to_simple_reference_conversion(reference /*ref*/, reference */*output_ref*/, descriptor */*output_desc*/);
extern void simple_cell_to_simple_cell_conversion(cell /*input_cell*/, cell */*output_cell*/, descriptor */*output_desc*/);
extern list eval_simple_cell_with_points_to(cell /*c*/, descriptor /*d*/, list /*ptl*/, bool */*exact_p*/, transformer /*t*/);
extern list simple_effect_to_constant_path_effects_with_pointer_values(effect /*eff*/);
extern list simple_effect_to_constant_path_effects_with_points_to(effect /*eff*/);
extern list eval_cell_with_points_to(cell /*c*/, list /*ptl*/, bool */*exact_p*/);
#endif /*  effects_simple_header_included */
