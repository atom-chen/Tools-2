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
        self.ui.m_btnCheck.clicked.connect(self.onBtnClkTest)
        self.ui.m_btnVersion.clicked.connect(self.onBtnClkCopy)
        
        self.ui.m_btnVerSwf.clicked.connect(self.onBtnClkConv)


    def onBtnClkTest(self):
        AppSysBase.instance().getLogSysPtr().info('test button')
        AppSysBase.instance().getConfigPtr().getProtoFilesList().parse()
        AppSysBase.instance().getExportCSharpFile().export()
        AppSysBase.instance().getExportCppFile().export()
    

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


