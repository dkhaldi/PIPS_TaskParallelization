/* Warning! Do not modify this file that is automatically generated! */
/* Modify src/Libs/control/control-local.h instead, to add your own modifications. */

/* header file built by cproto */

#ifndef  control_header_included
#define  control_header_included
/*

  $Id: control-local.h 23065 2016-03-02 09:05:50Z coelho $

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
/* -- control.h */

#ifndef CONTROL_INCLUDED
#define CONTROL_INCLUDED

/* Define the environment variables used to select which controlizer
   version to use independently of which one was activated at the pipsmake
   level: */
/* The name of the one to force the use of the new controlizer: */
#define USE_NEW_CONTROLIZER_ENV_VAR_NAME "PIPS_USE_NEW_CONTROLIZER"
/* The name of the one to force the use of the old controlizer: */
#define USE_OLD_CONTROLIZER_ENV_VAR_NAME "PIPS_USE_OLD_CONTROLIZER"
#endif
/* controlizer.c */
extern char vcid_control_controlizer[];
extern statement unsugared_loop_header(statement /*sl*/);
extern statement unsugared_forloop_header(statement /*sl*/);
extern statement unsugared_whileloop_header(statement /*sl*/);
extern statement unsugared_loop_test(statement /*sl*/);
extern statement unsugared_forloop_test(statement /*sl*/);
extern statement unsugared_whileloop_test(statement /*sl*/);
extern statement unsugared_loop_inc(statement /*sl*/);
extern statement unsugared_forloop_inc(statement /*sl*/);
extern control find_exit_control_node(list /*ctls*/, control /*succ*/);
extern control find_or_create_exit_control_node(list /*ctls*/, control /*succ*/);
extern bool controlize_statement(control /*c_res*/, control /*succ*/, hash_table /*used_labels*/);
extern statement hcfg(statement /*st*/);
/* old_controlizer.c */
extern char vcid_control_old_controlizer[];
extern statement loop_header(statement /*sl*/);
extern statement loop_test(statement /*sl*/);
extern statement loop_inc(statement /*sl*/);
extern statement forloop_header(statement /*sl*/);
extern statement forloop_test(statement /*sl*/);
extern statement forloop_inc(statement /*sl*/);
extern unstructured control_graph(statement /*st*/);
/* graph.c */
extern bool ctrl_graph_undefined_p(void);
extern void reset_ctrl_graph(void);
extern void error_reset_ctrl_graph(void);
extern void set_ctrl_graph(controlmap /*o*/);
extern controlmap get_ctrl_graph(void);
extern void init_ctrl_graph(void);
extern void close_ctrl_graph(void);
extern void store_ctrl_graph(statement /*k*/, control /*v*/);
extern void update_ctrl_graph(statement /*k*/, control /*v*/);
extern control load_ctrl_graph(statement /*k*/);
extern control delete_ctrl_graph(statement /*k*/);
extern bool bound_ctrl_graph_p(statement /*k*/);
extern void store_or_update_ctrl_graph(statement /*k*/, control /*v*/);
extern void clean_ctrl_graph(void);
extern list control_list_to_statement_list(list /*lc*/);
extern void build_full_ctrl_graph(statement /*s*/);
extern void full_control_graph(string /*name*/);
extern void init_ctrl_graph_travel(statement /*s*/, bool (* /*decision*/)(statement));
extern bool next_ctrl_graph_travel(statement */*ps*/);
extern void close_ctrl_graph_travel(void);
/* hierarchize.c */
extern void control_graph_recursive_decomposition(unstructured /*u*/);
/* module.c */
extern bool new_controlizer(const char */*module_name*/);
extern bool controlizer(const char */*module_name*/);
/* unspaghettify.c */
extern char vcid_unspaghettify[];
extern void fuse_sequences_in_unstructured(statement /*s*/);
extern statement take_out_the_exit_node_if_not_a_continue(statement /*s*/);
extern void unspaghettify_or_restructure_statement(statement /*mod_stmt*/);
extern void unspaghettify_statement(statement /*mod_stmt*/);
extern void simple_restructure_statement(statement /*mod_stmt*/);
extern bool unspaghettify(const string /*mod_name*/);
extern void restructure_statement(statement /*mod_stmt*/);
extern bool restructure_control(const string /*mod_name*/);
/* cfg.c */
extern bool unstructured_consistency_p(unstructured /*u*/, bool /*assert_p*/);
extern bool unstructured_while_p(unstructured /*u*/);
/* unreachable.c */
extern void init_reachable(statement /*start*/);
extern bool statement_reachable_p(statement /*s*/);
extern bool statement_continued_p(statement /*s*/);
extern void close_reachable(void);
/* bourdoncle.c */
extern bool meaningless_control_p(control /*c*/);
extern bool control_test_p(control /*c*/);
extern void add_control_to_embedding_control_list(control /*c*/);
extern control control_to_ancestor(control /*vertex*/, hash_table /*ancestor_map*/);
extern control control_shallow_copy(control /*c*/);
extern unstructured unstructured_shallow_copy(unstructured /*u*/, hash_table /*ancestor_map*/);
extern unstructured partition_to_unstructured(control /*vertex*/, list /*partition*/);
extern void intersect_successors_with_partition_or_complement(control /*c*/, list /*partition*/, bool /*complement_p*/);
extern void intersect_successors_with_partition(control /*c*/, list /*partition*/);
extern void intersect_successors_with_partition_complement(control /*c*/, list /*partition*/);
extern list bourdoncle_partition(unstructured /*u*/, unstructured */*p_ndu*/, hash_table */*p_ancestor_map*/, hash_table */*p_scc_map*/);
extern list bourdoncle_component(control /*vertex*/, hash_table /*ancestor_map*/, hash_table /*scc_map*/);
extern int bourdoncle_visit(control /*vertex*/, list */*ppartition*/, hash_table /*ancestor_map*/, hash_table /*scc_map*/);
extern unstructured ancestor_cycle_head_to_scc(control /*a*/, hash_table /*scc_map*/);
extern unstructured proper_cycle_head_to_scc(control /*h*/, hash_table /*scc_map*/);
extern bool cycle_head_p(control /*c*/, hash_table /*ancestor_map*/, hash_table /*scc_map*/);
extern bool proper_cycle_head_p(control /*c*/, hash_table /*scc_map*/);
extern bool direct_cycle_head_p(control /*c*/, hash_table /*scc_map*/);
extern unstructured cycle_head_to_scc(control /*c*/, hash_table /*ancestor_map*/, hash_table /*scc_map*/);
extern bool one_successor_kind_only_p(control /*c*/, bool /*true_p*/);
extern bool true_successors_only_p(control /*c*/);
extern bool false_successors_only_p(control /*c*/);
extern void bourdoncle_free(unstructured /*ndu*/, hash_table /*ancestor_map*/, hash_table /*scc_map*/);
/* for_to_do_or_while_loops.c */
extern sequence for_to_do_loop_conversion(forloop /*theloop*/, statement /*parent*/);
extern void try_to_transform_a_for_loop_into_a_do_loop(forloop /*f*/);
extern bool for_loop_to_do_loop(const string /*module_name*/);
extern sequence for_to_while_loop_conversion(expression /*init*/, expression /*cond*/, expression /*incr*/, statement /*body*/, extensions /*exts*/);
extern void transform_a_for_loop_into_a_while_loop(forloop /*f*/);
extern void transform_a_for_loop_statement_into_a_while_loop(statement /*st*/);
extern bool for_loop_to_while_loop(const string /*module_name*/);
/* dowhile_to_while.c */
extern bool dowhile_to_while(const char */*module_name*/);
extern void do_loop_to_while_loop(statement /*sl*/);
extern void do_loop_to_for_loop(statement /*sl*/);
#endif /*  control_header_included */
