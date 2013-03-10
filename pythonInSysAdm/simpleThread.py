#!/usr/bin/python

import threading
import time

count = 1

class SThread( threading.Thread ):
	def run(self):
		global count
		print "Thread # %s: Pretending to do stuff " % count
		count += 1
		time.sleep(2)
		print "done with stuff: %s\n" % count

for t in range(5):
	SThread().start()

