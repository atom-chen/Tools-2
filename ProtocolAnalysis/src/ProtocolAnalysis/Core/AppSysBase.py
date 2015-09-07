#-*- encoding=utf-8 -*-


class AppSysBase(object):
    '''
    classdocs
    '''
    
    g_pInstance = None
    
    @staticmethod
    def instance():
        return AppSysBase.g_pInstance


    def __init__(self):
        '''
        Constructor
        '''

    