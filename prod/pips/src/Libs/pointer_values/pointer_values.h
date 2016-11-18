/* Warning! Do not modify this file that is automatically generated! */
/* Modify src/Libs/pointer_values/pointer_values-local.h instead, to add your own modifications. */

/* header file built by cproto */

#ifndef  pointer_values_header_included
#define  pointer_values_header_included
/*

  $Id: pointer_values-local.h 23065 2016-03-02 09:05:50Z coelho $

  Copyright 1989-2016 MINES ParisTech
  Copyright 2010 HPC Project

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

/* pv_context is a structure holding the methods to use during
   pointer values analyses */
typedef struct {

  /* ANALYSIS CONTROL */
  bool initial_pointer_values_p; /* set to true for an initial module analysis */

  /* PIPSDEBM INTERFACES */
  statement_cell_relations (*db_get_pv_func)(const char *);
  void (*db_put_pv_func)(const char * , statement_cell_relations);
  list (*db_get_in_pv_func)(const char *);
  void (*db_put_in_pv_func)(const char * , list);
  list (*db_get_out_pv_func)(const char *);
  void (*db_put_out_pv_func)(const char * , list);
  list (*db_get_initial_pv_func)(const char *);
  void (*db_put_initial_pv_func)(const char * , list);
  list (*db_get_program_pv_func)();
  void (*db_put_program_pv_func)(list);

/*   statement_cell_relations (*db_get_gen_pv_func)(char *); */
/*   void (*db_put_gen_pv_func)(char * , statement_cell_relations); */
/*   statement_effects (*db_get_kill_pv_func)(char *); */
/*   void (*db_put_kill_pv_func)(char * , statement_effects); */

  list (*make_pv_from_effects_func)(effect, effect, cell_interpretation, list);

  /* COMPARISON OPERATORS */
  bool (*cell_preceding_p_func)(cell, descriptor,
				cell, descriptor ,
				transformer, bool, bool *);

  /* TRANSLATION OPERATORS */
  void (*cell_reference_with_value_of_cell_reference_translation_func)
  (reference , descriptor, reference , descriptor, int, reference *, descriptor *, bool *);
  void (*cell_reference_with_address_of_cell_reference_translation_func)
  (reference , descriptor, reference , descriptor, int, reference *, descriptor *, bool *);

  /* UNARY OPERATORS */
  cell_relation (*pv_composition_with_transformer_func)(cell_relation, transformer );

  /* BINARY OPERATORS */
  list (*pvs_must_union_func)(list, list);
  list (*pvs_may_union_func)(list, list);
  bool (*pvs_equal_p_func)(list, list);

  /* STACKS */
  stack stmt_stack;
} pv_context;

/* pv_results is a structure holding the different results of an expression pointer values analysis */
typedef struct {
  list l_out; /* resulting pointer_values */
  list result_paths; /* resulting pointer path of the expression evaluation */
  list result_paths_interpretations; /* interpretation of the resulting pointer path */

} pv_results;

#define pips_debug_pv_results(level, message, pv_res) \
  ifdebug(level) { pips_debug(level, "%s\n", message); \
  print_pv_results(pv_res);}
