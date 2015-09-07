# -*- coding: utf-8 -*-


from ProtocolAnalysis.ProtoHandle.ProtoParse.ProtoFile import ProtoFile
from ProtocolAnalysis.ProtoHandle.ProtoParse.ProtoDir import ProtoDir


class ProtoFilesList(object):
    '''
    classdocs
    '''
    ProtoDotExt = ".proto"


    # filesStr 配置文件中的字符串
    def __init__(self, filesStr):
        '''
        Constructor
        '''
        self.m_fileStr = filesStr     # 存放文件字符串
        self.m_filesList = []
        
        if len(self.m_fileStr) > 0:
            fileList = self.m_fileStr.split(',')
            idxList = 0
            while idxList < len(fileList):
                if len(fileList[idxList]):
                    if fileList[idxList].rfind(ProtoFilesList.ProtoDotExt) != -1:   # 如果有扩展名字
                        protoFile = ProtoFile(fileList[idxList])
                        self.m_filesList.append(protoFile)
                    else:
                        protoDir = ProtoDir(fileList[idxList])
                        self.m_filesList.append(protoDir)
                        
                    idxList += 1
                    
                    
    def parse(self):
        for file in self.m_filesList:
            file.parse();
                    
                    
        