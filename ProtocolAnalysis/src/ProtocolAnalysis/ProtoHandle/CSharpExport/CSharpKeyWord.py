# -*- coding: utf-8 -*-


from ProtocolAnalysis.ProtoHandle.ProtoBase.ProtoKeyWord import ProtoKeyWord


class CSharpKeyWord(object):
    '''
    classdocs
    '''


    sProtoKey2CSharpKey = {}
    sProtoKey2CSharpKey[ProtoKeyWord.eInt8] = "string"
    sProtoKey2CSharpKey[ProtoKeyWord.eUint8] = "byte"
    sProtoKey2CSharpKey[ProtoKeyWord.eInt16] = "short"
    sProtoKey2CSharpKey[ProtoKeyWord.eUint16] = "ushort"
    sProtoKey2CSharpKey[ProtoKeyWord.eInt32] = "int"
    sProtoKey2CSharpKey[ProtoKeyWord.eUint32] = "uint"


    def __init__(self, params):
        '''
        Constructor
        '''
        