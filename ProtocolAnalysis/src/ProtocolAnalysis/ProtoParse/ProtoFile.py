# -*- coding: utf-8 -*-

from ProtocolAnalysis.ProtoParse.ProtoFileBase import ProtoFileBase, eFileType
from ProtocolAnalysis.ProtoParse.ProtoBase.TokenParseBuffer import TokenParseBuffer
from ProtocolAnalysis.ProtoParse.ProtoBase.ProtoKeyWord import ProtoKeyWord
from ProtocolAnalysis.ProtoParse.ProtoBase.ProtoMessage import ProtoMessage

class ProtoFile(ProtoFileBase):
    '''
    classdocs
    '''


    def __init__(self, fullPath):
        '''
        Constructor
        '''
        super(ProtoFile, self).__init__(eFileType.eFile, fullPath)
        self.m_protoElemList = []


    def parse(self):
        tokenParseBuffer = TokenParseBuffer()
        tokenParseBuffer.openFile(self.m_fullPath)
        while not tokenParseBuffer.isEOF():
            tokenKey = tokenParseBuffer.getLineNoRemove()
            
            if tokenKey == ProtoKeyWord.eMessage:
                msg = ProtoMessage()
                self.m_protoElemList.append(msg)
                msg.parse(tokenParseBuffer)

