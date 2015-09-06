#-*- encoding=utf-8 -*-

from ProtocolAnalysis.ProtoParse.ProtoBase.ProtoElemBase import ProtoElemBase, eProtoElemType

class ProtoEnum(ProtoElemBase):
    '''
    classdocs
    '''


    def __init__(self):
        '''
        Constructor
        '''
        super(ProtoEnum, self).__init__(eProtoElemType.eEnum)

