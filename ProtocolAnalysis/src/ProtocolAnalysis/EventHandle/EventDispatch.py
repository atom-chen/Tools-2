#-*- encoding=utf-8 -*


from ProtocolAnalysis.DelayHandle.DelayHandleMgrBase import DelayHandleMgrBase
from ProtocolAnalysis.DataStruct.MList import MList
from ProtocolAnalysis.EventHandle.EventDispatchFunctionObject import EventDispatchFunctionObject
from ProtocolAnalysis.Core.AppSysBase import AppSysBase


'''
@brief 事件分发，之分发一类事件，不同类型的事件使用不同的事件分发
@brief 注意，事件分发缺点就是，可能被调用的对象已经释放，但是没有清掉事件处理器，结果造成空指针
'''
class EventDispatch(DelayHandleMgrBase):
    '''
    classdocs
    '''


    def __init__(self, eventId_ = 0):
        '''
        Constructor
        '''
        super(EventDispatch, self).__init__()
        
        self.m_eventId = eventId_
        self.m_handleList = MList()
        self.m_uniqueId = 0       # 唯一 Id ，调试使用


    # 相同的函数只能增加一次
    def addEventHandle(self, handle, paramList):
        funcObject = EventDispatchFunctionObject();
        funcObject.m_handle = handle;
        funcObject.m_paramList = paramList
        if None != handle:
            self.addObject(funcObject);
        else:
            AppSysBase.instance().m_logSys.log("Event Handle is null");


    def addObject(self, delayObject, priority = 0.0):
        if self.bInDepth():
            super(EventDispatch, self).addObject(delayObject, priority);
        else:
            # 这个判断说明相同的函数只能加一次，但是如果不同资源使用相同的回调函数就会有问题，但是这个判断可以保证只添加一次函数，值得，因此不同资源需要不同回调函数
            self.m_handleList.Add(delayObject);


    def removeEventHandle(self, handle):
        for idx in range(0, self.m_handleList.Count(), 1):
            if self.m_handleList[idx].m_handle is handle:
                break
        if idx < self.m_handleList.Count():
            self.delObject(self.m_handleList[idx])
        else:
            AppSysBase.instance().m_logSys.log("Event Handle not exist");


    def delObject(self, delayObject):
        if self.bInDepth():
            super(EventDispatch, self).delObject(delayObject);
        else:
            if not self.m_handleList.Remove(delayObject):
                AppSysBase.instance().m_logSys.log("Event Handle not exist");


    def dispatchEvent(self, dispatchObject):
        self.incDepth();

        for handle in self.m_handleList.list:
            if not handle.m_bClientDispose:
                handle.m_handle(handle.m_paramList, dispatchObject);

        self.decDepth();


    def clearEventHandle(self):
        if self.bInDepth():
            for item in self.m_handleList.list:
                self.delObject(item)
        else:
            self.m_handleList.Clear()


    # 这个判断说明相同的函数只能加一次，但是如果不同资源使用相同的回调函数就会有问题，但是这个判断可以保证只添加一次函数，值得，因此不同资源需要不同回调函数
    def existEventHandle(self, handle):
        bFinded = False
        for item in self.m_handleList.list:
            if item.m_handle is handle:
                bFinded = True
                break;

        return bFinded


    def copyFrom(self, rhv):
        for handle in rhv.handleList.list:
            self.m_handleList.Add(handle)
 
