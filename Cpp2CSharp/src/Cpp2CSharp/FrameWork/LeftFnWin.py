# -*- coding: utf-8 -*-
'''
Created on 2015-2-1

@author: Administrator
'''

from PyQt5 import QtWidgets

import CPP2CSharp.UI.ui_leftfnwin
from CPP2CSharp.Core.AppData import AppData
#from CPP2CSharp.Core.fileversioninfo import BuildFileVersion
from CPP2CSharp.Core.ConvThread import ConvThread
from CPP2CSharp.Core.Logger import Logger

class LeftFnWin(QtWidgets.QDockWidget):    
    def __init__(self):
        super(LeftFnWin, self).__init__()

        self.ui = CPP2CSharp.UI.ui_leftfnwin.Ui_LeftFnWin()
        self.ui.setupUi(self)
        
        # 注册事件处理函数
        self.ui.m_btnCheck.clicked.connect(self.onBtnClkTest)
        self.ui.m_btnVersion.clicked.connect(self.onBtnClkCopy)
        
        self.ui.m_btnVerSwf.clicked.connect(self.onBtnClkConv)


    def onBtnClkTest(self):
        Logger.instance().info('test button')
    

    # 拷贝文件
    def onBtnClkCopy(self):
        AppData.instance().copyFile();
        
    # 生成版本的 swf 文件
    def onBtnClkConv(self):
        #直接启动线程
        if AppData.instance().m_bConvOver:
            AppData.instance().m_convThread = ConvThread("ConvThread");
            AppData.instance().m_convThread.start()
        else:
            Logger.instance().info('Convthread is runing')


