#-*- encoding=utf-8 -*-

'''
@brief: 异常处理
'''

class UtilError(object):

    @staticmethod
    def error(dest):
        raise Exception(dest);
