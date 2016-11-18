# $Id: local.mk 23065 2016-03-02 09:05:50Z coelho $
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

clean: NO_INCLUDES=1
export NO_INCLUDES

# old stuff:
# paf-util pip prgm_mapping scheduling static_controlize reindexing array_dfg
# paf-util and static_controlize habe been rehabilitated for PoCC

# there is no rationnal order to compile the libraries:-(
# see local TODO

# FI->FC: OK, cycles have been introduced, but then when do you
# declare the library list for linking? I did not find the information
# in Section 10.3 of the developper guide and it is not in the
# tutorial either. See Section 10.3.2, file $PIPS_ROOT/libraries.make

# all subdirectories that contain the PIPS libraries
all.dirs = \
	misc newgen properties text-util naming pipsdbm \
	top-level ri-util workspace-util conversion movements \
	comp_sections transformer bootstrap control flint \
	syntax c_syntax modeling prettyprint alias-classes points-to pointer_values \
	effects-generic effects-simple semantics complexity \
	continuation reductions effects-convex \
	effects-util callgraph icfg ricedg \
	chains rice hyperplane transformations syntheses accel-util hwac expressions \
	locality instrumentation hpfc atomizer safescale sac phrase wp65 \
	preprocessor pipsmake step to_begin_with gpu scalopes \
	static_controlize paf-util pocc-interface taskify rstream_interface \
	regions_to_loops task_parallelization

ifdef PIPS_SPECIAL
spec.libs = ../../src/Documentation/pipsmake/$(PIPS_SPECIAL).libs
# be resilient if the file list is not available
FWD_DIRS = $(shell test -e $(spec.libs) && cat $(spec.libs) || echo $(all.dirs))
else
FWD_DIRS	= $(all.dirs)
endif

# janusvalue
FWD_PARALLEL	= 1

ifeq ($(FWD_TARGET),phase0)
FWD_DEPS = 1
else ifeq ($(FWD_TARGET),phase2)
FWD_DEPS = 1
else ifeq ($(FWD_TARGET),phase3)
FWD_DEPS = 1
endif # phase/phase2/phase3

# (re)build inter library header dependencies
inc2deps.sh	= ../../makes/inc2deps.sh
# break some cycles manually
# check cycles with: "make -n phase0 2>&1 | grep Circ"
break_cycles	= sed \
	-e '/effects-simple:pointer_values/d' \
	-e '/effects-generic:pointer_values/d' \
	-e '/effects-generic:effects-convex/d' \
	-e '/effects-generic:semantics/d' \
	-e '/semantics:effects-convex/d' \
	-e '/semantics:points-to/d' \
	-e '/conversion:effects-convex/d' \
	-e '/chains:ricedg/d' \
	-e '/ricedg:rice/d' \
	-e '/paf-util:static_controlize/d' \
	-e '/top-level:pipsmake/d' \
	-e '/prettyprint:effects-/d' \
	-e '/prettyprint:points-to/d' \
	-e '/prettyprint:transformer/d' \
	-e '/prettyprint:semantics/d'
deps.mk:
	{ \
	  $(inc2deps.sh) $(FWD_DIRS) | \
	    $(break_cycles) | \
	    sed -e 's/:/:fwd-/;/^[^#]/s/^/fwd-/' | \
	    sort -u ; \
	} > $@
