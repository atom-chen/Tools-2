#-*- encoding=utf-8 -*-

'''
@brief 延迟添加的对象
'''
from Libs.Core.GObject import GObject

class IDelayHandleItem(GObject):
    
    def __init__(self):
        super(IDelayHandleItem, self).__init__();
        
        self.mTypeId = "IDelayHandleItem";


    def setClientDispose(self):
        pass;


    def getClientDispose(self):
        pass;


