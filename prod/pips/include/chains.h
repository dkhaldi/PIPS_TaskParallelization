/* Warning! Do not modify this file that is automatically generated! */
/* Modify src/Libs/chains/chains-local.h instead, to add your own modifications. */

/* header file built by cproto */

#ifndef  chains_header_included
#define  chains_header_included
/*

  $Id: chains-local.h 23065 2016-03-02 09:05:50Z coelho $

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


/* To choose the concepts used to compute dependence chains */
enum chain_type {
  USE_PROPER_EFFECTS = 1,
  USE_REGIONS,
  USE_IN_OUT_REGIONS
};
/* chains.c */
extern graph statement_dependence_graph(statement /*s*/);
extern bool atomic_chains(const string /*module_name*/);
extern bool region_chains(const string /*module_name*/);
extern bool in_out_regions_chains(const string /*module_name*/);
#endif /*  chains_header_included */
