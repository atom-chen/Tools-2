#-*- encoding=utf-8 -*-

from ProtocolAnalysis.ProtoParse.ProtoBase.ProtoElemBase import ProtoElemBase, eProtoElemType

class ProtoPackage(ProtoElemBase):
    '''
    classdocs
    '''


    def __init__(self):
        '''
        Constructor
        '''
        super(ProtoPackage, self).__init__(eProtoElemType.ePackage)

