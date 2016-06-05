#-*- encoding=utf-8 -*-

'''
@brief: 多处理器 
'''
#-*- encoding=utf-8 -*-

import multiprocessing

from Libs.Core import GObject
import time
    
class MProcess(GObject):
    '''
    classdocs
    '''

    def __init__(self, processName, func):
        '''
        Constructor
        '''
        self.mProcessName = processName;
        self.m_runF = func;
        self.m_pid = 0;
        self.mProcessHandle = None;
        
    
    def start(self):
        if(self.mProcessHandle == None):
            self.mProcessHandle = multiprocessing.process(
                                                          target = self.run, 
                                                          args = (15, ), 
                                                          name = self.mProcessHandle
                                                          );            
        self.m_pid = self.pid;
        self.mProcessHandle.start();
        
        
    def run(self, params):
        if self.m_runF is not None:
            self.m_runF();
            time.sleep(10);


