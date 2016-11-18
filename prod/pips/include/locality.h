/* Warning! Do not modify this file that is automatically generated! */
/* Modify src/Libs/locality/locality-local.h instead, to add your own modifications. */

/* header file built by cproto */

#ifndef  locality_header_included
#define  locality_header_included
/*

  $Id: locality-local.h 23065 2016-03-02 09:05:50Z coelho $

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

/* cette structure contient une pile. La tete de cette pile contient le statement courant */
/* depth represente  la profondeur des nids */ 

typedef struct {
  hash_table contenu;
  hash_table depth;
  stack statement_stack;
} * context_p, context_t;


/* stats.c */
extern bool loop_statistics(const string /*name*/);
/* tiling_sequence.c */
extern loop loop1;
extern entity first_array;
extern statement permutation(statement /*s*/, Pmatrix /*P*/);
extern statement permutation2(statement /*s*/, Pmatrix /*P*/);
extern statement Hierarchical_tiling(void);
extern int position_one_element(Pmatrix /*P*/, int /*i*/);
extern statement Tiling_buffer_allocation(void);
extern statement Tiling2_buffer(void);
extern bool tiling_sequence(string /*module*/);
/* guard_elimination.c */
extern Psysteme sc_newbase;
extern Ptsg sg;
extern bool if1;
extern bool if2;
extern statement unimodular(statement /*s*/);
extern statement free_guards(statement /*s*/);
extern bool guard_elimination(string /*module*/);
#endif /*  locality_header_included */
