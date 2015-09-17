# -*- coding: utf-8 -*-


from ProtocolAnalysis.Core.ThreadWrap import ThreadWrap
from ProtocolAnalysis.Core.AppSysBase import AppSysBase


# 导出 Cpp 代码
class CppExportThread(ThreadWrap):
    '''
    classdocs
    '''


    def __init__(self, threadName):
        '''
        Constructor
        '''
        super(CppExportThread, self).__init__(threadName, None);


    def start(self):
        AppSysBase.instance().getLogSysPtr().info('Start Cpp Export Run')
        AppSysBase.instance().getConfigPtr().getProtoFilesList().parse()
        super(CppExportThread, self).start()


    def run(self):
        AppSysBase.instance().getLogSysPtr().info('CPP Export Start Run')
        super(CppExportThread, self).run()
        AppSysBase.instance().getExportCppFile().export()
        AppSysBase.instance().getLogSysPtr().info('CPP Export End Run')
        self.endRun()
        
        

        
        

