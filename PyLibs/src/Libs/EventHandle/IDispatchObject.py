#-*- encoding=utf-8 -*-

'''
@brief 可分发的对象
'''

from Libs.Core.GObject import GObject

class IDispatchObject(GObject):
    def __init__(self):
        super(IDispatchObject, self).__init__();
        self.mTypeId = "IDispatchObject";


