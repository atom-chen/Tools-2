#-*- encoding=utf-8 -*-


from ProtocolAnalysis.ProtoHandle.ProtoBase.ProtoElemBase import ProtoElemBase, eProtoElemType
from ProtocolAnalysis.ProtoHandle.ProtoBase.ProtoKeyWord import ProtoKeyWord
from ProtocolAnalysis.ProtoHandle.ProtoBase.MessageMember import MessageMember
from ProtocolAnalysis.ProtoHandle.ProtoBase.ProtoMemberComment import ProtoMemberComment
from ProtocolAnalysis.Core.AppSysBase import AppSysBase


class ProtoMessage(ProtoElemBase):
    '''
    classdocs
    '''


    def __init__(self):
        '''
        Constructor
        '''
        super(ProtoMessage, self).__init__(eProtoElemType.eMessage)
        self.m_parentCls = ""
        self.m_baseMemberInitList = []      # 父类成员初始化列表


    def parse(self, tokenParseBuffer):
        self.m_typeKeyWord = tokenParseBuffer.getTokenAndRemove()  # "message"
        self.m_typeName = tokenParseBuffer.getTokenAndRemove() # "stTest"
        # 检查父类
        nextToken = tokenParseBuffer.getTokenAndNoRemove()
        if nextToken == ":":     # 说明有基类
            nextToken = tokenParseBuffer.getTokenAndRemove()    # 移除 ":"
            self.m_parentCls = tokenParseBuffer.getTokenAndRemove()
        
        
        tokenParseBuffer.getTokenAndRemove()        # 移除 "{"
        
        while True:
            linePrefix = tokenParseBuffer.getTokenAndNoRemove()
            if linePrefix == ProtoKeyWord.eRightBraceSemicolon:     # 如果取出来是 "};"
                break
            elif linePrefix == ProtoKeyWord.eRightBrace:            # 如果取出来是 "}"
                tokenParseBuffer.getTokenAndRemove()        # 移除 ";"
                break
            elif AppSysBase.instance().getClsUtils().tokenIsComment(linePrefix):       # 如果当前符号是注释
                memberComment = ProtoMemberComment()
                self.m_memberList.append(memberComment)
                memberComment.parse(memberComment)
            elif linePrefix == ProtoKeyWord.eBase:
                messageMember = MessageMember()
                self.m_baseMemberInitList.append(messageMember)
                messageMember.parse(tokenParseBuffer)
            else:
                messageMember = MessageMember()
                self.m_memberList.append(messageMember)
                messageMember.parse(tokenParseBuffer)
            
        
        tokenParseBuffer.getTokenAndRemove()        # 移除 "};"
        
        
    def getParentCls(self):
        return self.m_parentCls
        
        
    # 获取基类成员初始化列表
    def getBaseMemberInitList(self):
        return self.m_baseMemberInitList

