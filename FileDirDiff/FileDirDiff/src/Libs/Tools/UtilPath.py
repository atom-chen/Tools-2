#-*- encoding=utf-8 -*-

'''
@brief: 目录处理
'''

import os
import shutil

from Libs.Tools.UtilStr import UtilStr
from Libs.Tools.UtilError import UtilError

class UtilPath(object):
    
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
    def mkdir(fullDir):
        os.mkdir(fullDir);
        
    # 复制文件，oldfile和newfile都只能是文件
    @staticmethod
    def copyFile(oldFileFullPath, newFileFullPath):
        shutil.copyfile(oldFileFullPath, newFileFullPath);
        
    
    # 复制文件，oldfile只能是文件夹，newfile可以是文件，也可以是目标目录
    @staticmethod
    def copy(oldDir, newFileFullPathOrDir):
        shutil.copy(oldDir, newFileFullPathOrDir);
        
    
    # 复制文件夹，olddir和newdir都只能是目录，且newdir必须不存在
    @staticmethod
    def copytree(oldDir, newDir):
        shutil.copytree(oldDir, newDir);
        
    
    # 移动文件（目录）
    @staticmethod
    def move(oldFilePathOrDir, newFilePathOrDir):
        shutil.move(oldFilePathOrDir, newFilePathOrDir);
        
    # 删除文件
    @staticmethod
    def remove(fileFullPath):
        os.remove(fileFullPath);
        
    
    # 重命名文件（目录），文件或目录都是使用这条命令
    @staticmethod
    def rename(oldFileNameOrDir, newFileNameOrDir):
        os.rename(oldFileNameOrDir, newFileNameOrDir);
        
    
    # 删除目录，只能删除空目录
    @staticmethod
    def rmdir(fullDir):
        os.rmdir(fullDir);
        
    
    # 删除目录，空目录、有内容的目录都可以删 
    @staticmethod
    def rmtree(fullDir):
        shutil.rmtree(fullDir);
    
    
    # 转换目录
    @staticmethod
    def chdir(fullDir):
        os.chdir(fullDir);
        
    # 判断目标，判断目标是否存在
    @staticmethod
    def exists(fullFileOrDir):
        return os.path.exists(fullFileOrDir);
    
    # 判断目标，判断目标是否目录
    @staticmethod
    def isdir(fullFileOrDir):
        return os.path.isdir(fullFileOrDir); 
    
    # 判断目标，判断目标是否文件
    @staticmethod
    def isfile(fullFileOrDir):
        return os.path.isfile(fullFileOrDir);
        
    # 获取文件名字
    @staticmethod
    def basename(fullFile):
        return os.path.basename(fullFile);
        
    # 获取目录名字
    @staticmethod
    def dirname(fullFile):
        return os.path.dirname(fullFile);
        
        
    # 分割文件目录和文件名字
    @staticmethod
    def split(fullFile):
        return os.path.split(fullFile);
    
    # 分割文件名字和扩展名
    @staticmethod
    def splitext(fullFile):
        return os.path.splitext(fullFile);
        
    # 连接目录
    @staticmethod
    def join(path_a, path_b, path_c):
        return os.path.join(path_a, path_b, path_c);
        
    
    # 获取绝对目录
    @staticmethod
    def abspath(fullPath):
        return os.path.abspath(fullPath);
    
    
    # 获取目录或者文件大小
    @staticmethod
    def getsize(fullFilePathOrDirPath):
        return os.path.getsize(fullFilePathOrDirPath);
        
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
                if(pThis != None and func != None):
                    func(pThis, UtilPath.join(root, oneFile), UtilPath.join(destPath, oneFile));
                else:
                    func(UtilPath.join(root, oneFile), UtilPath.join(destPath, oneFile));
                    

    