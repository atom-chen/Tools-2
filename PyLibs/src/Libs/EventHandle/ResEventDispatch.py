# -*- coding: utf-8 -*-

from Libs.EventHandle.EventDispatch import EventDispatch

class ResEventDispatch(EventDispatch):
    def __init__(self):
        super(ResEventDispatch, self).__init__()
        
        self.mTypeId = "ResEventDispatch";


    def dispatchEvent(self, dispatchObject):
        super(ResEventDispatch, self).dispatchEvent(dispatchObject);
        self.clearEventHandle();


