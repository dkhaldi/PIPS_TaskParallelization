# $Id: Makefile 6575 2015-09-05 08:25:33Z coelho $

PARALLEL_VALIDATION = 1
include ../validate.mk

# ignore empty-line changes on mpeg2enc
mpeg2enc.validate: FLT = sed -e 's,$(here),$$VDIR,g;/^ *$$/d'
