#-*- encoding=utf-8 -*-


from ProtocolAnalysis.ProtoHandle.ProtoBase.ProtoElemBase import ProtoElemBase, eProtoElemType
from ProtocolAnalysis.ProtoHandle.ProtoBase.ProtoKeyWord import ProtoKeyWord
from ProtocolAnalysis.ProtoHandle.ProtoBase.ProtoMemberComment import ProtoMemberComment
from ProtocolAnalysis.ProtoHandle.ProtoBase.EnumMember import EnumMember
from ProtocolAnalysis.Core.AppSysBase import AppSysBase


class ProtoEnum(ProtoElemBase):
    '''
    classdocs
    '''


    def __init__(self):
        '''
        Constructor
        '''
        super(ProtoEnum, self).__init__(eProtoElemType.eEnum)

    
    def parse(self, tokenParseBuffer):
        self.m_typeKeyWord = tokenParseBuffer.getTokenAndRemove()  # "enum"
        self.m_typeName = tokenParseBuffer.getTokenAndRemove() # "eTest"
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
            else:
                enumMember = EnumMember()
                self.m_memberList.append(enumMember)
                enumMember.parse(tokenParseBuffer)
            
        
        tokenParseBuffer.getTokenAndRemove()        # 移除 "};"
    
