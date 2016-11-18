/* Warning! Do not modify this file that is automatically generated! */
/* Modify src/Libs/continuation/continuation-local.h instead, to add your own modifications. */

/* header file built by cproto */

#ifndef  continuation_header_included
#define  continuation_header_included
/*

  $Id: continuation-local.h 23065 2016-03-02 09:05:50Z coelho $

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
/* continuation.c */
extern bool must_continuation_map_undefined_p(void);
extern void set_must_continuation_map(statement_mapping /*m*/);
extern statement_mapping get_must_continuation_map(void);
extern void reset_must_continuation_map(void);
extern void free_must_continuation_map(void);
extern void make_must_continuation_map(void);
extern transformer load_statement_must_continuation(statement /*s*/);
extern void delete_statement_must_continuation(statement /*s*/);
extern bool statement_must_continuation_undefined_p(statement /*s*/);
extern void store_statement_must_continuation(statement /*s*/, transformer /*t*/);
extern void update_statement_must_continuation(statement /*s*/, transformer /*t*/);
extern bool may_continuation_map_undefined_p(void);
extern void set_may_continuation_map(statement_mapping /*m*/);
extern statement_mapping get_may_continuation_map(void);
extern void reset_may_continuation_map(void);
extern void free_may_continuation_map(void);
extern void make_may_continuation_map(void);
extern transformer load_statement_may_continuation(statement /*s*/);
extern void delete_statement_may_continuation(statement /*s*/);
extern bool statement_may_continuation_undefined_p(statement /*s*/);
extern void store_statement_may_continuation(statement /*s*/, transformer /*t*/);
extern void update_statement_may_continuation(statement /*s*/, transformer /*t*/);
extern bool continuation_conditions(const string /*module_name*/);
/* prettyprint.c */
extern bool print_code_continuation_conditions(const string /*module_name*/);
extern bool print_source_continuation_conditions(const string /*module_name*/);
#endif /*  continuation_header_included */
