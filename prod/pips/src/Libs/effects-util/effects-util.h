/* Warning! Do not modify this file that is automatically generated! */
/* Modify src/Libs/effects-util/effects-util-local.h instead, to add your own modifications. */

/* header file built by cproto */

#ifndef  effects_util_header_included
#define  effects_util_header_included
/*

  $Id: effects-util-local.h 23065 2016-03-02 09:05:50Z coelho $

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
#include "newgen.h"
#include "ri.h"
#include "effects.h"
#include "points_to_private.h"

#define ANY_MODULE_NAME "*ANY_MODULE*"
#define ANYWHERE_LOCATION "*ANYWHERE*"
#define NOWHERE_LOCATION "*NOWHERE*"
// Target of the null pointers:
#define NULL_POINTER_NAME "*NULL*"
#define UNDEFINED_LOCATION "*UNDEFINED*"

#define UNDEFINED_POINTER_VALUE_NAME "*UNDEFINED*"
#define NULL_POINTER_VALUE_NAME "*NULL*"

#define PHI_PREFIX "PHI"
#define PSI_PREFIX "PSI"
#define RHO_PREFIX "RHO"
#define BETA_PREFIX "BETA"
#define PROPER true
#define SUMMARY false

/* some useful SHORTHANDS for EFFECT:
 */
/* FI: Let's hope this one is not used as lhs! */
#define effect_any_entity(e) effect_to_entity(e)
#define effect_action_tag(eff) action_tag(effect_action(eff))
#define effect_approximation_tag(eff) \
	approximation_tag(effect_approximation(eff))

/* #define effect_scalar_p(eff) entity_scalar_p(effect_entity(eff))
 *
 * The semantics of effects_scalar_p() must be refined. If all the
 * indices are constant expressions, we still have a scalar effect,
 * unless they are later replaced by "*", as is the case currently for
 * summary effects.
 *
 * Potential bug: eff is evaluated twice. Should be copied in a local
 * variable and braces be used.
 */
#define effect_scalar_p(eff) ((type_depth(entity_type(effect_entity(eff)))==0) \
			      && ENDP(reference_indices(effect_any_reference(eff))))
#define effect_read_p(eff) (action_tag(effect_action(eff))==is_action_read)
#define effect_write_p(eff) (action_tag(effect_action(eff))==is_action_write)
#define effect_may_p(eff) \
        (approximation_tag(effect_approximation(eff)) == is_approximation_may)
#define effect_must_p(eff) \
        (approximation_tag(effect_approximation(eff)) == is_approximation_must)
#define effect_exact_p(eff) \
        (approximation_tag(effect_approximation(eff)) ==is_approximation_exact)




/* For COMPATIBILITY purpose only - DO NOT USE anymore
 */
#define effect_variable(e) reference_variable(effect_any_reference(e))



/* true if e is a phi variable
 * PHI entities have a name like: REGIONS:PHI#, where # is a number.
 * takes care if TCST and undefined entities, just in case.
 * FC, 09/12/94
 */
#define variable_phi_p(e) \
  ((e)!=(entity)NULL && (e)!=entity_undefined && \
    strncmp(entity_name(e), REGIONS_MODULE_NAME, 10)==0 && \
    strstr(entity_name(e), PHI_PREFIX) != NULL)

#define variable_psi_p(e) \
  ((e)!=(entity)NULL && (e)!=entity_undefined && \
    strncmp(entity_name(e), REGIONS_MODULE_NAME, 10)==0 && \
    strstr(entity_name(e), PSI_PREFIX) != NULL)

#define variable_rho_p(e) \
  ((e)!=(entity)NULL && (e)!=entity_undefined && \
    strncmp(entity_name(e), REGIONS_MODULE_NAME, 10)==0 && \
    strstr(entity_name(e), RHO_PREFIX) != NULL)

#define variable_beta_p(e)\
  ((e)!=(entity)NULL && (e)!=entity_undefined && \
    strncmp(entity_name(e), REGIONS_MODULE_NAME, 10)==0 && \
    strstr(entity_name(e), BETA_PREFIX) != NULL)

#define effect_system(e) \
        (descriptor_convex_p(effect_descriptor(e))? \
         descriptor_convex(effect_descriptor(e)) : SC_UNDEFINED)

