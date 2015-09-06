#-*- encoding=utf-8 -*-

from ProtocolAnalysis.ProtoParse.CppExport import CppItemBase

class CppNameSpaceItem(CppItemBase):
    '''
    classdocs
    '''


    def __init__(self):
        '''
        Constructor
        '''
        super(CppNameSpaceItem, self).__init__(CppItemBase.CppItemBase.eCppNSItem)