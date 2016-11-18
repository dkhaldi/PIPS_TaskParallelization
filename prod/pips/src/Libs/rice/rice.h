/* Warning! Do not modify this file that is automatically generated! */
/* Modify src/Libs/rice/rice-local.h instead, to add your own modifications. */

/* header file built by cproto */

#ifndef  rice_header_included
#define  rice_header_included
/*

  $Id: rice-local.h 23065 2016-03-02 09:05:50Z coelho $

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
/* macros */
#define VERTEX_ENCLOSING_SCC(v) \
    sccflags_enclosing_scc(dg_vertex_label_sccflags((dg_vertex_label) \
	vertex_vertex_label(v)))


/* a macro to insert an element at the end of a list. c is the element
to insert.  bl and el are pointers to the begining and the end of the
list. */

#define INSERT_AT_END(bl, el, c) \
    { cons *_insert_ = c; if (bl == NIL) bl = _insert_; else CDR(el) = _insert_; el = _insert_; CDR(el) = NIL; }


/* external variables. see declarations in kennedy.c */
extern graph dg;
extern bool rice_distribute_only;
extern int Nbrdoall;
/* rice.c */
extern graph dg;
extern bool rice_distribute_only;
extern int enclosing;
extern void rice_unstructured(unstructured /*u*/, int /*l*/, statement (* /*codegen_fun*/)(statement, graph, set, int, bool));
extern statement rice_statement(statement /*stat*/, int /*l*/, statement (* /*codegen_fun*/)(statement, graph, set, int, bool));
extern statement rice_loop(statement /*stat*/, int /*l*/, statement (* /*codegen_fun*/)(statement, graph, set, int, bool));
extern bool do_it(string /*mod_name*/, bool /*distribute_p*/, string /*what*/, statement (* /*codegen_fun*/)(statement, graph, set, int, bool));
extern bool distributer(string /*mod_name*/);
extern bool rice_all_dependence(string /*mod_name*/);
extern bool rice_data_dependence(string /*mod_name*/);
extern bool rice_cray(string /*mod_name*/);
/* codegen.c */
extern bool ignore_this_conflict(vertex /*v1*/, vertex /*v2*/, conflict /*c*/, int /*l*/);
extern statement find_level_l_loop_statement(scc /*s*/, int /*l*/);
extern set scc_region(scc /*s*/);
extern bool contains_level_l_dependence(scc /*s*/, set /*region*/, int /*level*/);
extern bool strongly_connected_p(scc /*s*/, int /*l*/);
extern statement MakeNestOfParallelLoops(int /*l*/, cons */*loops*/, statement /*body*/, bool /*task_parallelize_p*/);
extern int statement_imbrication_level(statement /*st*/);
extern statement MakeNestOfStatementList(int /*l*/, int /*nbl*/, list */*lst*/, list /*loops*/, list */*block*/, list */*eblock*/, bool /*task_parallelize_p*/);
extern statement CodeGenerate(statement /*stat*/, graph /*g*/, set /*region*/, int /*l*/, bool /*task_parallelize_p*/);
extern statement MakeLoopAs(statement /*old_loop_statement*/, tag /*seq_or_par*/, statement /*body*/);
extern statement IsolatedStatement(scc /*s*/, int /*l*/, bool /*task_parallelize_p*/);
extern statement ConnectedStatements(graph /*g*/, scc /*s*/, int /*l*/, bool /*task_parallelize_p*/);
/* scc.c */
extern void set_sccs_drivers(bool (* /*ignore_this_vertex_fun*/)(set, vertex), bool (* /*ignore_this_successor_fun*/)(vertex, set, successor, int));
extern void reset_sccs_drivers(void);
extern void LowlinkCompute(graph /*g*/, set /*region*/, vertex /*v*/, int /*level*/, sccs /*Components*/);
extern int IsInStack(vertex /*v*/);
extern sccs FindSccs(graph /*g*/, set /*region*/, int /*level*/);
extern void ComputeInDegree(graph /*g*/, set /*region*/, int /*l*/);
extern list TopSortSccs(graph /*g*/, set /*region*/, int /*l*/, sccs /*Components*/);
extern list FindAndTopSortSccs(graph /*g*/, set /*region*/, int /*l*/);
extern void PrintScc(scc /*s*/);
extern void PrintSccs(sccs /*ss*/);
/* icm.c */
extern void dump_sef(statement_effects /*se*/);
extern void print_list_entities(list /*l*/);
extern bool invariant_code_motion(const char */*module_name*/);
#endif /*  rice_header_included */
