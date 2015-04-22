# -*- coding: utf-8 -*-
'''
Created on 2013-4-23

@author: Administrator
@brief mainwindow
'''

from PyQt5 import  QtWidgets, QtCore

import FileDirDiff.ui.ui_mainwindow
import FileDirDiff.Frame.LoggerWin
import FileDirDiff.Frame.LeftFnWin
from FileDirDiff.Core import Config
from FileDirDiff.Core import AppData
from FileDirDiff.Core.Logger import Logger
from FileDirDiff.Core.Utils import ParamInfo

from FileDirDiff.Core.IAppData import IAppData

class MainWindow(QtWidgets.QMainWindow):
    
    instance = None
    
    def __init__(self, app):
        # make sure multiple instantiation won't happen
        assert(MainWindow.instance is None)
        MainWindow.instance = self

        super(MainWindow, self).__init__()

        self.app = app
        
        self.ui = FileDirDiff.ui.ui_mainwindow.Ui_MainWindow()
        self.ui.setupUi(self)
        
        # 可停靠的窗口
        self.m_LoggerWin = FileDirDiff.Frame.LoggerWin.LoggerWin()
        self.addDockWidget(QtCore.Qt.BottomDockWidgetArea, self.m_LoggerWin)
        
        # 左边可停靠窗口
        self.m_LeftFnWin = FileDirDiff.Frame.LeftFnWin.LeftFnWin()
        self.addDockWidget(QtCore.Qt.LeftDockWidgetArea, self.m_LeftFnWin)
        
        # 显示初始化单件
        Config.Config.instance()
        Config.Config.instance().readInit('config.txt')
        # 写配置文件
        #config.Config.instance().swiftVersion()
        Config.Config.instance().saveCFG()
        
        # 实例化,共享数据
        #appdata.AppData.instance()
        IAppData.pInstance = AppData.AppData()
        AppData.AppData.instance().savaDirMd()

        Logger.instance()
        ParamInfo.instance()
        
        self.m_qttimer = QtCore.QTimer()
        self.m_qttimer.timeout.connect(self.onTimer)
        self.m_qttimer.start( 1000 )

    def onTimer(self):
        listdata = []
        Logger.instance().getlogger(listdata)
        for dataitem in listdata:
            self.m_LoggerWin.ui.textEdit.appendPlainText(dataitem)
