'''
Created on 2015年2月13日

@author: Administrator
'''

from ProtocolAnalysis.CPPParse import CppItemBase

class CppClassItem(CppItemBase.CppItemBase):
    '''
    classdocs
    '''


    def __init__(self, params):
        '''
        Constructor
        '''
        super(CppClassItem, self).__init__(CppItemBase.CppItemBase.eCppClassItem)
        
        
        
        
        