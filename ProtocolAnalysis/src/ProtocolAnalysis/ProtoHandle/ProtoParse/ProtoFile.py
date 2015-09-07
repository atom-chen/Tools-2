# -*- coding: utf-8 -*-


from ProtocolAnalysis.ProtoHandle.ProtoParse.ProtoFileBase import ProtoFileBase, eFileType
from ProtocolAnalysis.ProtoHandle.ProtoBase.TokenParseBuffer import TokenParseBuffer
from ProtocolAnalysis.ProtoHandle.ProtoBase.ProtoKeyWord import ProtoKeyWord
from ProtocolAnalysis.ProtoHandle.ProtoBase.ProtoMessage import ProtoMessage


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

