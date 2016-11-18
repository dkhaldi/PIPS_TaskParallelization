/*

  $Id: declarations2.c 23065 2016-03-02 09:05:50Z coelho $

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

// strndup are GNU extensions...
#include <stdio.h>
#include <string.h>

#include "genC.h"
#include "text.h"
#include "constants.h"

#include "text-util.h"
#include "properties.h"
#include "misc.h"
#include "linear.h"
#include "text-util.h"
#include "ri.h"
#include "ri-util.h"
#include "pipsdbm.h"
#include "workspace-util.h"
#include "prettyprint.h"

/* debugging for equivalences */
#define EQUIV_DEBUG 8

/* To deal with declarations above ri-util and pipsdbm and text-util */

/********************************************************************* TEXT */

#define ADD_WORD_LIST_TO_TEXT(t, l) ADD_WORD_LIST_TO_TEXT_WITH_MARGIN(t, l, 0)
#define ADD_WORD_LIST_TO_TEXT_WITH_MARGIN(t, l, m)\
  if (!ENDP(l)) ADD_SENTENCE_TO_TEXT(t,\
             make_sentence(is_sentence_unformatted, \
               make_unformatted(NULL, 0, m, l)));

/********************************************************** ALL DECLARATIONS */
/**
 * @brief This handle the fact that a Fortran95 declaration use "::" as a
 * separator between type and variable name. It also adds an "allocatable"
 * modifier if requested. Finally it add a "," between each variable if there
 * more than one to declare.
 **/
static list f77_f95_style_management(list prev,
                                     string str,
                                     bool allocatable_pass_p,
                                     bool space_p) {
  list result = prev;
  if (prev == NIL) {
    result = CHAIN_SWORD(result, str);
    if(allocatable_pass_p) {
      result = CHAIN_SWORD(result, ", ALLOCATABLE ");
    }
    if (prettyprint_language_is_fortran95_p ()) {
      result = CHAIN_SWORD(result, ":: ");
    }
  }
  else {
    result = CHAIN_SWORD(result, space_p? ", " : ",");
  }
  return result;
}

/* if the common is declared similarly in all routines, generate
 * "include 'COMMON.h'", and the file is put in Src. otherwise
 * the full local declarations are generated. That's fun.
 */

static text include(const char* file)
{
  return make_text
    (CONS(SENTENCE,
	  make_sentence(is_sentence_formatted,
			strdup(concatenate("      include '", file, "'\n", NULL))),
	  NIL));
}

static void equiv_class_debug(list l_equiv)
{
  if (ENDP(l_equiv))
    fprintf(stderr, "<none>");
  MAP(ENTITY, equiv_ent,
      {
	fprintf(stderr, " %s", entity_local_name(equiv_ent));
      }, l_equiv);
  fprintf(stderr, "\n");
}

/* static int equivalent_entity_compare(entity *ent1, entity *ent2)
 * input    : two pointers on entities.
 * output   : an integer for qsort.
 * modifies : nothing.
 * comment  : this is a comparison function for qsort; the purpose
 *            being to order a list of equivalent variables.
 * algorithm: If two variables have the same offset, the longest 
 * one comes first; if they have the same length, use a lexicographic
 * ordering.
 * author: bc.
 */
static int equivalent_entity_compare(entity *ent1, entity *ent2)
{
  int result;
  int offset1 = ram_offset(storage_ram(entity_storage(*ent1)));
  int offset2 = ram_offset(storage_ram(entity_storage(*ent2)));
  Value size1, size2;

  result = offset1 - offset2;

  /* pips_debug(1, "entities: %s %s\n", entity_local_name(*ent1),
     entity_local_name(*ent2)); */

  if (result == 0)
    {
      /* pips_debug(1, "same offset\n"); */
      size1 = ValueSizeOfArray(*ent1);
      size2 = ValueSizeOfArray(*ent2);
      result = value_compare(size2,size1);

      if (result == 0)
	{
	  /* pips_debug(1, "same size\n"); */
	  result = strcmp(entity_local_name(*ent1), entity_local_name(*ent2));
	}
    }

  return(result);
}

/* static text text_equivalence_class(list  l_equiv)
 * input    : a list of entities representing an equivalence class.
 * output   : a text, which is the prettyprint of this class.
 * modifies : sorts l_equiv according to equivalent_entity_compare.
 * comment  : partially associated entities are not handled.
 * author   : bc.
 */
