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
