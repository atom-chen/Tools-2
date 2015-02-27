# -*- coding: utf-8 -*-
'''
Created on 2013-5-15

@author: Administrator
'''

from PySide import QtCore, QtGui


import autoupdate.ui.ui_leftfnwin
from autoupdate.core.appdata import AppData
#from autoupdate.core.fileversioninfo import BuildFileVersion
from autoupdate.core.verthread import VerThread
from autoupdate.core.logger import Logger
from autoupdate.core import config
from autoupdate.core import appdata

class LeftFnWin(QtGui.QDockWidget):    
    def __init__(self):
        super(LeftFnWin, self).__init__()

        self.ui = autoupdate.ui.ui_leftfnwin.Ui_LeftFnWin()
        self.ui.setupUi(self)
        
        # 注册事件处理函数
        QtCore.QObject.connect(self.ui.m_btnCheck, QtCore.SIGNAL("clicked()"), self.onBtnClkCheck)
        QtCore.QObject.connect(self.ui.m_btnVersion, QtCore.SIGNAL("clicked()"), self.onBtnClkVersion)
        
        QtCore.QObject.connect(self.ui.m_btnVerSwf, QtCore.SIGNAL("clicked()"), self.onBtnClkVerSwf)

    # 生成当前版版本的 md5 文件
    def onBtnClkCheck(self):
        #AppData.instance().curmd5FileCount = 0
        #md5checker.md5_for_dirs(Config.instance().srcrootpath)
        #AppData.instance().closemdfile()
        Logger.instance().info('test button')
    
    # 生成版本文件，用于更新资源使用
    # 拷贝文件
    def onBtnClkVersion(self):
        #AppData.instance().curverFileCount = 0
        #buildver = fileversioninfo.BuildFileVersion()
        #buildver.buildVersionFile()
        
        AppData.instance().copyFile();
        
    # 生成版本的 swf 文件
    def onBtnClkVerSwf(self):
        #直接启动线程
        if AppData.instance().m_bOverVer:
            AppData.instance().m_verThread = VerThread("VerThread", VerThread.outVerSwf);
            AppData.instance().m_verThread.start()
        else:
            Logger.instance().info('Verthread is runing')
