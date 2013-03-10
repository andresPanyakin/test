#!/usr/bin/python

import optparse
import ConfigParser

def readConfig(File='hello.ini'):
	Config = ConfigParser.ConfigParser()
	Config.read(File)
	sections = Config.sections()

	for section in sections:
		print Config.items(section)
		phrase = Config.items(section)[0][1]
		return phrase

def main():
	p = optparse.OptionParser()
	p.add_option('--sysadmin', '-s')
	p.add_option('--config', '-c', action='store_true')
	p.set_defaults(sysadmin='BOFH')

	options, arguments = p.parse_args()
	if options.config:
		options.sysadmin = readConfig()
	print 'Hello, %s' % options.sysadmin

if __name__ == '__main__':
	main()
	readConfig()
