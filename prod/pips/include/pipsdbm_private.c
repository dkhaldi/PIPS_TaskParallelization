/*
 * THIS FILE HAS BEEN AUTOMATICALLY GENERATED BY NEWGEN.
 *
 * PLEASE DO NOT MODIFY IT.
 */

typedef void * db_void;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "genC.h"
#include "pipsdbm_private.h"


/* DB_OWNED_RESOURCES
 */
db_owned_resources copy_db_owned_resources(db_owned_resources p) {
  return (db_owned_resources) gen_copy_tree((gen_chunk*) p);
}
void free_db_owned_resources(db_owned_resources p) {
  gen_free((gen_chunk*) p);
}
db_owned_resources check_db_owned_resources(db_owned_resources p) {
  return (db_owned_resources) gen_check((gen_chunk*) p, db_owned_resources_domain);
}
bool db_owned_resources_consistent_p(db_owned_resources p) {
  check_db_owned_resources(p);
  return gen_consistent_p((gen_chunk*) p);
}
bool db_owned_resources_defined_p(db_owned_resources p) {
  return gen_defined_p((gen_chunk*) p);
}
list gen_db_owned_resources_cons(db_owned_resources p, list l) {
  return gen_typed_cons(DB_OWNED_RESOURCES_NEWGEN_DOMAIN, p, l);
}
void db_owned_resources_assign_contents(db_owned_resources r, db_owned_resources v) {
  check_db_owned_resources(r);
  check_db_owned_resources(v);
  message_assert("defined references to domain db_owned_resources",
                 db_owned_resources_defined_p(r) && db_owned_resources_defined_p(v));
       memcpy(r, v, sizeof(struct _newgen_struct_db_owned_resources_));
}
void db_owned_resources_non_recursive_free(db_owned_resources p) {
  // should clear up contents...
  free(p);
}
void write_db_owned_resources(FILE* f, db_owned_resources p) {
  gen_write(f, (gen_chunk*) p);
}
db_owned_resources read_db_owned_resources(FILE* f) {
  return (db_owned_resources) gen_read(f);
}
db_owned_resources make_db_owned_resources(void) {
  return (db_owned_resources) gen_alloc(2*sizeof(gen_chunk), GEN_CHECK_ALLOC, db_owned_resources_domain);
}
db_resource apply_db_owned_resources(db_owned_resources f, db_symbol k) {
  return (db_resource) (intptr_t)HASH_GET(p, p, db_owned_resources_hash_table(f), k);
}
void update_db_owned_resources(db_owned_resources f, db_symbol k, db_resource v) {
  HASH_UPDATE(p, p, db_owned_resources_hash_table(f), k, (intptr_t)v);
}
void extend_db_owned_resources(db_owned_resources f, db_symbol k, db_resource v) {
  HASH_EXTEND(p, p, db_owned_resources_hash_table(f), k, (intptr_t)v);
}
db_resource delete_db_owned_resources(db_owned_resources f, db_symbol k) {
  return (db_resource)(intptr_t) HASH_DELETE(p, p, db_owned_resources_hash_table(f), k);
}
bool bound_db_owned_resources_p(db_owned_resources f, db_symbol k) {
  return (intptr_t)HASH_BOUND_P(p, p, db_owned_resources_hash_table(f), k);
}

/* DB_RESOURCE
 */
