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
            # 拷贝配置文件
            srcfilename = Config.instance().m_charCfg.xswfDir + '/' + 'x' + v + '.swf'
            destfilename = Config.instance().m_commonCfg.serverid + '\\xml\\being\\' + 'x' + v + '.swf'
            UtilTools.copyFile(srcfilename, destfilename)
                
            # 拷贝资源文件
            srcfilename = Config.instance().m_charCfg.destrootdir + '/' + v + '*.swf'
            filelist = glob.glob(srcfilename)
            for srcfilename in filelist:
                destfilename = Config.instance().m_commonCfg.serverid + '\\being\\' + srcfilename.split('\\')[-1]
                #srcfilename = Config.instance().m_charCfg.destrootdir + '/' + srcfilename + '*.swf'
                UtilTools.copyFile(srcfilename, destfilename)

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
            srcfilename = Config.instance().m_effCfg.effectXmlSwf + '/' + 'x' + v + '.swf'
            destfilename = Config.instance().m_commonCfg.serverid + '\\xml\\effect\\' + 'x' + v + '.swf'
            UtilTools.copyFile(srcfilename, destfilename)
                
            # 拷贝资源文件
            srcfilename = Config.instance().m_effCfg.destrootdir + '/' + v + '*.swf'
            filelist = glob.glob(srcfilename)
            for srcfilename in filelist:
                destfilename = Config.instance().m_commonCfg.serverid + '\\effect\\' + srcfilename.split('\\')[-1]
                UtilTools.copyFile(srcfilename, destfilename)

        AppSys.instance().m_bOverECopy = True
        Logger.instance().loggerEff("end copy effect")
        Logger.instance().loggerEff("end copy effect thread")

    @staticmethod 
    def terCopy():
        #
        Logger.instance().loggerTer("start copy terrain")
        #
        for (k,v) in Config.instance().m_terCfg.srcn2destn.items():
            # 拷贝地形配置文件
            srcfilename = Config.instance().m_terCfg.destrootdir + '/' + Config.instance().m_terCfg.XmlSwfFolderName + '/' + 'x' + v.m_terFileName + '.swf'
            destfilename = Config.instance().m_commonCfg.serverid + '\\xml\\terrain\\' + 'x' + v.m_terFileName + '.swf'
            UtilTools.copyFile(srcfilename, destfilename)
                
            # 拷贝地形材质配置文件
            srcfilename = Config.instance().m_terCfg.destrootdir + '/' + Config.instance().m_terCfg.XmlSwfFolderName + '/' + 'x' + v.m_tplFileName + '.swf'
            destfilename = Config.instance().m_commonCfg.serverid + '\\xml\\terrain\\definitions\\' + 'x' + v.m_tplFileName + '.swf'
            UtilTools.copyFile(srcfilename, destfilename)
            
            # 拷贝阻挡点文件
            srcfilename = Config.instance().m_terCfg.destrootdir + '/' + Config.instance().m_terCfg.XmlSwfFolderName + '/' + 's' + v.m_terFileName + '.swf'
            destfilename = Config.instance().m_commonCfg.serverid + '\\xml\\terrain\\stoppoint\\' + 's' + v.m_terFileName + '.swf'
            UtilTools.copyFile(srcfilename, destfilename)
            
            # 拷贝地形资源
            srcfilename = Config.instance().m_terCfg.destrootdir + '/' + v.m_tplFileName + '*.swf'
            filelist = glob.glob(srcfilename)
            for srcfilename in filelist:
                destfilename = Config.instance().m_commonCfg.serverid + '\\terrain\\' + srcfilename.split('\\')[-1]
                UtilTools.copyFile(srcfilename, destfilename)
                
            # 拷贝缩略图资源
            srcfilename = Config.instance().m_terCfg.destrootdir + '/' + 'ttb' + v.m_tplFileName[1:] + '.swf'
            destfilename = Config.instance().m_commonCfg.serverid + '/' + Config.instance().m_terCfg.m_thumbnailsFolderName + '/' + 'ttb' + v.m_tplFileName[1:] + '.swf'
            UtilTools.copyFile(srcfilename, destfilename)
            
        AppSys.instance().m_bOverTCopy = True
        Logger.instance().loggerTer("end copy terrain")
        Logger.instance().loggerTer("end copy terrain thread")
