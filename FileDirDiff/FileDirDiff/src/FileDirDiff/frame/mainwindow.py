# -*- coding: utf-8 -*-
'''
Created on 2013-4-23

@author: Administrator
@brief mainwindow
'''

from PySide import QtCore
from PySide import QtGui

import autoupdate.ui.ui_mainwindow
import autoupdate.frame.loggerwin
import autoupdate.frame.leftfnwin
from autoupdate.core import config
from autoupdate.core import appdata
from autoupdate.core.logger import Logger
from autoupdate.core.utils import ParamInfo

from autoupdate.core.IAppData import IAppData

class MainWindow(QtGui.QMainWindow):
    
    instance = None
    
    def __init__(self, app):
        # make sure multiple instantiation won't happen
        assert(MainWindow.instance is None)
        MainWindow.instance = self

        super(MainWindow, self).__init__()

        self.app = app
        
        self.ui = autoupdate.ui.ui_mainwindow.Ui_MainWindow()
        self.ui.setupUi(self)
        
        # 可停靠的窗口
        self.m_LoggerWin = autoupdate.frame.loggerwin.LoggerWin()
        self.addDockWidget(QtCore.Qt.BottomDockWidgetArea, self.m_LoggerWin)
        
        # 左边可停靠窗口
        self.m_LeftFnWin = autoupdate.frame.leftfnwin.LeftFnWin()
        self.addDockWidget(QtCore.Qt.LeftDockWidgetArea, self.m_LeftFnWin)
        
        # 显示初始化单件
        config.Config.instance()
        config.Config.instance().readInit('config.txt')
        # 写配置文件
        #config.Config.instance().swiftVersion()
        config.Config.instance().saveCFG()
        
        # 实例化,共享数据
        #appdata.AppData.instance()
        IAppData.pInstance = appdata.AppData()
        appdata.AppData.instance().savaDirMd()

        Logger.instance()
        ParamInfo.instance()
        
        self.m_qttimer = QtCore.QTimer()
        QtCore.QObject.connect(self.m_qttimer, QtCore.SIGNAL("timeout()"), self.onTimer)
        self.m_qttimer.start( 1000 )

    def onTimer(self):
        listdata = []
        Logger.instance().getlogger(listdata)
        for dataitem in listdata:
            self.m_LoggerWin.ui.textEdit.appendPlainText(dataitem)
