/* Warning! Do not modify this file that is automatically generated! */
/* Modify src/Libs/properties/properties-local.h instead, to add your own modifications. */

/* header file built by cproto */

#ifndef  properties_header_included
#define  properties_header_included
/*

  $Id: properties-local.h 23065 2016-03-02 09:05:50Z coelho $

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
#include "property.h"

#define ONE_TRIP_DO "ONE_TRIP_DO"

#define PRETTYPRINT_TRANSFORMER "PRETTYPRINT_TRANSFORMER"
#define PRETTYPRINT_EXECUTION_CONTEXT "PRETTYPRINT_EXECUTION_CONTEXT"
#define PRETTYPRINT_EFFECTS "PRETTYPRINT_EFFECTS"
#define PRETTYPRINT_PARALLEL "PRETTYPRINT_PARALLEL"
#define PRETTYPRINT_REVERSE_DOALL "PRETTYPRINT_REVERSE_DOALL"
#define PRETTYPRINT_REGION "PRETTYPRINT_REGION"

#define SEMANTICS_FLOW_SENSITIVE "SEMANTICS_FLOW_SENSITIVE"
#define SEMANTICS_INTERPROCEDURAL "SEMANTICS_INTERPROCEDURAL"
#define SEMANTICS_INEQUALITY_INVARIANT "SEMANTICS_INEQUALITY_INVARIANT"
#define SEMANTICS_FIX_POINT "SEMANTICS_FIX_POINT"
#define SEMANTICS_DEBUG_LEVEL "SEMANTICS_DEBUG_LEVEL"
#define SEMANTICS_STDOUT "SEMANTICS_STDOUT"

#define PARALLELIZE_USE_EXECUTION_CONTEXT "PARALLELIZE_USE_EXECUTION_CONTEXT"

#define DEPENDENCE_TEST "DEPENDENCE_TEST"
#define RICEDG_PROVIDE_STATISTICS "RICEDG_PROVIDE_STATISTICS"

/* for upwards compatibility with Francois's modified version */
#define pips_flag_p(p) get_bool_property(p)
#define pips_flag_set(p) set_bool_property((p), true)
#define pips_flag_reset(p) set_bool_property((p), false)
#define pips_flag_fprint(fd) fprint_properties(fd)

bool too_many_property_errors_pending_p(void);
void reset_property_error(void);
/* properties.c */
extern FILE *prop_in;
extern FILE *prop_out;
extern int prop_lineno;
extern int prop__flex_debug;
extern char *prop_text;
extern void parse_properties_string(char */*s*/, bool /*processing_p*/);
extern int prop_lex(void);
extern void prop_restart(FILE */*input_file*/);
extern void prop_pop_buffer_state(void);
extern int prop_get_lineno(void);
extern FILE *prop_get_in(void);
extern FILE *prop_get_out(void);
extern char *prop_get_text(void);
extern void prop_set_lineno(int /*line_number*/);
extern void prop_set_in(FILE */*in_str*/);
extern void prop_set_out(FILE */*out_str*/);
extern int prop_get_debug(void);
extern void prop_set_debug(int /*bdebug*/);
extern int prop_lex_destroy(void);
extern void prop_free(void */*ptr*/);
extern int prop_wrap(void);
extern bool properties_initialized_p(void);
extern bool too_many_property_errors_pending_p(void);
extern void reset_property_error(void);
extern property get_property(const char */*name*/, bool /*cool*/);
extern bool get_bool_property(const char */*name*/);
extern void set_bool_property(const char */*name*/, bool /*b*/);
extern const char *get_string_property(const char */*name*/);
extern const char *get_string_property_or_ask(const char */*name*/, const char /*question*/[]);
extern void set_string_property(const char */*name*/, const char */*s*/);
extern int get_int_property(const char */*name*/);
extern void set_int_property(const char */*name*/, int /*i*/);
extern void fprint_property_direct(FILE */*fd*/, const char */*pname*/);
extern void fprint_property(FILE */*fd*/, const char */*pname*/);
extern void fprint_properties(FILE */*fd*/);
extern bool open_properties(void);
extern void save_properties(void);
#endif /*  properties_header_included */
