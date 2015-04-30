#-*- encoding=utf-8 -*-

import os
import lzma

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
            self.m_curMd5FileHandle = open(AppSysBase.instance().m_config.curMd5FilePath(), 'w', encoding='utf-8')
        
        if self.m_curMd5FileCount > 0:
            self.m_curMd5FileHandle.write('\n')
        self.m_curMd5FileCount += 1
        
        fullpath = os.path.join(directoryName, filename)
        fullpath = fullpath.replace('\\', '/')
        subLen = len(AppSysBase.instance().m_config.m_srcRootPath) + 1
        relPath = fullpath[subLen:]         # 相对文件名字
        with open(fullpath, 'r') as fHandle:
            fHandle.seek(0, 2)
            fileSize = fHandle.tell()
            fHandle.close()

        self.m_curMd5FileHandle.write(relPath + '=' + md + "=" + str(fileSize))
        
        AppSysBase.instance().m_logSys.info('文件  Md5 码:' + fullpath)


    def closemdfile(self):
        if not self.m_curMd5FileHandle is None:
            self.m_curMd5FileHandle.close()
            self.m_curMd5FileHandle = None


    def buildFileMd(self):
        self.m_curMd5FileCount = 0
        AppSysBase.instance().Md5Checker.mdcallback = self.writemd
        AppSysBase.instance().Md5Checker.m_subVersion = AppSysBase.instance().m_config.subVersionByte()
        AppSysBase.instance().Md5Checker.md5_for_dirs(AppSysBase.instance().m_config.m_srcRootPath)
        
        AppSysBase.instance().m_logSys.info(AppSysBase.instance().m_config.m_srcRootPath + 'md5 end')
        
        self.closemdfile()
        
    def buildMiniMd(self):
        # 计算 ModuleApp md5
        fileHandle = open(AppSysBase.instance().m_config.miniMd5FilePath(), 'w', encoding='utf-8')
        md = AppSysBase.instance().Md5Checker.md5_for_file(AppSysBase.instance().m_config.curMd5FilePath())
        
        with open(AppSysBase.instance().m_config.curMd5FilePath(), 'r') as fHandle:
            fHandle.seek(0, 2)
            fileSize = fHandle.tell()
            fHandle.close()
        
        fileHandle.write(AppSysBase.instance().m_config.verFileNameAndExt() + md + "=" + str(fileSize))

        fileHandle.close()
        AppSysBase.instance().m_logSys.info(AppSysBase.instance().m_config.miniMd5FilePath() + 'md5 end')
        
        
    def lzmaMd5File(self):
        # 压缩
        AppSysBase.instance().m_pParamInfo.m_curInCompressFullFileName = AppSysBase.instance().m_config.curMd5FilePath()
        AppSysBase.instance().m_pParamInfo.m_curOutCompressFullFileName = AppSysBase.instance().m_config.verFilePath()
        AppSysBase.instance().CmdLine.lzmaCompress()
        
        '''
        with open(AppSysBase.instance().m_pParamInfo.m_curInCompressFullFileName, 'r', encoding = 'utf8') as inHandle:
            data = inHandle.read()
            inHandle.close()
            byteArr = bytes(data, encoding = "utf8")
            with lzma.open(AppSysBase.instance().m_pParamInfo.m_curOutCompressFullFileName, 'w') as outHandle:
                outHandle.write(byteArr)
                outHandle.close()
        '''
        
        AppSysBase.instance().m_pParamInfo.m_curInCompressFullFileName = AppSysBase.instance().m_config.miniMd5FilePath()
        AppSysBase.instance().m_pParamInfo.m_curOutCompressFullFileName = AppSysBase.instance().m_config.verMiniPath()
        AppSysBase.instance().CmdLine.lzmaCompress()
        
        '''
        with open(AppSysBase.instance().m_pParamInfo.m_curInCompressFullFileName, 'r', encoding = 'utf8') as inHandle:
            data = inHandle.read()
            inHandle.close()
            byteArr = bytes(data, encoding = "utf8")
            with lzma.open(AppSysBase.instance().m_pParamInfo.m_curOutCompressFullFileName, 'w') as outHandle:
                outHandle.write(byteArr)
                outHandle.close()
        '''

    def copyFile(self):
        # 拷贝文件
        if AppSysBase.instance().m_bOverVer:
            filename = AppSysBase.instance().m_config.m_prefixVerFileName
            zipName = "{0}.txt".format(filename)
            AppSysBase.instance().FileOperate.copyFile(os.path.join(AppSysBase.instance().m_config.m_destRootPath, AppSysBase.instance().m_config.m_outDir, zipName), os.path.join(AppSysBase.instance().m_config.srcrootassetpath, zipName))
        
            filename = AppSysBase.instance().m_config.m_prefixVerMiniName
            zipName = "{0}.txt".format(filename)
        
            AppSysBase.instance().FileOperate.copyFile(os.path.join(AppSysBase.instance().m_config.m_destRootPath, AppSysBase.instance().m_config.m_outDir, zipName), os.path.join(AppSysBase.instance().m_config.srcrootassetpath, zipName))
            #FileOperate.copyFile(AppSysBase.instance().m_config.htmlPath(), os.path.join(AppSysBase.instance().m_config.m_srcRootPath, AppSysBase.instance().m_config.htmlname))
        else:
            AppSysBase.instance().m_logSys.info('File is Building, cannot copy file')

    def getCurVerFileCount(self):
        return self.m_curVerFileCount
    
    def addCurVerFileCount(self, value):
        self.m_curVerFileCount += value

