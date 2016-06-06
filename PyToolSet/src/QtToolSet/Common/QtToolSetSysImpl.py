# -*- coding: utf-8 -*-

'''
@brief: QtToolSetSysImpl
'''

from QtToolSet.Common.QtToolSetSys import QtToolSetSys
from ToolSet.FileDirDiff.FileDirDiffSysImpl import FileDirDiffSysImpl
from QtToolSet.Common.LogWinProxy import LogWinProxy
from Libs.FrameWork.Ctx import Ctx

class QtToolSetSysImpl(QtToolSetSys):
    
    def __init__(self):
        super(QtToolSetSysImpl, self).__init__();
        
        self.mTypeId = "PyToolSetSysImpl";
        
    
    def init(self):
        super(QtToolSetSysImpl, self).init();

        self.mFileDirDiffSys = FileDirDiffSysImpl();
        
        self.mWinLogDeviceProxy = LogWinProxy();
        Ctx.instance().m_logSys.addLogDevice(self.mWinLogDeviceProxy);

    
