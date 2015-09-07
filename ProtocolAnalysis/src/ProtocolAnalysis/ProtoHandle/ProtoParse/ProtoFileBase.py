# -*- coding: utf-8 -*-


class eFileType(object):
    eFile = 0
    eDir = 1


class ProtoFileBase(object):
    '''
    classdocs
    '''


    def __init__(self, fileType, fullPath):
        '''
        Constructor
        '''
        self.m_type = fileType
        self.m_fullPath = fullPath
        self.m_fileNameNoExt = ""


    def parse(self):
        pass


    def getFileType(self):
        return self.m_type
    
    
    def getFileNameNoExt(self):
        return self.m_fileNameNoExt
    
