/* Warning! Do not modify this file that is automatically generated! */
/* Modify src/Libs/polynome/polynome-local.h instead, to add your own modifications. */

/* header file built by cproto */

#ifndef  polynome_header_included
#define  polynome_header_included
/*

  $Id: polynome-local.h 1641 2016-03-02 08:20:19Z coelho $

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

/*
 *
 * SYMBOLIC POLYNOMIALS     P. Berthomier  02-08-90
 *
 *                          L. Zhou        Apr.8,91
 *
 *
 * This package contains some routines manipulating symbolic polynomials
 * with any number of variables. It uses the packages vecteur and arithmetique.
 *
 * There are routines for allocation/duplication/destruction, input/output,
 * "factorization", variable substitution, integer power exponentiation,
 * addition, multiplication, integration of polynomials.
 *
 * The package lacks: division by a one-variable polynomial, comparison
 * of two polynomials (when possible), ...
 *
 *
 * POLYNOMIAL STRUCTURE
 *
 *
 * We use a Pvecteur structure to represent a sort of "normalized monomial":
 * a product of powers of variables without scalar coefficient.
 *
 * The field "Variable" of the Pvecteur is a pointer to the variable
 * We only use pointer equality, so if two different pointers
 * refer to the same variable, the polynomials won't be normalized:
 * things such as 2*N + 3*N may appear.
 * The field "Value" contains the integer exponent of that unknown
 * in that monomial.
 *
 * We add a floating-point coefficient to form a complete monomial
 * structure: a *Pmonome.
 *
 * We define a polynomial as an unsorted list of monomial structure.
 *
 *
 *
 * Example of Pmonome:     2 * X^2.Y.Z^3
 * (the "@" below means: beginning of a pointer)
 *
 *
 *                    -----------
 * Pmonome @------>   |    2    | (coeff:float)
 *                    |---------|
 *                    |    @    | (term:Pvecteur)
 *                    ---- | ----
 *                         |
 *                         V
 *          /         -----------
 *          |         |  Y , 1  |
 *          |         -----------
 * Pvecteur |         |  Z , 3  |
 *          |         -----------
 *          |         |  X , 2  |
 *          \         -----------
 *
 *
 *
 * Example of Ppolynome:    6 * N^3.k + 3 * N.k - 2
 *
 *                  -----------    -----------    -----------    
 * Ppolynome:@----> |    @-------> |    @-------> |    /    | (succ:Ppolynome)
 *                  |---------|    |---------|    |---------|    
 *                  |    @    |    |    @    |    |    @    | (monome:Pmonome)   
 *                  ---- | ----    ---- | ----    ---- | ----    
 *                       |              |              |         
 *                       V              V              V         
 *          /       -----------    -----------    -----------    
 *          |       |    6    |    |    3    |    |   -2    |
 * Pmonomes |       -----------    -----------    -----------    
 *          |       |    @    |    |    @    |    |    @    |    
 *          \       ---- | ----    ---- | ----    ---- | ----    
 *                       |              |              |         
 *                       V              V              V         
 *          /       -----------    -----------    -----------    
 *          |       |  N , 3  |    |  N , 1  |    | TCST, 1 |    
 * Pvecteurs|       -----------    -----------    -----------    
 *          |       |  k , 1  |    |  k , 1  |
 *          \       -----------    -----------    
 *
 * Nul polynomials are represented by a fixed pointer: POLYNOME_NUL.
 * Undefined polynomials are represented by POLYNOME_UNDEFINED.
 *
 * The package is cut into ten files:
 *
 *   pnome-types.h
 *   polynome.h         (This file. Automatically generated from pnome-types.h)
 *
 *   pnome-alloc.c
 *   pnome-bin.c
 *   pnome-error.c
 *   pnome-io.c
 *   pnome-private.c
 *   pnome-reduc.c
 *   pnome-scal.c
 *   pnome-unaires.c
 *
 * 
 */


#ifndef POLYNOME_INCLUDED
#define POLYNOME_INCLUDED

typedef struct Smonome {
    float coeff;
    Pvecteur term;
} Smonome, *Pmonome;

typedef struct Spolynome {
    Pmonome monome;
    struct Spolynome *succ;
} Spolynome, *Ppolynome;


