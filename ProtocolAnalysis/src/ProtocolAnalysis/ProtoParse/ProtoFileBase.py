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


    def parse(self):
        pass
