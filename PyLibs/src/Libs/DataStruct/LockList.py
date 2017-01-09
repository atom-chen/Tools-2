# -*- coding: utf-8 -*-

'''
@brief 线程安全列表， T 是 Object ，便于使用 Equal 比较地址
'''

from Libs.Core.GObject import GObject;
from Libs.Thread.MMutex import MMutex;
from Libs.DataStruct.MList import MList;

class LockList(GObject):

    def __init__(self):
        super(LockList, self).__init__();
        
        self.mTypeId = "LockList";
        
        self.mVisitMutex = MMutex();
        self.mList = MList();


    def Count(self): 
        self.mVisitMutex.lock();
        return self.mList.length();
        self.mVisitMutex.unlock();


    def Add(self, item):
        self.mVisitMutex.lock();
        self.mList.Add(item);
        self.mVisitMutex.unlock();

    def Remove(self, item):
        self.mVisitMutex.lock();
        self.mList.Remove(item);
        self.mVisitMutex.unlock();


    def RemoveAt(self, index):
        self.mVisitMutex.lock();
        self.mList.RemoveAt(index);
        self.mVisitMutex.unlock();


    def IndexOf(self, item):
        self.mVisitMutex.lock();
        self.mList.IndexOf(item);
        self.mVisitMutex.unlock();


