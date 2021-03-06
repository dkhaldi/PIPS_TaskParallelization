#ifndef _newgen_word_attachment_included
#define _newgen_word_attachment_included
#define _gen_word_attachment_start 90
/*
 * THIS FILE HAS BEEN AUTOMATICALLY GENERATED BY NEWGEN.
 *
 * PLEASE DO NOT MODIFY IT.
 */

#if !defined(_newgen_call_domain_defined_)
#define _newgen_call_domain_defined_
#define CALL_NEWGEN_DOMAIN (call_domain)
#define call_NEWGEN_DOMAIN (call_domain)
typedef struct _newgen_struct_call_ * call;
#endif /* _newgen_call_domain_defined_ */

#if !defined(_newgen_entity_domain_defined_)
#define _newgen_entity_domain_defined_
#define ENTITY_NEWGEN_DOMAIN (entity_domain)
#define entity_NEWGEN_DOMAIN (entity_domain)
typedef struct _newgen_struct_entity_ * entity;
#endif /* _newgen_entity_domain_defined_ */

#if !defined(_newgen_loop_domain_defined_)
#define _newgen_loop_domain_defined_
#define LOOP_NEWGEN_DOMAIN (loop_domain)
#define loop_NEWGEN_DOMAIN (loop_domain)
typedef struct _newgen_struct_loop_ * loop;
#endif /* _newgen_loop_domain_defined_ */

#if !defined(_newgen_reference_domain_defined_)
#define _newgen_reference_domain_defined_
#define REFERENCE_NEWGEN_DOMAIN (reference_domain)
#define reference_NEWGEN_DOMAIN (reference_domain)
typedef struct _newgen_struct_reference_ * reference;
#endif /* _newgen_reference_domain_defined_ */

#if !defined(_newgen_void_star_domain_defined_)
#define _newgen_void_star_domain_defined_
#define newgen_void_star(p) (p) /* old hack compatible */
#define VOID_STAR_NEWGEN_EXTERNAL (_gen_word_attachment_start+0)
#define VOID_STAR_NEWGEN_DOMAIN (VOID_STAR_NEWGEN_EXTERNAL)
#define void_star_NEWGEN_DOMAIN (VOID_STAR_NEWGEN_EXTERNAL)
#endif /* _newgen_void_star_domain_defined_ */

#define attachee_domain (_gen_word_attachment_start+1)
#if !defined(_newgen_attachee_domain_defined_)
#define _newgen_attachee_domain_defined_
#define ATTACHEE_NEWGEN_DOMAIN (attachee_domain)
#define attachee_NEWGEN_DOMAIN (attachee_domain)
typedef struct _newgen_struct_attachee_ * attachee;
#endif /* _newgen_attachee_domain_defined_ */

#define attachment_domain (_gen_word_attachment_start+2)
#if !defined(_newgen_attachment_domain_defined_)
#define _newgen_attachment_domain_defined_
#define ATTACHMENT_NEWGEN_DOMAIN (attachment_domain)
#define attachment_NEWGEN_DOMAIN (attachment_domain)
typedef struct _newgen_struct_attachment_ * attachment;
#endif /* _newgen_attachment_domain_defined_ */

#define attachments_domain (_gen_word_attachment_start+3)
#if !defined(_newgen_attachments_domain_defined_)
#define _newgen_attachments_domain_defined_
#define ATTACHMENTS_NEWGEN_DOMAIN (attachments_domain)
#define attachments_NEWGEN_DOMAIN (attachments_domain)
typedef struct _newgen_struct_attachments_ * attachments;
#endif /* _newgen_attachments_domain_defined_ */

#define word_to_attachments_domain (_gen_word_attachment_start+4)
#if !defined(_newgen_word_to_attachments_domain_defined_)
#define _newgen_word_to_attachments_domain_defined_
#define WORD_TO_ATTACHMENTS_NEWGEN_DOMAIN (word_to_attachments_domain)
#define word_to_attachments_NEWGEN_DOMAIN (word_to_attachments_domain)
typedef struct _newgen_struct_word_to_attachments_ * word_to_attachments;
#endif /* _newgen_word_to_attachments_domain_defined_ */


/* ATTACHEE
 */
