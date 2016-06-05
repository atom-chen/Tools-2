﻿#-*- encoding=utf-8 -*-

from Libs.Log.LogDeviceBase import LogDeviceBase
from Libs.Log.LogColor import LogColor

'''
@brief 窗口日志
'''

class WinLogDevice(LogDeviceBase):
    
    def __init__(self):
        super(WinLogDevice, self).__init__();
        
        self.mTypeId = "WinLogDevice";

    
    def logout(self, message, logType = LogColor.LOG):
        print(message);


