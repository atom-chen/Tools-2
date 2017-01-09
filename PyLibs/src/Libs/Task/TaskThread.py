# -*- coding: utf-8 -*-

import time;
from Libs.Thread.MThread import MThread;
from Libs.Thread.MCondition import MCondition;

'''
@brief 任务线程
'''

class TaskThread(MThread):

    def __init__(self, name, taskQueue):
        super(TaskThread, self).__init__(None, None, name);
        self.mTaskQueue = taskQueue;
        self.mCondition = MCondition(name);


    '''
    brief 线程回调函数
    '''
    #def threadHandle(self, intParam, strParam):
    def threadHandle(self):
        while (not self.mIsExitFlag):
            if(self.mCondition.acquire()):
                self.m_curTask = self.mTaskQueue.pop();
                if(self.m_curTask != None):
                    self.m_curTask.runTask();
                else:
                    self.mCondition.wait();
                    
                self.mCondition.release();
                
                time.sleep(2);
            

    def notifySelf(self):
        if(self.mCondition.acquire()):
            self.mCondition.notifyAll();
            self.mCondition.release();
            return True;

        return False;

    