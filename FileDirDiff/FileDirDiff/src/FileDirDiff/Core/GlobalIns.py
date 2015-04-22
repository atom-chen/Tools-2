#-*- encoding=utf-8 -*-

'''
@brief 所有全部变量实例化都在这里，防止循环导入
'''

from FileDirDiff.Core.AppSys import AppSys
from FileDirDiff.Core import Md5Checker
from FileDirDiff.Core.Config import Config
from FileDirDiff.Core.Utils import FileOperate
from FileDirDiff.Core.LogSys import LogSys
from FileDirDiff.Core.Md5Dir import Md5DirOperate

class GlobalIns(object):
    '''
    classdocs
    '''

    def __init__(self, params):
        '''
        Constructor
        '''
        pass
    
    @staticmethod
    def insGlobal():
        AppSys.instance();          # 初始化全局变量
        AppSys.instance().m_config = Config()
        AppSys.instance().m_logSys = LogSys()
        AppSys.instance().m_md5DirOperate = Md5DirOperate()
        AppSys.instance().Md5Checker = Md5Checker;         # 保存模块
        AppSys.instance().FileOperate = FileOperate;       # 保存模块
        
        