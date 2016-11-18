/* Warning! Do not modify this file that is automatically generated! */
/* Modify src/Libs/gpu/gpu-local.h instead, to add your own modifications. */

/* header file built by cproto */

#ifndef  gpu_header_included
#define  gpu_header_included
/* Nothing yet... */
/* gpu-ify.c */
extern string build_outline_name(const char */*base_prefix*/, const char */*mod_name*/);
extern bool gpu_ify(const string /*mod_name*/);
/* xml_output.c */
extern void xml_print_entity_full(entity /*e*/);
extern void gather_grid_dim(statement /*s*/, void */*ctx*/);
extern bool gpu_xml_dump(string /*mod_name*/);
/* loop_nest_annotate.c */
extern bool gpu_loop_nest_annotate_on_statement(statement /*s*/);
extern bool gpu_loop_nest_annotate(const char */*module_name*/);
extern bool gpu_parallelize_annotated_loop_nest(const string /*mod_name*/);
extern bool clear_annotated_loop_nest(statement /*s*/);
extern bool gpu_clear_annotations_on_loop_nest(const string /*mod_name*/);
/* one_thread_kernel.c */
extern bool one_thread_parallelize(string /*mod_name*/);
/* gpu_qualify_pointers.c */
extern void do_gpu_qualify_pointers(entity /*module*/, statement code, callees /*funcs*/, bool /*do_casts*/);
extern bool gpu_qualify_pointers(const string /*module_name*/);
#endif /*  gpu_header_included */
