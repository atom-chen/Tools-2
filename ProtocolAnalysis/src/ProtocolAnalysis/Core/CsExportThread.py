# -*- coding: utf-8 -*-


from ProtocolAnalysis.Core.ThreadWrap import ThreadWrap
from ProtocolAnalysis.Core.AppSysBase import AppSysBase

 
# 导出 CS 代码
class CsExportThread(ThreadWrap):
    '''
    classdocs
    '''


    def __init__(self, threadName):
        '''
        Constructor
        '''
        super(CsExportThread, self).__init__(threadName, None);


    def start(self):
        AppSysBase.instance().getLogSysPtr().info('Start Cs Export Run')
        AppSysBase.instance().getConfigPtr().getProtoFilesList().parse()
        super(CsExportThread, self).start()


    def run(self):
        AppSysBase.instance().getLogSysPtr().info('CS Export Start Run')
        ThreadWrap.run(self)
        #super(CsExportProcess, self).run()
        AppSysBase.instance().getExportCSharpFile().export()
        AppSysBase.instance().getLogSysPtr().info('CS Export End Run')
        self.endRun()

