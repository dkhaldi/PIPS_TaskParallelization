/*
 * THIS FILE HAS BEEN AUTOMATICALLY GENERATED BY NEWGEN.
 *
 * PLEASE DO NOT MODIFY IT.
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "genC.h"
#include "database.h"

/* DATABASE
 */
database copy_database(database p) {
  return (database) gen_copy_tree((gen_chunk*) p);
}
void free_database(database p) {
  gen_free((gen_chunk*) p);
}
database check_database(database p) {
  return (database) gen_check((gen_chunk*) p, database_domain);
}
bool database_consistent_p(database p) {
  check_database(p);
  return gen_consistent_p((gen_chunk*) p);
}
bool database_defined_p(database p) {
  return gen_defined_p((gen_chunk*) p);
}
list gen_database_cons(database p, list l) {
  return gen_typed_cons(DATABASE_NEWGEN_DOMAIN, p, l);
}
void database_assign_contents(database r, database v) {
  check_database(r);
  check_database(v);
  message_assert("defined references to domain database",
                 database_defined_p(r) && database_defined_p(v));
       memcpy(r, v, sizeof(struct _newgen_struct_database_));
}
void database_non_recursive_free(database p) {
  // should clear up contents...
  free(p);
}
void write_database(FILE* f, database p) {
  gen_write(f, (gen_chunk*) p);
}
database read_database(FILE* f) {
  return (database) gen_read(f);
}
database make_database(string a1, string a2, list a3) {
  return (database) gen_alloc(4*sizeof(gen_chunk), GEN_CHECK_ALLOC, database_domain, a1, a2, a3);
}

/* RESOURCE
 */
resource copy_resource(resource p) {
  return (resource) gen_copy_tree((gen_chunk*) p);
}
void free_resource(resource p) {
  gen_free((gen_chunk*) p);
}
resource check_resource(resource p) {
  return (resource) gen_check((gen_chunk*) p, resource_domain);
}
bool resource_consistent_p(resource p) {
  check_resource(p);
  return gen_consistent_p((gen_chunk*) p);
}
bool resource_defined_p(resource p) {
  return gen_defined_p((gen_chunk*) p);
}
list gen_resource_cons(resource p, list l) {
  return gen_typed_cons(RESOURCE_NEWGEN_DOMAIN, p, l);
}
void resource_assign_contents(resource r, resource v) {
  check_resource(r);
  check_resource(v);
  message_assert("defined references to domain resource",
                 resource_defined_p(r) && resource_defined_p(v));
       memcpy(r, v, sizeof(struct _newgen_struct_resource_));
}
void resource_non_recursive_free(resource p) {
  // should clear up contents...
  free(p);
}
void write_resource(FILE* f, resource p) {
  gen_write(f, (gen_chunk*) p);
}
resource read_resource(FILE* f) {
  return (resource) gen_read(f);
}
resource make_resource(string a1, string a2, status a3, intptr_t a4, intptr_t a5) {
  return (resource) gen_alloc(6*sizeof(gen_chunk), GEN_CHECK_ALLOC, resource_domain, a1, a2, a3, a4, a5);
}

/* STATUS
 */
status copy_status(status p) {
  return (status) gen_copy_tree((gen_chunk*) p);
}
void free_status(status p) {
  gen_free((gen_chunk*) p);
}
status check_status(status p) {
  return (status) gen_check((gen_chunk*) p, status_domain);
}
bool status_consistent_p(status p) {
  check_status(p);
  return gen_consistent_p((gen_chunk*) p);
}
bool status_defined_p(status p) {
  return gen_defined_p((gen_chunk*) p);
}
list gen_status_cons(status p, list l) {
  return gen_typed_cons(STATUS_NEWGEN_DOMAIN, p, l);
}
void status_assign_contents(status r, status v) {
  check_status(r);
  check_status(v);
  message_assert("defined references to domain status",
                 status_defined_p(r) && status_defined_p(v));
       memcpy(r, v, sizeof(struct _newgen_struct_status_));
}
void status_non_recursive_free(status p) {
  // should clear up contents...
  free(p);
}
void write_status(FILE* f, status p) {
  gen_write(f, (gen_chunk*) p);
}
status read_status(FILE* f) {
  return (status) gen_read(f);
}
string status_tag_as_string(enum status_utype tag) {
  switch (tag) {
  case is_status_memory: return "memory";
  case is_status_file: return "file";
  default: return string_undefined;
  }
}
status make_status(enum status_utype tag, void * val) {
  return (status) gen_alloc(3*sizeof(gen_chunk), GEN_CHECK_ALLOC, status_domain, tag, val);
}
status make_status_memory(string _field_) {
  return make_status(is_status_memory, (void*)(intptr_t) _field_);
}
status make_status_file(string _field_) {
  return make_status(is_status_file, (void*)(intptr_t) _field_);
}
