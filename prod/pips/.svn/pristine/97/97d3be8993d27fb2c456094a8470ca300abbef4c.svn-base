/*

  $Id$

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
#ifdef HAVE_CONFIG_H
    #include "pips_config.h"
#endif

/* Interface with points-to library */

#include <stdio.h>
#include <string.h>

#include "genC.h"
#include "linear.h"

#include "misc.h"
#include "properties.h"

#include "ri.h"
#include "effects.h"

#include "ri-util.h"
#include "prettyprint.h"
#include "effects-util.h"

#include "text-util.h"

#include "effects-simple.h"

#include "pips-libs.h"
#ifdef HAVE_PIPS_points_to_LIBRARY
// for get_points_to_graph_from_statement & expression_to_points_to_sinks
#include "points-to.h" // 2 or more functions
#else // no HAVE_PIPS_points_to_LIBRARY
// typedef set points_to_graph
points_to_graph get_points_to_graph_from_statement(
  _UNUSED_ statement st)
{
  pips_internal_error("points-to library not available");
  return NULL;
}

list expression_to_points_to_sinks(
  _UNUSED_ expression e,
  _UNUSED_ points_to_graph in)
{
  pips_internal_error("points-to library not available");
  return NIL;
}

list expression_to_points_to_sources(
  _UNUSED_ expression e,
  _UNUSED_ points_to_graph in)
{
  pips_internal_error("points-to library not available");
  return NIL;
}

set user_call_to_points_to_interprocedural_binding_set(call c,
						       pt_map pt_caller)
{
  pips_internal_error("points-to library not available");
  return NIL;
}
#endif // HAVE_PIPS_points_to_LIBRARY

#include "transformer.h"

/* Special wrapping for the semantics analyses
 *
 * FI: check if new cells are allocated to build the returned location
 * list ll...
 */
list semantics_expression_to_points_to_sources(expression e)
{
  points_to_graph ptg = points_to_graph_undefined;
  if (!pt_to_list_undefined_p()) {
    statement curstat =  get_current_statement_from_statement_global_stack();
    ptg = get_points_to_graph_from_statement(curstat);
  }

  list ll = expression_to_points_to_sources(e, ptg);
  return ll;
}

/* Returns a list of cells */
list semantics_expression_to_points_to_sinks(expression e)
{
  list ll = list_undefined;
  if(pt_to_list_undefined_p()) {
    type t = points_to_expression_to_concrete_type(e);
    cell c = make_anywhere_points_to_cell(t);
    ll = CONS(CELL, c, NIL);
  }
  else {
    statement curstat =  get_current_statement_from_statement_global_stack();
    points_to_graph ptg = get_points_to_graph_from_statement(curstat);
    ll = expression_to_points_to_sinks(e, ptg);
  }
  return ll;
}

/* If both "se", rouce entity, and "de", destination entity, are
 * defined, substitute the values of "se" by the values of "de" in
 * "backward_p" mode, when translating a callee transformer at a call
 * site of a caller.
 *
 * If the "se" entity cannot be substituted, its value must be
 * project.
 */
transformer substitute_scalar_stub_in_transformer(transformer tf, entity se, entity de, bool backward_p, list * ppl)
{
  if(entity_undefined_p(se))
    ;
  else if(entity_undefined_p(de))
    *ppl = CONS(ENTITY, se, *ppl);
  else if(entity_has_values_p(de)) {
    // Not in the caller's frame
    // entity nsv = entity_to_new_value(se);
    entity nsv = se;
    entity ndv = entity_to_new_value(de);
    entity osv = global_new_value_to_global_old_value(nsv);
    entity odv = entity_to_old_value(de);
    // FI: first cut, must switch to references to handle fields
    if(backward_p) { // For transformers
      // tf = transformer_add_equality(tf, nsv, ndv);
      // tf = transformer_add_equality(tf, osv, odv);
      tf = transformer_value_substitute(tf, nsv, ndv);
      tf = transformer_value_substitute(tf, osv, odv);
    }
    else { // For preconditions
      tf = transformer_value_substitute(tf, ndv, nsv);
      tf = transformer_value_substitute(tf, odv, osv);
    }
  }
  else {
    // FI: could be some debugging stuff
    pips_user_warning("Stub \"%s\" cannot be substituted.\n",
		      entity_user_name(de));
    // FI: entity "de" must be projected
    *ppl = CONS(ENTITY, se, *ppl);
  }
  return tf;
}

/* Exploit the binding map to substitute calles's stubs by actual
 * arguments, which may be stubs of the callers,
 *
 * backward_p request a substitution from the callees' frame into the
 * caller's frame, which is useful for transformers. Flag bacard_p is
 * set to false to compute summary preconditions.
 */
transformer substitute_stubs_in_transformer(transformer tf, call c, statement s, bool backward_p)
{
  if(pt_to_list_undefined_p()) {
    // Return tf as is
  }
  else {
    points_to_graph ptg = get_points_to_graph_from_statement(s);
    bool bottom_p = points_to_graph_bottom(ptg);

    if(bottom_p) {
      // FI: should this lead to an empty transformer?
      pips_internal_error("Not implemented yet.\n");
    }
    else {
      set binding = user_call_to_points_to_interprocedural_binding_set(c, ptg);
      list pl = NIL; // FI: I am not sure we can managed forward and
		     // backward projections with one variable
      SET_FOREACH(points_to, pt, binding) {
	approximation ap = points_to_approximation(pt);
	if(approximation_exact_p(ap) || approximation_must_p(ap)) {
	  cell s = points_to_source(pt); // callee
	  cell d = points_to_sink(pt); // caller
	  reference sr = cell_any_reference(s);
	  reference dr = cell_any_reference(d);
	  list srs = reference_indices(sr);
	  list drs = reference_indices(dr);
	  if(ENDP(srs) && ENDP(drs)) {
	    entity se = reference_variable(sr);
	    entity de = reference_variable(dr);
	    //type se_t = entity_basic_concrete_type(se);
	    //type de_t = entity_basic_concrete_type(de);
	    if(entity_has_values_p(de))
	      tf = substitute_scalar_stub_in_transformer(tf, se, de, backward_p, &pl);
	    else
	      pl = CONS(ENTITY, se, pl);
	  }
	  else if(ENDP(srs) && !ENDP(drs)) {
	    entity se = reference_variable(sr);
	    if(analyzed_reference_p(dr)) {
	      entity de = constant_memory_access_path_to_location_entity(dr);
	      tf = substitute_scalar_stub_in_transformer(tf, se, de, backward_p, &pl);
	    }
	    else {
	      pl = CONS(ENTITY, se, pl);
	    }
	  }
	  else if(!ENDP(srs) && ENDP(drs)) {
	    entity se = constant_memory_access_path_to_location_entity(sr);
	    entity de = reference_variable(dr);
	    tf = substitute_scalar_stub_in_transformer(tf, se, de, backward_p, &pl);
	  }
	  else { // !ENDP(srs) & !ENDP(drs)
	    entity se = constant_memory_access_path_to_location_entity(sr);
	    entity de = constant_memory_access_path_to_location_entity(dr);
	    tf = substitute_scalar_stub_in_transformer(tf, se, de, backward_p, &pl);
	  }
	}
      }
      if(!ENDP(pl)) {
	// Get rid on untranslatable entities
	tf = safe_transformer_projection(tf, pl);
      }
    }
  }

  return tf;
}
