#-*- encoding=utf-8 -*-

'''
@brief 文件版本信息
'''

import os
from xml.dom.minidom import Document

from FileDirDiff.Core.AppSys import AppSys
from FileDirDiff.Core.Utils import ParamInfo
from FileDirDiff.Core.Utils import CmdLine

'''
@brief 文件版本信息
'''
class FileVersionInfo(object):
    def __init__(self, filename = '', version = 0):
        self.m_filename = filename
        self.m_version = version
        
    def __str__(self):
        return self.m_filename + '=' + str(self.m_version)
        
class FileMdInfo(object):
    def __init__(self, filename = '', md = ''):
        self.m_filename = filename
        self.m_md = md
        
'''
@brief 生成文件版本信息
'''
class BuildFileVersion(object):
    def __init__(self):
        self.m_srcVerFileName = AppSys.instance().m_config.preVerFilePath()  # 原始version版本信息文件,这个本来打算根据md来计算一个从0开始不断增大的一个整数
        self.m_destVerFileName = AppSys.instance().m_config.curVerFilePath()  # 目标version版本信息文件
        
        self.m_srcMdFileName = AppSys.instance().m_config.preCKFilePath()  # 原始md版本信息文件
        self.m_destMdFileName = AppSys.instance().m_config.curCKFilePath()  # 目标md版本信息文件
        
        self.m_srcVerlist = []
        self.m_srcVermap = {}
        self.m_destVerlist = []
        
        self.m_srcMdlist = []
        self.m_srcMdMap = {}
        self.m_destMdlist = []

    # 生成版本文件
    def buildVersionFile(self):
        AppSys.instance().m_logSys.info('start build version file')
        
        bVerSrcExist = False
        if os.path.exists(self.m_srcVerFileName):
            if os.path.isfile(self.m_srcVerFileName):
                bVerSrcExist = True
        
        bMdSrcExist = False
        if os.path.exists(self.m_srcMdFileName):
            if os.path.isfile(self.m_srcMdFileName):
                bMdSrcExist = True
        
        if bVerSrcExist:
            fHandleVerSrc = open(self.m_srcVerFileName, 'r', encoding='utf8')
            cursplit = None
            for curline in fHandleVerSrc:
                if len(curline):
                    cursplit = curline.split('=')
                    verinfo = FileVersionInfo()
                    verinfo.m_filename = cursplit[0]
                    verinfo.m_version = int(cursplit[1])
                    self.m_srcVerlist.append(verinfo)
                    self.m_srcVermap[verinfo.m_filename] = verinfo
        
        if bMdSrcExist:
            fHandleMdSrc = open(self.m_srcMdFileName, 'r', encoding='utf8')
            cursplit = None
            for curline in fHandleMdSrc:
                if len(curline):
                    cursplit = curline.split('=')
                    mdinfo = FileMdInfo()
                    mdinfo.m_filename = cursplit[0]
                    mdinfo.m_md = cursplit[1]
                    self.m_srcMdlist.append(mdinfo)
                    self.m_srcMdMap[mdinfo.m_filename] = mdinfo

        fHandleMdDest = open(self.m_destMdFileName, 'r', encoding='utf8')
        cursplit = None
        for curline in fHandleMdDest:
            if len(curline):
                cursplit = curline.split('=')
                mdinfo = FileMdInfo()
                mdinfo.m_filename = cursplit[0]
                mdinfo.m_md = cursplit[1]
                self.m_destMdlist.append(mdinfo)
        
        if not bVerSrcExist:
            for mditem in self.m_destMdlist:
                verinfo = FileVersionInfo()
                verinfo.m_filename = mditem.m_filename
                verinfo.m_version = 0
                self.m_destVerlist.append(verinfo)
        else:
            for mditem in self.m_destMdlist:
                verinfo = FileVersionInfo()
                verinfo.m_filename = mditem.m_filename
                verinfo.m_version = 0
                
                if mditem.m_filename in self.m_srcMdMap.keys():
                    if mditem.m_md == self.m_srcMdMap[mditem.m_filename].m_md:
                        verinfo.m_version = self.m_srcVermap[mditem.m_filename].m_version
                    else:
                        verinfo.m_version = self.m_srcVermap[mditem.m_filename].m_version + 1

                self.m_destVerlist.append(verinfo) 
        
        # 输出字符串
        fHandleVerDest = open(self.m_destVerFileName, 'w', encoding='utf8')
        for veritem in self.m_destVerlist:
            #if AppSys.AppSys.instance().curverFileCount > 0:
            if AppSys.instance().get_curverFileCount > 0:
                fHandleVerDest.write('\n')
            
            #AppSys.AppSys.instance().curverFileCount += 1
            AppSys.instance().add_curverFileCount(1)
            fHandleVerDest.write(veritem.m_filename + '=' + str(veritem.m_version))
            
        AppSys.instance().m_logSys.info('end build version file')

        # 生成版本文件
    def readPreVersionFile(self):
        AppSys.instance().m_logSys.info('start read preversion')
        
        preMdFileName = AppSys.instance().m_config.preCKFilePath()
        bMdSrcExist = False
        if os.path.exists(preMdFileName):
            if os.path.isfile(preMdFileName):
                bMdSrcExist = True
        
        if bMdSrcExist:
            fHandleMdSrc = open(preMdFileName, 'r', encoding='utf8')
            cursplit = None
            for curline in fHandleMdSrc:
                if len(curline):
                    cursplit = curline.split('=')
                    if len(cursplit) == 2:  # 如果只有一个 "\n" 长度也会大于 0
                        mdinfo = FileMdInfo()
                        mdinfo.m_filename = cursplit[0]
                        mdinfo.m_md = cursplit[1]
                        # 去掉最后的 "\n"
                        if mdinfo.m_md[len(mdinfo.m_md) - 1:] == "\n":
                            mdinfo.m_md = mdinfo.m_md[0:-1]
                        self.m_srcMdlist.append(mdinfo)
                        self.m_srcMdMap[mdinfo.m_filename] = mdinfo
            
        AppSys.instance().m_logSys.info('end read preversion')

    def getFileVersion(self, filepath):
        if filepath in self.m_srcMdMap.keys():
            return self.m_srcMdMap[filepath].m_md
        
        return "0"

    # 输出整个版本    
    def outVerSwf(self):
        filename = AppSys.instance().m_config.preckallverfilename
        tmpdir = os.path.join(AppSys.instance().m_config.destrootpath, AppSys.instance().m_config.tmpDir)
        
        doc = Document()
        root = doc.createElement('lib')
        root.setAttribute('allowDomain', '*')
        
        byteArray = doc.createElement('bytearray')
        byteArray.setAttribute('file', AppSys.instance().m_config.curCKFilePath())
        byteArray.setAttribute('class', AppSys.instance().m_config.allverclass)
        
        doc.appendChild(root)
        root.appendChild(byteArray)
       
        '''生成的xml写入文件'''
        xmlFullName = '%s\\%s' % (tmpdir, filename)
        fHandle = open('%s.xml' % xmlFullName, 'w')
        fHandle.write(str(doc.toprettyxml(indent = "  ", encoding="UTF-8"), encoding='utf-8'))
        fHandle.close()

        swfName = '%s.swf' % (filename)
        '''根据生成的xml打包as3用的xml成最终的swf包'''
        ParamInfo.pInstance.m_swiftFullXmlFile = xmlFullName
        ParamInfo.pInstance.m_swiftFullSwcFile = xmlFullName
        CmdLine.exec7z()

        open('%s\\%s' % (AppSys.instance().m_config.destrootpath + '/' + AppSys.instance().m_config.outDir, swfName), 'wb').write(open('%s\\library.swf' % (AppSys.instance().m_config.destrootpath + '/' + AppSys.instance().m_config.tmpDir), 'rb').read())
        os.remove('%s\\library.swf' % (AppSys.instance().m_config.destrootpath + '/' + AppSys.instance().m_config.tmpDir))
        os.remove('%s.swc' % xmlFullName)
        AppSys.instance().m_logSys.info(AppSys.instance().m_config.preckallverfilename + '包 %s 完成' % swfName)
    
    # 输出 app 模块的    
    def outVerAppSwf(self):
        filename = AppSys.instance().m_config.preckappverfilename
        tmpdir = os.path.join(AppSys.instance().m_config.destrootpath, AppSys.instance().m_config.tmpDir)
        
        doc = Document()
        root = doc.createElement('lib')
        root.setAttribute('allowDomain', '*')
        
        byteArray = doc.createElement('bytearray')
        byteArray.setAttribute('file', AppSys.instance().m_config.appCKFilePath())
        byteArray.setAttribute('class', 'art.ver.app')
        
        doc.appendChild(root)
        root.appendChild(byteArray)
       
        '''生成的xml写入文件'''
        xmlFullName = '%s\\%s' % (tmpdir, filename)
        fHandle = open('%s.xml' % xmlFullName, 'w')
        fHandle.write(str(doc.toprettyxml(indent = "  ", encoding="UTF-8"), encoding='utf-8'))
        fHandle.close()

        swfName = '%s.swf' % (filename)
        '''根据生成的xml打包as3用的xml成最终的swf包'''
        ParamInfo.pInstance.m_swiftFullXmlFile = xmlFullName
        ParamInfo.pInstance.m_swiftFullSwcFile = xmlFullName
        CmdLine.exec7z()

        open('%s\\%s' % (AppSys.instance().m_config.destrootpath + '/' + AppSys.instance().m_config.outDir, swfName), 'wb').write(open('%s\\library.swf' % (AppSys.instance().m_config.destrootpath + '/' + AppSys.instance().m_config.tmpDir), 'rb').read())
        os.remove('%s\\library.swf' % (AppSys.instance().m_config.destrootpath + '/' + AppSys.instance().m_config.tmpDir))
        os.remove('%s.swc' % xmlFullName)
        AppSys.instance().m_logSys.info(AppSys.instance().m_config.preckappverfilename + '包 %s 完成' % swfName)
            
if __name__ == '__main__':
    buildver = BuildFileVersion()
    buildver.buildVersionFile()
