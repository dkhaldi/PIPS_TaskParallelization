/* Warning! Do not modify this file that is automatically generated! */
/* Modify src/Libs/ray_dte/ray_dte-local.h instead, to add your own modifications. */

/* header file built by cproto */

#ifndef  ray_dte_header_included
#define  ray_dte_header_included
/*

  $Id: ray_dte-local.h 1641 2016-03-02 08:20:19Z coelho $

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

/* package ray_dte: structure de donnees representant les rayons et les
 * droites d'un systeme generateur; elle contient le vecteur correspondant,
 * un eventuel tableau de saturation, et le chainage vers les autres rayons
 * ou droites.
 *
 * Francois Irigoin, Mai 1989
 *
 * Voir poly.h
 *
 * A terme, poly.h devrait exploser et la definition de ray_dte etre remise
 * dans ce fichier; a moins qu'on ne mette plutot ray_dte.h dans sg.h
 * pour eviter une explosion des .h
 */

#ifndef RAY_DTE
/* numero du type de donnees */
#define RAY_DTE 105

typedef struct rdte   {
	int *eq_sat;
	struct	Svecteur *vecteur;
	struct rdte   *succ;
	} *Pray_dte,Sray_dte;

#define print_rd(s) ray_dte_fprint(stdout,s)

#define print_lray_dte(lv) fprint_lray_dte(stdout,lv)

#ifndef VERSION_FINALE
#define RAY_DTE_RM(rd,f) dbg_ray_dte_rm(rd,f)
#else
#define RAY_DTE_RM(rd,f) ray_dte_rm(rd)
#endif

#endif /* RAY_DTE */
/* ray_dte.c */
extern Pray_dte ray_dte_dup(Pray_dte /*rd_in*/);
extern Pray_dte ray_dte_new(void);
extern Pray_dte ray_dte_make(Pvecteur /*v*/);
extern Pray_dte ray_oppose(Pray_dte /*r*/);
extern void ray_dte_rm(Pray_dte /*rd*/);
extern void dbg_ray_dte_rm(Pray_dte /*rd*/, char */*f*/);
extern void ray_dte_fprint(FILE */*f*/, Pray_dte /*rd*/, char *(* /*nom_var*/)(Variable));
extern void ray_dte_fprint_as_dense(FILE */*f*/, Pray_dte /*rd*/, Pbase /*b*/);
extern void ray_dte_dump(Pray_dte /*rd*/);
extern void fprint_lray_dte(FILE */*f*/, Pray_dte /*listrd*/, char *(* /*nom_var*/)(Variable));
extern void fprint_lray_dte_as_dense(FILE */*f*/, Pray_dte /*listrd*/, Pbase /*b*/);
extern void ray_dte_normalize(Pray_dte /*rd*/);
extern bool rd_in_liste(Pray_dte /*rd*/, Pray_dte /*lrd*/);
extern bool egaliste_rd(Pray_dte /*l1*/, Pray_dte */*ad_l2*/);
extern Pray_dte elim_null_vect(Pray_dte /*l*/, int */*n*/);
extern void elim_tt_rd(Pray_dte /*listrd*/);
#endif /*  ray_dte_header_included */
