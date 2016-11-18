/* Warning! Do not modify this file that is automatically generated! */
/* Modify src/Libs/comp_sections/comp_sections-local.h instead, to add your own modifications. */

/* header file built by cproto */

#ifndef  comp_sections_header_included
#define  comp_sections_header_included
/*

  $Id: comp_sections-local.h 23065 2016-03-02 09:05:50Z coelho $

  Copyright 1989-2016 MINES ParisTech

  This file is part of PIPS.

  PIPS is free software: you can redistribute it and/or modify it
  under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  any later version.

  PIPS is distributed in the hope that it will be useful, but WITHOUT ANY
  WARRANTY; without even the implied warranty of MERCHANTABILITY or
  FITNESS FOR A PARTICULAR PURPOSE.

  See the GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with PIPS.  If not, see <http://www.gnu.org/licenses/>.

*/
/*{{{  defines*/
/* classifying subscript types for reference template 
 * done in newgen now
 */
#define LIN_INVARIANT		2
#define LIN_VARIANT			1
#define NON_LINEAR		 -1

/* accessing DAD components */
#define LSEC(x,i)	 	GetBoundary(x,i,1)
#define USEC(x,i)	 	GetBoundary(x,i,0)
#define PUT_NEST(d,val)         context_info_nest(simple_section_context(comp_sec_hull(comp_desc_section(d)))) = val
#define GET_NEST(d)         context_info_nest(simple_section_context(comp_sec_hull(comp_desc_section(d))))

/*}}}*/

enum BoundType {LOWER, UPPER};
enum RefType {READ, WRITE};
enum NestType {ZERO, SINGLE, MULTI};

/* used for merging linear expressions */
typedef enum { PLUS, MINUS} OpFlag;

/* only used for in print routines. The analysis does not
 * pose any limit on the number of array dimensions
 */
#define MAX_RANK 8

/*{{{  Dad definition*/
  /* data structures for data access descriptor */
  
  /* Reference Template part of DAD, an array of integers allocated dynamically */
  typedef unsigned int tRT;

  /*  A linear expression in Pips ; Pvecteur is a pointer */
#define LinExpr Pvecteur

  /* bounds are retained as high level tree structures to accommodate symbolic
     information in boundary expressions. When all the symbolic information
     gets resolved then the tree nodes are collapsed into a single instruction
     holding the constant value  
  */

  typedef struct sSimpBound 
  {
    LinExpr lb; /* lower bound */
    LinExpr ub; /* upper bound */
  } tSS;

  /* Simple Section part of DAD
   An array of type SimpBound struct allocated 
   dynamically based on rank of array
  */

  typedef struct DadComponent 
  {
    tRT  *RefTemp;
    tSS  *SimpSec;
  } DadComp;


/*}}}*/
/*{{{  Data structures required for computing Dads*/

/*{{{  structures for TranslateToLoop*/
/* structure to hold both Old and New variants */
typedef struct Variants  {
  list Old;
  list New;
}tVariants;

/*}}}*/

/*}}}*/

typedef simple_section tDad;


#define SEQUENTIAL_COMPSEC_SUFFIX ".csec"
#define USER_COMPSEC_SUFFIX ".ucsec"

