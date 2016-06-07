# -*- coding: utf-8 -*-

'''
@brief: VersionProcess
'''

from Libs.Thread.MProcess import MProcess
from ToolSet.Common.ToolSetSys import ToolSetSys
from ToolSet.FileDirDiff.VerParams import VerParams
from Libs.FileSystem.MDataStream import MDataStream
from Libs.FileSystem.MFileMode import MFileMode
from Libs.Tools.UtilPath import UtilPath
from Libs.Tools.UtilStr import UtilStr
from Libs.Tools.UtilHash import UtilHash
from ToolSet.FileDirDiff.AssetBundlesManifest import AssetBundlesManifest

class VersionProcess(MProcess):
    
    def __init__(self):
        #super(VersionProcess, self).__init__(ToolSetSys.instance(), "VersionProcess", None);
        params = VerParams();
        params.mVerConfig = ToolSetSys.instance().mFileDirDiffSys.mVerConfig;
        
        super(VersionProcess, self).__init__(params, "VersionProcess", None);
        
        self.mTypeId = "VersionProcess";
        
        self.mDataStream = None;
        self.mAssetBundlesManifest = None;


    
    def run(self, params):
        super(VersionProcess, self).run(params);

        self.buildVer();
    
        
    def buildVer(self):
        #if(self.mParams.isMakeResources()):
        self.buildResourcesVer();
        #if(self.mParams.isMakeStreamingAssets()):
        self.buildStreamingAssetsVer();
        #if(self.mParams.isMakePersistent()):
        #    self.buildPersistentVer();
    
    
    def buildResourcesVer(self):
        self.mDataStream = MDataStream(self.mParams.getResourcesVerFileFullOutPath(), MFileMode.WriteTxt);
        
        UtilPath.traverseDirectory(
                           self.mParams.getResourcesPath(), 
                           None, 
                           None, 
                           None,  
                           self, 
                           self.traverseResourcesPathHandle, 
                           True
                           );
        
        self.mDataStream.close();
        
    
    
    def buildStreamingAssetsVer(self):
        self.mDataStream = MDataStream(
                                       self.mParams.getStreamingAssetsVerFileFullOutPath(), 
                                       MFileMode.WriteTxt
                                       );
                                       
        self.mAssetBundlesManifest = AssetBundlesManifest();
        self.mAssetBundlesManifest.readManifest();
        
        UtilPath.traverseDirectory(
                           self.mParams.getStreamingAssetsPath(), 
                           None, 
                           None, 
                           None,  
                           self, 
                           self.traverseStreamingAssetsPathHandle, 
                           True
                           );
        
        self.mDataStream.close();
        self.mAssetBundlesManifest = None;
        
    
    def buildPersistentVer(self):
        self.mDataStream = MDataStream(
                                       self.mParams.getPersistentVerFileFullOutPath(), 
                                       MFileMode.WriteTxt
                                       );
        
        UtilPath.traverseDirectory(
                           self.mParams.getResourcesPath(), 
                           None, 
                           None, 
                           None,  
                           self, 
                           self.traverseResourcesPathHandle, 
                           True
                           );
        
        self.mDataStream.close();


    def traverseResourcesPathHandle(self, srcFullPath, srcCurName, destFullPath):
        extName = UtilPath.getFileExt(srcFullPath);
        if(extName != "meta"):
            resourcePath = UtilStr.replace(srcFullPath, self.mParams.getResourcesPath(), "");
            resourcePath = UtilStr.truncate(resourcePath, 1);
            resUniqueId = UtilPath.getFilePathNoExt(resourcePath);
            loadPath = UtilPath.getFilePathNoExt(resourcePath);
            fileMd5 = UtilHash.buildFileMd5(srcFullPath);
            fileSize = UtilPath.getsize(srcFullPath);
            strContent = UtilStr.format(
                                 "{0}={1}={2}={3}={4}", 
                                 resourcePath, 
                                 resUniqueId,
                                 loadPath,
                                 fileMd5,
                                 fileSize
                                 );

            self.mDataStream.writeLine(strContent);
            
            
    def traverseStreamingAssetsPathHandle(self, srcFullPath, srcCurName, destFullPath):
        extName = UtilPath.getFileExt(srcFullPath);
        if(extName != "meta"):
            resourcePath = UtilStr.replace(srcFullPath, self.mParams.getStreamingAssetsPath(), "");
            resourcePath = UtilStr.truncate(resourcePath, 1);
            assetBundlesItem = self.mAssetBundlesManifest.getAssetBundlesItem(resourcePath);
            resUniqueId = UtilPath.getFilePathNoExt(resourcePath);
            loadPath = resourcePath;
            if(assetBundlesItem != None):
                resourcePath = assetBundlesItem.mAssetItem.mAssetList[0];
            
            fileMd5 = UtilHash.buildFileMd5(srcFullPath);
            fileSize = UtilPath.getsize(srcFullPath);
            strContent = UtilStr.format(
                                 "{0}={1}={2}={3}={4}", 
                                 resourcePath, 
                                 resUniqueId,
                                 loadPath,
                                 fileMd5,
                                 fileSize
                                 );

            self.mDataStream.writeLine(strContent);


    def traversePersistentPathHandle(self, srcFullPath, srcCurName, destFullPath):
        extName = UtilPath.getFileExt(srcFullPath);
        if(extName != "meta"):
            resourcePath = UtilStr.replace(srcFullPath, self.mParams.getResourcesPath(), "");
            resourcePath = UtilStr.truncate(resourcePath, 1);
            resUniqueId = UtilPath.getFilePathNoExt(resourcePath);
            loadPath = UtilPath.getFilePathNoExt(resourcePath);
            fileMd5 = UtilHash.buildFileMd5(srcFullPath);
            fileSize = UtilPath.getsize(srcFullPath);
            strContent = UtilStr.format(
                                 "{0}={1}={2}={3}={4}", 
                                 resourcePath, 
                                 resUniqueId,
                                 loadPath,
                                 fileMd5,
                                 fileSize
                                 );

            self.mDataStream.writeLine(strContent);

