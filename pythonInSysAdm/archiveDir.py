#!/usr/bin/python

import os
import tarfile

tar = tarfile.open('temp.tar', 'w')

for root, Dir, files in os.walk('/tmp'):
	for File in files:
		fullPath = os.path.join(root, File)
		tar.add( fullPath )

tar.close()
		
