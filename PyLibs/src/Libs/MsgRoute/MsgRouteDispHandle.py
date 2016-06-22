# -*- coding: utf-8 -*-

from Libs.Core.GObject import GObject;
from Libs.DataStruct.MDictionary import MDictionary;

class MsgRouteDispHandle(GObject):

    def __init__(self):
        super(MsgRouteDispHandle, self).__init__();
        
        self.mTypeId = "MsgRouteDispHandle";
        
        self.m_id2DispDic = MDictionary();


    def handleMsg(self, msg):
        if (self.m_id2DispDic.ContainsKey(msg.m_msgType)):
            self.m_id2DispDic[msg.m_msgType].handleMsg(msg);
        else:
            # 输出日志
            pass;


