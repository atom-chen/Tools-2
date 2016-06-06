# -*- coding: utf-8 -*-

'''
@brief mainwindow
'''

from PyQt5 import  QtWidgets, QtCore

import QtToolSet.UI.ui_mainwindow
import QtToolSet.Frame.LoggerWin
import QtToolSet.Frame.LeftFnWin
from QtToolSet.Common.QtToolSetSys import QtToolSetSys
from Libs.FrameWork.Ctx import Ctx

class MainWindow(QtWidgets.QMainWindow):
    
    instance = None;
    
    def __init__(self, app):
        # make sure multiple instantiation won't happen
        assert(MainWindow.instance is None);
        super(MainWindow, self).__init__();
        
        MainWindow.m_instance = self;
        self.m_app = app;
        
        self.createUI();
        QtToolSetSys.instance().mWinLogDeviceProxy.setLogWin(self.m_LoggerWin);


    def createUI(self):
        self.ui = QtToolSet.UI.ui_mainwindow.Ui_MainWindow();
        self.ui.setupUi(self);
        
        # 可停靠的窗口
        self.m_LoggerWin = QtToolSet.Frame.LoggerWin.LoggerWin();
        self.addDockWidget(QtCore.Qt.BottomDockWidgetArea, self.m_LoggerWin);
        
        # 左边可停靠窗口
        self.m_LeftFnWin = QtToolSet.Frame.LeftFnWin.LeftFnWin();
        self.addDockWidget(QtCore.Qt.LeftDockWidgetArea, self.m_LeftFnWin);
        
        self.m_qttimer = QtCore.QTimer();
        self.m_qttimer.timeout.connect(self.onTimer);
        self.m_qttimer.start( 1000 );


    def onTimer(self):
        Ctx.instance().m_engineLoop.mainLoop();

