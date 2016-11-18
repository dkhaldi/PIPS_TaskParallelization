/* Warning! Do not modify this file that is automatically generated! */
/* Modify src/Libs/union/union-local.h instead, to add your own modifications. */

/* header file built by cproto */

#ifndef  union_header_included
#define  union_header_included


typedef struct Ssyslist  {
        Psysteme                psys;
        struct Ssyslist         *succ;
        } *Psyslist,Ssyslist;

#define SL_NULL      (Psyslist) NULL

typedef Ssyslist *Pdisjunct,Sdisjunct;

#define DJ_UNDEFINED    (Pdisjunct) NULL
 
typedef Ssysteme *Pcomplement,Scomplement;

#define CO_UNDEFINED    (Pcomplement) NULL
 typedef Ssyslist *Pcomplist,Scomplist; 
typedef struct Spath {
        Psysteme        psys;
        Pcomplist       pcomp;
        } *Ppath,Spath;

#define PA_UNDEFINED    (Ppath) NULL

typedef struct Sunion {
        Pdisjunct       pdi;
        Ppath           ppa;
        } *Punion,Sunion;

#define UN_UNDEFINED    (Punion) NULL
#define UN_FULL_SPACE   (Punion) NULL
#define UN_EMPTY_SPACE  (Punion) NULL

/* Implementation of the finite parallel half space lattice hspara
 *                
 *                      ________ full 
 *                     /          |
 *                    /          empty ___
 *                   /            |       \
 *                  /           keep       \
 *                 /           /    \       \
 *              ssplus        /    opplus    \
 *                 |      ssminus    |     opminus
 *               sszero        \   opzero    /
 *                  \           \   /       /
 *                   \________ unpara _____/
 */
enum hspara_elem
{                      /* compare   {h1: a1 X + b1 <= 0} with {hj: aj X + bj <= 0} */      
  unpara        = 0,   /*  unparallel ->   h1/hj = h1    */
  /**/                 /*  a1 == aj for same sign (ss)  part lattice */ 
    sszero      = 1,   /*  b1 == bj   ->   h1/hj = full  */ 
    ssplus      = 2,   /*  bj >  b1   ->   h1/hj = full  */
  /**/     
    /**/               /* keep part                      */
      /**/     
        ssminus = 3,   /*  bj <  b1   ->   h1/hj = h1    */ 
      /**/             /* -a1 == aj for opposite sign (op)  part lattice */
        opzero  = 4,   /*  b1 == bj   ->   h1/hj = h1    */ 
        opplus  = 5,   /*  bj >  b1   ->   h1/hj = h1    */
    keep        = 6,
    /**/               /* empty part                     */
      opminus   = 7,   /*  b1 <  bj   ->   h1/hj = empty */  
    empty       = 8,   
  full          = 9     
};
 
/* FOR BACKWARD COMPATIBILITY */
#define my_sc_full()         sc_full()
#define my_sc_empty()        sc_empty((Pbase) NULL)
#define is_sc_my_empty_p(ps) sc_empty_p((ps))
#define is_dj_full_p(dj)     dj_full_p((dj))
#define is_dj_empty_p(dj)    dj_empty_p((dj))
#define is_pa_full_p(pa)     pa_full_p((pa))
#define is_pa_empty_p(pa)    pa_empty_p((pa))


/* FOR BACKWARD COMPATIBILITY */
#define sc_difference(ps1, ps2)      pa_system_difference_ofl_ctrl((ps1),(ps2),FWD_OFL_CTRL)
#define sc_inclusion_p(ps1, ps2)     pa_inclusion_p_ofl_ctrl((ps1), (ps2), NO_OFL_CTRL)
#define sc_inclusion_p_ofl(ps1, ps2) pa_inclusion_p_ofl_ctrl((ps1), (ps2), FWD_OFL_CTRL)
#define sc_inclusion_p_ofl_ctrl(ps1, ps2, ofl) pa_inclusion_p_ofl_ctrl((ps1), (ps2), (ofl))
#define sc_equal_p(ps1,ps2)          pa_system_equal_p_ofl_ctrl((ps1), (ps2), NO_OFL_CTRL)
#define sc_equal_p_ofl(ps1,ps2)      pa_system_equal_p_ofl_ctrl((ps1), (ps2), FWD_OFL_CTRL)
#define sc_equal_p_ofl_ctrl(ps1, ps2, ofl) pa_system_equal_p_ofl_ctrl((ps1), (ps2), (ofl))
#define sc_convex_hull_equals_union_p(conv_hull, ps1, ps2) \
  pa_convex_hull_equals_union_p_ofl_ctrl((conv_hull), (ps1), (ps2),NO_OFL_CTRL, false)
