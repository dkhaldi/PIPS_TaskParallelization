/*

  $Id: message.c 23066 2016-03-02 09:19:16Z coelho $

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
#endif // HAVE_CONFIG_H

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>

#include "genC.h"
#include "misc.h"

// use real system abort/exit here
#ifdef abort
#undef abort
#endif // abort

#ifdef exit
#undef exit
#endif // exit

/* FC 2015-07-20: yuk, moved out to prevent an include cycle dependency
 * #include "properties.h"
 */
extern bool properties_initialized_p(void);
extern bool get_bool_property(const string);
extern char* get_string_property(const char*);
extern int get_int_property(const string);
extern bool too_many_property_errors_pending_p(void);

/* CATCH/TRY/UNCATCH/THROW stuff is here. */
#include "linear.h"

/**************************************************** CURRENT PIPSMAKE STUFF */

/* pips meta information from pipsmake are made available here...
 * (current phase and module...)
 */
static string current_phase = NULL;
static string current_module = NULL;

void set_pips_current_computation(const char* rname, const char* oname)
{
  pips_assert("no current computation", !current_module && !current_phase);

  current_phase = strdup(rname);
  current_module = strdup(oname);
}

/* Export this piece of information to customize warning functions in passes
 *
 * Passes are also called "phases" in PIPS jargon.
 */
string get_pips_current_pass_name(void)
{
  return current_phase;
}

string get_pips_current_module(void)
{
  return current_module;
}

void reset_pips_current_computation(void)
{
  pips_assert("some current computation", current_module && current_phase);

  free(current_module), current_module = NULL;
  free(current_phase), current_phase = NULL;
}


/********************************************************* META INFORMATIONS */

static string pips_revisions = NULL;
static string pips_date = NULL;
static string pips_cc = NULL;

void set_pips_meta_informations(
  const char * revs,
  const char * date,
  const char * comp)
{
  pips_revisions = (string) revs;
  pips_date = (string) date;
  pips_cc = (string) comp;
}

/************************************************************** USER REQUEST */

/* USER_REQUEST is a function that should be called to request some data
 * from the user. It returns the string typed by the user until the
 * return key is typed.
 * USER_REQUEST should be called as:
 *
 * USER_REQUEST(format [, arg] ... )
 *
 * where format and arg-list are passed as arguments to vprintf.
 */

string default_user_request(const char * fmt, va_list * args)
{
  va_list acpy;
  va_copy(acpy, *args);
  fprintf(stdout, "\nWaiting for your response: ");
  vfprintf(stdout, fmt, acpy);
  fflush(stdout);
  va_end(acpy);
  return safe_readline(stdin);
}

/* default assignment of pips_request_handler is default_user_request. Some
 * top-level (eg. wpips) may need a special user_request proceedure; they
 * should let pips_request_handler point toward it.
 */
string (* pips_request_handler)(const char *, va_list *) = default_user_request;

/* The generic fonction to ask something to the user. Note that if
 * the user cancels his/her request,the empty string "" is returned:
 */
string user_request(const char * a_message_format, ...)
{
  va_list args;
  va_start(args, a_message_format);
  string str = (* pips_request_handler)(a_message_format, &args);
  va_end(args);
  return str;
}

/******************************************************************* LOGFILE */

#define LOG_FILE "Logfile"

/* The log file is closed by default
 */
static FILE * log_file = NULL;

void
close_log_file(void)
{
   if (log_file != NULL && get_bool_property("USER_LOG_P") )
     if (fclose(log_file) != 0)
       pips_internal_error("Could not close log file");
   log_file = NULL;
}

void
open_log_file(const string dir)
{
  if (log_file != NULL)
    close_log_file();

  if (get_bool_property("USER_LOG_P"))
  {
    string log_file_name = strdup(concatenate(dir, "/", LOG_FILE, NULL));

    if ((log_file = fopen(log_file_name, "a")) == NULL) {
	    pips_user_error("Cannot open log file in workspace %s. "
                      "Check access rights.");
    }

    free(log_file_name);
  }
}

void
log_on_file(const char * desc)
{
  pips_log_desc(info_log, NULL, NULL,
                NULL, NULL, -1, NULL, NULL, -1, -1,
                NULL, NULL, (const string) desc);
}

/****************************************************************** USER LOG */

/* USER_LOG is a function that should be called to log the current
 * PIPS request, as soon as it is relevant. loging will occure if property
 * USER_LOG_P is TRUE. USER_LOG should be called as:
 *
 * USER_LOG(format [, arg] ... )
 *
 * where format and arg-list are passed as arguments to vprintf.
 */

/* default assignment of pips_log_handler is default_user_log. Some
 * top-level (eg. wpips) may need a special user_log proceedure; they
 * should let pips_log_handler point toward it.
 *
 * Every procedure pointed to by pips_log_handler must test the property
 * USER_LOG_P; this is necessary because (* pips_log_handler) may be called
 * anywhere (because VARARGS), whithout verifying it.
 */
