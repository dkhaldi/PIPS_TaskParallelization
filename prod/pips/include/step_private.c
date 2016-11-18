/*
 * THIS FILE HAS BEEN AUTOMATICALLY GENERATED BY NEWGEN.
 *
 * PLEASE DO NOT MODIFY IT.
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "genC.h"
#include "step_private.h"

/* MAP_EFFECT_BOOL
 */
map_effect_bool copy_map_effect_bool(map_effect_bool p) {
  return (map_effect_bool) gen_copy_tree((gen_chunk*) p);
}
void free_map_effect_bool(map_effect_bool p) {
  gen_free((gen_chunk*) p);
}
map_effect_bool check_map_effect_bool(map_effect_bool p) {
  return (map_effect_bool) gen_check((gen_chunk*) p, map_effect_bool_domain);
}
bool map_effect_bool_consistent_p(map_effect_bool p) {
  check_map_effect_bool(p);
  return gen_consistent_p((gen_chunk*) p);
}
bool map_effect_bool_defined_p(map_effect_bool p) {
  return gen_defined_p((gen_chunk*) p);
}
list gen_map_effect_bool_cons(map_effect_bool p, list l) {
  return gen_typed_cons(MAP_EFFECT_BOOL_NEWGEN_DOMAIN, p, l);
}
void map_effect_bool_assign_contents(map_effect_bool r, map_effect_bool v) {
  check_map_effect_bool(r);
  check_map_effect_bool(v);
  message_assert("defined references to domain map_effect_bool",
                 map_effect_bool_defined_p(r) && map_effect_bool_defined_p(v));
       memcpy(r, v, sizeof(struct _newgen_struct_map_effect_bool_));
}
void map_effect_bool_non_recursive_free(map_effect_bool p) {
  // should clear up contents...
  free(p);
}
void write_map_effect_bool(FILE* f, map_effect_bool p) {
  gen_write(f, (gen_chunk*) p);
}
map_effect_bool read_map_effect_bool(FILE* f) {
  return (map_effect_bool) gen_read(f);
}
map_effect_bool make_map_effect_bool(void) {
  return (map_effect_bool) gen_alloc(2*sizeof(gen_chunk), GEN_CHECK_ALLOC, map_effect_bool_domain);
}
bool apply_map_effect_bool(map_effect_bool f, effect k) {
  return (bool) (intptr_t)HASH_GET(p, b, map_effect_bool_hash_table(f), k);
}
void update_map_effect_bool(map_effect_bool f, effect k, bool v) {
  HASH_UPDATE(p, b, map_effect_bool_hash_table(f), k, (intptr_t)v);
}
void extend_map_effect_bool(map_effect_bool f, effect k, bool v) {
  HASH_EXTEND(p, b, map_effect_bool_hash_table(f), k, (intptr_t)v);
}
bool delete_map_effect_bool(map_effect_bool f, effect k) {
  return (bool)(intptr_t) HASH_DELETE(p, b, map_effect_bool_hash_table(f), k);
}
bool bound_map_effect_bool_p(map_effect_bool f, effect k) {
  return (intptr_t)HASH_BOUND_P(p, b, map_effect_bool_hash_table(f), k);
}

/* MAP_EFFECT_STEP_POINT
 */
