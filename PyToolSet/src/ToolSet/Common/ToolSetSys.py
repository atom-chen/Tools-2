# -*- coding: utf-8 -*-

'''
@brief: ToolSetSys
'''

from Libs.Core.GObject import GObject

class ToolSetSys(GObject):
    
    def __init__(self):   
        super(ToolSetSys, self).__init__();
        
        self.mTypeId = "ToolSetSys";
    
        self.mFileDirDiffSys = None;

