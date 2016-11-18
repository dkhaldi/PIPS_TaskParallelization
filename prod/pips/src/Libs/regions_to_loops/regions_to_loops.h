/* Warning! Do not modify this file that is automatically generated! */
/* Modify src/Libs/regions_to_loops/regions_to_loops-local.h instead, to add your own modifications. */

/* header file built by cproto */

#ifndef  regions_to_loops_header_included
#define  regions_to_loops_header_included
//
/* regions_to_loops.c */
extern statement make_write_loopbody(entity /*v*/, expression /*exp*/, list /*vl*/);
extern statement make_read_loopbody(entity /*v*/, entity /*readVar*/, list /*vl*/);
extern statement region_to_loop_nest(effect /*r*/, bool /*isRead*/, entity /*readVar*/, expression /*exp*/);
extern expression make_addition(expression /*e1*/, expression /*e2*/);
extern void replace_indices_region(effect /*r*/, list */*dadd*/, int /*indNum*/, entity /*module*/);
extern statement make_sequence_from_statement_list(list /*l*/);
extern bool regions_to_loops(char */*module_name*/);
#endif /*  regions_to_loops_header_included */
