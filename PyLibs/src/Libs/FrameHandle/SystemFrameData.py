# -*- coding: utf-8 -*-

from Libs.Core.GObject import GObject;

class SystemFrameData(GObject):
    
    def __init__(self):
        super(SystemFrameData, self).__init__();
        
        self.mTypeId = "SystemFrameData";
        
        self.m_totalFrameCount = 0;         # 当前帧数
        self.m_curFrameCount = 0;           # 当前帧数
        self.m_curTime = 0;                 # 当前一秒内时间
        self.m_fps = 0;                     # 帧率
        
    def nextFrame(self, delta):
        self.m_totalFrameCount = self.m_totalFrameCount + 1;
        self.m_curFrameCount = self.m_curFrameCount + 1;
        self.m_curTime += delta;

        if(self.m_curTime > 1.0):
            self.m_fps = (int)(self.m_curFrameCount / self.m_curTime);
            self.m_curFrameCount = 0;
            self.m_curTime = 0;

            # 输出日志


