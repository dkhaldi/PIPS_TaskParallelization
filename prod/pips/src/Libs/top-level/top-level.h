/* Warning! Do not modify this file that is automatically generated! */
/* Modify src/Libs/top-level/top-level-local.h instead, to add your own modifications. */

/* header file built by cproto */

#ifndef  top_level_header_included
#define  top_level_header_included
/*

  $Id: top-level-local.h 23065 2016-03-02 09:05:50Z coelho $

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
/* Top-level declares a extern jmp_buf pips_top_level :
 */
#include <setjmp.h>
#include "constants.h"
/* dbm.c */
extern void default_update_props(void);
extern void (*pips_update_props_handler)(void);
extern bool open_module(const char */*name*/);
extern bool open_module_if_unique(void);
extern bool create_workspace(gen_array_t /*files*/);
extern bool lazy_open_module(const char */*name*/);
extern bool open_workspace(const char */*name*/);
extern bool close_workspace(bool /*is_quit*/);
extern bool delete_workspace(const char */*wname*/);
extern bool check_delete_workspace(const char */*wname*/, bool /*check*/);
extern void compile_f90_module(string /*filename*/);
extern gen_array_t get_stubs(void);
/* help.c */
extern void get_help_topics(gen_array_t /*array*/);
extern void get_help_topic(string /*topic*/, gen_array_t /*array*/);
extern void pips_checks(void);
#endif /*  top_level_header_included */
