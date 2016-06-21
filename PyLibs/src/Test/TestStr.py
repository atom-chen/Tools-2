#-*- encoding=utf-8 -*-

from Libs.Core.GObject import GObject

class TestStr(GObject):
    
    def __init__(self):
        super(TestStr, self).__init__();
        
        self.mTypeId = "TestUtil";


    def run(self):
        self.test();


    def test(self):
        srcStr = "abcd";
        destStr = srcStr[0:2];
        print(destStr);
    
    