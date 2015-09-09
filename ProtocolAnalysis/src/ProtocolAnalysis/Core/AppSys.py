#-*- encoding=utf-8 -*-


from ProtocolAnalysis.Core.AppSysBase import AppSysBase
from ProtocolAnalysis.Core.Config import Config
from ProtocolAnalysis.Core.Logger import Logger
from ProtocolAnalysis.Core.CodeConv import CodeConv
from ProtocolAnalysis.Core.Utils import Utils
from ProtocolAnalysis.ProtoHandle.CSharpExport.ExportCSharpFile import ExportCSharpFile
from ProtocolAnalysis.ProtoHandle.CSharpExport.CSharpExportComment import CSharpExportComment
from ProtocolAnalysis.ProtoHandle.CSharpExport.CSharpExportMessage import CSharpExportMessage
from ProtocolAnalysis.ProtoHandle.CSharpExport.CSharpExportEnum import CSharpExportEnum
from ProtocolAnalysis.ProtoHandle.CSharpExport.CSharpExportUsing import CSharpExportUsing
from ProtocolAnalysis.ProtoHandle.CSharpExport.CSharpExportNS import CSharpExportNS
from ProtocolAnalysis.LogSystem.LogSys import LogSys


from ProtocolAnalysis.UnitTest.TestMain import TestMain


class AppSys(AppSysBase):
    '''
    classdocs
    '''


    @staticmethod
    def instance():
        if AppSysBase.g_pInstance is None:
            AppSysBase.g_pInstance = AppSys()
        return AppSysBase.g_pInstance


    def __init__(self):
        '''
        Constructor
        '''

        
    def construct(self):
        # 实例定义
        self.m_bConvOver = True
        self.m_convThread = None
        
        # Utils 类
        self.m_clsUtils = Utils
        self.m_clsCSharpExportMessage = CSharpExportMessage
        self.m_clsCSharpExportEnum = CSharpExportEnum
        self.m_clsCSharpExportUsing = CSharpExportUsing
        self.m_clsCSharpExportNS = CSharpExportNS
        self.m_clsCSharpExportComment = CSharpExportComment
        
        self.m_config = Config()
        self.m_config.readInit('Config/Config.txt')
        
        self.m_logger = Logger()
        self.m_codeConv = CodeConv()
        self.m_exportCSharpFile = ExportCSharpFile()
        
        self.m_logSys = LogSys()
        
        # 单元测试放在最后初始化
        self.m_testMain = TestMain()
        self.m_testMain.run()


    def getConfigPtr(self):
        return self.m_config    


    def getLoggerPtr(self):
        return self.m_logger   


    def getCodeConvPtr(self):
        return self.m_codeConv   


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

    
    