/* Macros definitions */
#define monome_coeff(pm) ((pm)->coeff)
#define monome_term(pm) ((pm)->term)
#define polynome_monome(pp) ((pp)->monome)
#define polynome_succ(pp) ((pp)->succ)
/*
#define is_single_monome(pp) ((POLYNOME_NUL_P(pp)) || (POLYNOME_NUL_P(polynome_succ(pp))))
*/
#define is_single_monome(pp) ((!POLYNOME_NUL_P(pp)) && (POLYNOME_NUL_P(polynome_succ(pp))))

#define monome_constant_new(coeff) make_monome(coeff, TCST, 1)
#define monome_power1_new(coeff, var) make_monome(coeff, var, 1)

/* Null/undefined, monomial/polynomial definitions */
#define MONOME_NUL ((Pmonome) -256)
#define MONOME_NUL_P(pm) ((pm)==MONOME_NUL)
#define MONOME_UNDEFINED ((Pmonome) -252)
#define MONOME_UNDEFINED_P(pm) ((pm)==MONOME_UNDEFINED)
#define MONOME_CONSTANT_P(pm) (term_cst((pm)->term))

#define POLYNOME_NUL ((Ppolynome) NULL)
#define POLYNOME_NUL_P(pp) ((pp)==POLYNOME_NUL)
#define POLYNOME_UNDEFINED ((Ppolynome) -248)
#define POLYNOME_UNDEFINED_P(pp) ((pp)==POLYNOME_UNDEFINED)

#define MONOME_COEFF_MULTIPLY_SYMBOL "*"
#define MONOME_VAR_MULTIPLY_SYMBOL "."
#define POLYNOME_NUL_SYMBOL "0"
#define POLYNOME_UNDEFINED_SYMBOL "<polynome undefined>"
#define MONOME_NUL_SYMBOL "<monome nul>"
#define MONOME_UNDEFINED_SYMBOL "<monome undefined>"

#define MAX_NAME_LENGTH 50

#define PNOME_MACH_EPS 1E-8          /* below this value, a float is null      */
#define PNOME_FLOAT_N_DECIMALES 2    /* nb of figures after point for coeffs   */
#define PNOME_FLOAT_TO_EXP_LEVEL 1E8 /* numbers >1E8 are printed with exponent */
#define PNOME_FLOAT_TO_FRAC_LEVEL 9  /* print 1/2..1/9 rather than 0.50..0.11  */

#endif /* POLYNOME_INCLUDED */

