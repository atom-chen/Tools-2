#-*- encoding=utf-8 -*-

from ProtocolAnalysis.DataStruct import MStack
from ProtocolAnalysis.ProtoParse.CppExport import CppItemBase
from ProtocolAnalysis.ProtoParse.CppExport import CppMultiComment
from ProtocolAnalysis.ProtoParse.CppExport import TokenParseData
from ProtocolAnalysis.ProtoParse.CppExport import CppStructItem
from ProtocolAnalysis.Core.AppSysBase import AppSysBase


class CppFile(CppItemBase.CppItemBase):
    '''
    classdocs
    '''


    def __init__(self):
        '''
        Constructor
        '''
        self.m_pStack = MStack.MStack(10)
        self.m_curCppElem = None
    
    
    #for line in fHandle:
    #line.lstrip()          # 删除左边的空格
    #lineList = line.split()            # 空格分割
    #if len(lineList):           # 如果还有内容
    
    def parseCpp(self, filePathName):
        with open(filePathName, 'r', encoding = 'utf8') as fHandle:
            #tokenParseData = TokenParseData.TokenParsTokenParseData
            tokenParseData = None         
            try:
                tokenParseData.m_fileStr = fHandle.read();       # 读取所有的内容
            except Exception as e:
                AppSysBase.instance().getClsUtils().logStackInfo()
                AppSysBase.instance().getLoggerPtr().instance().info("{0} 文件解析错误".format(filePathName))
                return
            
                
            AppSysBase.instance().getClsUtils().skipSpaceAndBr(tokenParseData)          # 删除左边的空格
            while len(tokenParseData.m_fileStr):
                oneToken = AppSysBase.instance().getClsUtils().getToken(tokenParseData)
                if oneToken == "#ifndef":
                    AppSysBase.instance().getClsUtils().skipCurLine(tokenParseData)
                elif oneToken == "#define":
                    AppSysBase.instance().getClsUtils().skipCurLine(tokenParseData)
                elif oneToken == "#include":
                    AppSysBase.instance().getClsUtils().skipCurLine(tokenParseData)
                elif oneToken[0:3] == "/**":
                    self.m_curCppElem = CppMultiComment.CppMultiComment()
                    self.m_pStack.push(self.m_curCppElem)
                    self.m_curCppElem.parseCppElem(tokenParseData)
                elif oneToken[0:2] == "//":
                    AppSysBase.instance().getClsUtils().skipCurLine(tokenParseData)
                elif oneToken == "struct":
                    self.m_curCppElem = CppStructItem.CppStructItem()
                    self.m_curCppElem.parseCppElem(tokenParseData)
    
                
                AppSysBase.instance().getClsUtils().skipSpaceAndBr(tokenParseData)          # 删除左边的空格
                
