/* Warning! Do not modify this file that is automatically generated! */
/* Modify src/Libs/phrase/phrase-local.h instead, to add your own modifications. */

/* header file built by cproto */

#ifndef  phrase_header_included
#define  phrase_header_included
/*

  $Id: phrase-local.h 23065 2016-03-02 09:05:50Z coelho $

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

#ifndef __PHRASEC_LOCAL_H__
#define __PHRASEC_LOCAL_H__

#include "dg.h"
typedef dg_arc_label arc_label;
typedef dg_vertex_label vertex_label;

#include "graph.h"
#endif 
/* comEngine_optimization_function.c */
extern hash_table gLoopToOpt;
extern statement comEngine_opt_loop_interchange(statement /*stat*/, statement /*innerStat*/, entity /*newInd*/);
/* comEngine_HRE_distribute.c */
extern expression get_fifoExp_from_ref(reference /*curRef*/, expression /*buffExp*/, hash_table /*ht*/);
extern statement generate_fifo_stat2(reference /*curRef*/, bool /*bRead*/);
extern statement generate_ind_fifo_stat2(entity /*oldInd*/, entity /*newInd*/, bool /*bRead*/);
extern void generate_fifo_stats2(list /*lRef*/, list */*lReadStats*/, list */*lWriteStats*/);
extern statement HRE_distribute(statement /*stat*/, string /*new_module_name*/, const char */*module_name*/);
/* comEngine_generate_code.c */
extern hash_table gLoopToOuterInd;
extern bool gGenHRE;
extern list glToggleInitStats;
extern entity comEngine_make_new_scalar_variable(const char */*prefix*/, basic /*bas*/);
extern statement make_toggle_init_statement(entity /*toggleEnt*/);
extern statement make_toggle_inc_statement(entity /*toggleEnt*/, int /*val*/);
extern statement generate_code_function(statement /*stat*/, bool /*bCalledFromSeq*/);
extern statement comEngine_generate_code(statement /*stat*/);
/* phrase_remove_dependences.c */
extern bool phrase_remove_dependences(const char */*module_name*/);
/* comEngine_generate_HRECode.c */
extern hash_table gRefToHREVar;
extern expression get_fifo_from_ref(reference /*ref*/);
extern entity get_HRE_buff_ent_from_ref(reference /*ref*/);
extern statement make_wait_step_statement(void);
extern void replace_array_ref_with_fifos(list /*lRef*/, expression /*buffIndExp*/, entity /*ind*/, statement */*newStat*/);
extern statement generate_stat_from_ref_list_HRE(list /*lRef*/, statement /*stat*/);
extern list generate_stat_from_ref_list_HRE_list(list /*lRef*/, list /*lInStats*/);
extern void get_supportedRef_HRE(statement /*stat*/, list */*lSupportedRef*/, list */*lUnSupportedRef*/);
extern void process_replacement_HRE(list /*lRef*/, expression /*buffIndExp*/, statement */*stat*/);
extern list process_replacement_HRE_OutRef(list /*lRef*/, list /*lStats*/);
extern statement get_call_stat_HRE(statement /*stat*/);
extern list make_loop_lStats_HRE(statement /*stat*/, entity /*transferSize*/, statement /*innerStat*/, entity /*newOuterInd*/, list /*lSupportedRef*/, hash_table /*htOffset*/, expression /*bufferSizeExp*/);
extern statement generate_code_test_HRE(statement /*stat*/);
extern list process_gLoopToSync_HRE(statement /*stat*/, list /*lInStats*/);
extern statement comEngine_generate_HRECode(statement /*externalized_code*/, string /*new_module_name*/, list /*l_in*/, list /*l_out*/, list /*l_params*/, list /*l_priv*/, const char */*module_name*/, int /*hreMemSize*/);
/* comEngine_generate_procCode.c */
extern bool has_call_stat_inside(statement /*stat*/);
extern statement make_step_inc_statement(int /*incNum*/);
extern statement make_loop_step_stat(statement /*stat*/, entity /*newOuterInd*/);
extern statement make_toggle_mmcd(entity /*ent*/);
extern statement make_init_newInd_stat(statement /*stat*/, entity /*newInd*/);
extern statement make_transStat(statement /*stat*/, entity /*newOuterInd*/, entity /*transferSize*/, expression /*bufferSizeExp*/);
extern void comEngine_replace_reference_in_stat(statement /*stat*/, reference /*ref*/, expression /*new*/);
extern statement make_exec_mmcd(void);
extern statement generate_stat_from_ref_list_proc(list /*lRef*/, list /*lToggleEnt*/, statement /*stat*/);
extern list generate_stat_from_ref_list_proc_list(list /*lRef*/, list /*lInStats*/);
extern void process_innerStat1_proc(statement /*stat*/, entity /*oldInd*/, entity /*newOuterInd*/, entity /*newInnerInd*/);
extern void get_supportedRef_proc(statement /*stat*/, hash_table /*htOffset*/, list */*lSupportedRef*/, list */*lUnSupportedRef*/);
extern statement get_call_stat_proc(statement /*stat*/);
extern list make_loop_lStats_proc(statement /*stat*/, entity /*transferSize*/, statement /*innerStat*/, entity /*newOuterInd*/, list /*lSupportedRef*/, hash_table /*htOffset*/, expression /*bufferSizeExp*/);
extern list add_index_out_effect_proc(loop /*curLoop*/, list /*lStats*/);
extern statement generate_code_test_proc(statement /*stat*/);
extern list process_gLoopToSync_proc(statement /*stat*/, list /*lInStats*/);
extern void create_realFifo_proc(statement /*stat*/, list /*lRef*/);
extern statement comEngine_generate_procCode(statement /*externalized_code*/, list /*l_in*/, list /*l_out*/);
/* comEngine_feasability.c */
extern list comEngine_expression_to_reference_list(expression /*e*/, list /*lr*/);
extern bool code_has_write_eff_ref_p(reference /*ref*/, statement /*stat*/);
extern list reference_indices_entity_list(reference /*ref*/);
extern bool comEngine_feasability(statement /*externalized_code*/, graph /*dg*/);
/* comEngine_distribute.c */
extern hash_table gLoopToRef;
extern hash_table gStatToRef;
extern hash_table gRefToEff;
extern hash_table gLoopToSync;
extern hash_table gLoopToSupRef;
extern hash_table gLoopToUnSupRef;
extern entity gHREMemory;
extern expression gBufferSizeEnt;
extern int gBufferSize;
extern hash_table gRefToFifo;
extern hash_table gRefToFifoOff;
extern hash_table gRefToHREFifo;
extern hash_table gStatToHtOffset;
extern hash_table gRefToBuffSize;
extern hash_table gIndToNum;
extern hash_table gRefToInd;
extern hash_table gLoopToToggleEnt;
extern hash_table gEntToHREFifo;
extern hash_table gRefToToggle;
extern hash_table gToggleToInc;
extern hash_table gIsNewLoop;
extern void create_HRE_module(const char */*new_module_name*/, const char */*module_name*/, statement /*stat*/, entity /*new_fun*/);
extern void comEngine_distribute(const char */*module_name*/, statement /*module_stat*/, entity /*module*/);
extern bool phrase_comEngine_distributor(const char */*module_name*/);
/* phrase_distributor.c */
extern string get_function_name_by_searching_tag(statement /*stat*/, const char */*tag*/);
extern list identify_analyzed_statements_to_distribute(statement /*stat*/);
extern entity create_private_variable_for_new_module(entity /*a_variable*/, const char */*new_name*/, const char */*new_module_name*/, entity /*module*/);
extern void add_parameter_variable_to_module(reference /*ref*/, entity /*module*/, statement /*stat*/, string /*new_module_name*/, int /*param_nb*/);
extern void add_private_variable_to_module(reference /*ref*/, entity /*module*/, statement /*stat*/, string /*new_module_name*/);
extern bool phrase_distributor_init(const char */*module_name*/);
extern bool phrase_distributor(const char */*module_name*/);
/* phrase_distributor_control_code.c */
extern entity create_parameter_for_new_module(variable /*var*/, const char */*parameter_name*/, const char */*module_name*/, entity /*module*/, int /*param_nb*/);
extern entity create_integer_parameter_for_new_module(const char */*parameter_name*/, const char */*module_name*/, entity /*module*/, int /*param_nb*/);
extern void store_new_module(const char */*module_name*/, entity /*module*/, statement /*module_statement*/);
extern entity create_new_common_variable(string /*name*/, entity /*module*/, entity /*common*/, variable /*var*/);
extern entity create_new_scalar_common_variable(string /*name*/, entity /*module*/, entity /*common*/, basic /*b*/);
extern entity create_new_integer_scalar_common_variable(string /*name*/, entity /*module*/, entity /*common*/);
extern void declare_common_variables_in_module(entity /*common*/, entity /*module*/);
extern string get_controlized_statement_comment(entity /*function*/);
extern string get_in_param_id_name(entity variable, entity /*function*/);
extern string get_out_param_id_name(entity variable, entity /*function*/);
extern string get_function_id_name(entity /*function*/);
extern string get_common_param_name(entity variable, entity /*function*/);
extern string get_send_parameter_module_name(variable /*var*/);
extern string get_receive_parameter_module_name(variable /*var*/);
extern entity entity_in_module(const char */*name*/, entity /*module*/);
extern bool phrase_distributor_control_code(const char */*module_name*/);
/* phrase_distributor_communication.c */
extern entity make_start_ru_module(hash_table /*ht_params*/, statement */*module_statement*/, int /*number_of_deployment_units*/, entity /*global_common*/, list /*l_commons*/);
extern entity make_wait_ru_module(statement */*module_statement*/, int /*number_of_deployment_units*/, entity /*global_common*/, list /*l_commons*/);
extern string get_dynamic_variable_name(entity /*dynamic_variable*/);
extern string get_ref_var_param_name(entity /*reference_param*/);
extern string get_send_param_module_name(entity /*function*/, effect /*reg*/);
extern string get_receive_param_module_name(entity /*function*/, effect /*reg*/);
extern list make_send_scalar_params_modules(hash_table /*ht_in_communications*/, int /*number_of_deployment_units*/, entity /*global_common*/, list /*l_commons*/);
extern list make_receive_scalar_params_modules(hash_table /*ht_out_communications*/, int /*number_of_deployment_units*/, entity /*global_common*/, list /*l_commons*/);
extern void compute_region_variables(effect /*reg*/, list */*l_reg_params*/, list */*l_reg_variables*/);
extern entity create_private_integer_variable_for_new_module(string /*new_name*/, const char */*new_module_name*/, entity /*module*/);
extern list make_send_array_params_modules(entity /*function*/, list /*l_regions*/, entity /*global_common*/, entity /*externalized_fonction_common*/, int /*number_of_deployment_units*/);
extern list make_receive_array_params_modules(entity /*function*/, list /*l_regions*/, entity /*global_common*/, entity /*externalized_fonction_common*/, int /*number_of_deployment_units*/);
/* distribution_context.c */
extern bool compute_distribution_context(list /*l_stats*/, statement /*module_stat*/, entity /*module*/, hash_table */*ht_stats*/, hash_table */*ht_params*/, hash_table */*ht_private*/, hash_table */*ht_in_regions*/, hash_table */*ht_out_regions*/);
extern bool compute_distribution_controlization_context(list /*l_calls*/, statement /*module_stat*/, entity /*module*/, hash_table */*ht_calls*/, hash_table */*ht_params*/, hash_table */*ht_private*/, hash_table */*ht_in_regions*/, hash_table */*ht_out_regions*/);
extern list compute_regions_union(list /*l_in*/, list /*l_out*/);
extern bool internal_compute_distribution_context(statement /*externalized_code*/, hash_table */*ht_params*/, hash_table */*ht_private*/, hash_table */*ht_in_regions*/, hash_table */*ht_out_regions*/, void */*key_value*/);
extern string get_externalizable_function_name(statement /*stat*/);
extern string get_externalized_function_name(statement /*stat*/);
extern string get_externalized_and_analyzed_function_name(statement /*stat*/, int */*stats_nb*/);
extern string variable_to_string(variable /*var*/);
extern void register_scalar_communications(hash_table */*ht_communications*/, entity /*function*/, list /*l_regions*/);
/* fsm_generation.c */
extern bool fsm_generation(const char */*module_name*/);
/* print_code_smalltalk.c */
extern bool print_code_smalltalk(const char */*module_name*/);
/* fsm_merge_states.c */
extern bool fsm_merge_states(const char */*module_name*/);
/* fsm_split_state.c */
extern bool fsm_split_state(const char */*module_name*/);
/* full_fsm_generation.c */
extern bool full_fsm_generation(const char */*module_name*/);
/* loop_spaghettify.c */
extern statement spaghettify_loop(statement /*stat*/, const char */*module_name*/);
/* whileloop_spaghettify.c */
extern statement spaghettify_whileloop(statement /*stat*/, const char */*module_name*/);
/* forloop_spaghettify.c */
extern statement spaghettify_forloop(statement /*stat*/, const char */*module_name*/);
/* test_spaghettify.c */
extern statement spaghettify_test(statement /*stat*/, const char */*module_name*/);
/* spaghettify.c */
extern statement spaghettify_statement(statement /*stat*/, const char */*module_name*/);
extern bool spaghettify(const char */*module_name*/);
/* full_spaghettify.c */
extern bool full_spaghettify(const char */*module_name*/);
/* fsm_tools.c */
extern expression make_expression_with_state_variable(entity /*state_variable*/, int value, string /*intrinsic_name*/);
extern entity create_state_variable(const char */*module_name*/, int /*name_identifier*/);
extern statement make_state_variable_assignement_statement(statement /*stat*/, entity /*state_variable*/, int /*assignement_value*/);
extern int entry_state_variable_value_for_unstructured(statement /*stat*/);
extern int exit_state_variable_value_for_unstructured(statement /*stat*/);
extern statement make_reset_state_variable_statement(statement /*stat*/, entity /*state_variable*/);
extern statement make_transition_statement(control /*current_node*/, statement /*root_statement*/, entity /*state_variable*/, const char */*module_name*/);
extern statement make_fsm_transitions_statement(statement /*stat*/, entity /*state_variable*/, const char */*module_name*/);
extern statement make_fsm_from_statement(statement /*stat*/, entity /*state_variable*/, const char */*module_name*/);
extern statement fsmize_statement(statement /*stat*/, entity /*state_variable*/, const char */*module_name*/);
/* phrase_tools.c */
extern string statement_type_as_string(statement /*stat*/);
extern void debug_statement(const char */*comments*/, statement /*stat*/, int /*debug_level*/);
extern void debug_control(const char */*comments*/, control /*a_control*/, int /*debug_level*/);
extern void debug_unstructured(unstructured /*an_unstructured*/, int /*debug_level*/);
extern void short_debug_unstructured(unstructured /*an_unstructured*/, int /*debug_level*/);
extern entity clone_variable_with_new_name(entity /*a_variable*/, const char */*new_name*/, const char */*module_name*/);
extern entity make_variable_from_name_and_entity(entity /*cloned_variable*/, const char */*base_name*/, statement /*stat*/, const char */*module_name*/);
extern statement make_binary_call_statement(const char */*operator_name*/, expression /*expression1*/, expression /*expression2*/, statement /*stat*/);
extern statement make_assignement_statement(entity /*a_variable*/, expression /*an_expression*/, statement /*stat*/);
extern int beautify_ordering(int /*an_ordering*/);
extern void clean_statement_from_tags(const char */*comment_portion*/, statement /*stat*/);
extern list get_statements_with_comments_containing(const char */*comment_portion*/, statement /*stat*/);
extern bool statement_is_contained_in_a_sequence_p(statement /*root_statement*/, statement /*searched_stat*/);
extern statement sequence_statement_containing(statement /*root_statement*/, statement /*searched_stat*/);
extern void replace_in_sequence_statement_with(statement /*old_stat*/, statement /*new_stat*/, statement /*root_stat*/);
extern list references_for_regions(list /*l_regions*/);
#endif /*  phrase_header_included */
