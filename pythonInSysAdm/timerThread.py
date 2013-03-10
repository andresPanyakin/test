#!/usr/bin/python
from threading import Timer
import sys
import time
import copy

if len(sys.argv) != 2:
	print 'must enter an interval'
	sys.exit(1)

def hello():
	print "Hello, i just got called after %s sec delay" % callTime

delay = sys.argv[1]
callTime = copy.copy(delay)

t = Timer(int(delay), hello)
t.start()

print "waiting %s secs to run function" % delay
for x in range(int(delay)):
	print "main prog is still running for %s more sec" % delay
	delay = int(delay) - 1
	time.sleep(1)

