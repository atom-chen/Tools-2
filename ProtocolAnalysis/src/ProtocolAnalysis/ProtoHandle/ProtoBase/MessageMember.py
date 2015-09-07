#-*- encoding=utf-8 -*-


from ProtocolAnalysis.ProtoHandle.ProtoBase.ProtoTypeMemberBase import ProtoTypeMemberBase


class MessageMember(ProtoTypeMemberBase):
    '''
    classdocs
    '''


    def __init__(self):
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
        if self.m_seqValue.find(";") != -1:     # 如果数字后面的分号一起取出来，中间没有空格
            self.m_seqValue = self.m_seqValue[:1]
        else: 
            tokenParseBuffer.getTokenAndRemove()        # 移除 ";"
        if hasComment:
            self.m_comment = tokenParseBuffer.getTokenAndRemove()
        