/* FI: it would be useful to assert cell_preference_p(effect_cell(e)),
   but I do not know how to do it in such a way that it works both for
   left hand sides and right hand sides using commas.
   I definitely remove this one : it is too dangerous.
*/
/* #define effect_reference(e)					\
   preference_reference(cell_preference(effect_cell(e))) */
#define effect_reference(e) \
  /* DO NOT REMOVE, PREVENT REDEFINITION :)
   * use effect_any_reference instead !
  */ \
    effect_reference_not_defined_anymore()

/* FI: cannot be used as a left hand side */
#define effect_any_reference(e) \
         (cell_preference_p(effect_cell(e))? preference_reference(cell_preference(effect_cell(e))) : cell_reference(effect_cell(e)))
#define make_preference_simple_effect(reference,action,approximation)\
    make_effect(make_cell(is_cell_preference, make_preference(reference)),\
		(action), (approximation),	\
		make_descriptor(is_descriptor_none,UU))

#define make_reference_simple_effect(reference,action,approximation)\
  make_effect(make_cell(is_cell_reference, (reference)),	    \
		(action), (approximation),	\
		make_descriptor(is_descriptor_none,UU))

#define make_simple_effect(reference,action,approximation)\
    make_effect(make_cell(is_cell_preference, make_preference(reference)),\
		(action), (approximation),	\
		make_descriptor(is_descriptor_none,UU))

#define make_convex_effect(reference,action,approximation,system)\
  make_effect(make_cell(is_reference, (reference)),			\
		(action), (approximation),				\
		make_descriptor(is_descriptor_convex,system))


/********* CELL_RELATION SHORTHANDS */

#define cell_relation_first_cell(cr)\
  interpreted_cell_cell(cell_relation_first(cr))

#define cell_relation_first_interpretation_tag(cr)\
  cell_interpretation_tag(interpreted_cell_cell_interpretation(cell_relation_first(cr)))

#define cell_relation_first_value_of_p(cr)\
  cell_interpretation_value_of_p(interpreted_cell_cell_interpretation(cell_relation_first(cr)))

#define cell_relation_first_address_of_p(cr)\
  cell_interpretation_address_of_p(interpreted_cell_cell_interpretation(cell_relation_first(cr)))

#define cell_relation_second_cell(cr)\
  interpreted_cell_cell(cell_relation_second(cr))

#define cell_relation_second_interpretation_tag(cr)\
  cell_interpretation_tag(interpreted_cell_cell_interpretation(cell_relation_second(cr)))

#define cell_relation_second_value_of_p(cr)\
  cell_interpretation_value_of_p(interpreted_cell_cell_interpretation(cell_relation_second(cr)))

#define cell_relation_second_address_of_p(cr)\
  cell_interpretation_address_of_p(interpreted_cell_cell_interpretation(cell_relation_second(cr)))

#define cell_relation_approximation_tag(cr)\
  approximation_tag(cell_relation_approximation(cr))

#define cell_relation_may_p(cr)\
  approximation_tag(cell_relation_approximation(cr))==is_approximation_may

#define cell_relation_exact_p(cr)\
  approximation_tag(cell_relation_approximation(cr))==is_approximation_exact

#define pips_debug_pv(level, message, pv) \
  ifdebug(level) { pips_debug(level, "%s\n", message); \
    print_pointer_value(pv);}

#define pips_debug_pvs(level, message, l_pv) \
  ifdebug(level) { pips_debug(level, "%s\n", message); \
  print_pointer_values(l_pv);}

