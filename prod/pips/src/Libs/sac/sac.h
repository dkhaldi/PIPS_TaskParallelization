/* Warning! Do not modify this file that is automatically generated! */
/* Modify src/Libs/sac/sac-local.h instead, to add your own modifications. */

/* header file built by cproto */

#ifndef  sac_header_included
#define  sac_header_included
/*

  $Id: sac-local.h 23065 2016-03-02 09:05:50Z coelho $

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
typedef hash_table operator_id_sons ;
#include "sac_private.h"
#include "dg.h"

typedef dg_arc_label arc_label;
typedef dg_vertex_label vertex_label;

#include "graph.h"


#define FUNC_TO_ATOMIZE_P(call) (\
        type_functional_p(entity_type(call_function(call))) && \
	    (gen_length(module_functional_parameters(call_function(call))) != 0) && \
        (!ENTITY_DEREFERENCING_P(call_function(call))) && \
        (!ENTITY_POINT_TO_P(call_function(call))) && \
        (!ENTITY_FIELD_P(call_function(call)))\
        )

/* if conversion */
#define IF_TO_CONVERT "PIPS IF_TO_CONVERT"
#define IF_CONV_TO_COMPACT "PIPS IF_CONV_TO_COMPACT"


#define ENTITY_FUNCTION_P(f) (type_functional_p(entity_type(f)) && \
			    (gen_length(module_functional_parameters(f)) != 0))

/* simd_loop_const_elim.c */

#define SIMD_MASKED_SUFFIX "_MASKED"
#define SIMD_GENERIC_SUFFIX "_GENERIC"
#define SIMD_CONSTANT_SUFFIX "_CONSTANT"
#define SIMD_BROADCAST_SUFFIX "_BROADCAST"
#define SAC_PADDING_ENTITY_NAME "PADDING_VALUE"

#define STATEMENT_INFO_NEWGEN_DOMAIN SIMDSTATEMENTINFO_NEWGEN_DOMAIN
#define gen_STATEMENT_INFO_cons gen_SIMDSTATEMENTINFO_cons


#define CHECK_VECTORELEMENT(ve) do {\
    pips_assert("vector Index seems legal",vectorElement_vectorIndex(ve) >= 0 && vectorElement_vectorIndex(ve) < simdStatementInfo_nbArgs(vectorElement_statement(ve)));\
    } while(0)


/* symbols exported by the parser */
extern FILE *patterns_yyin;
extern int patterns_yyparse();
extern int patterns_yylex();
extern void patterns_yyerror(const char*);

/* if_conversion_compact.c */
extern bool if_conversion_compact(char */*mod_name*/);
/* if_conversion_init.c */
extern bool if_conversion_init(char */*mod_name*/);
/* simdizer.c */
extern match get_statement_match_of_kind(statement /*s*/, opcodeClass /*kind*/);
extern statement sac_current_block;
extern instruction sac_real_current_instruction;
extern string sac_commenter(entity /*e*/);
extern bool simdizer(char */*mod_name*/);
extern bool simdizer_init(const char */*module_name*/);
/* varwidth.c */
extern int effective_variables_width(instruction /*i*/);
/* codegen.c */
extern void init_vector_to_expressions(void);
extern void reset_vector_to_expressions(void);
extern void invalidate_expressions_in_statement(statement /*s*/);
extern bool expression_reference_or_field_p(expression /*e*/);
extern bool simd_vector_entity_p(entity /*e*/);
extern int get_subwordSize_from_opcode(opcode /*oc*/, int /*argNum*/);
extern opcode generate_opcode(string /*name*/, list /*types*/, float /*cost*/);
extern expression distance_between_expression(const expression /*exp0*/, const expression /*exp1*/);
extern bool sac_aligned_entity_p(entity /*e*/);
extern statement make_shuffle_statement(entity */*from*/, list /*expressions*/, int */*perms*/);
extern simdstatement make_simd_statements(set /*opkinds*/, list /*statements*/);
extern list generate_simd_code(simdstatement /*ssi*/, float */*simdCost*/);
/* unroll.c */
extern bool loop_auto_unroll(const char */*mod_name*/);
extern bool simdizer_auto_unroll(char */*mod_name*/);
extern bool simdizer_auto_tile(const char */*module_name*/);
/* operatorid.c */
extern void set_simd_operator_mappings(void */*m*/);
extern void reset_simd_operator_mappings(void);
extern int get_operator_id(entity /*e*/);
extern bool simd_operator_mappings(const string /*module_name*/);
/* treematch.c */
extern void set_simd_treematch(matchTree /*t*/);
extern void reset_simd_treematch(void);
extern void simd_reset_finalArgType(void);
extern void simd_fill_finalArgType(statement /*stat*/);
extern void simd_fill_curArgType(statement /*stat*/);
extern bool simd_check_argType(void);
extern list match_statement(statement /*s*/);
extern void insert_opcodeClass(char */*s*/, int /*nbArgs*/, list /*opcodes*/);
extern void insert_pattern(char */*s*/, list /*tokens*/, list /*args*/);
extern bool simd_treematcher(const string /*module_name*/);
/* atomizer.c */
extern statement simd_atomize_this_expression(entity (* /*create*/)(entity, basic), expression /*e*/);
extern bool simd_atomizer(char */*mod_name*/);
extern bool reduction_atomization(const char */*module_name*/);
/* vectransform.c */
extern void insert_transformation(char */*name*/, int /*vectorLengthOut*/, int /*subwordSizeOut*/, int /*vectorLengthIn*/, int /*subwordSizeIn*/, int /*nbArgs*/, list /*mapping*/);
/* reductions.c */
extern bool sac_expression_reduction_p(expression /*e*/);
extern bool simd_remove_reductions(char */*mod_name*/);
extern bool redundant_load_store_elimination(char */*module_name*/);
/* singleass.c */
extern bool scalar_renaming(char */*mod_name*/);
/* deatomizer.c */
extern bool deatomizer(char */*mod_name*/);
/* if_conversion.c */
extern bool if_conversion(char */*mod_name*/);
extern bool loop_nest_unswitching(const char */*module_name*/);
/* simd_memory_packing.c */
extern bool simd_memory_packing(char */*mod_name*/);
/* patterns.y */
extern size_t sac_lineno;
extern int yywrap(void);
extern void yyerror(const char */*s*/);
/* lexer.l */
#endif /*  sac_header_included */
