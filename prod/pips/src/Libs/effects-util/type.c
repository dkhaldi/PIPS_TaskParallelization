/*

  $Id: type.c 23143 2016-07-11 21:35:16Z irigoin $

  Copyright 1989-2016 MINES ParisTech
  Copyright 2009-2010 HPC Project


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

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "genC.h"
#include "linear.h"
#include "ri.h"
#include "effects.h"
#include "ri-util.h"
#include "prettyprint.h"
#include "effects-util.h"
#include "misc.h"
#include "text-util.h"

/***************************************/

/**
   @param exp is an effect index expression which is either the rank or an entity corresponding to a struct, union or enum field
   @param l_fields is the list of fields of the corresponding struct, union or enum
   @return the entity corresponding to the field.
 */
entity effect_field_dimension_entity(expression exp, list l_fields)
{
  if(expression_constant_p(exp))
    {
      int rank = expression_to_int(exp);
      return ENTITY(gen_nth(rank-1, l_fields));
    }
  else
    {
      return expression_to_entity(exp);
    }
}

/**
   @brief recursively walks thru current_l_ind and current_type in parallel until a pointer dimension is found.
   @param current_l_ind is a list of effect reference indices.
   @param current_type is the corresponding type in the original entity type arborescence
   @param exact_p is a pointer to a bool, which is set to true if the result is not an approximation.
   @return -1 if no index corresponds to a pointer dimension in current_l_ind, the rank of the least index that may correspond to
      a pointer dimension in current_l_ind otherwise. If this information is exact, *exact_p is set to true.
 */
static int effect_indices_first_pointer_dimension_rank(list current_l_ind, type current_type, bool *exact_p)
{
  int result = -1; /*assume there is no pointer */
  basic current_basic = variable_basic(type_variable(current_type));
  size_t current_nb_dim = gen_length(variable_dimensions(type_variable(current_type)));

  pips_debug(8, "input type : %s\n", type_to_string(current_type));
  pips_debug(8, "current_basic : %s, and number of dimensions %d\n", basic_to_string(current_basic), (int) current_nb_dim);

  pips_assert("there should be no store effect on variable names\n", gen_length(current_l_ind) >= current_nb_dim);


  switch (basic_tag(current_basic))
    {
    case is_basic_pointer:
      {
	// no need to test if gen_length(current_l_ind) >= current_nb_dim because of previous assert
	result = (int) current_nb_dim;
	*exact_p = true;
	break;
      }
    case is_basic_derived:
      {
	int i;
	current_type = entity_type(basic_derived(current_basic));

	if (type_enum_p(current_type))
	  result = -1;
	else
	  {
	    /*first skip array dimensions if any*/
	    for(i=0; i< (int) current_nb_dim; i++, POP(current_l_ind));

	    if (same_string_p(entity_user_name(basic_derived(current_basic)), "_IO_FILE") && gen_length(current_l_ind) == 0)
	      {
		pips_debug(8, "_IO_FILE_ array: no pointer dimension\n");
		result = -1;
	      }
	    else
	      {
		pips_assert("there must be at least one index left for the field\n", gen_length(current_l_ind) > 0);

		list l_fields = derived_type_fields(current_type);

		entity current_field_entity = effect_field_dimension_entity(EXPRESSION(CAR(current_l_ind)), l_fields);

		if (variable_phi_p(current_field_entity) || same_string_p(entity_local_name(current_field_entity), UNBOUNDED_DIMENSION_NAME))
		  {
		    while (!ENDP(l_fields))
		      {
			int tmp_result = -1;
			entity current_field_entity = ENTITY(CAR(l_fields));
			type current_type = entity_basic_concrete_type(current_field_entity);
			size_t current_nb_dim = gen_length(variable_dimensions(type_variable(current_type)));

			if (gen_length(CDR(current_l_ind)) >= current_nb_dim)
			  // consider this field only if it can be an effect on this field
			  tmp_result = effect_indices_first_pointer_dimension_rank(CDR(current_l_ind), current_type, exact_p);

			POP(l_fields);
			if (tmp_result >= 0)
			  result = result < 0 ? tmp_result : (tmp_result <= result ? tmp_result : result);
		      }

		    *exact_p = (result < 0);
		    if (result >= 0) result += i+1; // do not forget the field index and array dimensions!
		  }
		else
		  {
		    current_type = entity_basic_concrete_type(current_field_entity);
		    result = effect_indices_first_pointer_dimension_rank(CDR(current_l_ind), current_type, exact_p);
		    if (result >=0) result += i+1; // do not forget the field index and array dimensions!
		  }
	      }
	  }
	break;
      }
    default:
      {
	result = -1;
	*exact_p = true;
	break;
      }
    }

  pips_debug(8, "returning %d\n", result);
  return result;

}


/**
   @brief walks thru ref indices and ref entity type arborescence in parallel until a pointer dimension is found.
   @param ref is an effect reference
   @param exact_p is a pointer to a bool, which is set to true if the result is not an approximation.
   @return -1 if no index corresponds to a pointer dimension, the rank of the least index that may correspond to
      a pointer dimension in current_l_ind otherwise. If this information is exact, *exact_p is set to true.
 */
static int effect_reference_first_pointer_dimension_rank(reference ref, bool *exact_p)
{
  entity ent = reference_variable(ref);
  list current_l_ind = reference_indices(ref);
  type ent_type = entity_type(ent);
  int result;

  pips_debug(8, "input reference : %s\n", words_to_string(effect_words_reference(ref)));

  if (!type_variable_p(ent_type))
    {
      result = -1;
    }
  else
    {
      if (false)
      /* if (FILE_star_effect_reference_p(ref)) */
	{
	  result = 0;
	  *exact_p = true;
	}
      else
	{
	  type current_type = entity_basic_concrete_type(ent);
	  result = effect_indices_first_pointer_dimension_rank(current_l_ind, current_type, exact_p);
	}
    }

  pips_debug(8, "returning %d\n", result);
  return result;

}

/**
   @param ref is an effect reference
   @param exact_p is a pointer to a bool, which is set to true if the result is not an approximation.
   @return false if no index corresponds to a pointer dimension, false if any index may correspond to
      a pointer dimension. If this information is exact, *exact_p is set to true.
 */
