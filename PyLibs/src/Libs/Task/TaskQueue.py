# -*- coding: utf-8 -*-

from Libs.DataStruct.LockQueue import LockQueue;

class TaskQueue(LockQueue):

    def __init__(self, name = ""):
        super(TaskQueue, self).__init__(name);

        self.mTypeId = "TaskQueue";
        
        self.mTaskThreadPool = None;
        
    
    def setTaskThreadPool(self, value):
        self.mTaskThreadPool = value;


    def push(self, item):
        super(TaskQueue, self).push(item);

        # 检查是否有线程空闲，如果有就唤醒
        self.mTaskThreadPool.notifyIdleThread();

