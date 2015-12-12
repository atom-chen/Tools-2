# -*- coding: utf-8 -*-

'''
'''

import subprocess
from threading import Thread
import traceback
import sys

from Pack.Frame.Logger import Logger
from Pack.Frame.AppSys import AppSys
from Pack.Frame.Config import Config

class TerrainThread(Thread):
    def __init__(self, threadName):
        super(TerrainThread, self).__init__(name = threadName)  # must add

    def run(self):
        Logger.instance().loggerTer("tpack is running")
        #handle = subprocess.Popen(["python", "./eff/maineff.py", "test"], shell=True, stdout=subprocess.PIPE)
        if Config.instance().startType == Config.MainPy:
            handle = subprocess.Popen([Config.instance().m_commonCfg.python, Config.instance().terExePath, "test"], shell=True, stdout=subprocess.PIPE)
        else:
            handle = subprocess.Popen([Config.instance().terExePath, "test"], shell=True, stdout=subprocess.PIPE)
        while handle.poll() != 0:
            try:
                output, errout = handle.communicate()
            except:
                #有异常直接退出吧
                Logger.instance().loggerChar("异常退出")
                typeerr, value, tb = sys.exc_info()
                errstr = traceback.format_exception(typeerr, value, tb)
                Logger.instance().loggerChar(errstr)
                break
                
            #Logger.instance().loggerTer(output)
            Logger.instance().loggerTer(errout)
        
        if handle.returncode == 0:
            Logger.instance().loggerTer("正常退出")
        elif handle.returncode < 0:
            Logger.instance().loggerTer("信号中断退出")
        else:
            Logger.instance().loggerTer("子进程错误退出")
        
        # 不是仅仅打包 xml 就需要打包资源
        if not Config.instance().m_terCfg.m_bJustXml:
            try:
                handle = subprocess.Popen([Config.instance().m_commonCfg.flashcs, Config.instance().m_terCfg.jsfl, Config.instance().m_commonCfg.jsflstartparam])
                # 缩略图就不在这里启动了，直接在 jsfl 中启动
                #handle = subprocess.Popen([Config.instance().m_commonCfg.flashcs, Config.instance().m_terCfg.m_thumbnailsjsfl])
            except:
                Logger.instance().loggerTer("Flash CS cannot start")
        
        AppSys.instance().m_bOverTer = True
