#-*- encoding=utf-8 -*-

'''
@brief: TestDataStruct 
'''

from Libs.Core.GObject import GObject;
from Libs.DataStruct.MList import MList;

class TestDataStruct(GObject):
    def __init__(self):
        super(TestDataStruct, self).__init__();
    
        self.mTypeId = "TestDataStruct";

    
    def run(self):
        self.testList();
    
    
    def testList(self):
        lst = MList();
        lst.Add(4);
        lst.Add(5);
        
        if(lst.IndexOf(2) != -1):
            print("aaa");
        else:
            print("bbb");
    
    
    