/*

  $Id: pipsmake.c 23166 2016-08-28 15:26:02Z coelho $

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
/*
 * pipsmake: call by need (make),
 * rule selection (activate),
 * explicit call (apply/capply)
 *
 * Remi Triolet, Francois Irigoin, Pierre Jouvelot, Bruno Baron,
 * Arnauld Leservot, Guillaume Oget, Fabien Coelho.
 *
 * Notes:
 *  - pismake uses some RI fields explicitly
 *  - see Bruno Baron's DEA thesis for more details
 *  - do not forget the difference between *virtual* resources like
 *    CALLERS.CODE and *real* resources like FOO.CODE; CALLERS is a
 *    variable (or a function) whose value depends on the current module;
 *    it is expanded into a list of real resources;
 *    the variables are CALLEES, CALLERS, ALL and MODULE (the current module
 *    itself);
 *    these variables are used to implement top-down and bottom-up traversals
 *    of the call tree; they make pipsmake different from
 *
 *  - memoization added to make() to speed-up a sequence of interprocedural
 *  requests on real applications; a resource r is up-to-date if it already
 *  has been
 *  proved up-to-date, or if all its arguments have been proved up-to-date and
 *  all its arguments are in the database and all its arguments are
 *  older than the requested resource r; this scheme is correct as soon as
 *  activate()
 *  destroys the resources produced by the activated (and de-activated) rule
 *  - include of an automatically generated builder_map
 *  - explicit *recursive* destruction of obsolete resources by
 *  activate() but not by apply(); beware! You cannot assume that all
 *  resources in the database are consistent;
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

#include "genC.h"

#include "linear.h"
#include "ri.h"
#include "constants.h"

#include "misc.h"

#include "ri-util.h"
#include "pipsdbm.h"
#include "workspace-util.h"
#include "resources.h"
#include "phases.h"
#include "properties.h"
#include "pips-libs.h"

#include "pipsmake.h"

// static generated table with all passes
#include "builder_map.h"

void set_current_phase_context(const char* rname, const char* oname)
{
  set_pips_current_computation(rname, oname);
  entity_basic_concrete_types_init();
  reset_std_static_entities();
}

void reset_current_phase_context(void)
{
  reset_pips_current_computation();
  entity_basic_concrete_types_reset();
  reset_std_static_entities();
}

/* call builder to build a resource for something.
 * handle possible exceptions while doing so.
 */
static bool catch_user_error(builder_func_t builder,
                             const char* rname, const char* oname)
{
  volatile bool success = false;

  // warn once if inconsistent gmp requirement
  // probably this could be moved elsewhere.
  // this is checked over and over again because environment variable
  // may be changed from a tpips script...
  static bool warned_about_gmp_inconsistent_requirement = false;
  if (!warned_about_gmp_inconsistent_requirement &&
      !linear_with_gmp() && linear_require_gmp())
  {
    pips_user_warning("gmp required but not available\n");
    warned_about_gmp_inconsistent_requirement = true;
  }

  set_current_phase_context(rname, oname);
  linear_reset_error_counters();

  _int db = get_debug_stack_pointer();

  CATCH(any_exception_error)
  {
    reset_static_phase_variables();
    success = false;
    set_debug_stack_pointer(db);

    if (the_last_just_thrown_exception == timeout_error)
      RETHROW();
  }
  TRY
  {
    reset_hooks_is_empty();
    success = (*builder)((const string) oname);
    reset_hooks_is_empty();
    UNCATCH(any_exception_error);
  }

  if (!success)
    pips_user_warning("pass has failed\n");

  if (linear_error_count())
  {
    unsigned int oe, se, me;
    linear_get_error_counts(&oe, &se, &me);
    if (oe || se)
      pips_user_warning("linear errors: overflow=%u, simplex=%u\n", oe, se);
    if (me)
      pips_user_warning("misc exceptions: %u\n", me);
  }

  reset_current_phase_context();

  return success;
}

static builder_func_t get_builder(const char* name)
{
  struct builder_map * pbm;
  for (pbm = builder_maps; pbm->builder_name; pbm++)
    if (same_string_p(pbm->builder_name, name))
	    return pbm->builder_func;
  pips_internal_error("no builder for %s", name);
  return NULL;
}

/*********************************************** UP TO DATE RESOURCES CACHE */

/* FI: pipsmmake is very slow when interprocedural analyzes have been selected;
 * some memoization has been added; we need to distinguish betweeen an
 * external make which initializes a set of up-to-date resources and
 * an internal recursive make which updates and exploits that set.
 *
 * This new functionality is extremely useful when old databases
 * are re-opened.
 *
 * apply(), which calls make() many times, does not fully benefit from
 * this memoization scheme.
 *
 * What is cached? a resource id, i.e. a db_resource, i.e. an object
 * hidden in pipsdbm_private...
 */
static set up_to_date_resources = set_undefined;

void reset_make_cache(void)
{
  pips_debug(8, "The up-to-date resource cache is reset\n");
  pips_assert("set is defined", !set_undefined_p(up_to_date_resources));
  set_free(up_to_date_resources);
  up_to_date_resources = set_undefined;
}

void init_make_cache(void)
{
  pips_debug(8, "The up-to-date resource cache is initialized to empty\n");
  pips_assert("not set", set_undefined_p(up_to_date_resources));
  up_to_date_resources = set_make(set_pointer);
}

/* Can the make cache be used? */
bool make_cache_p()
{
  return !set_undefined_p(up_to_date_resources);
}

void reinit_make_cache_if_necessary(void)
{
  if (!set_undefined_p(up_to_date_resources))
    reset_make_cache(), init_make_cache();
}

//bool make_cache_hit_p(real_resource rr)
bool make_cache_hit_p(void * rr_id)
{
  return set_belong_p(up_to_date_resources, rr_id);
}

//void add_resource_to_make_cache(real_resource res)
void add_resource_to_make_cache(void * res_id)
{
  /* FI: debugging messages cannot be factorized here because of
     sibling resources, unless an extra parameter is added... */
  //string res_rn = real_resource_resource_name((real_resource) res);
  //string res_on = real_resource_owner_name((real_resource) res);
  //pips_debug(5, "resource %s(%s) added to up_to_date make cache\n",
  //	     res_rn, res_on);
  set_add_element (up_to_date_resources,
		   up_to_date_resources,
		   res_id);
}

//void remove_resource_from_make_cache(real_resource res)
void remove_resource_from_make_cache(void * res_id)
{
  string res_rn = db_resource_name(res_id);
  string res_on = db_resource_owner_name(res_id);
  pips_debug(5, "resource %s(%s) deleted from up_to_date make cache\n",
             res_rn, res_on);
  set_del_element (up_to_date_resources,
                   up_to_date_resources,
                   res_id);
}

