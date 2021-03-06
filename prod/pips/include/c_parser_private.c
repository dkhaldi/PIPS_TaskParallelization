/*
 * THIS FILE HAS BEEN AUTOMATICALLY GENERATED BY NEWGEN.
 *
 * PLEASE DO NOT MODIFY IT.
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "genC.h"
#include "c_parser_private.h"

/* C_PARSER_CONTEXT
 */
c_parser_context copy_c_parser_context(c_parser_context p) {
  return (c_parser_context) gen_copy_tree((gen_chunk*) p);
}
void free_c_parser_context(c_parser_context p) {
  gen_free((gen_chunk*) p);
}
c_parser_context check_c_parser_context(c_parser_context p) {
  return (c_parser_context) gen_check((gen_chunk*) p, c_parser_context_domain);
}
bool c_parser_context_consistent_p(c_parser_context p) {
  check_c_parser_context(p);
  return gen_consistent_p((gen_chunk*) p);
}
bool c_parser_context_defined_p(c_parser_context p) {
  return gen_defined_p((gen_chunk*) p);
}
list gen_c_parser_context_cons(c_parser_context p, list l) {
  return gen_typed_cons(C_PARSER_CONTEXT_NEWGEN_DOMAIN, p, l);
}
void c_parser_context_assign_contents(c_parser_context r, c_parser_context v) {
  check_c_parser_context(r);
  check_c_parser_context(v);
  message_assert("defined references to domain c_parser_context",
                 c_parser_context_defined_p(r) && c_parser_context_defined_p(v));
       memcpy(r, v, sizeof(struct _newgen_struct_c_parser_context_));
}
void c_parser_context_non_recursive_free(c_parser_context p) {
  // should clear up contents...
  free(p);
}
void write_c_parser_context(FILE* f, c_parser_context p) {
  gen_write(f, (gen_chunk*) p);
}
c_parser_context read_c_parser_context(FILE* f) {
  return (c_parser_context) gen_read(f);
}
c_parser_context make_c_parser_context(string a1, type a2, storage a3, list a4, bool a5, bool a6) {
  return (c_parser_context) gen_alloc(7*sizeof(gen_chunk), GEN_CHECK_ALLOC, c_parser_context_domain, a1, a2, a3, a4, a5, a6);
}

