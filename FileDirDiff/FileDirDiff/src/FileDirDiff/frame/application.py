# -*- coding: utf-8 -*-
'''
Created on 2013-4-23

@author: Administrator
@brief application
'''

from PySide.QtGui import QApplication
import sys

class Application(QApplication):
    def __init__(self):
        super(Application, self).__init__(sys.argv)
        
        from autoupdate.frame import mainwindow

        self.mainWindow = mainwindow.MainWindow(self)
        self.mainWindow.show()
        self.mainWindow.raise_()
