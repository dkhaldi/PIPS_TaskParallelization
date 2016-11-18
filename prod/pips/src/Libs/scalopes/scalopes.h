/* Warning! Do not modify this file that is automatically generated! */
/* Modify src/Libs/scalopes/scalopes-local.h instead, to add your own modifications. */

/* header file built by cproto */

#ifndef  scalopes_header_included
#define  scalopes_header_included
/* Nothing yet... */
/* scalopify.c */
extern bool scalopify(char */*module_name*/);
/* sesamify.c */
extern hash_table shared_mem;
extern hash_table entity_action;
extern bool sesamify(char */*module_name*/);
/* scalopragma.c */
extern list statement_to_outline;
extern bool scalopragma(char */*module_name*/);
/* sesam_tasks_processing.c */
extern bool sesam_buffers_processing(const char */*module_name*/);
extern bool sesam_servers_processing(const char */*module_name*/);
#endif /*  scalopes_header_included */
