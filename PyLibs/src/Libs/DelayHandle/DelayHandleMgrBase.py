# -*- coding: utf-8 -*-

from Libs.Core.GObject import GObject;
from Libs.DataStruct.MList import MList;
from Libs.DelayHandle.DelayHandleObject import DelayHandleObject;
from Libs.DelayHandle.DelayDelParam import DelayDelParam;
from Libs.Tools.UtilApi import UtilApi;
from Libs.DelayHandle.DelayAddParam import DelayAddParam;

'''
@brief 当需要管理的对象可能在遍历中间添加的时候，需要这个管理器
'''

class DelayHandleMgrBase(GObject):

    def __init__(self):
        super(DelayHandleMgrBase, self).__init__();
        
        self.mTypeId = "DelayHandleParamBase";

        self.mDeferredAddQueue = MList();
        self.mDeferredDelQueue = MList();

        self.mLoopDepth = 0;


    def addObject(self, delayObject, priority = 0.0):
        if (self.mLoopDepth > 0):
            if (not self.existAddList(delayObject)):         # 如果添加列表中没有
                if (self.existDelList(delayObject)):         # 如果已经添加到删除列表中
                    self.delFromDelayDelList(delayObject);

                delayHandleObject = DelayHandleObject();
                delayHandleObject.mDelayParam = DelayAddParam();
                self.mDeferredAddQueue.Add(delayHandleObject);

                delayHandleObject.mDelayObject = delayObject;
                delayHandleObject.mDelayParam.mPriority = priority;


    def removeObject(self, delayObject):
        if (self.mLoopDepth > 0):
            if (not self.existDelList(delayObject)):
                if (self.existAddList(delayObject)):    # 如果已经添加到删除列表中
                    self.delFromDelayAddList(delayObject);

                delayObject.setClientDispose();

                delayHandleObject = DelayHandleObject();
                delayHandleObject.mDelayParam = DelayDelParam();
                self.mDeferredDelQueue.Add(delayHandleObject);
                delayHandleObject.mDelayObject = delayObject;


    # 只有没有添加到列表中的才能添加
    def existAddList(self, delayObject):
        for item in self.mDeferredAddQueue.getList():
            if(UtilApi.isAddressEqual(item.mDelayObject, delayObject)):
                return True;

        return False;


    # 只有没有添加到列表中的才能添加
    def existDelList(self, delayObject):
        for item in self.mDeferredDelQueue.getList():
            if (UtilApi.isAddressEqual(item.mDelayObject, delayObject)):
                return True;

        return False;


    # 从延迟添加列表删除一个 Item
    def delFromDelayAddList(self, delayObject):
        for item in self.mDeferredAddQueue.getList():
            if (UtilApi.isAddressEqual(item.mDelayObject, delayObject)):
                self.mDeferredAddQueue.Remove(item);

    # 从延迟删除列表删除一个 Item
    def delFromDelayDelList(self, delayObject):
        for item in self.mDeferredDelQueue.getList():
            if(UtilApi.isAddressEqual(item.mDelayObject, delayObject)):
                self.mDeferredDelQueue.Remove(item);


    def processDelayObjects(self):
        idx = 0;
        elemLen = 0;
        
        if (0 == self.mLoopDepth):       # 只有全部退出循环后，才能处理添加删除
            if (self.mDeferredAddQueue.Count() > 0):
                idx = 0;
                # len 是关键字
                elemLen = self.mDeferredAddQueue.Count();
                while(idx < elemLen):
                    self.addObject(self.mDeferredAddQueue[idx].mDelayObject, self.mDeferredAddQueue[idx].mDelayParam.mPriority);
                    idx = idx + 1;

                self.mDeferredAddQueue.Clear();

            if (self.mDeferredDelQueue.Count() > 0):
                idx = 0;
                elemLen = self.mDeferredDelQueue.Count();
                while(idx < elemLen):
                    self.removeObject(self.mDeferredDelQueue[idx].mDelayObject);
                    idx = idx + 1;

                self.mDeferredDelQueue.Clear();


    def incDepth(self):
        self.mLoopDepth = self.mLoopDepth + 1;


    def decDepth(self):
        self.mLoopDepth = self.mLoopDepth - 1;
        self.processDelayObjects();


    def bInDepth(self):
        return self.mLoopDepth > 0;

