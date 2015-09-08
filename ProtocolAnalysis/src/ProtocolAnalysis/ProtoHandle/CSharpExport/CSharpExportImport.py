#-*- encoding=utf-8 -*-


from ProtocolAnalysis.Core.AppSysBase import AppSysBase


class CSharpExportImport(object):
    '''
    classdocs
    '''


    def __init__(self):
        '''
        Constructor
        '''
        
    @staticmethod
    def exportImport(fHandle, protoElem):
        for importNS in protoElem.getHeaderList():
            nsStr = "using {0};".format(importNS)
            fHandle.write(nsStr)
            
            AppSysBase.instance().getClsUtils().writeNewLine2File(fHandle)
        
        