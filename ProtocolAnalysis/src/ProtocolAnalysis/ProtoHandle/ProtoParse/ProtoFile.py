# -*- coding: utf-8 -*-


from ProtocolAnalysis.ProtoHandle.ProtoParse.ProtoFileBase import ProtoFileBase, eFileType
from ProtocolAnalysis.ProtoHandle.ProtoBase.TokenParseBuffer import TokenParseBuffer
from ProtocolAnalysis.ProtoHandle.ProtoBase.ProtoKeyWord import ProtoKeyWord
from ProtocolAnalysis.ProtoHandle.ProtoBase.ProtoMessage import ProtoMessage
from ProtocolAnalysis.ProtoHandle.ProtoBase.ProtoComment import ProtoComment
from ProtocolAnalysis.ProtoHandle.ProtoBase.ProtoPackage import ProtoPackage
from ProtocolAnalysis.ProtoHandle.ProtoBase.ProtoEnum import ProtoEnum
from ProtocolAnalysis.ProtoHandle.ProtoBase.ProtoHeader import ProtoHeader
from ProtocolAnalysis.ProtoHandle.ProtoBase.ProtoImport import ProtoImport
from ProtocolAnalysis.Core.AppSysBase import AppSysBase


class ProtoFile(ProtoFileBase):
    '''
    classdocs
    '''


    def __init__(self, fullPath):
        '''
        Constructor
        '''
        super(ProtoFile, self).__init__(eFileType.eFile, fullPath)
        self.m_fullPath = AppSysBase.instance().getClsUtils().normalPath(self.m_fullPath)
        self.m_fileNameNoExt = AppSysBase.instance().getClsUtils().getFileNameNoExt(self.m_fullPath)
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
            elif tokenKey == ProtoKeyWord.eHeader:
                header_ = ProtoHeader()
                self.m_protoElemList.append(header_)
                header_.parse(tokenParseBuffer)
            elif tokenKey == ProtoKeyWord.eImport:
                import_ = ProtoImport()
                self.m_protoElemList.append(import_)
                import_.parse(tokenParseBuffer)
            else:   # 只处理注释
                if AppSysBase.instance().getClsUtils().tokenIsComment(tokenKey):       # 如果当前符号是注释
                    comment = ProtoComment()
                    self.m_protoElemList.append(comment)
                    comment.parse(tokenParseBuffer)


    def getProtoElemList(self):
        return self.m_protoElemList

