/* Warning! Do not modify this file that is automatically generated! */
/* Modify src/Libs/modeling/modeling-local.h instead, to add your own modifications. */

/* header file built by cproto */

#ifndef  modeling_header_included
#define  modeling_header_included
// $Id: modeling-local.h 23073 2016-03-09 09:51:11Z coelho $

typedef struct
{
  stack  loops_for_call;
  stack loop_indices;
  stack current_stat;
  stack testif;
  gen_array_t nested_loops;
  gen_array_t nested_loop_indices;
  gen_array_t nested_call;
  gen_array_t nested_if;
}
  nest_context_t,
  * nest_context_p;


#define spear_error(...) \
  spear_log_func(CURRENT_FUNCTION, __FILE__, __LINE__, spear_error_log, __VA_ARGS__)

#define spear_warning(...) \
  spear_log_func(CURRENT_FUNCTION, __FILE__, __LINE__, spear_warning_log, __VA_ARGS__)
/* utils.c */
extern void spear_log_func(const char */*pips_func*/, const char */*pips_file*/, const int /*pips_line*/, pips_log_t tag, statement /*stat*/, const string /*hint*/, const string /*format*/, ...);
/* claire_prettyprinter.c */
extern bool print_claire_code_with_explicit_motif(const char */*module_name*/);
extern bool print_claire_code(const char */*module_name*/);
/* xml_prettyprinter.c */
extern bool fortran_appli;
extern char *cornerturn_info;
extern bool print_xml_code_with_explicit_motif(const char */*module_name*/);
extern bool print_xml_code(const char */*module_name*/);
extern bool vect_one_p(Pvecteur /*v*/);
extern bool vect_zero_p(Pvecteur /*v*/);
extern void insert_xml_string(const char */*module_name*/, string /*s*/);
extern void array_vars_read_or_written(list /*effects_list*/, Pvecteur */*vl*/);
extern void vars_read_and_written(list /*effects_list*/, Pvecteur */*vr*/, Pvecteur */*vw*/);
extern int find_effect_actions_for_entity(list /*leff*/, effect */*effr*/, effect */*effw*/, entity /*e*/);
extern bool eval_linear_expression(expression /*exp*/, transformer /*ps*/, int */*val*/, int */*min*/, int */*max*/);
extern bool eval_linear_expression2(expression /*exp*/, Psysteme /*ps*/, int */*val*/, int */*min*/, int */*max*/);
extern void matrix_init(Pmatrix /*mat*/, int /*n*/, int /*m*/);
extern void xml_Transposed_Matrix3_5D(Pmatrix /*mat*/, int /*a*/[12], int /*ArrayDim1*/, int /*ArrayDim2*/);
extern void xml_Argument(statement /*s*/, entity /*function*/, int /*statnb*/, bool /*assign_func*/, expression /*exp0*/, entity /*FormalName*/, Pvecteur /*loop_indices*/, transformer /*t*/, Psysteme /*prec*/, string_buffer /*sb_result*/);
extern void xml_AssignArgument(statement /*s*/, entity /*function*/, int /*statnb*/, bool /*assign_func*/, expression /*exp*/, entity /*FormalName*/, Pvecteur /*loop_indices*/, transformer /*t*/, Psysteme /*prec*/, string_buffer /*sb_result*/);
extern void xml_Chain_Graph(entity /*module*/, statement /*mod_stat*/, graph /*mod_graph*/, nest_context_p /*nest*/, string_buffer /*sb_result*/);
extern void xml_Compute_and_Need(entity /*func*/, list /*effects_list*/, Pvecteur /*vargs*/, string_buffer /*sb_result*/);
extern bool entity_main_user_module_p(entity /*e*/);
extern int find_code_status(const char */*module_name*/);
extern void insert_xml_callees(const char */*module_name*/);
extern bool print_xml_application(const char */*module_name*/);
#endif /*  modeling_header_included */
