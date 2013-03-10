# -*- coding: utf8 -*-

##	\file	start_ufogp.py
##	\brief	Скрипт для старта приложения

import sys
import signal
import config as conf
from grabber import Grabber

__author__ = 'sima, rockosov'

def ufogp_init():
	"""
	\brief	ufogp_init - инициализация приложения
	"""
	grabber = Grabber()

if __name__ == '__main__':
	ufogp_init()