#define ATTACHEE(x) ((attachee)((x).p))
#define attachee_CAST(x) ATTACHEE(x)
#define ATTACHEE_CAST(x) ATTACHEE(x)
#define ATTACHEE_(x) ((x).e)
#define ATTACHEE_TYPE attachee
#define attachee_TYPE attachee
#define attachee_undefined ((attachee)gen_chunk_undefined)
#define attachee_undefined_p(x) ((x)==attachee_undefined)

extern attachee copy_attachee(attachee);
extern void free_attachee(attachee);
extern attachee check_attachee(attachee);
extern bool attachee_consistent_p(attachee);
extern bool attachee_defined_p(attachee);
#define gen_ATTACHEE_cons gen_attachee_cons
extern list gen_attachee_cons(attachee, list);
extern void attachee_assign_contents(attachee, attachee);
extern void attachee_non_recursive_free(attachee);
extern void write_attachee(FILE*, attachee);
extern attachee read_attachee(FILE*);
enum attachee_utype {
  is_attachee_statement_line_number,
  is_attachee_reference,
  is_attachee_call,
  is_attachee_declaration,
  is_attachee_type,
  is_attachee_loop,
  is_attachee_module_head,
  is_attachee_complementary_sections,
  is_attachee_complexities,
  is_attachee_continuation_conditions,
  is_attachee_cumulated_effects,
  is_attachee_out_regions,
  is_attachee_preconditions,
  is_attachee_privatized_regions,
  is_attachee_proper_effects,
  is_attachee_proper_regions,
  is_attachee_regions,
  is_attachee_static_control,
  is_attachee_transformers,
  is_attachee_decoration,
  is_attachee_comment
};
extern string attachee_tag_as_string(enum attachee_utype);
extern attachee make_attachee(enum attachee_utype, void *);
extern attachee make_attachee_statement_line_number(intptr_t);
extern attachee make_attachee_reference(reference);
extern attachee make_attachee_call(call);
extern attachee make_attachee_declaration(entity);
extern attachee make_attachee_type(string);
extern attachee make_attachee_loop(loop);
extern attachee make_attachee_module_head(entity);
extern attachee make_attachee_complementary_sections(void);
extern attachee make_attachee_complexities(void);
extern attachee make_attachee_continuation_conditions(void);
extern attachee make_attachee_cumulated_effects(void);
extern attachee make_attachee_out_regions(void);
extern attachee make_attachee_preconditions(void);
extern attachee make_attachee_privatized_regions(void);
extern attachee make_attachee_proper_effects(void);
extern attachee make_attachee_proper_regions(void);
extern attachee make_attachee_regions(void);
extern attachee make_attachee_static_control(void);
extern attachee make_attachee_transformers(void);
extern attachee make_attachee_decoration(void);
extern attachee make_attachee_comment(void);

struct _newgen_struct_attachee_ {
  intptr_t _type_;
  enum attachee_utype _attachee_tag__;
  union {
    intptr_t _attachee_statement_line_number_; /* statement_line_number:int */
    reference _attachee_reference_; /* reference:reference */
    call _attachee_call_; /* call:call */
    entity _attachee_declaration_; /* declaration:entity */
    string _attachee_type_; /* type:string */
    loop _attachee_loop_; /* loop:loop */
    entity _attachee_module_head_; /* module_head:entity */
    gen_chunk _attachee_complementary_sections_; /* complementary_sections:unit */
    gen_chunk _attachee_complexities_; /* complexities:unit */
    gen_chunk _attachee_continuation_conditions_; /* continuation_conditions:unit */
    gen_chunk _attachee_cumulated_effects_; /* cumulated_effects:unit */
    gen_chunk _attachee_out_regions_; /* out_regions:unit */
    gen_chunk _attachee_preconditions_; /* preconditions:unit */
    gen_chunk _attachee_privatized_regions_; /* privatized_regions:unit */
    gen_chunk _attachee_proper_effects_; /* proper_effects:unit */
    gen_chunk _attachee_proper_regions_; /* proper_regions:unit */
    gen_chunk _attachee_regions_; /* regions:unit */
    gen_chunk _attachee_static_control_; /* static_control:unit */
    gen_chunk _attachee_transformers_; /* transformers:unit */
    gen_chunk _attachee_decoration_; /* decoration:unit */
    gen_chunk _attachee_comment_; /* comment:unit */
  } _attachee_union_;
};

