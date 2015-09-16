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
        self.m_bRuning = False

    
        # 重载进程的启动，以便设置值，防止互斥操作
    def start(self):
        self.m_bRuning = True
        super(ProcessWrap, self).start()

        
    def run(self):
        if self.m_runF is not None:
            self.m_runF()
            
        self.m_bRuning = False
            

    def isRuning(self):
        return self.m_bRuning
    
    
    


