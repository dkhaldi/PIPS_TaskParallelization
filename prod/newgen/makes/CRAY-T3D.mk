# $Id: CRAY-T3D.mk 1231 2016-03-02 08:16:46Z coelho $
#
# Copyright 1989-2016 MINES ParisTech
#
# This file is part of PIPS.
#
# PIPS is free software: you can redistribute it and/or modify it
# under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# any later version.
#
# PIPS is distributed in the hope that it will be useful, but WITHOUT ANY
# WARRANTY; without even the implied warranty of MERCHANTABILITY or
# FITNESS FOR A PARTICULAR PURPOSE.
#
# See the GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with PIPS.  If not, see <http://www.gnu.org/licenses/>.
#

include $(MAKE.d)/flags.mk

AR	= ar
ARFLAGS	= -rv
CC	= cc -T cray-t3d
CFLAGS	= -O 3
CMKDEP	= -M
LD	= $(CC)
RANLIB	= :
LEX	= lex
LFLAGS	=
FC	= cf77 -C cray-t3d
# -g suppresses all optimizations!
FFLAGS	= -O 1 -O scalar3
LINT	= lint
LINTFLAGS= -habxu
YACC	= yacc
YFLAGS	=
ETAGS	= etags
TAR	= tar
ZIP	= compress
DIFF	= diff
# the cray m4 results in some internal stack overflow on hpfc runtime...
M4	= gm4
M4FLAGS	=
LX2HTML	= latex2html
L2HFLAGS= -link 8 -split 5
LATEX	= latex
BIBTEX	= bibtex
MAKEIDX	= makeindex
DVIPS	= dvips
RMAN	= rman
