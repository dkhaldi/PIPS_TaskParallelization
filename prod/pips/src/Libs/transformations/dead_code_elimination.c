/*

  $Id: dead_code_elimination.c 23065 2016-03-02 09:05:50Z coelho $

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
#if defined(BUILDER_DEAD_CODE_ELIMINATION) ||             \
  defined(BUILDER_DEAD_CODE_ELIMINATION_WITH_OUT_REGIONS)

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
#include "effects.h"
#include "ri-util.h"
#include "prettyprint.h"
#include "effects-util.h"

#include "text-util.h"

#include "control.h" // module_reorder

#include "semantics.h" // used: set and reset_precondition_map()
#include "effects-generic.h" // used
#include "effects-simple.h"  // used
#include "callgraph.h" // used

#include "dg.h"
// Instantiation of the dependence graph:
typedef dg_arc_label arc_label;
typedef dg_vertex_label vertex_label;
#include "graph.h"

#include "ricedg.h" // used

// for module_clean_declarations
// and loop_bound_minimization_with_out_regions_on_statement
#include "transformations.h"

static graph dependence_graph;

static hash_table ordering_to_dg_mapping;

static set the_useful_statements;

/* Define the mapping to store the statements generating something
   useful for a given statement and the functions used to deal
   with. It is a mapping from a statement to a *set* of statements,
   those that generate interesting use-def values.*/
static hash_table statements_use_def_dependence;


/* Define a static stack and related functions to remember the current
   statement for build_statement_to_statement_father_mapping(): */
DEFINE_LOCAL_STACK(current_statement, statement)


/*
 * A string list of user functions that we want to preserve from elimination
 */
static list keeped_functions = 0;

/*
 * A string list of user functions prefix that we want to preserve from elimination
 */
static list keeped_functions_prefix = 0;


static void dead_code_elimination_error_handler(void)
{
  error_reset_current_statement_stack();
}

/* Define the mapping to store the statement owning the statements and the
   functions used to deal with: */
GENERIC_LOCAL_FUNCTION(statement_father, persistant_statement_to_statement)


static void
add_statement_to_the_statement_to_statement_father_mapping(statement s)
{
  /* Pop the current_statement_stack: */
  current_statement_rewrite(s);

  pips_debug(4, "add_statement_to_the_statement_to_statement_father_mapping statement %p (%#zx), father %p\n",
      s, statement_ordering(s), current_statement_head());

  /* First add the current father for this statement: */
  /* Since statement_undefined == hash_undefined_value, we cannot put
      a statement_undefined in the hash_table... */
  if (current_statement_head() != statement_undefined)
    store_statement_father(s, current_statement_head());
}


/* Define the mapping to store the control fathers of the statements
   and the functions used to deal with: */
GENERIC_LOCAL_FUNCTION(control_father, persistant_statement_to_control)


/* Build a mapping from a statement to its eventual control father. */
static void
set_control_statement_father(control c)
{
  store_control_father(control_statement(c), c);
}


static void
build_statement_to_statement_father_mapping(statement s)
{
  pips_debug(4, "statement %p (%#zx)\n", s, statement_ordering(s));

  make_current_statement_stack();
  // The first statement has no father:
  current_statement_push(statement_undefined);

  gen_multi_recurse(s, statement_domain,
      // Just push the current statement on the current_statement_stack:
      current_statement_filter,
      add_statement_to_the_statement_to_statement_father_mapping,
      // Build a mapping from a statement to its eventual control father.
      control_domain, gen_true, set_control_statement_father,
      NULL);

  free_current_statement_stack();
}


/* Build the mapping from each statement to the statements generating
   something useful for it: */
