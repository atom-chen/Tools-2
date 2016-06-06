#-*- encoding=utf-8 -*-

'''
@brief: TestMain
'''

from Libs.Core.GObject import GObject
from Test.TestEventDispatch import TestEventDispatch
from Test.TestDataStruct import TestDataStruct
from Test.TestUtil import TestUtil

class TestMain(GObject):
    
    def __init__(self):
        super(TestMain, self).__init__();
        
        self.mTypeId = "TestMain";
        
        self.mTestEventDispatch = TestEventDispatch();
        self.mTestDataStruct = TestDataStruct();
        self.mTestUtil = TestUtil();
        
    
    def run(self):
        self.mTestEventDispatch.run();
        self.mTestDataStruct.run();
        self.mTestUtil.run();



testMain = TestMain();

testMain.run();