/* Debug function, to be tested... */
void print_make_cache()
{
  if (!set_undefined_p(up_to_date_resources)) {
    int count = 0;
    SET_FOREACH(void *, res_id, up_to_date_resources) {
      string res_rn = db_resource_name(res_id);
      string res_on = db_resource_owner_name(res_id);
      if(string_undefined_p(res_rn) || string_undefined_p(res_on))
        printf("Up-to-date resources/make cache inconsistent with "
               "pipsdbm resources\n");
      else
        printf("Up-to-date resource: \"%s.%s\"\n", res_on, res_rn);
      count++;
    }
    if(count==0)
      printf("No up-to-date resource is cached in make cache\n");
  }
  else
    printf("The up-to-date resource make cache is currently undefined\n");
}

/* Debug function: make sure that up-to-date resources do exist in the
   resource database. If the cache does not exist, it is considered
   consistent. */
bool make_cache_consistent_p()
{
  if (!set_undefined_p(up_to_date_resources)) {
    SET_FOREACH(void *, res_id, up_to_date_resources) {
      string res_rn = db_resource_name(res_id);
      /* FI: the first test should be enough */
      if(string_undefined_p(res_rn))
        return false;
      string res_on = db_resource_owner_name(res_id);
      if(string_undefined_p(res_on))
        return false;
      if(!db_resource_p(res_rn, res_on))
        return false;
    }
  }
  return true;
}

/* Static variables used by phases must be reset on error although
   pipsmake does not know which ones are used. */
/* FI: let us hope this is documented in PIPS developer guide... It is
   not mentionned in the PIPS tutorial. And rightly so I believe. It
   should be linked to the exception pips_user_error(). */
void reset_static_phase_variables()
{
#define DECLARE_ERROR_HANDLER(name) extern void name(); name()

    /* From ri-util/static.c */
    DECLARE_ERROR_HANDLER(error_reset_current_module_entity);
    DECLARE_ERROR_HANDLER(error_reset_current_module_statement);

    /* Macro-generated resets */
#ifdef HAVE_PIPS_effects_generic_LIBRARY
    DECLARE_ERROR_HANDLER(error_reset_rw_effects);
    DECLARE_ERROR_HANDLER(error_reset_invariant_rw_effects);
    DECLARE_ERROR_HANDLER(error_reset_proper_rw_effects);
    DECLARE_ERROR_HANDLER(error_reset_cumulated_rw_effects);
    /* Macro-generated resets in effects-generic/utils.c */
    DECLARE_ERROR_HANDLER(proper_effects_error_handler);
#endif // HAVE_PIPS_effects_generic_LIBRARY

#ifdef HAVE_PIPS_transformer_LIBRARY
    DECLARE_ERROR_HANDLER(reset_transformer_map);
#endif // HAVE_PIPS_transformer_LIBRARY

#ifdef HAVE_PIPS_semantics_LIBRARY
    DECLARE_ERROR_HANDLER(reset_precondition_map);
    DECLARE_ERROR_HANDLER(reset_total_precondition_map);
#endif // HAVE_PIPS_semantics_LIBRARY

#undef DECLARE_ERROR_HANDLER

    // call registered reset functions
    reset_hooks_call();
}

/* Apply an instantiated rule with a given ressource owner
 */

/* FI: uncomment if rmake no longer needed in callgraph.c */
/* static bool rmake(string, string); */

#define add_res(vrn, on)                                              \
  result = CONS(REAL_RESOURCE,                                        \
                make_real_resource(strdup(vrn), strdup(on)), result);

/* Translate and expand a list of virtual resources into a potentially
 * much longer list of real resources
 *
 * this is intrinsically a bad idea: if a new module is created as
 * a side effect of some processing, then the dependency on this new module
 * will never appear and cannot be checked for a redo here (see comments
 * of is_owner_all case).
 *
 * In spite of the name, no resource is actually built.
 *
 * FI: the result "result" seems to be always an empty list, NIL, but
 * macro add_res does update "result". Once again, macros improve
 * readability and maintenance.
 */
static list build_real_resources(const char* oname, list lvr)
{
  list pvr, result = NIL;

  for (pvr = lvr; pvr != NIL; pvr = CDR(pvr))
  {
    virtual_resource vr = VIRTUAL_RESOURCE(CAR(pvr));
    string vrn = virtual_resource_name(vr);
    tag vrt = owner_tag(virtual_resource_owner(vr));

    switch (vrt)
    {
	    // FI: should be is_owner_workspace, but changing Newgen decl...
    case is_owner_program:
	    // FI: for  relocation of workspaces
	    add_res(vrn, "");
	    break;

    case is_owner_module:
	    add_res(vrn, oname);
	    break;

    case is_owner_main:
    {
	    int number_of_main = 0;
	    gen_array_t a = db_get_module_list();

	    GEN_ARRAY_FOREACH(string, on, a)
	    {
        if (entity_main_module_p(local_name_to_top_level_entity(on)))
        {
          if (number_of_main)
            pips_internal_error("More than one main");

          number_of_main++;
          pips_debug(8, "Main is %s\n", (string) on);
          add_res(vrn, on);
        }
	    }

	    gen_array_full_free(a);
	    break;
    }
    case is_owner_callees:
    {
	    callees called_modules;
	    list lcallees;

	    if (!rmake(DBR_CALLEES, oname)) {
        // FI: probably missing source code...
        pips_user_error("unable to build callees for %s\n"
                        "Some source code probably is missing!\n",
                        oname);
	    }

	    called_modules = (callees)
        db_get_memory_resource(DBR_CALLEES, oname, true);
	    lcallees = gen_copy_string_list(callees_callees(called_modules));

	    if(!ENDP(lcallees))
	      pips_debug(8, "Callees of %s are:\n", oname);
	    FOREACH(STRING, on, lcallees) {
        pips_debug(8, "\t%s\n", on);
        add_res(vrn, on);
	    }
	    gen_free_string_list(lcallees);

	    break;
    }
    case is_owner_callers:
    {
	    // FI: the keyword callees was badly chosen; anyway,
      // it's just a list of strings... see ri.newgen
	    callees caller_modules;
	    list lcallers;

	    if (!rmake(DBR_CALLERS, oname)) {
        pips_user_error ("unable to build callers for %s\n"
                         "Any missing source code?\n",
                         oname);
	    }

	    caller_modules = (callees)
        db_get_memory_resource(DBR_CALLERS, oname, true);
	    lcallers = gen_copy_string_list(callees_callees(caller_modules));

	    pips_debug(8, "Callers of %s are:\n", oname);

      FOREACH(string, on, lcallers)
      {
        pips_debug(8, "\t%s\n", on);
        add_res(vrn, on);
      }
	    gen_free_string_list(lcallers);
	    break;
    }

    case is_owner_all:
    {
	    // some funny stuff here:
	    // some modules may be added by the phases here...
	    // then we might expect a later coredump if the new resource
	    // is not found.
	    gen_array_t modules = db_get_module_list();

	    GEN_ARRAY_FOREACH(string, on, modules)
      {
        pips_debug(8, "\t%s\n", (string) on);
        add_res(vrn, on);
      }

	    gen_array_full_free(modules);
	    break;
    }

    case is_owner_select:
    {
	    // do nothing ...
	    break;
    }

    case is_owner_compilation_unit:
	  {
	    string compilation_unit_name = compilation_unit_of_module(oname);
	    if(string_undefined_p(compilation_unit_name)) {
        // Source code for module oname is not available
        if(compilation_unit_p(oname))
        {
          // The user can make typos in tpips scripts
          // about compilation unit names.
          pips_user_error("No source code for compilation unit \"%s\"\n."
                          "Compilation units cannot be synthesized.\n",
                          oname);
        }
        pips_user_warning("No source code for module %s.\n", oname);
        // this is a really bad hack !
        // compilation_unit_name = strdup(concatenate(oname, FILE_SEP_STRING, NULL));
      } else {
        add_res(vrn, compilation_unit_name);
        free(compilation_unit_name);
      }
	    break;
	  }

	default:
	    pips_internal_error("unknown tag : %d", vrt);
    }
  }

  return gen_nreverse(result);
}

