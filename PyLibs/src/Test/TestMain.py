#-*- encoding=utf-8 -*-

'''
@brief: TestMain
'''

from Libs.Core.GObject import GObject
from Test.TestEventDispatch import TestEventDispatch

class TestMain(GObject):
    
    def __init__(self):
        super(TestMain, self).__init__();
        
        self.mTypeId = "TestMain";
        
        self.mTestEventDispatch = TestEventDispatch();
        
    
    def run(self):
        self.mTestEventDispatch.run();



testMain = TestMain();

testMain.run();

