/* Warning! Do not modify this file that is automatically generated! */
/* Modify src/Libs/alias-classes/alias-classes-local.h instead, to add your own modifications. */

/* header file built by cproto */

#ifndef  alias_classes_header_included
#define  alias_classes_header_included
/*

  $Id: alias-classes-local.h 23065 2016-03-02 09:05:50Z coelho $

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
#include "points_to_private.h"
#include "effects.h"
#define SEQUENTIAL_POINTS_TO_SETS_SUFFIX ".pt"
#define USER_POINTS_TO_SETS_SUFFIX ".upt"

// FI: just in case another data structure would be more suitable or
// more efficient
// For instance, set of points-to could be a type declared in
// points_to_private.tex
#if 0
typedef set pt_map;
#define pt_map_undefined set_undefined
#define pt_map_undefined_p(pt) ((pt)==set_undefined)
#define new_pt_map() set_generic_make(set_private, points_to_equal_p, points_to_rank)
#define assign_pt_map(x,y) set_assign(x, y)
#define clear_pt_map(pt) set_clear(pt)
#define free_pt_map(pt) set_free(pt)
#define print_pt_map(pt) print_points_to_set("",pt);
// FI: varargs; probably OK with gcc preprocessor
#define free_pt_maps sets_free
#define union_of_pt_maps(pt1, pt2, pt3) set_union(pt1, pt2, pt3)
#define difference_of_pt_maps(pt1, pt2, pt3) set_difference(pt1, pt2, pt3)

#define empty_pt_map_p(s) set_empty_p(s)
#define consistent_pt_map_p(s) consistent_points_to_set(s)
// FI: Not so sure we do not need a new name
#define source_in_pt_map_p(cell,set) source_in_set_p(cell,set)
#define add_arc_to_pt_map(a, s) set_add_element((set) s, (set) s, (void *) a)

// FI: useful to have a function for debugging
#define remove_arc_from_pt_map(a, s) set_del_element((set) s, (set) s, (void *) a)

// A reminder:
// full_copy_pt_map(pt_map m)
#else
typedef points_to_graph pt_map;
#define pt_map_undefined points_to_graph_undefined
#define pt_map_undefined_p(pt) ((pt)==points_to_graph_undefined)
#define new_pt_map() make_points_to_graph(false, set_generic_make(set_private, points_to_equal_p, points_to_rank))
#define new_simple_pt_map() set_generic_make(set_private, points_to_equal_p, points_to_rank)
#define assign_pt_map(x,y) ((void) set_assign(points_to_graph_set(x), points_to_graph_set(y)), (x))
#define clear_pt_map(pt) set_clear(points_to_graph_set(pt))
// FI: free_set() is a shallow free, free_points_to_graph() is a deep free
#define free_pt_map(pt) free_points_to_graph(pt)
#define print_pt_map(pt) print_points_to_set("", points_to_graph_set(pt));
// FI: varargs; probably OK with gcc preprocessor
#define free_pt_maps free_points_to_graph_sets

#define union_of_pt_maps(pt1, pt2, pt3) set_union(points_to_graph_set(pt1), \
						  points_to_graph_set(pt2), \
						  points_to_graph_set(pt3))
#define difference_of_pt_maps(pt1, pt2, pt3) \
  set_difference(points_to_graph_set(pt1), \
		 points_to_graph_set(pt2), \
		 points_to_graph_set(pt3))

#define empty_pt_map_p(s) set_empty_p(points_to_graph_set(s))
//#define consistent_pt_map_p(s) consistent_points_to_set(points_to_graph_set(s))
#define consistent_pt_map_p(s) consistent_points_to_graph_p(s)
// FI: Not so sure we do not need a new name
#define source_in_pt_map_p(cell,set) source_in_set_p(cell,points_to_graph_set(set))
// Returns pt_map s after update via side-effect
#define add_arc_to_pt_map(a, s) (set_add_element((set) points_to_graph_set(s), (set) points_to_graph_set(s), (void *) a), (s))
#define add_arc_to_simple_pt_map(a, s) set_add_element((set) s, (set) s, (void *) a)

// FI: useful to have a function for debugging
#define remove_arc_from_pt_map(a, s) (set_del_element((set) points_to_graph_set(s), (set) points_to_graph_set(s), (void *) a), (s))
#define remove_arc_from_simple_pt_map(a, s) set_del_element((set) s, (set) s, (void *) a)

// A reminder:
// full_copy_pt_map(pt_map m)
#endif
/* alias_pairs.c */
extern bool in_alias_pairs(const string /*module_name*/);
extern bool out_alias_pairs(const char */*module_name*/);
/* alias_lists.c */
extern bool alias_lists(const string /*module_name*/);
/* alias_classes.c */
extern bool alias_classes(const char */*module_name*/);
/* prettyprint.c */
extern bool print_in_alias_pairs(const char */*module_name*/);
extern bool print_out_alias_pairs(const char */*module_name*/);
extern bool print_alias_lists(const char */*module_name*/);
extern bool print_alias_classes(const char */*module_name*/);
#endif /*  alias_classes_header_included */