/* touch the resource if it exits
 * this is currently an experimental and partial implementation
 */
static void preserve_virtual_resource(const char * oname, virtual_resource vr)
{
  switch (owner_tag(virtual_resource_owner(vr)))
  {
  case is_owner_module:
    // touch only available resources
    if (db_resource_p(virtual_resource_name(vr), oname))
      db_touch_resource(virtual_resource_name(vr), oname);
    // ??? we should now touch the transitive closure of dependent resources
    // forall all resources in the database
    //   if it is up to date because the resource is either preserved
    //     or up to date, then touch it, otherwise delete it?
    // the problem is linked to the lazyness of pipsmake which keeps
    // obsolete resources if no one asks about them.
    break;
  case is_owner_program:
  case is_owner_main:
  case is_owner_callees:
  case is_owner_callers:
  case is_owner_all:
  case is_owner_select:
  case is_owner_compilation_unit:
  default:
    pips_internal_error("not implemented");
  }
}

static void update_preserved_resources(const char* oname, rule ru)
{
    list reals;

    /* We increment the logical time (kept by pipsdbm) */
    db_inc_logical_time();

    /* we build the list of modified real_resources */
    reals = build_real_resources(oname, rule_modified(ru));

    /* we delete them from the up-to-date set */
    FOREACH(real_resource, rr, reals)
    {
      string rron = real_resource_owner_name(rr);
      string rrrn = real_resource_resource_name(rr);

      /* is it up to date ? */
      // FI: this piece of code must have never been tested...
      void * rr_id = db_get_resource_id(rrrn, rron);
      if(make_cache_hit_p(rr_id))
      {
        remove_resource_from_make_cache(rr_id);
        /* GO 11/7/95: we need to del the resource from the data base
           for a next call of pipsmake to find it unavailable */
        db_unput_a_resource (rrrn, rron);
      }
    }

    gen_full_free_list (reals);

    /* handle resources that are marked as "preserved", with "="
     */
    FOREACH(virtual_resource, vr, rule_preserved(ru))
      preserve_virtual_resource(oname, vr);

    /* We increment the logical time again... (kept by pipsdbm)
     * this seems necessary??? BC & FC
     */
    db_inc_logical_time();
}

static bool apply_a_rule(const char* oname, rule ru)
{
  static int number_of_applications_of_a_rule = 0;
  static bool checkpoint_workspace_being_done = false;

  double initial_memory_size = 0.;
  string run = rule_phase(ru), rname, rowner;
  bool first_time = true, success_p = true,
    print_timing_p = get_bool_property("LOG_TIMINGS"),
    print_memory_usage_p = get_bool_property("LOG_MEMORY_USAGE"),
    check_res_use_p = get_bool_property("CHECK_RESOURCE_USAGE");
  builder_func_t builder = get_builder(run);
  int frequency = get_int_property("PIPSMAKE_CHECKPOINTS");
  list lrp;

  /* periodically checkpoints the workspace if required.
   */
  number_of_applications_of_a_rule++;

  if (!checkpoint_workspace_being_done &&
      frequency>0 && number_of_applications_of_a_rule>=frequency)
  {
    /* ??? FC 05/04/2002 quick fix because of a recursion loop:
       apply_a_rule -> checkpoint_workspace -> delete_obsolete_resources ->
       check_physical_resource_up_to_date -> build_real_resources -> rmake ->
       apply_a_rule !
       * maybe it would be better treated in checkpoint_workspace?
       */
    checkpoint_workspace_being_done = true;
    checkpoint_workspace();
    checkpoint_workspace_being_done = false;
    number_of_applications_of_a_rule = 0;
  }

  /* output the message somewhere...
   */
  lrp = build_real_resources(oname, rule_produced(ru));
  FOREACH(REAL_RESOURCE, rr, lrp)
  {
    list lr = build_real_resources(oname, rule_required(ru));
    bool is_required = false;
    rname = real_resource_resource_name(rr);
    rowner = real_resource_owner_name(rr);

    FOREACH(REAL_RESOURCE, rrr, lr)
    {
	    if (same_string_p(rname, real_resource_resource_name(rrr)) &&
          same_string_p(rowner, real_resource_owner_name(rrr)))
	    {
        is_required = true;
        break;
	    }
    }

    gen_full_free_list(lr);

    user_log("  %-30.60s %8s   %s(%s)\n",
             first_time == true ? (first_time = false,run) : "",
             is_required == true ? "updating" : "building",
             rname, rowner);
  }

  gen_full_free_list(lrp);

  if (check_res_use_p)
    init_resource_usage_check();

  if (print_timing_p)
    init_log_timers();

  if (print_memory_usage_p)
    initial_memory_size = get_process_gross_heap_size();

  /* DO IT HERE!
   */
  success_p = catch_user_error(builder, run, oname);

  if (print_timing_p)
  {
    string time_with_io,io_time;

    get_string_timers (&time_with_io, &io_time);

    user_log ("                                 time       ");
    user_log (time_with_io);
    user_log ("                                 IO time    ");
    user_log (io_time);
  }

  if (print_memory_usage_p) {
    double final_memory_size = get_process_gross_heap_size();
    user_log("\t\t\t\t memory size %10.3f, increase %10.3f\n",
             final_memory_size,
             final_memory_size-initial_memory_size);
  }

  if (check_res_use_p)
    do_resource_usage_check(oname, ru);

  pips_malloc_debug();

  update_preserved_resources(oname, ru);

  if (run_pipsmake_callback() == false)
    return false;

  if (interrupt_pipsmake_asap_p())
    return false;

  return success_p;
}


