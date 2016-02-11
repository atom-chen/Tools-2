# -*- coding: utf-8 -*-

'''
'''

import sys
import traceback
import os
import shutil
from Pack.Frame.Logger import Logger

class UtilTools(object):
    
    @staticmethod
    def copyFile(srcfilename, destfilename):
        if os.path.isfile(srcfilename):
            try:
                shutil.copyfile(srcfilename, destfilename)
            except:
                # 错误输出
                Logger.instance().loggerChar("copy file " + srcfilename + " error")
                typeerr, value, tb = sys.exc_info()
                errstr = traceback.format_exception(typeerr, value, tb)
                Logger.instance().loggerChar(errstr)

        else:
            Logger.instance().loggerChar("cannot find file " + srcfilename)








