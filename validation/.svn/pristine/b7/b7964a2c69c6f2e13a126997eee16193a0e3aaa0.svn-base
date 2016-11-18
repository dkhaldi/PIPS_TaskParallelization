#! /usr/bin/env python

from pyps import workspace

# build direct & indirect callees for m
def calls(w, m):
	recall = set(c.name for c in w[m].callees)
	for c in w[m].callees:
		recall.update(calls(w, c.name))
	return sorted(recall)

w = workspace('calls.c', deleteOnClose=True)

# note: sorted(w.fun) is not helpful
for m in sorted(f.name for f in w.fun):
	print("%s: %s" % (m, calls(w, m)))

w.close()
