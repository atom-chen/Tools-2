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
        if not os.path.exists(AppSysBase.instance().m_config.tmpFileDir()):
            os.makedirs(AppSysBase.instance().m_config.tmpFileDir())
        
        if not os.path.exists(AppSysBase.instance().m_config.outFileDir()):
            os.makedirs(AppSysBase.instance().m_config.outFileDir())
        
        # 生成所有的 md5 
        AppSysBase.instance().m_pBuildVersion.buildFileMd()
        # 生成 Mini 文件 
        AppSysBase.instance().m_pBuildVersion.buildMiniMd()
        
        # 生成压缩文件
        AppSysBase.instance().m_pBuildVersion.lzmaMd5File()
        #拷贝文件
        
        AppSysBase.instance().m_logSys.info("可以拷贝生成文件到目标文件夹了")
        AppSysBase.instance().m_bOverVer = True

