#-*- encoding=utf-8 -*-
'''
Created on 2013-5-15

@author: Administrator
'''

import os
import glob

from autoupdate.core import md5checker
from autoupdate.core.config import Config
from autoupdate.core.utils import FileOperate
from autoupdate.core.logger import Logger
from autoupdate.core.md5dir import Md5DirOperate
from autoupdate.core.IAppData import IAppData

# global data
class AppData(IAppData):
    def __init__(self):
        self.curmd5FileHandle = None    # 当前版本的 md5 版本文件
        self.curmd5FileCount = 0           # 当前 md5 文件数目
        self.curverFileCount = 0           # 当前 md5 文件数目
        
        self.m_bOverVer = True     # Over
        self.m_verThread = None    # ver thread
        self.m_md5DirOperate = Md5DirOperate()    # dir 操作
    
    def writemd(self, directoryName, filename, md):
        cmpdirectoryName = directoryName.replace('\\', '/')
        # asset/ui asset/module 下面的文件的  md5 码不用写入,这个需要比对目录的 md5
        uipath = Config.instance().srcrootassetpath + "\\ui"
        uipath = uipath.replace('\\', '/')
        modulepath = Config.instance().srcrootassetpath + "\\module"
        modulepath = modulepath.replace('\\', '/')
        
        # 如果计算文件夹 md5 的时候，才需要计算路径
        if Config.instance().getfoldermd5cmp():
            if uipath == cmpdirectoryName:
                return
            if modulepath == cmpdirectoryName:
                return
        
        # versionall.swf 和 versionapp.swf 不写入版本文件
        if (filename == (Config.instance().preckallverfilename + '.swf')) or (filename == (Config.instance().preckappverfilename + '.swf')):
            return
        
        # ModuleApp.swf 这个也不需要写入版本文件
        if filename == Config.instance().appAppSwfNameAndExt():
            return
        
        if self.curmd5FileHandle is None:
            #with open(config.Config.instance().curFilePath(), 'w', encoding='utf-8') as self.curmd5FileHandle:
            #    pass
            self.curmd5FileHandle = open(Config.instance().curCKFilePath(), 'w', encoding='utf-8')
        
        if self.curmd5FileCount > 0:
            self.curmd5FileHandle.write('\n')
        self.curmd5FileCount += 1
        
        fullpath = os.path.join(directoryName, filename)
        fullpath = fullpath.replace('\\', '/')
        idx = fullpath.find('asset')
        self.curmd5FileHandle.write(fullpath[idx:] + '=' + md)
        
        Logger.instance().info('文件 CK 码:' + fullpath)

    def closemdfile(self):
        if not self.curmd5FileHandle is None:
            self.curmd5FileHandle.close()
            self.curmd5FileHandle = None
            
    def buildAllMd(self):
        md5checker.mdcallback = self.writemd
        md5checker.m_subversion = Config.instance().subVersionByte()
        md5checker.md5_for_dirs(Config.instance().srcrootassetpath)
        
        Logger.instance().info(Config.instance().srcrootassetpath + 'md5 end')
        
    def buildAppMd(self):
        # 计算 ModuleApp md5
        fileHandle = open(Config.instance().appCKFilePath(), 'w', encoding='utf-8')
        md = md5checker.md5_for_file(Config.instance().appAppSwfPath())
        fileHandle.write('moduleapp=' + md + '\n')
        
        # 计算 startpicpath md5
        md = md5checker.md5_for_file(Config.instance().startPicPath())
        fileHandle.write('startpic=' + md + '\n')
        
        # 计算 versionall.swf 的 md5
        md = md5checker.md5_for_file(Config.instance().allverFilePath())
        fileHandle.write('allverfile=' + md)
         
        fileHandle.close()
        Logger.instance().info(Config.instance().appCKFilePath() + 'md5 end')

    # 生成启动的 html
    def buildStartHtml(self):
        startswfmd = md5checker.md5_for_file(Config.instance().appStartSwfPath())
        htmlfileHandle = open(Config.instance().htmlPath(), 'w', encoding='utf-8')
        tempfileHandle = open(Config.instance().htmltemplate, 'r', encoding='utf-8')
        
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
        
        Logger.instance().info('生成文件: ' + Config.instance().htmlname)
    
    def buildModuleMd(self):
        dirname = Config.instance().srcrootassetpath + "/module"
        os.chdir(dirname)
        allswffile = glob.glob('*.swf')
        allswffile.sort()
        uifilemd5lst = self.m_md5DirOperate.calcModuleFileDirMd5(allswffile, Config.instance().modulePath())
        
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
        dirname = Config.instance().srcrootassetpath + "/ui"
        os.chdir(dirname)
        allswffile = glob.glob('*.swf')
        allswffile.sort()
        uifilemd5lst = self.m_md5DirOperate.calcUIFileDirMd5(allswffile, Config.instance().uiPath())
        
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
        if AppData.instance().m_bOverVer:
            filename = Config.instance().preckappverfilename
            swfName = '%s.swf' % (filename)
            FileOperate.copyFile(os.path.join(Config.instance().destrootpath, Config.instance().outDir, swfName), os.path.join(Config.instance().srcrootassetpath, swfName))
        
            filename = Config.instance().preckallverfilename
            swfName = '%s.swf' % (filename)
        
            FileOperate.copyFile(os.path.join(Config.instance().destrootpath, Config.instance().outDir, swfName), os.path.join(Config.instance().srcrootassetpath, swfName))
            #FileOperate.copyFile(Config.instance().htmlPath(), os.path.join(Config.instance().srcrootpath, Config.instance().htmlname))
        else:
            Logger.instance().info('File is Building, cannot copy file')

    def get_curverFileCount(self):
        return self.curverFileCount
    
    def add_curverFileCount(self, value):
        self.curverFileCount += value
        
    def savaDirMd(self):
        self.m_md5DirOperate.savaDirMd()

