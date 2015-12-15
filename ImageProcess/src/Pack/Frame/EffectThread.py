# -*- coding: utf-8 -*-

'''
@brief effect thread
'''

import subprocess
from threading import Thread
import sys
import traceback

from Pack.Frame.Logger import Logger
from Pack.Frame.AppSys import AppSys
from Pack.Frame.Config import Config

class EffectThread(Thread):
    def __init__(self, threadName):
        super(EffectThread, self).__init__(name = threadName)  # must add

    def run(self):
        Logger.instance().loggerEff("epack is running")
        #handle = subprocess.Popen(["python", "./Effect/MainEffect.py", "test"], shell=True, stdout=subprocess.PIPE)
        if Config.instance().startType == Config.MainPy:
            handle = subprocess.Popen([Config.instance().m_commonCfg.python, Config.instance().effExePath, "test"], shell=True, stdout=subprocess.PIPE)
        else:
            handle = subprocess.Popen([Config.instance().effExePath, "test"], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        while handle.poll() != 0:
            try:
                output, errout = handle.communicate()
            except:
                #有异常直接退出吧
                Logger.instance().loggerEff("Eff 异常退出")
                typeerr, value, tb = sys.exc_info()
                errstr = traceback.format_exception(typeerr, value, tb)
                # bug 有时候这个返回的是 list
                if isinstance(errstr, list):
                    Logger.instance().loggerEff("".join(errstr))
                else:
                    Logger.instance().loggerEff(errstr)
                break
            
            Logger.instance().loggerEff(output)
            Logger.instance().loggerEff(errout)
        
        if handle.returncode == 0:
            Logger.instance().loggerEff("正常退出")
        elif handle.returncode < 0:
            Logger.instance().loggerEff("信号中断退出")
        else:
            Logger.instance().loggerEff("子进程错误退出")
        
        #继续打包特效资源，暂时没有实现

        AppSys.instance().m_bOverEff = True
