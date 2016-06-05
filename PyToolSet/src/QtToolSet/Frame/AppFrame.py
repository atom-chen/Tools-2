# -*- coding: utf-8 -*-

'''
@brief application
'''

from PyQt5.QtWidgets import QApplication
import sys

class AppFrame(QApplication):
    def __init__(self):
        super(AppFrame, self).__init__(sys.argv);
        
        from QtToolSet.Common.MApp import MApp;
        
        self.mApp = MApp();
        self.mApp.init();
        
        from QtToolSet.Frame import MainWindow;

        self.mMainWindow = MainWindow.MainWindow(self);
        self.mMainWindow.show();
        self.mMainWindow.raise_();

