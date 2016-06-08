# -*- coding: utf-8 -*-

from Libs.Core.GObject import GObject
from Libs.DataStruct.MList import MList
from Libs.FileSystem.MDataStream import MDataStream
from Libs.FileSystem.MFileMode import MFileMode
from Libs.Tools.UtilStr import UtilStr
from Libs.Tools.UtilPath import UtilPath
from Libs.DataStruct.MDictionary import MDictionary
from ToolSet.FileDirDiff.VerProcessSys import VerProcessSys
from Libs.Tools.UtilApi import UtilApi

'''
@brief 打包的进入 AssetBundles 中的资源列表
'''
class AssetItem(GObject):
    
    def __init__(self):
        super(AssetItemList, self).__init__();
        
        self.mTypeId = "AssetItem";
        
        self.mABPath = "";      # 资源在 AB 包中的资源的名字，可能前面加上 "Assets/Resources" 前缀，在 manifest 中间中的名字是大小写区分的，但是从 AB 包中使用接口 Api获取出来后，就是小写了，并且自己使用小写也是可以获取的，区分大小写不知道行不行
        self.mPrefabPath = "";  # 资源在 Resources 目录中的名字，是区分大小写的


'''
@brief 依赖的资源数据
'''
class DepItem(GObject):
    
    def __init__(self):
        super(DepItemList, self).__init__();
        
        self.mTypeId = "DepItem";
        
        self.mABName = "";      # 依赖的 AB 包的名字，自己在 Unity 编辑器中设置的
        
        
    def addDep(self, depPath):
        self.mDepList.Add(depPath);


'''
@brief 打包的进入 AssetBundles 中的资源列表
'''
class AssetItemList(GObject):
    
    def __init__(self):
        super(AssetItemList, self).__init__();
        
        self.mTypeId = "AssetItemList";
        
        self.mAssetList = MList();


    def addAsset(self, assetPath):
        assetItem = AssetItem;
        assetItem.mABPath = assetPath;
        
        self.mAssetList.Add(assetItem);
        
        
    def setResourcesName(self, abPath, resourcePath):
        for assetItem in self.mAssetList.getList():
            if(assetItem.mABPath == abPath):
                assetItem.mPrefabPath = resourcePath;
                break;


'''
@brief 依赖的资源数据
'''
class DepItemList(GObject):
    
    def __init__(self):
        super(DepItemList, self).__init__();
        
        self.mTypeId = "DepItemList";
        
        self.mDepList = MList();
        
        
    def addDep(self, depPath):
        depItem = DepItem();
        depItem.mABName = depPath;
        
        self.mDepList.Add(depItem);
        
        
'''
@brief 一个 AssetBundles AB 包
'''
class AssetBundlesItem(GObject):
    
    def __init__(self):
        super(AssetBundlesItem, self).__init__();
        
        self.mTypeId = "AssetBundlesItem";
        
        self.mAssetItemList = AssetItemList();
        self.mDepItemList = DepItemList();


    def addAsset(self, assetPath):
        self.mAssetItemList.addAsset(assetPath);
        
        
    def setResourcesName(self, abPath, resourcePath):
        self.mAssetItemList.setResourcesName(abPath, resourcePath);


    def addDep(self, depPath):
        self.mDepItemList.addDep(depPath);
        

'''
@brief 对应的一个生成的 Manifest 文件信息
'''
class AssetBundlesManifest(GObject):
    def __init__(self):
        super(AssetBundlesManifest, self).__init__();
        
        self.mTypeId = "AssetBundlesManifest";
        
        self.mABPathToItemDic = MDictionary();      # AB 资源目录到 Manifest 映射
        self.mABResPathToItemDic = MDictionary();   # AB 中包含的资源目录到 Manifest 映射，这个资源的名字是比 Resources 目录下的资源多了 "Assets/Resources"，并且是小写
        
        self.mResourcesPath = "";
        
        
    def getAssetBundlesItem(self, itemPath):
        return self.mAssetDic.value(itemPath);
    

    def readManifest(self):
        manifestPath = VerProcessSys.instance().mParams.mVerConfig.getAssetBundlesManifestPath();
        
        dataStream = MDataStream(manifestPath, MFileMode.ReadTxt);
        lines = dataStream.read();
        splitLineList = UtilStr.split(lines, UtilPath.CRLF);
        for oneLine in splitLineList:
            if(UtilStr.len(oneLine) > 0):
                # = Split
                equalSplitList = UtilStr.split(oneLine, UtilPath.SPLIT);
                assetBundlesItem = AssetBundlesItem();
                self.mABPathToItemDic.Add(equalSplitList[0], assetBundlesItem);
                # , Split
                commoList = UtilStr.split(equalSplitList[1], ",");
                for commoItem in commoList:
                    self.mABResPathToItemDic.Add(commoItem, assetBundlesItem);                    
                    assetBundlesItem.addAsset(commoItem);
                
                if(MList.len(equalSplitList) > 2):
                    commoList = UtilStr.split(equalSplitList[2], ",");
                    for commoItem in commoList:
                        assetBundlesItem.addDep(commoItem);


    # 查找 Resources 目录下的对应的名字
    def findResourcsName(self):
        self.mResourcesPath = VerProcessSys.instance().mParams.mVerConfig.getResourcesPath();

        UtilPath.traverseDirectory(
                           self.mResourcesPath, 
                           None, 
                           None, 
                           None,  
                           self, 
                           self.traverseResourcesPathHandle, 
                           True
                           );

        
    def traverseResourcesPathHandle(self, srcFullPath, srcCurName, destFullPath):
        extName = UtilPath.getFileExt(srcFullPath);
        # 如果是可以打成 AssetBundles 的资源
        if(VerProcessSys.instance().mParams.mVerConfig.isPrefabRes(extName)):
            resourcesPath = UtilStr.replace(srcFullPath, self.mResourcesPath, "");
            lowerResourcesPath = UtilApi.convResourcesPathToAssetBundlesPath(resourcesPath);
            lowerResourcesPath = UtilStr.lower(resourcesPath);
            assetBundlesItem = self.mABResPathToItemDic.value(lowerResourcesPath);
            if(assetBundlesItem != None):
                assetBundlesItem.setResourcesName(lowerResourcesPath, resourcesPath);

