# -*- coding: utf-8 -*-
'''
Created on 2013-5-15

@author: Administrator
'''

from PyQt5 import QtWidgets

import FileDirDiff.UI.ui_leftfnwin
from FileDirDiff.Core.AppSys import AppSysBase
from FileDirDiff.Core.VerThread import VerThread

class LeftFnWin(QtWidgets.QDockWidget):    
    def __init__(self):
        super(LeftFnWin, self).__init__()

        self.ui = FileDirDiff.UI.ui_leftfnwin.Ui_LeftFnWin()
        self.ui.setupUi(self)
        
        # 注册事件处理函数
        self.ui.m_btnCheck.clicked.connect(self.onBtnClkCheck)
        self.ui.m_btnCopy.clicked.connect(self.onBtnClkCopy)
        self.ui.m_btnDiff.clicked.connect(self.onBtnClkDiff)

    # 生成当前版版本的 md5 文件
    def onBtnClkCheck(self):
        #AppSysBase.instance().curmd5FileCount = 0
        #md5checker.md5_for_dirs(AppSysBase.instance().m_config.m_srcRootPath)
        #AppSysBase.instance().closemdfile()
        AppSysBase.instance().m_logSys.info('test button')
    
    # 生成版本文件，用于更新资源使用
    # 拷贝文件
    def onBtnClkCopy(self):
        #AppSysBase.instance().curverFileCount = 0
        #buildver = fileversioninfo.BuildFileVersion()
        #buildver.buildVersionFile()
        
        AppSysBase.instance().copyFile();
        
    # 生成版本的 swf 文件
    def onBtnClkDiff(self):
        #直接启动线程
        if AppSysBase.instance().m_bOverVer:
            AppSysBase.instance().m_verThread = VerThread("VerThread", VerThread.outDiff);
            AppSysBase.instance().m_verThread.start()
        else:
            AppSysBase.instance().m_logSys.info('Verthread is runing')
