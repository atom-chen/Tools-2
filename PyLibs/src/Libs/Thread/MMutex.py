# -*- coding: utf-8 -*-

from threading import Lock;
from Libs.Core.GObject import GObject;

'''
@brief 互斥
'''

class MMutex(GObject):
    
    def __init__(self):
        super(MMutex, self).__init__();
        
        self.mTypeId = "MLock";
        
        self.mMutex = Lock();


    def lock(self, timeout = 0):
        self.mMutex.acquire(timeout);


    def unlock(self):
        self.mMutex.release();

