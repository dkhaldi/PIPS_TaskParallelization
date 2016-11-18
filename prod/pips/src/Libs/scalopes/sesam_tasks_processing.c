/*

  $Id: sesam_tasks_processing.c 23065 2016-03-02 09:05:50Z coelho $

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
#include <string.h>

#include "genC.h"

#include "linear.h"
#include "ri.h"
#include "effects.h"
#include "database.h"

#include "misc.h"
#include "ri-util.h"
#include "effects-util.h"
#include "constants.h"
#include "misc.h"
#include "text-util.h"
#include "text.h"
#include "control.h"

#include "properties.h"

#include "pipsdbm.h"
#include "resources.h"

#include "effects-generic.h"
#include "effects-simple.h"

#include "scalopes_private.h"

/**
   @brief returns true if the input label entity name is
   prefixed by SCALOPES_KERNEL_TASK_PREFIX
 */
static bool sesam_task_label_p(entity e)
{
  const char * prefix = get_string_property ("SCALOPES_KERNEL_TASK_PREFIX");
  const char * e_name = entity_user_name(e);
  char * found_s = strstr(e_name, prefix);
  return found_s != NULL;
}

/**
   @brief initalizes the object describing how the targeted sesam application uses buffers
   all sets and hash tables are emtpy at the beginning.
 */
static void sbp_context_init(sesam_buffers_processing_context * sbp_context)
{
  *sbp_context =
    make_sesam_buffers_processing_context(set_make(set_pointer),
					  set_make(set_pointer),
					  make_entity_task_buffers(),
					  make_entity_task_buffers(),
					  set_make(set_pointer));
}

/**
   @brief retrieves the original entity from an entity generated by isolate_statement
 */
static entity sesam_buffer_to_server_entity(entity buffer)
{
  const char* prefix =  get_string_property ("ISOLATE_STATEMENT_VAR_PREFIX");
  size_t prefix_size =  strlen(prefix);
  const char* suffix =  get_string_property ("ISOLATE_STATEMENT_VAR_SUFFIX");


  const char * buffer_name = entity_user_name(buffer);

  pips_debug(5, "looking for %s server variable name\n", buffer_name);

  ifdebug(5){
    pips_assert("the input entity is a sesam_buffer var",
		strstr(buffer_name, prefix)!=NULL);
  }

  const char * name_without_prefix = &buffer_name[prefix_size];
  pips_debug(5, "name_without_prefix is %s\n", name_without_prefix);
  size_t s_without_prefix = strlen(name_without_prefix);

  string found_suffix = strstr(name_without_prefix, suffix);
  pips_debug(5, "found_suffix is %s\n", found_suffix);

  size_t s_name_end = strlen(found_suffix);

  size_t size_var_name = s_without_prefix - s_name_end;
  pips_debug(5, "s_without_prefix = %zd\n", s_without_prefix);
  pips_debug(5, "s_name_end = %zd\n", s_name_end);
  pips_debug(5, "size_var_name = %zd\n", size_var_name);

  char *res_name = strndup(name_without_prefix, size_var_name);

  pips_debug(5, "found server variable name: %s\n", res_name);
  entity res = FindEntityFromUserName(get_current_module_name(), res_name); /* try to find it in the current module*/
  if (entity_undefined_p(res))
    res = FindEntity(TOP_LEVEL_MODULE_NAME, res_name); /* try to find a global variable */
  free(res_name);
  pips_assert("Original entity found in current module or in global variables", !entity_undefined_p(res));
  return res;
}

/**
   @brief returns true if the entity name is prefixed by ISOLATE_STATEMENT_VAR_PREFIX.
 */
static bool entity_sesam_buffer_p(entity e)
{
  const char* prefix =  get_string_property("ISOLATE_STATEMENT_VAR_PREFIX");
  pips_debug(8, "prefix = %s \n", prefix);

  const char * e_name = entity_user_name(e);
  pips_debug(5, "checking entity %s\n", e_name);

  char * found_s = strstr(e_name, prefix);

  return (found_s != NULL);
}

