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
        self.m_taskQueue = taskQueue;
        self.m_condition = MCondition(name);


    '''
    brief 线程回调函数
    '''
    #def threadHandle(self, intParam, strParam):
    def threadHandle(self):
        while (not self.m_ExitFlag):
            if(self.m_condition.acquire()):
                self.m_curTask = self.m_taskQueue.pop();
                if(self.m_curTask != None):
                    self.m_curTask.runTask();
                else:
                    self.m_condition.wait();
                    
                self.m_condition.release();
                
                time.sleep(2);
            

    def notifySelf(self):
        if(self.m_condition.acquire()):
            self.m_condition.notifyAll();
            self.m_condition.release();
            return True;

        return False;

    