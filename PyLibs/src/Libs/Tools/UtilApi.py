# -*- coding: utf-8 -*-

'''
@brief: UtilApi
'''

import time;
import types;
import os;
from Libs.Core.GObject import GObject;

class UtilApi(GObject):
    
    @staticmethod
    def isAddressEqual(a, b):
        return a == b;
        
    
    @staticmethod
    def getTotalSeconds():
        return time.time();
    
    
    @staticmethod
    def isinstance(varName, typeProto):
        return isinstance(varName, typeProto);
    
    
    # 对于subclass之类的 type 就不行.所以,强烈建议不要使用type判断对象类型
    @staticmethod
    def isType(varName, typeProto):
        return (type(varName) == typeProto)
    
    
    
    @staticmethod
    def getpid():
        return os.getpid();
    
    