#define attachee_domain_number(x) ((x)->_type_)
#define attachee_tag(x) ((x)->_attachee_tag__)
#define attachee_statement_line_number_p(x) (attachee_tag(x)==is_attachee_statement_line_number)
#define attachee_statement_line_number_(x) attachee_statement_line_number(x) /* old hack compatible */
#define attachee_statement_line_number(x) ((x)->_attachee_union_._attachee_statement_line_number_)
#define attachee_reference_p(x) (attachee_tag(x)==is_attachee_reference)
#define attachee_reference_(x) attachee_reference(x) /* old hack compatible */
#define attachee_reference(x) ((x)->_attachee_union_._attachee_reference_)
#define attachee_call_p(x) (attachee_tag(x)==is_attachee_call)
#define attachee_call_(x) attachee_call(x) /* old hack compatible */
#define attachee_call(x) ((x)->_attachee_union_._attachee_call_)
#define attachee_declaration_p(x) (attachee_tag(x)==is_attachee_declaration)
#define attachee_declaration_(x) attachee_declaration(x) /* old hack compatible */
#define attachee_declaration(x) ((x)->_attachee_union_._attachee_declaration_)
#define attachee_type_p(x) (attachee_tag(x)==is_attachee_type)
#define attachee_type_(x) attachee_type(x) /* old hack compatible */
#define attachee_type(x) ((x)->_attachee_union_._attachee_type_)
#define attachee_loop_p(x) (attachee_tag(x)==is_attachee_loop)
#define attachee_loop_(x) attachee_loop(x) /* old hack compatible */
#define attachee_loop(x) ((x)->_attachee_union_._attachee_loop_)
#define attachee_module_head_p(x) (attachee_tag(x)==is_attachee_module_head)
#define attachee_module_head_(x) attachee_module_head(x) /* old hack compatible */
#define attachee_module_head(x) ((x)->_attachee_union_._attachee_module_head_)
#define attachee_complementary_sections_p(x) (attachee_tag(x)==is_attachee_complementary_sections)
#define attachee_complementary_sections_(x) attachee_complementary_sections(x) /* old hack compatible */
#define attachee_complementary_sections(x) ((x)->_attachee_union_._attachee_complementary_sections_.u)
#define attachee_complexities_p(x) (attachee_tag(x)==is_attachee_complexities)
#define attachee_complexities_(x) attachee_complexities(x) /* old hack compatible */
#define attachee_complexities(x) ((x)->_attachee_union_._attachee_complexities_.u)
#define attachee_continuation_conditions_p(x) (attachee_tag(x)==is_attachee_continuation_conditions)
#define attachee_continuation_conditions_(x) attachee_continuation_conditions(x) /* old hack compatible */
#define attachee_continuation_conditions(x) ((x)->_attachee_union_._attachee_continuation_conditions_.u)
#define attachee_cumulated_effects_p(x) (attachee_tag(x)==is_attachee_cumulated_effects)
#define attachee_cumulated_effects_(x) attachee_cumulated_effects(x) /* old hack compatible */
#define attachee_cumulated_effects(x) ((x)->_attachee_union_._attachee_cumulated_effects_.u)
#define attachee_out_regions_p(x) (attachee_tag(x)==is_attachee_out_regions)
#define attachee_out_regions_(x) attachee_out_regions(x) /* old hack compatible */
#define attachee_out_regions(x) ((x)->_attachee_union_._attachee_out_regions_.u)
#define attachee_preconditions_p(x) (attachee_tag(x)==is_attachee_preconditions)
#define attachee_preconditions_(x) attachee_preconditions(x) /* old hack compatible */
#define attachee_preconditions(x) ((x)->_attachee_union_._attachee_preconditions_.u)
#define attachee_privatized_regions_p(x) (attachee_tag(x)==is_attachee_privatized_regions)
#define attachee_privatized_regions_(x) attachee_privatized_regions(x) /* old hack compatible */
#define attachee_privatized_regions(x) ((x)->_attachee_union_._attachee_privatized_regions_.u)
#define attachee_proper_effects_p(x) (attachee_tag(x)==is_attachee_proper_effects)
#define attachee_proper_effects_(x) attachee_proper_effects(x) /* old hack compatible */
#define attachee_proper_effects(x) ((x)->_attachee_union_._attachee_proper_effects_.u)
#define attachee_proper_regions_p(x) (attachee_tag(x)==is_attachee_proper_regions)
#define attachee_proper_regions_(x) attachee_proper_regions(x) /* old hack compatible */
#define attachee_proper_regions(x) ((x)->_attachee_union_._attachee_proper_regions_.u)
#define attachee_regions_p(x) (attachee_tag(x)==is_attachee_regions)
#define attachee_regions_(x) attachee_regions(x) /* old hack compatible */
#define attachee_regions(x) ((x)->_attachee_union_._attachee_regions_.u)
#define attachee_static_control_p(x) (attachee_tag(x)==is_attachee_static_control)
#define attachee_static_control_(x) attachee_static_control(x) /* old hack compatible */
#define attachee_static_control(x) ((x)->_attachee_union_._attachee_static_control_.u)
#define attachee_transformers_p(x) (attachee_tag(x)==is_attachee_transformers)
#define attachee_transformers_(x) attachee_transformers(x) /* old hack compatible */
#define attachee_transformers(x) ((x)->_attachee_union_._attachee_transformers_.u)
#define attachee_decoration_p(x) (attachee_tag(x)==is_attachee_decoration)
#define attachee_decoration_(x) attachee_decoration(x) /* old hack compatible */
#define attachee_decoration(x) ((x)->_attachee_union_._attachee_decoration_.u)
#define attachee_comment_p(x) (attachee_tag(x)==is_attachee_comment)
#define attachee_comment_(x) attachee_comment(x) /* old hack compatible */
#define attachee_comment(x) ((x)->_attachee_union_._attachee_comment_.u)

