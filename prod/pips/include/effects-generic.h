/* Warning! Do not modify this file that is automatically generated! */
/* Modify src/Libs/effects-generic/effects-generic-local.h instead, to add your own modifications. */

/* header file built by cproto */

#ifndef  effects_generic_header_included
#define  effects_generic_header_included
/*

  $Id: effects-generic-local.h 23065 2016-03-02 09:05:50Z coelho $

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
#include "effects.h"



/* some string constants for prettyprints...
 */
#define ACTION_UNDEFINED 	string_undefined
#define ACTION_READ 		"R"
#define ACTION_WRITE 		"W"
#define ACTION_IN    		"IN"
#define ACTION_OUT		"OUT"
#define ACTION_COPYIN		"COPYIN"
#define ACTION_COPYOUT		"COPYOUT"
#define ACTION_PRIVATE		"PRIVATE"
#define ACTION_LIVE_IN		"ALIVE (IN)"
#define ACTION_LIVE_OUT		"ALIVE (OUT)"

/* for debug
*/
// functions that can be pointed by effect_consistent_p_func:
// effect_consistent_p
// region_consistent_p
#define pips_debug_effect(level, message, eff) \
  ifdebug(level) { pips_debug(level, "%s\n", message); \
  (*effect_consistent_p_func)(eff); \
  (*effect_prettyprint_func)(eff);}

#define pips_debug_effects(level, message, l_eff) \
  ifdebug(level) { pips_debug(level, "%s\n", message); \
  generic_print_effects(l_eff);}

/* prettyprint function types:
 */
#include "text.h" /* hum... */
typedef text (*generic_text_function)(list /* of effect */);
typedef void (*generic_prettyprint_function)(list /* of effect */);
typedef void (*generic_attachment_function)(text);

/* for db_* functions
 */
