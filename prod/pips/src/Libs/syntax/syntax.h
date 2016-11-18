/* Warning! Do not modify this file that is automatically generated! */
/* Modify src/Libs/syntax/syntax-local.h instead, to add your own modifications. */

/* header file built by cproto */

#ifndef  syntax_header_included
#define  syntax_header_included
/*

  $Id: syntax-local.h 23065 2016-03-02 09:05:50Z coelho $

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
/* Legal characters to start a comment line
 *
 * '\n' is added to cope with empty lines
 * Empty lines with SPACE and TAB characters 
 * are be preprocessed and reduced to an empty line by GetChar().
 */
#define START_COMMENT_LINE "CcDd*!#\n"

/* lex yacc interface */
extern FILE * syn_in; 
extern int syn_lex();
extern void syn_reset_lex();
extern int syn_parse();
extern void syn_error(const char*);

/* definition of implementation dependent constants */

#include "constants.h"

#define HASH_SIZE 1013
#define FORMATLENGTH (4096)
#define LOCAL static

#ifndef abs
#define abs(v) (((v) < 0) ? -(v) : (v))
#endif

/* extern char * getenv(); */

#define Warning(f,m) \
(user_warning(f,"Warning between lines %d and %d\n%s\n",line_b_I,line_e_I,m) )

#define FatalError(f,m) \
(pips_internal_error("Fatal error between lines %d and %d\n%s\n",line_b_I,line_e_I,m))

/* These global variables are declared in ri-util/util.c */
extern entity DynamicArea;
extern entity StaticArea;
extern entity HeapArea;
extern entity StackArea;
extern entity AllocatableArea;

#include "parser_private.h"

