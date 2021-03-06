/*
 * THIS FILE HAS BEEN AUTOMATICALLY GENERATED BY NEWGEN.
 *
 * PLEASE DO NOT MODIFY IT.
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "genC.h"
#include "reductions_private.h"

/* PSTATEMENT_REDUCTIONS
 */
pstatement_reductions copy_pstatement_reductions(pstatement_reductions p) {
  return (pstatement_reductions) gen_copy_tree((gen_chunk*) p);
}
void free_pstatement_reductions(pstatement_reductions p) {
  gen_free((gen_chunk*) p);
}
pstatement_reductions check_pstatement_reductions(pstatement_reductions p) {
  return (pstatement_reductions) gen_check((gen_chunk*) p, pstatement_reductions_domain);
}
bool pstatement_reductions_consistent_p(pstatement_reductions p) {
  check_pstatement_reductions(p);
  return gen_consistent_p((gen_chunk*) p);
}
bool pstatement_reductions_defined_p(pstatement_reductions p) {
  return gen_defined_p((gen_chunk*) p);
}
list gen_pstatement_reductions_cons(pstatement_reductions p, list l) {
  return gen_typed_cons(PSTATEMENT_REDUCTIONS_NEWGEN_DOMAIN, p, l);
}
void pstatement_reductions_assign_contents(pstatement_reductions r, pstatement_reductions v) {
  check_pstatement_reductions(r);
  check_pstatement_reductions(v);
  message_assert("defined references to domain pstatement_reductions",
                 pstatement_reductions_defined_p(r) && pstatement_reductions_defined_p(v));
       memcpy(r, v, sizeof(struct _newgen_struct_pstatement_reductions_));
}
void pstatement_reductions_non_recursive_free(pstatement_reductions p) {
  // should clear up contents...
  free(p);
}
void write_pstatement_reductions(FILE* f, pstatement_reductions p) {
  gen_write(f, (gen_chunk*) p);
}
pstatement_reductions read_pstatement_reductions(FILE* f) {
  return (pstatement_reductions) gen_read(f);
}
pstatement_reductions make_pstatement_reductions(void) {
  return (pstatement_reductions) gen_alloc(2*sizeof(gen_chunk), GEN_CHECK_ALLOC, pstatement_reductions_domain);
}
reductions apply_pstatement_reductions(pstatement_reductions f, statement k) {
  return (reductions) (intptr_t)HASH_GET(p, p, pstatement_reductions_hash_table(f), k);
}
void update_pstatement_reductions(pstatement_reductions f, statement k, reductions v) {
  HASH_UPDATE(p, p, pstatement_reductions_hash_table(f), k, (intptr_t)v);
}
void extend_pstatement_reductions(pstatement_reductions f, statement k, reductions v) {
  HASH_EXTEND(p, p, pstatement_reductions_hash_table(f), k, (intptr_t)v);
}
reductions delete_pstatement_reductions(pstatement_reductions f, statement k) {
  return (reductions)(intptr_t) HASH_DELETE(p, p, pstatement_reductions_hash_table(f), k);
}
bool bound_pstatement_reductions_p(pstatement_reductions f, statement k) {
  return (intptr_t)HASH_BOUND_P(p, p, pstatement_reductions_hash_table(f), k);
}

/* REDUCTION_OPERATOR
 */
