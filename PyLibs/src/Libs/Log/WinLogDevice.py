﻿#-*- encoding=utf-8 -*-

'''
@brief 窗口日志
'''

from Libs.Log.LogDeviceBase import LogDeviceBase
from Libs.Log.LogColor import LogColor

class WinLogDevice(LogDeviceBase):
    
    def __init__(self):
        super(WinLogDevice, self).__init__();
        
        self.mTypeId = "WinLogDevice";

    
    def logout(self, message, type = LogColor.LOG):
        print(message);


