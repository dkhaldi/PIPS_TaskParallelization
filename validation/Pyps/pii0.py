# this test should be in a separate directory,
# as it generates local "a.out" and "basics.o" files
# which interact with other scripts...

import os
import pii

pii.Pii(["pii","basics0.c"]).run()
os.remove("a.out")
os.remove("basics0.o")
