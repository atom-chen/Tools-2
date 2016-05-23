#-*- encoding=utf-8 -*-

'''
@brief: 字符串工具
'''
class UtilStr(object):
    
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


































