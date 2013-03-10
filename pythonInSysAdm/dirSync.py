#!/usr/bin/python

from threading import Timer
import sys
import time
import copy
import os
from subprocess import call

class EventLoopDelaySpawn(obj):
	def __init__(self, poll=10, wait=1, verbose=True, dir1='/tmp/dir1', dir2='/tmp/dir2'):
		self.poll = int(poll)
		self.wait = int(wait)
		self.verbose = verbose
		self.dir1 = dir1
		self.dir2 = dir2

	def poller(self):
		time.sleep(self.poll)
		if self.verbose:
			print "Polling at %s sec interval" % self.poll

	def action(self):
		if self.verbose:
			print 'waiting %s secs to run Action' % self.wait
		ret = call('rsync -av --delete %s/ %s' % (self.dir1, self.dir2), shell=True)

	def eventHandler(self):
		if os.listdir(self.dir1) != os.listdir(self.dir2):
			print os.listdir(self.dir1)
			t = Timer((self.wait), self.action)
			t.start()
			if self.verbose:
				print "Event registered"
			else:
				if self.verbose:
					print 'no event registered'

	def run(self):
		try:
			while 1:
				self.eventHandler()
				self.poller()
		except Exception, err:
			print "Error: %s" % err

		finally:
			sys.exit(0)
E = EventLoopDelaySpawn()
E.run()

