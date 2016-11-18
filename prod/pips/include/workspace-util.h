/* Warning! Do not modify this file that is automatically generated! */
/* Modify src/Libs/workspace-util/workspace-util-local.h instead, to add your own modifications. */

/* header file built by cproto */

#ifndef  workspace_util_header_included
#define  workspace_util_header_included
/*

  $Id$

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
/* WORKSPACE-UTIL Library: Functions dealing with the internal
   representation at the workspace level, mixing calls to pipsdbm,
   naming-util and ri-util.
 */

#include "linear.h"
#include "genC.h"

#include "ri.h"
#include "text.h"
#include "cloning.h"

#include "newgen.h"

#include "naming.h"
#include "ri-util.h"
#include "pipsdbm.h"
/* naming.c */
extern const char *entity_module_unambiguous_user_name(entity /*e*/, entity /*m*/);
extern const char *entity_unambiguous_user_name(entity /*e*/);
extern const char *entity_minimal_name(entity /*e*/);
extern const char *entity_minimal_user_name(entity /*e*/);
extern void print_arguments(list /*args*/);
extern entity string_to_entity(const char */*s*/, entity /*module*/);
extern list string_to_entities(const char */*str*/, const char */*seed*/, entity /*module*/);
/* expressions.c */
extern expression string_to_expression(const char */*s*/, entity /*module*/);
extern list string_to_expressions(const char */*str*/, const char */*seed*/, entity /*module*/);
/* misc_paf_utils.c */
extern list base_to_list(Pbase /*b*/);
extern Pbase list_to_base(list /*l*/);
extern expression make_max_exp(entity /*ent*/, expression /*exp1*/, expression /*exp2*/);
extern entity make_nlc_entity(int */*Gcount_nlc*/);
extern int Gcount_nsp;
extern int Gcount_nub;
extern entity make_nsp_entity(void);
extern entity make_nub_entity(void);
extern entity current_module(entity /*mod*/);
extern bool undefined_statement_list_p(list /*l*/);
extern entity expression_int_scalar(expression /*exp*/);
extern entity scalar_assign_call(call /*c*/);
extern void scalar_written_in_call(call /*the_call*/, list */*ell*/, list */*etl*/, list */*swfl*/);
/* module.c */
extern list module_declarations(entity /*m*/);
extern list current_module_declarations(void);
extern list module_entities(entity /*m*/);
extern entity module_entity_to_compilation_unit_entity(entity /*m*/);
extern bool language_module_p(entity /*m*/, string /*lid*/);
extern void AddEntityToCompilationUnit(entity /*e*/, entity /*cu*/);
extern void RemoveEntityFromCompilationUnit(entity /*e*/, entity /*cu*/);
extern void AddEntityToModuleCompilationUnit(entity /*e*/, entity /*module*/);
extern list module_to_all_declarations(entity /*m*/);
extern string compilation_unit_of_module(const char */*module_name*/);
extern string module_name_to_input_file_name(const char */*module_name*/);
#endif /*  workspace_util_header_included */
