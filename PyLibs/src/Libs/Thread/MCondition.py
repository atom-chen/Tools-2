# -*- coding: utf-8 -*-

import threading;

'''
@brief 单一对象同步
'''

from Libs.Core.GObject import GObject

class MCondition(GObject):
    
    def __init__(self, name):
        super(MCondition, self).__init__();
        
        self.mTypeId = "MCondition";
        
        self.mName = name;
        self.mCond = threading.Condition();


    def wait(self):
        self.mCond.wait();


    def notifyAll(self):
        self.mCond.notify();


