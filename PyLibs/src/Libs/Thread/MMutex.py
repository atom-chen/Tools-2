﻿#-*- encoding=utf-8 -*-

'''
@brief 互斥
'''

from Libs.Core.GObject import GObject
from threading import Lock

class MMutex(GObject):
    
    def __init__(self):
        super(MMutex, self).__init__();
        
        self.mTypeId = "MLock";
        
        self.m_mmutex = Lock();


    def lock(self, timeout = 0):
        self.m_mmutex.acquire(timeout);


    def unlock(self):
        self.m_mmutex.release();

