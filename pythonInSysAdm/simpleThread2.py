#!/usr/bin/python
import subprocess
import time

IP_LIST = [ 'google.com',
	'yahoo.com',
	'amazon.com',
	'clearink.com',
	'ironport.com' ]

cmdStub = 'ping -c 5 %s'

def ping(addr):
	print time.asctime(), "Doing ping for", addr
	cmd = cmdStub % (addr, )
	return subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE)
z = []

for ip in IP_LIST:
	p = ping(ip)
	z.append((p, ip))

for p, ip in z:
	print time.asctime(), "Waiting for", ip
	p.wait()
	print time.asctime(), ip, "returned", p.returncode

