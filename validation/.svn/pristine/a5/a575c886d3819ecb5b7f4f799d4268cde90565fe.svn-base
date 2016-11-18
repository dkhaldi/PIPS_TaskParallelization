/* Double declaration of a global constant in a compilation unit used to be
   OK, even with -ansi and -pedantic, with older version of gcc

   But for which version of gcc? gcc (Ubuntu 4.4.1-4ubuntu9) 4.4.1

   $ gcc -c decl22.c
   decl22.c:10: error: redefinition of ‘MAK_not_byte’
   decl22.c:7: note: previous definition of ‘MAK_not_byte’ was here
 */

/* PIPS prettyprinter cannot debuild the source code properly */

const char * MAK_not_byte;

const char * MAK_not_byte = "L'image n'est pas du type BYTE";

/* A second initialization is not OK, even for gcc with no optionss beyong -c */
const char * MAK_not_byte = "L'image n'est pas du type BYTE";

int v;

int v;

/*
void decl22()
{
  int v;
  int v;
}
*/
