/* Warning! Do not modify this file that is automatically generated! */
/* Modify src/Libs/complexity/complexity-local.h instead, to add your own modifications. */

/* header file built by cproto */

#ifndef  complexity_header_included
#define  complexity_header_included
/*

  $Id: complexity-local.h 23065 2016-03-02 09:05:50Z coelho $

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
/*
 *
 *  COMPLEXITY EVALUATION    P. Berthomier   21-08-90
 *
 *                           L. Zhou         21-03-90
 *
 * Modifications:
 *  - deletion of includes in this include file; Francois Irigoin,
 *    13 March 1991
 *
 *  - deletion of #define for operators ;
 *    (all the operators and the instrinsics are defined inside of ri-util-local.h); Molka Becher, 08.03.2011
 */
#include "matrice.h"

#define COMPLEXITY_PACKAGE_NAME "COMPLEXITY"
#define COMPLEXITY_UNDEFINED complexity_undefined
/*
#define COMPLEXITY_UNDEFINED_SYMBOL "<Complexity undefined>"
*/
#define COMPLEXITY_UNDEFINED_P(c) ((c)==complexity_undefined)
#define COMPLEXITY_NOT_FOUND ((complexity) HASH_UNDEFINED_VALUE)

#define MAX_CONTROLS_IN_UNSTRUCTURED 100

/* pseudo-variable for unknown variables     */
#define UNKNOWN_VARIABLE_NAME "UNKNOWN_VARIABLE"

/* pseudo-variable for default iteration number of a loop */
#define UNKNOWN_RANGE_NAME "UNKNOWN_RANGE"

#define TCST_NAME "_TCST_"

/* Prefix added to a variable name when its value is unknown but has to
 * be used in a complexity formulae
 */
#define UNKNOWN_VARIABLE_VALUE_PREFIX "U_"

/* defined complexity data file names here. LZ 13/03/92 */
#define COST_DATA "operation index memory trigo transcend overhead"

/* defines for "complexity_fprint" calls */
#define DO_PRINT_STATS true                 
#define DONT_PRINT_STATS false           
#define PRINT_LOCAL_NAMES true
#define PRINT_GLOBAL_NAMES false

#define HASH_LOOP_INDEX ((char *) 4)     /* Used as `value' field in the hash-table */
#define HASH_USER_VARIABLE ((char *) 8)  /* "hash_complexity_parameters"... useful? */
#define HASH_FORMAL_PARAM ((char *) 12)
#define HASH_COMMON_VARIABLE ((char *) 16) /* used for variable in common. LZ 04/12/91 */

#define ZERO_BYTE 0                      
#define INT_NBYTES 4                     /* number of bytes used by a standard int        */
#define FLOAT_NBYTES 4                   /* number of bytes used by a single-precision    */
#define DOUBLE_NBYTES 8                  /* number of bytes used by a double-precision    */
#define COMPLEX_NBYTES 2*FLOAT_NBYTES    /* complex, single-precision */
#define DCOMPLEX_NBYTES 2*DOUBLE_NBYTES  /* complex, double-precision */
#define MAKE_INT_BASIC make_basic(is_basic_int, (void *) INT_NBYTES)
#define MAKE_ADDRESS_BASIC make_basic(is_basic_int, (void *) DEFAULT_POINTER_TYPE_SIZE)
#define MAKE_FLOAT_BASIC make_basic(is_basic_float, (void *) FLOAT_NBYTES)
#define MAKE_DOUBLE_BASIC make_basic(is_basic_float, (void *) DOUBLE_NBYTES)
#define MAKE_COMPLEX_BASIC make_basic(is_basic_complex, (void *) COMPLEX_NBYTES)
#define MAKE_DCOMPLEX_BASIC make_basic(is_basic_complex, (void *) DCOMPLEX_NBYTES)
#define MAKE_STRING_BASIC make_basic(is_basic_string, make_value(is_value_unknown, UU))

#define hash_contains_p(htp, key) (hash_get(htp, key) != HASH_UNDEFINED_VALUE)
#define hash_contains_formal_param_p(htp, key) (hash_get(htp, key) == HASH_FORMAL_PARAM)
#define hash_contains_user_var_p(htp, key) (hash_get(htp, key) == HASH_USER_VARIABLE)
#define hash_contains_common_var_p(htp, key) (hash_get(htp, key) == HASH_COMMON_VARIABLE)
#define hash_contains_loop_index_p(htp, key) (hash_get(htp, key) == HASH_LOOP_INDEX)


