# -*- coding: utf-8 -*-


#from PyQt5 import  QtWidgets, QtCore, QtGui
from PyQt5 import  QtWidgets, QtCore

import ProtocolAnalysis.UI.ui_mainwindow
from ProtocolAnalysis.FrameWork import LoggerWin, LeftFnWin
from ProtocolAnalysis.Core.AppSys import AppSys
from ProtocolAnalysis.Core.AppSysBase import AppSysBase


class MainWindow(QtWidgets.QMainWindow):


    instance = None


    def __init__(self, app):
        # make sure multiple instantiation won't happen
        assert(MainWindow.instance is None)
        MainWindow.instance = self

        super(MainWindow, self).__init__()

        self.app = app
        
        self.ui = ProtocolAnalysis.UI.ui_mainwindow.Ui_MainWindow()
        self.ui.setupUi(self)
        
        # 可停靠的窗口
        self.m_LoggerWin = LoggerWin.LoggerWin()
        self.addDockWidget(QtCore.Qt.BottomDockWidgetArea, self.m_LoggerWin)
        
        # 左边可停靠窗口
        self.m_LeftFnWin = LeftFnWin.LeftFnWin()
        self.addDockWidget(QtCore.Qt.LeftDockWidgetArea, self.m_LeftFnWin)
        
        # 实例化系统
        AppSys.instance();
        
        self.m_qttimer = QtCore.QTimer()
        self.m_qttimer.timeout.connect(self.onTimer)
        self.m_qttimer.start( 1000 )


    def onTimer(self):
        listdata = []
        AppSysBase.instance().getLoggerPtr().getlogger(listdata)
        for dataitem in listdata:
            self.m_LoggerWin.ui.textEdit.appendPlainText(dataitem)


