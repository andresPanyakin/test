# -*- coding: utf-8 -*-
import urllib2, urllib, cookielib, socket

host = 'play.google.com'
get = '/store'


s = socket.socket( socket.AF_INET, socket.SOCK_STREAM )
s.connect( (host, 80))

head = "GET " + get + " HTTP/1.1\n"
head += "Host: " + host + "\n"

head += "User-Agent: Mozilla/5.0 (X11; U; Linux i686; ru; rv:1.9.0.9) Gecko/2009041500 SUSE/3.0.9-0.1.1 Firefox/3.0.9\n"

head += "Accept: text/html,application/xhtml+xml, application/xml;q=0.9,*/*;q=0.8\n"
head += "Accetp-Language: ru,en-us;q=0.7,en;q=0.3\n"
head += "Accept-Charset: windows-1251, utf-8;q=0.7,*;q=0.7\n"
head += "Connection: close\n\n"

s.send( head )
buff = ""
result = ""

while 1:
	buff = s.recv(1024)
	if buff: result += buff
	else: break
	
s.close()
print result
