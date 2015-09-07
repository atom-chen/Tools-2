#-*- encoding=utf-8 -*-


from ProtocolAnalysis.Core.AppSysBase import AppSysBase
from ProtocolAnalysis.Core.ThreadWrap import ThreadWrap


class ConvThread(ThreadWrap):
    
    def __init__(self, threadName):
        super(ConvThread, self).__init__(threadName = threadName)

    def run(self):
        AppSysBase.instance().setConvOver(False)
        AppSysBase.instance().getLoggerPtr().info("File Conv Start")
        
        AppSysBase.instance().getClsUtils().makeDir(AppSysBase.instance().getConfigPtr().m_tmpCodePath)
        AppSysBase.instance().getClsUtils().makeDir(AppSysBase.instance().getConfigPtr().m_destCodePath)
        
        AppSysBase.instance().getClsUtils().traverseDirs(AppSysBase.instance().getConfigPtr().m_srcCodePath, AppSysBase.instance().getCodeConvPtr().convProtocolAnalysis)

        AppSysBase.instance().getLoggerPtr().info("File Conv End")
        AppSysBase.instance().setConvOver(True)