static text text_equivalence_class(list /* of entities */ l_equiv)
{
  text t_equiv = make_text(NIL);
  list lw = NIL;
  list l1, l2;
  entity ent1, ent2;
  int offset1, offset2;
  Value size1, offset_end1;
  bool first;
  bool space_p = get_bool_property("PRETTYPRINT_LISTS_WITH_SPACES");

  if (gen_length(l_equiv)<=1) return t_equiv;

  /* FIRST, sort the list by increasing offset from the beginning of
     the memory suite. If two variables have the same offset, the longest
     one comes first; if they have the same lenght, use a lexicographic
     ordering */
  ifdebug(EQUIV_DEBUG)
  {
    pips_debug(1, "equivalence class before sorting:\n");
    equiv_class_debug(l_equiv);
  }

  gen_sort_list(l_equiv,
		(int (*)(const void *,const void *)) equivalent_entity_compare);

  ifdebug(EQUIV_DEBUG)
  {
    pips_debug(1, "equivalence class after sorting:\n");
    equiv_class_debug(l_equiv);
  }

  /* THEN, prettyprint the sorted list*/
  pips_debug(EQUIV_DEBUG,"prettyprint of the sorted list\n");

  /* At each step of the next loop, we consider two entities
   * from the equivalence class. l1 points on the first entity list,
   * and l2 on the second one. If l2 is associated with l1, we compute
   * the output string, and l2 becomes the next entity. If l2 is not
   * associated with l1, l1 becomes the next entity, until it is
   * associated with l1. In the l_equiv list, l1 is always before l2.
   */

  /* loop initialization */
  l1 = l_equiv;
  ent1 = ENTITY(CAR(l1));
  offset1 = ram_offset(storage_ram(entity_storage(ent1)));
  size1 = ValueSizeOfArray(ent1);
  l2 = CDR(l_equiv);
  first = true;

  while(!ENDP(l2))
    {
      ent2 = ENTITY(CAR(l2));
      offset2 = ram_offset(storage_ram(entity_storage(ent2)));

      pips_debug(EQUIV_DEBUG, "dealing with: %s %s\n",
		 entity_local_name(ent1),
		 entity_local_name(ent2));

      /* If the two variables have the same offset, their
       * first elements are equivalenced.
       */
      if (offset1 == offset2)
	{
	  pips_debug(EQUIV_DEBUG, "easiest case: offsets are the same\n");

	  if (first) lw = CHAIN_SWORD(lw, "EQUIVALENCE"), first = false;
	  else lw = CHAIN_SWORD(lw, space_p? ", " : ",");

	  lw = CHAIN_SWORD(lw, " (");
	  lw = CHAIN_SWORD(lw, entity_local_name(ent1));
	  lw = CHAIN_SWORD(lw, space_p? ", " : ",");
	  lw = CHAIN_SWORD(lw, entity_local_name(ent2));
	  lw = CHAIN_SWORD(lw, ")");
	  POP(l2);
	}
      /* Else, we first check that there is an overlap */
      else
	{
	  pips_assert("the equivalence class has been sorted\n",
		      offset1 < offset2);

	  offset_end1 = value_plus(offset1, size1);

	  /* If there is no overlap, we change the reference variable */
	  if (value_le(offset_end1,offset2))
	    {
	      pips_debug(1, "second case: there is no overlap\n");
	      POP(l1);
	      ent1 = ENTITY(CAR(l1));
	      offset1 = ram_offset(storage_ram(entity_storage(ent1)));
	      size1 = ValueSizeOfArray(ent1);
	      if (l1 == l2) POP(l2);
	    }

	  /* Else, we must compute the coordinates of the element of ent1
	   * which corresponds to the first element of ent2
	   */
	  else
	    {
	      /* ATTENTION: Je n'ai pas considere le cas
	       * ou il y a association partielle. De ce fait, offset
	       * est divisiable par size_elt_1. */
	      int offset = offset2 - offset1;
	      int rest;
	      int current_dim;
	      int dim_max = NumberOfDimension(ent1);
	      int size_elt_1 = SizeOfElements(
					      variable_basic(type_variable(entity_type(ent1))));
	      list l_tmp = variable_dimensions
		(type_variable(entity_type(ent1)));
	      normalized nlo;
	      Pvecteur pvlo;

	      pips_debug(EQUIV_DEBUG, "third case\n");
	      pips_debug(EQUIV_DEBUG,
			 "offset=%d, dim_max=%d, size_elt_1=%d\n",
			 offset, dim_max,size_elt_1);

	      if (first) lw = CHAIN_SWORD(lw, "EQUIVALENCE"), first = false;
	      else lw = CHAIN_SWORD(lw, space_p? ", " : ",");

	      lw = CHAIN_SWORD(lw, " (");
	      lw = CHAIN_SWORD(lw, entity_local_name(ent1));
	      lw = CHAIN_SWORD(lw, "(");

	      pips_assert("partial association case not implemented:\n"
			  "offset % size_elt_1 == 0",
			  (offset % size_elt_1) == 0);

	      offset = offset/size_elt_1;
	      current_dim = 1;

	      while (current_dim <= dim_max)
		{
		  dimension dim = DIMENSION(CAR(l_tmp));
		  int new_decl;
		  int size;

		  pips_debug(EQUIV_DEBUG, "prettyprinting dimension %d\n",
			     current_dim);
		  size = SizeOfIthDimension(ent1, current_dim);
		  rest = (offset % size);
		  offset = offset / size;
		  nlo = NORMALIZE_EXPRESSION(dimension_lower(dim));
		  pvlo = normalized_linear(nlo);

		  pips_assert("sg", vect_constant_p(pvlo));
		  pips_debug(EQUIV_DEBUG,
			     "size=%d, rest=%d, offset=%d, lower_bound=%d\n",
			     size, rest, offset, (int)VALUE_TO_INT(val_of(pvlo)));

		  new_decl = VALUE_TO_INT(val_of(pvlo)) + rest;
		  lw = CHAIN_SWORD(lw,int2a(new_decl));
		  if (current_dim < dim_max)
		    lw = CHAIN_SWORD(lw, space_p? ", " : ",");

		  POP(l_tmp);
		  current_dim++;

		} /* while */

	      lw = CHAIN_SWORD(lw, ")");
	      lw = CHAIN_SWORD(lw, space_p? ", " : ",");
	      lw = CHAIN_SWORD(lw, entity_local_name(ent2));
	      lw = CHAIN_SWORD(lw, ")");
	      POP(l2);
	    } /* if-else: there is an overlap */
	} /* if-else: not same offset */
    } /* while */
  ADD_WORD_LIST_TO_TEXT(t_equiv, lw);

  pips_debug(EQUIV_DEBUG, "end\n");
  return t_equiv;
}


/* input    : the current module, and the list of declarations.
 * output   : a text for all the equivalences.
 * modifies : nothing
 * comment  :
 */
