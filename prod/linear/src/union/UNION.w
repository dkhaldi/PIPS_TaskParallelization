%%
%% $Id: UNION.w 1641 2016-03-02 08:20:19Z coelho $
%%
%% Copyright 1989-2016 MINES ParisTech
%%
%% This file is part of Linear/C3 Library.
%%
%% Linear/C3 Library is free software: you can redistribute it and/or modify it
%% under the terms of the GNU Lesser General Public License as published by
%% the Free Software Foundation, either version 3 of the License, or
%% any later version.
%%
%% Linear/C3 Library is distributed in the hope that it will be useful, but WITHOUT ANY
%% WARRANTY; without even the implied warranty of MERCHANTABILITY or
%% FITNESS FOR A PARTICULAR PURPOSE.
%%
%% See the GNU Lesser General Public License for more details.
%%
%% You should have received a copy of the GNU Lesser General Public License
%% along with Linear/C3 Library.  If not, see <http://www.gnu.org/licenses/>.
%%

% title 	: Extension de C3 aux Unions de Poly�dres.
% author      	: Arnauld LESERVOT
% begin date  	: 10/93
% file name 	: UNION.w 
% called file 	: path.eps, disjunct.eps






% ---------- Dimensions et style
\documentstyle[a4,11pt,leservot-fre]{report}

% Il semble que ceci ne soit pas interprete de la meme facon par
% le latex sur les sun (colle la marge droite) et sur babar (correct).
\addtolength{\textwidth}{2cm}
\addtolength{\leftmargin}{-1cm}

%\title{Extension de C3 aux Unions de Poly�dres}
%\author{Arnauld LESERVOT}
%\date{\today}



% ---------- Debut document
\begin{document}
%\maketitle
\input{union-CEA-title}
\tableofcontents
\newpage

% ---------- Introduction
\chapter{Introduction} 

\paragraph{N�cessit� de l'union de poly�dres.}
Les poly�dres convexes sont intens�ment 
utilis�s dans le parall�liseur automatique Linear/C3 Library~\cite{IJT91},
notamment pour le calcul des d�pendances de donn�es.

La m�thode de Feautrier pour
calculer un graphe de d�pendance exact, l'Array Data Flow 
Graph~\cite{Fea91b}, fournit une fonction source pour chaque
op�rande du programme s�quentiel � traiter.

Cette fonction source est pr�sent�e sous forme 
de {\em quast} (QUasi Affine S�lection Tree), 
c'est � dire sous forme d'un arbre de d�cision : 
arbre binaire dont les noeuds sont des syst�mes 
d'�quations et d'in�quations lin�aires. 
La figure~\ref{decision-fig} repr�sente un tel arbre.

\begin{figure}
\[ \Ifthenelse{n - 3 \leq i \leq 2n - 2}
	{\mbox{op�ration 1}}
	{ \Ifthenelse{i \leq 4n + 5}
		{\mbox{op�ration 2}}
		{\mbox{op�ration 3}}
	}
\]
\caption{Un arbre de d�cision}
\label{decision-fig}
\end{figure}

Chaque feuille de l'arbre est acceptable si le chemin
qui la gouverne est vrai : on obtient ainsi, pour chaque op�rande
du programme, un ensemble de solutions conditionn�es par un pr�dicat.

Si nous reprenons l'exemple de la figure~\ref{decision-fig},
l'op�ration 2 est gouvern�e par $i \leq 4n+5 \wedge \neg ( n - 3
\leq i \leq 2n - 2)$. Ce pr�dicat est un {\em chemin} dans l'arbre de
d�cision. Il peut �tre mis sous forme d'une {\em disjonction}
�quivalente : $i \leq n - 4  \vee 2n-1 \leq i \leq 4n+5$.
Ces disjonctions proviennent de la prise, dans l'arbre de d�cision,
d'une branche fausse : la n�gation d'un syst�me ayant plus
d'une in�quation est une union de poly�dres.

L'objet de ce rapport est de pr�senter les structures de
bases d�finissant ces deux types de donn�es, ainsi que les
fonctions les manipulant. Nous nous attacherons plus
particuli�rement � r�duire le nombre des disjonctions
�quivalentes � un chemin. 


\paragraph{C3 et son extension aux unions.}
La biblioth�que d'Alg�bre lin�aire C3, �crite en C, regroupe les
structures de vecteur, de matrice, 
de polyn�me, de syst�me d'�quations ou
d'in�quations en nombre entiers et de poly�dre,
ainsi que les fonctions de manipulation de ces structures.
Le lecteur est renvoy� � \cite{Anc91} et \cite{Lam93} pour
plus d'information sur cette biblioth�que.

