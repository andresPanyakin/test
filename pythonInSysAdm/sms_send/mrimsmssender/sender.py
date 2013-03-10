# -*- coding: utf-8 -*-

import core
from mmptypes import *
import utils
import asyncore
import socket
import traceback
import logging
import sys
import time

class MMPConnection(core.Client):
	def __init__(self, user, password, logger):
		self.user = user
		self.password = password
		core.Client.__init__(self, self.user, self.password, logger, 'Python MMP Library 0.1', STATUS_ONLINE)
		self.run()
		
	def handle_expt(self):

		self.failure_exit("Connection has been closed abnormally")
		
	def handle_close(self):

		if self.state == 'init':
			self.get_server(self.servportdata)
		else:
			self.failure_exit("Connection reset by peer")
		
	def handle_error(self):

		t, err, tb = sys.exc_info()
		if t == socket.error:
			reason = utils.socket_error(err)
			if self.state == 'init':
				if reason != 'Broken pipe':
					self.failure_exit("Can't get address of target server (%s)" % reason)
			else:
				self.failure_exit(reason)
		else:
			traceback.print_exc()

	def exit(self):
		self.mmp_connection_close()
		
	def run(self, server=None, port=None):
		self.create_socket(socket.AF_INET, socket.SOCK_STREAM)
		self.log(logging.INFO, "Getting address of target server from mrim.mail.ru:2042")
		s = server or 'mrim.mail.ru'
		p = port or 2042
		try:
			self.connect((s, p))
		except socket.error, e:
			reason = utils.socket_error(e)
			self.failure_exit("Can't get address of target server (%s)" % reason)
			
	def main_connect(self):
		self.create_socket(socket.AF_INET, socket.SOCK_STREAM)
		self.log(logging.INFO, "Connecting to %s:%s" % (self.mrim_host_ip, self.mrim_host_port))
		self.connect((self.mrim_host_ip, self.mrim_host_port))
			
def logger_init(l):
	formatter = logging.Formatter('%(asctime)s %(message)s', '%d/%m/%y-%H:%M:%S')
	log_file_handler = logging.StreamHandler()
	log_file_handler.setFormatter(formatter)
	logger = logging.getLogger('mrim')
	logger.addHandler(log_file_handler)
	if l == 'debug':
		level = logging.DEBUG
	elif l == 'info':
		level = logging.INFO
	elif l == 'warning':
		level = logging.WARNING
	elif l == 'error':
		level = logging.ERROR
	elif l == 'critical':
		level = logging.CRITICAL
	else:
		level = logging.CRITICAL
	logger.setLevel(level)
	return logger

def asyncore_loop():
	asyncore.loop(1, use_poll=True)

def in_contacs(mmp, phone_number):
    contact_list = mmp.contact_list
    for user in contact_list.users:
        phones = contact_list.users[user]['phones'].split(',')
        if phone_number[1:] in phones:
            return True
    return False

def send_sms(email, passwd, phone_number, text):
    if type(text) != type(unicode()):
        raise UnicodeError
    logger = logger_init('critical')
    mmp = MMPConnection(email, passwd, logger)

    daemon = utils.start_daemon(asyncore_loop, (), 'asyncore_loop')
    
    time.sleep(5) # без таймаута оно бывает глючит
    
    run = 1
    send = 0
    while run:
        if mmp.state == "closed":
            run = 0
            break
        if mmp.state == "session_established":
            if in_contacs(mmp, phone_number):
                try:
                    mmp.mmp_send_sms(phone_number, text.encode("cp1251"))
                except:
                    run = 0
                    break
                send = 1
                run = 0
                break
            else:
                try:
                    mmp.mmp_add_sms_contact(phone_number[1:])
                except:
                    run = 0
                    break
                time.sleep(3)
                try:
                    mmp.mmp_send_sms(phone_number, text.encode("cp1251"))
                except:
                    run = 0
                    break
                send = 1
                run = 0
                break
    mmp.close()
    
    return send