void (* pips_log_handler)(const char * fmt, va_list * args) = NULL;

static void pips_user_log_alist(const char * format, va_list * args)
{
  pips_log_alist(info_log, NULL, NULL,
                 NULL, NULL, -1, NULL, NULL, -1, -1,
                 NULL, NULL, (const string) format, args);
}

void pips_user_log_func(const char * format, ...)
{
  va_list args;
  va_start(args, format);
  pips_user_log_alist(format, &args);
  va_end(args);
}

// ??? Hmmm... PYPS needs this...
void user_log(const char * format, ...)
{
  va_list args;
  va_start(args, format);
  pips_user_log_alist(format, &args);
  va_end(args);
}

/******************************************************************** THANKS */

#include <unistd.h> // isatty

/* The # "stringificator" only works in a macro expansion... */
#define PIPS_THANKS_STRING(arch)                                        \
  "%s (ARCH=" arch ")\n  running as %s\n"                               \
  "\n"                                                                  \
  "  (c) 1989-2016 MINES ParisTech\n"                                   \
  "                Centre de recherche en informatique.\n"              \
  "\n"                                                                  \
  "  CRI URL: http://www.cri.mines-paristech.fr/\n"                     \
  "  PIPS URL: http://pips4u.org/\n"                                    \
  "  EMAIL: pips-support at cri dot mines-paristech dot fr\n"           \
  "\n"                                                                  \
  "  This software is provided as is, under the terms of the GPL.\n"    \
  "  It includes and uses software from GNU (gnulib, readline),\n"      \
  "  Berkeley (fsplit), INRIA, IRISA and others (polylib, janus)...\n"  \
  "\n"

/* display pips thanks on startup, if it on a tty.
 */
void
pips_thanks(string name, string path)
{
  if (isatty(fileno(stdout)))
  {
    fprintf(stdout, PIPS_THANKS_STRING(STRINGIFY(SOFT_ARCH)), name, path);
    fflush(stdout);
  }
}

/***************************************************************** WARNINGS */

/* USER_WARNING issues a warning and don't stop the program (cf. user_error
 * for infos.)
 */

// Could be in constants.h, naming.h or pipsdbm.h
#define WARNING_FILE_NAME "Warnings"

static FILE * warning_file = NULL;
static string warning_file_name = NULL;

void open_warning_file(const char* dir)
{
  assert(warning_file_name == NULL && warning_file == NULL);
  warning_file_name = strdup(concatenate(dir, "/", WARNING_FILE_NAME, 0));
  warning_file = safe_fopen(warning_file_name, "a");
}

void close_warning_file(void)
{
  if (warning_file)
  {
    safe_fclose(warning_file, warning_file_name);

    warning_file = (FILE*) NULL;
    free(warning_file_name);
    warning_file_name = (string) NULL;
  }
}

/* To be used in error handling functions */
void append_to_warning_file(
  const char * calling_function_name,
  const char * format,
  va_list * args)
{
  if (properties_initialized_p() && get_bool_property("NO_USER_WARNING"))
    return;

  pips_log_alist(warning_log,
                 get_pips_current_pass_name(), get_pips_current_module(),
                 (const string) calling_function_name, NULL, -1,
                 NULL, NULL, -1, -1,
                 NULL, NULL, (const string) format, args);
}

/* default assignment of pips_warning_handler is default_user_warning. Some
 * top-level (eg. wpips) may need a special user_warning proceedure; they
 * should let pips_warning_handler point toward it.
 */
void (* pips_warning_handler)(const char *, const char *, va_list *) = NULL;

void
pips_user_warning_alist(
  const char * function_name,
  const char * funcfile,
  const int funcline,
  const char * format,
  va_list * args)
{
  if (properties_initialized_p() && get_bool_property("NO_USER_WARNING"))
    return;

  pips_log_alist(warning_log,
                 get_pips_current_pass_name(), get_pips_current_module(),
                 (const string) function_name, (const string)funcfile, funcline,
                 NULL, NULL, -1, -1,
                 NULL, NULL, (const string) format, args);
}

void
pips_user_warning_func(
  const char * calling_function_name,
  const char * funcfile,
  const int funcline,
  const char * format,
  ...)
{
  va_list args;
  va_start(args, format);
  pips_user_warning_alist(calling_function_name, funcfile, funcline,
                          format, &args);
  va_end(args);
}

/* fallback version without a calling function name */
void
pips_user_warning_func2(
  const char * format,
  ...)
{
  va_list args;
  va_start(args, format);
  pips_user_warning_alist(pips_unknown_function, NULL, -1, format, &args);
  va_end(args);
}

/******************************************************* PIPS INTERNAL ERROR */

