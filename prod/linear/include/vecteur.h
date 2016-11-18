/* Warning! Do not modify this file that is automatically generated! */
/* Modify src/Libs/vecteur/vecteur-local.h instead, to add your own modifications. */

/* header file built by cproto */

#ifndef  vecteur_header_included
#define  vecteur_header_included
/*

  $Id: vecteur-local.h 1641 2016-03-02 08:20:19Z coelho $

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

/* package sur les vecteurs creux et les bases
 *
 * Malik Imadache, Corinne Ancourt, Neil Butler, Francois Irigoin,
 * Remi Triolet
 *
 * Modifications:
 *  - les fonctions d'interface avec GenPgm dont les noms commencent par
 *    "_gC_" ont ete deplacees dans _gC_lib
 *  - passage a "char *" pour le type Variable au lieu de "int" (Linear-C3)
 *    et de "entity *" (Linear/C3 Library); le package n'est pas independant de la
 *    definition du type "Variable"; il faudrait ameliorer ca avec un
 *    package "Variable"
 *  - ajout des fonctions d'interface avec Newgen: (RT, 27/11/89)
 *  - ajout de la notion de base, comme cas particulier de vecteur
 *    (FI, 27/11/89) ou le champ "Value" n'a pas de signification
 *  - suppression de l'include de vecteur-basic-types.h; la fusion entre
 *    les versions C3 et Linear/C3 Library ne necessite plus cette distinction; il y a
 *    tellement peu de code a ecrire pour les variables et les valeurs
 *    qu'il est inutile d'avoir une directory differente pour lui
 *  - rapatriement de la definition du terme constant TCST et de la macro
 *    term_cst (du package contrainte) (PB, 06/06/90)
 *
 * - trop creux a mon avis. il faudrait une liste de petits tableaux ? FC.
 */

#ifndef NEWGEN
#define VECTEUR 1006	/* constante associee a un vecteur	*/
#endif

/* arithmetique is a requirement for vecteur, but I do not want
 * to inforce it in all pips files... thus here it is
 */
#include "arithmetique.h"

/* le type des variables (ou coordonnees) dans les vecteurs */
typedef void * Variable;
// The method type that return the name of a variable:
typedef char * (*get_variable_name_t)(Variable);

#define VARIABLE_UNDEFINED ((Variable) 0)
#define VARIABLE_UNDEFINED_P(v) ((v)==VARIABLE_UNDEFINED)
#define VARIABLE_DEFINED_P(v) ((v)!=VARIABLE_UNDEFINED)

/* le type des coefficients dans les vecteurs:
 * Value est defini dans le package arithmetique
 */

/* STRUCTURE D'UN VECTEUR
 *
 * Un vecteur est defini par une suite de couples Variable (i.e. element
 * de la base) et Valeur (valeur du coefficient correspondant). Les
 * coordonnees nulles ne sont pas representees et n'existe qu'implicitement
 * par rapport a une base (hypothetique) definie via la package "variable".
 *
 * En consequence, le vecteur nul est (malencontreusement) represente par
 * NULL. Cela gene toutes les procedures succeptibles de retourner une
 * valeur vecteur nul par effet de bord. Il faut alors passer en argument
 * un POINTEUR vers un Pvecteur. En general, nous avons prefere retourner
 * explicitement le vecteur calcule, a la maniere de ce qui est fait
 * dans string.h
 *
 * Il n'existe pas non plus de VECTEUR_UNDEFINED, puisque sa valeur devrait
 * logiquement etre NULL.
 */
typedef struct Svecteur {
    Variable var;
    Value val;
    struct Svecteur *succ;
} Svecteur, *Pvecteur;

/* STRUCTURE D'UNE BASE
 *
 * Une base est definie par son vecteur diagonal
 *
 * Les tests d'appartenance sont effectues par comparaison des pointeurs
 * et non par des strcmp.
 *
 * Rien ne contraint les coefficients a valoir 1 et le package plint
 * mais meme certains coefficients a 0, ce qui devrait revenir a faire
 * disparaitre la variable (i.e. la coordonnee) correspondante de la
 * base.
 */
