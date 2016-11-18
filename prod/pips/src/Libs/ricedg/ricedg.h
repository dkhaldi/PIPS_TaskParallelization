/* Warning! Do not modify this file that is automatically generated! */
/* Modify src/Libs/ricedg/ricedg-local.h instead, to add your own modifications. */

/* header file built by cproto */

#ifndef  ricedg_header_included
#define  ricedg_header_included
/*

  $Id: ricedg-local.h 23065 2016-03-02 09:05:50Z coelho $

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
#define INFAISABLE 0
#define FAISABLE 1

/* maximun number of nested loops */
#define MAXDEPTH 9
/* maximum number of scalar variables */
#define MAXSV 1024


/*the variables for the statistics of test of dependence and parallelization */
extern int NbrArrayDepInit;
extern int NbrIndepFind;
extern int NbrAllEquals;
extern int NbrDepCnst;
extern int NbrDepExact;
extern int NbrDepInexactEq;
extern int NbrDepInexactFM;
extern int NbrDepInexactEFM;
extern int NbrScalDep;
extern int NbrIndexDep;
extern int deptype[5][3], constdep[5][3];
extern int NbrTestCnst;
extern int NbrTestGcd;
extern int NbrTestSimple; /* by sc_normalize() */
extern int NbrTestDiCnst;
extern int NbrTestProjEqDi;
extern int NbrTestProjFMDi;
extern int NbrTestProjEq;
extern int NbrTestProjFM;
extern int NbrTestDiVar;
extern int NbrProjFMTotal;
extern int NbrFMSystNonAug;
extern int FMComp[18];
extern bool is_test_exact;
extern bool is_test_inexact_eq;
extern bool is_test_inexact_fm;
extern bool is_dep_cnst;
extern bool is_test_Di;
extern bool Finds2s1;

// counter used by one debug message, defined in ri-util.
extern int Nbrdo;

/* Definition for the dependance_verticies_p function
 */

#define FLOW_DEPENDANCE 1
#define ANTI_DEPENDANCE 2
#define OUTPUT_DEPENDANCE 4
#define INPUT_DEPENDANCE 8