/* This function returns the active rule to produce resource rname. It
   selects the first active rule in the database which produces the
   resource but does not use/require it.  */
rule find_rule_by_resource(const char* rname)
{
  makefile m = parse_makefile();

  pips_debug(5, "searching rule for resource %s\n", rname);

  /* walking thru rules */
  FOREACH(RULE, r, makefile_rules(m))
  {
    bool resource_required_p = false;

    /* walking thru resources required by this rule to eliminate rules
       using and producing this resource, e.g. code transformations
       for the CODE resource. */
    FOREACH(VIRTUAL_RESOURCE, vr, rule_required(r))
    {
      string vrn = virtual_resource_name(vr);
      owner vro = virtual_resource_owner(vr);

	    // We do not check callers and callees
	    if ( owner_callers_p(vro) || owner_callees_p(vro) ) {}
	    // Is this resource required ??
	    else if (same_string_p(vrn, rname))
        resource_required_p = true;
    }

    // If this particular resource is not required by the current rule.
    if (!resource_required_p)
    {
      // walking thru resources made by this particular rule
      FOREACH(VIRTUAL_RESOURCE, vr, rule_produced(r))
      {
        string vrn = virtual_resource_name(vr);

        if (same_string_p(vrn, rname)) {

          pips_debug(5, "made by phase %s\n", rule_phase(r));

          // Is this phase an active one ?
          FOREACH(STRING, pps, makefile_active_phases(m))
          {
            if (same_string_p(pps, rule_phase(r))) {
              pips_debug(5, "active phase\n");
              return r;
            }
          }

          pips_debug(5, "inactive phase\n");
        }
      }
    }
  }

  return rule_undefined;
}

/* Always returns a defined rule */
static rule safe_find_rule_by_resource(const char* rname)
{
  rule ru = rule_undefined;

  if ((ru = find_rule_by_resource(rname)) == rule_undefined) {
    /* else */
    pips_internal_error("could not find a rule for %s", rname);
  }

  return ru;
}

static bool make_pre_transformation(const char*, rule);
static bool make_post_transformation(const char*, rule);
static bool make_required(const char*, rule);

/* Apply do NOT activate the rule applied.
 *
 * In the case of an interprocedural rule, the rules applied to the
 * callees of the main will be the default rules. For instance,
 * "apply PRINT_CALL_GRAPH_WITH_TRANSFORMERS" applies the rule
 * PRINT_CALL_GRAPH to all callees of the main, leading to a core
 * dump.
 *
 * Safe apply checks if the rule applied is activated and produces ressources
 * that it requires (no transitive closure) --DB 8/96
 */
static bool apply_without_reseting_up_to_date_resources(
    const char* pname,
    const char* oname)
{
  rule ru;

  pips_debug(2, "apply %s on %s\n", pname, oname);

  // we look for the rule describing this phase
  if ((ru = find_rule_by_phase(pname)) == rule_undefined) {
    pips_user_warning("could not find rule %s\n", pname);
    return false;
  }

  if (!make_pre_transformation(oname, ru))
    return false;

  if (!make_required(oname, ru))
    return false;

  if (!apply_a_rule(oname, ru))
    return false;

  return make_post_transformation(oname, ru);
}


/* compute all pre or post-transformations to apply a rule on an
   object or activate a phase if owner is SELECT. The phase is not
   necessarily a transformation anymore: analyses can be requested as
   well although pipsmake may core dump as a consequence. The select
   clauses are performed first.
 */
static bool make_pre_post_transformation(const char* oname,
                                         rule ru,
                                         list transformations)
{
  list reals;
  bool success_p = true;

  /* we activate the requested rules if any */
  /* FI: apparently, we do not stack up the current active phase and
     we do not restore it once the requesting phase is completed. */
  FOREACH(VIRTUAL_RESOURCE, vr, transformations)
  {
      string vrn = virtual_resource_name(vr);
      owner vro = virtual_resource_owner(vr);

      if (owner_select_p(vro))
      {
        pips_debug(3, "rule %s : selecting phase %s\n",
                   rule_phase(ru), vrn);

        if(!active_phase_p(vrn)) {
          /* FI: activate() is part of the pipsmake API, debug_on() is
             activated, pipsmake.rc is potentially parsed,...  */
          if (activate(vrn) == NULL) {
            success_p = false;
            break;
          }
        }
      }
  }

  if (success_p) {
    /* we build the list of pre or post transformation real_resources */
    reals = build_real_resources(oname, transformations);

    /* we recursively make the resources */
    FOREACH(REAL_RESOURCE, rr, reals) {
      string rron = real_resource_owner_name(rr);
      /* actually the resource name is a phase name !! */
      string rrpn = real_resource_resource_name(rr);

      pips_debug(3, "rule %s : applying %s to %s - recursive call\n",
                 rule_phase(ru), rrpn, rron);

      if (!apply_without_reseting_up_to_date_resources (rrpn, rron))
	      success_p = false; // FI: success_p is not returned

      /* now we must drop the up_to_date cache.
       * maybe not that often? Or one should perform the transforms
       * top-down to avoid recomputations, with ALL...
       */
      reset_make_cache();
      init_make_cache();
    }
  }
  return true; // success_p
}

/* FI: guard added to simplify debugging and to call
   make_pre_post_transformation() only when it is useful. */
static bool make_pre_transformation(const char* oname, rule ru)
{
  bool success_p = true;
  if(!ENDP(rule_pre_transformation(ru)))
    success_p =  make_pre_post_transformation(oname,ru,
					      rule_pre_transformation(ru));
  return success_p;
}

/* FI: guard added to simplify debugging and to call
   make_pre_post_transformation() only when it is useful. */
static bool make_post_transformation(const char* oname, rule ru)
{
  bool success_p = true;
  if(!ENDP(rule_post_transformation(ru))) {
    reset_make_cache();
    init_make_cache();
    success_p = make_pre_post_transformation(oname,ru,rule_post_transformation(ru));
  }
  return success_p;
}

static bool make(const char* rname, const char* oname)
{
  bool success_p = true;

  debug(1, "make", "%s(%s) - requested\n", rname, oname);

  init_make_cache();

  dont_interrupt_pipsmake_asap();
  save_active_phases();
  ifdebug(5)
    db_print_all_required_resources(stderr);

  success_p = rmake(rname, oname);

  reset_make_cache();
  retrieve_active_phases();
  db_clean_all_required_resources();

  pips_debug(1, "%s(%s) - %smade\n",
             rname, oname, success_p? "": "could not be ");

  return success_p;
}

