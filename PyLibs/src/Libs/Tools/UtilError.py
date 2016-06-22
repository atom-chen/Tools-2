#-*- encoding=utf-8 -*-

from Libs.Core.GObject import GObject;

'''
@brief: 异常处理
'''

class UtilError(GObject):

    @staticmethod
    def error(dest):
        raise Exception(dest);
