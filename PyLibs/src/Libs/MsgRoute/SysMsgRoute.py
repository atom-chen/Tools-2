# -*- coding: utf-8 -*-

'''
@brief 系统消息流程，整个系统的消息分发都走这里，仅限单线程
'''

from Libs.DataStruct.LockQueue import LockQueue;

class SysMsgRoute(LockQueue):
    def __init__(self, name):
        pass;

