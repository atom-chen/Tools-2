# -*- coding: utf-8 -*-

from threading import Event;
from Libs.Core.GObject import GObject;

'''
@同步使用的 Event
'''

class MEvent(GObject):

    def __init__(self, initialState):
        super(MEvent, self).__init__();
        
        self.mTypeId = "MEvent";

        self.mEvent = Event(initialState);


    def WaitOne(self):
        self.mEvent.wait();


    def Reset(self):
        return self.mEvent.clear();


    def Set(self):
        return self.mEvent.set();


