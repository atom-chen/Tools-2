# -*- coding: utf-8 -*-

'''
@brief: 
'''

from Libs.Core.GObject import GObject

class VerProcessSys(GObject):
    
    msInstance = None;
    
    @staticmethod
    def instance():
        if(VerProcessSys.msInstance == None):
            VerProcessSys.msInstance = VerProcessSys();
            
        return VerProcessSys.msInstance;


    def __init__(self):
        super(VerProcessSys, self).__init__();
        
        self.mTypeId = "VerProcessSys";

        self.mParams = None;