bool effect_reference_contains_pointer_dimension_p(reference ref, bool *exact_p)
{
  int pointer_rank;
  pointer_rank = effect_reference_first_pointer_dimension_rank(ref, exact_p);
  return (pointer_rank >= 0);
}


/**
   @param ref is an effect reference
   @param exact_p is a pointer to a bool, which is set to true if the result is not an approximation.
   @return true if the effect reference may dereference a pointer, false otherwise.

 */
bool effect_reference_dereferencing_p(reference ref, bool * exact_p)
{
  list l_ind = reference_indices(ref);
  bool result;
  int p_rank;
  entity e = reference_variable(ref);

  //if (entity_all_locations_p(reference_variable(ref)))
  if (entity_abstract_location_p(e))
    {
      if(ENDP(l_ind)) {
	// result = true;
	result = false;
	*exact_p = false;
      }
      else {
	if(entity_all_locations_p(e)) {
	  /* FI: *ANY_MODULE*:*ANYWHERE* should not be indexed because
	   * any indexing can be eliminated as it results in
	   * *ANY_MODULE*:*ANYWHERE*
	   */
	  pips_internal_error("Unexpected indexing of an abstract location.\n");
	}
	else if(entity_typed_anywhere_locations_p(e)) {
	  /* FI: *ANY_MODULE*:*ANYWHERE*_b0, 1, 2 should not be
	   * indexed because any indexing can be eliminated and the
	   * reference replaced by a non-indexed reference to
	   * *ANY_MODULE*:*ANYWHERE*_bi , j, k depending on the type
	   * of the reference.
	   */
	  pips_internal_error("Unexpected indexing of an abstract location.\n");
	}
	else {
	  p_rank = effect_reference_first_pointer_dimension_rank(ref, exact_p);

	  if (p_rank == -1)
	    result = false;
	  else
	    result = p_rank < (int) gen_length(l_ind);
	}
      }
    }
  else
    {
      if (ENDP(l_ind)) /* no dereferencement if scalar reference, in particular, gets rid
			  of non store effect references */
	  p_rank = -1;
      else
	p_rank = effect_reference_first_pointer_dimension_rank(ref, exact_p);

      if (p_rank == -1)
	result = false;
      else
	result = p_rank < (int) gen_length(l_ind);
    }
  return result;
}

/*************************************************************************/
/* cell references */

static type r_cell_reference_to_type(list ref_l_ind, type current_type, bool *to_be_freed)
{
  type t = type_undefined;  /* the return type */

  switch (type_tag(current_type))
    {
    case is_type_variable:
      {
	basic current_basic = variable_basic(type_variable(current_type)); /* current basic */
	list l_current_dim = variable_dimensions(type_variable(current_type)); /* current type array dimensions */
	int current_nb_dim = gen_length(l_current_dim);
	int ref_l_ind_nb_dim = (int) gen_length(ref_l_ind);
	int common_nb_dim = MIN(current_nb_dim, ref_l_ind_nb_dim);

	pips_debug(8, "input type : %s\n", type_to_string(current_type));
	pips_debug(8, "current_basic : %s, and number of dimensions %d\n", basic_to_string(current_basic), current_nb_dim);
	pips_debug(8, "common number of dimensions: %d\n", common_nb_dim);
	/* the remainder of the function heavily relies on the following assumption */
	//pips_assert("there should be no memory access paths to variable names\n", (int) gen_length(ref_l_ind) >= current_nb_dim);

	if (ENDP(ref_l_ind)) /* We have reached the current type and there are no array dimensions to skip */
	  {
	    t = current_type;
	    *to_be_freed = false;
	  }
	else
	  {
	    /* skip common array dimensions if any */
	    for(int i=0; i< common_nb_dim; i++, POP(ref_l_ind), POP(l_current_dim));

	    if (ENDP(ref_l_ind)) /* We have reached the current basic */
	      {
		/* Warning : qualifiers are set to NIL, because I do not see
		   the need for something else for the moment. BC.
		*/
		/* Sub arrays are pointers to arrays, not arrays, at least for gcc
		 *
		 * a[10][20][30] -> a is int (*)[20][30]
		 *               -> a[1] is int *[30]
		 *               -> a[1][2] is int *
		 */
		if(ENDP(l_current_dim)) {
		    /* Beatrice's version */
		    t = make_type(is_type_variable,
				  make_variable(copy_basic(current_basic),
						gen_full_copy_list(l_current_dim),
						NIL));
		}
		else {
		  list n_dims = CDR(l_current_dim);
		  t = make_type(is_type_variable,
				make_variable(copy_basic(current_basic),
					      gen_full_copy_list(n_dims),
					      NIL));
		  t = type_to_pointer_type(t);
		}
		*to_be_freed = true;
	      }
	    else
	      {
		/* The cell reference contains indices that go beyond the current type array dimensions.
		   This can happen if and only if the current basic is a pointer or a derived
		   (typedef have been eliminated by the use of basic_concrete_type).
		*/
		switch (basic_tag(current_basic))
		  {
		  case is_basic_pointer:
		    {
		      /* if the input type is a bct, then I think there is no need to compute the bct of a basic_pointer. BC.*/
		      /*type new_current_type = compute_basic_concrete_type(basic_pointer(current_basic));*/
		      type new_current_type = basic_pointer(current_basic);
		      POP(ref_l_ind); /* pop the pointer dimension */
		      t = r_cell_reference_to_type(ref_l_ind, new_current_type, to_be_freed);
		      /* free_type(new_current_type);*/
		      break;
		    }
		  case is_basic_derived:
		    {
		      /* the next reference index should be a field entity */
		      expression next_index = EXPRESSION(CAR(ref_l_ind));
		      syntax s = expression_syntax(next_index);
		      if (syntax_reference_p(s))
			{
			  entity next_index_e = reference_variable(syntax_reference(s));
			  if (entity_field_p(next_index_e))
			    {
			      type new_current_type = entity_basic_concrete_type(next_index_e);
			      POP(ref_l_ind); /* pop the field dimension */
			      t = r_cell_reference_to_type(ref_l_ind, new_current_type, to_be_freed);
			    }
			  else
			    pips_internal_error("the current basic tag is derived, but corresponding index is not a field entity");
			}
		      else
			pips_internal_error("the current basic tag is derived, but corresponding index is not a reference");
		      break;
		    }
		  case is_basic_overloaded:
		    {
		      t = current_type;
		      *to_be_freed = false;
		      break;
		    }
		  default:
		    {
		      pips_internal_error("unexpected basic tag");
		    }
		  }
	      }
	  }

	ifdebug(8)
	  {
	    if (type_variable_p(t))
	      {
		variable v = type_variable(t);
		pips_debug(8, "output type is: %s\n",  type_to_string(t));
		pips_debug(8, "with basic : %s, and number of dimensions %d\n",
			   basic_to_string(variable_basic(v)),
			   (int) gen_length(variable_dimensions(v)));
		pips_debug(8, "*to_be_freed = %s\n", *to_be_freed? "true": "false");
	      }
	  }
	break;
      }
    case is_type_void:
      {
	t = copy_type(current_type);
	*to_be_freed = true;

	ifdebug(8)
	  {
	    pips_debug(8, "output type is: void\n");
	    pips_debug(8, "*to_be_freed = true\n");
	  }
	break;
      }
    default:
      pips_internal_error("non void and non variable case: not handled yet here, please report\n");
    }
  return t;
}

