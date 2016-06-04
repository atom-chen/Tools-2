# -*- coding: utf-8 -*-

'''
'''

from PyQt5 import QtWidgets

import PyToolSet.UI.ui_loggerwin

class LoggerWin(QtWidgets.QDockWidget):    
    def __init__(self):
        super(LoggerWin, self).__init__()

        self.ui = PyToolSet.UI.ui_loggerwin.Ui_LoggerWin()
        self.ui.setupUi(self)
