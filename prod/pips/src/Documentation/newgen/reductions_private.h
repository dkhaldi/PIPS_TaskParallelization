#ifndef _newgen_reductions_private_included
#define _newgen_reductions_private_included
#define _gen_reductions_private_start 97
/*
 * THIS FILE HAS BEEN AUTOMATICALLY GENERATED BY NEWGEN.
 *
 * PLEASE DO NOT MODIFY IT.
 */

#if !defined(_newgen_reference_domain_defined_)
#define _newgen_reference_domain_defined_
#define REFERENCE_NEWGEN_DOMAIN (reference_domain)
#define reference_NEWGEN_DOMAIN (reference_domain)
typedef struct _newgen_struct_reference_ * reference;
#endif /* _newgen_reference_domain_defined_ */

#if !defined(_newgen_preference_domain_defined_)
#define _newgen_preference_domain_defined_
#define PREFERENCE_NEWGEN_DOMAIN (preference_domain)
#define preference_NEWGEN_DOMAIN (preference_domain)
typedef struct _newgen_struct_preference_ * preference;
#endif /* _newgen_preference_domain_defined_ */

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

#define pstatement_reductions_domain (_gen_reductions_private_start+0)
#if !defined(_newgen_pstatement_reductions_domain_defined_)
#define _newgen_pstatement_reductions_domain_defined_
#define PSTATEMENT_REDUCTIONS_NEWGEN_DOMAIN (pstatement_reductions_domain)
#define pstatement_reductions_NEWGEN_DOMAIN (pstatement_reductions_domain)
typedef struct _newgen_struct_pstatement_reductions_ * pstatement_reductions;
#endif /* _newgen_pstatement_reductions_domain_defined_ */

#define reduction_operator_domain (_gen_reductions_private_start+1)
#if !defined(_newgen_reduction_operator_domain_defined_)
#define _newgen_reduction_operator_domain_defined_
#define REDUCTION_OPERATOR_NEWGEN_DOMAIN (reduction_operator_domain)
#define reduction_operator_NEWGEN_DOMAIN (reduction_operator_domain)
typedef struct _newgen_struct_reduction_operator_ * reduction_operator;
#endif /* _newgen_reduction_operator_domain_defined_ */

#define reduction_domain (_gen_reductions_private_start+2)
#if !defined(_newgen_reduction_domain_defined_)
#define _newgen_reduction_domain_defined_
#define REDUCTION_NEWGEN_DOMAIN (reduction_domain)
#define reduction_NEWGEN_DOMAIN (reduction_domain)
typedef struct _newgen_struct_reduction_ * reduction;
#endif /* _newgen_reduction_domain_defined_ */

#define reductions_domain (_gen_reductions_private_start+3)
#if !defined(_newgen_reductions_domain_defined_)
#define _newgen_reductions_domain_defined_
#define REDUCTIONS_NEWGEN_DOMAIN (reductions_domain)
#define reductions_NEWGEN_DOMAIN (reductions_domain)
typedef struct _newgen_struct_reductions_ * reductions;
#endif /* _newgen_reductions_domain_defined_ */

/* PSTATEMENT_REDUCTIONS
 */
#define PSTATEMENT_REDUCTIONS(x) ((pstatement_reductions)((x).p))
#define pstatement_reductions_CAST(x) PSTATEMENT_REDUCTIONS(x)
#define PSTATEMENT_REDUCTIONS_CAST(x) PSTATEMENT_REDUCTIONS(x)
#define PSTATEMENT_REDUCTIONS_(x) ((x).e)
#define PSTATEMENT_REDUCTIONS_TYPE pstatement_reductions
#define pstatement_reductions_TYPE pstatement_reductions
#define pstatement_reductions_undefined ((pstatement_reductions)gen_chunk_undefined)
#define pstatement_reductions_undefined_p(x) ((x)==pstatement_reductions_undefined)

extern pstatement_reductions copy_pstatement_reductions(pstatement_reductions);
extern void free_pstatement_reductions(pstatement_reductions);
extern pstatement_reductions check_pstatement_reductions(pstatement_reductions);
extern bool pstatement_reductions_consistent_p(pstatement_reductions);
extern bool pstatement_reductions_defined_p(pstatement_reductions);
#define gen_PSTATEMENT_REDUCTIONS_cons gen_pstatement_reductions_cons
extern list gen_pstatement_reductions_cons(pstatement_reductions, list);
extern void pstatement_reductions_assign_contents(pstatement_reductions, pstatement_reductions);
extern void pstatement_reductions_non_recursive_free(pstatement_reductions);
extern void write_pstatement_reductions(FILE*, pstatement_reductions);
extern pstatement_reductions read_pstatement_reductions(FILE*);
extern pstatement_reductions make_pstatement_reductions(void);

