#ifndef _newgen_dg_included
#define _newgen_dg_included
#define _gen_dg_start 221
/*
 * THIS FILE HAS BEEN AUTOMATICALLY GENERATED BY NEWGEN.
 *
 * PLEASE DO NOT MODIFY IT.
 */

#if !defined(_newgen_statement_domain_defined_)
#define _newgen_statement_domain_defined_
#define STATEMENT_NEWGEN_DOMAIN (statement_domain)
#define statement_NEWGEN_DOMAIN (statement_domain)
typedef struct _newgen_struct_statement_ * statement;
#endif /* _newgen_statement_domain_defined_ */

#if !defined(_newgen_effect_domain_defined_)
#define _newgen_effect_domain_defined_
#define EFFECT_NEWGEN_DOMAIN (effect_domain)
#define effect_NEWGEN_DOMAIN (effect_domain)
typedef struct _newgen_struct_effect_ * effect;
#endif /* _newgen_effect_domain_defined_ */

#if !defined(_newgen_vertex_domain_defined_)
#define _newgen_vertex_domain_defined_
#define VERTEX_NEWGEN_DOMAIN (vertex_domain)
#define vertex_NEWGEN_DOMAIN (vertex_domain)
typedef struct _newgen_struct_vertex_ * vertex;
#endif /* _newgen_vertex_domain_defined_ */

#if !defined(_newgen_Ptsg_domain_defined_)
#define _newgen_Ptsg_domain_defined_
#define newgen_Ptsg(p) (p) /* old hack compatible */
#define PTSG_NEWGEN_EXTERNAL (_gen_dg_start+0)
#define PTSG_NEWGEN_DOMAIN (PTSG_NEWGEN_EXTERNAL)
#define Ptsg_NEWGEN_DOMAIN (PTSG_NEWGEN_EXTERNAL)
#endif /* _newgen_Ptsg_domain_defined_ */

#define cone_domain (_gen_dg_start+1)
#if !defined(_newgen_cone_domain_defined_)
#define _newgen_cone_domain_defined_
#define CONE_NEWGEN_DOMAIN (cone_domain)
#define cone_NEWGEN_DOMAIN (cone_domain)
typedef struct _newgen_struct_cone_ * cone;
#endif /* _newgen_cone_domain_defined_ */

#define conflict_domain (_gen_dg_start+2)
#if !defined(_newgen_conflict_domain_defined_)
#define _newgen_conflict_domain_defined_
#define CONFLICT_NEWGEN_DOMAIN (conflict_domain)
#define conflict_NEWGEN_DOMAIN (conflict_domain)
typedef struct _newgen_struct_conflict_ * conflict;
#endif /* _newgen_conflict_domain_defined_ */

#define dg_arc_label_domain (_gen_dg_start+3)
#if !defined(_newgen_dg_arc_label_domain_defined_)
#define _newgen_dg_arc_label_domain_defined_
#define DG_ARC_LABEL_NEWGEN_DOMAIN (dg_arc_label_domain)
#define dg_arc_label_NEWGEN_DOMAIN (dg_arc_label_domain)
typedef struct _newgen_struct_dg_arc_label_ * dg_arc_label;
#endif /* _newgen_dg_arc_label_domain_defined_ */

#define dg_vertex_label_domain (_gen_dg_start+4)
#if !defined(_newgen_dg_vertex_label_domain_defined_)
#define _newgen_dg_vertex_label_domain_defined_
#define DG_VERTEX_LABEL_NEWGEN_DOMAIN (dg_vertex_label_domain)
#define dg_vertex_label_NEWGEN_DOMAIN (dg_vertex_label_domain)
typedef struct _newgen_struct_dg_vertex_label_ * dg_vertex_label;
#endif /* _newgen_dg_vertex_label_domain_defined_ */

#define sccflags_domain (_gen_dg_start+5)
#if !defined(_newgen_sccflags_domain_defined_)
#define _newgen_sccflags_domain_defined_
#define SCCFLAGS_NEWGEN_DOMAIN (sccflags_domain)
#define sccflags_NEWGEN_DOMAIN (sccflags_domain)
typedef struct _newgen_struct_sccflags_ * sccflags;
#endif /* _newgen_sccflags_domain_defined_ */

#define sccs_domain (_gen_dg_start+6)
#if !defined(_newgen_sccs_domain_defined_)
#define _newgen_sccs_domain_defined_
#define SCCS_NEWGEN_DOMAIN (sccs_domain)
#define sccs_NEWGEN_DOMAIN (sccs_domain)
typedef struct _newgen_struct_sccs_ * sccs;
#endif /* _newgen_sccs_domain_defined_ */

