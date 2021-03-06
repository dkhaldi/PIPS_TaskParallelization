#ifndef _newgen_message_included
#define _newgen_message_included
#define _gen_message_start 111
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

#if !defined(_newgen_range_domain_defined_)
#define _newgen_range_domain_defined_
#define RANGE_NEWGEN_DOMAIN (range_domain)
#define range_NEWGEN_DOMAIN (range_domain)
typedef struct _newgen_struct_range_ * range;
#endif /* _newgen_range_domain_defined_ */

#if !defined(_newgen_Pvecteur_domain_defined_)
#define _newgen_Pvecteur_domain_defined_
#define newgen_Pvecteur(p) (p) /* old hack compatible */
#define PVECTEUR_NEWGEN_EXTERNAL (_gen_message_start+0)
#define PVECTEUR_NEWGEN_DOMAIN (PVECTEUR_NEWGEN_EXTERNAL)
#define Pvecteur_NEWGEN_DOMAIN (PVECTEUR_NEWGEN_EXTERNAL)
#endif /* _newgen_Pvecteur_domain_defined_ */

#define message_domain (_gen_message_start+1)
#if !defined(_newgen_message_domain_defined_)
#define _newgen_message_domain_defined_
#define MESSAGE_NEWGEN_DOMAIN (message_domain)
#define message_NEWGEN_DOMAIN (message_domain)
typedef struct _newgen_struct_message_ * message;
#endif /* _newgen_message_domain_defined_ */


/* MESSAGE
 */
#define MESSAGE(x) ((message)((x).p))
#define message_CAST(x) MESSAGE(x)
#define MESSAGE_CAST(x) MESSAGE(x)
#define MESSAGE_(x) ((x).e)
#define MESSAGE_TYPE message
#define message_TYPE message
#define message_undefined ((message)gen_chunk_undefined)
#define message_undefined_p(x) ((x)==message_undefined)

extern message copy_message(message);
extern void free_message(message);
extern message check_message(message);
extern bool message_consistent_p(message);
extern bool message_defined_p(message);
#define gen_MESSAGE_cons gen_message_cons
extern list gen_message_cons(message, list);
extern void message_assign_contents(message, message);
extern void message_non_recursive_free(message);
extern void write_message(FILE*, message);
extern message read_message(FILE*);
extern message make_message(entity, list, Pvecteur, list);

struct _newgen_struct_message_ {
  intptr_t _type_;
  entity _message_array_; /* array:entity */
  list _message_content_; /* content:range* */
  Pvecteur _message_neighbour_; /* neighbour:Pvecteur */
  list _message_dom_; /* dom:range* */
};

#define message_domain_number(x) ((x)->_type_)
#define message_array_(x) message_array(x) /* old hack compatible */
#define message_array(x) ((x)->_message_array_)
#define message_content_(x) message_content(x) /* old hack compatible */
#define message_content(x) ((x)->_message_content_)
#define message_neighbour_(x) message_neighbour(x) /* old hack compatible */
#define message_neighbour(x) ((x)->_message_neighbour_)
#define message_dom_(x) message_dom(x) /* old hack compatible */
#define message_dom(x) ((x)->_message_dom_)

#define message_spec "\
--NEWGEN-START 111\n\
import entity from \"ri.newgen\";\n\
import range from \"ri.newgen\";\n\
external Pvecteur;\n\
message = array:entity x content:range* x neighbour:Pvecteur x dom:range*;\n\
"
#endif
