# -*- coding: utf-8 -*-

from Libs.Core.GObject import GObject
from Libs.Tools.UtilPath import UtilPath
from Libs.DataStruct.MList import MList

'''
@brief 生成版本的类型
'''
class eMakeType(GObject):
    eResources = 0;
    eStreamingAssets = 1;
    ePersistent = 2;
    

'''
@brief: Config
'''

class VerConfig(GObject):
    
    def __init__(self):
        super(VerConfig, self).__init__();
        
        self.mTypeId = "Config";
        
        self.mProjRootPath = "E:/Self/Self/unity/unitygame/Client_Start";    # 工程根目录
        self.mOutPutPath = "E:/Self/Self/unity/unitygame/Client_Start/OutPut";         # 输出目录
        self.mDestPath = "";        # 最终目录
        
        self.mAssetName = "Assets";       # Assets 目录名字
        self.mResourcesName = "Resources";  # Resources 目录名字
        self.mStreamingAssetsName = "StreamingAssets";  # StreamingAssets 目录名字
        self.mScenesName = "Scenes";
        
        self.mMakeVerTypeList = MList();       # 生成版本的类型
        self.mMakeVerTypeList.add(eMakeType.eResources);
        self.mMakeVerTypeList.add(eMakeType.eStreamingAssets);
        self.mMakeVerTypeList.add(eMakeType.ePersistent);
        
        self.mResourcesVerFileName = "Version_R.txt";       # Resources 版本文件名字
        self.mStreamingAssetsVerFileName = "Version_S.txt"; # StreamingAssets 版本文件名字
        self.mPersistentVerFileName = "Version_P.txt";      # Persistent 版本文件名字
        self.mMinVerFileName = "Version_Mini.txt";          # 就是版本的版本
        
        self.mPrefabResExtNameList = MList();        # Resources 目录下使用 AssetBundles 打包资源的资源扩展名字列表
        self.mPrefabResExtNameList.Add("prefab");
        self.mPrefabResExtNameList.Add("mat");
        self.mPrefabResExtNameList.Add("shader");
        self.mPrefabResExtNameList.Add("png");
        self.mPrefabResExtNameList.Add("jpg");
        self.mPrefabResExtNameList.Add("tga");
        
        self.mAssetBundlesExtNameList = MList();     # AssetBundles 资源的扩展名字
        self.mAssetBundlesExtNameList.Add("unity3d");
        
        self.mSceneExtNameList = MList();           # 场景文件扩赞名字列表
        self.mSceneExtNameList.Add("unity");
        
        self.mPersistentAssetBundlesPath = "E:/Self/Self/unity/unitygame/Client_Start/OutPut/AssetBundles/Windows";      # 最终的 AssetBudnles 输出的目录
        
        self.mIgnoreExtList = MList();
        self.mIgnoreExtList.Add("meta");
        self.mIgnoreExtList.Add("manifest");



    def isMakeResources(self):
        return self.mMakeVerTypeList.IndexOf(eMakeType.eResources) != -1;


    def isMakeStreamingAssets(self):
        return self.mMakeVerTypeList.IndexOf(eMakeType.eStreamingAssets) != -1;
    
    
    def isMakePersistent(self):
        return self.mMakeVerTypeList.IndexOf(eMakeType.ePersistent) != -1;


    def getAssetPath(self):
        return UtilPath.combine(self.mProjRootPath, self.mAssetName);
    
    
    def getResourcesPath(self):
        return UtilPath.combine(self.mProjRootPath, self.mAssetName, self.mResourcesName);


    def getStreamingAssetsPath(self):
        return UtilPath.combine(self.mProjRootPath, self.mAssetName, self.mStreamingAssetsName);
    
    def getPersistentPath(self):
        return self.mPersistentAssetBundlesPath;
    
    
    def getScenesPath(self):
        return UtilPath.combine(self.mProjRootPath, self.mAssetName, self.mScenesName);


    def getResourcesVerFileFullOutPath(self):
        return UtilPath.combine(self.mProjRootPath, self.mAssetName, self.mResourcesName, self.mResourcesVerFileName);
    

    def getStreamingAssetsVerFileFullOutPath(self):
        return UtilPath.combine(self.mProjRootPath, self.mAssetName, self.mStreamingAssetsName, self.mStreamingAssetsVerFileName);
    
    
    def getPersistentVerFileFullOutPath(self):
        return UtilPath.combine(self.mPersistentAssetBundlesPath, self.mPersistentVerFileName);


    def getOutPutRootPath(self):
        return self.mOutPutPath;
    
    
    def getAssetBundlesPath(self, buildTarget):
        pass;


    #def getAssetBundlesManifestPath(self, buildTarget):
    def getAssetBundlesManifestPath(self):
        return "E:/Self/Self/unity/unitygame/Client_Start/OutPut/BuildOut/AssetBundlesList.txt";

    
    def getBuildOutPath(self):
        pass


    def isPrefabRes(self, extName):
        return self.mPrefabResExtNameList.IndexOf(extName) != -1;


    def isSceneRes(self, extName):
        return self.mSceneExtNameList.IndexOf(extName) != -1;    
    
    
    def isPrefabOrSceneRes(self, extName):
        return self.isPrefabRes(extName) or self.isSceneRes(extName);
    
    
    
    def isAssetBundlesRes(self, extName):
        return self.mAssetBundlesExtNameList.IndexOf(extName) != -1;


    def isIgnoreFileByExt(self, extName):
        return self.mIgnoreExtList.IndexOf(extName) != -1;


    def getResourcesVerFileName(self):
        return self.mResourcesVerFileName;


    def getStreamingAssetsVerFileName(self):
        return self.mStreamingAssetsVerFileName;
    

    def getPersistentVerFileName(self):
        return self.mPersistentVerFileName;
    
    
    def getMinVerFileName(self):
        return self.mMinVerFileName;
    
    
    def isResourcesVerFileName(self, fileName):
        return self.mResourcesVerFileName == fileName;
    
    
    def isPersistentVerFileName(self, fileName):
        return self.mPersistentVerFileName == fileName;
    

