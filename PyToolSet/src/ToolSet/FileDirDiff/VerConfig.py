# -*- coding: utf-8 -*-

from Libs.Core.GObject import GObject
from Libs.Tools.UtilPath import UtilPath
from Libs.DataStruct.MList import MList
from Libs.FileSystem.MDataStream import MDataStream
from Libs.FileSystem.MFileMode import MFileMode
from Libs.Tools.UtilStr import UtilStr

'''
@brief 生成版本的类型
'''
class eMakeType(GObject):
    eResources = 0;
    eStreamingAssets = 1;
    ePersistent = 2;
    eMini = 3;
    

'''
@brief: Config
'''

class VerConfig(GObject):
    
    def __init__(self):
        super(VerConfig, self).__init__();
        
        self.mTypeId = "Config";
        
        self.mProjRootPath = "E:/Self/Self/unity/unitygame/Client_Start";    # 工程根目录
        self.mOutPutPath = "E:/Self/Self/unity/unitygame/Client_Start/OutPut";         # 输出目录
        #self.mProjRootPath = "/Users/zt-2202351/File/Client_Start";    # 工程根目录
        #self.mOutPutPath = "/Users/zt-2202351/File/Client_Start/OutPut";         # 输出目录
        self.mDestPath = "";        # 最终目录
        
        self.mAssetName = "Assets";       # Assets 目录名字
        self.mResourcesName = "Resources";  # Resources 目录名字
        self.mStreamingAssetsName = "StreamingAssets";  # StreamingAssets 目录名字
        self.mScenesName = "Scenes";
        
        self.mMakeVerTypeList = MList();       # 生成版本的类型
        self.mMakeVerTypeList.add(eMakeType.eResources);
        self.mMakeVerTypeList.add(eMakeType.eStreamingAssets);
        self.mMakeVerTypeList.add(eMakeType.ePersistent);
        self.mMakeVerTypeList.add(eMakeType.eMini);
        
        self.mResourcesVerFileName = "Version_R.txt";       # Resources 版本文件名字
        self.mStreamingAssetsVerFileName = "Version_S.txt"; # StreamingAssets 版本文件名字
        self.mPersistentVerFileName = "Version_P.txt";      # Persistent 版本文件名字
        self.mMinVerFileName = "Version_Mini.txt";          # 就是版本的版本
        self.mManifestConfigFileName = "AssetBundlesList.txt";
        
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

        self.mTargetPlatformType = "Windows";
        self.mTargetFolderName = "Windows";
        self.mPersistentAssetBundlesPath = "E:/Self/Self/unity/unitygame/Client_Start/OutPut/AssetBundles/Windows";      # 最终的 AssetBudnles 输出的目录
        #self.mPersistentAssetBundlesPath = "/Users/zt-2202351/File/Client_Start/OutPut/AssetBundles/Android";      # 最终的 AssetBudnles 输出的目录
        #self.mPersistentAssetBundlesPath = "/Users/zt-2202351/File/Client_Start/OutPut/AssetBundles/OSX";      # 最终的 AssetBudnles 输出的目录
        #self.mPersistentAssetBundlesPath = "/Users/zt-2202351/File/Client_Start/OutPut/AssetBundles/iOS";      # 最终的 AssetBudnles 输出的目录
        
        
        self.mPersistentAssetBundlesPath = UtilPath.combine(
                                                            self.mOutPutPath, 
                                                            "AssetBundles", 
                                                            self.mTargetFolderName
                                                            );
        
        self.mIgnoreExtList = MList();
        self.mIgnoreExtList.Add("meta");
        self.mIgnoreExtList.Add("manifest");
        
        self.readConfig();



    def isMakeResources(self):
        return self.mMakeVerTypeList.IndexOf(eMakeType.eResources) != -1;


    def isMakeStreamingAssets(self):
        return self.mMakeVerTypeList.IndexOf(eMakeType.eStreamingAssets) != -1;
    
    
    def isMakePersistent(self):
        return self.mMakeVerTypeList.IndexOf(eMakeType.ePersistent) != -1;
    
    
    def isMakeMini(self):
        return self.mMakeVerTypeList.IndexOf(eMakeType.eMini) != -1;


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
        # StreamingAssets 目录下的 "Version_S.txt" 不放在 StreamingAssets 目录下了，因为我们会同步加载 "Version_S.txt" 这个配置，但是在 Android 下 StreamingAssets 目录只能使用 WWW 异步加载非 AssetBundles 资源 
        #return UtilPath.combine(self.mProjRootPath, self.mAssetName, self.mStreamingAssetsName, self.mStreamingAssetsVerFileName);
        return UtilPath.combine(self.mProjRootPath, self.mAssetName, self.mResourcesName, self.mStreamingAssetsVerFileName);
    
    
    def getPersistentVerFileFullOutPath(self):
        return UtilPath.combine(self.mPersistentAssetBundlesPath, self.mPersistentVerFileName);
    
    
    def getMiniVerFileFullOutPath(self):
        return UtilPath.combine(self.mPersistentAssetBundlesPath, self.mMinVerFileName);

    def getOutPutRootPath(self):
        return self.mOutPutPath;
    
    
    def getAssetBundlesPath(self, buildTarget):
        pass;


    #def getAssetBundlesManifestPath(self, buildTarget):
    def getAssetBundlesManifestPath(self):
        #return "E:/Self/Self/unity/unitygame/Client_Start/OutPut/BuildOut/AssetBundlesList.txt";
        #return "/Users/zt-2202351/File/Client_Start/OutPut/BuildOut/AssetBundlesList.txt";
        return UtilPath.combine(self.mOutPutPath, "BuildOut", self.mManifestConfigFileName);

    
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
    

    def getLuaSrcPath(self):
        return UtilPath.combine(self.mProjRootPath, self.mAssetName, "uLua/Lua");
    
    
    def getLuaDestPath(self):
        return UtilPath.combine(self.mProjRootPath, self.mAssetName, self.mResourcesName, "Lua");
    
    
    def readConfig(self):
        path = UtilPath.combine(UtilPath.getcwd(), "Config/Config.txt"),
        dataStream = MDataStream(path, MFileMode.ReadTxt);
        content = dataStream.read();
        
        lineArr = UtilStr.split(content, UtilPath.CR_LF);
        idx = 0;
        arrLen = MList.len(lineArr);
        while(idx < arrLen):
            if(UtilStr.len(lineArr[idx]) > 0 and lineArr[idx][0] != UtilPath.COMMENT):
                equalSplitArr = UtilStr.split(lineArr[idx], UtilPath.SPLIT);
                if(equalSplitArr[0] == "mProjRootPath"):
                    self.mProjRootPath = equalSplitArr[0];
                elif(equalSplitArr[0] == "mOutPutPath"):
                    self.mOutPutPath = equalSplitArr[0];
                elif(equalSplitArr[0] == "mTargetPlatformType"):
                    self.mTargetPlatformType = equalSplitArr[0];

        self.postInit();

        
    def postInit(self):
        self.mTargetFolderName = self.mTargetPlatformType;

        self.mPersistentAssetBundlesPath = UtilPath.combine(
                                                            self.mOutPutPath, 
                                                            "AssetBundles", 
                                                            self.mTargetFolderName
                                                            );        
        
    
    

