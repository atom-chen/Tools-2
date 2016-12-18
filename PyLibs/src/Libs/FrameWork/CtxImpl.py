# -*- coding: utf-8 -*-

'''
@brief Ctx，基类，防止模块之间互相导入
'''

from Libs.Thread.MThread import MThread;
from Libs.FrameHandle.ResizeMgr import ResizeMgr;
from Libs.Task.TaskQueue import TaskQueue;
from Libs.Task.TaskThreadPool import TaskThreadPool;
from Libs.FrameHandle.SystemFrameData import SystemFrameData;
from Libs.FrameHandle.SystemTimeData import SystemTimeData;
from Libs.FrameHandle.TickMgr import TickMgr;
from Libs.FrameHandle.TimerMgr import TimerMgr;
from Libs.FrameHandle.FrameTimerMgr import FrameTimerMgr;
from Libs.FrameWork.EngineLoop import EngineLoop;
from Libs.Log.LogSys import LogSys;
from Libs.FrameWork.ProcessSys import ProcessSys;
from Libs.MsgRoute.MsgRouteNotify import MsgRouteNotify;
from Libs.MsgRoute.SysMsgRoute import SysMsgRoute;
from Libs.FrameWork.Ctx import Ctx;

class CtxImpl(Ctx):
    
    def __init__(self):
        super(Ctx, self).__init__();
        
        self.mTypeId = "Ctx";


    def preInit(self):
        MThread.getMainThreadID();  # 获取主线程 ID
        self.mMsgRouteNotify = MsgRouteNotify();
        
        self.mTaskQueue = TaskQueue("TaskQueue");
        self.mTaskThreadPool = TaskThreadPool();
        self.mSystemFrameData = SystemFrameData();
        self.mSystemTimeData = SystemTimeData();
        self.mProcessSys = ProcessSys();
        self.mTickMgr = TickMgr();
        self.mTimerMgr = TimerMgr();
        self.mFrameTimerMgr = FrameTimerMgr();
        self.mEngineLoop = EngineLoop();
        self.mResizeMgr = ResizeMgr();
        self.mSysMsgRoute = SysMsgRoute("SysMsgRoute");
        self.mLogSys = LogSys();


    def interInit(self):
        pass;


    def postInit(self):
        self.mTaskQueue.mTaskThreadPool = self.mTaskThreadPool;
        self.mTaskThreadPool.initThreadPool(2, self.mTaskQueue);


    def init(self):
        super(CtxImpl, self).init();
        self.preInit();
        self.interInit();
        self.postInit();


    # 卸载所有的资源
    def unloadAll(self):
        pass;

