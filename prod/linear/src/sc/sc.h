/* Warning! Do not modify this file that is automatically generated! */
/* Modify src/Libs/sc/sc-local.h instead, to add your own modifications. */

/* header file built by cproto */

#ifndef  sc_header_included
#define  sc_header_included
/*

  $Id: sc-local.h 1641 2016-03-02 08:20:19Z coelho $

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

 /* package sc sur les Systemes de Contraintes lineaires. Une contrainte
  * peut etre une egalite lineaire ou une inegalite lineaire
  *
  * Malik Imadache, Corinne Ancourt, Neil Butler, Francois Irigoin,
  * Remi Triolet
  *
  * Autres packages necessaires:
  *  - types.h
  *  - boolean.h
  *  - vecteur.h
  *  - contrainte.h
  *
  * Modifications:
  *  - redefinition de la structure "Ssysteme"; le champ "nbvars" est renomme
  *    "dimension"; il reste de type "int"; le champ "num_var" est remplace
  *    par un champ "base" de type "Pbase"; le champ "base" ne contient pas
  *    le terme constant; FI, 13/12/89;
  */


#ifndef SYSTEME
/* constante definissant le type Systeme */
#define SYSTEME 1001

#include "arithmetique.h"


/*
 * Le champ dimension donne le nombre de variables utilisees dans 
 * les egalites  et les inegalites, ou si l'on prefere, la dimension 
 * de l'espace dans lequel est defini le polyedre correspondant. 
 * Le terme constant ne fait pas partie de l'espace.
 *
 * La champ base contient tous les vecteurs de base, i.e. toutes les
 * variables apparaissant dans les egalites et les inegalites.
 * Le terme constant ne fait pas partie de la base.  La taille  de la 
 * base est donc egale a la  dimension du systeme. 
 * Si certaines fonctions ajoutent temporairement le terme constant a la
 * base, elles doivent l'oter apres traitement.
 * Le champ base est utilise par des algorithmes comme  celui du test 
 * de faisabilite mais il n'est pas entretenu automatiquement lors de 
 * l'ajout de nouvelles contraintes. Il faut penser aux mises a jour. 
 *
 */
typedef struct Ssysteme { 
	Pcontrainte egalites;
	Pcontrainte inegalites;
	int nb_eq;
	int nb_ineq;
	int dimension;
	Pbase base;
} *Psysteme,Ssysteme;

/* - Traitement des overflows :
 *  ~~~~~~~~~~~~~~~~~~~~~~~~~~ 
 * Pour ne pas dupliquer trop de fonctions pour le traitement des
 * overflows, nous avons fait une seule fonction prenant en parametre ofl_ctrl.
 *
 * NO_OFL_CTRL : pas de traitement des overflows.
 * 
 * FWD_OFL_CTRL : les overflows doivent e^tre re'cupe're's par les
 * fonctions appelantes.
 * OFL_CTRL : le setjmp est fait dans la fonction appele'e, et donc il est
 * inutile de faire un setjmp dans la fonction appelante. Cette dernie`re
 * option n'est pas disponible dans toutes les fonctions, car pour cela,
 * il faut rajouter un parame`tre permettant de savoir quoi retourner en
 * cas d'overflow, et ce n'e'tait pas toujours possible. Voir les
 * commentaires au dessus des fonctions pour cela.
 *
 * Toutes les fonctions qui acceptent ces valeurs en (dernier) parame`tre
 * ont leur nom qui finit par _ofl_ctrl.
 *
 * Ceci concerne quasiment toutes les fonctions de projection, les
 * fonctions de test de faisabilite', la fonction du simplexe, les
 * fonctions d'e'limination de redondances, la fonction de valeur absolue
 * (abs_ofl_ctrl), les fonctions de combinaisons line'aires de vecteurs.
 * Ceci n'est pas force'ment exhaustif...
 *
 *
 * - SC_EMPTY, SC_RN, sc_empty, sc_rn
 *   ~~~~~~~~~~~~~~~~ ~~~~~~~~~~~~~~~~
  * Le systeme vide "sc_empty" est represente par l'egalite "0==-1".
 * le systeme representant l'espace Rn "sc_rn" est un  systeme
 * ne contenant aucune contrainte.
 * Avant ces deux systemes etaient representes par Le pointeur (Psysteme) NULL.
 * Progressivement, les (Psysteme) NULL sont replaces par des appels aux
 *  fonctions sc_empty et sc_rn.
 * SC_EMPTY et SC_RN representent des valeurs obsoletes qu'ils faudraient
 * remplacer par les sc_empty et sc_rn.
 *
 * - entier ou rationnel ?
 *   ~~~~~~~~~~~~~~~~~~~~~
 * Les tests de faisabilite' e'taient fait en entier. Les deux tests
 * (entier et rationnel) sont maintenant disponibles (voir
 * sc_feasibility.c, il y a des commentaires).  Le test appele' par
 * l'ancienne fonction sc_faisabilite est celui en rationnel.
 * 
 * Les fonctions d'elimination des contraintes redondantes utilisent 
 * toujours la meme technique : inversion de la contrainte et ajout de 
 * la constante 1, avant de tester la faisabilite de cette contrainte inversee
 *  dans le contexte choisi. Ce contexte est soit le systeme entier pour 
 * "sc_elim_redund" ou le  systeme non redondant prealablement construit 
 * pour les fonctions  "build_sc_nredund..." et "sc_triang_elim_redund". 
 * Le test de faisabilite qui est applique est en rationnel pour les 
 * fonctions "build_sc_nredund..." et en entiers pour les 
 * "sc_triang_elim_redund". L'utilisation du test rationel permet de conserver 
 * des contraintes qui reduisent l'ensemble convexe des points entiers du 
 * polyedre. Ces contraintes peuvent etre redondantes en entiers, mais utiles 
 * si l'on veut tester l'exactitude de la projection. Ce type de contraintes 
 * est  considere comme redondant par "sc_triang_elim_redund".  
 * "sc_triang_elim_redund" est principalement utilise
 * pour parcourir les nids de boucles. En cas de projection non exacte, 
 * l'une des bornes inf. peut alors etre superieure a une borne sup. 
 * L'utilisation d'un test rationel pour "sc_triang_elim_redund" peut conduire 
 * a conserver des contraintes redondantes.
 * 
 * Note: l'inversion entiere de contrainte peut conduire a une augmentation 
 * du polyedre correspondant au systeme traite. Le nombre de contraintes est
 * minimise en entier mais le polyedre rationnel correspondant peut augmenter.
 * Si une enveloppe convexe est calculee ulterieurement, le resultat peut donc
 * etre degrade par une elimination de redondance anterieure.
 *
 */

