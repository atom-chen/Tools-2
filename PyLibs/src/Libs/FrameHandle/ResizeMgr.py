# -*- coding: utf-8 -*-

from Libs.DataStruct.MList import MList
from Libs.DelayHandle.DelayHandleMgrBase import DelayHandleMgrBase

class ResizeMgr(DelayHandleMgrBase):

    def __init__(self):
        super(ResizeMgr, self).__init__();
        
        self.mTypeId = "ResizeMgr";
        
        self.m_preWidth = 0;
        self.m_preHeight = 0;
        self.m_curWidth = 0;
        self.m_curHeight = 0;
        self.m_ResizeLst = MList();


    def addObject(self, delayObject, priority = 0.0):
        if(self.bInDepth()):
            super(ResizeMgr, self).addObject(delayObject, priority);
        else:
            self.addResizeObject(delayObject, priority);


    def removeObject(self, delayObject):
        if(self.bInDepth()):
            super().removeObject(delayObject);
        else:
            self.removeResizeObject(delayObject);

    def addResizeObject(self, obj, priority = 0):
        if (self.m_ResizeLst.IndexOf(obj) == -1):
            self.m_ResizeLst.Add(obj);


    def removeResizeObject(self, obj):
        if (self.m_ResizeLst.IndexOf(obj) != -1):
            self.m_ResizeLst.Remove(obj);


    def onTick(self, delta):
        self.m_preWidth = self.m_curWidth;
        self.m_curWidth = 0;
        self.m_preHeight = self.m_curHeight;
        self.m_curHeight = 0;

        if(self.m_preWidth != self.m_curWidth or self.m_preHeight != self.m_curHeight):
            self.onResize(self.m_curWidth, self.m_curHeight);


    def onResize(self, viewWidth, viewHeight):
        for resizeObj in self.m_ResizeLst.getList():
            resizeObj.onResize(viewWidth, viewHeight);


