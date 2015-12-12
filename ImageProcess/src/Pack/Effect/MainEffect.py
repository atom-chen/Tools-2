# -*- coding: utf-8 -*-
'''
Created on 2013-4-12

@author: Administrator
'''

#import sys
from Pack.Frame.config import Config
from pack.eff.epackage import startPack
from Pack.Frame.logger import Logger

def main():
    #for arg in sys.argv:
    #    sys.stdout.write(arg)
    #    sys.stdout.flush()
    
    #idx = 0
    #while (idx < 10):
    #    sys.stdout.write(str(idx))
    #    sys.stdout.flush()
    #    idx += 1
    
    #print("end")
    
    #Config.instance().readInit("../config.txt")
    #Config.instance().readNameFile("../effname.txt")
    
    #Config.instance().readInit("config.txt")
    #Config.instance().readNameFile("effname.txt")
    
    #Config.instance().initPath(Config.EffPy)
    Logger.instance().loggerESubPro('进入特效打包子进程')
    Config.instance().readInit(Config.instance().configFile)
    Config.instance().readEffNameFile(Config.instance().effNameFile)
    
    startPack(Config.instance())
    
    #释放资源
    Logger.instance().loggerESubPro('退出特效打包子进程')
    Logger.instance().loggerECloseSubPro()

main()
