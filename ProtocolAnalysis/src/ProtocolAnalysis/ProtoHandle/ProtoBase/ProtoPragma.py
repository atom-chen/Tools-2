# -*- coding: utf-8 -*-


from ProtocolAnalysis.ProtoHandle.ProtoBase.ProtoElemBase import ProtoElemBase, eProtoElemType


class ProtoPragma(ProtoElemBase):
    '''
    classdocs
    '''


    def __init__(self):
        '''
        Constructor
        '''
        super(ProtoPragma, self).__init__(eProtoElemType.ePragma)
        
        self.m_pragmaList = []
        self.m_commentStr = ""


    def parse(self, tokenParseBuffer):
        super(ProtoPragma, self).parse(tokenParseBuffer)

        line = tokenParseBuffer.getLineNoRemove()       # 注释可能在一行的结尾
        hasComment = (line.find("//") != -1)
        
        tokenParseBuffer.getTokenAndRemove()  # "pragma"
        pragmaStr = tokenParseBuffer.getTokenAndRemove()  # pack(1)
        
        if pragmaStr.find(";") != -1:     # 如果数字后面的分号一起取出来，中间没有空格
            pragmaStr = pragmaStr[:len(pragmaStr) - 1]
        else: 
            tokenParseBuffer.getTokenAndRemove()        # 移除 ";"
            
        self.m_pragmaList = pragmaStr.split(",")
            
        if hasComment:
            self.m_commentStr = tokenParseBuffer.getLineRemove()

    
    def getPragmaList(self):
        return self.m_pragmaList
    
    
    def getCommentStr(self):
        return self.m_commentStr
    
