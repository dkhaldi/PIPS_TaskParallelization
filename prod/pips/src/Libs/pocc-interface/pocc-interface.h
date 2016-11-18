/* Warning! Do not modify this file that is automatically generated! */
/* Modify src/Libs/pocc-interface/pocc-interface-local.h instead, to add your own modifications. */

/* header file built by cproto */

#ifndef  pocc_interface_header_included
#define  pocc_interface_header_included
//
/* pocc_prettyprinter.c */
extern bool condition_body_contains_loop_p(statement /*s*/);
extern bool condition_contains_loop_p(statement /*s*/);
extern bool is_SCOP_rich(sequence /*seq*/, statement /*last_added_pragma*/, statement /*curStmt*/, bool */*pragma_added_p*/);
extern bool is_subroutine(instruction /*inst*/);
extern bool pocc_prettyprinter(char */*module_name*/);
#endif /*  pocc_interface_header_included */
