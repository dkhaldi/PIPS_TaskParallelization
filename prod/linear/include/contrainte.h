/* Warning! Do not modify this file that is automatically generated! */
/* Modify src/Libs/contrainte/contrainte-local.h instead, to add your own modifications. */

/* header file built by cproto */

#ifndef  contrainte_header_included
#define  contrainte_header_included
/*

  $Id: contrainte-local.h 1641 2016-03-02 08:20:19Z coelho $

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

/* package sur les contraintes. 
 *
 * Une contrainte est une egalite ou une inegalite. Elle est representee
 * par un vecteur dont une coordonnee particuliere, TCST, represente
 * le terme constant.
 *
 * Les contraintes sont stockees sous forme de membres gauches, ce qui 
 * n'est utile a savoir que pour les inegalites:
 *
 *      sum a x + b <= 0
 *       i   i i
 * ou b est le terme constant.
 *
 * Les tableaux de saturations sont calcules en fonction de polyedre
 * (systeme generateur ou systeme de contraintes) et leurs dimensions
 * sont inconnues au niveau des contraintes. Ils sont ignores la
 * plupart du temps.
 *
 * Les contraintes sont traitees sous forme de liste de contraintes
 * (systeme d'egalites ou systeme d'inegalites) et possedent un champ
 * de chainage. Certaines des fonctions portent sur des listes de
 * contraintes et non sur des contraintes. Cette double semantique
 * complique beaucoup les choses.
 *
 * Le pointeur NULL represente implicitement l'une des contraintes toujours
 * faisables, 0 == 0 ou 0 <= 0. Au moins, la plupart du temps... car
 * il represente la valeur CONTRAINTE_UNDEFINED dans les routines de gestion
 * memoire.
 *
 * Il vaut mieux utiliser la macro CONTRAINTE_NULLE_P() qui verifie que
 * le vecteur associe est le VECTEUR_NUL.
 *
 * Les contraintes trivialement faisables et infaisables sont representees
 * par un unique terme constant: 0 == k, 0 <= k, 0 <= -k (k positif).
 * Il existe deux fonctions pour les tester.
 *
 * Autres packages a inclure:
 *  - types.h
 *  - boolean.h
 *  - vecteur.h
 *
 * Malik Imadache, Corinne Ancourt, Neil Butler, Francois Irigoin
 *
 * Bugs:
 *  - melange de la notion de chainage et de la notion de terme constant
 *  - definition directe de TCST: on ne peut pas decider dynamiquement
 *    de la variable representant le terme constant
 *  - definition de TCST au niveau contrainte, alors que TCST doit etre
 *    utilise au niveau vecteur (cf. macro term_cst())
 *
 * Modifications:
 *  - passage du terme constant a gauche (FI, 24/11/89)
 *  - deplacement de la definition du terme constant TCST et de la macro
 *    term_cst dans le package vecteur (PB, 06/06/90)
 */

#ifndef CONTRAINTE

/* constante associee a la structure de donnees "contrainte" */
#define CONTRAINTE 1005

typedef struct Scontrainte   {
        int *eq_sat;
	int *s_sat,*r_sat;
	Pvecteur vecteur;
	struct Scontrainte *succ;
	} Scontrainte,*Pcontrainte;

typedef Scontrainte Segalite, * Pegalite;

typedef Scontrainte Sinegalite, * Pinegalite;

/* MACROS ET CONSTANTES */

#define egalite_print(eg) egalite_fprint(stdout,eg)
/* FI: this macro requires an additional parameter or a default value
   as third parameter of inegalite_fprint() */
#define inegalite_print(ineg) inegalite_fprint(stdout,ineg)

/* passage au champ vecteur d'une contrainte "a la  Newgen" */
#define contrainte_vecteur(c) ((c)->vecteur)

#define contrainte_succ(c) ((c)->succ)

/* contrainte nulle (non contrainte 0 == 0 ou 0 <= 0) */
#define CONTRAINTE_NULLE_P(c) (VECTEUR_NUL_P(contrainte_vecteur(c)))

#define CONTRAINTE_UNDEFINED ((Pcontrainte) NULL)

#define CONTRAINTE_UNDEFINED_P(c) ((c)==CONTRAINTE_UNDEFINED)

/* int COEFF_CST(Pcontrainte c): terme constant d'une contrainte */
#define COEFF_CST(c) vect_coeff(TCST,(c)->vecteur)

/* the standard xxx_rm does not return a value */
#define contrainte_rm(c) (void) contrainte_free(c)

#define VERSION_FINALE
#ifndef VERSION_FINALE
#define CONTRAINTE_RM(rd,f) dbg_contrainte_rm(rd,f)
#else
#define CONTRAINTE_RM(rd,f) contrainte_rm(rd)
#endif


