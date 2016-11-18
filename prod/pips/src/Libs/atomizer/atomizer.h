/* Warning! Do not modify this file that is automatically generated! */
/* Modify src/Libs/atomizer/atomizer-local.h instead, to add your own modifications. */

/* header file built by cproto */

#ifndef  atomizer_header_included
#define  atomizer_header_included
/*

  $Id: atomizer-local.h 23065 2016-03-02 09:05:50Z coelho $

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
   #define ATOMIZER_MODULE_NAME "ATOMIZE"
   */
#define TMP_ENT 1
#define AUX_ENT 2
#define DOUBLE_PRECISION_SIZE 8

/* During the computation, the program has to deal with blocks of statements.
 * We define a new structure in order to have a simple control over all
 * the manipulations of the blocks of statements.
 *
 * With this new structure we know the current statement being translated
 * and the list of statements (ie the block) in which we put the new
 * statements created.
 */
typedef struct {
     list last;
     list first;
     bool stmt_generated;
    } Block;
/* The list "first" is a truncated list from the first to the current
 * statement (not included).
 * The list "last" is a truncated list from the current statement (included)
 * to the last.
 * The union of "first" and "last" is equal to the entire block.
 *
 * The bool "stmt_generated" says if the current statement has:
 *       _ true : already generated statements.
 *       _ false : not generated statements.
 *
 * Thus, when the current statement generates a new statement it is put at the
 * end of the list "first" (just before the current statement).
 * The current statement gives its caracteristics to the new one if the bool
 * "stmt_generated" is false; this allows to keep these caracteristics
 * at the first statement of the list generated by the translation of the
 * current statement.
 * The caracteristics of a statement are its "label", "number", "ordering" and
 * "comments" (cf. RI).
 */

/* This global variable is used for the modification of the control graph,
 * see commentaries of atomizer_of_unstructured() in atomizer.c.
 */
extern list l_inst;

// moved to ri-util/variable.c
// extern list integer_entities, real_entities, complex_entities,
// logical_entities, double_entities, char_entities;

/* Mappings for the cumulated effects of statements. */
/* extern statement_mapping cumulated_effects_map;*/
/* new_atomizer.c */
extern bool new_atomizer(char */*mod_name*/);
/* atomizer.c */
extern list l_inst;
extern hash_table MemToTmp;
extern void normalize_wp65_code(statement /*stat*/);
extern bool atomizer(const string /*mod_name*/);
extern void atomizer_of_unstructured(unstructured /*u*/);
extern void atomizer_of_statement(statement /*stmt*/, Block */*cb*/);
extern void atomizer_of_block(instruction /*i*/);
extern void atomizer_of_test(test /*t*/, Block */*cb*/);
extern void atomizer_of_loop(loop /*l*/, Block */*cb*/);
extern void atomizer_of_call(call /*c*/, Block */*cb*/);
extern void atomizer_of_intrinsic(call /*c*/, Block */*cb*/);
extern void atomizer_of_external(call /*c*/, Block */*cb*/);
extern list atomizer_of_expressions(list /*expl*/, Block */*cb*/);
extern expression atomizer_of_expression(expression /*exp*/, Block */*cb*/, int /*mem_var*/);
extern void atomizer_of_array_indices(expression /*exp*/, Block */*cb*/);
/* utils.c */
extern bool instruction_in_list_p(instruction /*inst*/, list /*l*/);
extern bool nlc_linear_expression_p(expression /*exp*/);
/* codegen.c */
extern void put_stmt_in_Block(statement /*new_stmt*/, Block */*cb*/);
extern expression assign_tmp_to_exp(expression /*exp*/, Block */*cb*/);
extern void insert_one_type_declaration(entity /*mod_entity*/, list /*var_to_decl*/, string /*type_decl*/);
extern void insert_new_declarations(char */*mod_name*/);
extern void store_expression(expression /*exp*/, Block */*cb*/);
/* control.c */
extern void modify_blocks(control /*c*/);
extern void atom_get_blocs(control /*c*/, cons **/*l*/);
extern control find_control_block(control /*c*/);
/* norm_exp.c */
extern void normal_expression_of_expression(expression /*exp*/);
extern void normal_expression_of_statement(statement /*s*/);
extern void normal_expression_of_unstructured(unstructured /*u*/);
extern int get_nlc_number(entity /*nlc_ent*/);
extern void reconfig_expression(expression /*exp*/);
/* defs_elim.c */
extern bool true_dependence_with_entity_p(conflict /*conf*/, entity /*e*/);
extern bool defs_elim_of_assign_call(statement /*assign_stmt*/, graph /*dg*/);
extern bool defs_elim_of_statement(statement /*s*/, graph /*dg*/);
extern void defs_elim_of_unstructured(unstructured /*u*/, graph /*dg*/);
#endif /*  atomizer_header_included */
