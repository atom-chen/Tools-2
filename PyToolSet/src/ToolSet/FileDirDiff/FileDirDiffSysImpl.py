# -*- coding: utf-8 -*-

'''
@author: FileDirDiffSysImpl
'''

from ToolSet.FileDirDiff.Config import Config
from ToolSet.FileDirDiff.FileDirDiffSys import FileDirDiffSys

class FileDirDiffSysImpl(FileDirDiffSys):
    
    def __init__(self):
        super(FileDirDiffSysImpl, self).__init__();
        
        self.mTypeId = "FileDirDiffSysImpl";
        
        self.mConfig = Config();


    def start(self):
        self.mConfig.readInit('Config/Config.txt');