static text text_equivalences(
    entity __attribute__ ((unused)) module     /* the module dealt with */,
    list ldecl        /* the list of declarations to consider */,
    bool no_commons /* whether to print common equivivalences */)
{
  list equiv_classes = NIL, l_tmp;
  text t_equiv_class;

  pips_debug(1,"begin\n");

  /* FIRST BUILD EQUIVALENCE CLASSES */

  pips_debug(EQUIV_DEBUG, "loop on declarations\n");
  /* consider each entity in the declaration */
  MAP(ENTITY, e,
      {
	storage s = entity_storage(e);
	/* but only variables which have a ram storage must be considered
	 */
	if (type_variable_p(entity_type(e)) && storage_ram_p(s))
	  {
	    ram r = storage_ram(s);
	    entity common = ram_section(r);
	    list l_shared = ram_shared(r);

	    if (no_commons && !entity_special_area_p(common))
	      break;

	    ifdebug(EQUIV_DEBUG)
	    {
	      pips_debug(1, "considering entity: %s\n",entity_local_name(e));
	      pips_debug(1, "shared variables:\n");
	      equiv_class_debug(l_shared);
	    }

	    /* If this variable is statically aliased */
	    if (!ENDP(l_shared))
	      {
		bool found = false;
		list found_equiv_class = NIL;

		/* We first look in already found equivalence classes
		 * if there is already a class in which one of the
		 * aliased variables appears
		 */
		MAP(LIST, equiv_class,
		    {
		      ifdebug(EQUIV_DEBUG)
		      {
			pips_debug(1, "considering equivalence class:\n");
			equiv_class_debug(equiv_class);
		      }

		      MAP(ENTITY, ent,
			  {
			    if (variable_in_list_p(ent, equiv_class))
			      {
				found = true;
				found_equiv_class = equiv_class;
				break;
			      }
			  }, l_shared);

		      if (found) break;
		    },
		    equiv_classes);

		if (found)
		  {
		    pips_debug(EQUIV_DEBUG, "already there\n");
		    /* add the entities of shared which are not already in
		     * the existing equivalence class. Useful ??
		     */
		    MAP(ENTITY, ent,
			{
			  if(!variable_in_list_p(ent, found_equiv_class) &&
			     variable_in_list_p(ent, ldecl)) /* !!! */
			    found_equiv_class =
			      CONS(ENTITY, ent, found_equiv_class);
			}, l_shared)
		      }
		else
		  {
		    list l_tmp = NIL;
		    pips_debug(EQUIV_DEBUG, "not found\n");
		    /* add the list of variables in l_shared; necessary
		     * because variables may appear several times in
		     * l_shared. */
		    MAP(ENTITY, shared_ent,
			{
			  if (!variable_in_list_p(shared_ent, l_tmp) &&
			      variable_in_list_p(shared_ent, ldecl))
			    /* !!! restricted to declared... */
			    l_tmp = CONS(ENTITY, shared_ent, l_tmp);
			},
			l_shared);
		    equiv_classes = CONS(LIST, l_tmp, equiv_classes);
		  }
	      }
	  }
      },
      ldecl);

  ifdebug(EQUIV_DEBUG)
  {
    pips_debug(1, "final equivalence classes:\n");
    MAP(LIST, equiv_class, equiv_class_debug(equiv_class), equiv_classes);
  }

  /* SECOND, PRETTYPRINT THEM */
  t_equiv_class = make_text(NIL);
  MAP(LIST, equiv_class,
      {
	MERGE_TEXTS(t_equiv_class, text_equivalence_class(equiv_class));
      }, equiv_classes);

  /* AND FREE THEM */
  for(l_tmp = equiv_classes; !ENDP(l_tmp); POP(l_tmp))
    {
      list equiv_class = LIST(CAR(l_tmp));
      gen_free_list(equiv_class);
      LIST(CAR(l_tmp)) = NIL;
    }
  gen_free_list(equiv_classes);

  /* THE END */
  pips_debug(EQUIV_DEBUG, "end\n");
  return(t_equiv_class);
}

/**
 * @brief Create a sentence for a USE directive
 *
 * @description Use directive is handled by copying the string directly in the
 * name of the entity during the parsing. So we juste get the local name and put
 * it in a sentence.
 *
 * @return a sentence with correct indentation containing the whole use
 * directive in one word.
 */
static sentence sentence_f95use_declaration( entity e ) {
  list decl = NIL;

  decl = CHAIN_SWORD(decl, entity_local_name(e));

  return (make_sentence(is_sentence_unformatted, make_unformatted(NULL,
                                                                  0,
                                                                  INDENTATION,
                                                                  decl)));
}

static sentence sentence_external(entity f)
{
  list pc = NIL;

  pc = CHAIN_SWORD(pc, "EXTERNAL ");
  pc = CHAIN_SWORD(pc, entity_local_name(f));

  return(make_sentence(is_sentence_unformatted,
		       make_unformatted(NULL, 0, get_prettyprint_indentation(), pc)));
}

static sentence sentence_symbolic(entity f, list * ppdl)
{
  list pc = NIL;
  value vf = entity_initial(f);
  expression e = symbolic_expression(value_symbolic(vf));

  pc = CHAIN_SWORD(pc, "PARAMETER (");
  pc = CHAIN_SWORD(pc, entity_local_name(f));
  pc = CHAIN_SWORD(pc, " = ");
  pc = gen_nconc(pc, words_expression(e, ppdl));
  pc = CHAIN_SWORD(pc, ")");

  return(make_sentence(is_sentence_unformatted,
		       make_unformatted(NULL, 0, get_prettyprint_indentation(), pc)));
}

/* why is it assumed that the constant is an int ???
 */