static void
build_statement_to_statement_dependence_mapping(graph dependence_graph)
{
  statements_use_def_dependence = hash_table_make(hash_pointer, 0);

  FOREACH(vertex, a_vertex, graph_vertices(dependence_graph))
  {
    statement s1 = vertex_to_statement(a_vertex);

    pips_debug(7, "build_statement_to_statement_dependence_mapping"
        "\tSuccessor list: %p for statement ordering %p\n",
        vertex_successors(a_vertex),
        (void *)dg_vertex_label_statement(vertex_vertex_label(a_vertex)));

    FOREACH(successor, a_successor, vertex_successors(a_vertex))
    {
      vertex v2 = successor_vertex(a_successor);
      statement s2 = vertex_to_statement(v2);
      dg_arc_label an_arc_label = successor_arc_label(a_successor);
      pips_debug(7, "\t%p (%#zx) --> %p (%#zx) with conflicts\n",
          s1, statement_ordering(s1),
          s2, statement_ordering(s2));
      // Try to find at least one of the use-def chains
      // between s and a successor:
      FOREACH(conflict, a_conflict, dg_arc_label_conflicts(an_arc_label))
      {
        statement use, def;

        ifdebug(7)
        {
          fprintf(stderr, "\t\tfrom ");
          print_words(stderr, words_effect(conflict_source(a_conflict)));
          fprintf(stderr, " to ");
          print_words(stderr, words_effect(conflict_sink(a_conflict)));
          fprintf(stderr, "\n");
        }

        // Something is useful for the current statement
        // if it writes something that is used in the current statement:
        if (action_write_p(effect_action(conflict_source(a_conflict)))
            && action_read_p(effect_action(conflict_sink(a_conflict)))) {
          def = s1;
          use = s2;
          // Mark that we will visit the node that defined a
          // source for this statement, if not already visited:
          set statements_set =
              (set) hash_get(statements_use_def_dependence, (void *) use);

          if (statements_set == (set) HASH_UNDEFINED_VALUE) {
            // It is the first dependence we found for s1. Create the set:
            statements_set = set_make(set_pointer);
            hash_put(statements_use_def_dependence,
                (void *) use, (void *) statements_set);
          }

          // Mark the fact that s2 create something useful for s1:
          set_add_element(statements_set, statements_set, (void *) def);

          ifdebug(6)
          fprintf(stderr, "\tUse: statement %p (%#zx). "
              "Def: statement %p (%#zx).\n",
              use, statement_ordering(use),
              def, statement_ordering(def));
          // One use-def is enough for this variable couple:
          break;
        }
      }
    }
  }
}


static void
free_statement_to_statement_dependence_mapping()
{
  HASH_MAP(key, value,
      {
          set_free((set) value);
      },
      statements_use_def_dependence);
}

/* unused */
#if 0 
static void
mark_this_node_and_its_predecessors_in_the_dg_as_useful(set s,
    vertex v)
{
  if (set_belong_p(s, (char *) v))
    /* We have already seen this node: */
    return;

  /* Mark the current vertex as useful: */
  set_add_element(s, s, (char *) v);

  pips_debug(6, "mark_this_node_and_its_predecessors_in_the_dg_as_useful: vertex %p marked, statement ordering (%#x).\n",
      v,
      dg_vertex_label_statement(vertex_vertex_label(v)));

  MAP(SUCCESSOR, a_successor,
      {
          dg_arc_label label = successor_arc_label(a_successor);
          /* Try to find at least one use-def chain: */
          MAP(CONFLICT, a_conflict,
              {
                  /* Something is useful for the current statement if
                    it writes something that is used in the current
                    statement: */
                  if (effect_read_p(conflict_source(a_conflict))
                      && effect_write_p(conflict_sink(a_conflict))) {
                    /* Mark the node that generate something useful
                       for the current statement as useful: */
                    mark_this_node_and_its_predecessors_in_the_dg_as_useful(s,
                        successor_vertex(a_successor));
                    /* Only needed to mark once: */
                    break;
                  }
              },
              dg_arc_label_conflicts(label));
      },
      vertex_successors(v));
}
#endif


