# -*- coding: utf8 -*-

##	\file	poison.py
##	\brief	Реализация функций работы с ядовитыми запросами

import os
import sys
import logging
import inspect

import config as conf
import exploits.base

__author__ = 'sima, rockosov'

conf.configuration_logging()

class PoisonFunc( object ):
	"""
	\brief	PoisonFunc - класс ядовитой функции
	"""
	def __init__( self, func, name, addr ):
		self.func = func				#!< Исполняемая функция
		self.name = name				#!< Имя функции
		self.addr = addr 				#!< Адрес с которым работает функция
	"""
	\brief	execute - Метод безопасно исполняет функцию  при условии, что она включена
	\return Метод возвращает список флагов
	"""	
	def execute( self ):
		flags_list = []
		try:
			flags_list = self.func( self.addr ) 
		except:
			logging.warn( 'Exeption while execute poison "%s" ' % self.name )
			pass
		return flags_list
		
def	get_poison( addr ):
	"""
	\brief	get_poison - Создает список ядовитых функций
	\return	Список ядовитых функций
	"""
	modules = []			#!< Имена загруженных модулей
	ret = []				#!< Список ядовитых функций
	# Перебирем файлы в папке exploits
	for fname in os.listdir( conf.PLUGIN_PATH ):
		if fname.endswith( '.py' ):
			module_name = fname[: -3]
			if module_name != 'base' and module_name != '__init__':
				# Загружаем модуль и добавляем его имя в список загруженных модулей
				package_obj = __import__( conf.PLUGIN_PATH + '.' +  module_name )
				modules.append( (module_name, package_obj) )
	
	for module in modules:
		module_obj = getattr( module[1], module[0] )
		# Перебираем все, что есть внутри модуля
		for elem in dir( module_obj ):
			obj = getattr( module_obj, elem )
			if inspect.isclass( obj ):
				# Если класс производный от PosionBase
				if issubclass( obj, exploits.base.PoisonBase ):
					# Создаем экземпляр класса PoisonFunc
					poison_func = PoisonFunc( obj().run, obj().name, addr )
					ret.append( poison_func )
	return ret
