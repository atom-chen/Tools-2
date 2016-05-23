#-*- encoding=utf-8 -*-

'''
@brief: 字符串工具
'''
class UtilStr(object):
    
    @staticmethod
    def startswith(srcStr, subStr, beg, end):
        if(beg == None):
            beg = 0;
        if(end == None):
            end = len(srcStr);
        return srcStr.startswith(subStr, beg, end);
    
    
    @staticmethod
    def isEmptyOrNull(srcStr):
        if(srcStr == None or len(srcStr) == 0):
            return True;
        
        return False;