/* ATTACHMENT
 */
#define ATTACHMENT(x) ((attachment)((x).p))
#define attachment_CAST(x) ATTACHMENT(x)
#define ATTACHMENT_CAST(x) ATTACHMENT(x)
#define ATTACHMENT_(x) ((x).e)
#define ATTACHMENT_TYPE attachment
#define attachment_TYPE attachment
#define attachment_undefined ((attachment)gen_chunk_undefined)
#define attachment_undefined_p(x) ((x)==attachment_undefined)

extern attachment copy_attachment(attachment);
extern void free_attachment(attachment);
extern attachment check_attachment(attachment);
extern bool attachment_consistent_p(attachment);
extern bool attachment_defined_p(attachment);
#define gen_ATTACHMENT_cons gen_attachment_cons
extern list gen_attachment_cons(attachment, list);
extern void attachment_assign_contents(attachment, attachment);
extern void attachment_non_recursive_free(attachment);
extern void write_attachment(FILE*, attachment);
extern attachment read_attachment(FILE*);
extern attachment make_attachment(attachee, intptr_t, intptr_t);

struct _newgen_struct_attachment_ {
  intptr_t _type_;
  attachee _attachment_attachee_; /* attachee:attachee */
  intptr_t _attachment_begin_; /* begin:int */
  intptr_t _attachment_end_; /* end:int */
};

#define attachment_domain_number(x) ((x)->_type_)
#define attachment_attachee_(x) attachment_attachee(x) /* old hack compatible */
#define attachment_attachee(x) ((x)->_attachment_attachee_)
#define attachment_begin_(x) attachment_begin(x) /* old hack compatible */
#define attachment_begin(x) ((x)->_attachment_begin_)
#define attachment_end_(x) attachment_end(x) /* old hack compatible */
#define attachment_end(x) ((x)->_attachment_end_)

/* ATTACHMENTS
 */
#define ATTACHMENTS(x) ((attachments)((x).p))
#define attachments_CAST(x) ATTACHMENTS(x)
#define ATTACHMENTS_CAST(x) ATTACHMENTS(x)
#define ATTACHMENTS_(x) ((x).e)
#define ATTACHMENTS_TYPE attachments
#define attachments_TYPE attachments
#define attachments_undefined ((attachments)gen_chunk_undefined)
#define attachments_undefined_p(x) ((x)==attachments_undefined)

