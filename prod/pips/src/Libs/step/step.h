/* Warning! Do not modify this file that is automatically generated! */
/* Modify src/Libs/step/step-local.h instead, to add your own modifications. */

/* header file built by cproto */

#ifndef  step_header_included
#define  step_header_included
#include "genC.h" // for list, stack, set, ...
#include "linear.h" // needed by ri.h for Pvecteur; needed by dg.h for Ptsg
#include "ri.h" // for entity, statement, ...
#include "step_private.h" // for step_directive
#include "effects.h" // for effect


/* directives.c */
extern void get_step_directive_name(step_directive /*drt*/, string */*directive_txt*/);
extern void step_directive_type_print(step_directive /*drt*/);
extern void step_directives_print(void);
extern void step_directives_init(bool /*first_p*/);
extern void step_directives_reset(void);
extern void step_directives_save(void);
extern step_directive step_directives_load(statement /*stmt*/);
extern bool step_directives_bound_p(statement /*stmt*/);
extern void step_directives_store(statement /*stmt*/, step_directive /*d*/);
extern bool step_directive_to_strings(step_directive /*d*/, bool /*is_fortran*/, string */*begin_txt*/, string */*end_txt*/);
extern statement step_directive_basic_workchunk(step_directive /*d*/);
extern list step_directive_basic_workchunk_index(step_directive /*d*/);
extern void step_directive_print(step_directive /*d*/);
extern bool step_private_p(statement /*stmt*/, entity /*e*/);
/* analyse.c */
extern bool step_interlaced_p(effect /*reg*/);
extern bool step_partial_p(effect /*reg*/);
extern bool step_analysed_module_p(const char */*module_name*/);
extern void load_step_comm(void);
extern void reset_step_comm(void);
extern void store_step_comm(void);
extern void debug_print_effects_list(list /*l*/, string /*txt*/);
extern bool step_analyse_init(const string /*module_name*/);
extern effect rectangularization_region(effect /*reg*/);
extern bool step_analyse(const char */*module_name*/);
/* compile_RT.c */
extern expression get_expression_addr(expression /*expr*/);
extern void generate_call_construct_begin_construct_end(entity /*new_module*/, step_directive /*drt*/, statement /*mpi_begin_stmt*/, statement /*mpi_end_stmt*/);
extern void generate_call_flush(statement */*stepalltoall_stmt*/);
extern void generate_loop_workchunk(entity /*mpi_module*/, statement */*compute_regions_stmt*/);
extern void generate_call_get_workchunk_loopbounds(entity /*mpi_module*/, loop /*loop_stmt*/, statement */*compute_regions_stmt*/);
extern statement generate_call_get_rank_loopbounds(entity /*new_module*/, loop /*loop_stmt*/);
extern statement generate_call_get_rank(entity /*new_module*/);
extern statement generate_call_compute_loopslices(entity /*new_module*/, loop /*loop_stmt*/);
extern statement generate_call_get_commsize(entity /*new_module*/);
extern void generate_call_init_regionArray(list /*referenced_entities*/, statement /*before*/, statement /*after*/);
extern set step_created_entity;
extern void set_RT_add_local(entity /*e*/);
extern void step_RT_clean_local(void);
extern set step_created_symbolic;
extern entity step_parameter(string /*name_*/, entity /*module*/, expression /*expr*/);
extern entity step_symbolic(string /*name*/, entity /*module*/);
extern expression step_symbolic_expression(string /*name*/, entity /*module*/);
extern expression step_function(string /*name*/, list /*args*/);
extern void step_RT_set_local_declarations(entity /*module*/, statement /*body*/);
extern entity step_local_regionArray(entity /*module*/, entity /*array*/, string /*region_array_name*/, expression /*expr_nb_region*/);
extern entity step_local_slice_index(entity /*module*/);
extern entity step_local_loopSlices(entity /*module*/, entity /*i*/);
extern entity get_entity_step_rank(entity /*module*/);
extern entity get_entity_step_commsize(entity /*module*/);
extern entity step_local_loop_index(entity /*module*/, string /*name*/);
extern entity step_type(entity data);
extern statement build_call_STEP_init_regionArray(entity /*array*/);
extern statement build_call_STEP_AllToAll(entity /*module*/, entity /*array*/, bool /*is_partial*/, bool /*is_interlaced*/);
extern statement build_call_STEP_WaitAll(list /*comm_stmt*/);
extern statement build_call_STEP_set_sendregions(entity /*user_array*/, expression /*expr_nb_workchunk*/, entity /*regions_array*/, bool /*is_interlaced*/, bool /*is_reduction*/);
extern statement build_call_STEP_set_recvregions(entity /*user_array*/, expression /*expr_nb_workchunk*/, entity /*regions_array*/);
extern statement build_call_STEP_flush(void);
extern statement call_STEP_subroutine3(string /*name*/, ...);
extern statement call_STEP_subroutine2(string /*name*/, ...);
extern void check_entity_step_type(entity data);
extern statement call_STEP_subroutine(string /*name*/, list /*args*/, entity data);
/* compile_mpi.c */
extern statement compile_mpi(statement /*directive_stmt*/, string /*new_module_name*/, step_directive /*drt*/, int /*transformation*/);
/* compile_regions.c */
extern void compile_regions(entity /*new_module*/, list /*regions_l*/, bool /*loop_p*/, loop /*loop_stmt*/, list /*send_as_comm_l*/, set /*reductions_l*/[4], statement /*mpi_begin_stmt*/, statement /*mpi_end_stmt*/);
/* compile.c */
extern statement compile_omp(statement /*stmt*/, step_directive /*d*/);
extern void add_omp_guard(statement */*block*/);
extern void step_compile_analysed_module(const char */*module_name*/, string /*finit_name*/);
extern void step_compile_generated_module(const char */*module_name*/, string /*finit_name*/);
extern bool step_compile(const char */*module_name*/);
/* parser.c */
extern void set_current_transform(int /*transform*/);
extern void insert_optional_pragma(int type);
extern entity entity_from_user_name(string /*name*/);
extern void remove_old_pragma(void);
extern step_directive begin_omp_construct(int type, string /*s*/);
extern step_directive end_omp_construct(int type);
extern bool step_parser(const char */*module_name*/);
/* install.c */
extern bool step_install(const string /*program_name*/);
#endif /*  step_header_included */