/********* CONTEXT AND FLOW SENSITIVITY INFORMATION */
typedef struct
{
    statement current_stmt;
    entity current_module;
    list enclosing_flow; /* not used yet, we don't know if it should retain enclosing loops and/or modules */
} sensitivity_information;
/* effects.c */
extern entity effect_entity(effect /*e*/);
extern entity cell_entity(cell /*c*/);
extern list cell_indices(cell /*c*/);
extern reference cell_any_reference(cell /*c*/);
extern bool memory_dereferencing_p(reference /*r*/);
extern effects list_to_effects(list /*l_eff*/);
extern list effects_to_list(effects /*efs*/);
extern statement_mapping listmap_to_effectsmap(statement_mapping /*l_map*/);
extern statement_mapping effectsmap_to_listmap(statement_mapping /*efs_map*/);
extern bool statement_has_a_module_formal_argument_write_effect_p(statement /*s*/, entity /*module*/, statement_mapping /*effects_list_map*/);
extern bool cell_abstract_location_p(cell /*c*/);
extern bool effect_abstract_location_p(effect /*eff*/);
extern bool effects_abstract_location_p(list /*el*/);
extern effect anywhere_effect(action /*ac*/);
extern bool anywhere_effect_p(effect /*e*/);
extern bool typed_anywhere_effect_p(effect /*e*/);
extern bool any_anywhere_effect_p(effect /*e*/);
extern bool anywhere_cell_p(cell /*c*/);
extern bool anywhere_reference_p(reference /*r*/);
extern effect heap_effect(entity /*m*/, action /*ac*/);
extern bool heap_effect_p(effect /*e*/);
extern bool heap_cell_p(cell /*c*/);
extern bool all_heap_locations_cell_p(cell /*c*/);
extern bool nowhere_cell_p(cell /*c*/);
extern bool null_cell_p(cell /*c*/);
extern bool malloc_effect_p(effect /*e*/);
extern bool malloc_cell_p(cell /*c*/);
extern bool malloc_reference_p(reference /*r*/);
extern bool io_effect_entity_p(entity /*e*/);
extern bool io_effect_p(effect /*e*/);
extern bool io_cell_p(cell /*c*/);
extern bool io_effects_p(list effects);
extern bool std_file_effect_p(effect /*e*/);
extern bool std_file_cell_p(cell /*c*/);
extern bool std_file_effects_p(list effects);
extern bool FILE_star_effect_reference_p(reference /*ref*/);
extern bool effect_comparable_p(effect /*e1*/, effect /*e2*/);
extern bool store_independent_effect_p(effect /*eff*/);
extern bool effect_on_non_local_variable_p(effect /*eff*/);
extern bool effects_on_non_local_variable_p(list effects);
extern bool effects_interfere_p(effect /*eff1*/, effect /*eff2*/);
extern effect effect_to_store_independent(effect /*eff*/);
extern effect effect_to_pointer_store_independent_effect(effect /*eff*/, entity /*p*/);
extern effect effect_to_non_pointer_store_independent_effect(effect /*eff*/);
extern effect effect_interference(effect /*eff1*/, effect /*eff2*/);
extern string action_to_string(action /*ac*/);
extern string full_action_to_string(action /*ac*/);
extern string full_action_to_short_string(action /*ac*/);
extern string action_kind_to_string(action_kind /*ak*/);
extern action make_action_write_memory(void);
extern action make_action_read_memory(void);
extern bool action_equal_p(action /*a1*/, action /*a2*/);
extern action_kind action_to_action_kind(action /*a*/);
extern action_kind effect_action_kind(effect /*eff*/);
extern bool store_effect_p(effect /*e*/);
extern bool environment_effect_p(effect /*e*/);
extern bool type_declaration_effect_p(effect /*e*/);
extern bool effects_write_variable_p(list /*el*/, entity /*v*/);
extern bool effects_write_p(list /*el*/);
extern bool effects_read_variable_p(list /*el*/, entity /*v*/);
extern bool effects_all_read_p(list /*el*/);
extern bool effect_list_can_be_safely_full_freed_p(list /*el*/);
extern tag approximation_and(tag /*t1*/, tag /*t2*/);
extern tag approximation_or(tag /*t1*/, tag /*t2*/);
extern bool cell_equal_p(cell /*c1*/, cell /*c2*/);
extern bool cell_entity_equal_p(cell /*c1*/, cell /*c2*/);
extern bool points_to_reference_included_p(reference /*r1*/, reference /*r2*/);
extern bool cell_included_p(cell /*c1*/, cell /*c2*/);
extern bool cell_equivalent_p(cell /*c1*/, cell /*c2*/);
extern reference cell_to_reference(cell /*c*/);
extern bool effect_list_consistent_p(list /*el*/);
extern bool union_compatible_effects_p(effect /*ef1*/, effect /*ef2*/);
extern entity effect_to_entity(effect /*ef*/);
extern bool vect_contains_phi_p(Pvecteur /*v*/);
extern cell points_to_cell_add_field_dimension(cell /*c*/, entity /*f*/);
extern reference reference_add_field_dimension(reference /*r*/, entity /*f*/);
extern reference simple_reference_add_field_dimension(reference /*r*/, entity /*f*/);
extern void points_to_cell_add_fixed_subscripts(cell /*c*/, bool /*zero_p*/);
extern void points_to_cell_add_zero_subscripts(cell /*c*/);
extern void points_to_cell_add_zero_subscript(cell /*c*/);
extern void points_to_cell_complete_with_zero_subscripts(cell /*c*/);
extern void points_to_cell_add_unbounded_subscripts(cell /*c*/);
extern void points_to_cell_update_last_subscript(cell /*c*/, expression /*s*/);
extern bool atomic_effect_p(effect /*e*/);
extern list recursive_cell_to_pointer_cells(cell /*c*/);
extern list cell_to_pointer_cells(cell /*c*/);
/* anywhere_abstract_locations.c */
extern entity entity_all_locations(void);
extern entity entity_anywhere_locations(void);
extern bool entity_all_locations_p(entity /*e*/);
extern entity entity_typed_anywhere_locations(type /*t*/);
extern entity generic_entity_typed_anywhere_locations(type /*t*/);
extern bool entity_anywhere_locations_p(entity /*e*/);
extern bool cell_typed_anywhere_locations_p(cell /*c*/);
extern bool reference_typed_anywhere_locations_p(reference /*r*/);
extern bool entity_typed_anywhere_locations_p(entity /*e*/);
extern entity entity_nowhere_locations(void);
extern entity entity_typed_nowhere_locations(type /*t*/);
extern bool entity_nowhere_locations_p(entity /*e*/);
extern bool entity_typed_nowhere_locations_p(entity /*e*/);
extern entity entity_null_locations(void);
extern bool entity_null_locations_p(entity /*e*/);
extern entity entity_all_module_locations(entity /*m*/);
extern bool entity_all_module_locations_p(entity /*e*/);
extern entity entity_all_module_xxx_locations(entity /*m*/, const char */*xxx*/);
extern entity entity_all_module_xxx_locations_typed(const char */*mn*/, const char */*xxx*/, type /*t*/);
extern bool entity_all_module_xxx_locations_p(entity /*e*/, string /*xxx*/);
extern entity entity_all_xxx_locations(string /*xxx*/);
extern entity entity_all_xxx_locations_typed(string /*xxx*/, type /*t*/);
extern bool entity_all_xxx_locations_p(entity /*e*/, string /*xxx*/);
extern entity entity_all_module_heap_locations(entity /*m*/);
extern entity entity_all_module_heap_locations_typed(entity /*m*/, type /*t*/);
extern bool entity_all_module_heap_locations_p(entity /*e*/);
extern entity entity_all_heap_locations(void);
extern bool entity_all_heap_locations_p(entity /*e*/);
extern entity entity_all_heap_locations_typed(type /*t*/);
extern entity entity_all_module_stack_locations(entity /*m*/);
extern bool entity_all_module_stack_locations_p(entity /*e*/);
extern entity entity_all_stack_locations(void);
extern bool entity_all_stack_locations_p(entity /*e*/);
extern entity entity_all_module_static_locations(entity /*m*/);
extern bool entity_all_module_static_locations_p(entity /*e*/);
extern entity entity_all_static_locations(void);
extern bool entity_all_static_locations_p(entity /*e*/);
extern entity entity_all_module_dynamic_locations(entity /*m*/);
extern bool entity_all_module_dynamic_locations_p(entity /*e*/);
extern entity entity_all_dynamic_locations(void);
extern bool entity_all_dynamic_locations_p(entity /*e*/);
extern bool entity_stub_sink_p(entity /*e*/);
extern bool stub_entity_of_module_p(entity /*s*/, entity /*m*/);
extern bool entity_abstract_location_p(entity /*al*/);
extern entity variable_to_abstract_location(entity /*v*/);
extern entity abstract_locations_max(entity /*al1*/, entity /*al2*/);
extern entity entity_locations_max(entity /*al1*/, entity /*al2*/);
extern entity entity_locations_dereference(entity /*al*/);
extern void check_abstract_locations(void);
extern bool abstract_locations_may_conflict_p(entity /*al1*/, entity /*al2*/);
extern bool abstract_locations_must_conflict_p(entity /*al1*/, entity /*al2*/);
/* abstract_location.c */
extern bool entity_heap_location_p(entity /*b*/);
extern entity entity_flow_or_context_sentitive_heap_location(int /*stmt_number*/, type /*t*/);
extern bool entity_flow_or_context_sentitive_heap_location_p(entity /*e*/);
extern type malloc_arg_to_type(expression /*e*/);
extern entity malloc_type_to_abstract_location(type /*t*/, sensitivity_information */*psi*/);
extern entity malloc_to_abstract_location(expression /*malloc_exp*/, sensitivity_information */*psi*/);
extern entity calloc_to_abstract_location(expression /*n*/, expression /*size*/, sensitivity_information */*psi*/);
extern reference original_malloc_to_abstract_location(expression /*lhs*/, type /*var_t*/, type /*cast_t*/, expression /*sizeof_exp*/, entity /*f*/, statement /*stmt*/);
extern sensitivity_information make_sensitivity_information(statement /*current_stmt*/, entity /*current_module*/, list /*enclosing_flow*/);
/* points_to.c */
extern bool pt_to_list_undefined_p(void);
extern void reset_pt_to_list(void);
extern void error_reset_pt_to_list(void);
extern void set_pt_to_list(statement_points_to /*o*/);
extern statement_points_to get_pt_to_list(void);
extern void init_pt_to_list(void);
extern void close_pt_to_list(void);
extern void store_pt_to_list(statement /*k*/, points_to_list /*v*/);
extern void update_pt_to_list(statement /*k*/, points_to_list /*v*/);
extern points_to_list load_pt_to_list(statement /*k*/);
extern points_to_list delete_pt_to_list(statement /*k*/);
extern bool bound_pt_to_list_p(statement /*k*/);
extern void store_or_update_pt_to_list(statement /*k*/, points_to_list /*v*/);
extern cell make_anywhere_points_to_cell(type /*t*/);
extern bool formal_parameter_points_to_cell_p(cell /*c*/);
extern bool stub_points_to_cell_p(cell /*c*/);
extern bool points_to_cell_in_list_p(cell /*c*/, list /*L*/);
extern list merge_points_to_cell_lists(list /*l1*/, list /*l2*/);
extern bool related_points_to_cell_in_list_p(cell /*c*/, list /*L*/);
extern bool related_points_to_cells_p(cell /*c1*/, cell /*c2*/);
extern void fprint_points_to_cell(FILE */*f*/, cell /*c*/);
extern void print_points_to_cell(cell /*c*/);
extern void print_points_to_cells(list /*cl*/);
extern bool field_reference_expression_p(expression /*e*/);
extern int points_to_reference_to_final_dimension(reference /*r*/);
extern void points_to_reference_update_final_subscripts(reference /*r*/, list /*nsl*/);
extern list points_to_reference_to_typed_index(reference /*r*/, type /*t*/);
extern bool atomic_points_to_cell_p(cell /*c*/);
extern bool generic_atomic_points_to_cell_p(cell /*c*/, bool /*strict_p*/);
extern bool generic_atomic_points_to_reference_p(reference /*r*/, bool /*strict_p*/);
extern bool atomic_points_to_reference_p(reference /*r*/);
extern bool points_to_cells_intersect_p(cell /*lc*/, cell /*rc*/);
extern cell points_to_cells_minimal_upper_bound(list /*cl*/);
extern entity points_to_cells_minimal_module_upper_bound(list /*cl*/);
extern type points_to_cells_minimal_type_upper_bound(list /*cl*/);
extern reference points_to_cells_minimal_reference_upper_bound(entity /*m*/, type /*t*/, list /*cl*/);
extern bool points_to_array_reference_p(reference /*r*/);
extern type points_to_array_reference_to_type(reference /*r*/);
extern void complete_points_to_reference_with_fixed_subscripts(reference /*r*/, bool /*zero_p*/);
extern void complete_points_to_reference_with_zero_subscripts(reference /*r*/);
extern bool cells_must_point_to_null_p(list /*cl*/);
extern bool cells_may_not_point_to_null_p(list /*cl*/);
extern bool cell_points_to_non_null_sink_in_set_p(cell /*source*/, set /*pts*/);
extern bool cell_points_to_null_sink_in_set_p(cell /*source*/, set /*pts*/);
extern bool points_to_cell_equal_p(cell /*c1*/, cell /*c2*/);
extern bool similar_arc_in_points_to_set_p(points_to /*spt*/, set /*in*/, approximation */*pa*/);
extern list points_to_cell_to_upper_bound_points_to_cells(cell /*c*/);
extern list points_to_cells_to_upper_bound_points_to_cells(list /*cl*/);
extern bool exact_points_to_subscript_list_p(list /*sl*/);
extern bool compatible_points_to_subscripts_p(expression /*s1*/, expression /*s2*/);
extern points_to points_to_with_stripped_sink(points_to /*pt*/, int (* /*line_number_func*/)(void));
extern bool recursive_store_independent_points_to_reference_p(type /*t*/, list /*sl*/);
extern bool store_independent_points_to_reference_p(reference /*r*/);
extern bool constant_points_to_indices_p(list /*sl*/);
/* cell_relations.c */
extern list cell_relations_generic_binary_op(list /*l1*/, list /*l2*/, bool (* /*cr1_cr2_combinable_p*/)(cell_relation, cell_relation), list (* /*cr1_cr2_binary_op*/)(cell_relation, cell_relation), list (* /*cr1_unary_op*/)(cell_relation), list (* /*cr2_unary_op*/)(cell_relation), list (* /*union_op*/)(list, list));
/* pointer_values.c */
extern entity undefined_pointer_value_entity(void);
extern cell make_undefined_pointer_value_cell(void);
extern bool undefined_pointer_value_entity_p(entity /*e*/);
extern bool undefined_pointer_value_cell_p(cell /*c*/);
extern entity null_pointer_value_entity(void);
extern cell make_null_pointer_value_cell(void);
extern bool null_pointer_value_entity_p(entity /*e*/);
extern bool null_pointer_value_cell_p(cell /*c*/);
extern bool abstract_pointer_value_entity_p(entity /*e*/);
extern bool abstract_pointer_value_cell_p(cell /*c*/);
extern cell_relation make_value_of_pointer_value(cell /*c1*/, cell /*c2*/, tag /*app_tag*/, descriptor /*d*/);
extern cell_relation make_address_of_pointer_value(cell /*c1*/, cell /*c2*/, tag /*app_tag*/, descriptor /*d*/);
extern bool pv_cells_syntactically_equal_p(cell_relation /*pv1*/, cell_relation /*pv2*/);
extern bool pv_cells_mergeable_p(cell_relation /*pv1*/, cell_relation /*pv2*/);
/* compare.c */
extern int cell_reference_compare(reference */*pr1*/, reference */*pr2*/);
extern int cell_compare(cell */*c1*/, cell */*c2*/);
extern int effect_compare(effect */*peff1*/, effect */*peff2*/);
extern int compare_effect_reference(effect */*e1*/, effect */*e2*/);
extern int compare_effect_reference_in_common(effect */*e1*/, effect */*e2*/);
extern int pointer_value_compare(cell_relation */*ppv1*/, cell_relation */*ppv2*/);
extern int is_inferior_cell_descriptor_pvarval(Pvecteur */*pvarval1*/, Pvecteur */*pvarval2*/);
/* prettyprint.c */
extern list effect_words_reference(reference /*obj*/);
extern string effect_reference_to_string(reference /*ref*/);
extern const char *pips_region_user_name(entity /*ent*/);
extern list words_fictious_reference(reference /*obj*/);
extern list points_to_words_reference(reference /*r*/);
extern list word_points_to(points_to /*pt*/);
extern int points_to_compare_cells(const void */*vpt1*/, const void */*vpt2*/);
extern list points_to_list_sort(list /*ptl*/);
extern list words_points_to_list(string /*note*/, points_to_list /*s*/);
extern list words_pointer_value(cell_relation /*pv*/);
extern string approximation_to_string(approximation /*a*/);
extern text text_pointer_value(cell_relation /*pv*/);
extern text text_pointer_values(list /*lpv*/, string /*header*/);
extern void print_pointer_value(cell_relation /*pv*/);
extern void print_pointer_values(list /*lpv*/);
/* type.c */
extern entity effect_field_dimension_entity(expression /*exp*/, list /*l_fields*/);
extern bool effect_reference_contains_pointer_dimension_p(reference /*ref*/, bool */*exact_p*/);
extern bool effect_reference_dereferencing_p(reference /*ref*/, bool */*exact_p*/);
extern type cell_reference_to_type(reference /*ref*/, bool */*to_be_freed*/);
extern type cell_to_type(cell /*c*/, bool */*to_be_freed*/);
extern type points_to_reference_to_type(reference /*ref*/, bool */*to_be_freed*/);
extern type points_to_expression_to_type(expression /*e*/, bool */*to_be_freed*/);
extern type points_to_expression_to_concrete_type(expression /*e*/);
extern type points_to_expression_to_pointed_type(expression /*e*/);
extern type points_to_cell_to_type(cell /*c*/, bool */*to_be_freed*/);
extern type points_to_cell_to_concrete_type(cell /*c*/);
extern type points_to_reference_to_concrete_type(reference /*r*/);
extern bool basic_concrete_types_compatible_for_effects_interprocedural_translation_p(type /*real_ct*/, type /*formal_ct*/);
extern bool types_compatible_for_effects_interprocedural_translation_p(type /*real_arg_t*/, type /*formal_arg_t*/);
extern void points_to_cell_types_compatibility(cell /*l*/, cell /*r*/);
extern bool points_to_source_cell_compatible_p(cell /*c*/);
extern bool points_to_sink_cell_compatible_p(cell /*c*/);
extern list find_points_to_subscript_for_type(cell /*c*/, type /*t*/);
extern bool adapt_reference_to_type(reference /*r*/, type /*et*/, int (* /*line_number_func*/)(void));
extern bool reference_unbounded_indices_p(reference /*r*/);
extern bool strict_constant_path_p(reference /*r*/);
extern bool can_be_constant_path_p(reference /*r*/);
/* conflicts.c */
extern void set_conflict_testing_properties(void);
extern bool effects_must_conflict_p(effect /*eff1*/, effect /*eff2*/);
extern bool effects_might_conflict_even_read_only_p(effect /*eff1*/, effect /*eff2*/);
extern bool effects_may_conflict_p(effect /*eff1*/, effect /*eff2*/);
extern bool effects_conflict_p(effect /*eff1*/, effect /*eff2*/);
extern bool array_references_may_conflict_p(list /*sl1*/, list /*sl2*/);
extern bool variable_references_may_conflict_p(entity /*v*/, list /*sl1*/, list /*sl2*/);
extern bool references_may_conflict_p(reference /*r1*/, reference /*r2*/);
extern bool references_must_conflict_p(reference /*r1*/, reference /*r2*/);
extern bool cells_may_conflict_p(cell /*c1*/, cell /*c2*/);
extern bool points_to_cell_lists_may_conflict_p(list /*l1*/, list /*l2*/);
extern bool cells_must_conflict_p(cell /*c1*/, cell /*c2*/);
extern bool points_to_cell_lists_must_conflict_p(list /*l1*/, list /*l2*/);
extern bool entities_maymust_conflict_p(entity /*e1*/, entity /*e2*/, bool /*must_p*/);
extern bool entities_may_conflict_p(entity /*e1*/, entity /*e2*/);
extern bool entities_must_conflict_p(entity /*e1*/, entity /*e2*/);
extern bool first_effect_certainly_includes_second_effect_p(effect /*eff1*/, effect /*eff2*/);
extern bool first_exact_scalar_effect_certainly_includes_second_effect_p(effect /*eff1*/, effect /*eff2*/);
extern bool effect_may_read_or_write_memory_paths_from_entity_p(effect /*ef*/, entity /*e*/);
extern bool effects_may_read_or_write_memory_paths_from_entity_p(list /*l_eff*/, entity /*e*/);
extern bool generic_effects_maymust_read_or_write_scalar_entity_p(list /*fx*/, entity /*e*/, bool /*must_p*/, bool /*concrete_p*/);
extern bool effects_maymust_read_or_write_scalar_entity_p(list /*fx*/, entity /*e*/, bool /*must_p*/);
extern bool concrete_effects_maymust_read_or_write_scalar_entity_p(list /*fx*/, entity /*e*/, bool /*must_p*/);
extern bool effects_may_read_or_write_scalar_entity_p(list /*fx*/, entity /*e*/);
extern bool concrete_effects_may_read_or_write_scalar_entity_p(list /*fx*/, entity /*e*/);
extern bool effects_must_read_or_write_scalar_entity_p(list /*fx*/, entity /*e*/);
extern list effects_entities_which_may_conflict_with_scalar_entity(list /*fx*/, entity /*e*/);
extern list concrete_effects_entities_which_may_conflict_with_scalar_entity(list /*fx*/, entity /*e*/);
/* locations.c */
extern entity make_location_entity(reference /*cp*/);
extern string constant_memory_access_path_to_location_name(reference /*cp*/);
extern entity constant_memory_access_path_to_location_entity(reference /*cp*/);
extern bool location_entity_p(entity /*le*/);
#endif /*  effects_util_header_included */
