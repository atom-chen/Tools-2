#-*- encoding=utf-8 -*-

import multiprocessing;
import time;
    
class MProcessExt(multiprocessing.process):
    '''
    classdocs
    '''

    def __init__(self, processName, func):
        '''
        Constructor
        '''
        super(MProcessExt, self).__init__(name=processName, target = self.run);
        self.mRunF = func;
        self.mPid = self.pid;
        
    def run(self):
        if self.mRunF is not None:
            self.mRunF();
            time.sleep(10);


