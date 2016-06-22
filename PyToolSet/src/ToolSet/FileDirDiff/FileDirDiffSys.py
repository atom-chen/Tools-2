# -*- coding: utf-8 -*-

'''
@author: FileDirDiffSys
'''

from Libs.Core.GObject import GObject;

class FileDirDiffSys(GObject):
    
    def __init__(self):
        super(FileDirDiffSys, self).__init__();
        
        self.mTypeId = "FileDirDiffSys";
        
        self.mVerConfig = None;
        self.m_bOverVer = True;
        self.mVerProcess = None;


    def start(self):
        self.mConfig.readInit('Config/Config.txt');
        
        
    def isVersionOver(self):
        if(self.mVerProcess != None and self.mVerProcess.isValid()):
            self.m_bOverVer = not self.mVerProcess.is_alive();
        else:
            self.m_bOverVer = True;
        return self.m_bOverVer;
    
    
    def startVerProcess(self):
        pass



