/*

  $Id: sc_cmp.c 1641 2016-03-02 08:20:19Z coelho $

  Copyright 1989-2016 MINES ParisTech

  This file is part of Linear/C3 Library.

  Linear/C3 Library is free software: you can redistribute it and/or modify it
  under the terms of the GNU Lesser General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  any later version.

  Linear/C3 Library is distributed in the hope that it will be useful, but WITHOUT ANY
  WARRANTY; without even the implied warranty of MERCHANTABILITY or
  FITNESS FOR A PARTICULAR PURPOSE.

  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public License
  along with Linear/C3 Library.  If not, see <http://www.gnu.org/licenses/>.

*/

 /* Test whether two systems are equivalent
  */

#ifdef HAVE_CONFIG_H
    #include "config.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "linear.h"

/* show how s differs from r */
static void show_nredund(const char *msg, Psysteme s, Psysteme r)
{
  fprintf(stdout, "%s specific constraints:\n", msg);
  for (Pcontrainte c = s->egalites; c; c = c->succ)
    if (!eq_redund_with_sc_p(r, c))
      contrainte_fprint(stdout, c, false, *variable_default_name);
  for (Pcontrainte c = s->inegalites; c; c = c->succ)
    if (!ineq_redund_with_sc_p(r, c))
      contrainte_fprint(stdout, c, true, *variable_default_name);
}

int main(int argc, const char **argv)
{
  if (argc != 3) {
    fprintf(stderr, "Usage: %s sc1 sc2\n", argv[0]);
    exit(1);
  }

  const char *n1 = argv[1], *n2 = argv[2];

  // open input files
  FILE *f1;
  if ((f1 = fopen(n1,"r")) == NULL) {
    fprintf(stderr, "cannot open file: %s\n", n1);
    exit(4);
  }

  FILE *f2;
  if ((f2 = fopen(n2, "r")) == NULL) {
    fprintf(stderr, "cannot open file: %s\n", n2);
    exit(4);
  }

  Psysteme s1 = sc_new();
  if (sc_fscan(f1, &s1)) {
    fprintf(stderr,"file syntax is ok: %s\n", n1);
    sc_fprint(stdout, s1, *variable_default_name);
    assert(sc_weak_consistent_p(s1));
  }
  else {
    fprintf(stderr, "syntax error in file: %s\n", n1);
    exit(1);
  }

  Psysteme s2 = sc_new();
  if (sc_fscan(f2, &s2)) {
    fprintf(stderr,"file syntax is ok: %s\n", n2);
    sc_fprint(stdout, s2, *variable_default_name);
    assert(sc_weak_consistent_p(s2));
  }
  else {
    fprintf(stderr, "syntax error in file: %s\n", n2);
    exit(2);
  }

  if (sc_equal_p_ofl(s1, s2))
  {
    fprintf(stdout, "%s & %s are equivalent\n", n1, n2);
  }
  else
  {
    fprintf(stdout, "%s & %s are NOT equivalent\n", n1, n2);
    if (sc_inclusion_p_ofl(s1, s2))
    {
      fprintf(stdout, "%s is strictly included in %s\n", n1, n2);
      show_nredund(n1, s1, s2);
    }
    else if (sc_inclusion_p_ofl(s2, s1))
    {
      fprintf(stdout, "%s is strictly included in %s\n", n2, n1);
      show_nredund(n2, s2, s1);
    }
    else
    {
      fprintf(stdout, "no inclusion\n");
      show_nredund(n1, s1, s2);
      show_nredund(n2, s2, s1);
    }
  }

  return 0;
}
