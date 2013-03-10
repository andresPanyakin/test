#!/usr/bin/python

import os
import sys

path = "/tmp/"


def enumeratePaths(path=path):
	pathCollection = []
	for dirPath, dirNames, fileNames in os.walk(path):
		for File in fileNames:
			fullPath = os.path.join(dirPath, File)
			pathCollection.append(fullPath)
	return pathCollection

def enumerateFiles(path=path):
	fileCollection = []
	
	for dirPath, dirNames, fileNames in os.walk(path):
		for File in fileNames:
			fileCollection.append(File)
	return fileCollection


def enumerateDir(path=path):
	dirCollection = []
	
	for dirPath, dirNames, fileNames in os.walk(path):
		for directory in dirNames:
			dirCollection.append(directory)

	return dirCollection

if __name__ == '__main__':
	if len(sys.argv) > 1:
		path = sys.argv[1]

	print '\nrecursive listing of all paths in dir:'
	for path in enumeratePaths(path):
		print path 

	print '\nrecursive listing of all files in dir:'
	for File in enumerateFiles(path):
		print File

	print '\nRecursive listing of all dirs in dir:'
	for directory in enumerateDir(path):
		print directory