/**
 @brief computes the type of a cell reference representing a memory access path.
        Cell references are not compatible with entity typing: spurious dimensions
        are added to handle struct fields and the dereferencing operator.
	BEWARE : does not work if field entity indices have been converted to ranks.
 @param ref is a reference from a cell.
 @return a *newly allocated* type corresponding to the type of the memory cells targeted by the access path.
 */
type cell_reference_to_type(reference ref, bool *to_be_freed)
{
  debug_on("EFFECTS-UTIL_DEBUG_LEVEL");
  type t = type_undefined;
  type ref_type = entity_basic_concrete_type(reference_variable(ref));
  *to_be_freed= false;

  pips_debug(6, "input reference: %s \n",  reference_to_string(ref));

  if (ENDP(reference_indices(ref))) /* in particular, gets rid of non-store effect references */
    {
      t = ref_type;
    }
  else
    {
      if(type_variable_p(ref_type))
	{
	  t = r_cell_reference_to_type(reference_indices(ref), ref_type, to_be_freed);
	}
      else if(type_functional_p(ref_type))
	{
	  /* A reference to a function returns a pointer to a function
	     of the very same time */
	  t = make_type(is_type_variable,
			make_variable
			(make_basic(is_basic_pointer, copy_type(ref_type)),
			 NIL, NIL));
	  *to_be_freed = true;
	}
      else if(type_unknown_p(ref_type)) {
	/* FI: for some abstract locations that have type unknown
	   instead of type variable, with basic overloaded */
	t = ref_type;
	*to_be_freed = false;
      }
      else
	{
	  pips_internal_error("Bad reference type tag %d \"%s\" for reference %s",
			      type_tag(ref_type),
			      type_to_string(ref_type),
			      entity_name(reference_variable(ref)));
	}
    }
  debug_off();
  return t;
}

type cell_to_type(cell c, bool *to_be_freed)
{
  pips_assert("a cell cannot be a gap yet\n", !cell_gap_p(c));
  reference ref = cell_reference_p(c)? cell_reference(c) : preference_reference(cell_preference(c));

  return cell_reference_to_type(ref, to_be_freed);
}

/* FI: I need more generality than is offered by cell_to_type()
 *
 * Maybe because of fields.
 *
 * Surely because of implicit arrays linked to scalar pointers
 */
type points_to_reference_to_type(reference ref, bool *to_be_freed)
{
  type t = type_undefined;

  entity v = reference_variable(ref);
  list sl = reference_indices(ref);

  if(ENDP(sl)) {
    t = entity_type(v);
    *to_be_freed = false;
  }
  else {
    int ns = (int) gen_length(sl);
    expression fs = EXPRESSION(CAR(sl));
    bool int_p = expression_integer_constant_p(fs);
    // FI: faire un cas particulier pour des cas comme i[1] ou i est un scalaire?
    // FI: I do not know what can happen with struct objects; they are
    // scalar, a dimension may be added and nevertheless a field may be
    // accessed....
    if(entity_scalar_p(v) && ns==1 && int_p) {
      *to_be_freed = false;
      t = entity_type(v);
    }
    else {
      expression ls = EXPRESSION(CAR(gen_last(sl)));
      syntax lss = expression_syntax(ls);
      if(syntax_reference_p(lss)) {
	reference r = syntax_reference(lss);
	entity f = reference_variable(r);
	if(entity_field_p(f)) {
	  t = entity_type(f);
	  *to_be_freed = false;
	}
      }
    }
  }
    
  if(type_undefined_p(t))
    t = cell_reference_to_type(ref, to_be_freed);

  return t;
}

static void substitute_unbounded_call(call c)
{
  entity f = call_function(c);
  const char* fn = entity_local_name(f);
  if (same_string_p(fn, UNBOUNDED_DIMENSION_NAME)) {
    entity z = int_to_entity(0);
    call_function(c) = z;
  }
}

/* Allocate a copy of expression "e" where calls to the unbounded
 * function are replaced by calls to the zero function so that typing
 * can be performed.
 */
static expression eliminate_calls_to_unbounded(expression e)
{
  gen_recurse(e, call_domain, gen_true, substitute_unbounded_call);
  return e;
}

/* FI: I need more generality than is offered by expression_to_type()
   because fields are assimilated to subscripts. */
type points_to_expression_to_type(expression e, bool * to_be_freed)
{
  type t = type_undefined;
  syntax s = expression_syntax(e);
  if(syntax_reference_p(s)) {
    reference r = syntax_reference(s);
    t = points_to_reference_to_type(r, to_be_freed);
  }
  else {
    /* In order to type t[*] as well as t[0]... */
    expression ne = copy_expression(e);
    eliminate_calls_to_unbounded(ne);
    *to_be_freed = true;
    t = expression_to_type(ne);
    free_expression(ne);
  }

  return t;
}

/* The type returned is stored in a hash-table. It should not be
 * freed. See compute_basic_concrete_type().
 *
 * This function is useful to avoid the conditional free.
 */
type points_to_expression_to_concrete_type(expression e)
{
  bool to_be_freed;
  type t = points_to_expression_to_type(e, &to_be_freed);
  type ct = compute_basic_concrete_type(t);
  if(to_be_freed) free_type(t);
  return ct;
}

