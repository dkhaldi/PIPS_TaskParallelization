/*
 * THIS FILE HAS BEEN AUTOMATICALLY GENERATED BY NEWGEN.
 *
 * PLEASE DO NOT MODIFY IT.
 */

typedef void * Ptsg;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "genC.h"
#include "dg.h"


/* CONE
 */
cone copy_cone(cone p) {
  return (cone) gen_copy_tree((gen_chunk*) p);
}
void free_cone(cone p) {
  gen_free((gen_chunk*) p);
}
cone check_cone(cone p) {
  return (cone) gen_check((gen_chunk*) p, cone_domain);
}
bool cone_consistent_p(cone p) {
  check_cone(p);
  return gen_consistent_p((gen_chunk*) p);
}
bool cone_defined_p(cone p) {
  return gen_defined_p((gen_chunk*) p);
}
list gen_cone_cons(cone p, list l) {
  return gen_typed_cons(CONE_NEWGEN_DOMAIN, p, l);
}
void cone_assign_contents(cone r, cone v) {
  check_cone(r);
  check_cone(v);
  message_assert("defined references to domain cone",
                 cone_defined_p(r) && cone_defined_p(v));
       memcpy(r, v, sizeof(struct _newgen_struct_cone_));
}
void cone_non_recursive_free(cone p) {
  // should clear up contents...
  free(p);
}
void write_cone(FILE* f, cone p) {
  gen_write(f, (gen_chunk*) p);
}
cone read_cone(FILE* f) {
  return (cone) gen_read(f);
}
cone make_cone(list a1, Ptsg a2) {
  return (cone) gen_alloc(3*sizeof(gen_chunk), GEN_CHECK_ALLOC, cone_domain, a1, a2);
}

/* CONFLICT
 */
conflict copy_conflict(conflict p) {
  return (conflict) gen_copy_tree((gen_chunk*) p);
}
void free_conflict(conflict p) {
  gen_free((gen_chunk*) p);
}
conflict check_conflict(conflict p) {
  return (conflict) gen_check((gen_chunk*) p, conflict_domain);
}
bool conflict_consistent_p(conflict p) {
  check_conflict(p);
  return gen_consistent_p((gen_chunk*) p);
}
bool conflict_defined_p(conflict p) {
  return gen_defined_p((gen_chunk*) p);
}
list gen_conflict_cons(conflict p, list l) {
  return gen_typed_cons(CONFLICT_NEWGEN_DOMAIN, p, l);
}
void conflict_assign_contents(conflict r, conflict v) {
  check_conflict(r);
  check_conflict(v);
  message_assert("defined references to domain conflict",
                 conflict_defined_p(r) && conflict_defined_p(v));
       memcpy(r, v, sizeof(struct _newgen_struct_conflict_));
}
void conflict_non_recursive_free(conflict p) {
  // should clear up contents...
  free(p);
}
void write_conflict(FILE* f, conflict p) {
  gen_write(f, (gen_chunk*) p);
}
conflict read_conflict(FILE* f) {
  return (conflict) gen_read(f);
}
conflict make_conflict(effect a1, effect a2, cone a3) {
  return (conflict) gen_alloc(4*sizeof(gen_chunk), GEN_CHECK_ALLOC, conflict_domain, a1, a2, a3);
}

/* DG_ARC_LABEL
 */