static void _NORETURN_
pips_internal_error_alist(
  const char * funcname,
  const char * funcfile,
  const int funcline,
  const char * format,
  va_list * args)
{
  pips_log_alist(internal_error_log,
                 get_pips_current_pass_name(),
                 get_pips_current_module(),
                 (const string) funcname, (const string) funcfile, funcline,
                 NULL, NULL, -1, -1,
                 NULL, NULL, (const string) format, args);

  // dead code, stopped from pips_log_desc
  abort();
}

void _NORETURN_
pips_internal_error_func(
  const char * funcname,
  const char * funcfile,
  const int funcline,
  const char * fmt,
  ...)
{
  va_list args;
  va_start(args, fmt);
  pips_internal_error_alist(funcname, funcfile, funcline, fmt, &args);
  va_end(args);
}

void _NORETURN_
pips_internal_error_func2(
  const char * format,
  ...)
{
  va_list args;
  va_start(args, format);
  pips_internal_error_alist(pips_unknown_function, "<unknownfile>", 0,
                            format, &args);
  va_end(args);
}

/* PROMPT_USER schould be implemented. (its a warning with consent of the user)
The question is: how schould it be called?
*/

/* USER_ERROR is a function that should be called to terminate the current
   PIPS request execution or to restore the previous saved stack environment
   when an error in a Fortran file or elsewhere is detected.
   USER_ERROR first prints on stderr a description of the error, then tests
   the property ABORT_ON_USER_ERROR and aborts case true. Else it will restore
   the last saved stack environment (ie. come back to the last executed
   setjmp(pips_top_level) ), except for eventuality it has already been
   called. In this case, it terminates execution with exit.
   USER_ERROR should be called as:

   USER_ERROR(fonction, format [, arg] ... )

   where function is a string containing the name of the function
   calling USER_ERROR, and where format and arg-list are passed as
   arguments to vprintf.

   Modifications:

 - user_error() was initially called when a Fortran syntax error was
   encountered by the parser; execution was stopped; this had to be changed
   because different kind of errors can occur and because pips is no longer
   structured using exec(); one has to go back to PIPS top level, in tpips
   or in wpips; (Francois Irigoin, 19 November 1990)
 - user_error() calls (* pips_error_handler) which can either be
   default_user_error or a user_error function specific to the used top-level.
   But each user_error function should have the same functionalities.
*/

/* default assignment of pips_error_handler is default_user_error. Some
 * top-level (eg. wpips) may need a special user_error proceedure; they
 * should let pips_error_handler point toward it.
 */
void (* pips_error_handler)(const char *, const char *, va_list *) = NULL;

static void _NORETURN_
pips_user_error_alist(
  const char * calling_function_name,
  const char * funcfile,
  const int funcline,
  const char * format,
  va_list * args)
{
  pips_log_alist(
    user_error_log,
    get_pips_current_pass_name(),
    get_pips_current_module(),
    (const string) calling_function_name, (const string) funcfile, funcline,
    NULL, NULL, -1, -1,
    NULL, NULL, (const string) format, args);

  // dead code, should not get there...
  abort();
}

void _NORETURN_
pips_user_error_func(
  const char * func_name,
  const char * funcfile,
  const int funcline,
  const char * format,
  ...)
{
  va_list args;
  va_start(args, format);
  pips_user_error_alist(func_name, funcfile, funcline, format, &args);
  va_end(args);
}

void _NORETURN_
pips_user_error_func2(
  const char * format,
  ...)
{
  va_list args;
  va_start(args, format);
  pips_user_error_alist(pips_unknown_function, NULL, -1, format, &args);
  va_end(args);
}

/* PIPS_ERROR is a function that should be called to terminate PIPS
execution when data structures are corrupted. PIPS_ERROR should be
called as:
  PIPS_ERROR(fonction, format [, arg] ... )
where function is a string containing the name of the function
calling PIPS_ERROR, and where format and arg-list are passed as
arguments to vprintf. PIPS_ERROR terminates execution with abort.
*/

void (*pips_internal_error_handler)(const char *, const char *, ...) = NULL;

/************************************************** IRRECOVERABLE USER ERROR */

void _NORETURN_
pips_user_irrecoverable_error_alist(
  const char * func_name,
  const char * funcfile,
  const int funcline,
  const char * format,
  va_list *args)
{
  pips_log_alist(irrecoverable_error_log,
                 get_pips_current_pass_name(),
                 get_pips_current_module(),
                 (const string) func_name, (const string) funcfile, funcline,
                 NULL, NULL, -1, -1,
                 NULL, NULL, (const string) format, args);

  // dead code, stopped in previous call
  exit(1);
}

void _NORETURN_
pips_user_irrecoverable_error_func(
  const char * func_name,
  const char * funcfile,
  const int funcline,
  const char * format,
  ...)
{
  va_list args;
  va_start(args, format);
  pips_user_irrecoverable_error_alist(func_name, funcfile, funcline,
                                      format, &args);
  va_end(args);
}

