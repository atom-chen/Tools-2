# -*- coding: utf-8 -*-

from Libs.Core.GObject import GObject;
from Libs.DataStruct.LockList import LockList;

class LockQueue(GObject):
    
    def __init__(self, name = ""):
        super(LockQueue, self).__init__();
        
        self.mList = LockList();
        
        self.mName = name;
        

    def push(self, item):
        self.mList.Add(item);


    def pop(self):
        return self.mList.RemoveAt(0);


