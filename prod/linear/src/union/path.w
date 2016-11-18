%%
%% $Id: path.w 1641 2016-03-02 08:20:19Z coelho $
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


\section{Structure de donn�e}
\paragraph{Compl�mentaire d'un poly�dre.} 
On d�finit tout d'abord la structure de compl�mentaire
de poly�dre, Scomplement, qui est repr�sent� par le poly�dre
lui-m�me.
@d Type  @{ 
typedef Ssysteme *Pcomplement,Scomplement;

#define CO_UNDEFINED    (Pcomplement) NULL
@}

Notons que ce sont les solutions enti�res qui nous int�ressent. Le
compl�mentaire du poly�dre 
$\vec{x}.\vec{h} \geq 0$ est donc $\vec{x}.\vec{h} \leq -1$. 

La structure de liste de compl�mentaires est celle de Ssyslist :
@d Type  @{ typedef Ssyslist *Pcomplist,Scomplist; @}

\paragraph{Un chemin} est d�fini comme l'intersection
d'un poly�dre avec une suite de compl�mentaires
de poly�dres :
\[
{\cal C} = {\cal P}_{0} \bigwedge_{i=1}^{n} \neg {\cal P}_{i}
\]

Le chemin est repr�sent� par :
@d Type  @{
typedef struct Spath {
        Psysteme        psys;
        Pcomplist       pcomp;
        } *Ppath,Spath;

#define PA_UNDEFINED    (Ppath) NULL
@}

G�om�triquement, $\cal C$ est enti�rement inclus dans ${\cal P}_{0}$ et
la liste de compl�mentaires constitue en fait des
``encoches'' dans ce syst�me, comme on peut le
voir sur la figure~\ref{path-fig}.

\begin{figure} \alepsf{path.eps}{2/3} 
\caption{Une union vue comme chemin} \label{path-fig}
\end{figure}

Cette structure repr�sente efficacement le pr�dicat qui gouverne
un n{\oe}ud dans un arbre de d�cision. ${\cal P}_{0}$ correspond
� l'intersection de tous les pr�dicats des branches VRAI du chemin,
et chaque $\neg {\cal P}_{i}$ correspond � une branche fausse.
Cette repr�sentation, peu efficace pour le calcul de
l'union de deux chemins, est efficace pour le calcul de l'intersection.

La suite pr�sente les fonctions bas�es sur cette structure. 
Ces fonctions sont dans le fichier :
@O path.c  -d @{
@< includes @>
@< fonctions Ppath @>
@}

\paragraph{L'Union.}
Une union est repr�sentable par l'une des
deux mod�lisations d�crite pr�c�demment : disjonction ou chemin.
@d Type  @{
typedef struct Sunion {
        Pdisjunct       pdi;
        Ppath           ppa;
        } *Punion,Sunion;

#define UN_UNDEFINED    (Punion) NULL
#define UN_FULL_SPACE 	(Punion) NULL
#define UN_EMPTY_SPACE 	(Punion) NULL
@}

Seule la structure Sunion a �t� d�finie. Les fonctions
associ�es � cette structure n'ont pas �t� implant�.
Notons que cette structure, parce qu'elle ne rassemble
que des repr�sentations de poly�dres bas�s
sur des syst�mes lin�aires, ne prend pas 
en compte la repr�sentation par des points, rayons
et droites (syst�me g�n�rateur).


\section{Fonctions de base}
\subsection{Allocation, d�sallocation} 
\paragraph{pa\_make} alloue de la m�moire pour un chemin en
positionnant les champs suivant les variables entr�es.

La duplication totale {\bf pa\_dup} r�plique tous les
�l�ments d'un chemin, jusqu'aux Psystemes. 
La duplication partielle {\bf pa\_dup1} partage le syst�me $\cal
P_0$ et les compl�mentaires.

De m�me, les d�sallocations sont totales : {\bf pa\_free}, ou
partielles : {\bf pa\_free1}.
pa\_free(pa\_dup( pa )) et pa\_free1(pa\_dup1( pa )) sont neutres pour
la m�moire.
@D fonctions Ppath @{
/* Ppath pa_make(in_ps, in_pcomp)    AL 16/11/93
 * Allocates a Ppath and initialize it with in_ps and in_pcomp
 * SHARING.
 */
Ppath pa_make( in_ps, in_pcomp )
Psysteme in_ps;
Pcomplist in_pcomp;
{
  Ppath ret_pa = (Ppath) malloc( sizeof( Spath ) );
  if (ret_pa == NULL) {
    (void) fprintf(stderr,"pa_new: Out of memory space\n");
    exit(-1);
  }
  ret_pa->psys = in_ps; ret_pa->pcomp = in_pcomp;
  return ret_pa;
}


/* void pa_dup(Ppath pa) 	    AL 30/05/94 */
Ppath pa_dup(in_pa)
Ppath in_pa;
{
  if (in_pa == PA_UNDEFINED ) return PA_UNDEFINED;
  return pa_make( sc_dup(in_pa->psys), sl_dup(in_pa->pcomp) );
}

/* Ppath pa_free(Ppath pa) 	  BA, AL 30/05/94 */
Ppath pa_free(in_pa)
Ppath in_pa;
{
  if (in_pa != PA_UNDEFINED) {
    in_pa->psys  = sc_free(in_pa->psys);
    in_pa->pcomp = sl_free((Psyslist) in_pa->pcomp);
    free( in_pa ); in_pa = PA_UNDEFINED;
  }
  return((Ppath) PA_UNDEFINED);
}


/* void pa_dup1(Ppath pa) 		      AL 30/05/94
 * 1 depth duplication: system and complements are shared. 
 */
Ppath pa_dup1(in_pa)
Ppath in_pa;
{
  if (in_pa == PA_UNDEFINED) return PA_UNDEFINED;
  return pa_make( in_pa->psys, sl_dup1(in_pa->pcomp) );
}


/* Ppath pa_free1(Ppath pa) 	     BA, AL 30/05/94
 * 1 depth free. System and complement are not freed.
 */
Ppath pa_free1(in_pa)
Ppath in_pa;
{
  if (in_pa != PA_UNDEFINED) {
    sl_free1((Psyslist) in_pa->pcomp);
    free( in_pa ); in_pa = PA_UNDEFINED;
  }  
  return((Ppath) PA_UNDEFINED);
}
@| pa_make pa_dup pa_free pa_dup1 pa_free1 @}



\subsection{Chemins particuliers.}
\paragraph{pa\_full} est similaire � pa\_new. Il repr�sente l'espace entier.\\
{\bf pa\_full\_p} indique si un chemin repr�sente l'espace entier.\\
{\bf pa\_empty} � pour $\cal P_{0}$ le syst�me infaisable $1 = 0$, la
liste des compl�mentaires �tant vide. \\
{\bf pa\_empty\_p} est Vrai si le chemin est l'ensemble vide.

@D fonctions Ppath @{
/* Ppath pa_full()		   AL 18/11/93
 * Returns full space path : pa_full = pa_new()
 */
Ppath pa_full() { return pa_new(); }


/* pa_full_p( (Ppath) in_pa )   AL 18/11/93
 * Returns True if in_pa = (NIL) ^ (NIL)
 */
boolean pa_full_p( in_pa )
Ppath in_pa;
{
  return( (in_pa != PA_UNDEFINED) &&
	 ( in_pa->pcomp == NULL ) &&
	 ( in_pa->psys  == NULL ) );
}


/* Ppath	pa_empty()		      AL 18/11/93
 * Returns empty path : pa_empty = sc_empty(NULL) ^ (NIL)
 */
Ppath pa_empty() { return pa_make(sc_empty(NULL), NULL); }


/* pa_empty_p( (Ppath) in_pa )   AL 18/11/93
 * Returns True if in_pa = (1*TCST = 0) ^ (NIL)
 */
boolean pa_empty_p( in_pa )
Ppath in_pa;
{
  return( (in_pa != PA_UNDEFINED) &&
	 ( in_pa->pcomp == NULL ) &&
	 ( in_pa->psys != NULL ) &&
	 ( sc_empty_p( in_pa->psys ) ) );
}
@| pa_full pa_full_p pa_empty pa_empty @}


\subsection{Information}
\paragraph{pa\_max\_constraints\_nb} renvoie le nombre maximum de
contraintes des syst�mes contenus dans le chemin d'entr� 
{\tt in\_pa}. Une in�galit� est compt�e comme une contrainte
et une �galit� comme deux contraintes.

@D fonctions Ppath @{
/* int pa_max_constraints_nb( (Ppath) in_pa )
 * Give the maximum constraints nb among systems of in_pa. 
 */
int pa_max_constraints_nb( in_pa )
Ppath    in_pa;
{
  Psysteme   ps;
  int        loc, ret_int;

  if (PA_UNDEFINED_P(in_pa)||pa_full_p(in_pa)) return 0;
  if ( pa_empty_p(in_pa) )                     return 1;

  ps      = in_pa->psys; 
  ret_int = 2*(ps->nb_eq) + ps->nb_ineq;
  loc     = sl_max_constraints_nb( (Psyslist) in_pa->pcomp );
  
  if (loc > ret_int) ret_int = loc;
  return ret_int;
}
@| pa_max_constraints_nb @}





\section{Op�rations sur les chemins}
\subsection{Intersections}
\paragraph{pa\_intersect\_system} calcule l'intersection d'un chemin
avec un syst�me : $\cal C \wedge \cal P$. Complexit� de 1 :
simple intersection ${\cal P}_{0} \wedge \cal P$, sans test de
faisabilit�. 

@D fonctions Ppath @{
/* Ppath pa_intersect_system( (Ppath) in_pa, (Psysteme) in_ps )
 * Computes the intersection between in_pa and in_ps. AL 25/04/95
 * No sharing 
 */
Ppath pa_intersect_system( in_pa, in_ps )
Ppath    in_pa;
Psysteme in_ps;
{
  Psysteme ps;

  if (PA_UNDEFINED_P(in_pa)||SC_UNDEFINED_P(in_ps)) 
                            return PA_UNDEFINED;
  if ( pa_empty_p(in_pa) )  return pa_empty();
  if ( pa_full_p(in_pa) )   return pa_make(sc_dup(in_ps),NULL);
  
  ps = sc_normalize(sc_append( sc_dup(in_pa->psys), in_ps ));
  if (ps == NULL){ ps = sc_free(ps); return pa_empty(); }
  return pa_make(ps, sl_dup(in_pa->pcomp));
}
@| pa_intersect_system @}

\paragraph{pa\_intersect\_complement} calcule l'intersection
d'un chemin $C$ et d'un compl�mentaire : $\cal C \wedge \neg \cal
P$. Complexit� de 1 : simple ajout de $\cal P$ dans la liste des compl�mentaires.
@D fonctions Ppath @{
/* Ppath pa_intersect_complement( (Ppath) in_pa, (Pcomplement) in_pc )
 * Computes the intersection between in_pa and in_ps.  AL 17/11/93
 * No sharing 
 */
Ppath pa_intersect_complement( in_pa, in_pc )
Ppath       in_pa;
Pcomplement in_pc;
{
  Pcomplist  pc;
  Psysteme   ps;

  if (PA_UNDEFINED_P(in_pa)||SC_UNDEFINED_P(in_pc)) return PA_UNDEFINED;
  if (pa_empty_p(in_pa))                            return pa_empty();

  if (pa_full_p(in_pa)) ps = sc_full(); else  ps = sc_dup(in_pa->psys);
  pc = sl_append_system( sl_dup(in_pa->pcomp), sc_dup(in_pc) );
  return pa_make(ps, pc) ;
}
@| pa_intersect_complement @}


\subsection{Divers}
\paragraph{pa\_manage\_simple\_complement} calcule un chemin r�duit,
c'est � dire rep�re les compl�ments n'ayant qu'une seule
in�galit� et les int�gre au syst�me $\cal P_{0}$.
@D fonctions Ppath @{
/* Ppath pa_reduce_simple_complement( (Ppath) in_pa )		 AL 16/11/93
 * Scan all the complement. If one complement is a simple inequality,
 * its complement is computed and intersected with psys part of in_pa.
 * in_pa is modified. (Sharing with in_pa).
 */
Ppath pa_reduce_simple_complement( in_pa )
Ppath in_pa;
{
  Psysteme      pss;
  Pcomplist	pco, pco2 = NULL, tofree = NULL;
  Ppath         ret_pa;
  boolean       at_least_one = FALSE ; /* Do we have a simple complement ? */
  
  if( pa_full_p(in_pa) || pa_empty_p(in_pa) || (in_pa == PA_UNDEFINED) ) 
                return (in_pa);
  
  C3_DEBUG("pa_reduce_simple_complement", {
    fprintf(stderr, "Input path:\n");  
    pa_fprint_tab( stderr, in_pa, union_variable_name, 1 );
  });

  pss = in_pa->psys;
  for( pco = in_pa->pcomp, pco2 = NULL; pco != NULL; pco = pco->succ ) {
    Psysteme ps = pco->psys;
    
    if (ps == SC_UNDEFINED) { 
	pco2  = sl_free1(pco2); 
	in_pa = pa_free1(in_pa); 
	return PA_UNDEFINED ; 
    }
    else if (sc_empty_p(ps)) continue;
    else if ((ps->nb_ineq == 1) && (ps->nb_eq == 0)) {
      Pdisjunct dj = dj_system_complement( ps );
      pss          = sc_safe_append( pss, dj->psys );
      tofree       = sl_append_system( tofree, ps );
      dj           = dj_free( dj ); 
      at_least_one = TRUE;
    }
    else { pco2 = (Pcomplist) sl_append_system( pco2, ps ); }
  }

  if(!at_least_one) {
    pco2   = sl_free1(pco2);  
    ret_pa = in_pa;
  }
  else if(!sc_faisabilite_ofl(pss)) {
    pco2   = sl_free1( pco2   ); 
    tofree = sl_free1( tofree );
    in_pa  = pa_free ( in_pa  ); /* also frees pss */
    ret_pa = pa_empty(); 
  } 
  else {
    in_pa  = pa_free1( in_pa  ); 
    tofree = sl_free ( tofree );
    ret_pa = pa_make ( pss, pco2 );
  }

  C3_RETURN( IS_PA, ret_pa );
}
@| pa_reduce_simple_complement @}



\paragraph{pa\_transform\_eg\_in\_ineg} transforme toutes les
�galit�s des syst�mes composants {\tt in\_pa} en in�galit�s.
@D fonctions Ppath @{
/* Ppath pa_transform_eg_in_ineg( in_pa )
 * Transforms all equalities of all systems composing in_pa in
 * inequalities and returns in_pa.
 * in_pa is modified. (Sharing with in_pa).
 */
Ppath pa_transform_eg_in_ineg( in_pa )
Ppath in_pa;
{
  Pcomplist pco;

  if( pa_full_p(in_pa) || pa_empty_p(in_pa) || (in_pa == PA_UNDEFINED) ) 
                return (in_pa);
  
  sc_transform_eg_in_ineg( in_pa->psys );
  for( pco = in_pa->pcomp; pco != NULL; pco = pco->succ ) 
    { sc_transform_eg_in_ineg( pco->psys ); }

  return in_pa;
}
@| pa_transform_eg_in_ineg @}




\paragraph{pa\_feasibility\_ofl\_ctrl} est Vrai si le chemin est faisable. 
Elle transforme le chemin en disjonction
gr�ce � la fonction pa\_path\_to\_few\_disjunct()
et calcule sa faisabilit�.
@D fonctions Ppath @{
/* boolean pa_feasibility_ofl_ctrl( (Ppath) in_pa, int ofl_ctrl)   
 * Returns true if the input path is possible and FALSE if it 
 * is not possible or undefined.                 
 */
#ifdef TRACE_LINEAR_PATH
extern char* entity_local_name() ;
#endif 

boolean pa_feasibility_ofl_ctrl( in_pa, ofl_ctrl )
Ppath in_pa;
int ofl_ctrl;
{
  Pdisjunct  dj;
  Ppath      pa;
  boolean    ret_bo = FALSE;
#ifdef TRACE_LINEAR_PATH
  FILE*      report_file;
#endif 

  if ( PA_UNDEFINED_P( in_pa )) return FALSE;
  if ( pa_empty_p    ( in_pa )) return FALSE;
  if ( pa_full_p     ( in_pa )) return TRUE;
  
#ifdef TRACE_LINEAR_PATH
  /* Just to keep trace of input paths if wanted */
  if (getenv("KEEP_PATH") != (char*) NULL) {
    struct timeval  *tp = (struct timeval*)  malloc(sizeof(struct timeval));
    struct timezone *tz = (struct timezone*) malloc(sizeof(struct timezone));
    int seconds;
    gettimeofday( tp, tz ); seconds = tp->tv_sec;
    report_file = fopen("mail_those_paths_to_arnauld","a");
    pa_fprint( report_file, in_pa, union_variable_name );
    fprintf( report_file, "# %s", ctime( &(seconds) ));
    fprintf( report_file, 
	    "# Module:                            \t%s\n", db_get_current_module_name());
    fprintf( report_file, 
	    "# Input number of complement:        \t%d\n", sl_length(in_pa->pcomp)     );
    fprintf( report_file, 
	    "# Input max constrainst:             \t%d\n", pa_max_constraints_nb(in_pa));
    fflush ( report_file ); free( tp ); free( tz );
  }
#endif  

  pa = pa_supress_same_constraints( in_pa );
  dj = pa_path_to_few_disjunct_ofl_ctrl( pa, ofl_ctrl );
  if( dj_empty_p(dj) || (dj == NULL) ) ret_bo = FALSE;
  else                                 ret_bo = TRUE;


#ifdef TRACE_LINEAR_PATH
  /* keep trace of paths */
  if (getenv("KEEP_PATH") != (char*) NULL) {
    fprintf( report_file, 
	    "# Output number of disjunctions:     \t%d\n", sl_length(dj)            );
    fprintf( report_file, 
	    "# Output max constrainst:            \t%d\n", sl_max_constraints_nb(dj));
    fprintf( report_file, 
	    "# Feasible:                          \t%s\n", (ret_bo) ? "YES":"NO"    );
    fclose ( report_file );
  }
#endif 

  pa = pa_free( pa );  dj = dj_free( dj );
  return ret_bo;
}
@| pa_feasibility_ofl_ctrl @}


\section{Passage aux disjonctions}
\paragraph{pa\_path\_to\_disjunct\_ofl\_ctrl} calcule de fa�on
na�ve le chemin sous forme d'une disjonction. La complexit�
th�orique est exponentielle. Si le chemin a $n$ compl�ments de
$p$ in�galit�s, le calcul est effectu� en $n^p$. \\

@D fonctions Ppath @{
/* Pdisjunct pa_path_to_disjunct_ofl_ctrl
 *       ( (Ppath) in_pa, (int) ofl_ctrl)    
 * Produces a Pdisjunct corresponding to the path Ppath.
 * No sharing.
 */
Pdisjunct pa_path_to_disjunct_ofl_ctrl( in_pa, ofl_ctrl )
Ppath   in_pa;
int     ofl_ctrl;
{
  Pdisjunct       ret_dj;
  Pcomplist       comp;
  int             meth1 = 0, meth2 = 1; /* comparison between 2 methods */

  if ( in_pa == PA_UNDEFINED )   return DJ_UNDEFINED;
  if (pa_full_p(in_pa))          return dj_full();
  if (pa_empty_p(in_pa))         return dj_empty();
  if ((in_pa->psys != NULL) && 
	sc_empty_p(in_pa->psys)) return dj_empty();
  
  ret_dj = (Pdisjunct) sl_append_system(NULL, sc_dup(in_pa->psys)); 
  for( comp = in_pa->pcomp; comp != NULL; comp = comp->succ) {
    Pdisjunct dj1 = dj_system_complement( comp->psys ); 
    Pdisjunct dj2 = ret_dj;
    int       lg1 = sl_length( dj1 );
    int       lg2 = sl_length( dj2 );

    meth1 = meth1 + lg2*lg1 ; meth2 = meth2 * lg1;

    ret_dj        = dj_intersection_ofl_ctrl( ret_dj, dj1, ofl_ctrl);
    dj1           = dj_free( dj1 ); dj2 = dj_free( dj2 );
  }
	
  C3_DEBUG("pa_path_to_disjunct_ofl_ctrl", {
    fprintf(stderr, "Feasibility calls with method 1 and 2 : %d\t%d\n", 
		meth1, meth2);  
  });

  return( ret_dj );
}
@| pa_path_to_disjunct_ofl_ctrl@}