void _NORETURN_
pips_user_irrecoverable_error_func2(
  const char * format,
  ...)
{
  va_list args;
  va_start(args, format);
  pips_user_irrecoverable_error_alist("UNKNOWN...", NULL, -1, format, &args);
  va_end(args);
}

bool function_same_string_p(const char * s1, const char * s2)
{
  return strcmp(s1, s2) == 0;
}

/******************************************************************* XML LOG */

static FILE * xml_logfile = NULL;
static string xml_logfile_name = NULL;

/*
 * Warning/UserError
 * - (debug) PipsFunction/PipsFile/PipsLine
 * - AppFunction/AppFile/AppLine
 * - Pass
 * - Message
 * - Statement
 * // - Proposition ??
 *
 * vs UserError -> spear_user_error -> pips_user_warning
 *
 * pips_user_error => exception levée
 * -  tpips selon "ABORT_ON_USER_ERROR" => pour spear s'arrêter !
 *
 * pips_internal_error => stderr + abort()
 * - message
 *
 * * InternalError => script
 * - Status/Code?
 *
 * * facultatifs
 */

/* generate xml: attribute="escaped-stuff"
 */
static void append_xml_attribute(
  string_buffer sb,
  const string attribute,
  const string value)
{
  string_buffer_append(sb, attribute);
  string_buffer_append(sb, "=\"");
  if (value && *value)
    string_buffer_append_xml_text(sb, value, true);
  string_buffer_append(sb, "\" ");
}

void open_xml_logfile(const char *filename)
{
  xml_logfile_name = (string) filename;
  xml_logfile = safe_fopen(filename, "w");

  // put version as an XML comment...
  if (!getenv("PIPS_VALIDATION_IN_PROGRESS"))
  {
    string_buffer sb = string_buffer_make(true);
    string_buffer_append(sb, "<!-- pips informations:\n     ");
    append_xml_attribute(sb, "Architecture", STRINGIFY(SOFT_ARCH));
    string_buffer_append(sb, "\n     ");
    append_xml_attribute(sb, "Revisions", pips_revisions);
    string_buffer_append(sb, "\n     ");
    append_xml_attribute(sb, "Date", pips_date);
    string_buffer_append(sb, "\n     ");
    append_xml_attribute(sb, "Compiler", pips_cc);
    string_buffer_append(sb, "\n-->\n");
    string_buffer_to_file(sb, xml_logfile);
    fflush(xml_logfile);
    string_buffer_free(&sb);
  }
}

void close_xml_logfile(void)
{
  if (xml_logfile)
  {
    safe_fclose(xml_logfile, xml_logfile_name);
    xml_logfile = NULL;
    xml_logfile_name = NULL;
  }
}

static void append_xml_line_numbers(
  string_buffer sb,
  const string attribute,
  int val1, int val2)
{
  if (val1 > 0)
  {
    if (val1 < val2)
      string_buffer_printf(sb, "%s=\"%d-%d\" ", attribute, val1, val2);
    else
      string_buffer_printf(sb, "%s=\"%d\" ", attribute, val1);
  }
  else
    string_buffer_printf(sb, "%s=\"\" ", attribute);
}

static string pips_log_xml_tag(pips_log_t tag)
{
  switch (tag) {
  case info_log: return "Info";
  case warning_log: return "Warning";
  case spear_warning_log: return "SpearWarning";
  case spear_error_log: return "SpearError";
  case user_error_log: return "UserError";
  case internal_error_log: return "InternalError";
  case irrecoverable_error_log: return "InternalError";
  default: abort();
  }
}

/* append pips-level stuff (function, file, line) to xml file
 */
static void pips_log_xml_pips_level(
  string_buffer sb,
  const string pips_pass,
  const string pips_owner,
  const string pips_func,
  const string pips_file,
  const int pips_line)
{
  // pips level information
  append_xml_attribute(sb, "Pass", pips_pass);
  append_xml_attribute(sb, "Owner", pips_owner);
  append_xml_attribute(sb, "PipsFunction", pips_func);
  if (pips_file && getenv("PIPS_VALIDATION_IN_PROGRESS"))
  {
    // just show a short version of the file & hide the line
    string short_file = strstr(pips_file, "/src/");
    append_xml_attribute(sb, "PipsFile", short_file? short_file: "...");
    append_xml_attribute(sb, "PipsLine", "...");
  }
  else
  {
    append_xml_attribute(sb, "PipsFile", pips_file);
    append_xml_line_numbers(sb, "PipsLine", pips_line, 0);
  }
}

/* add a full log entry to the xml log file
 */
