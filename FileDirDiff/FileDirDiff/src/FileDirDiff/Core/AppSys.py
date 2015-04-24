#-*- encoding=utf-8 -*-

#import os
#import glob

from FileDirDiff.Core.AppSysBase import AppSysBase
from FileDirDiff.Core import Md5Checker
from FileDirDiff.Core.Config import Config
from FileDirDiff.Core.Utils import FileOperate
from FileDirDiff.Core.LogSys import LogSys
from FileDirDiff.Core.BuildVersion import BuildVersion

# global data
class AppSys(AppSysBase):
    #g_pInstance = None
    #g_pInstance = AppSys()
    #g_pInstance = AppSys.AppSys()
    
    @staticmethod
    def instance():
        if AppSysBase.g_pInstance is None:
            AppSysBase.g_pInstance = AppSys()
        return AppSysBase.g_pInstance
    
    def __init__(self):
        self.m_bOverVer = True     # Over
        self.m_verThread = None    # ver thread
        self.m_md5DirOperate = None    # dir 操作
        self.m_config = None
        self.m_logSys = None
        self.Md5Checker = None
        self.FileOperate = None
        self.m_pBuildVersion = None
        

    def postInit(self):
        AppSysBase.instance().m_config = Config()
        AppSysBase.instance().m_logSys = LogSys()
        AppSysBase.instance().Md5Checker = Md5Checker;         # 保存模块
        AppSysBase.instance().FileOperate = FileOperate;       # 保存模块
        self.m_pBuildVersion = BuildVersion()
        
        AppSysBase.instance().m_config.readInit('config.txt')
    
