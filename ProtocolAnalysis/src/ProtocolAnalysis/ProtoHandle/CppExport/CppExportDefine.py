#-*- encoding=utf-8 -*-


from ProtocolAnalysis.Core.AppSysBase import AppSysBase


class CppExportDefine(object):
    '''
    classdocs
    '''


    def __init__(self, params):
        '''
        Constructor
        '''


    @staticmethod
    def exportHeaderDefineStart(fHandle, fileName):
        AppSysBase.instance().getClsUtils().writeNewLine2File(fHandle)
        fHandle.write("#ifndef _st{0}_h".format(fileName))
        AppSysBase.instance().getClsUtils().writeNewLine2File(fHandle)
        fHandle.write("#define _st{0}_h".format(fileName))


    @staticmethod
    def exportHeaderDefineEnd(fHandle, fileName):
        AppSysBase.instance().getClsUtils().writeNewLine2File(fHandle)
        fHandle.write("#endif")

