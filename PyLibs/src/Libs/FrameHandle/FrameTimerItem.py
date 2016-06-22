# -*- coding: utf-8 -*-

from Libs.DelayHandle.IDelayHandleItem import IDelayHandleItem;

'''
@brief 定时器，这个是不断增长的
'''

class FrameTimerItem(IDelayHandleItem):
    def __init__(self):
        super(FrameTimerItem, self).__init__();
        
        self.mTypeId = "FrameTimerItem";
        
        self.m_internal = 1;            # 帧数间隔
        self.m_totalFrameCount = 1;     # 当前已经调用的定时器的时间
        self.m_curFrame = 0;            # 剩余帧数
        self.m_bInfineLoop = False;     # 是否是无限循环
        self.m_curLeftFrame = 0;        
        self.m_timerDisp = None;        # 定时器分发
        self.m_disposed = False;        # 是否已经被释放


    def OnFrameTimer(self):
        if (self.m_disposed):
            return;

        self.m_curFrame = self.m_curFrame + 1;
        self.m_curLeftFrame = self.m_curLeftFrame + 1;

        if (self.m_bInfineLoop):
            if (self.m_curLeftFrame == self.m_internal):
                self.m_curLeftFrame = 0;

                if (self.m_timerDisp != None):
                    self.m_timerDisp(self);
        else:
            if (self.m_curFrame == self.m_totalFrameCount):
                self.m_disposed = True;
                if (self.m_timerDisp != None):
                    self.m_timerDisp(self);
            else:
                if (self.m_curLeftFrame == self.m_internal):
                    self.m_curLeftFrame = 0;
                    if (self.m_timerDisp != None):
                        self.m_timerDisp(self);


    def reset(self):
        self.m_curFrame = 0;
        self.m_curLeftFrame = 0;
        self.m_disposed = False;


    def setClientDispose(self):
        pass;


    def getClientDispose(self):
        return False;

