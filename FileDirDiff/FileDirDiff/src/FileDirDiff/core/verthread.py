#-*- encoding=utf-8 -*-
'''
Created on 2013-5-23

@author: Administrator
'''

from threading import Thread
import os

from autoupdate.core.appdata import AppData

from autoupdate.core.fileversioninfo import BuildFileVersion
from autoupdate.core.config import Config
from autoupdate.core import appdata
from autoupdate.core.logger import Logger

class VerThread(Thread):
    
    def __init__(self, threadName, func):
        super(VerThread, self).__init__(name = threadName)  # must add
        self.m_runF = func

    def run(self):
        if self.m_runF is not None:
            self.m_runF()

    @staticmethod
    def outVerSwf():
        AppData.instance().m_bOverVer = False
        
        # 只有在点击生成版本的时候，才更改当前版本的版本日期，设置当前版本
        Config.instance().swiftVersion()
        Config.instance().saveCFG()
        
        # 检查目录
        if not os.path.exists(os.path.join(Config.instance().destrootpath,  Config.instance().tmpDir)):
            os.makedirs(os.path.join(Config.instance().destrootpath,  Config.instance().tmpDir))
        
        if not os.path.exists(os.path.join(Config.instance().destrootpath,  Config.instance().outDir)):
            os.makedirs(os.path.join(Config.instance().destrootpath,  Config.instance().outDir))
        
        # 生成 app 文件，这个需要放在生成  versionall.swf 之后，因为需要 versionall.swf 的 md5 ，决定是否重新加载 versionall.swf 
        #AppData.instance().buildAppMd()
        
        # 生成所有的 md5 
        AppData.instance().curmd5FileCount = 0
        AppData.instance().buildAllMd()
        
        # 如果计算文件夹 md5 的时候，才需要计算路径
        if Config.instance().getfoldermd5cmp():
            AppData.instance().buildModuleMd()
            AppData.instance().buildUIMd()
        AppData.instance().closemdfile()

        # 生成版本文件
        AppData.instance().curverFileCount = 0
        buildver = BuildFileVersion()
        #buildver.buildVersionFile()
        
        # 生成版本文件 swf 文件
        buildver.outVerSwf()
        
        # 生成 app 文件，这个需要放在生成  versionall.swf 之后，因为需要 versionall.swf 的 md5 ，决定是否重新加载 versionall.swf 
        AppData.instance().buildAppMd()
        
        # 生成 moduleapp.swf 的 MD5 ，包括 versionall.swf 和 startpicpath 的 md5 
        buildver.outVerAppSwf()
        
        #Config.instance().saveCFG()
        #Config.instance().swiftVersion()
            
        # 如果计算文件夹 md5 的时候，才需要计算路径
        if Config.instance().getfoldermd5cmp():
            appdata.AppData.instance().savaDirMd()
        
        # 生成启动的 html 的配置，尤其是 start 的配置
        #AppData.instance().buildStartHtml()
        
        Logger.instance().info("可以拷贝生成文件到目标文件夹了")
        AppData.instance().m_bOverVer = True