/* util.c */
extern statement vertex_to_statement(vertex /*v*/);
extern int vertex_ordering(vertex /*v*/);
extern int compare_vertex(const void */*v0*/, const void */*v1*/);
extern hash_table compute_ordering_to_dg_mapping(graph /*dependance_graph*/);
extern int vertex_sort_callback(const vertex */*v1*/, const vertex */*v2*/);
extern int successor_sort_callback(const successor */*succ1*/, const successor */*succ2*/);
extern int conflicts_sort_callback(conflict */*c1*/, conflict */*c2*/);
extern void prettyprint_dependence_graph(FILE */*fd*/, statement /*mod_stat*/, graph /*mod_graph*/);
extern void prettyprint_dot_dependence_graph(FILE */*fd*/, statement /*mod_stat*/, graph /*mod_graph*/);
extern void prettyprint_dependence_graph_view(FILE */*fd*/, statement /*mod_stat*/, graph /*mod_graph*/);
extern void print_vect_in_vertice_val(FILE */*fd*/, Pvecteur /*v*/, Pbase /*b*/);
extern void print_dependence_cone(FILE */*fd*/, Ptsg /*dc*/, Pbase /*basis*/);
extern hash_table statements_to_successors(list /*statements*/, graph /*dg*/);
/* contexts.c */
extern statement_mapping contexts_mapping_of_nest(statement /*stat*/);
/* testdep_util.c */
extern entity DiVars[9];
extern entity LiVars[9];
extern entity DsiVars[1024];
extern entity MakeDiVar(int /*l*/);
extern entity GetDiVar(int /*l*/);
extern entity MakeLiVar(int /*l*/);
extern entity GetLiVar(int /*l*/);
extern entity MakeDsiVar(int /*l*/);
extern entity GetDsiVar(int /*l*/);
extern int DiVarLevel(entity /*e*/);
extern void sc_add_di(int /*l*/, entity /*e*/, Psysteme /*s*/, int /*li*/);
extern void sc_add_dsi(int /*l*/, entity /*e*/, Psysteme /*s*/);
extern int sc_proj_on_di(int /*cl*/, Psysteme /*s*/);
extern Pbase MakeDibaseinorder(int /*n*/);
extern int FindMaximumCommonLevel(cons */*n1*/, cons */*n2*/);
extern void ResetLoopCounter(void);
extern entity MakeLoopCounter(void);
extern int dep_type(action /*ac1*/, action /*ac2*/);
extern int sc_proj_optim_on_di_ofl(int /*cl*/, Psysteme */*psc*/);
extern bool sc_faisabilite_optim(Psysteme /*sc*/);
extern Psysteme sc_projection_optim_along_vecteur_ofl(Psysteme /*sc*/, Pvecteur /*pv*/);
extern bool sc_minmax_of_variable_optim(Psysteme volatile /*ps*/, Variable /*var*/, Value */*pmin*/, Value */*pmax*/);
extern Psysteme sc_invers(Psysteme /*ps*/);
extern void vect_chg_var_sign(Pvecteur */*ppv*/, Variable /*var*/);
/* ricedg.c */
extern int NbrArrayDepInit;
extern int NbrIndepFind;
extern int NbrAllEquals;
extern int NbrDepCnst;
extern int NbrTestExact;
extern int NbrDepInexactEq;
extern int NbrDepInexactFM;
extern int NbrDepInexactEFM;
extern int NbrScalDep;
extern int NbrIndexDep;
extern int deptype[5][3];
extern int constdep[5][3];
extern int NbrTestCnst;
extern int NbrTestGcd;
extern int NbrTestSimple;
extern int NbrTestDiCnst;
extern int NbrTestProjEqDi;
extern int NbrTestProjFMDi;
extern int NbrTestProjEq;
extern int NbrTestProjFM;
extern int NbrTestDiVar;
extern int NbrProjFMTotal;
extern int NbrFMSystNonAug;
extern int FMComp[18];
extern bool is_test_exact;
extern bool is_test_inexact_eq;
extern bool is_test_inexact_fm;
extern bool is_dep_cnst;
extern bool is_test_Di;
extern bool Finds2s1;
extern bool context_map_undefined_p(void);
extern void set_context_map(statement_mapping /*m*/);
extern statement_mapping get_context_map(void);
extern void reset_context_map(void);
extern void free_context_map(void);
extern void make_context_map(void);
extern Psysteme load_statement_context(statement /*s*/);
extern void delete_statement_context(statement /*s*/);
extern bool statement_context_undefined_p(statement /*s*/);
extern void store_statement_context(statement /*s*/, Psysteme /*t*/);
extern void update_statement_context(statement /*s*/, Psysteme /*t*/);
extern bool rice_fast_dependence_graph(char */*mod_name*/);
extern bool rice_full_dependence_graph(char */*mod_name*/);
extern bool rice_semantics_dependence_graph(char */*mod_name*/);
extern bool rice_regions_dependence_graph(char */*mod_name*/);
extern list TestCoupleOfReferences(list /*n1*/, Psysteme /*sc1*/, statement /*s1*/, effect /*ef1*/, reference /*r1*/, list /*n2*/, Psysteme /*sc2*/, statement /*s2*/, effect /*ef2*/, reference /*r2*/, list /*llv*/, Ptsg */*gs*/, list */*levelsop*/, Ptsg */*gsop*/);
extern void writeresult(char */*mod_name*/);
extern graph compute_dg_on_statement_from_chains_in_place(statement /*s*/, graph /*chains*/);
extern graph compute_dg_on_statement_from_chains(statement /*s*/, graph /*chains*/);
/* prettyprint.c */
extern bool print_whole_dependence_graph(const string /*mod_name*/);
extern bool print_filtered_dependence_graph(const string /*mod_name*/);
extern bool print_filtered_dependence_daVinci_graph(const string /*mod_name*/);
extern bool print_effective_dependence_graph(const string /*mod_name*/);
extern bool print_loop_carried_dependence_graph(const string /*mod_name*/);
extern bool print_dependence_graph(string /*name*/);
extern bool print_chains_graph(string /*name*/);
extern bool print_dot_chains_graph(string /*name*/);
extern bool print_dot_dependence_graph(string /*name*/);
/* quick_privatize.c */
extern void quick_privatize_graph(graph /*dep_graph*/);
/* trace.c */
extern vertex get_vertex_in_list(list /*in_l*/, string /*in_s*/);
extern void prettyprint_graph_text(FILE */*out_f*/, list /*l_of_vers*/);
extern void prettyprint_graph_daVinci(FILE */*out_f*/, list /*l_of_vers*/);
extern list make_filtered_dg_or_dvdg(statement /*mod_stat*/, graph /*mod_graph*/);
extern bool print_filtered_dg_or_dvdg(string /*mod_name*/, bool /*is_dv*/);
/* impact_check.c */
extern bool find_covering_reference_path(set /*arcs_processed_set*/, statement /*s_src*/, action /*act_src*/, entity /*ent_src*/, statement /*s_dest*/, action /*act_dest*/, entity /*ent_dest*/);
extern bool check_way_between_two_statements(statement /*s1*/, statement /*s2*/, graph /*g*/);
extern list union_list(list /*l1*/, list /*l2*/);
extern bool impact_check(char */*module_name*/);
#endif /*  ricedg_header_included */
