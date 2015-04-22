#-*- encoding=utf-8 -*-

'''
'''

import subprocess
import sys
import traceback
import os
import shutil

from FileDirDiff.Core.Config import Config
from FileDirDiff.Core.Logger import Logger

class CmdLine:
    @staticmethod
    def execSwift():
        cmd = 'java -jar %s xml2lib %s.xml %s.swc' % (Config.instance().swiftjar, ParamInfo.instance().m_swiftFullXmlFile, ParamInfo.instance().m_swiftFullSwcFile)
        handle = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE)
        handle.wait()
    
    @staticmethod
    def exec7z():
        cmd = '"%s" e -y %s.swc -o%s *.swf' % (Config.instance().z7z, ParamInfo.instance().m_swiftFullSwcFile, Config.instance().destrootpath + '/' + Config.instance().tmpDir)
        handle = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE)
        handle.wait()

'''
parameter info
'''
class ParamInfo(object):
    
    pInstance = None
    
    @staticmethod
    def instance():
        if ParamInfo.pInstance is None:
            ParamInfo.pInstance = ParamInfo()
        return ParamInfo.pInstance
    
    def __init__(self):
        self.m_swiftFullXmlFile = ''
        self.m_swiftFullSwcFile = ''
    
class FileOperate(object):
    @staticmethod
    def copyFile(srcfilename, destfilename):
        if os.path.isfile(srcfilename):
            try:
                shutil.copyfile(srcfilename, destfilename)
                Logger.instance().info("copy file success: " + srcfilename)
            except:
                # 错误输出
                Logger.instance().info("copy file error: " + srcfilename)
                typeerr, value, tb = sys.exc_info()
                errstr = traceback.format_exception(typeerr, value, tb)
                Logger.instance().info(errstr)

        else:
            Logger.instance().info("cannot find file: " + srcfilename)


