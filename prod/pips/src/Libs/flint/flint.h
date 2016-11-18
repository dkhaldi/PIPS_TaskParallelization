/* Warning! Do not modify this file that is automatically generated! */
/* Modify src/Libs/flint/flint-local.h instead, to add your own modifications. */

/* header file built by cproto */

#ifndef  flint_header_included
#define  flint_header_included
/*

  $Id: flint-local.h 23065 2016-03-02 09:05:50Z coelho $

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
extern statement flint_current_statement;
/* flint.c */
extern statement flint_current_statement;
extern bool flinter(const string /*module_name*/);
extern void flint_message(char */*fun*/, char */*fmt*/, ...);
extern void flint_message_2(char */*fun*/, char */*fmt*/, ...);
extern void raw_flint_message(bool /*count*/, char */*fmt*/, ...);
/* flint_walk.c */
extern void flint_cons_dimension(list /*pc*/);
extern dimension flint_dimension(dimension /*d*/);
extern call flint_call(call /*c*/);
extern range flint_range(range /*r*/);
extern reference flint_reference(reference /*r*/);
extern void flint_syntax(syntax /*s*/);
extern void flint_cons_expression(list /*pc*/);
extern void flint_cons_actual_argument(list /*pc*/);
extern expression flint_expression(expression /*e*/);
extern loop flint_loop(loop /*l*/);
extern test flint_test(test /*t*/);
extern instruction flint_instruction(instruction /*i*/);
extern void flint_unstructured(unstructured /*u*/);
extern void flint_cons_statement(list /*pc*/);
extern statement flint_statement(statement /*s*/);
/* flint_check.c */
extern bool check_procedure(call /*c*/);
extern bool check_the_call(call /*c*/);
extern bool check_call_intrinsic(list /*la*/, list /*lt*/, call /*c*/);
extern bool check_call_args_number(list /*la*/, list /*lt*/, call /*c*/);
extern bool check_call_types_compatibility(list /*la*/, list /*lt*/, call /*c*/);
extern bool check_call_one_type(expression /*exp*/, parameter /*param*/, call /*c*/, int /*i*/);
extern bool check_call_basic(basic /*be*/, basic /*bp*/, call /*c*/, int /*i*/);
extern bool check_call_dim(list /*de*/, list /*dp*/, call /*c*/, int /*i*/);
extern bool check_call_basic_and_dim(expression /*exp*/, parameter /*param*/, call /*c*/, int /*i*/);
extern void check_the_reference(reference /*ref*/);
extern bool check_call_mode_consistency(list /*la*/, list /*lt*/, entity /*the_fnct*/);
extern bool check_call_one_mode(expression /*exp*/, parameter /*param*/, entity /*the_fnct*/, list /*sefs_list*/, int /*i*/);
extern bool look_at_the_commons(entity /*module*/);
extern bool position_in_the_area(entity /*the_var*/, intptr_t */*inf*/, intptr_t */*sup*/);
extern bool check_commons(entity /*module*/);
extern void check_one_common(entity /*local*/, entity /*module*/);
extern bool check_overlap_in_common(entity /*the_common*/, entity /*e1*/, int /*inf1*/, int /*sup1*/, entity /*e2*/, int /*inf2*/, int /*sup2*/);
/* flint_utils.c */
extern bool number_of_elements(list /*ld*/, intptr_t */*the_result*/);
extern bool size_of_dimension(dimension /*d*/, intptr_t */*the_int*/);
extern bool control_type_in_expression(enum basic_utype /*a_basic*/, int /*a_dim*/, expression /*exp*/);
extern bool find_bd_parameter(parameter /*param*/, basic */*base*/, list */*dims*/);
extern bool find_bd_type_variable(type /*tp*/, basic */*base*/, list */*dims*/);
extern bool find_bd_expression(expression /*exp*/, basic */*base*/, list */*dims*/);
extern bool find_bd_reference(reference /*ref*/, basic */*base*/, list */*dims*/);
extern bool find_bd_call(call /*c*/, basic */*base*/, list */*dims*/);
/* uninitialized_variables.c */
extern void flint_uninitialized_variables(graph /*dependence_graph*/, statement /*module_stat*/);
#endif /*  flint_header_included */
