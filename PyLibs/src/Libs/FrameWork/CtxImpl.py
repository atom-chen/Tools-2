﻿#-*- encoding=utf-8 -*-

'''
@brief: CtxImpl
'''

from Libs.FrameWork.Ctx import Ctx

class CtxImpl(Ctx):
    
    def __init__(self):
        super(Ctx, self).__init__();
        
        self.mTypeId = "CtxImpl";
        
        # 声明需要的变量，当然也可以不必在这里声明，直接赋值就行了
        self.m_msgRouteNotify = None;
        self.m_TaskQueue = None;
        self.m_TaskThreadPool = None;
        self.m_systemFrameData = None;
        self.m_systemTimeData = None;
        self.m_processSys = None;
        self.m_tickMgr = None;
        self.m_timerMgr = None;
        self.m_frameTimerMgr = None;
        self.m_engineLoop = None;
        self.m_resizeMgr = None;
        self.m_sysMsgRoute = None;
        self.m_logSys = None;


    def init(self):
        pass;

