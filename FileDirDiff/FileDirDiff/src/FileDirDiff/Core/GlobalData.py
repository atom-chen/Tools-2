#-*- encoding=utf-8 -*-

'''
@brief 存放所有的全局变量
'''

class GlobalData(object):
    '''
    classdocs
    '''
    g_pInstance = None
    
    @staticmethod
    def instance():
        if GlobalData.g_pInstance == None:
            GlobalData.g_pInstance = GlobalData()
            
        return GlobalData.g_pInstance

    def __init__(self):
        '''
        Constructor
        '''
        self.g_pAppSys = None
        
