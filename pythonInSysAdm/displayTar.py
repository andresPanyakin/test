#!/usr/bin/python

import tarfile 

tar = tarfile.open('temp.tar', 'r')

print tar.list()