/* recursive make resource. Should be static, but FI uses it in callgraph.c */
bool rmake(const char* rname, const char* oname)
{
  rule ru;
  char * res_id = NULL;

  pips_debug(2, "%s(%s) - requested\n", rname, oname);

  /* is it up to date ? */
  if (db_resource_p(rname, oname))
  {
    res_id = db_get_resource_id(rname, oname);
    if(make_cache_hit_p(res_id))
    {
      pips_debug(5, "resource %s(%s) found up_to_date, time stamp %d\n",
                 rname, oname, db_time_of_resource(rname, oname));
      return true; /* YES, IT IS! */
    }
    else
    {
      /* this resource exists but may be up-to-date? */
      res_id = NULL; /* NO, IT IS NOT. */
    }
  }
  else if (db_resource_is_required_p(rname, oname))
  {
    /* the resource is already being required... this is bad */
    db_print_all_required_resources(stderr);
    pips_user_error("recursion on resource %s of %s\n", rname, oname);
  }
  else
  {
    /* Well, the resource does not exists, we have to build it. */
    db_set_resource_as_required(rname, oname);

    // FC: YUK, this warning should not be here:-(
    /* Let's check  if the proper options have been selected. */
    /* These conditions should not be hardwired here but managed by
       the tpips script language. */
    if(same_string_p(rname, "IN_REGIONS")
       || same_string_p(rname, "OUT_REGIONS")) {
      if (!same_string_p(rule_phase(find_rule_by_resource("REGIONS")),
                         "MUST_REGIONS"))
        pips_user_warning("\nMUST REGIONS not selected - "
                          "Do not expect interesting results.\n");
    }
  }

  /* we look for the active rule to produce this resource */
  if ((ru = find_rule_by_resource(rname)) == rule_undefined)
    pips_internal_error("could not find a rule for %s", rname);

  /* we recursively make the pre transformations. */
  if (!make_pre_transformation(oname, ru))
    return false;

  /* we recursively make required resources. */
  if (!make_required(oname, ru))
    return false;

  if (check_resource_up_to_date (rname, oname))
  {
    pips_debug(8,
               "Resource %s(%s) becomes up-to-date after applying\n"
               "  pre-transformations and building required resources\n",
               rname,oname);
  }
  else
  {
    bool success = false;
    list lr;

    /* we build the resource */
    db_set_resource_as_required(rname, oname);

    success = apply_a_rule(oname, ru);
    if (!success) return false;

    lr = build_real_resources(oname, rule_produced(ru));

    /* set up-to-date all the produced resources for that rule */
    FOREACH(REAL_RESOURCE, rr, lr) {
      string rron = real_resource_owner_name(rr);
      string rrrn = real_resource_resource_name(rr);

      if (db_resource_p(rrrn, rron))
      {
        res_id = db_get_resource_id(rrrn, rron);
        pips_debug(5, "resource %s(%s) added to up_to_date "
                   "with time stamp %d\n",
                   rrrn, rron, db_time_of_resource(rrrn, rron));
        add_resource_to_make_cache(res_id);
      }
      else {
        pips_internal_error("resource %s[%s] just built not found!",
                            rrrn, rron);
      }
    }

    gen_full_free_list(lr);
  }

  /* we recursively make the post transformations. */
  if (!make_post_transformation(oname, ru))
    return false;

  return true;
}


static bool apply(const char* pname, const char* oname)
{
  bool success_p = true;

  pips_debug(1, "%s.%s - requested\n", oname, pname);

  init_make_cache();
  dont_interrupt_pipsmake_asap();
  save_active_phases();

  success_p = apply_without_reseting_up_to_date_resources(pname, oname);

  reset_make_cache();
  retrieve_active_phases();

  pips_debug(1, "%s.%s - done\n", oname, pname);
  return success_p;
}


static bool concurrent_apply(
  const char* pname,       /* phase to be applied */
  gen_array_t modules /* modules that must be computed */)
{
  bool okay = true;
  rule ru = find_rule_by_phase(pname);

  init_make_cache();
  dont_interrupt_pipsmake_asap();
  save_active_phases();

  GEN_ARRAY_FOREACH(string, oname, modules)
  {
    if (!make_pre_transformation(oname, ru)) {
      okay = false;
      break;
    }
  }

  if (okay) {
    GEN_ARRAY_FOREACH(string, oname, modules)
    {
      if (!make_required(oname, ru)) {
        okay = false;
        break;
      }
    }
  }

  if (okay) {
    GEN_ARRAY_FOREACH(string, oname, modules)
    {
      if (!apply_a_rule(oname, ru)) {
        okay = false;
        break;
      }
    }
  }

  if(okay) {
    GEN_ARRAY_FOREACH(string, oname, modules)
    {
      if (!make_post_transformation(oname, ru)) {
        okay = false;
        break;
      }
    }
  }

  reset_make_cache();
  retrieve_active_phases();
  return okay;
}

/* compute all real resources needed to apply a rule "ru" on an object
 * related to owner "oname".
 *
 * Make sure that the first computation of the resources does not
 * require a recomputation either because the number of resources has
 * increased because new modules have been added for call sites to
 * missing library source codes or by the user, or because some
 * resource computation include pre- or post-actions which destroy
 * resources already considered up-to-date.
 *
 * If the processus does not converge with one retry, core dump. The
 * pre- and post-actions (a.k.a. transformations) must be checked for
 * consistency.
 */
