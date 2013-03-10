#!/usr/bin/python
import gtk

class logViewer(object):
	def __init__(self):
		#Main window of app
		self.window = gtk.Window(gtk.WINDOW_TOPLEVEL)
		self.window.set_size_request(640, 480)
		self.window.maximize()

		self.window.connect("destroy", self.quit)
		self.outerVbox = gtk.VBox()

		self.toolbar = gtk.Toolbar()
		openIcon = gtk.Image()
		quitIcon = gtk.Image()

		openIcon.set_from_stock(gtk.STOCK_OPEN, gtk.ICON_SIZE_LARGE_TOOLBAR)
		quitIcon.set_from_stock(gtk.STOCK_QUIT, gtk.ICON_SIZE_LARGE_TOOLBAR)

		self.open_button = gtk.ToolButton(icon_widget=openIcon)
		self.quit_button= gtk.ToolButton(icon_widget=quitIcon)

		self.open_button.connect('clicked', self.show_file_chooser)
		self.quit_button.connect('clicked', self.quit)

		self.toolbar.insert(self.open_button, 0)
		self.toolbar.insert(self.quit_button, 1)

		self.file_chooser = gtk.FileChooserWidget()
		self.file_chooser.connect('file_activated', self.load_logfile)

#Представление данных, имеющих вид списка.
		self.loglines_store = gtk.ListStore(int, str, str, int, str)
		self.loglines_tree = gtk.TreeView(model=self.loglines_store)

		self.add_column(self.loglines_tree, 'Line Number', 0)
		self.add_column(self.loglines_tree, 'Remote Host', 1)
		self.add_column(self.loglines_tree, 'Status', 2)
		self.add_column(self.loglines_tree, 'Bytes Sent', 3)
		self.add_column(self.loglines_tree, 'Logline', 4)

		self.loglines_window = gtk.ScrolledWindow()

		self.window.add(self.outerVbox)
		self.outerVbox.pack_start(self.toolbar, False, False)
		self.outerVbox.pack_start(self.loglines_window)
		self.loglines_window.add(self.loglines_tree)

		self.window.show_all()
		self.file_chooser.hide()

		def addColumn(self, TreeView, title, cou)


