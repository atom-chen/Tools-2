#-*- encoding=utf-8 -*-


from ProtocolAnalysis.ProtoHandle.ProtoBase.ProtoTypeMemberBase import ProtoTypeMemberBase


class ProtoMemberComment(ProtoTypeMemberBase):
    '''
    classdocs
    '''


    def __init__(self, params):
        '''
        Constructor
        '''

    # 可能是单行注释或者多行注释
    def parse(self, tokenParseBuffer):
        self.m_commentStr = tokenParseBuffer.getCommentAndSpaceLine()

