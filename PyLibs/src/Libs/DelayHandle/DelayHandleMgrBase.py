#-*- encoding=utf-8 -*-

'''
@brief 当需要管理的对象可能在遍历中间添加的时候，需要这个管理器
'''

from Libs.Core.GObject import GObject
from Libs.DataStruct.MList import MList
from Libs.DelayHandle.DelayHandleObject import DelayHandleObject
from Libs.DelayHandle.DelayDelParam import DelayDelParam
from Libs.Tools.UtilApi import UtilApi
from Libs.DelayHandle.DelayAddParam import DelayAddParam

class DelayHandleMgrBase(GObject):

    def __init__(self):
        super(DelayHandleMgrBase, self).__init__();
        
        self.mTypeId = "DelayHandleParamBase";

        self.m_deferredAddQueue = MList();
        self.m_deferredDelQueue = MList();

        self.m_loopDepth = 0;


    def addObject(self, delayObject, priority = 0.0):
        if (self.m_loopDepth > 0):
            if (not self.existAddList(delayObject)):         # 如果添加列表中没有
                if (self.existDelList(delayObject)):         # 如果已经添加到删除列表中
                    self.delFromDelayDelList(delayObject);

                delayHandleObject = DelayHandleObject();
                delayHandleObject.m_delayParam = DelayAddParam();
                self.m_deferredAddQueue.Add(delayHandleObject);

                delayHandleObject.m_delayObject = delayObject;
                delayHandleObject.m_delayParam.m_priority = priority;


    def removeObject(self, delayObject):
        if (self.m_loopDepth > 0):
            if (not self.existDelList(delayObject)):
                if (self.existAddList(delayObject)):    # 如果已经添加到删除列表中
                    self.delFromDelayAddList(delayObject);

                delayObject.setClientDispose();

                delayHandleObject = DelayHandleObject();
                delayHandleObject.m_delayParam = DelayDelParam();
                self.m_deferredDelQueue.Add(delayHandleObject);
                delayHandleObject.m_delayObject = delayObject;


    # 只有没有添加到列表中的才能添加
    def existAddList(self, delayObject):
        for item in self.m_deferredAddQueue.getList():
            if(UtilApi.isAddressEqual(item.m_delayObject, delayObject)):
                return True;

        return False;


    # 只有没有添加到列表中的才能添加
    def existDelList(self, delayObject):
        for item in self.m_deferredDelQueue.getList():
            if (UtilApi.isAddressEqual(item.m_delayObject, delayObject)):
                return True;

        return False;


    # 从延迟添加列表删除一个 Item
    def delFromDelayAddList(self, delayObject):
        for item in self.m_deferredAddQueue.getList():
            if (UtilApi.isAddressEqual(item.m_delayObject, delayObject)):
                self.m_deferredAddQueue.Remove(item);

    # 从延迟删除列表删除一个 Item
    def delFromDelayDelList(self, delayObject):
        for item in self.m_deferredDelQueue.getList():
            if(UtilApi.isAddressEqual(item.m_delayObject, delayObject)):
                self.m_deferredDelQueue.Remove(item);


    def processDelayObjects(self):
        idx = 0;
        elemLen = 0;
        
        if (0 == self.m_loopDepth):       # 只有全部退出循环后，才能处理添加删除
            if (self.m_deferredAddQueue.Count() > 0):
                idx = 0;
                # len 是关键字
                elemLen = self.m_deferredAddQueue.Count();
                while(idx < elemLen):
                    self.addObject(self.m_deferredAddQueue[idx].m_delayObject, self.m_deferredAddQueue[idx].m_delayParam.m_priority);
                    idx = idx + 1;

                self.m_deferredAddQueue.Clear();

            if (self.m_deferredDelQueue.Count() > 0):
                idx = 0;
                elemLen = self.m_deferredDelQueue.Count();
                while(idx < elemLen):
                    self.removeObject(self.m_deferredDelQueue[idx].m_delayObject);
                    idx = idx + 1;

                self.m_deferredDelQueue.Clear();


    def incDepth(self):
        self.m_loopDepth = self.m_loopDepth + 1;


    def decDepth(self):
        self.m_loopDepth = self.m_loopDepth - 1;
        self.processDelayObjects();


    def bInDepth(self):
        return self.m_loopDepth > 0;

