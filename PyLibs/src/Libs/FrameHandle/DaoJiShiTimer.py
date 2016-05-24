#-*- encoding=utf-8 -*-

'''
@brief 倒计时定时器
'''

from Libs.FrameHandle.TimerItemBase import TimerItemBase

class DaoJiShiTimer(TimerItemBase):
    
    def __init__(self):
        super(DaoJiShiTimer, self).__init__();
    
    def setTotalTime(self, value):
        super(DaoJiShiTimer, self).setTotalTime(value);
        self.m_curRunTime = value;


    def getRunTime(self):
        return self.m_totalTime - self.m_curRunTime;


    # 如果要获取剩余的倒计时时间，使用 getLeftCallTime
    def getLeftRunTime(self):
        return self.m_curRunTime;


    def OnTimer(self, delta):
        if (self.m_disposed):
            return;

        self.m_curRunTime -= delta;
        if(self.m_curRunTime < 0):
            self.m_curRunTime = 0;

        self.m_intervalLeftTime += delta;

        if (self.m_bInfineLoop):
            self.checkAndDisp();
        else:
            if (self.m_curRunTime <= 0):
                self.disposeAndDisp();
            else:
                self.checkAndDisp();



    def reset(self):
        self.m_curRunTime = self.m_totalTime;
        self.m_curCallTime = 0;
        self.m_intervalLeftTime = 0;
        self.m_disposed = False;