static void pips_log_xml(
  const pips_log_t tag,
  const string pips_pass,
  const string pips_owner,
  const string pips_func,
  const string pips_file,
  const int pips_line,
  const string user_func,
  const string user_file,
  const int user_line,
  const int user_line2,
  const string stmt,
  const string suggestion,
  const string description)
{
  // only tag warnings & above...
  if (tag == info_log) return;

  assert(xml_logfile != NULL);

  // build XML in a string buffer
  string_buffer sb = string_buffer_make(true);
  string field = pips_log_xml_tag(tag);

  string_buffer_cat(sb, "<", field, ">\n  <Description ", NULL);
  // user level information
  append_xml_attribute(sb, "AppFunction", user_func);
  append_xml_attribute(sb, "AppFile", user_file);
  append_xml_line_numbers(sb, "AppLine", user_line, user_line2);

  pips_log_xml_pips_level(sb, pips_pass, pips_owner,
                          pips_func, pips_file, pips_line);

  if (stmt)
  {
    char * s = stmt;
    while (*s && (*s == '\n' || *s == '\t' || *s == ' ')) s++;
    append_xml_attribute(sb, "Statement", s);
  }
  else
    append_xml_attribute(sb, "Statement", NULL);

  // remove leading spaces for xml
  string desc = description;
  while (desc && *desc && *desc == ' ') desc++;

  append_xml_attribute(sb, "Message", desc);
  append_xml_attribute(sb, "Proposition", suggestion);
  string_buffer_cat(sb, "/>\n</", field, ">\n", NULL);

  string_buffer_to_file(sb, xml_logfile);
  string_buffer_free(& sb);

  fflush(xml_logfile);
}

/***************************************************************** STOP PIPS */

static string code2status(int code)
{
  switch (code)
  {
  case -1:  return "ABORT";
  case 0:   return "OK";
  case 1:   return "INTERNAL_ERROR";
  case TIMEOUT_CODE: return "TIMEOUT";
  default:  return "USER_ERROR";
  }
}

static void pips_stop_xml(
  pips_log_t tag,
  int code,
  const string pips_func,
  const string pips_file,
  const int pips_line,
  const string description)
{
  assert(xml_logfile != NULL);

  string_buffer sb = string_buffer_make(true);
  string_buffer_printf(sb,
                       "<Exit Code=\"%d\" Status=\"%s\" Source=\"%s\">\n",
                       code, code2status(code),
                       code? pips_log_tag_name(tag): "pips");
  string_buffer_append(sb,
                       "  <Description AppFunction=\"\" AppFile=\"\" "
                       "AppLine=\"\" Statement=\"\" Proposition=\"\" ");
  pips_log_xml_pips_level(sb, get_pips_current_pass_name(),
                          get_pips_current_module(),
                          pips_func, pips_file, pips_line);
  append_xml_attribute(sb, "Message", description);
  string_buffer_append(sb, "/>\n</Exit>\n");

  string_buffer_to_file(sb, xml_logfile);
  fflush(xml_logfile);

  string_buffer_free(&sb);
}

static void pips_stop_file(
  FILE * out,
  pips_log_t tag,
  int code,
  const char * pips_func,
  const char * pips_file,
  const int pips_line,
  const string description)
{
  if (code)
  {
    // some error, precise report
    string
      pass = get_pips_current_pass_name(),
      owner = get_pips_current_module();

    if (pass)
      fprintf(out, "%s[%s] ", pass, owner? owner: "<unknown");

    if (pips_func)
      fprintf(out, "(%s) ", pips_func);

    fprintf(out, "[%s] ", pips_log_tag_name(tag));

    fprintf(out, "stopping pips on code %d (%s) ", code, code2status(code));

    // not good for validation, this might move easily... so only on abort
    if (pips_file && code == -1)
      fprintf(out, "at (\"%s\":%d) ", pips_file, pips_line);

    if (description && *description)
    {
      fputs("for ", out);
      fputs(description, out);
    }
    fputs("\n", out);
  }
  else // short output for normal exit(0)
    fprintf(out, "Pips is done: %s\n", description);

  fflush(out);
}

static void _NORETURN_
pips_stop_desc(
  pips_log_t tag,
  int code,
  const string pips_func,
  const string pips_file,
  const int pips_line,
  const string desc)
{
  // trace
  pips_stop_file(stderr, tag, code, pips_func, pips_file, pips_line, desc);

  if (log_file && tag == info_log)
    pips_stop_file(log_file, tag, code, pips_func, pips_file, pips_line, desc);

  if (log_file)
    fclose(log_file);

  if (warning_file && tag >= warning_log)
    pips_stop_file(warning_file,
                   tag, code, pips_func, pips_file, pips_line, desc);

  if (warning_file)
    fclose(warning_file);

  if (xml_logfile)
  {
    pips_stop_xml(tag, code, pips_func, pips_file, pips_line, desc);
    fclose(xml_logfile);
  }

  // do the deed
  if (code < 0)
    abort();
  else
    exit(code);
}