static sentence sentence_data(entity e)
{
  list pc = NIL;
  constant c;

  if (! value_constant_p(entity_initial(e)))
    return(sentence_undefined);

  c = value_constant(entity_initial(e));

  if (! constant_int_p(c))
    return(sentence_undefined);

  pc = CHAIN_SWORD(pc, "DATA ");
  pc = CHAIN_SWORD(pc, entity_local_name(e));
  pc = CHAIN_SWORD(pc, " /");
  pc = CHAIN_IWORD(pc, constant_int(c));
  pc = CHAIN_SWORD(pc, "/");

  return(make_sentence(is_sentence_unformatted,
		       make_unformatted(NULL, 0, get_prettyprint_indentation(), pc)));
}


/*  special management of empty commons added.
 *  this may happen in the hpfc generated code.
 */
static sentence sentence_area(entity e, entity module, bool pp_dimensions, list * ppdl)
{
    const char* area_name = module_local_name(e);
    type te = entity_type(e);
    list pc = NIL, entities = NIL;
    bool space_p = get_bool_property("PRETTYPRINT_LISTS_WITH_SPACES");

    /* FI: POINTER declarations should be generated for the heap area */
    if (dynamic_area_p(e) || heap_area_p(e) || stack_area_p(e) || pointer_dummy_targets_area_p(e)) /* shouldn't get in? */
	return sentence_undefined;

    assert(type_area_p(te));

    if (!ENDP(area_layout(type_area(te))))
    {
	bool pp_hpfc = get_bool_property("PRETTYPRINT_HPFC");

	if (pp_hpfc)
	    entities = gen_copy_seq(area_layout(type_area(te)));
	else
	    entities = common_members_of_module(e, module, true);

	/*  the common is not output if it is empty
	 */
	if (!ENDP(entities))
	{
	    bool comma = false, is_save = static_area_p(e);

	    if (is_save)
	    {
		pc = CHAIN_SWORD(pc, "SAVE ");
	    }
	    else
	    {
		pc = CHAIN_SWORD(pc, "COMMON ");
		if (strcmp(area_name, BLANK_COMMON_LOCAL_NAME) != 0)
		{
		    pc = CHAIN_SWORD(pc, "/");
		    pc = CHAIN_SWORD(pc, area_name);
		    pc = CHAIN_SWORD(pc, "/ ");
		}
	    }

	    MAP(ENTITY, ee,
	     {
		 if (comma) pc = CHAIN_SWORD(pc, space_p? ", " : ",");
		 else comma = true;
		 pc = gen_nconc(pc,
				words_declaration(ee, !is_save && pp_dimensions, ppdl));
	     },
		 entities);

	    gen_free_list(entities);
	}
	else
	{
	    pips_user_warning("empty common %s for module %s encountered...\n",
			      entity_name(e), entity_name(module));
	    return make_sentence(is_sentence_formatted,
	       strdup(concatenate("!! empty common ", entity_local_name(e),
				  " in module ", entity_local_name(module),
				  "\n", NULL)));
	}
    }

    return make_sentence(is_sentence_unformatted,
			 make_unformatted(NULL, 0, get_prettyprint_indentation(), pc));
}

static sentence sentence_basic_declaration(entity e)
{
  list decl = NIL;
  basic b = entity_basic(e);

  pips_assert("b is defined", !basic_undefined_p(b));

  decl = CHAIN_SWORD(decl, basic_to_string(b));
  decl = CHAIN_SWORD(decl, " ");
  decl = CHAIN_SWORD(decl, entity_local_name(e));

  return(make_sentence(is_sentence_unformatted,
		       make_unformatted(NULL, 0, get_prettyprint_indentation(), decl)));
}


/* Prettyprint the initializations field of code */
static sentence sentence_data_statement(statement is, list * ppdl)
{
  unformatted u =
    make_unformatted
    (NULL,
     STATEMENT_NUMBER_UNDEFINED, get_prettyprint_indentation(),
     CONS(STRING, strdup("DATA "), NIL));
  sentence s = make_sentence(is_sentence_unformatted, u);
  list wl = unformatted_words(u);
  instruction ii = statement_instruction(is);
  call ic = instruction_call(ii);
  entity ife = entity_undefined;
  list al = list_undefined; /* Argument List */
  list rl = list_undefined; /* Reference List */
  expression rle = expression_undefined; /* reference list expression, i.e. call to DATA LIST */
  entity rlf = entity_undefined; /* DATA LIST entity function */
  bool space_p = get_bool_property("PRETTYPRINT_LISTS_WITH_SPACES");

  pips_assert("An initialization instruction is a call", instruction_call_p(ii));
  ife = call_function(ic);
  pips_assert("The static initialization function is called",
	      ENTITY_STATIC_INITIALIZATION_P(ife));
  al = call_arguments(ic);

  /* Find all initialized variables pending from DATA LIST */
  rle = EXPRESSION(CAR(al));
  POP(al); /* Move al to the first value */
  pips_assert("The first argument is a call", expression_call_p(rle));
  rlf = call_function(syntax_call(expression_syntax(rle)));
  pips_assert("This is the DATA LIST function", ENTITY_DATA_LIST_P(rlf));
  rl = call_arguments(syntax_call(expression_syntax(rle)));

  for(; !ENDP(rl); POP(rl)){
    expression ive = expression_undefined;
    list ivwl = list_undefined;

    if(rl!=call_arguments(syntax_call(expression_syntax(rle)))) {
      wl = CHAIN_SWORD(wl, strdup(space_p? ", " : ","));
    }

    ive = EXPRESSION(CAR(rl));
    ivwl = words_expression(ive, ppdl);
    wl = gen_nconc(wl, ivwl);
  }

  pips_assert("The value list is not empty", !ENDP(al));

  /* Print all values */

  wl = CHAIN_SWORD(wl, " /");

  for(; !ENDP(al); POP(al)){
    expression ve = EXPRESSION(CAR(al));
    call vc = syntax_call(expression_syntax(ve));
    list iwl = list_undefined;

    pips_assert("Values are encoded as calls", expression_call_p(ve));

    if(strcmp(module_local_name(call_function(vc)), REPEAT_VALUE_NAME)==0) {
      expression rfe = expression_undefined;
      expression rve = expression_undefined;
      list rwl = list_undefined;

      pips_assert("Pseudo-intrinsic REPEAT-VALUE must have two arguments",
		  gen_length(call_arguments(vc))==2);

      rfe = binary_call_lhs(vc);
      rve = binary_call_rhs(vc);

      if(!(integer_constant_expression_p(rfe) && expression_to_int(rfe)==1)) {
	/* print out the repeat factor if it is not one */
	rwl = words_expression(rfe, ppdl);
	wl = gen_nconc(wl, rwl);
	wl = gen_nconc(wl, CONS(STRING, strdup("*"), NIL));
      }
      iwl = words_expression(rve, ppdl);
      wl = gen_nconc(wl, iwl);
    }
    else {
      iwl = words_expression(ve, ppdl);
      wl = gen_nconc(wl, iwl);
    }
    if(!ENDP(CDR(al))) {
      wl = gen_nconc(wl, CONS(STRING, strdup(space_p? ", " : ","), NIL));
    }
  }

  wl = CHAIN_SWORD(wl, "/");

  return s;
}

