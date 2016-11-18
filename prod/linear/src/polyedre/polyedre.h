/* Warning! Do not modify this file that is automatically generated! */
/* Modify src/Libs/polyedre/polyedre-local.h instead, to add your own modifications. */

/* header file built by cproto */

#ifndef  polyedre_header_included
#define  polyedre_header_included
/*

  $Id: polyedre-local.h 1641 2016-03-02 08:20:19Z coelho $

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

/* package sur les polyedres poly
 *
 * Malik Imadache, Corinne Ancourt, Neil Butler, Francois Irigoin
 *
 * Modifications:
 *  - declaration de Ppoly et Spoly utilisant Psysteme au lieu de struct
 *    Ssysteme * (FI, 3/1/90)
 */
#include "ray_dte.h"
#include "sg.h"
#include "polynome.h"

/* obsolete (not maintained)
 */
/*

typedef struct ssinter {
	int val_sat,sv;
	Psommet som_sat;
	} Ss_sat_inter;

typedef struct srdinter {
	int val_sat;
	Pray_dte vect_sat;
	} Svect_sat_inter;

typedef struct Spoly {
	Psysteme sc;
	Ptsg sg;
	} *Ppoly,Spoly;


#define POLYEDRE_UNDEFINED ((Ppoly) NULL)
#define POLYEDRE_UNDEFINED_P(p) ((p)==POLYEDRE_UNDEFINED)

#define print_ineq_sat(ineq,nb_s,nb_r) fprint_ineq_sat(stdout,ineq,nb_s,nb_r)

#define print_lineq_sat(lineq,nb_s,nb_r) \
    fprint_lineq_sat(stdout,lineq,nb_s,nb_r)
*/

/* macro d'acces aux champs et sous-champs d'un polyedre, de son systeme
 * generateur sg et de son systeme de contraintes sc
 */
/*
#define poly_inegalites(p) ((p)->sc->inegalites)
#define poly_egalites(p) ((p)->sc->egalites)
#define poly_sommets(p) (sg_sommets((p)->sg))
#define poly_rayons(p) (sg_rayons((p)->sg))
#define poly_droites(p) (sg_droites((p)->sg))

#define poly_nbre_sommets(p) (sg_nbre_sommets((p)->sg))
#define poly_nbre_rayons(p) (sg_nbre_rayons((p)->sg))
#define poly_nbre_droites(p) (sg_nbre_droites((p)->sg))

#define poly_nbre_egalites(p) (sc_nbre_egalites((p)->sc))
#define poly_nbre_inegalites(p) (sc_nbre_inegalites((p)->sc))
*/

/* sc_enveloppe.c */
extern Psysteme sc_enveloppe_chernikova_ofl_ctrl(Psysteme /*s1*/, Psysteme /*s2*/, int /*ofl_ctrl*/);
extern Psysteme sc_enveloppe_chernikova(Psysteme /*s1*/, Psysteme /*s2*/);
extern Psysteme elementary_convex_union(Psysteme /*s1*/, Psysteme /*s2*/);
extern Psysteme sc_cute_convex_hull(Psysteme /*is1*/, Psysteme /*is2*/);
extern Psysteme sc_rectangular_hull(Psysteme /*sc*/, Pbase /*pb*/);
/* chernikova_fixprec.c */
extern Ptsg sc_to_sg_chernikova_fixprec(Psysteme /*sc*/);
extern Psysteme sg_to_sc_chernikova_fixprec(Ptsg /*sg*/);
extern Psysteme sc_convex_hull_fixprec(Psysteme /*sc1*/, Psysteme /*sc2*/);
/* chernikova_mulprec.c */
/* chernikova.c */
extern Ptsg sc_to_sg_chernikova(Psysteme /*sc*/);
extern Psysteme sg_to_sc_chernikova(Ptsg /*sg*/);
extern Psysteme sc_convex_hull(Psysteme /*sc1*/, Psysteme /*sc2*/);
#endif /*  polyedre_header_included */
