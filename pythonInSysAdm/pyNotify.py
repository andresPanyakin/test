#!/usr/bin/python

import os
import time
import sys
from pyinotify import  WatchManager, Notifier, ProcessEvent, EventsCodes


class PClose( ProcessEvent ):
	def __init__(self, path):
		self.path = path
	
	def process_IN_CLOSE(self, event):
		path = self.path
		if event.name:
			self.File = "%s" % os.path.join( event.path, event.name )
		else:
			self.File = "%s" % event.path
		print "%s Closed" % self.File
		print 'perfoming pretend action on %s...' % self.File
		time.sleep(2)
		print "%s has been processed" % self.File

class Controller( object ):
	def __init__(self, path='/tmp'):
		self.path = path
	
	def run(self):
		self.pclose = PClose(self.path)
		PC = self.pclose
		mask = EventsCodes.ALL_FLAGS['IN_CLOSE_WRITE'] | EventsCodes.ALL_FLAGS['IN_CLOSE_NOWRITE']

		wm = WatchManager()
		notifier = Notifier( wm, PC)
		print 'monitoring of %s started' % self.path
		addedFlag = False
	
		while 1:
			try:
				if not addedFlag:
					wm.add_watch(self.path, mask)
					addedFlag = True
				notifier.process_events()
				if notifier.check_events():
					notifier.read_events()
			except KeyboardInterrupt:
				print 'stop monitoring'
				notifier.stop()
				break
			except Exception as err:
				print err
	
def main():
	monitor = Controller()
	monitor.run()

if __name__ == '__main__':
	main()

