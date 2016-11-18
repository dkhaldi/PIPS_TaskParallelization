/* Warning! Do not modify this file that is automatically generated! */
/* Modify src/Libs/instrumentation/instrumentation-local.h instead, to add your own modifications. */

/* header file built by cproto */

#ifndef  instrumentation_header_included
#define  instrumentation_header_included
/*

  $Id: instrumentation-local.h 23065 2016-03-02 09:05:50Z coelho $

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
/* array_bound_check_bottom_up.c */
extern string int_to_dimension(int /*i*/);
extern bool array_need_bound_check_p(entity /*e*/);
extern expression subscript_value(entity /*arr*/, list /*l_inds*/);
extern string print_variables(expression /*e*/);
extern statement emit_message_and_stop(string /*stop_message*/);
extern bool array_bound_check_bottom_up(const char */*module_name*/);
/* array_bound_check_top_down.c */
extern string bool_to_bound(bool /*b*/);
extern bool array_bound_check_top_down(const char */*module_name*/);
/* array_bound_check_instrumentation.c */
extern statement array_bound_check_display(void);
extern bool old_array_bound_check_instrumentation(const char */*module_name*/);
extern bool array_bound_check_instrumentation(const char */*module_name*/);
/* array_bound_check_interprocedural.c */
extern bool array_bound_check_interprocedural(const char */*module_name*/);
/* alias_propagation.c */
extern expression translate_to_module_frame(entity /*mod1*/, entity /*mod2*/, expression /*e1*/, call /*c*/);
extern bool alias_propagation(char */*module_name*/);
/* alias_check.c */
extern expression simplify_relational_expression(expression /*e*/);
extern bool included_call_chain_p(list /*l1*/, list /*l2*/);
extern void print_alias_association(alias_association /*aa*/);
extern void print_list_of_alias_associations(list /*l*/);
extern bool functional_call_p(call /*c*/);
extern bool alias_check(char */*module_name*/);
/* used_before_set.c */
extern bool used_before_set(const char */*module_name*/);
/* control_counters.c */
extern bool add_control_counters(const string /*module_name*/);
#endif /*  instrumentation_header_included */
