#-*- encoding=utf-8 -*-

'''
@brief 定时器，这个是不断增长的
'''

from Libs.Core.GObject import GObject
from Libs.FrameHandle.TimerFunctionObject import TimerFunctionObject

class TimerItemBase(GObject):

    def __init__(self):
        super(TimerItemBase, self).__init__();
        
        self.mTypeId = "TimerItemBase";
        
        self.m_internal = 1;             # 定时器间隔
        self.m_totalTime = 1;            # 总共定时器时间
        self.m_curRunTime = 0;           # 当前定时器运行的时间
        self.m_curCallTime = 0;          # 当前定时器已经调用的时间
        self.m_bInfineLoop = False;      # 是否是无限循环
        self.m_intervalLeftTime = 0;     # 定时器调用间隔剩余时间
        self.m_timerDisp = TimerFunctionObject();    # 定时器分发
        self.m_disposed = False;         # 是否已经被释放
        self.m_bContinuous = False;      # 是否是连续的定时器


    def setFuncObject(self, handle):
        self.m_timerDisp.setFuncObject(handle);


    def setTotalTime(self, value):
        self.m_totalTime = value;


    def getRunTime(self):
        return self.m_curRunTime;


    def getCallTime(self):
        return self.m_curCallTime;


    def getLeftRunTime(self):
        return self.m_totalTime - self.m_curRunTime;


    def getLeftCallTime(self):
        return self.m_totalTime - self.m_curCallTime;


    # 在调用回调函数之前处理
    def onPreCallBack(self):
        pass;


    def OnTimer(self, delta):
        if (self.m_disposed):
            return;

        self.m_curRunTime += delta;
        if (self.m_curRunTime > self.m_totalTime):
            self.m_curRunTime = self.m_totalTime;

        self.m_intervalLeftTime += delta;

        if (self.m_bInfineLoop):
            self.checkAndDisp();
        else:
            if (self.m_curRunTime >= self.m_totalTime):
                self.disposeAndDisp();
            else:
                self.checkAndDisp();


    def disposeAndDisp(self):
        if (self.m_bContinuous):
            self.continueDisposeAndDisp();
        else:
            self.discontinueDisposeAndDisp();


    def continueDisposeAndDisp(self):
        self.m_disposed = True;

        while (self.m_intervalLeftTime >= self.m_internal and self.m_curCallTime < self.m_totalTime):
            self.m_curCallTime = self.m_curCallTime + self.m_internal;
            self.m_intervalLeftTime = self.m_intervalLeftTime - self.m_internal;
            self.onPreCallBack();

            if (self.m_timerDisp.isValid()):
                self.m_timerDisp.call(self);


    def discontinueDisposeAndDisp(self):
        self.m_disposed = True;
        self.m_curCallTime = self.m_totalTime;
        self.onPreCallBack();

        if (self.m_timerDisp.isValid()):
            self.m_timerDisp.call(self);


    def checkAndDisp(self):
        if(self.m_bContinuous):
            self.continueCheckAndDisp();
        else:
            self.discontinueCheckAndDisp();

    # 连续的定时器
    def continueCheckAndDisp(self):
        while (self.m_intervalLeftTime >= self.m_internal):
            # 这个地方 m_curCallTime 肯定会小于 m_totalTime，因为在调用这个函数的外部已经进行了判断
            self.m_curCallTime = self.m_curCallTime + self.m_internal;
            self.m_intervalLeftTime = self.m_intervalLeftTime - self.m_internal;
            self.onPreCallBack();

            if (self.m_timerDisp.isValid()):
                self.m_timerDisp.call(self);



    # 不连续的定时器
    def discontinueCheckAndDisp(self):
        if (self.m_intervalLeftTime >= self.m_internal):
            # 这个地方 m_curCallTime 肯定会小于 m_totalTime，因为在调用这个函数的外部已经进行了判断
            self.m_curCallTime = self.m_curCallTime + (((int)(self.m_intervalLeftTime / self.m_internal)) * self.m_internal);
            self.m_intervalLeftTime = self.m_intervalLeftTime % self.m_internal;   # 只保留余数
            self.onPreCallBack();

            if (self.m_timerDisp.isValid()):
                self.m_timerDisp.call(self);


    def reset(self):
        self.m_curRunTime = 0;
        self.m_curCallTime = 0;
        self.m_intervalLeftTime = 0;
        self.m_disposed = False;


    def setClientDispose(self):
        pass;


    def getClientDispose(self):
        return False;

