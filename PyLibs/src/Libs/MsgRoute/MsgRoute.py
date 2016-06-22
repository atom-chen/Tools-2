# -*- coding: utf-8 -*-

from Libs.MsgRoute.MsgRouteBase import MsgRouteBase, MsgRouteID;

class SocketOpenedMR(MsgRouteBase):
    def __init__(self):
        super(SocketOpenedMR, self).__init__(MsgRouteID.eMRIDSocketOpened);

        self.mTypeId = "SocketOpenedMR";


class SocketCloseedMR(MsgRouteBase):
    
    def __init__(self):
        super(SocketCloseedMR, self).__init__(MsgRouteID.eMRIDSocketClosed);
        
        self.mTypeId = "SocketCloseedMR";


class LoadedWebResMR(MsgRouteBase):

    def __init__(self):
        super(LoadedWebResMR, self).__init__(MsgRouteID.eMRIDLoadedWebRes);

        self.mTypeId = "LoadedWebResMR";


    def resetDefault(self):
        self.m_task = None;


# 线程日志
class ThreadLogMR(MsgRouteBase):

    def __init__(self):
        super(ThreadLogMR, self).__init__(MsgRouteID.eMRIDThreadLog);

        self.mTypeId = "ThreadLogMR";
        
        self.m_logSys = "";

