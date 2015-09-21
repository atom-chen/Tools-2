#-*- encoding=utf-8 -*-


from ProtocolAnalysis.ProtoHandle.ProtoBase.ProtoTypeMemberBase import PropertyType
from ProtocolAnalysis.ProtoHandle.ProtoBase.ProtoKeyWord import ProtoKeyWord



class PropertyData(object):
    '''
    classdocs
    '''
    
    
    def __init__(self):
        '''
        Constructor
        '''
        self.m_propertyType = 0    # 属性类型
        
        
    def getProtertyType(self):
        return self.m_propertyType
    
    
    # 生成数组的关键字
    @staticmethod
    def createTypeArrKeyWord(key_):
        return "{0}_{1}".format(key_, "Array")



# 属性关键字到属性的一些映射
class ProtoPropertyTypeKeyWord2Property(object):
    '''
    classdocs
    '''
    m_sKeyWord2PropertyData = {}
    m_sKeyWord2PropertyData[ProtoKeyWord.eInt8] = PropertyData()
    m_sKeyWord2PropertyData[ProtoKeyWord.eInt8].m_propertyType = PropertyType.eInt8
    
    m_sKeyWord2PropertyData[ProtoKeyWord.eUint8] = PropertyData()
    m_sKeyWord2PropertyData[ProtoKeyWord.eUint8].m_propertyType = PropertyType.eUint8
    
    m_sKeyWord2PropertyData[ProtoKeyWord.eInt16] = PropertyData()
    m_sKeyWord2PropertyData[ProtoKeyWord.eInt16].m_propertyType = PropertyType.eInt16
    
    m_sKeyWord2PropertyData[ProtoKeyWord.eUInt16] = PropertyData()
    m_sKeyWord2PropertyData[ProtoKeyWord.eUInt16].m_propertyType = PropertyType.eUInt16
    
    m_sKeyWord2PropertyData[ProtoKeyWord.eInt32] = PropertyData()
    m_sKeyWord2PropertyData[ProtoKeyWord.eInt32].m_propertyType = PropertyType.eInt32
    
    m_sKeyWord2PropertyData[ProtoKeyWord.eUInt32] = PropertyData()
    m_sKeyWord2PropertyData[ProtoKeyWord.eUInt32].m_propertyType = PropertyType.eUInt32
    
    m_sKeyWord2PropertyData[PropertyData.createTypeArrKeyWord(ProtoKeyWord.eInt8)] = PropertyData()
    m_sKeyWord2PropertyData[PropertyData.createTypeArrKeyWord(ProtoKeyWord.eInt8)].m_propertyType = PropertyType.eInt8Array
    
    m_sKeyWord2PropertyData[PropertyData.createTypeArrKeyWord(ProtoKeyWord.eUint8)] = PropertyData()
    m_sKeyWord2PropertyData[PropertyData.createTypeArrKeyWord(ProtoKeyWord.eUint8)].m_propertyType = PropertyType.eUInt8Array
    
    m_sKeyWord2PropertyData[PropertyData.createTypeArrKeyWord(ProtoKeyWord.eInt16)] = PropertyData()
    m_sKeyWord2PropertyData[PropertyData.createTypeArrKeyWord(ProtoKeyWord.eInt16)].m_propertyType = PropertyType.eInt16Array
    
    m_sKeyWord2PropertyData[PropertyData.createTypeArrKeyWord(ProtoKeyWord.eUInt16)] = PropertyData()
    m_sKeyWord2PropertyData[PropertyData.createTypeArrKeyWord(ProtoKeyWord.eUInt16)].m_propertyType = PropertyType.eUInt16Array
    
    m_sKeyWord2PropertyData[PropertyData.createTypeArrKeyWord(ProtoKeyWord.eInt32)] = PropertyData()
    m_sKeyWord2PropertyData[PropertyData.createTypeArrKeyWord(ProtoKeyWord.eInt32)].m_propertyType = PropertyType.eInt32Array
    
    m_sKeyWord2PropertyData[PropertyData.createTypeArrKeyWord(ProtoKeyWord.eUInt32)] = PropertyData()
    m_sKeyWord2PropertyData[PropertyData.createTypeArrKeyWord(ProtoKeyWord.eUInt32)].m_propertyType = PropertyType.eUInt32Array
    
    m_sKeyWord2PropertyData[ProtoKeyWord.eBase] = PropertyData()
    m_sKeyWord2PropertyData[ProtoKeyWord.eBase].m_propertyType = PropertyType.eBase


    def __init__(self):
        '''
        Constructor
        '''

    
    
    