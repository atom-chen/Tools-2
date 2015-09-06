'''
Created on 2015年2月13日

@author: {Administrator}
'''

from ProtocolAnalysis.CppParse import CppItemBase
from ProtocolAnalysis.Core.Utils import Utils

class CppMultiComment(CppItemBase.CppItemBase):
    '''
    classdocs
    '''


    def __init__(self):
        '''
        Constructor
        '''
        super(CppMultiComment, self).__init__(CppItemBase.CppItemBase.eCppNSItem)
        
    
    def parseCppElem(self, strParam):
        super.parseCppElem(strParam)
        while len(strParam):
            oneToken = Utils.getToken(strParam)
            if oneToken[0:2] == "*/":
                break
        
        
    