/*************************************************************** PARAMETERS */

static text text_of_parameters(list /* of entity that are parameters */ lp)
{
  list /* of sentence */ ls = NIL;

  /* generate the sentences
   */
  FOREACH(ENTITY, e, lp) {
    list pdl = NIL; // Assumed to be Fortran only
    ls = CONS(SENTENCE, sentence_basic_declaration(e),
	      CONS(SENTENCE, sentence_symbolic(e, &pdl), ls));
  }

  return make_text(ls);
}

/* We add this function to cope with the declaration
 * When the user declare sth. there's no need to declare sth. for the user.
 * When nothing is declared ( especially there is no way to know whether it's
 * a SUBROUTINE or PROGRAM). We will go over the entire module to find all the
 * variables and declare them properly.
 * Lei ZHOU 18/10/91
 *
 * the float length is now tested to generate REAL*4 or REAL*8.
 * ??? something better could be done, printing "TYPE*%d".
 * the problem is that you cannot mix REAL*4 and REAL*8 in the same program
 * Fabien Coelho 12/08/93 and 15/09/93
 *
 * pf4 and pf8 distinction added, FC 26/10/93
 *
 * Is it really a good idea to print overloaded type variables~? FC 15/09/93
 * PARAMETERS added. FC 15/09/93
 *
 * typed PARAMETERs FC 13/05/94
 * EXTERNALS are missing: added FC 13/05/94
 *
 * Bug: parameters and their type should be put *before* other declarations
 *      since they may use them. Changed FC 08/06/94
 *
 * COMMONS are also missing:-) added, FC 19/08/94
 *
 * updated to fully control the list to be used.
 */
/* hook for commons, when not generated...
 */
static string default_common_hook(entity __attribute__ ((unused)) module,
				  entity common)
{
  return strdup(concatenate
		("common to include: ", entity_local_name(common), "\n", NULL));
}

static string (*common_hook)(entity, entity) = default_common_hook;

void set_prettyprinter_common_hook(string(*f)(entity,entity))
{
  common_hook=f;
}

void reset_prettyprinter_common_hook(void)
{
  common_hook=default_common_hook;
}

static text text_area_included(
    entity common /* the common the declaration of which are of interest */,
    entity module /* the module dealt with */)
{
  string dir, file, local;
  const char* name;
  text t;

  dir = db_get_directory_name_for_module(WORKSPACE_SRC_SPACE);
  name = module_local_name(common);
  if (same_string_p(name, BLANK_COMMON_LOCAL_NAME))
    name = "blank";
  local = strdup(concatenate(name, ".h", NULL));
  file = strdup(concatenate(dir, "/", local, NULL));
  free(dir);

  if (file_exists_p(file))
    {
      /* the include was generated once before... */
      t = include(local);
    }
  else
    {
      string nofile =
	strdup(concatenate(file, ".sorry_common_not_homogeneous", NULL));
      t = text_common_declaration(common, module);
      if (!file_exists_p(nofile))
	{
	  if (check_common_inclusion(common))
	    {
	      /* same declaration, generate the file! */
	      FILE * f = safe_fopen(file, "w");
	      fprintf(f, "!!\n!! pips: include file for common %s\n!!\n",
		      name);
	      print_text(f, t);
	      safe_fclose(f, file);
	      t = include(local);
	    }
	  else
	    {
	      /* touch the nofile to avoid the inclusion check latter on. */
	      FILE * f = safe_fopen(nofile, "w");
	      fprintf(f,
		      "!!\n!! pips: sorry,  cannot include common %s\n!!\n",
		      name);
	      safe_fclose(f, nofile);
	    }
	  free(nofile);
	}
    }

  free(local); free(file);
  return t;
}

/* @brief This function compute the list of declaration at the begining of
 * a module. It's intended to be used with Fortran or Fortran95 only
 *
 * @param ldecl is the list of entity to be prettyprinted
 * @param force_common will force the prettyprint of common in include
 * @param
 * @param pdl is the list of previously declared derived entities
 * @return the text of module declarations
 */
