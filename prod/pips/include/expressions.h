/* Warning! Do not modify this file that is automatically generated! */
/* Modify src/Libs/expressions/expressions-local.h instead, to add your own modifications. */

/* header file built by cproto */

#ifndef  expressions_header_included
#define  expressions_header_included
/*

  $Id: expressions-local.h 23065 2016-03-02 09:05:50Z coelho $

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
#ifndef EXPRESSION_H_
#define EXPRESSION_H_
/*
 * for partial_eval.c:
 *
 * EFORMAT: the expression format used in recursiv evaluations. 
 * = ((ICOEF * EXPR) + ISHIFT)
 * it is SIMPLER when it is interesting to replace initial expression by the
 * one generated from eformat.
 */
struct eformat {
    expression expr;
    int icoef;
    int ishift;
    bool simpler;
};

typedef struct eformat eformat_t;
#endif
/* partial_eval.c */
extern void set_live_loop_indices(void);
extern void reset_live_loop_indices(void);
extern void dump_live_loop_indices(void);
extern void init_use_proper_effects(const char */*module_name*/);
extern effects stmt_to_fx(statement /*stmt*/, statement_effects /*fx_map*/);
extern bool entity_written_p(entity /*ent*/, effects /*fx*/);
extern void init_use_preconditions(const char */*module_name*/);
extern Psysteme stmt_prec(statement /*stmt*/);
extern void transformer_map_print(void);
extern bool eformat_equivalent_p(eformat_t /*ef1*/, eformat_t /*ef2*/);
extern void print_eformat(eformat_t /*ef*/, char */*name*/);
extern void partial_eval_expression_and_regenerate(expression */*ep*/, Psysteme /*ps*/, effects /*fx*/);
extern eformat_t partial_eval_expression_and_copy(expression /*expr*/, Psysteme /*ps*/, effects /*fx*/);
extern eformat_t partial_eval_expression(expression /*e*/, Psysteme /*ps*/, effects /*fx*/);
extern eformat_t partial_eval_syntax(expression /*e*/, Psysteme /*ps*/, effects /*fx*/);
extern eformat_t partial_eval_reference(expression /*e*/, Psysteme /*ps*/, effects /*fx*/);
extern void partial_eval_call_and_regenerate(call /*ca*/, Psysteme /*ps*/, effects /*fx*/);
extern eformat_t partial_eval_call(call /*ec*/, Psysteme /*ps*/, effects /*fx*/);
extern eformat_t partial_eval_call_expression(expression /*exp*/, Psysteme /*ps*/, effects /*fx*/);
extern eformat_t partial_eval_unary_operator(entity /*func*/, cons */*la*/, Psysteme /*ps*/, effects /*fx*/);
extern eformat_t partial_eval_mult_operator(expression */*ep1*/, expression */*ep2*/, Psysteme /*ps*/, effects /*fx*/);
extern eformat_t partial_eval_plus_or_minus_operator(int /*token*/, expression */*ep1*/, expression */*ep2*/, Psysteme /*ps*/, effects /*fx*/);
extern eformat_t partial_eval_plus_operator(expression */*ep1*/, expression */*ep2*/, Psysteme /*ps*/, effects /*fx*/);
extern eformat_t partial_eval_plus_c_operator(expression */*ep1*/, expression */*ep2*/, Psysteme /*ps*/, effects /*fx*/);
extern eformat_t partial_eval_minus_operator(expression */*ep1*/, expression */*ep2*/, Psysteme /*ps*/, effects /*fx*/);
extern eformat_t partial_eval_minus_c_operator(expression */*ep1*/, expression */*ep2*/, Psysteme /*ps*/, effects /*fx*/);
extern eformat_t partial_eval_div_or_mod_operator(int /*token*/, expression */*ep1*/, expression */*ep2*/, Psysteme /*ps*/, effects /*fx*/);
extern eformat_t partial_eval_div_operator(expression */*ep1*/, expression */*ep2*/, Psysteme /*ps*/, effects /*fx*/);
extern eformat_t partial_eval_mod_operator(expression */*ep1*/, expression */*ep2*/, Psysteme /*ps*/, effects /*fx*/);
extern eformat_t partial_eval_c_mod_operator(expression */*ep1*/, expression */*ep2*/, Psysteme /*ps*/, effects /*fx*/);
extern eformat_t partial_eval_min_or_max_operator(int /*token*/, expression */*ep1*/, expression */*ep2*/, Psysteme /*ps*/, effects /*fx*/);
extern eformat_t partial_eval_min_operator(expression */*ep1*/, expression */*ep2*/, Psysteme /*ps*/, effects /*fx*/);
extern eformat_t partial_eval_max_operator(expression */*ep1*/, expression */*ep2*/, Psysteme /*ps*/, effects /*fx*/);
extern eformat_t partial_eval_power_operator(expression */*ep1*/, expression */*ep2*/, Psysteme /*ps*/, effects /*fx*/);
extern eformat_t partial_eval_update_operators(expression */*ep1*/, expression */*ep2*/, Psysteme /*ps*/, effects /*fx*/);
extern eformat_t partial_eval_binary_operator(entity /*func*/, cons */*la*/, Psysteme /*ps*/, effects /*fx*/);
extern eformat_t partial_eval_binary_operator_old(entity /*func*/, cons */*la*/, Psysteme /*ps*/, effects /*fx*/);
extern void regenerate_expression(eformat_t */*efp*/, expression */*ep*/);
extern void regenerate_call(eformat_t */*efp*/, call /*ca*/);
extern expression generate_monome(int /*coef*/, expression /*expr*/);
extern void partial_eval_declaration(entity /*v*/, Psysteme /*pre_sc*/, effects /*fx*/);
extern void partial_eval_declarations(list /*el*/, Psysteme /*pre_sc*/, effects /*fx*/);
extern void partial_eval_statement(statement /*stmt*/);
extern bool partial_eval(const char */*module_name*/);
/* simple_atomize.c */
extern statement atomize_this_expression(entity (* /*create*/)(entity, basic), expression /*e*/);
extern void cleanup_subscripts(void */*obj*/);
extern void atomize_as_required(statement /*stat*/, bool (* /*ref_decide*/)(reference, expression), bool (* /*call_decide*/)(call, expression), bool (* /*test_decide*/)(test, expression), bool (* /*range_decide*/)(range, expression), bool (* /*while_decide*/)(whileloop, expression), entity (* /*new*/)(entity, basic));
/* forward_substitution.c */
extern bool forward_substitute(const char */*module_name*/);
/* optimize.c */
extern void naryfication_of_expressions(statement /*s*/);
extern entity inverse_operator_of(entity /*e*/);
extern void inverse_normalization_of_expressions(statement /*s*/);
extern void convert_to_c_operators(void */*v*/);
extern void convert_to_standard_operators(void */*v*/);
extern bool optimize_expressions(const char */*module_name*/);
/* sequence_gcm_cse.c */
extern void perform_icm_association(const char */*name*/, statement /*s*/);
extern void try_reorder_expressions(void */*s*/, bool /*icm*/);
extern void perform_ac_cse(const char */*name*/, statement /*s*/);
extern bool common_subexpression_elimination(const char */*module_name*/);
extern bool icm(const char */*module_name*/);
/* instruction_selection.c */
extern bool instruction_selection(const char */*module_name*/);
/* expression_substitution.c */
extern void substitute_expression(void */*in*/, expression /*pattern*/, expression /*into*/);
extern bool expression_substitution(const char */*module_name*/);
/* simplify.c */
extern bool simplify_subscripts(const char */*module_name*/);
extern bool split_structures(const char */*module_name*/);
extern void complex_translation_array_of_structs(list */*pl*/, list /*l*/);
extern void complex_translation_struct_of_array(list */*pl*/, list /*l*/);
extern bool simplify_complex(const char */*module_name*/);
extern void simplify_c_operator(statement /*s*/);
extern bool simplify_constant_address_expressions(const char */*module_name*/);
/* rename_operator.c */
extern bool rename_operator(const char */*module_name*/);
#endif /*  expressions_header_included */
