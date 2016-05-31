# -*- coding: utf-8 -*-
'''
Created on 2013-4-24

@author: Administrator
'''

from PyQt5 import QtWidgets

import FileDirDiff.UI.ui_loggerwin

class LoggerWin(QtWidgets.QDockWidget):    
    def __init__(self):
        super(LoggerWin, self).__init__()

        self.ui = FileDirDiff.UI.ui_loggerwin.Ui_LoggerWin()
        self.ui.setupUi(self)