dg_arc_label copy_dg_arc_label(dg_arc_label p) {
  return (dg_arc_label) gen_copy_tree((gen_chunk*) p);
}
void free_dg_arc_label(dg_arc_label p) {
  gen_free((gen_chunk*) p);
}
dg_arc_label check_dg_arc_label(dg_arc_label p) {
  return (dg_arc_label) gen_check((gen_chunk*) p, dg_arc_label_domain);
}
bool dg_arc_label_consistent_p(dg_arc_label p) {
  check_dg_arc_label(p);
  return gen_consistent_p((gen_chunk*) p);
}
bool dg_arc_label_defined_p(dg_arc_label p) {
  return gen_defined_p((gen_chunk*) p);
}
list gen_dg_arc_label_cons(dg_arc_label p, list l) {
  return gen_typed_cons(DG_ARC_LABEL_NEWGEN_DOMAIN, p, l);
}
void dg_arc_label_assign_contents(dg_arc_label r, dg_arc_label v) {
  check_dg_arc_label(r);
  check_dg_arc_label(v);
  message_assert("defined references to domain dg_arc_label",
                 dg_arc_label_defined_p(r) && dg_arc_label_defined_p(v));
       memcpy(r, v, sizeof(struct _newgen_struct_dg_arc_label_));
}
void dg_arc_label_non_recursive_free(dg_arc_label p) {
  // should clear up contents...
  free(p);
}
void write_dg_arc_label(FILE* f, dg_arc_label p) {
  gen_write(f, (gen_chunk*) p);
}
dg_arc_label read_dg_arc_label(FILE* f) {
  return (dg_arc_label) gen_read(f);
}
dg_arc_label make_dg_arc_label(list a) {
  return (dg_arc_label) gen_alloc(2*sizeof(gen_chunk), GEN_CHECK_ALLOC, dg_arc_label_domain, a);
}

/* DG_VERTEX_LABEL
 */
dg_vertex_label copy_dg_vertex_label(dg_vertex_label p) {
  return (dg_vertex_label) gen_copy_tree((gen_chunk*) p);
}
void free_dg_vertex_label(dg_vertex_label p) {
  gen_free((gen_chunk*) p);
}
dg_vertex_label check_dg_vertex_label(dg_vertex_label p) {
  return (dg_vertex_label) gen_check((gen_chunk*) p, dg_vertex_label_domain);
}
bool dg_vertex_label_consistent_p(dg_vertex_label p) {
  check_dg_vertex_label(p);
  return gen_consistent_p((gen_chunk*) p);
}
bool dg_vertex_label_defined_p(dg_vertex_label p) {
  return gen_defined_p((gen_chunk*) p);
}
list gen_dg_vertex_label_cons(dg_vertex_label p, list l) {
  return gen_typed_cons(DG_VERTEX_LABEL_NEWGEN_DOMAIN, p, l);
}
void dg_vertex_label_assign_contents(dg_vertex_label r, dg_vertex_label v) {
  check_dg_vertex_label(r);
  check_dg_vertex_label(v);
  message_assert("defined references to domain dg_vertex_label",
                 dg_vertex_label_defined_p(r) && dg_vertex_label_defined_p(v));
       memcpy(r, v, sizeof(struct _newgen_struct_dg_vertex_label_));
}
void dg_vertex_label_non_recursive_free(dg_vertex_label p) {
  // should clear up contents...
  free(p);
}
void write_dg_vertex_label(FILE* f, dg_vertex_label p) {
  gen_write(f, (gen_chunk*) p);
}
dg_vertex_label read_dg_vertex_label(FILE* f) {
  return (dg_vertex_label) gen_read(f);
}
dg_vertex_label make_dg_vertex_label(intptr_t a1, sccflags a2) {
  return (dg_vertex_label) gen_alloc(3*sizeof(gen_chunk), GEN_CHECK_ALLOC, dg_vertex_label_domain, a1, a2);
}

/* SCCFLAGS
 */