/**
   @brief updates sbp_context knowing that buffer will be a buffer
   (input if in_p is true, output otherwise) of kernel task k_task

   @param sbp_context is the object describing how the targeted sesam application uses buffers
   @param k_task is the kernel task label, used here as an identifier
   @param buffer is the pointer to the buffer, used here as an identifier
   @param in_p is a bool true if the buffer is an input buffer of the task

   This function:
      - adds the buffer to sbp_context set of buffers
      - adds the original variable server task to sbp_context set of server tasks
      - adds the task to sbp_context set of kernel tasks
      - adds the buffer to the input (resp. ouput) set of buffers of kernel task k_task.
      - adds the buffer to the output (resp. input) set of buffers of the server task.

   This is an unoptimized version: servers are systematically used for original variables.

 */
static void sbp_context_add_kernel_task_buffer(sesam_buffers_processing_context * sbp_context,
					       entity k_task,
					       entity buffer,
					       bool in_p)
{
  /* first add the buffer to the set of buffers */
  sesam_buffers_processing_context_buffers(*sbp_context) =
    set_add_element(sesam_buffers_processing_context_buffers(*sbp_context),
		 sesam_buffers_processing_context_buffers(*sbp_context),
		 buffer);

  /* Then add it in the task input (resp. ouput) buffers
     if in_p is true (resp. false) */
  /* if the task has not yet been encountered,
     then add an entry in the kernel task set and buffers first */
  sesam_buffers_processing_context_kernel_tasks(*sbp_context) =
    set_add_element(sesam_buffers_processing_context_kernel_tasks(*sbp_context),
		    sesam_buffers_processing_context_kernel_tasks(*sbp_context),
		    k_task);
  entity_task_buffers k_buf = sesam_buffers_processing_context_kernel_buffers(*sbp_context);
  if (!bound_entity_task_buffers_p(k_buf, k_task))
    extend_entity_task_buffers(k_buf, k_task,
			       make_task_buffers(set_make(set_pointer),
						 set_make(set_pointer)));

  task_buffers t_buf =  apply_entity_task_buffers(k_buf, k_task);

  if (in_p)
    task_buffers_input(t_buf) = set_add_element(task_buffers_input(t_buf),
					     task_buffers_input(t_buf),
					     buffer);
  else
    task_buffers_output(t_buf) = set_add_element(task_buffers_output(t_buf),
					     task_buffers_output(t_buf),
					     buffer);

  /* Finally, retrieve the original variable corresponding to the buffer
     and add it in the server task ouput (resp. input) buffers
     if in_p is true (resp. false).*/
  /* if the server task has not yet been encountered,
     then add an entry in the server task sets and buffers first */

  entity s_task = sesam_buffer_to_server_entity(buffer);
  sesam_buffers_processing_context_server_tasks(*sbp_context) =
    set_add_element(sesam_buffers_processing_context_server_tasks(*sbp_context),
		    sesam_buffers_processing_context_server_tasks(*sbp_context),
		    s_task);
  entity_task_buffers s_buf
    = sesam_buffers_processing_context_server_buffers(*sbp_context);

  if (!bound_entity_task_buffers_p(s_buf, s_task))
    extend_entity_task_buffers(s_buf, s_task,
			       make_task_buffers(set_make(set_pointer),
						 set_make(set_pointer)));

  t_buf =  apply_entity_task_buffers(s_buf, s_task);

  if (!in_p)
    task_buffers_input(t_buf) = set_add_element(task_buffers_input(t_buf),
					     task_buffers_input(t_buf),
					     buffer);
  else
    task_buffers_output(t_buf) = set_add_element(task_buffers_output(t_buf),
					     task_buffers_output(t_buf),
					     buffer);
}

/**
   @brief update the object describing how the targeted sesam application uses buffers
   with the current statement characteristics
 */
