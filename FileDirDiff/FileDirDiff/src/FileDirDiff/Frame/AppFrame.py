# -*- coding: utf-8 -*-
'''
Created on 2013-4-23

@author: Administrator
@brief application
'''

from PyQt5.QtWidgets import QApplication
import sys

class AppFrame(QApplication):
    def __init__(self):
        super(AppFrame, self).__init__(sys.argv)
        
        from FileDirDiff.Frame import MainWindow

        self.mainWindow = MainWindow.MainWindow(self)
        self.mainWindow.show()
        self.mainWindow.raise_()
