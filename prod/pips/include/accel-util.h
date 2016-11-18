/* Warning! Do not modify this file that is automatically generated! */
/* Modify src/Libs/accel-util/accel-util-local.h instead, to add your own modifications. */

/* header file built by cproto */

#ifndef  accel_util_header_included
#define  accel_util_header_included

enum region_to_dma_switch { dma_load, dma_store, dma_allocate, dma_deallocate };
/* Add NewGen-like methods: */
#define dma_load_p(e) ((e) == dma_load )
#define dma_store_p(e) ((e) == dma_store )
#define dma_allocate_p(e) ((e) == dma_allocate )
#define dma_deallocate_p(e) ((e) == dma_deallocate )

#define OUTLINE_PRAGMA "outline this"
#define OUTLINE_IGNORE "outline_ignore"


/* Dependences for accel-util.h */
#include "transformer.h"
#include "effects.h"
/* group_constants.c */
extern bool group_constants(const string /*module_name*/);
/* isolate_statement.c */
extern void region_to_dimensions(effect /*reg*/, transformer /*tr*/, list */*dimensions*/, list */*offsets*/, expression */*condition*/);
extern list variable_to_dimensions(effect /*reg_from*/);
extern call dimensions_to_dma(effect /*reg_from*/, entity /*to*/, list /*ld*/, list /*lo*/, enum region_to_dma_switch /*m*/);
extern void do_isolate_statement(statement /*s*/, const char */*prefix*/, const char */*suffix*/);
extern void isolate_patch_entities(void */*where*/, entity /*old*/, entity /*new*/, list /*offsets*/);
extern bool region_to_minimal_dimensions(effect /*r*/, transformer /*tr*/, list */*dims*/, list */*offsets*/, bool /*exact*/, expression */*condition*/);
extern effect find_region_on_entity(entity /*e*/, list /*regions*/);
extern range dimension_to_range(dimension /*d*/);
extern bool isolate_statement(const char */*module_name*/);
/* statement_insertion.c */
extern bool statement_insertion(const char */*module_name*/);
extern bool array_expansion(const char */*module_name*/);
/* loop_expansion.c */
extern bool loop_expansion(const char */*module_name*/);
extern bool loop_expansion_init(const char */*module_name*/);
/* outlining.c */
extern list outliner_statements_referenced_entities(list /*statements*/);
extern hash_table outliner_init(entity /*new_fun*/, list /*statements_to_outline*/);
extern list outliner_scan(entity /*new_fun*/, list /*statements_to_outline*/, statement /*new_body*/);
extern bool is_entity_in_list(entity /*e*/, list /*l*/);
extern void outliner_parameters(entity /*new_fun*/, statement /*new_body*/, list /*referenced_entities*/, hash_table /*entity_to_effective_parameter*/, list */*effective_parameters_*/, list */*formal_parameters_*/);
extern void outliner_patch_parameters(list /*statements_to_outline*/, list /*referenced_entities*/, list /*effective_parameters*/, list /*formal_parameters*/, statement /*new_body*/, statement /*begin*/, statement /*end*/);
extern void outliner_file(entity /*new_fun*/, list /*formal_parameters*/, statement */*new_body*/);
extern statement outliner_call(entity /*new_fun*/, list /*statements_to_outline*/, list /*effective_parameters*/);
extern void remove_from_formal_parameters(list /*induction_var*/, list */*formal_parameters*/);
extern void remove_from_effective_parameters(list /*induction_var*/, list */*effective_parameters*/);
extern void add_induction_var_to_local_declarations(statement */*new_body*/, list /*induction_var*/);
extern statement outliner(const char */*outline_module_name*/, list /*statements_to_outline*/);
extern bool outline(const string /*module_name*/);
/* array_to_pointer.c */
extern bool do_convert_this_array_to_pointer_p(entity /*e*/);
extern size_t type_dereferencement_depth(type /*t*/);
extern bool linearize_array_generic(const char */*module_name*/);
extern bool linearize_array(const char */*module_name*/);
extern bool linearize_array_fortran(const char */*module_name*/);
/* inlining.c */
extern bool has_entity_with_same_name(entity /*e*/, list /*l*/);
extern bool inlining(const char */*module_name*/);
extern bool inlining_simple(const char */*module_name*/);
extern bool unfolding(char */*module_name*/);
extern bool unfolding_simple(char */*module_name*/);
/* kernels.c */
extern bool kernel_load_store(const char */*module_name*/);
extern bool kernelize(const string /*module_name*/);
extern bool flag_kernel(const string /*module_name*/);
extern bool bootstrap_kernels(const string /*module_name*/);
/* ikernels.c */
extern void dump_entity_set(set /*s*/);
extern bool is_a_kernel(const char */*func_name*/);
extern bool ikernel_load_store(char */*module_name*/);
extern bool kernel_data_mapping(char */*module_name*/);
extern bool wrap_kernel_argument(char */*module_name*/);
/* terapixify.c */
extern void normalize_microcode_anotate(void);
extern void terapix_loop_optimizer(statement /*st*/);
extern bool normalize_microcode(char */*module_name*/);
extern bool terapix_warmup(const char */*module_name*/);
extern bool generate_two_addresses_code(const string /*module_name*/);
extern bool terapix_remove_divide(const string /*module_name*/);
/* constraints.c */
extern bool solve_hardware_constraints(const char */*module_name*/);
/* delay.c */
extern void remove_preferences(void */*obj*/);
extern bool simd_load_stat_p(statement /*stat*/);
extern bool simd_work_stat_p(statement /*stat*/);
extern bool simd_store_stat_p(statement /*stat*/);
extern bool simd_dma_stat_p(statement /*stat*/);
extern bool simd_stat_p(statement /*stat*/);
extern bool delay_load_communications(char */*module_name*/);
extern bool delay_load_communications_inter(char */*module_name*/);
extern bool delay_load_communications_intra(char */*module_name*/);
extern bool delay_store_communications(char */*module_name*/);
extern bool delay_store_communications_inter(char */*module_name*/);
extern bool delay_store_communications_intra(char */*module_name*/);
extern bool delay_communications_inter(const char */*module_name*/);
extern bool delay_communications_intra(const char */*module_name*/);
/* gpu_promote_sequential.c */
extern void gpu_promote_sequential_on_sequence(sequence /*seq*/, loop /*l*/);
extern void gpu_promote_sequential_on_statement(statement /*s*/);
extern bool gpu_promote_sequential(const char */*module_name*/);
/* computation_intensity.c */
extern bool computation_intensity(const char */*module_name*/);
/* manage_pragma.c */
extern bool statement_has_omp_parallel_directive_p(statement /*s*/);
extern bool pragma_omp_p(pragma /*p*/);
extern bool omp_merge_pragma(const char */*module_name*/);
extern bool omp_loop_parallel_threshold_set(const char */*module_name*/);
extern void clear_pragma_on_statement(statement /*s*/);
extern bool clear_pragma(const char */*module_name*/);
extern bool outline_stmts_between_pragmas_in_sequence(sequence /*s*/, void */*_ctx*/);
extern bool pragma_outliner(char */*module_name*/);
/* generate_pragma.c */
extern bool ompify_code(const char */*module_name*/);
/* misc.c */
extern void get_variables_to_remove(list /*ref_ent*/, statement /*s*/, list */*l*/);
#endif /*  accel_util_header_included */
