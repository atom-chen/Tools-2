# -*- coding: utf-8 -*-


from ProtocolAnalysis.UnitTest.TestFor import TestFor


class TestMain(object):
    '''
    classdocs
          测试 入口
    '''


    def __init__(self, params):
        '''
        Constructor
        '''
        self.testFor = TestFor()
        
        self.run()
        

    def run(self):
        self.testFor.run()
    
    

if __name__ == "__main__":
    testMain = TestMain()
    testMain.run();