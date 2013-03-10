#!/usr/bin/python
import os

class diskWalk(object):
	def __init__(self, path):
		self.path = path
	
	def enumeratePaths(self):
		pathCollection = []
		for dirPath, dirNames, fileNames in os.walk(self.path):
			for File in fileNames:
				fullPath = os.path.join(dirPath, File)
				pathCollection.append(fullPath)
		return pathCollection

	def enumerateFiles(self):
		fileCollection = []
		for dirPath, dirNames, fileNames in os.walk(self.path):
			for File in fileNames:
				fileCollection.append(File)
		return fileCollection

	def enumerateDir(self):
		dirCollection = []
		for dirPath, dirNames, fileNames in os.walk(self.path):
			for directory in dirNames:
				dirCollection.append(directory)
		return dirCollection


