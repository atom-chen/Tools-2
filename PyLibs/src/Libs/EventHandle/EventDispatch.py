#-*- encoding=utf-8 -*-

'''
@brief 事件分发，之分发一类事件，不同类型的事件使用不同的事件分发
@brief 注意，事件分发缺点就是，可能被调用的对象已经释放，但是没有清掉事件处理器，结果造成空指针
'''

from Libs.DelayHandle.DelayHandleMgrBase import DelayHandleMgrBase
from Libs.DataStruct.MList import MList
from Libs.EventHandle.EventDispatchFunctionObject import EventDispatchFunctionObject

class EventDispatch(DelayHandleMgrBase):

    def __init__(self, eventId_ = 0):
        super(EventDispatch, self).__init__();
        
        self.mTypeId = "EventDispatch";
        
        self.m_eventId = eventId_;
        self.m_handleList = MList();


    def getHandleList(self):
        return self.m_handleList;

    # 相同的函数只能增加一次，Lua ，Python 这些语言不支持同时存在几个相同名字的函数，只支持参数可以赋值，因此不单独提供同一个名字不同参数的接口了
    def addEventHandle(self, pThis, handle):
        if (None != pThis or None != handle):
            funcObject = EventDispatchFunctionObject();
            if (None != handle):
                funcObject.setFuncObject(pThis, handle);

            self.addObject(funcObject);
        else:
            # 输出日志
            pass;


    def removeEventHandle(self, pThis, handle):
        idx = 0;
        elemLen = 0;
        elemLen = self.m_handleList.Count();
        while(idx < elemLen):
            if (self.m_handleList[idx].isEqual(pThis, handle)):
                break;
            
            idx = idx + 1;

        if(idx < self.m_handleList.Count()):
            self.removeObject(self.m_handleList[idx]);
        else:
            # 输出日志
            pass;


    def addObject(self, delayObject, priority = 0.0):
        if (self.bInDepth()):
            super(EventDispatch, self).addObject(delayObject, priority);
        else:
            # 这个判断说明相同的函数只能加一次，但是如果不同资源使用相同的回调函数就会有问题，但是这个判断可以保证只添加一次函数，值得，因此不同资源需要不同回调函数
            self.m_handleList.Add(delayObject);


    def removeObject(self, delayObject):
        if (self.bInDepth()):
            super(EventDispatch, self).removeObject(delayObject);
        else:
            if (not self.m_handleList.Remove(delayObject)):
                # 输出日志
                pass;


    def dispatchEvent(self, dispatchObject):
        #try:
            self.incDepth();

            for handle in self.m_handleList.getList():
                if (not handle.m_bClientDispose):
                    handle.call(dispatchObject);

            self.decDepth();
        # except Exception , e:
            # 输出日志
            # pass;


    def clearEventHandle(self):
        if (self.bInDepth()):
            for item in self.m_handleList.getList():
                self.removeObject(item);
        else:
            self.m_handleList.Clear();


    # 这个判断说明相同的函数只能加一次，但是如果不同资源使用相同的回调函数就会有问题，但是这个判断可以保证只添加一次函数，值得，因此不同资源需要不同回调函数
    def existEventHandle(self, pThis, handle):
        bFinded = False;
        for item in self.m_handleList.getList():
            if (item.isEqual(pThis, handle)):
                bFinded = True;
                break;

        return bFinded;


    def copyFrom(self, rhv):
        for handle in rhv.handleList.getList():
            self.m_handleList.Add(handle);


    def getHandleCount(self):
        return self.m_handleList.Count();


