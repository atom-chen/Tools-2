# -*- coding: utf-8 -*-

'''
@brief: ToolSetSys
'''

from Libs.Core.GObject import GObject
from Libs.Tools.UtilError import UtilError

class ToolSetSys(GObject):
                
    msInstance = None;
    
    @staticmethod
    def setInstance(ins):
        if (ToolSetSys.msInstance == None):
            ToolSetSys.msInstance = ins;
        else:
            UtilError.error("Ins Can not Ins Twice");   
    

    @staticmethod
    def instance():
        #if (ToolSetSys.msInstance == None):
        #    ToolSetSys.msInstance = PyToolSetSys();

        return ToolSetSys.msInstance;


    def __init__(self):   
        super(ToolSetSys, self).__init__();
        
        self.mTypeId = "ToolSetSys";
    
        self.mFileDirDiffSys = None;

