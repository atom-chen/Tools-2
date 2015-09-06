#-*- encoding=utf-8 -*-

from ProtocolAnalysis.Core.Utils import Utils

class CppItemBase(object):
    '''
    classdocs
    '''
    eCppClassItem = 0,
    eCppNSItem = 1,
    eCppStructItem = 2,
    

    def __init__(self, cppelemtype):
        '''
        Constructor
        '''
        self.m_cppElemType = cppelemtype


    def parseCppElem(self, strParam):
        Utils.skipSpaceAndBr(strParam)          # 删除左边的空格
        pass;
    
    
    
    
    