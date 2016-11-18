/* Warning! Do not modify this file that is automatically generated! */
/* Modify src/Libs/c_syntax/c_syntax-local.h instead, to add your own modifications. */

/* header file built by cproto */

#ifndef  c_syntax_header_included
#define  c_syntax_header_included
/*

  $Id: c_syntax-local.h 23065 2016-03-02 09:05:50Z coelho $

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

#include "c_parser_private.h"

extern FILE * c_in; /* the file read in by the c_lexer */
extern int c_lineno ;
extern int c_lex();
extern int c_parse();

/* The labels in C have function scope... but beware of
   inlining... and conflict with user labels */
/* To disambiguate labels, in case inlining is performed later and to
   suppress the potential for conflicts with user labels.

   Temporary entities have to be generated to be replaced later by the
   final labels. The temporary entities should be eliminated from the
   symbol table...
 */
#define get_label_prefix() "-"  // a character that cannot be used in a correct

/* These global variables are declared in ri-util/util.c */
extern entity DynamicArea;
extern entity StaticArea;
extern entity HeapArea;
extern entity StackArea;
extern entity AllocatableArea;

/* Error handling */
#define FIRST_C_LINE_NUMBER (1)
#define UNDEFINED_C_LINE_NUMBER (-1)

#define CParserError(m) c_parser_error(CURRENT_FUNCTION, m)
#define c_parser_user_warning(...)                                      \
  c_parser_user_warning_func(CURRENT_FUNCTION, __FILE__, __LINE__, __VA_ARGS__)
