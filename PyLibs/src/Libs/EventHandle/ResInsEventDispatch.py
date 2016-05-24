#-*- encoding=utf-8 -*-

'''
@brief 资源实例化事件分发器
'''

from Libs.EventHandle.EventDispatch import EventDispatch

class ResInsEventDispatch(EventDispatch):

    def __init__(self):
        super(ResInsEventDispatch, self).__init__();
        
        self.mTypeId = "ResInsEventDispatch";
        
        self.mIsValid = True;


    def setIsValid(self, value):
        self.mIsValid = value;


    def getIsValid(self):
        return self.mIsValid;


    def setInsGO(self, go):
        self.mInsGO = go;


    def getInsGO(self):
        return self.mInsGO;


    def dispatchEvent(self, dispatchObject):
        if(self.mIsValid):
            super(ResInsEventDispatch, self).dispatchEvent(dispatchObject);
        else:
            # 输出日志
            pass;


