# -*- coding: utf-8 -*-

'''
@brief: GObject
'''
class GObject(object):
    # Constructor
    def __init__(self):
        self.mTypeId = "GObject";      # 名字


    # 获取类型 Id
    def getTypeId(self):
        return self.mTypeId;

