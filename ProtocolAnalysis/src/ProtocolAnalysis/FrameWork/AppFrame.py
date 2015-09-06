# -*- coding: utf-8 -*-

'''
@brief 自己的程序框架
'''

from PyQt5.QtWidgets import QApplication
import sys

class AppFrame(QApplication):
    def __init__(self):
        super(AppFrame, self).__init__(sys.argv)
        
        from ProtocolAnalysis.FrameWork import MainWindow

        self.mainWindow = MainWindow.MainWindow(self)
        self.mainWindow.show()
        self.mainWindow.raise_()

