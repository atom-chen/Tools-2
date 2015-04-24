# -*- coding: utf-8 -*-
'''
Created on 2013-4-23

@author: Administrator
@brief mainwindow
'''

from PyQt5 import  QtWidgets, QtCore

import FileDirDiff.UI.ui_mainwindow
import FileDirDiff.Frame.LoggerWin
import FileDirDiff.Frame.LeftFnWin
#from FileDirDiff.Core.GlobalIns import GlobalIns
from FileDirDiff.Core.AppSys import AppSys

class MainWindow(QtWidgets.QMainWindow):
    
    instance = None
    
    def __init__(self, app):
        # make sure multiple instantiation won't happen
        assert(MainWindow.instance is None)
        super(MainWindow, self).__init__()
        
        MainWindow.m_instance = self
        self.m_app = app
        
        self.createUI()
        #实例化全局变量
        #GlobalIns.insGlobal()
        AppSys.instance();
        AppSys.instance().postInit();


    def createUI(self):
        self.ui = FileDirDiff.UI.ui_mainwindow.Ui_MainWindow()
        self.ui.setupUi(self)
        
        # 可停靠的窗口
        self.m_LoggerWin = FileDirDiff.Frame.LoggerWin.LoggerWin()
        self.addDockWidget(QtCore.Qt.BottomDockWidgetArea, self.m_LoggerWin)
        
        # 左边可停靠窗口
        self.m_LeftFnWin = FileDirDiff.Frame.LeftFnWin.LeftFnWin()
        self.addDockWidget(QtCore.Qt.LeftDockWidgetArea, self.m_LeftFnWin)
        
        self.m_qttimer = QtCore.QTimer()
        self.m_qttimer.timeout.connect(self.onTimer)
        self.m_qttimer.start( 1000 )


    def onTimer(self):
        listdata = []
        AppSys.instance().m_logSys.getlogger(listdata)
        for dataitem in listdata:
            self.m_LoggerWin.ui.textEdit.appendPlainText(dataitem)