#define scc_domain (_gen_dg_start+7)
#if !defined(_newgen_scc_domain_defined_)
#define _newgen_scc_domain_defined_
#define SCC_NEWGEN_DOMAIN (scc_domain)
#define scc_NEWGEN_DOMAIN (scc_domain)
typedef struct _newgen_struct_scc_ * scc;
#endif /* _newgen_scc_domain_defined_ */


/* CONE
 */
#define CONE(x) ((cone)((x).p))
#define cone_CAST(x) CONE(x)
#define CONE_CAST(x) CONE(x)
#define CONE_(x) ((x).e)
#define CONE_TYPE cone
#define cone_TYPE cone
#define cone_undefined ((cone)gen_chunk_undefined)
#define cone_undefined_p(x) ((x)==cone_undefined)

extern cone copy_cone(cone);
extern void free_cone(cone);
extern cone check_cone(cone);
extern bool cone_consistent_p(cone);
extern bool cone_defined_p(cone);
#define gen_CONE_cons gen_cone_cons
extern list gen_cone_cons(cone, list);
extern void cone_assign_contents(cone, cone);
extern void cone_non_recursive_free(cone);
extern void write_cone(FILE*, cone);
extern cone read_cone(FILE*);
extern cone make_cone(list, Ptsg);

struct _newgen_struct_cone_ {
  intptr_t _type_;
  list _cone_levels_; /* levels:int* */
  Ptsg _cone_generating_system_; /* generating_system:Ptsg */
};

#define cone_domain_number(x) ((x)->_type_)
#define cone_levels_(x) cone_levels(x) /* old hack compatible */
#define cone_levels(x) ((x)->_cone_levels_)
#define cone_generating_system_(x) cone_generating_system(x) /* old hack compatible */
#define cone_generating_system(x) ((x)->_cone_generating_system_)

/* CONFLICT
 */
#define CONFLICT(x) ((conflict)((x).p))
#define conflict_CAST(x) CONFLICT(x)
#define CONFLICT_CAST(x) CONFLICT(x)
#define CONFLICT_(x) ((x).e)
#define CONFLICT_TYPE conflict
#define conflict_TYPE conflict
#define conflict_undefined ((conflict)gen_chunk_undefined)
#define conflict_undefined_p(x) ((x)==conflict_undefined)

extern conflict copy_conflict(conflict);
extern void free_conflict(conflict);
extern conflict check_conflict(conflict);
extern bool conflict_consistent_p(conflict);
extern bool conflict_defined_p(conflict);
#define gen_CONFLICT_cons gen_conflict_cons
extern list gen_conflict_cons(conflict, list);
extern void conflict_assign_contents(conflict, conflict);
extern void conflict_non_recursive_free(conflict);
extern void write_conflict(FILE*, conflict);
extern conflict read_conflict(FILE*);
extern conflict make_conflict(effect, effect, cone);

struct _newgen_struct_conflict_ {
  intptr_t _type_;
  effect _conflict_source_; /* source:effect */
  effect _conflict_sink_; /* sink:effect */
  cone _conflict_cone_; /* cone:cone */
};

#define conflict_domain_number(x) ((x)->_type_)
#define conflict_source_(x) conflict_source(x) /* old hack compatible */
#define conflict_source(x) ((x)->_conflict_source_)
#define conflict_sink_(x) conflict_sink(x) /* old hack compatible */
#define conflict_sink(x) ((x)->_conflict_sink_)
#define conflict_cone_(x) conflict_cone(x) /* old hack compatible */
#define conflict_cone(x) ((x)->_conflict_cone_)

/* DG_ARC_LABEL
 */
#define DG_ARC_LABEL(x) ((dg_arc_label)((x).p))
#define dg_arc_label_CAST(x) DG_ARC_LABEL(x)
#define DG_ARC_LABEL_CAST(x) DG_ARC_LABEL(x)
#define DG_ARC_LABEL_(x) ((x).e)
#define DG_ARC_LABEL_TYPE dg_arc_label
#define dg_arc_label_TYPE dg_arc_label
#define dg_arc_label_undefined ((dg_arc_label)gen_chunk_undefined)
#define dg_arc_label_undefined_p(x) ((x)==dg_arc_label_undefined)

