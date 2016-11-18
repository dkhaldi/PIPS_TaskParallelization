/* Warning! Do not modify this file that is automatically generated! */
/* Modify src/Libs/misc/misc-local.h instead, to add your own modifications. */

/* header file built by cproto */

#ifndef  misc_header_included
#define  misc_header_included
/*

  $Id: misc-local.h 23268 2016-11-02 08:57:16Z coelho $

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

#include <stdarg.h>
#include <stdlib.h>
#include <setjmp.h>

// different type of logs...
// pg: debug, log, notice, warning, error, fatal, panic
typedef enum {
  none_log,                // nought
  info_log,                // some information
  warning_log,             // just a warning
  spear_warning_log,
  spear_error_log,
  user_error_log,          // phase is stopped because of user, exception
  internal_error_log,      // phase is stopped because of pips, exception
  irrecoverable_error_log  // phase is stopped because of pips + exit/abort
} pips_log_t;

// logic: 128 + SIGALRM==14 == 142
#define TIMEOUT_CODE (128+14)

/* To generate a string from a macro: */
#define STRINGIFY_SECOND_STAGE(symbol) #symbol
/* If not using this 2-stage macro evaluation, the generated string is not
   the value of the macro but the name of the macro... Who said C was a
   simple language? :-/ */
#define STRINGIFY(symbol) STRINGIFY_SECOND_STAGE(symbol)

// yep, override system abort/exit...
#define abort() pips_stop(internal_error_log, -1, "abort() called")
#define exit(code) pips_stop(user_error_log, code, "exit(%d) called", code)

/* Measurement type for mem_spy.c */
typedef enum { SBRK_MEASURE, NET_MEASURE, GROSS_MEASURE } measurement_type;

# if defined(CURRENT_FUNCTION)
# undef CURRENT_FUNCTION
# endif // CURRENT_FUNCTION

#define pips_unknown_function "Unknown Function Name"

# if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L) // C99
#   define CURRENT_FUNCTION __func__
# else
#   if defined(__GNUC__) // GCC
#     define CURRENT_FUNCTION __FUNCTION__
#   else
#     define CURRENT_FUNCTION pips_unknown_function
#   endif // __GNUC__
# endif // C99

/* these macros use the GNU extensions that allow variadic macros,
 * including with an empty list.
 *
 * if not available, function calls are used.
 *
 * a slightly better job could be done if C99 is assumed.
 */

#if defined(__GNUC__) // GCC

// Use the old "do {...} while(0)" C hack to allow a macro with arbitrary
//  code to be used everywhere

