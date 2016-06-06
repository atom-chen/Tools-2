# -*- coding: utf-8 -*-

from Libs.Core.GObject import GObject
from Libs.DataStruct.LockList import LockList
from Libs.DataStruct.MList import MList
from Libs.Thread.MThread import MThread
from Libs.Log.LogTypeId import LogTypeId
from Libs.Log.LogColor import LogColor
from Libs.Log.WinLogDevice import WinLogDevice

class LogSys(GObject):

    def __init__(self):
        super(LogSys, self).__init__();
        self.m_asyncLogList = LockList();               # 这个是多线程访问的
        self.m_asyncWarnList = LockList();              # 这个是多线程访问的
        self.m_asyncErrorList = LockList();             # 这个是多线程访问的

        self.m_logDeviceList = MList();
        self.mEnableLog = True;         #  这个是总的开关
        self.registerDevice();
        self.registerFileLogDevice();


    def setEnableLog(self, value):
        self.mEnableLog = value;


    def addLogDevice(self, logDevice):
        logDevice.initDevice();
        self.m_logDeviceList.Add(logDevice);


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
        self.m_asyncLogList.Add(message);


    # 多线程日志
    def asyncWarn(self, message):
        self.m_asyncWarnList.Add(message);


    # 多线程日志
    def asyncError(self, message):
        self.m_asyncErrorList.Add(message);

    
    def logout(self, message, logTypeId = LogColor.LOG):
        MThread.needMainThread();

        if (self.m_bOutLog):
            for logDevice in self.m_logDeviceList.getList():
                logDevice.logout(message, logTypeId);


    def updateLog(self):
        MThread.needMainThread();

        while (self.m_asyncLogList.Count() > 0):
            tmpStr = self.m_asyncLogList.RemoveAt(0);
            self.logout(tmpStr, LogColor.LOG);

        while (self.m_asyncWarnList.Count() > 0):
            tmpStr = self.m_asyncWarnList.RemoveAt(0);
            self.logout(tmpStr, LogColor.LOG);

        while (self.m_asyncErrorList.Count() > 0):
            tmpStr = self.m_asyncErrorList.RemoveAt(0);
            self.logout(tmpStr, LogColor.LOG);


    def closeDevice(self):
        for logDevice in self.m_logDeviceList.getList():
            logDevice.closeDevice();