#define get_sc_debug_level() sc_debug_level
#define ifscdebug(l) if (get_sc_debug_level()>=l)

/* MACROS */

#define sc_nbre_egalites(psc) ((psc)->nb_eq)
#define sc_nbre_inegalites(psc) ((psc)->nb_ineq)
#define sc_egalites(psc) ((psc)->egalites)
#define sc_inegalites(psc) ((psc)->inegalites)
#define sc_base(psc) ((psc)->base)
#define sc_dimension(psc) ((psc)->dimension)

void sc_add_egalite(Psysteme, Pcontrainte);
void sc_add_inegalite(Psysteme, Pcontrainte);

/* For the parsers: */
extern void sc_init_lex(void);
extern int syst_parse(void);
extern void syst_restart(FILE * input_file );


/* old compatible... */
#define sc_add_eg(p,c) sc_add_egalite(p, c)
#define sc_add_ineg(p,c) sc_add_inegalite(p, c)

/* ex-definition d'un systeme de contraintes infaisable, representant un
 * polyedre vide.
 *
 * Utiliser sc_empty() et sc_empty_p() plutot que ces macros obsoletes.
 */
#define SC_EMPTY ((Psysteme) NULL)
#define SC_EMPTY_P(sc) ((sc)==SC_EMPTY)

/* ex-definition d'un systeme de contraintes vide, representant tout l'espace,
 * dont la base se trouve eventuellement dans "base" (quand ce champ est
 * alloue); quand la base et la dimension ne sont pas definies, cela
 * represente un espace de dimension quelconque.
 *
 * Utiliser sc_rn() et sc_rn_p() plutot que ces macros obsoletes.
 */
#define SC_RN ((Psysteme) NULL)
#define SC_RN_P(sc) ((sc)==(Psysteme) NULL)

/* definition du systeme de contraintes non initialise
 */
#define SC_UNDEFINED ((Psysteme) NULL)
#define SC_UNDEFINED_P(sc) ((sc)==(Psysteme) NULL)

/* nombre maximum d'inequations que doit comporter un systeme lineaire
pour que l'elimination des redondances en nombres REELS s'effectue en un
temps raisonnable */
#define NB_INEQ_MAX1 100

/* nombre maximum d'inequations que doit comporter un systeme lineaire
pour que l'elimination des redondances en nombres ENTIERS s'effectue en
un temps raisonnable */
#define NB_INEQ_MAX2  50

/* ensemble de macros permettant de compiler les programmes utilisant
les anciens noms des fonctions */