map_effect_step_point copy_map_effect_step_point(map_effect_step_point p) {
  return (map_effect_step_point) gen_copy_tree((gen_chunk*) p);
}
void free_map_effect_step_point(map_effect_step_point p) {
  gen_free((gen_chunk*) p);
}
map_effect_step_point check_map_effect_step_point(map_effect_step_point p) {
  return (map_effect_step_point) gen_check((gen_chunk*) p, map_effect_step_point_domain);
}
bool map_effect_step_point_consistent_p(map_effect_step_point p) {
  check_map_effect_step_point(p);
  return gen_consistent_p((gen_chunk*) p);
}
bool map_effect_step_point_defined_p(map_effect_step_point p) {
  return gen_defined_p((gen_chunk*) p);
}
list gen_map_effect_step_point_cons(map_effect_step_point p, list l) {
  return gen_typed_cons(MAP_EFFECT_STEP_POINT_NEWGEN_DOMAIN, p, l);
}
void map_effect_step_point_assign_contents(map_effect_step_point r, map_effect_step_point v) {
  check_map_effect_step_point(r);
  check_map_effect_step_point(v);
  message_assert("defined references to domain map_effect_step_point",
                 map_effect_step_point_defined_p(r) && map_effect_step_point_defined_p(v));
       memcpy(r, v, sizeof(struct _newgen_struct_map_effect_step_point_));
}
void map_effect_step_point_non_recursive_free(map_effect_step_point p) {
  // should clear up contents...
  free(p);
}
void write_map_effect_step_point(FILE* f, map_effect_step_point p) {
  gen_write(f, (gen_chunk*) p);
}
map_effect_step_point read_map_effect_step_point(FILE* f) {
  return (map_effect_step_point) gen_read(f);
}
map_effect_step_point make_map_effect_step_point(void) {
  return (map_effect_step_point) gen_alloc(2*sizeof(gen_chunk), GEN_CHECK_ALLOC, map_effect_step_point_domain);
}
step_point apply_map_effect_step_point(map_effect_step_point f, effect k) {
  return (step_point) (intptr_t)HASH_GET(p, p, map_effect_step_point_hash_table(f), k);
}
void update_map_effect_step_point(map_effect_step_point f, effect k, step_point v) {
  HASH_UPDATE(p, p, map_effect_step_point_hash_table(f), k, (intptr_t)v);
}
void extend_map_effect_step_point(map_effect_step_point f, effect k, step_point v) {
  HASH_EXTEND(p, p, map_effect_step_point_hash_table(f), k, (intptr_t)v);
}
step_point delete_map_effect_step_point(map_effect_step_point f, effect k) {
  return (step_point)(intptr_t) HASH_DELETE(p, p, map_effect_step_point_hash_table(f), k);
}
bool bound_map_effect_step_point_p(map_effect_step_point f, effect k) {
  return (intptr_t)HASH_BOUND_P(p, p, map_effect_step_point_hash_table(f), k);
}

/* MAP_ENTITY_INT
 */
map_entity_int copy_map_entity_int(map_entity_int p) {
  return (map_entity_int) gen_copy_tree((gen_chunk*) p);
}
void free_map_entity_int(map_entity_int p) {
  gen_free((gen_chunk*) p);
}
map_entity_int check_map_entity_int(map_entity_int p) {
  return (map_entity_int) gen_check((gen_chunk*) p, map_entity_int_domain);
}
bool map_entity_int_consistent_p(map_entity_int p) {
  check_map_entity_int(p);
  return gen_consistent_p((gen_chunk*) p);
}
bool map_entity_int_defined_p(map_entity_int p) {
  return gen_defined_p((gen_chunk*) p);
}
list gen_map_entity_int_cons(map_entity_int p, list l) {
  return gen_typed_cons(MAP_ENTITY_INT_NEWGEN_DOMAIN, p, l);
}
void map_entity_int_assign_contents(map_entity_int r, map_entity_int v) {
  check_map_entity_int(r);
  check_map_entity_int(v);
  message_assert("defined references to domain map_entity_int",
                 map_entity_int_defined_p(r) && map_entity_int_defined_p(v));
       memcpy(r, v, sizeof(struct _newgen_struct_map_entity_int_));
}
void map_entity_int_non_recursive_free(map_entity_int p) {
  // should clear up contents...
  free(p);
}
void write_map_entity_int(FILE* f, map_entity_int p) {
  gen_write(f, (gen_chunk*) p);
}
map_entity_int read_map_entity_int(FILE* f) {
  return (map_entity_int) gen_read(f);
}
map_entity_int make_map_entity_int(void) {
  return (map_entity_int) gen_alloc(2*sizeof(gen_chunk), GEN_CHECK_ALLOC, map_entity_int_domain);
}
intptr_t apply_map_entity_int(map_entity_int f, entity k) {
  return (intptr_t) (intptr_t)HASH_GET(p, i, map_entity_int_hash_table(f), k);
}
void update_map_entity_int(map_entity_int f, entity k, intptr_t v) {
  HASH_UPDATE(p, i, map_entity_int_hash_table(f), k, (intptr_t)v);
}
void extend_map_entity_int(map_entity_int f, entity k, intptr_t v) {
  HASH_EXTEND(p, i, map_entity_int_hash_table(f), k, (intptr_t)v);
}
intptr_t delete_map_entity_int(map_entity_int f, entity k) {
  return (intptr_t)(intptr_t) HASH_DELETE(p, i, map_entity_int_hash_table(f), k);
}
bool bound_map_entity_int_p(map_entity_int f, entity k) {
  return (intptr_t)HASH_BOUND_P(p, i, map_entity_int_hash_table(f), k);
}

