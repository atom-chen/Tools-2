#-*- encoding=utf-8 -*-

'''
'''

from threading import Thread
import os

from FileDirDiff.Core.AppSys import AppSys
from FileDirDiff.Core.FileVersionInfo import BuildFileVersion

class VerThread(Thread):
    
    def __init__(self, threadName, func):
        super(VerThread, self).__init__(name = threadName)  # must add
        self.m_runF = func

    def run(self):
        if self.m_runF is not None:
            self.m_runF()

    @staticmethod
    def outDiff():
        AppSys.instance().m_bOverVer = False
        
        # 只有在点击生成版本的时候，才更改当前版本的版本日期，设置当前版本
        AppSys.instance().m_config.swiftVersion()
        AppSys.instance().m_config.saveCFG()
        
        # 检查目录
        if not os.path.exists(os.path.join(AppSys.instance().m_config.destrootpath,  AppSys.instance().m_config.tmpDir)):
            os.makedirs(os.path.join(AppSys.instance().m_config.destrootpath,  AppSys.instance().m_config.tmpDir))
        
        if not os.path.exists(os.path.join(AppSys.instance().m_config.destrootpath,  AppSys.instance().m_config.outDir)):
            os.makedirs(os.path.join(AppSys.instance().m_config.destrootpath,  AppSys.instance().m_config.outDir))
        
        # 生成 app 文件，这个需要放在生成  versionall.swf 之后，因为需要 versionall.swf 的 md5 ，决定是否重新加载 versionall.swf 
        #AppSys.instance().buildAppMd()
        
        # 生成所有的 md5 
        AppSys.instance().curmd5FileCount = 0
        AppSys.instance().buildAllMd()
        
        # 如果计算文件夹 md5 的时候，才需要计算路径
        if AppSys.instance().m_config.getfoldermd5cmp():
            AppSys.instance().buildModuleMd()
            AppSys.instance().buildUIMd()
        AppSys.instance().closemdfile()

        # 生成版本文件
        AppSys.instance().curverFileCount = 0
        buildver = BuildFileVersion()
        #buildver.buildVersionFile()
        
        # 生成版本文件 swf 文件
        buildver.outVerSwf()
        
        # 生成 app 文件，这个需要放在生成  versionall.swf 之后，因为需要 versionall.swf 的 md5 ，决定是否重新加载 versionall.swf 
        AppSys.instance().buildAppMd()
        
        # 生成 moduleapp.swf 的 MD5  
        buildver.outVerAppSwf()
            
        # 如果计算文件夹 md5 的时候，才需要计算路径
        if AppSys.instance().m_config.getfoldermd5cmp():
            AppSys.instance().savaDirMd()
        
        # 生成启动的 html 的配置，尤其是 start 的配置
        AppSys.instance().buildStartHtml()
        
        AppSys.instance().m_logSys.info("可以拷贝生成文件到目标文件夹了")
        AppSys.instance().m_bOverVer = True
