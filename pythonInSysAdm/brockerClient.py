#!/usr/bin/python

from twisted.spread import pb
from twisted.internet import reactor

def handleErr(reason):
	print 'error: ', reason
	reactor.stop()

def callLs(def_CallObj):
	return def_CallObj.callRemote('ls', '/var/' )

def printLs(printResult):
	print printResult
	reactor.stop()

if __name__ == '__main__':
	factory = pb.PBClientFactory()
	reactor.connectTCP( 'localhost', 9876, factory )
	d = factory.getRootObject()
	d.addCallback( callLs )
	d.addCallback( printLs )
	d.addErrback( handleErr )
	reactor.run()
