# -*- coding: utf-8 -*-

from Libs.DelayHandle.IDelayHandleItem import IDelayHandleItem;
from Libs.Tools.UtilApi import UtilApi;

class EventDispatchFunctionObject(IDelayHandleItem):
    
    def __init__(self):
        super(EventDispatchFunctionObject, self).__init__();
        
        self.mTypeId = "EventDispatchFunctionObject";
        
        self.m_bClientDispose = False;      # 是否释放了资源
        self.mThis = None;
        self.m_handle = None;


    def setFuncObject(self, pThis, func):
        self.mThis = pThis;
        self.m_handle = func;


    def isValid(self):
        return self.mThis != None or self.m_handle != None;


    def isEqual(self, pThis, handle):
        ret = False;
        if(pThis != None):
            ret = UtilApi.isAddressEqual(self.mThis, pThis);
            if (not ret):
                return ret;

        if (handle != None):
            ret = UtilApi.isAddressEqual(self.m_handle, handle);
            if(not ret):
                return ret;

        return ret;


    def call(self, dispObj):
        #if(self.mThis != None)
        #{
        #    self.mThis.call(dispObj);
        #}

        if(None != self.m_handle):
            self.m_handle(dispObj);


    def setClientDispose(self):
        self.m_bClientDispose = True;


    def getClientDispose(self):
        return self.m_bClientDispose;

