# -*- coding: utf-8 -*-


from ProtocolAnalysis.ProtoHandle.ProtoBase.ProtoKeyWord import ProtoKeyWord


class CSharpKeyWord(object):
    '''
    classdocs
    '''


    sProtoKey2CSharpKey = {}
    sProtoKey2CSharpKey[ProtoKeyWord.eUint32] = "uint32"


    def __init__(self, params):
        '''
        Constructor
        '''
        