#-*- encoding=utf-8 -*-


from ProtocolAnalysis.Core.AppSysBase import AppSysBase
from ProtocolAnalysis.Core.Config import Config
from ProtocolAnalysis.Core.Utils import Utils


from ProtocolAnalysis.ProtoHandle.CSharpExport.ExportCSharpFile import ExportCSharpFile
from ProtocolAnalysis.ProtoHandle.CSharpExport.CSharpExportComment import CSharpExportComment
from ProtocolAnalysis.ProtoHandle.CSharpExport.CSharpExportMessage import CSharpExportMessage
from ProtocolAnalysis.ProtoHandle.CSharpExport.CSharpExportEnum import CSharpExportEnum
from ProtocolAnalysis.ProtoHandle.CSharpExport.CSharpExportUsing import CSharpExportUsing
from ProtocolAnalysis.ProtoHandle.CSharpExport.CSharpExportNS import CSharpExportNS

from ProtocolAnalysis.ProtoHandle.CppExport.ExportCppFile import ExportCppFile
from ProtocolAnalysis.ProtoHandle.CppExport.CppExportComment import CppExportComment
from ProtocolAnalysis.ProtoHandle.CppExport.CppExportMessage import CppExportMessage
from ProtocolAnalysis.ProtoHandle.CppExport.CppExportEnum import CppExportEnum
from ProtocolAnalysis.ProtoHandle.CppExport.CppExportInclude import CppExportInclude
from ProtocolAnalysis.ProtoHandle.CppExport.CppExportNS import CppExportNS
from ProtocolAnalysis.ProtoHandle.CppExport.CppExportPragma import CppExportPragma
from ProtocolAnalysis.ProtoHandle.CppExport.CppExportDefine import CppExportDefine

from ProtocolAnalysis.LogSystem.LogSys import LogSys
from ProtocolAnalysis.Core.UtilFile import UtilFile
from ProtocolAnalysis.Core.CppExportProcess import CppExportProcess
from ProtocolAnalysis.Core.CsExportProcess import CsExportProcess


from ProtocolAnalysis.UnitTest.TestMain import TestMain


class AppSys(AppSysBase):
    '''
    classdocs
    '''


    #@staticmethod
    #def instance():
    #    if AppSysBase.g_pInstance is None:
    #        AppSysBase.g_pInstance = AppSys()
    #    return AppSysBase.g_pInstance


    def __init__(self):
        '''
        Constructor
        '''
        self.construct()
        
        
    def __new__(cls, *args, **kwd):         # 在__init__之前调用
        if AppSysBase.g_pInstance is None:    # 生成唯一实例
            AppSysBase.g_pInstance = object.__new__(cls, *args, **kwd)
        return AppSysBase.g_pInstance

        
    def construct(self):
        # 实例定义
        self.m_bConvOver = True
        self.m_convThread = None
        
        self.m_logSys = LogSys()
        
        # Utils 类
        self.m_clsUtils = Utils
        self.m_clsUtilFile = UtilFile
        
        
        # CSharp 导出
        self.m_clsCSharpExportMessage = CSharpExportMessage
        self.m_clsCSharpExportEnum = CSharpExportEnum
        self.m_clsCSharpExportUsing = CSharpExportUsing
        self.m_clsCSharpExportNS = CSharpExportNS
        self.m_clsCSharpExportComment = CSharpExportComment
        
        
        
        # Cpp 导出
        self.m_clsCppExportMessage = CppExportMessage
        self.m_clsCppExportEnum = CppExportEnum
        self.m_clsCppExportInclude = CppExportInclude
        self.m_clsCppExportNS = CppExportNS
        self.m_clsCppExportComment = CppExportComment
        self.m_clsCppExportPragma = CppExportPragma
        self.m_clsCppExportDefine = CppExportDefine
        
        
        
        self.m_config = Config()
        self.m_config.readInit('Config/Config.txt')
        self.m_exportCSharpFile = ExportCSharpFile()
        self.m_exportCppFile = ExportCppFile()
        
        self.m_exportCppProcess = CppExportProcess("CppExportProcess")
        self.m_exportCsProcess = CsExportProcess("CsExportProcess")
        
        # 单元测试放在最后初始化
        #self.m_testMain = TestMain()
        #self.m_testMain.run()


    def getConfigPtr(self):
        return self.m_config    


    def getLogSysPtr(self):
        return self.m_logSys   


    def getConvOver(self):
        return self.m_bConvOver


    def setConvOver(self, rhv):
        self.m_bConvOver = rhv


    def getClsUtils(self):
        return self.m_clsUtils


    def getConvThread(self):
        self.m_convThread


    def setConvThread(self, rhv): 
        self.m_convThread = rhv


    def getExportCSharpFile(self):
        return self.m_exportCSharpFile
    
    
    def getExportCppFile(self):
        return self.m_exportCppFile
    
    
    def getClsCSharpExportMessage(self):
        return self.m_clsCSharpExportMessage
    

    def getClsCSharpExportEnum(self):
        return self.m_clsCSharpExportEnum
    
    
    def getClsCSharpExportComment(self):
        return self.m_clsCSharpExportComment
    
    
    def getClsCSharpExportUsing(self):
        return self.m_clsCSharpExportUsing
    
    
    def getClsCSharpExportNS(self):
        return self.m_clsCSharpExportNS
    
    
    def getClsCppExportMessage(self):
        return self.m_clsCppExportMessage
        
        
    def getClsCppExportEnum(self):
        return self.m_clsCppExportEnum

        
    def getClsCppExportInclude(self):
        return self.m_clsCppExportInclude
        
        
    def getClsCppExportNS(self):
        return self.m_clsCppExportNS
        
        
    def getClsCppExportComment(self):
        return self.m_clsCppExportComment
        
        
    def getClsCppExportPragma(self):
        return self.m_clsCppExportPragma
        
        
    def getClsCppExportDefine(self):
        return self.m_clsCppExportDefine


    def getClsUtilFile(self):
        return self.m_clsUtilFile
    
    
    def getCppExportProcess(self):
        return self.m_exportCppProcess
    
    
    def getCsExportProcess(self):
        return self.m_exportCppProcess
    
    
    
    