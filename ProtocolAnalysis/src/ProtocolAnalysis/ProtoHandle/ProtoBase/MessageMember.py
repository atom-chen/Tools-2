#-*- encoding=utf-8 -*-


from ProtocolAnalysis.ProtoHandle.ProtoBase.ProtoTypeMemberBase import ProtoTypeMemberBase, PropertyType
from ProtocolAnalysis.ProtoHandle.ProtoBase.ProtoKeyWord import ProtoKeyWord
from ProtocolAnalysis.ProtoHandle.ProtoBase.ProtoPropertyTypeKeyWord2Property import ProtoPropertyTypeKeyWord2Property, PropertyData
from ProtocolAnalysis.ProtoHandle.ProtoBase.ProtoKeyWord import ProtoKeyWordList


class MessageMember(ProtoTypeMemberBase):
    '''
    classdocs
    '''


    def __init__(self):
        '''
        Constructor
        '''
        super(MessageMember, self).__init__()
        
        self.m_varNameAndArray = ""
        self.m_arrLen = ""
        
        self.m_arrLenBeforDot = ""    # 默认值点前面部分，例如 CVMsg.MAX_PASSWORD ，值就是 CVMsg ，如果是 10 ，这个值是 "10"
        self.m_arrLenAfterDot = ""    # 默认值点前面部分，例如 CVMsg.MAX_PASSWORD ，值就是 CVMsg ，如果是 10 ，这个值是 "10"
        
        self.m_defaultValueBeforDot = ""  # 默认值点前面部分，例如 CVMsg.MAX_PASSWORD ，值就是 CVMsg ，如果是 10 ，这个值是 "10"
        self.m_defaultValueAfterDot = ""  # 默认值点前面部分，例如 CVMsg.MAX_PASSWORD ，值就是 MAX_PASSWORD ，如果是 10 ，这个值是 "10"


    def parse(self, tokenParseBuffer):
        super(MessageMember, self).parse(tokenParseBuffer)
        
        line = tokenParseBuffer.getLineNoRemove()       # 注释可能在一行的结尾
        hasComment = (line.find("//") != -1)
        
        #self.m_qualifier = tokenParseBuffer.getTokenAndRemove()        # 修饰符，例如 optional
        self.m_typeName = tokenParseBuffer.getTokenAndRemove()          # 类型，例如 uint32
        self.m_varName = tokenParseBuffer.getTokenAndRemove()           # 变量名字， 例如 time
        if self.m_varName.find(";") != -1:  # 如果变量名字直接有 ";" 分号，就说明没有默认值
            self.m_varName = self.m_varName[:len(self.m_varName) - 1]
            equalOrSemicolonToken = ";"
        else:
            equalOrSemicolonToken = tokenParseBuffer.getTokenAndRemove()    # "=" 或者 ";" 
        if ProtoKeyWord.eEqualToken == equalOrSemicolonToken:           # 如果是等号，就说明有默认值
            self.m_defaultValue = tokenParseBuffer.getTokenAndRemove()
            if self.m_defaultValue.find(";") != -1:     # 如果数字后面的分号一起取出来，中间没有空格
                self.m_defaultValue = self.m_defaultValue[:len(self.m_defaultValue) - 1]
            else: 
                tokenParseBuffer.getTokenAndRemove()        # 移除 ";"
        elif ProtoKeyWord.eSemicolonToken == equalOrSemicolonToken:   # 如果是分号，说明没有默认值
            self.m_defaultValue = None          # 给这个值赋值 None
        
        if hasComment:
            self.m_commentStr = tokenParseBuffer.getLineRemove()
        
        if self.m_defaultValue != None:         # 如果有设置默认值
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
            
            #if self.m_typeName == ProtoKeyWord.eInt8: 
            #    self.m_propType = PropertyType.eInt8Array
            #if self.m_typeName == ProtoKeyWord.eUint8: 
            #    self.m_propType = PropertyType.eUint8Array
            #if self.m_typeName == ProtoKeyWord.eInt16: 
            #    self.m_propType = PropertyType.eInt16Array
            #if self.m_typeName == ProtoKeyWord.eUint16: 
            #    self.m_propType = PropertyType.eUint16Array
            #if self.m_typeName == ProtoKeyWord.eInt32: 
            #    self.m_propType = PropertyType.eInt32Array
            #if self.m_typeName == ProtoKeyWord.eUint32: 
            #    self.m_propType = PropertyType.eUint32Array
            
            if self.m_typeName in ProtoKeyWordList.sKeyWordBasicType:        # 如果类型在基本类型中
                arrTypeKeyWord = PropertyData.createTypeArrKeyWord(self.m_typeName)
                self.m_propType = ProtoPropertyTypeKeyWord2Property.m_sKeyWord2PropertyData[arrTypeKeyWord].getProtertyType()
            else:       # 不是基本类型
                self.m_propType = PropertyType.eUserDataArray
        else:
            #if self.m_typeName == ProtoKeyWord.eInt8:
            #    self.m_propType = PropertyType.eInt8
            #if self.m_typeName == ProtoKeyWord.eUint8:
            #    self.m_propType = PropertyType.eUint8
            #if self.m_typeName == ProtoKeyWord.eInt16:
            #    self.m_propType = PropertyType.eInt16
            #if self.m_typeName == ProtoKeyWord.eUint16:
            #    self.m_propType = PropertyType.eUint16
            #if self.m_typeName == ProtoKeyWord.eInt32:
            #    self.m_propType = PropertyType.eInt32
            #if self.m_typeName == ProtoKeyWord.eUint32:
            #    self.m_propType = PropertyType.eUint32

            if self.m_typeName in ProtoKeyWordList.sKeyWordBasicType:        # 如果类型在基本类型中
                self.m_propType = ProtoPropertyTypeKeyWord2Property.m_sKeyWord2PropertyData[self.m_typeName].getProtertyType()
            else:
                self.m_propType = PropertyType.eUserData
                
        
    
    # 分割默认值，数字是没有小数点的，如果有小数点，需要转换成整数才行，类似乘以 100 
    def splitDefaultValue(self):
        dotIdx = self.m_defaultValue.find(".")
        if dotIdx != -1:
            self.m_defaultValueBeforDot = self.m_defaultValue[ : dotIdx]
            self.m_defaultValueAfterDot = self.m_defaultValue[dotIdx + 1 : len(self.m_defaultValue)]
        else:
            self.m_defaultValueAfterDot = self.m_defaultValue


    def splitArrLen(self):
        if self.m_propType == PropertyType.eInt8Array or \
            self.m_propType == PropertyType.eUint8Array or \
            self.m_propType == PropertyType.eInt16Array or \
            self.m_propType == PropertyType.eUint16Array or \
            self.m_propType == PropertyType.eInt32Array or \
            self.m_propType == PropertyType.eUint32Array or \
            self.m_propType == PropertyType.eUserDataArray:
            
            dotIdx = self.m_arrLen.find(".")
            if dotIdx != -1:
                self.m_arrLenBeforDot = self.m_arrLen[ : dotIdx]
                self.m_arrLenAfterDot = self.m_arrLen[dotIdx + 1 : len(self.m_arrLen)]
            else:
                self.m_arrLenAfterDot = self.m_arrLen
    
    
    def getVarNameAndArray(self):
        return self.m_varNameAndArray;
    
    
    def getArrLen(self):
        return self.m_arrLen
        
    
    def getDefaultValueBeforDot(self):
        return self.m_defaultValueBeforDot


    def getDefaultValueAfterDot(self):
        return self.m_defaultValueAfterDot


    def getArrLenBeforDot(self):
        return self.m_arrLenBeforDot


    def getArrLenAfterDot(self):
        return self.m_arrLenAfterDot
    
    
    # 判断是否有默认的
    def hasDefaultValue(self):
        return self.m_defaultValue != None
    
    
    # 默认值是否是枚举常量
    def isDefaultValueCV(self):
        if self.hasDefaultValue(): # 如果有默认值
            return self.m_defaultValue.find(".") != -1      # 看是否有小数点，可能数字中间也有小数点
        
        return False
    
    
    # 数据类型是否是基本数据类型
    def isBasicType(self):
        if self.getPropertyType() == PropertyType.eInt8 or \
            self.getPropertyType() == PropertyType.eUint8 or \
            self.getPropertyType() == PropertyType.eInt16 or \
            self.getPropertyType() == PropertyType.eUint16 or \
            self.getPropertyType() == PropertyType.eInt32 or \
            self.getPropertyType() == PropertyType.eUint32:
            
            return True
        
        return False

    
    def isUserType(self):
        return self.getPropertyType() == PropertyType.eUserData

    
    # 是否是单个元素类型
    def isAllType(self):
        return self.isBasicType() or self.isUserType()


    # 是否是数组类型
    def isBasicArrayType(self):
        if self.getPropertyType() == PropertyType.eInt8Array or \
            self.getPropertyType() == PropertyType.eUint8Array or \
            self.getPropertyType() == PropertyType.eInt16Array or \
            self.getPropertyType() == PropertyType.eUint16Array or \
            self.getPropertyType() == PropertyType.eInt32Array or \
            self.getPropertyType() == PropertyType.eUint32Array:
            return True
        
        return False
    
    
    # 数据类型是否是 char[] 字符数组类型
    def isCharArrayType(self):
        return self.getPropertyType() == PropertyType.eInt8Array
    

    def isUserArrayType(self):
        return self.getPropertyType() == PropertyType.eUserDataArray
    
    
    def isAllArrayType(self):
        if self.isBasicArrayType() or self.getPropertyType() == PropertyType.eUserDataArray:
            return True
        
        return False