/* defines for "expression_to_polynome" parameters */
#define KEEP_SYMBOLS true
#define DONT_KEEP_SYMBOLS false
#define MAXIMUM_VALUE  1
#define MINIMUM_VALUE -1
#define EXACT_VALUE    0
#define TAKE_MAX(m) ((m) == MAXIMUM_VALUE)
#define TAKE_MIN(m) ((m) == MINIMUM_VALUE)
#define KEEP_EXACT(m) ((m) == EXACT_VALUE)

/* Intrinsics costs defines */

typedef struct intrinsic_cost_rec {
    char *name;
    _int min_basic_result;
    _int min_nbytes_result;
    _int int_cost;
    _int float_cost;
    _int double_cost;
    _int complex_cost;
    _int dcomplex_cost;
} intrinsic_cost_record;

#define LOOP_INIT_OVERHEAD "LOOP-INIT-OVERHEAD"
#define LOOP_BRANCH_OVERHEAD "LOOP-BRANCH-OVERHEAD"
#define CONDITION_OVERHEAD "CONDITION-OVERHEAD"

#define CALL_ZERO_OVERHEAD      "CALL-ZERO-OVERHEAD"      
#define CALL_ONE_OVERHEAD       "CALL-ONE-OVERHEAD"       
#define CALL_TWO_OVERHEAD       "CALL-TWO-OVERHEAD"       
#define CALL_THREE_OVERHEAD     "CALL-THREE-OVERHEAD"     
#define CALL_FOUR_OVERHEAD      "CALL-FOUR-OVERHEAD"      
#define CALL_FIVE_OVERHEAD      "CALL-FIVE-OVERHEAD"      
#define CALL_SIX_OVERHEAD       "CALL-SIX-OVERHEAD"       
#define CALL_SEVEN_OVERHEAD     "CALL-SEVEN-OVERHEAD"   

/* TYPE_CAST_COST added to handle cast case ; Molka Becher  */
#define TYPE_CAST_COST  "TypeCast"  

/* the above two lines are added for 6th cost file, overhead. LZ 280993 */
/* overhead is divided into two. init and branch 081093 */

#define MEMORY_READ_NAME "MEMORY-READ"
#define ONE_INDEX_NAME   "ONE-INDEX"    /* to count indexation costs in multi-dim arrays */
#define TWO_INDEX_NAME   "TWO-INDEX"    /* to count indexation costs in multi-dim arrays */
#define THREE_INDEX_NAME "THREE-INDEX"
#define FOUR_INDEX_NAME  "FOUR-INDEX"
#define FIVE_INDEX_NAME  "FIVE-INDEX"
#define SIX_INDEX_NAME   "SIX-INDEX"
#define SEVEN_INDEX_NAME "SEVEN-INDEX"
#define STRING_INTRINSICS_COST 1
#define LOGICAL_INTRINSICS_COST 1

#define DONT_COUNT_THAT     0,   0,   0,   0,  0
#define EMPTY_COST 0,0,0,0,0
#define DISCRIMINE_TYPES    1,  10, 100,1000,10000
#define REAL_INTRINSIC    100, 100, 100, 100, 100
#define DOUBLE_INTRINSIC  200, 200, 200, 200, 200
#define COMPLEX_INTRINSIC 400, 400, 400, 400, 400

#define MEMORY_READ_COST  DONT_COUNT_THAT
#define MEMORY_WRITE_COST DONT_COUNT_THAT
#define PLUS_MINUS_COST   1, 10, 20, 20, 40
/*
#define MULTIPLY_COST     50, 50, 100, 100, 200
#define DIVIDE_COST       50, 50, 100, 100, 200
*/
#define MULTIPLY_COST     PLUS_MINUS_COST
#define DIVIDE_COST       PLUS_MINUS_COST
#define POWER_COST        100, 100, 200, 200, 400

#define TRANSC_COST       REAL_INTRINSIC
#define DTRANSC_COST      DOUBLE_INTRINSIC
#define CTRANSC_COST      COMPLEX_INTRINSIC
#define TRIGO_COST        REAL_INTRINSIC
#define DTRIGO_COST       DOUBLE_INTRINSIC
#define CTRIGO_COST       COMPLEX_INTRINSIC
#define TRIGOH_COST       REAL_INTRINSIC
#define DTRIGOH_COST      DOUBLE_INTRINSIC
#define CTRIGOH_COST      COMPLEX_INTRINSIC

