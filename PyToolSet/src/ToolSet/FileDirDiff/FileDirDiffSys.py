# -*- coding: utf-8 -*-

'''
@author: FileDirDiffSys
'''

from Libs.Core.GObject import GObject
from ToolSet.FileDirDiff.Config import Config

class FileDirDiffSys(GObject):
    
    def __init__(self):
        super(FileDirDiffSys, self).__init__();
        
        self.mTypeId = "FileDirDiffSys";
        
        self.mConfig = Config();


    def start(self):
        self.mConfig.readInit('Config/Config.txt');


