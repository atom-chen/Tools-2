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

