# -*- coding: utf-8 -*-

from Libs.DelayHandle.DelayHandleMgrBase import DelayHandleMgrBase;
from Libs.DataStruct.MList import MList;
from Libs.Tools.UtilApi import UtilApi;

'''
@brief 定时器管理器
'''

class TimerMgr(DelayHandleMgrBase):

    def __init__(self):
        super(TimerMgr, self).__init__();
        
        self.mTypeId = "TimerMgr";
        
        self.mTimerList = MList();     # 当前所有的定时器列表


    def addObject(self, delayObject, priority = 0.0):
        # 检查当前是否已经在队列中
        if (self.mTimerList.IndexOf(delayObject) == -1):
            if (self.bInDepth()):
                super(TimerMgr, self).addObject(delayObject, priority);
            else:
                self.mTimerList.Add(delayObject);


    def removeObject(self, delayObject):
        # 检查当前是否在队列中
        if (self.mTimerList.IndexOf(delayObject) != -1):
            delayObject.mIsDisposed = True;
            if (self.bInDepth()):
                super(TimerMgr, self).removeObject(delayObject);
            else:
                for item in self.mTimerList.getList():
                    if (UtilApi.isAddressEqual(item, delayObject)):
                        self.mTimerList.Remove(item);
                        break;


    # 从 Lua 中添加定时器，这种定时器尽量整个定时器周期只与 Lua 通信一次
    def addTimer(self, delayObject, priority = 0.0):
        self.addObject(delayObject, priority);


    def removeTimer(self, timer):
        self.removeObject(timer);


    def Advance(self, delta):
        self.incDepth();

        for timerItem in self.mTimerList.getList():
            if (not timerItem.IsClientDispose()):
                timerItem.OnTimer(delta);

            if (timerItem.mIsDisposed):        # 如果已经结束
                self.removeObject(timerItem);

        self.decDepth();

