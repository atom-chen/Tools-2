# -*- coding: utf-8 -*-

from Libs.Core.GObject import GObject
from Libs.DataStruct.MDictionary import MDictionary
from Libs.EventHandle.AddOnceEventDispatch import AddOnceEventDispatch

class MsgRouteHandleBase(GObject):
    def __init__(self):
        super(MsgRouteHandleBase, self).__init__();
        
        self.mTypeId = "MsgRouteHandleBase";
        
        self.m_id2HandleDic = MDictionary();
        
        
    def addMsgRouteHandle(self, msgRouteID, handle):
        if(not self.m_id2HandleDic.ContainsKey(msgRouteID)):
            self.m_id2HandleDic[msgRouteID] = AddOnceEventDispatch();

        self.m_id2HandleDic.value(msgRouteID).addEventHandle(None, handle);


    def removeMsgRouteHandle(self, msgRouteID, handle):
        if (self.m_id2HandleDic.ContainsKey(msgRouteID)):
            self.m_id2HandleDic.value(msgRouteID).removeEventHandle(None, handle);
          

    def handleMsg(self, msg):
        if (self.m_id2HandleDic.ContainsKey(msg.m_msgID)):
            self.m_id2HandleDic[msg.m_msgID].dispatchEvent(msg);
        else:
            # 输出日志
            pass;




