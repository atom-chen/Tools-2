#-*- encoding=utf-8 -*-


class PropertyType(object):
    eUint32 = 0                 # uint32
    eCharArray = 1              # char [30]
    eUserData = 2               # 用户自定义数据类型


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
    
    