/* Return a new allocated type "t" of the address pointed by expression "e", if
 * expression "e" denotes an address.
 *
 * "t" should not be freed. 
 */
type points_to_expression_to_pointed_type(expression e)
{
  type t = type_undefined;
  bool to_be_freed;
  type et = points_to_expression_to_type(e, &to_be_freed);
  type cet = compute_basic_concrete_type(et);
  if(to_be_freed) free_type(et);

  if(pointer_type_p(cet)) {
    type pt = type_to_pointed_type(cet);
    t = copy_type(compute_basic_concrete_type(pt));
  }
  else if(array_type_p(cet)) {
    /* We should return a pointer towards an array of dimension
       n-1. The first dimension is lost. */
    variable cet_v = type_variable(cet);
    list cet_v_dl = variable_dimensions(cet_v);
    /* Build the pointed type, copy of cet except for its first dimension */
    list ndl = gen_full_copy_list(CDR(cet_v_dl));
    basic nat_b = copy_basic(variable_basic(cet_v));
    variable nat_v = make_variable(nat_b, ndl, NIL);
    type nat = make_type_variable(nat_v);
    /* Build the poiinter type*/
    // variable v = type_variable(nat);
    basic b = make_basic_pointer(nat);
    variable v = make_variable(b, NIL, NIL);
    t = make_type_variable(v);
  }
  else
    pips_internal_error("Arg. is not in definition domain.\n");
  return t;
}

/* FI: I need more generality than is offered by cell_to_type() */
type points_to_cell_to_type(cell c, bool *to_be_freed)
{
  type t = type_undefined;
  pips_assert("a cell cannot be a gap yet", !cell_gap_p(c));
  reference ref = cell_any_reference(c);

  t = points_to_reference_to_type(ref, to_be_freed);

  return t;
}

type points_to_cell_to_concrete_type(cell c)
{
  bool to_be_freed;
  type t = points_to_cell_to_type(c, &to_be_freed);
  type ct = compute_basic_concrete_type(t);
  if(to_be_freed) free_type(t);
  return ct;
}

type points_to_reference_to_concrete_type(reference r)
{
  bool to_be_freed;
  type t = points_to_reference_to_type(r, &to_be_freed);
  type ct = compute_basic_concrete_type(t);
  if(to_be_freed) free_type(t);
  return ct;
}

/**
    tests if the actual argument type and the formal argument type are compatible
    with the current state of the interprocedural translation algorithms. Input types
    are @see basic_concrete_type .
 */
