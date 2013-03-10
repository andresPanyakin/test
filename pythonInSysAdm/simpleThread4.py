#!/usr/bin/python

from threading import Thread
import subprocess
from Queue import Queue
import re

num_ping_threads = 3
num_arp_threads = 3

inQueue = Queue()
outQueue = Queue()
ips = ['127.0.0.1', '127.0.0.2', '127.0.0.3']

def pinger(i, iq, oq):
	while 1:
		ip = iq.get()
		print "Thread %s: Pinging %s" % (i, ip)
		ret = subprocess.call("ping -c 1 %s" % ip, shell=True,stdout=open('/dev/null','w'),stderr=subprocess.STDOUT)

		if ret == 0:
			oq.put(ip)
		else:
			print "%s did not respond" % ip
		iq.task_done()

def arping(i, oq):
	while 1:
		ip = oq.get()
		p = subprocess.Popen( 'arping -c 1 %s' % ip, shell=True, stdout=subprocess.PIPE)
		out = p.stdout.read()
		result = out.split()
		pattern = re.compile(":")
		mac = None
		for item in result:
			if re.search(pattern, item):
				mac = item
		print "IP addr: %s | mac addr: %s" % ( ip, mac)
		oq.task_done()

for ip in ips:
	inQueue.put(ip)

for i in range(num_ping_threads):
	worker = Thread(target=pinger, args=(i, inQueue, outQueue))
	worker.setDaemon(True)
	worker.start()

for i in range(num_arp_threads):
	worker = Thread(target=arping, args=(i, outQueue))
	worker.setDaemon(True)
	worker.start()

print "Main thread waiting"
inQueue.join()
outQueue.join()
print "Done"

