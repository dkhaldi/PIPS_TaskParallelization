/* Warning! Do not modify this file that is automatically generated! */
/* Modify src/Libs/paf-util/paf-util-local.h instead, to add your own modifications. */

/* header file built by cproto */

#ifndef  paf_util_header_included
#define  paf_util_header_included
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
/* adg_read_paf.c */
extern graph dfg;
extern list stmt_list;
extern list loop_list;
extern graph adg_read_paf(char */*s*/);
extern void init_new_dfg(void);
extern void new_param(string /*s*/);
extern void init_new_df_sink_ins(void);
extern void init_new_df_source(char */*s_ins*/);
extern void new_df_trans_exp(void);
extern void finish_new_df_source(void);
extern void init_new_df_gov_pred(void);
extern void save_pred(int /*option*/);
extern void elim_last_pred(void);
extern void new_df_gov_pred(void);
extern void init_new_df_ref(char */*s_ref*/);
extern void save_int(int /*i*/);
extern void save_id(string /*s*/);
extern void init_op_name(string /*op_name*/);
extern void init_op_exp(string /*op_name*/);
extern void save_exp(void);
extern void new_df_ref_ind(string /*s_ind*/);
extern void finish_new_df_ref(void);
extern void new_df_sink_ins(char */*s_ins*/);
extern void init_new_do_loop(char */*s_loop*/);
extern void init_loop_ctrl(char */*s_ind*/);
extern void lbound_exp(void);
extern void step_exp(void);
extern void ubound_exp(void);
extern void finish_new_do_loop(void);
extern void init_new_gd_ins(char */*s_ins*/);
extern void new_eng_loop(char */*s_loop*/);
extern void finish_new_gd_ins(void);
/* bdt_read_paf.c */
extern bdt base;
extern bdt bdt_read_paf(char */*s*/);
extern bool same_predicate_p(predicate /*p1*/, predicate /*p2*/);
extern void reorganize_bdt(bdt /*base*/);
extern void bdt_init_new_base(void);
extern void bdt_init_new_ins(char */*s_ins*/);
extern void bdt_new_shedule(string /*s_func*/);
extern void bdt_save_pred(int /*option*/);
extern void bdt_elim_last_pred(void);
extern void bdt_save_int(int /*i*/);
extern void bdt_save_id(string /*s*/);
extern void bdt_init_op_exp(string /*op_name*/);
extern void bdt_save_exp(void);
/* utils.c */
extern void pu_matrices_to_contraintes(Pcontrainte */*pc*/, Pbase /*b*/, matrice /*A*/, matrice /*B*/, int /*n*/, int /*m*/);
extern void pu_contraintes_to_matrices(Pcontrainte /*pc*/, Pbase /*b*/, matrice /*A*/, matrice /*B*/, int /*n*/, int /*m*/);
extern void contraintes_with_sym_cst_to_matrices(Pcontrainte /*pc*/, Pbase /*index_base*/, Pbase /*const_base*/, matrice /*A*/, matrice /*B*/, int /*n*/, int /*m1*/, int /*m2*/);
extern void matrices_to_contraintes_with_sym_cst(Pcontrainte */*pc*/, Pbase /*index_base*/, Pbase /*const_base*/, matrice /*A*/, matrice /*B*/, int /*n*/, int /*m1*/, int /*m2*/);
extern vertex in_dfg_vertex_list(list /*l*/, vertex /*v*/);
extern vertex in_dg_vertex_list(list /*l*/, vertex /*v*/);
extern expression make_id_expression(string /*s*/);
extern expression make_array_ref(list /*l*/);
extern expression make_func_op(string /*func_name*/, list /*args*/);
extern expression lisp_exp_to_ri_exp(lisp_expression /*le*/);
extern expression negate_expression(expression /*exp*/);
extern predicate expressions_to_predicate(list /*exp_l*/);
extern int vertex_int_stmt(vertex /*v*/);
extern void comp_exec_domain(graph /*g*/, hash_table /*STS*/);
extern Psysteme make_expression_equalities(list /*le*/);
extern Pbase make_base_of_nest(int /*stmt*/);
extern successor first_succ_of_vertex(vertex /*v*/);
extern dataflow first_df_of_succ(successor /*s*/);
extern loop loop_dup(loop /*l*/);
extern list static_control_to_indices(static_control /*stct*/);
extern Pvecteur polynome_to_vecteur(Ppolynome /*pp*/);
extern Pcontrainte polynome_to_contrainte(Ppolynome /*pp*/);
extern Psysteme old_polynome_to_sc(Ppolynome /*pp*/, list /*l*/);
extern Psysteme polynome_to_sc(Ppolynome /*pp*/, list /*l*/);
extern void substitute_var_with_vec(Psysteme /*ps*/, entity /*var*/, Value /*val*/, Pvecteur /*vec*/);
extern bool is_entity_in_list_p(entity /*e*/, list /*l*/);
extern Psysteme elim_var_with_eg(Psysteme /*ps*/, list */*init_l*/, list */*elim_l*/);
extern Psysteme better_elim_var_with_eg(Psysteme /*ps*/, list */*init_l*/, list */*elim_l*/);
extern bool single_var_vecteur_p(Pvecteur /*pv*/);
extern list vecteur_to_list(Pvecteur /*v*/);
extern Ppolynome old_vecteur_to_polynome(Pvecteur /*vec*/);
extern list meld(list /*l1*/, list /*l2*/, bool (* /*compare_obj*/)(void));
extern list new_general_merge_sort(list /*l*/, bool (* /*compare_obj*/)(void));
extern list general_merge_sort(list /*l*/, bool (* /*compare_obj*/)(void));
extern expression rational_op_exp(string /*op_name*/, expression /*exp1*/, expression /*exp2*/);
extern Pvecteur vect_var_subst(Pvecteur /*vect*/, Variable /*var*/, Pvecteur /*new_vect*/);
extern Ppolynome prototype_var_subst(Ppolynome /*pp*/, Variable /*var*/, Ppolynome /*ppsubst*/);
extern Ppolynome vecteur_mult(Pvecteur /*v1*/, Pvecteur /*v2*/);
extern Pvecteur prototype_factorize(Ppolynome /*pp*/, Variable /*var*/);
extern Pcontrainte simplify_minmax_contrainte(Pcontrainte /*pc*/, Psysteme /*ps_cont*/, int /*min_or_max*/);
extern list vectors_to_expressions(Pcontrainte /*pc*/);
extern Pcontrainte expressions_to_vectors(list /*lexp*/);
extern list simplify_minmax(list /*lexp*/, Psysteme /*ps_cont*/, int /*min_or_max*/);
extern Psysteme find_implicit_equation(Psysteme /*ps*/);
extern void set_current_stco_map(statement_mapping /*scm*/);
extern statement_mapping get_current_stco_map(void);
extern void reset_current_stco_map(void);
extern static_control get_stco_from_current_map(statement /*s*/);
extern expression make_rational_exp(Pvecteur /*v*/, Value /*d*/);
extern int stco_common_loops_of_statements(statement_mapping /*in_map*/, statement /*in_s*/, statement /*in_s2*/);
/* print.c */
extern void pu_inegalite_fprint(FILE */*fp*/, Pcontrainte /*ineg*/, const char *(* /*variable_name*/)(entity));
extern void pu_egalite_fprint(FILE */*fp*/, Pcontrainte /*eg*/, const char *(* /*variable_name*/)(entity));
extern void vecteur_fprint(FILE */*fp*/, Pcontrainte /*vec*/, const char *(* /*variable_name*/)(entity));
extern void fprint_dataflow(FILE */*fp*/, int /*stmt*/, dataflow /*df*/);
extern void fprint_pred(FILE */*fp*/, predicate /*pred*/);
extern void fprint_psysteme(FILE */*fp*/, Psysteme /*ps*/);
extern void fprint_sc_pvecteur(FILE */*fp*/, Psysteme /*ps*/);
extern void fprint_bdt(FILE */*fp*/, bdt /*obj*/);
extern const char *pu_variable_name(Variable /*v*/);
extern bool pu_is_inferior_var(Variable /*v1*/, Variable /*v2*/);
extern void pu_vect_fprint(FILE */*fp*/, Pvecteur /*v*/);
extern void fprint_indent(FILE */*fp*/, int /*indent*/);
extern void imprime_quast(FILE */*fp*/, quast /*qu*/);
#endif /*  paf_util_header_included */
