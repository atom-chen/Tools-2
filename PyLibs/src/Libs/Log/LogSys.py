# -*- coding: utf-8 -*-

from Libs.Core.GObject import GObject;
from Libs.DataStruct.LockList import LockList;
from Libs.DataStruct.MList import MList;
from Libs.Thread.MThread import MThread;
from Libs.Log.LogTypeId import LogTypeId;
from Libs.Log.LogColor import LogColor;
from Libs.Log.WinLogDevice import WinLogDevice;

class LogSys(GObject):

    def __init__(self):
        super(LogSys, self).__init__();
        self.mAsyncLogList = LockList();               # 这个是多线程访问的
        self.mAsyncWarnList = LockList();              # 这个是多线程访问的
        self.mAsyncErrorList = LockList();             # 这个是多线程访问的

        self.mLogDeviceList = MList();
        self.mEnableLog = True;         #  这个是总的开关
        self.registerDevice();



    def setEnableLog(self, value):
        self.mEnableLog = value;


    def addLogDevice(self, logDevice):
        logDevice.initDevice();
        self.mLogDeviceList.Add(logDevice);


    def registerDevice(self):
        logDevice = WinLogDevice();
        self.addLogDevice(logDevice);


    def isInFilter(self, logTypeId):
        if(not self.mEnableLog):
            return False;
        
        if(logTypeId == LogTypeId.eLogCommon or
            logTypeId == LogTypeId.eLogTest):
            return True;

        return False;


    def log(self, message, logTypeId = LogTypeId.eLogCommon):
        if (self.isInFilter(logTypeId)):
            if (MThread.isMainThread()):
                self.logout(message, LogColor.LOG);
            else:
                self.asyncLog(message);


    def warn(self, message, logTypeId = LogTypeId.eLogCommon):
        if (self.isInFilter(logTypeId)):
            if (MThread.isMainThread()):
                self.logout(message, LogColor.WARN);
            else:
                self.asyncWarn(message);


    def error(self, message, logTypeId = LogTypeId.eLogCommon):
        if (self.isInFilter(logTypeId)):
            if (MThread.isMainThread()):
                self.logout(message, LogColor.ERROR);
            else:
                self.asyncError(message);


    # 多线程日志
    def asyncLog(self, message):
        self.mAsyncLogList.Add(message);


    # 多线程日志
    def asyncWarn(self, message):
        self.mAsyncWarnList.Add(message);


    # 多线程日志
    def asyncError(self, message):
        self.mAsyncErrorList.Add(message);

    
    def logout(self, message, logTypeId = LogColor.LOG):
        MThread.needMainThread();

        if (self.m_bOutLog):
            for logDevice in self.mLogDeviceList.getList():
                logDevice.logout(message, logTypeId);


    def updateLog(self):
        MThread.needMainThread();

        while (self.mAsyncLogList.Count() > 0):
            tmpStr = self.mAsyncLogList.RemoveAt(0);
            self.logout(tmpStr, LogColor.LOG);

        while (self.mAsyncWarnList.Count() > 0):
            tmpStr = self.mAsyncWarnList.RemoveAt(0);
            self.logout(tmpStr, LogColor.LOG);

        while (self.mAsyncErrorList.Count() > 0):
            tmpStr = self.mAsyncErrorList.RemoveAt(0);
            self.logout(tmpStr, LogColor.LOG);


    def closeDevice(self):
        for logDevice in self.mLogDeviceList.getList():
            logDevice.closeDevice();