static bool update_sesam_tasks_buffers(statement stmt,
              sesam_buffers_processing_context * sbp_context)
{
  bool res = true; // by default, stmt is not a sesam task
  entity stmt_label = statement_label(stmt);

  if (sesam_task_label_p(stmt_label)) // stmt is a sesam task statement
    {
      pips_debug(1, "considering task with label %s\n", entity_user_name(stmt_label));

      list l_eff = load_cumulated_rw_effects_list(stmt);

      FOREACH(EFFECT, eff, l_eff)
	{
	  reference r = effect_any_reference(eff);
	  entity e = effect_entity(eff);
	  pips_debug(5, "considering entity %s\n", entity_name(e));
	  pips_debug_effect(5, "and effect:", eff);

	  /* isolate_statement generates pointers to the actual buffers.
	     do not consider effects on them, but only on the buffers
	     themselves */
	  if (entity_sesam_buffer_p(e) && !ENDP(reference_indices(r)))
	    {
	      pips_debug(5, "adding entity to buffers\n");
	      sbp_context_add_kernel_task_buffer(sbp_context,
						 stmt_label,
						 e,
						 effect_read_p(eff));
	    }
	}
      res = false; // do not go further, nested tasks are not yet allowed
    }
  return(res);
}

/**
 @brief prettyprints in input file how each task uses the buffers

 @param fp is the File pointer
 @param tasks_to_buffers is the hash table giving the input and output buffers of each task
 @param l_buffers is an ordered list of buffers
 @param task_prefix is a string appended before the task names

  Then for each task: (sorted before)
        print #ifdef "task_prefix""task_name"
        for each buffer in l_buffers
            if buffer belongs to task input buffers
               print #define buffer_cons_p 1
            else
	       print #define buffer_cons_p 0
            if buffer belongs to task output buffers
               print #define buffer_prod_p 1
            else
	       print #define buffer_prod_p 0
        print #endif
   */
static void print_entity_task_buffers(FILE *fp, set tasks,
				      entity_task_buffers tasks_to_buffers,
				      list l_buffers,
				      const char * task_prefix)
{
  list l_tasks = set_to_sorted_list(tasks, (gen_cmp_func_t) compare_entities);

  FOREACH(ENTITY, task, l_tasks)
    {
      const char * task_name = entity_user_name(task);
      fprintf(fp, "\n%s%s%s\n", "#ifdef ", task_prefix, task_name);
      fprintf(fp, "#define %s%s_p 1\n", task_prefix, task_name);
      task_buffers bufs = apply_entity_task_buffers(tasks_to_buffers, task);
      set input_bufs = task_buffers_input(bufs);
      set output_bufs = task_buffers_output(bufs);

      FOREACH(ENTITY, buf, l_buffers)
	{
	  if (set_belong_p(input_bufs, buf))
	    fprintf(fp, "%s %s%s\n", "#define", entity_user_name(buf), "_cons_p 1");
	  else
	    fprintf(fp, "%s %s%s\n", "#define", entity_user_name(buf), "_cons_p 0");
	  if (set_belong_p(output_bufs, buf))
	    fprintf(fp, "%s %s%s\n", "#define", entity_user_name(buf), "_prod_p 1");
	  else
	    fprintf(fp, "%s %s%s\n", "#define", entity_user_name(buf), "_prod_p 0");

	}
      fprintf(fp, "#else\n");
      fprintf(fp, "#define %s%s_p 0\n", task_prefix, task_name);
      fprintf(fp, "%s\n", "#endif");
    }
  gen_free_list(l_tasks);
}

/**
   @brief prints a header file describing how the targeted sesam application uses buffers
   @param module_name is the current module name
   @param sbp_context is the object describing how the targeted sesam application uses buffers
 */
