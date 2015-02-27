# -*- coding: utf-8 -*-
'''
Created on 2013-4-24

@author: Administrator
'''

from PySide import QtGui
import autoupdate.ui.ui_loggerwin

class LoggerWin(QtGui.QDockWidget):    
    def __init__(self):
        super(LoggerWin, self).__init__()

        self.ui = autoupdate.ui.ui_loggerwin.Ui_LoggerWin()
        self.ui.setupUi(self)
