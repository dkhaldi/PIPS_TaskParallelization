/*

  $Id: paf-util-local.h 23065 2016-03-02 09:05:50Z coelho $

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
#include "matrix.h"
#include "matrice.h"

#define PIP_SOLVE_MIN 0
#define PIP_SOLVE_MAX 1

#define IS_MIN 0
#define IS_MAX 1

#define PAF_UTIL_MODULE_NAME "PAFUTIL"
#define DFG_MODULE_NAME "DFG"
#define MAPPING_MODULE_NAME "MAPPING"
#define DIFF_PREFIX "DIFF"
#define COEFF_PREFIX "COEFF"

#define POSITIVE 1
#define NEGATIVE 0

#define ADD_ELEMENT_TO_LIST( _list, _type, _element) \
    (_list = gen_nconc( _list, CONS( _type, _element, NIL)))

#define BASE_NODE_NUMBER 1000
