# -*- coding: utf-8 -*-


from ProtocolAnalysis.ProtoHandle.ProtoBase.ProtoTypeMemberBase import ProtoTypeMemberBase


class EnumMember(ProtoTypeMemberBase):
    '''
    classdocs
    '''


    def __init__(self):
        '''
        Constructor
        '''
    

    def parse(self, tokenParseBuffer):
        line = tokenParseBuffer.getLineNoRemove()       # 注释可能在一行的结尾
        hasComment = (line.find("//") != -1)

        self.m_varName = tokenParseBuffer.getTokenAndRemove()
        tokenParseBuffer.getTokenAndRemove()        # 移除 "="
        self.m_defaultValue = tokenParseBuffer.getTokenAndRemove()
        if self.m_defaultValue.find(";") != -1:     # 如果数字后面的分号一起取出来，中间没有空格
            self.m_defaultValue = self.m_defaultValue[:len(self.m_defaultValue) - 1]
        else: 
            tokenParseBuffer.getTokenAndRemove()        # 移除 ";"
        if hasComment:
            self.m_commentStr = tokenParseBuffer.getLineRemove()