static void
iterate_through_the_predecessor_graph(statement s,
    set elements_to_visit)
{
  pips_debug(6, "iterate_through_the_predecessor_graph, statement %p (%#zx).\n",
      s, statement_ordering(s));

  /* Mark the current statement as useful: */
  set_add_element(the_useful_statements, the_useful_statements, (char *) s);

  /* First mark the dependence graph predecessors: */
  {
    set statements_set = (set) hash_get(statements_use_def_dependence,
        (char *) s);
    if (statements_set != (set) HASH_UNDEFINED_VALUE) {
      /* There is at least one statement that generates something
            useful for s: */
      SET_MAP(element,
          {
              statement s2 = (statement) element;

              /* Mark that we will visit the node that defined a
                       source for this statement, if not already
                       visited: */
              set_add_element(elements_to_visit,
                  elements_to_visit,
                  (char *) s2);
              pips_debug(6, "\tstatement %p (%#zx) useful by use-def.\n",
                  s2, statement_ordering(s2));
          },
          statements_set);
    }
  }

  /* Mark the father too for control dependences: */
  if (bound_statement_father_p(s)) {
    statement father = load_statement_father(s);
    set_add_element(elements_to_visit, elements_to_visit, (char *) father);
    pips_debug(6, "\tstatement %p (%#zx) useful as the statement owner.\n",
        father, statement_ordering(father));
  }

  {
    /* And if the statement is in an unstructured, mark all the
         controlling unstructured nodes predecessors as useful, that
         is all the unstructured IF back-reachable. */
    if (bound_control_father_p(s)) {
      list blocks = NIL;
      control control_father = load_control_father(s);
      BACKWARD_CONTROL_MAP(pred, {
          if (gen_length(control_successors(pred)) == 2) {
            /* pred is an unstructured IF that control control_father: */
            set_add_element(elements_to_visit,
                elements_to_visit,
                (char *) control_statement(pred));
            pips_debug(6, "\tstatement unstructed IF %p (%#zx) useful by control dependence.\n",
                control_statement(pred), statement_ordering(control_statement(pred)));
          }
      }, control_father, blocks);
      gen_free_list(blocks);
    }
  }
}


static void
propagate_the_usefulness_through_the_predecessor_graph()
{
  pips_debug(5, "Entering propagate_the_usefulness_through_the_predecessor_graph\n");

  gen_set_closure((void (*)(void *, set)) iterate_through_the_predecessor_graph,
      the_useful_statements);

  pips_debug(5, "Exiting propagate_the_usefulness_through_the_predecessor_graph\n");
}




static bool match_call_to_user_function(call c, bool *user_function_found) {
  const char* match_name = entity_local_name(call_function(c));

  FOREACH(STRING, func, keeped_functions) {
    if(strcmp(match_name,func)==0) {
      *user_function_found = true;
    }
  }

  FOREACH(STRING, func_prefix, keeped_functions_prefix) {
    if(strncmp(match_name,func_prefix,strlen(func_prefix))==0) {
      *user_function_found = true;
    }
  }


  return !user_function_found;
}

static bool statement_call_a_keep_function_p( statement s ) {
  bool user_function_found = false;
  if(statement_call_p(s) || statement_expression_p(s)) {
    gen_context_recurse(s,&user_function_found,call_domain, match_call_to_user_function,gen_true);
  }

  /* FIXME : LOOP header && so one... */

  return user_function_found;
}

