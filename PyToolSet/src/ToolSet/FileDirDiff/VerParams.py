# -*- coding: utf-8 -*-

'''
@brief: Process 传递的参数
'''

from Libs.Core.GObject import GObject

class VerParams(GObject):
    def __init__(self):
        self.mId = 10;
        self.mVerConfig = None;


    def isMakeResources(self):
        return self.mVerConfig.isMakeResources();
    
    
    def isMakeStreamingAssets(self):
        return self.mVerConfig.isMakeStreamingAssets();
    
    
    def isMakePersistent(self):
        return self.mVerConfig.isMakePersistent();
    
    def getResourcesPath(self):
        return self.mVerConfig.getResourcesPath();
        

    def getResourcesVerFileFullOutPath(self):
        return self.mVerConfig.getResourcesVerFileFullOutPath();
    