struct _newgen_struct_pstatement_reductions_ {
  intptr_t _type_;
  hash_table _pstatement_reductions_holder_;
};

#define pstatement_reductions_domain_number(x) ((x)->_type_)
#define pstatement_reductions_hash_table(x) ((x)->_pstatement_reductions_holder_)
#define pstatement_reductions_key_type statement
#define pstatement_reductions_value_type reductions
#define PSTATEMENT_REDUCTIONS_MAP(k,v,c,f) FUNCTION_MAP(pstatement_reductions,p,p,k,v,c,f)
#define PSTATEMENT_REDUCTIONS_FOREACH(k,v,f) FUNCTION_FOREACH(pstatement_reductions,p,p,k,v,f)
extern reductions apply_pstatement_reductions(pstatement_reductions, statement);
extern void update_pstatement_reductions(pstatement_reductions, statement, reductions);
extern void extend_pstatement_reductions(pstatement_reductions, statement, reductions);
extern reductions delete_pstatement_reductions(pstatement_reductions, statement);
extern bool bound_pstatement_reductions_p(pstatement_reductions, statement);

/* REDUCTION_OPERATOR
 */
#define REDUCTION_OPERATOR(x) ((reduction_operator)((x).p))
#define reduction_operator_CAST(x) REDUCTION_OPERATOR(x)
#define REDUCTION_OPERATOR_CAST(x) REDUCTION_OPERATOR(x)
#define REDUCTION_OPERATOR_(x) ((x).e)
#define REDUCTION_OPERATOR_TYPE reduction_operator
#define reduction_operator_TYPE reduction_operator
#define reduction_operator_undefined ((reduction_operator)gen_chunk_undefined)
#define reduction_operator_undefined_p(x) ((x)==reduction_operator_undefined)

extern reduction_operator copy_reduction_operator(reduction_operator);
extern void free_reduction_operator(reduction_operator);
extern reduction_operator check_reduction_operator(reduction_operator);
extern bool reduction_operator_consistent_p(reduction_operator);
extern bool reduction_operator_defined_p(reduction_operator);
#define gen_REDUCTION_OPERATOR_cons gen_reduction_operator_cons
extern list gen_reduction_operator_cons(reduction_operator, list);
extern void reduction_operator_assign_contents(reduction_operator, reduction_operator);
extern void reduction_operator_non_recursive_free(reduction_operator);
extern void write_reduction_operator(FILE*, reduction_operator);
extern reduction_operator read_reduction_operator(FILE*);
enum reduction_operator_utype {
  is_reduction_operator_none,
  is_reduction_operator_min,
  is_reduction_operator_max,
  is_reduction_operator_sum,
  is_reduction_operator_csum,
  is_reduction_operator_prod,
  is_reduction_operator_and,
  is_reduction_operator_or,
  is_reduction_operator_bitwise_and,
  is_reduction_operator_bitwise_or,
  is_reduction_operator_bitwise_xor,
  is_reduction_operator_eqv,
  is_reduction_operator_neqv
};
extern string reduction_operator_tag_as_string(enum reduction_operator_utype);
extern reduction_operator make_reduction_operator(enum reduction_operator_utype, void *);
extern reduction_operator make_reduction_operator_none(void);
extern reduction_operator make_reduction_operator_min(void);
extern reduction_operator make_reduction_operator_max(void);
extern reduction_operator make_reduction_operator_sum(void);
extern reduction_operator make_reduction_operator_csum(void);
extern reduction_operator make_reduction_operator_prod(void);
extern reduction_operator make_reduction_operator_and(void);
extern reduction_operator make_reduction_operator_or(void);
extern reduction_operator make_reduction_operator_bitwise_and(void);
extern reduction_operator make_reduction_operator_bitwise_or(void);
extern reduction_operator make_reduction_operator_bitwise_xor(void);
extern reduction_operator make_reduction_operator_eqv(void);
extern reduction_operator make_reduction_operator_neqv(void);

