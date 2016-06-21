#-*- encoding=utf-8 -*-

import re
from Libs.Core.GObject import GObject

'''
@brief: 字符串工具
'''
class UtilStr(GObject):
    
    @staticmethod
    def len(srcStr):
        return len(srcStr);
    
    @staticmethod
    def max(srcStr):
        return max(srcStr);
        
    @staticmethod
    def min(srcStr):
        return min(srcStr);
    
    
    @staticmethod
    def cmp(stra, strb):
        #return cmp(stra, strb);
        pass;
    
    @staticmethod
    def truncate(stra, start = None, end = None):
        if(start != None and end != None):
            return stra[start:end];
        elif(start != None and end == None):
            return stra[start:];
        elif(start == None and end != None):
            return stra[:end];
    
    
    @staticmethod
    def isInStr(stra, strb):
        return stra in strb;
        

    @staticmethod
    def isNotInStr(stra, strb):
        return stra not in strb;
    
    
    # 可指范围查找子串，返回索引值，否则返回-1
    @staticmethod
    def find(srcStr, subStr, start = 0, end = 0):
        if(end == 0):
            end = len(srcStr);
        return srcStr.find(subStr, start , end);
    
    # 反向查找
    @staticmethod
    def rfind(srcStr, subStr, start = 0, end = 0):
        if(end == 0):
            end = len(srcStr);
        return srcStr.rfind(subStr, start , end);
    

    # 同find，只是找不到产生ValueError异常
    @staticmethod
    def index(srcStr, subStr, start = 0, end = 0):
        if(end == 0):
            end = len(srcStr);
        return srcStr.index(subStr, start , end);
        
    # 同上反向查找
    @staticmethod
    def rindex(srcStr, subStr, start = 0, end = 0):
        if(end == 0):
            end = len(srcStr);
        return srcStr.rindex(subStr, start , end);
        
        
    # 返回找到子串的个数
    @staticmethod
    def count(srcStr, subStr, start = 0, end = 0):
        if(end == 0):
            end = len(srcStr);
        return srcStr.count(subStr, start ,end);
        
        
    @staticmethod
    def lowercase(srcStr):
        return srcStr.lowercase();
    
    
    # 首字母大写
    @staticmethod
    def capitalize(srcStr):
        return srcStr.capitalize();
        

    # 转小写
    @staticmethod
    def lower(srcStr):
        return srcStr.lower();
        
    #转大写
    @staticmethod
    def upper(srcStr):
        return srcStr.upper();    
    
    
    #大小写互换
    @staticmethod
    def swapcase(srcStr):    
        return srcStr.swapcase();    

    
    #将string转list，以空格切分
    @staticmethod
    def split(srcStr, splitStr):
        return srcStr.split(splitStr);


    #将list转string，以空格连接
    @staticmethod
    def join(sreStr, lst):
        return sreStr.join(lst, ' ');
            
    
    @staticmethod
    def startswith(srcStr, subStr, beg = 0, end = 0):
        if(beg == None):
            beg = 0;
        if(end == 0 or end == None):
            end = len(srcStr);

        if(UtilStr.isEmptyOrNull(subStr) or UtilStr.isEmptyOrNull(srcStr)):
            return False;
        
        return srcStr.startswith(subStr, beg, end);
    
    
    @staticmethod
    def isEmptyOrNull(srcStr):
        if(srcStr == None or len(srcStr) == 0):
            return True;
        
        return False;

    @staticmethod
    def format(formatStr, var0, var1 = None, var2 = None, var3 = None, var4 = None, var5 = None, var6 = None, var7 = None, var8 = None, var9 = None):
        if(var0 != None and var1 != None and var2 != None and var3 != None and var4 != None and var5 != None and var6 != None and var7 != None and var8 != None and var9 != None):
            return formatStr.format(var0, var1, var2, var3, var4, var5, var6, var7, var8, var9);
        elif(var0 != None and var1 != None and var2 != None and var3 != None and var4 != None and var5 != None and var6 != None and var7 != None and var8 != None):
            return formatStr.format(var0, var1, var2, var3, var4, var5, var6, var7, var8);
        elif(var0 != None and var1 != None and var2 != None and var3 != None and var4 != None and var5 != None and var6 != None and var7 != None):
            return formatStr.format(var0, var1, var2, var3, var4, var5, var6, var7);
        elif(var0 != None and var1 != None and var2 != None and var3 != None and var4 != None and var5 != None and var6 != None):
            return formatStr.format(var0, var1, var2, var3, var4, var5, var6);
        elif(var0 != None and var1 != None and var2 != None and var3 != None and var4 != None and var5 != None):
            return formatStr.format(var0, var1, var2, var3, var4, var5);
        elif(var0 != None and var1 != None and var2 != None and var3 != None and var4 != None):
            return formatStr.format(var0, var1, var2, var3, var4);
        elif(var0 != None and var1 != None and var2 != None and var3 != None):
            return formatStr.format(var0, var1, var2, var3);
        elif(var0 != None and var1 != None and var2 != None):
            return formatStr.format(var0, var1, var2);
        elif(var0 != None and var1 != None):
            return formatStr.format(var0, var1);
        elif(var0 != None):
            return formatStr.format(var0);
        else:
            return "";


    @staticmethod
    def replace(srcStr, findStr, replaceStr):
        return srcStr.replace(findStr, replaceStr);
    
    
    @staticmethod
    def replaceRex(srcStr, findStr, replaceStr):
        strinfo = re.compile(findStr);
        return strinfo.sub(replaceStr, srcStr);

