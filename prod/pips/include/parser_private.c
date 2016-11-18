/*
 * THIS FILE HAS BEEN AUTOMATICALLY GENERATED BY NEWGEN.
 *
 * PLEASE DO NOT MODIFY IT.
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "genC.h"
#include "parser_private.h"

/* ATOM
 */
atom copy_atom(atom p) {
  return (atom) gen_copy_tree((gen_chunk*) p);
}
void free_atom(atom p) {
  gen_free((gen_chunk*) p);
}
atom check_atom(atom p) {
  return (atom) gen_check((gen_chunk*) p, atom_domain);
}
bool atom_consistent_p(atom p) {
  check_atom(p);
  return gen_consistent_p((gen_chunk*) p);
}
bool atom_defined_p(atom p) {
  return gen_defined_p((gen_chunk*) p);
}
list gen_atom_cons(atom p, list l) {
  return gen_typed_cons(ATOM_NEWGEN_DOMAIN, p, l);
}
void atom_assign_contents(atom r, atom v) {
  check_atom(r);
  check_atom(v);
  message_assert("defined references to domain atom",
                 atom_defined_p(r) && atom_defined_p(v));
       memcpy(r, v, sizeof(struct _newgen_struct_atom_));
}
void atom_non_recursive_free(atom p) {
  // should clear up contents...
  free(p);
}
void write_atom(FILE* f, atom p) {
  gen_write(f, (gen_chunk*) p);
}
atom read_atom(FILE* f) {
  return (atom) gen_read(f);
}
atom make_atom(entity a1, intptr_t a2) {
  return (atom) gen_alloc(3*sizeof(gen_chunk), GEN_CHECK_ALLOC, atom_domain, a1, a2);
}

/* CHAIN
 */
chain copy_chain(chain p) {
  return (chain) gen_copy_tree((gen_chunk*) p);
}
void free_chain(chain p) {
  gen_free((gen_chunk*) p);
}
chain check_chain(chain p) {
  return (chain) gen_check((gen_chunk*) p, chain_domain);
}
bool chain_consistent_p(chain p) {
  check_chain(p);
  return gen_consistent_p((gen_chunk*) p);
}
bool chain_defined_p(chain p) {
  return gen_defined_p((gen_chunk*) p);
}
list gen_chain_cons(chain p, list l) {
  return gen_typed_cons(CHAIN_NEWGEN_DOMAIN, p, l);
}
void chain_assign_contents(chain r, chain v) {
  check_chain(r);
  check_chain(v);
  message_assert("defined references to domain chain",
                 chain_defined_p(r) && chain_defined_p(v));
       memcpy(r, v, sizeof(struct _newgen_struct_chain_));
}
void chain_non_recursive_free(chain p) {
  // should clear up contents...
  free(p);
}
void write_chain(FILE* f, chain p) {
  gen_write(f, (gen_chunk*) p);
}
chain read_chain(FILE* f) {
  return (chain) gen_read(f);
}
chain make_chain(list a) {
  return (chain) gen_alloc(2*sizeof(gen_chunk), GEN_CHECK_ALLOC, chain_domain, a);
}

/* DATA
 */
data copy_data(data p) {
  return (data) gen_copy_tree((gen_chunk*) p);
}
void free_data(data p) {
  gen_free((gen_chunk*) p);
}
data check_data(data p) {
  return (data) gen_check((gen_chunk*) p, data_domain);
}
bool data_consistent_p(data p) {
  check_data(p);
  return gen_consistent_p((gen_chunk*) p);
}
bool data_defined_p(data p) {
  return gen_defined_p((gen_chunk*) p);
}
list gen_data_cons(data p, list l) {
  return gen_typed_cons(DATA_NEWGEN_DOMAIN, p, l);
}
void data_assign_contents(data r, data v) {
  check_data(r);
  check_data(v);
  message_assert("defined references to domain data",
                 data_defined_p(r) && data_defined_p(v));
       memcpy(r, v, sizeof(struct _newgen_struct_data_));
}
void data_non_recursive_free(data p) {
  // should clear up contents...
  free(p);
}
void write_data(FILE* f, data p) {
  gen_write(f, (gen_chunk*) p);
}
data read_data(FILE* f) {
  return (data) gen_read(f);
}
data make_data(list a1, list a2) {
  return (data) gen_alloc(3*sizeof(gen_chunk), GEN_CHECK_ALLOC, data_domain, a1, a2);
}

/* DATAVAL
 */
