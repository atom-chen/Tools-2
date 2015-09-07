# -*- coding: utf-8 -*-


from ProtocolAnalysis.ProtoParse.ProtoFileBase import ProtoFileBase, eFileType


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


    def parse(self):
        for file in self.m_filesList:
            file.parse();

