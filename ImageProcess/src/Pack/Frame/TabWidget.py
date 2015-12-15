# -*- coding: utf-8 -*-

'''
'''

from PyQt5 import QtGui, QtWidgets
from Pack.Frame.ui_tabwidget import Ui_TabWidget

from Pack.Frame.AppSys import AppSys
from Pack.Frame.EffectThread import EffectThread
from Pack.Frame.CharacterThread import CharacterThread
from Pack.Frame.TerrainThread import TerrainThread
from Pack.Frame.Logger import Logger

from Pack.Frame.CopyThread import CopyThread
from Pack.Frame.Config import Config
import os

from Pack.Frame.UtilTools import UtilTools


class TabWidget(QtWidgets.QTabWidget):
    def __init__(self, parent=None):
        super(TabWidget, self).__init__(parent)
        
        self.ui = Ui_TabWidget()
        self.ui.setupUi(self)
        
        self.ui.m_btnEffSart.clicked.connect(self.onBtnClkEPack)
        self.ui.m_btnCharSart.clicked.connect(self.onBtnClkCPack)
        self.ui.m_btnTerSart.clicked.connect(self.onBtnClkTPack)
        
        self.ui.m_btnEffCopy.clicked.connect(self.onBtnClkECopy)
        self.ui.m_btnCharCopy.clicked.connect(self.onBtnClkCCopy)
        self.ui.m_btnTerCopy.clicked.connect(self.onBtnClkTCopy)
        
        self.ui.m_rbtnCommon.clicked.connect(self.onRBtnClk1t)
        self.ui.m_rbtnNCCenter.clicked.connect(self.onRBtnClk2t)
        self.ui.m_rbtnCCenter.clicked.connect(self.onRBtnClk3t)
        
        self.ui.m_rbtnFightTer.clicked.connect(self.onRBtnClkFightTer)
        self.ui.m_rbtnJustXml.clicked.connect(self.onRBtnClkJustXml)
        
        self.ui.m_btnEffBuildCfg.clicked.connect(self.onBtnEffBuildCfg)
        self.ui.m_btnEffCopyCfg.clicked.connect(self.onBtnEffCopyCfg)
        self.ui.m_btnChaBuildCfg.clicked.connect(self.onBtnChaBuildCfg)
        self.ui.m_btnChaCopyCfg_2.clicked.connect(self.onBtnChaCopyCfg)
        
    def initUI(self):
        # 特效 UI 
        if Config.instance().m_effCfg.packType == 0:
            self.ui.m_rbtnCommon.setChecked(True)
        elif Config.instance().m_effCfg.packType == 1:
            self.ui.m_rbtnNCCenter.setChecked(True)
        else:
            self.ui.m_rbtnCCenter.setChecked(True)
            
        # 战斗地形打包
        if Config.instance().m_terCfg.m_bfight:
            self.ui.m_rbtnFightTer.setChecked(True)
        # 地形只输出 xml
        if Config.instance().m_terCfg.m_bJustXml:
            self.ui.m_rbtnJustXml.setChecked(True)
        
        # 数字
        self.ui.m_plainTextEditWidth.appendPlainText(str(Config.instance().m_effCfg.packWidth))
        self.ui.m_plainTextEditHeight.appendPlainText(str(Config.instance().m_effCfg.packHeight))

    def onBtnClkEPack(self):
        if(AppSys.instance().m_bOverEff == True):
            # 保存配置文件信息，启动子进程
            Config.instance().m_effCfg.packWidth = int(self.ui.m_plainTextEditWidth.toPlainText())
            Config.instance().m_effCfg.packHeight = int(self.ui.m_plainTextEditHeight.toPlainText())
            Config.instance().saveCFG()
            
            if os.path.exists(Config.instance().m_charCfg.destrootdir + '/' + 'eflag.txt'):
                os.remove(Config.instance().m_charCfg.destrootdir + '/' + 'eflag.txt')
            AppSys.instance().m_bEffPicPackOver = False
            
            AppSys.instance().m_bOverEff = False
            AppSys.instance().m_effThread = EffectThread("EffThread")
            AppSys.instance().m_effThread.start()
        else:
            Logger.instance().loggerEff("effpack is running")
            
    def onBtnClkCPack(self):
        if(AppSys.instance().m_bOverChar == True):
            #
            if os.path.exists(Config.instance().m_charCfg.destrootdir + '/' + 'cflag.txt'):
                os.remove(Config.instance().m_charCfg.destrootdir + '/' + 'cflag.txt')
            AppSys.instance().m_bCharPicPackOver = False
            
            AppSys.instance().m_bOverChar = False
            AppSys.instance().m_charThread = CharacterThread("CharThread")
            AppSys.instance().m_charThread.start()
        else:
            Logger.instance().loggerChar("charpack is running")
            
    def onBtnClkTPack(self):
        if(AppSys.instance().m_bOverTer == True):
            # 保存配置文件，一边子进程启动读取
            Config.instance().saveCFG()
            if os.path.exists(Config.instance().m_terCfg.destrootdir + '/' + 'tflag.txt'):
                os.remove(Config.instance().m_terCfg.destrootdir + '/' + 'tflag.txt')
            AppSys.instance().m_bTerPicPackOver = False
            
            AppSys.instance().m_bOverTer = False
            AppSys.instance().m_terThread = TerrainThread("TerThread")
            AppSys.instance().m_terThread.start()
        else:
            Logger.instance().loggerTer("terrainpack is running")

    #
    def onBtnClkCCopy(self):
        if AppSys.instance().m_bCharPicPackOver == True:
            if(AppSys.instance().m_bOverCCopy == True):
                Logger.instance().loggerChar("start char copy thread")
                AppSys.instance().m_bOverCCopy = False
                AppSys.instance().m_charCopyThread = CopyThread("char copy Thread", CopyThread.charCopy)
                AppSys.instance().m_charCopyThread.start()
            else:
                Logger.instance().loggerChar("char copy thread is running")
        else:
            Logger.instance().loggerChar("char pic pack not complete")
    
    #
    def onBtnClkECopy(self):
        if AppSys.instance().m_bEffPicPackOver == True:
            if(AppSys.instance().m_bOverECopy == True):
                AppSys.instance().m_bOverECopy = False
                AppSys.instance().m_effCopyThread = CopyThread("eff copy Thread", CopyThread.effCopy)
                AppSys.instance().m_effCopyThread.start()
            else:
                Logger.instance().loggerEff("eff copy thread is running")
        else:
            Logger.instance().loggerEff("eff pic pack not complete")
    
    #
    def onBtnClkTCopy(self):
        if AppSys.instance().m_bTerPicPackOver == True:
            if(AppSys.instance().m_bOverTCopy == True):
                AppSys.instance().m_bOverTCopy = False
                AppSys.instance().m_terCopyThread = CopyThread("ter copy Thread", CopyThread.terCopy)
                AppSys.instance().m_terCopyThread.start()
            else:
                Logger.instance().loggerTer("ter copy thread is running")
        else:
            Logger.instance().loggerTer("ter pic pack not complete")

    def onRBtnClk1t(self):
        Config.instance().m_effCfg.packType = 0
    
    def onRBtnClk2t(self):
        Config.instance().m_effCfg.packType = 1
    
    def onRBtnClk3t(self):
        Config.instance().m_effCfg.packType = 2

    # 打包战斗地形
    def onRBtnClkFightTer(self):
        Config.instance().m_terCfg.m_bfight = self.ui.m_rbtnFightTer.isChecked()
        
    def onRBtnClkJustXml(self):
        Config.instance().m_terCfg.m_bJustXml = self.ui.m_rbtnJustXml.isChecked()
        
    def onBtnEffBuildCfg(self):
        pass
    
    def onBtnEffCopyCfg(self):
        pass
    
    def onBtnChaBuildCfg(self):
        pass
    
    def onBtnChaCopyCfg(self):
        pass
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
