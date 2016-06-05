# -*- coding: utf-8 -*-

'''
@brief: MApp
'''

from Libs.Core.GObject import GObject
from QtToolSet.Common.QtToolSetSys import QtToolSetSys
from QtToolSet.Common.QtToolSetSysImpl import QtToolSetSysImpl
from Libs.FrameWork.Ctx import Ctx
from Libs.FrameWork.CtxImpl import CtxImpl

class MApp(GObject):
    
    def __init__(self):
        super(MApp, self).__init__();
        
        self.mTypeId = "MApp";

    
    def init(self):
        #实例化全局变量
        Ctx.msInstance = CtxImpl();
        QtToolSetSys.msInstance = QtToolSetSysImpl();
        QtToolSetSys.instance().init();



    