#define DB_GET_SE(name, NAME)                                     \
  static statement_effects db_get_##name(const char *module_name) \
  {                                                               \
    return (statement_effects)                                    \
      db_get_memory_resource(DBR_##NAME, module_name, true);      \
  }

#define DB_GET_LS(name, NAME)                                           \
  static list db_get_##name(const char *module_name)                    \
  {                                                                     \
    return effects_to_list(                                             \
      (effects) db_get_memory_resource(DBR_##NAME, module_name, true)); \
  }

#define DB_GET_EE(name, NAME)                                     \
  static entity_effects db_get_##name(const char *module_name)    \
  {                                                               \
    return (entity_effects)                                       \
      db_get_memory_resource(DBR_##NAME, module_name, true);      \
  }

#define DB_PUT_SE(name, NAME)                                           \
  static void db_put_##name(                                            \
    const char *module_name, statement_effects se)                      \
  {                                                                     \
    DB_PUT_MEMORY_RESOURCE(DBR_##NAME, module_name, (void*) se);        \
  }

#define DB_PUT_LS(name, NAME)                                           \
  static void db_put_##name(const char *module_name, list l)            \
  {                                                                     \
    DB_PUT_MEMORY_RESOURCE(DBR_##NAME, module_name,                     \
                           (void*) list_to_effects(l));                 \
  }

#define DB_PUT_EE(name, NAME)                                           \
  static void db_put_##name(                                            \
    const char *module_name, entity_effects ee)                         \
  {                                                                     \
    DB_PUT_MEMORY_RESOURCE(DBR_##NAME, module_name, (void*) ee);        \
  }

#define DB_NOPUT_SE(name)                                               \
  static void db_put_##name(_UNUSED_ const char *m, statement_effects se) \
  {                                                                     \
    free_statement_effects(se);                                         \
  }

#define DB_NOPUT_LS(name)                                   \
  static void db_put_##name(_UNUSED_ const char *m, list l) \
  {                                                         \
    gen_full_free_list(l);                                  \
  }

#define DB_NOPUT_EE(name)                                              \
  static void db_put_##name(_UNUSED_ const char *m, entity_effects ee) \
  {                                                                    \
    free_entity_effects(se);                                           \
  }

#define DB_GETPUT_SE(name, NAME) DB_GET_SE(name, NAME) DB_PUT_SE(name, NAME)
#define DB_GETNOPUT_SE(name, NAME) DB_GET_SE(name, NAME) DB_NOPUT_SE(name)
#define DB_GETPUT_LS(name, NAME) DB_GET_LS(name, NAME) DB_PUT_LS(name, NAME)
#define DB_GETNOPUT_LS(name, NAME) DB_GET_LS(name, NAME) DB_NOPUT_LS(name)
#define DB_GETPUT_EE(name, NAME) DB_GET_EE(name, NAME) DB_PUT_EE(name, NAME)
#define DB_GETNOPUT_EE(name, NAME) DB_GET_EE(name, NAME) DB_NOPUT_EE(name)

typedef enum { with_no_pointer_info, with_points_to, with_pointer_values }
  pointer_info_val;

typedef enum { simple, convex } effects_representation_val;

/* end of effects-generic-local.h
 */
/* proper_effects_engine.c */
extern void set_contracted_proper_effects(bool /*b*/);
extern void proper_effects_error_handler(void);
extern list generic_proper_effects_of_range(range /*r*/);
extern list generic_proper_effects_of_derived_reference(reference /*ref*/, bool /*write_p*/);
extern list generic_intermediary_proper_effects_of_reference(reference /*ref*/);
extern list generic_p_proper_effect_of_reference(reference /*ref*/, effect */*pme*/, bool /*write_p*/, bool /*allow_partials_on_pme*/);
extern list generic_proper_effects_of_reference(reference /*ref*/, bool /*written_p*/);
extern list generic_proper_effects_of_read_reference(reference /*ref*/);
extern list generic_proper_effects_of_written_reference(reference /*ref*/);
extern list generic_proper_effects_of_complex_address_assign_dereferencing_op(expression /*lhs*/, expression /*rhs*/, list */*l_pme*/, bool /*write_p*/);
extern list generic_proper_effects_of_complex_address_address_of_dereferencing_op(expression /*e1*/, list */*l_pme*/, bool /*write_p*/);
extern list generic_proper_effects_of_complex_address_cast_dereferencing_op(cast /*dc*/, expression /*deref_exp*/, list */*l_pme*/, bool /*write_p*/);
extern list generic_proper_effects_of_complex_address_conditional_dereferencing_op(expression /*cond*/, expression /*e1*/, expression /*e2*/, list */*l_pme*/, bool /*write_p*/);
extern list generic_proper_effects_of_complex_address_dereferencing_cast_op(list /*args*/, list */*l_pme*/, bool /*write_p*/);
extern list new_generic_proper_effects_of_complex_address_conditional_op(list /*args*/, list */*l_pme*/, bool /*write_p*/);
extern list old_generic_proper_effects_of_complex_address_conditional_op(list /*args*/, list */*l_pme*/, bool /*write_p*/);
extern list generic_proper_effects_of_complex_address_assign_op(list /*args*/, list */*l_pme*/, bool /*write_p*/);
extern list generic_proper_effects_of_complex_address_update_op(list /*args*/, list */*l_pme*/, bool /*write_p*/);
extern list generic_proper_effects_of_complex_address_expression(expression /*add_exp*/, list */*l_pme*/, int /*write_p*/);
extern list generic_proper_effects_of_any_lhs(expression /*lhs*/);
extern list generic_proper_effects_of_complex_memory_access_expression(expression /*addexp*/, list */*l_addexp_pme*/, list */*lpme*/, int /*write_p*/);
extern list generic_proper_effects_of_address_expression(expression /*addexp*/, int /*write_p*/);
extern list generic_proper_effects_of_subscript(subscript /*s*/);
extern list generic_proper_effects_of_application(application /*a*/);
extern list generic_proper_effects_of_expression(expression /*e*/);
extern list generic_proper_effects_of_expressions(list /*exprs*/);
extern bool check_sdfi_effects_p(entity /*func*/, list /*func_sdfi*/);
extern list generic_proper_effects_of_c_function_call_argument(expression /*arg*/);
extern list generic_r_proper_effects_of_call(call /*c*/);
extern list type_to_effects(type /*t*/);
extern list recursive_type_to_effects(type /*t*/, set /*ts*/);
extern effect make_declaration_effect(entity /*e*/, bool /*written_p*/);
extern void proper_effects_of_module_statement(statement /*module_stat*/);
extern bool proper_effects_engine(const char */*module_name*/);
extern void expression_proper_effects_engine(const char */*module_name*/, statement /*current*/);
/* rw_effects_engine.c */
extern void set_contracted_rw_effects(bool /*b*/);
extern bool summary_rw_effects_engine(const char */*module_name*/);
extern void rw_effects_of_module_statement(statement /*module_stat*/);
extern bool rw_effects_engine(const char */*module_name*/);
/* in_effects_engine.c */
extern bool summary_in_effects_engine(const char */*module_name*/);
extern bool in_effects_engine(const char */*module_name*/, effects_representation_val /*representation*/);
/* out_effects_engine.c */
extern void reset_out_summary_effects_list(void);
extern void update_out_summary_effects_list(list /*l_out*/);
extern list get_out_summary_effects_list(void);
extern bool summary_out_effects_engine(const char */*module_name*/);
extern bool out_effects_engine(const char */*module_name*/, effects_representation_val /*representation*/);
/* mappings.c */
extern bool proper_references_undefined_p(void);
extern void reset_proper_references(void);
extern void error_reset_proper_references(void);
extern void set_proper_references(statement_effects /*o*/);
extern statement_effects get_proper_references(void);
extern void init_proper_references(void);
extern void close_proper_references(void);
extern void store_proper_references(statement /*k*/, effects /*v*/);
extern void update_proper_references(statement /*k*/, effects /*v*/);
extern effects load_proper_references(statement /*k*/);
extern effects delete_proper_references(statement /*k*/);
extern bool bound_proper_references_p(statement /*k*/);
extern void store_or_update_proper_references(statement /*k*/, effects /*v*/);
extern bool cumulated_references_undefined_p(void);
extern void reset_cumulated_references(void);
extern void error_reset_cumulated_references(void);
extern void set_cumulated_references(statement_effects /*o*/);
extern statement_effects get_cumulated_references(void);
extern void init_cumulated_references(void);
extern void close_cumulated_references(void);
extern void store_cumulated_references(statement /*k*/, effects /*v*/);
extern void update_cumulated_references(statement /*k*/, effects /*v*/);
extern effects load_cumulated_references(statement /*k*/);
extern effects delete_cumulated_references(statement /*k*/);
extern bool bound_cumulated_references_p(statement /*k*/);
extern void store_or_update_cumulated_references(statement /*k*/, effects /*v*/);
extern bool proper_rw_pointer_effects_undefined_p(void);
extern void reset_proper_rw_pointer_effects(void);
extern void error_reset_proper_rw_pointer_effects(void);
extern void set_proper_rw_pointer_effects(statement_effects /*o*/);
extern statement_effects get_proper_rw_pointer_effects(void);
extern void init_proper_rw_pointer_effects(void);
extern void close_proper_rw_pointer_effects(void);
extern void store_proper_rw_pointer_effects(statement /*k*/, effects /*v*/);
extern void update_proper_rw_pointer_effects(statement /*k*/, effects /*v*/);
extern effects load_proper_rw_pointer_effects(statement /*k*/);
extern effects delete_proper_rw_pointer_effects(statement /*k*/);
extern bool bound_proper_rw_pointer_effects_p(statement /*k*/);
extern void store_or_update_proper_rw_pointer_effects(statement /*k*/, effects /*v*/);
extern bool proper_rw_effects_undefined_p(void);
extern void reset_proper_rw_effects(void);
extern void error_reset_proper_rw_effects(void);
extern void set_proper_rw_effects(statement_effects /*o*/);
extern statement_effects get_proper_rw_effects(void);
extern void init_proper_rw_effects(void);
extern void close_proper_rw_effects(void);
extern void store_proper_rw_effects(statement /*k*/, effects /*v*/);
extern void update_proper_rw_effects(statement /*k*/, effects /*v*/);
extern effects load_proper_rw_effects(statement /*k*/);
extern effects delete_proper_rw_effects(statement /*k*/);
extern bool bound_proper_rw_effects_p(statement /*k*/);
extern void store_or_update_proper_rw_effects(statement /*k*/, effects /*v*/);
extern bool rw_pointer_effects_undefined_p(void);
extern void reset_rw_pointer_effects(void);
extern void error_reset_rw_pointer_effects(void);
extern void set_rw_pointer_effects(statement_effects /*o*/);
extern statement_effects get_rw_pointer_effects(void);
extern void init_rw_pointer_effects(void);
extern void close_rw_pointer_effects(void);
extern void store_rw_pointer_effects(statement /*k*/, effects /*v*/);
extern void update_rw_pointer_effects(statement /*k*/, effects /*v*/);
extern effects load_rw_pointer_effects(statement /*k*/);
extern effects delete_rw_pointer_effects(statement /*k*/);
extern bool bound_rw_pointer_effects_p(statement /*k*/);
extern void store_or_update_rw_pointer_effects(statement /*k*/, effects /*v*/);
extern bool invariant_rw_pointer_effects_undefined_p(void);
extern void reset_invariant_rw_pointer_effects(void);
extern void error_reset_invariant_rw_pointer_effects(void);
extern void set_invariant_rw_pointer_effects(statement_effects /*o*/);
extern statement_effects get_invariant_rw_pointer_effects(void);
extern void init_invariant_rw_pointer_effects(void);
extern void close_invariant_rw_pointer_effects(void);
extern void store_invariant_rw_pointer_effects(statement /*k*/, effects /*v*/);
extern void update_invariant_rw_pointer_effects(statement /*k*/, effects /*v*/);
extern effects load_invariant_rw_pointer_effects(statement /*k*/);
extern effects delete_invariant_rw_pointer_effects(statement /*k*/);
extern bool bound_invariant_rw_pointer_effects_p(statement /*k*/);
extern void store_or_update_invariant_rw_pointer_effects(statement /*k*/, effects /*v*/);
extern bool rw_effects_undefined_p(void);
extern void reset_rw_effects(void);
extern void error_reset_rw_effects(void);
extern void set_rw_effects(statement_effects /*o*/);
extern statement_effects get_rw_effects(void);
extern void init_rw_effects(void);
extern void close_rw_effects(void);
extern void store_rw_effects(statement /*k*/, effects /*v*/);
extern void update_rw_effects(statement /*k*/, effects /*v*/);
extern effects load_rw_effects(statement /*k*/);
extern effects delete_rw_effects(statement /*k*/);
extern bool bound_rw_effects_p(statement /*k*/);
extern void store_or_update_rw_effects(statement /*k*/, effects /*v*/);
extern bool invariant_rw_effects_undefined_p(void);
extern void reset_invariant_rw_effects(void);
extern void error_reset_invariant_rw_effects(void);
extern void set_invariant_rw_effects(statement_effects /*o*/);
extern statement_effects get_invariant_rw_effects(void);
extern void init_invariant_rw_effects(void);
extern void close_invariant_rw_effects(void);
extern void store_invariant_rw_effects(statement /*k*/, effects /*v*/);
extern void update_invariant_rw_effects(statement /*k*/, effects /*v*/);
extern effects load_invariant_rw_effects(statement /*k*/);
extern effects delete_invariant_rw_effects(statement /*k*/);
extern bool bound_invariant_rw_effects_p(statement /*k*/);
extern void store_or_update_invariant_rw_effects(statement /*k*/, effects /*v*/);
extern bool cumulated_rw_effects_undefined_p(void);
extern void reset_cumulated_rw_effects(void);
extern void error_reset_cumulated_rw_effects(void);
extern void set_cumulated_rw_effects(statement_effects /*o*/);
extern statement_effects get_cumulated_rw_effects(void);
extern void init_cumulated_rw_effects(void);
extern void close_cumulated_rw_effects(void);
extern void store_cumulated_rw_effects(statement /*k*/, effects /*v*/);
extern void update_cumulated_rw_effects(statement /*k*/, effects /*v*/);
extern effects load_cumulated_rw_effects(statement /*k*/);
extern effects delete_cumulated_rw_effects(statement /*k*/);
extern bool bound_cumulated_rw_effects_p(statement /*k*/);
extern void store_or_update_cumulated_rw_effects(statement /*k*/, effects /*v*/);
extern bool expr_prw_effects_undefined_p(void);
extern void reset_expr_prw_effects(void);
extern void error_reset_expr_prw_effects(void);
extern void set_expr_prw_effects(persistant_expression_to_effects /*o*/);
extern persistant_expression_to_effects get_expr_prw_effects(void);
extern void init_expr_prw_effects(void);
extern void close_expr_prw_effects(void);
extern void store_expr_prw_effects(expression /*k*/, effects /*v*/);
extern void update_expr_prw_effects(expression /*k*/, effects /*v*/);
extern effects load_expr_prw_effects(expression /*k*/);
extern effects delete_expr_prw_effects(expression /*k*/);
extern bool bound_expr_prw_effects_p(expression /*k*/);
extern void store_or_update_expr_prw_effects(expression /*k*/, effects /*v*/);
extern bool in_effects_undefined_p(void);
extern void reset_in_effects(void);
extern void error_reset_in_effects(void);
extern void set_in_effects(statement_effects /*o*/);
extern statement_effects get_in_effects(void);
extern void init_in_effects(void);
extern void close_in_effects(void);
extern void store_in_effects(statement /*k*/, effects /*v*/);
extern void update_in_effects(statement /*k*/, effects /*v*/);
extern effects load_in_effects(statement /*k*/);
extern effects delete_in_effects(statement /*k*/);
extern bool bound_in_effects_p(statement /*k*/);
extern void store_or_update_in_effects(statement /*k*/, effects /*v*/);
extern bool cumulated_in_effects_undefined_p(void);
extern void reset_cumulated_in_effects(void);
extern void error_reset_cumulated_in_effects(void);
extern void set_cumulated_in_effects(statement_effects /*o*/);
extern statement_effects get_cumulated_in_effects(void);
extern void init_cumulated_in_effects(void);
extern void close_cumulated_in_effects(void);
extern void store_cumulated_in_effects(statement /*k*/, effects /*v*/);
extern void update_cumulated_in_effects(statement /*k*/, effects /*v*/);
extern effects load_cumulated_in_effects(statement /*k*/);
extern effects delete_cumulated_in_effects(statement /*k*/);
extern bool bound_cumulated_in_effects_p(statement /*k*/);
extern void store_or_update_cumulated_in_effects(statement /*k*/, effects /*v*/);
extern bool invariant_in_effects_undefined_p(void);
extern void reset_invariant_in_effects(void);
extern void error_reset_invariant_in_effects(void);
extern void set_invariant_in_effects(statement_effects /*o*/);
extern statement_effects get_invariant_in_effects(void);
extern void init_invariant_in_effects(void);
extern void close_invariant_in_effects(void);
extern void store_invariant_in_effects(statement /*k*/, effects /*v*/);
extern void update_invariant_in_effects(statement /*k*/, effects /*v*/);
extern effects load_invariant_in_effects(statement /*k*/);
extern effects delete_invariant_in_effects(statement /*k*/);
extern bool bound_invariant_in_effects_p(statement /*k*/);
extern void store_or_update_invariant_in_effects(statement /*k*/, effects /*v*/);
extern bool out_effects_undefined_p(void);
extern void reset_out_effects(void);
extern void error_reset_out_effects(void);
extern void set_out_effects(statement_effects /*o*/);
extern statement_effects get_out_effects(void);
extern void init_out_effects(void);
extern void close_out_effects(void);
extern void store_out_effects(statement /*k*/, effects /*v*/);
extern void update_out_effects(statement /*k*/, effects /*v*/);
extern effects load_out_effects(statement /*k*/);
extern effects delete_out_effects(statement /*k*/);
extern bool bound_out_effects_p(statement /*k*/);
extern void store_or_update_out_effects(statement /*k*/, effects /*v*/);
extern bool live_in_paths_undefined_p(void);
extern void reset_live_in_paths(void);
extern void error_reset_live_in_paths(void);
extern void set_live_in_paths(statement_effects /*o*/);
extern statement_effects get_live_in_paths(void);
extern void init_live_in_paths(void);
extern void close_live_in_paths(void);
extern void store_live_in_paths(statement /*k*/, effects /*v*/);
extern void update_live_in_paths(statement /*k*/, effects /*v*/);
extern effects load_live_in_paths(statement /*k*/);
extern effects delete_live_in_paths(statement /*k*/);
extern bool bound_live_in_paths_p(statement /*k*/);
extern void store_or_update_live_in_paths(statement /*k*/, effects /*v*/);
extern bool live_out_paths_undefined_p(void);
extern void reset_live_out_paths(void);
extern void error_reset_live_out_paths(void);
extern void set_live_out_paths(statement_effects /*o*/);
extern statement_effects get_live_out_paths(void);
extern void init_live_out_paths(void);
extern void close_live_out_paths(void);
extern void store_live_out_paths(statement /*k*/, effects /*v*/);
extern void update_live_out_paths(statement /*k*/, effects /*v*/);
extern effects load_live_out_paths(statement /*k*/);
extern effects delete_live_out_paths(statement /*k*/);
extern bool bound_live_out_paths_p(statement /*k*/);
extern void store_or_update_live_out_paths(statement /*k*/, effects /*v*/);
extern bool useful_variables_effects_undefined_p(void);
extern void reset_useful_variables_effects(void);
extern void error_reset_useful_variables_effects(void);
extern void set_useful_variables_effects(entity_effects /*o*/);
extern entity_effects get_useful_variables_effects(void);
extern void init_useful_variables_effects(void);
extern void close_useful_variables_effects(void);
extern void store_useful_variables_effects(entity /*k*/, effects /*v*/);
extern void update_useful_variables_effects(entity /*k*/, effects /*v*/);
extern effects load_useful_variables_effects(entity /*k*/);
extern effects delete_useful_variables_effects(entity /*k*/);
extern bool bound_useful_variables_effects_p(entity /*k*/);
extern void store_or_update_useful_variables_effects(entity /*k*/, effects /*v*/);
extern list load_proper_rw_pointer_effects_list(statement /*s*/);
extern void store_proper_rw_pointer_effects_list(statement /*s*/, list /*l_eff*/);
extern void update_proper_rw_pointer_effects_list(statement /*s*/, list /*l_eff*/);
extern list load_proper_rw_effects_list(statement /*s*/);
extern void store_proper_rw_effects_list(statement /*s*/, list /*l_eff*/);
extern void update_proper_rw_effects_list(statement /*s*/, list /*l_eff*/);
extern list load_rw_pointer_effects_list(statement /*s*/);
extern void store_rw_pointer_effects_list(statement /*s*/, list /*l_eff*/);
extern void update_rw_pointer_effects_list(statement /*s*/, list /*l_eff*/);
extern list load_rw_effects_list(statement /*s*/);
extern void store_rw_effects_list(statement /*s*/, list /*l_eff*/);
extern void update_rw_effects_list(statement /*s*/, list /*l_eff*/);
extern list load_invariant_rw_pointer_effects_list(statement /*s*/);
extern void store_invariant_rw_pointer_effects_list(statement /*s*/, list /*l_eff*/);
extern void update_invariant_rw_pointer_effects_list(statement /*s*/, list /*l_eff*/);
extern list load_invariant_rw_effects_list(statement /*s*/);
extern void store_invariant_rw_effects_list(statement /*s*/, list /*l_eff*/);
extern void update_invariant_rw_effects_list(statement /*s*/, list /*l_eff*/);
extern list load_cumulated_rw_effects_list(statement /*s*/);
extern void store_cumulated_rw_effects_list(statement /*s*/, list /*l_eff*/);
extern void update_cumulated_rw_effects_list(statement /*s*/, list /*l_eff*/);
extern list load_in_effects_list(statement /*s*/);
extern void store_in_effects_list(statement /*s*/, list /*l_eff*/);
extern void update_in_effects_list(statement /*s*/, list /*l_eff*/);
extern list load_cumulated_in_effects_list(statement /*s*/);
extern void store_cumulated_in_effects_list(statement /*s*/, list /*l_eff*/);
extern void update_cummulated_in_effects_list(statement /*s*/, list /*l_eff*/);
extern list load_invariant_in_effects_list(statement /*s*/);
extern void store_invariant_in_effects_list(statement /*s*/, list /*l_eff*/);
extern void update_invariant_in_effects_list(statement /*s*/, list /*l_eff*/);
extern list load_out_effects_list(statement /*s*/);
extern void store_out_effects_list(statement /*s*/, list /*l_eff*/);
extern void update_out_effects_list(statement /*s*/, list /*l_eff*/);
extern list load_live_in_paths_list(statement /*s*/);
extern void store_live_in_paths_list(statement /*s*/, list /*l_paths*/);
extern void update_live_in_paths_list(statement /*s*/, list /*l_paths*/);
extern list load_live_out_paths_list(statement /*s*/);
extern void store_live_out_paths_list(statement /*s*/, list /*l_paths*/);
extern void update_live_out_paths_list(statement /*s*/, list /*l_paths*/);
extern list load_statement_local_regions(statement /*s*/);
extern void store_statement_local_regions(statement /*s*/, list /*t*/);
extern void update_statement_local_regions(statement /*s*/, list /*t*/);
extern list load_statement_inv_regions(statement /*s*/);
extern void store_statement_inv_regions(statement /*s*/, list /*t*/);
extern void update_statement_inv_regions(statement /*s*/, list /*t*/);
extern list load_statement_proper_regions(statement /*s*/);
extern void store_statement_proper_regions(statement /*s*/, list /*t*/);
extern list load_statement_in_regions(statement /*s*/);
extern void store_statement_in_regions(statement /*s*/, list /*t*/);
extern list load_statement_inv_in_regions(statement /*s*/);
extern void store_statement_inv_in_regions(statement /*s*/, list /*t*/);
extern void update_statement_inv_in_regions(statement /*s*/, list /*t*/);
extern list load_statement_cumulated_in_regions(statement /*s*/);
extern void store_statement_cumulated_in_regions(statement /*s*/, list /*t*/);
extern list load_statement_out_regions(statement /*s*/);
extern void store_statement_out_regions(statement /*s*/, list /*t*/);
/* unary_operators.c */
extern void effects_map(list /*l_eff*/, void (* /*apply*/)(effect));
extern list effects_to_effects_map(list /*l_eff*/, effect (* /*pure_apply*/)(effect));
extern void effects_filter_map(list /*l_eff*/, bool (* /*filter*/)(effect), void (* /*apply*/)(effect));
extern list effects_to_effects_filter_map(list /*l_eff*/, bool (* /*filter*/)(effect), effect (* /*pure_apply*/)(effect));
extern list effects_add_effect(list /*l_eff*/, effect /*eff*/);
extern list effects_read_effects(list /*l_eff*/);
extern list effects_store_effects(list /*l_eff*/);
extern list effects_write_effects(list /*l_eff*/);
extern bool effects_write_at_least_once_p(list /*l_eff*/);
extern list effects_read_effects_dup(list /*l_eff*/);
extern list effects_write_effects_dup(list /*l_eff*/);
extern effect effect_nop(effect /*eff*/);
extern list effects_nop(list /*l_eff*/);
extern void effect_to_may_effect(effect /*eff*/);
extern void effects_to_may_effects(list /*l_eff*/);
extern void effect_to_must_effect(effect /*eff*/);
extern void effects_to_must_effects(list /*l_eff*/);
extern void effect_to_write_effect(effect /*eff*/);
extern void effects_to_write_effects(list /*l_eff*/);
extern void effect_to_read_effect(effect /*eff*/);
extern void effects_to_read_effects(list /*l_eff*/);
extern void array_effects_to_may_effects(list /*l_eff*/);
extern list effects_dup_without_variables(list /*l_eff*/, list /*l_var*/);
extern list effects_dup(list /*l_eff*/);
extern void effect_free(effect /*eff*/);
extern void effects_free(list /*l_eff*/);
extern list effect_to_nil_list(effect /*eff*/);
extern list effect_to_nil_list_and_free(effect /*eff*/);
extern list effects_to_nil_list(effect /*eff1*/, effect /*eff2*/);
extern list effect_to_list(effect /*eff*/);
extern list effect_to_may_effect_list(effect /*eff*/);
extern list effects_to_written_scalar_entities(list /*l_eff*/);
extern list effects_undefined_composition_with_transformer(list /*l_eff*/, transformer /*trans*/);
extern list effects_composition_with_transformer_nop(list /*l_eff*/, transformer /*trans*/);
extern list effects_undefined_composition_with_preconditions(list /*l_eff*/, transformer /*trans*/);
extern list effects_composition_with_preconditions_nop(list /*l_eff*/, transformer /*trans*/, bool /*b*/);
extern descriptor loop_undefined_descriptor_make(loop /*l*/);
extern list effects_undefined_union_over_range(list /*l_eff*/, entity /*index*/, range /*r*/, descriptor /*d*/);
extern list effects_union_over_range_nop(list /*l_eff*/, entity /*index*/, range /*r*/, descriptor /*d*/);
extern list effects_undefined_descriptors_variable_change(list /*l_eff*/, entity /*orig_ent*/, entity /*new_ent*/);
extern list effects_descriptors_variable_change_nop(list /*l_eff*/, entity /*orig_ent*/, entity /*new_ent*/);
extern descriptor effects_undefined_vector_to_descriptor(Pvecteur /*v*/);
extern list effects_undefined_loop_normalize(list /*l_eff*/, entity /*index*/, range /*r*/, entity */*new_index*/, descriptor /*range_descriptor*/, bool /*descriptor_update_p*/);
extern list effects_loop_normalize_nop(list /*l_eff*/, entity /*index*/, range /*r*/, entity */*new_index*/, descriptor /*range_descriptor*/, bool /*descriptor_update_p*/);
extern list db_get_empty_list(string /*name*/);
extern void effect_add_dereferencing_dimension(effect /*eff*/);
extern void effect_add_field_dimension(effect /*eff*/, entity /*field*/);
extern list filter_effects_with_declaration(list /*l_eff*/, entity /*decl*/);
extern list effect_intermediary_pointer_paths_effect(effect /*eff*/);
/* binary_operators.c */
extern list list_of_effects_generic_binary_op(list /*l1*/, list /*l2*/, bool (* /*r1_r2_combinable_p*/)(effect, effect), list (* /*r1_r2_generic_binary_op*/)(effect, effect, bool, bool, bool *, bool *, list (*)(effect, effect)), list (* /*r1_r2_concrete_binary_op*/)(effect, effect), list (* /*r1_unary_op*/)(effect), list (* /*r2_unary_op*/)(effect));
extern list list_of_effects_generic_union_op(list /*l1*/, list /*l2*/, bool (* /*r1_r2_combinable_p*/)(effect, effect), list (* /*r1_r2_concrete_union_op*/)(effect, effect), list (* /*r_unary_op*/)(effect));
extern list list_of_effects_generic_intersection_op(list /*l1*/, list /*l2*/, bool (* /*r1_r2_combinable_p*/)(effect, effect), list (* /*r1_r2_concrete_intersection_op*/)(effect, effect));
extern list list_of_effects_generic_cells_intersection_op(list /*l1*/, list /*l2*/, bool (* /*r1_r2_combinable_p*/)(effect, effect), list (* /*r1_r2_concrete_cells_intersection_op*/)(effect, effect));
extern list list_of_effects_generic_sup_difference_op(list /*l1*/, list /*l2*/, bool (* /*r1_r2_combinable_p*/)(effect, effect), list (* /*r1_r2_concrete_sup_difference_op*/)(effect, effect));
extern list list_of_effects_generic_inf_difference_op(list /*l1*/, list /*l2*/, bool (* /*r1_r2_combinable_p*/)(effect, effect), list (* /*r1_r2_concrete_inf_difference_op*/)(effect, effect));
extern list list_of_effects_generic_cells_inf_difference_op(list /*l1*/, list /*l2*/, bool (* /*r1_r2_combinable_p*/)(effect, effect), list (* /*r1_r2_concrete_cells_inf_difference_op*/)(effect, effect));
extern list proper_to_summary_effects(list /*l_effects*/);
extern list proper_effects_contract(list /*l_effects*/);
extern list proper_effects_combine(list /*l_eff*/, bool /*scalars_only_p*/);
extern bool effects_combinable_p(effect /*eff1*/, effect /*eff2*/);
extern bool cells_combinable_p(cell /*c1*/, cell /*c2*/);
extern bool effects_scalars_and_same_action_p(effect /*eff1*/, effect /*eff2*/);
extern bool effects_same_action_p(effect /*eff1*/, effect /*eff2*/);
extern bool effects_same_variable_p(effect /*eff1*/, effect /*eff2*/);
extern bool r_r_combinable_p(effect /*eff1*/, effect /*eff2*/);
extern bool w_w_combinable_p(effect /*eff1*/, effect /*eff2*/);
extern bool r_w_combinable_p(effect /*eff1*/, effect /*eff2*/);
extern bool w_r_combinable_p(effect /*eff1*/, effect /*eff2*/);
extern list effects_undefined_binary_operator(list /*l1*/, list /*l2*/, bool (* /*effects_combinable_p*/)(effect, effect));
extern list effects_entities_intersection(list /*l1*/, list /*l2*/, bool (* /*intersection_combinable_p*/)(effect, effect));
extern list effects_entities_inf_difference(list /*l1*/, list /*l2*/, bool (* /*difference_combinable_p*/)(effect, effect));
/* utils.c */
extern void make_effects_private_current_stmt_stack(void);
extern void free_effects_private_current_stmt_stack(void);
extern stack get_effects_private_current_stmt_stack(void);
extern void set_effects_private_current_stmt_stack(stack /*s*/);
extern void reset_effects_private_current_stmt_stack(void);
extern void effects_private_current_stmt_push(statement /*i*/);
extern bool effects_private_current_stmt_filter(statement /*i*/);
extern void effects_private_current_stmt_rewrite(statement /*i*/);
extern statement effects_private_current_stmt_replace(statement /*i*/);
extern statement effects_private_current_stmt_pop(void);
extern statement effects_private_current_stmt_head(void);
extern statement effects_private_current_stmt_nth(int /*n*/);
extern bool effects_private_current_stmt_empty_p(void);
extern int effects_private_current_stmt_size(void);
extern void error_reset_effects_private_current_stmt_stack(void);
extern void make_effects_private_current_context_stack(void);
extern void free_effects_private_current_context_stack(void);
extern stack get_effects_private_current_context_stack(void);
extern void set_effects_private_current_context_stack(stack /*s*/);
extern void reset_effects_private_current_context_stack(void);
extern void effects_private_current_context_push(transformer /*i*/);
extern bool effects_private_current_context_filter(transformer /*i*/);
extern void effects_private_current_context_rewrite(transformer /*i*/);
extern transformer effects_private_current_context_replace(transformer /*i*/);
extern transformer effects_private_current_context_pop(void);
extern transformer effects_private_current_context_head(void);
extern transformer effects_private_current_context_nth(int /*n*/);
extern bool effects_private_current_context_empty_p(void);
extern int effects_private_current_context_size(void);
extern void error_reset_effects_private_current_context_stack(void);
extern bool effects_private_current_context_stack_initialized_p(void);
extern bool effects_private_current_stmt_stack_initialized_p(void);
extern bool normalizable_and_linear_loop_p(entity /*index*/, range /*l_range*/);
extern transformer transformer_remove_variable_and_dup(transformer /*orig_trans*/, entity /*ent*/);
extern void set_descriptor_range_p(bool /*b*/);
extern bool get_descriptor_range_p(void);
extern descriptor descriptor_inequality_add(descriptor /*d*/, Pvecteur /*v*/);
extern transformer descriptor_to_context(descriptor /*d*/);
extern void descriptor_variable_rename(descriptor /*d*/, entity /*old_ent*/, entity /*new_ent*/);
extern descriptor descriptor_append(descriptor /*d1*/, descriptor /*d2*/);
extern transformer load_undefined_context(statement /*s*/);
extern transformer load_undefined_transformer(statement /*s*/);
extern bool empty_context_test_false(transformer /*context*/);
extern void effects_computation_no_init(const char */*module_name*/);
extern void effects_computation_no_reset(const char */*module_name*/);
extern string vect_debug_entity_name(entity /*e*/);
extern bool some_integer_scalar_read_or_write_effects_p(cons */*fx*/);
extern bool statement_io_effect_p(statement /*s*/);
extern bool statement_has_a_formal_argument_write_effect_p(statement /*s*/);
extern list make_effects_for_array_declarations(list /*refs*/);
extern list summary_effects_from_declaration(const char */*module_name*/);
extern void dump_cell(cell /*c*/);
extern void dump_effect(effect /*e*/);
extern void dump_effects(list /*le*/);
extern bool effects_reference_sharing_p(list /*el*/, bool /*persistant_p*/);
extern effect make_some_anywhere_effect(action /*act*/, entity /*anywhere_ent*/);
extern effect make_anywhere_effect(action /*act*/);
extern effect make_generic_anywhere_effect(action /*act*/, reference /*r*/);
extern effect make_typed_anywhere_effect(action /*act*/, type /*t*/);
extern effect make_anywhere_write_memory_effect(void);
extern effect make_anywhere_read_memory_effect(void);
extern list make_anywhere_read_write_memory_effects(void);
extern list clean_anywhere_effects(list /*l_eff*/);
extern effect make_null_pointer_value_effect(action /*act*/);
extern bool null_pointer_value_effect_p(effect /*eff*/);
extern effect make_undefined_pointer_value_effect(action /*act*/);
extern bool undefined_pointer_value_effect_p(effect /*eff*/);
extern list effect_to_effects_with_given_tag(effect /*eff*/, tag /*act*/);
extern list generic_effect_generate_all_accessible_paths_effects_with_level(effect /*eff*/, type /*eff_type*/, tag /*act*/, bool /*add_eff*/, int /*level*/, bool /*pointers_only*/);
extern list generic_effect_generate_all_accessible_paths_effects(effect /*eff*/, type /*eff_type*/, tag /*act*/);
extern bool r_effect_pointer_type_p(effect /*eff*/, list /*l_ind*/, type /*ct*/);
extern bool effect_pointer_type_p(effect /*eff*/);
extern type simple_effect_reference_type(reference /*ref*/);
extern bool regions_weakly_consistent_p(list /*rl*/);
extern bool region_weakly_consistent_p(effect /*r*/);
extern list statement_modified_pointers_effects_list(statement /*s*/);
extern bool abstract_effect_in_effect_list_p(action /*ea*/, type /*et*/, list /*el*/);
extern list generic_effects_store_update(list /*l_eff*/, statement /*s*/, bool /*backward_p*/);
extern list pointer_effects_to_constant_path_effects(list /*l_pointer_eff*/);
extern list effect_to_constant_path_effects_with_no_pointer_information(effect /*eff*/);
extern list effects_to_constant_path_effects_with_no_pointer_information(list /*el*/);
extern bool find_write_effect_on_entity(statement /*s*/, entity /*e*/);
/* methods.c */
extern void set_pointer_info_kind(pointer_info_val /*val*/);
extern pointer_info_val get_pointer_info_kind(void);
extern void set_constant_paths_p(bool /*b*/);
extern bool get_constant_paths_p(void);
extern bool (*effect_consistent_p_func)(effect);
extern void (*effects_computation_init_func)(const char *);
extern void (*effects_computation_reset_func)(const char *);
extern effect (*effect_dup_func)(effect eff);
extern void (*effect_free_func)(effect eff);
extern effect (*reference_to_effect_func)(reference, action, bool);
extern list (*effect_to_store_independent_effect_list_func)(effect, bool);
extern void (*effect_add_expression_dimension_func)(effect eff, expression exp);
extern void (*effect_change_ith_dimension_expression_func)(effect eff, expression exp, int i);
extern effect (*effect_union_op)(effect, effect);
extern list (*effects_union_op)(list, list, bool (*eff1_eff2_combinable_p)(effect, effect));
extern list (*effects_test_union_op)(list, list, bool (*eff1_eff2_combinable_p)(effect, effect));
extern list (*effects_intersection_op)(list, list, bool (*eff1_eff2_combinable_p)(effect, effect));
extern list (*effects_sup_difference_op)(list, list, bool (*eff1_eff2_combinable_p)(effect, effect));
extern list (*effects_inf_difference_op)(list, list, bool (*eff1_eff2_combinable_p)(effect, effect));
extern list (*effects_transformer_composition_op)(list, transformer);
extern list (*effects_transformer_inverse_composition_op)(list, transformer);
extern list (*effects_precondition_composition_op)(list, transformer, bool);
extern list (*eval_cell_with_points_to_func)(cell, descriptor, list, bool *, transformer);
extern list (*effect_to_constant_path_effects_func)(effect);
extern list (*effects_descriptors_variable_change_func)(list, entity, entity);
extern descriptor (*loop_descriptor_make_func)(loop);
extern void (*loop_range_in_effect_func)(loop, list *, list *, bool (*)(effect, effect), entity *, range);
extern list (*effects_loop_normalize_func)(list, entity, range, entity *, descriptor, bool);
extern list (*effects_union_over_range_op)(list, entity, range, descriptor);
extern descriptor (*vector_to_descriptor_func)(Pvecteur);
extern void (*effects_translation_init_func)(entity, list, bool);
extern void (*effects_translation_end_func)(void);
extern void (*effect_descriptor_interprocedural_translation_op)(effect);
extern list (*fortran_effects_backward_translation_op)(entity, list, list, transformer);
extern list (*fortran_effects_forward_translation_op)(entity, list, list, transformer);
extern list (*c_effects_on_formal_parameter_backward_translation_func)(list, expression, transformer);
extern list (*c_effects_on_actual_parameter_forward_translation_func)(entity, expression, entity, list, transformer);
extern list (*effects_local_to_global_translation_op)(list);
extern transformer (*load_context_func)(statement);
extern transformer (*load_transformer_func)(statement);
extern transformer (*load_completed_transformer_func)(statement);
extern bool (*empty_context_test)(transformer);
extern effect (*proper_to_summary_effect_func)(effect);
extern void (*effects_descriptor_normalize_func)(list);
extern statement_effects (*db_get_proper_rw_effects_func)(const char *);
extern void (*db_put_proper_rw_effects_func)(const char *, statement_effects);
extern statement_effects (*db_get_invariant_rw_effects_func)(const char *);
extern void (*db_put_invariant_rw_effects_func)(const char *, statement_effects);
extern statement_effects (*db_get_rw_effects_func)(const char *);
extern void (*db_put_rw_effects_func)(const char *, statement_effects);
extern list (*db_get_summary_rw_effects_func)(const char *);
extern void (*db_put_summary_rw_effects_func)(const char *, list);
extern statement_effects (*db_get_in_effects_func)(const char *);
extern void (*db_put_in_effects_func)(const char *, statement_effects);
extern statement_effects (*db_get_cumulated_in_effects_func)(const char *);
extern void (*db_put_cumulated_in_effects_func)(const char *, statement_effects);
extern statement_effects (*db_get_invariant_in_effects_func)(const char *);
extern void (*db_put_invariant_in_effects_func)(const char *, statement_effects);
extern list (*db_get_summary_in_effects_func)(const char *);
extern void (*db_put_summary_in_effects_func)(const char *, list);
extern list (*db_get_summary_out_effects_func)(const char *);
extern void (*db_put_summary_out_effects_func)(const char *, list);
extern statement_effects (*db_get_out_effects_func)(const char *);
extern void (*db_put_out_effects_func)(const char *, statement_effects);
extern statement_effects (*db_get_live_in_paths_func)(const char *);
extern void (*db_put_live_in_paths_func)(const char *, statement_effects);
extern statement_effects (*db_get_live_out_paths_func)(const char *);
extern void (*db_put_live_out_paths_func)(const char *, statement_effects);
extern list (*db_get_live_in_summary_paths_func)(const char *);
extern void (*db_put_live_in_summary_paths_func)(const char *, list);
extern list (*db_get_live_out_summary_paths_func)(const char *);
extern void (*db_put_live_out_summary_paths_func)(const char *, list);
extern entity_effects (*db_get_useful_variables_effects_func)(const char *);
extern void (*db_put_useful_variables_effects_func)(const char *, entity_effects);
extern void (*effects_prettyprint_func)(list);
extern void (*effect_prettyprint_func)(effect);
extern text (*effects_to_text_func)(list);
extern void (*attach_effects_decoration_to_text_func)(text);
extern bool (*cell_preceding_p_func)(cell, descriptor, cell, descriptor, bool, bool *);
extern bool (*stmt_strongly_feasible_p_func)(statement);
extern void generic_effects_reset_all_methods(void);
/* prettyprint.c */
extern void set_action_interpretation(string /*r*/, string /*w*/);
extern void reset_action_interpretation(void);
extern string action_interpretation(int tag);
extern void set_is_user_view_p(bool /*user_view_p*/);
extern void set_prettyprint_with_attachments(bool /*attachments_p*/);
extern void reset_generic_prettyprints(void);
extern void set_a_generic_prettyprint(string /*resource_name*/, bool /*is_a_summary*/, gen_chunk */*res*/, generic_text_function /*tf*/, generic_prettyprint_function /*tp*/, generic_attachment_function /*ta*/);
extern void add_a_generic_prettyprint(string /*resource_name*/, bool /*is_a_summary*/, generic_text_function /*tf*/, generic_prettyprint_function /*tp*/, generic_attachment_function /*ta*/);
extern bool print_source_or_code_effects_engine(const char */*module_name*/, string /*file_suffix*/, bool /*use_values*/);
extern text get_any_effect_type_text(const char */*module_name*/, string /*resource_name*/, string /*summary_resource_name*/, bool /*give_code_p*/);
extern bool print_source_or_code_with_any_effects_engine(const char */*module_name*/, string /*resource_name*/, string /*summary_resource_name*/, string /*file_suffix*/, bool /*use_values*/);
extern void generic_print_effects(list /*pc*/);
/* intrinsics.c */
extern list generic_proper_effects_of_intrinsic(entity /*e*/, list /*args*/);
/* interprocedural.c */
extern list generic_fortran_effects_backward_translation(entity /*callee*/, list /*real_args*/, list /*l_sum_eff*/, transformer /*context*/);
extern list c_actual_argument_to_may_summary_effects(expression /*real_arg*/, tag /*act*/);
extern list generic_c_effects_backward_translation(entity /*callee*/, list /*real_args*/, list /*l_sum_eff*/, transformer /*context*/);
extern list generic_c_effects_forward_translation(entity /*callee*/, list /*real_args*/, list /*l_eff*/, transformer /*context*/);
extern list generic_effects_backward_translation(entity /*callee*/, list /*real_args*/, list /*l_sum_eff*/, transformer /*context*/);
extern list generic_effects_forward_translation(entity /*callee*/, list /*real_args*/, list /*l_eff*/, transformer /*context*/);
extern void effects_translate_fields_compilation_unit(list /*l_eff*/, string /*source_cu_name*/, string /*target_cu_name*/);
/* eval.c */
extern int effects_statement_line_number(void);
extern list generic_reference_to_points_to_matching_list(reference /*input_ref*/, descriptor /*input_desc*/, size_t */*p_current_max_path_length*/, bool */*exact_p*/, transformer /*current_precondition*/, list /*ptl*/, void (* /*cell_reference_conversion_func*/)(reference, reference *, descriptor *), bool (* /*cell_reference_preceding_p_func*/)(reference, descriptor, reference, descriptor, transformer, bool, bool *));
extern list generic_eval_cell_with_points_to(cell /*input_cell*/, descriptor /*input_desc*/, list /*ptl*/, bool */*exact_p*/, transformer /*current_precondition*/, bool (* /*cell_reference_preceding_p_func*/)(reference, descriptor, reference, descriptor, transformer, bool, bool *), void (* /*cell_reference_with_address_of_cell_reference_translation_func*/)(reference, descriptor, reference, descriptor, int, reference *, descriptor *, bool *), void (* /*cell_reference_conversion_func*/)(reference, reference *, descriptor *));
extern list generic_effect_find_equivalent_simple_pointer_values(effect /*eff*/, list /*l_in*/, cell_relation */*exact_aliased_pv*/, list */*l_in_remnants*/, bool (* /*cells_intersection_p_func*/)(cell, descriptor, cell, descriptor, bool *), bool (* /*cells_inclusion_p_func*/)(cell, descriptor, cell, descriptor, bool *), void (* /*simple_cell_conversion_func*/)(cell, cell *, descriptor *));
extern list generic_effect_find_aliases_with_simple_pointer_values(effect /*eff*/, list /*l_pv*/, bool */*exact_p*/, transformer /*current_precondition*/, bool (* /*cell_preceding_p_func*/)(cell, descriptor, cell, descriptor, transformer, bool, bool *), void (* /*cell_with_address_of_cell_translation_func*/)(cell, descriptor, cell, descriptor, int, cell *, descriptor *, bool *), void (* /*cell_with_value_of_cell_translation_func*/)(cell, descriptor, cell, descriptor, int, cell *, descriptor *, bool *), bool (* /*cells_intersection_p_func*/)(cell, descriptor, cell, descriptor, bool *), bool (* /*cells_inclusion_p_func*/)(cell, descriptor, cell, descriptor, bool *), void (* /*simple_cell_conversion_func*/)(cell, cell *, descriptor *));
/* liveness_analysis_engine.c */
extern bool live_in_summary_paths_engine(const char */*module_name*/);
extern bool live_out_summary_paths_engine(const char */*module_name*/);
extern bool live_paths_engine(const char */*module_name*/, effects_representation_val /*representation*/);
#endif /*  effects_generic_header_included */
