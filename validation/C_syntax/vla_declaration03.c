/* Bug: the parser has lost the type of p when analyzing
 * p->N5. However, if foo is declared on one line, the parser is OK
 * (see vla_declaration01.c). The difference between the two files
 * is/seems to be purely syntactical...
 *
 */

typedef struct
{
  int N1;
  int N2;
  int N3;
  int N4;
  int N5;
} param;


void foo(param* p, 
	 float bar[p->N5]);
