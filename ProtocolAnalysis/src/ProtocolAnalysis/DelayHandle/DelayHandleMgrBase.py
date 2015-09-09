# -*- coding: utf-8 -*-


from ProtocolAnalysis.DataStruct.MList import MList
from ProtocolAnalysis.DelayHandle.DelayHandleObject import  DelayHandleObject
from ProtocolAnalysis.DelayHandle.DelayAddParam import  DelayAddParam
from ProtocolAnalysis.DelayHandle.DelayDelParam import  DelayDelParam


'''
@brief 当需要管理的对象可能在遍历中间添加的时候，需要这个管理器
'''
class DelayHandleMgrBase(object):
    '''
    classdocs
    '''
    
    
    
    def __init__(self):
        '''
        Constructor
        '''
        self.m_deferredAddQueue = MList()
        self.m_deferredDelQueue = MList()

        self.m_loopDepth = 0           # 是否在循环中，支持多层嵌套，就是循环中再次调用循环


    def addObject(self, delayObject, priority = 0.0):
        if self.m_loopDepth > 0:
            if not self.existAddList(delayObject):        # 如果添加列表中没有
                if self.existDelList(delayObject):    # 如果已经添加到删除列表中
                    self.delFromDelayDelList(delayObject)

                delayHandleObject = DelayHandleObject()
                delayHandleObject.m_delayParam = DelayAddParam()
                self.m_deferredAddQueue.Add(delayHandleObject)

                delayHandleObject.m_delayObject = delayObject
                delayHandleObject.m_delayParam.m_priority = priority


    def delObject(self, delayObject):
        if self.m_loopDepth > 0:
            if not self.existDelList(delayObject):
                if self.existAddList(delayObject):    # 如果已经添加到删除列表中
                    self.delFromDelayAddList(delayObject)

                delayObject.setClientDispose()

                delayHandleObject = DelayHandleObject()
                delayHandleObject.m_delayParam = DelayDelParam()
                self.m_deferredDelQueue.Add(delayHandleObject)
                delayHandleObject.m_delayObject = delayObject


    # 只有没有添加到列表中的才能添加
    def existAddList(self, delayObject):
        for item in self.m_deferredAddQueue.list:
            if item.m_delayObject is delayObject:
                return True

        return False

    # 只有没有添加到列表中的才能添加
    def existDelList(self, delayObject):
        for item in self.m_deferredDelQueue.list:
            if item.m_delayObject is delayObject:
                return True

        return False


    # 从延迟添加列表删除一个 Item
    def delFromDelayAddList(self, delayObject):
        for item in self.m_deferredAddQueue.list:
            if item.m_delayObject is delayObject:
                self.m_deferredAddQueue.Remove(item)


    # 从延迟删除列表删除一个 Item
    def delFromDelayDelList(self, delayObject):
        for item in self.m_deferredDelQueue.list:
            if item.m_delayObject is delayObject:
                self.m_deferredDelQueue.Remove(item)


    def processDelayObjects(self):
        if 0 == self.m_loopDepth:       # 只有全部退出循环后，才能处理添加删除
            if self.m_deferredAddQueue.Count() > 0:
                for idx in range(0, self.m_deferredAddQueue.Count(), 1):
                    self.addObject(self.m_deferredAddQueue[idx].m_delayObject, self.m_deferredAddQueue[idx].m_delayParam.m_priority)

                self.m_deferredAddQueue.Clear()

            if self.m_deferredDelQueue.Count() > 0:
                for idx in range(0, self.m_deferredDelQueue.Count(), 1):
                    self.delObject(self.m_deferredDelQueue[idx].m_delayObject)

                self.m_deferredDelQueue.Clear()


    def incDepth(self):
        self.m_loopDepth += 1


    def decDepth(self):
        self.m_loopDepth -= 1
        self.processDelayObjects()


    def bInDepth(self):
        return self.m_loopDepth > 0