#define pips_debug(level, format, args...)                        \
  do {                                                            \
    ifdebug(level)                                                \
      fprintf(stderr, "[%s] " format, CURRENT_FUNCTION, ##args);  \
  } while(0)

#define pips_user_warning(format, args...)                              \
  pips_user_warning_func(CURRENT_FUNCTION, __FILE__, __LINE__, format, ##args)

#define pips_user_error(format, args...)                                \
  pips_user_error_func(CURRENT_FUNCTION, __FILE__, __LINE__, format, ##args)

#define pips_user_irrecoverable_error(format, args...)                  \
  pips_user_irrecoverable_error_func(CURRENT_FUNCTION, __FILE__, __LINE__, \
                                     format, ##args)

// internal errors add file/line information
#define pips_internal_error(format, args...)                        \
  pips_internal_error_func(CURRENT_FUNCTION,  __FILE__ , __LINE__,  \
                           format, ##args)

#define pips_log(args...)                                     \
  pips_log_func(CURRENT_FUNCTION, __FILE__, __LINE__, ##args)

#define pips_stop(args...)                                      \
  pips_stop_func(CURRENT_FUNCTION, __FILE__, __LINE__, ##args)

#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L) // C99

#define pips_debug(level, ...)                                \
  do {                                                        \
    ifdebug(level)                                            \
      pips_debug_func(level, CURRENT_FUNCTION, __VA_ARGS__);  \
  } while (0)

#define pips_user_warning(...)                                          \
  pips_user_warning_func(CURRENT_FUNCTION, __FILE__, __LINE__, __VA_ARGS__)

#define pips_user_error(...)                          \
  pips_user_error_func(CURRENT_FUNCTION, __FILE__, __LINE__, __VA_ARGS__)

#define pips_user_irrecoverable_error(...)                          \
  pips_user_irrecoverable_error_func(CURRENT_FUNCTION, __FILE__, __LINE__, \
                                     __VA_ARGS__)

#define pips_internal_error(...)                                    \
  pips_internal_error_func(CURRENT_FUNCTION, __FILE__ , __LINE__,  \
                           __VA_ARGS__)

#define pips_log(...)                                               \
  pips_log_func(CURRENT_FUNCTION, __FILE__, __LINE__, __VA_ARGS__)

#define pips_stop(...)                                              \
  pips_log_func(CURRENT_FUNCTION, __FILE__, __LINE__, __VA_ARGS__)

#else // others, function name, file and line is lost
#define pips_debug pips_debug_func2
#define pips_user_warning pips_user_warning_func2
#define pips_user_error pips_user_error_func2
#define pips_user_irrecoverable_error pips_user_irrecoverable_error_func2
#define pips_internal_error pips_internal_error_func2
#define pips_log pips_log_func2
#define pips_stop pips_stop_func2
#endif

#define pips_where(out)                                               \
  fprintf(out, "[%s] (%s:%d) ", CURRENT_FUNCTION, __FILE__, __LINE__)

#define debug_on(env)                                           \
  debug_on_function(env, CURRENT_FUNCTION, __FILE__, __LINE__)

#define debug_off() \
  debug_off_function(CURRENT_FUNCTION, __FILE__, __LINE__)

/* common macros, two flavors depending on NDEBUG */
#ifdef NDEBUG

#define pips_assert(what, predicate)
#define pips_user_assert(what, predicate)
#define ifdebug(l) if(0)

#else

#define pips_assert(what, predicate)                                    \
  do {                                                                  \
    if (!(predicate)) {                                                 \
      pips_internal_error("assertion failed\n\n '%s' not verified\n\n", \
                          what);                                        \
      abort();                                                          \
    }                                                                   \
  } while(0)

#define pips_user_assert(what, predicate)                             \
    do {                                                              \
      if (!(predicate)) {                                             \
        pips_user_error("assertion failed\n\n '%s' not verified\n\n"  \
                        "this is a USER ERROR, I guess\n", what);     \
      }                                                               \
    } while(0)

#define ifdebug(l) if (the_current_debug_level>=(l))

#endif

#define pips_exit(code, format, args...)          \
   pips_user_warning(format, ##args), exit(code)

/* FI:need to breakpoint while inlining is available */
/* #define same_string_p(s1, s2) (strcmp((s1), (s2)) == 0)*/
#define same_string_p(s1, s2) function_same_string_p(s1,s2)
#define same_stringn_p(a,b,c) (!strncmp((a),(b),(c)))

/* MAXPATHLEN is defined in <sys/param.h> for SunOS... but not for all OS! */
#ifndef MAXPATHLEN
#define MAXPATHLEN 1024
#endif

#define PIPS_CATCH(what)                                                \
  if (push_debug_status(),                                              \
       setjmp(*push_exception_on_stack(what, __CURRENT_FUNCTION_NAME__, \
      	                    __FILE__, __LINE__, pop_debug_status)))

/* SG moved there from transformation.h */
#define SIGN_EQ(a,b) ((((a)>0 && (b)>0) || ((a)<0 && (b)<0)) ? true : false)
#define FORTRAN_DIV(n,d) (SIGN_EQ((n),(d)) ? ABS(n)/ABS(d) : -(ABS(n)/ABS(d)))
#define C_DIVISION(n,d) ((n)/(d))
#define FORTRAN_MOD(n,m) (SIGN_EQ((n),(m)) ? ABS(n)%ABS(m) : -(ABS(n)%ABS(m)))
#define C_MODULO(n,m) ((n)%(m))

// redundant declaration to ease bootstrapping
extern int the_current_debug_level;

// a reset functions is just something to call...
typedef void (*reset_func_t)(void);

// to avoid compiler warnings...
#define asprintf safe_asprintf
#define vasprintf safe_vasprintf

#ifndef __has_attribute
#define __has_attribute(att) 0
#endif // !__has_attribute

#define _UNUSED_ __attribute__((unused))
#define _NORETURN_ __attribute__((noreturn))

#if __has_attribute(fallthrough)
#define _FALLTHROUGH_ __attribute__((fallthrough))
#else
#define _FALLTHROUGH_
#endif // fallthrough

/* expecititely declare "noreturn" functions...
 * because cproto generated headers seem to ignore attributes
 */
void _NORETURN_ pips_stop_func(const char *, const char *, const int,
                               pips_log_t, int, const string, ...);
void _NORETURN_ pips_internal_error_func(const char *, const char *, const int,
                                         const char *, ...);
void _NORETURN_ pips_user_error_func(const char *, const char *, const int,
                                     const char *, ...);
void _NORETURN_ pips_user_irrecoverable_error_alist(
  const char *, const char *, const int, const char *,  va_list *);
void _NORETURN_ pips_user_irrecoverable_error_func(
  const char *, const char *, const int, const char *, ...);

void _NORETURN_ pips_stop_func2(pips_log_t, int, const string, ...);
void _NORETURN_ pips_internal_error_func2(const char *, ...);
void _NORETURN_ pips_user_error_func2(const char *, ...);
void _NORETURN_ pips_user_irrecoverable_error_func2(const char *, ...);

/***************************************************************** OLD STUFF */

#define user_warning(fn, ...)                                 \
  pips_user_warning_func(fn, __FILE__, __LINE__, __VA_ARGS__)

#define user_error(fn, ...)                                 \
  pips_user_error_func(fn, __FILE__, __LINE__, __VA_ARGS__)
/* debug.c */
extern int the_current_debug_level;
extern void set_debug_level(const int /*l*/);
extern int get_debug_level(void);
extern _int get_debug_stack_pointer(void);
extern void set_debug_stack_pointer(const int /*i*/);
extern void debug_on_function(const char */*env*/, const char */*function*/, const char */*file*/, const int /*line*/);
extern void debug_off_function(const char */*function*/, const char */*file*/, const int /*line*/);
extern void print_debug_stack(void);
extern void debug(const int /*the_expected_debug_level*/, const char */*calling_function_name*/, const char */*a_message_format*/, ...);
extern void pips_debug_function(const int /*the_expected_debug_level*/, const char */*a_message_format*/, ...);
extern double get_process_memory_size(void);
extern double get_process_gross_heap_size(void);
/* file.c */
extern FILE *check_fopen(const char */*file*/, const char */*mode*/);
extern FILE *safe_fopen(const char */*filename*/, const char */*what*/);
extern int safe_fclose(FILE */*stream*/, const char */*filename*/);
extern int safe_fflush(FILE */*stream*/, char */*filename*/);
extern FILE *safe_freopen(char */*filename*/, char */*what*/, FILE */*stream*/);
extern int safe_fseek(FILE */*stream*/, long int /*offset*/, int /*wherefrom*/, char */*filename*/);
extern long int safe_ftell(FILE */*stream*/, char */*filename*/);
extern void safe_rewind(FILE */*stream*/, char */*filename*/);
extern int safe_fgetc(FILE */*stream*/, char */*filename*/);
extern int safe_getc(FILE */*stream*/, char */*filename*/);
extern char *safe_fgets(char */*s*/, int /*n*/, FILE */*stream*/, char */*filename*/);
extern int safe_fputc(int /*c*/, FILE */*stream*/, char */*filename*/);
extern int safe_putc(int /*c*/, FILE */*stream*/, char */*filename*/);
extern int safe_fputs(char */*s*/, FILE */*stream*/, char */*filename*/);
extern int safe_fread(char */*ptr*/, int /*element_size*/, int /*count*/, FILE */*stream*/, char */*filename*/);
extern int safe_fwrite(char */*ptr*/, int /*element_size*/, int /*count*/, FILE */*stream*/, char */*filename*/);
extern int safe_list_files_in_directory(gen_array_t /*files*/, string /*dir*/, string /*re*/, bool (* /*file_name_predicate*/)(const char *));
extern void list_files_in_directory(gen_array_t /*files*/, string /*dir*/, string /*re*/, bool (* /*file_name_predicate*/)(const char *));
extern bool directory_exists_p(const char */*name*/);
extern bool file_exists_p(const char */*name*/);
extern char *strescape(const char */*source*/);
extern string nth_path(const char */*path_list*/, int /*n*/);
extern char *find_file_in_directories(const char */*file_name*/, const char */*dir_path*/);
extern bool file_readable_p(char */*name*/);
extern bool create_directory(char */*name*/);
extern bool purge_directory(char */*name*/);
extern char *get_cwd(void);
extern char *safe_readline(FILE */*file*/);
extern string safe_read_nth_line(string /*fn*/, int /*n*/);
extern string safe_get_line_interval(const string /*fn*/, int /*f*/, int /*l*/);
extern void safe_copy_line_interval(string /*fn*/, int /*f*/, int /*l*/, FILE */*out*/);
extern char *safe_readfile(FILE */*file*/);
extern void safe_cat(FILE */*out*/, FILE */*in*/);
extern void safe_append(FILE */*out*/, char */*file*/, int /*margin*/, bool /*but_comments*/);
extern void safe_copy(char */*source*/, char */*target*/);
extern int safe_display(char */*fname*/);
extern char *pips_filename(char */*fullpath*/, char */*suffix*/, bool /*short_p*/);
extern char *pips_basename(char */*fullpath*/, char */*suffix*/);
extern char *pips_initial_filename(char */*fullpath*/, char */*suffix*/);
extern char *pips_dirname(char */*fullpath*/);
extern void safe_unlink(const char */*file_name*/);
extern void safe_symlink(const char */*topath*/, const char */*frompath*/);
extern void safe_link(const char */*topath*/, const char */*frompath*/);
extern char *safe_system_output(char */*what*/);
extern char *safe_system_substitute(char */*what*/);
extern char *safe_new_tmp_file(char */*prefix*/);
extern FILE *fopen_config(const char */*canonical_name*/, const char */*cproperty*/, const char */*cenv*/);
/* message.c */
extern void set_pips_current_computation(const char */*rname*/, const char */*oname*/);
extern string get_pips_current_pass_name(void);
extern string get_pips_current_module(void);
extern void reset_pips_current_computation(void);
extern void set_pips_meta_informations(const char */*revs*/, const char */*date*/, const char */*comp*/);
extern string default_user_request(const char */*fmt*/, va_list */*args*/);
extern string (*pips_request_handler)(const char *, va_list *);
extern string user_request(const char */*a_message_format*/, ...);
extern void close_log_file(void);
extern void open_log_file(const string /*dir*/);
extern void log_on_file(const char */*desc*/);
extern void (*pips_log_handler)(const char *fmt, va_list *args);
extern void pips_user_log_func(const char */*format*/, ...);
extern void user_log(const char */*format*/, ...);
extern void pips_thanks(string /*name*/, string /*path*/);
extern void open_warning_file(const char */*dir*/);
extern void close_warning_file(void);
extern void append_to_warning_file(const char */*calling_function_name*/, const char */*format*/, va_list */*args*/);
extern void (*pips_warning_handler)(const char *, const char *, va_list *);
extern void pips_user_warning_alist(const char */*function_name*/, const char */*funcfile*/, const int /*funcline*/, const char */*format*/, va_list */*args*/);
extern void pips_user_warning_func(const char */*calling_function_name*/, const char */*funcfile*/, const int /*funcline*/, const char */*format*/, ...);
extern void pips_user_warning_func2(const char */*format*/, ...);
extern void pips_internal_error_func(const char */*funcname*/, const char */*funcfile*/, const int /*funcline*/, const char */*fmt*/, ...);
extern void pips_internal_error_func2(const char */*format*/, ...);
extern void (*pips_error_handler)(const char *, const char *, va_list *);
extern void pips_user_error_func(const char */*func_name*/, const char */*funcfile*/, const int /*funcline*/, const char */*format*/, ...);
extern void pips_user_error_func2(const char */*format*/, ...);
extern void (*pips_internal_error_handler)(const char *, const char *, ...);
extern void pips_user_irrecoverable_error_alist(const char */*func_name*/, const char */*funcfile*/, const int /*funcline*/, const char */*format*/, va_list */*args*/);
extern void pips_user_irrecoverable_error_func(const char */*func_name*/, const char */*funcfile*/, const int /*funcline*/, const char */*format*/, ...);
extern void pips_user_irrecoverable_error_func2(const char */*format*/, ...);
extern bool function_same_string_p(const char */*s1*/, const char */*s2*/);
extern void open_xml_logfile(const char */*filename*/);
extern void close_xml_logfile(void);
extern void pips_stop_func(const char */*pips_func*/, const char */*pips_file*/, const int /*pips_line*/, pips_log_t tag, int /*code*/, const string /*format*/, ...);
extern void pips_stop_func2(pips_log_t tag, int /*code*/, const string /*format*/, ...);
extern string pips_log_tag_name(pips_log_t tag);
extern void pips_log_desc(const pips_log_t tag, const string /*pips_pass*/, const string /*pips_owner*/, const string /*pips_func*/, const string /*pips_file*/, const int /*pips_line*/, const string /*user_func*/, const string /*user_file*/, const int /*user_line*/, const int /*user_line2*/, const string /*stmt*/, const string /*suggestion*/, const string /*description*/);
extern void pips_log_alist(const pips_log_t tag, const string /*pips_pass*/, const string /*pips_owner*/, const string /*pips_func*/, const string /*pips_file*/, const int /*pips_line*/, const string /*user_func*/, const string /*user_file*/, const int /*user_line*/, const int /*user_line2*/, const string /*stmt*/, const string /*suggestion*/, const string /*format*/, va_list */*args*/);
extern void pips_log_func(const string /*pips_func*/, const string /*pips_file*/, const int /*pips_line*/, const pips_log_t tag, const string /*pips_pass*/, const string /*pips_owner*/, const string /*user_func*/, const string /*user_file*/, const int /*user_line*/, const int /*user_line2*/, const string /*stmt*/, const string /*suggestion*/, const string /*format*/, ...);
extern void pips_log_stop(const char */*function*/, const char */*file*/, const int /*lineno*/, const pips_log_t tag, const int /*code*/, const string /*format*/, ...);
extern int safe_vasprintf(char **/*strp*/, const char */*fmt*/, va_list /*args*/);
extern int safe_asprintf(char **/*strp*/, const char */*fmt*/, ...);
/* dotting.c */
extern void start_dotting(FILE */*dotting_file*/, const char /*dotting_character*/, const char */*fmt*/, ...);
extern void stop_dotting(void);
/* args.c */
extern void list_to_array(list /*l*/, gen_array_t /*a*/);
extern void update_list_from_array(list /*l*/, gen_array_t /*a*/);
extern void sort_list_of_strings(list /*l*/);
extern string list_to_string(list /*l*/);
/* system.c */
extern void safe_system(string /*command*/);
extern int safe_system_no_abort(string /*command*/);
extern int safe_system_no_abort_no_warning(string /*command*/);
/* exception.c */
extern void push_pips_context(char const */*file*/, char const */*function*/, int /*line*/);
extern void pop_pips_context(char const */*file*/, char const */*function*/, int /*line*/);
/* perf_spy.c */
extern void push_performance_spy(void);
extern void pop_performance_spy(FILE */*f*/, string /*msg*/);
/* malloc_debug.c */
extern void pips_malloc_debug(void);
/* reset_hooks.c */
extern void reset_hooks_register(reset_func_t /*function*/);
extern void reset_hooks_call(void);
extern void reset_hooks_is_empty(void);
extern void reset_hooks_unregister(reset_func_t /*function*/);
#endif /*  misc_header_included */