{\em Poly�dre} d�signe, ici comme dans C3,
un poly�dre convexe dans un espace de dimension finie : il 
est donc repr�sentable par un syst�me d'�quations ou 
d'in�quations lin�aires ou par un syst�me g�n�rateur
de points, droites et rayons. Nous renvoyons le lecteur
�~\cite{Hal79} pour plus de d�tails. 
C'est la repr�sentation sous forme de syst�me qui sera 
utilis�e ici. Les poly�dres seront not�s dans la suite $P_{i}$. 

Les structures de donn�es et les fonctions ont �t�
implant� en C et con�u pour s'int�grer � la
biblioth�que d'alg�bre lin�aire C3.

\paragraph{Travaux similaires.}
D. Wilde d�crit dans \cite{Wil93} une
extension de C3-IRISA pour contenir les unions de poly�dres. La structure
de chemin n'y est cependant pas repr�sent�e et la fonction de
diff�rence, n'�tant pas bas�es sur les chemins, n'int�gre
pas les r�ductions introduites dans ce rapport.

Citons aussi les travaux de Pugh~\cite{Pug91} � l'universit� de
Maryland dont le calculateur symbolique Omega r�alise des
op�rations similaires � celles de C3 augment� des unions. 
La structure de chemin n'y est par contre pas particuli�rement �tudi�e. 


\paragraph{Plan du rapport.}
Le chapitre ~\ref{strucom-chap} pr�sente une structure de donn�e
r�utilis�e par la suite pour d�crire les disjonctions et les
chemins : la liste de syst�mes. Le chapitre~\ref{disjonction-chap}
d�crit les disjonctions et le chapitre~\ref{chemin-chap} les
chemins. Les fonctions de lecture et d'�critures des disjonctions et
des chemins sont pr�sent�es au chapitre~\ref{lectec-chap}.


\paragraph{Remerciements.}
Je remercie B. Apvrille pour ces remarques ainsi que pour sa contribution 
� certaines des fonctions pr�sent�es ici.



% ---------- Structures Communes
\chapter{Structures Communes}
\label{strucom-chap}
@i sc_list.w


% ---------- Disjonctions
\chapter{Les Disjonctions}
\label{disjonction-chap}
@i disjunct.w


% ---------- Chemins
\chapter{Les Chemins}
\label{chemin-chap}
@i path.w

% ---------- Reduction
\chapter{R�duction des hyperplans redondants}
\label{reduc-chap}
@i reduc.w


% ---------- Entree-Sortie
\chapter{Lecture-�criture}
\label{lectec-chap}
@i sl_io.w


% ---------- Bibliographie
\bibliographystyle{alpha}
\bibliography{/gandhi/home1/s8/leservot/Biblio/biblio,/gandhi/local/pips/Pcp/Biblio/pcp}
\addcontentsline{toc}{chapter}{Bibliographie}


% ---------- Annexes
\appendix
\chapter{Index g�n�ral}

\paragraph{Fichiers g�n�r�s}
@f

\paragraph{Macros d�finies}
@m

\paragraph{Fonctions et termes index�s}
@u


\chapter{LCZOS.F}
\label{lczos-annexe}
\begin{verbatim}
       program lczos
       real alpha(400), a(400,400), beta(400), real y(400,400), x(400)
       real Norm1, Norm2(400), gamma(400,400), yp(400,400)
       do 3 i = 1, n
          alpha(i) = 0.0
3         beta(i) = 0.0
       do 5 i = 1, n
5         y(i, 1) = 0.0
       Norm1 = 0.0
       do 10 i = 1, n
10        Norm1 = Norm1 + x(i)*x(i)
       Norm1 = 2*Norm1
       do 20 i = 1, n
20        y(i,1) = x(i)/Norm1
       do 30 i = 1, n
          gamma(i,1) = 0.0
          do 30  k = 1, n
30           gamma(i,1) = gamma(i,1) + a(i,k)*y(k,1)
       do 40 i = 1, n
40        alpha(1) = alpha(1)+ gamma(i,1)*y(i,1)
       do 50 i = 1, n
50        yp(i,2) = gamma(i,1) - alpha(1)*y(i,1)
       Norm2(1) = 0.0
       do 60 i = 1, n
60        Norm2(1) = Norm2(1) + yp(i,2)*yp(i,2)
       beta(1) = sqrt(Norm2(1))
       do 70 i = 1, n
70        y(i,2) = yp(i,2)/ beta(1)
       do 800 j = 2, m-1
          do 300 i = 1, n
             gamma(i,j) = 0.0
             do 300  k = 1,n
300             gamma(i,j) = gamma(i,j) + a(i,k)*y(k,j)
          do 400 i = 1, n
