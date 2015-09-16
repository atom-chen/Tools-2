# -*- coding: utf-8 -*-


from ProtocolAnalysis.Core.ProcessWrap import ProcessWrap
from ProtocolAnalysis.Core.AppSysBase import AppSysBase


# 导出 Cpp 代码
class CppExportProcess(ProcessWrap):
    '''
    classdocs
    '''


    def __init__(self, processName):
        '''
        Constructor
        '''
        super(CppExportProcess, self).__init__(processName, None);


    def start(self):
        super(CppExportProcess, self).start()
        AppSysBase.instance().getConfigPtr().getProtoFilesList().parse()


    def run(self):
        AppSysBase.instance().getLogSysPtr().info('CPP Export Start Run')
        super(CppExportProcess, self).run()
        AppSysBase.instance().getExportCppFile().export()
        
        

        
        

