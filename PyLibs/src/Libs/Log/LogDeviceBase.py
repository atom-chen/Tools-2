﻿#-*- encoding=utf-8 -*-

from Libs.Core.GObject import GObject
from Libs.Log.LogColor import LogColor

'''
@brief 日志设备
'''

class LogDeviceBase(GObject):
    
    def __init__(self):
        super(LogDeviceBase).__init__();
        
        self.mTypeId = "LogDeviceBase";

    
    def initDevice(self):
        pass;


    def closeDevice(self):
        pass;


    def logout(self, message, logType = LogColor.LOG):
        pass;


