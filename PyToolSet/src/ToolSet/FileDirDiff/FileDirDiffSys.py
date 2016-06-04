# -*- coding: utf-8 -*-

'''
@author: FileDirDiffSys
'''

from Libs.Core.GObject import GObject

class FileDirDiffSys(GObject):
    
    def __init__(self):
        super(FileDirDiffSys, self).__init__();
        
        self.mTypeId = "FileDirDiffSys";
        
        self
        
    def start(self):
        AppSysBase.instance().m_config.readInit('Config/Config.txt')