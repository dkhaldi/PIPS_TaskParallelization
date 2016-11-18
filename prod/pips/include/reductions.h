/* Warning! Do not modify this file that is automatically generated! */
/* Modify src/Libs/reductions/reductions-local.h instead, to add your own modifications. */

/* header file built by cproto */

#ifndef  reductions_header_included
#define  reductions_header_included
/*

  $Id: reductions-local.h 23065 2016-03-02 09:05:50Z coelho $

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
#include "reductions_private.h"
/* shorthands for REDUCTION:
 */
#define reduction_variable(r) reference_variable(reduction_reference(r))
#define reduction_none_p(r) reduction_operator_none_p(reduction_op(r))
#define reduction_tag(r) reduction_operator_tag(reduction_op(r))
#define make_none_reduction(var) \
    make_reduction(make_reference(var, NIL), \
                   make_reduction_operator(is_reduction_operator_none, UU),\
                   NIL, NIL)

/* quick debug macros
 */
#define DEBUG_REDUCTION(level, msg, red) \
  ifdebug(level){pips_debug(level, msg); print_reduction(red);}
#define DEBUG_REDUCTIONS(level, msg, reds) \
  ifdebug(level){pips_debug(level, msg); \
                 gen_map(print_reduction, reductions_list(reds));}

/* end of it
 */



/* atomic.c */
extern bool replace_reduction_with_atomic(string /*mod_name*/);
extern bool flag_parallel_reduced_loops_with_atomic(string /*mod_name*/);
extern bool flag_parallel_reduced_loops_with_openmp_directives(const char */*mod_name*/);
/* stub.c */
extern bool old_reductions(string /*mod_name*/);
/* reductions.c */
extern reductions load_summary_reductions(entity /*f*/);
extern bool summary_reductions(const char */*module_name*/);
extern bool proper_reductions_undefined_p(void);
extern void reset_proper_reductions(void);
extern void error_reset_proper_reductions(void);
extern void set_proper_reductions(pstatement_reductions /*o*/);
extern pstatement_reductions get_proper_reductions(void);
extern void init_proper_reductions(void);
extern void close_proper_reductions(void);
extern void store_proper_reductions(statement /*k*/, reductions /*v*/);
extern void update_proper_reductions(statement /*k*/, reductions /*v*/);
extern reductions load_proper_reductions(statement /*k*/);
extern reductions delete_proper_reductions(statement /*k*/);
extern bool bound_proper_reductions_p(statement /*k*/);
extern void store_or_update_proper_reductions(statement /*k*/, reductions /*v*/);
extern bool proper_reductions(const char */*module_name*/);
extern bool cumulated_reductions_undefined_p(void);
extern void reset_cumulated_reductions(void);
extern void error_reset_cumulated_reductions(void);
extern void set_cumulated_reductions(pstatement_reductions /*o*/);
extern pstatement_reductions get_cumulated_reductions(void);
extern void init_cumulated_reductions(void);
extern void close_cumulated_reductions(void);
extern void store_cumulated_reductions(statement /*k*/, reductions /*v*/);
extern void update_cumulated_reductions(statement /*k*/, reductions /*v*/);
extern reductions load_cumulated_reductions(statement /*k*/);
extern reductions delete_cumulated_reductions(statement /*k*/);
extern bool bound_cumulated_reductions_p(statement /*k*/);
extern void store_or_update_cumulated_reductions(statement /*k*/, reductions /*v*/);
extern bool cumulated_reductions(const char */*module_name*/);
extern entity reduction_operator_entity(reduction_operator /*op*/);
extern bool same_reduction_p(reduction /*r1*/, reduction /*r2*/);
/* utils.c */
extern bool reduction_star_p(reduction /*r*/);
extern void remove_variable_from_reduction(reduction /*red*/, entity /*var*/);
extern bool update_reduction_under_effect(reduction /*red*/, effect /*eff*/);
extern bool update_compatible_reduction_with(reduction */*pr*/, entity /*var*/, reduction /*r*/);
extern bool update_compatible_reduction(reduction */*pr*/, entity /*var*/, list /*le*/, reductions /*reds*/);
extern bool pure_function_p(entity /*f*/);
extern bool no_other_effects_on_references(statement /*s*/, list /*lr*/);
extern bool call_proper_reduction_p(statement /*s*/, call /*c*/, reduction */*red*/);
extern expression get_complement_expression(statement /*s*/, reference /*reduced*/);
/* transformation.c */
extern bool loop_reductions(string /*module*/);
/* pragma.c */
extern list reductions_get_omp_pragma_expr(loop /*l*/, statement /*stmt*/, bool /*strict*/);
extern string reductions_get_omp_pragma_str(loop /*l*/, statement /*stmt*/);
extern bool omp_pragma_expr_for_reduction(loop /*l*/, statement /*stmt*/, bool /*strict*/);
extern bool omp_pragma_expr_for(loop /*l*/, statement /*stmt*/);
/* prettyprint.c */
extern bool printed_reductions_undefined_p(void);
extern void reset_printed_reductions(void);
extern void error_reset_printed_reductions(void);
extern void set_printed_reductions(pstatement_reductions /*o*/);
extern pstatement_reductions get_printed_reductions(void);
extern void init_printed_reductions(void);
extern void close_printed_reductions(void);
extern void store_printed_reductions(statement /*k*/, reductions /*v*/);
extern void update_printed_reductions(statement /*k*/, reductions /*v*/);
extern reductions load_printed_reductions(statement /*k*/);
extern reductions delete_printed_reductions(statement /*k*/);
extern bool bound_printed_reductions_p(statement /*k*/);
extern void store_or_update_printed_reductions(statement /*k*/, reductions /*v*/);
extern string note_for_statement(statement /*s*/);
extern string reduction_operator_tag_name(tag /*t*/);
extern string reduction_operator_name(reduction_operator /*o*/);
extern string reduction_name(reduction /*r*/);
extern void print_reduction(reduction /*r*/);
extern bool print_code_proper_reductions(const char */*module_name*/);
extern bool print_code_cumulated_reductions(const char */*module_name*/);
/* call.c */
extern list summary_to_proper_reference(call /*c*/, reference /*r*/);
extern list translate_reductions(call /*c*/);
/* propagation.c */
extern bool reduction_propagation(const char */*mod_name*/);
extern bool reduction_detection(const char */*mod_name*/);
#endif /*  reductions_header_included */