reduction_operator copy_reduction_operator(reduction_operator p) {
  return (reduction_operator) gen_copy_tree((gen_chunk*) p);
}
void free_reduction_operator(reduction_operator p) {
  gen_free((gen_chunk*) p);
}
reduction_operator check_reduction_operator(reduction_operator p) {
  return (reduction_operator) gen_check((gen_chunk*) p, reduction_operator_domain);
}
bool reduction_operator_consistent_p(reduction_operator p) {
  check_reduction_operator(p);
  return gen_consistent_p((gen_chunk*) p);
}
bool reduction_operator_defined_p(reduction_operator p) {
  return gen_defined_p((gen_chunk*) p);
}
list gen_reduction_operator_cons(reduction_operator p, list l) {
  return gen_typed_cons(REDUCTION_OPERATOR_NEWGEN_DOMAIN, p, l);
}
void reduction_operator_assign_contents(reduction_operator r, reduction_operator v) {
  check_reduction_operator(r);
  check_reduction_operator(v);
  message_assert("defined references to domain reduction_operator",
                 reduction_operator_defined_p(r) && reduction_operator_defined_p(v));
       memcpy(r, v, sizeof(struct _newgen_struct_reduction_operator_));
}
void reduction_operator_non_recursive_free(reduction_operator p) {
  // should clear up contents...
  free(p);
}
void write_reduction_operator(FILE* f, reduction_operator p) {
  gen_write(f, (gen_chunk*) p);
}
reduction_operator read_reduction_operator(FILE* f) {
  return (reduction_operator) gen_read(f);
}
string reduction_operator_tag_as_string(enum reduction_operator_utype tag) {
  switch (tag) {
  case is_reduction_operator_none: return "none";
  case is_reduction_operator_min: return "min";
  case is_reduction_operator_max: return "max";
  case is_reduction_operator_sum: return "sum";
  case is_reduction_operator_csum: return "csum";
  case is_reduction_operator_prod: return "prod";
  case is_reduction_operator_and: return "and";
  case is_reduction_operator_or: return "or";
  case is_reduction_operator_bitwise_and: return "bitwise_and";
  case is_reduction_operator_bitwise_or: return "bitwise_or";
  case is_reduction_operator_bitwise_xor: return "bitwise_xor";
  case is_reduction_operator_eqv: return "eqv";
  case is_reduction_operator_neqv: return "neqv";
  default: return string_undefined;
  }
}
reduction_operator make_reduction_operator(enum reduction_operator_utype tag, void * val) {
  return (reduction_operator) gen_alloc(3*sizeof(gen_chunk), GEN_CHECK_ALLOC, reduction_operator_domain, tag, val);
}
reduction_operator make_reduction_operator_none(void) {
  return make_reduction_operator(is_reduction_operator_none, UU);
}
reduction_operator make_reduction_operator_min(void) {
  return make_reduction_operator(is_reduction_operator_min, UU);
}
reduction_operator make_reduction_operator_max(void) {
  return make_reduction_operator(is_reduction_operator_max, UU);
}
reduction_operator make_reduction_operator_sum(void) {
  return make_reduction_operator(is_reduction_operator_sum, UU);
}
reduction_operator make_reduction_operator_csum(void) {
  return make_reduction_operator(is_reduction_operator_csum, UU);
}
reduction_operator make_reduction_operator_prod(void) {
  return make_reduction_operator(is_reduction_operator_prod, UU);
}
reduction_operator make_reduction_operator_and(void) {
  return make_reduction_operator(is_reduction_operator_and, UU);
}
reduction_operator make_reduction_operator_or(void) {
  return make_reduction_operator(is_reduction_operator_or, UU);
}
reduction_operator make_reduction_operator_bitwise_and(void) {
  return make_reduction_operator(is_reduction_operator_bitwise_and, UU);
}
reduction_operator make_reduction_operator_bitwise_or(void) {
  return make_reduction_operator(is_reduction_operator_bitwise_or, UU);
}
reduction_operator make_reduction_operator_bitwise_xor(void) {
  return make_reduction_operator(is_reduction_operator_bitwise_xor, UU);
}
reduction_operator make_reduction_operator_eqv(void) {
  return make_reduction_operator(is_reduction_operator_eqv, UU);
}
reduction_operator make_reduction_operator_neqv(void) {
  return make_reduction_operator(is_reduction_operator_neqv, UU);
}

/* REDUCTION
 */
reduction copy_reduction(reduction p) {
  return (reduction) gen_copy_tree((gen_chunk*) p);
}
void free_reduction(reduction p) {
  gen_free((gen_chunk*) p);
}
reduction check_reduction(reduction p) {
  return (reduction) gen_check((gen_chunk*) p, reduction_domain);
}
bool reduction_consistent_p(reduction p) {
  check_reduction(p);
  return gen_consistent_p((gen_chunk*) p);
}
bool reduction_defined_p(reduction p) {
  return gen_defined_p((gen_chunk*) p);
}
list gen_reduction_cons(reduction p, list l) {
  return gen_typed_cons(REDUCTION_NEWGEN_DOMAIN, p, l);
}
void reduction_assign_contents(reduction r, reduction v) {
  check_reduction(r);
  check_reduction(v);
  message_assert("defined references to domain reduction",
                 reduction_defined_p(r) && reduction_defined_p(v));
       memcpy(r, v, sizeof(struct _newgen_struct_reduction_));
}
void reduction_non_recursive_free(reduction p) {
  // should clear up contents...
  free(p);
}
void write_reduction(FILE* f, reduction p) {
  gen_write(f, (gen_chunk*) p);
}
reduction read_reduction(FILE* f) {
  return (reduction) gen_read(f);
}
reduction make_reduction(reference a1, reduction_operator a2, list a3, list a4) {
  return (reduction) gen_alloc(5*sizeof(gen_chunk), GEN_CHECK_ALLOC, reduction_domain, a1, a2, a3, a4);
}

/* REDUCTIONS
 */
reductions copy_reductions(reductions p) {
  return (reductions) gen_copy_tree((gen_chunk*) p);
}
void free_reductions(reductions p) {
  gen_free((gen_chunk*) p);
}
reductions check_reductions(reductions p) {
  return (reductions) gen_check((gen_chunk*) p, reductions_domain);
}
bool reductions_consistent_p(reductions p) {
  check_reductions(p);
  return gen_consistent_p((gen_chunk*) p);
}
bool reductions_defined_p(reductions p) {
  return gen_defined_p((gen_chunk*) p);
}
list gen_reductions_cons(reductions p, list l) {
  return gen_typed_cons(REDUCTIONS_NEWGEN_DOMAIN, p, l);
}
void reductions_assign_contents(reductions r, reductions v) {
  check_reductions(r);
  check_reductions(v);
  message_assert("defined references to domain reductions",
                 reductions_defined_p(r) && reductions_defined_p(v));
       memcpy(r, v, sizeof(struct _newgen_struct_reductions_));
}
void reductions_non_recursive_free(reductions p) {
  // should clear up contents...
  free(p);
}
void write_reductions(FILE* f, reductions p) {
  gen_write(f, (gen_chunk*) p);
}
reductions read_reductions(FILE* f) {
  return (reductions) gen_read(f);
}
reductions make_reductions(list a) {
  return (reductions) gen_alloc(2*sizeof(gen_chunk), GEN_CHECK_ALLOC, reductions_domain, a);
}

