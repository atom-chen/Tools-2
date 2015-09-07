# -*- coding: utf-8 -*-


from ProtocolAnalysis.ProtoHandle.ProtoParse.ProtoFileBase import ProtoFileBase, eFileType
from ProtocolAnalysis.ProtoHandle.ProtoBase.TokenParseBuffer import TokenParseBuffer
from ProtocolAnalysis.ProtoHandle.ProtoBase.ProtoKeyWord import ProtoKeyWord
from ProtocolAnalysis.ProtoHandle.ProtoBase.ProtoMessage import ProtoMessage
from ProtocolAnalysis.ProtoHandle.ProtoBase.ProtoComment import ProtoComment
from ProtocolAnalysis.ProtoHandle.ProtoBase.ProtoPackage import ProtoPackage
from ProtocolAnalysis.ProtoHandle.ProtoBase.ProtoEnum import ProtoEnum


class ProtoFile(ProtoFileBase):
    '''
    classdocs
    '''


    def __init__(self, fullPath):
        '''
        Constructor
        '''
        super(ProtoFile, self).__init__(eFileType.eFile, fullPath)
        self.m_protoElemList = []


    def parse(self):
        tokenParseBuffer = TokenParseBuffer()
        tokenParseBuffer.openFile(self.m_fullPath)
        while not tokenParseBuffer.isEOF():
            tokenKey = tokenParseBuffer.getTokenAndNoRemove()       # 获取一个符号，检查具体类型
            
            if tokenKey == ProtoKeyWord.eMessage:
                msg = ProtoMessage()
                self.m_protoElemList.append(msg)
                msg.parse(tokenParseBuffer)
            elif tokenKey == ProtoKeyWord.ePackage:
                package = ProtoPackage()
                self.m_protoElemList.append(package)
                package.parse(tokenParseBuffer)
            elif tokenKey == ProtoKeyWord.eEnum:
                enum_ = ProtoEnum()
                self.m_protoElemList.append(enum_)
                enum_.parse(tokenParseBuffer)
            else:   # 只处理注释
                if len(tokenKey) == 2:  # // 注释
                    if tokenKey == ProtoKeyWord.eSingleLineComment:
                        comment = ProtoComment()
                        self.m_protoElemList.append(comment)
                        comment.parse(tokenParseBuffer)
                elif len(tokenKey) == 3:  # /** 注释
                    if tokenKey == ProtoKeyWord.eMulLineCommentStart:
                        comment = ProtoComment()
                        self.m_protoElemList.append(comment)
                        comment.parse(tokenParseBuffer)
                elif len(tokenKey) > 2:
                    tokenKey = tokenKey[:2]         # 截取前两个字节
                    if tokenKey == ProtoKeyWord.eSingleLineComment:
                        comment = ProtoComment()
                        self.m_protoElemList.append(comment)
                        comment.parse(tokenParseBuffer)
                elif len(tokenKey) > 3:
                    tokenKey = tokenKey[:3]         # 截取前两个字节
                    if tokenKey == ProtoKeyWord.eMulLineCommentStart:
                        comment = ProtoComment()
                        self.m_protoElemList.append(comment)
                        comment.parse(tokenParseBuffer)

