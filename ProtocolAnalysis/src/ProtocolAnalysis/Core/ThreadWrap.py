#-*- encoding=utf-8 -*-

from threading import Thread

class ThreadWrap(Thread):
    
    def __init__(self, threadName):
        super(ThreadWrap, self).__init__(name = threadName)  # must add

    def run(self):
        pass;
