# -*- coding: utf-8 -*-

  

class TestFuncPtr(object):
    '''
    classdocs
          测试函数指针
    '''


    def __init__(self):
        '''
        Constructor
        '''
        
        
    def funcHandle(self, hello):
        print("funcHandle called")
        
        
    @staticmethod
    def staticFuncHandle(self, hello):
        print("hello")
        

class TestFuncObj(object):
    
    def __init__(self):
        self.m_obj = None
        self.m_funcPtr = None
        self.m_sFuncPtr = None
    

    def run(self):
        self.m_obj = TestFuncPtr()
        self.m_funcPtr = self.m_obj.funcHandle
        
        #self.m_funcPtr(self.m_obj, "hello")
        
        self.m_sFuncPtr = TestFuncPtr.staticFuncHandle
        self.m_sFuncPtr(self.m_obj, "hello")




