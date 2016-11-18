# $Id: gfc2pips.mk 23065 2016-03-02 09:05:50Z coelho $
#
# Copyright 1989-2016 MINES ParisTech
#
# This file is part of PIPS.
#
# PIPS is free software: you can redistribute it and/or modify it
# under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# any later version.
#
# PIPS is distributed in the hope that it will be useful, but WITHOUT ANY
# WARRANTY; without even the implied warranty of MERCHANTABILITY or
# FITNESS FOR A PARTICULAR PURPOSE.
#
# See the GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with PIPS.  If not, see <http://www.gnu.org/licenses/>.
#



# PIPS Libraries
ROOT=../../../../../..
PROJECT = pips
MAKE.d = $(ROOT)/makes
include $(ROOT)/makes/root.mk
include $(ROOT)/makes/arch.mk

LIBS_PIPS_DIR = $(ROOT)/lib/$(ARCH)
# repeat workspace to try to work around cycles...
# prettyprint: find_or_create_allocatable_struct
LIBS_PIPS = \
	$(LIBS_PIPS_DIR)/libsyntax.a \
	$(LIBS_PIPS_DIR)/libalias-classes.a \
	$(LIBS_PIPS_DIR)/libeffects-util.a \
	$(LIBS_PIPS_DIR)/libprettyprint.a \
	$(LIBS_PIPS_DIR)/libworkspace-util.a \
	$(LIBS_PIPS_DIR)/libcontrol.a \
	$(LIBS_PIPS_DIR)/libri-util.a \
	$(LIBS_PIPS_DIR)/libworkspace-util.a \
	$(LIBS_PIPS_DIR)/libtext-util.a \
	$(LIBS_PIPS_DIR)/libnaming.a \
	$(LIBS_PIPS_DIR)/libmisc.a \
	$(LIBS_PIPS_DIR)/libnewgen.a \
	$(NEWGEN_ROOT)/lib/$(ARCH)/libgenC.a \
	$(LINEAR_ROOT)/lib/$(ARCH)/libpolynome.a \
	$(LINEAR_ROOT)/lib/$(ARCH)/libvecteur.a \
	$(LINEAR_ROOT)/lib/$(ARCH)/libsc.a \
	$(LINEAR_ROOT)/lib/$(ARCH)/libcontrainte.a \
	$(LINEAR_ROOT)/lib/$(ARCH)/libarithmetique.a \
	-lm

PIPS_INC_POST += -I$(NEWGEN_ROOT)/include/ -I$(PIPS_ROOT)/include/ -I $(LINEAR_ROOT)/include/


