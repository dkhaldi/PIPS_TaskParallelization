/* Warning! Do not modify this file that is automatically generated! */
/* Modify src/Libs/transformations/transformations-local.h instead, to add your own modifications. */

/* header file built by cproto */

#ifndef  transformations_header_included
#define  transformations_header_included
/*

  $Id: transformations-local.h 23065 2016-03-02 09:05:50Z coelho $

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


/* What is returned by dead_test_filter : */
enum dead_test { nothing_about_test, then_is_dead, else_is_dead };
typedef enum dead_test dead_test;
/* util.c */
extern void statement_clean_declarations(statement /*s*/);
extern void entity_clean_declarations(entity /*module*/, statement /*s*/);
extern statement find_loop_from_label(statement /*s*/, entity /*label*/);
extern int get_processor_number(void);
extern int get_vector_register_length(void);
extern int get_vector_register_number(void);
/* loop_unroll.c */
extern void do_loop_unroll(statement /*loop_statement*/, int /*rate*/, void (* /*statement_post_processor*/)(statement));
extern void loop_unroll(statement /*loop_statement*/, int /*rate*/);
extern bool loop_fully_unrollable_p(loop /*l*/);
extern void full_loop_unroll(statement /*loop_statement*/);
extern bool unroll(const string /*mod_name*/);
extern bool full_unroll(const string /*mod_name*/);
extern bool full_unroll_pragma(const string /*mod_name*/);
/* prettyprintcray.c */
extern bool print_parallelizedcray_code(char */*mod_name*/);
/* strip_mine.c */
extern statement loop_strip_mine(statement /*loop_statement*/, int /*chunk_size*/, int /*chunk_number*/);
extern bool strip_mine(const string /*mod_name*/);
/* interactive_loop_transformation.c */
extern entity selected_label;
extern bool selected_loop_p(statement /*s*/);
extern bool interactive_loop_transformation(const char */*module_name*/, statement (* /*loop_transformation*/)(list, bool (*)(statement)));
extern bool print_loops(const string /*module_name*/);
extern bool flag_loops(const string /*module_name*/);
extern char *loop_pragma(const char */*module_name*/, const char */*parent_loop*/);
extern char *module_loops(const char */*module_name*/, const char */*parent_loop*/);
/* loop_normalize.c */
extern void loop_normalize_statement(statement /*s*/);
extern bool loop_normalize(const string /*mod_name*/);
extern bool linearize_loop_range(const char */*module_name*/);
/* interchange.c */
extern statement interchange_inner_outermost_loops(list /*lls*/, bool (* /*unused*/)(statement));
extern statement interchange_two_loops(list /*lls*/, int /*n1*/, int /*n2*/);
extern bool loop_interchange(const string /*module_name*/);
/* nest_parallelization.c */
extern bool nest_parallelization(const char */*module_name*/);
/* coarse_grain_parallelization.c */
extern bool coarse_grain_parallelization(const string /*module_name*/);
extern bool coarse_grain_parallelization_with_reduction(const string /*module_name*/);
/* dead_code_elimination.c */
extern bool dead_code_elimination_on_module(char */*module_name*/, bool /*use_out_regions*/);
extern bool dead_code_elimination(char */*module_name*/);
extern bool dead_code_elimination_with_out_regions(char */*module_name*/);
extern bool use_def_elimination(char */*module_name*/);
/* trivial_test_elimination.c */
extern bool suppress_trivial_test(const string /*mod_name*/);
/* privatize.c */
extern bool privatize_module(const string /*mod_name*/);
extern bool privatize_module_even_globals(const string /*mod_name*/);
extern bool localize_declaration(const string /*mod_name*/);
/* array_privatization.c */
extern bool array_privatizer(const string /*module_name*/);
extern bool array_section_privatizer(const string /*module_name*/);
extern bool print_code_privatized_regions(const string /*module_name*/);
extern bool declarations_privatizer(const string /*mod_name*/);
/* standardize_structure.c */
extern bool stf(const string /*mod_name*/);
/* simplify_control.c */
extern bool simplify_control(const string /*mod_name*/);
extern bool simplify_control_directly(const string /*mod_name*/);
extern bool suppress_dead_code(const string /*mod_name*/);
extern bool remove_useless_label(const string /*module_name*/);
/* declarations.c */
extern void module_clean_declarations(entity /*module*/, statement /*module_statement*/);
extern bool clean_declarations(const string /*module_name*/);
/* dynamic_declarations.c */
extern bool clean_unused_dynamic_variables(string /*module*/);
/* transformation_test.c */
extern bool transformation_test(const string /*mod_name*/);
/* freeze_variables.c */
extern bool freeze_variables(char */*mod_name*/);
/* array_resizing_bottom_up.c */
extern bool array_resizing_bottom_up(char */*mod_name*/);
extern bool array_resizing_full_bottom_up(char */*mod_name*/);
/* array_resizing_top_down.c */
extern bool array_resizing_top_down(const char */*module_name*/);
/* array_resizing_statistic.c */
extern bool array_resizing_statistic(const string /*module_name*/);
/* partial_redundancy_elimination.c */
extern bool partial_redundancy_elimination(const string /*module_name*/);
/* variable_expansion.c */
extern bool variable_expansion(const char */*module_name*/);
extern bool reduction_variable_expansion(const char */*module_name*/);
/* internalize_parallel_code.c */
extern bool internalize_parallel_code(const string /*mod_name*/);
/* index_set_splitting.c */
extern bool index_set_splitting(const string /*module_name*/);
extern bool force_loop_fusion(const string /*module_name*/);
/* for_loop_recovering.c */
extern bool recover_for_loop(const string /*module_name*/);
/* scalarization.c */
extern bool scalarization(const string /*module_name*/);
extern bool constant_array_scalarization(const string /*module_name*/);
extern bool quick_scalarization(const string /*module_name*/);
/* flatten_code.c */
extern bool statement_flatten_declarations(entity /*module*/, statement /*s*/);
extern bool flatten_code(const string /*module_name*/);
extern void statement_split_initializations(statement /*s*/);
extern bool split_initializations(const char */*module_name*/);
extern void split_update_call(call /*c*/);
extern bool split_update_operator(const char */*module_name*/);
/* induction_substitution.c */
extern bool induction_substitution(const string /*module_name*/);
/* strength_reduction.c */
extern bool strength_reduction(const string /*module_name*/);
/* loop_fusion.c */
extern bool loop_fusion(char */*module_name*/);
extern bool loop_fusion_with_regions(char */*module_name*/);
/* set_return_type.c */
extern bool set_return_type_as_typedef(const string /*mod_name*/);
/* cast_at_call_sites.c */
extern bool cast_at_call_sites(const string /*mod_name*/);
/* manage_parallel_loops.c */
extern bool limit_nested_parallelism(const string /*module_name*/);
extern bool limit_parallelism_using_complexity(const string /*module_name*/);
/* registers.c */
extern bool force_register_declarations(const char */*module_name*/);
/* identity_elimination.c */
extern bool identity_elimination(const char */*module_name*/);
extern bool identity_elimination_with_points_to(const char */*module_name*/);
/* loop_bound_minimization.c */
extern bool loop_bound_minimization_with_out_regions_on_statement(statement /*module_statement*/);
extern bool loop_bound_minimization_with_out_regions(const char */*module_name*/);
/* cprettyprinter.c */
extern bool print_interface(const char */*module_name*/);
extern bool print_crough(const char */*module_name*/);
extern bool print_c_code(const char */*module_name*/);
/* initialized_vla.c */
extern bool check_initialize_vla_with_preconditions(const string /*module_name*/);
extern bool check_initialize_vla_with_effects(const string /*module_name*/);
extern bool check_initialize_vla_with_regions(const string /*module_name*/);
extern bool initialize_vla_with_preconditions(const char */*module_name*/);
extern bool initialize_vla_with_effects(const char */*module_name*/);
extern bool initialize_vla_with_regions(const char */*module_name*/);
#endif /*  transformations_header_included */
