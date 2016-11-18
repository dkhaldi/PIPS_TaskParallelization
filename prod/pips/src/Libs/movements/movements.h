/* Warning! Do not modify this file that is automatically generated! */
/* Modify src/Libs/movements/movements-local.h instead, to add your own modifications. */

/* header file built by cproto */

#ifndef  movements_header_included
#define  movements_header_included
/*

  $Id: movements-local.h 23065 2016-03-02 09:05:50Z coelho $

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
/* Package movements   */

#include "matrice.h"

#define COLUMN_MAJOR true

#define SUFFIX_FOR_TEMP_VAR1_IN_INNER_LOOP          "_1"
#define SUFFIX_FOR_TEMP_VAR2_IN_INNER_LOOP          "_2"

 
/* movement_computation.c */
extern Pbase build_image_base(bool /*bank_code*/, Pbase /*proc_id*/, Pbase /*bank_indices*/, Pbase /*tile_indices*/);
extern void print_fullname_base(Pbase /*sb*/);
extern void update_basis(Pbase /*scbase*/, Pbase */*index_base*/, Pbase */*const_base*/, Pbase */*image_base*/, Pbase /*bank_indices*/, Pbase /*tile_indices*/, Pbase */*lindex*/, Pbase */*lvar_coeff_nunit*/, Pbase */*lvar_coeff_unit*/, Pbase */*loop_body_offsets*/, Pbase */*loop_body_indices*/, bool /*bank_code*/, Pbase /*ppid*/);
extern void sort_tile_indices(Pbase /*tile_indices*/, Pbase */*new_tile_indices*/, matrice /*Q*/, int /*m*/);
extern Psysteme elim_redund_sc_with_sc(Psysteme /*sc1*/, Psysteme /*sc2*/, Pbase /*index_base*/, int /*dim*/);
extern Pbase variables_in_declaration_list(entity /*module*/, code /*ce*/);
extern statement movement_computation(entity /*module*/, bool /*used_def*/, bool /*bank_code*/, bool /*receive_code*/, entity /*private_entity*/, Psysteme /*sc_image*/, Pbase /*const_base*/, Pbase /*bank_indices*/, Pbase /*tile_indices*/, Pbase /*ppid*/, Pbase /*loop_body_indices*/, int /*n*/, int /*dim_h*/);
extern Psysteme sc_image_computation(entity /*module*/, entity /*entity_var*/, Psysteme /*sc_domain*/, Psysteme /*sc_array_function*/, Pbase /*index_base*/, Pbase */*const_base*/, entity /*proc_id*/, Pbase /*bank_indices*/, Pbase /*tile_indices*/, Pbase */*new_tile_indices*/, int /*pn*/, int /*bn*/, int /*ls*/, int */*n*/, int */*dim_h*/);
/* bound_generation.c */
extern expression lower_bound_generation(Psysteme /*sc_neg*/, Pbase /*index_base*/, int /*number_of_lower_bounds*/, int /*loop_rank*/);
extern expression upper_bound_generation(Psysteme /*sc_pos*/, Pbase /*index_base*/, int /*number_of_upper_bounds*/, int /*loop_rank*/);
extern expression test_bound_generation(Psysteme /*sc_test*/, Pbase /*index_base*/);
extern statement bound_generation(entity /*module*/, bool /*bank_code*/, bool /*receive_code*/, entity /*ent*/, Pbase /*loop_body_indices*/, Pbase /*var_id*/, Psysteme */*lsystem*/, Pbase /*index_base*/, int /*n*/, int /*sc_info*/[][4]);
/* operation.c */
extern expression make_div_expression(expression /*ex1*/, cons */*ex2*/);
extern expression make_op_expression(entity /*op*/, cons */*ex2*/);
/* complex_bound_generation.c */
extern expression complex_bound_generation(Value /*coeff1*/, Value /*coeff2*/, Value /*coeff3*/, Pvecteur /*exp1*/, Variable /*var1*/, Pvecteur /*exp2*/, Variable /*var2*/);
extern expression complex_bound_computation(Psysteme /*sc*/, Pbase /*index_base*/, Pcontrainte /*ineq1*/, Pcontrainte /*ineq2*/, int /*rank*/);
/* constraint_distribution.c */
extern void bound_distribution(Psysteme */*pps*/, Pbase /*index_base*/, int /*sc_info*/[][4], int /*nb_loop*/, Psysteme */*sc_neg*/, Psysteme */*sc_pos*/, Psysteme /*sc_test*/);
extern void constraint_distribution(Psysteme /*sc*/, Psysteme */*bound_systems*/, Pbase /*index_base*/, int /*sc_info*/[][4]);
extern void egalite_distribution(Psysteme /*sc*/, Psysteme */*bound_systems*/, Pbase /*index_base*/);
/* make_loop_body.c */
extern void wp65_debug_print_text(entity /*m*/, statement /*s*/);
extern void wp65_debug_print_module(entity /*m*/, statement /*s*/);
extern bool variable_in_declaration_module_p(entity /*m*/, entity /*v*/);
extern entity find_operator(entity /*module*/, string /*oper*/, string /*str*/);
extern statement make_statement_operator(entity /*oper*/, cons */*args*/);
extern statement make_movements_loop_body_wp65(entity /*module*/, bool /*receive_code*/, entity /*ent*/, Pbase /*local_indices*/, Pbase /*var_id*/, Psysteme /*sc_neg*/, Psysteme /*sc_pos*/, Pbase /*index_base*/, int /*rank*/, int /*number_of_lower_bounds*/, int /*number_of_upper_bounds*/);
extern statement make_datum_movement(entity /*module*/, bool /*receive_code*/, entity /*ent*/, Pbase /*local_indices*/, Pbase /*var_id*/);
extern statement make_movement_scalar_wp65(entity /*module*/, bool /*receive_code*/, reference /*r*/, entity /*var_id*/);
/* build_sc_machine.c */
extern Psysteme build_sc_machine(int /*pn*/, int /*bn*/, int /*ls*/, Psysteme /*sc_array_function*/, entity /*proc_id*/, Pbase /*bank_indices*/, entity /*entity_var*/);
/* build_sc_tile.c */
extern Pvecteur make_loop_indice_equation(Pbase /*loop_indices*/, tiling /*tile*/, Pvecteur /*tile_delay*/, Pvecteur /*tile_indices*/, Pvecteur /*tile_local_indices*/, int /*rank*/);
extern Psysteme loop_bounds_to_tile_bounds(Psysteme /*loop_bounds*/, Pbase /*loop_indices*/, tiling /*t*/, Pvecteur /*tile_delay*/, Pvecteur /*tile_indices*/, Pvecteur /*tile_local_indices*/);
/* sc_add_variable.c */
extern Variable sc_add_new_variable_name(entity /*module*/, Psysteme /*ps*/);
#endif /*  movements_header_included */