static void print_sesam_tasks_buffers_header(const char* module_name,
            sesam_buffers_processing_context sbp_context)
{
  string buffers_header_name = NULL;
  string local_buffers_header_name = NULL;
  FILE *fp;
  local_buffers_header_name =
    db_build_file_resource_name(DBR_SESAM_BUFFERS_FILE,
				module_name, "_buffers.h");
  buffers_header_name =
    strdup(concatenate(db_get_current_workspace_directory(),
		       "/", local_buffers_header_name, NULL));
  fp = safe_fopen(buffers_header_name, "w");


  /* first sort buffers list so that buffers are always
     printed in the same order */
  set buffers = sesam_buffers_processing_context_buffers(sbp_context);
  list l_buffers = set_to_sorted_list(buffers,
				      (gen_cmp_func_t) compare_entities);

  fprintf(fp, "%s%d\n", "#define NB_BUFFERS ",
	  (int) gen_length(l_buffers));
  /* Then generate buffer identifiers values: */
  /* for each buffer in buffer list
         print #define buffer value
         value ++
   */
  int buf_id = 0;
  FOREACH(ENTITY, buf, l_buffers)
    {
      fprintf(fp, "%s%s%s%s\n","#define ", entity_user_name(buf),
	      "_id ", int2a(buf_id));
      buf_id++;
    }

  /* Then for each kernel task: (sorted before)
        print #ifdef task_name
        for each buffer in buffer list
            if buffer belongs to task input buffers
               print #define buffer_cons_p 1
            else
	       print #define buffer_cons_p 0
            if buffer belongs to task output buffers
               print #define buffer_prod_p 1
            else
	       print #define buffer_prod_p 0
        print #endif
   */
  set kernel_tasks = sesam_buffers_processing_context_kernel_tasks(sbp_context);
  entity_task_buffers kernel_buffers
    = sesam_buffers_processing_context_kernel_buffers(sbp_context);
  print_entity_task_buffers(fp, kernel_tasks, kernel_buffers, l_buffers, "");

  /* Then do the same for server tasks */
  set server_tasks = sesam_buffers_processing_context_server_tasks(sbp_context);
  entity_task_buffers server_buffers
    = sesam_buffers_processing_context_server_buffers(sbp_context);
  print_entity_task_buffers(fp, server_tasks, server_buffers, l_buffers,
			    get_string_property ("SCALOPES_SERVER_TASK_PREFIX"));

  safe_fclose(fp, buffers_header_name);
  free(buffers_header_name);
  gen_free_list(l_buffers);

  char * server_file_name =
    strdup(concatenate(db_get_current_workspace_directory(),
		       "/", module_name, "/", module_name, ".servers", NULL));
  fp = safe_fopen(server_file_name, "w");

  list l_server_tasks = set_to_sorted_list(server_tasks, (gen_cmp_func_t) compare_entities);
  const char* prefix = get_string_property ("SCALOPES_SERVER_TASK_PREFIX");
  FOREACH(ENTITY, server_task, l_server_tasks)
    {
      fprintf(fp, "%s%s\n", prefix, entity_user_name(server_task));
    }
  gen_free_list(l_server_tasks);
  safe_fclose(fp, server_file_name);
  free(server_file_name);

  DB_PUT_FILE_RESOURCE(DBR_SESAM_BUFFERS_FILE, strdup(module_name),
		       local_buffers_header_name);
}

/**
   @brief PIPS phase that takes a module transformed by isolated statements
   and produces a header file describing buffer usage for targeted sesam application.

   @param module_name is the current module name
 */
bool sesam_buffers_processing(const char* module_name)
{
  // Use this module name and this environment variable to set
  statement module_statement = PIPS_PHASE_PRELUDE(module_name,
						  "SCALOPES_DEBUG_LEVEL");
  sesam_buffers_processing_context sbp_context
    = sesam_buffers_processing_context_undefined;

  sbp_context_init(&sbp_context);

  // use cumulated effects for the moment, regions can be used later if need be
  set_cumulated_rw_effects((statement_effects)
			   db_get_memory_resource(DBR_CUMULATED_EFFECTS, module_name, true));

  set_methods_for_rw_effects_prettyprint(module_name);
  gen_context_recurse(module_statement, &sbp_context,
		      statement_domain, update_sesam_tasks_buffers, gen_identity);
  reset_methods_for_effects_prettyprint(module_name);
  print_sesam_tasks_buffers_header(module_name, sbp_context);

  reset_cumulated_rw_effects();

  free_sesam_buffers_processing_context(sbp_context);
  // Put back the new statement module
  PIPS_PHASE_POSTLUDE(module_statement);

  return (true);
}

bool sesam_servers_processing(const char* module_name)
{
  // Use this module name and this environment variable to set
  statement module_statement = PIPS_PHASE_PRELUDE(module_name,
						  "SCALOPES_DEBUG_LEVEL");

  // Put back the new statement module
  PIPS_PHASE_POSTLUDE(module_statement);

  return (true);
}