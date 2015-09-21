# -*- coding: utf-8 -*-


from ProtocolAnalysis.Core.ProcessWrap import ProcessWrap
from ProtocolAnalysis.Core.AppSysBase import AppSysBase

 
# 导出 CS 代码
class CsExportProcess(ProcessWrap):
    '''
    classdocs
    '''


    def __init__(self, processName):
        '''
        Constructor
        '''
        super(CsExportProcess, self).__init__(processName, None);


    def start(self):
        AppSysBase.instance().getConfigPtr().getProtoFilesList().parse()
        super(CsExportProcess, self).start()


    def run(self):
        AppSysBase.instance().getLogSysPtr().info('CPP Export Start Run')
        ProcessWrap.run(self)
        #super(CsExportProcess, self).run()
        AppSysBase.instance().getExportCSharpFile().export()
        

