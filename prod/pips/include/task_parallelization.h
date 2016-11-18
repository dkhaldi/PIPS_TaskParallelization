/* Warning! Do not modify this file that is automatically generated! */
/* Modify src/Libs/task_parallelization/task_parallelization-local.h instead, to add your own modifications. */

/* header file built by cproto */

#ifndef  task_parallelization_header_included
#define  task_parallelization_header_included
/* parameters of BDSC, to be recovered using pips properties */
int  NBCLUSTERS;
int  MEMORY_SIZE;
string INSTRUMENTED_FILE;
/* Global variables */
gen_array_t annotations;
gen_array_t clusters;


typedef struct {
  double tlevel;
  double blevel;
  double prio;
  double task_time;
  gen_array_t edge_cost;
  list data;
  bool scheduled;
  int order_sched;
  int cluster;
  int nbclusters;
}annotation;

typedef struct {
  double time;
  list data;
}cluster;
/* SDG.c */
extern int NBCLUSTERS;
extern int MEMORY_SIZE;
extern string INSTRUMENTED_FILE;
extern gen_array_t annotations;
extern gen_array_t clusters;
extern _Bool statement_equal_p(statement /*s1*/, statement /*s2*/);
extern vertex statement_to_vertex(statement /*s*/, graph /*g*/);
extern graph partitioning_sdg(statement /*module_stmt*/);
extern void print_SDGs(statement /*stmt*/, graph /*tg*/, FILE */*ftg*/, gen_array_t /*annotations*/);
extern _Bool sequence_dependence_graph(char */*module_name*/);
/* cost_model.c */
extern _Bool costly_task(statement /*st*/);
extern double polynomial_to_numerical(Ppolynome /*poly_amount*/);
extern double size_of_regions(list /*l_data*/);
extern double edge_cost(statement /*s1*/, statement /*s2*/);
extern double t_level(vertex /*v*/, graph /*dg*/, gen_array_t /*annotations*/);
extern void top_level(graph /*dg*/, gen_array_t /*annotations*/);
extern void bottom_level(graph /*dg*/, gen_array_t /*annotations*/);
extern void priorities(gen_array_t /*annotations*/);
extern void initialization(graph /*dg*/, gen_array_t /*annotations*/);
extern void parse_instrumented_file(char */*file_name*/, graph /*dg*/, gen_array_t /*annotations*/);
/* BDSC.c */
extern void allocate_task_to_cluster(statement /*ready_st*/, int /*cl_p*/, int /*order*/);
extern int BDSC(sequence /*seq*/, int /*P*/, int /*M*/, int /*ordering*/);
extern int DSC(sequence /*seq*/, int /*ordering*/);
/* HBDSC.c */
extern graph kdg;
extern graph ddg;
extern statement return_st;
extern persistant_statement_to_cluster stmt_to_cluster;
extern list topological_sort(statement /*stmt*/);
extern int hierarchical_schedule(statement /*stmt*/, int /*k*/, int /*P*/, int /*M*/, _Bool /*dsc_p*/);
extern _Bool hbdsc_parallelization(char */*module_name*/);
extern _Bool dsc_code_parallelization(char */*module_name*/);
/* instrumentation.c */
extern _Bool bdsc_code_instrumentation(char */*module_name*/);
/* spire_generation.c */
extern list com_declarations_to_add;
extern void cluster_stage_spire_generation(persistant_statement_to_cluster /*stmt_to_cluster*/, graph /*tg*/, statement /*stmt*/, int /*P*/);
extern _Bool spire_shared_unstructured_to_structured(char */*module_name*/);
extern _Bool spire_distributed_unstructured_to_structured(char */*module_name*/);
/* communication_generation.c */
extern statement make_com_loopbody(entity /*v*/, _Bool /*neighbor*/, list /*vl*/, int /*k*/);
extern statement region_to_com_nest(effect /*r*/, _Bool /*isRead*/, int /*k*/);
extern void communications_construction(graph /*tg*/, statement /*stmt*/, persistant_statement_to_cluster /*st_to_cluster*/, int /*kp*/);
/* openmp_generation.c */
extern _Bool openmp_task_generation(char */*module_name*/);
/* mpi_generation.c */
extern _Bool mpi_task_generation(char */*module_name*/);
#endif /*  task_parallelization_header_included */
