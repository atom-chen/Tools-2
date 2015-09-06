# -*- coding: utf-8 -*-

from ProtocolAnalysis.ProtoParse.ProtoFileBase import ProtoFileBase, eFileType

class ProtoFile(ProtoFileBase):
    '''
    classdocs
    '''


    def __init__(self, fullPath):
        '''
        Constructor
        '''
        super(ProtoFile, self).__init__(eFileType.eFile, fullPath)
        