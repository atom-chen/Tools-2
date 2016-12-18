# -*- coding: utf-8 -*-

from Libs.DataStruct.MList import MList;
from Libs.Tools.UtilApi import UtilApi;
from Libs.DelayHandle.DelayHandleMgrBase import DelayHandleMgrBase;
from Libs.FrameHandle.TickProcessObject import TickProcessObject;

'''
@brief 心跳管理器
'''

class TickMgr(DelayHandleMgrBase):

    def __init__(self):
        super(TickMgr, self).__init__();
        
        self.mTypeId = "TickMgr";
        
        self.mTickList = MList();


    def addTick(self, tickObj, priority = 0.0):
        self.addObject(tickObj, priority);


    def addObject(self, delayObject, priority = 0.0):
        if (self.bInDepth()):
            super(TickMgr, self).addObject(delayObject, priority);
        else:
            position = -1;
            idx = 0;
            elemLen = self.mTickList.Count();
            while(idx < elemLen):
                if (self.mTickList[idx] == None):
                    continue;

                if (self.mTickList[idx].mTickObject == delayObject):
                    return;

                if (self.mTickList[idx].mPriority < priority):
                    position = idx;
                    break;
                
                idx = idx + 1;

            processObject = TickProcessObject();
            processObject.mTickObject = delayObject;
            processObject.mPriority = priority;

            if (position < 0 or position >= self.mTickList.Count()):
                self.mTickList.Add(processObject);
            else:
                self.mTickList.Insert(position, processObject);



    def delTick(self, tickObj):
        self.removeObject(tickObj);


    def removeObject(self, delayObject):
        if (self.bInDepth()):
            super(TickMgr, self).removeObject(delayObject);
        else:
            for item in self.mTickList.getList():
                if (UtilApi.isAddressEqual(item.mTickObject, delayObject)):
                    self.mTickList.Remove(item);
                    break;


    def Advance(self, delta):
        self.incDepth();

        for tk in self.mTickList.getList():
            if (not tk.mTickObject.IsClientDispose()):
                tk.mTickObject.onTick(delta);

        self.decDepth();


