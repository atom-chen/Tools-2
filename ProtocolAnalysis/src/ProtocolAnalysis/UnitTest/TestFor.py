# -*- coding: utf-8 -*-


class TestFor(object):
    '''
    classdocs
          测试 for
    '''


    def __init__(self):
        '''
        Constructor
        '''
    
    def run(self):
        self.testFor()
    
    
    '''
          顺便提一下range()函数。
    range([start,] stop [, step])
    # start  可选参数，起始数
          ＃stop   终止数，如果 range 只有一个参数x，则产生一个包含 0 至 x-1 的整数列表
          ＃step   可选参数，步长
    '''
    def testFor(self):
        print("输出结果: ")
        for i in range(0, 10, 1):
            print(i)        # 输出结果: 0 1 2 3 4 5 6 7 8 9  
        
    
    
    