static void _NORETURN_
pips_stop_alist(
  pips_log_t tag,
  int code,
  const string pips_func,
  const string pips_file,
  const int pips_line,
  const string format,
  va_list * args)
{
  string description;
  va_list acpy;
  va_copy(acpy, *args);
  vasprintf(&description, format, acpy);
  va_end(acpy);

  pips_stop_desc(tag, code, pips_func, pips_file, pips_line, description);

  free(description);
}

void _NORETURN_
pips_stop_func(
  // added parameters
  const char * pips_func,
  const char * pips_file,
  const int pips_line,
  // provided arguments
  pips_log_t tag,
  int code,
  const string format,
  ...)
{
  va_list args;
  va_start(args, format);
  pips_stop_alist(tag, code,
                  (const string) pips_func, (const string) pips_file, pips_line,
                  format, &args);
  va_end(args);
}

void _NORETURN_
pips_stop_func2(
  pips_log_t tag,
  int code,
  const string format,
  ...)
{
  va_list args;
  va_start(args, format);
  pips_stop_alist(tag, code, NULL, NULL, -1, format, &args);
  va_end(args);
}

/******************************************************************* ALL LOG */

string pips_log_tag_name(pips_log_t tag)
{
  switch (tag)
  {
  case none_log: return "none";
  case info_log: return "information";
  case warning_log: return "warning";
  case spear_warning_log: return "spear warning";
  case spear_error_log: return "spear error";
  case user_error_log: return "user error";
  case internal_error_log: return "internal error";
  case irrecoverable_error_log: return "irrecoverable error";
  default: return "<missing tag name>";
  }
}

static void pips_log_file(
  FILE * out,
  const pips_log_t tag,
  const string pips_pass,
  const string pips_owner,
  const string pips_func,
  const string pips_file,
  const int pips_line,
  const string user_func,
  const string user_file,
  const int user_line,
  const int user_line2,
  const string stmt,
  const string suggestion,
  const string description)
{
  // whether to add a new line after line headers
  bool nl = false;

  if (pips_pass) {
    fprintf(out, "%s[%s] ", pips_pass, pips_owner? pips_owner: "?");
  }

  if (pips_func && tag >= warning_log)
    fprintf(out, "(%s) ", pips_func);

  if (tag >= user_error_log)
    fprintf(out, "[%s] ", pips_log_tag_name(tag));

  if (pips_file && tag >= internal_error_log) {
    fprintf(out, "(%s:%d) ", pips_file, pips_line);
    nl = true;
  }

  if (user_func && !pips_owner) {
    fprintf(out, "in function %s ", user_func);
    nl = true;
  }

  if (user_file)
  {
    fprintf(out, "(\"%s\"", user_file);
    if (user_line >= 0)
    {
      fprintf(out, ":%d", user_line);
      if (user_line < user_line2)
        fprintf(out, "-%d", user_line2);
    }
    fputs(") ", out);
    nl = true;
  }
  else
  {
    if (user_line >= 0)
    {
      fprintf(out, "line %d", user_line);
      if (user_line < user_line2)
        fprintf(out, "-%d", user_line2);
      fputs(" ", out);
      nl = true;
    }
  }

  if (nl || stmt) fputc('\n', out);

  if (stmt) {
    string s = stmt;
    while (*s && *s == '\n') s++; // skip leading newlines
    fprintf(out, "at statement:\n\n\t%s\n\n", s);
  }

  if (description) {
    fputs(description, out);
    fputc('\n', out);
  }

  if (suggestion) {
    fputs(suggestion, out);
    fputc('\n', out);
  }

  fflush(out);
}

/* manage "displaying" a log entry, on stderr, in files...
 */
static void pips_log_display(
  const pips_log_t tag,
  const string pips_pass,
  const string pips_owner,
  const string pips_func,
  const string pips_file,
  const int pips_line,
  const string user_func,
  const string user_file,
  const int user_line,
  const int user_line2,
  const string stmt,
  const string suggestion,
  const string desc)
{
  // always show on stderr
  pips_log_file(stderr, tag,
                pips_pass, pips_owner,
                pips_func, pips_file, pips_line,
                user_func, user_file, user_line, user_line2,
                stmt, suggestion, desc);

  // send to logfile if there
  if (log_file && tag == info_log)
    pips_log_file(log_file, tag,
                  pips_pass, pips_owner,
                  pips_func, pips_file, pips_line,
                  user_func, user_file, user_line, user_line2,
                  stmt, suggestion, desc);

  // send to WARNINGS?
  if (warning_file && tag >= warning_log)
    pips_log_file(warning_file, tag,
                  pips_pass, pips_owner,
                  pips_func, pips_file, pips_line,
                  user_func, user_file, user_line, user_line2,
                  stmt, suggestion, desc);

  // XML output
  if (xml_logfile)
    pips_log_xml(tag,
                 pips_pass, pips_owner,
                 pips_func, pips_file, pips_line,
                 user_func, user_file, user_line, user_line2,
                 stmt, suggestion, desc);
}

