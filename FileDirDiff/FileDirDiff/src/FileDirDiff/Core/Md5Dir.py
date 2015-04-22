#-*- encoding=utf-8 -*-

'''
@brief: calc dir md5
'''
import os

from FileDirDiff.Core import Md5Checker
from FileDirDiff.Core.FileVersionInfo import FileVersionInfo
from FileDirDiff.Core.FileVersionInfo import BuildFileVersion
from FileDirDiff.Core import GlobalData
from FileDirDiff.Core.EConst import EConst

class Md5DirOperate(object):
    def __init__(self):
        self.m_dirMd5Lst = [Md5Dir(), Md5Dir()] # 两个版本的目录比较, [0] 是之前的版本 [1] 是现在的版本
        self.m_buildver = BuildFileVersion()
        self.m_buildver.readPreVersionFile()
        
        # 读取原始的目录配置文件
        bVerSrcExist = False
        if os.path.exists(GlobalData.g_pAppSys.m_config.preVerDirPath()):
            if os.path.isfile(GlobalData.g_pAppSys.m_config.preVerDirPath()):
                bVerSrcExist = True
        
        if bVerSrcExist:
            self.m_dirMd5Lst[EConst.ePreMd5Dir].initFromFile(GlobalData.g_pAppSys.m_config.preVerDirPath())
            
        self.m_dirMd5Lst[EConst.eCurMd5Dir].initFormDir(GlobalData.g_pAppSys.m_config.uiSrcRootPath())
        self.m_dirMd5Lst[EConst.eCurMd5Dir].initFormDir(GlobalData.g_pAppSys.m_config.externSrcRootPath())
        self.m_dirMd5Lst[EConst.eCurMd5Dir].initFormDir(GlobalData.g_pAppSys.m_config.coreSrcRootPath())
        self.m_dirMd5Lst[EConst.eCurMd5Dir].initFormDir(GlobalData.g_pAppSys.m_config.moduleSrcRootPath())
    
    # filelst: 文件列表    rootdirname: 根目录名字, filelst 中的每一项的形式如下 UIArenaInfomation.swf,subdir 形式 asset/ui/UIArenaBetialRank.swf
    def calcUIFileDirMd5(self, filelst, rootdirname):
        retlst = []     # 返回的 list
        curfileinfo = None
        #buildver = BuildFileVersion()
        #buildver.readPreVersionFile()
        for filenameext in filelst:
            dotidx = filenameext.find('.')
            filenamenoext = filenameext[0:dotidx]
            subdir = os.path.join(rootdirname, filenameext)
            subdir = subdir.replace('\\', '/')

            curfileinfo = FileVersionInfo()
            curfileinfo.m_filename = subdir
            retlst.append(curfileinfo)
            
            key = os.path.join("ui", filenamenoext)
            key = key.replace('\\', '/')
            if self.isDirMd5Change(key): # 如果目录 md5 改变,就求取新的 md5
                curfileinfo.m_version = Md5Checker.md5_for_file(subdir)
            else:           # 直接从上一次的 md5 获取
                binidx = subdir.find('bin')
                subdir = subdir[binidx + 4:]
                curfileinfo.m_version = self.m_buildver.getFileVersion(subdir)
                
        return retlst
    
    def calcModuleFileDirMd5(self, filelst, rootdirname):
        retlst = []     # 返回的 list
        curfileinfo = None
        #buildver = BuildFileVersion()
        #buildver.readPreVersionFile()
        for filenameext in filelst:
            dotidx = filenameext.find('.')
            filenamenoext = filenameext[0:dotidx]
            subdir = os.path.join(rootdirname, filenameext)
            subdir = subdir.replace('\\', '/')

            curfileinfo = FileVersionInfo()
            curfileinfo.m_filename = subdir
            retlst.append(curfileinfo)
            
            key = os.path.join("module", filenamenoext)
            key = key.replace('\\', '/')
            # 如果是 module/ModuleApp.swf ,这个需要比较库的 md5 
            if "module/ModuleApp".lower() == key.lower():
                if self.isDirMd5Change(key) or self.isDirMd5Change("core/src") or self.isDirMd5Change("module/modulecommon") or self.isDirMd5Change("extern/GTween_V2_01") or self.isDirMd5Change("extern/richtextfield"):
                    curfileinfo.m_version = Md5Checker.md5_for_file(subdir)
                else:           # 直接从上一次的 md5 获取
                    binidx = subdir.find('bin')
                    subdir = subdir[binidx + 4:]
                    curfileinfo.m_version = self.m_buildver.getFileVersion(subdir)
            else:
                if self.isDirMd5Change(key): # 如果目录 md5 改变,就求取新的 md5
                    curfileinfo.m_version = Md5Checker.md5_for_file(subdir)
                else:           # 直接从上一次的 md5 获取
                    binidx = subdir.find('bin')
                    subdir = subdir[binidx + 4:]
                    curfileinfo.m_version = self.m_buildver.getFileVersion(subdir)
                
        return retlst 

    def isDirMd5Change(self, dirname):
        #lst = self.m_dirMd5Lst[EConst.eCurMd5Dir].m_dirDic.keys()
        #if dirname not in lst:    # 如果当前的源代码目录都没有,肯定是没有改变
        #    return False
        #lst = self.m_dirMd5Lst[EConst.ePreMd5Dir].m_dirDic.keys()
        #if dirname in lst:
        #    preDirMd = self.m_dirMd5Lst[EConst.ePreMd5Dir].m_dirDic[dirname]
        #    if self.m_dirMd5Lst[EConst.eCurMd5Dir].m_dirDic[dirname]:
        #        curDirMd = self.m_dirMd5Lst[EConst.eCurMd5Dir].m_dirDic[dirname]
        #        preDirMd.isNotEqualDir(curDirMd) 

        #return True;
    
        dirname = self.keyInDic(EConst.eCurMd5Dir, dirname)
        if not dirname:    # 如果当前的源代码目录都没有,肯定是没有改变
            return False
        
        dirname = self.keyInDic(EConst.ePreMd5Dir, dirname)
        if dirname:
            preDirMd = self.m_dirMd5Lst[EConst.ePreMd5Dir].m_dirDic[dirname]
            curDirMd = self.m_dirMd5Lst[EConst.eCurMd5Dir].m_dirDic[dirname]
            return preDirMd.isNotEqualDir(curDirMd)

        return True;

    def savaDirMd(self):
        self.m_dirMd5Lst[EConst.eCurMd5Dir].writeToFile(GlobalData.g_pAppSys.m_config.curVerDirPath())
    
    # 例如 ui/UIEquipSys.swf 可能目录是 ui/uiEquipSys ,返回正确的键值
    def keyInDic(self, idx, cmpstr):
        for (key, _) in self.m_dirMd5Lst[idx].m_dirDic.items():
            if key.lower() == cmpstr.lower():
                return key
        
        return None

