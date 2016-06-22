# -*- coding: utf-8 -*-

'''
@brief: VersionProcess
'''

from Libs.Thread.MProcess import MProcess;
from ToolSet.Common.ToolSetSys import ToolSetSys;
from ToolSet.FileDirDiff.VerParams import VerParams;
from Libs.FileSystem.MDataStream import MDataStream;
from Libs.FileSystem.MFileMode import MFileMode;
from Libs.Tools.UtilPath import UtilPath;
from Libs.Tools.UtilStr import UtilStr;
from Libs.Tools.UtilHash import UtilHash;
from ToolSet.FileDirDiff.AssetBundlesManifest import AssetBundlesManifest;
from ToolSet.FileDirDiff.VerProcessSys import VerProcessSys;
from Libs.Tools.UtilTime import UtilTime;

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
        self.copyLuaToResources();
        self.createAssetBundleManifest();
        
        if(self.mParams.isMakePersistent()):
            self.copyFromResourcesToPersistent();
            self.buildPersistentVer();
        if(self.mParams.isMakeStreamingAssets()):
            self.copyFromPersistentToStreamingAssets();
            self.buildStreamingAssetsVer();
        if(self.mParams.isMakeResources()):
            self.buildResourcesVer();
        if(self.mParams.isMakeMini()):
            self.buildMiniVer();


    def buildResourcesVer(self):
        self.mDataStream = MDataStream(self.mParams.getResourcesVerFileFullOutPath(), MFileMode.WriteTxt);

        strContent = "aaaaa";
        self.mDataStream.writeLine(strContent);

        
        self.mDataStream.close();
        
        
            # 拷贝资源从 Persistent 到 StreamingAssets 目录下
    def copyFromPersistentToStreamingAssets(self):
        UtilPath.traverseDirectory(
                                   self.mParams.getPersistentPath(), 
                                   self.mParams.getStreamingAssetsPath(), 
                                   None, 
                                   None, 
                                   self, 
                                   self.onCopyFromPersistentToStreamingAssets, 
                                   True, 
                                   False
                                   );
                                   
                                   
    def onCopyFromPersistentToStreamingAssets(self, srcFullPath, srcCurName, destFullPath):
        extName = UtilPath.getFileExt(srcFullPath);
        if(not self.mParams.isIgnoreFileByExt(extName) and not self.mParams.mVerConfig.isPersistentVerFileName(srcCurName)):
            destFullFilePath = UtilPath.combine(destFullPath, srcCurName);
            if(UtilPath.exists(destFullFilePath)):
                UtilPath.deleteFile(destFullFilePath);
            elif(not UtilPath.exists(destFullPath)):
                UtilPath.makedirs(destFullPath);
                
            UtilPath.copyFile(srcFullPath, destFullFilePath);


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


    # 拷贝资源从 Resources 到 Persistent 目录下
    def copyFromResourcesToPersistent(self):
        UtilPath.traverseDirectory(
                                   self.mParams.getResourcesPath(), 
                                   self.mParams.getPersistentPath(), 
                                   None, 
                                   None, 
                                   self, 
                                   self.onCopyFromResourcesToPersistent, 
                                   True, 
                                   False
                                   );
                                   
                                   
    def onCopyFromResourcesToPersistent(self, srcFullPath, srcCurName, destFullPath):
        extName = UtilPath.getFileExt(srcFullPath);
        if(not self.mParams.isIgnoreFileByExt(extName) and not self.mParams.mVerConfig.isResourcesVerFileName(srcCurName)):
            if(not self.mParams.mVerConfig.isPrefabOrSceneRes(extName)):
                destFullFilePath = UtilPath.combine(destFullPath, srcCurName);
                if(UtilPath.exists(destFullFilePath)):
                    UtilPath.deleteFile(destFullFilePath);
                elif(not UtilPath.exists(destFullPath)):
                    UtilPath.makedirs(destFullPath);
                    
                UtilPath.copyFile(srcFullPath, destFullFilePath);


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


    Count = 0;

    def traverseResourcesPathHandle(self, srcFullPath, srcCurName, destFullPath):
        extName = UtilPath.getFileExt(srcFullPath);
        if(not VerProcessSys.instance().mParams.isIgnoreFileByExt(extName)):
            VersionProcess.Count = VersionProcess.Count + 1;
            if(VersionProcess.Count > 1):
                return;
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

            strContent = "aaaaa";
            self.mDataStream.writeLine(strContent);
            

    def traverseResourcesScenesPathHandle(self, srcFullPath, srcCurName, destFullPath):
        return;
        extName = UtilPath.getFileExt(srcFullPath);
        if(not VerProcessSys.instance().mParams.isIgnoreFileByExt(extName)):
            resourcePath = UtilStr.replace(srcFullPath, self.mParams.getAssetPath(), "");
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
            if(VerProcessSys.instance().mParams.mVerConfig.isAssetBundlesRes(extName) and assetBundlesItem != None):
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
            if(VerProcessSys.instance().mParams.mVerConfig.isAssetBundlesRes(extName) and assetBundlesItem != None):
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


    def buildMiniVer(self):
        if(UtilPath.exists(self.mParams.mVerConfig.getMiniVerFileFullOutPath())):
            UtilPath.deleteFile(self.mParams.mVerConfig.getMiniVerFileFullOutPath());
        
        self.mDataStream = MDataStream(
                                       self.mParams.mVerConfig.getMiniVerFileFullOutPath(), 
                                       MFileMode.WriteTxt
                                       );
        
        verLine = UtilStr.format('Version={0}', UtilTime.getTimeStamp());
        self.mDataStream.writeLine(verLine);
        
        pVerPath = self.mParams.mVerConfig.getPersistentVerFileFullOutPath();
        if(UtilPath.exists(pVerPath)):
            resourcePath = UtilStr.replace(pVerPath, self.mParams.getPersistentPath(), "");
            resourcePath = UtilStr.truncate(resourcePath, 1);
            resUniqueId = UtilPath.getFilePathNoExt(resourcePath);
            loadPath = resourcePath;
            fileMd5 = UtilHash.buildFileMd5(pVerPath);
            fileSize = UtilPath.getsize(pVerPath);
            
            strContent = UtilStr.format(
                     "{0}={1}={2}={3}={4}", 
                     resourcePath, 
                     resUniqueId,
                     loadPath,
                     fileMd5,
                     fileSize
                     );
            self.mDataStream.writeLine(strContent);
        
        self.mDataStream.close();
        

    # 拷贝 Lua 文件到 Resources 文件夹
    def copyLuaToResources(self):
        srcPath = self.mParams.mVerConfig.getLuaSrcPath();
        destPath = self.mParams.mVerConfig.getLuaDestPath();
        
        UtilPath.traverseDirectory(
                           srcPath, 
                           destPath, 
                           None, 
                           None,  
                           self, 
                           self.traverseLua, 
                           True
                           );        

    # 遍历 Lua 目录，然后拷贝，并且将扩展名字修改成 txt 的扩展名字
    def traverseLua(self, srcFullPath, srcCurName, destFullPath):
        extName = UtilPath.getFileExt(srcCurName);
        if(extName == 'lua'):
            fileNameNoExt = UtilPath.getFileNameNoExt(srcCurName);
            destFilePath = UtilStr.format("{0}/{1}.txt", destFullPath, fileNameNoExt);
            if(UtilPath.exists(destFilePath)):
                UtilPath.deleteFile(destFilePath);
            elif(not UtilPath.exists(destFullPath)):
                UtilPath.makedirs(destFullPath);
            UtilPath.copyFile(srcFullPath, destFilePath);
        
        

