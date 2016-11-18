/* Warning! Do not modify this file that is automatically generated! */
/* Modify src/Libs/sparse_sc/sparse_sc-local.h instead, to add your own modifications. */

/* header file built by cproto */

#ifndef  sparse_sc_header_included
#define  sparse_sc_header_included
/*

  $Id: sparse_sc-local.h 1641 2016-03-02 08:20:19Z coelho $

  Copyright 1989-2016 MINES ParisTech

  This file is part of Linear/C3 Library.

  Linear/C3 Library is free software: you can redistribute it and/or modify it
  under the terms of the GNU Lesser General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  any later version.

  Linear/C3 Library is distributed in the hope that it will be useful, but WITHOUT ANY
  WARRANTY; without even the implied warranty of MERCHANTABILITY or
  FITNESS FOR A PARTICULAR PURPOSE.

  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public License
  along with Linear/C3 Library.  If not, see <http://www.gnu.org/licenses/>.

*/

/* sys_matrice_conv.c */
extern void sys_matrice_index(Psysteme /*sc*/, Pbase /*base_index*/, matrice /*A*/, int /*n*/, int /*m*/);
extern void matrice_index_sys(Psysteme /*sc*/, Pbase /*base_index*/, matrice /*AG*/, int /*n*/, int /*m*/);
extern void sc_to_matrices(Psysteme /*ps*/, Pbase /*base_index*/, matrice /*A*/, matrice /*B*/, int /*n*/, int /*m*/);
extern void matrices_to_sc(Psysteme /*ps*/, Pbase /*base_index*/, matrice /*A*/, matrice /*B*/, int /*n*/, int /*m*/);
extern void loop_sc_to_matrices(Psysteme /*ps*/, Pbase /*index_base*/, Pbase /*const_base*/, matrice /*A*/, matrice /*B*/, int /*n*/, int /*m1*/, int /*m2*/);
extern void matrices_to_loop_sc(Psysteme /*ps*/, Pbase /*index_base*/, Pbase /*const_base*/, matrice /*A*/, matrice /*B*/, int /*n*/, int /*m1*/, int /*m2*/);
extern void constraints_to_matrices(Pcontrainte /*pc*/, Pbase /*b*/, Pmatrix /*A*/, Pmatrix /*B*/);
extern void matrices_to_constraints(Pcontrainte */*pc*/, Pbase /*b*/, Pmatrix /*A*/, Pmatrix /*B*/);
extern void constraints_with_sym_cst_to_matrices(Pcontrainte /*pc*/, Pbase /*index_base*/, Pbase /*const_base*/, Pmatrix /*A*/, Pmatrix /*B*/);
extern void matrices_to_constraints_with_sym_cst(Pcontrainte */*pc*/, Pbase /*index_base*/, Pbase /*const_base*/, Pmatrix /*A*/, Pmatrix /*B*/);
#endif /*  sparse_sc_header_included */
