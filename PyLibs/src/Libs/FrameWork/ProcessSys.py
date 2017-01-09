# -*- coding: utf-8 -*-

'''
@brief 系统循环
'''

from Libs.Core.GObject import GObject;
from Libs.FrameWork.Ctx import Ctx;

class ProcessSys(GObject):
    
    def __init__(self):
        super(ProcessSys, self).__init__();
        
        self.mTypeId = "ProcessSys";


    def ProcessNextFrame(self):
        Ctx.instance().mSystemTimeData.nextFrame();
        self.Advance(Ctx.instance().mSystemTimeData.getDeltaSec());


    def Advance(self, delta):
        Ctx.instance().mSystemFrameData.nextFrame(delta);
        Ctx.instance().mTickMgr.Advance(delta);                # 心跳
        Ctx.instance().mTimerMgr.Advance(delta);               # 定时器
        Ctx.instance().mFrameTimerMgr.Advance(delta);          # 帧定时器