/* pointer_values_analyses.c */
extern bool pv_undefined_p(void);
extern void reset_pv(void);
extern void error_reset_pv(void);
extern void set_pv(statement_cell_relations /*o*/);
extern statement_cell_relations get_pv(void);
extern void init_pv(void);
extern void close_pv(void);
extern void store_pv(statement /*k*/, cell_relations /*v*/);
extern void update_pv(statement /*k*/, cell_relations /*v*/);
extern cell_relations load_pv(statement /*k*/);
extern cell_relations delete_pv(statement /*k*/);
extern bool bound_pv_p(statement /*k*/);
extern void store_or_update_pv(statement /*k*/, cell_relations /*v*/);
extern bool gen_pv_undefined_p(void);
extern void reset_gen_pv(void);
extern void error_reset_gen_pv(void);
extern void set_gen_pv(statement_cell_relations /*o*/);
extern statement_cell_relations get_gen_pv(void);
extern void init_gen_pv(void);
extern void close_gen_pv(void);
extern void store_gen_pv(statement /*k*/, cell_relations /*v*/);
extern void update_gen_pv(statement /*k*/, cell_relations /*v*/);
extern cell_relations load_gen_pv(statement /*k*/);
extern cell_relations delete_gen_pv(statement /*k*/);
extern bool bound_gen_pv_p(statement /*k*/);
extern void store_or_update_gen_pv(statement /*k*/, cell_relations /*v*/);
extern bool kill_pv_undefined_p(void);
extern void reset_kill_pv(void);
extern void error_reset_kill_pv(void);
extern void set_kill_pv(statement_effects /*o*/);
extern statement_effects get_kill_pv(void);
extern void init_kill_pv(void);
extern void close_kill_pv(void);
extern void store_kill_pv(statement /*k*/, effects /*v*/);
extern void update_kill_pv(statement /*k*/, effects /*v*/);
extern effects load_kill_pv(statement /*k*/);
extern effects delete_kill_pv(statement /*k*/);
extern bool bound_kill_pv_p(statement /*k*/);
extern void store_or_update_kill_pv(statement /*k*/, effects /*v*/);
extern statement_cell_relations db_get_simple_pv(const char */*module_name*/);
extern void db_put_simple_pv(const char */*module_name*/, statement_cell_relations /*scr*/);
extern list db_get_in_simple_pv(const char */*module_name*/);
extern void db_put_in_simple_pv(const char */*module_name*/, list /*l_pv*/);
extern list db_get_out_simple_pv(const char */*module_name*/);
extern void db_put_out_simple_pv(const char */*module_name*/, list /*l_pv*/);
extern list db_get_initial_simple_pv(const char */*module_name*/);
extern void db_put_initial_simple_pv(const char */*module_name*/, list /*l_pv*/);
extern list db_get_program_simple_pv(void);
extern void db_put_program_simple_pv(list /*l_pv*/);
extern pv_context make_simple_pv_context(void);
extern void reset_pv_context(pv_context */*p_ctxt*/);
extern void pv_context_statement_push(statement /*s*/, pv_context */*ctxt*/);
extern void pv_context_statement_pop(pv_context */*ctxt*/);
extern statement pv_context_statement_head(pv_context */*ctxt*/);
extern pv_results make_pv_results(void);
extern void free_pv_results_paths(pv_results */*pv_res*/);
extern void print_pv_results(pv_results /*pv_res*/);
extern list make_anywhere_anywhere_pvs(void);
extern void range_to_post_pv(range /*r*/, list /*l_in*/, pv_results */*pv_res*/, pv_context */*ctxt*/);
extern void expression_to_post_pv(expression /*exp*/, list /*l_in*/, pv_results */*pv_res*/, pv_context */*ctxt*/);
extern void single_pointer_assignment_to_post_pv(effect /*lhs_eff*/, list /*l_rhs_eff*/, list /*l_rhs_kind*/, bool /*declaration_p*/, list /*l_in*/, pv_results */*pv_res*/, pv_context */*ctxt*/);
extern void multiple_pointer_assignment_to_post_pv(effect /*lhs_base_eff*/, type /*lhs_type*/, list /*l_rhs_base_eff*/, list /*l_rhs_base_kind*/, bool /*declaration_p*/, list /*l_in*/, pv_results */*pv_res*/, pv_context */*ctxt*/);
extern void assignment_to_post_pv(expression /*lhs*/, bool /*may_lhs_p*/, expression /*rhs*/, bool /*declaration_p*/, list /*l_in*/, pv_results */*pv_res*/, pv_context */*ctxt*/);
extern bool simple_pointer_values(const string /*module_name*/);
extern bool initial_simple_pointer_values(const string /*module_name*/);
extern bool program_simple_pointer_values(const string /*prog_name*/);
/* pointer_values_operators.c */
extern list make_simple_pv_from_simple_effects(effect /*lhs_eff*/, effect /*rhs_eff*/, cell_interpretation /*ci*/, list /*l_in*/);
extern list kill_pointer_values(list /*l_in*/, list /*l_kill*/, pv_context */*ctxt*/);
extern list kill_pointer_value(effect /*eff_kill*/, list /*l_in*/, pv_context */*ctxt*/);
extern cell_relation simple_pv_translate(cell_relation /*pv_in*/, bool /*in_first_p*/, cell_relation /*pv_old*/);
extern list effect_find_equivalent_pointer_values(effect /*eff*/, list /*l_in*/, cell_relation */*exact_aliased_pv*/, list */*l_in_remnants*/);
extern list effect_find_aliased_paths_with_pointer_values(effect /*eff*/, list /*l_pv*/, pv_context */*ctxt*/);
extern void pointer_values_remove_var(entity /*e*/, bool /*may_p*/, list /*l_in*/, pv_results */*pv_res*/, pv_context */*ctxt*/);
extern cell_relation simple_pv_composition_with_transformer(cell_relation /*pv*/, transformer /*t*/);
extern list pvs_composition_with_transformer(list /*l_pv*/, transformer /*t*/, pv_context */*ctxt*/);
extern list cell_relation_to_list(cell_relation /*cr*/);
extern list cell_relation_to_may_list(cell_relation /*cr*/);
extern list simple_pv_must_union(cell_relation /*pv1*/, cell_relation /*pv2*/);
extern list simple_pv_may_union(cell_relation /*pv1*/, cell_relation /*pv2*/);
extern bool pvs_union_combinable_p(cell_relation /*pv1*/, cell_relation /*pv2*/);
extern list simple_pvs_must_union(list /*l_pv1*/, list /*l_pv2*/);
extern list simple_pvs_may_union(list /*l_pv1*/, list /*l_pv2*/);
extern bool simple_pvs_syntactically_equal_p(list /*l_pv1*/, list /*l_pv2*/);
/* pointer_values_intrinsics.c */
extern void intrinsic_to_post_pv(entity /*func*/, list /*func_args*/, list /*l_in*/, pv_results */*pv_res*/, pv_context */*ctxt*/);
/* prettyprint.c */
extern text text_pv(entity /*module*/, int /*margin*/, statement /*s*/);
extern bool generic_print_code_pv(char */*module_name*/, pv_context */*ctxt*/);
extern bool print_code_simple_pointer_values(char */*module_name*/);
extern void generic_print_code_gen_kill_pv(char */*module_name*/);
extern bool print_code_simple_gen_kill_pointer_values(char */*module_name*/);
#endif /*  pointer_values_header_included */
