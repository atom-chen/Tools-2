# -*- coding: utf-8 -*-

from Libs.DataStruct.MList import MList;
from Libs.DelayHandle.DelayHandleMgrBase import DelayHandleMgrBase;

class ResizeMgr(DelayHandleMgrBase):

    def __init__(self):
        super(ResizeMgr, self).__init__();
        
        self.mTypeId = "ResizeMgr";
        
        self.mPreWidth = 0;
        self.mPreHeight = 0;
        self.mCurWidth = 0;
        self.mCurHeight = 0;
        self.mResizeList = MList();


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
        if (self.mResizeList.IndexOf(obj) == -1):
            self.mResizeList.Add(obj);


    def removeResizeObject(self, obj):
        if (self.mResizeList.IndexOf(obj) != -1):
            self.mResizeList.Remove(obj);


    def onTick(self, delta):
        self.mPreWidth = self.mCurWidth;
        self.mCurWidth = 0;
        self.mPreHeight = self.mCurHeight;
        self.mCurHeight = 0;

        if(self.mPreWidth != self.mCurWidth or self.mPreHeight != self.mCurHeight):
            self.onResize(self.mCurWidth, self.mCurHeight);


    def onResize(self, viewWidth, viewHeight):
        for resizeObj in self.mResizeList.getList():
            resizeObj.onResize(viewWidth, viewHeight);


