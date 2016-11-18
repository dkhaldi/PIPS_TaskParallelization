/*************
 * Header file for spiceif.c
 * 1999 E. Rouat
 * $Id: spiceif.h 5188 2011-12-31 09:49:52Z coelho $
 ************/

#ifndef SPICEIF_H_INCLUDED
#define SPICEIF_H_INCLUDED

char * if_inpdeck(struct line *deck, INPtables **tab);
int if_run(char *t, char *what, wordlist *args, char *tab);
int if_option(void *ckt, char *name, int type, char *value);
void if_dump(void *ckt, FILE *file);
void if_cktfree(void *ckt, char *tab);
char * if_errstring(int code);
struct variable * spif_getparam(void *ckt, char **name, char *param, int ind, int do_model);
struct variable * spif_getparam_special(void *ckt,char **name,char *param,int ind,int do_model);
void if_setparam_model(void *ckt, char **name, char *val);
void if_setparam(void *ckt, char **name, char *param, struct dvec *val, int do_model);
int  if_analQbyName(void *ckt, int which, void *anal, char *name, IFvalue *parm);
bool if_tranparams(struct circ *ci, double *start, double *stop, double *step);
struct variable * if_getstat(void *ckt, char *name);

#ifdef EXPERIMENTAL_CODE
void com_loadsnap(wordlist *wl);
void com_savesnap(wordlist *wl);
#endif

#endif /* SPICEIF_H_INCLUDED */