struct _newgen_struct_reduction_operator_ {
  intptr_t _type_;
  enum reduction_operator_utype _reduction_operator_tag__;
  union {
    gen_chunk _reduction_operator_none_; /* none:unit */
    gen_chunk _reduction_operator_min_; /* min:unit */
    gen_chunk _reduction_operator_max_; /* max:unit */
    gen_chunk _reduction_operator_sum_; /* sum:unit */
    gen_chunk _reduction_operator_csum_; /* csum:unit */
    gen_chunk _reduction_operator_prod_; /* prod:unit */
    gen_chunk _reduction_operator_and_; /* and:unit */
    gen_chunk _reduction_operator_or_; /* or:unit */
    gen_chunk _reduction_operator_bitwise_and_; /* bitwise_and:unit */
    gen_chunk _reduction_operator_bitwise_or_; /* bitwise_or:unit */
    gen_chunk _reduction_operator_bitwise_xor_; /* bitwise_xor:unit */
    gen_chunk _reduction_operator_eqv_; /* eqv:unit */
    gen_chunk _reduction_operator_neqv_; /* neqv:unit */
  } _reduction_operator_union_;
};

#define reduction_operator_domain_number(x) ((x)->_type_)
#define reduction_operator_tag(x) ((x)->_reduction_operator_tag__)
#define reduction_operator_none_p(x) (reduction_operator_tag(x)==is_reduction_operator_none)
#define reduction_operator_none_(x) reduction_operator_none(x) /* old hack compatible */
#define reduction_operator_none(x) ((x)->_reduction_operator_union_._reduction_operator_none_.u)
#define reduction_operator_min_p(x) (reduction_operator_tag(x)==is_reduction_operator_min)
#define reduction_operator_min_(x) reduction_operator_min(x) /* old hack compatible */
#define reduction_operator_min(x) ((x)->_reduction_operator_union_._reduction_operator_min_.u)
#define reduction_operator_max_p(x) (reduction_operator_tag(x)==is_reduction_operator_max)
#define reduction_operator_max_(x) reduction_operator_max(x) /* old hack compatible */
#define reduction_operator_max(x) ((x)->_reduction_operator_union_._reduction_operator_max_.u)
#define reduction_operator_sum_p(x) (reduction_operator_tag(x)==is_reduction_operator_sum)
#define reduction_operator_sum_(x) reduction_operator_sum(x) /* old hack compatible */
#define reduction_operator_sum(x) ((x)->_reduction_operator_union_._reduction_operator_sum_.u)
#define reduction_operator_csum_p(x) (reduction_operator_tag(x)==is_reduction_operator_csum)
#define reduction_operator_csum_(x) reduction_operator_csum(x) /* old hack compatible */
#define reduction_operator_csum(x) ((x)->_reduction_operator_union_._reduction_operator_csum_.u)
#define reduction_operator_prod_p(x) (reduction_operator_tag(x)==is_reduction_operator_prod)
#define reduction_operator_prod_(x) reduction_operator_prod(x) /* old hack compatible */
#define reduction_operator_prod(x) ((x)->_reduction_operator_union_._reduction_operator_prod_.u)
#define reduction_operator_and_p(x) (reduction_operator_tag(x)==is_reduction_operator_and)
#define reduction_operator_and_(x) reduction_operator_and(x) /* old hack compatible */
#define reduction_operator_and(x) ((x)->_reduction_operator_union_._reduction_operator_and_.u)
#define reduction_operator_or_p(x) (reduction_operator_tag(x)==is_reduction_operator_or)
#define reduction_operator_or_(x) reduction_operator_or(x) /* old hack compatible */
#define reduction_operator_or(x) ((x)->_reduction_operator_union_._reduction_operator_or_.u)
#define reduction_operator_bitwise_and_p(x) (reduction_operator_tag(x)==is_reduction_operator_bitwise_and)
#define reduction_operator_bitwise_and_(x) reduction_operator_bitwise_and(x) /* old hack compatible */
#define reduction_operator_bitwise_and(x) ((x)->_reduction_operator_union_._reduction_operator_bitwise_and_.u)
#define reduction_operator_bitwise_or_p(x) (reduction_operator_tag(x)==is_reduction_operator_bitwise_or)
#define reduction_operator_bitwise_or_(x) reduction_operator_bitwise_or(x) /* old hack compatible */
#define reduction_operator_bitwise_or(x) ((x)->_reduction_operator_union_._reduction_operator_bitwise_or_.u)
#define reduction_operator_bitwise_xor_p(x) (reduction_operator_tag(x)==is_reduction_operator_bitwise_xor)
#define reduction_operator_bitwise_xor_(x) reduction_operator_bitwise_xor(x) /* old hack compatible */
#define reduction_operator_bitwise_xor(x) ((x)->_reduction_operator_union_._reduction_operator_bitwise_xor_.u)
#define reduction_operator_eqv_p(x) (reduction_operator_tag(x)==is_reduction_operator_eqv)
#define reduction_operator_eqv_(x) reduction_operator_eqv(x) /* old hack compatible */
#define reduction_operator_eqv(x) ((x)->_reduction_operator_union_._reduction_operator_eqv_.u)
#define reduction_operator_neqv_p(x) (reduction_operator_tag(x)==is_reduction_operator_neqv)
#define reduction_operator_neqv_(x) reduction_operator_neqv(x) /* old hack compatible */
#define reduction_operator_neqv(x) ((x)->_reduction_operator_union_._reduction_operator_neqv_.u)

