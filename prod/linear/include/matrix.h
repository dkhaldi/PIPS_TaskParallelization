/* Warning! Do not modify this file that is automatically generated! */
/* Modify src/Libs/matrix/matrix-local.h instead, to add your own modifications. */

/* header file built by cproto */

#ifndef  matrix_header_included
#define  matrix_header_included
/*

  $Id: matrix-local.h 1641 2016-03-02 08:20:19Z coelho $

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

/* package matrice
 *
 * Neil Butler, Corinne Ancourt, Francois Irigoin, Yi-qing Yang
 *
 */

/* Les matrices sont des matrices pleines, a coeffcients rationnels.
 *
 * Les matrices sont representes par des tableaux d'entiers mono-dimensionnels
 * Elles sont  stockees par colonne ("column-major"), comme en Fortran.
 * Les indices commencent a 1, toujours comme en Fortran et non comme en C.
 *
 * Le denominateur doit etre strictement positif, i.e. plus grand ou egal
 * a un. Un denominateur nul n'aurait pas de sens. Un denominateur negatif
 * doublerait le nombre de representations possibles d'une matrice.
 *
 * Les matrices renvoyees par certaines routines, comme matrix_multiply(),
 * ne sont pas normalisees par le pgcd des coefficients et du denominateur
 * pour des raisons d'efficacite. Mais les routines de test, comme
 * matrix_identity_p(), supposent leurs arguments normalises.
 *
 * Il faudrait sans doute introduire deux niveaux de procedure, un niveau
 * externe sur garantissant la normalisation, et un niveau interne efficace
 * sans normalisation automatique.
 *
 * La bibliotheque utilise une notion de sous-matrice, definie systematiquement
 * par un parametre appele "level". Seuls les elements dont les indices
 * de lignes et de colonnes sont superieurs a level+1
 * sont pris en consideration. Il s'agit donc de sous-matrice dont le
 * premier element se trouve sur la diagonale de la matrice complete et
 * dont le dernier element et le dernier element de la matrice complete.
 *
 * Note: en cas detection d'incoherence, Neil Butler renvoyait un code
 * d'erreur particulier; Francois Irigoin a supprime ces codes de retour
 * et a traite les exceptions par des appels a assert(), et indirectement
 * a abort()
 */

typedef struct {
    Value denominator;
    int number_of_lines;
    int number_of_columns;
    Value * coefficients;
} * Pmatrix, Smatrix;

#define MATRIX_UNDEFINED ((Pmatrix) NULL)

/* Allocation et desallocation d'une matrice */
#define matrix_free(m) (free(m), (m)=(Pmatrix) NULL)

/* Macros d'acces aux elements d'une matrice */

/* int MATRIX_ELEM(int * matrix, int i, int j):
 * acces a l'element (i,j) de la matrice matrix.
 */
#define MATRIX_ELEM(matrix, i, j)                                       \
  ((matrix)->coefficients[(((j)-1)*((matrix)->number_of_lines))+((i)-1)])

/* int MATRIX_DENONIMATOR(matrix): acces au denominateur global
 * d'une matrice matrix
 */
#define MATRIX_DENOMINATOR(matrix) ((matrix)->denominator)
#define MATRIX_NB_LINES(matrix)  ((matrix)->number_of_lines)
#define MATRIX_NB_COLUMNS(matrix)  ((matrix)->number_of_columns)

/* bool matrix_triangular_inferieure_p(matrice a):
 * test de triangularite de la matrice a
 */
#define matrix_triangular_inferieure_p(a)       \
  matrix_triangular_p(a, true)

/* bool matrix_triangular_superieure_p(matrice a, int n, int m):
 * test de triangularite de la matrice a
 */
#define matrix_triangular_superieure_p(a)       \
  matrix_triangular_p(a, false)

/* MATRIX_RIGHT_INF_ELEM Permet d'acceder des sous-matrices dont le
 * coin infe'rieur droit (i.e. le premier element) se trouve sur la
 * diagonal
 */
#define SUB_MATRIX_ELEM(matrix, i, j, level)                            \
  (matrix->coefficients[((j)-1+(level))*                                \
                        ((matrix)->number_of_lines) + (i) - 1 + (level)])
