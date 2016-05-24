#-*- encoding=utf-8 -*-

from Libs.Core import GObject

class IResizeObject(GObject):
    
    def __init__(self):
        super(IResizeObject, self).__init__();
        
        self.mTypeId = "IResizeObject";
        
        
    def onResize(self, viewWidth, viewHeight):
        pass;

