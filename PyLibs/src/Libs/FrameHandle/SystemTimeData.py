# -*- coding: utf-8 -*-

from Libs.Core.GObject import GObject;
from Libs.Tools.UtilApi import UtilApi;

class SystemTimeData(GObject):

    def __init__(self):
        super(SystemTimeData, self).__init__();
        
        self.mTypeId = "SystemTimeData";
        
        self.mPreTime = 0;         # 上一次更新时的秒数
        self.mCurTime = 0;         # 正在获取的时间
        self.mDeltaSec = 0.0;     # 两帧之间的间隔


    def getDeltaSec(self):
        return self.mDeltaSec;
    

    def setDeltaSec(self, value):
        self.mDeltaSec = value;


    def getCurTime(self):
        return self.mCurTime;


    def setCurTime(self, value):
        self.mCurTime = value;


    def nextFrame(self):
        self.mCurTime = UtilApi.getTotalSeconds();
        if (self.mPreTime != 0):     # 第一帧跳过，因为这一帧不好计算间隔
            self.mDeltaSec = self.mCurTime - self.mPreTime;
        else:
            self.mDeltaSec = 1 / 24;        # 每秒 24 帧

        self.mPreTime = self.mCurTime;

