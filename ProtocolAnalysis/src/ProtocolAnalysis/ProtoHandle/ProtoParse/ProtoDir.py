# -*- coding: utf-8 -*-


from ProtocolAnalysis.ProtoHandle.ProtoParse.ProtoFileBase import ProtoFileBase, eFileType
from ProtocolAnalysis.Core.AppSysBase import AppSysBase
from ProtocolAnalysis.ProtoHandle.ProtoParse.ProtoFile import ProtoFile


class ProtoDir(ProtoFileBase):
    '''
    classdocs
    '''


    def __init__(self, fullPath):
        '''
        Constructor
        '''
        super(ProtoDir, self).__init__(eFileType.eDir, fullPath)
        self.m_filesList = []
        
        self.convDir2Files()


    def parse(self):
        for file in self.m_filesList:
            file.parse();


    # 转变目录到文件列表
    def convDir2Files(self):
        AppSysBase.instance().getClsUtilFile().getEventDispatch().addEventHandle(self.findFileHandle, [self])
        
        AppSysBase.instance().getClsUtilFile().traversalAllDirs(self.m_fullPath)
        
        AppSysBase.instance().getClsUtilFile().getEventDispatch().removeEventHandle(self.findFileHandle)
    
    # 查找文件回调函数
    @staticmethod
    def findFileHandle(paramList, disp):
        file = ProtoFile(AppSysBase.instance().getClsUtilFile().getFileFullPath())
        paramList[0].m_filesList.append(file)
        
        
        
        