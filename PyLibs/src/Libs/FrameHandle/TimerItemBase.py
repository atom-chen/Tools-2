# -*- coding: utf-8 -*-

from Libs.Core.GObject import GObject;
from Libs.FrameHandle.TimerFunctionObject import TimerFunctionObject;

'''
@brief 定时器，这个是不断增长的
'''

class TimerItemBase(GObject):

    def __init__(self):
        super(TimerItemBase, self).__init__();
        
        self.mTypeId = "TimerItemBase";
        
        self.mInternal = 1;             # 定时器间隔
        self.mTotalTime = 1;            # 总共定时器时间
        self.mCurRunTime = 0;           # 当前定时器运行的时间
        self.mCurCallTime = 0;          # 当前定时器已经调用的时间
        self.mIsInfineLoop = False;      # 是否是无限循环
        self.mIntervalLeftTime = 0;     # 定时器调用间隔剩余时间
        self.mTimerDisp = TimerFunctionObject();    # 定时器分发
        self.mIsDisposed = False;         # 是否已经被释放
        self.mIsContinuous = False;      # 是否是连续的定时器


    def setFuncObject(self, handle):
        self.mTimerDisp.setFuncObject(handle);


    def setTotalTime(self, value):
        self.mTotalTime = value;


    def getRunTime(self):
        return self.mCurRunTime;


    def getCallTime(self):
        return self.mCurCallTime;


    def getLeftRunTime(self):
        return self.mTotalTime - self.mCurRunTime;


    def getLeftCallTime(self):
        return self.mTotalTime - self.mCurCallTime;


    # 在调用回调函数之前处理
    def onPreCallBack(self):
        pass;


    def OnTimer(self, delta):
        if (self.mIsDisposed):
            return;

        self.mCurRunTime += delta;
        if (self.mCurRunTime > self.mTotalTime):
            self.mCurRunTime = self.mTotalTime;

        self.mIntervalLeftTime += delta;

        if (self.mIsInfineLoop):
            self.checkAndDisp();
        else:
            if (self.mCurRunTime >= self.mTotalTime):
                self.disposeAndDisp();
            else:
                self.checkAndDisp();


    def disposeAndDisp(self):
        if (self.mIsContinuous):
            self.continueDisposeAndDisp();
        else:
            self.discontinueDisposeAndDisp();


    def continueDisposeAndDisp(self):
        self.mIsDisposed = True;

        while (self.mIntervalLeftTime >= self.mInternal and self.mCurCallTime < self.mTotalTime):
            self.mCurCallTime = self.mCurCallTime + self.mInternal;
            self.mIntervalLeftTime = self.mIntervalLeftTime - self.mInternal;
            self.onPreCallBack();

            if (self.mTimerDisp.isValid()):
                self.mTimerDisp.call(self);


    def discontinueDisposeAndDisp(self):
        self.mIsDisposed = True;
        self.mCurCallTime = self.mTotalTime;
        self.onPreCallBack();

        if (self.mTimerDisp.isValid()):
            self.mTimerDisp.call(self);


    def checkAndDisp(self):
        if(self.mIsContinuous):
            self.continueCheckAndDisp();
        else:
            self.discontinueCheckAndDisp();

    # 连续的定时器
    def continueCheckAndDisp(self):
        while (self.mIntervalLeftTime >= self.mInternal):
            # 这个地方 mCurCallTime 肯定会小于 mTotalTime，因为在调用这个函数的外部已经进行了判断
            self.mCurCallTime = self.mCurCallTime + self.mInternal;
            self.mIntervalLeftTime = self.mIntervalLeftTime - self.mInternal;
            self.onPreCallBack();

            if (self.mTimerDisp.isValid()):
                self.mTimerDisp.call(self);



    # 不连续的定时器
    def discontinueCheckAndDisp(self):
        if (self.mIntervalLeftTime >= self.mInternal):
            # 这个地方 mCurCallTime 肯定会小于 mTotalTime，因为在调用这个函数的外部已经进行了判断
            self.mCurCallTime = self.mCurCallTime + (((int)(self.mIntervalLeftTime / self.mInternal)) * self.mInternal);
            self.mIntervalLeftTime = self.mIntervalLeftTime % self.mInternal;   # 只保留余数
            self.onPreCallBack();

            if (self.mTimerDisp.isValid()):
                self.mTimerDisp.call(self);


    def reset(self):
        self.mCurRunTime = 0;
        self.mCurCallTime = 0;
        self.mIntervalLeftTime = 0;
        self.mIsDisposed = False;


    def setClientDispose(self):
        pass;


    def IsClientDispose(self):
        return False;

