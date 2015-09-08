#-*- encoding=utf-8 -*-


#import subprocess
import sys
import traceback
import os
import shutil
from ProtocolAnalysis.Core.AppSysBase import AppSysBase
from ProtocolAnalysis.ProtoHandle.ProtoBase.ProtoKeyWord import ProtoKeyWord


class Utils(object):


    @staticmethod
    def copyFile(srcfilename, destfilename):
        if os.path.isfile(srcfilename):
            try:
                shutil.copyfile(srcfilename, destfilename)
                AppSysBase.instance().getLoggerPtr().info("copy file success: " + srcfilename)
            except:
                # 错误输出
                AppSysBase.instance().getLoggerPtr().info("copy file error: " + srcfilename)
                typeerr, value, tb = sys.exc_info()
                errstr = traceback.format_exception(typeerr, value, tb)
                AppSysBase.instance().getLoggerPtr().info(''.join(errstr))

        else:
            AppSysBase.instance().getLoggerPtr().info("cannot find file: " + srcfilename)


    # 获取字符串的编码
    @staticmethod
    def str2Byte(self):
        #self.subversion.encode("utf-8")
        return bytes(self.subversion, encoding = "utf8")


    # 遍历目录
    @staticmethod
    def traverseDirs(rootDir, handleDisp):
        for root, dirs, files in os.walk(rootDir):
            AppSysBase.instance().getLoggerPtr().info(''.join(dirs))
            Utils.traverseOneDirs(root, files, handleDisp)
    
    
    #一个目录的 md5 码
    @staticmethod
    def traverseOneDirs(directoryName, filesInDirectory, handleDisp):
        AppSysBase.instance().getLoggerPtr().info(directoryName)
        for fname in filesInDirectory:
            fpath = os.path.join(directoryName, fname)
            if not os.path.isdir(fpath):
                if handleDisp is not None:
                    handleDisp(fname, fpath)
    
    
    @staticmethod
    def joinPath(path, file):
        return os.path.join(path, file)


    @staticmethod
    def makeDir(path):
        # 检查目录
        if not os.path.exists(path):
            os.makedirs(path)
            
    
    @staticmethod        
    def logStackInfo():
        typeerr, value, tb = sys.exc_info()
        errstr = traceback.format_exception(typeerr, value, tb)
        AppSysBase.instance().getLoggerPtr().info(''.join(errstr))


    # 从字符串的左边获取一个符号，并且删除这个符号
    @staticmethod
    def getToken(strParam):
        Utils.skipSpaceAndBr(strParam)
        
        idx = 0;
        ret = ''
        while idx < len(strParam.m_fileStr):
            if strParam.m_fileStr[idx] == ' ' or strParam.m_fileStr[idx] == '\n' or strParam.m_fileStr[idx] == '\t':       # 如果遇到空格或者换行符，就算是一个符号
                break 
            ret += strParam.m_fileStr[idx]
            idx += 1
            
        if len(ret):
            strParam.m_fileStr = strParam.m_fileStr[idx:]         # 删除内容
            
        Utils.skipSpaceAndBr(strParam)
        
        return ret
        

    # 跳过当前行
    @staticmethod
    def skipCurLine(strParam):
        idx = 0;
        while idx < len(strParam.m_fileStr):
            if strParam.m_fileStr[idx] == '\n':
                break;
            idx += 1

        strParam.m_fileStr = strParam.m_fileStr[idx:]         # 删除内容
        

    # 跳过空格和换行
    @staticmethod
    def skipSpaceAndBr(strParam):
        idx = 0;
        while idx < len(strParam.m_fileStr):
            if strParam.m_fileStr[idx] != ' ' and strParam.m_fileStr[idx] != '\n' and strParam.m_fileStr[idx] != '\t':       # 如果遇到空格或者换行符，就算是一个符号
                break;
            idx += 1

        strParam.m_fileStr = strParam.m_fileStr[idx:]         # 删除内容


    # 当前符号是否是注释
    @staticmethod
    def tokenIsComment(tokenKey):
        if len(tokenKey) == 2:  # // 注释
            if tokenKey == ProtoKeyWord.eSingleLineComment:
                return True
        elif len(tokenKey) == 3:  # /** 注释
            if tokenKey == ProtoKeyWord.eMulLineCommentStart:
                return True
        elif len(tokenKey) > 2:
            tokenKey = tokenKey[:2]         # 截取前两个字节
            if tokenKey == ProtoKeyWord.eSingleLineComment:
                return True
        elif len(tokenKey) > 3:
            tokenKey = tokenKey[:3]         # 截取前两个字节
            if tokenKey == ProtoKeyWord.eMulLineCommentStart:
                return True

        return False


    # 修改路径为 "/"
    @staticmethod
    def normalPath(fullPath):
        ret = fullPath.replace('\\', '/')
        return ret


    # 获取文件的文件名字，没有扩展目录
    @staticmethod
    def getFileNameNoExt(fileName):
        normalFileName = Utils.normalPath(fileName)
        lastSlashIdx = normalFileName.rfind("/")
        lastDotIdx = normalFileName.rfind(".")
        ret = ""
        if lastSlashIdx != -1:       # 如果查找到斜杠
            if lastDotIdx != -1:
                ret = normalFileName[lastSlashIdx + 1:lastDotIdx]
            else:
                ret = normalFileName[lastSlashIdx + 1:]
        else:
            if lastDotIdx != -1:
                ret = normalFileName[:lastDotIdx]
            else:
                ret = normalFileName
        return ret
            
            
    # 添加一个水平制表
    @staticmethod
    def writeTab2File(fHandle):
        # 写入一个水平制表 \t
        fHandle.write("\t")
        
        
    # 写入一个空行
    @staticmethod
    def writeNewLine2File(fHandle):
        # 写入一个空行
        fHandle.write("\n")
        
    
    # 写入左大括号
    @staticmethod
    def writeLBrace2File(fHandle):
        fHandle.write("{")
        
        
    # 写入右大括号
    @staticmethod
    def writeRBrace2File(fHandle):
        fHandle.write("}")
    
    
    