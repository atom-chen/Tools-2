# -*- coding: utf-8 -*-

from Libs.Core.GObject import GObject;
from Libs.Tools.UtilApi import UtilApi;

class SystemTimeData(GObject):

    def __init__(self):
        super(SystemTimeData, self).__init__();
        
        self.mTypeId = "SystemTimeData";
        
        self.m_preTime = 0;         # 上一次更新时的秒数
        self.m_curTime = 0;         # 正在获取的时间
        self.m_deltaSec = 0.0;     # 两帧之间的间隔


    def getDeltaSec(self):
        return self.m_deltaSec;
    

    def setDeltaSec(self, value):
        self.m_deltaSec = value;


    def getCurTime(self):
        return self.m_curTime;


    def setCurTime(self, value):
        self.m_curTime = value;


    def nextFrame(self):
        self.m_curTime = UtilApi.getTotalSeconds();
        if (self.m_preTime != 0):     # 第一帧跳过，因为这一帧不好计算间隔
            self.m_deltaSec = self.m_curTime - self.m_preTime;
        else:
            self.m_deltaSec = 1 / 24;        # 每秒 24 帧

        self.m_preTime = self.m_curTime;

