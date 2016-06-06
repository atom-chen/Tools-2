# -*- coding: utf-8 -*-

from Libs.Core.GObject import GObject;

class ITickedObject(GObject):
    def __init__(self):
        super(ITickedObject, self).__init__();
        
        self.mTypeId = "ITickedObject";

        
    def onTick(self, delta):
        pass;


