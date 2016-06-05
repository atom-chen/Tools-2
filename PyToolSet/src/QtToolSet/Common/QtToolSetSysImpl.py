# -*- coding: utf-8 -*-

'''
@brief: PyToolSetSysImpl
'''

from PyToolSet.Common.PyToolSetSys import PyToolSetSys
from ToolSet.FileDirDiff.FileDirDiffSysImpl import FileDirDiffSysImpl
from PyToolSet.Common.LogWinProxy import LogWinProxy
from Libs.FrameWork.Ctx import Ctx

class PyToolSetSysImpl(PyToolSetSys):
    
    def __init__(self):
        super(PyToolSetSysImpl, self).__init__();
        
        self.mTypeId = "PyToolSetSysImpl";
        
    
    def init(self):
        super(PyToolSetSysImpl, self).init();

        self.mFileDirDiffSys = FileDirDiffSysImpl();
        
        self.mWinLogDeviceProxy = LogWinProxy();
        Ctx.instance().m_logSys.addLogDevice(self.mWinLogDevice);

    
