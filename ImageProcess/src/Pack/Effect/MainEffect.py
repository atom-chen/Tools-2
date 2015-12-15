# -*- coding: utf-8 -*-

'''
'''

#import sys
from Pack.Frame.Config import Config
from Pack.Effect.EffectPack import startPack
from Pack.Frame.Logger import Logger

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
