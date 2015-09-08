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
        self.m_qualifier = ""       # message
        self.m_typeName = ""        # message
        self.m_varName = ""         # message enum
        self.m_seqValue = 0         # message enum
        self.m_commentStr = ""      # message enum


    def parse(self, tokenParseBuffer):
        pass
    
    
    def getTypeName(self):
        return self.m_typeName
    
    
    
    def getVarName(self):
        return self.m_varName
    
    
    def getCommentStr(self):
        return self.m_commentStr
    
