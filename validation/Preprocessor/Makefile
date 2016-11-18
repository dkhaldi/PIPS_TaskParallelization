# $Id: Makefile 6589 2015-09-10 15:52:56Z coelho $

PARALLEL_VALIDATION = 1
include ../validate.mk

# hm... workaround
fixrts.validate laguer.validate: FLT += -e '/"<built-in>"/d'

clean: local-clean
local-clean:
	$(RM) source02.src/module0[12].s
