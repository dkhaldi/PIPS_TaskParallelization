#ifndef _newgen_scalopes_private_included
#define _newgen_scalopes_private_included
#define _gen_scalopes_private_start 214
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

#if !defined(_newgen_effect_domain_defined_)
#define _newgen_effect_domain_defined_
#define EFFECT_NEWGEN_DOMAIN (effect_domain)
#define effect_NEWGEN_DOMAIN (effect_domain)
typedef struct _newgen_struct_effect_ * effect;
#endif /* _newgen_effect_domain_defined_ */

#define entity_task_buffers_domain (_gen_scalopes_private_start+0)
#if !defined(_newgen_entity_task_buffers_domain_defined_)
#define _newgen_entity_task_buffers_domain_defined_
#define ENTITY_TASK_BUFFERS_NEWGEN_DOMAIN (entity_task_buffers_domain)
#define entity_task_buffers_NEWGEN_DOMAIN (entity_task_buffers_domain)
typedef struct _newgen_struct_entity_task_buffers_ * entity_task_buffers;
#endif /* _newgen_entity_task_buffers_domain_defined_ */

#define sesam_buffers_processing_context_domain (_gen_scalopes_private_start+1)
#if !defined(_newgen_sesam_buffers_processing_context_domain_defined_)
#define _newgen_sesam_buffers_processing_context_domain_defined_
#define SESAM_BUFFERS_PROCESSING_CONTEXT_NEWGEN_DOMAIN (sesam_buffers_processing_context_domain)
#define sesam_buffers_processing_context_NEWGEN_DOMAIN (sesam_buffers_processing_context_domain)
typedef struct _newgen_struct_sesam_buffers_processing_context_ * sesam_buffers_processing_context;
#endif /* _newgen_sesam_buffers_processing_context_domain_defined_ */

#define task_buffers_domain (_gen_scalopes_private_start+2)
#if !defined(_newgen_task_buffers_domain_defined_)
#define _newgen_task_buffers_domain_defined_
#define TASK_BUFFERS_NEWGEN_DOMAIN (task_buffers_domain)
#define task_buffers_NEWGEN_DOMAIN (task_buffers_domain)
typedef struct _newgen_struct_task_buffers_ * task_buffers;
#endif /* _newgen_task_buffers_domain_defined_ */

/* ENTITY_TASK_BUFFERS
 */
#define ENTITY_TASK_BUFFERS(x) ((entity_task_buffers)((x).p))
#define entity_task_buffers_CAST(x) ENTITY_TASK_BUFFERS(x)
#define ENTITY_TASK_BUFFERS_CAST(x) ENTITY_TASK_BUFFERS(x)
#define ENTITY_TASK_BUFFERS_(x) ((x).e)
#define ENTITY_TASK_BUFFERS_TYPE entity_task_buffers
#define entity_task_buffers_TYPE entity_task_buffers
#define entity_task_buffers_undefined ((entity_task_buffers)gen_chunk_undefined)
#define entity_task_buffers_undefined_p(x) ((x)==entity_task_buffers_undefined)

extern entity_task_buffers copy_entity_task_buffers(entity_task_buffers);
extern void free_entity_task_buffers(entity_task_buffers);
extern entity_task_buffers check_entity_task_buffers(entity_task_buffers);
extern bool entity_task_buffers_consistent_p(entity_task_buffers);
extern bool entity_task_buffers_defined_p(entity_task_buffers);
#define gen_ENTITY_TASK_BUFFERS_cons gen_entity_task_buffers_cons
extern list gen_entity_task_buffers_cons(entity_task_buffers, list);
extern void entity_task_buffers_assign_contents(entity_task_buffers, entity_task_buffers);
extern void entity_task_buffers_non_recursive_free(entity_task_buffers);
extern void write_entity_task_buffers(FILE*, entity_task_buffers);
extern entity_task_buffers read_entity_task_buffers(FILE*);
extern entity_task_buffers make_entity_task_buffers(void);

