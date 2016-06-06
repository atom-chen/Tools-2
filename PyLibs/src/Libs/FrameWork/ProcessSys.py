# -*- coding: utf-8 -*-

'''
@brief 系统循环
'''

from Libs.Core.GObject import GObject
from Libs.FrameWork.Ctx import Ctx

class ProcessSys(GObject):
    
    def __init__(self):
        super(ProcessSys, self).__init__();
        
        self.mTypeId = "ProcessSys";


    def ProcessNextFrame(self):
        Ctx.instance().m_systemTimeData.nextFrame();
        self.Advance(Ctx.instance().m_systemTimeData.deltaSec);


    def Advance(self, delta):
        Ctx.instance().m_systemFrameData.nextFrame(delta);
        Ctx.instance().m_tickMgr.Advance(delta);                # 心跳
        Ctx.instance().m_timerMgr.Advance(delta);               # 定时器
        Ctx.instance().m_frameTimerMgr.Advance(delta);          # 帧定时器


