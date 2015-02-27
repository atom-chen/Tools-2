'''
Created on 2014年1月11日

@author: hhh
@brief AppData 的接口
'''

class IAppData(object):
    pInstance = None
    
    @staticmethod
    def instance():
        return IAppData.pInstance

    def get_curverFileCount(self):
        return 0
    
    def add_curverFileCount(self, value):
        pass