static text text_entity_declaration(entity module,
				    list /* of entity */ ldecl,
				    bool force_common,
				    list * ppdl)
{
  /*
   * allocatable_pass indicate if we want to prettyprint allocatable or non
   * allocatable entity, this is set to true during a second recursive pass.
   */
  static bool allocatable_pass_p = false;
  list allocatable_list = NULL;

  const char* how_common = get_string_property("PRETTYPRINT_COMMONS");
  bool print_commons = !same_string_p(how_common, "none");
  /* prettyprint common in include if possible... */
  bool pp_cinc = same_string_p(how_common, "include") && !force_common;
  list before = NIL, area_decl = NIL, pi1 = NIL, pi2 = NIL, pi4 = NIL, pi8 =
      NIL, ph1 = NIL, ph2 = NIL, ph4 = NIL, ph8 = NIL, pf4 = NIL, pf8 = NIL,
      pl = NIL, pc8 = NIL, pc16 = NIL, ps = NIL, lparam = NIL, uses = NIL;
  list * ppi = NULL;
  list * pph = NULL;
  text r, t_chars = make_text(NIL), t_area = make_text(NIL);
  const char* pp_var_dim = get_string_property("PRETTYPRINT_VARIABLE_DIMENSIONS");
  bool pp_in_type = false, pp_in_common = false;
  bool space_p = get_bool_property("PRETTYPRINT_LISTS_WITH_SPACES");
  /* Declarations cannot be sorted out because Fortran standard impose
   at least an order on parameters. Fortunately here, PARAMETER are
   mostly integers, defined from other integer parameters... I assume
   that PIPS would fail with an ENTRY referencing an integer array
   dimensionned with a real parameter. But real parameters are not
   really well processed by PIPS anyway... Also we are in trouble if
   arrays or functions are used dimension other arrays

   list sorted_ldecl = gen_copy_seq(ldecl);

   gen_sort_list(sorted_ldecl, compare_entities); */

  check_fortran_declaration_dependencies(ldecl);


  /*
   * Deals with indentation
   */
  list indentation_words = NIL;
  if( prettyprint_language_is_fortran95_p() ) {
    for(int i=0; i<INDENTATION; i++) {
      indentation_words = CHAIN_SWORD(indentation_words, " ");
    }
  }

  /* where to put the dimension information.
   */
  if (same_string_p(pp_var_dim, "type")) {
    pp_in_type = true, pp_in_common = false;
  } else if (same_string_p(pp_var_dim, "common")) {
    pp_in_type = false, pp_in_common = true;
  } else {
    pips_internal_error("PRETTYPRINT_VARIABLE_DIMENSIONS=\"%s\""
        " unexpected value\n", pp_var_dim);
  }



  FOREACH(ENTITY, e,ldecl) {
    type te = entity_type(e);
    bool func = type_functional_p(te) && storage_rom_p(entity_storage(e));
    value v = entity_initial(e);
    bool param = func && value_symbolic_p(v);
    bool external = /* subroutines won't be declared */
          (func
        && (value_code_p(v) || value_unknown_p(v) /* not parsed callee */)
        && !(type_void_p(functional_result(type_functional(te)))
            || (type_variable_p(functional_result(type_functional(te)))
                && basic_overloaded_p(variable_basic(type_variable
                        (functional_result(type_functional(te))))))));
    bool area_p = type_area_p(te);
    bool var = type_variable_p(te);
    bool in_ram = storage_ram_p(entity_storage(e));
    bool in_common = in_ram
        && !entity_special_area_p(ram_section(storage_ram(entity_storage(e))));
    bool skip_it = same_string_p(entity_local_name(e),
        entity_local_name(module));

    pips_debug(3, "entity name is %s\n", entity_name(e));

    /* Do not declare variables used to replace formal labels */
    if (storage_formal_p(entity_storage(e))
        && get_bool_property("PRETTYPRINT_REGENERATE_ALTERNATE_RETURNS")
        && formal_label_replacement_p(e))
      continue;

    if (!print_commons && area_p && !entity_special_area_p(e) && !pp_cinc) {
      area_decl = CONS(SENTENCE,
          make_sentence(is_sentence_formatted,
              common_hook(module, e)),
          area_decl);
    }

    if (skip_it) {
      pips_debug(5, "skipping function %s\n", entity_name(e));
    } else if (entity_f95use_p(e)) {
      uses = CONS(SENTENCE, sentence_f95use_declaration(e), uses);
    } else if (!print_commons && (area_p || (var && in_common && pp_cinc))) {
      pips_debug(5, "skipping entity %s\n", entity_name(e));
    } else if (param) {
      /*        PARAMETER
       */
      pips_debug(7, "considered as a parameter\n");
      lparam = CONS(ENTITY, e, lparam);
    } else if (external) {
      /*        EXTERNAL
       */
      pips_debug(7, "considered as an external\n");
      before = CONS(SENTENCE, sentence_basic_declaration(e), before);
      before = CONS(SENTENCE, sentence_external(e), before);
    } else if (area_p && !dynamic_area_p(e) && !heap_area_p(e)
	       && !stack_area_p(e) && !pointer_dummy_targets_area_p(e) && !empty_static_area_p(e) ) {
      /*            AREAS: COMMONS and SAVEs
       */
      pips_debug(7, "considered as a regular common\n");
      if (pp_cinc && !entity_special_area_p(e)) {
        text t = text_area_included(e, module);
        MERGE_TEXTS(t_area, t);
      } else
        area_decl = CONS(SENTENCE,
            sentence_area(e, module, pp_in_common, ppdl),
            area_decl);
    } else if (var && !(in_common && pp_cinc)) {
      basic b = variable_basic(type_variable(te));
      bool pp_dim = pp_in_type || variable_static_p(e);

      pips_debug(7, "is a variable...\n");

      switch(basic_tag(b)) {
        case is_basic_int:
          /* simple integers are moved ahead... */

          pips_debug(7, "is an integer\n");
          if (variable_dimensions(type_variable(te))) {
            string s = string_undefined;
            switch(basic_int(b)) {
              case 4:
                ppi = &pi4;
                s = "INTEGER ";
                break;
              case 2:
                ppi = &pi2;
                s = "INTEGER*2 ";
                break;
              case 8:
                ppi = &pi8;
                s = "INTEGER*8 ";
                break;
              case 1:
                ppi = &pi1;
                s = "INTEGER*1 ";
                break;

              default:
                pips_internal_error("Unexpected integer size");
            }

            *ppi = f77_f95_style_management (*ppi, s, allocatable_pass_p, space_p);
            *ppi = gen_nconc(*ppi, words_declaration(e, pp_dim, ppdl));
          } else {
            string s = string_undefined;

            switch(basic_int(b)) {
              case 4:
                pph = &ph4;
                s = "INTEGER ";
                break;
              case 2:
                pph = &ph2;
                s = "INTEGER*2 ";
                break;
              case 8:
                pph = &ph8;
                s = "INTEGER*8 ";
                break;
              case 1:
                pph = &ph1;
                s = "INTEGER*1 ";
                break;
              default:
                pips_internal_error("Unexpected integer size");
            }
            *pph = f77_f95_style_management (*pph, s, allocatable_pass_p, space_p);
            *pph = gen_nconc(*pph, words_declaration(e, pp_dim, ppdl));
          }
          break;
        case is_basic_float:
          pips_debug(7, "is a float\n");
          switch(basic_float(b)) {
            case 4:
              pf4 = f77_f95_style_management(pf4, "REAL*4 ", allocatable_pass_p, space_p);
              pf4 = gen_nconc(pf4, words_declaration(e, pp_dim, ppdl));
              break;
            case 8:
            default:
              pf8 = f77_f95_style_management(pf8, "REAL*8 ", allocatable_pass_p, space_p);
              pf8 = gen_nconc(pf8, words_declaration(e, pp_dim, ppdl));
              break;
          }
          break;
        case is_basic_complex:
          pips_debug(7, "is a complex\n");
          switch(basic_complex(b)) {
            case 8:
              pc8 = f77_f95_style_management(pc8, "COMPLEX*8 ", allocatable_pass_p, space_p);
              pc8 = gen_nconc(pc8, words_declaration(e, pp_dim, ppdl));
              break;
            case 16:
            default:
              pc16 = f77_f95_style_management(pc16, "COMPLEX*16 ", allocatable_pass_p, space_p);
              pc16 = gen_nconc(pc16, words_declaration(e, pp_dim, ppdl));
              break;
          }
          break;
        case is_basic_logical:
          pips_debug(7, "is a logical\n");
          pl = CHAIN_SWORD(pl, pl==NIL ? "LOGICAL " : (space_p? ", " : ","));
          pl = gen_nconc(pl, words_declaration(e, pp_dim, ppdl));
          break;
        case is_basic_overloaded:
          /* nothing! some in hpfc I guess...
           */
          break;
        case is_basic_string: {
          value v = basic_string(b);
          pips_debug(7, "is a string\n");

          if (value_constant_p(v) && constant_int_p(value_constant(v))) {
            int i = constant_int(value_constant(v));

            if (i == 1) {
              ps = f77_f95_style_management(ps, "CHARACTER ", allocatable_pass_p, space_p);
              ps = gen_nconc(ps, words_declaration(e, pp_dim, ppdl));
            } else {
              list chars = NIL;
              chars = CHAIN_SWORD(chars, "CHARACTER*");
              chars = CHAIN_IWORD(chars, i);
              chars = CHAIN_SWORD(chars, " ");
              chars = gen_nconc(chars, words_declaration(e, pp_dim, ppdl));
              attach_declaration_size_type_to_words(chars, "CHARACTER", i);
              ADD_WORD_LIST_TO_TEXT_WITH_MARGIN(t_chars, chars,
                                                get_prettyprint_indentation());
            }
          } else if (value_unknown_p(v)) {
            list chars = NIL;
            chars = CHAIN_SWORD(chars, "CHARACTER*(*) ");
            chars = gen_nconc(chars, words_declaration(e, pp_dim, ppdl));
            attach_declaration_type_to_words(chars, "CHARACTER*(*)");
            ADD_WORD_LIST_TO_TEXT_WITH_MARGIN(t_chars, chars,
                                              get_prettyprint_indentation());
          } else if (value_symbolic_p(v)) {
            list chars = NIL;
            symbolic s = value_symbolic(v);
            chars = CHAIN_SWORD(chars, "CHARACTER*(");
            chars = gen_nconc(chars, words_expression(symbolic_expression(s),
                                                      ppdl));
            chars = CHAIN_SWORD(chars, ") ");
            chars = gen_nconc(chars, words_declaration(e, pp_dim, ppdl));

            attach_declaration_type_to_words(chars, "CHARACTER*(*)");
            ADD_WORD_LIST_TO_TEXT(t_chars, chars);
          } else
            pips_internal_error("unexpected value");
          break;
        }
        case is_basic_derived: {
          if(allocatable_pass_p) {
            pips_internal_error("We got an allocatable but we are inside"
                "allocatable pass !! This should be impossible...\n");
          }
          // Chains the entity to be declared, aka the array inside allocatable
          allocatable_list = CONS(entity,get_allocatable_data_entity(e),allocatable_list);
          break;
        }
        default:
          pips_internal_error("unexpected basic tag (%d)",
              basic_tag(b));
      }
    }
  }


  /* usually they are sorted in order, and appended backwards,
   * hence the reversion.
   */
  r = make_text(uses);
  MERGE_TEXTS(r, make_text(gen_nreverse(before)));

  MERGE_TEXTS(r, text_of_parameters(lparam));
  gen_free_list(lparam), lparam = NIL;

  ADD_WORD_LIST_TO_TEXT_WITH_MARGIN(r, ph1, get_prettyprint_indentation());
  attach_declaration_type_to_words(ph1, "INTEGER*1");
  ADD_WORD_LIST_TO_TEXT_WITH_MARGIN(r, ph2, get_prettyprint_indentation());
  attach_declaration_type_to_words(ph2, "INTEGER*2");
  ADD_WORD_LIST_TO_TEXT_WITH_MARGIN(r, ph4, get_prettyprint_indentation());
  attach_declaration_type_to_words(ph4, "INTEGER");
  ADD_WORD_LIST_TO_TEXT_WITH_MARGIN(r, ph8, get_prettyprint_indentation());
  attach_declaration_type_to_words(ph8, "INTEGER*8");
  ADD_WORD_LIST_TO_TEXT_WITH_MARGIN(r, pi1, get_prettyprint_indentation());
  attach_declaration_type_to_words(pi1, "INTEGER*1");
  ADD_WORD_LIST_TO_TEXT_WITH_MARGIN(r, pi2, get_prettyprint_indentation());
  attach_declaration_type_to_words(pi2, "INTEGER*2");
  ADD_WORD_LIST_TO_TEXT_WITH_MARGIN(r, pi4, get_prettyprint_indentation());
  attach_declaration_type_to_words(pi4, "INTEGER");
  ADD_WORD_LIST_TO_TEXT_WITH_MARGIN(r, pi8, get_prettyprint_indentation());
  attach_declaration_type_to_words(pi8, "INTEGER*8");
  ADD_WORD_LIST_TO_TEXT_WITH_MARGIN(r, pf4, get_prettyprint_indentation());
  attach_declaration_type_to_words(pf4, "REAL*4");
  ADD_WORD_LIST_TO_TEXT_WITH_MARGIN(r, pf8, get_prettyprint_indentation());
  attach_declaration_type_to_words(pf8, "REAL*8");
  ADD_WORD_LIST_TO_TEXT_WITH_MARGIN(r, pl, get_prettyprint_indentation());
  attach_declaration_type_to_words(pl, "LOGICAL");
  ADD_WORD_LIST_TO_TEXT_WITH_MARGIN(r, pc8, get_prettyprint_indentation());
  attach_declaration_type_to_words(pc8, "COMPLEX*8");
  ADD_WORD_LIST_TO_TEXT_WITH_MARGIN(r, pc16, get_prettyprint_indentation());
  attach_declaration_type_to_words(pc16, "COMPLEX*16");
  ADD_WORD_LIST_TO_TEXT_WITH_MARGIN(r, ps, get_prettyprint_indentation());
  attach_declaration_type_to_words(ps, "CHARACTER");
  MERGE_TEXTS(r, t_chars);

  /* all about COMMON and SAVE declarations
   */
  MERGE_TEXTS(r, make_text(area_decl));
  MERGE_TEXTS(r, t_area);

  /* and EQUIVALENCE statements... - BC
   */
  MERGE_TEXTS(r, text_equivalences(module, /* sorted_ */ldecl,
          pp_cinc || !print_commons));

  /* what about DATA statements! FC
   */
  /* More general way with with call to text_initializations(module) in
   text_named_module() */
  /*
   if(get_bool_property("PRETTYPRINT_DATA_STATEMENTS")) {
   MERGE_TEXTS(r, text_data(module, ldecl));
   }
   */

  /* gen_free_list(sorted_ldecl); */

  if(!allocatable_pass_p && !ENDP(allocatable_list)) {
    /* We have to do a recursive call to get the allocatable declarations */
    allocatable_pass_p = true;
    MERGE_TEXTS(r,text_entity_declaration(module,allocatable_list,force_common,ppdl));
    allocatable_pass_p = false;
  }

  return r;
}