db_resource copy_db_resource(db_resource p) {
  return (db_resource) gen_copy_tree((gen_chunk*) p);
}
void free_db_resource(db_resource p) {
  gen_free((gen_chunk*) p);
}
db_resource check_db_resource(db_resource p) {
  return (db_resource) gen_check((gen_chunk*) p, db_resource_domain);
}
bool db_resource_consistent_p(db_resource p) {
  check_db_resource(p);
  return gen_consistent_p((gen_chunk*) p);
}
bool db_resource_defined_p(db_resource p) {
  return gen_defined_p((gen_chunk*) p);
}
list gen_db_resource_cons(db_resource p, list l) {
  return gen_typed_cons(DB_RESOURCE_NEWGEN_DOMAIN, p, l);
}
void db_resource_assign_contents(db_resource r, db_resource v) {
  check_db_resource(r);
  check_db_resource(v);
  message_assert("defined references to domain db_resource",
                 db_resource_defined_p(r) && db_resource_defined_p(v));
       memcpy(r, v, sizeof(struct _newgen_struct_db_resource_));
}
void db_resource_non_recursive_free(db_resource p) {
  // should clear up contents...
  free(p);
}
void write_db_resource(FILE* f, db_resource p) {
  gen_write(f, (gen_chunk*) p);
}
db_resource read_db_resource(FILE* f) {
  return (db_resource) gen_read(f);
}
db_resource make_db_resource(db_void a1, db_status a2, intptr_t a3, intptr_t a4) {
  return (db_resource) gen_alloc(5*sizeof(gen_chunk), GEN_CHECK_ALLOC, db_resource_domain, a1, a2, a3, a4);
}

/* DB_RESOURCES
 */
db_resources copy_db_resources(db_resources p) {
  return (db_resources) gen_copy_tree((gen_chunk*) p);
}
void free_db_resources(db_resources p) {
  gen_free((gen_chunk*) p);
}
db_resources check_db_resources(db_resources p) {
  return (db_resources) gen_check((gen_chunk*) p, db_resources_domain);
}
bool db_resources_consistent_p(db_resources p) {
  check_db_resources(p);
  return gen_consistent_p((gen_chunk*) p);
}
bool db_resources_defined_p(db_resources p) {
  return gen_defined_p((gen_chunk*) p);
}
list gen_db_resources_cons(db_resources p, list l) {
  return gen_typed_cons(DB_RESOURCES_NEWGEN_DOMAIN, p, l);
}
void db_resources_assign_contents(db_resources r, db_resources v) {
  check_db_resources(r);
  check_db_resources(v);
  message_assert("defined references to domain db_resources",
                 db_resources_defined_p(r) && db_resources_defined_p(v));
       memcpy(r, v, sizeof(struct _newgen_struct_db_resources_));
}
void db_resources_non_recursive_free(db_resources p) {
  // should clear up contents...
  free(p);
}
void write_db_resources(FILE* f, db_resources p) {
  gen_write(f, (gen_chunk*) p);
}
db_resources read_db_resources(FILE* f) {
  return (db_resources) gen_read(f);
}
db_resources make_db_resources(void) {
  return (db_resources) gen_alloc(2*sizeof(gen_chunk), GEN_CHECK_ALLOC, db_resources_domain);
}
db_owned_resources apply_db_resources(db_resources f, db_symbol k) {
  return (db_owned_resources) (intptr_t)HASH_GET(p, p, db_resources_hash_table(f), k);
}
void update_db_resources(db_resources f, db_symbol k, db_owned_resources v) {
  HASH_UPDATE(p, p, db_resources_hash_table(f), k, (intptr_t)v);
}
void extend_db_resources(db_resources f, db_symbol k, db_owned_resources v) {
  HASH_EXTEND(p, p, db_resources_hash_table(f), k, (intptr_t)v);
}
db_owned_resources delete_db_resources(db_resources f, db_symbol k) {
  return (db_owned_resources)(intptr_t) HASH_DELETE(p, p, db_resources_hash_table(f), k);
}
bool bound_db_resources_p(db_resources f, db_symbol k) {
  return (intptr_t)HASH_BOUND_P(p, p, db_resources_hash_table(f), k);
}

/* DB_STATUS
 */
