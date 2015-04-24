#-*- encoding=utf-8 -*-

import os

from FileDirDiff.Core.AppSysBase import AppSysBase

class BuildVersion(object):
    '''
    classdocs
    '''
    def __init__(self):
        '''
        Constructor
        '''
        self.m_curMd5FileHandle = None    # 当前版本的 md5 版本文件
        self.m_curMd5FileCount = 0           # 当前 md5 文件数目
        self.m_curVerFileCount = 0           # 当前 md5 文件数目
        
    def writemd(self, directoryName, filename, md):
        if self.m_curMd5FileHandle is None:
            #with open(config.AppSysBase.instance().m_config.curFilePath(), 'w', encoding='utf-8') as self.m_curMd5FileHandle:
            #    pass
            self.m_curMd5FileHandle = open(AppSysBase.instance().m_config.curCKFilePath(), 'w', encoding='utf-8')
        
        if self.m_curMd5FileCount > 0:
            self.m_curMd5FileHandle.write('\n')
        self.m_curMd5FileCount += 1
        
        fullpath = os.path.join(directoryName, filename)
        fullpath = fullpath.replace('\\', '/')
        subLen = len(AppSysBase.instance().m_config.m_srcRootPath) + 1
        relPath = fullpath[subLen:]
        self.m_curMd5FileHandle.write(relPath + '=' + md)
        
        AppSysBase.instance().m_logSys.info('文件 CK 码:' + fullpath)


    def closemdfile(self):
        if not self.m_curMd5FileHandle is None:
            self.m_curMd5FileHandle.close()
            self.m_curMd5FileHandle = None


    def buildFileMd(self):
        AppSysBase.instance().Md5Checker.mdcallback = self.writemd
        AppSysBase.instance().Md5Checker.m_subVersion = AppSysBase.instance().m_config.subVersionByte()
        AppSysBase.instance().Md5Checker.md5_for_dirs(AppSysBase.instance().m_config.m_srcRootPath)
        
        AppSysBase.instance().m_logSys.info(AppSysBase.instance().m_config.m_srcRootPath + 'md5 end')
        
    def buildAllMd(self):
        # 计算 ModuleApp md5
        fileHandle = open(AppSysBase.instance().m_config.allCKFilePath(), 'w', encoding='utf-8')
        md = AppSysBase.instance().Md5Checker.md5_for_file(AppSysBase.instance().m_config.curCKFilePath())
        fileHandle.write('all=' + md + '\n')

        fileHandle.close()
        AppSysBase.instance().m_logSys.info(AppSysBase.instance().m_config.allCKFilePath() + 'md5 end')

    def copyFile(self):
        # 拷贝文件
        if AppSysBase.instance().m_bOverVer:
            filename = AppSysBase.instance().m_config.m_preVerFileName
            zipName = "{0}.txt".format(filename)
            AppSysBase.instance().FileOperate.copyFile(os.path.join(AppSysBase.instance().m_config.m_destRootPath, AppSysBase.instance().m_config.m_outDir, zipName), os.path.join(AppSysBase.instance().m_config.srcrootassetpath, zipName))
        
            filename = AppSysBase.instance().m_config.m_preVerAllName
            zipName = "{0}.txt".format(filename)
        
            AppSysBase.instance().FileOperate.copyFile(os.path.join(AppSysBase.instance().m_config.m_destRootPath, AppSysBase.instance().m_config.m_outDir, zipName), os.path.join(AppSysBase.instance().m_config.srcrootassetpath, zipName))
            #FileOperate.copyFile(AppSysBase.instance().m_config.htmlPath(), os.path.join(AppSysBase.instance().m_config.m_srcRootPath, AppSysBase.instance().m_config.htmlname))
        else:
            AppSysBase.instance().m_logSys.info('File is Building, cannot copy file')

    def getCurVerFileCount(self):
        return self.m_curVerFileCount
    
    def addCurVerFileCount(self, value):
        self.m_curVerFileCount += value

