# -*- coding: utf-8 -*-

'''
@brief: VersionProcess
'''

from Libs.Thread.MProcess import MProcess;
from ToolSet.Common.ToolSetSys import ToolSetSys;

class VersionProcess(MProcess):
    
    def __init__(self):
        super(VersionProcess, self).__init__("VersionProcess", None);
        
        self.mTypeId = "VersionProcess";
    
    def run(self, params):
        super(VersionProcess, self).run(params);
        
        self.buildVer();
    
        
    def buildVer(self):
        if(ToolSetSys.instance().mFileDirDiffSys.mConfig.isMakeResources()):
            self.buildResourcesVer();
        if(ToolSetSys.instance().mFileDirDiffSys.mConfig.isMakeStreamingAssets()):
            self.buildStreamingAssetsVer();
        if(ToolSetSys.instance().mFileDirDiffSys.mConfig.isMakePersistent()):
            self.buildPersistentVer();
    
    
    def buildResourcesVer(self):
        pass;
    
    
    def buildStreamingAssetsVer(self):
        pass;
        
    
    def buildPersistentVer(self):
        pass;
    
    
    
        
        
        
