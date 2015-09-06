#-*- encoding=utf-8 -*-

class eProtoElemType(object):
    ePackage = 0    # 指定包的名字
    eEnum = 1       # 枚举类型
    eMessage = 2    # message 类型

class ProtoElemBase(object):
    
    def __init__(self, elemType):
        self.m_type = elemType
        self.m_commentStr = ""          # 注释字符串
        self.m_typeName = ""            # 元素的类型名字
        self.m_memberList = []          # 成员列表
    
    
    def parse(self, tokenParseBuffer):
        pass

