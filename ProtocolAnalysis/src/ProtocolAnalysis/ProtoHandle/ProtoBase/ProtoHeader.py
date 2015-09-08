#-*- encoding=utf-8 -*-


from ProtocolAnalysis.ProtoHandle.ProtoBase.ProtoElemBase import ProtoElemBase, eProtoElemType


class ProtoHeader(ProtoElemBase):
    '''
    classdocs
    '''


    def __init__(self):
        '''
        Constructor
        '''
        super(ProtoHeader, self).__init__(eProtoElemType.eHeader)
        
        self.m_headerList = []
        self.m_commentStr = ""


    def parse(self, tokenParseBuffer):
        super(ProtoHeader, self).parse(tokenParseBuffer)

        line = tokenParseBuffer.getLineNoRemove()       # 注释可能在一行的结尾
        hasComment = (line.find("//") != -1)
        
        tokenParseBuffer.getTokenAndRemove()  # "header"
        headerStr = tokenParseBuffer.getTokenAndRemove()  # ""aaa/bbb.h","dddd/gggg.h";"
        
        if headerStr.find(";") != -1:     # 如果数字后面的分号一起取出来，中间没有空格
            headerStr = headerStr[:len(headerStr) - 1]
        else: 
            tokenParseBuffer.getTokenAndRemove()        # 移除 ";"
            
        self.m_headerList = headerStr.split(",")
            
        if hasComment:
            self.m_commentStr = tokenParseBuffer.getLineRemove()

    
    def getHeaderList(self):
        return self.m_headerList
    
    
    def getCommentStr(self):
        return self.m_commentStr
    
