#-*- encoding=utf-8 -*-

'''
@brief AppSys 的接口，如果有循环导入，就是用这个接口
'''

class IAppSys(object):
    pInstance = None
    
    @staticmethod
    def instance():
        return IAppSys.pInstance

    def get_curverFileCount(self):
        return 0
    
    def add_curverFileCount(self, value):
        pass