/* exported for hpfc.
 */
text text_declaration(entity module)
{
  /* Assume Fortran only! */
  list pdl = NIL;
  text t = text_entity_declaration
      (module, code_declarations(entity_code(module)), false, &pdl);
  gen_free_list(pdl);
  return t;
}

/* needed for hpfc
 */
text text_common_declaration(
    entity common,
    entity module)
{
    type t = entity_type(common);
    list l;
    text result;
    list pdl = NIL; // Assumed Fortran only
    pips_assert("indeed a common", type_area_p(t));
    l = CONS(ENTITY, common, common_members_of_module(common, module, false));
    result = text_entity_declaration(module, l, true, &pdl);
    gen_free_list(l);
    gen_free_list(pdl);
    return result;
}

text text_initializations(entity m)
{
  text t = make_text(NIL);
  list il = list_undefined;

  pips_assert("m is a module", entity_module_p(m));

  il = sequence_statements(code_initializations(value_code(entity_initial(m))));

  FOREACH(STATEMENT, is, il) {
    /* The previous declaration list is useless in Fortran, but the
       signature of functions designed for C or Fortran must be
       respected. */
    list pdl = NIL;
    if(!empty_comments_p(statement_comments(is))) {
      ADD_SENTENCE_TO_TEXT(t, make_sentence(is_sentence_formatted,
					    strdup(statement_comments(is))));
    }
    ADD_SENTENCE_TO_TEXT(t, sentence_data_statement(is, &pdl));
    gen_free_list(pdl);
  }

  return t;
}

/* returns the DATA initializations.
 * limited to integers, because I do not know where is the value
 * for other types...
 */
static text __attribute__ ((unused))
text_data(entity __attribute__ ((unused)) module, list /* of entity */ ldecl)
{
  list /* of sentence */ ls = NIL;

  FOREACH(ENTITY, e, ldecl)
      {
	value v = entity_initial(e);
	if(!value_undefined_p(v) &&
	   value_constant_p(v) && constant_int_p(value_constant(v)))
	  ls = CONS(SENTENCE, sentence_data(e), ls);
      }

  return make_text(ls);
}
