/* Warning! Do not modify this file that is automatically generated! */
/* Modify src/Libs/conversion/conversion-local.h instead, to add your own modifications. */

/* header file built by cproto */

#ifndef  conversion_header_included
#define  conversion_header_included
/*

  $Id: conversion-local.h 23065 2016-03-02 09:05:50Z coelho $

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
/*
 *  Package conversion
 */
#include "matrice.h"


/* change_of_Pbase.c */
extern void derive_new_basis(Pbase /*base_oldindex*/, Pbase */*base_newindex*/, entity (* /*new_entity*/)(entity));
extern void change_of_base_index(Pbase /*base_oldindex*/, Pbase */*base_newindex*/);
extern entity make_index_prime_entity(entity /*old_index*/);
extern entity make_index_entity(entity /*old_index*/);
extern Psysteme sc_change_baseindex(Psysteme /*sc*/, Pbase /*base_old*/, Pbase /*base_new*/);
/* code_change_of_basis.c */
extern void scanning_base_to_vect(matrice /*G*/, int /*n*/, Pbase /*base*/, Pvecteur /*pvg*/[]);
extern Pvecteur vect_change_base(Pvecteur /*pv_old*/, Pbase /*base_oldindex*/, Pvecteur /*pvg*/[]);
extern cons *listexpres_to_listexpres_newbase(cons */*lex*/, Pvecteur /*pvg*/[], Pbase /*base_oldindex*/);
extern expression expression_to_expression_newbase(expression /*e_old*/, Pvecteur /*pvg*/[], Pbase /*base_oldindex*/);
extern void statement_newbase(statement /*s*/, Pvecteur /*pvg*/[], Pbase /*base_oldindex*/);
/* loop_iteration_domaine_to_sc.c */
extern Psysteme loop_iteration_domaine_to_sc(list /*lls*/, Pbase */*baseindex*/);
extern void loop_index_domaine_to_contrainte(range /*r*/, entity /*ind*/, Psysteme /*sc*/);
/* look_for_nested_loops.c */
extern void look_for_nested_loop_statements(statement /*s*/, statement (* /*loop_transformation*/)(list, bool (*)(statement)), bool (* /*loop_predicate*/)(statement));
extern statement look_for_inner_loops(loop /*l*/, list /*sl*/, statement (* /*loop_transformation*/)(list, bool (*)(statement)), bool (* /*loop_predicate*/)(statement));
extern void look_for_nested_loops_unstructured(unstructured /*u*/, statement (* /*loop_transformation*/)(list, bool (*)(statement)), bool (* /*loop_predicate*/)(statement));
/* system_to_code.c */
extern expression Psysteme_to_expression(Psysteme /*systeme*/);
extern list Pcontrainte_to_expression_list(Pcontrainte /*constraint*/, entity /*operator*/);
extern void set_information_for_code_optimizations(Psysteme /*s*/);
extern void reset_information_for_code_optimizations(void);
extern expression constraints_to_loop_bound(Pcontrainte /*c*/, Variable /*var*/, bool /*is_lower*/, entity /*divide*/);
extern bool bounds_equal_p(Variable /*var*/, Pcontrainte /*lower*/, Pcontrainte /*upper*/);
extern statement systeme_to_loop_nest(Psysteme /*sc*/, list /*vars*/, statement /*body*/, entity /*divide*/);
extern statement generate_optional_if(Psysteme /*sc*/, statement /*stat*/);
#endif /*  conversion_header_included */