bool basic_concrete_types_compatible_for_effects_interprocedural_translation_p(type real_ct, type formal_ct)
{
  static list real_structured_types = NIL;
  static list formal_structured_types = NIL;

  pips_debug(8,"real_ct : %s \t formal_ct: %s\n",
	     string_of_type(real_ct),
	     string_of_type(formal_ct));

  bool result = false; /* safe default result */
  /* easiest case */
  if (real_ct == formal_ct)
    {
      pips_debug(8, "types are equal\n");
      result = true;
    }

  else if (type_tag(real_ct) != type_tag(formal_ct))
    {
      pips_debug(8, "not same type tags\n");
      result = false;
    }

  else
    {
      switch(type_tag(real_ct))
	{
	case is_type_void:
	  result = true;
	  break;
	case is_type_variable:
	  {
	    pips_debug(8, "variable case\n");
	    basic real_b = variable_basic(type_variable(real_ct));
	    list real_dims = variable_dimensions(type_variable(real_ct));
	    basic formal_b = variable_basic(type_variable(formal_ct));
	    list formal_dims = variable_dimensions(type_variable(formal_ct));

	    bool finished = false;
	    /* we do not take care of array dimension sizes */
	    while (! finished)
	      {
		if (gen_length(real_dims) == gen_length(formal_dims))
		  {
		    /* well, basic_equal_strict_p is at the same time too restrictive
		       for derived and too optimistic for pointers and arrays because
		       dimensions are skipped
		    */
		    if (basic_pointer_p(real_b) && basic_pointer_p(formal_b))
		      {
			pips_debug(8, "pointer case\n");
			result =
			  basic_concrete_types_compatible_for_effects_interprocedural_translation_p
			  (basic_pointer(real_b), basic_pointer(formal_b));
		      }
		    else if (basic_derived_p(real_b) && basic_derived_p(formal_b))
		      {
			entity real_basic_e = basic_derived(real_b);
			entity formal_basic_e = basic_derived(formal_b);
			pips_debug(8, "derived case, real: %s, formal: %s\n",
				   entity_name(real_basic_e),
				   entity_name(formal_basic_e));
			if (same_entity_p(real_basic_e, formal_basic_e))
			  {
			    pips_debug(8, "same entities (1) \n");
			    result = true;
			  }
			else
			  {
			    type formal_dt = entity_type(formal_basic_e);
			    type real_dt =  entity_type(real_basic_e);

			    void * found_formal_t = (type) gen_find_eq(formal_dt,formal_structured_types);
			    void * found_real_t = (type) gen_find_eq(real_dt,real_structured_types);

			    if (!gen_chunk_undefined_p(found_formal_t))
			      {
				pips_debug(8, "types already encountered (1) \n");
			  	result = gen_position(found_formal_t, formal_structured_types)
				  == gen_position(found_real_t, real_structured_types);
			      }
			    else
			      {
				pips_debug(8, "types not encountered (1) \n");
			  	formal_structured_types = gen_type_cons(formal_dt, formal_structured_types);
				real_structured_types = gen_type_cons(real_dt, real_structured_types);
				result = basic_concrete_types_compatible_for_effects_interprocedural_translation_p(real_dt, formal_dt);
				list old_formal_structured_types = formal_structured_types;
				list old_real_structured_types = real_structured_types;
				POP(formal_structured_types);
				POP(real_structured_types);
				CDR(old_formal_structured_types) = NIL;
				CDR(old_real_structured_types) = NIL;
				gen_free_list(old_formal_structured_types);
				gen_free_list(old_real_structured_types);
			      }
			  }
		      }
		    else
		      result = basic_equal_p(real_b, formal_b);
		    finished = true;
		  }
		else
		  {
		    /* skip same number of array and pointer dimensions until we reach the
		       ultimate basic or there are no more corresponding dimensions
		    */
		    if (basic_pointer_p(real_b) && gen_length(real_dims) == 0)
		      {
			real_ct = basic_pointer(real_b);
			if (type_void_p(real_ct))
			  {
			    /* we have a void * as actual argument */
			    /* translation cannot be accurate */
			    finished = true;
			  }
			else if (type_variable_p(real_ct))
			  {
			    real_b = variable_basic(type_variable(real_ct));
			    real_dims = variable_dimensions(type_variable(real_ct));
			    formal_dims = CDR(formal_dims); /* we are sure here that gen_length(formal_dims) != 0*/
			  }
			else
			  finished = true;
		      }
		    else if (basic_pointer_p(formal_b) && gen_length(formal_dims) == 0)
		      {
			formal_ct = basic_pointer(formal_b);
			if (type_void_p(formal_ct))
			  {
			    /* we have a void * as actual argument */
			    /* translation cannot be accurate */
			    finished = true;
			  }
			else if (type_variable_p(formal_ct))
			  {
			    formal_b = variable_basic(type_variable(formal_ct));
			    formal_dims = variable_dimensions(type_variable(formal_ct));
			    real_dims = CDR(real_dims); /* we are sure here that gen_length(real_dims) != 0*/
			  }
			else
			  finished = true;
		      }
		    else
		      finished = true;
		  }
	      }
	  }
	  break;
	case is_type_struct:
	case is_type_union:
	case is_type_enum:
	  pips_debug(8, "struct, union or enum case\n");
	  list real_fields = type_fields(real_ct);
	  list formal_fields = type_fields(formal_ct);
	  if (gen_length(real_fields) == gen_length(formal_fields))
	    {
	      result = true;
	      while(result && !ENDP(real_fields))
		{
		  entity real_fe = ENTITY(CAR(real_fields));
		  entity formal_fe = ENTITY(CAR(formal_fields));
		  pips_debug(8, "fields, real: %s, formal: %s\n",
			     entity_name(real_fe),
			     entity_name(formal_fe));

		  if (same_entity_p(real_fe, formal_fe))
		    {
		      pips_debug(8, "same entities (2)\n");
		      result = true;
		    }
		  else
		    {
		      type real_ft = entity_type(real_fe);
		      type formal_ft = entity_type(formal_fe);

		      void * found_formal_ft = (type) gen_find_eq(formal_ft,formal_structured_types);
		      void * found_real_ft = (type) gen_find_eq(real_ft,real_structured_types);

		      if (!gen_chunk_undefined_p(found_formal_ft))
			{
			  pips_debug(8, "types already encountered (2)\n");
			  result = gen_position(found_formal_ft, formal_structured_types)
			    == gen_position(found_real_ft, real_structured_types);
			}
		      else
			{
			  pips_debug(8, "types not encountered (2)\n");
			  /* store types and not bct becasue bct cannot be equal,
			     since a new type is generated each time.
			     We really need a global table for bcts */
			  formal_structured_types = gen_type_cons(formal_ft, formal_structured_types);
			  real_structured_types = gen_type_cons(real_ft, real_structured_types);
			  type real_fbct = entity_basic_concrete_type(real_fe);
			  type formal_fbct = entity_basic_concrete_type(formal_fe);
			  /* It should be a strict type equality here, but I don't think type_equal_p
			     is very robust when types are declared in headers
			  */
			  result =
			    basic_concrete_types_compatible_for_effects_interprocedural_translation_p
			    (real_fbct, formal_fbct);

			  list old_formal_structured_types = formal_structured_types;
			  list old_real_structured_types = real_structured_types;
			  POP(formal_structured_types);
			  POP(real_structured_types);
			  CDR(old_formal_structured_types) = NIL;
			  CDR(old_real_structured_types) = NIL;
			  gen_free_list(old_formal_structured_types);
			  gen_free_list(old_real_structured_types);
			}
		    }
		  POP(real_fields);
		  POP(formal_fields);
		}
	    }
	  break;
	case is_type_functional:
	  pips_debug(8, "functional case\n");
	  result = true;
	  break;
	default:
	  pips_internal_error("unexpected function argument type: %s\n", type_to_string(real_ct) );
	}
    }
  pips_debug(8, "returning %s\n", result? "true":"false");
  return result;
}

/**
    tests if the actual argument type and the formal argument type are compatible
    with the current state of the interprocedural translation algorithms.
 */
bool types_compatible_for_effects_interprocedural_translation_p(type real_arg_t, type formal_arg_t)
{
  bool result = false; /* safe default result */

  if (real_arg_t == formal_arg_t)
    result = true;
  else
    {
      type real_arg_ct = compute_basic_concrete_type(real_arg_t);
      type formal_arg_ct = compute_basic_concrete_type(formal_arg_t);

      result =
	basic_concrete_types_compatible_for_effects_interprocedural_translation_p
	(real_arg_ct, formal_arg_ct);

      free_type(real_arg_ct);
      free_type(formal_arg_ct);
    }

  return result;
}

/* Make sure that cell l can points towards cell r 
 *
 * FI-AM/FC: Unfortunately, a lot of specification work is missing to develop
 * this function while taking care of abstract locations and their lattice. 
 *
 * 1. Restrictions on cell "l"
 *
 *  1.1 "l" cannot be the abstract nowhere/undefined cell
 *
 * ...
 *
 * Note: this should be part of points_to_set_consistent_p(), which is
 * called consistent_points_to_set(), but this function goes beyond
 * checking the compatibility. It enforces it when legal and possible.
 *
 * Maybe this function should be relocated in alias-classes
 *
 * Beware of possible side-effects on l
 *
 * FI, 10 August 2012: this function is a mess. No side effect should
 * be applied. it should be redesigned to check compatibility cases
 * one after the other and it should be renamed
 * points_to_cell_types_compatibility_p()
 *
 * FI, 14 August 2012: the dimension of the sink entity and sink
 * reference must be greater than the dimension of the source
 * reference. This is not checked yet.
 *
 * FI, 19 August 2012: all cells used in a points-to arc must be
 * scalar, either pointers or basic types
 */
