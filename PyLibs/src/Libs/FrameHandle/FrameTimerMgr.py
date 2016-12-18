# -*- coding: utf-8 -*-

from Libs.DataStruct.MList import MList;
from Libs.Tools.UtilApi import UtilApi;
from Libs.DelayHandle.DelayHandleMgrBase import DelayHandleMgrBase;

'''
* @brief 定时器管理器
'''

class FrameTimerMgr(DelayHandleMgrBase):

    def __init__(self):
        super(FrameTimerMgr, self).__init__();
        
        self.mTypeId = "FrameTimerMgr";
        
        self.mTimerList = MList();      # 当前所有的定时器列表


    def addObject(self, delayObject, priority = 0.0):
        # 检查当前是否已经在队列中
        if (self.mTimerList.IndexOf(delayObject) == -1):
            if (self.bInDepth()):
                super(FrameTimerMgr, self).addObject(delayObject, priority);
            else:
                self.mTimerList.Add(delayObject);



    def removeObject(self, delayObject):
        # 检查当前是否在队列中
        if (self.mTimerList.IndexOf(delayObject) != -1):
            delayObject.mIsDisposed = True;
            if (self.bInDepth()):
                super(FrameTimerMgr,self).addObject(delayObject);
            else:
                for item in self.mTimerList.getList():
                    if (UtilApi.isAddressEqual(item, delayObject)):
                        self.mTimerList.Remove(item);
                        break;


    def addFrameTimer(self, timer, priority = 0.0):
        self.addObject(timer, priority);


    def removeFrameTimer(self, timer):
        self.removeObject(timer);


    def Advance(self, delta):
        self.incDepth();

        for timerItem in self.mTimerList.getList():
            if (not timerItem.IsClientDispose()):
                timerItem.OnFrameTimer();
            if (timerItem.mIsDisposed):
                self.removeObject(timerItem);

        self.decDepth();

