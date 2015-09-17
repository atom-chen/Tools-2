#-*- encoding=utf-8 -*-


import multiprocessing
from ProtocolAnalysis.Core.AppSysBase import AppSysBase


#class ProcessWrap(multiprocessing.process):         # 这样继承之前是没有问题的，但是现在就有问题了
#class ProcessWrap(object):
class ProcessWrap(multiprocessing.context.Process):
    '''
    classdocs
    '''

    def __init__(self, processName, func):
        '''
        Constructor
        '''
        super(ProcessWrap, self).__init__(name = processName, target = self.run, args = (AppSysBase.instance(),));
        #self.m_process = multiprocessing.context.Process(name = processName, target = processRun, args = (self,))
        self.m_runF = func
        self.m_pid = self.pid
        #self.m_pid = self.m_process.pid
        self.m_bRuning = False
        #self.m_gAppSys = AppSysBase.instance()


        # 重载进程的启动，以便设置值，防止互斥操作
    def start(self):
        self.m_bRuning = True
        super(ProcessWrap, self).start()
        #self.m_process.start()
        

        
    def run(self, gAppSys):
        self.m_gAppSys = gAppSys
        if self.m_runF is not None:
            self.m_runF()
            
        self.m_bRuning = False
            

    def isRuning(self):
        return self.m_bRuning
    

# 子进程入口函数
def processRun(pSelf):
        pSelf.run()
    
    
    


