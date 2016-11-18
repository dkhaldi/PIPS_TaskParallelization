/* Warning! Do not modify this file that is automatically generated! */
/* Modify src/Libs/icfg/icfg-local.h instead, to add your own modifications. */

/* header file built by cproto */

#ifndef  icfg_header_included
#define  icfg_header_included
/*

  $Id: icfg-local.h 23065 2016-03-02 09:05:50Z coelho $

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
/*
   icfg.h -- acronym
   include file for Interprocedural Control Flow Graph
 */

#define ICFG_NOT_FOUND NULL
#define ICFG_OPTIONS "tcdDIFl"

#define ICFG_CALLEES_TOPO_SORT "ICFG_CALLEES_TOPO_SORT"
#define ICFG_DRAW "ICFG_DRAW"
#define ICFG_DEBUG "ICFG_DEBUG"
#define ICFG_DEBUG_LEVEL "ICFG_DEBUG_LEVEL"
#define ICFG_DOs "ICFG_DOs"
#define ICFG_IFs "ICFG_IFs"
#define ICFG_DV "ICFG_DV"
#define ICFG_FLOATs "ICFG_FLOATs"
#define ICFG_SHORT_NAMES "ICFG_SHORT_NAMES"

#include "dg.h"

typedef dg_arc_label arc_label;
typedef dg_vertex_label vertex_label;

#include "graph.h"

#define CALL_MARK "CALL_MARK@@@@"
#define ADD_ELEMENT_TO_LIST( _list, _type, _element) \
    (_list = gen_nconc( _list, CONS( _type, _element, NIL)))

/* toposort.c */
extern list module_name_to_callees(const char */*module_name*/);
extern list module_to_callees(entity /*mod*/);
extern void topological_number_assign_to_module(hash_table /*hash_module_to_depth*/, entity /*mod*/, size_t /*n*/);
extern list module_list_sort(hash_table /*hash_module_to_depth*/, list /*current_list*/, entity /*mod*/, size_t /*n*/);
extern list topologically_sorted_module_list(entity /*mod*/);
extern void print_module_name_to_toposorts(const char */*module_name*/);
/* icfg_scan.c */
extern void icfg_set_indentation(int /*indent*/);
extern void icfg_reset_indentation(void);
extern void icfg_error_handler(void);
extern bool generic_print_icfg(const string /*module_name*/, bool /*with_ifs*/, bool /*with_loops*/, bool /*do_graph*/, text (* /*decoration*/)(const string));
extern bool generic_print_icfg_precise(const string /*module_name*/, bool /*with_ifs*/, bool /*with_loops*/, bool /*do_graph*/, text (* /*decoration*/)(entity, entity, statement, call));
extern bool generic_print_icfg_filtered(const string /*module_name*/, bool /*with_ifs*/, bool /*with_loops*/, bool /*do_graph*/, text (* /*decoration_call*/)(entity, statement, call), text (* /*decoration_stmt*/)(entity, statement));
/* print.c */
extern bool print_icfg(const string /*module_name*/);
extern bool print_icfg_with_loops(const string /*module_name*/);
extern bool print_icfg_with_control(const string /*module_name*/);
/* util.c */
extern void safe_free_vertex(vertex /*ver*/, list /*l_of_vers*/);
extern list safe_add_vertex_to_list(vertex /*ver*/, list /*l_of_vers*/);
extern list list_of_connected_nodes(vertex /*ver*/, list /*l_of_vers*/);
extern vertex get_vertex_by_string(const char */*str_name*/, list /*l_of_vers*/);
extern list safe_make_successor(vertex /*ver_parent*/, vertex /*ver_child*/, list /*l_of_vers*/);
extern void print_graph_of_text_to_daVinci(FILE */*f_out*/, list /*l_of_vers*/);
extern void print_graph_daVinci_from_starting_node(FILE */*f_out*/, vertex /*start_ver*/);
extern void print_marged_text_from_starting_node(FILE */*fd*/, int /*margin*/, vertex /*start_ver*/, list /*l_of_vers*/);
extern bool make_resource_from_starting_node(const char */*mod_name*/, string /*res_name*/, string /*file_ext*/, vertex /*start_ver*/, list /*l_of_vers*/, bool /*res_text_type*/);
#endif /*  icfg_header_included */
