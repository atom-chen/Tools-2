# -*- coding: utf-8 -*-

'''
@brief: VersionProcess
'''

from Libs.Thread.MProcess import MProcess

class VersionProcess(MProcess):
    
    def __init__(self):
        super(VersionProcess, self).__init__("VersionProcess", None);
        
        self.mTypeId = "VersionProcess";
    
    def run(self, params):
        super(VersionProcess, self).run(params);
        
        
        
