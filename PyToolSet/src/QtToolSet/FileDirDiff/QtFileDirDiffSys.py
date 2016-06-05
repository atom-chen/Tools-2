# -*- coding: utf-8 -*-

'''
@brief: QtFileDirDiffSys
'''

from ToolSet.FileDirDiff.FileDirDiffSysImpl import FileDirDiffSysImpl

class QtFileDirDiffSys(FileDirDiffSysImpl):
    
    def __init__(self):
        super(QtFileDirDiffSys, self).__init__();
            
        self.mTypeId = "PyFileDirDiffSys";
        
