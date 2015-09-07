#-*- encoding=utf-8 -*-


from ProtocolAnalysis.ProtoHandle.ProtoBase.ProtoElemBase import ProtoElemBase, eProtoElemType


class ProtoPackage(ProtoElemBase):
    '''
    classdocs
    '''


    def __init__(self):
        '''
        Constructor
        '''
        super(ProtoPackage, self).__init__(eProtoElemType.ePackage)


    def parse(self, tokenParseBuffer):
        self.m_typeKeyWord = tokenParseBuffer.getTokenAndRemove()  # "package"
        self.m_typeName = tokenParseBuffer.getTokenAndRemove() # "stTest"
        
        if self.m_typeName.find(";") != -1:     # 如果数字后面的分号一起取出来，中间没有空格
            self.m_seqValue = self.m_seqValue[:len(self.m_typeName) - 1]
        else: 
            tokenParseBuffer.getTokenAndRemove()        # 移除 ";"
        
