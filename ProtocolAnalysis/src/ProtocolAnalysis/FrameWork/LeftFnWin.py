# -*- coding: utf-8 -*-


from PyQt5 import QtWidgets

import ProtocolAnalysis.UI.ui_leftfnwin

from ProtocolAnalysis.Core.ConvThread import ConvThread
from ProtocolAnalysis.Core.AppSysBase import AppSysBase


class LeftFnWin(QtWidgets.QDockWidget):

    
    def __init__(self):
        super(LeftFnWin, self).__init__()

        self.ui = ProtocolAnalysis.UI.ui_leftfnwin.Ui_LeftFnWin()
        self.ui.setupUi(self)
        
        # 注册事件处理函数
        self.ui.m_pushButtonExportCpp.clicked.connect(self.onBtnClkExportCpp)
        self.ui.m_pushButtonExportCS.clicked.connect(self.onBtnClkExportCs)
        self.ui.m_btnCopyFile.clicked.connect(self.onBtnClkCopy)
        self.ui.m_btnConvFile.clicked.connect(self.onBtnClkConv)


    def onBtnClkExportCpp(self):
        # 子进程实现
        #if not AppSysBase.instance().getCppExportProcess().isRuning():
        #    AppSysBase.instance().getCppExportProcess().start()
        #else:
        #    AppSysBase.instance().getLogSysPtr().info('CPP Export Is Runing, Please Wait End')
        
        # 子线程实现
        if not AppSysBase.instance().getCppExportThread().isRuning():
            AppSysBase.instance().getCppExportThread().start()
        else:
            AppSysBase.instance().getLogSysPtr().info('CPP Export Is Runing, Please Wait End')
        
        
    def onBtnClkExportCs(self):
        # 子进程实现
        #if not AppSysBase.instance().getCsExportProcess().isRuning():
        #    AppSysBase.instance().getCsExportProcess().start()
        #else:
        #    AppSysBase.instance().getLogSysPtr().info('CS Export Is Runing, Please Wait End')
        
        # 子线程实现
        if not AppSysBase.instance().getCsExportThread().isRuning():
            AppSysBase.instance().getCsExportThread().start()
        else:
            AppSysBase.instance().getLogSysPtr().info('CS Export Is Runing, Please Wait End')
        
    

    # 拷贝文件
    def onBtnClkCopy(self):
        #AppData.instance().copyFile();
        pass


    # 生成版本的 swf 文件
    def onBtnClkConv(self):
        #直接启动线程
        if AppSysBase.instance().getLoggerPtr().getConvOver():
            AppSysBase.instance().setConvThread(ConvThread("ConvThread"));
            AppSysBase.instance().getConvThread().start()
        else:
            AppSysBase.instance().getLoggerPtr().info('Convthread is runing')