400          alpha(j) = alpha(j)+ gamma(i,j)*y(i,j)
          do 500 i = 1,n
500          yp(i, j+1) = gamma(i,j)-alpha(j)*y(i,j)- beta(j-1)*y(i,j-1)
          Norm2(j) = 0.0
          do 600 i = 1, n
600           Norm2(j) = Norm2(j) + yp(i,j+1)*yp(i,j+1)
              beta(j) = sqrt(Norm2(j))
          do 700 i = 1, n
700           y(i,j+1) = yp(i,j+1)/ beta(j)
800    continue
       end
\end{verbatim}


\chapter{D�monstration des r�gles 1, 2, 3.}
\label{demo-annexe}
\input{/gandhi/home1/s8/leservot/These/avancement-regles}


\chapter{Types et ent�te}
\label{entete-annexe}
\section{Fichier des types.} Ce fichier comprend la d�finition des types et des
red�finitions de fonctions pour des questions de compatibilit� avec
les versions ant�rieures.
@o union-local.h @{
@< Type @> 
/* FOR BACKWARD COMPATIBILITY */
#define my_sc_full()         sc_full()
#define my_sc_empty()        sc_empty((Pbase) NULL)
#define is_sc_my_empty_p(ps) sc_empty_p((ps))
#define is_dj_full_p(dj)     dj_full_p((dj))
#define is_dj_empty_p(dj)    dj_empty_p((dj))
#define is_pa_full_p(pa)     pa_full_p((pa))
#define is_pa_empty_p(pa)    pa_empty_p((pa))


/* FOR BACKWARD COMPATIBILITY */
#define sc_difference(ps1, ps2)      pa_system_difference_ofl_ctrl((ps1),(ps2),FWD_OFL_CTRL)
#define sc_inclusion_p(ps1, ps2)     pa_inclusion_p_ofl_ctrl((ps1), (ps2), NO_OFL_CTRL)
#define sc_inclusion_p_ofl(ps1, ps2) pa_inclusion_p_ofl_ctrl((ps1), (ps2), FWD_OFL_CTRL)
#define sc_inclusion_p_ofl_ctrl(ps1, ps2, ofl) pa_inclusion_p_ofl_ctrl((ps1), (ps2), (ofl))
#define sc_equal_p(ps1,ps2)          pa_system_equal_p_ofl_ctrl((ps1), (ps2), NO_OFL_CTRL)
#define sc_equal_p_ofl(ps1,ps2)      pa_system_equal_p_ofl_ctrl((ps1), (ps2), FWD_OFL_CTRL)
#define sc_equal_p_ofl_ctrl(ps1, ps2, ofl) pa_system_equal_p_ofl_ctrl((ps1), (ps2), (ofl))
#define sc_convex_hull_equals_union_p(conv_hull, ps1, ps2) \
  pa_convex_hull_equals_union_p_ofl_ctrl((conv_hull), (ps1), (ps2),NO_OFL_CTRL, FALSE)
#define sc_convex_hull_equals_union_p_ofl(conv_hull, ps1, ps2) \
  pa_convex_hull_equals_union_p_ofl_ctrl((conv_hull), (ps1), (ps2), OFL_CTRL, FALSE)
#define sc_convex_hull_equals_union_p_ofl_ctrl(conv_hull, ps1, ps2, ofl, bo) \
  pa_convex_hull_equals_union_p_ofl_ctrl((conv_hull), (ps1), (ps2), (ofl), (bo))

/* OTHERS */
#define sc_elim_redund_with_first(ps1, ps2) sc_elim_redund_with_first_ofl_ctrl((ps1), (ps2), NO_OFL_CTRL)

#define dj_fprint(fi,dj,fu)           dj_fprint_tab((fi), (dj), (fu), 0)
#define DJ_UNDEFINED_P(dj)            ((dj) == DJ_UNDEFINED)
#define dj_faisabilite(dj)            dj_feasibility_ofl_ctrl((dj), NO_OFL_CTRL)
#define dj_feasibility(dj)            dj_feasibility_ofl_ctrl((dj), NO_OFL_CTRL)
#define dj_faisabilite_ofl(dj)        dj_feasibility_ofl_ctrl((dj), FWD_OFL_CTRL)
#define dj_intersection(dj1, dj2)     dj_intersection_ofl_ctrl((dj1), (dj2), NO_OFL_CTRL)
#define dj_intersect_system(dj,ps)    dj_intersect_system_ofl_ctrl((dj), (ps), NO_OFL_CTRL ) 
#define dj_intersect_djcomp(dj1,dj2)  dj_intersect_djcomp_ofl_ctrl( (dj1), (dj2), NO_OFL_CTRL )
#define dj_projection_along_variables(dj,pv) \
  dj_projection_along_variables_ofl_ctrl((dj),(pv),NO_OFL_CTRL)
#define dj_variable_substitution_with_eqs(dj,co,pv) \
  dj_variable_substitution_with_eqs_ofl_ctrl( (dj), (co), (pv), NO_OFL_CTRL )

#define pa_fprint(fi,pa,fu)           pa_fprint_tab((fi), (pa), (fu), 0)
#define PA_UNDEFINED_P(pa)            ((pa) == PA_UNDEFINED)
#define pa_new()                      pa_make(NULL, NULL)
#define pa_faisabilite(pa)            pa_feasibility_ofl_ctrl((pa), NO_OFL_CTRL)
#define pa_feasibility(pa)            pa_feasibility_ofl_ctrl((pa), NO_OFL_CTRL)
#define pa_faisabilite_ofl(pa)        pa_feasibility_ofl_ctrl((pa), FWD_OFL_CTRL)
#define pa_path_to_disjunct(pa)       pa_path_to_disjunct_ofl_ctrl((pa), NO_OFL_CTRL )
#define pa_path_dup_to_disjunct(pa)   pa_path_to_disjunct_ofl_ctrl((pa), NO_OFL_CTRL )
#define pa_system_difference(ps1,ps2) pa_system_difference_ofl_ctrl((ps1),(ps2),NO_OFL_CTRL)
#define pa_system_equal_p(ps1,ps2)    pa_system_equal_p_ofl_ctrl((ps1),(ps2),NO_OFL_CTRL)
#define pa_inclusion_p(ps1,ps2)       pa_inclusion_p_ofl_ctrl((ps1),(ps2),NO_OFL_CTRL)
#define pa_path_to_disjunct_ofl(pa)   pa_path_to_disjunct_ofl_ctrl((pa), FWD_OFL_CTRL )
#define pa_path_to_disjunct_rule4(pa) pa_path_to_disjunct_rule4_ofl_ctrl((pa), FWD_OFL_CTRL )
#define pa_path_to_few_disjunct(pa)   pa_path_to_few_disjunct_ofl_ctrl((pa), NO_OFL_CTRL)
#define pa_system_difference(ps1,ps2) pa_system_difference_ofl_ctrl((ps1),(ps2),NO_OFL_CTRL)
#define pa_convex_hull_equals_union_p(conv_hull, ps1, ps2) \
  pa_convex_hull_equals_union_p_ofl_ctrl((conv_hull), (ps1), (ps2), NO_OFL_CTRL, FALSE)

#define un_fprint(fi,un,fu,ty)        un_fprint_tab((fi), (un), (fu), (ty), 0)


/* Misceleanous (debuging...) */
#define PATH_MAX_CONSTRAINTS          12

#define IS_SC                         1
#define IS_SL                         2
#define IS_DJ                         3
#define IS_PA                         4

extern char* (*union_variable_name)(Variable);

#if(defined(DEBUG_UNION_C3) || defined(DEBUG_UNION_LINEAR))
#define C3_DEBUG( fun, code )         \
  {if(getenv("DEBUG_UNION")){fprintf(stderr,"[%s]\n", fun); {code}}}
#define C3_RETURN( type, val )      \
  {if(getenv("DEBUG_UNION")){ \
     char* val1 = (char*) val; \
     fprintf(stderr,"Returning:\n"); \
     un_fprint_tab(stderr,(char*)val1,union_variable_name,type,1); return val1;} \
   else{ return val; }}
#else 
#define C3_DEBUG( fun, code )
#define C3_RETURN( type, val )        {return val;}
#endif

/* For the parsers: */
extern void sl_init_lex();
extern int slx_parse ();
@}

\section{Ent�te de fichiers C.}
@d includes @{
/* Package  :	C3/union
 * Author   : 	Arnauld LESERVOT (leservot(a)limeil.cea.fr)
 * Date     :	
 * Modified :   04 04 95
 * Documents:   UNION.tex : ``Extension de C3 aux unions de polyedres''
 * Comments :
 */
/* 
 *                  WARNING
 * 
 *   THOSE FUNCTIONS ARE AUTOMATICALLY DERIVED 
 *    
 *           FROM THE WEB SOURCES !
 */

/* Ansi includes        */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <sys/time.h>

/* Linear includes      */
#include "boolean.h"
#include "arithmetique.h"
#include "vecteur.h"
#include "contrainte.h"
#include "sc.h"
#include "sommet.h"
#include "polyedre.h"
#include "union.h" 

@}



\end{document}

