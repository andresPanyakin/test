#!/usr/bin/python
# -*- coding: utf-8 -*-

import mrimsmssender
from optparse import OptionParser
import locale

parser = OptionParser()
parser.add_option("-n", "--number", action="store", dest="phone", type="string", help="Phone number. Ex: +79221412345")
parser.add_option("-t", "--text", action="store", dest="text", type="string", help="Sms content")
parser.add_option("-l", "--login", action="store", dest="login", type="string", help="Email address")
parser.add_option("-p", "--password", action="store", dest="passwd", type="string", help="Your password")

if __name__ == "__main__":
    encode = locale.getdefaultlocale()
    (options, args) = parser.parse_args()
    if options.phone is None or options.text is None \
        or options.login is None or options.passwd is None \
        or len(options.phone) < 12 or len(options.phone) > 13 or options.phone[0] != "+":
        parser.print_help()
        exit()
    options.text = options.text.decode(encode[1])
    print "sending..."
    if mrimsmssender.send_sms(options.login, options.passwd, options.phone, options.text):
        print "ok!"
    else:
        print "ooops. error."
