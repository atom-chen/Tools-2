#-*- encoding=utf-8 -*-


class eProtoElemType(object):
    ePackage = 0    # 指定包的名字
    eEnum = 1       # 枚举类型
    eMessage = 2    # message 类型
    eComment = 3    # 注释
    eHeader = 4     # C++ 的包含头文件
    eImport = 5     # CSharp 包含的名字空间


class ProtoElemBase(object):


    def __init__(self, elemType):
        self.m_elemType = elemType          # 基本元素类型， message enum 
        self.m_typeKeyWord = ""         # Proto 关键字，例如 "message\enum" 类似, message enum
        self.m_typeName = ""            # 元素的类型名字, message enum
        self.m_commentList = []          # 注释字符串列表，就是可能会有很多行，只有 ProtoComment 会用到这个字段, Comment
        self.m_memberList = []          # 成员列表,message enum
    
    
    def parse(self, tokenParseBuffer):
        pass


    def getElemType(self):
        return self.m_elemType


    def getTypeName(self):
        return self.m_typeName
    

    def getCommentList(self):
        return self.m_commentList


    def getMemberList(self):
        return self.m_memberList

