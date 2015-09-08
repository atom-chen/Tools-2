#-*- encoding=utf-8 -*-


from ProtocolAnalysis.ProtoHandle.ProtoBase.ProtoTypeMemberBase import ProtoTypeMemberBase, PropertyType
from ProtocolAnalysis.ProtoHandle.ProtoBase.ProtoKeyWord import ProtoKeyWord


class MessageMember(ProtoTypeMemberBase):
    '''
    classdocs
    '''


    def __init__(self):
        '''
        Constructor
        '''
        self.m_varNameAndArray = ""
        self.m_arrLen = ""


    def parse(self, tokenParseBuffer):
        line = tokenParseBuffer.getLineNoRemove()       # 注释可能在一行的结尾
        hasComment = (line.find("//") != -1)
        
        #self.m_qualifier = tokenParseBuffer.getTokenAndRemove()     # 修饰符，例如 optional
        self.m_typeName = tokenParseBuffer.getTokenAndRemove()      # 类型，例如 uint32
        self.m_varName = tokenParseBuffer.getTokenAndRemove()       # 变量名字， 例如 time
        tokenParseBuffer.getTokenAndRemove()        # 移除 "="
        self.m_defaultValue = tokenParseBuffer.getTokenAndRemove()
        if self.m_defaultValue.find(";") != -1:     # 如果数字后面的分号一起取出来，中间没有空格
            self.m_defaultValue = self.m_defaultValue[:len(self.m_defaultValue) - 1]
        else: 
            tokenParseBuffer.getTokenAndRemove()        # 移除 ";"
        if hasComment:
            self.m_commentStr = tokenParseBuffer.getLineRemove()
        
        self.resolveMemberType()
            
    # 解析成员类型
    def resolveMemberType(self):
        if self.m_varName[len(self.m_varName) - 1 : len(self.m_varName)] == "]":    # 如果最后是一个 "]" ，就说明是一个数组
            self.m_varNameAndArray = self.m_varName
            lBraceIdx = self.m_varNameAndArray.rfind("[")
            rBraceidx = self.m_varNameAndArray.rfind("]")
            self.m_varName = self.m_varNameAndArray[ : lBraceIdx]
            self.m_arrLen = self.m_varNameAndArray[lBraceIdx + 1 : rBraceidx]
            
            if self.m_typeName == ProtoKeyWord.eChar:
                self.m_propType = PropertyType.eCharArray
        else:
            if self.m_typeName == ProtoKeyWord.eUint32:
                self.m_propType = PropertyType.eUint32
        
            
