#-*- encoding=utf-8 -*-

from Libs.Core.GObject import GObject
from Libs.Tools.UtilApi import UtilApi

class TimerFunctionObject(GObject):

    def __init__(self):
        super(TimerFunctionObject, self).__init__();
        
        self.mTypeId = "TimerFunctionObject";
        
        self.m_handle = None;


    def setFuncObject(self, handle):    
        self.m_handle = handle;


    def isValid(self):
        return self.m_handle != None;


    def isEqual(self, handle):
        ret = False;
        if(handle != None):
            ret = UtilApi.isAddressEqual(self.m_handle, handle);
            if(not ret):
                return ret;
        
        return ret;


    def call(self, dispObj):
        if (None != self.m_handle):
            self.m_handle(dispObj);

