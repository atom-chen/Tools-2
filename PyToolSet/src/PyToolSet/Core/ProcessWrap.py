#-*- encoding=utf-8 -*-

import multiprocessing
    
class ProcessWrap(multiprocessing.process):
    '''
    classdocs
    '''

    def __init__(self, processName, func):
        '''
        Constructor
        '''
        super(ProcessWrap, self).__init__(name=processName, target = self.run);
        self.m_runF = func
        self.m_pid = self.pid
        
    def run(self):
        if self.m_runF is not None:
            self.m_runF()


