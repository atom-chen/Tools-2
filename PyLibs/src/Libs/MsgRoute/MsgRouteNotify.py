# -*- coding: utf-8 -*-

from Libs.Core.GObject import GObject
from Libs.DataStruct.MList import MList

class MsgRouteNotify(GObject):

    def __init__(self):
        super(MsgRouteNotify, self).__init__();

        self.mTypeId = "MsgRouteNotify";
        
        self.m_dispList = MList();
 

    def addOneDisp(self, disp):   
        if(self.m_dispList.IndexOf(disp) == -1):
            self.m_dispList.Add(disp);



    def emoveOneDisp(self, disp):
        if(self.m_dispList.IndexOf(disp) != -1):
            self.m_dispList.Remove(disp);


    def handleMsg(self, msg):
        for item in self.m_dispList:
            item.handleMsg(msg);


