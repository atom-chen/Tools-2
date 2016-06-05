# -*- coding: utf-8 -*-

'''
@brief: LogWinProxy
'''
from Libs.Log.LogDeviceBase import LogDeviceBase
from Libs.Log.LogColor import LogColor

class LogWinProxy(LogDeviceBase):
    
    def __init__(self):
        super(LogDeviceBase, self).__init__();
        
        self.mTypeId = "LogWinProxy";
        
        self.mLogWin = None;


    def logout(self, message, logType = LogColor.LOG):
        self.mLogWin.ui.textEdit.appendPlainText(message);

    
    def setLogWin(self, logWin):
        self.mLogWin = logWin;
    
    
    