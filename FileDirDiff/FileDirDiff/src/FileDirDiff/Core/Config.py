#-*- encoding=utf-8 -*-

'''
'''

import os
import datetime
#import time

# base config info
class Config(object):
    def __init__(self): 
        # 注意全部需要初始化，否则如果配置文件不用，并且没有判断是否有这个属性，就会出问题
        self.m_srcRootPath = ""       # 资源的根目录,这个是原始资源的 目录
        self.m_destRootPath = ""      # 存放最终文件的目录,这个就是临时目录
        self.m_preVersion = ""        # 之前版本，倒数第二次保存的版本信息
        self.m_curVersion = ""        # 当前版本，最后一次保存的版本信息
        self.m_preCkDirName = "md5dir"      # 目录的 md5 文件前缀
        self.m_preCkFileName = "md5file"       # 校验和文件名字前缀
        self.m_preCkAppName = "md5app"        # app md5原始文件
        self.m_preVerFileName = "version"       # 版本文件名字前缀
        
        # 工具类
        self.m_z7z= 'D:\\ProgramFiles\\7-Zip\\7z.exe'
        
        self.m_tmpDir = 'tmp'         # 临时文件夹目录
        self.m_outDir = 'output'      # 最终输出文件目录
        
        self.m_srcCodeRoot = ''       # 源代码目录,用目录 md5 的时候使用
        self.m_folderMd5Cmp = False   # 是否开启比较文件夹 md5 ，主要是之前老的 asc1.0 编译的时候重新编译一个模块，模块的 md5 就会改变，而新的 asc 2.0 就不会，因此 asc2.0 还是不用比较文件夹目录
        
        self.m_subVersion = '0';        # 子版本号，主要是升级所有的文件的版本，经常有些文件传到服务器上，的那是文件有问题，需要主动升级版本号,'0' 是没有版本号
        
        #读取初始化数据
    def readInit(self, filename):
        fHandle = open(filename, 'r', encoding = 'utf8')
        cont = fHandle.read()
        strlist = cont.split('\n')
        idx = 0
        substrList = []
        listlen = len(strlist)
        while(idx < listlen):
            substrList = strlist[idx].split('=')
            if len(substrList[0]):
                if substrList[0] == 'm_folderMd5Cmp':
                    if int(substrList[1]):
                        self.__dict__[substrList[0]] = True
                    else:
                        self.__dict__[substrList[0]] = False
                else:
                    self.__dict__[substrList[0]] = substrList[1]
            idx += 1


    # 当前 md 校验和文件路径加名字
    def curCKFilePath(self):
        curfilename = "{0}_{1}{2}".format(self.m_preCkFileName, self.m_curVersion, '.txt')
        return os.path.join(self.m_destRootPath, curfilename)

    # 之前 md 校验和文件路径加名字
    def preCKFilePath(self):
        curfilename = "{0}_{1}{2}".format(self.m_preCkFileName, self.m_preVersion, '.txt')
        return os.path.join(self.m_destRootPath, curfilename)

    # 当前版本文件路径加名字
    def curVerFilePath(self):
        curfilename = "{0}_{1}{2}".format(self.m_preVerFileName, self.m_curVersion, '.txt')
        return os.path.join(self.m_destRootPath, curfilename)        

    # 当前版本文件路径加名字
    def preVerFilePath(self):
        curfilename = "{0}_{1}{2}".format(self.m_preVerFileName, self.m_preVersion, '.txt')
        return os.path.join(self.m_destRootPath, curfilename)
    
    # 之前的目录 md 文件
    def preVerDirPath(self):
        curfilename = "{0}_{1}{2}".format(self.m_preCkDirName, self.m_preVersion, '.txt')
        return os.path.join(self.m_destRootPath, curfilename)
    
        # 当前的目录 md 文件
    def curVerDirPath(self):
        curfilename = "{0}_{1}{2}".format(self.m_preCkDirName, self.m_curVersion, '.txt')
        return os.path.join(self.m_destRootPath, curfilename)

    # 当前的目录 md 文件
    def uim_srcRootPath(self):
        return os.path.join(self.m_srcCodeRoot, "ui")
    
    # core code 当前的目录 md 文件
    def corem_srcRootPath(self):
        return os.path.join(self.m_srcCodeRoot, "core")
    
    # module code 当前的目录 md 文件
    def modulem_srcRootPath(self):
        return os.path.join(self.m_srcCodeRoot, "module")
    
        # module code 当前的目录 md 文件
    def externm_srcRootPath(self):
        return os.path.join(self.m_srcCodeRoot, "extern")

    # 返回 app 文件全
    def appCKFilePath(self):
        curfilename = ('{0}_{1}{2}', (self.m_preCkAppName, self.m_curVersion, '.txt'))
        return os.path.join(self.m_destRootPath, curfilename)
    
    # 获取最终生成的 versionall.swf 的 md5 
    def allverFilePath(self):
        return os.path.join(self.m_destRootPath, self.m_outDir, self.m_preCkAllVerFileName + '.swf')    
    
    def isExistPreV(self):
        return self.m_preVersion != '0'
    
    def isExistCurV(self):
        return self.m_curVersion != '0'
    
    # 返回是否比较文件夹目录 md5 ，asc1.0 版本的时候，每一次重新编译，生成的  swf 的 md5 都不一样， asc2.0 重新编译生成的swf 的 md5 一样
    def getm_folderMd5Cmp(self):
        return self.m_folderMd5Cmp
    
    def refreshVersion(self):
        self.m_preVersion = self.m_curVersion
        #self.m_curVersion = str(datetime.date.year) + str(datetime.date.month) + str(datetime.date.day) + str(datetime.time.hour) + str(datetime.time.minute) + str(datetime.time.second)
        #nowdata = datetime.date()
        #nowtime = datetime.time()
        self.m_curVersion = str(datetime.datetime.now())
        dotidx = self.m_curVersion.find('.')
        self.m_curVersion = self.m_curVersion[0:dotidx]
        self.m_curVersion = self.m_curVersion.replace(' ', '-')
        self.m_curVersion = self.m_curVersion.replace(':', '-')

    
    def saveCFG(self):
        filename = "config.txt"
        fHandle = open(filename, 'w', encoding = 'utf8')
        fHandle.write('m_preVersion=' + self.m_preVersion + '\n')
        fHandle.write('m_curVersion=' + self.m_curVersion + '\n')
        fHandle.write('m_preCkDirName=' + self.m_preCkDirName + '\n')
        fHandle.write('m_preCkFileName=' + self.m_preCkFileName + '\n')
        fHandle.write('m_preCkAppName=' + self.m_preCkAppName + '\n')
        fHandle.write('m_preVerFileName=' + self.m_preVerFileName + '\n')

        fHandle.write('m_srcRootPath=' + self.m_srcRootPath + '\n')
        fHandle.write('m_destRootPath=' + self.m_destRootPath + '\n')
        fHandle.write('m_z7z=' + self.m_z7z + '\n')
        fHandle.write('m_srcCodeRoot=' + self.m_srcCodeRoot + '\n')
        if self.m_folderMd5Cmp:
            fHandle.write('m_folderMd5Cmp=' + str(1) + '\n')
        else: 
            fHandle.write('m_folderMd5Cmp=' + str(0) + '\n')
            
        fHandle.write('m_subVersion=' + self.m_subVersion)
        
        fHandle.close()
        
    def hasm_subVersion(self):
        return self.m_subVersion != '0'       # '0' 是没有子版本号

    # 获取版本字符串的编码
    def m_subVersionByte(self):
        #self.m_subVersion.encode("utf-8")
        return bytes(self.m_subVersion, encoding = "utf8")
        

