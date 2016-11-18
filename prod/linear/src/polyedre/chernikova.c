/*

  $Id: chernikova.c 1641 2016-03-02 08:20:19Z coelho $

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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdlib.h>

#include "assert.h"
#include "boolean.h"
#include "vecteur.h"
#include "contrainte.h"
#include "sc.h"
#include "sommet.h"
#include "ray_dte.h"
#include "sg.h"
#include "polyedre.h"
#include "polynome.h"

Ptsg sc_to_sg_chernikova(Psysteme sc)
{
	Ptsg sg;

	if (linear_use_gmp())
#ifdef HAVE_GMP_H
		sg = sc_to_sg_chernikova_mulprec(sc);
#else
    abort();
#endif
	else
		sg = sc_to_sg_chernikova_fixprec(sc);

	return sg;
}

Psysteme sg_to_sc_chernikova(Ptsg sg)
{
	Psysteme sc;

	if (linear_use_gmp())
#ifdef HAVE_GMP_H
		sc = sg_to_sc_chernikova_mulprec(sg);
#else
    abort();
#endif // HAVE_GMP_H
	else
		sc = sg_to_sc_chernikova_fixprec(sg);

	return sc;
}

Psysteme sc_convex_hull(Psysteme sc1, Psysteme sc2)
{
	Psysteme sc;

	if (linear_use_gmp())
#ifdef HAVE_GMP_H
		sc = sc_convex_hull_mulprec(sc1, sc2);
#else
    abort();
#endif // HAVE_GMP_H
	else
		sc = sc_convex_hull_fixprec(sc1, sc2);

	return sc;
}
