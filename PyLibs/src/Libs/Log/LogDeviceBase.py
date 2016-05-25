﻿#-*- encoding=utf-8 -*-

'''
@brief 日志设备
'''

from Libs.Core.GObject import GObject
from Libs.Log.LogColor import LogColor

class LogDeviceBase(GObject):
    
    def __init__(self):
        super(LogDeviceBase).__init__();
        
        self.mTypeId = "LogDeviceBase";

    
    def initDevice(self):
        pass;


    def closeDevice(self):
        pass;


    def logout(self, message, type = LogColor.LOG):
        pass;