#define TWO_INDEX_COST    DONT_COUNT_THAT
#define THREE_INDEX_COST  DONT_COUNT_THAT
#define FOUR_INDEX_COST   DONT_COUNT_THAT
#define FIVE_INDEX_COST   DONT_COUNT_THAT
#define SIX_INDEX_COST    DONT_COUNT_THAT
#define SEVEN_INDEX_COST  DONT_COUNT_THAT

/* comp_scan.c */
extern hash_table hash_callee_to_complexity;
extern hash_table hash_complexity_parameters;
extern bool complexity_map_undefined_p(void);
extern void set_complexity_map(statement_mapping /*m*/);
extern statement_mapping get_complexity_map(void);
extern void reset_complexity_map(void);
extern void free_complexity_map(void);
extern void make_complexity_map(void);
extern complexity load_statement_complexity(statement /*s*/);
extern void delete_statement_complexity(statement /*s*/);
extern bool statement_complexity_undefined_p(statement /*s*/);
extern void store_statement_complexity(statement /*s*/, complexity /*t*/);
extern void update_statement_complexity(statement /*s*/, complexity /*t*/);
extern bool uniform_complexities(const string /*module_name*/);
extern bool fp_complexities(const string /*module_name*/);
extern bool any_complexities(const string /*module_name*/);
extern bool summary_complexity(const string /*module_name*/);
extern complexity statement_to_complexity(statement /*stat*/, transformer /*precon*/, list /*eff_list*/);
extern complexity instruction_to_complexity(instruction /*instr*/, transformer /*precond*/, list /*effects_list*/);
extern complexity block_to_complexity(list /*block*/, transformer /*precond*/, list /*effects_list*/);
extern complexity test_to_complexity(test /*test_instr*/, transformer /*precond*/, list /*effects_list*/);
extern complexity loop_to_complexity(loop /*loop_instr*/, transformer /*precond*/, list /*effects_list*/);
extern complexity goto_to_complexity(statement /*st*/, transformer /*precond*/, list /*effects_list*/);
extern complexity whileloop_to_complexity(whileloop /*while_instr*/, transformer /*precond*/, list /*effects_list*/);
extern complexity call_to_complexity(call /*call_instr*/, basic */*pbasic*/, transformer /*precond*/, list /*effects_list*/);
extern complexity arguments_to_complexity(list /*exprlist*/, basic */*pbasic*/, transformer /*precond*/, list /*effects_list*/);
extern complexity expression_to_complexity(expression /*expr*/, basic */*pbasic*/, transformer /*precond*/, list /*effects_list*/);
extern complexity subscript_to_complexity(subscript /*sub*/, basic */*pbasic*/, transformer /*precond*/, list /*effects_list*/);
extern complexity syntax_to_complexity(syntax /*s*/, basic */*pbasic*/, transformer /*precond*/, list /*effects_list*/);
extern complexity reference_to_complexity(reference /*ref*/, basic */*pbasic*/, transformer /*precond*/, list /*effects_list*/);
extern complexity indices_to_complexity(list /*exprlist*/, basic */*pbasic*/, transformer /*precond*/, list /*effects_list*/);
extern complexity range_to_complexity(range /*rng*/, transformer /*precond*/, list /*effects_list*/);
/* comp_expr_to_pnome.c */
extern char *noms_var(entity /*e*/);
extern complexity make_complexity_unknown(const char */*name*/);
extern complexity expression_to_complexity_polynome(expression /*expr*/, transformer /*precond*/, list /*effects_list*/, bool /*keep_symbols*/, int /*maximize*/);
extern complexity syntax_to_polynome(syntax /*synt*/, transformer /*precond*/, list /*effects_list*/, bool /*keep_symbols*/, int /*maximize*/);
extern complexity normalized_to_polynome(normalized /*no*/, transformer /*precond*/, list /*effects_list*/, bool /*keep_symbols*/, int /*maximize*/);
extern complexity pvecteur_to_polynome(Pvecteur /*pvect*/, transformer /*precond*/, list /*effects_list*/, bool /*keep_symbols*/, int /*maximize*/);
extern complexity reference_to_polynome(reference /*ref*/, transformer /*precond*/, list /*effects_list*/, bool /*keep_symbols*/, int /*maximize*/);
extern complexity range_to_polynome(range /*rg*/, transformer /*precond*/, list /*effects_list*/, bool /*keep_symbols*/, int /*maximize*/);
extern complexity call_to_polynome(call /*call_instr*/, transformer /*precond*/, list /*effects_list*/, bool /*keep_symbols*/, int /*maximize*/);
extern complexity cast_to_polynome(cast /*cast_instr*/, transformer /*precond*/, list /*effects_list*/, bool /*keep_symbols*/, int /*maximize*/);
extern complexity plus_op_handler(list /*args*/, transformer /*precond*/, list /*effects_list*/, bool /*keep_symbols*/, int /*maximize*/);
extern complexity minus_op_handler(list /*args*/, transformer /*precond*/, list /*effects_list*/, bool /*keep_symbols*/, int /*maximize*/);
extern complexity multiply_op_handler(list /*args*/, transformer /*precond*/, list /*effects_list*/, bool /*keep_symbols*/, int /*maximize*/);
extern complexity field_op_handler(list /*args*/, transformer /*precond*/, list /*effects_list*/, bool /*keep_symbols*/, int /*maximize*/);
extern complexity unary_minus_op_handler(list /*args*/, transformer /*precond*/, list /*effects_list*/, bool /*keep_symbols*/, int /*maximize*/);
extern complexity unary_plus_op_handler(list /*args*/, transformer /*precond*/, list /*effects_list*/, bool /*keep_symbols*/, int /*maximize*/);
extern complexity divide_op_handler(list /*args*/, transformer /*precond*/, list /*effects_list*/, bool /*keep_symbols*/, int /*maximize*/);
extern complexity power_op_handler(list /*args*/, transformer /*precond*/, list /*effects_list*/, bool /*keep_symbols*/, int /*maximize*/);
extern complexity evaluate_var_to_complexity(entity /*var*/, transformer /*precond*/, list /*effects_list*/, int /*maximize*/);
extern complexity simplify_sc_to_complexity(Psysteme /*ps*/, Variable /*var*/);
/* comp_unstr.c */
extern complexity unstructured_to_complexity(unstructured /*unstr*/, transformer /*precond*/, list /*effects_list*/);
extern void controls_to_hash_table(control /*cont*/, int */*pn_controls*/, control /*control_array*/[], hash_table /*hash_control_to_complexity*/, transformer /*precond*/, list /*effects_list*/);
extern int control_element_position_in_control_array(control /*cont*/, control /*control_array*/[], int /*n_controls*/);
extern matrice average_probability_matrix(unstructured /*unstr*/, int /*n_controls*/, control /*control_array*/[]);
extern void node_successors_to_matrix(control /*cont*/, matrice /*P*/, int /*n_controls*/, control /*control_array*/[], bool /*already_examined*/[]);
/* comp_util.c */
extern bool complexity_check(complexity /*comp*/);
extern void complexity_check_and_warn(const char */*s*/, complexity /*comp*/);
extern void good_complexity_assert(string /*function*/, complexity /*comp*/);
extern complexity complexity_dup(complexity /*comp*/);
extern void complexity_rm(complexity */*pcomp*/);
extern char *complexity_sprint(complexity /*comp*/, bool /*print_stats_p*/, bool /*print_local_names_p*/);
extern void complexity_fprint(FILE */*fd*/, complexity /*comp*/, bool /*print_stats_p*/, bool /*print_local_names_p*/);
extern void complexity_dump(complexity /*comp*/);
extern void prc(complexity /*comp*/);
extern void prp(Ppolynome /*pp*/);
extern void prv(Pvecteur /*pv*/);
extern void fprint_statement_complexity(entity /*module*/, statement /*stat*/, hash_table /*hash_statement_to_complexity*/);
extern intrinsic_cost_record intrinsic_cost_table[];
extern void fprint_cost_table(FILE */*fd*/);
extern void init_cost_table(void);
extern void load_cost_file(FILE */*fd*/, double /*file_factor*/);
extern int intrinsic_cost(const char */*s*/, basic */*pargsbasic*/);
extern float constant_entity_to_float(entity /*e*/);
extern void trace_on(char */*fmt*/, ...);
extern void trace_off(void);
extern bool is_linear_unstructured(unstructured /*unstr*/);
extern list entity_list_reverse(list /*l*/);
extern void add_formal_parameters_to_hash_table(entity /*mod*/, hash_table /*hash_complexity_params*/);
extern void remove_formal_parameters_from_hash_table(entity /*mod*/, hash_table /*hash_complexity_params*/);
extern hash_table free_callees_complexities(hash_table /*h*/);
extern hash_table fetch_callees_complexities(char */*module_name*/);
extern hash_table fetch_complexity_parameters(char */*module_name*/);
extern void add_common_variables_to_hash_table(entity /*module*/, hash_table /*hash_complexity_params*/);
extern void remove_common_variables_from_hash_table(entity /*module*/, hash_table /*hash_complexity_params*/);
extern bool is_must_be_written_var(list /*effects_list*/, char */*var_name*/);
extern complexity final_statement_to_complexity_evaluation(complexity /*comp*/, transformer /*precond*/, list /*effects_list*/);
extern complexity translate_complexity_from_local_to_current_name(complexity /*callee_comp*/, string /*oldname*/, string /*newname*/);
extern bool complexity_is_monomial_p(complexity /*c*/);
extern int complexity_degree(complexity /*c*/);
/* comp_math.c */
extern complexity complexity_sigma(complexity /*comp*/, Variable /*index*/, complexity /*clower*/, complexity /*cupper*/);
extern complexity complexity_var_subst(complexity /*comp*/, Variable /*var*/, complexity /*compsubst*/);
extern complexity polynome_to_new_complexity(Ppolynome /*pp*/);
extern complexity make_single_var_complexity(double /*f*/, Variable /*var*/);
extern complexity make_constant_complexity(double /*f*/);
extern complexity make_zero_complexity(void);
extern bool complexity_zero_p(complexity /*comp*/);
extern bool complexity_constant_p(complexity /*comp*/);
extern bool complexity_unknown_p(complexity /*comp*/);
extern float complexity_TCST(complexity /*comp*/);
extern void complexity_scalar_mult(complexity */*pcomp*/, double /*f*/);
extern void complexity_stats_add(complexity */*pcomp1*/, complexity /*comp2*/);
extern void complexity_add(complexity */*pcomp1*/, complexity /*comp2*/);
extern void complexity_sub(complexity */*pcomp1*/, complexity /*comp2*/);
extern void complexity_mult(complexity */*pcomp1*/, complexity /*comp2*/);
extern void complexity_div(complexity */*pcomp1*/, complexity /*comp2*/);
extern void complexity_polynome_add(complexity */*pcomp*/, Ppolynome /*pp*/);
extern void complexity_float_add(complexity */*pcomp*/, double /*f*/);
extern Ppolynome complexity_polynome(complexity /*comp*/);
extern complexity replace_formal_parameters_by_real_ones(complexity /*comp*/, entity /*mod*/, list /*args*/, transformer /*precond*/, list /*effects_list*/);
extern list list_ith_element(list /*thelist*/, int /*ith*/);
/* comp_prettyprint.c */
extern bool print_code_complexities(const string /*module_name*/);
extern bool print_code_as_a_graph_complexities(const string /*mod_name*/);
extern bool print_source_complexities(const string /*module_name*/);
extern bool print_call_graph_with_complexities(const string /*module_name*/);
extern bool print_icfg_with_complexities(const string /*module_name*/);
extern bool print_icfg_with_loops_complexities(const string /*module_name*/);
extern bool print_icfg_with_control_complexities(const string /*module_name*/);
/* polynome_ri.c */
extern char *variable_name(Variable /*var*/);
extern char *variable_local_name(Variable /*var*/);
extern bool is_inferior_var(Variable /*var1*/, Variable /*var2*/);
extern int is_inferior_varval(Pvecteur /*varval1*/, Pvecteur /*varval2*/);
extern int is_inferior_pvarval(Pvecteur */*pvarval1*/, Pvecteur */*pvarval2*/);
extern Variable name_to_variable(char */*name*/);
extern Variable local_name_to_variable(char */*name*/);
/* comp_matrice.c */
extern void lu_decomposition(float */*a*/, int /*n*/, int */*indx*/, int */*pd*/);
extern void lu_back_substitution(float */*a*/, int /*n*/, int */*indx*/, float */*b*/);
extern void float_matrice_inversion(float */*a*/, int /*n*/, int */*indx*/, int */*pd*/);
#endif /*  complexity_header_included */
