#-*- encoding=utf-8 -*-

'''
'''

import os
import glob

from FileDirDiff.Core.AppSysBase import AppSysBase
from FileDirDiff.Core import Md5Checker
from FileDirDiff.Core.Config import Config
from FileDirDiff.Core.Utils import FileOperate
from FileDirDiff.Core.LogSys import LogSys
from FileDirDiff.Core.Md5Dir import Md5DirOperate

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
        self.curmd5FileHandle = None    # 当前版本的 md5 版本文件
        self.curmd5FileCount = 0           # 当前 md5 文件数目
        self.curverFileCount = 0           # 当前 md5 文件数目
        
        self.m_bOverVer = True     # Over
        self.m_verThread = None    # ver thread
        self.m_md5DirOperate = None    # dir 操作
        self.m_config = None
        self.m_logSys = None
        self.Md5Checker = None
        self.FileOperate = None
        

    def postInit(self):
        AppSysBase.instance().m_config = Config()
        AppSysBase.instance().m_logSys = LogSys()
        AppSysBase.instance().m_md5DirOperate = Md5DirOperate()
        AppSysBase.instance().Md5Checker = Md5Checker;         # 保存模块
        AppSysBase.instance().FileOperate = FileOperate;       # 保存模块
        
        AppSysBase.instance().m_config.readInit('config.txt')
    

    def writemd(self, directoryName, filename, md):
        if self.curmd5FileHandle is None:
            #with open(config.AppSysBase.instance().m_config.curFilePath(), 'w', encoding='utf-8') as self.curmd5FileHandle:
            #    pass
            self.curmd5FileHandle = open(self.m_config.curCKFilePath(), 'w', encoding='utf-8')
        
        if self.curmd5FileCount > 0:
            self.curmd5FileHandle.write('\n')
        self.curmd5FileCount += 1
        
        fullpath = os.path.join(directoryName, filename)
        fullpath = fullpath.replace('\\', '/')
        subLen = len(self.m_config.m_srcRootPath) + 1
        relPath = fullpath[subLen:]
        self.curmd5FileHandle.write(relPath + '=' + md)
        
        self.m_logSys.info('文件 CK 码:' + fullpath)


    def closemdfile(self):
        if not self.curmd5FileHandle is None:
            self.curmd5FileHandle.close()
            self.curmd5FileHandle = None


    def buildAllMd(self):
        self.Md5Checker.mdcallback = self.writemd
        self.Md5Checker.m_m_subVersion = self.m_config.m_subVersionByte()
        self.Md5Checker.md5_for_dirs(self.m_config.m_srcRootPath)
        
        self.m_logSys.info(self.m_config.m_srcRootPath + 'md5 end')
        
    def buildAppMd(self):
        # 计算 ModuleApp md5
        fileHandle = open(self.m_config.appCKFilePath(), 'w', encoding='utf-8')
        md = self.Md5Checker.md5_for_file(self.m_config.appAppSwfPath())
        fileHandle.write('moduleapp=' + md + '\n')
        
        # 计算 versionall.swf 的 md5
        md = self.Md5Checker.md5_for_file(self.m_config.allverFilePath())
        fileHandle.write('allverfile=' + md)
         
        fileHandle.close()
        self.m_logSys.info(self.m_config.appCKFilePath() + 'md5 end')

    def buildModuleMd(self):
        dirname = AppSysBase.instance().m_config.srcrootassetpath + "/module"
        os.chdir(dirname)
        allswffile = glob.glob('*.swf')
        allswffile.sort()
        uifilemd5lst = self.m_md5DirOperate.calcModuleFileDirMd5(allswffile, AppSysBase.instance().m_config.modulePath())
        
        for filever in uifilemd5lst:
            if self.curmd5FileCount > 0:
                self.curmd5FileHandle.write('\n')
            self.curmd5FileCount += 1
            
            fullpath = filever.m_filename
            fullpath = fullpath.replace('\\', '/')
            idx = fullpath.find('asset')
            self.curmd5FileHandle.write(fullpath[idx:] + '=' + filever.m_version)
        
    def copyFile(self):
        # 拷贝文件
        if AppSysBase.instance().m_bOverVer:
            filename = AppSysBase.instance().m_config.m_preCkAppVerFileName
            swfName = '%s.swf' % (filename)
            self.FileOperate.copyFile(os.path.join(AppSysBase.instance().m_config.m_destRootPath, AppSysBase.instance().m_config.m_outDir, swfName), os.path.join(AppSysBase.instance().m_config.srcrootassetpath, swfName))
        
            filename = AppSysBase.instance().m_config.m_preCkAllVerFileName
            swfName = '%s.swf' % (filename)
        
            self.FileOperate.copyFile(os.path.join(AppSysBase.instance().m_config.m_destRootPath, AppSysBase.instance().m_config.m_outDir, swfName), os.path.join(AppSysBase.instance().m_config.srcrootassetpath, swfName))
            #FileOperate.copyFile(AppSysBase.instance().m_config.htmlPath(), os.path.join(AppSysBase.instance().m_config.m_srcRootPath, AppSysBase.instance().m_config.htmlname))
        else:
            AppSysBase.instance().m_logSys.info('File is Building, cannot copy file')

    def get_curverFileCount(self):
        return self.curverFileCount
    
    def add_curverFileCount(self, value):
        self.curverFileCount += value
        
    def savaDirMd(self):
        self.m_md5DirOperate.savaDirMd()

