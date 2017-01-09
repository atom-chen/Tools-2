# -*- coding: utf-8 -*-

from Libs.Core.GObject import GObject;

class SystemFrameData(GObject):
    
    def __init__(self):
        super(SystemFrameData, self).__init__();
        
        self.mTypeId = "SystemFrameData";
        
        self.mTotalFrameCount = 0;         # 当前帧数
        self.mCurFrameCount = 0;           # 当前帧数
        self.mCurTime = 0;                 # 当前一秒内时间
        self.mFps = 0;                     # 帧率
        
    def nextFrame(self, delta):
        self.mTotalFrameCount = self.mTotalFrameCount + 1;
        self.mCurFrameCount = self.mCurFrameCount + 1;
        self.mCurTime += delta;

        if(self.mCurTime > 1.0):
            self.mFps = (int)(self.mCurFrameCount / self.mCurTime);
            self.mCurFrameCount = 0;
            self.mCurTime = 0;

            # 输出日志


