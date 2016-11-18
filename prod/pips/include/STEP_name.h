/*
  Variable name in genereted file
*/

#define STEP_SLICE_INDEX_NAME "IDX"
#define STEP_INDEX_LOW_NAME(index) concatenate(entity_user_name(index),"_LOW",NULL)
#define STEP_INDEX_UP_NAME(index) concatenate(entity_user_name(index),"_UP",NULL)
#define STEP_BOUNDS_LOW(index) concatenate("STEP_", entity_user_name(index),"_LOW", NULL)
#define STEP_BOUNDS_UP(index) concatenate("STEP_", entity_user_name(index),"_UP", NULL)
#define STEP_LOOPSLICES_NAME(index) concatenate("STEP_",entity_user_name(index),"_LOOPSLICES",NULL)
#define STEP_SR_NAME(array) concatenate("STEP_SR_",entity_user_name(array),NULL)
#define STEP_RR_NAME(array) concatenate("STEP_RR_",entity_user_name(array),NULL)

/* In Runtime/step/STEP.h */
#define STEP_COMM_SIZE_NAME         "STEP_COMM_SIZE"    /* variable */
#define STEP_COMM_RANK_NAME	    "STEP_COMM_RANK"    /* variable */
/* Runtime MACRO (generated from step_common.h ) */
#define STEP_BARRIER_NAME "STEP_BARRIER"
#define STEP_C_NAME "STEP_C"
#define STEP_COMPLEX16_NAME "STEP_COMPLEX16"
#define STEP_COMPLEX8_NAME "STEP_COMPLEX8"
#define STEP_COMPLEX_NAME "STEP_COMPLEX"
#define STEP_DO_NAME "STEP_DO"
#define STEP_DOUBLE_PRECISION_NAME "STEP_DOUBLE_PRECISION"
#define STEP_FORTRAN_NAME "STEP_FORTRAN"
#define STEP_INDEX_SLICE_LOW_NAME "STEP_INDEX_SLICE_LOW"
#define STEP_INDEX_SLICE_UP_NAME "STEP_INDEX_SLICE_UP"
#define STEP_INTEGER1_NAME "STEP_INTEGER1"
#define STEP_INTEGER2_NAME "STEP_INTEGER2"
#define STEP_INTEGER4_NAME "STEP_INTEGER4"
#define STEP_INTEGER8_NAME "STEP_INTEGER8"
#define STEP_INTEGER_NAME "STEP_INTEGER"
#define STEP_MASTER_NAME "STEP_MASTER"
#define STEP_MAX_NB_LOOPSLICES_NAME "STEP_MAX_NB_LOOPSLICES"
#define STEP_MAX_REDUCE_NAME "STEP_MAX_REDUCE"
#define STEP_MIN_REDUCE_NAME "STEP_MIN_REDUCE"
#define STEP_NBLOCKING_ALG_NAME "STEP_NBLOCKING_ALG"
#define STEP_NOWAIT_NAME "STEP_NOWAIT"
#define STEP_PARALLEL_DO_NAME "STEP_PARALLEL_DO"
#define STEP_PARALLEL_NAME "STEP_PARALLEL"
#define STEP_PROD_REDUCE_NAME "STEP_PROD_REDUCE"
#define STEP_REAL16_NAME "STEP_REAL16"
#define STEP_REAL4_NAME "STEP_REAL4"
#define STEP_REAL8_NAME "STEP_REAL8"
#define STEP_REAL_NAME "STEP_REAL"
#define STEP_SINGLE_NAME "STEP_SINGLE"
#define STEP_SUM_REDUCE_NAME "STEP_SUM_REDUCE"
#define STEP_TAG_DEFAULT_NAME "STEP_TAG_DEFAULT"
#define STEP_THREADPRIVATE_NAME "STEP_THREADPRIVATE"
#define STEP_TYPE_UNDEFINED_NAME "STEP_TYPE_UNDEFINED"
#define STEP_UNDEF_REDUCE_NAME "STEP_UNDEF_REDUCE"
#define STEP_WAIT_NAME "STEP_WAIT"
/* Runtime MACRO (end) */
/* Runtime API intrinsic name (generated from step_api.h ) */
#define RT_STEP_alltoall_full_interlaced "STEP_ALLTOALL_FULL_INTERLACED"
#define RT_STEP_alltoall_full "STEP_ALLTOALL_FULL"
#define RT_STEP_alltoall_partial_interlaced "STEP_ALLTOALL_PARTIAL_INTERLACED"
#define RT_STEP_alltoall_partial "STEP_ALLTOALL_PARTIAL"
#define RT_STEP_alltoall "STEP_ALLTOALL"
#define RT_STEP_barrier "STEP_BARRIER"
#define RT_STEP_compute_loopslices "STEP_COMPUTE_LOOPSLICES"
#define RT_STEP_construct_begin "STEP_CONSTRUCT_BEGIN"
#define RT_STEP_construct_end "STEP_CONSTRUCT_END"
#define RT_STEP_finalize "STEP_FINALIZE"
#define RT_STEP_flush "STEP_FLUSH"
#define RT_STEP_get_commsize "STEP_GET_COMMSIZE"
#define RT_STEP_get_loopbounds "STEP_GET_LOOPBOUNDS"
#define RT_STEP_get_rank "STEP_GET_RANK"
#define RT_STEP_init_arrayregions "STEP_INIT_ARRAYREGIONS"
#define RT_STEP_init_c_order "STEP_INIT_C_ORDER"
#define RT_STEP_init_fortran_order "STEP_INIT_FORTRAN_ORDER"
#define RT_STEP_initreduction "STEP_INITREDUCTION"
#define RT_STEP_reduction "STEP_REDUCTION"
#define RT_STEP_register_alltoall_partial "STEP_REGISTER_ALLTOALL_PARTIAL"
#define RT_STEP_set_interlaced_sendregions "STEP_SET_INTERLACED_SENDREGIONS"
#define RT_STEP_set_recvregions "STEP_SET_RECVREGIONS"
#define RT_STEP_set_reduction_sendregions "STEP_SET_REDUCTION_SENDREGIONS"
#define RT_STEP_set_sendregions "STEP_SET_SENDREGIONS"
#define RT_STEP_timer_dump "STEP_TIMER_DUMP"
#define RT_STEP_timer_event "STEP_TIMER_EVENT"
#define RT_STEP_timer_finalize "STEP_TIMER_FINALIZE"
#define RT_STEP_timer_init "STEP_TIMER_INIT"
#define RT_STEP_timer_reset "STEP_TIMER_RESET"
/* Runtime API intrinsic name (end) */
