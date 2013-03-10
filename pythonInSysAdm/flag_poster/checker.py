# -*- coding: utf8 -*-

##	\file	checker.py
##	\brief	Реализация чекера

import logging
import threading
import time
import socket

import config as conf
import poison

__author__ = 'sima, rockosov'

conf.configuration_logging()

class CheckerThread( threading.Thread ):
	"""
	\brief	CheckerThread - поток чекера 
			Вызывает ядовитые функции
	"""
	def __init__( self, dst_addr, stop_event ):
		self.stop_event = stop_event						#!< Событие остановки потока
		self.dst_addr = dst_addr							#!< Целевой адрес с которым работает поток
		self.sk = None										#!< Сокет, через который поток работает с чекером
		threading.Thread.__init__( self, name=dst_addr )
	
	def _connect_to_checker( self, addr, port ):
		"""
		\brief	_connect_to_checker - функция соединения с чекером 
		\return	возвращает сокет установленного соединения
		"""
		again = True
		
		# Пытаемся подключиться к чекеру каждые 10 секунд c таймаутом 5 секунд
		while again:
			try:	
				sk = socket.create_connection( (addr, port), 5 )
				again = False
			except:
				logging.warn( 'Failed to connect to checker at %s:%d' %(addr, port) )
				time.sleep(10)
			
		logging.debug( 'Connection with checker was established' )
		
		# ATTENTION: 	Здесь, если необходимо, задать получение приветственного сообщения
		# 				или другой инфы с постилки
		return sk
	
	def _send_flags( self, flags_list ):
		"""
		\brief	_send_flags - функция отправки флагов чекеру
		"""
		# Подключаемся к чекеру
		sk = self._connect_to_checker( conf.CHECKER_ADDR, conf.CHECKER_PORT )
		
		for flag in flags_list:
			# TODO: проверка флага.
			
			sk.send( flag )
			time.sleep(0.1)
		
		sk.close()
		
	def run( self ):
		
		logging.debug( 'Created checker for %s'%(self.dst_addr) )
		
		while True:				
			flags_list = list()	#!< Список фалгов, добытых чекером в текущем цикле	
					
			# Исполняем все ядовитые функции			
			for func in poison.get_poison( self.dst_addr ):
				flags_list += func.execute()
			
			conf.FLAGS_COUNTER += len( flags_list )
			
			# Если список не пустой,то вызываем функцию отправки флагов	
			if flags_list != []:
				logging.info( 'Flags: %s' %flags_list )
				self._send_flags( flags_list )
				
			time.sleep(conf.TIME_TO_SLEEP_FOR_THREAD)
			if self.stop_event.isSet():
				logging.debug( 'Thread %s will terminate'%(self.dst_addr) )
				break
			
			
class Checker( object ):
	"""
	\brief	Checker - класс чекера. 
			На каждый IP адрес будет создаваться свой чекер со своим потоком и списком ядовитых функций
			TODO: После остановки чекера и остановки потока, еще раз стартануть поток не получается
	"""
	def __init__( self, dst_addr ):
		self.dst_addr = dst_addr									#!< Удаленный адрес
		self.stop_event = threading.Event()							#!< Событие на остановку потока
		self.thread = CheckerThread( dst_addr, self.stop_event )	#!< Поток чекера
		
	def start( self ):
		"""
		\brief	start - старт чекера
		"""
		# Проверяем, что поток не запущен
		if self.thread.isAlive():
			logging.warning( 'Thread already started' )
			return
		
		# Запускаем поток 	
		self.thread.start()
		
	def stop( self ):
		"""
		\brief	stop - остановка чекера. TODO: пока не используется
		"""
		if self.stop_event.isSet():
			logging.warning( 'Stop event already set' )
			return
			
		self.stop_event.set() 
		