/* FI: not only if it is useful, but if it is legal... */
static void use_def_deal_if_useful(statement s) {
  bool this_statement_has_an_io_effect;
  /* When a call by reference is used... */
  bool this_statement_writes_a_procedure_argument;
  bool this_statement_is_a_format;
  bool this_statement_is_an_unstructured_test = false;
  /* FI: any statement that does not have a must/exact continuation
   * should be preserved. For the time being, only exact
   * non-continuing calls are checked: return, exit and abort. Since
   * exceptions are not taken into account, the semantics of the code
   * may be changed.
   *
   * Exact non-continuation can be checked with the statement
   * transformer. beatrice Creusillet has also developped a
   * continuation analysis.
   */
  bool this_statement_is_a_c_return;
  bool outside_effect_p = false;
  bool this_statement_call_a_user_function;

  ifdebug(5) {
    int debugLevel = get_debug_level();
    set_debug_level(0);
    fprintf(stderr, "statement %p (%#zx)\n",
        s, statement_ordering(s));
    print_text(stderr, Text_Statement(get_current_module_entity(), 0, s));
    set_debug_level(debugLevel);
  }

  if (statement_ordering(s) == STATEMENT_ORDERING_UNDEFINED) {
    pips_user_warning("exited since it found a statement without ordering: statement %p (%#x)\n", s, statement_ordering(s));
    return;
  }

  /* The possible reasons to have useful code: */
  /* - the statement does an I/O: */
  this_statement_has_an_io_effect = statement_io_effect_p(s);

  /* - the statement writes a procedure argument or the return
     variable of the function, so the value may be used by another
     procedure: */
  /* Regions out should be more precise: */
  this_statement_writes_a_procedure_argument =
      statement_has_a_formal_argument_write_effect_p(s);

  /* Avoid to remove formats in a first approach: */
  this_statement_is_a_format = instruction_format_p(statement_instruction(s));

  /* Unstructured tests are very hard to deal with since they can
     have major control effects, such as leading to an infinite loop,
     etc. and it is very hard to cope with... Thus, keep all
     unstructured tests in this approach since I cannot prove the
     termination of the program and so on.  */
  if (bound_control_father_p(s)) {
    control control_father = load_control_father(s);
    if (gen_length(control_successors(control_father)) == 2)
      /* It is an unstructured test: keep it: */
      this_statement_is_an_unstructured_test = true;
  }

  /* All statements with control effects such as exit() or abort()
     should be preserved. Continuations should be checked for
     user-defined functions. Exceptions are also a problem. */
  this_statement_is_a_c_return = return_statement_p(s)
        || exit_statement_p(s) || abort_statement_p(s);

  /* Check if this statement write some other things than a local variable */
  list effects_list = load_proper_rw_effects_list(s);
  entity current_func = get_current_module_entity();
  FOREACH(EFFECT, eff,effects_list) {
    reference a_reference = effect_any_reference(eff);
    entity touched = reference_variable(a_reference);
    if(effect_write_p(eff)
        && (!entity_local_variable_p(touched,current_func)
            /* FI: we should also check that the static effect is
               leaked by the function but this is hard to check and is
               usually not intended by the programmer. See
               Transformations/Dead_code_elimination.sub/use_def_elim07/08. */
            || entity_static_variable_p(touched))) {
      outside_effect_p = true;
      pips_debug(7, "Statement %p, outside effect on %s (module %s)\n",
          s,
          entity_name(touched),
          entity_local_name(current_func));
      break;
    }
  }

  this_statement_call_a_user_function = statement_call_a_keep_function_p(s);

  ifdebug(6) {
    pips_debug(6, "Statement %p:\n%s\n Statement number: %" _intFMT "\n", s,
               text_to_string(statement_to_text(s)), statement_number(s));
    if (outside_effect_p)
      pips_debug(6, "Statement %p has an outside effect.\n", s);
    if (this_statement_has_an_io_effect)
      pips_debug(6, "Statement %p has an io effect.\n", s);
    if (this_statement_writes_a_procedure_argument)
      pips_debug(6,"Statement %p writes an argument of its procedure.\n", s);
    if (this_statement_is_a_format)
      pips_debug(6, "Statement %p is a FORMAT.\n", s);
    if (this_statement_is_an_unstructured_test)
      pips_debug(6, "Statement %p is an unstructured test.\n", s);
    if (this_statement_is_a_c_return)
      pips_debug(6, "Statement %p is a C return.\n", s);
  }



  if (this_statement_has_an_io_effect
      || outside_effect_p
      || this_statement_writes_a_procedure_argument
      || this_statement_is_a_format
      || this_statement_is_an_unstructured_test
      || this_statement_is_a_c_return
      || this_statement_call_a_user_function
  )
    /* Mark this statement as useful: */
    set_add_element(the_useful_statements, the_useful_statements, (char *) s);

  pips_debug(5, "end\n");
}


