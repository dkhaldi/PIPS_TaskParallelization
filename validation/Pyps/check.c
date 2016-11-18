/*

  $Id: check.c 5188 2011-12-31 09:49:52Z coelho $

  Copyright 1989-2009 MINES ParisTech

  This file is part of PIPS.

  PIPS is free software: you can redistribute it and/or modify it
  under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  any later version.

  PIPS is distributed in the hope that it will be useful, but WITHOUT ANY
  WARRANTY; without even the implied warranty of MERCHANTABILITY or
  FITNESS FOR A PARTICULAR PURPOSE.

  See the GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with PIPS.  If not, see <http://www.gnu.org/licenses/>.

*/
#include <stdio.h>

int foo(int a) {
    return a;
}

void bar(int *c) {
    *c=foo(2);
}
void malabar(int *c) {
    *c=foo(3);
}

int megablast(int n)
{
    int i,j;
    for(i=0;i<n;i++)
        j=foo(i);
    return j;
}
int main(){
    printf("%d\n", megablast(2));
    return 0;
}