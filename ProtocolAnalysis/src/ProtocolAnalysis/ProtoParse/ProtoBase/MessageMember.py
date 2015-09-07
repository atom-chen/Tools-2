#-*- encoding=utf-8 -*-


from ProtocolAnalysis.ProtoParse.ProtoBase.ProtoTypeMemberBase import ProtoTypeMemberBase


class MessageMember(ProtoTypeMemberBase):
    '''
    classdocs
    '''


    def __init__(self, params):
        '''
        Constructor
        '''

    def parse(self, tokenParseBuffer):
        line = tokenParseBuffer.getLineNoRemove()
        hasComment = (line.find("//") != -1)
        
        self.m_qualifier = tokenParseBuffer.getTokenAndRemove()
        self.m_typeName = tokenParseBuffer.getTokenAndRemove()
        self.m_varName = tokenParseBuffer.getTokenAndRemove()
        tokenParseBuffer.getTokenAndRemove()        # 移除 "="
        self.m_seqValue = tokenParseBuffer.getTokenAndRemove()
        tokenParseBuffer.getTokenAndRemove()        # 移除 ";"
        if hasComment:
            self.m_comment = tokenParseBuffer.getTokenAndRemove()
        