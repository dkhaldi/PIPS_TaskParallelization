#! /usr/bin/env python

# grrr...
from __future__ import print_function

from pyps import workspace

with workspace('hello_world.c', recoverInclude=True, deleteOnClose=True) as w:
	# save does some post-filtering to recover includes
	w.save()
	f = open(w.tmpdirname + '/hello_world.c')
	for l in f.readlines():
		print(l,end='')
	f.close()
