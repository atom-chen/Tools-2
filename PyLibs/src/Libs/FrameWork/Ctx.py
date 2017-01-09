# -*- coding: utf-8 -*-

'''
@brief: Ctx
'''

from Libs.Core.GObject import GObject;
from Libs.Tools.UtilError import UtilError;

class Ctx(GObject):
    
    msInstance = None;
    
    @staticmethod
    def setInstance(ins):
        if (Ctx.msInstance == None):
            Ctx.msInstance = ins;
        else:
            UtilError.error("Ins Can not Ins Twice");   
    
    
    
    @staticmethod
    def instance():
        #if (Ctx.msInstance == None):
        #    Ctx.msInstance = Ctx();

        return Ctx.msInstance;

    
    def __init__(self):
        super(Ctx, self).__init__();
        
        self.mTypeId = "CtxImpl";
        
        # 声明需要的变量，当然也可以不必在这里声明，直接赋值就行了
        self.mMsgRouteNotify = None;
        self.mTaskQueue = None;
        self.mTaskThreadPool = None;
        self.mSystemFrameData = None;
        self.mSystemTimeData = None;
        self.mProcessSys = None;
        self.mTickMgr = None;
        self.mTimerMgr = None;
        self.mFrameTimerMgr = None;
        self.mEngineLoop = None;
        self.mResizeMgr = None;
        self.mSysMsgRoute = None;
        self.mLogSys = None;


    def init(self):
        pass;