/* STEP_CLAUSE
 */
step_clause copy_step_clause(step_clause p) {
  return (step_clause) gen_copy_tree((gen_chunk*) p);
}
void free_step_clause(step_clause p) {
  gen_free((gen_chunk*) p);
}
step_clause check_step_clause(step_clause p) {
  return (step_clause) gen_check((gen_chunk*) p, step_clause_domain);
}
bool step_clause_consistent_p(step_clause p) {
  check_step_clause(p);
  return gen_consistent_p((gen_chunk*) p);
}
bool step_clause_defined_p(step_clause p) {
  return gen_defined_p((gen_chunk*) p);
}
list gen_step_clause_cons(step_clause p, list l) {
  return gen_typed_cons(STEP_CLAUSE_NEWGEN_DOMAIN, p, l);
}
void step_clause_assign_contents(step_clause r, step_clause v) {
  check_step_clause(r);
  check_step_clause(v);
  message_assert("defined references to domain step_clause",
                 step_clause_defined_p(r) && step_clause_defined_p(v));
       memcpy(r, v, sizeof(struct _newgen_struct_step_clause_));
}
void step_clause_non_recursive_free(step_clause p) {
  // should clear up contents...
  free(p);
}
void write_step_clause(FILE* f, step_clause p) {
  gen_write(f, (gen_chunk*) p);
}
step_clause read_step_clause(FILE* f) {
  return (step_clause) gen_read(f);
}
string step_clause_tag_as_string(enum step_clause_utype tag) {
  switch (tag) {
  case is_step_clause_reduction: return "reduction";
  case is_step_clause_private: return "private";
  case is_step_clause_shared: return "shared";
  case is_step_clause_transformation: return "transformation";
  case is_step_clause_nowait: return "nowait";
  case is_step_clause_threadprivate: return "threadprivate";
  case is_step_clause_copyin: return "copyin";
  case is_step_clause_firstprivate: return "firstprivate";
  case is_step_clause_schedule: return "schedule";
  default: return string_undefined;
  }
}
step_clause make_step_clause(enum step_clause_utype tag, void * val) {
  return (step_clause) gen_alloc(3*sizeof(gen_chunk), GEN_CHECK_ALLOC, step_clause_domain, tag, val);
}
step_clause make_step_clause_reduction(map_entity_int _field_) {
  return make_step_clause(is_step_clause_reduction, (void*)(intptr_t) _field_);
}
step_clause make_step_clause_private(list _field_) {
  return make_step_clause(is_step_clause_private, (void*)(intptr_t) _field_);
}
step_clause make_step_clause_shared(list _field_) {
  return make_step_clause(is_step_clause_shared, (void*)(intptr_t) _field_);
}
step_clause make_step_clause_transformation(intptr_t _field_) {
  return make_step_clause(is_step_clause_transformation, (void*)(intptr_t) _field_);
}
step_clause make_step_clause_nowait(void) {
  return make_step_clause(is_step_clause_nowait, UU);
}
step_clause make_step_clause_threadprivate(list _field_) {
  return make_step_clause(is_step_clause_threadprivate, (void*)(intptr_t) _field_);
}
step_clause make_step_clause_copyin(list _field_) {
  return make_step_clause(is_step_clause_copyin, (void*)(intptr_t) _field_);
}
step_clause make_step_clause_firstprivate(list _field_) {
  return make_step_clause(is_step_clause_firstprivate, (void*)(intptr_t) _field_);
}
step_clause make_step_clause_schedule(list _field_) {
  return make_step_clause(is_step_clause_schedule, (void*)(intptr_t) _field_);
}

