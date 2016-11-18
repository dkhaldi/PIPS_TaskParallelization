#ifndef _newgen_cloning_included
#define _newgen_cloning_included
#define _gen_cloning_start 166
/*
 * THIS FILE HAS BEEN AUTOMATICALLY GENERATED BY NEWGEN.
 *
 * PLEASE DO NOT MODIFY IT.
 */

#if !defined(_newgen_entity_domain_defined_)
#define _newgen_entity_domain_defined_
#define ENTITY_NEWGEN_DOMAIN (entity_domain)
#define entity_NEWGEN_DOMAIN (entity_domain)
typedef struct _newgen_struct_entity_ * entity;
#endif /* _newgen_entity_domain_defined_ */

#if !defined(_newgen_statement_domain_defined_)
#define _newgen_statement_domain_defined_
#define STATEMENT_NEWGEN_DOMAIN (statement_domain)
#define statement_NEWGEN_DOMAIN (statement_domain)
typedef struct _newgen_struct_statement_ * statement;
#endif /* _newgen_statement_domain_defined_ */

#define clone_context_domain (_gen_cloning_start+0)
#if !defined(_newgen_clone_context_domain_defined_)
#define _newgen_clone_context_domain_defined_
#define CLONE_CONTEXT_NEWGEN_DOMAIN (clone_context_domain)
#define clone_context_NEWGEN_DOMAIN (clone_context_domain)
typedef struct _newgen_struct_clone_context_ * clone_context;
#endif /* _newgen_clone_context_domain_defined_ */

/* CLONE_CONTEXT
 */
#define CLONE_CONTEXT(x) ((clone_context)((x).p))
#define clone_context_CAST(x) CLONE_CONTEXT(x)
#define CLONE_CONTEXT_CAST(x) CLONE_CONTEXT(x)
#define CLONE_CONTEXT_(x) ((x).e)
#define CLONE_CONTEXT_TYPE clone_context
#define clone_context_TYPE clone_context
#define clone_context_undefined ((clone_context)gen_chunk_undefined)
#define clone_context_undefined_p(x) ((x)==clone_context_undefined)

extern clone_context copy_clone_context(clone_context);
extern void free_clone_context(clone_context);
extern clone_context check_clone_context(clone_context);
extern bool clone_context_consistent_p(clone_context);
extern bool clone_context_defined_p(clone_context);
#define gen_CLONE_CONTEXT_cons gen_clone_context_cons
extern list gen_clone_context_cons(clone_context, list);
extern void clone_context_assign_contents(clone_context, clone_context);
extern void clone_context_non_recursive_free(clone_context);
extern void write_clone_context(FILE*, clone_context);
extern clone_context read_clone_context(FILE*);
extern clone_context make_clone_context(entity, entity, list, statement);

struct _newgen_struct_clone_context_ {
  intptr_t _type_;
  entity _clone_context_previous_module_; /* previous_module:entity */
  entity _clone_context_new_module_; /* new_module:entity */
  list _clone_context_labels_; /* labels:entity* */
  statement _clone_context_new_module_statement_; /* new_module_statement:statement */
};

#define clone_context_domain_number(x) ((x)->_type_)
#define clone_context_previous_module_(x) clone_context_previous_module(x) /* old hack compatible */
#define clone_context_previous_module(x) ((x)->_clone_context_previous_module_)
#define clone_context_new_module_(x) clone_context_new_module(x) /* old hack compatible */
#define clone_context_new_module(x) ((x)->_clone_context_new_module_)
#define clone_context_labels_(x) clone_context_labels(x) /* old hack compatible */
#define clone_context_labels(x) ((x)->_clone_context_labels_)
#define clone_context_new_module_statement_(x) clone_context_new_module_statement(x) /* old hack compatible */
#define clone_context_new_module_statement(x) ((x)->_clone_context_new_module_statement_)

#define cloning_spec "\
--NEWGEN-START 166\n\
import entity from \"ri.newgen\";\n\
import statement from \"ri.newgen\";\n\
clone_context = previous_module:entity x new_module:entity x labels:entity* x persistant new_module_statement:statement;\n\
"
#endif