#define sc_faisabilite(sc) sc_rational_feasibility_ofl_ctrl((sc), NO_OFL_CTRL,true) 
#define sc_faisabilite_ofl(sc) \
 sc_rational_feasibility_ofl_ctrl((sc), FWD_OFL_CTRL, true)
#define sc_feasible_ofl(sc, b) sc_rational_feasibility_ofl_ctrl((sc), OFL_CTRL, (b))
#define sc_elim_redond(ps) sc_elim_redund((ps))
#define sc_triang_elim_redond(x,y) sc_triang_elim_redund(x,y)
#define sc_rm_empty_constraints( ps,b) sc_elim_empty_constraints((ps),(b))
#define sc_kill_db_eg( ps) sc_elim_db_constraints((ps))
#define sc_safe_kill_db_eg( ps) sc_safe_elim_db_constraints((ps))
#define non_redundent_subsystem( s1,  s2) extract_nredund_subsystem((s1), (s2))
#define sc_nredund_ofl( psc) build_sc_nredund_2pass_ofl_ctrl((psc),FWD_OFL_CTRL)
#define sc_nredund_optim( psc) build_sc_nredund_2pass((psc))
#define sc_nredund( psc) build_sc_nredund_2pass((psc))
#define sc_projection_on_list_of_variables(sc,ib,pv) \
 sc_projection_on_variables((sc),(ib),(pv))
#define combiner(sc, v) \
 sc_fourier_motzkin_variable_elimination_ofl_ctrl((sc),(v),false,false,NO_OFL_CTRL)
#define combiner_ofl(sc, v) \
 sc_fourier_motzkin_variable_elimination_ofl_ctrl((sc),(v),false,false,FWD_OFL_CTRL)
#define exact_combiner_ofl(sc, v, b) \
 sc_fourier_motzkin_variable_elimination_ofl_ctrl((sc),(v),true, (b), FWD_OFL_CTRL)
#define eq_v_min_coeff(c, v, cf) contrainte_var_min_coeff((c), (v), (cf), false)
#define sc_projection_ofl_with_eq(sc, eq, v) \
 sc_variable_substitution_with_eq_ofl_ctrl((sc), (eq), (v), FWD_OFL_CTRL)
#define cond_suff_comb_integer(sc,pos,neg, v) \
 cond_suff_comb_integer_ofl_ctrl((sc),(pos),(neg), (v), NO_OFL_CTRL)
#define cond_suff_comb_integer_ofl(sc,pos,neg, v) \
 cond_suff_comb_integer_ofl_ctrl((sc),(pos),(neg), (v), FWD_OFL_CTRL)
#define sc_projection_int_along_vecteur(fsc,sc,ib,pv,ti,dim,n) \
 sc_integer_projection_along_variables((fsc),(sc),(ib),(pv),(ti),(dim),(n))
#define integer_projection(sci,sc,v) \
 sc_integer_projection_along_variable((sci),(sc),(v))

typedef int (*two_int_infop)[2];

typedef int (* constraint_cmp_func_t)
(const Pcontrainte *, const Pcontrainte *, void *);

