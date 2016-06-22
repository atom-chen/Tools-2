# -*- coding: utf-8 -*-

'''
@brief 可被调用的函数对象
'''

from Libs.Core.GObject import GObject;

class ICalleeObject(GObject):
    
    def __init__(self):
        super(ICalleeObject, self).__init__();
        
        self.mTypeId = "ICalleeObject";

    
    def call(self, dispObj):
        pass;
    
    