static int pips_log_recursion_count = 0;

static void pips_log_in_progress(
  const char * pips_func,
  const char * pips_file,
  const int pips_line)
{
  // deep recursion detection, should never get there...
  if (pips_log_recursion_count ++ > 3)
  {
    // hmmm... cannot call pips_log!
    fprintf(stderr, "pips_log recursion (%d) from %s (%s:%d)\n",
            pips_log_recursion_count, pips_func, pips_file, pips_line);
    fflush(stderr);

    if (pips_log_recursion_count > 10)
      pips_stop_func(pips_func, pips_file, pips_line,
                     internal_error_log, -1,
                     "deep pips_log recursion (%d)", pips_log_recursion_count);
  }
}

static void pips_log_done(void)
{
  pips_log_recursion_count --;
}

/* end of log entry (nothing, exception, abort, exit...)
 */
static void pips_log_end(pips_log_t tag)
{
  pips_log_done();

  if (tag <= spear_warning_log)
    return;

  // just in case, flush stuff before stopping?
  fflush(stderr);
  fflush(stdout);
  if (xml_logfile) fflush(xml_logfile);
  if (warning_file) fflush(warning_file);
  if (log_file) fflush(log_file);

  // ??? get_bool_property("CLOSE_WORKSPACE_AND_QUIT_ON_ERROR")

  // handle various stops
  if (tag == internal_error_log)
    pips_stop(tag, -1, "internal error raised");

  if (tag == irrecoverable_error_log)
    pips_stop(tag, 1, "irrecoverable error raised");

  if (tag == user_error_log || tag == spear_error_log)
  {
    if (properties_initialized_p() &&
        get_bool_property("CLOSE_WORKSPACE_AND_QUIT_ON_ERROR"))
      // the close workspace part only works for tpips user error handler
      pips_stop(tag, 2, "CLOSE_WORKSPACE_AND_QUIT_ON_ERROR");

    if (too_many_property_errors_pending_p())
      pips_stop(tag, -1, "too many property errors pending");

    if (properties_initialized_p() &&
        get_bool_property("ABORT_ON_USER_ERROR"))
      pips_stop(tag, -1, "ABORT_ON_USER_ERROR");

    static int user_error_called = 0;

    if (properties_initialized_p() &&
        user_error_called > get_int_property("MAXIMUM_USER_ERROR"))
    {
      pips_stop(user_error_log, 3,
                "over MAXIMUM_USER_ERROR=%d user errors",
                get_int_property("MAXIMUM_USER_ERROR"));
    }

    user_error_called++;

    // throw according to linear exception stack
    // If it is OK there, we should do a reset_property_error()
    THROW(user_exception_error);
  }
}

/* log entry with preprocessed format/arguments
 */
void pips_log_desc(
  const pips_log_t tag,
  const string pips_pass,
  const string pips_owner,
  const string pips_func,
  const string pips_file,
  const int pips_line,
  const string user_func,
  const string user_file,
  const int user_line,
  const int user_line2,
  const string stmt,
  const string suggestion,
  const string description)
{
  pips_log_in_progress(pips_func, pips_file, pips_line);

  pips_log_display(tag, pips_pass, pips_owner,
                   pips_func, pips_file, pips_line,
                   user_func, user_file, user_line, user_line2,
                   stmt, suggestion, description);

  pips_log_end(tag);
}

/* log entry with unprocessed format/alist arguments
 */