#define sc_convex_hull_equals_union_p_ofl(conv_hull, ps1, ps2) \
  pa_convex_hull_equals_union_p_ofl_ctrl((conv_hull), (ps1), (ps2), OFL_CTRL, false)
#define sc_convex_hull_equals_union_p_ofl_ctrl(conv_hull, ps1, ps2, ofl, bo) \
  pa_convex_hull_equals_union_p_ofl_ctrl((conv_hull), (ps1), (ps2), (ofl), (bo))

/* OTHERS */
#define sc_elim_redund_with_first(ps1, ps2) sc_elim_redund_with_first_ofl_ctrl((ps1), (ps2), NO_OFL_CTRL)

#define dj_fprint(fi,dj,fu)           dj_fprint_tab((fi), (dj), (fu), 0)
#define DJ_UNDEFINED_P(dj)            ((dj) == DJ_UNDEFINED)
#define dj_faisabilite(dj)            dj_feasibility_ofl_ctrl((dj), NO_OFL_CTRL)
#define dj_feasibility(dj)            dj_feasibility_ofl_ctrl((dj), NO_OFL_CTRL)
#define dj_faisabilite_ofl(dj)        dj_feasibility_ofl_ctrl((dj), FWD_OFL_CTRL)
#define dj_intersection(dj1, dj2)     dj_intersection_ofl_ctrl((dj1), (dj2), NO_OFL_CTRL)
#define dj_intersect_system(dj,ps)    dj_intersect_system_ofl_ctrl((dj), (ps), NO_OFL_CTRL ) 
#define dj_intersect_djcomp(dj1,dj2)  dj_intersect_djcomp_ofl_ctrl( (dj1), (dj2), NO_OFL_CTRL )
#define dj_projection_along_variables(dj,pv) \
  dj_projection_along_variables_ofl_ctrl((dj),(pv),NO_OFL_CTRL)
#define dj_variable_substitution_with_eqs(dj,co,pv) \
  dj_variable_substitution_with_eqs_ofl_ctrl( (dj), (co), (pv), NO_OFL_CTRL )

#define pa_fprint(fi,pa,fu)           pa_fprint_tab((fi), (pa), (fu), 0)
#define PA_UNDEFINED_P(pa)            ((pa) == PA_UNDEFINED)
#define pa_new()                      pa_make(NULL, NULL)
#define pa_faisabilite(pa)            pa_feasibility_ofl_ctrl((pa), NO_OFL_CTRL)
#define pa_feasibility(pa)            pa_feasibility_ofl_ctrl((pa), NO_OFL_CTRL)
#define pa_faisabilite_ofl(pa)        pa_feasibility_ofl_ctrl((pa), FWD_OFL_CTRL)
#define pa_path_to_disjunct(pa)       pa_path_to_disjunct_ofl_ctrl((pa), NO_OFL_CTRL )
#define pa_path_dup_to_disjunct(pa)   pa_path_to_disjunct_ofl_ctrl((pa), NO_OFL_CTRL )
#define pa_system_difference(ps1,ps2) pa_system_difference_ofl_ctrl((ps1),(ps2),NO_OFL_CTRL)
#define pa_system_equal_p(ps1,ps2)    pa_system_equal_p_ofl_ctrl((ps1),(ps2),NO_OFL_CTRL)
#define pa_inclusion_p(ps1,ps2)       pa_inclusion_p_ofl_ctrl((ps1),(ps2),NO_OFL_CTRL)
#define pa_path_to_disjunct_ofl(pa)   pa_path_to_disjunct_ofl_ctrl((pa), FWD_OFL_CTRL )
#define pa_path_to_disjunct_rule4(pa) pa_path_to_disjunct_rule4_ofl_ctrl((pa), FWD_OFL_CTRL )
#define pa_path_to_few_disjunct(pa)   pa_path_to_few_disjunct_ofl_ctrl((pa), NO_OFL_CTRL)
#define pa_system_difference(ps1,ps2) pa_system_difference_ofl_ctrl((ps1),(ps2),NO_OFL_CTRL)
#define pa_convex_hull_equals_union_p(conv_hull, ps1, ps2) \
  pa_convex_hull_equals_union_p_ofl_ctrl((conv_hull), (ps1), (ps2), NO_OFL_CTRL, false)

#define un_fprint(fi,un,fu,ty)        un_fprint_tab((fi), (un), (fu), (ty), 0)


