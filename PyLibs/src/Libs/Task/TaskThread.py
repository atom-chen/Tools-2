﻿#-*- encoding=utf-8 -*-

from Libs.Thread.MThread import MThread
from Libs.Thread.MCondition import MCondition

'''
@brief 任务线程
'''

class TaskThread(MThread):

    def __init__(self, name, taskQueue):
        super(TaskThread, self).__init__();
        self.m_taskQueue = taskQueue;
        self.m_condition = MCondition(name);


    '''
    brief 线程回调函数
    '''
    def threadHandle(self):
        while (not self.m_ExitFlag):
            self.m_curTask = self.m_taskQueue.pop();
            if(self.m_curTask != None):
                self.m_curTask.runTask();
            else:
                self.m_condition.wait();
            

    def notifySelf(self):
        if(self.m_condition.canEnterWait):
            self.m_condition.notifyAll();
            return True;

        return False;

    