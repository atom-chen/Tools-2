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
from ToolSet.FileDirDiff.VerProcessSys import VerProcessSys

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
        
        VerProcessSys.instance().mParams = self.mParams;

        self.buildVer();
        
    def createAssetBundleManifest(self):
        if(self.mAssetBundlesManifest == None):
            self.mAssetBundlesManifest = AssetBundlesManifest();
            self.mAssetBundlesManifest.readManifest();
            self.mAssetBundlesManifest.findResourcsName();
            self.mAssetBundlesManifest.calcMd5(VerProcessSys.instance().mParams.mVerConfig.getPersistentPath());
    
        
    def buildVer(self):
        self.createAssetBundleManifest();
        
        if(self.mParams.isMakePersistent()):
            self.buildPersistentVer();
        if(self.mParams.isMakeStreamingAssets()):
            self.buildStreamingAssetsVer();
        if(self.mParams.isMakeResources()):
            self.buildResourcesVer();


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


    def buildPersistentVer(self):
        self.mDataStream = MDataStream(
                                       self.mParams.getPersistentVerFileFullOutPath(), 
                                       MFileMode.WriteTxt
                                       );
        
        UtilPath.traverseDirectory(
                           self.mParams.getPersistentPath(), 
                           None, 
                           None, 
                           None,  
                           self, 
                           self.traversePersistentPathHandle, 
                           True
                           );
        
        self.mDataStream.close();


    def traverseResourcesPathHandle(self, srcFullPath, srcCurName, destFullPath):
        extName = UtilPath.getFileExt(srcFullPath);
        if(not VerProcessSys.instance().mParams.isIgnoreFileByExt(extName)):
            resourcePath = UtilStr.replace(srcFullPath, self.mParams.getResourcesPath(), "");
            resourcePath = UtilStr.truncate(resourcePath, 1);
            resUniqueId = UtilPath.getFilePathNoExt(resourcePath);
            loadPath = UtilPath.getFilePathNoExt(resourcePath);
            if(VerProcessSys.instance().mParams.mVerConfig.isPrefabOrSceneRes(extName)):
                fileMd5 = self.mAssetBundlesManifest.getResPathMd5(resourcePath);
            else:
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
        if(not VerProcessSys.instance().mParams.isIgnoreFileByExt(extName)):
            resourcePath = UtilStr.replace(srcFullPath, self.mParams.getStreamingAssetsPath(), "");
            resourcePath = UtilStr.truncate(resourcePath, 1);
            assetBundlesItem = self.mAssetBundlesManifest.getAssetBundlesItem(resourcePath);
            resUniqueId = UtilPath.getFilePathNoExt(resourcePath);
            loadPath = resourcePath;
            if(VerProcessSys.instance().mParams.mVerConfig.isPrefabOrSceneRes(extName) and assetBundlesItem != None):
                index = 0;
                while(index < assetBundlesItem.mAssetItemList.mAssetList.length()):
                    resourcePath = assetBundlesItem.mAssetItemList.mAssetList[index].mABPath;
                    
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
                    
                    index = index + 1;
            else:
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
        if(not VerProcessSys.instance().mParams.isIgnoreFileByExt(extName)):
            resourcePath = UtilStr.replace(srcFullPath, self.mParams.getPersistentPath(), "");
            resourcePath = UtilStr.truncate(resourcePath, 1);
            assetBundlesItem = self.mAssetBundlesManifest.getAssetBundlesItem(resourcePath);
            resUniqueId = UtilPath.getFilePathNoExt(resourcePath);
            loadPath = resourcePath;
            if(VerProcessSys.instance().mParams.mVerConfig.isPrefabOrSceneRes(extName) and assetBundlesItem != None):
                index = 0;
                while(index < assetBundlesItem.mAssetItemList.mAssetList.length()):
                    resourcePath = assetBundlesItem.mAssetItemList.mAssetList[index].mABPath;
                    
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
                    
                    index = index + 1;
            else:
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


