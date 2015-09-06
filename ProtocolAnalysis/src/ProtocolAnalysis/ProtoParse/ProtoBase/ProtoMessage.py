#-*- encoding=utf-8 -*-

from ProtocolAnalysis.ProtoParse.ProtoBase.ProtoElemBase import ProtoElemBase, eProtoElemType
from ProtocolAnalysis.ProtoParse.ProtoBase.ProtoKeyWord import ProtoKeyWord
from ProtocolAnalysis.ProtoParse.ProtoBase.MessageMember import MessageMember

class ProtoMessage(ProtoElemBase):
    '''
    classdocs
    '''


    def __init__(self):
        '''
        Constructor
        '''
        super(ProtoMessage, self).__init__(eProtoElemType.eMessage)


    def parse(self, tokenParseBuffer):
        typeKeyWord = tokenParseBuffer.getTokenAndRemove()  # "message"
        self.m_typeName = tokenParseBuffer.getTokenAndRemove() # "stUserInfo"
        tokenParseBuffer.getTokenAndRemove()        # 移除 "{"
        
        while True:
            linePrefix = tokenParseBuffer.getTokenAndNoRemove()
            if linePrefix == ProtoKeyWord.eRightBrace:
                break
            else:
                messageMember = MessageMember()
                self.m_memberList.append(messageMember)
                messageMember.parse(tokenParseBuffer)
            
        
        tokenParseBuffer.getTokenAndRemove()        # 移除 "}"
        tokenParseBuffer.getTokenAndRemove()        # 移除 ";"
        
