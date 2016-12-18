# -*- coding: utf-8 -*-

from Libs.Core.GObject import GObject;
from Libs.DataStruct.MDictionary import MDictionary;
from Libs.EventHandle.AddOnceEventDispatch import AddOnceEventDispatch;

class MsgRouteHandleBase(GObject):
    def __init__(self):
        super(MsgRouteHandleBase, self).__init__();
        
        self.mTypeId = "MsgRouteHandleBase";
        
        self.mId2HandleDic = MDictionary();
        
        
    def addMsgRouteHandle(self, msgRouteID, handle):
        if(not self.mId2HandleDic.ContainsKey(msgRouteID)):
            self.mId2HandleDic[msgRouteID] = AddOnceEventDispatch();

        self.mId2HandleDic.value(msgRouteID).addEventHandle(None, handle);


    def removeMsgRouteHandle(self, msgRouteID, handle):
        if (self.mId2HandleDic.ContainsKey(msgRouteID)):
            self.mId2HandleDic.value(msgRouteID).removeEventHandle(None, handle);
          

    def handleMsg(self, msg):
        if (self.mId2HandleDic.ContainsKey(msg.m_msgID)):
            self.mId2HandleDic[msg.m_msgID].dispatchEvent(msg);
        else:
            # 输出日志
            pass;