struct _newgen_struct_entity_task_buffers_ {
  intptr_t _type_;
  hash_table _entity_task_buffers_holder_;
};

#define entity_task_buffers_domain_number(x) ((x)->_type_)
#define entity_task_buffers_hash_table(x) ((x)->_entity_task_buffers_holder_)
#define entity_task_buffers_key_type entity
#define entity_task_buffers_value_type task_buffers
#define ENTITY_TASK_BUFFERS_MAP(k,v,c,f) FUNCTION_MAP(entity_task_buffers,p,p,k,v,c,f)
#define ENTITY_TASK_BUFFERS_FOREACH(k,v,f) FUNCTION_FOREACH(entity_task_buffers,p,p,k,v,f)
extern task_buffers apply_entity_task_buffers(entity_task_buffers, entity);
extern void update_entity_task_buffers(entity_task_buffers, entity, task_buffers);
extern void extend_entity_task_buffers(entity_task_buffers, entity, task_buffers);
extern task_buffers delete_entity_task_buffers(entity_task_buffers, entity);
extern bool bound_entity_task_buffers_p(entity_task_buffers, entity);

/* SESAM_BUFFERS_PROCESSING_CONTEXT
 */
#define SESAM_BUFFERS_PROCESSING_CONTEXT(x) ((sesam_buffers_processing_context)((x).p))
#define sesam_buffers_processing_context_CAST(x) SESAM_BUFFERS_PROCESSING_CONTEXT(x)
#define SESAM_BUFFERS_PROCESSING_CONTEXT_CAST(x) SESAM_BUFFERS_PROCESSING_CONTEXT(x)
#define SESAM_BUFFERS_PROCESSING_CONTEXT_(x) ((x).e)
#define SESAM_BUFFERS_PROCESSING_CONTEXT_TYPE sesam_buffers_processing_context
#define sesam_buffers_processing_context_TYPE sesam_buffers_processing_context
#define sesam_buffers_processing_context_undefined ((sesam_buffers_processing_context)gen_chunk_undefined)
#define sesam_buffers_processing_context_undefined_p(x) ((x)==sesam_buffers_processing_context_undefined)

extern sesam_buffers_processing_context copy_sesam_buffers_processing_context(sesam_buffers_processing_context);
extern void free_sesam_buffers_processing_context(sesam_buffers_processing_context);
extern sesam_buffers_processing_context check_sesam_buffers_processing_context(sesam_buffers_processing_context);
extern bool sesam_buffers_processing_context_consistent_p(sesam_buffers_processing_context);
extern bool sesam_buffers_processing_context_defined_p(sesam_buffers_processing_context);
#define gen_SESAM_BUFFERS_PROCESSING_CONTEXT_cons gen_sesam_buffers_processing_context_cons
extern list gen_sesam_buffers_processing_context_cons(sesam_buffers_processing_context, list);
extern void sesam_buffers_processing_context_assign_contents(sesam_buffers_processing_context, sesam_buffers_processing_context);
extern void sesam_buffers_processing_context_non_recursive_free(sesam_buffers_processing_context);
extern void write_sesam_buffers_processing_context(FILE*, sesam_buffers_processing_context);
extern sesam_buffers_processing_context read_sesam_buffers_processing_context(FILE*);
extern sesam_buffers_processing_context make_sesam_buffers_processing_context(set, set, entity_task_buffers, entity_task_buffers, set);

struct _newgen_struct_sesam_buffers_processing_context_ {
  intptr_t _type_;
  set _sesam_buffers_processing_context_kernel_tasks_; /* kernel_tasks:entity{} */
  set _sesam_buffers_processing_context_server_tasks_; /* server_tasks:entity{} */
  entity_task_buffers _sesam_buffers_processing_context_kernel_buffers_; /* kernel_buffers:entity_task_buffers */
  entity_task_buffers _sesam_buffers_processing_context_server_buffers_; /* server_buffers:entity_task_buffers */
  set _sesam_buffers_processing_context_buffers_; /* buffers:entity{} */
};

