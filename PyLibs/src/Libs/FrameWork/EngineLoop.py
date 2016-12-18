# -*- coding: utf-8 -*-

'''
@brief 主循环
'''

from Libs.Core.GObject import GObject;
from Libs.FrameWork.Ctx import Ctx;

class EngineLoop(GObject):
    
    def __init__(self):
        super(EngineLoop, self).__init__();
        
        self.mTypeId = "EngineLoop";
        
        
    
    def mainLoop(self):
        # 游戏循环处理
        Ctx.instance().mProcessSys.ProcessNextFrame();
        Ctx.instance().mLogSys.updateLog();

