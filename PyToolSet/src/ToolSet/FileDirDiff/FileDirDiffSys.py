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
        self.m_bOverVer = True;
        self.mVerProcess = None;


    def start(self):
        self.mConfig.readInit('Config/Config.txt');
        
        
    def isVersionOver(self):
        return self.m_bOverVer;
    
    
    def startVerProcess(self):
        pass



