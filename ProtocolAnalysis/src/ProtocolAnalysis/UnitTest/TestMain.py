# -*- coding: utf-8 -*-


from ProtocolAnalysis.UnitTest.TestFor import TestFor
from ProtocolAnalysis.UnitTest.TestInternalFunc import TestInternalFunc


class TestMain(object):
    '''
    classdocs
          测试 入口
    '''


    def __init__(self):
        '''
        Constructor
        '''
        self.m_testFor = TestFor()
        self.m_testInternalFunc = TestInternalFunc()
        

    def run(self):
        self.m_testFor.run()
        self.m_testInternalFunc.run()
        self.m_testInternalFunc = None     # __del__ 测试，可以调用
        #self.m_testInternalFunc.dispose()   # __del__ 测试，不能调用
    
    

if __name__ == "__main__":
    testMain = TestMain()
    testMain.run();