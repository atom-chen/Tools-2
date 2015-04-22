# -*- coding: utf-8 -*-
'''
Created on 2013-5-15

@author: Administrator
'''

from PyQt5 import QtWidgets

import FileDirDiff.UI.ui_leftfnwin
from FileDirDiff.Core.AppSys import AppSys
#from FileDirDiff.core.fileversioninfo import BuildFileVersion
from FileDirDiff.Core.VerThread import VerThread
from FileDirDiff.Core.Logger import Logger
from FileDirDiff.Core import Config
from FileDirDiff.Core import AppSys

class LeftFnWin(QtWidgets.QDockWidget):    
    def __init__(self):
        super(LeftFnWin, self).__init__()

        self.ui = FileDirDiff.UI.ui_leftfnwin.Ui_LeftFnWin()
        self.ui.setupUi(self)
        
        # 注册事件处理函数
        self.ui.m_btnCheck.clicked.connect(self.onBtnClkCheck)
        self.ui.m_btnVersion.clicked.connect(self.onBtnClkVersion)
        self.ui.m_btnVerSwf.clicked.connect(self.onBtnClkVerSwf)

    # 生成当前版版本的 md5 文件
    def onBtnClkCheck(self):
        #AppSys.instance().curmd5FileCount = 0
        #md5checker.md5_for_dirs(Config.instance().srcrootpath)
        #AppSys.instance().closemdfile()
        Logger.instance().info('test button')
    
    # 生成版本文件，用于更新资源使用
    # 拷贝文件
    def onBtnClkVersion(self):
        #AppSys.instance().curverFileCount = 0
        #buildver = fileversioninfo.BuildFileVersion()
        #buildver.buildVersionFile()
        
        AppSys.instance().copyFile();
        
    # 生成版本的 swf 文件
    def onBtnClkVerSwf(self):
        #直接启动线程
        if AppSys.instance().m_bOverVer:
            AppSys.instance().m_verThread = VerThread("VerThread", VerThread.outVerSwf);
            AppSys.instance().m_verThread.start()
        else:
            Logger.instance().info('Verthread is runing')
