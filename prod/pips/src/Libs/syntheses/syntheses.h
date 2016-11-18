/* Warning! Do not modify this file that is automatically generated! */
/* Modify src/Libs/syntheses/syntheses-local.h instead, to add your own modifications. */

/* header file built by cproto */

#ifndef  syntheses_header_included
#define  syntheses_header_included
/*

  $Id$

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
/* SYNTHESES Library: Passes and functions generating new modules, or
 * removing modules, such as initializer, clone, inlining and
 * outlining
 */

#include "linear.h"
#include "genC.h"

#include "text.h"

#include "newgen.h"

#include "naming.h"
#include "ri.h"
#include "ri-util.h"
#include "pipsdbm.h"
#include "workspace-util.h"
/* initializer.c */
extern void add_new_compilation_unit(const char */*compilation_unit_name*/, bool /*is_fortran*/, entity /*module*/);
extern bool add_new_module_from_text(const char */*module_name*/, text /*code_text*/, bool /*is_fortran*/, const char */*compilation_unit_name*/);
extern bool add_new_module(const char */*module_name*/, entity /*module*/, statement /*stat*/, bool /*is_fortran*/);
extern void set_internal_missing_module_resolver_handler(string (* /*_internal_resolver*/)(const char *));
extern bool fortran_initializer(const string /*module_name*/);
extern bool initializer(const string /*module_name*/);
extern bool c_initializer(const string /*module_name*/);
/* clone.c */
extern bool clone_on_argument(const string /*name*/);
extern bool clone(const string /*name*/);
extern bool clone_substitute(const string /*name*/);
extern bool clone_only(const string /*mod_name*/);
#endif /*  syntheses_header_included */
