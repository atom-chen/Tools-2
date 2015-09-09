# -*- coding: utf-8 -*-


class TestInternalFunc(object):
    '''
    classdocs
    '''

    def run(self):
        pass


    # 实例的生成操作
    def __new__(cls, *args, **kwd):         # 在__init__之前调用
        print("__new__  is called")
        ins = object.__new__(cls, *args, **kwd)
        return ins


    # 初始化对象，在创建新对象时调用
    def __init__(self, params):
        '''
        Constructor
        '''
        print("__init__  is called")
        
    
    # 释放对象，在对象被删除之前调用
    def __del__(self):
        print("__del__  is called")
        
    
    def __len__(self):
        print("__len__  is called")
    
        
    def __getattribute__(self, *args, **kwargs):
        print("__getattribute__() is called")
        return object.__getattribute__(self, *args, **kwargs)
    
    
    def __getattr__(self, name):
        print("__getattr__() is called ")  
        attrName = "m_{0}".format(name)
        if self.__dict__.has_key(attrName):
            return self.__dict__[attrName]
        else:
            return None
        

    def __setattr__(self, name, value):
        print("__setattr__() is called ")
        attrName = "m_{0}".format(name)
        self.__dict__[attrName] = value
        
        
    def __delattr__(self, name):
        print("__delattr__() is called ")
        
        
    def __getitem__(self, key):
        print("__getitem__() is called ")
        attrName = "m_{0}".format(key)
        if self.__dict__.has_key(attrName):
            return self.__dict__[attrName]
        
        return None
    

    def __setitem__(self, key, value):
        print("__setitem__() is called ")
        attrName = "m_{0}".format(key)
        self.m_dict[attrName] = value;
        

    @staticmethod  
    def sayHello(hello):  
        if not hello:  
            hello='hello'  
        print(hello)
 
 
    @classmethod  
    def introduce(cls, hello):  
        cls.sayHello(hello)  
        print("from introduce method")  
  
    def hello(self, hello):
        self.sayHello(hello)  
        print("from hello method")

    
