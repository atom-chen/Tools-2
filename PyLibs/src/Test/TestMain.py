#-*- encoding=utf-8 -*-

'''
@brief: TestMain
'''

from Libs.Core.GObject import GObject;
from Test.TestEventDispatch import TestEventDispatch;
from Test.TestDataStruct import TestDataStruct;
from Test.TestUtil import TestUtil;
from Test.TestRef import TestRef;
from Test.TestClassAttr import TestClassAttr;
from Test.TestPath import TestPath;
from Test.TestStr import TestStr;

class TestMain(GObject):
    
    def __init__(self):
        super(TestMain, self).__init__();
        
        self.mTypeId = "TestMain";
        
        self.mTestEventDispatch = TestEventDispatch();
        self.mTestDataStruct = TestDataStruct();
        self.mTestUtil = TestUtil();
        self.mTestRef = TestRef();
        self.mTestClassAttr = TestClassAttr();
        self.mTestPath = TestPath();
        self.mTestStr = TestStr();
        
    
    def run(self):
        #self.mTestEventDispatch.run();
        #self.mTestDataStruct.run();
        #self.mTestUtil.run();
        #self.mTestRef.run();
        #self.mTestClassAttr.run();
        #self.mTestPath.run();
        self.mTestStr.run();



testMain = TestMain();

testMain.run();

