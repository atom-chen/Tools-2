#-*- encoding=utf-8 -*-


from ProtocolAnalysis.DataStruct.MDictionary import MDictionary
from ProtocolAnalysis.Core.AppSysBase import AppSysBase


class EventDispatchGroup(object):
    '''
    classdocs
    '''


    def __init__(self):
        '''
        Constructor
        '''
        self.m_groupID2DispatchDic = MDictionary()
        self.m_bInLoop = False       # 是否是在循环遍历中


    # 添加分发器
    def addEventDispatch(self, groupID, disp):
        if self.m_groupID2DispatchDic.ContainsKey(groupID):
            self.m_groupID2DispatchDic[groupID] = disp


    def addEventHandle(self, groupID, handle):
        self.m_groupID2DispatchDic[groupID].addEventHandle(handle)


    def removeEventHandle(self, groupID, handle):
        if self.m_groupID2DispatchDic.ContainsKey(groupID):
            self.m_groupID2DispatchDic[groupID].removeEventHandle(handle)
        else:
            AppSysBase.instance().m_logSys.log("Event Dispatch Group not exist")


    def dispatchEvent(self, groupID, dispatchObject):
        self.m_bInLoop = True
        if self.m_groupID2DispatchDic.ContainsKey(groupID):
            self.m_groupID2DispatchDic[groupID].dispatchEvent(dispatchObject)
        else:
            AppSysBase.instance().m_logSys.log("Event Dispatch Group not exist")
        self.m_bInLoop = False;


    def clearAllEventHandle(self):
        if not self.m_bInLoop:
            for dispatch in self.m_groupID2DispatchDic.Values():
                dispatch.clearEventHandle()

            self.m_groupID2DispatchDic.Clear()
        else:
            AppSysBase.instance().m_logSys.log("looping cannot delete element");


    def clearGroupEventHandle(self, groupID):
        if not self.m_bInLoop:
            if self.m_groupID2DispatchDic.ContainsKey(groupID):
                self.m_groupID2DispatchDic[groupID].clearEventHandle()
                self.m_groupID2DispatchDic.Remove(groupID)
            else:
                AppSysBase.instance().m_logSys.log("Event Dispatch Group not exist");
        else:
            AppSysBase.instance().m_logSys.log("looping cannot delete element");

