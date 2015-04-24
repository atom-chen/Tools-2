#-*- encoding=utf-8 -*-

'''
'''

import subprocess
import sys
import traceback
import os
import shutil

from FileDirDiff.Core.AppSys import AppSysBase

class CmdLine:
    @staticmethod
    def exec7z():
        cmd = '"{0}" c -y {1}.txt -o {2}.txt' % (AppSysBase.instance().m_config.m_z7z, AppSysBase.instance().m_pParamInfo.m_curCompressFullFileName, AppSysBase.instance().m_config.m_destRootPath + '/' + AppSysBase.instance().m_config.m_tmpDir + "/" + "aaa")
        handle = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE)
        handle.wait()

'''
parameter info
'''
class ParamInfo(object):
    def __init__(self):
        self.m_curCompressFullFileName = ''
    
class FileOperate(object):
    @staticmethod
    def copyFile(srcfilename, destfilename):
        if os.path.isfile(srcfilename):
            try:
                shutil.copyfile(srcfilename, destfilename)
                AppSysBase.instance().m_logSys.info("copy file success: " + srcfilename)
            except:
                # 错误输出
                AppSysBase.instance().m_logSys.info("copy file error: " + srcfilename)
                typeerr, value, tb = sys.exc_info()
                errstr = traceback.format_exception(typeerr, value, tb)
                AppSysBase.instance().m_logSys.info(errstr)

        else:
            AppSysBase.instance().m_logSys.info("cannot find file: " + srcfilename)


