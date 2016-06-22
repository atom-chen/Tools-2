#-*- encoding=utf-8 -*-

'''
@brief: 
'''

from Libs.Core.GObject import GObject;

class RefObject(GObject):
    
    def __init__(self):
        super(RefObject, self).__init__();
        
        self.mTypeId = "RefObject";
        
        self.mId = 10;

class TestRef(GObject):
    
    def __init__(self):
        super(TestRef, self).__init__();
        
        self.mTypeId = "TestRef";
    

    def run(self):
        self.testRef();
    
    
    
    def testRef(self):
        refObj = RefObject();
        self.deliverRef(refObj);
        
        print(refObj.mId);
    
    
    def deliverRef(self, refObj):
        refObj.mId = 100;
        
        
    
    
