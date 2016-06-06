# -*- coding: utf-8 -*-

'''
@brief: VersionProcess
'''

from Libs.Thread.MProcess import MProcess;
from ToolSet.Common.ToolSetSys import ToolSetSys;
from ToolSet.FileDirDiff.VerParams import VerParams

class VersionProcess(MProcess):
    
    def __init__(self):
        #super(VersionProcess, self).__init__(ToolSetSys.instance(), "VersionProcess", None);
        params = VerParams();
        params.mVerConfig = ToolSetSys.instance().mFileDirDiffSys.mVerConfig;
        
        super(VersionProcess, self).__init__(params, "VersionProcess", None);
        
        self.mTypeId = "VersionProcess";
    
    def run(self, params):
        super(VersionProcess, self).run(params);
        
        self.mParams = params;
        self.buildVer();
    
        
    def buildVer(self):
        if(self.mParams.mVerConfig.isMakeResources()):
            self.buildResourcesVer();
        if(self.mParams.mVerConfig.isMakeStreamingAssets()):
            self.buildStreamingAssetsVer();
        if(self.mParams.mVerConfig.isMakePersistent()):
            self.buildPersistentVer();
    
    
    def buildResourcesVer(self):
        pass;
    
    
    def buildStreamingAssetsVer(self):
        pass;
        
    
    def buildPersistentVer(self):
        pass;

