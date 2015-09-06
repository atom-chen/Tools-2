#-*- encoding=utf-8 -*-

from ProtocolAnalysis.Core.AppSysBase import AppSysBase
from ProtocolAnalysis.CppParse import CppFile

class CodeConv(object):
    '''
    classdocs
    '''

    def __init__(self):
        '''
        Constructor
        '''
        pass
    
    
    # 转换 dirName 目录名字中的文件  fileName 
    def convProtocolAnalysis(self, fineName, filePathName):
        if fineName in AppSysBase.instance().getConfigPtr().m_fileNameList:
            AppSysBase.instance().getLoggerPtr().info(filePathName)
            
            cppFile = CppFile.CppFile()
            cppFile.parseCpp(filePathName)

