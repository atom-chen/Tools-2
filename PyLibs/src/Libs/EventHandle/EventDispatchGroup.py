# -*- coding: utf-8 -*-

from Libs.Core.GObject import GObject
from Libs.DataStruct.MDictionary import MDictionary
from Libs.EventHandle.EventDispatch import EventDispatch

class EventDispatchGroup(GObject):

    def __init__(self):
        super(EventDispatchGroup, self).__init__();
        
        self.mTypeId = "EventDispatchGroup";
        
        self.m_groupID2DispatchDic = MDictionary();
        self.m_bInLoop = False;          # 是否是在循环遍历中


    # 添加分发器
    def addEventDispatch(self, groupID, disp):
        if (not self.m_groupID2DispatchDic.ContainsKey(groupID)):
            self.m_groupID2DispatchDic.Add(groupID, disp);


    def addEventHandle(self, groupID, handle):
        # 如果没有就创建一个
        if (not self.m_groupID2DispatchDic.ContainsKey(groupID)):
            self.addEventDispatch(groupID, EventDispatch());

        self.m_groupID2DispatchDic.value(groupID).addEventHandle(None, handle);


    def removeEventHandle(self, groupID, handle):
        if (self.m_groupID2DispatchDic.ContainsKey(groupID)):
            self.m_groupID2DispatchDic.value(groupID).removeEventHandle(None, handle);

            # 如果已经没有了
            if (self.m_groupID2DispatchDic.value(groupID).getHandleCount() == 0):
                self.m_groupID2DispatchDic.Remove(groupID);
        else:
            # 输出日志
            pass;


    def dispatchEvent(self, groupID, dispatchObject):
        self.m_bInLoop = True;
        if (self.m_groupID2DispatchDic.ContainsKey(groupID)):
            self.m_groupID2DispatchDic.value(groupID).dispatchEvent(dispatchObject);
        else:
            # 输出日志
            pass;

        self.m_bInLoop = False;


    def clearAllEventHandle(self):
        if (not self.m_bInLoop):
            for (_, dispatch) in self.m_groupID2DispatchDic.items():
                dispatch.clearEventHandle();

            self.m_groupID2DispatchDic.Clear();
        else:
            # 输出日志
            pass;


    def clearGroupEventHandle(self, groupID):
        if (not self.m_bInLoop):
            if (self.m_groupID2DispatchDic.ContainsKey(groupID)):
                self.m_groupID2DispatchDic.value(groupID).clearEventHandle();
                self.m_groupID2DispatchDic.Remove(groupID);
            else:
                # 输出日志
                pass;
        else:
            # 输出日志
            pass;

