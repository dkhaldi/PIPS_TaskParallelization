/*************
* Header file for hpgl.c
* $Id: hpgl.h 5188 2011-12-31 09:49:52Z coelho $
************/

#ifndef HPGH_H
#define HPGH_H 

int GL_Init(void);
int GL_NewViewport(GRAPH *graph);
int GL_Close(void);
int GL_Clear(void);
int GL_DrawLine(int x1, int y1, int x2, int y2);
int GL_Arc(int x0, int y0, int r, double theta1, double theta2);
int GL_Text(char *text, int x, int y);
int GL_DefineLinestyle();
int GL_SetLinestyle(int linestyleid);
int GL_SetColor(int colorid);
int GL_Update(void);

#endif /* HPGH_H */