sccflags copy_sccflags(sccflags p) {
  return (sccflags) gen_copy_tree((gen_chunk*) p);
}
void free_sccflags(sccflags p) {
  gen_free((gen_chunk*) p);
}
sccflags check_sccflags(sccflags p) {
  return (sccflags) gen_check((gen_chunk*) p, sccflags_domain);
}
bool sccflags_consistent_p(sccflags p) {
  check_sccflags(p);
  return gen_consistent_p((gen_chunk*) p);
}
bool sccflags_defined_p(sccflags p) {
  return gen_defined_p((gen_chunk*) p);
}
list gen_sccflags_cons(sccflags p, list l) {
  return gen_typed_cons(SCCFLAGS_NEWGEN_DOMAIN, p, l);
}
void sccflags_assign_contents(sccflags r, sccflags v) {
  check_sccflags(r);
  check_sccflags(v);
  message_assert("defined references to domain sccflags",
                 sccflags_defined_p(r) && sccflags_defined_p(v));
       memcpy(r, v, sizeof(struct _newgen_struct_sccflags_));
}
void sccflags_non_recursive_free(sccflags p) {
  // should clear up contents...
  free(p);
}
void write_sccflags(FILE* f, sccflags p) {
  gen_write(f, (gen_chunk*) p);
}
sccflags read_sccflags(FILE* f) {
  return (sccflags) gen_read(f);
}
sccflags make_sccflags(scc a1, intptr_t a2, intptr_t a3, intptr_t a4) {
  return (sccflags) gen_alloc(5*sizeof(gen_chunk), GEN_CHECK_ALLOC, sccflags_domain, a1, a2, a3, a4);
}

/* SCCS
 */
sccs copy_sccs(sccs p) {
  return (sccs) gen_copy_tree((gen_chunk*) p);
}
void free_sccs(sccs p) {
  gen_free((gen_chunk*) p);
}
sccs check_sccs(sccs p) {
  return (sccs) gen_check((gen_chunk*) p, sccs_domain);
}
bool sccs_consistent_p(sccs p) {
  check_sccs(p);
  return gen_consistent_p((gen_chunk*) p);
}
bool sccs_defined_p(sccs p) {
  return gen_defined_p((gen_chunk*) p);
}
list gen_sccs_cons(sccs p, list l) {
  return gen_typed_cons(SCCS_NEWGEN_DOMAIN, p, l);
}
void sccs_assign_contents(sccs r, sccs v) {
  check_sccs(r);
  check_sccs(v);
  message_assert("defined references to domain sccs",
                 sccs_defined_p(r) && sccs_defined_p(v));
       memcpy(r, v, sizeof(struct _newgen_struct_sccs_));
}
void sccs_non_recursive_free(sccs p) {
  // should clear up contents...
  free(p);
}
void write_sccs(FILE* f, sccs p) {
  gen_write(f, (gen_chunk*) p);
}
sccs read_sccs(FILE* f) {
  return (sccs) gen_read(f);
}
sccs make_sccs(list a) {
  return (sccs) gen_alloc(2*sizeof(gen_chunk), GEN_CHECK_ALLOC, sccs_domain, a);
}

/* SCC
 */
scc copy_scc(scc p) {
  return (scc) gen_copy_tree((gen_chunk*) p);
}
void free_scc(scc p) {
  gen_free((gen_chunk*) p);
}
scc check_scc(scc p) {
  return (scc) gen_check((gen_chunk*) p, scc_domain);
}
bool scc_consistent_p(scc p) {
  check_scc(p);
  return gen_consistent_p((gen_chunk*) p);
}
bool scc_defined_p(scc p) {
  return gen_defined_p((gen_chunk*) p);
}
list gen_scc_cons(scc p, list l) {
  return gen_typed_cons(SCC_NEWGEN_DOMAIN, p, l);
}
void scc_assign_contents(scc r, scc v) {
  check_scc(r);
  check_scc(v);
  message_assert("defined references to domain scc",
                 scc_defined_p(r) && scc_defined_p(v));
       memcpy(r, v, sizeof(struct _newgen_struct_scc_));
}
void scc_non_recursive_free(scc p) {
  // should clear up contents...
  free(p);
}
void write_scc(FILE* f, scc p) {
  gen_write(f, (gen_chunk*) p);
}
scc read_scc(FILE* f) {
  return (scc) gen_read(f);
}
scc make_scc(list a1, intptr_t a2) {
  return (scc) gen_alloc(3*sizeof(gen_chunk), GEN_CHECK_ALLOC, scc_domain, a1, a2);
}

