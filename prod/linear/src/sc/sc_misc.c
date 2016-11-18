/*

  $Id: sc_misc.c 1641 2016-03-02 08:20:19Z coelho $

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

#ifdef HAVE_CONFIG_H
    #include "config.h"
#endif

#include <stdio.h>
#include <stdlib.h>
//#include <assert.h>
//#include <string.h>

#include "boolean.h"
#include "arithmetique.h"
#include "vecteur.h"
#include "contrainte.h"
#include "sc.h"

/* for an improved dependence test (Beatrice Creusillet)
 *
 * The routine name says it all. Only constraints transitively connected
 * to a constraint referencing a variable of interest with a non-zero
 * coefficient are copied from sc to sc_res.
 *
 * Input:
 *  sc: unchanged
 *  variables: list of variables of interest (e.g. phi variables of regions)
 * Output:
 *  sc_res: a newly allocated restricted version of sc
 * Temporary:
 *  sc: the pointer is modified to make debugging more interesting:-(
 *      (no impact on the value pointed to by sc on procedure entry)
 *
 * FI: I'm sceptical... OK for speed, quid of accuracy? Nonfeasibility
 * due to existencial variables is lost if these variables are not
 * transitively related to the so-called variables of interest, isn'it?
 * Well, I do not manage to build a counter example because existential
 * problems are caught by the precondition normalization. Although it is
 * not as strong as one could wish, it gets lots of stuff...
 */

Psysteme
sc_restricted_to_variables_transitive_closure(
  Psysteme sc,
  Pbase variables)
{
  Psysteme sc_res;
  Pcontrainte c, c_pred, c_suiv;
  Pvecteur v;

  // first, handle special cases
  if (sc_rn_p(sc)){
    // we return a sc_rn predicate,on the space of the input variables
    sc_res = sc_rn(variables);
    return sc_res;
  }
  if (sc_empty_p(sc)) {
    // we return an empty predicate,on the space of the input variables */
    sc_res = sc_empty(variables);
    return sc_res;
  }

  // sc has no particularity. We just scan its equalities and inequalities
  // to find which variables are related to the PHI variables
  sc = sc_dup(sc);
  base_rm(sc->base);
  sc->base = BASE_NULLE;
  sc_creer_base(sc);

  sc_res = sc_new();
  sc_res->base = variables;
  sc_res->dimension = vect_size(variables);

  while (vect_common_variables_p(sc->base, sc_res->base))
  {
    // equalities first
    c = sc_egalites(sc);
    c_pred = (Pcontrainte) NULL;
    while (c != (Pcontrainte) NULL) {
	    c_suiv = c->succ;

	    /* if a constraint is found in sc, that contains a variable
	     * that already belongs to the base of sc_res, then this
	     * constraint is removed from sc, added to sc_res  and its
	     * variables are added to the base of sc_res */
	    if (vect_common_variables_p(c->vecteur,sc_res->base)){

        // the constraint is removed from sc
        if (c_pred != (Pcontrainte) NULL)
          c_pred->succ = c_suiv;
        else
          sc_egalites(sc) = c_suiv;

        // and added to sc_res
        c->succ = (Pcontrainte) NULL;
        sc_add_egalite(sc_res, c);

        // sc_res base is updated with the variables occuring in c
        for(v = c->vecteur; !VECTEUR_NUL_P(v); v = v->succ) {
          if (vecteur_var(v) != TCST)
            sc_base_add_variable(sc_res, vecteur_var(v));
        }
	    }
	    else
        c_pred = c;
	    c = c_suiv;
    }

    // inequalities then
    c = sc_inegalites(sc);
    c_pred = (Pcontrainte) NULL;
    while (c != (Pcontrainte) NULL) {
	    c_suiv = c->succ;

	    /* if a constraint is found in sc, that contains a variable
	     * that already belongs to the base of sc_res, then this
	     * constraint is removed from sc, added to sc_res  and its
	     * variables are added to the base of sc_res */
	    if (vect_common_variables_p(c->vecteur,sc_res->base)){
        // the constraint is removed from sc
        if (c_pred != (Pcontrainte) NULL)
          c_pred->succ = c_suiv;
        else
          sc_inegalites(sc) = c_suiv;

        // and added to sc_res
        c->succ = (Pcontrainte) NULL;
        sc_add_inegalite(sc_res, c);

        // sc_res base is updated with the variables occuring in c
        for(v = c->vecteur; !VECTEUR_NUL_P(v); v = v->succ) {
          if (vecteur_var(v) != TCST)
            sc_base_add_variable(sc_res, vecteur_var(v));
        }
	    }
	    else
        c_pred = c;
	    c = c_suiv;
    }

    // update sc base
    base_rm(sc->base);
    sc_base(sc) = (Pbase) NULL;
    (void) sc_creer_base(sc);
  } // while()

  sc_rm(sc);
  sc = NULL;

  return sc_res;
}

/* Does "var" appears with a non-zero coefficient in any equation or
 * inequality of constraint system "sc?
 */
bool sc_constrains_variable_p(Psysteme sc, Variable var, bool is_equations_p)
{
  Pcontrainte e = is_equations_p? sc_egalites(sc) :sc_inegalites(sc);
  bool found_p = false;

    for (; !CONTRAINTE_UNDEFINED_P(e) && !found_p; e = e->succ) {
      Pvecteur ev = contrainte_vecteur(e);
      Value val = vect_coeff(var, ev);
      found_p = (val!=VALUE_ZERO);
  }
  return found_p;
}

bool sc_equations_constrain_variable_p(Psysteme sc, Variable var)
{
  return sc_constrains_variable_p(sc, var, true);
}

bool sc_inequalities_constrain_variable_p(Psysteme sc, Variable var)
{
  return sc_constrains_variable_p(sc, var, false);
}
