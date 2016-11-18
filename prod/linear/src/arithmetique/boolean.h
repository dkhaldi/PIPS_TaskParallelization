/*

  $Id: boolean.h 1641 2016-03-02 08:20:19Z coelho $

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

#ifndef BOOLEAN_INCLUDED
#define BOOLEAN_INCLUDED

#include <stdint.h>

#ifdef bool
    #error newgen header not compatible with stdbool.h and linear header have to be compatible with newgen
#endif

typedef int bool; /* we cannot use an enum or stdbool because we need to be compatible with newgen */

#define false 0
#define true 1

#endif /* BOOLEAN_INCLUDED */
