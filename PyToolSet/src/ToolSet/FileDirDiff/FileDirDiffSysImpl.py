# -*- coding: utf-8 -*-

'''
@author: FileDirDiffSysImpl
'''

from ToolSet.FileDirDiff.VerConfig import VerConfig;
from ToolSet.FileDirDiff.FileDirDiffSys import FileDirDiffSys;
from ToolSet.FileDirDiff.VersionProcess import VersionProcess;

class FileDirDiffSysImpl(FileDirDiffSys):
    
    def __init__(self):
        super(FileDirDiffSysImpl, self).__init__();
        
        self.mTypeId = "FileDirDiffSysImpl";
        
        self.mVerConfig = VerConfig();


    def start(self):
        self.mConfig.readInit('Config/Config.txt');


    def startVerProcess(self):
        super(FileDirDiffSysImpl, self).startVerProcess();
        
        if(self.isVersionOver()):
            self.mVerProcess = VersionProcess();
            self.mVerProcess.start();
        
        
        
