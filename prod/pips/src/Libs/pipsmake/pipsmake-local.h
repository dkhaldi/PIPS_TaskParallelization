/*

  $Id: pipsmake-local.h 23065 2016-03-02 09:05:50Z coelho $

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
#include "makefile.h"
typedef bool (*pipsmake_callback_handler_type)(void);

/* symbols exported by lex / yacc */
extern void pipsmake_error(const char *);
extern FILE *pipsmake_in;
extern int pipsmake_lex(void);
extern int pipsmake_parse(void);