typedef struct Svecteur Sbase, * Pbase;

/* DEFINITION DU VECTEUR NUL */
#define VECTEUR_NUL ((Pvecteur) 0)
#define VECTEUR_NUL_P(v) ((v)==VECTEUR_NUL)
#define VECTEUR_UNDEFINED ((Pvecteur) 0)
#define VECTEUR_UNDEFINED_P(v) ((v)==VECTEUR_UNDEFINED)

/* definition de la valeur de type PlinX==Pvecteur qui correspond a un
 * vecteur indefini parce que l'expression correspondante n'est pas
 * lineaire (Malik Imadache, Jean Goubault ?)
 */
#define PlinX Pvecteur
#define NONEXPLIN ((PlinX)-1)

/* MACROS SUR LES VECTEURS */
#define print_vect(s) vect_fprint(stdout,(s))
#define var_of(varval) ((varval)->var)
#define val_of(varval) ((varval)->val)
#define vecteur_var(v) ((v)->var)
#define vecteur_val(v) ((v)->val)
#define vecteur_succ(v) ((v)->succ)

/* VARIABLE REPRESENTANT LE TERME CONSTANT */
#define TCST ((Variable) 0)
#define term_cst(varval) ((varval)->var == TCST)

/* MACROS SUR LES BASES */
#define BASE_NULLE VECTEUR_NUL
#define BASE_NULLE_P(b) ((b)==VECTEUR_NUL)
#define BASE_UNDEFINED ((Pbase) 0)
#define BASE_UNDEFINED_P(b) ((b)==BASE_UNDEFINED)
#define base_dimension(b) vect_size((Pvecteur)(b))
#define base_add_dimension(b,v) vect_chg_coeff((Pvecteur *)(b),(v),VALUE_ONE)
#define base_rm(b) (vect_rm((Pvecteur)(b)), (b)=BASE_NULLE)
#define BASE_FOREACH(v, b)                                  \
  Pbase v ## _base = b;                                     \
  Variable v = v ## _base? v ## _base->var: NULL;           \
  for(; v ## _base != BASE_NULLE; v ## _base = v ## _base->succ, v = v ## _base? v ## _base->var: NULL)

/* I do thing that overflows are managed in a very poor manner. FC.
 * It should be all or not, as provided by any os that would raise
 * integer overflows. Thus we should have thought of a sofware
 * mecanism compatible with such a hardware and os approach.
 * maybe by defining a mult_Value macro to check explicitely for
 * overflows if needed, and defined to a simple product if not.
 * functions would have an additional argument for returning a
 * conservative answer in case of overflow. Maybe some global
 * variable could count the number of overflow that occured so that
 * some caller could check whether sg got wrong and thus could
 * warn about the result and this fact.
 * then we would have either the library compiled for these soft checks
 * or for none, but without any difference or explicite requirements
 * from the user of these functions.
 *
 * instead of that, we have the two versions at the same time with explicite
 * control required from the user. I heard that for some functions
 * this is not used... thus allowing good performance (each time some
 * result is false someone tracks down the not checked function and
 * checks overflow explicitely, thus it is not a very good approach).
 * moreover the most costly functions (simplexe, chernikova) are also
 * those in which the exceptions occurs thus they are all checked.
 * the the impact on performances is definitely low.
 * as far as software engineering is concerned, the current solution
 * adds low level switch for calling different versions (controled or not)
 * of pieces of code... this will have to be removed if some good os
 * is to host this software...
 */

/* OVERFLOW CONTROL
 */
#if (defined(LINEAR_NO_OVERFLOW_CONTROL))
#define OFL_CTRL 0
#define FWD_OFL_CTRL 0
#define NO_OFL_CTRL 0
#else /* some OVERFLOW CONTROL is allowed */
#define OFL_CTRL 2     /* overflows are treated in the called procedure */
#define FWD_OFL_CTRL 1 /* overflows are treated by the calling procedure */
#define NO_OFL_CTRL 0  /* overflows are not trapped at all  (dangerous !) */
#endif /* LINEAR_NO_OVERFLOW_CONTROL */

/* internal hash table for variable sets. */
struct linear_hashtable_st;
typedef struct linear_hashtable_st * linear_hashtable_pt;

/* end of vecteur-local.h */
/* alloc.c */
extern Pvecteur vect_dup(Pvecteur /*v_in*/);
extern void vect_rm(Pvecteur /*v*/);
extern Pvecteur vect_new(Variable /*var*/, Value /*coeff*/);
extern void dbg_vect_rm(Pvecteur /*v*/, char */*f*/);
extern Pvecteur vect_make(Pvecteur /*v*/, Variable /*var*/, Value /*val*/, ...);
extern Pvecteur vect_make_dense(Pbase /*b*/, Value /*val*/, ...);
extern Pvecteur vect_make_1D(Value /*a*/, Variable /*x*/, Value /*b*/);
extern Pbase vect_copy(Pvecteur /*b*/);
extern Pbase base_dup(Pbase /*b*/);
extern Pbase base_copy(Pbase /*b*/);
/* binaires.c */
extern Pvecteur vect_add(Pvecteur /*v1*/, Pvecteur /*v2*/);
extern Pvecteur vect_substract(Pvecteur /*v1*/, Pvecteur /*v2*/);
extern Pvecteur vect_substitute_dimension(Pvecteur /*v*/, Variable /*i*/, Pvecteur /*s*/);
extern Pvecteur vect_cl_ofl_ctrl(Pvecteur /*v*/, Value /*lambda*/, Pvecteur /*u*/, int /*ofl_ctrl*/);
extern Pvecteur vect_cl_ofl(Pvecteur /*v*/, Value /*lambda*/, Pvecteur /*u*/);
extern Pvecteur vect_cl(Pvecteur /*v*/, Value /*lambda*/, Pvecteur /*u*/);
extern Pvecteur vect_cl2_ofl_ctrl(Value /*x1*/, Pvecteur /*v1*/, Value /*x2*/, Pvecteur /*v2*/, int /*ofl_ctrl*/);
extern Pvecteur vect_cl2_ofl(Value /*x1*/, Pvecteur /*v1*/, Value /*x2*/, Pvecteur /*v2*/);
extern Pvecteur vect_cl2(Value /*x1*/, Pvecteur /*v1*/, Value /*x2*/, Pvecteur /*v2*/);
extern Pvecteur vect_subst(Variable /*v*/, Pvecteur /*v1*/, Pvecteur /*v2*/);
/* io.c */
extern Pvecteur vect_read(Pbase */*b*/);
extern void vect_fprint(FILE */*f*/, Pvecteur /*v*/, get_variable_name_t /*variable_name*/);
extern void vect_fprint_as_dense(FILE */*f*/, Pvecteur /*v*/, Pbase /*b*/);
extern void vect_fprint_as_monome(FILE */*f*/, Pvecteur /*v*/, Pbase /*b*/, get_variable_name_t /*variable_name*/, char */*mult_symbol*/);
extern char *vect_sprint_as_monome(Pvecteur /*v*/, Pbase /*b*/, get_variable_name_t /*variable_name*/, char */*mult_symbol*/);
extern void vect_dump(Pvecteur /*v*/);
extern void vect_print(Pvecteur /*v*/, get_variable_name_t /*variable_name*/);
extern void vect_fdump(FILE */*f*/, Pvecteur /*v*/);
extern void base_fprint(FILE */*f*/, Pbase /*b*/, get_variable_name_t /*variable_name*/);
/* reductions.c */
extern int vect_size(Pvecteur /*v*/);
extern int vect_dimension(Pvecteur /*v*/);
extern Value vect_prod_scal(Pvecteur /*v1*/, Pvecteur /*v2*/);
extern Value vect_pgcd_all(Pvecteur /*v*/);
extern Value vect_pgcd_except(Pvecteur /*v*/, Variable /*var*/);
extern Value vect_max0(Pvecteur /*v*/);
extern Value vect_min0(Pvecteur /*v*/);
extern Value vect_min(Pvecteur /*v*/);
extern Value vect_max(Pvecteur /*v*/);
extern Value vect_sum(Pvecteur /*v*/);
extern bool vect_equal(Pvecteur /*v1*/, Pvecteur /*v2*/);
extern bool vect_equal_except(Pvecteur /*v1*/, Pvecteur /*v2*/, Variable /*var*/);
extern bool vect_oppos(Pvecteur /*v1*/, Pvecteur /*v2*/);
extern bool vect_opposite_except(Pvecteur /*v1*/, Pvecteur /*v2*/, Variable /*var*/);
extern int vect_proport(Pvecteur /*v1*/, Pvecteur /*v2*/);
extern bool vect_colin_base(Pvecteur /*vec*/, Variable /*var*/);
extern bool vect_check(Pvecteur /*cv*/);
extern bool vect_consistent_p(Pvecteur /*v*/);
extern bool vect_larger_coef_p(Pvecteur /*v*/, Value /*val*/);
/* unaires.c */
extern void vect_normalize(Pvecteur /*v*/);
extern void vect_add_elem(Pvecteur */*pvect*/, Variable /*var*/, Value /*val*/);
extern void vect_erase_var(Pvecteur */*ppv*/, Variable /*v*/);
extern void vect_chg_coeff(Pvecteur */*ppv*/, Variable /*var*/, Value /*val*/);
extern void vect_chg_var(Pvecteur */*ppv*/, Variable /*v_old*/, Variable /*v_new*/);
extern Variable vect_one_coeff_if_any(Pvecteur /*v*/);
extern Pvecteur vect_del_var(Pvecteur /*v_in*/, Variable /*var*/);
extern Value vect_coeff(Variable /*var*/, Pvecteur /*vect*/);
extern Value vect_coeff_sum(Pvecteur /*vect*/);
extern Pvecteur vect_sign(Pvecteur /*v*/);
extern void vect_sort_in_place(Pvecteur */*pv*/, int (* /*compare*/)(Pvecteur *, Pvecteur *));
extern Pvecteur vect_sort(Pvecteur /*v*/, int (* /*compare*/)(Pvecteur *, Pvecteur *));
extern int vect_compare(Pvecteur */*pv1*/, Pvecteur */*pv2*/);
extern void Pvecteur_separate_on_sign(Pvecteur /*v*/, Pvecteur */*pvpos*/, Pvecteur */*pvneg*/);
extern bool vect_common_variables_p(Pvecteur /*v1*/, Pvecteur /*v2*/);
extern bool vect_contains_variable_p(Pvecteur /*v*/, Variable /*var*/);
extern int vect_lexicographic_compare(Pvecteur /*v1*/, Pvecteur /*v2*/, int (* /*compare*/)(Pvecteur *, Pvecteur *));
extern int vect_lexicographic_compare2(Pvecteur /*v1*/, Pvecteur /*v2*/, int (* /*compare*/)(Pvecteur *, Pvecteur *));
extern int vect_lexicographic_unsafe_compare(Pvecteur /*v1*/, Pvecteur /*v2*/, int (* /*compare*/)(Pvecteur *, Pvecteur *));
extern int vect_lexicographic_unsafe_compare2(Pvecteur /*v1*/, Pvecteur /*v2*/, int (* /*compare*/)(Pvecteur *, Pvecteur *));
extern int vect_lexicographic_unsafe_compare_generic(Pvecteur /*v1*/, Pvecteur /*v2*/, int (* /*compare*/)(Pvecteur *, Pvecteur *), bool /*is_equation*/);
/* base.c */
extern Pbase vect_add_variable(Pbase /*b*/, Variable /*v*/);
extern Pbase base_add_variable(Pbase /*b*/, Variable /*var*/);
extern Pbase make_base_from_vect(Pvecteur /*pv*/);
extern Pbase base_remove_variable(Pbase /*b*/, Variable /*v*/);
extern bool base_contains_variable_p(Pbase /*b*/, Variable /*v*/);
extern Variable base_find_variable(Pbase /*b*/, Variable /*v*/);
extern Variable base_find_variable_name(Pbase /*b*/, Variable /*v*/, char *(* /*variable_name*/)(Variable));
extern int base_find_variable_rank(Pbase /*b*/, Variable /*v*/, char *(* /*variable_name*/)(Variable));
extern Pbase base_reversal(Pbase /*b_in*/);
extern Pvecteur vect_rename(Pvecteur /*v*/, Pbase /*b*/, char *(* /*variable_name*/)(Variable));
extern Pvecteur vect_rename_variables(Pvecteur /*v*/, bool (* /*renamed_p*/)(Variable), Variable (* /*new_variable*/)(Variable));
extern Pvecteur vect_translate(Pvecteur /*v*/, Pbase /*b*/, char *(* /*variable_name*/)(Variable));
extern bool vect_in_basis_p(Pvecteur /*v*/, Pbase /*b*/);
extern Pvecteur vect_variable_rename(Pvecteur /*v*/, Variable /*v_old*/, Variable /*v_new*/);
extern void base_append(Pbase */*pb1*/, Pbase /*b2*/);
extern Pbase base_union(Pbase /*b1*/, Pbase /*b2*/);
extern Pbase base_intersection(Pbase /*b1*/, Pbase /*b2*/);
extern int rank_of_variable(Pbase /*base*/, Variable /*var*/);
extern Variable variable_of_rank(Pbase /*base*/, int /*rank*/);
extern int search_higher_rank(Pvecteur /*vect*/, Pbase /*base*/);
extern Variable search_var_of_higher_rank(Pvecteur /*pvect*/, Pbase /*base*/, Variable /*var*/);
extern Pvecteur search_i_element(Pbase /*b*/, int /*i*/);
extern Pbase base_normalize(Pbase /*b*/);
extern bool base_normalized_p(Pbase /*b*/);
extern Pbase base_difference(Pbase /*b1*/, Pbase /*b2*/);
extern bool base_included_p(Pbase /*b1*/, Pbase /*b2*/);
extern bool bases_strictly_equal_p(Pbase /*b1*/, Pbase /*b2*/);
/* error.c */
extern void vect_error(char */*name*/, char */*fmt*/, ...);
/* private.c */
extern Pvecteur vect_chain(Pvecteur /*v_in*/, Variable /*var*/, Value /*coeff*/);
extern Pvecteur vect_elem(Pvecteur /*vect*/, Variable /*var*/);
extern Pvecteur vect_extract(Pvecteur /*pvec*/, Variable /*var*/);
extern Variable vect_first_var(Pvecteur /*pvec*/);
extern Pvecteur vect_reversal(Pvecteur /*vect_in*/);
/* scalaires.c */
extern Pvecteur vect_div(Pvecteur /*v*/, Value /*x*/);
extern Pvecteur vect_clean(Pvecteur /*v*/);
extern Pvecteur vect_multiply(Pvecteur /*v*/, Value /*x*/);
extern void vect_chg_sgn(Pvecteur /*v*/);
/* variable.c */
extern bool variable_equal(Variable /*v1*/, Variable /*v2*/);
extern char *variable_default_name(Variable /*v*/);
extern char *variable_dump_name(Variable /*v*/);
extern char *(*variable_debug_name)(Variable);
extern void init_variable_debug_name(char *(* /*name*/)(Variable));
extern void reset_variable_debug_name(void);
extern Variable variable_make(char */*name*/);
/* hashpointer.c */
extern void linear_hashtable_dump(linear_hashtable_pt /*h*/);
extern bool linear_hashtable_coherent_p(linear_hashtable_pt /*h*/);
extern linear_hashtable_pt linear_hashtable_make(void);
extern void linear_hashtable_free(linear_hashtable_pt /*h*/);
extern void linear_hashtable_put(linear_hashtable_pt /*h*/, void */*k*/, void */*v*/);
extern void linear_hashtable_put_once(linear_hashtable_pt /*h*/, void */*k*/, void */*v*/);
extern bool linear_hashtable_isin(linear_hashtable_pt /*h*/, void */*k*/);
extern bool linear_hashtable_remove(linear_hashtable_pt /*h*/, void */*k*/);
extern void *linear_hashtable_get(linear_hashtable_pt /*h*/, void */*k*/);
extern int linear_hashtable_nitems(linear_hashtable_pt /*h*/);
#endif /*  vecteur_header_included */
