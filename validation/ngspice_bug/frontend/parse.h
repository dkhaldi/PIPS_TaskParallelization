/*************
 * Header file for parse.c
 * 1999 E. Rouat
 * $Id: parse.h 5188 2011-12-31 09:49:52Z coelho $
 ************/

#ifndef _PARSE_H
#define _PARSE_H

#include <pnode.h>
#include <wordlist.h>

struct pnode * ft_getpnames(wordlist *wl, bool check);
#ifndef free_pnode
#define free_pnode(ptr)  free_pnode_x(ptr); ptr=NULL;
#endif
void free_pnode_x(struct pnode *t);


#endif
