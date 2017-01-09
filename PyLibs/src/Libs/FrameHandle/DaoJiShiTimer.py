# -*- coding: utf-8 -*-

from Libs.FrameHandle.TimerItemBase import TimerItemBase;

'''
@brief 倒计时定时器
'''

class DaoJiShiTimer(TimerItemBase):
    
    def __init__(self):
        super(DaoJiShiTimer, self).__init__();
        
        self.mTypeId = "DaoJiShiTimer";

    
    def setTotalTime(self, value):
        super(DaoJiShiTimer, self).setTotalTime(value);
        self.mCurRunTime = value;


    def getRunTime(self):
        return self.mTotalTime - self.mCurRunTime;


    # 如果要获取剩余的倒计时时间，使用 getLeftCallTime
    def getLeftRunTime(self):
        return self.mCurRunTime;


    def OnTimer(self, delta):
        if (self.mIsDisposed):
            return;

        self.mCurRunTime -= delta;
        if(self.mCurRunTime < 0):
            self.mCurRunTime = 0;

        self.mIntervalLeftTime += delta;

        if (self.mIsInfineLoop):
            self.checkAndDisp();
        else:
            if (self.mCurRunTime <= 0):
                self.disposeAndDisp();
            else:
                self.checkAndDisp();



    def reset(self):
        self.mCurRunTime = self.mTotalTime;
        self.mCurCallTime = 0;
        self.mIntervalLeftTime = 0;
        self.mIsDisposed = False;