#endif /* SYSTEME */
/* sc_alloc.c */
extern Psysteme sc_new(void);
extern Pbase sc_to_minimal_basis(Psysteme /*ps*/);
extern void sc_creer_base(Psysteme /*ps*/);
extern void sc_fix(Psysteme /*s*/);
extern Pbase sc_base_dup(int /*nbv*/, Pbase /*b*/);
extern Psysteme sc_dup(Psysteme /*ps*/);
extern Psysteme sc_copy(Psysteme /*ps*/);
extern void sc_rm(Psysteme /*ps*/);
extern Psysteme sc_init_with_sc(Psysteme /*sc*/);
extern Psysteme sc_empty(Pbase /*b*/);
extern Psysteme sc_rn(Pbase /*b*/);
extern bool sc_empty_p(Psysteme /*sc*/);
extern bool sc_rn_p(Psysteme /*sc*/);
extern void sc_add_egalite(Psysteme /*p*/, Pcontrainte /*e*/);
extern void sc_add_inegalite(Psysteme /*p*/, Pcontrainte /*i*/);
extern void sc_add_egalites(Psysteme /*p*/, Pcontrainte /*i*/);
extern void sc_add_inegalites(Psysteme /*p*/, Pcontrainte /*i*/);
/* sc_projection.c */
extern void sc_projection_along_variable_ofl_ctrl(Psysteme volatile */*psc*/, Variable /*v*/, int /*ofl_ctrl*/);
extern void sc_and_base_projection_along_variable_ofl_ctrl(Psysteme volatile */*psc*/, Variable /*v*/, int /*ofl_ctrl*/);
extern void sc_projection_along_variables_ofl_ctrl(Psysteme */*psc*/, Pvecteur /*pv*/, int /*ofl_ctrl*/);
extern void sc_projection_along_variables_with_test_ofl_ctrl(Psysteme */*psc*/, Pvecteur /*pv*/, bool */*is_proj_exact*/, int /*ofl_ctrl*/);
extern Psysteme sc_variable_substitution_with_eq_ofl_ctrl(Psysteme /*sc*/, Pcontrainte /*eq*/, Variable /*v*/, int /*ofl_ctrl*/);
extern Psysteme sc_simple_variable_substitution_with_eq_ofl_ctrl(Psysteme /*sc*/, Pcontrainte /*def*/, Variable /*v*/, int /*ofl_ctrl*/);
extern bool sc_fourier_motzkin_variable_elimination_ofl_ctrl(Psysteme /*sc*/, Variable /*v*/, bool /*integer_test_p*/, bool */*integer_test_res_p*/, int /*ofl_ctrl*/);
extern Psysteme sc_projection_on_variables(Psysteme /*sc*/, Pbase /*index_base*/, Pvecteur /*pv*/);
extern Pcontrainte sc_integer_inequalities_combination_ofl_ctrl(Psysteme /*sc*/, Pcontrainte /*posit*/, Pcontrainte /*negat*/, Variable /*v*/, bool */*integer_combination_p*/, int /*ofl_ctrl*/);
extern Psysteme sc_projection(Psysteme /*sc*/, Variable /*v*/);
extern Psysteme sc_projection_ofl(Psysteme /*sc*/, Variable /*v*/);
extern Psysteme sc_projection_pure(Psysteme /*sc*/, Variable /*v*/);
extern Psysteme sc_projection_ofl_along_variables(Psysteme /*sc*/, Pvecteur /*pv*/);
extern Psysteme sc_projection_ofl_along_variables_with_test(Psysteme /*sc*/, Pvecteur /*pv*/, bool */*is_proj_exact*/);
extern Psysteme sc_projection_by_eq(Psysteme /*sc*/, Pcontrainte /*eq*/, Variable /*v*/);
extern bool cond_suff_comb_integer_ofl_ctrl(Psysteme /*sc*/, Pcontrainte /*posit*/, Pcontrainte /*negat*/, Variable /*v*/, int /*ofl_ctrl*/);
extern Psysteme sc_projection_optim_along_vecteur(volatile Psysteme /*sc*/, Pvecteur /*pv*/);
extern Pcontrainte eq_v_coeff_min(Pcontrainte /*contraintes*/, Variable /*v*/);
extern bool sc_expensive_projection_p(Psysteme /*sc*/, Variable /*v*/);
extern void sc_extract_exact_common_equalities(Psysteme /*cl*/, Psysteme /*common*/, Psysteme /*s1*/, Psysteme /*s2*/);
extern void sc_project_very_simple_equalities(Psysteme /*s*/);
extern void sc_projection_along_variable_ofl_ctrl_timeout_ctrl(Psysteme volatile */*psc*/, Variable /*v*/, int /*ofl_ctrl*/);
extern Psysteme sc_system_projection_along_variables(Psysteme /*ps*/, Pvecteur /*pv*/);
/* sc_read.c */
extern Pcontrainte p_eg_fin;
extern Pcontrainte p_ineg_fin;
extern Pvecteur p_pred;
extern Pvecteur p_membre_courant;
extern Pvecteur cp;
extern char *nom_var[100];
extern void init_globals(void);
extern void new_ident(Psysteme /*ps*/, Variable /*s*/);
extern Variable rec_ident(Psysteme /*ps*/, Variable /*s*/);
extern void creer_eg(Psysteme /*ps*/, Pcontrainte /*peq*/);
extern void creer_ineg(Psysteme /*ps*/, Pcontrainte /*peq*/, int /*sens*/);
extern Psysteme sc_reversal(Psysteme /*sc*/);
extern Pcontrainte contrainte_reversal(Pcontrainte /*c*/);
/* sc.c */
extern void norm_syst(Psysteme /*sc*/);
extern Psysteme sc_make(Pcontrainte /*leg*/, Pcontrainte /*lineg*/);
extern Psysteme sc_translate(Psysteme /*s*/, Pbase /*b*/, char *(* /*variable_name*/)(void));
extern Psysteme sc_substitute_dimension(Psysteme /*s*/, Variable /*i*/, Pvecteur /*v*/);
extern Psysteme sc_variable_rename(Psysteme /*s*/, Variable /*v_old*/, Variable /*v_new*/);
extern Psysteme sc_rename_variables(Psysteme /*s*/, bool (* /*renamed_p*/)(void), Variable (* /*new_variable*/)(void));
extern Psysteme sc_variables_rename(Psysteme /*s*/, Pvecteur /*pv_old*/, Pvecteur /*pv_new*/, get_variable_name_t /*variable_name*/);
extern void sc_base_remove_variable(Psysteme /*sc*/, Variable /*v*/);
extern void sc_base_add_variable(Psysteme /*sc*/, Variable /*var*/);
extern bool sc_consistent_p(Psysteme /*sc*/);
extern bool sc_weak_consistent_p(Psysteme /*sc*/);
extern void sc_separate_on_vars(Psysteme /*s*/, Pbase /*b*/, Psysteme */*pwith*/, Psysteme */*pwithout*/);
/* sc_integer_analyze.c */
extern bool var_with_unity_coeff_p(Psysteme /*sc*/, Variable /*var*/);
extern void sc_integer_projection_information(Psysteme /*sc*/, Pbase /*index_base*/, int /*sc_info*/[][4], int /*dim_h*/, int /*n*/);
extern void constraint_integer_combination(Pbase /*index_base*/, Pcontrainte /*ineq1*/, Pcontrainte /*ineq2*/, int /*rank*/, Variable */*right_var*/, int */*right_rank*/, Value */*right_coeff*/, Variable */*left_var*/, int */*left_rank*/, Value */*left_coeff*/);
/* sc_feasibility.c */
extern bool FM_timeout;
extern bool J_timeout;
extern bool S_timeout;
extern bool sc_rational_feasibility_ofl_ctrl(Psysteme /*sc*/, int /*ofl_ctrl*/, bool /*ofl_res*/);
extern bool sc_integer_feasibility_ofl_ctrl(Psysteme /*sc*/, int /*ofl_ctrl*/, bool /*ofl_res*/);
extern void decision_data(Pcontrainte /*c*/, int volatile */*pc*/, int volatile */*pv*/, Value */*magnitude*/, int /*weight*/);
extern bool sc_feasibility_ofl_ctrl(Psysteme /*sc*/, bool /*integer_p*/, volatile int /*ofl_ctrl*/, volatile bool /*ofl_res*/);
extern bool sc_fourier_motzkin_feasibility_ofl_ctrl(Psysteme /*s*/, bool /*integer_p*/, int /*ofl_ctrl*/);
extern bool sc_fourier_motzkin_feasibility_ofl_ctrl_timeout_ctrl(Psysteme /*sc*/, bool /*int_p*/, int /*ofl_ctrl*/);
extern bool sc_simplexe_feasibility_ofl_ctrl_timeout_ctrl(Psysteme /*sc*/, bool /*project_eq_p*/, bool /*int_p*/, int /*ofl_ctrl*/);
extern bool sc_janus_feasibility_ofl_ctrl_timeout_ctrl(Psysteme /*sc*/, bool /*ofl_ctrl*/);
extern bool efficient_sc_check_inequality_feasibility(Pvecteur /*v*/, Psysteme /*prec*/);
/* sc_intersection.c */
extern Psysteme sc_fusion(Psysteme /*s1*/, Psysteme /*s2*/);
extern Psysteme sc_intersection(Psysteme /*s1*/, Psysteme /*s2*/, Psysteme /*s3*/);
extern Psysteme sc_append(Psysteme /*s1*/, Psysteme /*s2*/);
extern Psysteme sc_safe_intersection(Psysteme /*s1*/, Psysteme /*s2*/, Psysteme /*s3*/);
extern Psysteme sc_safe_append(Psysteme /*s1*/, Psysteme /*s2*/);
extern bool sc_intersection_empty_p_ofl(Psysteme /*ps1*/, Psysteme /*ps2*/);
extern Psysteme extract_common_syst(Psysteme /*s1*/, Psysteme /*s2*/);
/* sc_integer_projection.c */
extern bool sc_integer_fourier_motzkin_variable_elimination(Psysteme /*sci*/, Psysteme /*sc*/, Variable /*v*/);
extern Psysteme sc_integer_projection_along_variable(Psysteme /*sci*/, volatile Psysteme /*sc*/, Variable /*v*/);
extern Psysteme sc_integer_projection_along_variables(Psysteme /*fsc*/, Psysteme /*sc*/, Pbase /*index_base*/, Pvecteur /*pv*/, int /*tab_info*/[][4], int /*dim*/, int /*n*/);
/* sc_normalize.c */
extern Pcontrainte find_intermediate_constraints_recursively(Pvecteur /*v*/, Variable /*x*/, Variable /*y*/, Value /*lmpx*/, Value /*lmpy*/, Value /*rmpx*/, Value /*rmpy*/);
extern Pcontrainte find_intermediate_constraints(Pvecteur /*v*/, Variable /*x*/, Variable /*y*/, Value /*lmpx*/, Value /*lmpy*/, Value /*rmpx*/, Value /*rmpy*/);
extern Psysteme sc_bounded_normalization(Psysteme /*ps*/);
extern Psysteme sc_normalize(Psysteme /*ps*/);
extern Psysteme sc_normalize2(volatile Psysteme /*ps*/);
extern Psysteme sc_add_normalize_eq(Psysteme /*ps*/, Pcontrainte /*eq*/);
extern Psysteme sc_add_normalize_ineq(Psysteme /*ps*/, Pcontrainte /*ineq*/);
extern Psysteme sc_safe_normalize(Psysteme /*ps*/);
extern Psysteme sc_strong_normalize(Psysteme /*ps*/);
extern Psysteme sc_strong_normalize3(Psysteme /*ps*/);
extern Psysteme sc_strong_normalize_and_check_feasibility(volatile Psysteme /*ps*/, Psysteme (* /*check_feasibility*/)(Psysteme));
extern Psysteme sc_strong_normalize2(volatile Psysteme /*ps*/);
extern Psysteme sc_strong_normalize4(Psysteme /*ps*/, char *(* /*variable_name*/)(Variable));
extern Psysteme sc_strong_normalize5(Psysteme /*ps*/, char *(* /*variable_name*/)(Variable));
extern Psysteme sc_strong_normalize_and_check_feasibility2(volatile Psysteme /*ps*/, Psysteme (* /*check_feasibility*/)(Psysteme), char *(* /*variable_name*/)(Variable), int /*level*/);
extern void sc_gcd_normalize(Psysteme /*ps*/);
/* sc_build_sc_nredund.c */
extern bool ineq_redund_with_sc_p(Psysteme /*sc*/, Pcontrainte /*ineq*/);
extern bool eq_redund_with_sc_p(Psysteme /*sc*/, Pcontrainte /*eq*/);
extern Psysteme extract_nredund_subsystem(Psysteme /*s1*/, Psysteme /*s2*/);
extern void build_sc_nredund_1pass_ofl_ctrl(Psysteme volatile */*psc*/, int /*ofl_ctrl*/);
extern void sc_safe_build_sc_nredund_1pass(Psysteme volatile */*ps*/);
extern void build_sc_nredund_1pass(Psysteme volatile */*ps*/);
extern void build_sc_nredund_2pass_ofl_ctrl(Psysteme volatile */*psc*/, int /*ofl_ctrl*/);
extern void sc_safe_build_sc_nredund_2pass(Psysteme volatile */*ps*/);
extern void build_sc_nredund_2pass(Psysteme volatile */*psc*/);
extern Psysteme build_integer_sc_nredund(volatile Psysteme /*ps*/, Pbase /*index_base*/, int /*tab_info*/[][4], int /*loop_level*/, int /*dim_h*/, int /*n*/);
extern bool bound_redund_with_sc_p(Psysteme /*sc*/, Pcontrainte /*ineq1*/, Pcontrainte /*ineq2*/, Variable /*var*/);
/* sc_oppose.c */
extern Psysteme sc_oppose(Psysteme /*ps*/);
/* sc_triang_elim_redond.c */
extern Pvecteur highest_rank_pvector(Pvecteur /*v*/, Pbase /*b*/, int */*prank*/);
extern Pcontrainte constraints_sort_with_compare(Pcontrainte /*c*/, Pbase /*sort_base*/, constraint_cmp_func_t /*compare*/, void */*context*/);
extern Pcontrainte contrainte_sort(Pcontrainte /*c*/, Pbase /*base*/, Pbase /*sort_base*/, bool /*inner_first*/, bool /*complex_first*/);
extern Psysteme sc_sort_constraints(Psysteme /*ps*/, Pbase /*base_index*/);
extern Psysteme sc_triang_elim_redund(Psysteme /*ps*/, Pbase /*base_index*/);
extern void move_n_first_constraints(Pcontrainte */*source*/, Pcontrainte */*target*/, int /*n*/);
extern void sc_triang_elim_redund_n_first(Psysteme /*s*/, int /*n*/);
extern Psysteme sc_build_triang_elim_redund(Psysteme /*s*/, Pbase /*indexes*/);
extern Psysteme sc_sort_constraints_simplest_first(Psysteme /*ps*/, Pbase /*base_index*/);
/* sc_elim_redund.c */
extern Psysteme sc_inequations_elim_redund(Psysteme /*ps*/);
extern Psysteme sc_elim_redund(Psysteme /*ps*/);
extern Psysteme sc_safe_elim_redund(Psysteme /*ps*/);
/* sc_elim_simple_redund.c */
extern bool sc_elim_simple_redund_with_eq(Psysteme /*ps*/, Pcontrainte /*eg*/);
extern bool sc_elim_simple_redund_with_ineq(Psysteme /*ps*/, Pcontrainte /*ineg*/);
extern int sc_check_inequality_redundancy(Pcontrainte /*ineq*/, Psysteme /*ps*/);
extern void sc_elim_empty_constraints(Psysteme /*ps*/, bool /*process_equalities*/);
extern Psysteme sc_elim_db_constraints(Psysteme /*ps*/);
extern Psysteme sc_safe_elim_db_constraints(Psysteme /*ps*/);
extern Psysteme sc_elim_double_constraints(Psysteme /*ps*/);
/* sc_insert_eq.c */
extern void insert_ineq_begin_sc(Psysteme /*sc*/, Pcontrainte /*ineq*/);
extern void insert_2ineq_end_sc(Psysteme /*sc*/, Pcontrainte /*ineq*/);
extern void insert_ineq_end_sc(Psysteme /*sc*/, Pcontrainte /*ineq*/);
extern Psysteme sc_equation_add(Psysteme /*sc*/, Pcontrainte /*c*/);
extern Psysteme sc_inequality_add(Psysteme /*sc*/, Pcontrainte /*c*/);
extern Psysteme sc_constraint_add(Psysteme /*sc*/, Pcontrainte /*c*/, bool /*equality*/);
/* sc_transformation.c */
extern void sc_transform_eg_in_ineg(Psysteme /*sc*/);
extern void sc_transform_ineg_in_eg(Psysteme /*sc*/);
extern void sc_find_equalities(Psysteme */*ps*/);
/* sc_var.c */
extern Variable creat_new_var(Psysteme /*ps*/);
extern bool var_in_lcontrainte_p(Pcontrainte /*pc*/, Variable /*var*/);
extern bool var_in_sc_p(Psysteme /*sc*/, Variable /*var*/);
/* sc_eval.c */
extern bool sc_value_of_variable(Psysteme /*ps*/, Variable /*var*/, Value */*pval*/);
extern bool sc_minmax_of_variable(Psysteme /*ps*/, Variable /*var*/, Value */*pmin*/, Value */*pmax*/);
extern void sc_minmax_of_variables(Psysteme /*ps1*/, Psysteme /*ps2*/, Pbase /*b*/);
extern void sc_force_variable_to_zero(Psysteme /*ps*/, Variable /*var*/);
extern bool sc_minmax_of_variable2(volatile Psysteme /*ps*/, Variable /*var*/, Value */*pmin*/, Value */*pmax*/);
/* sc_unaires.c */
extern Psysteme sc_elim_var(Psysteme /*sc*/, Variable /*v*/);
extern void sc_chg_var(Psysteme /*s*/, Variable /*v_old*/, Variable /*v_new*/);
extern void sc_vect_sort(Psysteme /*s*/, int (* /*compare*/)(Pvecteur *, Pvecteur *));
extern void sc_sort(Psysteme /*sc*/, Pbase /*sort_base*/, int (* /*compare*/)(Pvecteur *, Pvecteur *));
extern Pvecteur vect_printout_order(Pvecteur /*v*/, int (* /*compare*/)(Pvecteur *, Pvecteur *));
extern void sc_lexicographic_sort(Psysteme /*sc*/, int (* /*compare*/)(Pvecteur *, Pvecteur *));
extern bool sc_remove_large_coef(Psysteme /*sc*/, Value /*val*/, bool /*equalities*/, bool /*inequalities*/);
/* sc_error.c */
extern void sc_error(char */*name*/, char */*fmt*/, ...);
/* sc_io.c */
extern Psysteme *sc_read(char */*nomfic*/);
extern bool sc_fscan(FILE */*f*/, Psysteme */*ps*/);
extern void sc_dump(Psysteme /*sc*/);
extern void sc_default_dump(Psysteme /*sc*/);
extern void sc_print(Psysteme /*ps*/, get_variable_name_t /*nom_var*/);
extern void sc_fprint(FILE */*fp*/, Psysteme /*ps*/, get_variable_name_t /*nom_var*/);
extern void sc_fprint_for_sc_fscan(FILE */*f*/, Psysteme /*sc*/, char *(* /*nom_var*/)(Variable));
extern void sc_default_dump_to_files(Psysteme /*sc*/, int /*sc_nb*/, char */*directory_name*/);
/* sc_new_loop_bound.c */
extern Psysteme new_loop_bound(Psysteme /*scn*/, Pbase /*base_index*/);
extern Psysteme get_other_constraints(Psysteme */*psyst*/, Pbase /*vars*/);
extern void algorithm_row_echelon_generic(Psysteme /*scn*/, Pbase /*base_index*/, Psysteme */*pcondition*/, Psysteme */*penumeration*/, bool /*redundancy*/);
extern void algorithm_row_echelon(Psysteme /*scn*/, Pbase /*base_index*/, Psysteme */*pcondition*/, Psysteme */*penumeration*/);
extern void sc_set_row_echelon_redundancy(bool /*b*/);
extern void algorithm_tiling(Psysteme /*syst*/, Pbase /*outer*/, Pbase /*inner*/, Psysteme */*pcondition*/, Psysteme */*ptile_enum*/, Psysteme */*piter_enum*/);
/* sc_simplex_feasibility_fixprec.c */
extern void frac_init(frac */*f*/, int /*n*/);
extern void frac_simpl(Value */*a*/, Value */*b*/);
extern void frac_simplifie(frac */*f*/);
extern void frac_div(frac */*x*/, frac /*y*/, frac /*z*/, bool /*ofl_ctrl*/);
extern void frac_mul(frac */*x*/, frac /*y*/, frac /*z*/, bool /*ofl_ctrl*/);
extern void frac_sub(frac */*X*/, frac /*A*/, frac /*B*/, bool /*ofl_ctrl*/);
extern void full_pivot_sioux(frac */*X*/, frac /*A*/, frac /*B*/, frac /*C*/, frac /*D*/, bool /*ofl_ctrl*/);
extern void full_pivot_direct(frac */*X*/, frac /*A*/, frac /*B*/, frac /*C*/, frac /*D*/, bool /*ofl_ctrl*/);
extern void full_pivot(frac */*X*/, frac /*A*/, frac /*B*/, frac /*C*/, frac /*D*/, bool /*ofl_ctrl*/);
extern void partial_pivot_sioux(frac */*X*/, frac /*B*/, frac /*C*/, frac /*D*/, bool /*ofl_ctrl*/);
extern void partial_pivot_direct(frac */*X*/, frac /*B*/, frac /*C*/, frac /*D*/, bool /*ofl_ctrl*/);
extern void partial_pivot(frac */*X*/, frac /*B*/, frac /*C*/, frac /*D*/, bool /*ofl_ctrl*/);
extern void pivot(frac */*X*/, frac /*A*/, frac /*B*/, frac /*C*/, frac /*D*/, bool /*ofl_ctrl*/);
extern bool sc_simplex_feasibility_ofl_ctrl_fixprec(Psysteme /*sc*/, int /*ofl_ctrl*/);
/* sc_simplex_feasibility_mulprec.c */
/* sc_simplex_feasibility.c */
extern bool sc_simplex_feasibility_ofl_ctrl(Psysteme /*sys*/, int /*ofl_ctrl*/);
/* sc_debug.c */
extern int sc_debug_level;
extern int sc_switch_heuristic_flag;
extern void set_sc_debug_level(int /*l*/);
extern void sc_variable_name_push(char *(* /*fun*/)(Variable));
extern void sc_variable_name_pop(void);
extern char *default_variable_to_string(Variable /*v*/);
extern void initialize_sc(char *(* /*var_to_string*/)(Variable));
/* sc_janus_feasibility.c */
extern bool sc_janus_feasibility_fallback(Psysteme /*sc*/);
extern bool sc_janus_feasibility(Psysteme /*sc*/);
extern void set_sc_janus_feasibility(bool (* /*sc_janus_feasibility_fct*/)(Psysteme));
/* sc_belong.c */
extern bool sc_belongs_p(Psysteme /*ps*/, Pvecteur /*v*/);
extern bool sc_internal_p(Psysteme /*ps*/, Pvecteur /*v*/);
/* sc_misc.c */
extern Psysteme sc_restricted_to_variables_transitive_closure(Psysteme /*sc*/, Pbase /*variables*/);
extern bool sc_constrains_variable_p(Psysteme /*sc*/, Variable /*var*/, bool /*is_equations_p*/);
extern bool sc_equations_constrain_variable_p(Psysteme /*sc*/, Variable /*var*/);
extern bool sc_inequalities_constrain_variable_p(Psysteme /*sc*/, Variable /*var*/);
#endif /*  sc_header_included */
