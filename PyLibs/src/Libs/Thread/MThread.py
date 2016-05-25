﻿#-*- encoding=utf-8 -*-

from Libs.Core.GObject import GObject
import threading

'''
@brief 基本的线程
'''

#class MThread(Thread):
class MThread(GObject):
    m_sMainThreadID = 0;           # 主线程 id
    
    def __init__(self, func, param, name):
        super(MThread, self).__init__();
        
        self.mTypeId = "MThread";
        
        self.mThread = None;
        self.m_curThreadID = 0;     # 当前线程的 id
        self.m_cb = func;
        self.m_param = param;
        self.mName = name;
        self.m_ExitFlag = False;


    def setExitFlag(self, value):
        self.m_ExitFlag = value;


    def setCb(self, value):
        self.m_cb = value;


    def setParam(self, value):
        self.m_param = value;
        

    '''
    @brief 开启一个线程
    '''
    def start(self):
        if(self.mThread == None):
            self.mThread = threading.Thread(target = self.threadHandle, args=(0, "aaa"), name = self.mName); 

        self.mThread.Start();


    def join(self):
        self.mThread.Join();


    def run(self):
        pass;

    '''
    @brief 线程回调函数
    '''
    def threadHandle(self, params):
        self.getCurThreadID();

        if(self.m_cb != None):
            self.m_cb(self.m_param);



    def getCurThreadID(self):
        self.m_curThreadID = threading.current_thread.ident;       # 当前线程的 ID


    def isCurThread(self, threadID):
        return (self.m_curThreadID == threadID);


    @staticmethod
    def getMainThreadID():
        MThread.m_sMainThreadID = threading.current_thread.ident;


    @staticmethod
    def isMainThread():
        return (MThread.m_sMainThreadID == threading.current_thread.ident);


    @staticmethod
    def needMainThread():
        if (not MThread.isMainThread()):
            raise Exception("cannot call function in thread");



