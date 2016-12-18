# -*- coding: utf-8 -*-

'''
'''

from PyQt5 import QtWidgets;

import QtToolSet.UI.ui_leftfnwin;
from Libs.FrameWork.Ctx import Ctx;
from QtToolSet.Common.QtToolSetSys import QtToolSetSys;

class LeftFnWin(QtWidgets.QDockWidget):    
    def __init__(self):
        super(LeftFnWin, self).__init__()

        self.ui = QtToolSet.UI.ui_leftfnwin.Ui_LeftFnWin()
        self.ui.setupUi(self)
        
        # 注册事件处理函数
        self.ui.m_btnCheck.clicked.connect(self.onBtnClkCheck)
        self.ui.m_btnCopy.clicked.connect(self.onBtnClkCopy)
        self.ui.m_btnDiff.clicked.connect(self.onBtnClkDiff)

    # 生成当前版版本的 md5 文件
    def onBtnClkCheck(self):
        Ctx.instance().mLogSys.log('test button')
    
    # 生成版本文件，用于更新资源使用
    # 拷贝文件
    def onBtnClkCopy(self):
        pass;
        
    # 生成版本文件
    def onBtnClkDiff(self):
        #直接启动线程
        if QtToolSetSys.instance().mFileDirDiffSys.isVersionOver():
            QtToolSetSys.instance().mFileDirDiffSys.startVerProcess();
        else:
            Ctx.instance().mLogSys.log('Verthread is runing')

