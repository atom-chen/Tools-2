# -*- coding: utf-8 -*-

from Libs.Core.GObject import GObject;
from Libs.Thread.MMutex import MMutex;
from Libs.DataStruct.MList import MList;

'''
@brief 线程安全列表， T 是 Object ，便于使用 Equal 比较地址
'''

class LockList(GObject):

    def __init__(self):
        super(LockList, self).__init__();
        
        self.mTypeId = "LockList";
        
        self.m_visitMutex = MMutex();
        self.mList = MList();


    def Count(self): 
        self.m_visitMutex.lock();
        return self.mList.length();
        self.m_visitMutex.unlock();


    def Add(self, item):
        self.m_visitMutex.lock();
        self.mList.Add(item);
        self.m_visitMutex.unlock();

    def Remove(self, item):
        self.m_visitMutex.lock();
        self.mList.Remove(item);
        self.m_visitMutex.unlock();


    def RemoveAt(self, index):
        self.m_visitMutex.lock();
        self.mList.RemoveAt(index);
        self.m_visitMutex.unlock();


    def IndexOf(self, item):
        self.m_visitMutex.lock();
        self.mList.IndexOf(item);
        self.m_visitMutex.unlock();


