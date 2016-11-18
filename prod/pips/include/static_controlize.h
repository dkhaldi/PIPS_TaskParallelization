/* Warning! Do not modify this file that is automatically generated! */
/* Modify src/Libs/static_controlize/static_controlize-local.h instead, to add your own modifications. */

/* header file built by cproto */

#ifndef  static_controlize_header_included
#define  static_controlize_header_included
/*

  $Id: static_controlize-local.h 23065 2016-03-02 09:05:50Z coelho $

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
#define STATIC_CONTROLIZE_MODULE_NAME 	"STATCON"
#define NLC_PREFIX 			"NLC"
#define NSP_PREFIX 			"NSP"
#define NUB_PREFIX			"NUB"

#define give_entity(n)	gen_find_tabulated(make_entity_fullname( \
				TOP_LEVEL_MODULE_NAME, n), entity_domain)
#define ENTITY_GE   give_entity(GREATER_OR_EQUAL_OPERATOR_NAME)
#define ENTITY_GT   give_entity(GREATER_THAN_OPERATOR_NAME)
#define ENTITY_LE   give_entity(LESS_OR_EQUAL_OPERATOR_NAME)
#define ENTITY_LT   give_entity(LESS_THAN_OPERATOR_NAME)
#define ENTITY_NOT  give_entity(NOT_OPERATOR_NAME)
#define ENTITY_EQ   give_entity(EQUAL_OPERATOR_NAME)
#define ENTITY_NE   give_entity(NOT_EQUAL_OPERATOR_NAME)
#define ENTITY_OR   give_entity(OR_OPERATOR_NAME)
#define ENTITY_AND  give_entity(AND_OPERATOR_NAME)

#define ENTITY_NLC_P(e) (strncmp(entity_local_name(e), NLC_PREFIX, 3) == 0)
#define ENTITY_NSP_P(e) (strncmp(entity_local_name(e), NSP_PREFIX, 3) == 0)
#define ENTITY_NUB_P(e) (strcmp(entity_local_name(e), NUB_PREFIX, 3) == 0)
#define ENTITY_SP_P(ent) \
   (gen_find_eq(ent, Gstructure_parameters) != chunk_undefined)
#define ENTITY_STRICT_LOGICAL_OPERATOR_P(e) \
		( ENTITY_AND_P(e) || \
		  ENTITY_OR_P(e) || \
		  ENTITY_EQUIV_P(e) || \
		  ENTITY_NON_EQUIV_P(e) || \
		  ENTITY_NOT_P(e) )

extern int Gcount_nlc;
extern int Gcount_nsp;
extern int Gcount_nub;
/* prettyprint.c */
extern bool print_code_static_control(const string /*module_name*/);
extern text text_static_control(entity /*module*/, int /*margin*/, statement /*stat*/);
extern text store_sc_text_line(static_control /*sc*/);
extern cons *words_test_list(list /*obj*/);
extern cons *words_loop_list(list /*obj*/);
extern list words_entity_list(list /*obj*/);
/* static_controlize.c */
extern list Gstructure_parameters;
extern statement_mapping Gstatic_control_map;
extern static_control static_controlize_call(call /*c*/);
extern static_control static_controlize_loop(loop /*l*/);
extern static_control static_controlize_forloop(forloop /*fl*/);
extern static_control static_controlize_whileloop(whileloop /*wl*/);
extern list assigned_var;
extern static_control static_controlize_statement(statement /*s*/);
extern static_control static_controlize_unstructured(unstructured /*u*/);
extern bool static_controlize(string /*mod_name*/);
extern list loop_normalize_of_loop(loop /*l*/, hash_table /*fst*/, list */*ell*/, list */*etl*/, list */*swfl*/, int */*Gcount_nlc*/);
extern list loop_normalize_of_statement(statement /*s*/, hash_table /*fst*/, list */*ell*/, list */*etl*/, list */*swfl*/, int */*Gcount_nlc*/);
extern void loop_normalize_of_unstructured(unstructured /*u*/, hash_table /*fst*/, list */*ell*/, list */*etl*/, list */*swfl*/, int */*Gcount_nlc*/);
/* utils.c */
extern list stco_same_loops(statement_mapping /*in_map*/, statement /*in_s*/, statement /*in_s2*/);
extern int stco_renumber_code(statement /*in_st*/, int /*in_ct*/);
extern expression sc_opposite_exp_of_conjunction(expression /*exp*/, list */*ell*/);
extern bool splc_positive_relation_p(expression /*exp*/, list */*ell*/);
extern list ndf_normalized_test(expression /*exp*/, list */*ell*/);
extern expression normalize_test_leaves(expression /*exp*/, list */*ell*/);
extern expression sc_conditional(expression /*exp*/, list */*ell*/);
extern list loops_to_indices(list /*l*/);
extern bool splc_linear_expression_p(expression /*exp*/, list */*ell*/);
extern bool splc_linear_expression_list_p(list /*l*/, list */*ell*/);
extern bool splc_linear_access_to_arrays_p(list /*l*/, list */*ell*/);
extern string print_structurals(list /*l*/);
extern list sc_list_of_exp_dup(list /*l*/);
extern list sc_list_of_entity_dup(list /*l*/);
extern list sc_list_of_loop_dup(list /*l*/);
extern loop sc_loop_dup(loop /*l*/);
extern list make_undefined_list(void);
extern int in_forward_defined(entity /*ent*/, list */*swfl*/);
extern bool in_forward_defined_p(entity /*ent*/, list */*swfl*/);
extern void verify_structural_parameters(list /*the_list*/, list */*swfl*/);
extern list sc_entity_to_formal_integer_parameters(entity /*f*/);
extern bool sp_linear_expression_p(expression /*exp*/);
extern bool splc_feautrier_expression_p(expression /*exp*/, list */*ell*/);
extern bool sp_feautrier_expression_p(expression /*exp*/);
extern entity sp_feautrier_scalar_assign_call(call /*c*/);
extern bool get_sp_of_call_p(call /*c*/, hash_table /*fst*/, list */*swfl*/);
extern void forward_substitute_in_anyloop(void */*pl*/, hash_table /*fst*/);
extern void forward_substitute_in_exp(expression */*pe*/, hash_table /*fst*/);
extern void forward_substitute_in_call(call */*pc*/, hash_table /*fst*/);
extern bool normalizable_loop_p(loop /*l*/);
extern bool normalizable_loop_p_retrieved(loop /*l*/);
extern bool is_expression_in_list(expression /*exp*/, list /*l*/);
extern bool get_reference_assignments(statement /*s*/, list */*l*/);
#endif /*  static_controlize_header_included */
