/*
 * THIS FILE HAS BEEN AUTOMATICALLY GENERATED BY NEWGEN.
 *
 * PLEASE DO NOT MODIFY IT.
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "genC.h"
#include "scalopes_private.h"

/* ENTITY_TASK_BUFFERS
 */
entity_task_buffers copy_entity_task_buffers(entity_task_buffers p) {
  return (entity_task_buffers) gen_copy_tree((gen_chunk*) p);
}
void free_entity_task_buffers(entity_task_buffers p) {
  gen_free((gen_chunk*) p);
}
entity_task_buffers check_entity_task_buffers(entity_task_buffers p) {
  return (entity_task_buffers) gen_check((gen_chunk*) p, entity_task_buffers_domain);
}
bool entity_task_buffers_consistent_p(entity_task_buffers p) {
  check_entity_task_buffers(p);
  return gen_consistent_p((gen_chunk*) p);
}
bool entity_task_buffers_defined_p(entity_task_buffers p) {
  return gen_defined_p((gen_chunk*) p);
}
list gen_entity_task_buffers_cons(entity_task_buffers p, list l) {
  return gen_typed_cons(ENTITY_TASK_BUFFERS_NEWGEN_DOMAIN, p, l);
}
void entity_task_buffers_assign_contents(entity_task_buffers r, entity_task_buffers v) {
  check_entity_task_buffers(r);
  check_entity_task_buffers(v);
  message_assert("defined references to domain entity_task_buffers",
                 entity_task_buffers_defined_p(r) && entity_task_buffers_defined_p(v));
       memcpy(r, v, sizeof(struct _newgen_struct_entity_task_buffers_));
}
void entity_task_buffers_non_recursive_free(entity_task_buffers p) {
  // should clear up contents...
  free(p);
}
void write_entity_task_buffers(FILE* f, entity_task_buffers p) {
  gen_write(f, (gen_chunk*) p);
}
entity_task_buffers read_entity_task_buffers(FILE* f) {
  return (entity_task_buffers) gen_read(f);
}
entity_task_buffers make_entity_task_buffers(void) {
  return (entity_task_buffers) gen_alloc(2*sizeof(gen_chunk), GEN_CHECK_ALLOC, entity_task_buffers_domain);
}
task_buffers apply_entity_task_buffers(entity_task_buffers f, entity k) {
  return (task_buffers) (intptr_t)HASH_GET(p, p, entity_task_buffers_hash_table(f), k);
}
void update_entity_task_buffers(entity_task_buffers f, entity k, task_buffers v) {
  HASH_UPDATE(p, p, entity_task_buffers_hash_table(f), k, (intptr_t)v);
}
void extend_entity_task_buffers(entity_task_buffers f, entity k, task_buffers v) {
  HASH_EXTEND(p, p, entity_task_buffers_hash_table(f), k, (intptr_t)v);
}
task_buffers delete_entity_task_buffers(entity_task_buffers f, entity k) {
  return (task_buffers)(intptr_t) HASH_DELETE(p, p, entity_task_buffers_hash_table(f), k);
}
bool bound_entity_task_buffers_p(entity_task_buffers f, entity k) {
  return (intptr_t)HASH_BOUND_P(p, p, entity_task_buffers_hash_table(f), k);
}

/* SESAM_BUFFERS_PROCESSING_CONTEXT
 */
sesam_buffers_processing_context copy_sesam_buffers_processing_context(sesam_buffers_processing_context p) {
  return (sesam_buffers_processing_context) gen_copy_tree((gen_chunk*) p);
}
void free_sesam_buffers_processing_context(sesam_buffers_processing_context p) {
  gen_free((gen_chunk*) p);
}
sesam_buffers_processing_context check_sesam_buffers_processing_context(sesam_buffers_processing_context p) {
  return (sesam_buffers_processing_context) gen_check((gen_chunk*) p, sesam_buffers_processing_context_domain);
}
bool sesam_buffers_processing_context_consistent_p(sesam_buffers_processing_context p) {
  check_sesam_buffers_processing_context(p);
  return gen_consistent_p((gen_chunk*) p);
}
bool sesam_buffers_processing_context_defined_p(sesam_buffers_processing_context p) {
  return gen_defined_p((gen_chunk*) p);
}
list gen_sesam_buffers_processing_context_cons(sesam_buffers_processing_context p, list l) {
  return gen_typed_cons(SESAM_BUFFERS_PROCESSING_CONTEXT_NEWGEN_DOMAIN, p, l);
}
void sesam_buffers_processing_context_assign_contents(sesam_buffers_processing_context r, sesam_buffers_processing_context v) {
  check_sesam_buffers_processing_context(r);
  check_sesam_buffers_processing_context(v);
  message_assert("defined references to domain sesam_buffers_processing_context",
                 sesam_buffers_processing_context_defined_p(r) && sesam_buffers_processing_context_defined_p(v));
       memcpy(r, v, sizeof(struct _newgen_struct_sesam_buffers_processing_context_));
}
void sesam_buffers_processing_context_non_recursive_free(sesam_buffers_processing_context p) {
  // should clear up contents...
  free(p);
}
void write_sesam_buffers_processing_context(FILE* f, sesam_buffers_processing_context p) {
  gen_write(f, (gen_chunk*) p);
}
sesam_buffers_processing_context read_sesam_buffers_processing_context(FILE* f) {
  return (sesam_buffers_processing_context) gen_read(f);
}
sesam_buffers_processing_context make_sesam_buffers_processing_context(set a1, set a2, entity_task_buffers a3, entity_task_buffers a4, set a5) {
  return (sesam_buffers_processing_context) gen_alloc(6*sizeof(gen_chunk), GEN_CHECK_ALLOC, sesam_buffers_processing_context_domain, a1, a2, a3, a4, a5);
}

/* TASK_BUFFERS
 */
task_buffers copy_task_buffers(task_buffers p) {
  return (task_buffers) gen_copy_tree((gen_chunk*) p);
}
void free_task_buffers(task_buffers p) {
  gen_free((gen_chunk*) p);
}
task_buffers check_task_buffers(task_buffers p) {
  return (task_buffers) gen_check((gen_chunk*) p, task_buffers_domain);
}
bool task_buffers_consistent_p(task_buffers p) {
  check_task_buffers(p);
  return gen_consistent_p((gen_chunk*) p);
}
bool task_buffers_defined_p(task_buffers p) {
  return gen_defined_p((gen_chunk*) p);
}
list gen_task_buffers_cons(task_buffers p, list l) {
  return gen_typed_cons(TASK_BUFFERS_NEWGEN_DOMAIN, p, l);
}
void task_buffers_assign_contents(task_buffers r, task_buffers v) {
  check_task_buffers(r);
  check_task_buffers(v);
  message_assert("defined references to domain task_buffers",
                 task_buffers_defined_p(r) && task_buffers_defined_p(v));
       memcpy(r, v, sizeof(struct _newgen_struct_task_buffers_));
}
void task_buffers_non_recursive_free(task_buffers p) {
  // should clear up contents...
  free(p);
}
void write_task_buffers(FILE* f, task_buffers p) {
  gen_write(f, (gen_chunk*) p);
}
task_buffers read_task_buffers(FILE* f) {
  return (task_buffers) gen_read(f);
}
task_buffers make_task_buffers(set a1, set a2) {
  return (task_buffers) gen_alloc(3*sizeof(gen_chunk), GEN_CHECK_ALLOC, task_buffers_domain, a1, a2);
}

