#-*- encoding=utf-8 -*-


from ProtocolAnalysis.ProtoHandle.ProtoBase.ProtoTypeMemberBase import PropertyType


class CSharpPropertyData(object):
    '''
    classdocs
    '''    


    def __init__(self, params):
        '''
        Constructor
        '''
        self.m_propertyTypeKeyWord = ""         # 例如 byte string uint int 之类的
        self.m_serializeFuncKeyWord = ""        # 序列化函数关键字，例如 int 对应的就是  writeInt32 
        self.m_derializeFuncKeyWord = "" 



class CSharpPropertyType2PropertyData(object):
    '''
    classdocs
    '''
    m_sType2PropertyData = {}
    m_sType2PropertyData[PropertyType.eInt8] = CSharpPropertyData()
    m_sType2PropertyData[PropertyType.eInt8].m_propertyTypeKeyWord = "char"
    m_sType2PropertyData[PropertyType.eInt8].m_m_serializeFuncKeyWord = "writeInt8"
    m_sType2PropertyData[PropertyType.eInt8].m_derializeFuncKeyWord = "writeInt8"
    
    m_sType2PropertyData[PropertyType.eUint8] = CSharpPropertyData()
    m_sType2PropertyData[PropertyType.eUint8].m_propertyTypeKeyWord = "byte"
    m_sType2PropertyData[PropertyType.eUint8].m_m_serializeFuncKeyWord = "writeUnsignedInt8"
    m_sType2PropertyData[PropertyType.eUint8].m_derializeFuncKeyWord = "readUnsignedInt8"
    
    m_sType2PropertyData[PropertyType.eInt16] = CSharpPropertyData()
    m_sType2PropertyData[PropertyType.eInt16].m_propertyTypeKeyWord = "short"
    m_sType2PropertyData[PropertyType.eInt16].m_m_serializeFuncKeyWord = "writeInt16"
    m_sType2PropertyData[PropertyType.eInt16].m_derializeFuncKeyWord = "readInt16"
    
    m_sType2PropertyData[PropertyType.eUint16] = CSharpPropertyData()
    m_sType2PropertyData[PropertyType.eUint16].m_propertyTypeKeyWord = "ushort"
    m_sType2PropertyData[PropertyType.eUint16].m_m_serializeFuncKeyWord = "writeUnsignedInt16"
    m_sType2PropertyData[PropertyType.eUint16].m_derializeFuncKeyWord = "readUnsignedInt16"
    
    m_sType2PropertyData[PropertyType.eInt32] = CSharpPropertyData()
    m_sType2PropertyData[PropertyType.eInt32].m_propertyTypeKeyWord = "int"
    m_sType2PropertyData[PropertyType.eInt32].m_m_serializeFuncKeyWord = "writeInt32"
    m_sType2PropertyData[PropertyType.eInt32].m_derializeFuncKeyWord = "readInt32"
    
    m_sType2PropertyData[PropertyType.eUint32] = CSharpPropertyData()
    m_sType2PropertyData[PropertyType.eUint32].m_propertyTypeKeyWord = "uint"
    m_sType2PropertyData[PropertyType.eUint32].m_m_serializeFuncKeyWord = "writeUnsignedInt32"
    m_sType2PropertyData[PropertyType.eUint32].m_derializeFuncKeyWord = "readUnsignedInt32"
    
    # char 全部作为 string 处理
    #m_sType2PropertyData[PropertyType.eInt8] = CSharpPropertyData()
    #m_sType2PropertyData[PropertyType.eInt8].m_propertyTypeKeyWord = "string"
    #m_sType2PropertyData[PropertyType.eInt8].m_m_serializeFuncKeyWord = "writeMultiByte"
    #m_sType2PropertyData[PropertyType.eInt8].m_derializeFuncKeyWord = "readMultiByte"
    
    m_sType2PropertyData[PropertyType.eUint8Array] = CSharpPropertyData()
    m_sType2PropertyData[PropertyType.eUint8Array].m_propertyTypeKeyWord = "byte"
    m_sType2PropertyData[PropertyType.eUint8Array].m_m_serializeFuncKeyWord = "writeUnsignedByte"
    m_sType2PropertyData[PropertyType.eUint8Array].m_derializeFuncKeyWord = "readUnsignedByte"
    
    m_sType2PropertyData[PropertyType.eInt16Array] = CSharpPropertyData()
    m_sType2PropertyData[PropertyType.eInt16Array].m_propertyTypeKeyWord = "short"
    m_sType2PropertyData[PropertyType.eInt16Array].m_m_serializeFuncKeyWord = "writeInt16"
    m_sType2PropertyData[PropertyType.eInt16Array].m_derializeFuncKeyWord = "readInt16"
    
    m_sType2PropertyData[PropertyType.eUint16Array] = CSharpPropertyData()
    m_sType2PropertyData[PropertyType.eUint16Array].m_propertyTypeKeyWord = "ushort"
    m_sType2PropertyData[PropertyType.eUint16Array].m_m_serializeFuncKeyWord = "writeUnsignedInt16"
    m_sType2PropertyData[PropertyType.eUint16Array].m_derializeFuncKeyWord = "readUnsignedInt16"
    
    m_sType2PropertyData[PropertyType.eInt32Array] = CSharpPropertyData()
    m_sType2PropertyData[PropertyType.eInt32Array].m_propertyTypeKeyWord = "int"
    m_sType2PropertyData[PropertyType.eInt32Array].m_m_serializeFuncKeyWord = "writeInt32"
    m_sType2PropertyData[PropertyType.eInt32Array].m_derializeFuncKeyWord = "readInt32"
    
    m_sType2PropertyData[PropertyType.eUint32Array] = CSharpPropertyData()
    m_sType2PropertyData[PropertyType.eUint32Array].m_propertyTypeKeyWord = "uint"
    m_sType2PropertyData[PropertyType.eUint32Array].m_m_serializeFuncKeyWord = "writeUnsignedInt32"
    m_sType2PropertyData[PropertyType.eUint32Array].m_derializeFuncKeyWord = "readUnsignedInt32"


    def __init__(self, params):
        '''
        Constructor
        '''

        