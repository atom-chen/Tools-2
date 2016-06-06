# -*- coding: utf-8 -*-

'''
@brief: 多处理器 
'''

import multiprocessing;
import time;
from Libs.Core.GObject import GObject;

class MProcess(GObject):
    '''
    classdocs
    '''

    def __init__(self, processName = "", func = None):
        '''
        Constructor
        '''
        super(MProcess, self).__init();
        
        self.mTypeId = "MProcess";
        
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


