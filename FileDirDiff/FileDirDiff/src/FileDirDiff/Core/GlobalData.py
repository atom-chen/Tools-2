#-*- encoding=utf-8 -*-

'''
@brief 所有全部变量实例化都在这里，防止循环导入，使用方式 GlobalData.g_pAppSys.m_config ，不能 g_pAppSys.m_config ，这样使用是指在当前模块中的全局变量 g_pAppSys ，但是使用这种方法 PyDev  会提示一些错误，但是实际上是没有错误的，因为 g_pAppSys 是没有类型的， PyDev 不能推断是什么类型 
'''

g_pAppSys = None
