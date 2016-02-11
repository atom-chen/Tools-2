# -*- coding: utf-8 -*-

'''
@brief 
'''

import sys
import traceback
import os
import shutil
import glob

from threading import Thread
from Pack.Frame.AppSys import AppSys
from Pack.Frame.Config import Config
from Pack.Frame.Logger import Logger
from Pack.Frame.UtilTools import UtilTools

class CopyThread(Thread):
    '''
    func : 
    '''
    def __init__(self, threadName, func):
        super(CopyThread, self).__init__(name = threadName)  # must add
        self.m_runF = func

    def run(self):
        if self.m_runF is not None:
            self.m_runF()
        
    @staticmethod 
    def charCopy():
        Logger.instance().loggerChar("start copy character")
        #
        for (k,v) in Config.instance().m_charCfg.srcn2destn.items():
            pass
        AppSys.instance().m_bOverECopy = True
        Logger.instance().loggerChar("end copy character")
        Logger.instance().loggerChar("end copy character thread")
    
    @staticmethod 
    def effCopy():
        #
        Logger.instance().loggerEff("start copy effect")
        #
        for (k,v) in Config.instance().m_effCfg.srcn2destn.items():
            # 拷贝配置文件
            pass

        AppSys.instance().m_bOverECopy = True
        Logger.instance().loggerEff("end copy effect")
        Logger.instance().loggerEff("end copy effect thread")

    @staticmethod 
    def terCopy():
        # 拷贝资源
        Logger.instance().loggerTer("start copy terrain")
            
        AppSys.instance().m_bOverTCopy = True
        Logger.instance().loggerTer("end copy terrain")
        Logger.instance().loggerTer("end copy terrain thread")
