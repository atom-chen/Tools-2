#-*- encoding=utf-8 -*-

'''
@brief 所有全部变量实例化都在这里，防止循环导入
'''

from FileDirDiff.Core.GlobalData import GlobalData
from FileDirDiff.Core.AppSys import AppSys

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
        GlobalData.instance()   # 实例化自己
        GlobalData.g_pInstance.g_pAppSys = AppSys.instance()        # 实例化全局变量
        
        