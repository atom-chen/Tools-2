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
    def lzmaUnCompress():
        cmd = '"{0}" c -y {1}.7z -o *.txt'.format(AppSysBase.instance().m_config.m_z7z, AppSysBase.instance().m_pParamInfo.m_curUnCompressFullFileName)
        handle = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE)
        handle.wait()
        
    @staticmethod
    def lzmaCompress():
        cmd = '"{0}" a -t7z {1} {2}'.format(AppSysBase.instance().m_config.m_z7z, AppSysBase.instance().m_pParamInfo.m_curOutCompressFullFileName, AppSysBase.instance().m_pParamInfo.m_curInCompressFullFileName)
        handle = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE)
        #handle.wait()  # 防止死锁
        while handle.poll() != 0:
            try:
                output = handle.communicate()[0]
                AppSysBase.instance().m_logSys.info(output)
            except:
                exc_type, exc_value, exc_tb = sys.exc_info()
                output = "the exc type is: {0}, the exc value is: {1}, the exc tb is: ".format(exc_type, exc_value, exc_tb)
                AppSysBase.instance().m_logSys.info(output)
                traceback.print_exception(exc_type, exc_value, exc_tb)  # 格式化输出信息
        
        if handle.poll() != 0:          # 如果不能正常结束，就结束子进程
            subprocess.Popen.terminate()
        

'''
parameter info
'''
class ParamInfo(object):
    def __init__(self):
        self.m_curUnCompressFullFileName = ''
        self.m_curInCompressFullFileName = ''
        self.m_curOutCompressFullFileName = ''
    
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


