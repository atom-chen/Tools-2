# -*- coding: utf-8 -*-


from ProtocolAnalysis.Core.Utils import Utils


class TestInternalFunc(object):
    '''
    classdocs
    '''

    def run(self):
        self.staticHello(None)
        self.clsHello(None)
        self.selfHello(None)
        
        len(self)               # __len__ 测试
        
        self.testAtt            # __getattr__ 测试
        self.testAtt = "new"    # __setattr__ 测试
        
        self["testAtt"]         # __getitem__ 测试
        self["testAtt"] = "key" # __setitem__ 测试
        
        del self.m_testAtt  # 删除属性测试
        #del self # 删除自己测试 这样不会调用 __del__ 函数


    # 实例的生成操作
    def __new__(cls, *args, **kwd):         # 在__init__之前调用
        print("__new__  is called")
        ins = object.__new__(cls, *args, **kwd)
        return ins


    # 初始化对象，在创建新对象时调用
    def __init__(self):
        '''
        Constructor
        '''
        print("__init__  is called")
        self.m_testAtt = "nihao"
        
    
    # 释放对象，在对象被删除之前调用
    def __del__(self):
        print("__del__  is called")
        
    
    def __len__(self):
        print("__len__  is called")
        return 0        # 这个一定要返回值，否则报错
    
    
    # 成员函数访问的时候会调用，数据成员访问的时候也会调用    
    def __getattribute__(self, *args, **kwargs):
        print("__getattribute__() is called")
        return object.__getattribute__(self, *args, **kwargs)
    
    
    # 成员函数访问的时候不会调用，数据成员访问的时候会调用
    def __getattr__(self, name):
        print("__getattr__() is called ")  
        attrName = Utils.addMemberPrefix(name)
        #if self.__dict__.has_key(attrName):      # __dict__ 没有 has_key 属性
        #    return self.__dict__[attrName]
        #else:
        #    return None
        return self.__dict__[attrName]
        

    def __setattr__(self, name, value):
        print("__setattr__() is called ")
        
        attrName = Utils.addMemberPrefix(name)
        self.__dict__[attrName] = value
        
        
    def __delattr__(self, name):
        print("__delattr__() is called ")
        object.__delattr__(self, name)
        
        
    def __getitem__(self, key):
        print("__getitem__() is called ")
        attrName = Utils.addMemberPrefix(key)
        #if self.__dict__.has_key(attrName):     # AttributeError: 'dict' object has no attribute 'has_key'
        #    return self.__dict__[attrName]
        return self.__dict__[attrName]
        
        return None
    

    def __setitem__(self, key, value):
        print("__setitem__() is called ")
        attrName = Utils.addMemberPrefix(key)
        self.__dict__[attrName] = value;
        
        
    def dispose(self):
        self = None
        

    @staticmethod
    def staticHello(hello):
        print("@staticmethod is called ")
        if not hello:
            hello='hello'
        print(hello)


    @classmethod
    def clsHello(cls, hello):
        print("@classmethod is called ")
        cls.staticHello(hello)
        print("from introduce method")


    def selfHello(self, hello):
        print("@self is called ")
        self.staticHello(hello)
        print("from hello method")

