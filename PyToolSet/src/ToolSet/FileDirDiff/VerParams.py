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
    

    def isMakeMini(self):
        return self.mVerConfig.isMakeMini();
    
    
    def getAssetPath(self):
        return self.mVerConfig.getAssetPath();
    
    
    def getResourcesPath(self):
        return self.mVerConfig.getResourcesPath();
        
        
    def getStreamingAssetsPath(self):
        return self.mVerConfig.getStreamingAssetsPath();
    
    
    def getPersistentPath(self):
        return self.mVerConfig.getPersistentPath();
    
       
    def getScenesPath(self):
        return self.mVerConfig.getScenesPath();


    def getResourcesVerFileFullOutPath(self):
        return self.mVerConfig.getResourcesVerFileFullOutPath();
    
    
    def getStreamingAssetsVerFileFullOutPath(self):
        return self.mVerConfig.getStreamingAssetsVerFileFullOutPath();
    
    
    def getPersistentVerFileFullOutPath(self):
        return self.mVerConfig.getPersistentVerFileFullOutPath();
    
    
    def getAssetBundlesManifestPath(self):
        return self.mVerConfig.getAssetBundlesManifestPath();


    def isIgnoreFileByExt(self, extName):
        return self.mVerConfig.isIgnoreFileByExt(extName);



