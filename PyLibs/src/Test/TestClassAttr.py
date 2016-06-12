# -*- coding: utf-8 -*-

'''
@brief: lvguanghai
'''

from Libs.Core.GObject import GObject

class A(GObject):
    
    def __init__(self):
        super(A, self).__init__();
        
        self.mTypeId = "A";
        
        self.mAttra = "aaa";


class TestClassAttr(GObject):
    
    def __init__(self):
        super(TestClassAttr, self).__init__();
        
        self.mTypeId = "TestClassAttr";


    def run(self):
        self.testClassAttr();
    
    
    def testClassAttr(self):
        a1 = A;
        a1.mAttra = "a1";
        
        a2 = A;
        a2.mAttra = "a2";
        
        a3 = A;
        a3.mAttra = "a3";
        
        a4 = A;
        a4.mAttra = "a4";
        
        print(a4.mAttra);
        
        


