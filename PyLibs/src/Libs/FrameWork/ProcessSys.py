﻿#-*- encoding=utf-8 -*-

'''
@brief 系统循环
'''

from Libs.Core.GObject import GObject

class ProcessSys(GObject):
    
    def __init__(self):
        super(ProcessSys, self).__init__();
        
        self.mTypeId = "ProcessSys";


    def ProcessNextFrame(self):
        Ctx.msInstance.m_systemTimeData.nextFrame();
        self.Advance(Ctx.msInstance.m_systemTimeData.deltaSec);


    def Advance(self, delta):
        Ctx.m_instance.m_systemFrameData.nextFrame(delta);
        Ctx.m_instance.m_tickMgr.Advance(delta);                # 心跳
        //Ctx.m_instance.m_timerMgr.Advance(delta);             # 定时器
        //Ctx.m_instance.m_frameTimerMgr.Advance(delta);        # 帧定时器


