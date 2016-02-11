# -*- coding: utf-8 -*-

'''
@brief 主对话框
'''

import os

from PyQt5 import QtCore, QtGui, QtWidgets
from Pack.Frame.ui_effdialog import Ui_Dialog
from Pack.Frame.AppSys import AppSys
from Pack.Frame.EffectThread import EffectThread
from Pack.Frame.CharacterThread import CharacterThread
from Pack.Frame.Logger import Logger

from Pack.Frame.TabWidget import TabWidget
from Pack.Frame.AppSys import AppSys
from Pack.Frame.Config import Config

#from threading import Timer

class MainDialog(QtWidgets.QDialog):
    def __init__(self, parent=None):
        super(MainDialog, self).__init__(parent)
        
        #self.m_timer = Timer(1, self.callback)
        #self.m_timer.start()
        
        self.m_qttimer = QtCore.QTimer()
        self.m_qttimer.timeout.connect(self.onTimer)
        self.m_qttimer.start( 1000 )
        
        # 两个按钮
        self.ui = Ui_Dialog()
        self.ui.setupUi(self)
        
        # tab widget
        #self.tabWidget = TabWidget(parent);
        self.tabWidget = TabWidget();
        self.tabWidget.initUI()
        #self.tabWidget.show()
        
        # 事件监听
        #self.ui.m_btnEPack.clicked.connect(self.onBtnClkEPack)
        #self.ui.m_btnCPack.clicked.connect(self.onBtnClkCPack)
        
        #mainLayout = QtGui.QVBoxLayout()
        #mainLayout.addWidget(self.ui)
        #mainLayout.addWidget(self.tabWidget)
        #self.setLayout(mainLayout)
        self.ui.m_verticalLayout.addWidget(self.tabWidget)

        self.setWindowTitle("Tools")
    
    # 打包按钮处理
    def onBtnClkEPack(self):
        if(AppSys.instance().m_bOverEff == False):
            AppSys.instance().m_effThread = EffectThread("EffThread")
            AppSys.instance().m_effThread.start()
        else:
            Logger.instance().logger("effpack is running")
            
    def onBtnClkCPack(self):
        if(AppSys.instance().m_bOverChar == False):
            AppSys.instance().m_charThread = CharacterThread("CharThread")
            AppSys.instance().m_charThread.start()
        else:
            Logger.instance().logger("charpack is running")
    
    # update ui
    #def callback(self):
        #self.m_timer.cancel()
        #self.m_timer = Timer(1, self.callback)
        #self.m_timer.start()
        
    def onTimer(self):
        listdata = []
        Logger.instance().getloggerEff(listdata)
        for dataitem in listdata:
            self.tabWidget.ui.m_textEffLog.appendPlainText(dataitem)
            
        del listdata[:]
        
        Logger.instance().getloggerChar(listdata)
        for dataitem in listdata:
            self.tabWidget.ui.m_textCharLog.appendPlainText(self.tr(dataitem))
            
        del listdata[:]
            
        Logger.instance().getloggerTer(listdata)
        for dataitem in listdata:
            self.tabWidget.ui.m_textTerLog.appendPlainText(dataitem)
            
        # 检测人物图片打包是否结束
        if AppSys.instance().m_bCharPicPackOver == False:
            if os.path.exists(Config.instance().m_charCfg.destrootdir + '/' + 'cflag.txt'):
                AppSys.instance().m_bCharPicPackOver = True
                Logger.instance().loggerChar("character pic pack complete")

        if AppSys.instance().m_bEffPicPackOver == False:
            if os.path.exists(Config.instance().m_effCfg.destrootdir + '/' + 'eflag.txt'):
                AppSys.instance().m_bEffPicPackOver = True
                Logger.instance().loggerEff("effect pic pack complete")
                
        if AppSys.instance().m_bTerPicPackOver == False:
            if os.path.exists(Config.instance().m_terCfg.destrootdir + '/' + 'tflag.txt'):
                AppSys.instance().m_bTerPicPackOver = True
                Logger.instance().loggerTer("terrain pic pack complete")
