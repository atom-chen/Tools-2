#-*- encoding=utf-8 -*-

'''
@brief 全局数据区
'''

from Libs.Thread.MThread import MThread
from Libs.FrameHandle.ResizeMgr import ResizeMgr
from Libs.Task.TaskQueue import TaskQueue
from Libs.Task.TaskThreadPool import TaskThreadPool
from Libs.FrameHandle.SystemFrameData import SystemFrameData
from Libs.FrameHandle.SystemTimeData import SystemTimeData
from Libs.FrameHandle.TickMgr import TickMgr
from Libs.FrameHandle.TimerMgr import TimerMgr
from Libs.FrameHandle.FrameTimerMgr import FrameTimerMgr
from Libs.FrameWork.EngineLoop import EngineLoop
from Libs.Log.LogSys import LogSys
from Libs.FrameWork.CtxBase import CtxBase
from Libs.FrameWork.ProcessSys import ProcessSys
from Libs.MsgRoute.MsgRouteNotify import MsgRouteNotify
from Libs.MsgRoute.SysMsgRoute import SysMsgRoute

class Ctx(CtxBase):

    def __init__(self):
        super(Ctx, self).__init__();
        
        self.mTypeId = "Ctx";


    def preInit(self):
        MThread.getMainThreadID();  # 获取主线程 ID
        self.m_msgRouteNotify = MsgRouteNotify();
        
        self.m_TaskQueue = TaskQueue("TaskQueue");
        self.m_TaskThreadPool = TaskThreadPool();
        self.m_systemFrameData = SystemFrameData();
        self.m_systemTimeData = SystemTimeData();
        self.m_processSys = ProcessSys();
        self.m_tickMgr = TickMgr();
        self.m_timerMgr = TimerMgr();
        self.m_frameTimerMgr = FrameTimerMgr();
        self.m_engineLoop = EngineLoop();
        self.m_resizeMgr = ResizeMgr();
        self.m_sysMsgRoute = SysMsgRoute("SysMsgRoute");
        self.m_logSys = LogSys();


    def interInit(self):
        pass;


    def postInit(self):
        self.m_TaskQueue.m_pTaskThreadPool = self.m_TaskThreadPool;
        self.m_TaskThreadPool.initThreadPool(2, self.m_TaskQueue);


    def init(self):
        self.preInit();
        self.interInit();
        self.postInit();


    # 卸载所有的资源
    def unloadAll(self):
        pass;

