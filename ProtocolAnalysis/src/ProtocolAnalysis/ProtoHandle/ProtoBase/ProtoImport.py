#-*- encoding=utf-8 -*-


from ProtocolAnalysis.ProtoHandle.ProtoBase.ProtoElemBase import ProtoElemBase, eProtoElemType


class ProtoImport(ProtoElemBase):
    '''
    classdocs
    '''


    def __init__(self):
        '''
        Constructor
        '''
        super(ProtoImport, self).__init__(eProtoElemType.eImport)
        
        self.m_headerList = []
        self.m_commentStr = ""



    def parse(self, tokenParseBuffer):
        super(ProtoImport, self).parse(tokenParseBuffer)

        line = tokenParseBuffer.getLineNoRemove()       # 注释可能在一行的结尾
        hasComment = (line.find("//") != -1)
        
        tokenParseBuffer.getTokenAndRemove()  # "header"
        importStr = tokenParseBuffer.getTokenAndRemove()  # ""aaa/bbb.h","dddd/gggg.h";"
        
        if importStr.find(";") != -1:     # 如果数字后面的分号一起取出来，中间没有空格
            importStr = importStr[:len(importStr) - 1]
        else: 
            tokenParseBuffer.getTokenAndRemove()        # 移除 ";"
            
        self.m_headerList = importStr.split(",")
            
        if hasComment:
            self.m_commentStr = tokenParseBuffer.getLineRemove()

    
    def getHeaderList(self):
        return self.m_headerList
    
    
    def getCommentStr(self):
        return self.m_commentStr


        