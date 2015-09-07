#-*- encoding=utf-8 -*-


class eProtoElemType(object):
    ePackage = 0    # 指定包的名字
    eEnum = 1       # 枚举类型
    eMessage = 2    # message 类型
    eComment = 3    # 注释


class ProtoElemBase(object):


    def __init__(self, elemType):
        self.m_type = elemType          # 基本元素类型
        self.m_typeKeyWord = ""         # Proto 关键字，例如 "message\enum" 类似
        self.m_typeName = ""            # 元素的类型名字
        self.m_commentStr = ""          # 注释字符串，只有 ProtoComment 会用到这个字段
        self.m_memberList = []          # 成员列表
    
    
    def parse(self, tokenParseBuffer):
        pass


    def getType(self):
        return self.m_type


    def getTypeName(self):
        return self.m_typeName
    

    def getCommentStr(self):
        return self.m_commentStr


    def getMemberList(self):
        return self.m_memberList