static void remove_this_statement_if_useless(statement s, set entities_to_remove) {
  if (! set_belong_p(the_useful_statements, (char *) s)) {
    pips_debug(6, "remove_this_statement_if_useless removes statement %p (%#zx).\n", s, statement_ordering(s));
    ifdebug(7) {
      print_statement(s);
    }
    // If this is a "declaration statement" keep track of removed declarations
    if(empty_statement_or_continue_p(s)) {
      FOREACH(ENTITY,e, statement_declarations(s)) {
        set_add_element(entities_to_remove,entities_to_remove,e);
      }
    }

    // Get rid of declarations
    gen_free_list(statement_declarations(s));
    statement_declarations(s) = NIL;

    // Free old instruction
    free_instruction(statement_instruction(s));

    // Replace statement with a continue, so that we keep label && comments
    statement_instruction(s) = make_continue_instruction();
  } else {
    // Get rid of removed entity in declarations
    if(statement_declarations(s) != NIL) {
      SET_FOREACH(entity,e,entities_to_remove) {
        pips_debug(5,"Declaration removed for %s\n",entity_name(e));
        gen_remove(&statement_declarations(s),e);
      }
    }
    /*
     *  Let dive into sequence and really remove the statement, it's a lot
     *  cleaner than keeping empty statement when there's not label or comment
     */
    if(statement_block_p(s)) {
      pips_debug(6,"Checking sequence\n");
      list statement_to_remove = NIL;
      FOREACH(statement,st,statement_block(s)) {
        if (! set_belong_p(the_useful_statements, (char *) st)
            && empty_statement_or_continue_without_comment_p(st) ) {
          pips_debug(4,"Register %p to be removed\n",st);
          statement_to_remove = CONS(STATEMENT,st,statement_to_remove);
        }
      }
      FOREACH(statement,st,statement_to_remove) {
        gen_remove_once(&sequence_statements(statement_sequence(s)),st);
      }
      gen_free_list(statement_to_remove);

      // If the sequence is empty now, mark as removable :-)
      if(empty_statement_or_continue_without_comment_p(s)) {
        set_add_element(the_useful_statements,the_useful_statements,s);
      }
    }
  }
  pips_debug(6, "end\n");
  ifdebug(7) {
    print_statement(s);
  }
}


static void
remove_all_the_non_marked_statements(statement s)
{
  pips_debug(5, "Entering remove_all_the_non_marked_statements\n");

  // Keep track of removed entities
  set entities_to_remove = set_make(set_pointer);

  gen_context_recurse(s, entities_to_remove, statement_domain,
      /* Since statements can be nested, only remove in a
                  bottom-up way: */
      gen_true,
      remove_this_statement_if_useless);

  ifdebug(6) {
    SET_FOREACH(entity,e,entities_to_remove) {
      pips_debug(6,"Entity '%s' has been totaly removed\n",entity_name(e));
    }
  }

  set_free(entities_to_remove);

  pips_debug(5, "Exiting remove_all_the_non_marked_statements\n");
}


/**
 * Caution : callees may be changed and should be updated for the module
 * owning this statement !
 */
static void
dead_code_elimination_on_a_statement(statement s)
{
  the_useful_statements = set_make(set_pointer);
  init_control_father();
  init_statement_father();

  ordering_to_dg_mapping = compute_ordering_to_dg_mapping(dependence_graph);

  build_statement_to_statement_father_mapping(s);
  build_statement_to_statement_dependence_mapping(dependence_graph);

  /* Mark as useful the seed statements: */
  gen_recurse(s, statement_domain,
      gen_true,
      use_def_deal_if_useful);

  /* Propagate the usefulness through all the predecessor graph: */
  propagate_the_usefulness_through_the_predecessor_graph();

  remove_all_the_non_marked_statements(s);

  hash_table_free(ordering_to_dg_mapping);
  free_statement_to_statement_dependence_mapping();
  close_statement_father();
  close_control_father();
  set_free(the_useful_statements);
}

static bool non_empty_out_regions_p(statement s)
{
  list l_out = load_statement_out_regions(s);
  list l_out_global = load_statement_out_regions(get_current_module_statement());
  bool main_p = entity_main_module_p(get_current_module_entity());
  bool go_down = true;
  if(s==get_current_module_statement()) {
    if(entity_main_module_p(get_current_module_entity())) {
      // FI: IO's have no impact on the out regions of a main...
      // The OUT regions of a main function are always empty
      set_add_element(the_useful_statements, the_useful_statements, (char *) s);
    }
    else {
      /* We can remove all statements but must preserve at least one
       * return statement, although it is useless, so as not to
       * generate inconsistent C or Fortran code. So, this cannot be
       * done directly...
       */
      set_add_element(the_useful_statements, the_useful_statements, (char *) s);
    }
  }
  else if(declaration_statement_p(s)) {
    // FI: the OUT regions do not take into account all effects
    // all declaration statements are preserved to be conservative
    // Other passes might be able to deal witht them, maybe after a
    // split_initializations pass
    set_add_element(the_useful_statements, the_useful_statements, (char *) s);
  }
  else if(ENDP(l_out)) {
    go_down = false;
  }
  else if((ENDP(l_out_global) && !main_p)) {
    /* FI: this does not work because OUT regions do not let
       distinguish between functions whose returned value is used and
       functions whose returned value is not used; somehow, the return
       value should be taken into account by the region analysis. */
    //go_down = false;
    set_add_element(the_useful_statements, the_useful_statements, (char *) s);
  }
  else {
    /* Mark statement as useful */
    set_add_element(the_useful_statements, the_useful_statements, (char *) s);
  }
  return go_down;
}