/* STEP_COMM
 */
step_comm copy_step_comm(step_comm p) {
  return (step_comm) gen_copy_tree((gen_chunk*) p);
}
void free_step_comm(step_comm p) {
  gen_free((gen_chunk*) p);
}
step_comm check_step_comm(step_comm p) {
  return (step_comm) gen_check((gen_chunk*) p, step_comm_domain);
}
bool step_comm_consistent_p(step_comm p) {
  check_step_comm(p);
  return gen_consistent_p((gen_chunk*) p);
}
bool step_comm_defined_p(step_comm p) {
  return gen_defined_p((gen_chunk*) p);
}
list gen_step_comm_cons(step_comm p, list l) {
  return gen_typed_cons(STEP_COMM_NEWGEN_DOMAIN, p, l);
}
void step_comm_assign_contents(step_comm r, step_comm v) {
  check_step_comm(r);
  check_step_comm(v);
  message_assert("defined references to domain step_comm",
                 step_comm_defined_p(r) && step_comm_defined_p(v));
       memcpy(r, v, sizeof(struct _newgen_struct_step_comm_));
}
void step_comm_non_recursive_free(step_comm p) {
  // should clear up contents...
  free(p);
}
void write_step_comm(FILE* f, step_comm p) {
  gen_write(f, (gen_chunk*) p);
}
step_comm read_step_comm(FILE* f) {
  return (step_comm) gen_read(f);
}
step_comm make_step_comm(map_effect_step_point a1, map_effect_bool a2, map_effect_bool a3) {
  return (step_comm) gen_alloc(4*sizeof(gen_chunk), GEN_CHECK_ALLOC, step_comm_domain, a1, a2, a3);
}

/* STEP_DIRECTIVES
 */
step_directives copy_step_directives(step_directives p) {
  return (step_directives) gen_copy_tree((gen_chunk*) p);
}
void free_step_directives(step_directives p) {
  gen_free((gen_chunk*) p);
}
step_directives check_step_directives(step_directives p) {
  return (step_directives) gen_check((gen_chunk*) p, step_directives_domain);
}
bool step_directives_consistent_p(step_directives p) {
  check_step_directives(p);
  return gen_consistent_p((gen_chunk*) p);
}
bool step_directives_defined_p(step_directives p) {
  return gen_defined_p((gen_chunk*) p);
}
list gen_step_directives_cons(step_directives p, list l) {
  return gen_typed_cons(STEP_DIRECTIVES_NEWGEN_DOMAIN, p, l);
}
void step_directives_assign_contents(step_directives r, step_directives v) {
  check_step_directives(r);
  check_step_directives(v);
  message_assert("defined references to domain step_directives",
                 step_directives_defined_p(r) && step_directives_defined_p(v));
       memcpy(r, v, sizeof(struct _newgen_struct_step_directives_));
}
void step_directives_non_recursive_free(step_directives p) {
  // should clear up contents...
  free(p);
}
void write_step_directives(FILE* f, step_directives p) {
  gen_write(f, (gen_chunk*) p);
}
step_directives read_step_directives(FILE* f) {
  return (step_directives) gen_read(f);
}
step_directives make_step_directives(void) {
  return (step_directives) gen_alloc(2*sizeof(gen_chunk), GEN_CHECK_ALLOC, step_directives_domain);
}
step_directive apply_step_directives(step_directives f, statement k) {
  return (step_directive) (intptr_t)HASH_GET(p, p, step_directives_hash_table(f), k);
}
void update_step_directives(step_directives f, statement k, step_directive v) {
  HASH_UPDATE(p, p, step_directives_hash_table(f), k, (intptr_t)v);
}
void extend_step_directives(step_directives f, statement k, step_directive v) {
  HASH_EXTEND(p, p, step_directives_hash_table(f), k, (intptr_t)v);
}
step_directive delete_step_directives(step_directives f, statement k) {
  return (step_directive)(intptr_t) HASH_DELETE(p, p, step_directives_hash_table(f), k);
}
bool bound_step_directives_p(step_directives f, statement k) {
  return (intptr_t)HASH_BOUND_P(p, p, step_directives_hash_table(f), k);
}

