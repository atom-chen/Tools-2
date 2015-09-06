#-*- encoding=utf-8 -*-

# 类型成员基本属性
class ProtoTypeMemberBase(object):
    '''
    classdocs
    '''


    def __init__(self):
        '''
        Constructor
        '''
        self.m_qualifier = ""
        self.m_typeName = ""
        self.m_varName = ""
        self.m_seqValue = 0
        self.m_comment = ""


    def parse(self, tokenParseBuffer):
        pass
    
