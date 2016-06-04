#-*- encoding=utf-8 -*-

import multiprocessing
import time
    
class MProcessExt(multiprocessing.process):
    '''
    classdocs
    '''

    def __init__(self, processName, func):
        '''
        Constructor
        '''
        super(MProcessExt, self).__init__(name=processName, target = self.run);
        self.m_runF = func;
        self.m_pid = self.pid;
        
    def run(self):
        if self.m_runF is not None:
            self.m_runF();
            time.sleep(10);