void pips_log_alist(
  // what kind of log, somehow a severity information
  const pips_log_t tag,
  // what is going on
  const string pips_pass,
  const string pips_owner,
  // where it comes from (pips)
  const string pips_func,
  const string pips_file,
  const int pips_line,
  // where it comes from (user)
  const string user_func,
  const string user_file,
  const int user_line,
  const int user_line2,
  //const statement stmt,
  const string stmt,
  // what to tell
  const string suggestion,
  const string format,
  va_list * args)
{
  pips_log_in_progress(pips_func, pips_file, pips_line);

  // process issue description once and for all
  string description = NULL;
  va_list acpy;
  va_copy(acpy, *args);
  // BUG: if a timeout is raised while being in malloc, this call is deadlocked
  // as a lock is already held and vasprintf needs to allocate... Also, XML
  // output generation also requires malloc later on...
  vasprintf(&description, format, acpy);
  va_end(acpy);

  // trim leading newlines/tabs and trailing newlines/tabs/spaces
  string desc = description;
  while (*desc && (*desc == '\n' || *desc == '\t' || *desc == '\r'))
    desc ++;
  int last = strlen(desc) - 1;
  while (last >= 0 &&
         (desc[last] == '\n' || desc[last] == '\t' || desc[last] == ' ' ||
          desc[last] == '\r'))
    desc[last--] = '\0';

  // display part
  pips_log_display(tag, pips_pass, pips_owner,
                   pips_func, pips_file, pips_line,
                   user_func, user_file, user_line, user_line2,
                   stmt, suggestion, desc);

  // cleanup
  free(description);

  // (legacy?) alist level callbacks...
  if (tag == info_log && pips_log_handler)
  {
    va_copy(acpy, *args);
    pips_log_handler(format, &acpy);
    va_end(acpy);
  }
  else if ((tag == warning_log || tag == spear_warning_log) &&
           pips_warning_handler)
  {
    va_copy(acpy, *args);
    pips_warning_handler(pips_func, format, &acpy);
    va_end(acpy);
  }
  else if (tag == user_error_log && pips_error_handler)
  {
    va_copy(acpy, *args);
    pips_error_handler(pips_func, format, &acpy);
    va_end(acpy);
  }
  else if (tag == internal_error_log && pips_internal_error_handler)
  {
    va_copy(acpy, *args);
    pips_internal_error_handler(pips_func, format, &acpy);
    va_end(acpy);
  }

  // conclusion (exit, abort, whatever), although it may never be reached...
  pips_log_end(tag);
}

/* direct pips_log call with format and free arguments ("...")
 */
void pips_log_func(
  // where it comes from (pips)
  const string pips_func,
  const string pips_file,
  const int pips_line,
  // what kind of log, somehow a severity information
  const pips_log_t tag,
  // what is going on
  const string pips_pass,
  const string pips_owner,
  // where it comes from (user)
  const string user_func,
  const string user_file,
  const int user_line,
  const int user_line2,
  //const statement stmt,
  const string stmt,
  // what to tell
  const string suggestion,
  const string format,
  ...
  )
{
  va_list args;
  va_start(args, format);
  pips_log_alist(tag,
                 pips_pass, pips_owner,
                 pips_func, pips_file, pips_line,
                 user_func, user_file, user_line, user_line2,
                 stmt, suggestion, format, &args);
  va_end(args);
}

/* quick log and stop, called on timeout
 * this must not invoke malloc as it may still held locks if interrupted
 * this implementation is missing XML escapes...
 */
void pips_log_stop(
  const char * function,
  const char * file,
  const int lineno,
  const pips_log_t tag,
  const int code,
  const string format,
  ...)
{
  // STDERR
  va_list args;
  va_start(args, format);
  fprintf(stderr, "(%s) [%s] stopping pips on code %d (%s) for ",
          function, pips_log_tag_name(tag), code, code2status(code));
  vfprintf(stderr, format, args);
  va_end(args);
  fputs("\n", stderr);
  fflush(stderr);

  // XML
  if (xml_logfile)
  {
    fprintf(xml_logfile,
            "<Exit Code=\"%d\" Status=\"%s\" Source=\"%s\">\n",
            code, code2status(code), pips_log_tag_name(tag));

    string
      pass = get_pips_current_pass_name(),
      module = get_pips_current_module();

    fprintf(xml_logfile,
            "  <Description AppFunction=\"\" AppFile=\"\" "
            "AppLine=\"\" Statement=\"\" Proposition=\"\" "
            "Pass=\"%s\" Owner=\"%s\" PipsFunction=\"%s\" ",
            pass? pass: "", module? module: "", function);

    if (file && getenv("PIPS_VALIDATION_IN_PROGRESS"))
    {
      // just show a short version of the file & hide the line
      string short_file = strstr(file, "/src/");
      fprintf(xml_logfile,
              "PipsFile=\"%s\" PipsLine=\"...\" ",
              short_file? short_file: "...");
    }
    else
    {
      fprintf(xml_logfile, "PipsFile=\"%s\" PipsLine=\"%d\" ", file, lineno);
    }

    fprintf(xml_logfile, "Message=\"");

    va_start(args, format);
    vfprintf(xml_logfile, format, args);
    va_end(args);

    fprintf(xml_logfile, "\" />\n</Exit>\n");
    fflush(xml_logfile);
  }

  exit(code);
}


// void pips_log_func2()

/********************************************************************* UTILS */

#ifdef asprintf
#undef asprintf
#endif // asprintf

#ifdef vasprintf
#undef vasprintf
#endif // vasprintf

int safe_vasprintf(char ** strp, const char * fmt, va_list args)
{
  va_list acpy;
  va_copy(acpy, args);
  int ret = vasprintf(strp, fmt, acpy);
  pips_assert("vasprintf is ok", ret >= 0);
  va_end(acpy);
  return ret;
}

int safe_asprintf(char ** strp, const char * fmt, ...)
{
  va_list args;
  va_start(args, fmt);
  return safe_vasprintf(strp, fmt, args);
  va_end(args);
}
