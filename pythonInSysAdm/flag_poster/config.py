# -*- coding: utf8 -*-

##	\file	config.py
##	\brief	Конфигурация программы

import logging

__author__ = 'sima, rockosov'

##	\brief	Настройки логирования
LOG_LEVEL = logging.DEBUG
LOG_FILE_NAME = 'ufogp.log'
LOG_TO_FILE = False
##  \brief  Конфигурация логгирования
def configuration_logging():
	if LOG_TO_FILE:
		logging.basicConfig( format='%(asctime)s || %(levelname)8s | %(threadName)10s || %(message)s', level=LOG_LEVEL, filename=LOG_FILE_NAME )
	else:
		logging.basicConfig( format='%(asctime)s || %(levelname)8s | %(threadName)10s || %(message)s', level=LOG_LEVEL )


##	\brief	Папка с плагинами
PLUGIN_PATH = 'exploits'

##	\brief	Период работы
TIME_TO_SLEEP_FOR_THREAD = 5

##	\brief	Адрес чекера
CHECKER_ADDR = '10.10.10.100'
CHECKER_PORT = 1234

##	\brief	создание списка IP
ip_template = '10.10.10.%d'	#<! Шаблон ip адресов
low_ip = 109						#<! Нижняя граница
high_ip = 111					#<! Верхняя граница
evil_ip_list = [ip_template % i for i in range( low_ip, high_ip )]


FLAGS_COUNTER = 0
