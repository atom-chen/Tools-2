# -*- coding: utf-8 -*-

'''
@brief: PyFileDirDiffSys
'''

from ToolSet.FileDirDiff.FileDirDiffSysImpl import FileDirDiffSysImpl

class PyFileDirDiffSys(FileDirDiffSysImpl):
    
    def __init__(self):
        super(PyFileDirDiffSys, self).__init__();
            
        self.mTypeId = "PyFileDirDiffSys";
        