/* Misceleanous (debuging...) */
#define PATH_MAX_CONSTRAINTS          12

#define IS_SC                         1
#define IS_SL                         2
#define IS_DJ                         3
#define IS_PA                         4

extern char* (*union_variable_name)(Variable);

#if(defined(DEBUG_UNION_C3) || defined(DEBUG_UNION_PIPS))
#define C3_DEBUG( fun, code )         \
  {if(getenv("DEBUG_UNION")){fprintf(stderr,"[%s]\n", fun); {code}}}
#define C3_RETURN( type, val )      \
  {if(getenv("DEBUG_UNION")){ \
     char* val1 = (char*) val; \
     fprintf(stderr,"Returning:\n"); \
     un_fprint_tab(stderr,(char*)val1,union_variable_name,type,1); return val1;} \
   else{ return val; }}
#else 
#define C3_DEBUG( fun, code )
#define C3_RETURN( type, val )        {return val;}
#endif
/* disjunct.c */
extern Pdisjunct dj_new(void);
extern Pdisjunct dj_dup(Pdisjunct /*in_dj*/);
extern Pdisjunct dj_free(Pdisjunct /*in_dj*/);
extern Pdisjunct dj_dup1(Pdisjunct /*in_dj*/);
extern Pdisjunct dj_free1(Pdisjunct /*in_dj*/);
extern Pdisjunct dj_full(void);
extern bool dj_full_p(Pdisjunct /*in_dj*/);
extern Pdisjunct dj_empty(void);
extern bool dj_empty_p(Pdisjunct /*in_dj*/);
extern Pdisjunct dj_intersection_ofl_ctrl(Pdisjunct /*in_dj1*/, Pdisjunct /*in_dj2*/, int /*ofl_ctrl*/);
extern Pdisjunct dj_intersect_system_ofl_ctrl(Pdisjunct /*in_dj*/, Psysteme /*in_ps*/, int /*ofl_ctrl*/);
extern Pdisjunct dj_intersect_djcomp_ofl_ctrl(Pdisjunct /*in_dj1*/, Pdisjunct /*in_dj2*/, int /*ofl_ctrl*/);
extern Pdisjunct dj_union(Pdisjunct /*in_dj1*/, Pdisjunct /*in_dj2*/);
extern bool dj_feasibility_ofl_ctrl(Pdisjunct /*in_dj*/, int /*ofl_ctrl*/);
extern Pdisjunct dj_system_complement(Psysteme /*in_ps*/);
extern Pdisjunct dj_disjunct_complement(Pdisjunct /*in_dj*/);
extern Pdisjunct dj_projection_along_variables_ofl_ctrl(Pdisjunct /*in_dj*/, Pvecteur /*in_pv*/, int /*ofl_ctrl*/);
extern Pdisjunct dj_simple_inegs_to_eg(Pdisjunct /*in_dj*/);
extern bool dj_is_system_p(Pdisjunct /*in_dj*/);
extern Pdisjunct dj_append_system(Pdisjunct /*in_dj*/, Psysteme /*in_ps*/);
extern Pdisjunct dj_variable_rename(Pdisjunct /*in_dj*/, Variable /*in_vold*/, Variable /*in_vnew*/);
extern Pdisjunct dj_variable_substitution_with_eqs_ofl_ctrl(Pdisjunct /*in_dj*/, Pcontrainte /*in_pc*/, Pvecteur /*in_pv*/, int /*ofl_ctrl*/);
extern void dj_fprint_tab(FILE */*in_fi*/, Pdisjunct /*in_dj*/, char *(* /*in_fu*/)(void), int /*in_tab*/);
extern Pdisjunct dj_read(char */*nomfic*/);
/* path.c */
extern Ppath pa_make(Psysteme /*in_ps*/, Pcomplist /*in_pcomp*/);
extern Ppath pa_dup(Ppath /*in_pa*/);
extern Ppath pa_free(Ppath /*in_pa*/);
extern Ppath pa_dup1(Ppath /*in_pa*/);
extern Ppath pa_free1(Ppath /*in_pa*/);
extern Ppath pa_full(void);
extern bool pa_full_p(Ppath /*in_pa*/);
extern Ppath pa_empty(void);
extern bool pa_empty_p(Ppath /*in_pa*/);
extern int pa_max_constraints_nb(Ppath /*in_pa*/);
extern Ppath pa_intersect_system(Ppath /*in_pa*/, Psysteme /*in_ps*/);
extern Ppath pa_intersect_complement(Ppath /*in_pa*/, Pcomplement /*in_pc*/);
extern Ppath pa_reduce_simple_complement(Ppath /*in_pa*/);
extern Ppath pa_transform_eg_in_ineg(Ppath /*in_pa*/);
extern bool pa_feasibility_ofl_ctrl(Ppath /*in_pa*/, int /*ofl_ctrl*/);
extern Pdisjunct pa_path_to_disjunct_ofl_ctrl(Ppath /*in_pa*/, int /*ofl_ctrl*/);
extern void pa_fprint_tab(FILE */*in_fi*/, Ppath /*in_pa*/, char *(* /*in_fu*/)(void), int /*in_tab*/);
extern Ppath pa_read(char */*nomfic*/);
/* reduc.c */
extern enum hspara_elem vect_parallel(Pvecteur /*in_v1*/, Pvecteur /*in_v2*/);
extern enum hspara_elem contrainte_parallel_in_liste(Pcontrainte /*in_co*/, Pcontrainte /*in_lc*/);
extern Psysteme sc_supress_parallel_redund_constraints(Psysteme /*in_ps1*/, Psysteme /*in_ps2*/);
extern Psysteme sc_supress_same_constraints(Psysteme /*in_ps1*/, Psysteme /*in_ps2*/);
extern Psysteme sc_elim_redund_with_first_ofl_ctrl(Psysteme /*in_ps1*/, Psysteme /*in_ps2*/, int /*ofl_ctrl*/);
extern Ppath pa_supress_same_constraints(Ppath /*in_pa*/);
extern Pdisjunct pa_path_to_disjunct_rule4_ofl_ctrl(Ppath /*in_pa*/, int /*ofl_ctrl*/);
extern Pdisjunct pa_path_to_few_disjunct_ofl_ctrl(Ppath /*in_pa*/, int /*ofl_ctrl*/);
extern bool pa_inclusion_p_ofl_ctrl(Psysteme /*ps1*/, Psysteme /*ps2*/, int /*ofl_ctrl*/);
extern bool pa_system_equal_p_ofl_ctrl(Psysteme /*ps1*/, Psysteme /*ps2*/, int /*ofl_ctrl*/);
extern Pdisjunct pa_system_difference_ofl_ctrl(Psysteme /*ps1*/, Psysteme /*ps2*/, int /*ofl_ctrl*/);
extern bool pa_convex_hull_equals_union_p_ofl_ctrl(Psysteme /*conv_hull*/, Psysteme /*ps1*/, Psysteme /*ps2*/, int /*ofl_ctrl*/, volatile bool /*ofl_res*/);
/* sc_list.c */
extern char *(*union_variable_name)(Variable);
extern Psysteme sc_full(void);
extern bool sc_full_p(Psysteme /*in_ps*/);
extern Psysteme sc_dup1(Psysteme /*in_ps*/);
extern Psysteme sc_free(Psysteme /*in_ps*/);
extern Psysteme sc_free1(Psysteme /*in_ps*/);
extern Psysteme sc_concatenate(Psysteme /*in_s1*/, Psysteme /*in_s2*/);
extern bool sl_length(Psyslist /*in_sl*/);
extern int sl_max_constraints_nb(Psyslist /*in_sl*/);
extern bool sl_is_system_p(Psyslist /*in_sl*/);
extern Psyslist sl_append_system(Psyslist /*in_sl*/, Psysteme /*in_ps*/);
extern Psyslist sl_append_system_first(Psyslist /*in_sl*/, Psysteme /*in_ps*/);
extern Psyslist sl_new(void);
extern Psyslist sl_dup(Psyslist /*in_sl*/);
extern Psyslist sl_dup1(Psyslist /*in_sl*/);
extern Psyslist sl_free(Psyslist /*psl*/);
extern Psyslist sl_free1(Psyslist /*psl*/);
extern void sl_set_variable_name(char *(* /*in_fu*/)(void));
extern char *sl_get_tab_string(int /*in_tab*/);
extern void sl_fprint_tab(FILE */*in_fi*/, Psyslist /*in_sl*/, char *(* /*in_fu*/)(void), int /*in_tab*/);
extern void sl_fprint(FILE */*in_fi*/, Psyslist /*in_sl*/, char *(* /*in_fu*/)(void));
extern Psyslist sl_read(char */*nomfic*/);
extern void un_fprint_tab(FILE */*in_fi*/, char */*in_un*/, char *(* /*in_fu*/)(void), int /*in_ty*/, int /*in_tab*/);
#endif /*  union_header_included */
