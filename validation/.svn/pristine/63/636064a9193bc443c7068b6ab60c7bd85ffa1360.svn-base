#! /usr/bin/env python

from pyps import workspace

w = workspace('hello_world.c', recoverInclude=True, deleteOnClose=True)
# save does some post-filtering to recover includes
(files, headers) = w.save()

import os
# show regenerated file
os.system('cat ' + ' '.join(files))

# done
w.close()