/* STEP_DIRECTIVE
 */
step_directive copy_step_directive(step_directive p) {
  return (step_directive) gen_copy_tree((gen_chunk*) p);
}
void free_step_directive(step_directive p) {
  gen_free((gen_chunk*) p);
}
step_directive check_step_directive(step_directive p) {
  return (step_directive) gen_check((gen_chunk*) p, step_directive_domain);
}
bool step_directive_consistent_p(step_directive p) {
  check_step_directive(p);
  return gen_consistent_p((gen_chunk*) p);
}
bool step_directive_defined_p(step_directive p) {
  return gen_defined_p((gen_chunk*) p);
}
list gen_step_directive_cons(step_directive p, list l) {
  return gen_typed_cons(STEP_DIRECTIVE_NEWGEN_DOMAIN, p, l);
}
void step_directive_assign_contents(step_directive r, step_directive v) {
  check_step_directive(r);
  check_step_directive(v);
  message_assert("defined references to domain step_directive",
                 step_directive_defined_p(r) && step_directive_defined_p(v));
       memcpy(r, v, sizeof(struct _newgen_struct_step_directive_));
}
void step_directive_non_recursive_free(step_directive p) {
  // should clear up contents...
  free(p);
}
void write_step_directive(FILE* f, step_directive p) {
  gen_write(f, (gen_chunk*) p);
}
step_directive read_step_directive(FILE* f) {
  return (step_directive) gen_read(f);
}
step_directive make_step_directive(intptr_t a1, statement a2, list a3) {
  return (step_directive) gen_alloc(4*sizeof(gen_chunk), GEN_CHECK_ALLOC, step_directive_domain, a1, a2, a3);
}

/* STEP_POINT
 */
step_point copy_step_point(step_point p) {
  return (step_point) gen_copy_tree((gen_chunk*) p);
}
void free_step_point(step_point p) {
  gen_free((gen_chunk*) p);
}
step_point check_step_point(step_point p) {
  return (step_point) gen_check((gen_chunk*) p, step_point_domain);
}
bool step_point_consistent_p(step_point p) {
  check_step_point(p);
  return gen_consistent_p((gen_chunk*) p);
}
bool step_point_defined_p(step_point p) {
  return gen_defined_p((gen_chunk*) p);
}
list gen_step_point_cons(step_point p, list l) {
  return gen_typed_cons(STEP_POINT_NEWGEN_DOMAIN, p, l);
}
void step_point_assign_contents(step_point r, step_point v) {
  check_step_point(r);
  check_step_point(v);
  message_assert("defined references to domain step_point",
                 step_point_defined_p(r) && step_point_defined_p(v));
       memcpy(r, v, sizeof(struct _newgen_struct_step_point_));
}
void step_point_non_recursive_free(step_point p) {
  // should clear up contents...
  free(p);
}
void write_step_point(FILE* f, step_point p) {
  gen_write(f, (gen_chunk*) p);
}
step_point read_step_point(FILE* f) {
  return (step_point) gen_read(f);
}
step_point make_step_point(entity a1, statement a2, effect a3) {
  return (step_point) gen_alloc(4*sizeof(gen_chunk), GEN_CHECK_ALLOC, step_point_domain, a1, a2, a3);
}

