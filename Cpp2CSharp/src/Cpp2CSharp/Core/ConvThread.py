#-*- encoding=utf-8 -*-
'''
Created on 2015-2-1

@author: Administrator
'''


from Cpp2CSharp.Core.ThreadWrap import ThreadWrap
from Cpp2CSharp.Core.AppData import AppData

from Cpp2CSharp.Core.Config import Config
from Cpp2CSharp.Core.Logger import Logger
from Cpp2CSharp.Core.Utils import Utils
from Cpp2CSharp.Core.CodeConv import CodeConv

class ConvThread(ThreadWrap):
    
    def __init__(self, threadName):
        super(ConvThread, self).__init__(threadName = threadName)

    def run(self):
        AppData.instance().m_bConvOver = False
        Logger.instance().info("File Conv Start")
        
        Utils.makeDir(Config.instance().m_tmpCodePath)
        Utils.makeDir(Config.instance().m_destCodePath)
        
        Utils.traverseDirs(Config.instance().m_srcCodePath, CodeConv.pInstance.convCpp2CSharp)

        Logger.instance().info("File Conv End")
        AppData.instance().m_bConvOver = True