/* declaration.c */
extern int SafeSizeOfArray(entity /*a*/);
extern void InitAreas(void);
extern void save_all_entities(void);
extern void SaveEntity(entity /*e*/);
extern void MakeVariableStatic(entity /*v*/, bool /*force_it*/);
extern void ProcessSave(entity /*v*/);
extern void save_initialized_variable(entity /*v*/);
extern void SaveCommon(entity /*c*/);
extern void PrintData(cons */*ldvr*/, cons */*ldvl*/);
extern void AnalyzeData(list /*ldvr*/, list /*ldvl*/);
extern void MakeDataStatement(list /*ldr*/, list /*ldv*/);
extern void DeclarePointer(entity /*ptr*/, entity /*pointed_array*/, list /*decl_dims*/);
extern void DeclareVariable(entity /*e*/, type /*t*/, list /*d*/, storage /*s*/, value /*v*/);
extern void DeclareIntrinsic(entity /*e*/);
extern bool fortran_relevant_area_entity_p(entity /*c*/);
extern void initialize_common_size_map(void);
extern void reset_common_size_map(void);
extern void reset_common_size_map_on_error(void);
extern bool common_to_defined_size_p(entity /*a*/);
extern size_t common_to_size(entity /*a*/);
extern void set_common_to_size(entity /*a*/, size_t /*size*/);
extern void update_common_to_size(entity /*a*/, size_t /*new_size*/);
extern entity MakeCommon(entity /*e*/);
extern entity NameToCommon(string /*n*/);
extern void AddVariableToCommon(entity /*c*/, entity /*v*/);
extern int CurrentOffsetOfArea(entity /*a*/, entity /*v*/);
extern void update_common_sizes(void);
extern void InitImplicit(void);
extern void cr_implicit(tag /*t*/, int /*l*/, int /*lettre_d*/, int /*lettre_f*/);
extern type ImplicitType(entity /*e*/);
extern bool implicit_type_p(entity /*e*/);
extern void retype_formal_parameters(void);
extern type MakeFortranType(tag /*t*/, value /*v*/);
extern int OffsetOfReference(reference /*r*/);
extern int ValueOfIthLowerBound(entity /*e*/, int /*i*/);
extern int SizeOfRange(range /*r*/);
extern int IsIntegerScalar(entity /*e*/);
extern void update_user_common_layouts(entity /*m*/);
extern bool update_common_layout(entity /*m*/, entity /*c*/);
extern entity SafeFindOrCreateEntity(const char */*package*/, const char */*name*/);
extern void add_entity_to_declarations(string /*name*/, string /*area_name*/, enum basic_utype tag, void */*val*/);
/* expression.c */
extern char vcid_syntax_expression[];
extern entity MakeParameter(entity /*e*/, expression /*x*/);
extern expression MakeImpliedDo(syntax /*v*/, range /*r*/, cons */*l*/);
extern expression loop_to_implieddo(loop /*l*/);
extern syntax MakeAtom(entity /*e*/, cons */*indices*/, expression /*fc*/, expression /*lc*/, int /*HasParenthesis*/);
extern cons *MakeIoList(cons */*l*/);
extern list FortranExpressionList(list /*l*/);
extern expression MakeFortranBinaryCall(entity /*op*/, expression /*e1*/, expression /*e2*/);
extern expression MakeFortranUnaryCall(entity /*op*/, expression /*e1*/);
extern syntax CheckLeftHandSide(syntax /*s*/);
extern entity make_Fortran_constant_entity(string /*name*/, tag /*bt*/, size_t /*size*/);
/* equivalence.c */
extern char vcid_syntax_equivalence[];
extern void ResetChains(void);
extern void SetChains(void);
extern atom MakeEquivAtom(syntax /*s*/);
extern void StoreEquivChain(chain /*c*/);
extern void ComputeEquivalences(void);
extern int AddOrMergeChain(chain /*ct*/);
extern int ChainIntersection(cons */*opc1*/, cons */*opc2*/);
extern cons *MergeTwoChains(cons */*opc1*/, cons */*opc2*/);
extern void PrintChains(equivalences /*e*/);
extern void PrintChain(chain /*c*/);
extern bool entity_in_equivalence_chains_p(entity /*e*/);
extern bool entity_in_equivalence_chain_p(entity /*e*/, chain /*c*/);
extern void ComputeAddresses(void);
extern void SaveChains(void);
/* parser.c */
extern char *CurrentFN;
extern cons *FormalParameters;
extern const char *CurrentPackage;
extern int line_b_I;
extern int line_e_I;
extern int line_b_C;
extern int line_e_C;
extern char lab_I[6];
extern void reset_current_label_string(void);
extern string get_current_label_string(void);
extern void set_current_label_string(string /*ln*/);
extern bool empty_current_label_string_p(void);
extern char FormatValue[(4096)];
extern bool InParserError;
extern bool ParserError(const char */*f*/, const char */*m*/);
extern void BeginingOfParsing(void);
extern bool hpfc_parser(const string /*module*/);
extern bool parser(const string /*module*/);
extern void init_parser_properties(void);
/* procedure.c */
extern void init_ghost_variable_entities(void);
extern void substitute_ghost_variable_in_expression(expression /*expr*/, entity /*v*/, entity /*f*/);
extern void substitute_ghost_variable_in_statement(statement /*stmt*/, entity /*v*/, entity /*f*/);
extern void remove_ghost_variable_entities(bool /*substitute_p*/);
extern void add_ghost_variable_entity(entity /*e*/);
extern void reify_ghost_variable_entity(entity /*e*/);
extern bool ghost_variable_entity_p(entity /*e*/);
extern void BeginingOfProcedure(void);
extern void update_called_modules(entity /*e*/);
extern void remove_from_called_modules(entity /*e*/);
extern void AbortOfProcedure(void);
extern void EndOfProcedure(void);
extern void UpdateFunctionalType(entity /*f*/, list /*l*/);
extern void remove_module_entity(entity /*m*/);
extern void MakeCurrentFunction(type /*t*/, int /*msf*/, const char */*cfn*/, list /*lfp*/);
extern void ResetEntries(void);
extern void AbortEntries(void);
extern bool EmptyEntryListsP(void);
extern void AddEntryLabel(entity /*l*/);
extern void AddEntryTarget(statement /*s*/);
extern void AddEntryEntity(entity /*e*/);
extern void AddEffectiveFormalParameter(entity /*f*/);
extern bool IsEffectiveFormalParameterP(entity /*f*/);
extern entity SafeLocalToGlobal(entity /*e*/, type /*r*/);
extern type MakeResultType(entity /*e*/, type /*r*/);
extern entity LocalToGlobal(entity /*e*/);
extern instruction MakeEntry(entity /*e*/, list /*lfp*/);
extern void ProcessEntries(void);
extern entity NameToFunctionalEntity(string /*name*/);
extern void TypeFunctionalEntity(entity /*fe*/, type /*r*/);
extern entity MakeExternalFunction(entity /*e*/, type /*r*/);
extern entity DeclareExternalFunction(entity /*e*/);
extern void MakeFormalParameter(entity /*m*/, entity /*fp*/, int /*nfp*/);
extern void ScanFormalParameters(entity /*m*/, list /*l*/);
extern void UpdateFormalStorages(entity /*m*/, list /*lfp*/);
/* reader.c */
extern char *Comm;
extern char *PrevComm;
extern char *CurrComm;
extern int iComm;
extern int iPrevComm;
extern int iCurrComm;
extern void append_data_current_stmt_buffer_to_declarations(void);
extern void parser_reset_all_reader_buffers(void);
extern void init_parser_reader_properties(void);
extern int syn_wrap(void);
extern void ScanNewFile(void);
extern int IsCapKeyword(char */*s*/);
extern int PipsGetc(FILE */*fp*/);
extern int GetChar(FILE */*fp*/);
extern int ReadLine(FILE */*fp*/);
extern int ReadStmt(FILE */*fp*/);
extern void CheckParenthesis(void);
extern int FindDoWhile(void);
extern int FindDo(void);
extern int FindImplicit(void);
extern int FindIfArith(void);
extern void FindIf(void);
extern void FindAutre(void);
extern int FindAssign(void);
extern void FindPoints(void);
extern size_t FindProfZero(int /*c*/);
extern size_t FindMatchingPar(size_t /*i*/);
extern int StmtEqualString(char */*s*/, int /*i*/);
extern int CapitalizeStmt(char /*s*/[], int /*i*/);
extern int NeedKeyword(void);
extern void dump_current_statement(void);
extern int get_statement_number(void);
/* statement.c */
extern void parser_reset_StmtHeap_buffer(void);
extern statement LabelToStmt(string /*l*/);
extern void CheckAndInitializeStmt(void);
extern void NewStmt(entity /*e*/, statement /*s*/);
extern void ResetBlockStack(void);
extern bool IsBlockStackEmpty(void);
extern bool IsBlockStackFull(void);
extern void PushBlock(instruction /*i*/, string /*l*/);
extern instruction PopBlock(void);
extern entity MakeLabel(const char */*s*/);
extern statement MakeNewLabelledStatement(entity /*l*/, instruction /*i*/);
extern statement ReuseLabelledStatement(statement /*s*/, instruction /*i*/);
extern statement MakeStatement(entity /*l*/, instruction /*i*/);
extern void LinkInstToCurrentBlock(instruction /*i*/, bool /*number_it*/);
extern instruction MakeEmptyInstructionBlock(void);
extern instruction MakeZeroOrOneArgCallInst(char */*s*/, expression /*e*/);
extern instruction MakeGotoInst(string /*n*/);
extern instruction make_goto_instruction(entity /*l*/);
extern instruction MakeComputedGotoInst(list /*ll*/, expression /*e*/);
extern instruction MakeAssignedGotoInst(list /*ll*/, entity /*i*/);
extern instruction MakeAssignedOrComputedGotoInst(list /*ll*/, expression /*ce*/, bool /*assigned*/);
extern instruction MakeAssignInst(syntax /*l*/, expression /*e*/);
extern void update_functional_type_result(entity /*f*/, type /*nt*/);
extern void update_functional_type_with_actual_arguments(entity /*e*/, list /*l*/);
extern instruction MakeCallInst(entity /*e*/, cons */*l*/);
extern void MakeDoInst(syntax /*s*/, range /*r*/, string /*l*/);
extern void MakeWhileDoInst(expression /*c*/, string /*l*/);
extern expression fix_if_condition(expression /*e*/);
extern instruction MakeLogicalIfInst(expression /*e*/, instruction /*i*/);
extern instruction MakeArithmIfInst(expression /*e*/, string /*l1*/, string /*l2*/, string /*l3*/);
extern void MakeBlockIfInst(expression /*e*/, int /*elsif*/);
extern int MakeElseInst(bool /*is_else_p*/);
extern void MakeEndifInst(void);
extern void MakeEnddoInst(void);
extern string NameOfToken(int /*token*/);
extern statement make_check_io_statement(string /*n*/, expression /*u*/, entity /*l*/);
extern instruction MakeIoInstA(int /*keyword*/, list /*lci*/, list /*lio*/);
extern instruction MakeIoInstB(int /*keyword*/, expression /*e1*/, expression /*e2*/, expression /*e3*/, expression /*e4*/);
extern instruction MakeSimpleIoInst1(int /*keyword*/, expression unit);
extern instruction MakeSimpleIoInst2(int /*keyword*/, expression /*f*/, list /*io_list*/);
extern void reset_first_statement(void);
extern void set_first_format_statement(void);
extern bool first_executable_statement_seen(void);
extern bool first_format_statement_seen(void);
extern void check_in_declarations(void);
extern void check_first_statement(void);
/* return.c */
extern void SubstituteAlternateReturns(const char */*option*/);
extern bool SubstituteAlternateReturnsP(void);
extern entity GetReturnCodeVariable(void);
extern bool ReturnCodeVariableP(entity /*rcv*/);
extern void ResetReturnCodeVariable(void);
extern bool uses_alternate_return_p(void);
extern void uses_alternate_return(bool /*use*/);
extern void set_current_number_of_alternate_returns(void);
extern void reset_current_number_of_alternate_returns(void);
extern int get_current_number_of_alternate_returns(void);
extern list add_formal_return_code(list /*fpl*/);
extern list add_actual_return_code(list /*apl*/);
extern void add_alternate_return(string /*label_name*/);
extern list get_alternate_returns(void);
extern void set_alternate_returns(void);
extern void reset_alternate_returns(void);
extern void soft_reset_alternate_returns(void);
extern instruction generate_return_code_checks(list /*labels*/);
extern instruction MakeReturn(expression /*e*/);
extern void GenerateReturn(void);
/* malloc-info.c */
extern void print_malloc_info(FILE */*fd*/);
extern void print_full_malloc_info(FILE */*fd*/);
/* macros.c */
extern void parser_init_macros_support(void);
extern void parser_close_macros_support(void);
extern bool parser_entity_macro_p(entity /*e*/);
extern void parser_add_a_macro(call /*c*/, expression /*e*/);
extern void reset_substitute_expression_in_expression(void);
extern void parser_macro_expansion(expression /*e*/);
extern void parser_substitute_all_macros(statement /*s*/);
extern void parser_substitute_all_macros_in_expression(expression /*e*/);
/* gram.y */
extern int ici;
extern type CurrentType;
extern intptr_t CurrentTypeSize;
/* scanner.l */
extern void syn_error(const char */*msg*/);
extern void syn_reset_lex(void);
#endif /*  syntax_header_included */
