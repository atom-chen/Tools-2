# -*- coding: utf-8 -*-

'''
@brief character thread
'''

import subprocess
from threading import Thread
import traceback
import sys

from Pack.Frame.AppSys import AppSys
from Pack.Frame.Logger import Logger
from Pack.Frame.Config import Config

class CharacterThread(Thread):
    def __init__(self, threadName):
        super(CharacterThread, self).__init__(name = threadName)  # must add

    def run(self):
        Logger.instance().loggerChar("cpack is 运行")
        if Config.instance().startType == Config.MainPy:
            handle = subprocess.Popen([Config.instance().m_commonCfg.python, Config.instance().charExePath, "中文"], shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        else:
            #handle = subprocess.Popen([Config.instance().charExePath, "中文"], shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
            handle = subprocess.Popen([Config.instance().charExePath, "中文"], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        
        # 或者由于信号退出，或者正在运行，或者正常退出，或者执行错误退出
        while handle.poll() == None:
            try:
                output, errout = handle.communicate()
            except:
                #有异常直接退出吧
                Logger.instance().loggerChar("异常退出")
                typeerr, value, tb = sys.exc_info()
                errstr = traceback.format_exception(typeerr, value, tb)
                Logger.instance().loggerChar(errstr)
                break
                
            #Logger.instance().loggerChar(output)
            Logger.instance().loggerChar(errout)
                
        if handle.returncode == 0:
            Logger.instance().loggerChar("正常退出")
        elif handle.returncode < 0:
            Logger.instance().loggerChar("信号中断退出")
        else:
            Logger.instance().loggerChar("子进程错误退出")
        
        # 继续打包资源，暂时没有实现
        
        AppSys.instance().m_bOverChar = True