/**
 * Caution : callees may be changed and should be updated for the module
 * owning this statement !
 */
static void
dead_code_elimination_on_a_statement_with_out_regions(statement s)
{
  the_useful_statements = set_make(set_pointer);
  init_control_father();
  init_statement_father();

  //ordering_to_dg_mapping = compute_ordering_to_dg_mapping(dependence_graph);

  build_statement_to_statement_father_mapping(s);
  //build_statement_to_statement_dependence_mapping(dependence_graph);

  /* Mark as useful the seed statements: */
  gen_recurse(s, statement_domain,
      gen_true,
      use_def_deal_if_useful);

  /* Propagate the usefulness through all the predecessor graph: */
  // propagate_the_usefulness_through_the_predecessor_graph();
  // all statements with a non empty out region are useful
  gen_recurse(s, statement_domain, non_empty_out_regions_p, gen_null);

  remove_all_the_non_marked_statements(s);

  //hash_table_free(ordering_to_dg_mapping);
  //free_statement_to_statement_dependence_mapping();
  close_statement_father();
  close_control_father();
  set_free(the_useful_statements);
}


bool dead_code_elimination_on_module(char * module_name, bool use_out_regions)
{
  statement module_statement;
  entity module = module_name_to_entity(module_name);

  /*
   * For C code, this pass requires that effects are calculated with property
   * MEMORY_EFFECTS_ONLY set to false because we need that the chains include
   * arcs for declarations as these latter are separate statements now.
   */
  bool memory_effects_only_p = get_bool_property("MEMORY_EFFECTS_ONLY");
  if(c_module_p(module) && memory_effects_only_p && !use_out_regions) {
    pips_user_error("For C code, Dead code elimination should be run with property "
        "MEMORY_EFFECTS_ONLY set to FALSE.\n"
        "For C code, this pass requires that effects are calculated with property"
        " MEMORY_EFFECTS_ONLY set to false because we need that the chains include"
        " arcs for declarations as these latter are separate statements now.\n");
    return false; // return to pass manager with a failure code
  }

  /* Get the true ressource, not a copy. */
  module_statement =
      (statement) db_get_memory_resource(DBR_CODE, module_name, true);

  /* Get the data dependence graph: */
  /* The dg is more precise than the chains, so I (RK) guess I should
      remove more code with the dg, specially with array sections and
      so on. */
  /* FI: it's much too expensive; and how can you gain something
   * with scalar variables?
   */
  /*
   dependence_graph =
      (graph) db_get_memory_resource(DBR_DG, module_name, true);
   */

  if(!use_out_regions) {
    dependence_graph =
        (graph) db_get_memory_resource(DBR_CHAINS, module_name, true);
  }

  /* The proper effect to detect the I/O operations: */
  set_proper_rw_effects((statement_effects)
      db_get_memory_resource(DBR_PROPER_EFFECTS,
          module_name,
          true));
  if(use_out_regions) {
    set_out_effects( (statement_effects)
        db_get_memory_resource(DBR_OUT_REGIONS, module_name, true) );
    set_precondition_map( (statement_mapping)
        db_get_memory_resource(DBR_PRECONDITIONS, module_name, true) );
  }

  set_current_module_statement(module_statement);
  set_current_module_entity(module);

  set_ordering_to_statement(module_statement);

  debug_on("DEAD_CODE_ELIMINATION_DEBUG_LEVEL");
  pips_debug(1, "begin dead_code_elimination\n");
  reset_hooks_register(dead_code_elimination_error_handler);

  /* DEAD_CODE_ELIMINATION_KEEP_FUNCTIONS is a property that can be defined
   * by the user for telling that a space separated list of functions has to
   * be considered as important and we have to keep them
   * Note: it doesn't work with out_regions
   */
  keeped_functions = strsplit(get_string_property("DEAD_CODE_ELIMINATION_KEEP_FUNCTIONS")," ");
  keeped_functions_prefix = strsplit(get_string_property("DEAD_CODE_ELIMINATION_KEEP_FUNCTIONS_PREFIX")," ");

  if(use_out_regions) {
    dead_code_elimination_on_a_statement_with_out_regions(module_statement);
  }
  else
    dead_code_elimination_on_a_statement(module_statement);

  gen_map(free,keeped_functions);gen_free_list(keeped_functions);
  keeped_functions = 0;
  gen_map(free,keeped_functions_prefix);gen_free_list(keeped_functions_prefix);
  keeped_functions_prefix = 0;


  /* Reorder the module, because some statements have been deleted.
      Well, the order on the remaining statements should be the same,
      but by reordering the statements, the number are consecutive. Just
      for pretty print... :-) */
  module_reorder(module_statement);

  pips_debug(2, "done for %s\n", module_name);
  debug_off();

  /* Apply clean declarations ! */
  /*
   * NL: This code are usefull to eliminate:
   *  - when an useless variable is declare with some usefull variable (int usefull, useless;)
   *  - in C, when an useless variable is initialize in the declaration (int useless=0;)
   *  - useless declaration when we use out region for dead_code_elimination
   *    (Transformations/Dead_code_declaratios.sub/use_def_elim10)
   *  - other case?
   */
  debug_on("CLEAN_DECLARATIONS_DEBUG_LEVEL");
  pips_debug(1, "begin clean_declarations\n");

  set_cumulated_rw_effects(
      (statement_effects)db_get_memory_resource(DBR_CUMULATED_EFFECTS,
          module_name,
          true));

  module_clean_declarations(get_current_module_entity(),
      get_current_module_statement());

  pips_debug(1, "end clean_declarations\n");
  debug_off();

  /*
   * If out_regions available
   * also reduce loop bound iteration
   */
  if(use_out_regions) {
    debug_on("LOOP_BOUND_MINIMIZATION_DEBUG_LEVEL");
    pips_debug(1, "begin loop_bound_minimization\n");

    loop_bound_minimization_with_out_regions_on_statement(get_current_module_statement());

    pips_debug(1, "end loop_bound_minimization\n");
    debug_off();
  }


  DB_PUT_MEMORY_RESOURCE(DBR_CODE, module_name, module_statement);

  // We may have removed some function call, thus recompute the callees
  DB_PUT_MEMORY_RESOURCE(DBR_CALLEES, module_name,
      compute_callees(get_current_module_statement()));


  reset_cumulated_rw_effects();
  reset_proper_rw_effects();
  if(use_out_regions) {
    reset_out_effects();
    reset_precondition_map();
  }
  reset_current_module_statement();
  reset_current_module_entity();
  reset_ordering_to_statement();

  reset_hooks_unregister(dead_code_elimination_error_handler);

  /* Should have worked: */
  return true;
}

bool dead_code_elimination(char * module_name)
{
  debug_on("DEAD_CODE_ELIMINATION_DEBUG_LEVEL");
  bool success = dead_code_elimination_on_module(module_name, false);
  debug_off();
  return success;
}

bool dead_code_elimination_with_out_regions(char * module_name)
{
  debug_on("DEAD_CODE_ELIMINATION_DEBUG_LEVEL");
  bool success = dead_code_elimination_on_module(module_name, true);
  debug_off();
  return success;
}

/* Obsolete name: it should be called dead_code_elimination()
 *
 * Maintained for backward compatibility.
 */
bool use_def_elimination(char * module_name)
{
  debug_on("USE_DEF_ELIMINATION_DEBUG_LEVEL");
  pips_user_warning("This phase has been renamed, please use "
      "'dead_code_elimination' from now.\n" );
  bool success = dead_code_elimination_on_module(module_name, false);
  debug_off();
  return success;
}

/**  @} */

/**  @} */

#endif // BUILDER_DEAD_CODE_ELIMINATION*
