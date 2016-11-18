/* Warning! Do not modify this file that is automatically generated! */
/* Modify src/Libs/callgraph/callgraph-local.h instead, to add your own modifications. */

/* header file built by cproto */

#ifndef  callgraph_header_included
#define  callgraph_header_included
/*

  $Id: callgraph-local.h 23065 2016-03-02 09:05:50Z coelho $

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
/* callgraph.h
   include file for callgraphs
 */

#ifndef CALLGRAPH_INCLUDED
#define CALLGRAPH_INCLUDED

#define CALLGRAPH_NOT_FOUND NULL

#define CALLGRAPH_DRAW "CALLGRAPH_DRAW"
#define CALLGRAPH_DEBUG "CALLGRAPH_DEBUG"
#define CALLGRAPH_DEBUG_LEVEL "CALLGRAPH_DEBUG_LEVEL"
#define CALLGRAPH_SHORT_NAMES "CALLGRAPH_SHORT_NAMES"

#define CALLGRAPH_INDENT 4

#endif /* CALLGRAPH_INCLUDED */
/* callgraph.c */
extern list string_to_callees(const string /*module_name*/);
extern list entity_to_callees(entity /*mod*/);
extern bool module_is_called_by_main_program_p(entity /*mod*/);
extern list callers_to_call_sites(list /*callers_statement*/, entity /*called_module*/);
extern list callers_to_statements(list /*callers*/);
extern void sort_parameters(entity /*module*/, gen_cmp_func_t /*cmp*/);
extern bool module_to_callgraph(entity /*module*/, text (* /*module_to_text*/)(const string));
extern callees compute_callees(const statement /*stat*/);
extern bool callgraph(const string /*name*/);
/* print.c */
extern void print_callees(callees /*c*/);
extern bool print_decorated_call_graph(const string /*module_name*/, text (* /*module_to_text*/)(const string));
extern bool print_call_graph(const string /*module_name*/);
/* graph.c */
extern bool graph_of_calls(const string /*name*/);
extern bool full_graph_of_calls(string /*name*/);
#endif /*  callgraph_header_included */