db_status copy_db_status(db_status p) {
  return (db_status) gen_copy_tree((gen_chunk*) p);
}
void free_db_status(db_status p) {
  gen_free((gen_chunk*) p);
}
db_status check_db_status(db_status p) {
  return (db_status) gen_check((gen_chunk*) p, db_status_domain);
}
bool db_status_consistent_p(db_status p) {
  check_db_status(p);
  return gen_consistent_p((gen_chunk*) p);
}
bool db_status_defined_p(db_status p) {
  return gen_defined_p((gen_chunk*) p);
}
list gen_db_status_cons(db_status p, list l) {
  return gen_typed_cons(DB_STATUS_NEWGEN_DOMAIN, p, l);
}
void db_status_assign_contents(db_status r, db_status v) {
  check_db_status(r);
  check_db_status(v);
  message_assert("defined references to domain db_status",
                 db_status_defined_p(r) && db_status_defined_p(v));
       memcpy(r, v, sizeof(struct _newgen_struct_db_status_));
}
void db_status_non_recursive_free(db_status p) {
  // should clear up contents...
  free(p);
}
void write_db_status(FILE* f, db_status p) {
  gen_write(f, (gen_chunk*) p);
}
db_status read_db_status(FILE* f) {
  return (db_status) gen_read(f);
}
string db_status_tag_as_string(enum db_status_utype tag) {
  switch (tag) {
  case is_db_status_loaded: return "loaded";
  case is_db_status_stored: return "stored";
  case is_db_status_required: return "required";
  case is_db_status_loaded_and_stored: return "loaded_and_stored";
  default: return string_undefined;
  }
}
db_status make_db_status(enum db_status_utype tag, void * val) {
  return (db_status) gen_alloc(3*sizeof(gen_chunk), GEN_CHECK_ALLOC, db_status_domain, tag, val);
}
db_status make_db_status_loaded(void) {
  return make_db_status(is_db_status_loaded, UU);
}
db_status make_db_status_stored(void) {
  return make_db_status(is_db_status_stored, UU);
}
db_status make_db_status_required(void) {
  return make_db_status(is_db_status_required, UU);
}
db_status make_db_status_loaded_and_stored(void) {
  return make_db_status(is_db_status_loaded_and_stored, UU);
}

/* DB_SYMBOL
 */
db_symbol copy_db_symbol(db_symbol p) {
  return (db_symbol) gen_copy_tree((gen_chunk*) p);
}
void free_db_symbol(db_symbol p) {
  gen_free((gen_chunk*) p);
}
db_symbol check_db_symbol(db_symbol p) {
  return (db_symbol) gen_check((gen_chunk*) p, db_symbol_domain);
}
bool db_symbol_consistent_p(db_symbol p) {
  check_db_symbol(p);
  return gen_consistent_p((gen_chunk*) p);
}
bool db_symbol_defined_p(db_symbol p) {
  return gen_defined_p((gen_chunk*) p);
}
list gen_db_symbol_cons(db_symbol p, list l) {
  return gen_typed_cons(DB_SYMBOL_NEWGEN_DOMAIN, p, l);
}
void db_symbol_assign_contents(db_symbol r, db_symbol v) {
  check_db_symbol(r);
  check_db_symbol(v);
  message_assert("defined references to domain db_symbol",
                 db_symbol_defined_p(r) && db_symbol_defined_p(v));
       memcpy(r, v, sizeof(struct _newgen_struct_db_symbol_));
}
void db_symbol_non_recursive_free(db_symbol p) {
  // should clear up contents...
  free(p);
}
db_symbol gen_find_db_symbol(char* s) {
  return (db_symbol) gen_find_tabulated(s, db_symbol_domain);
}
void write_tabulated_db_symbol(FILE* f) {
  (void) gen_write_tabulated(f, db_symbol_domain);
}
void read_tabulated_db_symbol(FILE* f) {
  int domain = gen_read_tabulated(f, 0);
  if (domain!=db_symbol_domain) {
    fprintf(stderr, "[newgen internal error]""inconsistent domain number for db_symbol: %d (expecting %d)\n",
            domain, db_symbol_domain);
    abort();
  }
}
db_symbol make_db_symbol(string a1) {
  return (db_symbol) gen_alloc(3*sizeof(gen_chunk), GEN_CHECK_ALLOC, db_symbol_domain, a1);
}

