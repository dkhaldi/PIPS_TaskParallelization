/* Warning! Do not modify this file that is automatically generated! */
/* Modify src/Libs/sommet/sommet-local.h instead, to add your own modifications. */

/* header file built by cproto */

#ifndef  sommet_header_included
#define  sommet_header_included
/*

  $Id: sommet-local.h 1641 2016-03-02 08:20:19Z coelho $

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

/* package sommet: structure de donnees representant les sommets
 * d'un systeme generateur; elle contient:
 *  - le vecteur correspondant, a un coefficient multiplicatif pret qui le
 *    rend entier,
 *  - son denominateur,
 *  - un eventuel tableau de saturation (par rapport a une liste implicite
 *    de contraintes),
 *  - le chainage vers les autres rayons ou droites.
 *
 * Francois Irigoin, Mai 1989
 *
 * Cette structure de donnees est aussi utilisee dans plint.dir pour
 * representer la fonction economique, les contraintes lineaires et
 * les systemes de contraintes lineaires.
 *
 * FI: commentaires a completer par Corinne, declaration d'un type
 * synonyme pour eviter les conflits?
 */

#ifndef SOMMET

/* valeur numerique utilise pour flagger les structures de donnees de type
 * sommet */
#define SOMMET 1004

/* structure de donnees Sommet
 *  - eq_sat: eventuel tableau des saturations du sommets par rapport a un
 *    eventuel systeme de contraintes; inutilisable quand on ne connait pas
 *    le nombre de contraintes, egalites ou inegalites
 *  - vecteur: coordonnees entieres du sommet, a un coefficient multiplicatif
 *    pres; l'inverse de ce coefficient est donne par le champ suivant
 *  - denominateur: coefficient permettant de garder les coordonnees du
 *    sommet sous forme rationnelle; les numerateurs des coordonnees se
 *    trouvent dans "vecteur"; le denominateur est unique, pour le sommet,
 *    i.e. c'est le PGCD des coordonnees; le denominateur doit toujours
 *    etre strictement positif
 *  - succ: pointeur vers le sommet suivant; on s'interesse a l'ensemble
 *    des sommets du systeme generateur plutot qu'a un sommet particulier
 */
typedef struct typ_som {
    int *eq_sat;
    Pvecteur vecteur;
    Value denominateur;
    struct typ_som *succ;
} *Psommet,Ssommet;

#define print_som(s) sommet_fprint(stdout,s)

#define print_lsom(ls) fprint_lsom(stdout,ls)

#define VERSION_FINALE
#ifdef VERSION_FINALE
#define SOMMET_RM(s,function_name) sommet_rm(s)
#else
#define SOMMET_RM(s,function_name) dbg_sommet_rm(s,function_name)
#endif

/* macros d'acces */

/* int sommet_denominateur(Psommet): denominateur des coordonnees d'un
 * sommet; ex den_of()
 */
#define sommet_denominateur(s) ((s)->denominateur)

#endif /* SOMMET */
/* sommet.c */
extern Psommet sommet_new(void);
extern Psommet sommet_make(Value /*d*/, Pvecteur /*v*/);
extern Psommet sommet_dup(Psommet /*s_in*/);
extern void sommet_rm(Psommet /*s*/);
extern void dbg_sommet_rm(Psommet /*s*/, char */*f*/);
extern void sommet_fprint(FILE */*f*/, Psommet /*s*/, char *(* /*nom_var*/)(Variable));
extern void sommet_fprint_as_dense(FILE */*f*/, Psommet /*s*/, Pbase /*b*/);
extern void sommet_dump(Psommet /*s*/);
extern void fprint_lsom(FILE */*f*/, Psommet /*ls*/, char *(* /*nom_var*/)(Variable));
extern void fprint_lsom_as_dense(FILE */*f*/, Psommet /*ls*/, Pbase /*b*/);
extern void sommet_normalize(Psommet /*ns*/);
extern bool som_in_liste(Psommet /*s*/, Psommet /*listes*/);
extern bool sommet_egal(Psommet /*s1*/, Psommet /*s2*/);
extern bool egaliste_s(Psommet /*l1*/, Psommet */*ad_l2*/);
extern void sommet_add(Psommet */*ps*/, Psommet /*som*/, int */*nb_som*/);
/* sommets.c */
extern Psommet sommets_dup(Psommet /*som*/);
extern void sommets_rm(Psommet /*ps*/);
extern void sommets_normalize(Psommet /*som*/);
#endif /*  sommet_header_included */