extern attachments copy_attachments(attachments);
extern void free_attachments(attachments);
extern attachments check_attachments(attachments);
extern bool attachments_consistent_p(attachments);
extern bool attachments_defined_p(attachments);
#define gen_ATTACHMENTS_cons gen_attachments_cons
extern list gen_attachments_cons(attachments, list);
extern void attachments_assign_contents(attachments, attachments);
extern void attachments_non_recursive_free(attachments);
extern void write_attachments(FILE*, attachments);
extern attachments read_attachments(FILE*);
extern attachments make_attachments(list);

struct _newgen_struct_attachments_ {
  intptr_t _type_;
  list _attachments_holder_;
};

#define attachments_domain_number(x) ((x)->_type_)
#define attachments_attachment(x) ((x)->_attachments_holder_)

/* WORD_TO_ATTACHMENTS
 */
#define WORD_TO_ATTACHMENTS(x) ((word_to_attachments)((x).p))
#define word_to_attachments_CAST(x) WORD_TO_ATTACHMENTS(x)
#define WORD_TO_ATTACHMENTS_CAST(x) WORD_TO_ATTACHMENTS(x)
#define WORD_TO_ATTACHMENTS_(x) ((x).e)
#define WORD_TO_ATTACHMENTS_TYPE word_to_attachments
#define word_to_attachments_TYPE word_to_attachments
#define word_to_attachments_undefined ((word_to_attachments)gen_chunk_undefined)
#define word_to_attachments_undefined_p(x) ((x)==word_to_attachments_undefined)

extern word_to_attachments copy_word_to_attachments(word_to_attachments);
extern void free_word_to_attachments(word_to_attachments);
extern word_to_attachments check_word_to_attachments(word_to_attachments);
extern bool word_to_attachments_consistent_p(word_to_attachments);
extern bool word_to_attachments_defined_p(word_to_attachments);
#define gen_WORD_TO_ATTACHMENTS_cons gen_word_to_attachments_cons
extern list gen_word_to_attachments_cons(word_to_attachments, list);
extern void word_to_attachments_assign_contents(word_to_attachments, word_to_attachments);
extern void word_to_attachments_non_recursive_free(word_to_attachments);
extern void write_word_to_attachments(FILE*, word_to_attachments);
extern word_to_attachments read_word_to_attachments(FILE*);
extern word_to_attachments make_word_to_attachments(void);

struct _newgen_struct_word_to_attachments_ {
  intptr_t _type_;
  hash_table _word_to_attachments_holder_;
};

#define word_to_attachments_domain_number(x) ((x)->_type_)
#define word_to_attachments_hash_table(x) ((x)->_word_to_attachments_holder_)
#define word_to_attachments_key_type void_star
#define word_to_attachments_value_type attachments
#define WORD_TO_ATTACHMENTS_MAP(k,v,c,f) FUNCTION_MAP(word_to_attachments,p,p,k,v,c,f)
#define WORD_TO_ATTACHMENTS_FOREACH(k,v,f) FUNCTION_FOREACH(word_to_attachments,p,p,k,v,f)
extern attachments apply_word_to_attachments(word_to_attachments, void_star);
extern void update_word_to_attachments(word_to_attachments, void_star, attachments);
extern void extend_word_to_attachments(word_to_attachments, void_star, attachments);
extern attachments delete_word_to_attachments(word_to_attachments, void_star);
extern bool bound_word_to_attachments_p(word_to_attachments, void_star);

#define word_attachment_spec "\
--NEWGEN-START 90\n\
import call from \"ri.newgen\";\n\
import entity from \"ri.newgen\";\n\
import loop from \"ri.newgen\";\n\
import reference from \"ri.newgen\";\n\
external void_star;\n\
attachee = statement_line_number:int + persistant reference:reference + persistant call:call + persistant declaration:entity + type:string + persistant loop:loop + persistant module_head:entity + complementary_sections:unit + complexities:unit + continuation_conditions:unit + cumulated_effects:unit + out_regions:unit + preconditions:unit + privatized_regions:unit + proper_effects:unit + proper_regions:unit + regions:unit + static_control:unit + transformers:unit + decoration:unit + comment:unit;\n\
attachment = attachee:attachee x begin:int x end:int;\n\
attachments = attachment:attachment*;\n\
word_to_attachments = word_pointer:void_star -> attachments:attachments;\n\
"
#endif
