#-*- encoding=utf-8 -*-


class TokenParseBuffer(object):
    '''
    classdocs
    '''


    def __init__(self):
        '''
        Constructor
        '''
        self.m_fileBytes = ""       # 整个 Proto 的内容
        self.m_curPos = 0           # 当前读写位置
        
    def openFile(self, fileName):
        with open(fileName, 'r', encoding = 'utf8') as fHandle:
            self.m_fileBytes = fHandle.read()
            self.m_curPos = 0


    def isEOF(self):
        return self.m_curPos == len(self.m_fileBytes) 
    
    
    # 从字符串的左边获取一个符号，并且删除这个符号
    def getTokenAndRemove(self):
        self.skipSpaceBrTab()
        
        idx = 0;
        ret = ''
        while idx < len(self.m_fileBytes):
            if self.m_fileBytes[idx] == ' ' or self.m_fileBytes[idx] == '\n' or self.m_fileBytes[idx] == '\t':       # 如果遇到空格或者换行符，就算是一个符号
                break 
            ret += self.m_fileBytes[idx]
            idx += 1
            
        if len(ret):
            self.m_fileBytes = self.m_fileBytes[idx:]         # 删除内容
            
        self.skipSpaceBrTab()
        
        return ret


    # 获取一个符号，但是不从缓冲区中移除符号
    def getTokenAndNoRemove(self):
        curPos_ = self.m_curPos         # 记录当前位置
        
        self.skipSpaceBrTab()
        
        idx = 0;
        ret = ''
        while idx < len(self.m_fileBytes):
            if self.m_fileBytes[idx] == ' ' or self.m_fileBytes[idx] == '\n' or self.m_fileBytes[idx] == '\t':       # 如果遇到空格或者换行符，就算是一个符号
                break 
            ret += self.m_fileBytes[idx]
            idx += 1
            
        self.skipSpaceBrTab()
        
        self.m_curPos = curPos_
        
        return ret
        

    # 移除一个符号，并且返回符号长度
    def removeOneToken(self):
        self.skipSpaceBrTab()
        
        idx = 0;
        ret = ''
        while idx < len(self.m_fileBytes):
            if self.m_fileBytes[idx] == ' ' or self.m_fileBytes[idx] == '\n' or self.m_fileBytes[idx] == '\t':       # 如果遇到空格或者换行符，就算是一个符号
                break 
            ret += self.m_fileBytes[idx]
            idx += 1
            
        if len(ret):
            self.m_fileBytes = self.m_fileBytes[idx:]         # 删除内容
            
        self.skipSpaceBrTab()
        
        return len(ret) 


    # 跳过当前行
    def skipCurLine(self):
        idx = 0;
        while idx < len(self.m_fileBytes):
            if self.m_fileBytes[idx] == '\n':
                break;
            idx += 1

        self.m_curPos += idx
        

    # 跳过空格和换行
    def skipSpaceBrTab(self):
        idx = 0;
        while idx < len(self.m_fileBytes):
            if self.m_fileBytes[idx] != ' ' and self.m_fileBytes[idx] != '\n' and self.m_fileBytes[idx] != '\t':       # 如果遇到空格或者换行符，就算是一个符号
                break;
            idx += 1

        self.m_curPos += idx

    
    def skipSpace(self):
        idx = 0;
        while idx < len(self.m_fileBytes):
            if self.m_fileBytes[idx] != ' ':
                break;
            idx += 1
            
        self.m_curPos += idx
    
    
    def skipBr(self):
        idx = 0;
        while idx < len(self.m_fileBytes):
            if self.m_fileBytes[idx] != '\n':
                break;
            idx += 1
            
        self.m_curPos += idx        
    
    
    def skipTab(self):
        idx = 0;
        while idx < len(self.m_fileBytes):
            if self.m_fileBytes[idx] != '\t':
                break;
            idx += 1
            
        self.m_curPos += idx
        
        
    def getLineNoRemove(self):
        idx = 0;
        ret = ""
        while idx < len(self.m_fileBytes):
            if self.m_fileBytes[idx] == '\n':
                break;
            ret += self.m_fileBytes[idx]
            idx += 1

        
        return ret