void points_to_cell_types_compatibility(cell l, cell r)
{
  if(points_to_source_cell_compatible_p(l)) {
    if(null_cell_p(r))
      ;
    else if(points_to_sink_cell_compatible_p(r)) {
      // FI: I'm not sure enought filtering has been performed... to
      // have here type information, especially with an anywhere or a
      // nowhere/undefined not typed

      // FI : tests supplementaires pour eviter les cells qui ne sont pas typees:-(

      bool l_to_be_freed, r_to_be_freed;
      type lt = points_to_cell_to_type(l, &l_to_be_freed);
      type rt = points_to_cell_to_type(r, &r_to_be_freed);
      type ult = compute_basic_concrete_type(lt);
      type urt = compute_basic_concrete_type(rt);
      if(C_pointer_type_p(ult)) {
	type pt = pointer_type_p(ult) ?
	  copy_type(compute_basic_concrete_type(type_to_pointed_type(ult))) :
	  array_type_to_element_type(ult);

	// Several options are possible

	bool get_bool_property(const char *);
	if(array_pointer_type_equal_p(pt, urt)) 
	  ; // the pointed type is the type of the right cell
	// FI: we could/should add a compatibility type between void
	// and any scalar type
	// The problem occurs in Pointers/fulguro13 because a cast is
	// not processed:
	// fgUINT16 *array_s = (fgUINT16 *) vct->array;
	// FI->AM/FC/PJ: we need a trick to handle the casts or the
	// typing of the points-to graph is not possible
	else if(scalar_type_p(pt) && type_void_p(urt)) {
	  // A void * pointer may be assigned to anything?
	  ; // OK, they are compatible...
	}
	else if(type_void_p(pt) /* && overloaded_type_p(urt)*/ ) {
	  // a void * is expected to point toward any type, which is
	  // encoded with overloaded but could be anything when casts
	  // or functions, user or intrinsic, are used. See fulguro03.c
	  ;
	}
	else if(overloaded_type_p(urt)) {
	  // This is compatible with any pointed type pt by definition
	  // of overloaded. See fulguro03.c
	  ;
	}
	else if(array_type_p(pt) && scalar_type_p(urt)) {
	  /* The source points towards an array and the cell is an
	     element of this array. */
	  basic pb = variable_basic(type_variable(pt));
	  basic rb = variable_basic(type_variable(urt));
	  if(basic_equal_p(pb, rb)) {
	    ; // OK
	  }
	  else {
	    pips_internal_error("???");
	  }
	}
	else if(array_type_p(urt)
		&& !get_bool_property("POINTS_TO_STRICT_POINTER_TYPES")) {
	  /* Formal parameters and potentially stubs can be assumed to
	   * points towards an array although they are declared as
	   * pointers to a scalar.
	   *
	   * This should never be a problem when sink cells are always
	   * array elements and not arrays.
	   */
	  if(type_variable_p(pt)) {
	    basic pb = variable_basic(type_variable(pt));
	    basic rb = variable_basic(type_variable(urt));
	    if(basic_equal_p(pb,rb)) {
	      ; // OK, they are compatible
	    }
	    else {
	      fprintf(stderr, "Type pointed by source \"pt\": \"");
	      print_type(pt);
	      fprintf(stderr, "\"\nSink type \"urt\": \"");
	      print_type(urt);
	      pips_internal_error("\"\nIncompatible basics.\n");
	    }
	  }
	  else {
	      fprintf(stderr, "Pointed type \"pt\": ");
	      print_type(pt);
	    pips_internal_error("Unexpected type \"pt\".\n");
	  }
	}
	else if(array_type_p(urt)
		&& get_bool_property("POINTS_TO_STRICT_POINTER_TYPES")) {
	  // Pointers/assignment10.c
	  if(type_variable_p(pt)) {
	    basic pb = variable_basic(type_variable(pt));
	    basic rb = variable_basic(type_variable(urt));
	    if(basic_equal_p(pb,rb)) {
	      // OK, they are compatible, but r must be subscripted
	      points_to_cell_add_zero_subscripts(r);
	    }
	    else {
	      fprintf(stderr, "Type pointed by source \"pt\": \"");
	      print_type(pt);
	      fprintf(stderr, "\"\nSink type \"urt\": \"");
	      print_type(urt);
	      pips_internal_error("\"\nIncompatible basics.\n");
	    }
	  }
	}
	else if(type_functional_p(urt)) {
	  // FI->AM: we should check that the function is a constant
	  // with no parameters
	  type ret_t = functional_result(type_functional(urt));
	  type u_ret_t = compute_basic_concrete_type(ret_t);
	  if(pointer_type_p(u_ret_t)) {
	    pips_internal_error("This should be useless.\n");
	    // FI->AM: must be useless... Designed for C constant strings, but...
	    type p_u_ret_t = type_to_pointed_type(u_ret_t);
	    if(array_pointer_type_equal_p(pt, p_u_ret_t))
	      ;
	    else
	      pips_internal_error("Type mismatch.\n");
	    free_type(u_ret_t);
	  }
	  else if(string_type_p(u_ret_t)) {
	    // FI: hidden pointer...
	    // char * fmt; ftm = "foo";
	    variable ptv = type_variable(pt);
	    basic ptb = variable_basic(ptv);
	    if(basic_int_p(ptb) && basic_int(ptb)==1)
	      ; // char
	    else
	      pips_internal_error("Illegal string assignment...\n");
	  }
	  else {
	    pips_internal_error("Illegal assignment to pointer...\n");
	  }
	}
	else {
	  /* Here we may be in trouble because of the heap modeling
	   * malloc() returns by default a "void *", or sometimes a
	   * "char *" which may be casted into anything...
	   *
	   * The dimension of the allocated array should be given by
	   * the size of the pointed type and by the size of the right
	   * type.
	   *
	   * Also, we have different heap modelling, with different flexibilities
	   */
	  if(heap_cell_p(r) && !all_heap_locations_cell_p(r) 
	     /*&& !all_heap_locations_typed_cell_p(r) */) {
	    pips_internal_error("Type mistake for heap allocation. Probably a user error. It should have been trapped at a higher level.\n");
	    type nt = copy_type(pt);
	    if(array_type_p(nt)
	       || get_bool_property("POINTS_TO_STRICT_POINTER_TYPES"))
	      ; // Do not add a dimension to an existing array.
	    else if(!type_void_p(nt)) {
	      variable v = type_variable(nt);
	      expression z = int_to_expression(0);
	      // FI FI FI: should be computed... and checked
	      expression s = make_unbounded_expression();
	      dimension d = make_dimension(z, s, NIL);
	      variable_dimensions(v) = CONS(DIMENSION, d, NIL);
	    }
	    // FI: could be a function entity_type_substitution()...
	    // but interference with r_to_be_freed
	    r_to_be_freed = true;
	    reference rr = cell_any_reference(r);
	    entity rv = reference_variable(rr);
	    // This assignment breaks the internal consistency of heap modelling
	    if(!array_pointer_type_equal_p(nt, entity_type(rv)))
	      pips_internal_error("Incompatible types for \"%s\".\n",
				  entity_name(rv));
	    entity_type(rv) = nt;
	  }
	  else if(all_heap_locations_cell_p(r))
	    ; // always compatible
	  else if(false /* all_heap_locations_typed_cell_p(r)*/)
	    ; // FI: I am not sure what to do...
	  else if(null_cell_p(r)) {
	    ; // always compatible
	  }
	  else if(anywhere_cell_p(r)) {
	    ; // not typed anywhere, always compatible
	  }
	  else if(nowhere_cell_p(r)) {
	    ; // not typed nowhere/undefined, always compatible
	  }
	  else {
	    /* There must be a typing issue. */
	      fprintf(stderr, "Type pointed by source cell, \"pt\": \"");
	      void print_points_to_cell(cell); // FI: library organization
	      print_points_to_cell(l);
	      fprintf(stderr, "\" with type: \"");
	      print_type(pt);
	      fprintf(stderr, "\"\nType of sink cell, \"urt\": \"");
	      print_points_to_cell(r);
	      fprintf(stderr, "\" with type: \"");
	      print_type(urt);
	      fprintf(stderr, "\"\n");
	      pips_internal_error("Incompatible Types.\n");
	  }
	}
      }
      else if(array_type_p(ult)) {
	/* This may happen with the heap model */
	extern bool get_bool_property(const char *);
	if(!get_bool_property("POINTS_TO_STRICT_POINTER_TYPES")) {
	  /* Is it an (implicit) array of pointers*/
	  basic ultb = variable_basic(type_variable(ult));
	  if(basic_pointer_p(ultb)) { // Array 
	    // FI: "pt" should be freed later...
	    // FI: should have been done earlier when building l
	    // reference lr = cell_any_reference(l);
	    // reference_add_zero_subscripts(lr, ult);
	    type pt = compute_basic_concrete_type(basic_pointer(ultb));
	    if(generic_type_equal_p(pt, urt, false, false)) {
	      // FI: subscripts must be added to the source reference lr
	      // FI: implicit typing of pointers as array of pointers
	      reference lr = cell_any_reference(l);
	      reference_add_zero_subscripts(lr, ult);
	    }
	    else {
	      // FI: error message could be improved...
	      pips_internal_error("Incompatible types.\n");
	    }
	  }
	  else
	    pips_internal_error("Not an array of pointers.\n");
	}
	else
	  pips_internal_error("The source is an array but not a pointer.\n");
      }
      else if(overloaded_type_p(ult)) {
	/* This may happen with the heap model */
	; // A pointer type is assumed
      }
      else {
	// Could be checked by points_to_source_cell_compatible_p()
	pips_internal_error("The source is not a pointer.\n");
      }

      if(l_to_be_freed) free_type(lt);
      if(r_to_be_freed) free_type(rt);
      free_type(ult), free_type(urt);
    }
  }
  return;
}

