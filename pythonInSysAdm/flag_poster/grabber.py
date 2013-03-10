# -*- coding: utf8 -*-

##	\file	grabber.py
##	\brief	Реализация граббера

import logging
import time

import config as conf
from checker import Checker

__author__ = 'sima, rockosov'

conf.configuration_logging()

class Grabber( object ):
	"""
	\brief	Grabber - класс граббера.
			Создает для каждого IP адреса чекер и стартует их
	"""
	def __init__( self ):
		logging.debug( 'Initialize' )
		
		for addr in conf.evil_ip_list:
			checker = Checker( addr )
			checker.start()
			
		
