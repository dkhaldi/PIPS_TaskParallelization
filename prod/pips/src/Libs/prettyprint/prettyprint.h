/* Warning! Do not modify this file that is automatically generated! */
/* Modify src/Libs/prettyprint/prettyprint-local.h instead, to add your own modifications. */

/* header file built by cproto */

#ifndef  prettyprint_header_included
#define  prettyprint_header_included
/*

  $Id: prettyprint-local.h 23065 2016-03-02 09:05:50Z coelho $

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
#include "effects.h"
/* allocatable.c */
extern entity find_or_create_allocatable_struct(basic /*b*/, string /*name*/, int /*ndim*/);
/* area.c */
extern bool check_common_inclusion(entity /*common*/);
/* cmfortran.c */
extern cons *words_cmf_loop_range(range /*obj*/);
extern text text_loop_cmf(entity /*module*/, const char */*label*/, int /*margin*/, loop /*obj*/, int /*n*/, list /*lr*/, list /*lidx*/);
/* craft.c */
extern expression remove_modulo(expression /*exp*/);
extern text text_loop_craft(entity /*module*/, const char */*label*/, int /*margin*/, loop /*obj*/, int /*n*/, list /*lr*/, list /*lidx*/);
/* constraint_to_text.c */
extern void sc_syst_debug(Psysteme /*s*/);
extern void inegalite_debug(Pcontrainte /*c*/);
extern void egalite_debug(Pcontrainte /*c*/);
extern string contrainte_text_format(string /*aux_line*/, string /*continuation*/, text /*txt*/, Pcontrainte /*c*/, bool /*is_inegalite*/, string (* /*variable_name*/)(Variable), bool /*a_la_fortran*/, bool /*first_line*/);
extern string egalite_text_format(string /*aux_line*/, string /*continuation*/, text /*txt*/, Pcontrainte /*eg*/, string (* /*variable_name*/)(Variable), bool /*a_la_fortran*/, bool /*first_line*/);
extern string inegalite_text_format(string /*aux_line*/, string /*continuation*/, text /*txt*/, Pcontrainte /*ineg*/, string (* /*variable_name*/)(void), bool /*a_la_fortran*/, bool /*first_line*/);
extern void system_sorted_text_format(string /*line*/, string /*prefix*/, text /*txt*/, Psysteme /*ps*/, string (* /*variable_name*/)(Variable), bool (* /*put_first*/)(Pvecteur), bool /*a_la_fortran*/);
extern void system_text_format(string /*line*/, string /*prefix*/, text /*txt*/, Psysteme /*ps*/, string (* /*variable_name*/)(Variable), bool /*a_la_fortran*/);
extern void entity_list_text_format(string /*line*/, string /*continuation*/, text /*t*/, list /*le*/, const char *(* /*var_name*/)(entity));
/* declarations.c */
extern list words_declaration(entity /*e*/, bool /*prettyprint_common_variable_dimensions_p*/, list */*ppdl*/);
extern list words_basic(basic /*obj*/, list */*ppdl*/);
extern sentence sentence_variable(entity /*e*/, list */*ppdl*/);
extern sentence Sentence_Variable(entity /*e*/);
extern sentence sentence_head(entity /*e*/, list */*ppdl*/);
extern list words_qualifiers(list /*obj*/);
extern list words_type(type /*obj*/, list */*ppdl*/, bool /*argument_p*/);
extern list Words_Type(type /*obj*/);
extern bool c_brace_expression_p(expression /*e*/);
extern list words_brace_expression(expression /*exp*/, list */*ppdl*/);
extern list words_dimensions(list /*dims*/, list */*ppdl*/);
extern list generic_c_words_entity(type /*t*/, list /*name*/, bool /*is_safe*/, bool /*add_dummy_parameter_name_p*/, list */*ppdl*/);
extern list generic_c_words_simplified_entity(type /*t*/, list /*name*/, bool /*is_safe*/, bool /*add_dummy_parameter_name_p*/, bool /*is_first*/, bool /*in_type_declaration*/, bool /*argument_p*/, list */*ppdl*/);
extern list c_words_simplified_entity(type /*t*/, list /*name*/, bool /*is_first*/, bool /*in_type_declaration*/, list */*ppdl*/);
extern list c_words_entity(type /*t*/, list /*name*/, list */*ppdl*/);
extern list safe_c_words_entity(type /*t*/, list /*name*/);
extern text c_text_entities(entity /*module*/, list /*ldecl*/, int /*margin*/, list */*ppdl*/);
extern text c_text_related_entities(entity /*module*/, list /*del*/, int /*margin*/, int /*sn*/, list */*ppdl*/, list /*cl*/);
extern text c_text_entity(entity /*module*/, entity /*e*/, int /*margin*/, list */*ppdl*/, bool /*init_p*/);
extern text c_text_entity_simple(entity /*module*/, entity /*e*/, int /*margin*/);
/* declarations2.c */
extern void set_prettyprinter_common_hook(string (* /*f*/)(entity, entity));
extern void reset_prettyprinter_common_hook(void);
extern text text_declaration(entity /*module*/);
extern text text_common_declaration(entity /*common*/, entity /*module*/);
extern text text_initializations(entity /*m*/);
/* entity.c */
extern void print_entity_variable(entity /*e*/);
/* expression.c */
extern void fprint_expression(FILE */*f*/, expression /*e*/);
extern void print_expression(expression /*e*/);
extern string expression_to_string(expression /*e*/);
extern string reference_to_string(reference /*r*/);
extern void print_expressions(list /*le*/);
extern void print_syntax_expressions(list /*le*/);
extern void print_syntax(syntax /*s*/);
extern void fprint_reference(FILE */*fd*/, reference /*r*/);
extern void print_reference(reference /*r*/);
extern void print_reference_list(list /*lr*/);
extern void print_references(list /*rl*/);
extern void print_normalized(normalized /*n*/);
extern bool maxima_simplify(expression */*presult*/);
extern void fprint_list_of_exp(FILE */*fp*/, list /*exp_l*/);
/* extension.c */
extern string close_extension(extension /*e*/);
extern string close_extensions(extensions /*es*/, bool /*nl*/);
extern string extension_to_string(extension /*e*/);
extern string extensions_to_string(extensions /*es*/, bool /*nl*/);
/* fortran90.c */
extern text text_loop_90(entity /*module*/, const char */*label*/, int /*margin*/, loop /*obj*/, int /*n*/);
extern expression expand_reference(syntax /*s*/, expression /*e*/, entity /*i*/, range /*r*/);
extern expression expand_expression(expression /*e*/, entity /*i*/, range /*r*/);
/* html_prettyprinter.c */
extern void html_output(const char */*out*/, bool /*cr*/);
extern void html_print_entity_full(entity /*e*/);
extern void html_print_symbol_table(void);
extern bool html_prettyprint(const string /*mod_name*/);
extern bool html_prettyprint_symbol_table(const string /*module*/);
/* loop.c */
extern void printf_loop(loop /*lp*/);
extern void print_loops_list(entity /*mod*/, list /*sl*/);
/* misc.c */
extern char lib_ri_util_prettyprint_c_rcsid[];
extern string get_comment_sentinel(void);
extern string get_comment_continuation(void);
extern unsigned int get_prettyprint_indentation(void);
extern text empty_text(entity /*e*/, int /*m*/, statement /*s*/);
extern void init_prettyprint(text (* /*hook*/)(entity, int, statement));
extern void close_prettyprint(void);
extern bool one_liner_p(statement /*s*/);
extern bool gcc_if_block_braces_required_p(test /*obj*/);
extern list words_loop_range(range /*obj*/, list */*ppdl*/);
extern list C_loop_range(range /*obj*/, entity /*i*/, list */*ppdl*/);
extern list words_range(range /*obj*/, list */*ppdl*/);
extern list words_subscript_range(range /*obj*/, list */*ppdl*/);
extern list words_any_reference(reference /*obj*/, list */*ppdl*/, const char *(* /*enf*/)(entity));
extern list Words_Any_Reference(reference /*obj*/, list /*pdl*/, const char *(* /*enf*/)(entity));
extern list words_reference(reference /*obj*/, list */*ppdl*/);
extern list Words_Reference(reference /*obj*/);
extern void set_alternate_return_set(void);
extern void reset_alternate_return_set(void);
extern void add_target_to_alternate_return_set(entity /*l*/);
extern text generate_alternate_return_targets(void);
extern list words_regular_call(call /*obj*/, bool /*is_a_subroutine*/, list */*ppdl*/);
extern list Words_Regular_Call(call /*obj*/, bool /*is_a_subroutine*/);
extern list words_call_intrinsic(call /*obj*/, int /*precedence*/, bool /*leftmost*/, list */*ppdl*/);
extern list words_goto_label(const char */*tlabel*/);
extern list eole_fma_specific_op(call /*obj*/, int /*precedence*/, bool /*leftmost*/, list */*ppdl*/);
extern list eole_fms_specific_op(call /*obj*/, int /*precedence*/, bool /*leftmost*/, list */*ppdl*/);
extern void register_intrinsic_handler(const char */*name*/, intrinsic_desc_t */*desc*/);
extern list words_call(call /*obj*/, int /*precedence*/, bool /*leftmost*/, bool /*is_a_subroutine*/, list */*ppdl*/);
extern list Words_Call(call /*obj*/, int /*precedence*/, bool /*leftmost*/, bool /*is_a_subroutine*/);
extern list words_expression(expression /*obj*/, list */*ppdl*/);
extern list Words_Expression(expression /*obj*/);
extern list words_syntax(syntax /*obj*/, list */*ppdl*/);
extern list Words_Syntax(syntax /*obj*/);
extern list words_subexpression(expression /*obj*/, int /*precedence*/, bool /*leftmost*/, list */*ppdl*/);
extern list Words_Subexpression(expression /*obj*/, int /*precedence*/, bool /*leftmost*/);
extern sentence sentence_goto_label(entity /*module*/, const char */*label*/, int /*margin*/, const char */*tlabel*/, int /*n*/);
extern text text_omp_directive(loop /*l*/, int /*m*/);
extern text text_loop_default(entity /*module*/, const char */*label*/, int /*margin*/, loop /*obj*/, int /*n*/, list */*ppdl*/, bool /*is_recursive_p*/);
extern text text_loop(entity /*module*/, const char */*label*/, int /*margin*/, loop /*obj*/, int /*n*/, list */*ppdl*/, bool /*is_recursive_p*/);
extern text init_text_statement(entity /*module*/, int /*margin*/, statement /*obj*/);
extern void set_prettyprinter_head_hook(string (* /*f*/)(entity));
extern void reset_prettyprinter_head_hook(void);
extern bool C_comment_p(string /*c*/);
extern text C_any_comment_to_text(int /*r_margin*/, string /*c*/);
extern text C_standard_comment_to_text(int /*margin*/, string /*comment*/);
extern text C_comment_to_text(int /*margin*/, string /*comment*/);
extern text generic_text_statement_enclosed(entity /*module*/, int /*imargin*/, statement /*stmt*/, bool /*braces_p*/, bool /*drop_continue_p*/, list */*ppdl*/, bool /*is_recursive_p*/, bool /*with_comments*/);
extern text text_statement_enclosed(entity /*module*/, int /*imargin*/, statement /*stmt*/, bool /*braces_p*/, bool /*drop_continue_p*/, list */*ppdl*/);
extern text Text_Statement_Enclosed(entity /*module*/, int /*imargin*/, statement /*stmt*/, bool /*braces_p*/, bool /*drop_continue_p*/);
extern text text_statement(entity /*module*/, int /*margin*/, statement /*stmt*/, list */*ppdl*/);
extern text Text_Statement(entity /*module*/, int /*margin*/, statement /*stmt*/);
extern text Text_Proper_Statement(entity /*module*/, int /*margin*/, statement /*stmt*/);
extern string proper_statement_to_string(statement /*cs*/);
extern statement find_last_statement(statement /*s*/);
extern void set_last_statement(statement /*s*/);
extern void reset_last_statement(void);
extern bool last_statement_p(statement /*s*/);
extern void insure_return_as_last_statement(entity /*module*/, statement */*ps*/);
extern list initialize_previously_declared_entities(entity /*module*/);
extern text text_named_module(entity /*name*/, entity /*module*/, statement /*stat*/);
extern text text_module(entity /*module*/, statement /*stat*/);
extern void add_control_node_identifier_to_text(text /*r*/, control /*c*/);
extern void output_a_graph_view_of_the_unstructured_successors(text /*r*/, entity /*module*/, int /*margin*/, control /*c*/);
extern bool output_a_graph_view_of_the_unstructured_from_a_control(text /*r*/, entity /*module*/, int /*margin*/, control /*begin_control*/, control /*exit_control*/);
extern void output_a_graph_view_of_the_unstructured(text /*r*/, entity /*module*/, const char */*label*/, int /*margin*/, unstructured /*u*/, int /*num*/);
/* module.c */
extern bool recompile_module(const string /*module*/);
/* parameter.c */
extern void print_parameter(parameter /*p*/);
extern void print_parameters(list /*lp*/);
extern void print_mode(mode /*m*/);
extern void print_dummy(dummy /*d*/);
/* pragma.c */
extern string close_pragma(pragma /*p*/);
extern string pragma_to_string(pragma /*p*/);
extern void add_expr_to_pragma_expr_list(pragma /*pr*/, expression /*ex*/);
/* print.c */
extern bool make_text_resource(const char */*mod_name*/, const char */*res_name*/, const char */*file_ext*/, text /*texte*/);
extern bool make_text_resource_and_free(const char */*mod_name*/, const char */*res_name*/, const char */*file_ext*/, text /*t*/);
extern bool user_view_p(void);
extern bool print_code_or_source(string /*mod_name*/);
extern bool print_code(const string /*mod_name*/);
extern bool print_source(const string /*mod_name*/);
extern bool print_parallelized_code(const string /*mod_name*/);
extern bool print_parallelized90_code(const string /*mod_name*/);
extern bool print_parallelized77_code(const string /*mod_name*/);
extern bool print_parallelizedHPF_code(const string /*module_name*/);
extern bool print_parallelizedOMP_code(const string /*mod_name*/);
extern bool print_parallelizedMPI_code(const string /*mod_name*/);
extern void dprint(expression /*x*/);
/* print_code_as_a_graph.c */
extern bool print_code_as_a_graph(const string /*mod_name*/);
/* same_names.c */
extern bool same_lexpr_name_p(list /*l1*/, list /*l2*/);
extern bool same_entity_lname_p(entity /*e1*/, entity /*e2*/);
extern bool same_call_name_p(call /*c1*/, call /*c2*/);
extern bool same_ref_name_p(reference /*r1*/, reference /*r2*/);
extern bool same_range_name_p(range /*r1*/, range /*r2*/);
extern bool same_sizeofexpression_name_p(sizeofexpression /*s0*/, sizeofexpression /*s1*/);
extern bool same_subscript_name_p(subscript /*ss1*/, subscript /*ss2*/);
extern bool same_cast_name_p(cast /*cs1*/, cast /*cs2*/);
extern bool same_application_name_p(application /*a1*/, application /*a2*/);
extern bool same_va_arg_name_p(list /*l1*/, list /*l2*/);
extern bool same_syntax_name_p(syntax /*s1*/, syntax /*s2*/);
extern bool same_expression_name_p(expression /*e1*/, expression /*e2*/);
/* statement.c */
extern void print_statement_set(FILE */*fd*/, set /*r*/);
extern void fprint_statement(FILE */*fd*/, statement /*s*/);
extern void print_statement(statement /*s*/);
extern void print_statements(list /*sl*/);
extern void print_statement_of_module(statement /*s*/, const char */*mn*/);
extern text statement_to_text(statement /*s*/);
extern void safe_print_statement(statement /*s*/);
extern void print_parallel_statement(statement /*s*/);
extern statement last_statement(statement /*s*/);
extern void print_number_to_statement(hash_table /*nts*/);
extern list find_statements_interactively(statement /*s*/);
/* symbol_table.c */
extern void dump_common_layout(string_buffer /*result*/, entity /*c*/, bool /*debug_p*/, bool /*isfortran*/);
extern string get_symbol_table(entity /*m*/, bool /*isfortran*/);
extern void actual_symbol_table_dump(const char */*module_name*/, bool /*is_parsed*/);
extern bool parsed_symbol_table(const char */*module_name*/);
extern bool symbol_table(const char */*module_name*/);
/* type.c */
extern string type_to_full_string_definition(type /*t*/);
extern string string_of_type(const type /*t*/);
extern bool same_type_name_p(const type /*t0*/, const type /*t1*/);
extern string basic_to_string(basic /*b*/);
extern void print_types(list /*tl*/);
extern void print_type(type /*t*/);
extern void print_qualifiers(list /*ql*/);
extern void print_qualifier(qualifier /*q*/);
/* unstructured.c */
extern text text_unstructured(entity /*module*/, const char */*label*/, int /*margin*/, unstructured /*u*/, int /*num*/, list */*ppdl*/);
extern list unstructured_to_trail(unstructured /*u*/);
extern void dump_trail(list /*trail*/);
extern void dump_control_to_label_name(hash_table /*h*/);
#endif /*  prettyprint_header_included */