/*
 * Restrictions on a source cell "c"
 *
 * 1. "l" cannot be the abstract nowhere/undefined cell
 * 2. "l" cannot be the/a null pointer
 */
bool points_to_source_cell_compatible_p(cell c)
{
  bool compatible_p = true;

  if(nowhere_cell_p(c))
    compatible_p = false;
  else if(null_cell_p(c))
    compatible_p = false;

  return compatible_p;
}

/*
 * Restrictions on a sink cell "c"
 *
 * FI: I cannot think of any right now...
 */
bool points_to_sink_cell_compatible_p(cell c __attribute__ ((unused)))
{
  bool compatible_p = true;

  return compatible_p;
}

/* Find the subscript in the reference of cell "c" that would make the
 * reference type be "t" if the subscript list were truncated just
 * after it. Select the longest possible subscript list.
 *
 * Core dump if it is not possible.
 *
 * No smart implementation: trial and error (probably already
 * implemented somewhere else.
 */
list find_points_to_subscript_for_type(cell c, type t)
{
  list csl = list_undefined;
  reference r = cell_any_reference(c);
  entity v = reference_variable(r);
  type rt = points_to_reference_to_concrete_type(r); // reference type
  list sl = reference_indices(r); // subscript list
  list rsl = gen_nreverse(sl); // temporary side-effect on "r" (and "c")
  list crsl = rsl; // current reverse subscript list

  while(!array_pointer_type_equal_p(t, rt) && !ENDP(crsl)) {
    POP(crsl);
    list nsl = gen_copy_seq(crsl);
    reference nr = make_reference(v, nsl);
    rt = points_to_reference_to_concrete_type(nr);
    reference_indices(nr) = NIL;
    free_reference(nr);
  }

  reference_indices(r)= gen_nreverse(rsl);

  if(!ENDP(crsl)) {
    csl = crsl;
  }
  else {
    if(array_pointer_type_equal_p(t, rt)) {
      // dereferencing18.c: only one element is allocated. 0 is the
      // only possible subscript;
      csl = NIL; // ==crsl
    }
    else {
      /* Let's try to add a zero subscript instead... */
      expression z = make_zero_expression();
      list nsl = CONS(EXPRESSION, z, NIL);
      /* For the time being, no need to restore the reference in case of
	 failure. */
      reference_indices(r) = gen_nconc(reference_indices(r), nsl);
      rt = points_to_reference_to_concrete_type(r);
      if(array_pointer_type_equal_p(t, rt))
	csl = nsl;
      else
	pips_internal_error("Type t and reference r are incompatible.\n");
    }
  }

  return csl;
}

/* FI: a really stupid function... Why do we add zero subscript right
 *  away when building the sink cell to remove them later? Let's now
 * remove the excessive subscripts of "r" with respect to type
 * "at"...
 */
