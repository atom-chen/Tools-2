# -*- coding: utf-8 -*-

'''
@brief 锁操作
'''

from threading import Lock;
from Libs.Core.GObject import GObject;

class MLock(GObject):
    
    def __init__(self):
        super(MLock, self).__init__();
        
        self.mTypeId = "MLock";
        
        self.mMutex = Lock();


    def lock(self, timeout = 0):
        self.mMutex.acquire(timeout);


    def unlock(self):
        self.mMutex.release();

