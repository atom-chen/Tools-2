#-*- encoding=utf-8 -*-


from threading import Thread


class ThreadWrap(Thread):
    '''
    classdocs
    '''


    def __init__(self, threadName, func):
        super(ThreadWrap, self).__init__(name = threadName)  # must add
        self.m_runF = func
        self.m_bRuning = False


    def start(self):
        self.m_bRuning = True
        super(ThreadWrap, self).start()


    def run(self):
        if self.m_runF is not None:
            self.m_runF()


    def isRuning(self):
        #return self.m_bRuning
        return self.is_alive()
    
    
    def endRun(self):
        self._stop()
        self.m_bRuning = False