static bool make_required(const char* oname, rule ru)
{
  list reals;
  bool success_p = true;

  /* we build the list of required real_resources */
  reals = build_real_resources(oname, rule_required(ru));

  /* we recursively make required resources */
  FOREACH(REAL_RESOURCE, rr, reals) {
    string rron = real_resource_owner_name(rr);
    string rrrn = real_resource_resource_name(rr);

    pips_debug(3, "rule %s : %s(%s) - recursive call\n",
	       rule_phase(ru), rrrn, rron);

    if (!rmake(rrrn, rron)) {
      success_p = false;
      /* Want to free the list ... */
      break;
    }

    /* In french:
       ici nous devons  tester si un des regles modified
       fait partie des required. Dans ce cas on la fabrique
       de suite. */

  }

  /* Two problems may occur: ALL has changed, for instance because
   * some code has been synthesized (issue for PROGAM.PRECONDITION),
   * or one pre-transformation may have destroyed a resource that
   * was available earlier (see Semantics-New/pointer02 with
   * pre-transformations !CALLEES.proper_effects_with_points_to and
   *  !CALLEES.cumulated_effects_with_points_to)
   *
   * In the first case, list "reals" should be recomputed and
   * compared. In the second case, list "reals" should be compared
   * to the content of the make cache. The second test can be
   * performed first. The first test can be made conditional to code
   * synthesis.
   */

  /* Check that all required resources exist and are up-to-date. */
  if(success_p && make_cache_p()) {
    FOREACH(REAL_RESOURCE, rr, reals) {
      string rron = real_resource_owner_name(rr);
      string rrrn = real_resource_resource_name(rr);
      if(db_resource_p(rrrn, rron)) {
        void * rr_id = db_get_resource_id(rrrn, rron);
        /* file resources such as USER_FILEs, which are mostly
           generated by create_worspace, are not inserted as ready in
           the make cache... It it were requested again here, it would
           then be in the cache... FI: no idea why... */
        if(!make_cache_hit_p(rr_id) && strcmp(rrrn, DBR_USER_FILE)!=0) {
          pips_user_warning("Computed resource \"%s.%s\" is not up-to-date"
                            " and must be recomputed\n",
                            rron, rrrn);
          if (!rmake(rrrn, rron)) {
            success_p = false;
            break;
          }
        }
      }
      else {
        if (!rmake(rrrn, rron)) {
          success_p = false;
          break;
        }
      }
    }
  }

  /* We re-build the list of required real_resources in case ALL
     is used and modified because some code has been synthesized. */
  /* FI: In case ALL is updated and some bang rule is used, it would
     be better to fix ALL first. */
  if(success_p
     && (strcmp(get_string_property("PREPROCESSOR_MISSING_FILE_HANDLING"),
                "generate")==0
         || strcmp(get_string_property("PREPROCESSOR_MISSING_FILE_HANDLING"),
                   "query")==0)) {
    list nreals = build_real_resources(oname, rule_required(ru));
    int c = (int) gen_length(reals);
    int nc = (int) gen_length(nreals);
    if(c!=nc) {
      pips_user_warning("More resources are now requested:"
                        " %d instead of %d...\n", nc, c);
      /* The first resources must be removed from the make cache */
      FOREACH(REAL_RESOURCE, rr, reals) {
        string rron = real_resource_owner_name(rr);
        string rrrn = real_resource_resource_name(rr);
        void * rr_id = db_get_resource_id(rrrn, rron);
        remove_resource_from_make_cache(rr_id);
      }
      /* The new resources must be recomputed if necessary */
      FOREACH(REAL_RESOURCE, rr, nreals) {
        string rron = real_resource_owner_name(rr);
        string rrrn = real_resource_resource_name(rr);

        pips_debug(3, "rule %s : %s(%s) - recursive call (retry)\n",
                   rule_phase(ru), rrrn, rron);

        if (!rmake(rrrn, rron)) {
          success_p = false;
          /* Want to free the list ... */
          break;
        }
      }
    }
    gen_full_free_list(nreals); // FI: why junk nreals rather than reals?
  }

  /* ALL should not be a problem anymore, but FI has no idea if
     pre-transformations have to converge in one step... */

  /* Check again that all required resources are up-to-date. */
  /* FI: should be as bugged as the initial previous test. The resource
     existence should be tested before its id is requested. */
  if(success_p && make_cache_p()) {
    FOREACH(REAL_RESOURCE, rr, reals) { // FI: why reals rather than nreals
      string rron = real_resource_owner_name(rr);
      string rrrn = real_resource_resource_name(rr);
      void * rr_id = db_get_resource_id(rrrn, rron);
      /* file resources such as USER_FILE are not cached the first time... */
      if(!make_cache_hit_p(rr_id) && strcmp(rrrn, DBR_USER_FILE)!=0) {
        pips_internal_error("Computed resource \"%s.%s\" is still not"
                            " up-to-date after one recomputation.\n"
                            "The rules involved and their pre- and "
                            "post-actions must be checked",
                            rron, rrrn);
      }
    }
  }

  gen_full_free_list (reals);
  return success_p;
}

/* returns whether resource is up to date.
 */
static bool check_physical_resource_up_to_date(
  const char* rname, const char* oname)
{
  list real_required_resources = NIL;
  list real_modified_resources = NIL;
  rule ru = rule_undefined;
  bool result = true;
  void * res_id = db_get_resource_id(rname, oname);

  /* Maybe is has already been proved true */
  if(make_cache_hit_p(res_id))
    return true;

  /* Initial resources by definition are not associated to a rule.
   * FI: and they always are up-to-date?!? Even if somebody touched the file?
   * You mean you do not propagate modifications performed outside of
   * the workspace?
   */
  if (same_string_p(rname, DBR_USER_FILE))
    return true;

  /* We get the active rule to build this resource */
  ru = safe_find_rule_by_resource(rname);

  /* we build the list of required real_resources */
  /* Here we are sure (thanks to find_rule_by_resource) that the rule does
     not use a resource it produces. FI: OK, this does not rule out
     modified resources which should not be taken into account to avoid
     infinite recursion. */

  real_required_resources = build_real_resources(oname, rule_required(ru));
  real_modified_resources = build_real_resources(oname, rule_modified(ru));

  /* we are going to check if the required resources are
     - in the database or in the rule_modified list
     - proved up to date (recursively)
     - have timestamps older than the tested one
  */
  FOREACH(REAL_RESOURCE, rr, real_required_resources)
  {
    string rron = real_resource_owner_name(rr);
    string rrrn = real_resource_resource_name(rr);

    bool res_in_modified_list_p = false;

    // we build the list of modified real_resources
    FOREACH(REAL_RESOURCE, mod_rr, real_modified_resources)
    {
      string mod_rron = real_resource_owner_name(mod_rr);
      string mod_rrrn = real_resource_resource_name(mod_rr);

      if ((same_string_p(mod_rron, rron)) &&
          (same_string_p(mod_rrrn, rrrn))) {
        // we found it
        res_in_modified_list_p = true;
        pips_debug(3, "resource %s(%s) is in the rule_modified list",
                   rrrn, rron);
        break;
      }
    }

    /* If the resource is in the modified list, then
       don't check anything */
    if (res_in_modified_list_p == false) {
      if (!db_resource_p(rrrn, rron)) {
        pips_debug(5, "resource %s(%s) is not there "
                   "and not in the rule_modified list", rrrn, rron);
        result = false;
        break;
      } else {
        /* Check if this resource is up to date */
        long rest;
        long respt;
        if (check_resource_up_to_date(rrrn, rron) == false) {
          pips_debug(5, "resource %s(%s) is not up to date", rrrn, rron);
          result = false;
          break;
        }
        rest = db_time_of_resource(rname, oname);
        respt = db_time_of_resource(rrrn, rron);
        /* Check if the timestamp is OK */
        if (rest<respt)
        {
          pips_debug(5, "resource %s(%s) with time stamp %ld is newer "
                     "than resource %s(%s) with time stamp %ld\n",
                     rrrn, rron, respt, rname, oname, rest);
          result = false;
          break;
        }
      }
    }
  }

  gen_full_free_list (real_required_resources);
  gen_full_free_list (real_modified_resources);

  /* If the resource is up to date then add it in the set, as well as its
     siblings, if they are produced by the same rule. Think of callgraph
     with may produce literaly thousands of resources, three times the
     number of modules! */
  if (result == true)
  {
      list real_produced_resources =  build_real_resources(oname, rule_produced(ru));
      bool res_found_p = false;

      pips_debug(5, "resource %s(%s) added to up_to_date "
		 "with time stamp %d\n",
		 rname, oname, db_time_of_resource(rname, oname));
      add_resource_to_make_cache(res_id);

      FOREACH(REAL_RESOURCE, rpr, real_produced_resources) {
	string srname = real_resource_resource_name(rpr);
	string soname = real_resource_owner_name(rpr);
	void * sres_id = (void *) db_get_resource_id(srname, soname);
	// real_resource sres_id = db_get_resource_id(srname, soname);

	if(sres_id != res_id) {

	  if(same_string_p(rname, srname)) {
	    /* We would retrieve the same rule and the same required
               resources. rpr is up-to-date.*/

	    pips_debug(5, "sibling resource %s(%s) added to up_to_date "
		       "with time stamp %d\n",
		       srname, soname, db_time_of_resource(srname, soname));
	    add_resource_to_make_cache(sres_id);
	  }
	  else {
	    /* Check that the sibling is currently obtained by the same
               rule, because an activate might preempt it for some of the
               produced resources? */
	    rule sru = find_rule_by_resource(srname);
	    if(sru==ru) {
	      /* The rule does not have to be fired again, so its produced
                 resources are up-to-date. */
	      string soname = real_resource_owner_name(rpr);

	      pips_debug(5, "sibling resource %s(%s) added to up_to_date "
			 "with time stamp %d\n",
			 srname, soname, db_time_of_resource(srname, soname));
	      add_resource_to_make_cache(sres_id);
	    }
	  }
	}
	else {
	  res_found_p = true;
	}
      }

      pips_assert("The resources res is among the real resources produced by rule ru",
		  res_found_p);

      gen_full_free_list (real_produced_resources);
    }
  else
    {
      /* well, if it is not okay, let us delete it!???
       * okay, this might be done later, but in some case it is not.
       * I'm not really sure this is the right fix, but at least it avoids
       * a coredump after touching some internal file (.f_initial) and
       * requesting the PRINTED_FILE for it.
       * FC, 22/07/1998
       *
       * FI: this may be costly and should be avoided on a quit!
       */
      db_delete_resource(rname, oname);
    }

  return result;
}

