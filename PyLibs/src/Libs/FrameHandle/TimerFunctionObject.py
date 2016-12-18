#-*- encoding=utf-8 -*-

from Libs.Core.GObject import GObject;
from Libs.Tools.UtilApi import UtilApi;

class TimerFunctionObject(GObject):

    def __init__(self):
        super(TimerFunctionObject, self).__init__();
        
        self.mTypeId = "TimerFunctionObject";
        
        self.mHandle = None;


    def setFuncObject(self, handle):    
        self.mHandle = handle;


    def isValid(self):
        return self.mHandle != None;


    def isEqual(self, handle):
        ret = False;
        if(handle != None):
            ret = UtilApi.isAddressEqual(self.mHandle, handle);
            if(not ret):
                return ret;
        
        return ret;


    def call(self, dispObj):
        if (None != self.mHandle):
            self.mHandle(dispObj);

