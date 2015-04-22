#-*- encoding=utf-8 -*-

'''
'''

import os
import glob

from FileDirDiff.Core import Md5Checker
from FileDirDiff.Core.Config import Config
from FileDirDiff.Core.Utils import FileOperate
from FileDirDiff.Core.LogSys import LogSys
from FileDirDiff.Core.Md5Dir import Md5DirOperate
from FileDirDiff.Core import GlobalData

# global data
class AppSys():
    g_pInstance = None
    #g_pInstance = AppSys()
    #g_pInstance = AppSys.AppSys()
    
    @staticmethod
    def instance():
        if AppSys.g_pInstance is None:
            AppSys.g_pInstance = AppSys()
        # 这样写就会奖  g_pAppSys 添加到  AppSys  模块中了
        #g_pAppSys = AppSys.g_pInstance;
        GlobalData.g_pAppSys = AppSys.g_pInstance;
        return AppSys.g_pInstance
    
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
        
    def postConstruct(self):
        self.m_config = Config()
        self.m_logSys = LogSys()
        self.m_md5DirOperate = Md5DirOperate()
        self.Md5Checker = Md5Checker;         # 保存模块
        self.FileOperate = FileOperate;       # 保存模块
        
    
    def writemd(self, directoryName, filename, md):
        cmpdirectoryName = directoryName.replace('\\', '/')
        # asset/ui asset/module 下面的文件的  md5 码不用写入,这个需要比对目录的 md5
        uipath = self.m_config.srcrootassetpath + "\\ui"
        uipath = uipath.replace('\\', '/')
        modulepath = self.m_config.srcrootassetpath + "\\module"
        modulepath = modulepath.replace('\\', '/')
        
        # 如果计算文件夹 md5 的时候，才需要计算路径
        if self.m_config.getfoldermd5cmp():
            if uipath == cmpdirectoryName:
                return
            if modulepath == cmpdirectoryName:
                return
        
        # versionall.swf 和 versionapp.swf 不写入版本文件
        if (filename == (self.m_config.preckallverfilename + '.swf')) or (filename == (self.m_config.preckappverfilename + '.swf')):
            return
        
        # ModuleApp.swf 这个也不需要写入版本文件
        if filename == self.m_config.appAppSwfNameAndExt():
            return
        
        if self.curmd5FileHandle is None:
            #with open(config.GlobalData.g_pAppSys.m_config.curFilePath(), 'w', encoding='utf-8') as self.curmd5FileHandle:
            #    pass
            self.curmd5FileHandle = open(self.m_config.curCKFilePath(), 'w', encoding='utf-8')
        
        if self.curmd5FileCount > 0:
            self.curmd5FileHandle.write('\n')
        self.curmd5FileCount += 1
        
        fullpath = os.path.join(directoryName, filename)
        fullpath = fullpath.replace('\\', '/')
        idx = fullpath.find('asset')
        self.curmd5FileHandle.write(fullpath[idx:] + '=' + md)
        
        self.m_logSys.info('文件 CK 码:' + fullpath)

    def closemdfile(self):
        if not self.curmd5FileHandle is None:
            self.curmd5FileHandle.close()
            self.curmd5FileHandle = None
            
    def buildAllMd(self):
        self.Md5Checker.mdcallback = self.writemd
        self.Md5Checker.m_subversion = self.m_config.subVersionByte()
        self.Md5Checker.md5_for_dirs(self.m_config.srcrootassetpath)
        
        self.m_logSys.info(self.m_config.srcrootassetpath + 'md5 end')
        
    def buildAppMd(self):
        # 计算 ModuleApp md5
        fileHandle = open(self.m_config.appCKFilePath(), 'w', encoding='utf-8')
        md = self.Md5Checker.md5_for_file(self.m_config.appAppSwfPath())
        fileHandle.write('moduleapp=' + md + '\n')
        
        # 计算 startpicpath md5
        md = self.Md5Checker.md5_for_file(self.m_config.startPicPath())
        fileHandle.write('startpic=' + md + '\n')
        
        # 计算 versionall.swf 的 md5
        md = self.Md5Checker.md5_for_file(self.m_config.allverFilePath())
        fileHandle.write('allverfile=' + md)
         
        fileHandle.close()
        self.m_logSys.info(self.m_config.appCKFilePath() + 'md5 end')

    # 生成启动的 html
    def buildStartHtml(self):
        startswfmd = self.Md5Checker.md5_for_file(GlobalData.g_pAppSys.m_config.appStartSwfPath())
        htmlfileHandle = open(GlobalData.g_pAppSys.m_config.htmlPath(), 'w', encoding='utf-8')
        tempfileHandle = open(GlobalData.g_pAppSys.m_config.htmltemplate, 'r', encoding='utf-8')
        
        for curline in tempfileHandle:
            idx = curline.find('?v=')
            if idx != -1:
                htmlfileHandle.write(curline[0:idx])
                htmlfileHandle.write('?v=')
                htmlfileHandle.write(startswfmd)
                htmlfileHandle.write("\",\n")
            else:
                htmlfileHandle.write(curline)
        
        htmlfileHandle.close()
        tempfileHandle.close()
        
        GlobalData.g_pAppSys.m_logSys.info('生成文件: ' + GlobalData.g_pAppSys.m_config.htmlname)
    
    def buildModuleMd(self):
        dirname = GlobalData.g_pAppSys.m_config.srcrootassetpath + "/module"
        os.chdir(dirname)
        allswffile = glob.glob('*.swf')
        allswffile.sort()
        uifilemd5lst = self.m_md5DirOperate.calcModuleFileDirMd5(allswffile, GlobalData.g_pAppSys.m_config.modulePath())
        
        for filever in uifilemd5lst:
            if self.curmd5FileCount > 0:
                self.curmd5FileHandle.write('\n')
            self.curmd5FileCount += 1
            
            fullpath = filever.m_filename
            fullpath = fullpath.replace('\\', '/')
            idx = fullpath.find('asset')
            self.curmd5FileHandle.write(fullpath[idx:] + '=' + filever.m_version)
    
    # 生成 "asset/ui" 这个文件夹下的资源的 md5
    def buildUIMd(self):
        dirname = GlobalData.g_pAppSys.m_config.srcrootassetpath + "/ui"
        os.chdir(dirname)
        allswffile = glob.glob('*.swf')
        allswffile.sort()
        uifilemd5lst = self.m_md5DirOperate.calcUIFileDirMd5(allswffile, GlobalData.g_pAppSys.m_config.uiPath())
        
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
        if GlobalData.g_pAppSys.m_bOverVer:
            filename = GlobalData.g_pAppSys.m_config.preckappverfilename
            swfName = '%s.swf' % (filename)
            self.FileOperate.copyFile(os.path.join(GlobalData.g_pAppSys.m_config.destrootpath, GlobalData.g_pAppSys.m_config.outDir, swfName), os.path.join(GlobalData.g_pAppSys.m_config.srcrootassetpath, swfName))
        
            filename = GlobalData.g_pAppSys.m_config.preckallverfilename
            swfName = '%s.swf' % (filename)
        
            self.FileOperate.copyFile(os.path.join(GlobalData.g_pAppSys.m_config.destrootpath, GlobalData.g_pAppSys.m_config.outDir, swfName), os.path.join(GlobalData.g_pAppSys.m_config.srcrootassetpath, swfName))
            #FileOperate.copyFile(GlobalData.g_pAppSys.m_config.htmlPath(), os.path.join(GlobalData.g_pAppSys.m_config.srcrootpath, GlobalData.g_pAppSys.m_config.htmlname))
        else:
            GlobalData.g_pAppSys.m_logSys.info('File is Building, cannot copy file')

    def get_curverFileCount(self):
        return self.curverFileCount
    
    def add_curverFileCount(self, value):
        self.curverFileCount += value
        
    def savaDirMd(self):
        self.m_md5DirOperate.savaDirMd()

