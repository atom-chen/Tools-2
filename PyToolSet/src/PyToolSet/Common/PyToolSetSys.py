# -*- coding: utf-8 -*-

'''
@brief: PyToolSetSys
'''

from ToolSet.Common import ToolSetSys

class PyToolSetSys(ToolSetSys):
            
    msInstance = None;
    
    @staticmethod
    def instance():
        #if (PyToolSetSys.msInstance == None):
        #    PyToolSetSys.msInstance = PyToolSetSys();

        return PyToolSetSys.msInstance;

    
    def __init__(self):
        super(PyToolSetSys, self).__init__();
        
        self.mTypeId = "PyToolSetSys";
    

    def init(self):
        pass;