bool adapt_reference_to_type(reference r, type et,
			     int (*line_number_func)(void))
{
  bool succeed_p = true;
  bool to_be_freed;
  type at = compute_basic_concrete_type(et);
  type rt = points_to_reference_to_type(r, &to_be_freed);
  type t = compute_basic_concrete_type(rt);
  while(!array_pointer_type_equal_p(at, t) && !ENDP(reference_indices(r))) {
    if(to_be_freed) free_type(t);
    list sl = reference_indices(r);
    list last = gen_last(sl);
    expression e = EXPRESSION(CAR(last));
    if(expression_field_p(e))
      break;
    int l1 = (int) gen_length(sl);
    gen_remove_once(&sl, (void *) e);
    int l2 = (int) gen_length(sl);
    if(l1==l2)
      pips_internal_error("gen_remove() is ineffective.\n");
    reference_indices(r) = sl;
    type nrt = points_to_reference_to_type(r, &to_be_freed);
    t = compute_basic_concrete_type(nrt);
  }
  if(!array_pointer_string_type_equal_p(at, t)) {
    // FI: this function used to be in library alias_classes
    // It should be passed as a functional argument.
    //int points_to_context_statement_line_number(void);
    pips_user_warning("There may be a typing error at line %d (e.g. improper malloc call).\n",
		      // points_to_context_statement_line_number());
		      (*line_number_func)());
    //pips_internal_error("Cell type mismatch.");
    succeed_p = false;
  }
  if(to_be_freed) free_type(t);
  return succeed_p;
}

/* This function should be at expression.c. It already exist
   and is called reference_with_unbounded_indices_p() but 
   includes two cases that should be disjoint: constant indices 
   and unbounded ones.
*/
bool reference_unbounded_indices_p(reference r)
{
  list sel = reference_indices(r);
  bool unbounded_p = true;

  MAP(EXPRESSION, se, {
      if(!unbounded_expression_p(se)) {
	unbounded_p = false;
	break;
      }
    }, sel);
  return unbounded_p;
}

/*
 * want to test if r can only be a constant path and nothing else
 * WARNING : not totally tested
 * for instance
 *        a[0], a[1], a[i], i, j, ... have to return false
 *        a[*], var points by formal parameter (_p_0, ...), element of strut (s.id, ...), heap element have to return true
 *  * !effect_reference_dereferencing_p(r, &exact_p)
 *      can return true when it's not a constant path like a[i] (a[i] and not a[*])
 *      can make a side effect for the declaration of variable in parameter (only?), don't know why
 *      for instance with Semantics-New/Pointer.sub/memcopy01
 *        void memcopy01([...], char dst[size])  -->  void memcopy01([...], char dst[i])
 *  * store_independent_reference_p(r)
 *      can return false for some cp like a[0], can't permit to treat the array
 *          return false for the structure too, can't permit to treat the struct
 *      can return true for i, j, ... that can be a constant path but not strictly a constant path
 * param r          reference to analyze to see if it's a constant path
 * return           true if r is exactly a constant path
 *
 * This function is not used by the points-to analysis, but by semantics
 */
bool strict_constant_path_p(reference r)
{
  bool constant_path = false;
  entity v = reference_variable(r);
  list l_ind = reference_indices(r);

  // Test the different top and bottom area
  if (entity_all_locations_p(v)
      || entity_anywhere_locations_p(v) || entity_typed_anywhere_locations_p(v)
      || entity_nowhere_locations_p(v) || entity_typed_nowhere_locations_p(v)
      || entity_all_module_locations_p(v)
      ) {
    constant_path = true;
  }
  else if (entity_all_module_heap_locations_p(v)
      || entity_all_heap_locations_p(v)
      ) {
    constant_path = true;
  }
  else if (entity_all_module_stack_locations_p(v)
      || entity_all_stack_locations_p(v)
      ) {
    constant_path = true;
  }
  else if (entity_all_module_static_locations_p(v)
      || entity_all_static_locations_p(v)
      ) {
    constant_path = true;
  }
  else if (entity_all_module_dynamic_locations_p(v)
      || entity_all_dynamic_locations_p(v)
      ) {
    constant_path = true;
  }
  else if (entity_abstract_location_p(v)) { // Maybe this test permit to eliminate the 4 test just before?
    constant_path = true;
  }
  // Test if it's the constant NULL
  else if (entity_null_locations_p(v)) {
    constant_path = true;
  }
  // Test if it's a formal parameter
  else if (entity_stub_sink_p(v)) {
    constant_path = true;
  }
  // Test if it's a heap element
  else if (heap_area_p(v)) {
    constant_path = true;
  }
  // Maybe not efficient enough, for array of struct or struct of array?
  // Test if it's a structure
  else if (struct_type_p(entity_type(v)) && !ENDP(l_ind)) {
    constant_path = true;
  }
  // Test if it's a array with only *
  else if (!ENDP(l_ind)) {
    // see reference_unbounded_indices_p
    constant_path = reference_unbounded_indices_p(r);
  }

  return constant_path;
}


/* TODO
 * most of the time return same result that !effect_reference_dereferencing_p for the moment
 * want to test if r can be a constant path
 * for instance
 *        a[i] have to return false (something else?)
 *        a[0], a[1], i, j, a[*], var points by formal parameter (_p_0, ...), element of strut (s.id, ...), heap element
 *                  have to return true
 *  * !effect_reference_dereferencing_p(r, &exact_p)
 *      can return true when it's not a constant path like a[i] (a[i] and not a[*])
 *      can make a side effect for the declaration of variable in parameter (only?), don't know why
 *      for instance with Semantics-New/Pointer.sub/memcopy01
 *        void memcopy01([...], char dst[size])  -->  void memcopy01([...], char dst[i])
 *  * store_independent_reference_p(r)
 *      can return false for some cp like a[0], can't permit to treat the array
 *          return false for the structure too, can't permit to treat the struct
 *      can return true for i, j, ... that can be a constant path but not strictly a constant path
 * param r          reference to analyze to see if it's a constant path
 * return           true if r can be constant path
 *
 * This function is not used by the points-to analysis, but by semantics
 */
bool can_be_constant_path_p(reference r)
{
  bool constant_path = true;

  if (strict_constant_path_p(r))
    constant_path = true;
  else {
    bool exact_p = true;
    if (!effect_reference_dereferencing_p(r, &exact_p)) {
      constant_path = true;
    }
    else {
      constant_path = false;
    }
  }

  return constant_path;
}
