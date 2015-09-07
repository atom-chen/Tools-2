# -*- coding: utf-8 -*-


class EnumMember(object):
    '''
    classdocs
    '''


    def __init__(self, params):
        '''
        Constructor
        '''
    

    def parse(self, tokenParseBuffer):
        line = tokenParseBuffer.getLineNoRemove()       # 注释可能在一行的结尾
        hasComment = (line.find("//") != -1)

        self.m_varName = tokenParseBuffer.getTokenAndRemove()
        tokenParseBuffer.getTokenAndRemove()        # 移除 "="
        self.m_seqValue = tokenParseBuffer.getTokenAndRemove()
        if self.m_seqValue.find(";") != -1:     # 如果数字后面的分号一起取出来，中间没有空格
            self.m_seqValue = self.m_seqValue[:len(self.m_seqValue) - 1]
        else: 
            tokenParseBuffer.getTokenAndRemove()        # 移除 ";"
        if hasComment:
            self.m_commentStr = tokenParseBuffer.getTokenAndRemove()

