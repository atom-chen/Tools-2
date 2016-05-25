﻿#-*- encoding=utf-8 -*-

from threading import Event
from Libs.Core.GObject import GObject

'''
@同步使用的 Event
'''

class MEvent(GObject):

    def __init__(self, initialState):
        super(MEvent, self).__init__();
        
        self.mTypeId = "MEvent";

        self.m_event = Event(initialState);


    def WaitOne(self):
        self.m_event.wait();


    def Reset(self):
        return self.m_event.clear();


    def Set(self):
        return self.m_event.set();


