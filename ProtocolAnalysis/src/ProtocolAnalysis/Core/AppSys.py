#-*- encoding=utf-8 -*-

from ProtocolAnalysis.Core.AppSysBase import AppSysBase
from ProtocolAnalysis.Core.Config import Config
from ProtocolAnalysis.Core.Logger import Logger
from ProtocolAnalysis.Core.CodeConv import CodeConv
from ProtocolAnalysis.Core.Utils import Utils


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
        
        self.m_bConvOver = True
        self.m_convThread = None
        
        self.m_config = Config()
        self.m_config.readInit('config.txt')
        
        self.m_logger = Logger()
        self.m_codeConv = CodeConv()
        
        # Utils 类
        self.m_clsUtils = Utils
    
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
    