int delete_obsolete_resources(void)
{
    int ndeleted;
    bool cache_off = !make_cache_p();
    // FI: this test breaks the consistency of init() and reset() for
    // the make cache
    if (cache_off) init_make_cache();
    ndeleted =
	db_delete_obsolete_resources(check_physical_resource_up_to_date);
    if (cache_off) reset_make_cache();
    return ndeleted;
}

/* this is quite ugly, but I wanted to put the enumeration down to pipsdbm.
 */
void delete_some_resources(void)
{
    const char* what = get_string_property("PIPSDBM_RESOURCES_TO_DELETE");
    dont_interrupt_pipsmake_asap();

    user_log("Deletion of %s resources:\n", what);

    if (same_string_p(what, "obsolete"))
    {
	int ndeleted = delete_obsolete_resources();
	if (ndeleted>0) user_log("%d destroyed.\n", ndeleted);
	else user_log("none destroyed.\n");
    } else if (same_string_p(what, "all")) {
	db_delete_all_resources();
	user_log("done.\n");
    } else
	pips_internal_error("unexpected delete request %s", what);
}

/* To be used in a rule. use and update the up_to_dat list
 * created by makeapply
 */
bool check_resource_up_to_date(const char* rname, const char* oname)
{
  return db_resource_p(rname, oname)?
    check_physical_resource_up_to_date(rname, oname): false;
}

/* Delete from up_to_date_resources make cache all the resources with
 * a given resource name. There is no internal data structure in
 * pipsdbm to access these resources efficiently... The two-level
 * mapping of database.c must be inverted.
 *
 * FI: FC claims in an e-mail that this could be done more efficiently
 * but does not explain how.
 */
void delete_named_resources(const char* rn)
{
  pips_assert("make cache is consistent before deletion",
	      make_cache_consistent_p());

  // firstly, clean up the up-to-date cache if it exists
  int count = 0;
  if (make_cache_p()) {
    list rl = db_retrieve_resources(rn);
    FOREACH(STRING, r_id, rl) {
      if (make_cache_hit_p(r_id)) {
        remove_resource_from_make_cache(r_id);
	count++;
      }
    }
    gen_free_list(rl);
  }

  pips_debug(8, "Number of resources no longer considered up-to-date: %d\n",
	     count);

  // Then remove the resource
  // GO 29/6/95: many lines ...  db_unput_resources_verbose (rn);
  int count2 = db_unput_resources(rn);
  pips_assert("The number of resources removed from the cache is smaller "
	      "than the number of resources removed from te database\n",
	      count<=count2);
  pips_assert("make cache is consistent before deletion",
	      make_cache_consistent_p());
}

void delete_all_resources(void)
{
  db_delete_all_resources();
  reset_make_cache();
  init_make_cache();
}

/* Should be able to handle Fortran applications, C applications and
 *  mixed Fortran/C applications.
 *
 * This is a duplicate for pipsdbm function, get_main_entity_name()
 */
string get_first_main_module(void)
{
  string dir_name = db_get_current_workspace_directory();
  string main_name;
  string name = string_undefined;

  debug_on("PIPSMAKE_DEBUG_LEVEL");

  // Let's look for a Fortran main
  main_name = strdup(concatenate(dir_name, "/", MAIN_FILE_NAMES, NULL));

  if (file_exists_p(main_name))
  {
    FILE * tmp_file = safe_fopen(main_name, "r");
    name = safe_readline(tmp_file);
    safe_fclose(tmp_file, main_name);
  }
  free(main_name);

  if(string_undefined_p(name)) {
    // Let's now look for a C main
    main_name = strdup(concatenate(dir_name, "/", MAIN_FILE_NAMES, NULL));
    if (file_exists_p(main_name))
      name = strdup("main");
    free(main_name);
  }

  free(dir_name);
  debug_off();
  return name;
}

/* check the usage of resources
 */