extern dg_arc_label copy_dg_arc_label(dg_arc_label);
extern void free_dg_arc_label(dg_arc_label);
extern dg_arc_label check_dg_arc_label(dg_arc_label);
extern bool dg_arc_label_consistent_p(dg_arc_label);
extern bool dg_arc_label_defined_p(dg_arc_label);
#define gen_DG_ARC_LABEL_cons gen_dg_arc_label_cons
extern list gen_dg_arc_label_cons(dg_arc_label, list);
extern void dg_arc_label_assign_contents(dg_arc_label, dg_arc_label);
extern void dg_arc_label_non_recursive_free(dg_arc_label);
extern void write_dg_arc_label(FILE*, dg_arc_label);
extern dg_arc_label read_dg_arc_label(FILE*);
extern dg_arc_label make_dg_arc_label(list);

struct _newgen_struct_dg_arc_label_ {
  intptr_t _type_;
  list _dg_arc_label_holder_;
};

#define dg_arc_label_domain_number(x) ((x)->_type_)
#define dg_arc_label_conflicts(x) ((x)->_dg_arc_label_holder_)

/* DG_VERTEX_LABEL
 */
#define DG_VERTEX_LABEL(x) ((dg_vertex_label)((x).p))
#define dg_vertex_label_CAST(x) DG_VERTEX_LABEL(x)
#define DG_VERTEX_LABEL_CAST(x) DG_VERTEX_LABEL(x)
#define DG_VERTEX_LABEL_(x) ((x).e)
#define DG_VERTEX_LABEL_TYPE dg_vertex_label
#define dg_vertex_label_TYPE dg_vertex_label
#define dg_vertex_label_undefined ((dg_vertex_label)gen_chunk_undefined)
#define dg_vertex_label_undefined_p(x) ((x)==dg_vertex_label_undefined)

extern dg_vertex_label copy_dg_vertex_label(dg_vertex_label);
extern void free_dg_vertex_label(dg_vertex_label);
extern dg_vertex_label check_dg_vertex_label(dg_vertex_label);
extern bool dg_vertex_label_consistent_p(dg_vertex_label);
extern bool dg_vertex_label_defined_p(dg_vertex_label);
#define gen_DG_VERTEX_LABEL_cons gen_dg_vertex_label_cons
extern list gen_dg_vertex_label_cons(dg_vertex_label, list);
extern void dg_vertex_label_assign_contents(dg_vertex_label, dg_vertex_label);
extern void dg_vertex_label_non_recursive_free(dg_vertex_label);
extern void write_dg_vertex_label(FILE*, dg_vertex_label);
extern dg_vertex_label read_dg_vertex_label(FILE*);
extern dg_vertex_label make_dg_vertex_label(intptr_t, sccflags);

struct _newgen_struct_dg_vertex_label_ {
  intptr_t _type_;
  intptr_t _dg_vertex_label_statement_; /* statement:int */
  sccflags _dg_vertex_label_sccflags_; /* sccflags:sccflags */
};

#define dg_vertex_label_domain_number(x) ((x)->_type_)
#define dg_vertex_label_statement_(x) dg_vertex_label_statement(x) /* old hack compatible */
#define dg_vertex_label_statement(x) ((x)->_dg_vertex_label_statement_)
#define dg_vertex_label_sccflags_(x) dg_vertex_label_sccflags(x) /* old hack compatible */
#define dg_vertex_label_sccflags(x) ((x)->_dg_vertex_label_sccflags_)

/* SCCFLAGS
 */
#define SCCFLAGS(x) ((sccflags)((x).p))
#define sccflags_CAST(x) SCCFLAGS(x)
#define SCCFLAGS_CAST(x) SCCFLAGS(x)
#define SCCFLAGS_(x) ((x).e)
#define SCCFLAGS_TYPE sccflags
#define sccflags_TYPE sccflags
#define sccflags_undefined ((sccflags)gen_chunk_undefined)
#define sccflags_undefined_p(x) ((x)==sccflags_undefined)

extern sccflags copy_sccflags(sccflags);
extern void free_sccflags(sccflags);
extern sccflags check_sccflags(sccflags);
extern bool sccflags_consistent_p(sccflags);
extern bool sccflags_defined_p(sccflags);
#define gen_SCCFLAGS_cons gen_sccflags_cons
extern list gen_sccflags_cons(sccflags, list);
extern void sccflags_assign_contents(sccflags, sccflags);
extern void sccflags_non_recursive_free(sccflags);
extern void write_sccflags(FILE*, sccflags);
extern sccflags read_sccflags(FILE*);
extern sccflags make_sccflags(scc, intptr_t, intptr_t, intptr_t);

