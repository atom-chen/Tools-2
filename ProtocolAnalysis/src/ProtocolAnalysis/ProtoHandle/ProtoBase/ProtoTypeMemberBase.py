#-*- encoding=utf-8 -*-


class PropertyType(object):
    eInt8 = 0                   # char
    eUint8 = 1                  # uint8
    eInt16 = 2                  # int16
    eUInt16 = 3                 # uint16
    eInt32 = 4                  # uint32
    eUInt32 = 5                 # uint32
    
    eInt8Array = 6              # char [30]
    eUInt8Array = 7             # byte [30]
    eInt16Array = 8             # int16 [30]
    eUInt16Array = 9            # uint16 [30]
    eInt32Array = 10            # int32 [30]
    eUInt32Array = 11           # uint32 [30]
    eUserData = 12              # 用户自定义数据类型
    eUserDataArray = 13         # 用户自定义数据数组类型
    eBase = 14                  # base 属性


# 类型成员基本属性
class ProtoTypeMemberBase(object):
    '''
    classdocs
    '''


    def __init__(self):
        '''
        Constructor
        '''
        self.m_propType = 0
        #self.m_qualifier = ""       # message
        self.m_typeName = ""        # 变量类型，message
        self.m_varName = ""         # 变量名字，message enum
        self.m_defaultValue = 0     # 默认值， message enum
        self.m_commentStr = ""      # message enum，但是只有一行


    def parse(self, tokenParseBuffer):
        pass
    
    
    def getPropertyType(self):
        return self.m_propType
    
    
    def getTypeName(self):
        return self.m_typeName
    

    def getVarName(self):
        return self.m_varName
    
    
    def getCommentStr(self):
        return self.m_commentStr
    
    
    def getDefaultValue(self):
        return self.m_defaultValue
    
    
