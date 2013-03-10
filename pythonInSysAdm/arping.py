#!/usr/bin/python

import subprocess
import re
import sys
from scapy.all import *


def arping( iprange = '127.0.0.1/24' ):
	conf.verb = 0
	ans, unans = srp(Ether(dst='ff:ff:ff:ff:ff:ff')/ARP(pdst=iprange), timeout=2)
	collection = []
	print ans
	for snd, rcv in ans:
		result = rcv.sprintf( r'%ARP.psrc% %Ether.src%').split()
		collection.append(result)
	return collection


if __name__ == '__main__':
	if len(sys.argv) > 1:
		for ip in sys.argv[1:]:
			print "arping: %s" % ip
			print arping(ip)
	else:
		print arping()