struct _newgen_struct_sccflags_ {
  intptr_t _type_;
  scc _sccflags_enclosing_scc_; /* enclosing_scc:scc */
  intptr_t _sccflags_mark_; /* mark:int */
  intptr_t _sccflags_dfnumber_; /* dfnumber:int */
  intptr_t _sccflags_lowlink_; /* lowlink:int */
};

#define sccflags_domain_number(x) ((x)->_type_)
#define sccflags_enclosing_scc_(x) sccflags_enclosing_scc(x) /* old hack compatible */
#define sccflags_enclosing_scc(x) ((x)->_sccflags_enclosing_scc_)
#define sccflags_mark_(x) sccflags_mark(x) /* old hack compatible */
#define sccflags_mark(x) ((x)->_sccflags_mark_)
#define sccflags_dfnumber_(x) sccflags_dfnumber(x) /* old hack compatible */
#define sccflags_dfnumber(x) ((x)->_sccflags_dfnumber_)
#define sccflags_lowlink_(x) sccflags_lowlink(x) /* old hack compatible */
#define sccflags_lowlink(x) ((x)->_sccflags_lowlink_)

/* SCCS
 */
#define SCCS(x) ((sccs)((x).p))
#define sccs_CAST(x) SCCS(x)
#define SCCS_CAST(x) SCCS(x)
#define SCCS_(x) ((x).e)
#define SCCS_TYPE sccs
#define sccs_TYPE sccs
#define sccs_undefined ((sccs)gen_chunk_undefined)
#define sccs_undefined_p(x) ((x)==sccs_undefined)

extern sccs copy_sccs(sccs);
extern void free_sccs(sccs);
extern sccs check_sccs(sccs);
extern bool sccs_consistent_p(sccs);
extern bool sccs_defined_p(sccs);
#define gen_SCCS_cons gen_sccs_cons
extern list gen_sccs_cons(sccs, list);
extern void sccs_assign_contents(sccs, sccs);
extern void sccs_non_recursive_free(sccs);
extern void write_sccs(FILE*, sccs);
extern sccs read_sccs(FILE*);
extern sccs make_sccs(list);

struct _newgen_struct_sccs_ {
  intptr_t _type_;
  list _sccs_holder_;
};

#define sccs_domain_number(x) ((x)->_type_)
#define sccs_sccs(x) ((x)->_sccs_holder_)

/* SCC
 */
#define SCC(x) ((scc)((x).p))
#define scc_CAST(x) SCC(x)
#define SCC_CAST(x) SCC(x)
#define SCC_(x) ((x).e)
#define SCC_TYPE scc
#define scc_TYPE scc
#define scc_undefined ((scc)gen_chunk_undefined)
#define scc_undefined_p(x) ((x)==scc_undefined)

extern scc copy_scc(scc);
extern void free_scc(scc);
extern scc check_scc(scc);
extern bool scc_consistent_p(scc);
extern bool scc_defined_p(scc);
#define gen_SCC_cons gen_scc_cons
extern list gen_scc_cons(scc, list);
extern void scc_assign_contents(scc, scc);
extern void scc_non_recursive_free(scc);
extern void write_scc(FILE*, scc);
extern scc read_scc(FILE*);
extern scc make_scc(list, intptr_t);

struct _newgen_struct_scc_ {
  intptr_t _type_;
  list _scc_vertices_; /* vertices:vertex* */
  intptr_t _scc_indegree_; /* indegree:int */
};

#define scc_domain_number(x) ((x)->_type_)
#define scc_vertices_(x) scc_vertices(x) /* old hack compatible */
#define scc_vertices(x) ((x)->_scc_vertices_)
#define scc_indegree_(x) scc_indegree(x) /* old hack compatible */
#define scc_indegree(x) ((x)->_scc_indegree_)

#define dg_spec "\
--NEWGEN-START 221\n\
import statement from \"ri.newgen\";\n\
import effect from \"effects.newgen\";\n\
import vertex from \"graph.newgen\";\n\
external Ptsg;\n\
cone = levels:int* x generating_system:Ptsg;\n\
conflict = persistant source:effect x persistant sink:effect x cone:cone;\n\
dg_arc_label = conflicts:conflict*;\n\
dg_vertex_label = statement:int x sccflags:sccflags;\n\
sccflags = enclosing_scc:scc x mark:int x dfnumber:int x lowlink:int;\n\
sccs = sccs:scc*;\n\
scc = vertices:vertex* x indegree:int;\n\
"
#endif