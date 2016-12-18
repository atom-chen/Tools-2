#-*- encoding=utf-8 -*-

from threading import Thread;

class MThreadExt(Thread):
    
    def __init__(self, threadName, func):
        super(MThreadExt, self).__init__(name = threadName);  # must add
        self.mRunF = func;

    def run(self):
        if self.mRunF is not None:
            self.mRunF();


