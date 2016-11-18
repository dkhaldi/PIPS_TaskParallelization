/*

  $Id: util.c 23065 2016-03-02 09:05:50Z coelho $

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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "genC.h"
#include "linear.h"

#include "misc.h"
#include "pipsdbm.h"
#include "properties.h"

#include "ri.h"
#include "ri-util.h"

#include "effects.h"
#include "effects-simple.h"  // used

/******************************************************** CLEAN DECLARATIONS */

static bool filterout_statement(void *obj) {
  bool return_val = !INSTANCE_OF(statement,(gen_chunkp)obj);
  return return_val;
}

/* entities that match the following conditions are not
 * cleaned from declarations:
 */
static bool wipeout_entity(entity e) {
  pips_debug(6,"Wipeout entity evaluating %s\n",entity_name(e));
  bool return_val = entity_not_constant_or_intrinsic_p(e) && // filters out constants and intrinsics
      !formal_parameter_p(e) &&
      !storage_return_p(entity_storage(e)) &&
      !entity_area_p(e)&&
      !entity_struct_p(e)&&
      !entity_union_p(e) &&
      !typedef_entity_p(e);

  pips_debug(6,"return %d\n",return_val);

  return return_val;
}

/**
 * remove useless entities from declarations
 * an entity is flagged useless when no reference is found in stmt
 * and when it is not used by an entity found in stmt
 *
 * @param declarations list of entity to purge
 * @param stmt statement where entities are used
 *
 */
static void statement_clean_declarations_helper(list declarations,
    statement stmt) {
  set referenced_entities =
      get_referenced_entities_filtered(stmt,
          filterout_statement,
          wipeout_entity);

  /* look for entity that are used in the statement
   * SG: we need to work on  a copy of the declarations because of
   * the RemoveLocalEntityFromDeclarations
   */
  list decl_cpy = gen_copy_seq(declarations);
  FOREACH(ENTITY,e,decl_cpy) {
    /* filtered referenced entities are always used,
     * some entity types listed in keep_entity cannot be wiped out*/
    if(wipeout_entity(e) && !set_belong_p(referenced_entities, e)) {
      /* entities whose declaration have a side effect are always used too */
      bool has_side_effects_p = false;
      value v = entity_initial(e);
      list effects = NIL;
      if(value_expression_p(v))
        effects = gen_nconc(effects,
            expression_to_proper_effects(value_expression(v)));
      /* one should check if dimensions do not have side effects either */
      if(entity_variable_p(e)) {
        FOREACH(DIMENSION,dim,variable_dimensions(type_variable(entity_type(e))))
            {
          expression upper = dimension_upper(dim), lower = dimension_lower(dim);
          effects = gen_nconc(effects, expression_to_proper_effects(upper));
          effects = gen_nconc(effects, expression_to_proper_effects(lower));
            }
      }
      pips_debug(5,"Evaluating effects on %s\n",entity_name(e));
      FOREACH(EFFECT, eff, effects) {
        ifdebug(6) {
          print_effect(eff);
        }
        if(action_write_p(effect_action(eff)))
          has_side_effects_p = true;
      }
      gen_full_free_list(effects);

      /* do not keep the declaration, and remove it from any declaration_statement */
      if(!has_side_effects_p) {
        pips_debug(4,"Remove declaration for %s\n",entity_name(e));
        RemoveLocalEntityFromDeclarations(e, get_current_module_entity(), stmt);
      }
    }
  }
  gen_free_list(decl_cpy);

  set_free(referenced_entities);
}

/**
 * check if all entities used in s and module are declared in module
 * does not work as well as expected on c module because it does not fill the statement declaration
 * @param module module to check
 * @param s statement where reference can be found
 */
static void entity_generate_missing_declarations(entity module, statement s)
{
  /* gather referenced entities */
  set referenced_entities = get_referenced_entities(s);

  /* fill the declarations with missing entities (ohhhhh a nice 0(n²) algorithm*/
  list new = NIL;
  SET_FOREACH(entity,e1,referenced_entities) {
    if(gen_chunk_undefined_p(gen_find_eq(e1,entity_declarations(module))))
      new=CONS(ENTITY,e1,new);
  }

  set_free(referenced_entities);
  sort_list_of_entities(new);
  entity_declarations(module)=gen_nconc(new,entity_declarations(module));
}


/**
 * remove all the entity declared in s but never referenced
 * it's a lower version of use-def-elim !
 *
 * @param s statement to check
 */
void statement_clean_declarations(statement s)
{
  if(statement_block_p(s)) {
    statement_clean_declarations_helper( statement_declarations(s),s);
  }
}

/**
 * remove all entities declared in module but never used in s
 *
 * @param module module to check
 * @param s statement where entites may be used
 */
void entity_clean_declarations(entity module,statement s)
{
  entity curr = get_current_module_entity();
  if( ! same_entity_p(curr,module)) {
    reset_current_module_entity();
    set_current_module_entity(module);
  }
  else
    curr=entity_undefined;

  statement_clean_declarations_helper(entity_declarations(module),s);
  if(fortran_module_p(module)) /* to keep backward compatibility with hpfc*/
    entity_generate_missing_declarations(module,s);

  if(!entity_undefined_p(curr)){
    reset_current_module_entity();
    set_current_module_entity(curr);
  }
}

/****************************************************** FIND LOOP FROM LABEL */

struct flfl {
  entity label;
  statement found;
};

static bool find_loop_from_label_walker(loop l, struct flfl *p)
{
  statement s = (statement) gen_get_ancestor(statement_domain, l);
  entity
    do_lab_ent = loop_label(l),
    stmt_lab_ent = statement_label(s);
  if (gen_eq(p->label, do_lab_ent) || gen_eq(p->label, stmt_lab_ent) )
  {
    p->found = s;
    gen_recurse_stop(NULL);
  }
  return true;
}

statement find_loop_from_label(statement s, entity label)
{
  struct flfl ctx = { label, statement_undefined };
  gen_context_recurse(s, &ctx,
                      loop_domain, find_loop_from_label_walker, gen_null);
  return ctx.found;
}


/******************************************************************** TARGET */

// where is this used?

int get_processor_number(void)
{
    return 16;
}

int get_vector_register_length(void)
{
    return 64;
}

int get_vector_register_number(void)
{
    return 8;
}

#if 0
static int get_cache_line_size(void)
{
    return 1;
}
static int get_minimal_task_size(void)
{
    /* the unit is supposed to be consistent with the complexity cost tables used
     * that should be expressed in machine cycles
     */
    return 10000;
}
#endif
