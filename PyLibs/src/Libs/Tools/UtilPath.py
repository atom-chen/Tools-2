#-*- encoding=utf-8 -*-

import os
import shutil
import glob

from Libs.Tools.UtilStr import UtilStr
from Libs.Tools.UtilError import UtilError
from Libs.DataStruct.MList import MList
from Libs.Core.GObject import GObject
from Libs.FileSystem.MFileDirInfo import MFileAndDirList, MFileInfo, MDirInfo

'''
@brief: 目录处理
'''

class UtilPath(GObject):
    # 将 "\" 转换成 "/"
    @staticmethod
    def normal(fullPath):
        return fullPath.replace("\\", "/");
    
    # 创建文件，创建空文件
    @staticmethod
    def mknod(fullFilePath):
        #os.mknod(fullFilePath);
        pass;
        
    # 创建文件，直接打开一个文件，如果文件不存在则创建文件
    @staticmethod
    def open(fullFilePath, mode):
        return os.open(fullFilePath, mode);
        
    # 创建目录
    @staticmethod
    def mkdir(fullDirPath):
        os.mkdir(fullDirPath);
        
    # 复制文件，oldfile和newfile都只能是文件
    @staticmethod
    def copyFile(oldFullFilePath, newFullFilePath):
        shutil.copyfile(oldFullFilePath, newFullFilePath);
        
    
    # 复制文件，oldfile只能是文件夹，newfile可以是文件，也可以是目标目录
    @staticmethod
    def copy(oldFullDirPath, newFullFileOrDirPath):
        shutil.copy(oldFullDirPath, newFullFileOrDirPath);
        
    
    # 复制文件夹，olddir和newdir都只能是目录，且newdir必须不存在
    @staticmethod
    def copytree(oldFullDirPath, newFullDirPath):
        shutil.copytree(oldFullDirPath, newFullDirPath);
        
    
    # 移动文件（目录）
    @staticmethod
    def move(oldFullFilePathOrDir, newFullFileOrDirPath):
        shutil.move(oldFullFilePathOrDir, newFullFileOrDirPath);
        
    # 删除文件
    @staticmethod
    def remove(fullFilePath):
        os.remove(fullFilePath);
        
    
    # 重命名文件（目录），文件或目录都是使用这条命令
    @staticmethod
    def rename(oldFullFileOrDirPath, newFullFileOrDirPath):
        os.rename(oldFullFileOrDirPath, newFullFileOrDirPath);
        
    
    # 删除目录，只能删除空目录
    @staticmethod
    def rmdir(fullDirPath):
        os.rmdir(fullDirPath);
        
    
    # 删除目录，空目录、有内容的目录都可以删 
    @staticmethod
    def rmtree(fullDirPath):
        shutil.rmtree(fullDirPath);
    
    
    # 转换目录
    @staticmethod
    def chdir(fullDirPath):
        os.chdir(fullDirPath);
        
    # 判断目标，判断目标是否存在
    @staticmethod
    def exists(fullFileOrDirPath):
        return os.path.exists(fullFileOrDirPath);
    
    # 判断目标，判断目标是否目录
    @staticmethod
    def isdir(fullFileOrDirPath):
        return os.path.isdir(fullFileOrDirPath); 
    
    # 判断目标，判断目标是否文件
    @staticmethod
    def isfile(fullFileOrDirPath):
        return os.path.isfile(fullFileOrDirPath);
        
    # 去掉目录路径，返回文件名
    @staticmethod
    def basename(fullFilePath):
        return os.path.basename(fullFilePath);
        
    # 去掉文件名，返回目录路径
    @staticmethod
    def dirname(fullFilePath):
        return os.path.dirname(fullFilePath);
        
        
    # 分割文件名与目录名
    @staticmethod
    def split(fullFilePath):
        return os.path.split(fullFilePath);
    
    # 分割文件名字和扩展名
    @staticmethod
    def splitext(fullFilePath):
        pathNoExt, ext = os.path.splitext(fullFilePath);
        pathNoExt = UtilPath.normal(pathNoExt);
        return pathNoExt, ext;
        
    # 连接目录
    @staticmethod
    def join(path_a, path_b, path_c = None):
        if(path_a != None and path_b != None and path_c != None):
            return os.path.join(path_a, path_b, path_c);
        elif(path_a != None and path_b != None):
            return os.path.join(path_a, path_b);
        elif(path_a != None):
            return path_a;
        else:
            return "";
        
    
    # 获取绝对目录
    @staticmethod
    def abspath(fullFileOrDirPath):
        return os.path.abspath(fullFileOrDirPath);
    
    
    # 获取目录或者文件大小
    @staticmethod
    def getsize(fullFileOrDirPath):
        return os.path.getsize(fullFileOrDirPath);
        
    # 列出目录下所有的内容
    @staticmethod
    def listdir(fullDirPath):
        return os.path.getsize(fullDirPath);
    
    # 获取当前工作目录
    @staticmethod
    def getcwd():
        return os.getcwd();
    
        
    # 递归遍历整个目录
    @staticmethod
    def recurseTraverseDirectory(srcPath, destPath, pThis, func):
        if(UtilStr.startswith(srcPath, destPath)):
            UtilError.error("Dir Can not Same");
            
        if(not UtilPath.exists(srcPath)):
            return;
        
        if(not UtilStr.isEmptyOrNull(destPath)):
            if(not UtilPath.exists(destPath)):
                UtilPath.mkdir(destPath);
        
        for root, dirs, files in os.walk(srcPath):
            for oneFile in files:
                if(func != None):
                    func(UtilPath.join(root, oneFile), UtilPath.join(destPath, oneFile));
                    

    @staticmethod
    def getAllFile(self, srcPath, includeExtList = None, excludeExtList = None, isRecurse = True):
        fileAndDirList = glob(UtilPath.join(srcPath, '*'));
        fileList = MList();
        dirList = MList();
        fullFileOrDirPath = "";
        extName = "";
        
        for fileOrDir in fileAndDirList:
            fullFileOrDirPath = UtilPath.join(srcPath, fileOrDir);
            if(UtilPath.isfile(fullFileOrDirPath)):
                _, extName = UtilPath.splitext(fileOrDir);
                if(excludeExtList == None or excludeExtList.IndexOf(extName) != -1):
                    if(includeExtList == None or includeExtList.IndexOf(extName) != -1):
                        curFileInfo = MFileInfo();
                        curFileInfo.mFullPath = fullFileOrDirPath;
                        curFileInfo.mFileName = fileOrDir;
                        fileList.Add(curFileInfo);
            else:
                curDirInfo = MDirInfo();
                curDirInfo.mFullPath = fullFileOrDirPath;
                curDirInfo.mDirName = fileOrDir;
                dirList.Add(curDirInfo);
                        
        if(isRecurse):
            for dirPath in dirList.getList():
                subDirFileList = self.getAllFile(dirPath.mFullPath, includeExtList, excludeExtList, isRecurse);
                fileList.merge(subDirFileList);
                
        return fileList
    
    
    @staticmethod
    def getAllDir(self, srcPath, isRecurse = True):
        fileAndDirList = glob(UtilPath.join(srcPath, '*'));
        dirList = MList();
        fullFileOrDirPath = "";
        
        for fileOrDir in fileAndDirList:
            fullFileOrDirPath = UtilPath.join(srcPath, fileOrDir);
            if(UtilPath.isdir(fullFileOrDirPath)):
                curDirInfo = MDirInfo();
                curDirInfo.mFullPath = fullFileOrDirPath;
                curDirInfo.mDirName = fileOrDir;
                dirList.Add(curDirInfo);
                        
        if(isRecurse):
            for dirPath in dirList.getList():
                subDirList = self.getAllDir(dirPath.mFullPath, isRecurse);
                dirList.merge(subDirList);
                
        return dirList;
    
    
    @staticmethod
    def getAllFileOrDir(self, srcPath, includeExtList = None, excludeExtList = None, isRecurse = True):
        fileAndDirList = glob(UtilPath.join(srcPath, '*'));
        retFileAndDirListInfo = MFileAndDirList();
        fullFileOrDirPath = "";
        extName = "";
        
        for fileOrDir in fileAndDirList:
            fullFileOrDirPath = UtilPath.join(srcPath, fileOrDir);
            if(UtilPath.isfile(fullFileOrDirPath)):
                _, extName = UtilPath.splitext(fileOrDir);
                if(excludeExtList == None or excludeExtList.IndexOf(extName) != -1):
                    if(includeExtList == None or includeExtList.IndexOf(extName) != -1):
                        curFileInfo = MFileInfo();
                        curFileInfo.mFullPath = fullFileOrDirPath;
                        curFileInfo.mFileName = fileOrDir;
                        retFileAndDirListInfo.mFileList.Add(curFileInfo);
            else:
                curDirInfo = MDirInfo();
                curDirInfo.mFullPath = fullFileOrDirPath;
                curDirInfo.mDirName = fileOrDir;
                retFileAndDirListInfo.mDirList.Add(curDirInfo);
                        
        if(isRecurse):
            for dirPath in retFileAndDirListInfo.mDirList.getList():
                subDirFileListInfo = self.getAllFile(dirPath.mFullPath, isRecurse);
                retFileAndDirListInfo.mFileList.merge(subDirFileListInfo.mFileList);
                retFileAndDirListInfo.mDirList.merge(subDirFileListInfo.mDirList);
                
        return retFileAndDirListInfo;
     

    # 递归拷贝目录
    @staticmethod
    def copyDirectory(srcPath, destPath, includeExtList = None, excludeExtList = None, isRecurse = True):
        if(UtilStr.startswith(srcPath, destPath)):
            UtilError.error("Dir Can not Same");
        
        if(not UtilPath.exists(srcPath)):
            return;
    
        if(not UtilPath.exists(destPath)):
            UtilPath.mkdir(destPath);

        fileAndDirListInfo = UtilPath.getAllFileOrDir(srcPath, includeExtList, excludeExtList, False);
        for fileItemInfo in fileAndDirListInfo.mFileList:
            UtilPath.copy(fileItemInfo.mFullPath, destPath);

        destDirPath = "";
        if(isRecurse):
            for dirItemInfo in fileAndDirListInfo.mDirList.getList():
                destDirPath = UtilPath.join(destPath, dirItemInfo.mDirName);
                UtilPath.copyDirectory(dirItemInfo.mFullPath, destDirPath, isRecurse);

