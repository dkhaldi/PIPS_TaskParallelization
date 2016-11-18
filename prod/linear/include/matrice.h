/* Warning! Do not modify this file that is automatically generated! */
/* Modify src/Libs/matrice/matrice-local.h instead, to add your own modifications. */

/* header file built by cproto */

#ifndef  matrice_header_included
#define  matrice_header_included
/*

  $Id: matrice-local.h 1641 2016-03-02 08:20:19Z coelho $

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

#if defined(__GNUC__)
// Comment this warning since no one has fixed this issue since the 90's...
//#warning matrice is obsolete, use matrix instead.
#endif

/* Les matrices sont des matrices pleines, a coefficients rationnels.
 *
 * Les matrices sont representes par des tableaux d'entiers mono-dimensionnels
 * dont l'element 0 represente le denominateur global. Elles sont
 * stockees par colonne ("column-major"), comme en Fortran. Les indices
 * commencent a 1, toujours comme en Fortran et non comme en C.
 * Les deux dimensions sont implicites et doivent etre passees en
 * parametre avec la matrice dans les appels de procedures.
 *
 * Le denominateur doit etre strictement positif, i.e. plus grand ou egal
 * a un. Un denominateur nul n'aurait pas de sens. Un denominateur negatif
 * doublerait le nombre de representations possibles d'une matrice.
 *
 * Les matrices renvoyees par certaines routines, comme matrice_multiply(),
 * ne sont pas normalisees par le pgcd des coefficients et du denominateur
 * pour des raisons d'efficacite. Mais les routines de test, comme
 * matrice_identite_p(), supposent leurs arguments normalises.
 *
 * Il faudrait sans doute introduire deux niveaux de procedure, un niveau
 * externe sur garantissant la normalisation, et un niveau interne efficace
 * sans normalisation automatique.
 *
 * La bibliotheque utilise une notion de sous-matrice, definie systematiquement
 * par un parametre appele "level". Seuls les elements dont les indices
 * de lignes et de colonnes sont superieurs a level+1 (ou level? FI->CA)
 * sont pris en consideration. Il s'agit donc de sous-matrice dont le
 * premier element se trouve sur la diagonale de la matrice complete et
 * dont le dernier element et le dernier element de la matrice complete.
 *
 * Note: en cas detection d'incoherence, Neil Butler renvoyait un code
 * d'erreur particulier; Francois Irigoin a supprime ces codes de retour
 * et a traite les exceptions par des appels a assert(), et indirectement
 * a abort()
 */

typedef Value * matrice;

#define MATRICE_UNDEFINED ((matrice) NULL)
#define MATRICE_NULLE ((matrice) NULL)

/* Allocation et desallocation d'une matrice */
#define matrice_new(n,m) ((matrice) malloc(sizeof(Value)*((n*m)+1)))
#define matrice_free(m) (free((char *) (m)))

/* Macros d'acces aux elements d'une matrice */

/* int ACCESS(int * matrix, int column, int i, int j): acces a l'element (i,j)
 * de la matrice matrix, dont la taille des colonnes, i.e. le nombre de 
 * lignes, est column.
 */
#define ACCESS(matrix,column,i,j) ((matrix)[(((j)-1)*(column))+(i)])

/* int DENOMINATEUR(matrix): acces au denominateur global d'une matrice matrix
 * La combinaison *(&()) est necessaire pour avoir des parentheses autour
 * de matrix[0] et pour pouvoir simultanement utiliser cette macro comme lhs.
 */
/* #define DENOMINATOR(matrix) *(&((matrix)[0])) */
#define DENOMINATOR(matrix) ((matrix)[0])

/* bool matrice_triangulaire_inferieure_p(matrice a, int n, int m):
 * test de triangularite de la matrice a
 */
#define matrice_triangulaire_inferieure_p(a,n,m) \
    matrice_triangulaire_p(a,n,m,true)

/* bool matrice_triangulaire_superieure_p(matrice a, int n, int m):
 * test de triangularite de la matrice a
 */
#define matrice_triangulaire_superieure_p(a,n,m) \
    matrice_triangulaire_p(a,n,m,false)

/* FI: Corinne, peux-tu expliquer la raison d'etre de cette macro? */
/* d'apres ce que je comprends de la suite, ca permet de definir
 * des sous-matrices dont le coin superieur droit (i.e. le premier
 * element) se trouve sur la diagonal?
 */
#define ACC_ELEM(matrix,column,i,j,level) \
    (matrix[((j)-1+(level))*(column) + (i) + (level)])

/* FI: Corinne, pourrais-tu nous eclairer sur la signification de ces
 * constantes?
 */
#define VALIDATION 0
/* FI #define NULL 0 */
#define MATRIX 0

