#-*- encoding=utf-8 -*-

'''
@brief AppSysBase.instance().m_config 这样访问 PyDev 中就没有红色提示错误
'''
class AppSysBase(object):
    '''
    classdocs
    '''
    g_pInstance = None
    
    
    @staticmethod
    def instance():
        #assert(False)   # 不能创建实例
        #if AppSysBase.g_pInstance is None:
        #    AppSysBase.g_pInstance = AppSysBase()
        return AppSysBase.g_pInstance


    def __init__(self, params):
        '''
        Constructor
        '''
        