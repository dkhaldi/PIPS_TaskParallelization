/*

  $Id: identity_elimination.c 23065 2016-03-02 09:05:50Z coelho $

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

// do not compile unless required
#include "phases.h"
#if defined(BUILDER_IDENTITY_ELIMINATION) ||            \
  defined(BUILDER_IDENTITY_ELIMINATION_WITH_POINTS_TO)

#ifdef HAVE_CONFIG_H
    #include "pips_config.h"
#endif

#include <stdlib.h>
#include <stdio.h>

#include "genC.h"
#include "linear.h"

#include "pipsdbm.h"
#include "misc.h"

#include "ri.h"
#include "ri-util.h"
#include "prettyprint.h"

#include "effects-generic.h" // used
#include "effects-simple.h" // expression_with_side_effect_p
#include "control.h" // module_reorder

/*
 * Identity elimination, done by Nelson LOSSING
 * Pass : Identity elimination :
 * We want to eliminate identity instruction like "x=x;", or "a[i]=a[i];"
 * We need the effects to verify that there is no side effect in the affectation.
 * We don't want to eliminate "a[i++]=a[i++];"
 *
 * This pass can eliminate some raising exception.
 * For instance, with "p=p;", if p is an invalid memory cell an exception can be raise.
 * After the identity elimination, this instruction will be eliminate, so no more exception can be raise.
 *
 * An enhancement can be make to consider pointer/array :
 * int x, *p;
 * p=&x;
 * x=*p;    //can be delete
 * *p=x;    //can be delete
 * need effect for this
 */



//static bool is_assign_satement(statement s) {
//  pips_debug(0, "toto");
//  print_statement(s);
//  instruction i = statement_instruction(s);
//  if (instruction_call_p(i)) {
//    call c = instruction_call(i);
//    if (call_intrinsic_p(c)) {
//      entity e = call_function(c);
//      return ENTITY_ASSIGN_P(e);
//    }
//  }
//
//  return false;
//}

/**
 * remove identity statement like x=x, but conserve a[i++]=a[i++]
 * \param s         statement to consider
 */
static void identity_statement_remove(statement s) {
  instruction i = statement_instruction(s);
  ifdebug(5) {
    pips_debug(5, "begin\n");
    pips_debug(5, "study statement :\n");
    print_statement(s);
  }
  if (instruction_call_p(i)) {
    call c = instruction_call(i);
    if (call_intrinsic_p(c)) {
      entity e = call_function(c);
      cons *pc = call_arguments(c);
      if (ENTITY_ASSIGN_P(e)) {
        print_statement(s);

        pips_assert("2 args to assign", CDR(CDR(pc))==NIL);

        expression lhs = EXPRESSION(CAR(pc));
        expression rhs = EXPRESSION(CAR(CDR(pc)));

        // - we want to determinate if lhs and rhs are the same expressions
        // - we also need to be sure that there is no side effect in lhs, or rhs
        //   in fact only need to check side effect in lhs or rhs and not in the two expression
        //   because lhs and rhs have to be the same expressions
        if (expression_equal_p(lhs, rhs) &&
            //!expression_with_side_effect_p(lhs) &&
            !expression_with_side_effect_p(rhs)
            ) {
          pips_debug(5, "The statement is deleted\n");
          // Free old instruction
          free_instruction(statement_instruction(s));

          // Replace statement with a continue, so that we keep label
          statement_instruction(s) = make_continue_instruction();
          if(!empty_comments_p(statement_comments(s))) free(statement_comments(s)); statement_comments(s)=empty_comments;
          statement_remove_extensions(s);
        }
      }
    }
  }
  pips_debug(5, "end\n");
}

/**
 * TODO
 * remove identity statement like *p=x, or x=*p when p=&x
 * \param s         statement to consider
 */
/*
static void identity_statement_remove_with_points_to(_UNUSED_ statement s) {
//  instruction i = statement_instruction(s);
//  if (instruction_call_p(i)) {
//    call c = instruction_call(i);
//    if (call_intrinsic_p(c)) {
//      entity e = call_function(c);
//      cons *pc = call_arguments(c);
//      if (ENTITY_ASSIGN_P(e)) {
//        print_statement(s);
//
//        expression lhs = EXPRESSION(CAR(pc));
//        expression rhs = EXPRESSION(CAR(CDR(pc)));
//
//        pips_assert("2 args to assign", CDR(CDR(pc))==NIL);
//
//        // TODO
//        if (false
//            ) {
//          // Free old instruction
//          free_instruction(statement_instruction(s));
//
//          // Replace statement with a continue, so that we keep label && comments
//          statement_instruction(s) = make_continue_instruction();
//        }
//      }
//    }
//  }
}
*/

/**
 * generic_identity_elimination
 * get the environment, dependencies and launch the elimination
 * \param module_name   module to work on
 * \param use_points_to if we also consider pointer (*p=x, with p=&x)
 */
static bool generic_identity_elimination(
  const char* module_name,
  bool use_points_to)
{
  statement module_statement;
  bool good_result_p = true;

  debug_on("IDENTITY_ELIMINATION_DEBUG_LEVEL");
  pips_debug(1, "begin\n");

  //-- configure environment --//
  set_current_module_entity(module_name_to_entity(module_name));
  // entity module = get_current_module_entity();

  set_current_module_statement( (statement)
      db_get_memory_resource(DBR_CODE, module_name, true) );
  module_statement = get_current_module_statement();

  pips_assert("Statement should be OK before...",
      statement_consistent_p(module_statement));

  set_ordering_to_statement(module_statement);

  //-- get dependencies --//
  if(use_points_to) {
    set_pointer_info_kind(with_points_to); //enough?
  }

  set_proper_rw_effects((statement_effects)
      db_get_memory_resource(DBR_PROPER_EFFECTS, module_name, true));

  //-- Make the job -- //
  gen_recurse(module_statement, statement_domain, gen_true, identity_statement_remove);
  if(use_points_to) {
    //TODO
    //gen_recurse(module_statement, statement_domain, gen_true, identity_statement_remove_with_points_to);
  }

  /* Reorder the module, because some statements have been deleted.
     Well, the order on the remaining statements should be the same,
     but by reordering the statements, the number are consecutive. Just
     for pretty print... :-) */
  module_reorder(module_statement);

  pips_assert("Statement should be OK after...",
      statement_consistent_p(module_statement));

  //-- Save modified code to database --//
  DB_PUT_MEMORY_RESOURCE(DBR_CODE, strdup(module_name), module_statement);
//  DB_PUT_MEMORY_RESOURCE(DBR_CALLEES, module_name,
//       compute_callees(module_statement));

  reset_proper_rw_effects();
  reset_current_module_statement();
  reset_current_module_entity();
  reset_ordering_to_statement();

  pips_debug(1, "end\n");
  debug_off();

  return (good_result_p);
}

/**
 * PIPS pass
 */
bool identity_elimination(const char* module_name)
{
  return generic_identity_elimination(module_name, false);
}

/**
 * PIPS pass
 * TODO Not implemented
 */
bool identity_elimination_with_points_to(const char* module_name)
{
  pips_user_warning("identity_elimination_with_points_to not implemented, identity_elimination was done instead.");
  return generic_identity_elimination(module_name, true);
}

#endif // BUILDER_IDENTITY_ELIMINATION*
