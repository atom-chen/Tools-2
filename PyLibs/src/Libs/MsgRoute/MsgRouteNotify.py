# -*- coding: utf-8 -*-

from Libs.Core.GObject import GObject;
from Libs.DataStruct.MList import MList;

class MsgRouteNotify(GObject):

    def __init__(self):
        super(MsgRouteNotify, self).__init__();

        self.mTypeId = "MsgRouteNotify";
        
        self.mDispList = MList();
 

    def addOneDisp(self, disp):   
        if(self.mDispList.IndexOf(disp) == -1):
            self.mDispList.Add(disp);



    def emoveOneDisp(self, disp):
        if(self.mDispList.IndexOf(disp) != -1):
            self.mDispList.Remove(disp);


    def handleMsg(self, msg):
        for item in self.mDispList:
            item.handleMsg(msg);


