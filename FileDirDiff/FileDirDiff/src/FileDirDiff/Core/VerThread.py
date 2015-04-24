#-*- encoding=utf-8 -*-

'''
'''

from threading import Thread
import os

from FileDirDiff.Core.AppSys import AppSysBase

class VerThread(Thread):
    
    def __init__(self, threadName, func):
        super(VerThread, self).__init__(name = threadName)  # must add
        self.m_runF = func

    def run(self):
        if self.m_runF is not None:
            self.m_runF()

    @staticmethod
    def outDiff():
        AppSysBase.instance().m_bOverVer = False
        
        # 只有在点击生成版本的时候，才更改当前版本的版本日期，设置当前版本
        AppSysBase.instance().m_config.refreshVersion()
        AppSysBase.instance().m_config.saveCFG()
        
        # 检查目录
        if not os.path.exists(os.path.join(AppSysBase.instance().m_config.m_destRootPath,  AppSysBase.instance().m_config.m_tmpDir)):
            os.makedirs(os.path.join(AppSysBase.instance().m_config.m_destRootPath,  AppSysBase.instance().m_config.m_tmpDir))
        
        if not os.path.exists(os.path.join(AppSysBase.instance().m_config.m_destRootPath,  AppSysBase.instance().m_config.m_outDir)):
            os.makedirs(os.path.join(AppSysBase.instance().m_config.m_destRootPath,  AppSysBase.instance().m_config.m_outDir))
        
        # 生成所有的 md5 
        AppSysBase.instance().m_pBuildVersion.m_curMd5FileCount = 0
        AppSysBase.instance().m_pBuildVersion.buildFileMd()
        AppSysBase.instance().m_pBuildVersion.closemdfile()
        
        # 生成 all 文件 
        AppSysBase.instance().m_pBuildVersion.buildAllMd()
        
        AppSysBase.instance().m_logSys.info("可以拷贝生成文件到目标文件夹了")
        AppSysBase.instance().m_bOverVer = True