#define sesam_buffers_processing_context_domain_number(x) ((x)->_type_)
#define sesam_buffers_processing_context_kernel_tasks_(x) sesam_buffers_processing_context_kernel_tasks(x) /* old hack compatible */
#define sesam_buffers_processing_context_kernel_tasks(x) ((x)->_sesam_buffers_processing_context_kernel_tasks_)
#define sesam_buffers_processing_context_server_tasks_(x) sesam_buffers_processing_context_server_tasks(x) /* old hack compatible */
#define sesam_buffers_processing_context_server_tasks(x) ((x)->_sesam_buffers_processing_context_server_tasks_)
#define sesam_buffers_processing_context_kernel_buffers_(x) sesam_buffers_processing_context_kernel_buffers(x) /* old hack compatible */
#define sesam_buffers_processing_context_kernel_buffers(x) ((x)->_sesam_buffers_processing_context_kernel_buffers_)
#define sesam_buffers_processing_context_server_buffers_(x) sesam_buffers_processing_context_server_buffers(x) /* old hack compatible */
#define sesam_buffers_processing_context_server_buffers(x) ((x)->_sesam_buffers_processing_context_server_buffers_)
#define sesam_buffers_processing_context_buffers_(x) sesam_buffers_processing_context_buffers(x) /* old hack compatible */
#define sesam_buffers_processing_context_buffers(x) ((x)->_sesam_buffers_processing_context_buffers_)

/* TASK_BUFFERS
 */
#define TASK_BUFFERS(x) ((task_buffers)((x).p))
#define task_buffers_CAST(x) TASK_BUFFERS(x)
#define TASK_BUFFERS_CAST(x) TASK_BUFFERS(x)
#define TASK_BUFFERS_(x) ((x).e)
#define TASK_BUFFERS_TYPE task_buffers
#define task_buffers_TYPE task_buffers
#define task_buffers_undefined ((task_buffers)gen_chunk_undefined)
#define task_buffers_undefined_p(x) ((x)==task_buffers_undefined)

extern task_buffers copy_task_buffers(task_buffers);
extern void free_task_buffers(task_buffers);
extern task_buffers check_task_buffers(task_buffers);
extern bool task_buffers_consistent_p(task_buffers);
extern bool task_buffers_defined_p(task_buffers);
#define gen_TASK_BUFFERS_cons gen_task_buffers_cons
extern list gen_task_buffers_cons(task_buffers, list);
extern void task_buffers_assign_contents(task_buffers, task_buffers);
extern void task_buffers_non_recursive_free(task_buffers);
extern void write_task_buffers(FILE*, task_buffers);
extern task_buffers read_task_buffers(FILE*);
extern task_buffers make_task_buffers(set, set);

struct _newgen_struct_task_buffers_ {
  intptr_t _type_;
  set _task_buffers_input_; /* input:entity{} */
  set _task_buffers_output_; /* output:entity{} */
};

#define task_buffers_domain_number(x) ((x)->_type_)
#define task_buffers_input_(x) task_buffers_input(x) /* old hack compatible */
#define task_buffers_input(x) ((x)->_task_buffers_input_)
#define task_buffers_output_(x) task_buffers_output(x) /* old hack compatible */
#define task_buffers_output(x) ((x)->_task_buffers_output_)

#define scalopes_private_spec "\
--NEWGEN-START 214\n\
import entity from \"ri.newgen\";\n\
import effect from \"effects.newgen\";\n\
entity_task_buffers = entity:entity -> task_buffers:task_buffers;\n\
sesam_buffers_processing_context = kernel_tasks:entity{} x server_tasks:entity{} x kernel_buffers:entity_task_buffers x server_buffers:entity_task_buffers x buffers:entity{};\n\
task_buffers = input:entity{} x output:entity{};\n\
"
#endif