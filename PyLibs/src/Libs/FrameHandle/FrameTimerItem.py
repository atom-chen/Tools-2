# -*- coding: utf-8 -*-

from Libs.DelayHandle.IDelayHandleItem import IDelayHandleItem;

'''
@brief 定时器，这个是不断增长的
'''

class FrameTimerItem(IDelayHandleItem):
    def __init__(self):
        super(FrameTimerItem, self).__init__();
        
        self.mTypeId = "FrameTimerItem";
        
        self.mInternal = 1;            # 帧数间隔
        self.mTotalFrameCount = 1;     # 当前已经调用的定时器的时间
        self.mCurFrame = 0;            # 剩余帧数
        self.mIsInfineLoop = False;     # 是否是无限循环
        self.mCurLeftFrame = 0;        
        self.mTimerDisp = None;        # 定时器分发
        self.mIsDisposed = False;        # 是否已经被释放


    def OnFrameTimer(self):
        if (self.mIsDisposed):
            return;

        self.mCurFrame = self.mCurFrame + 1;
        self.mCurLeftFrame = self.mCurLeftFrame + 1;

        if (self.mIsInfineLoop):
            if (self.mCurLeftFrame == self.mInternal):
                self.mCurLeftFrame = 0;

                if (self.mTimerDisp != None):
                    self.mTimerDisp(self);
        else:
            if (self.mCurFrame == self.mTotalFrameCount):
                self.mIsDisposed = True;
                if (self.mTimerDisp != None):
                    self.mTimerDisp(self);
            else:
                if (self.mCurLeftFrame == self.mInternal):
                    self.mCurLeftFrame = 0;
                    if (self.mTimerDisp != None):
                        self.mTimerDisp(self);


    def reset(self):
        self.mCurFrame = 0;
        self.mCurLeftFrame = 0;
        self.mIsDisposed = False;


    def setClientDispose(self):
        pass;


    def IsClientDispose(self):
        return False;

