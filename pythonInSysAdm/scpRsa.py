#!/usr/bin/python

import paramiko

hostName = '127.0.0.1'
port = 22
userName = 'andres'
pkeyFile = '/home/andres/.ssh/id_rsa'

if __name__ == '__main__':
	key = paramiko.RSAKey.from_private_key_file(pkeyFile)
	s = paramiko.SSHClient()
	s.load_system_host_keys()
	s.connect( hostName, port, pkey=key )
	stdin, stdout, stderr = s.exec_command('ifconfig')
	print stdout.read()
	s.close()
