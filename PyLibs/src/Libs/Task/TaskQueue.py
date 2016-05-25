﻿#-*- encoding=utf-8 -*-

from Libs.DataStruct.LockQueue import LockQueue

class TaskQueue(LockQueue):

    def __init__(self):
        super(TaskQueue, self).__init__();

        self.mTypeId = "TaskQueue";
        
    
    def setTaskThreadPool(self, value):
        self.m_pTaskThreadPool = value;


    def push(self, item):
        super(TaskQueue, self).push(item);

        # 检查是否有线程空闲，如果有就唤醒
        self.m_pTaskThreadPool.notifyIdleThread();

