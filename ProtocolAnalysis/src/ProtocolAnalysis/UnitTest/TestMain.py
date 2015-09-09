# -*- coding: utf-8 -*-


from ProtocolAnalysis.UnitTest.TestFor import TestFor
from ProtocolAnalysis.UnitTest.TestInternalFunc import TestInternalFunc


class TestMain(object):
    '''
    classdocs
          测试 入口
    '''


    def __init__(self, params):
        '''
        Constructor
        '''
        self.m_testFor = TestFor()
        self.m_testInternalFunc = TestInternalFunc()
        
        self.run()
        

    def run(self):
        self.testFor.run()
        self.m_testInternalFunc.run()
    
    

if __name__ == "__main__":
    testMain = TestMain()
    testMain.run();