/* alloc.c */
extern Pmatrix matrix_new(int /*m*/, int /*n*/);
extern void matrix_rm(Pmatrix /*a*/);
/* determinant.c */
extern void matrix_determinant(Pmatrix /*a*/, Value /*result*/[]);
extern void matrix_sub_determinant(Pmatrix /*a*/, int /*i*/, int /*j*/, Value /*result*/[]);
/* hermite.c */
extern void matrix_hermite(Pmatrix /*MAT*/, Pmatrix /*P*/, Pmatrix /*H*/, Pmatrix /*Q*/, Value */*det_p*/, Value */*det_q*/);
extern int matrix_hermite_rank(Pmatrix /*a*/);
extern int matrix_dim_hermite(Pmatrix /*H*/);
/* inversion.c */
extern void matrix_unimodular_triangular_inversion(Pmatrix /*u*/, Pmatrix /*inv_u*/, bool /*infer*/);
extern void matrix_diagonal_inversion(Pmatrix /*s*/, Pmatrix /*inv_s*/);
extern void matrix_triangular_inversion(Pmatrix /*h*/, Pmatrix /*inv_h*/, bool /*infer*/);
extern void matrix_general_inversion(Pmatrix /*a*/, Pmatrix /*inv_a*/);
extern void matrix_unimodular_inversion(Pmatrix /*u*/, Pmatrix /*inv_u*/);
/* matrix.c */
extern Value *matrix_elem_ref(Pmatrix /*M*/, int /*r*/, int /*c*/);
extern Value matrix_elem(Pmatrix /*M*/, int /*r*/, int /*c*/);
extern void matrix_transpose(const Pmatrix /*A*/, Pmatrix /*At*/);
extern void matrix_multiply(const Pmatrix /*a*/, const Pmatrix /*b*/, Pmatrix /*c*/);
extern void matrix_normalize(Pmatrix /*a*/);
extern void matrix_normalizec(Pmatrix /*MAT*/);
extern void matrix_swap_columns(Pmatrix /*A*/, int /*c1*/, int /*c2*/);
extern void matrix_swap_rows(Pmatrix /*A*/, int /*r1*/, int /*r2*/);
extern void matrix_assign(Pmatrix /*A*/, Pmatrix /*B*/);
extern bool matrix_equality(Pmatrix /*A*/, Pmatrix /*B*/);
extern void matrix_nulle(Pmatrix /*Z*/);
extern bool matrix_nulle_p(Pmatrix /*Z*/);
extern bool matrix_diagonal_p(Pmatrix /*Z*/);
extern bool matrix_triangular_p(Pmatrix /*Z*/, bool /*inferieure*/);
extern bool matrix_triangular_unimodular_p(Pmatrix /*Z*/, bool /*inferieure*/);
extern void matrix_substract(Pmatrix /*a*/, Pmatrix /*b*/, Pmatrix /*c*/);
extern void matrix_add(Pmatrix /*a*/, Pmatrix /*b*/, Pmatrix /*c*/);
extern void matrix_subtraction_column(Pmatrix /*MAT*/, int /*c1*/, int /*c2*/, Value /*x*/);
extern void matrix_subtraction_line(Pmatrix /*MAT*/, int /*r1*/, int /*r2*/, Value /*x*/);
extern void matrix_uminus(Pmatrix /*A*/, Pmatrix /*mA*/);
/* matrix_io.c */
extern void matrix_fprint(FILE */*f*/, Pmatrix /*a*/);
extern void matrix_print(Pmatrix /*a*/);
extern void matrix_fscan(FILE */*f*/, Pmatrix */*a*/, int */*n*/, int */*m*/);
extern void matrix_pr_quot(FILE */*f*/, Value /*a*/, Value /*b*/);
/* smith.c */
extern void matrix_smith(Pmatrix /*MAT*/, Pmatrix /*P*/, Pmatrix /*D*/, Pmatrix /*Q*/);
extern int matrices_to_1D_lattice(Pmatrix /*A*/, Pmatrix /*B*/, int /*n*/, int /*m*/, int /*i*/, Value */*gcd_p*/, Value */*c_p*/);
/* sub-matrix.c */
extern int matrix_line_nnul(Pmatrix /*MAT*/, int /*level*/);
extern void matrix_perm_col(Pmatrix /*MAT*/, int /*k*/, int /*level*/);
extern void matrix_perm_line(Pmatrix /*MAT*/, int /*k*/, int /*level*/);
extern void matrix_min(Pmatrix /*MAT*/, int */*i_min*/, int */*j_min*/, int /*level*/);
extern void matrix_maj_col(Pmatrix /*A*/, Pmatrix /*P*/, int /*level*/);
extern void matrix_maj_line(Pmatrix /*A*/, Pmatrix /*Q*/, int /*level*/);
extern void matrix_identity(Pmatrix /*ID*/, int /*level*/);
extern bool matrix_identity_p(Pmatrix /*ID*/, int /*level*/);
extern int matrix_line_el(Pmatrix /*MAT*/, int /*level*/);
extern int matrix_col_el(Pmatrix /*MAT*/, int /*level*/);
extern void matrix_coeff_nnul(Pmatrix /*MAT*/, int */*lg_nnul*/, int */*cl_nnul*/, int /*level*/);
extern void ordinary_sub_matrix(Pmatrix /*A*/, Pmatrix /*A_sub*/, int /*i1*/, int /*i2*/, int /*j1*/, int /*j2*/);
extern void insert_sub_matrix(Pmatrix /*A*/, Pmatrix /*A_sub*/, int /*i1*/, int /*i2*/, int /*j1*/, int /*j2*/);
#endif /*  matrix_header_included */