void do_resource_usage_check(const char* oname, rule ru)
{
  list reals;
  set res_read = set_undefined;
  set res_write = set_undefined;

  // Get the dbm sets
  get_logged_resources (&res_read, &res_write);

  // build the real required resrouces
  reals = build_real_resources(oname, rule_required (ru));

  // Delete then from the set of read resources
  FOREACH(real_resource, rr, reals)
  {
    string rron = real_resource_owner_name(rr);
    string rrrn = real_resource_resource_name(rr);
    string elem_name = strdup(concatenate(rron,".", rrrn, NULL));

    if (set_belong_p (res_read, elem_name)){
	    pips_debug (5, "resource %s.%s has been read: ok\n", rron, rrrn);
	    set_del_element(res_read, res_read, elem_name);
    }
    else
	    user_log("resource %s.%s has not been read\n", rron, rrrn);
  }

  // Try to find an illegally read resource ... */
  SET_MAP(re,	user_log("resource %s has been read\n", re), res_read);
  gen_full_free_list(reals);

  // build the real produced resources
  reals = build_real_resources(oname, rule_produced(ru));

  // Delete then from the set of written/generated resources
  FOREACH(real_resource, rr, reals /*res_write*/)
  {
    string rron = real_resource_owner_name(rr);
    string rrrn = real_resource_resource_name(rr);
    string elem_name = strdup(concatenate(rron,".", rrrn, NULL));

    if (set_belong_p (res_write, (void *) elem_name)){
	    pips_debug (5, "resource %s.%s has been written: ok\n", rron, rrrn);
	    set_del_element(res_write, res_write, elem_name);
    }
    else
	    user_log ("resource %s.%s has not been written\n", rron, rrrn);
  }

  // Try to find an illegally written resource ...
  SET_MAP(re, user_log ("resource %s has been written\n", re), res_write);

  gen_full_free_list(reals);

  // not free!
  set_clear(res_read);
  set_clear(res_write);
}


/******************************************************** EXTERNAL INTERFACE */

static double initial_memory_size;

static void logs_on(void)
{
  if (get_bool_property("LOG_TIMINGS"))
    init_request_timers();

  if (get_bool_property("LOG_MEMORY_USAGE"))
    initial_memory_size = get_process_gross_heap_size();
}

static void logs_off(void)
{
  if (get_bool_property("LOG_TIMINGS"))
  {
    string request_time, phase_time, dbm_time;
    get_request_string_timers (&request_time, &phase_time, &dbm_time);

    user_log ("                                 stime      ");
    user_log (request_time);
    user_log ("                                 phase time ");
    user_log (phase_time);
    user_log ("                                 IO stime   ");
    user_log (dbm_time);
  }

  if (get_bool_property("LOG_MEMORY_USAGE"))
  {
    double final_memory_size = get_process_gross_heap_size();
    user_log("\t\t\t\t memory size %10.3f, increase %10.3f\n",
             final_memory_size,
             final_memory_size-initial_memory_size);
  }
}

static bool safe_do_something(
  const char* name,
  const char* module_n,
  const char* what_it_is,
  rule (*find_rule)(const char*),
  bool (*doit)(const char*,const char*))
{
  bool success = false;

  debug_on("PIPSMAKE_DEBUG_LEVEL");

  if (find_rule(name) == rule_undefined)
  {
    pips_user_warning("Unknown %s \"%s\"\n", what_it_is, name);
    success = false;
    debug_off();
    return success;
  }

  _int db = get_debug_stack_pointer();

  CATCH(any_exception_error)
  {
    // global variables that have to be reset after user-error
    reset_make_cache();
    reset_static_phase_variables();
    retrieve_active_phases();
    set_debug_stack_pointer(db);
    pips_user_warning("Request aborted in pipsmake: "
                      "build %s %s for module %s.\n",
                      what_it_is, name, module_n);
    db_clean_all_required_resources();
    success = false;
  }
  TRY
  {
    user_log("Request: build %s %s for module %s.\n",
             what_it_is, name, module_n);
    logs_on();
    pips_malloc_debug();

    // DO IT HERE!
    success = doit(name, module_n);

    if(success)
    {
	    user_log("%s made for %s.\n", name, module_n);
	    logs_off();
    }
    else
    {
	    pips_user_warning("Request aborted under pipsmake: "
                        "build %s %s for module %s.\n",
                        what_it_is, name, module_n);
    }
    UNCATCH(any_exception_error);
  }
  debug_off();
  return success;
}

bool safe_make(const char* res_n, const char* module_n)
{
  return safe_do_something(res_n, module_n, "resource",
                           find_rule_by_resource, make);
}

bool safe_apply(const char* phase_n, const char* module_n)
{
  return safe_do_something(phase_n, module_n, "phase/rule",
                           find_rule_by_phase, apply);
}

bool safe_concurrent_apply(
  const char* phase_n,
  gen_array_t modules)
{
  bool ok = true;
  debug_on("PIPSMAKE_DEBUG_LEVEL");

  // Get a human being representation of the modules:
  string module_list = strdup(string_array_join(modules, ","));

  if (find_rule_by_phase(phase_n)==rule_undefined)
  {
    pips_user_warning("Unknown phase \"%s\"\n", phase_n);
    ok = false;
  }
  else
  {
    CATCH(any_exception_error)
    {
      reset_make_cache();
      retrieve_active_phases();
      pips_user_warning("Request aborted in pipsmake\n");
      ok = false;

      if (the_last_just_thrown_exception == timeout_error)
        RETHROW();
    }
    TRY
    {
      logs_on();
      user_log("Request: capply %s for module [%s].\n", phase_n, module_list);

      ok = concurrent_apply(phase_n, modules);

      if (ok)	{
        user_log("capply %s made for [%s].\n", phase_n, module_list);
        logs_off();
      }
      else {
        pips_user_warning("Request aborted under pipsmake: "
                          "capply %s for module [%s].\n",
                          phase_n, module_list);
      }
      UNCATCH(any_exception_error);
    }
  }

  free(module_list);
  debug_off();
  return ok;
}

bool safe_set_property(const char* propname, const char* value)
{
  size_t len = strlen(propname) + strlen(value) + 2;
  char* line = calloc(len, sizeof(char));
  strcat(line, propname);
  strcat(line, " ");
  strcat(line, value);
  user_log("set %s\n", line);
  parse_properties_string(line, false);
  free(line);
  // parse_properties_string() doesn't return whether it succeeded
  return true;
}

/* Get all the callers of the specified module.
   The returned value is allocated dynamically
   and needs to be freed by the caller of this function
*/
gen_array_t get_callers(string module)
{
  callees caller_modules;

  if (!safe_make(DBR_CALLERS, module))
    pips_internal_error("Cannot make callers for %s", module);

  caller_modules = (callees)
    db_get_memory_resource(DBR_CALLERS, module,true);

  return gen_array_from_list(callees_callees(caller_modules));
}

/* Get all the callers of the specified module.
   The returned value is allocated dynamically
   and needs to be freed by the caller of this function
*/
gen_array_t get_callees(string module)
{
  callees callee_modules;

  if (!safe_make(DBR_CALLEES, module))
    pips_internal_error("Cannot make callees for %s", module);

  callee_modules = (callees)
    db_get_memory_resource(DBR_CALLEES, module,true);

  return gen_array_from_list(callees_callees(callee_modules));
}