dataval copy_dataval(dataval p) {
  return (dataval) gen_copy_tree((gen_chunk*) p);
}
void free_dataval(dataval p) {
  gen_free((gen_chunk*) p);
}
dataval check_dataval(dataval p) {
  return (dataval) gen_check((gen_chunk*) p, dataval_domain);
}
bool dataval_consistent_p(dataval p) {
  check_dataval(p);
  return gen_consistent_p((gen_chunk*) p);
}
bool dataval_defined_p(dataval p) {
  return gen_defined_p((gen_chunk*) p);
}
list gen_dataval_cons(dataval p, list l) {
  return gen_typed_cons(DATAVAL_NEWGEN_DOMAIN, p, l);
}
void dataval_assign_contents(dataval r, dataval v) {
  check_dataval(r);
  check_dataval(v);
  message_assert("defined references to domain dataval",
                 dataval_defined_p(r) && dataval_defined_p(v));
       memcpy(r, v, sizeof(struct _newgen_struct_dataval_));
}
void dataval_non_recursive_free(dataval p) {
  // should clear up contents...
  free(p);
}
void write_dataval(FILE* f, dataval p) {
  gen_write(f, (gen_chunk*) p);
}
dataval read_dataval(FILE* f) {
  return (dataval) gen_read(f);
}
dataval make_dataval(constant a1, intptr_t a2) {
  return (dataval) gen_alloc(3*sizeof(gen_chunk), GEN_CHECK_ALLOC, dataval_domain, a1, a2);
}

/* DATAVAR
 */
datavar copy_datavar(datavar p) {
  return (datavar) gen_copy_tree((gen_chunk*) p);
}
void free_datavar(datavar p) {
  gen_free((gen_chunk*) p);
}
datavar check_datavar(datavar p) {
  return (datavar) gen_check((gen_chunk*) p, datavar_domain);
}
bool datavar_consistent_p(datavar p) {
  check_datavar(p);
  return gen_consistent_p((gen_chunk*) p);
}
bool datavar_defined_p(datavar p) {
  return gen_defined_p((gen_chunk*) p);
}
list gen_datavar_cons(datavar p, list l) {
  return gen_typed_cons(DATAVAR_NEWGEN_DOMAIN, p, l);
}
void datavar_assign_contents(datavar r, datavar v) {
  check_datavar(r);
  check_datavar(v);
  message_assert("defined references to domain datavar",
                 datavar_defined_p(r) && datavar_defined_p(v));
       memcpy(r, v, sizeof(struct _newgen_struct_datavar_));
}
void datavar_non_recursive_free(datavar p) {
  // should clear up contents...
  free(p);
}
void write_datavar(FILE* f, datavar p) {
  gen_write(f, (gen_chunk*) p);
}
datavar read_datavar(FILE* f) {
  return (datavar) gen_read(f);
}
datavar make_datavar(entity a1, intptr_t a2) {
  return (datavar) gen_alloc(3*sizeof(gen_chunk), GEN_CHECK_ALLOC, datavar_domain, a1, a2);
}

/* EQUIVALENCES
 */
equivalences copy_equivalences(equivalences p) {
  return (equivalences) gen_copy_tree((gen_chunk*) p);
}
void free_equivalences(equivalences p) {
  gen_free((gen_chunk*) p);
}
equivalences check_equivalences(equivalences p) {
  return (equivalences) gen_check((gen_chunk*) p, equivalences_domain);
}
bool equivalences_consistent_p(equivalences p) {
  check_equivalences(p);
  return gen_consistent_p((gen_chunk*) p);
}
bool equivalences_defined_p(equivalences p) {
  return gen_defined_p((gen_chunk*) p);
}
list gen_equivalences_cons(equivalences p, list l) {
  return gen_typed_cons(EQUIVALENCES_NEWGEN_DOMAIN, p, l);
}
void equivalences_assign_contents(equivalences r, equivalences v) {
  check_equivalences(r);
  check_equivalences(v);
  message_assert("defined references to domain equivalences",
                 equivalences_defined_p(r) && equivalences_defined_p(v));
       memcpy(r, v, sizeof(struct _newgen_struct_equivalences_));
}
void equivalences_non_recursive_free(equivalences p) {
  // should clear up contents...
  free(p);
}
void write_equivalences(FILE* f, equivalences p) {
  gen_write(f, (gen_chunk*) p);
}
equivalences read_equivalences(FILE* f) {
  return (equivalences) gen_read(f);
}
equivalences make_equivalences(list a) {
  return (equivalences) gen_alloc(2*sizeof(gen_chunk), GEN_CHECK_ALLOC, equivalences_domain, a);
}

