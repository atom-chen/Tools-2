# -*- coding: utf-8 -*-

'''
@brief: ToolSetSysImpl
'''

from ToolSet.Common.ToolSetSys import ToolSetSys
from ToolSet.FileDirDiff.FileDirDiffSysImpl import FileDirDiffSysImpl

class ToolSetSysImpl(ToolSetSys):
    
    def __init__(self):
        super(ToolSetSysImpl, self).__init__();
        
        self.mTypeId = "ToolSetSysImpl";
        
        self.mFileDirDiffSys = FileDirDiffSysImpl();
    
