# -*- coding: utf-8 -*-

from Libs.Core.GObject import GObject

class TickProcessObject(GObject):

    def __init__(self):
        super(TickProcessObject, self).__init__();
        
        self.mTypeId = "TickProcessObject";
        
        self.m_tickObject = None;
        self.m_priority = 0.0;