class Md5Dir(object):
    def __init__(self):
        self.m_dirDic = {}      # 目录字典

    def isDirExist(self, dirname):
        if self.m_dirDic[dirname]:
            return True
        
        return False
    
    # init file
    def initFromFile(self, dirname):
        # format
        fHandle = open(dirname, 'r', encoding = 'utf8')
        cont = fHandle.read()
        oneline = cont.split('\n')
        curdirinfo = None
        curfileinfo = None
        strlst = None
        idx = 0
        while idx < len(oneline):
            if len(oneline[idx]):
                # 如果有 = 号，就是文件的 md5， 如果没有 = 号就是目录名字
                if "=" in oneline[idx]:  # 文件的  md5 码
                    strlst = oneline[idx].split('=')
                    curfileinfo = FileInfo()
                    curfileinfo.m_file = strlst[0]
                    curfileinfo.m_md = strlst[1]
                    if curdirinfo:
                        curdirinfo.m_fileDic[curfileinfo.m_file] = curfileinfo
                else:   # 这一行就是一个目录
                    if curdirinfo:
                        curdirinfo.calcFileCnt()
                    curdirinfo = DirInfo()
                    self.m_dirDic[oneline[idx]] = curdirinfo
                
            idx += 1
         
        fHandle.close()

    # init dir dirname = E:\e\work\client-new-1224\client\ui
    def initFormDir(self, dirname):
        filemd5 = 0
        curdirdepth = dirname.count("/") + dirname.count("\\") 
        curdirinfo = None
        curfileinfo = None
        substr = 'client'
        subroot = None
        substridx = 0
        #for root, dirs, files in os.walk(dirname):
        for root, _, files in os.walk(dirname):
            if root.count("/") + root.count("\\") == curdirdepth:   # 如果是当前目录正式根目录,文件也不检查了,都是工程文件
                continue
            if root.count("/") + root.count("\\") == curdirdepth + 1:   # 如果目录是第二级子目录就创建数据
                if root[root.rfind('/') + 1:] == "obj":      # 如果是 obj 文件夹就继续
                    continue
                if root[root.rfind('\\') + 1:] == "obj":      # 如果是 obj 文件夹就继续
                    continue
                # .settings 这个目录也要去掉
                if '.settings' in root:
                    continue
                if root not in self.m_dirDic.keys():
                    if curdirinfo:      # 计算这个目录总共的文件的数量
                        curdirinfo.calcFileCnt()
                    curdirinfo = DirInfo()
                    substridx = root.rfind(substr)
                    subroot = root[substridx + 1 + len(substr):]
                    subroot = subroot.replace('\\', '/')
                    self.m_dirDic[subroot] = curdirinfo
            
            # .settings 这个目录也要去掉
            if '.settings' in root:
                continue
       
            for fname in files:
                if fname != ".actionScriptProperties" and fname != ".project":
                    fpath = os.path.join(root, fname)
                    if not os.path.isdir(fpath):
                        filemd5 = Md5Checker.md5_for_file(fpath)
                        curfileinfo = FileInfo()
                        substridx = fpath.rfind(substr)
                        subroot = fpath[(substridx + 1 + len(substr)):]
                        subroot = subroot.replace('\\', '/')
                        curfileinfo.m_file = subroot
                        curfileinfo.m_md = filemd5
                        curdirinfo.m_fileDic[curfileinfo.m_file] = curfileinfo
        
        if curdirinfo:      # 计算这个目录总共的文件的数量
            curdirinfo.calcFileCnt()
                        
    def writeToFile(self, filename):
        fHandle = open(filename, 'w', encoding = 'utf8')
        for (k1, v1) in self.m_dirDic.items():
            fHandle.write(k1 + "\n")
            for (k2, v2) in v1.m_fileDic.items():
                fHandle.write(k2 + "=" + v2.m_md + "\n")
                
        fHandle.close()

# brief dir info
class DirInfo(object):
    # brief constructor 
    def __init__(self):
        self.m_dir = ""         # 目录名字
        self.m_fileCnt = 0;     # 文件数量
        self.m_fileDic = {};    # 文件字典

    def isFileExist(self, filename):
        if self.m_fileDic[filename]:
            return True
        
        return False
    
    def calcFileCnt(self):
        self.m_fileCnt = len(self.m_fileDic.keys())
    
    # True 是目录md 不相同 Flase 是相同
    def isNotEqualDir(self, rh):
        if self.m_fileCnt == rh.m_fileCnt:
            for (key1, value1) in self.m_fileDic.items():
                if key1 in rh.m_fileDic.keys():
                    if value1.m_md != rh.m_fileDic[key1].m_md:
                        return True
                else:
                    return True
        else:
            return True
                        
        return False
        
# brief file info  
class FileInfo(object):
    def __init__(self):
        self.m_file = ""        # file name
        self.m_md = ""          # file md5



