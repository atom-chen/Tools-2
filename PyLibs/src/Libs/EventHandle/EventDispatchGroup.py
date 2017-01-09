# -*- coding: utf-8 -*-

from Libs.Core.GObject import GObject;
from Libs.DataStruct.MDictionary import MDictionary;
from Libs.EventHandle.EventDispatch import EventDispatch;

class EventDispatchGroup(GObject):

    def __init__(self):
        super(EventDispatchGroup, self).__init__();
        
        self.mTypeId = "EventDispatchGroup";
        
        self.mGroupID2DispatchDic = MDictionary();
        self.mIsInLoop = False;          # 是否是在循环遍历中


    # 添加分发器
    def addEventDispatch(self, groupID, disp):
        if (not self.mGroupID2DispatchDic.ContainsKey(groupID)):
            self.mGroupID2DispatchDic.Add(groupID, disp);


    def addEventHandle(self, groupID, handle):
        # 如果没有就创建一个
        if (not self.mGroupID2DispatchDic.ContainsKey(groupID)):
            self.addEventDispatch(groupID, EventDispatch());

        self.mGroupID2DispatchDic.value(groupID).addEventHandle(None, handle);


    def removeEventHandle(self, groupID, handle):
        if (self.mGroupID2DispatchDic.ContainsKey(groupID)):
            self.mGroupID2DispatchDic.value(groupID).removeEventHandle(None, handle);

            # 如果已经没有了
            if (self.mGroupID2DispatchDic.value(groupID).getHandleCount() == 0):
                self.mGroupID2DispatchDic.Remove(groupID);
        else:
            # 输出日志
            pass;


    def dispatchEvent(self, groupID, dispatchObject):
        self.mIsInLoop = True;
        if (self.mGroupID2DispatchDic.ContainsKey(groupID)):
            self.mGroupID2DispatchDic.value(groupID).dispatchEvent(dispatchObject);
        else:
            # 输出日志
            pass;

        self.mIsInLoop = False;


    def clearAllEventHandle(self):
        if (not self.mIsInLoop):
            for (_, dispatch) in self.mGroupID2DispatchDic.items():
                dispatch.clearEventHandle();

            self.mGroupID2DispatchDic.Clear();
        else:
            # 输出日志
            pass;


    def clearGroupEventHandle(self, groupID):
        if (not self.mIsInLoop):
            if (self.mGroupID2DispatchDic.ContainsKey(groupID)):
                self.mGroupID2DispatchDic.value(groupID).clearEventHandle();
                self.mGroupID2DispatchDic.Remove(groupID);
            else:
                # 输出日志
                pass;
        else:
            # 输出日志
            pass;

