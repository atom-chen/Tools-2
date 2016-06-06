# -*- coding: utf-8 -*-

'''
@brief 多处理器
@brief 主要代码都在 multiprocessing.process.BaseProcess
'''

import multiprocessing;
import time;
from Libs.Core.GObject import GObject;

class MProcess(GObject):
    '''
    classdocs
    '''

    def __init__(self, params = None, processName = "", func = None):
    #def __init__(self, processName = "", func = None):
        '''
        Constructor
        '''
        super(MProcess, self).__init__();
        
        self.mTypeId = "MProcess";
        
        #self.mManager = multiprocessing.Manager();
        #self.mParam = self.mManager.Value('params', params);
        
        self.mParam = params;
        self.mProcessName = processName;
        self.m_runF = func;
        self.m_pid = 0;
        self.mProcessHandle = None;
        
    
    def setInfo(self, info):
        self.mInfo = info;
        
        
    def isValid(self):
        return self.mProcessHandle != None;
        
    
    def start(self):
        if(self.mProcessHandle == None):
            self.mProcessHandle = multiprocessing.Process(
                                                          target = self.run, 
                                                          args = (self.mParam, ), 
                                                          name = self.mProcessName
                                                          );

            self.mProcessHandle.start();
            self.m_pid = self.getIdent();
            
            
    def terminate(self):
        self.mProcessHandle.terminate();
        
        
    def join(self, timeout=None):
        self.mProcessHandle.terminate(timeout);
        
    
    def is_alive(self):
        self.mProcessHandle.is_alive();
        

    def getName(self):
        return self.mProcessHandle.name;
    
    
    def setName(self, name):
        self.mProcessHandle.name = name;
        
        
    def getDaemon(self):
        return self.mProcessHandle.daemon;
    
    # 守护进程就是不阻挡主程序退出，自己干自己的 mutilprocess.setDaemon(True)
    def setDaemon(self, daemonic):
        self.mProcessHandle.daemon = daemonic;
        
        
    def getExitcode(self):
        return self.mProcessHandle.exitcode;
    
    # 这个一定要在调用 start 函数后面才能获取，否则返回值是 None
    def getIdent(self):
        return self.mProcessHandle.ident;

        
    def run(self, params):
        if self.m_runF is not None:
            self.m_runF();
            time.sleep(10);


    @staticmethod
    def current_process():
        return multiprocessing.current_process();