#endif /* CONTRAINTE */
/* alloc.c */
extern Pcontrainte contrainte_new(void);
extern Pcontrainte contrainte_make(Pvecteur /*pv*/);
extern Pcontrainte contrainte_make_1D(Value /*a*/, Variable /*x*/, Value /*b*/, bool /*less_p*/);
extern Pcontrainte contraintes_make(Pvecteur /*pv*/, ...);
extern Pcontrainte contrainte_dup(Pcontrainte /*c_in*/);
extern Pcontrainte contraintes_dup(Pcontrainte /*c_in*/);
extern Pcontrainte contrainte_free(Pcontrainte /*c*/);
extern Pcontrainte contraintes_free(Pcontrainte /*pc*/);
extern void dbg_contrainte_rm(Pcontrainte /*c*/, char */*f*/);
extern Pcontrainte contrainte_copy(Pcontrainte /*c_in*/);
extern Pcontrainte contraintes_copy(Pcontrainte /*c_in*/);
/* binaires.c */
extern int contrainte_subst_ofl(Variable /*v*/, Pcontrainte /*def*/, Pcontrainte /*c*/, bool /*eq_p*/);
extern int contrainte_subst(Variable /*v*/, Pcontrainte /*def*/, Pcontrainte /*c*/, bool /*eq_p*/);
extern Pcontrainte contrainte_substitute_dimension(Pcontrainte /*e*/, Variable /*i*/, Pvecteur /*v*/);
extern Pcontrainte inegalite_comb(Pcontrainte /*posit*/, Pcontrainte /*negat*/, Variable /*v*/);
extern Pcontrainte inegalite_comb_ofl(Pcontrainte /*posit*/, Pcontrainte /*negat*/, Variable /*v*/);
extern int contrainte_subst_ofl_ctrl(Variable /*v*/, Pcontrainte /*def*/, Pcontrainte /*c*/, bool /*eq_p*/, int /*ofl_ctrl*/);
extern Pcontrainte inegalite_comb_ofl_ctrl(Pcontrainte /*posit*/, Pcontrainte /*negat*/, Variable /*v*/, int /*ofl_ctrl*/);
extern Value eq_diff_const(Pcontrainte /*c1*/, Pcontrainte /*c2*/);
extern Value eq_sum_const(Pcontrainte /*c1*/, Pcontrainte /*c2*/);
extern Pcontrainte contrainte_append(Pcontrainte /*c1*/, Pcontrainte /*c2*/);
extern Pcontrainte extract_common_constraints(Pcontrainte */*pc1*/, Pcontrainte */*pc2*/, bool /*eq*/);
/* error.c */
extern void contrainte_error(char */*name*/, char */*fmt*/, ...);
/* io.c */
extern void contrainte_fprint(FILE */*fp*/, Pcontrainte /*c*/, bool /*is_inegalite*/, char *(* /*variable_name*/)(Variable));
extern void egalite_fprint(FILE */*fp*/, Pcontrainte /*eg*/, char *(* /*variable_name*/)(Variable));
extern void egalite_dump(Pcontrainte /*c*/);
extern void inegalite_fprint(FILE */*fp*/, Pcontrainte /*ineg*/, char *(* /*variable_name*/)(Variable));
extern void inegalite_dump(Pcontrainte /*c*/);
extern void egalites_fprint(FILE */*fp*/, Pcontrainte /*eg*/, char *(* /*variable_name*/)(Variable));
extern void egalites_dump(Pcontrainte /*eg*/);
extern void inegalites_fprint(FILE */*fp*/, Pcontrainte /*ineg*/, char *(* /*variable_name*/)(Variable));
extern void inegalites_dump(Pcontrainte /*eg*/);
extern void sprint_operator(char */*s*/, bool /*is_inegalite*/, bool /*a_la_fortran*/);
extern char *contrainte_sprint(char */*s*/, Pcontrainte /*c*/, bool /*is_inegalite*/, char *(* /*variable_name*/)(Variable));
extern char *contrainte_sprint_format(char */*s*/, Pcontrainte /*c*/, bool /*is_inegalite*/, char *(* /*variable_name*/)(Variable), bool /*a_la_fortran*/);
extern char *egalite_sprint(char */*s*/, Pcontrainte /*eg*/, char *(* /*variable_name*/)(Variable));
extern char *inegalite_sprint(char */*s*/, Pcontrainte /*ineg*/, char *(* /*variable_name*/)(Variable));
extern char *egalite_sprint_format(char */*s*/, Pcontrainte /*eg*/, char *(* /*variable_name*/)(Variable), bool /*a_la_fortran*/);
extern char *inegalite_sprint_format(char */*s*/, Pcontrainte /*ineg*/, char *(* /*variable_name*/)(Variable), bool /*a_la_fortran*/);
/* listes.c */
extern bool contrainte_in_liste(Pcontrainte /*c*/, Pcontrainte /*lc*/);
extern int constraint_rank(Pcontrainte /*c*/, Pcontrainte /*lc*/);
extern bool egalite_in_liste(Pcontrainte /*v*/, Pcontrainte /*listev*/);
extern int nb_elems_list(Pcontrainte /*list*/);
extern bool cyclic_constraint_list_p(Pcontrainte /*l*/);
extern int safe_nb_elems_list(Pcontrainte /*list*/, int /*n*/);
extern Pcontrainte contrainte_remove_large_coef(Pcontrainte /*lc*/, Value /*val*/);
/* normalize.c */
extern bool contrainte_normalize(Pcontrainte /*c*/, bool /*is_egalite*/);
extern bool egalite_normalize(Pcontrainte /*eg*/);
extern bool inegalite_normalize(Pcontrainte /*ineg*/);
/* predicats.c */
extern bool eq_smg(Pcontrainte /*c1*/, Pcontrainte /*c2*/);
extern bool inequalities_opposite_p(Pcontrainte /*c1*/, Pcontrainte /*c2*/);
extern bool egalite_equal(Pcontrainte /*eg1*/, Pcontrainte /*eg2*/);
extern bool contrainte_equal(Pcontrainte /*c1*/, Pcontrainte /*c2*/);
extern bool contrainte_parallele(Pcontrainte /*c1*/, Pcontrainte /*c2*/, Value */*pa1*/, Value */*pa2*/);
extern bool contrainte_constante_p(Pcontrainte /*c*/);
extern bool vect_constant_p(Pvecteur /*v*/);
extern bool contrainte_verifiee(Pcontrainte /*ineg*/, bool /*eq_p*/);
extern bool contrainte_oppos(Pcontrainte /*ineg1*/, Pcontrainte /*ineg2*/);
extern bool constraint_without_vars(Pcontrainte /*c*/, Pbase /*vars*/);
extern bool constraints_without_vars(Pcontrainte /*pc*/, Pbase /*vars*/);
extern Value contrainte_eval(Pvecteur /*c*/, Pvecteur /*v*/);
extern bool contrainte_eval_p(Pvecteur /*c*/, Pvecteur /*v*/, bool /*is_equality_p*/);
extern bool equality_eval_p(Pvecteur /*c*/, Pvecteur /*v*/);
extern bool inequality_eval_p(Pvecteur /*c*/, Pvecteur /*v*/);
/* unaires.c */
extern void norm_eq(Pcontrainte /*nr*/);
extern void contrainte_chg_sgn(Pcontrainte /*c*/);
extern void contrainte_reverse(Pcontrainte /*c*/);
extern void eq_set_vect_nul(Pcontrainte /*c*/);
extern Pcontrainte contrainte_translate(Pcontrainte /*c*/, Pbase /*b*/, char *(* /*variable_name*/)(void));
extern Pcontrainte contrainte_variable_rename(Pcontrainte /*c*/, Variable /*v_old*/, Variable /*v_new*/);
extern void Pcontrainte_separate_on_vars(Pcontrainte /*initial*/, Pbase /*vars*/, Pcontrainte */*pwith*/, Pcontrainte */*pwithout*/);
extern void constraints_for_bounds(Variable /*var*/, Pcontrainte */*pinit*/, Pcontrainte */*plower*/, Pcontrainte */*pupper*/);
extern Pcontrainte contrainte_dup_extract(Pcontrainte /*c*/, Variable /*var*/);
extern Pcontrainte contrainte_extract(Pcontrainte */*pc*/, Pbase /*base*/, Variable /*var*/);
extern int level_contrainte(Pcontrainte /*pc*/, Pbase /*base_index*/);
extern void contrainte_vect_sort(Pcontrainte /*c*/, int (* /*compare*/)(Pvecteur *, Pvecteur *));
extern Pcontrainte contrainte_var_min_coeff(Pcontrainte /*contraintes*/, Variable /*v*/, Value */*coeff*/, bool /*rm_if_not_first_p*/);
extern int equation_lexicographic_compare(Pcontrainte /*c1*/, Pcontrainte /*c2*/, int (* /*compare*/)(Pvecteur *, Pvecteur *));
extern int inequality_lexicographic_compare(Pcontrainte /*c1*/, Pcontrainte /*c2*/, int (* /*compare*/)(Pvecteur *, Pvecteur *));
extern Pcontrainte equations_lexicographic_sort(Pcontrainte /*cl*/, int (* /*compare*/)(Pvecteur *, Pvecteur *));
extern Pcontrainte inequalities_lexicographic_sort(Pcontrainte /*cl*/, int (* /*compare*/)(Pvecteur *, Pvecteur *));
extern Pcontrainte constraints_lexicographic_sort(Pcontrainte /*cl*/, int (* /*compare*/)(Pvecteur *, Pvecteur *));
extern Pcontrainte constraints_lexicographic_sort_generic(Pcontrainte /*cl*/, int (* /*compare*/)(Pvecteur *, Pvecteur *), bool /*is_equation*/);
extern Variable contrainte_simple_equality(Pcontrainte /*e*/);
#endif /*  contrainte_header_included */
