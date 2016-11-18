/* Warning! Do not modify this file that is automatically generated! */
/* Modify src/Libs/points-to/points-to-local.h instead, to add your own modifications. */

/* header file built by cproto */

#ifndef  points_to_header_included
#define  points_to_header_included
/*

  $Id: points-to-local.h 23065 2016-03-02 09:05:50Z coelho $

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
#include "points_to_private.h"
#include "effects.h"
#define SEQUENTIAL_POINTS_TO_SETS_SUFFIX ".pt"
#define USER_POINTS_TO_SETS_SUFFIX ".upt"

// FI: just in case another data structure would be more suitable or
// more efficient
// For instance, set of points-to could be a type declared in
// points_to_private.tex
#if 0
typedef set pt_map;
#define pt_map_undefined set_undefined
#define pt_map_undefined_p(pt) ((pt)==set_undefined)
#define new_pt_map() set_generic_make(set_private, points_to_equal_p, points_to_rank)
#define assign_pt_map(x,y) set_assign(x, y)
#define clear_pt_map(pt) set_clear(pt)
#define free_pt_map(pt) set_free(pt)
#define print_pt_map(pt) print_points_to_set("",pt);
// FI: varargs; probably OK with gcc preprocessor
#define free_pt_maps sets_free
#define union_of_pt_maps(pt1, pt2, pt3) set_union(pt1, pt2, pt3)
#define difference_of_pt_maps(pt1, pt2, pt3) set_difference(pt1, pt2, pt3)

#define empty_pt_map_p(s) set_empty_p(s)
#define consistent_pt_map_p(s) consistent_points_to_set(s)
// FI: Not so sure we do not need a new name
#define source_in_pt_map_p(cell,set) source_in_set_p(cell,set)
#define add_arc_to_pt_map(a, s) set_add_element((set) s, (set) s, (void *) a)

// FI: useful to have a function for debugging
#define remove_arc_from_pt_map(a, s) set_del_element((set) s, (set) s, (void *) a)

// A reminder:
// full_copy_pt_map(pt_map m)
#else
typedef points_to_graph pt_map;
#define pt_map_undefined points_to_graph_undefined
#define pt_map_undefined_p(pt) ((pt)==points_to_graph_undefined)
#define new_pt_map() make_points_to_graph(false, set_generic_make(set_private, points_to_equal_p, points_to_rank))
#define new_simple_pt_map() set_generic_make(set_private, points_to_equal_p, points_to_rank)
#define assign_pt_map(x,y) ((void) set_assign(points_to_graph_set(x), points_to_graph_set(y)), (x))
#define clear_pt_map(pt) set_clear(points_to_graph_set(pt))
// FI: free_set() is a shallow free, free_points_to_graph() is a deep free
#define free_pt_map(pt) free_points_to_graph(pt)
#define print_pt_map(pt) print_points_to_set("", points_to_graph_set(pt));
// FI: varargs; probably OK with gcc preprocessor
#define free_pt_maps free_points_to_graph_sets

#define union_of_pt_maps(pt1, pt2, pt3) set_union(points_to_graph_set(pt1), \
						  points_to_graph_set(pt2), \
						  points_to_graph_set(pt3))
#define difference_of_pt_maps(pt1, pt2, pt3) \
  set_difference(points_to_graph_set(pt1), \
		 points_to_graph_set(pt2), \
		 points_to_graph_set(pt3))

#define empty_pt_map_p(s) set_empty_p(points_to_graph_set(s))
//#define consistent_pt_map_p(s) consistent_points_to_set(points_to_graph_set(s))
#define consistent_pt_map_p(s) consistent_points_to_graph_p(s)
// FI: Not so sure we do not need a new name
#define source_in_pt_map_p(cell,set) source_in_set_p(cell,points_to_graph_set(set))
// Returns pt_map s after update via side-effect
#define add_arc_to_pt_map(a, s) (set_add_element((set) points_to_graph_set(s), (set) points_to_graph_set(s), (void *) a))
#define add_arc_to_pt_map_(a, s) (add_arc_to_pt_map(a, s), (s))
#define add_arc_to_simple_pt_map(a, s) set_add_element((set) s, (set) s, (void *) a)

// FI: useful to have a function for debugging
#define remove_arc_from_pt_map(a, s) (set_del_element((set) points_to_graph_set(s), (set) points_to_graph_set(s), (void *) a))
#define remove_arc_from_pt_map_(a, s) (remove_arc_from_pt_map(a, s), (s))
#define remove_arc_from_simple_pt_map(a, s) set_del_element((set) s, (set) s, (void *) a)

// A reminder:
// full_copy_pt_map(pt_map m)
#endif
/* points_to_set.c */
extern int compare_entities_without_scope(const entity */*pe1*/, const entity */*pe2*/);
extern entity location_entity(cell /*c*/);
extern bool locations_equal_p(cell /*acc1*/, cell /*acc2*/);
extern int points_to_equal_p(const void */*vpt1*/, const void */*vpt2*/);
extern _uint points_to_rank(const void */*vpt*/, size_t /*size*/);
extern string points_to_name(const points_to /*pt*/);
extern string points_to_cell_name(cell /*source*/);
extern set points_to_set_block_projection(set /*pts*/, list /*l*/, bool /*main_p*/, bool /*body_p*/);
extern set points_to_source_projection(set /*pts*/, entity /*e*/);
extern points_to_graph points_to_cell_source_projection(points_to_graph /*ptg*/, cell /*c*/);
extern set remove_points_to_cell(cell /*c*/, set /*g*/);
extern set remove_points_to_cells(list /*cl*/, set /*g*/);
extern list potential_to_effective_memory_leaks(list /*pmll*/, set /*res*/);
extern set points_to_function_projection(set /*pts*/);
extern bool cell_out_of_scope_p(cell /*c*/);
extern void print_or_dump_points_to(const points_to /*pt*/, bool /*print_p*/);
extern void print_points_to(const points_to /*pt*/);
extern void dump_points_to(const points_to /*pt*/);
extern void print_or_dump_points_to_set(string /*what*/, set /*s*/, bool /*print_p*/);
extern void print_points_to_set(string /*what*/, set /*s*/);
extern void dump_points_to_set(string /*what*/, set /*s*/);
extern bool source_in_set_p(cell /*source*/, set /*s*/);
extern bool source_subset_in_set_p(cell /*source*/, set /*s*/);
extern bool source_in_graph_p(cell /*source*/, points_to_graph /*s*/);
extern bool sink_in_set_p(cell /*sink*/, set /*s*/);
extern points_to find_arc_in_points_to_set(cell /*source*/, cell /*sink*/, pt_map /*ptm*/);
extern list anywhere_source_to_sinks(cell /*source*/, pt_map /*pts*/);
extern void print_points_to_path(list /*p*/);
extern bool type_compatible_with_points_to_cell_p(type /*t*/, cell /*c*/);
extern cell type_compatible_super_cell(type /*t*/, cell /*c*/);
extern cell find_kth_points_to_node_in_points_to_path(list /*p*/, type /*t*/, int /*k*/);
extern bool node_in_points_to_path_p(cell /*n*/, list /*p*/);
extern points_to points_to_path_to_k_limited_points_to_path(list /*p*/, int /*k*/, type /*t*/, bool /*array_p*/, pt_map /*in*/);
extern points_to create_k_limited_stub_points_to(cell /*source*/, type /*t*/, bool /*array_p*/, pt_map /*in*/);
extern list sink_to_sources(cell /*sink*/, set /*pts*/, bool /*fresh_p*/);
extern list stub_source_to_sinks(cell /*source*/, pt_map /*pts*/, bool /*fresh_p*/);
extern list scalar_stub_source_to_sinks(cell /*source*/, pt_map /*pts*/, bool /*fresh_p*/);
extern list array_stub_source_to_sinks(cell /*source*/, pt_map /*pts*/, bool /*fresh_p*/);
extern list generic_stub_source_to_sinks(cell /*source*/, pt_map /*pts*/, bool /*array_p*/, bool /*fresh_p*/);
extern list points_to_cell_null_initialization(cell /*c*/, pt_map /*pts*/);
extern list nowhere_source_to_sinks(cell /*source*/, pt_map /*pts*/);
extern list null_source_to_sinks(cell /*source*/, pt_map /*pts*/);
extern list formal_source_to_sinks(cell /*source*/, pt_map /*pts*/, bool /*fresh_p*/);
extern list global_source_to_sinks(cell /*source*/, pt_map /*pts*/, bool /*fresh_p*/);
extern list reference_to_points_to_translations(entity /*v*/, list /*sl*/, pt_map /*ptm*/);
extern list points_to_reference_to_translation(reference /*n_r*/, list /*sl*/, pt_map /*ptm*/, bool /*fresh_p*/);
extern list points_to_source_to_translations(cell /*source*/, pt_map /*ptm*/, bool /*fresh_p*/);
extern list generic_points_to_source_to_sinks(cell /*source*/, pt_map /*ptm*/, bool /*fresh_p*/, bool /*strict_p*/, bool /*all_p*/, bool /*effective_p*/);
extern list points_to_source_to_sinks(cell /*source*/, pt_map /*ptm*/, bool /*fresh_p*/);
extern list points_to_source_to_effective_sinks(cell /*source*/, pt_map /*ptm*/, bool /*fresh_p*/);
extern list points_to_source_to_some_sinks(cell /*source*/, pt_map /*ptm*/, bool /*fresh_p*/);
extern list points_to_source_to_any_sinks(cell /*source*/, pt_map /*ptm*/, bool /*fresh_p*/);
extern list points_to_sink_to_sources(cell /*sink*/, pt_map /*ptm*/, bool /*fresh_p*/);
extern points_to points_to_sink_to_points_to(cell /*sink*/, pt_map /*ptm*/);
extern list points_to_source_name_to_sinks(string /*sn*/, pt_map /*ptm*/, bool /*fresh_p*/);
extern cell points_to_source_name_to_source_cell(string /*sn*/, pt_map /*ptm*/, bool /*fresh_p*/);
extern list generic_points_to_sources_to_sinks(list /*sources*/, pt_map /*ptm*/, bool /*fresh_p*/, bool /*effective_p*/);
extern list points_to_sources_to_sinks(list /*sources*/, pt_map /*ptm*/, bool /*fresh_p*/);
extern list points_to_sources_to_effective_sinks(list /*sources*/, pt_map /*ptm*/, bool /*fresh_p*/);
extern list points_to_source_to_arcs(cell /*source*/, pt_map /*ptm*/, bool /*fresh_p*/);
extern int points_to_cell_to_number_of_unbounded_dimensions(cell /*c*/);
extern int points_to_reference_to_number_of_unbounded_dimensions(reference /*r*/);
extern int points_to_subscripts_to_number_of_unbounded_dimensions(list /*sl*/);
extern bool sinks_fully_matches_source_p(cell /*source*/, list /*sinks*/);
extern list source_to_sinks(cell /*source*/, pt_map /*pts*/, bool /*fresh_p*/);
extern list extended_source_to_sinks(cell /*sc*/, pt_map /*in*/);
extern list extended_sources_to_sinks(list /*pointed*/, pt_map /*in*/);
extern list any_source_to_sinks(cell /*source*/, pt_map /*pts*/, bool /*fresh_p*/);
extern list pointer_source_to_sinks(cell /*sc*/, pt_map /*in*/);
extern list variable_to_sinks(entity /*e*/, pt_map /*ptm*/, bool /*fresh_p*/);
extern list null_to_sinks(cell /*source*/, pt_map /*ptm*/);
extern list sources_to_sinks(list /*sources*/, pt_map /*ptm*/, bool /*fresh_p*/);
extern list reference_to_sinks(reference /*r*/, pt_map /*in*/, bool /*fresh_p*/);
extern set merge_points_to_set(set /*s1*/, set /*s2*/);
extern set exact_to_may_points_to_set(set /*s*/);
extern bool cell_in_list_p(cell /*c*/, const list /*lx*/);
extern bool points_to_in_list_p(points_to /*pt*/, const list /*lx*/);
extern bool points_to_compare_cell(cell /*c1*/, cell /*c2*/);
extern bool points_to_compare_ptr_cell(const void */*vcel1*/, const void */*vcel2*/);
extern int points_to_compare_location(void */*vpt1*/, void */*vpt2*/);
extern bool consistent_points_to_set(set /*s*/);
extern bool points_to_set_sharing_p(set /*s*/);
extern void upgrade_approximations_in_points_to_set(pt_map /*ptm*/);
extern void remove_points_to_arcs(cell /*source*/, cell /*sink*/, pt_map /*pt*/);
extern void points_to_cell_list_and(list */*a*/, const list /*b*/);
extern void free_points_to_graph_sets(points_to_graph /*s*/, ...);
extern pt_map graph_assign_list(pt_map /*ptm*/, list /*l*/);
extern pt_map merge_points_to_graphs(pt_map /*s1*/, pt_map /*s2*/);
extern pt_map points_to_graph_assign(pt_map /*out*/, pt_map /*in*/);
extern points_to fuse_points_to_sink_cells(cell /*source*/, list /*sink_l*/, pt_map /*in*/);
extern int maximal_out_degree_of_points_to_graph(string */*mod_cell*/, pt_map /*in*/);
extern pt_map normalize_points_to_graph(pt_map /*ptg*/);
extern string points_to_cell_to_string(cell /*c*/);
extern bool unreachable_points_to_cell_p(cell /*c*/, pt_map /*ptg*/);
extern pt_map generic_remove_unreachable_vertices_in_points_to_graph(pt_map /*ptg*/, int code, bool /*verbose_p*/);
extern pt_map remove_unreachable_stub_vertices_in_points_to_graph(pt_map /*in*/);
extern pt_map remove_unreachable_heap_vertices_in_points_to_graph(pt_map /*in*/, bool /*verbose_p*/);
extern pt_map remove_unreachable_vertices_in_points_to_graph(pt_map /*in*/);
extern bool consistent_points_to_graph_p(points_to_graph /*ptg*/);
extern void remove_impossible_arcs_to_null(list */*pL*/, pt_map /*in*/);
extern bool arc_in_points_to_set_p(points_to /*spt*/, set /*pts*/);
extern pt_map get_points_to_graph_from_statement(statement /*st*/);
/* points_to_prettyprint.c */
extern bool printed_points_to_list_undefined_p(void);
extern void reset_printed_points_to_list(void);
extern void error_reset_printed_points_to_list(void);
extern void set_printed_points_to_list(statement_points_to /*o*/);
extern statement_points_to get_printed_points_to_list(void);
extern void init_printed_points_to_list(void);
extern void close_printed_points_to_list(void);
extern void store_printed_points_to_list(statement /*k*/, points_to_list /*v*/);
extern void update_printed_points_to_list(statement /*k*/, points_to_list /*v*/);
extern points_to_list load_printed_points_to_list(statement /*k*/);
extern points_to_list delete_printed_points_to_list(statement /*k*/);
extern bool bound_printed_points_to_list_p(statement /*k*/);
extern void store_or_update_printed_points_to_list(statement /*k*/, points_to_list /*v*/);
extern text text_points_to(entity /*module*/, int /*margin*/, statement /*s*/);
extern text text_code_points_to(statement /*s*/);
extern bool print_code_points_to(const char */*module_name*/, string /*resource_name*/, string /*file_suffix*/);
extern void print_points_to_list(points_to_list /*ptl*/);
extern void print_points_to_graph(points_to_graph /*ptg*/);
extern bool print_code_points_to_list(const char */*module_name*/);
extern list words_points_to(points_to /*pt*/);
extern text text_points_to_relation(points_to /*pt_to*/);
extern text text_points_to_relations(points_to_list /*ptl*/, string /*header*/);
extern void print_points_to_relation(points_to /*pt_to*/);
extern void print_points_to_relations(list /*l_pt_to*/);
extern text text_pt_to(entity /*module_name*/, int /*margin*/, statement /*s*/);
/* points_to_init_analysis.c */
extern void points_to_forward_translation(void);
extern void points_to_backward_translation(void);
extern set formal_points_to_parameter(cell /*c*/);
extern entity create_stub_entity(entity /*e*/, string /*fs*/, type /*t*/);
extern cell create_scalar_stub_sink_cell(entity /*v*/, type /*st*/, type /*pt*/, int /*d*/, list /*sl*/, string /*fs*/);
extern int points_to_indices_to_array_index_number(list /*sl*/);
extern void points_to_indices_to_unbounded_indices(list /*sl*/);
extern list points_to_indices_to_subscript_indices(list /*ptsl*/);
extern string reference_to_field_disambiguator(reference /*r*/);
extern points_to create_stub_points_to(cell /*c*/, type /*unused_st*/, bool /*exact_p*/);
extern points_to create_advanced_stub_points_to(cell /*c*/, type /*t*/, bool /*exact_p*/);
extern points_to create_pointer_to_array_stub_points_to(cell /*c*/, type /*t*/, bool /*exact_p*/);
extern set pointer_formal_parameter_to_stub_points_to(type /*pt*/, cell /*c*/);
extern set derived_formal_parameter_to_stub_points_to(type /*pt*/, cell /*c*/);
extern set typedef_formal_parameter_to_stub_points_to(type /*pt*/, cell /*c*/);
extern set array_formal_parameter_to_stub_points_to(type /*t*/, cell /*c*/);
/* statement.c */
extern set full_copy_simple_pt_map(set /*m*/);
extern pt_map full_copy_pt_map(pt_map /*in*/);
extern void init_statement_points_to_context(void);
extern void push_statement_points_to_context(statement /*s*/, pt_map /*in*/);
extern void add_arc_to_statement_points_to_context(points_to /*pt*/);
extern void update_statement_points_to_context_with_arc(points_to /*pt*/);
extern int points_to_context_statement_line_number(void);
extern pt_map points_to_context_statement_in(void);
extern pt_map pop_statement_points_to_context(void);
extern void reset_statement_points_to_context(void);
extern bool statement_points_to_context_defined_p(void);
extern pt_map statement_to_points_to(statement /*s*/, pt_map /*pt_in*/);
extern pt_map declaration_statement_to_points_to(statement /*s*/, pt_map /*pt_in*/);
extern pt_map instruction_to_points_to(instruction /*i*/, pt_map /*pt_in*/);
extern pt_map sequence_to_points_to(sequence /*seq*/, pt_map /*pt_in*/);
extern void equalize_points_to_domains(points_to_graph /*pt_t*/, points_to_graph /*pt_f*/);
extern pt_map test_to_points_to(test /*t*/, pt_map /*pt_in*/);
extern pt_map loop_to_points_to(loop /*l*/, pt_map /*pt_in*/);
extern pt_map whileloop_to_points_to(whileloop /*wl*/, pt_map /*pt_in*/);
extern pt_map any_loop_to_points_to(statement /*b*/, expression /*init*/, expression /*c*/, expression /*inc*/, pt_map /*pt_in*/);
extern pt_map new_any_loop_to_points_to(statement /*b*/, expression /*init*/, expression /*c*/, expression /*inc*/, pt_map /*pt_in*/);
extern pt_map k_limit_points_to(pt_map /*pt_out*/, int /*k*/);
extern cell make_anywhere_cell(type /*t*/);
extern pt_map unstructured_to_points_to(unstructured /*u*/, pt_map /*pt_in*/);
extern pt_map multitest_to_points_to(multitest /*mt*/, pt_map /*pt_in*/);
extern pt_map forloop_to_points_to(forloop /*fl*/, pt_map /*pt_in*/);
/* expression.c */
extern void subscripted_reference_to_points_to(reference /*r*/, list /*sl*/, pt_map /*pt_in*/);
extern pt_map expression_to_points_to(expression /*e*/, pt_map /*pt_in*/, bool /*side_effect_p*/);
extern pt_map expressions_to_points_to(list /*el*/, pt_map /*pt_in*/, bool /*side_effect_p*/);
extern pt_map reference_to_points_to(reference /*r*/, pt_map /*pt_in*/, bool /*side_effect_p*/);
extern pt_map range_to_points_to(range /*r*/, pt_map /*pt_in*/, bool /*side_effect_p*/);
extern pt_map call_to_points_to(call /*c*/, pt_map /*pt_in*/, list /*el*/, bool /*side_effect_p*/);
extern pt_map constant_call_to_points_to(call /*c*/, pt_map /*pt_in*/);
extern pt_map intrinsic_call_to_points_to(call /*c*/, pt_map /*pt_in*/, bool /*side_effect_p*/);
extern pt_map pointer_arithmetic_to_points_to(expression /*lhs*/, expression /*delta*/, pt_map /*pt_in*/);
extern void offset_array_reference(reference /*r*/, expression /*delta*/, type /*et*/);
extern void offset_cells(cell /*source*/, list /*sinks*/, expression /*delta*/, type /*et*/, pt_map /*in*/);
extern points_to offset_cell(points_to /*pt*/, expression /*delta*/, type /*et*/);
extern void offset_points_to_cells(list /*sinks*/, expression /*delta*/, type /*t*/);
extern void offset_points_to_cell(cell /*sink*/, expression /*delta*/, type /*t*/, bool /*unique_p*/);
extern pt_map assignment_to_points_to(expression /*lhs*/, expression /*rhs*/, pt_map /*pt_in*/);
extern void check_type_of_points_to_cells(list /*sinks*/, type /*ct*/, bool /*eval_p*/);
extern void check_rhs_value_types(expression /*lhs*/, expression /*rhs*/, list /*sinks*/);
extern pt_map internal_pointer_assignment_to_points_to(expression /*lhs*/, expression /*rhs*/, pt_map /*pt_in*/);
extern pt_map pointer_assignment_to_points_to(expression /*lhs*/, expression /*rhs*/, pt_map /*pt_in*/);
extern list freeable_points_to_cells(list /*R*/);
extern pt_map freed_list_to_points_to(expression /*lhs*/, list /*L*/, list /*R*/, pt_map /*pt_in*/);
extern pt_map freed_pointer_to_points_to(expression /*lhs*/, pt_map /*pt_in*/, bool /*side_effect_p*/);
extern cell reduce_cell_to_pointer_type(cell /*c*/);
extern list reduce_cells_to_pointer_type(list /*cl*/);
extern list points_to_cell_to_pointer_cells(cell /*c*/);
extern pt_map memory_leak_to_more_memory_leaks(cell /*l*/, pt_map /*in*/);
extern pt_map list_assignment_to_points_to(list /*L*/, list /*R*/, pt_map /*pt_out*/);
extern pt_map struct_initialization_to_points_to(expression /*lhs*/, expression /*rhs*/, pt_map /*in*/);
extern pt_map struct_assignment_to_points_to(expression /*lhs*/, expression /*rhs*/, pt_map /*pt_in*/);
extern pt_map application_to_points_to(application /*a*/, pt_map /*pt_in*/, bool /*side_effect_p*/);
extern pt_map condition_to_points_to(expression /*c*/, pt_map /*in*/, bool /*true_p*/);
extern pt_map reference_condition_to_points_to(reference /*r*/, pt_map /*in*/, bool /*true_p*/);
extern pt_map call_condition_to_points_to(call /*c*/, pt_map /*in*/, list /*el*/, bool /*true_p*/);
extern pt_map intrinsic_call_condition_to_points_to(call /*c*/, pt_map /*in*/, bool /*true_p*/);
extern pt_map user_call_condition_to_points_to(call /*c*/, pt_map /*in*/, list /*el*/, bool /*true_p*/);
extern pt_map boolean_intrinsic_call_condition_to_points_to(call /*c*/, pt_map /*in*/, bool /*true_p*/);
extern bool cell_is_less_than_or_equal_to_p(cell /*c1*/, cell /*c2*/);
extern bool cell_is_less_than_p(cell /*c1*/, cell /*c2*/);
extern bool cell_is_greater_than_or_equal_to_p(cell /*c1*/, cell /*c2*/);
extern bool cell_is_greater_than_p(cell /*c1*/, cell /*c2*/);
extern pt_map null_equal_condition_to_points_to(expression /*e*/, pt_map /*in*/);
extern pt_map null_non_equal_condition_to_points_to(expression /*e*/, pt_map /*in*/);
extern pt_map equal_condition_to_points_to(list /*al*/, pt_map /*in*/);
extern pt_map non_equal_condition_to_points_to(list /*al*/, pt_map /*in*/);
extern pt_map order_condition_to_points_to(entity /*f*/, list /*al*/, bool /*true_p*/, pt_map /*in*/);
extern pt_map relational_intrinsic_call_condition_to_points_to(call /*c*/, pt_map /*in*/, bool /*true_p*/);
/* passes.c */
extern void points_to_storage(set /*pts_to_set*/, statement /*s*/, bool /*store*/);
extern void fi_points_to_storage(pt_map /*ptm*/, statement /*s*/, bool /*store*/);
extern pt_map points_to_to_context_points_to(pt_map /*in*/);
extern void init_points_to_context(pt_map /*init*/);
extern void reset_points_to_context(void);
extern pt_map update_points_to_graph_with_arc(points_to /*a*/, pt_map /*pt*/);
extern void add_arc_to_points_to_context(points_to /*pt*/);
extern void update_points_to_context_with_arc(points_to /*pt*/);
extern pt_map get_points_to_context(void);
extern void clean_up_points_to_stubs(entity /*module*/);
extern bool init_points_to_analysis(char */*module_name*/);
extern bool interprocedural_points_to_analysis_p(void);
extern bool fast_interprocedural_points_to_analysis_p(void);
extern bool intraprocedural_points_to_analysis(char */*module_name*/);
extern bool interprocedural_points_to_analysis(char */*module_name*/);
extern bool fast_interprocedural_points_to_analysis(char */*module_name*/);
extern bool initial_points_to(char */*name*/);
extern bool program_points_to(char */*name*/);
/* sinks.c */
extern list entity_to_sinks(entity /*e*/);
extern cell entity_to_cell(entity /*e*/);
extern list points_to_null_sinks(void);
extern cell make_null_cell(void);
extern list points_to_anywhere_sinks(type /*t*/);
extern list call_to_points_to_sinks(call /*c*/, type /*et*/, pt_map /*in*/, bool /*eval_p*/, bool /*constant_p*/);
extern list intrinsic_call_to_points_to_sinks(call /*c*/, pt_map /*in*/, bool /*eval_p*/, bool /*constant_p*/);
extern list unary_intrinsic_call_to_points_to_sinks(call /*c*/, pt_map /*in*/, bool /*eval_p*/, bool /*constant_p*/);
extern list binary_intrinsic_call_to_points_to_sinks(call /*c*/, pt_map /*in*/, bool /*eval_p*/);
extern list expression_to_points_to_sinks_with_offset(expression /*a1*/, expression /*a2*/, pt_map /*in*/);
extern list ternary_intrinsic_call_to_points_to_sinks(call /*c*/, pt_map /*in*/, bool /*eval_p*/, bool /*constant_p*/);
extern list nary_intrinsic_call_to_points_to_sinks(call /*c*/, pt_map /*in*/);
extern reference simplified_reference(reference /*r*/);
extern list pointer_reference_to_points_to_sinks(reference /*r*/, pt_map /*in*/, bool /*eval_p*/);
extern list reference_to_points_to_sinks(reference /*r*/, type /*et*/, pt_map /*in*/, bool /*eval_p*/, bool /*constant_p*/);
extern list cast_to_points_to_sinks(cast /*ce*/, type /*et*/, pt_map /*in*/, bool /*eval_p*/);
extern list sizeofexpression_to_points_to_sinks(sizeofexpression /*soe*/, type /*et*/, pt_map /*in*/);
extern void init_heap_model(statement /*s*/);
extern void reset_heap_model(void);
extern statement get_heap_statement(void);
extern int get_heap_counter(void);
extern list malloc_to_points_to_sinks(expression /*e*/, pt_map /*in*/);
extern list unique_malloc_to_points_to_sinks(expression /*e*/);
extern list insensitive_malloc_to_points_to_sinks(expression /*e*/);
extern list flow_sensitive_malloc_to_points_to_sinks(expression /*e*/);
extern list application_to_points_to_sinks(application /*a*/, type /*et*/, pt_map /*in*/);
extern expression pointer_subscript_to_expression(cell /*c*/, list /*csl*/);
extern list subscript_to_points_to_sinks(subscript /*s*/, type /*et*/, pt_map /*in*/, bool /*eval_p*/);
extern list range_to_points_to_sinks(range /*r*/, pt_map /*in*/);
extern list expression_to_points_to_cells(expression /*e*/, pt_map /*in*/, bool /*eval_p*/, bool /*constant_p*/);
extern list expression_to_points_to_sinks(expression /*e*/, pt_map /*in*/);
extern list expression_to_points_to_sources(expression /*e*/, pt_map /*in*/);
extern bool reference_must_points_to_null_p(reference /*r*/, pt_map /*in*/);
extern bool reference_may_points_to_null_p(reference /*r*/, pt_map /*in*/);
/* unstructured.c */
extern bool control_in_set_p(control /*c*/, set /*s*/);
extern bool control_equal_p(const void */*vc1*/, const void */*vc2*/);
extern _uint control_rank(const void */*vc*/, size_t /*size*/);
extern bool Ready_p(control /*c*/, set /*Processed*/, set /*Reachable*/);
extern set ready_to_be_processed_set(control /*n*/, set /*Processed*/, set /*Reachable*/);
extern pt_map new_points_to_unstructured(unstructured /*uns*/, pt_map /*pt_in_g*/, bool /*store*/);
/* variable.c */
extern list variable_to_pointer_locations(entity /*e*/);
extern list struct_variable_to_pointer_locations(entity /*e*/, entity /*ee*/);
extern list struct_variable_to_pointer_subscripts(cell /*c*/, entity /*f*/);
/* interprocedural.c */
extern list points_to_cells_parameters(list /*dl*/);
extern list points_to_cells_pointer_arguments(list /*al*/);
extern points_to_graph user_call_to_points_to(call /*c*/, points_to_graph /*pt_in*/, list /*el*/);
extern list user_call_to_points_to_sinks(call /*c*/, type /*et*/, pt_map /*in*/, bool /*eval_p*/);
extern void remove_arcs_from_pt_map(points_to /*pts*/, set /*pt_out*/);
extern pt_map user_call_to_points_to_fast_interprocedural(call /*c*/, pt_map /*pt_in*/, list /*csel*/);
extern void recursive_filter_formal_context_according_to_actual_context(list /*fcl*/, set /*pt_in*/, set /*pt_binded*/, set /*binding*/, set /*filtered*/);
extern set filter_formal_context_according_to_actual_context(list /*fpcl*/, set /*pt_in*/, set /*pt_binded*/, set /*binding*/);
extern set filter_formal_out_context_according_to_formal_in_context(set /*out*/, set /*in*/, list /*wpl*/, entity /*f*/);
extern void points_to_translation_of_struct_formal_parameter(cell /*fc*/, cell /*ac*/, approximation /*a*/, type /*st*/, set /*translation*/);
extern bool points_to_translation_mapping_is_typed_p(set /*translation*/);
extern void points_to_translation_of_formal_parameters(list /*fpcl*/, list /*al*/, pt_map /*pt_in*/, set /*translation*/);
extern void add_implicitly_killed_arcs_to_kill_set(set /*pt_kill*/, list /*wpl*/, set /*pt_caller*/, set /*pt_out_callee_filtered*/, set /*binding*/, entity /*f*/);
extern list translation_transitive_closure(cell /*c*/, set /*translation*/);
extern bool aliased_translation_p(list /*fpcl*/, set /*translation*/);
extern set user_call_to_points_to_interprocedural_binding_set(call /*c*/, pt_map /*pt_caller*/);
extern pt_map user_call_to_points_to_interprocedural(call /*c*/, pt_map /*pt_caller*/);
extern pt_map user_call_to_points_to_intraprocedural(call /*c*/, pt_map /*pt_in*/, list /*el*/);
extern set compute_points_to_kill_set(list /*written_must_translated*/, set /*pt_caller*/, set /*binding*/);
extern list points_to_cell_translation(cell /*sr1*/, set /*binding*/, entity /*f*/);
extern list generic_points_to_cells_translation(list /*cl*/, set /*binding*/, entity /*f*/, bool /*exact_p*/);
extern list points_to_cells_translation(list /*cl*/, set /*binding*/, entity /*f*/);
extern list points_to_cells_exact_translation(list /*cl*/, set /*binding*/, entity /*f*/);
extern set compute_points_to_gen_set(set /*pt_out*/, list /*Written*/, set /*binding*/, entity /*f*/);
extern set points_to_binding_arguments(cell /*c1*/, cell /*c2*/, set /*in*/, set /*pt_binded*/);
extern list written_pointers_set(list /*eff*/);
extern list certainly_written_pointers_set(list /*eff*/);
extern set compute_points_to_binded_set(entity /*called_func*/, list /*real_args*/, set /*pt_caller*/, bool */*success_p*/);
extern set points_to_binding(list /*args*/, set /*in*/, set /*pt_binded*/);
extern list generic_points_to_set_to_stub_cell_list(entity /*f*/, set /*s*/, list /*osl*/);
extern list points_to_set_to_stub_cell_list(set /*s*/, list /*osl*/);
extern list points_to_set_to_module_stub_cell_list(entity /*m*/, set /*s*/, list /*osl*/);
extern cell points_to_source_alias(points_to /*pt*/, set /*pt_binded*/);
/* dereferencing.c */
extern pt_map dereferencing_subscript_to_points_to(subscript /*sub*/, pt_map /*in*/);
extern pt_map dereferencing_to_points_to(expression /*p*/, pt_map /*in*/);
extern bool pointer_points_to_reference_p(reference /*r*/);
extern void pointer_reference_dereferencing_to_points_to(reference /*r*/, pt_map /*in*/);
extern pt_map reference_dereferencing_to_points_to(reference /*r*/, pt_map /*in*/, bool /*nowhere_dereferencing_p*/, bool /*null_dereferencing_p*/);
extern bool expression_to_points_to_cell_p(expression /*e*/);
extern list dereferencing_to_sinks(expression /*a*/, pt_map /*in*/, bool /*eval_p*/);
/* constant-path-utils.c */
extern cell make_nowhere_cell(void);
extern cell make_typed_nowhere_cell(type /*t*/);
extern cell cell_to_nowhere_sink(cell /*source*/);
extern set points_to_anywhere_typed(list /*lhs_list*/, set /*input*/);
extern set points_to_anywhere(list /*lhs_list*/, set /*input*/);
extern list array_to_constant_paths(expression /*e*/, set /*in*/);
extern cell max_module(cell /*m1*/, cell /*m2*/);
extern bool entity_any_module_p(entity /*e*/);
extern bool opkill_may_module(cell /*m1*/, cell /*m2*/);
extern bool opkill_must_module(cell /*m1*/, cell /*m2*/);
extern cell op_gen_module(cell /*m1*/, cell /*m2*/);
extern bool opkill_may_name(cell /*n1*/, cell /*n2*/);
extern bool opkill_must_name(cell /*n1*/, cell /*n2*/);
extern type max_type(type /*t1*/, type /*t2*/);
extern bool opkill_may_type(type /*t1*/, type /*t2*/);
extern bool opkill_must_type(type /*t1*/, type /*t2*/);
extern type opgen_may_type(type /*t1*/, type /*t2*/);
extern type opgen_must_type(type /*t1*/, type /*t2*/);
extern bool opkill_may_reference(cell /*c1*/, cell /*c2*/);
extern bool opkill_must_reference(cell /*c1*/, cell /*c2*/);
extern bool opkill_may_vreference(cell /*c1*/, cell /*c2*/);
extern bool opkill_must_vreference(cell /*c1*/, cell /*c2*/);
extern bool opkill_may_constant_path(cell /*c1*/, cell /*c2*/);
extern bool opkill_must_constant_path(cell /*c1*/, cell /*c2*/);
extern set kill_may_set(list /*L*/, set /*in_may*/);
extern set kill_must_set(list /*L*/, set /*in*/);
extern set points_to_may_filter(set /*in*/);
extern set points_to_must_filter(set /*in*/);
extern bool address_of_expression_p(expression /*e*/);
extern bool subscript_expression_p(expression /*e*/);
extern set gen_may_set(list /*L*/, list /*R*/, set /*in_may*/, bool */*address_of_p*/);
extern set gen_must_set(list /*L*/, list /*R*/, set /*in_must*/, bool */*address_of_p*/);
extern bool unique_location_cell_p(cell /*c*/);
extern set gen_may_constant_paths(cell /*l*/, list /*R*/, set /*in_may*/, bool */*address_of_p*/, int /*Lc*/);
extern set gen_must_constant_paths(cell /*l*/, list /*R*/, set /*in_must*/, bool */*address_of_p*/, int /*Lc*/);
extern points_to opgen_may_constant_path(cell /*l*/, cell /*r*/);
extern points_to opgen_must_constant_path(cell /*l*/, cell /*r*/);
extern bool opgen_may_module(entity /*e1*/, entity /*e2*/);
extern bool opgen_must_module(entity /*e1*/, entity /*e2*/);
extern bool opgen_may_name(entity /*e1*/, entity /*e2*/);
extern bool opgen_must_name(entity /*e1*/, entity /*e2*/);
extern bool opgen_may_vreference(list /*vr1*/, list /*vr2*/);
extern bool atomic_constant_path_p(cell /*cp*/);
extern set opgen_null_location(set /*L*/, cell /*r*/);
extern set points_to_independent_store(set /*s*/);
extern bool equal_must_vreference(cell /*c1*/, cell /*c2*/);
extern set points_to_nowhere(list /*lhs_list*/, set /*input*/);
#endif /*  points_to_header_included */
