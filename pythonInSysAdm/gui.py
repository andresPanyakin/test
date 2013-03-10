#!/usr/bin/python

import pygtk
import gtk
import time

class SimpleButtonApp(object):
	def __init__(self):
		self.window = gtk.Window(gtk.WINDOW_TOPLEVEL)
		self.window.connect('destroy', self.quit)
		self.button = gtk.Button('Click me')
	
		self.button.connect('clicked', self.update_button_label, None)
		self.window.add(self.button)

		self.button.show()
		self.window.show()

	def update_button_label(self, widget, data=None):
		self.button.set_label(time.asctime())

	def quit(self, widget, data=None):
		gtk.main_quit()

	def main(self):
		gtk.main()

if __name__=='__main__':
	s = SimpleButtonApp()
	s.main()

