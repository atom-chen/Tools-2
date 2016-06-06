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
        
        self.m_tickLst = MList();


    def addTick(self, tickObj, priority = 0.0):
        self.addObject(tickObj, priority);


    def addObject(self, delayObject, priority = 0.0):
        if (self.bInDepth()):
            super(TickMgr, self).addObject(delayObject, priority);
        else:
            position = -1;
            idx = 0;
            elemLen = self.m_tickLst.Count();
            while(idx < elemLen):
                if (self.m_tickLst[idx] == None):
                    continue;

                if (self.m_tickLst[idx].m_tickObject == delayObject):
                    return;

                if (self.m_tickLst[idx].m_priority < priority):
                    position = idx;
                    break;
                
                idx = idx + 1;

            processObject = TickProcessObject();
            processObject.m_tickObject = delayObject;
            processObject.m_priority = priority;

            if (position < 0 or position >= self.m_tickLst.Count()):
                self.m_tickLst.Add(processObject);
            else:
                self.m_tickLst.Insert(position, processObject);



    def delTick(self, tickObj):
        self.removeObject(tickObj);


    def removeObject(self, delayObject):
        if (self.bInDepth()):
            super(TickMgr, self).removeObject(delayObject);
        else:
            for item in self.m_tickLst.getList():
                if (UtilApi.isAddressEqual(item.m_tickObject, delayObject)):
                    self.m_tickLst.Remove(item);
                    break;


    def Advance(self, delta):
        self.incDepth();

        for tk in self.m_tickLst.getList():
            if (not tk.m_tickObject.getClientDispose()):
                tk.m_tickObject.onTick(delta);

        self.decDepth();