/* pnome-alloc.c */
extern Pmonome new_monome(void);
extern Ppolynome new_polynome(void);
extern Pmonome make_monome(float /*coeff*/, Variable /*var*/, Value /*expo*/);
extern Ppolynome make_polynome(float /*coeff*/, Variable /*var*/, Value /*expo*/);
extern Ppolynome monome_to_new_polynome(Pmonome /*pm*/);
extern Pmonome monome_dup(Pmonome /*pm*/);
extern void monome_rm(Pmonome */*ppm*/);
extern void polynome_rm(Ppolynome */*ppp*/);
extern Ppolynome polynome_free(Ppolynome /*pp*/);
extern Ppolynome polynome_dup(Ppolynome /*pp*/);
/* pnome-bin.c */
extern void polynome_monome_add(Ppolynome */*ppp*/, Pmonome /*pm*/);
extern Ppolynome polynome_monome_addition(Ppolynome /*pp*/, Pmonome /*pm*/);
extern void polynome_add(Ppolynome */*ppp*/, Ppolynome /*pp2*/);
extern Ppolynome polynome_addition(Ppolynome /*pp*/, Ppolynome /*pp2*/);
extern Ppolynome polynome_monome_mult(Ppolynome /*pp*/, Pmonome /*pm*/);
extern Ppolynome polynome_mult(Ppolynome /*pp1*/, Ppolynome /*pp2*/);
extern Pmonome monome_monome_div(Pmonome /*pm1*/, Pmonome /*pm2*/);
extern Ppolynome polynome_monome_div(Ppolynome /*pp*/, Pmonome /*pm*/);
extern Ppolynome polynome_div(Ppolynome /*pp1*/, Ppolynome /*pp2*/);
extern Ppolynome vecteur_to_polynome(Pvecteur /*pv*/);
/* pnome-error.c */
extern void polynome_error(const char */*name*/, char */*fmt*/, ...);
extern void good_polynome_assert(char */*function*/, ...);
extern bool monome_check(Pmonome /*pm*/);
extern bool polynome_check(Ppolynome /*pp*/);
extern bool is_polynome_a_monome(Ppolynome /*pp*/);
/* pnome-io.c */
extern void float_to_frac(double /*x*/, char **/*ps*/);
extern void monome_fprint(FILE */*fd*/, Pmonome /*pm*/, Pbase /*pb*/, bool /*plus_sign*/, char *(* /*variable_name*/)(Variable));
extern char *monome_sprint(Pmonome /*pm*/, Pbase /*pb*/, bool /*plus_sign*/, char *(* /*variable_name*/)(Variable));
extern void polynome_fprint(FILE */*fd*/, Ppolynome /*pp*/, char *(* /*variable_name*/)(Variable), int (* /*is_inferior_var*/)(Pvecteur *, Pvecteur *));
extern char *polynome_sprint(Ppolynome /*pp*/, char *(* /*variable_name*/)(Variable), int (* /*is_inferior_var*/)(Pvecteur *, Pvecteur *));
extern char *default_variable_name(Variable /*var*/);
extern int default_is_inferior_var(Variable /*var1*/, Variable /*var2*/);
extern int default_is_inferior_varval(Pvecteur /*varval1*/, Pvecteur /*varval2*/);
extern int default_is_inferior_pvarval(Pvecteur */*pvarval1*/, Pvecteur */*pvarval2*/);
extern Ppolynome polynome_sscanf(char */*sp*/, Variable (* /*name_to_variable*/)(Variable));
/* pnome-private.c */
extern Pmonome monome_del_var(Pmonome /*pm*/, Variable /*var*/);
extern bool monome_colin(Pmonome /*pm1*/, Pmonome /*pm2*/);
extern bool monome_equal(Pmonome /*pm1*/, Pmonome /*pm2*/);
extern float Bernouilli(int /*i*/);
extern int factorielle(int /*n*/);
extern double intpower(double /*d*/, int /*n*/);
extern bool is_inferior_monome(Pmonome /*pm1*/, Pmonome /*pm2*/, int (* /*is_inferior_var*/)(Pvecteur *, Pvecteur *));
/* pnome-reduc.c */
extern Ppolynome polynome_var_subst(Ppolynome /*pp*/, Variable /*var*/, Ppolynome /*ppsubst*/);
extern int polynome_degree(Ppolynome /*pp*/, Variable /*var*/);
extern int polynome_max_degree(Ppolynome /*pp*/);
extern Ppolynome polynome_factorize(Ppolynome /*pp*/, Variable /*var*/, int /*n*/);
extern float polynome_TCST(Ppolynome /*pp*/);
extern bool polynome_constant_p(Ppolynome /*pp*/);
extern Pbase polynome_used_var(Ppolynome /*pp*/, int (* /*is_inferior_var*/)(Pvecteur *, Pvecteur *));
extern bool polynome_contains_var(Ppolynome /*pp*/, Variable /*var*/);
extern bool polynome_equal(Ppolynome /*pp1*/, Ppolynome /*pp2*/);
/* pnome-scal.c */
extern void polynome_scalar_mult(Ppolynome */*ppp*/, double /*factor*/);
extern Ppolynome polynome_scalar_multiply(Ppolynome /*pp*/, double /*factor*/);
extern void polynome_scalar_add(Ppolynome */*ppp*/, double /*term*/);
extern Ppolynome polynome_scalar_addition(Ppolynome /*pp*/, double /*term*/);
extern Ppolynome polynome_power_n(Ppolynome /*pp*/, int /*n*/);
extern Ppolynome polynome_nth_root(Ppolynome /*p*/, int /*n*/);
extern Ppolynome number_replaces_var(Ppolynome /*pp*/, Variable /*var*/, double /*num*/);
extern Ppolynome polynome_incr(Ppolynome /*pp*/);
extern Ppolynome polynome_decr(Ppolynome /*pp*/);
/* pnome-root.c */
extern Pvecteur polynome_roots(Ppolynome /*p*/, Variable /*var*/);
/* pnome-unaires.c */
extern void polynome_negate(Ppolynome */*ppp*/);
extern Ppolynome polynome_opposed(Ppolynome /*pp*/);
extern Ppolynome polynome_sum_of_power(Ppolynome /*ppsup*/, int /*p*/);
extern Ppolynome polynome_sigma(Ppolynome /*pp*/, Variable /*var*/, Ppolynome /*ppinf*/, Ppolynome /*ppsup*/);
extern Ppolynome polynome_sort(Ppolynome */*ppp*/, int (* /*is_inferior_var*/)(Pvecteur *, Pvecteur *));
extern void polynome_chg_var(Ppolynome */*ppp*/, Variable /*v_old*/, Variable /*v_new*/);
#endif /*  polynome_header_included */
