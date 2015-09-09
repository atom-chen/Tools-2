#-*- encoding=utf-8 -*


from ProtocolAnalysis.DelayHandle.IDelayHandleItem import IDelayHandleItem


class EventDispatchFunctionObject(IDelayHandleItem):
    '''
    classdocs
    '''
    

    def __init__(self, eventId_ = 0):
        '''
        Constructor
        '''
        self.m_bClientDispose = False       # 是否释放了资源
        self.m_handle = None


    def setClientDispose(self):
        self.m_bClientDispose = True;
    

    def getClientDispose(self):
        return self.m_bClientDispose;


