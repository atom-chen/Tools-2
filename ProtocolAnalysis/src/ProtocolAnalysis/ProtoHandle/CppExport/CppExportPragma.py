#-*- encoding=utf-8 -*-


from ProtocolAnalysis.Core.AppSysBase import AppSysBase
from ProtocolAnalysis.ProtoHandle.ProtoBase.ProtoElemBase import eProtoElemType

class CppExportPragma(object):
    '''
    classdocs
    '''


    def __init__(self, params):
        '''
        Constructor
        '''


    @staticmethod
    def exportPragmaBeforeNS(fHandle, file):
        for message in file.getProtoElemList():
            if message.getElemType() == eProtoElemType.ePackage:
                break
            elif message.getElemType() == eProtoElemType.ePragma:
                for pragma in message.getPragmaList():
                    AppSysBase.instance().getClsUtils().writeNewLine2File(fHandle)
                    pragmaFull = "#pragma {0}".format(pragma)
                    fHandle.write(pragmaFull)

                    
                    
    @staticmethod
    def exportPragmaAfterNS(fHandle, file):
        bFindNS = False
        for message in file.getProtoElemList():
            if message.getElemType() == eProtoElemType.ePackage:
                bFindNS = True
            elif message.getElemType() == eProtoElemType.ePragma:
                if bFindNS:
                    for pragma in message.getPragmaList():
                        AppSysBase.instance().getClsUtils().writeNewLine2File(fHandle)
                        pragmaFull = "#pragma {0}".format(pragma)
                        fHandle.write(pragmaFull)