/* REDUCTION
 */
#define REDUCTION(x) ((reduction)((x).p))
#define reduction_CAST(x) REDUCTION(x)
#define REDUCTION_CAST(x) REDUCTION(x)
#define REDUCTION_(x) ((x).e)
#define REDUCTION_TYPE reduction
#define reduction_TYPE reduction
#define reduction_undefined ((reduction)gen_chunk_undefined)
#define reduction_undefined_p(x) ((x)==reduction_undefined)

extern reduction copy_reduction(reduction);
extern void free_reduction(reduction);
extern reduction check_reduction(reduction);
extern bool reduction_consistent_p(reduction);
extern bool reduction_defined_p(reduction);
#define gen_REDUCTION_cons gen_reduction_cons
extern list gen_reduction_cons(reduction, list);
extern void reduction_assign_contents(reduction, reduction);
extern void reduction_non_recursive_free(reduction);
extern void write_reduction(FILE*, reduction);
extern reduction read_reduction(FILE*);
extern reduction make_reduction(reference, reduction_operator, list, list);

struct _newgen_struct_reduction_ {
  intptr_t _type_;
  reference _reduction_reference_; /* reference:reference */
  reduction_operator _reduction_op_; /* op:reduction_operator */
  list _reduction_dependences_; /* dependences:entity* */
  list _reduction_trusted_; /* trusted:preference* */
};

#define reduction_domain_number(x) ((x)->_type_)
#define reduction_reference_(x) reduction_reference(x) /* old hack compatible */
#define reduction_reference(x) ((x)->_reduction_reference_)
#define reduction_op_(x) reduction_op(x) /* old hack compatible */
#define reduction_op(x) ((x)->_reduction_op_)
#define reduction_dependences_(x) reduction_dependences(x) /* old hack compatible */
#define reduction_dependences(x) ((x)->_reduction_dependences_)
#define reduction_trusted_(x) reduction_trusted(x) /* old hack compatible */
#define reduction_trusted(x) ((x)->_reduction_trusted_)

/* REDUCTIONS
 */
#define REDUCTIONS(x) ((reductions)((x).p))
#define reductions_CAST(x) REDUCTIONS(x)
#define REDUCTIONS_CAST(x) REDUCTIONS(x)
#define REDUCTIONS_(x) ((x).e)
#define REDUCTIONS_TYPE reductions
#define reductions_TYPE reductions
#define reductions_undefined ((reductions)gen_chunk_undefined)
#define reductions_undefined_p(x) ((x)==reductions_undefined)

extern reductions copy_reductions(reductions);
extern void free_reductions(reductions);
extern reductions check_reductions(reductions);
extern bool reductions_consistent_p(reductions);
extern bool reductions_defined_p(reductions);
#define gen_REDUCTIONS_cons gen_reductions_cons
extern list gen_reductions_cons(reductions, list);
extern void reductions_assign_contents(reductions, reductions);
extern void reductions_non_recursive_free(reductions);
extern void write_reductions(FILE*, reductions);
extern reductions read_reductions(FILE*);
extern reductions make_reductions(list);

struct _newgen_struct_reductions_ {
  intptr_t _type_;
  list _reductions_holder_;
};

#define reductions_domain_number(x) ((x)->_type_)
#define reductions_list(x) ((x)->_reductions_holder_)

#define reductions_private_spec "\
--NEWGEN-START 97\n\
import reference from \"ri.newgen\";\n\
import preference from \"ri.newgen\";\n\
import entity from \"ri.newgen\";\n\
import statement from \"ri.newgen\";\n\
pstatement_reductions = persistant statement:statement -> reductions:reductions;\n\
reduction_operator = none:unit + min:unit + max:unit + sum:unit + csum:unit + prod:unit + and:unit + or:unit + bitwise_and:unit + bitwise_or:unit + bitwise_xor:unit + eqv:unit + neqv:unit;\n\
reduction = reference:reference x op:reduction_operator x dependences:entity* x trusted:preference*;\n\
reductions = list:reduction*;\n\
"
#endif