/* c_parser.c */
extern string compilation_unit_name;
extern list CalledModules;
extern statement ModuleStatement;
extern string get_c_parser_current_input_file_name(void);
extern void set_c_parser_current_input_file_name(string /*file_name*/);
extern void reset_c_parser_current_input_file_name(void);
extern void error_reset_c_parser_current_input_file_name(void);
extern string get_c_parser_current_user_input_file_name(void);
extern void set_c_parser_current_user_input_file_name(string /*file_name*/);
extern void reset_c_parser_current_user_input_file_name(void);
extern void error_reset_c_parser_current_user_input_file_name(void);
extern stack ContextStack;
extern stack FunctionStack;
extern stack FormalStack;
extern stack OffsetStack;
extern stack StructNameStack;
extern int loop_counter;
extern int derived_counter;
extern void init_entity_type_storage_table(void);
extern void put_to_entity_type_stack_table(entity /*key*/, stack value);
extern stack get_from_entity_type_stack_table(entity /*key*/);
extern void remove_entity_type_stack(entity /*e*/);
extern void remove_entity_type_stacks(list /*el*/);
extern void reset_entity_type_stack_table(void);
extern void parser_init_keyword_typedef_table(void);
extern bool c_parser_error(const char */*func*/, const char */*msg*/);
extern void make_predefined_C_entities(string /*compilation_unit_name*/);
extern bool compilation_unit_parser_is_running_p;
extern list removable_extern_entities;
extern bool c_parser(const char */*module_name*/);
extern bool compilation_unit_parser(const char */*module_name*/);
/* statement.c */
extern stack BlockStack;
extern list LabeledStatements;
extern stack SwitchGotoStack;
extern stack SwitchControllerStack;
extern stack LoopStack;
extern void MakeCurrentModule(entity /*e*/);
extern void ResetCurrentModule(void);
extern void InitializeBlock(void);
extern statement MakeBlock(list /*stmts*/);
extern statement FindStatementFromLabel(entity /*l*/);
extern statement MakeLabeledStatement(string /*label*/, statement /*s*/, string /*comment*/);
extern statement MakeGotoStatement(string /*label*/);
extern entity MakeCLabel(string /*s*/);
extern statement MakeWhileLoop(list /*lexp*/, statement /*s*/, bool /*before*/);
extern statement MakeForloop(expression /*e1*/, expression /*e2*/, expression /*e3*/, statement /*body*/);
extern statement MakeForloopWithIndexDeclaration(list /*decls*/, expression /*e2*/, expression /*e3*/, statement /*body*/);
extern statement MakeSwitchStatement(statement /*s*/);
extern statement MakeCaseStatement(expression /*e*/);
extern statement MakeDefaultStatement(void);
extern statement MakeBreakStatement(string /*cmt*/);
extern statement MakeContinueStatement(string /*cmt*/);
extern statement ExpressionToStatement(expression /*e*/);
extern list add_prettyprint_control_list_to_declaration_statement(statement /*s*/, list /*initialization_expressions*/);
extern void set_prettyprint_control_list_to_extern(void);
extern bool extern_prettyprint_control_list_p(void);
extern void set_prettyprint_control_list_to_dummy(void);
extern bool dummy_prettyprint_control_list_p(void);
/* util.c */
extern void c_parser_user_warning_alist(const char */*pips_func*/, const char */*pips_file*/, const int /*pips_line*/, const char */*format*/, va_list */*args*/);
extern void c_parser_user_warning_func(const char */*pips_func*/, const char */*pips_file*/, const int /*pips_line*/, const char */*format*/, ...);
extern void reset_current_dummy_parameter_number(void);
extern entity get_top_level_entity(void);
extern void MakeTopLevelEntity(void);
extern void init_c_areas(void);
extern entity make_C_constant_entity(string /*name*/, tag /*bt*/, size_t /*size*/);
extern void init_c_implicit_variables(entity /*m*/);
extern entity get_current_compilation_unit_entity(void);
extern void MakeCurrentCompilationUnitEntity(const char */*name*/);
extern void ResetCurrentCompilationUnitEntity(bool /*is_compilation_unit_parser*/);
extern expression MakeFunctionExpression(expression /*e*/, list /*le*/);
extern expression MemberDerivedIdentifierToExpression(type /*t*/, string /*m*/);
extern expression MemberIdentifierToExpression(expression /*e*/, string /*m*/);
extern expression IdentifierToExpression(string /*s*/);
extern expression MakeArrayExpression(expression /*exp*/, list /*lexp*/);
extern entity FindEntityFromLocalName(string /*name*/);
extern entity FindOrCreateEntityFromLocalNameAndPrefix(string /*name*/, string /*prefix*/, bool /*is_external*/);
extern entity FindOrCreateEntityFromLocalNameAndPrefixAndScope(string /*name*/, string /*prefix*/, string /*scope*/, bool /*is_external*/);
extern entity FindEntityFromLocalNameAndPrefixAndScope(string /*name*/, string /*prefix*/, string /*scope*/);
extern entity FindEntityFromLocalNameAndPrefix(string /*name*/, string /*prefix*/);
extern entity CreateEntityFromLocalNameAndPrefix(string /*name*/, string /*prefix*/, bool /*is_external*/);
extern bool CheckExternList(void);
extern void c_parser_put_new_typedef(const char */*name*/);
extern void put_new_typedef(const char */*name*/);
extern entity FindOrCreateCurrentEntity(string /*name*/, stack /*ContextStack*/, stack /*FormalStack*/, stack /*FunctionStack*/, bool /*is_external*/);
extern void UpdateParenEntity(entity /*e*/, list /*lq*/);
extern dimension MakeDimension(list /*le*/, list /*ql*/);
extern type UpdateFinalPointer(type /*pt*/, type /*t*/);
extern void UpdatePointerEntity(entity /*e*/, type /*pt*/, list /*lq*/);
extern void UpdateArrayEntity(entity /*e*/, list /*lq*/, list /*le*/);
extern entity RenameFunctionEntity(entity /*oe*/);
extern void UpdateFunctionEntity(entity /*oe*/, list /*la*/);
extern type UpdateType(type /*t1*/, type /*t2*/);
extern void CCompilationUnitMemoryAllocations(entity /*module*/, bool /*first_p*/);
extern void CCompilationUnitMemoryAllocation(entity /*module*/);
extern void CCompilationUnitMemoryReallocation(entity /*module*/);
extern void CModuleMemoryAllocation(entity /*module*/);
extern void UseDummyArguments(entity /*f*/);
extern void UseFormalArguments(entity /*f*/);
extern void RemoveDummyArguments(entity /*f*/, list /*refs*/);
extern void SubstituteDummyParameters(entity /*f*/, list /*el*/);
extern void CreateReturnEntity(entity /*f*/);
extern void UpdateEntity2(entity /*f*/, stack /*FormalStack*/, stack /*OffsetStack*/);
extern void UpdateEntity(entity /*e*/, stack /*ContextStack*/, stack /*FormalStack*/, stack /*FunctionStack*/, stack /*OffsetStack*/, bool /*is_external*/, bool /*is_declaration*/);
extern void UpdateEntities(list /*le*/, stack /*ContextStack*/, stack /*FormalStack*/, stack /*FunctionStack*/, stack /*OffsetStack*/, bool /*is_external*/, bool /*is_declaration*/);
extern void CleanUpEntities(list /*le*/);
extern void UpdateAbstractEntity(entity /*e*/, stack /*ContextStack*/);
extern void RemoveFromExterns(entity /*e*/);
extern void AddToExterns(entity /*e*/, entity /*mod*/);
extern void AddToDeclarations(entity /*e*/, entity /*mod*/);
extern void UpdateDerivedEntity(list /*ld*/, entity /*e*/, stack /*ContextStack*/);
extern list TakeDerivedEntities(list /*le*/);
extern void UpdateDerivedEntities(list /*ld*/, list /*le*/, stack /*ContextStack*/);
extern void InitializeEnumMemberValues(list /*lem*/);
extern entity MakeDerivedEntity(string /*name*/, list /*members*/, bool /*is_external*/, int /*i*/);
extern storage MakeStorageRam(entity /*v*/, bool /*is_external*/, bool /*is_static*/);
extern string CreateMemberScope(string /*derived*/, bool /*is_external*/);
extern value MakeEnumeratorInitialValue(list /*enum_list*/, int /*counter*/);
extern int ComputeAreaOffset(entity /*a*/, entity /*v*/);
extern list MakeParameterList(list /*l1*/, list /*l2*/, stack /*FunctionStack*/);
extern parameter FindParameterEntity(string /*s*/, int /*offset*/, list /*l*/);
extern void AddToCalledModules(entity /*e*/);
extern void NStackPop(stack /*s*/, int /*n*/);
extern void StackPop(stack /*OffsetStack*/);
extern void StackPush(stack /*OffsetStack*/);
extern void set_entity_initial(entity /*v*/, expression /*nie*/);
extern bool check_declaration_uniqueness_p(statement /*s*/);
extern list insert_qualifier(list /*ql*/, qualifier /*nq*/);
extern void reset_preprocessor_line_analysis(void);
extern int analyze_preprocessor_line(string /*line*/, int /*C_line_number*/);
/* return.c */
extern entity Generate_C_ReturnLabel(entity /*m*/);
extern statement Generate_C_ReturnStatement(void);
extern void Reset_C_ReturnStatement(void);
extern statement Get_C_ReturnStatement(void);
extern statement C_MakeReturnStatement(list /*el*/, int /*ln*/, string /*c*/);
extern int GetReturnNumber(void);
extern void FixCReturnStatements(statement /*ms*/);
/* cyacc.y */
extern entity GetFunction(void);
extern void reset_expression_comment(void);
extern string pop_block_scope(string /*old_scope*/);
extern string scope_to_block_scope(string /*full_scope*/);
extern c_parser_context CreateDefaultContext(void);
extern void InitScope(void);
extern int ScopeStackSize(void);
extern string GetScope(void);
extern string GetParentScope(void);
extern void ExitScope(void);
extern void PushContext(c_parser_context /*c*/);
extern void PopContext(void);
extern c_parser_context GetContext(void);
extern c_parser_context GetContextCopy(void);
extern void reset_declaration_counter(void);
extern int get_declaration_counter(void);
extern void init_c_parser_scope_stack(void);
extern void reset_c_parser_scope_stack(void);
extern void force_reset_c_parser_scope_stack(void);
extern void push_new_c_parser_scope(void);
extern void pop_c_parser_scope_stack(void);
extern bool c_parser_scope_stack_empty_p(void);
extern string get_c_parser_current_scope(void);
extern string get_c_parser_nth_scope(int /*n*/);
extern int c_parser_number_of_scopes(void);
/* clex.l */
extern int C_line_increment;
extern int get_previous_c_lineno(void);
extern unsigned int character_occurences_in_string(string /*s*/, char /*c*/);
extern int get_current_C_line_number(void);
extern int get_previous_C_line_number(void);
extern void set_current_C_line_number(void);
extern void push_current_C_line_number(void);
extern int pop_current_C_line_number(void);
extern void reset_current_C_line_number(void);
extern void error_reset_current_C_line_number(void);
extern void reset_token_has_been_seen_p(void);
extern string get_current_C_comment(void);
extern void push_current_C_comment(void);
extern string pop_current_C_comment(void);
extern void update_C_comment(string /*a_comment*/);
extern void remove_LFs_from_C_comment(int /*extra_LF*/);
extern void discard_C_comment(void);
extern void reset_C_comment(bool /*is_compilation_unit_p*/);
extern void error_reset_C_comment(bool /*is_compilation_unit_p*/);
extern void clear_C_comment(void);
extern void init_C_comment(void);
extern void c_error(char */*msg*/);
extern void c_reset_lex(void);
extern int c_wrap(void);
#endif /*  c_syntax_header_included */
