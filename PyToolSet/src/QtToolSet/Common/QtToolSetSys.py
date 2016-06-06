# -*- coding: utf-8 -*-

'''
@brief: QtToolSetSys
'''

from ToolSet.Common.ToolSetSys import ToolSetSys

class QtToolSetSys(ToolSetSys):
    
    def __init__(self):
        super(QtToolSetSys, self).__init__();
        
        self.mTypeId = "PyToolSetSys";
        
        self.mWinLogDeviceProxy = None;

    

    def init(self):
        pass;

