/* Warning! Do not modify this file that is automatically generated! */
/* Modify src/Libs/hyperplane/hyperplane-local.h instead, to add your own modifications. */

/* header file built by cproto */

#ifndef  hyperplane_header_included
#define  hyperplane_header_included
/*

  $Id: hyperplane-local.h 23065 2016-03-02 09:05:50Z coelho $

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
/* package hyperplane */

#define HYPERPLANE_OPTIONS "X"
#include "matrice.h"

/* hyperplane.c */
extern statement hyperplane(cons */*lls*/);
/* hyperplane_direction.c */
extern bool interactive_hyperplane_direction(Value */*h*/, int /*n*/);
/* scanning_base.c */
extern void scanning_base_hyperplane(Value /*h*/[], int /*n*/, matrice /*G*/);
extern void base_G_h1_unnull(Value /*h*/[], int /*n*/, matrice /*G*/);
/* global_parallelization.c */
extern void global_parallelization(const char */*module_name*/);
extern bool loop_hyperplane(const char */*module_name*/);
/* code_generation.c */
extern statement code_generation(list /*lls*/, Pvecteur /*pvg*/[], Pbase /*base_oldindex*/, Pbase /*base_newindex*/, Psysteme /*sc_newbase*/, bool /*preserve_entry_label_p*/);
/* tiling.c */
extern bool static_partitioning_matrix(matrice /*P*/, int /*n*/, const char */*serialized_matrix*/);
extern bool interactive_partitioning_matrix(matrice /*P*/, int /*n*/);
extern Pvecteur loop_nest_to_offset(list /*lls*/);
extern statement tiling(list /*lls*/);
extern bool loop_tiling(const char */*module_name*/);
/* symbolic_tiling.c */
extern bool fix_loop_index_sign(loop /*l*/);
extern void do_symbolic_tiling(statement /*base*/, list /*vector*/);
extern bool symbolic_tiling(const char */*module_name*/);
/* unimodular.c */
extern int loop_unimodular(string /*name*/);
#endif /*  hyperplane_header_included */
