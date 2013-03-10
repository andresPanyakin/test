#!/usr/bin/python
#coding=utf-8

from sqlalchemy import create_engine
from sqlalchemy import Table, Column, Integer, String, MetaData, ForeignKey
from sqlalchemy.orm import mapper, sessionmaker

import os

path = '/tmp'

#Создание механизма
engine = create_engine('sqlite:///:memory:', echo=False)

#Создание метаданных
metaData = MetaData()
fileSystemTable = Table( 'fileSystem', metaData, Column('Id', primary_key=True), Column('path', String(500)), Column('File', String(255)) )
metaData.create_all(engine)

#Класс отображения.
class FileSystem(object):
	def __init__(self, path, File):
		self.path = path
		self.File = File

	def __repr(self):
		return "[FileSystem('%s','%s')]" % ( self.path, self.File )

#Функция отображения
mapper( Filesystem, fileSystem )

Session = sessionmaker( bind = engine, autoflush = True, transactional = True)
session = Session()

#Обход файловой системы и заполнение баз даннх результатами.
for dirPath, dirNames, fileNames in os.walk( path ):
	for File in fileNames:
		fullPath = os.path.join( dirPath, File )
		record = FileSystem( fullPath, File )
		session.save( record )

#подтверждение записи данных в базу.
session.commit()

#Запрос
for record in sessin.query( Filesystem ):
	print "Database Record Number: %s, Path: %s, File: %s"\
		% (record.Id, record.path, record.File)


	
