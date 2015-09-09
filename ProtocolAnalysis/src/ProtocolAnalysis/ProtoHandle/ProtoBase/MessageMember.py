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
        
        self.arrLenBeforDot = ""
        self.arrLenAfterDot = ""
        
        self.defaultValueBeforDot = ""  # 默认值点前面部分，例如 CVMsg.MAX_PASSWORD ，值就是 CVMsg ，如果是 10 ，这个值是 ""
        self.defaultValueAfterDot = ""  # 默认值点前面部分，例如 CVMsg.MAX_PASSWORD ，值就是 MAX_PASSWORD ，如果是 10 ，这个值是 ""


    def parse(self, tokenParseBuffer):
        super(MessageMember, self).parse(tokenParseBuffer)
        
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
        
        self.splitDefaultValue()
        self.resolveMemberType()
        self.splitArrLen()
            
    # 解析成员类型
    def resolveMemberType(self):
        if self.m_varName[len(self.m_varName) - 1 : len(self.m_varName)] == "]":    # 如果最后是一个 "]" ，就说明是一个数组
            self.m_varNameAndArray = self.m_varName
            lBraceIdx = self.m_varNameAndArray.rfind("[")
            rBraceidx = self.m_varNameAndArray.rfind("]")
            self.m_varName = self.m_varNameAndArray[ : lBraceIdx]
            self.m_arrLen = self.m_varNameAndArray[lBraceIdx + 1 : rBraceidx]
            
            if self.m_typeName == ProtoKeyWord.eInt8: 
                self.m_propType = PropertyType.eInt8Array
            if self.m_typeName == ProtoKeyWord.eUint8: 
                self.m_propType = PropertyType.eUint8Array
            if self.m_typeName == ProtoKeyWord.eInt16: 
                self.m_propType = PropertyType.eInt16Array
            if self.m_typeName == ProtoKeyWord.eUint16: 
                self.m_propType = PropertyType.eUint16Array
            if self.m_typeName == ProtoKeyWord.eInt32: 
                self.m_propType = PropertyType.eInt32Array
            if self.m_typeName == ProtoKeyWord.eUint32: 
                self.m_propType = PropertyType.eUint32Array
        else:
            if self.m_typeName == ProtoKeyWord.eInt8:
                self.m_propType = PropertyType.eInt8
            if self.m_typeName == ProtoKeyWord.eUint8:
                self.m_propType = PropertyType.eUint8
            if self.m_typeName == ProtoKeyWord.eInt16:
                self.m_propType = PropertyType.eInt16
            if self.m_typeName == ProtoKeyWord.eUint16:
                self.m_propType = PropertyType.eUint16
            if self.m_typeName == ProtoKeyWord.eInt32:
                self.m_propType = PropertyType.eInt32
            if self.m_typeName == ProtoKeyWord.eUint32:
                self.m_propType = PropertyType.eUint32
        
    
    # 分割默认值，数字是没有小数点的，如果有小数点，需要转换成整数才行，类似乘以 100 
    def splitDefaultValue(self):
        dotIdx = self.m_defaultValue.find(".")
        if dotIdx != -1:
            self.defaultValueBeforDot = self.m_defaultValue[ : dotIdx]
            self.defaultValueAfterDot = self.m_defaultValue[dotIdx + 1 : len(self.m_defaultValue)]


    def splitArrLen(self):
        if self.m_propType == PropertyType.eInt8Array:
            dotIdx = self.m_arrLen.find(".")
            if dotIdx != -1:
                self.arrLenBeforDot = self.m_arrLen[ : dotIdx]
                self.arrLenAfterDot = self.m_arrLen[dotIdx + 1 : len(self.m_arrLen)]            
    
    
    def getVarNameAndArray(self):
        return self.m_varNameAndArray;
    
    
    def getArrLen(self):
        return self.m_arrLen
        
    
    def getDefaultValueBeforDot(self):
        return self.defaultValueBeforDot


    def getDefaultValueAfterDot(self):
        return self.defaultValueAfterDot


    def getArrLenBeforDot(self):
        return self.arrLenBeforDot


    def getArrLenAfterDot(self):
        return self.arrLenAfterDot

