# -*- coding: utf-8 -*-


from ProtocolAnalysis.ProtoHandle.ProtoBase.ProtoElemBase import ProtoElemBase, eProtoElemType


class ProtoComment(ProtoElemBase):
    '''
    classdocs
    '''


    def __init__(self):
        '''
        Constructor
        '''
        super(ProtoComment, self).__init__(eProtoElemType.eComment)


    # 可能是单行注释或者多行注释
    def parse(self, tokenParseBuffer):
        self.m_commentList = tokenParseBuffer.getCommentAndSpaceLine()
        
        