/* definition temporaire d'une vraie fonction pour dbx */
/* #define matrice_print(a,n,m) matrice_fprint(stdout,a,n,m) */
/* determinant.c */
extern void matrice_determinant(matrice /*a*/, int /*n*/, Value /*result*/[]);
extern void matrice_sous_determinant(matrice /*a*/, int /*n*/, int /*i*/, int /*j*/, Value /*result*/[]);
/* hermite.c */
extern void matrice_hermite(Value */*MAT*/, int /*n*/, int /*m*/, Value */*P*/, Value */*H*/, Value */*Q*/, Value */*det_p*/, Value */*det_q*/);
extern int matrice_hermite_rank(matrice /*a*/, int /*n*/, int /*m*/);
extern int dim_H(matrice /*H*/, int /*n*/, int /*m*/);
/* inversion.c */
extern void matrice_unimodulaire_triangulaire_inversion(matrice /*u*/, matrice /*inv_u*/, int /*n*/, bool /*infer*/);
extern void matrice_diagonale_inversion(matrice /*s*/, matrice /*inv_s*/, int /*n*/);
extern void matrice_triangulaire_inversion(matrice /*h*/, matrice /*inv_h*/, int /*n*/, bool /*infer*/);
extern void matrice_general_inversion(matrice /*a*/, matrice /*inv_a*/, int /*n*/);
extern void matrice_unimodulaire_inversion(matrice /*u*/, matrice /*inv_u*/, int /*n*/);
/* matrice.c */
extern void matrice_transpose(matrice /*a*/, matrice /*a_t*/, int /*n*/, int /*m*/);
extern void matrice_multiply(matrice /*a*/, matrice /*b*/, matrice /*c*/, int /*p*/, int /*q*/, int /*r*/);
extern void matrice_normalize(matrice /*a*/, int /*n*/, int /*m*/);
extern void matrice_normalizec(matrice /*MAT*/, int /*n*/, int /*m*/);
extern void matrice_swap_columns(matrice /*matrix*/, int /*n*/, int /*m*/, int /*c1*/, int /*c2*/);
extern void matrice_swap_rows(matrice /*a*/, int /*n*/, int /*m*/, int /*r1*/, int /*r2*/);
extern void matrice_assign(matrice /*A*/, matrice /*B*/, int /*n*/, int /*m*/);
extern bool matrice_egalite(matrice /*A*/, matrice /*B*/, int /*n*/, int /*m*/);
extern void matrice_nulle(matrice /*Z*/, int /*n*/, int /*m*/);
extern bool matrice_nulle_p(matrice /*Z*/, int /*n*/, int /*m*/);
extern bool matrice_diagonale_p(matrice /*Z*/, int /*n*/, int /*m*/);
extern bool matrice_triangulaire_p(matrice /*Z*/, int /*n*/, int /*m*/, bool /*inferieure*/);
extern bool matrice_triangulaire_unimodulaire_p(matrice /*Z*/, int /*n*/, bool /*inferieure*/);
extern void matrice_substract(matrice /*a*/, matrice /*b*/, matrice /*c*/, int /*n*/, int /*m*/);
extern void matrice_soustraction_colonne(matrice /*MAT*/, int /*n*/, int /*m*/, int /*c1*/, int /*c2*/, Value /*x*/);
extern void matrice_soustraction_ligne(matrice /*MAT*/, int /*n*/, int /*m*/, int /*r1*/, int /*r2*/, Value /*x*/);
/* matrice_io.c */
extern void matrice_fprint(FILE */*f*/, matrice /*a*/, int /*n*/, int /*m*/);
extern void matrice_print(matrice /*a*/, int /*n*/, int /*m*/);
extern void matrice_fscan(FILE */*f*/, matrice */*a*/, int */*n*/, int */*m*/);
/* smith.c */
extern void matrice_smith(matrice /*MAT*/, int /*n*/, int /*m*/, matrice /*P*/, matrice /*D*/, matrice /*Q*/);
/* sous-matrice.c */
extern int mat_lig_nnul(matrice /*MAT*/, int /*n*/, int /*m*/, int /*level*/);
extern void mat_perm_col(matrice /*MAT*/, int /*n*/, int /*m*/, int /*k*/, int /*level*/);
extern void mat_perm_lig(matrice /*MAT*/, int /*n*/, int /*m*/, int /*k*/, int /*level*/);
extern void mat_min(matrice /*MAT*/, int /*n*/, int /*m*/, int */*i_min*/, int */*j_min*/, int /*level*/);
extern void mat_maj_col(matrice /*A*/, int /*n*/, int /*m*/, matrice /*P*/, int /*level*/);
extern void mat_maj_lig(matrice /*A*/, int /*n*/, int /*m*/, matrice /*Q*/, int /*level*/);
extern void matrice_identite(matrice /*ID*/, int /*n*/, int /*level*/);
extern bool matrice_identite_p(matrice /*ID*/, int /*n*/, int /*level*/);
extern int mat_lig_el(matrice /*MAT*/, int /*n*/, int /*m*/, int /*level*/);
extern int mat_col_el(matrice /*MAT*/, int /*n*/, int /*m*/, int /*level*/);
extern void mat_coeff_nnul(matrice /*MAT*/, int /*n*/, int /*m*/, int */*lg_nnul*/, int */*cl_nnul*/, int /*level*/);
#endif /*  matrice_header_included */
