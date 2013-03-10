#!/usr/bin/python

from threading import Thread
import subprocess
from Queue import Queue

numThreads = 3
queue = Queue()
ips = ['127.0.0.1', '127.0.0.2', '127.0.0.3']

def pinger(i, q):
	while 1:
		ip = q.get()
		print "Thread %s: pinging %s" % (i, ip)
		ret = subprocess.call("ping -c 1 %s" % ip, shell = True, stdout=open('/dev/null', 'w'),
							stderr = subprocess.STDOUT)
		if ret == 0:
			print '%s is alive\n' % ip
		else:
			print "%s: died\n" % ip
		
		q.task_done()

for i in range(numThreads):
	worker = Thread(target=pinger, args=(i, queue))
	worker.setDaemon(True)
	worker.start()

for ip in ips:
	queue.put(ip)
	print "main thread waiting\n"
	queue.join()
	print 'Done'

