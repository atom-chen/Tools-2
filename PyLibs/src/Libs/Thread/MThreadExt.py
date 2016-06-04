#-*- encoding=utf-8 -*-

from threading import Thread

class MThreadExt(Thread):
    
    def __init__(self, threadName, func):
        super(MThreadExt, self).__init__(name = threadName);  # must add
        self.m_runF = func;

    def run(self):
        if self.m_runF is not None:
            self.m_runF();


