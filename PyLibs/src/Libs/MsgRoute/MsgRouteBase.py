# -*- coding: utf-8 -*-

from Libs.Core.GObject import GObject;

class MsgRouteType(GObject):
    eMRT_BASIC = 0;      # 基本类型


class MsgRouteID(GObject):
    eMRIDSocketOpened = 0;      # socket Opened
    eMRIDSocketClosed = 1;      # socket Opened
    eMRIDLoadedWebRes = 2;      # web 资源加载完成
    eMRIDThreadLog = 3;         # 线程打日志


class MsgRouteBase(GObject):
    
    def __init__(self, uniqueId):
        super(GObject, self).__init__();
        
        self.mTypeId = "MsgRouteBase";

        self.m_msgType = MsgRouteType.eMRT_BASIC;
        self.m_msgID = uniqueId;


    def resetDefault(self):
        pass;

