#-*- encoding=utf-8 -*-

'''
@brief: 测试 EventDispatch
'''

from Libs.Core.GObject import GObject;
from Libs.EventHandle.AddOnceAndCallOnceEventDispatch import AddOnceAndCallOnceEventDispatch;

class TestEventDispatch(GObject):
    
    def __init__(self):
        super(TestEventDispatch, self).__init__();
        
        self.mTypeId = "TestEventDispatch";
        
    
    def run(self):
        self.testDisp();
    
    
    def testDisp(self):
        disp = AddOnceAndCallOnceEventDispatch();
        disp.addEventHandle(self, self.onCalled);
        disp.dispatchEvent(self);
        
    
    def onCalled(self, dispObj):
        print("over");
        