/* comp_sections.c */
extern bool summary_complementary_sections(const char */*module_name*/);
extern bool complementary_sections(const char */*module_name*/);
extern bool print_code_complementary_sections(const char */*module_name*/);
/* propagate.c */
extern bool local_comp_regions_map_undefined_p(void);
extern void set_local_comp_regions_map(statement_mapping /*m*/);
extern statement_mapping get_local_comp_regions_map(void);
extern void reset_local_comp_regions_map(void);
extern void free_local_comp_regions_map(void);
extern void make_local_comp_regions_map(void);
extern list load_statement_local_comp_regions(statement /*s*/);
extern void delete_statement_local_comp_regions(statement /*s*/);
extern bool statement_local_comp_regions_undefined_p(statement /*s*/);
extern void store_statement_local_comp_regions(statement /*s*/, list /*t*/);
extern void update_statement_local_comp_regions(statement /*s*/, list /*t*/);
extern void CheckStride(loop /*Loop*/);
extern list CompRegionsExactUnion(list /*l1*/, list /*l2*/, bool (* /*union_combinable_p*/)(effect, effect));
extern list CompRegionsMayUnion(list /*l1*/, list /*l2*/, bool (* /*union_combinable_p*/)(effect, effect));
extern bool comp_regions(const char */*module_name*/);
extern list comp_regions_of_statement(statement /*s*/);
extern list comp_regions_of_instruction(instruction /*i*/, transformer /*t_inst*/, transformer /*context*/, list */*plpropreg*/);
extern list comp_regions_of_block(list /*linst*/);
extern list comp_regions_of_test(test /*t*/, transformer /*context*/, list */*plpropreg*/);
extern list comp_regions_of_loop(loop /*l*/, transformer /*loop_trans*/, transformer /*context*/, list */*plpropreg*/);
extern list comp_regions_of_call(call /*c*/, transformer /*context*/, list */*plpropreg*/);
extern list comp_regions_of_unstructured(unstructured /*u*/, transformer /*t_unst*/);
extern list comp_regions_of_range(range /*r*/, transformer /*context*/);
extern list comp_regions_of_syntax(syntax /*s*/, transformer /*context*/);
extern list comp_regions_of_expressions(list /*exprs*/, transformer /*context*/);
extern list comp_regions_of_expression(expression /*e*/, transformer /*context*/);
extern list comp_regions_of_read(reference /*ref*/, transformer /*context*/);
extern list comp_regions_of_write(reference /*ref*/, transformer /*context*/);
/* ss.c */
extern Pvecteur my_vect_var_subst(Pvecteur /*vect*/, Variable /*var*/, Pvecteur /*new_vect*/);
extern Pvecteur my_vect_substract(Pvecteur /*pvec1*/, Pvecteur /*pvec2*/);
extern void PrintCompRegions(list /*CompList*/);
extern void PrintLinExpr(Pvecteur /*Lin*/);
extern void PrintSimp(comp_desc /*Dad*/);
extern void DisplayDad(comp_desc /*TheDad*/);
extern void DisplayRefTemp(simple_section /*Dad*/);
extern void DisplaySimpleSection(simple_section /*Dad*/);
extern tag GetRefTemp(simple_section /*Dad*/, _int /*DimNo*/);
extern void PutRefTemp(simple_section /*Dad*/, int /*DimNo*/, tag /*Val*/);
extern Pvecteur GetBoundary(simple_section /*Dad*/, int /*DimNo*/, unsigned /*Low*/);
extern void PutBoundPair(simple_section /*Dad*/, _int /*DimNo*/, Pvecteur /*Low*/, Pvecteur /*Up*/);
extern Pvecteur MinBoundary(Pvecteur /*Lin1*/, Pvecteur /*Lin2*/);
extern Pvecteur MaxBoundary(Pvecteur /*Lin1*/, Pvecteur /*Lin2*/);
extern Pvecteur MergeLinExprs(Pvecteur /*Expr1*/, Pvecteur /*Expr2*/, OpFlag /*Op*/);
extern unsigned int ComputeIndex(unsigned int /*I*/, unsigned int /*J*/, unsigned int /*Rank*/);
extern Pvecteur CopyAccVec(Pvecteur /*Expr*/);
extern bool IsExprConst(Pvecteur /*Expr*/);
extern bool DivExists(loop /*Loop*/, Pvecteur /*Lin*/);
extern expression GetAccVec(unsigned /*No*/, const reference /*ref*/);
extern unsigned int CardinalityOf(list /*gl*/);
extern dad_struct AllocateDadStruct(int /*Rank*/);
extern simple_section AllocateSimpleSection(reference /*ref*/);
extern void ScanAllDims(loop /*Loop*/, comp_desc /*Desc*/);
extern void ComputeRTandSS(expression /*Sub*/, unsigned /*DimNo*/, simple_section /*Dad*/, loop /*Loop*/);
extern void TranslateRefsToLoop(loop /*ThisLoop*/, list /*ListOfComps*/);
extern void TranslateToLoop(loop /*ThisLoop*/, comp_desc /*Desc*/);
extern tVariants TransRefTemp(loop /*ThisLoop*/, comp_desc /*Desc*/);
extern void UpdateUnresolved(simple_section /*Dad*/, loop /*Loop*/);
extern void ComputeBoundaries(simple_section /*Dad*/, loop /*Loop*/, Pvecteur /*lbExpr*/, Pvecteur /*ubExpr*/, unsigned /*Offset*/);
extern void TransSimpSec(comp_desc /*Desc*/, loop /*Loop*/, tVariants */*Vars*/);
extern Pvecteur Lbound(loop /*Loop*/, Pvecteur /*Lin*/);
extern Pvecteur Ubound(loop /*Loop*/, Pvecteur /*Lin*/);
extern simple_section SimpUnion(simple_section /*S1*/, simple_section /*S2*/);
/* operators.c */
extern comp_desc InitCompDesc(reference /*ref*/, tag /*ReadWrite*/);
extern comp_sec CompUnion(comp_sec /*cs1*/, comp_sec /*cs2*/);
extern bool CompIntersection(comp_sec /*cs1*/, comp_sec /*cs2*/);
/* myintrinsics.c */
extern list comp_regions_of_intrinsic(entity /*e*/, list /*args*/, transformer /*context*/);
extern list proper_comp_regions_of_intrinsic(entity /*e*/, list /*args*/, transformer /*context*/);
extern list no_write_comp_regions(entity /*e*/, list /*args*/, transformer /*context*/);
extern list affect_comp_regions(entity /*e*/, list /*args*/, transformer /*context*/);
extern list io_comp_regions(entity /*e*/, list /*args*/, transformer /*context*/);
extern list comp_regions_of_ioelem(expression /*exp*/, tag /*act*/, transformer /*context*/);
extern list comp_regions_of_iolist(list /*exprs*/, tag /*act*/, transformer /*context*/);
extern list comp_regions_of_implied_do(expression /*exp*/, tag /*act*/, transformer /*context*/);
/* dbase.c */
extern comp_desc_set list_to_comp_secs(list /*l_eff*/);
extern list comp_desc_set_to_list(comp_desc_set /*cset*/);
extern statement_mapping listmap_to_compsecs_map(statement_mapping /*l_map*/);
extern statement_mapping comp_secs_map_to_listmap(statement_mapping /*compsecs_map*/);
extern list comp_regions_dup(list /*l_reg*/);
extern comp_desc comp_region_dup(comp_desc /*reg*/);
extern list comp_region_add_to_regions(comp_desc /*reg*/, list /*l_reg*/);
/* prettyprint.c */
extern text get_text_comp_regions(const char */*module_name*/);
extern bool print_source_comp_regions(const char */*module_name*/);
extern bool print_code_comp_regions(const char */*module_name*/);
extern text text_all_comp_regions(list /*l_reg*/);
extern text text_comp_regions(list /*l_reg*/);
extern text text_comp_region(effect /*reg*/);
#endif /*  comp_sections_header_included */
