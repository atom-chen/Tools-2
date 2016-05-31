#-*- encoding=utf-8 -*-

import os
from FileDirDiff.Core.AppSys import AppSysBase
from FileDirDiff.Core.ProcessWrap import ProcessWrap

class VerTask(object):
    '''
    classdocs
    '''

    def __init__(self, params):
        '''
        Constructor
        '''
        self.m_verProcess = ProcessWrap("VerProcess", self.outDiff);

    def start(self):
        self.m_verProcess.start()
        #self.m_verProcess.join()

    # @staticmethod
    def outDiff(self):
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
        # 拷贝文件
        AppSysBase.instance().m_pBuildVersion.copyFileNoSafe()
        # 生成清单文件
        AppSysBase.instance().m_pBuildVersion.buildFileListManifest()
        
        AppSysBase.instance().m_logSys.info("版本数据文件生成结束")
        AppSysBase.instance().m_bOverVer = True

        